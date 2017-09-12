#include "jit_common.hpp"

//#include "OrcLazyJIT.h"
//#include "RemoteJITUtils.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/CodeGen/LinkAllCodegenComponents.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/JITEventListener.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/ObjectCache.h"
#include "llvm/ExecutionEngine/OrcMCJITReplacement.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/Orc/OrcRemoteTargetClient.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Object/Archive.h"
#include "llvm/Object/ObjectFile.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/Memory.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/PluginLoader.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Instrumentation.h"
#include <cerrno>

using namespace llvm;

namespace {
    enum class JITKind { MCJIT, OrcMCJITReplacement, OrcLazy };

    cl::opt<std::string>
        TargetTriple("mtriple", cl::desc("Override target triple for module"));

    cl::opt<std::string>
        MArch("march",
                cl::desc("Architecture to generate assembly for (see --version)"));

    cl::opt<std::string>
        MCPU("mcpu",
                cl::desc("Target a specific cpu type (-mcpu=help for details)"),
                cl::value_desc("cpu-name"),
                cl::init(""));

    cl::list<std::string>
        MAttrs("mattr",
                cl::CommaSeparated,
                cl::desc("Target specific attributes (-mattr=help for details)"),
                cl::value_desc("a1,+a2,-a3,..."));

    cl::list<std::string>
        ExtraModules("extra-module",
                cl::desc("Extra modules to be loaded"),
                cl::value_desc("input bitcode"));

    cl::list<std::string>
        ExtraObjects("extra-object",
                cl::desc("Extra object files to be loaded"),
                cl::value_desc("input object"));

    cl::list<std::string>
        ExtraArchives("extra-archive",
                cl::desc("Extra archive files to be loaded"),
                cl::value_desc("input archive"));

    cl::opt<std::string>
        ObjectCacheDir("object-cache-dir",
                cl::desc("Directory to store cached object files "
                    "(must be user writable)"),
                cl::init(""));

    cl::opt<std::string>
        FakeArgv0("fake-argv0",
                cl::desc("Override the 'argv[0]' value passed into the executing"
                    " program"), cl::value_desc("executable"));

    cl::opt<Reloc::Model>
        RelocModel("relocation-model",
                cl::desc("Choose relocation model"),
                cl::init(Reloc::Default),
                cl::values(
                    clEnumValN(Reloc::Default, "default",
                        "Target default relocation model"),
                    clEnumValN(Reloc::Static, "static",
                        "Non-relocatable code"),
                    clEnumValN(Reloc::PIC_, "pic",
                        "Fully relocatable, position independent code"),
                    clEnumValN(Reloc::DynamicNoPIC, "dynamic-no-pic",
                        "Relocatable external references, non-relocatable code"),
                    clEnumValEnd));

    cl::opt<llvm::CodeModel::Model>
        CMModel("code-model",
                cl::desc("Choose code model"),
                cl::init(CodeModel::JITDefault),
                cl::values(clEnumValN(CodeModel::JITDefault, "default",
                        "Target default JIT code model"),
                    clEnumValN(CodeModel::Small, "small",
                        "Small code model"),
                    clEnumValN(CodeModel::Kernel, "kernel",
                        "Kernel code model"),
                    clEnumValN(CodeModel::Medium, "medium",
                        "Medium code model"),
                    clEnumValN(CodeModel::Large, "large",
                        "Large code model"),
                    clEnumValEnd));

    cl::opt<bool>
        GenerateSoftFloatCalls("soft-float",
                cl::desc("Generate software floating point library calls"),
                cl::init(false));

    cl::opt<llvm::FloatABI::ABIType>
        FloatABIForCalls("float-abi",
                cl::desc("Choose float ABI type"),
                cl::init(FloatABI::Default),
                cl::values(
                    clEnumValN(FloatABI::Default, "default",
                        "Target default float ABI type"),
                    clEnumValN(FloatABI::Soft, "soft",
                        "Soft float ABI (implied by -soft-float)"),
                    clEnumValN(FloatABI::Hard, "hard",
                        "Hard float ABI (uses FP registers)"),
                    clEnumValEnd));
}

int llvm_load_module_from_bc_file(char* file_name, sCLClass* klass)
{
    ExecutionEngine* EE = nullptr;

    LLVMContext& context = getGlobalContext();

    // Load the bitcode...
    SMDiagnostic Err;
    std::unique_ptr<Module> Owner = parseIRFile(file_name, Err, context);
    Module *Mod = Owner.get();
    if (!Mod) {
        Err.print(file_name, errs());
        return 1;
    }

    std::string ErrorMsg;
    EngineBuilder builder(std::move(Owner));
    builder.setMArch(MArch);
    builder.setMCPU(MCPU);
    builder.setMAttrs(MAttrs);
    builder.setRelocationModel(RelocModel);
    builder.setCodeModel(CMModel);
    builder.setErrorStr(&ErrorMsg);
    builder.setEngineKind(EngineKind::JIT);
    //builder.setUseOrcMCJITReplacement(UseJITKind == JITKind::OrcMCJITReplacement);

    // If we are supposed to override the target triple, do so now.
    if (!TargetTriple.empty())
        Mod->setTargetTriple(Triple::normalize(TargetTriple));

    // Enable MCJIT if desired.
    RTDyldMemoryManager *RTDyldMM = nullptr;
    RTDyldMM = new SectionMemoryManager();

    // Deliberately construct a temp std::unique_ptr to pass in. Do not null out
    // RTDyldMM: We still use it below, even though we don't own it.
    builder.setMCJITMemoryManager(
            std::unique_ptr<RTDyldMemoryManager>(RTDyldMM));

    builder.setOptLevel(CodeGenOpt::Default);

    TargetOptions Options;
    if (FloatABIForCalls != FloatABI::Default)
        Options.FloatABIType = FloatABIForCalls;

    builder.setTargetOptions(Options);

    EE = builder.create();
    if (!EE) {
        if (!ErrorMsg.empty())
            errs() << file_name << ": error creating EE: " << ErrorMsg << "\n";
        else
            errs() << file_name << ": unknown error creating EE!\n";
        exit(1);
    }

    for (unsigned i = 0, e = ExtraObjects.size(); i != e; ++i) {
        ErrorOr<object::OwningBinary<object::ObjectFile>> Obj =
            object::ObjectFile::createObjectFile(ExtraObjects[i]);
        if (!Obj) {
            Err.print(file_name, errs());
            return 1;
        }
        object::OwningBinary<object::ObjectFile> &O = Obj.get();
        EE->addObjectFile(std::move(O));
    }

    for (unsigned i = 0, e = ExtraArchives.size(); i != e; ++i) {
        ErrorOr<std::unique_ptr<MemoryBuffer>> ArBufOrErr =
            MemoryBuffer::getFileOrSTDIN(ExtraArchives[i]);
        if (!ArBufOrErr) {
            Err.print(file_name, errs());
            return 1;
        }
        std::unique_ptr<MemoryBuffer> &ArBuf = ArBufOrErr.get();

        ErrorOr<std::unique_ptr<object::Archive>> ArOrErr =
            object::Archive::create(ArBuf->getMemBufferRef());
        if (std::error_code EC = ArOrErr.getError()) {
            errs() << EC.message();
            return 1;
        }
        std::unique_ptr<object::Archive> &Ar = ArOrErr.get();

        object::OwningBinary<object::Archive> OB(std::move(Ar), std::move(ArBuf));

        EE->addArchive(std::move(OB));
    }

    // The following functions have no effect if their respective profiling
    // support wasn't enabled in the build configuration.
    EE->RegisterJITEventListener(
            JITEventListener::createOProfileJITEventListener());
    EE->RegisterJITEventListener(
            JITEventListener::createIntelJITEventListener());

    // Run static constructors.
    EE->finalizeObject();
    EE->runStaticConstructorsDestructors(false);

    klass->RTDyldMM = RTDyldMM;
    klass->mModule = Mod;
    klass->EE = EE;

    return 0;
}

static BOOL llvm_call_method_from_module(Module* module, RTDyldMemoryManager* RTDyldMM, ExecutionEngine* EE, char* method_path2, CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address, int var_num, sConst* constant, sByteCode* code)
{
    Function* fun = module->getFunction(method_path2);

    fJITMethodType fun2 = (fJITMethodType)EE->getFunctionAddress(fun->getName().str());

    if(fun2) {
        BOOL result = fun2(stack_ptr, lvar, info, stack, stack_ptr_address, var_num, constant, code);

        return result;
    }
    else {
        fprintf(stderr, "%s function is not found\n", method_path2);
        return FALSE;
    }
}

static void llvm_finalize_ee()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        sCLClass* klass = p->mItem;
        
        ExecutionEngine* ee = (ExecutionEngine*)klass->EE;

        if(ee) {
            ee->runStaticConstructorsDestructors(true);
            delete ee;
        }

        p = p->mNextClass;
    }
}

extern "C" 
{
struct sCLVALUEAndBoolResult gCLValueAndBoolStructMemory;
struct sPointerAndBoolResult gCLPointerAndBoolStructMemory;

CLObject* gJITObjects;
int gNumJITObjects;
int gSizeJITObjects;

void init_jit_objects()
{
    gSizeJITObjects = 1024;
    gJITObjects = (CLObject*)MCALLOC(1, sizeof(CLObject)*gSizeJITObjects);
    gNumJITObjects = 0;
}

void free_jit_objects()
{
    MFREE(gJITObjects);
}

void push_jit_object(CLObject obj)
{
    if(gNumJITObjects >= gSizeJITObjects) {
        int new_size = gSizeJITObjects * 2;
        gJITObjects = (CLObject*)MREALLOC(gJITObjects, sizeof(CLObject)*new_size);
        memset(gJITObjects + gSizeJITObjects, 0, sizeof(CLObject)*(new_size - gSizeJITObjects));

        gSizeJITObjects = new_size;
    }

    gJITObjects[gNumJITObjects] = obj;
    gNumJITObjects++;
}

//////////////////////////////////////////////////
// JIT runtime functions
//////////////////////////////////////////////////
char* get_try_catch_label_name(sVMInfo* info)
{
    return info->try_catch_label_name;
}

void try_function(sVMInfo* info, int catch_label_name_offset, int try_offset, sByteCode* code, sConst* constant)
{
    if(catch_label_name_offset != 0) {
        info->try_catch_label_name = CONS_str(constant, catch_label_name_offset);
    }
    else {
        info->try_catch_label_name = NULL;
    }
    info->try_offset = try_offset;
    info->try_code = code;
}

struct sCLVALUEAndBoolResult* get_field_from_object(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject obj, int field_index)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3)");
        result->result1.mLongValue = 0;
        result->result2 = 0;

        return result;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(37)");
        result->result1.mLongValue = 0;
        result->result2 = 0;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(1)");
        result->result1.mLongValue = 0;
        result->result2 = 0;
        return result;
    }

    CLVALUE value = object_pointer->mFields[field_index];

    result->result1 = value;
    result->result2 = 1;

    return result;
}

CLObject get_string_object_of_object_name(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    CLObject object2 = create_string_object(CLASS_NAME(object_data->mClass));

    return object2;
}

BOOL call_invoke_method(sCLClass* klass, int method_index, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    sCLMethod* method = klass->mMethods + method_index;
    return invoke_method(klass, method, stack, var_num, stack_ptr, info);
}

BOOL call_invoke_virtual_method(int offset, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sConst* constant, CLObject object)
{
    /// go ///
    sCLObject* object_data = CLOBJECT(object);

    sCLClass* klass = object_data->mClass;

    MASSERT(klass != NULL);

    char* method_name_and_params = CONS_str(constant, offset);

    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    if(method == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_VIRTUAL_METHOD: Method not found");
        return FALSE;
    }
    else {
        if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL call_invoke_dynamic_method(int offset, int offset2, int num_params, int static_, int num_method_chains, int max_method_chains, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant)
{
    /// none static method ////
    if(static_ == 0) {
        int num_real_params = num_params + 1;
        char* method_name = CONS_str(constant, offset2);

        CLObject object = ((*stack_ptr)-num_real_params)->mObjectValue;

        sCLObject* object_data = CLOBJECT(object);

        sCLClass* klass = object_data->mClass;

        MASSERT(klass != NULL);

        if(klass->mCallingMethodIndex == -1) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_DYNAMIC_METHOD: Method not found(1)");
            return FALSE;
        }

        sCLMethod* method = klass->mMethods + klass->mCallingMethodIndex;

        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            CLObject object = ((*stack_ptr)-num_params + i)->mObjectValue;

            elements[i] = object;
        }

        CLObject carray = create_carray_object_with_elements(num_params, elements);

        gGlobalStackPtr->mObjectValue = carray;
        gGlobalStackPtr++;

        (*stack_ptr)-=num_params;

        (*stack_ptr)->mObjectValue = create_string_object(method_name);
        (*stack_ptr)++;
        (*stack_ptr)->mObjectValue = carray;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = num_method_chains;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = max_method_chains;
        (*stack_ptr)++;

        gGlobalStackPtr--;

        if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
            return FALSE;
        }
    }
    /// static method ///
    else {
        char* class_name = CONS_str(constant, offset);
        char* method_name = CONS_str(constant, offset2);

        sCLClass* klass = get_class_with_load_and_initialize(class_name);

        if(klass == NULL) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(38)");
            return FALSE;
        }

        if(klass->mCallingClassMethodIndex == -1) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_DYNAMIC_METHOD: Method not found(2)");
            return FALSE;
        }

        sCLMethod* method = klass->mMethods + klass->mCallingClassMethodIndex;

        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            CLObject object = ((*stack_ptr)-num_params + i)->mObjectValue;

            elements[i] = object;
        }

        CLObject carray = create_carray_object_with_elements(num_params, elements);

        gGlobalStackPtr->mObjectValue = carray;
        gGlobalStackPtr++;

        (*stack_ptr)-=num_params;

        (*stack_ptr)->mObjectValue = create_string_object(method_name);
        (*stack_ptr)++;
        (*stack_ptr)->mObjectValue = carray;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = num_method_chains;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = max_method_chains;
        (*stack_ptr)++;

        gGlobalStackPtr--;

        if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
            return FALSE;
        }
    }

    return TRUE;
}

void catch_function(sVMInfo* info, sByteCode* code) 
{
    if(info->try_code == code && info->try_offset != 0) {
        *info->try_pc = info->try_code->mCodes + info->try_offset;
        info->try_offset = 0;
        info->try_code = NULL;
    }
}

BOOL invoke_block_in_jit(int num_params, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    CLObject block_object = ((*stack_ptr)-num_params-1)->mObjectValue;

    if(!invoke_block(block_object, stack, var_num, num_params, stack_ptr, info)) 
    {
        return FALSE;
    }

    CLVALUE result = *((*stack_ptr)-1);

    (*stack_ptr) -= num_params+1+1;

    **stack_ptr = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL store_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject obj, CLVALUE value, int field_index)
{
    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(5)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(39)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(2)");
        return FALSE;
    }

    object_pointer->mFields[field_index] = value;

    return TRUE;
}

struct sCLVALUEAndBoolResult* load_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(40)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(3)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLField* field = klass->mClassFields + field_index;

    result->result1 = field->mValue;
    result->result2 = TRUE;

    return result;
}

BOOL store_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant, CLVALUE value)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(41)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(4)");
        return FALSE;
    }

    sCLField* field = klass->mClassFields + field_index;
    field->mValue = value;

    return TRUE;
}

BOOL run_store_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, int element_num, CLVALUE value)
{
    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(8)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "element index is invalid(1)");
        return FALSE;
    }

    object_pointer->mFields[element_num] = value;

    return TRUE;
}

int get_array_length(CLObject array_)
{
    sCLObject* array_data = CLOBJECT(array_);
    return array_data->mArrayNum;
}

struct sCLVALUEAndBoolResult* load_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, int element_num, int size)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(7)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "element index is invalid(2)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    result->result1 = object_pointer->mFields[element_num];
    result->result2 = TRUE;

    return result;
}

wchar_t char_uppercase(wchar_t c)
{
    wchar_t result = c;
    if(c >= 'a' && c <= 'z') {
        result = c - 'a' + 'A';
    }

    return result;
}

wchar_t char_lowercase(wchar_t c)
{
    wchar_t result = c;
    if(c >= 'A' && c <= 'Z') {
        result = c - 'A' + 'a';
    }

    return result;
}

BOOL get_regex_global(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mGlobal;
}

BOOL get_regex_ignorecase(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mIgnoreCase;
}

BOOL get_regex_multiline(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mMultiline;
}

BOOL get_regex_extended(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mExtended;
}

BOOL get_regex_dotall(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mDotAll;
}

BOOL get_regex_anchored(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mAnchored;
}

BOOL get_regex_dollar_endonly(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mDollarEndOnly;
}

BOOL get_regex_ungreedy(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mUngreedy;
}

struct sCLVALUEAndBoolResult* run_create_array(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(42)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject array_object = create_array_object(klass, num_elements);
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    sCLObject* object_data = CLOBJECT(array_object);

    int i;
    for(i=0; i<num_elements; i++) {
        object_data->mFields[i] = *((*stack_ptr)-1-num_elements+i);
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

////////////////////////////////////////
// JIT main
////////////////////////////////////////

static BOOL search_for_bc_file(char* class_name, char* class_bc_file_name, size_t class_bc_file_name_size)
{
    char* home = getenv("HOME");

    /// .clover directory ///
    if(home) {
        snprintf(class_bc_file_name, class_bc_file_name_size, "%s/.clover2/%s.bc", home, class_name);

        if(access(class_bc_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    char* cwd = getenv("PWD");

    /// current working directory ///
    if(cwd) {
        snprintf(class_bc_file_name, class_bc_file_name_size, "%s/%s.bc", cwd, class_name);

        if(access(class_bc_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL load_bc_file(sCLClass* klass)
{
    if(klass->mModule == NULL) {
        char* class_name = CLASS_NAME(klass);

        char class_bc_file_name[PATH_MAX+1];
        if(search_for_bc_file(class_name, class_bc_file_name, PATH_MAX)) {
            if(llvm_load_module_from_bc_file(class_bc_file_name, klass) != 0) {
                fprintf(stderr, "bc file not found error %s.bc\n", class_name);
                return FALSE;
            }
        }
    }

    return TRUE;
}

sCLClass* get_class_with_load_and_initialize_in_jit(sConst* constant, int offset)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        fprintf(stderr, "class not found error %s(54)\n", class_name);
        return NULL;
    }

    return klass;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info, CLVALUE** stack_ptr)
{
    int num_jit_objects = gNumJITObjects;

    klass->mMethodCallCount++;

klass->mMethodCallCount = 1000;

    if(klass->mMethodCallCount > 100) {
        if(!load_bc_file(klass)) {
            return FALSE;
        }
    }

    if(klass->mModule != NULL && strcmp(METHOD_NAME2(klass, method), "initialize") != 0 && strcmp(METHOD_NAME2(klass, method), "finalize") != 0 && !(method->mFlags & METHOD_FLAGS_NATIVE)) 
    {
        char method_path2[METHOD_NAME_MAX + 128];
        create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);

        CLVALUE* stack_ptr = stack + var_num;
        CLVALUE* lvar = stack;

        sCLStack* stack_id = append_stack_to_stack_list(stack, &stack_ptr);

        info->current_stack = stack;        // for invoking_block in native method
        info->current_var_num = var_num;
        info->stack_id = stack_id;

        if(!llvm_call_method_from_module((Module*)klass->mModule, (RTDyldMemoryManager*)klass->RTDyldMM, (ExecutionEngine*)klass->EE, method_path2, stack_ptr, lvar, info, stack, &stack_ptr, var_num, constant, code)) 
        {
            remove_stack_to_stack_list(stack_id);
            gNumJITObjects = num_jit_objects;
            return FALSE;
        }

        remove_stack_to_stack_list(stack_id);
    }
    else {
        BOOL result = vm(code, constant, stack, var_num, klass, info);

        if(!result) {
            gNumJITObjects = num_jit_objects;
            return FALSE;
        }
    }

    gNumJITObjects = num_jit_objects;

    return TRUE;
}

void jit_init_on_runtime()
{
    gCLValueAndBoolStructMemory.result1.mIntValue = 0;
    gCLValueAndBoolStructMemory.result2 = 0;

    gCLPointerAndBoolStructMemory.result1 = NULL;
    gCLPointerAndBoolStructMemory.result2 = FALSE;

    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    init_jit_objects();
}

void jit_final_on_runtime()
{
    llvm_finalize_ee();
    //llvm_shutdown();
    free_jit_objects();
}


} // extern "C"
