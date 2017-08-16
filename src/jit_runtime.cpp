#include "jit_common.hpp"
/*
#include "llvm/IR/LLVMContext.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/Triple.h"
//#include "llvm/Bitcode/BitcodeReader.h"
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

#ifdef __CYGWIN__
#include <cygwin/version.h>
#if defined(CYGWIN_VERSION_DLL_MAJOR) && CYGWIN_VERSION_DLL_MAJOR<1007
#define DO_NOTHING_ATEXIT 1
#endif
#endif

using namespace llvm;

#define DEBUG_TYPE "lli"

namespace {

  enum class JITKind { MCJIT, OrcMCJITReplacement, OrcLazy };

  cl::opt<std::string>
  InputFile(cl::desc("<input bitcode>"), cl::Positional, cl::init("-"));

  cl::list<std::string>
  InputArgv(cl::ConsumeAfter, cl::desc("<program arguments>..."));

  cl::opt<bool> ForceInterpreter("force-interpreter",
                                 cl::desc("Force interpretation: disable JIT"),
                                 cl::init(false));

  cl::opt<JITKind> UseJITKind("jit-kind",
                              cl::desc("Choose underlying JIT kind."),
                              cl::init(JITKind::MCJIT),
                              cl::values(
                                clEnumValN(JITKind::MCJIT, "mcjit",
                                           "MCJIT"),
                                clEnumValN(JITKind::OrcMCJITReplacement,
                                           "orc-mcjit",
                                           "Orc-based MCJIT replacement"),
                                clEnumValN(JITKind::OrcLazy,
                                           "orc-lazy",
                                           "Orc-based lazy JIT.")));

  // The MCJIT supports building for a target address space separate from
  // the JIT compilation process. Use a forked process and a copying
  // memory manager with IPC to execute using this functionality.
  cl::opt<bool> RemoteMCJIT("remote-mcjit",
    cl::desc("Execute MCJIT'ed code in a separate process."),
    cl::init(false));

  // Manually specify the child process for remote execution. This overrides
  // the simulated remote execution that allocates address space for child
  // execution. The child process will be executed and will communicate with
  // lli via stdin/stdout pipes.
  cl::opt<std::string>
  ChildExecPath("mcjit-remote-process",
                cl::desc("Specify the filename of the process to launch "
                         "for remote MCJIT execution.  If none is specified,"
                         "\n\tremote execution will be simulated in-process."),
                cl::value_desc("filename"), cl::init(""));

  // Determine optimization level.
  cl::opt<char>
  OptLevel("O",
           cl::desc("Optimization level. [-O0, -O1, -O2, or -O3] "
                    "(default = '-O2')"),
           cl::Prefix,
           cl::ZeroOrMore,
           cl::init(' '));

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

  cl::opt<std::string>
  EntryFunc("entry-function",
            cl::desc("Specify the entry function (default = 'main') "
                     "of the executable"),
            cl::value_desc("function"),
            cl::init("main"));

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

  cl::opt<bool>
  EnableCacheManager("enable-cache-manager",
        cl::desc("Use cache manager to save/load mdoules"),
        cl::init(false));

  cl::opt<std::string>
  ObjectCacheDir("object-cache-dir",
                  cl::desc("Directory to store cached object files "
                           "(must be user writable)"),
                  cl::init(""));

  cl::opt<std::string>
  FakeArgv0("fake-argv0",
            cl::desc("Override the 'argv[0]' value passed into the executing"
                     " program"), cl::value_desc("executable"));

  cl::opt<bool>
  DisableCoreFiles("disable-core-files", cl::Hidden,
                   cl::desc("Disable emission of core files if possible"));

  cl::opt<bool>
  NoLazyCompilation("disable-lazy-compilation",
                  cl::desc("Disable JIT lazy compilation"),
                  cl::init(false));

  cl::opt<Reloc::Model> RelocModel(
      "relocation-model", cl::desc("Choose relocation model"),
      cl::values(
          clEnumValN(Reloc::Static, "static", "Non-relocatable code"),
          clEnumValN(Reloc::PIC_, "pic",
                     "Fully relocatable, position independent code"),
          clEnumValN(Reloc::DynamicNoPIC, "dynamic-no-pic",
                     "Relocatable external references, non-relocatable code")));

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
                                "Large code model")));

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
                                "Hard float ABI (uses FP registers)")));

  ExitOnError ExitOnErr;
}

//===----------------------------------------------------------------------===//
// Object cache
//
// This object cache implementation writes cached objects to disk to the
// directory specified by CacheDir, using a filename provided in the module
// descriptor. The cache tries to load a saved object using that path if the
// file exists. CacheDir defaults to "", in which case objects are cached
// alongside their originating bitcodes.
//
class LLIObjectCache : public ObjectCache {
public:
  LLIObjectCache(const std::string& CacheDir) : CacheDir(CacheDir) {
    // Add trailing '/' to cache dir if necessary.
    if (!this->CacheDir.empty() &&
        this->CacheDir[this->CacheDir.size() - 1] != '/')
      this->CacheDir += '/';
  }
  ~LLIObjectCache() override {}

  void notifyObjectCompiled(const Module *M, MemoryBufferRef Obj) override {
    const std::string &ModuleID = M->getModuleIdentifier();
    std::string CacheName;
    if (!getCacheFilename(ModuleID, CacheName))
      return;
    if (!CacheDir.empty()) { // Create user-defined cache dir.
      SmallString<128> dir(sys::path::parent_path(CacheName));
      sys::fs::create_directories(Twine(dir));
    }
    std::error_code EC;
    raw_fd_ostream outfile(CacheName, EC, sys::fs::F_None);
    outfile.write(Obj.getBufferStart(), Obj.getBufferSize());
    outfile.close();
  }

  std::unique_ptr<MemoryBuffer> getObject(const Module* M) override {
    const std::string &ModuleID = M->getModuleIdentifier();
    std::string CacheName;
    if (!getCacheFilename(ModuleID, CacheName))
      return nullptr;
    // Load the object from the cache filename
    ErrorOr<std::unique_ptr<MemoryBuffer>> IRObjectBuffer =
        MemoryBuffer::getFile(CacheName, -1, false);
    // If the file isn't there, that's OK.
    if (!IRObjectBuffer)
      return nullptr;
    // MCJIT will want to write into this buffer, and we don't want that
    // because the file has probably just been mmapped.  Instead we make
    // a copy.  The filed-based buffer will be released when it goes
    // out of scope.
    return MemoryBuffer::getMemBufferCopy(IRObjectBuffer.get()->getBuffer());
  }

private:
  std::string CacheDir;

  bool getCacheFilename(const std::string &ModID, std::string &CacheName) {
    std::string Prefix("file:");
    size_t PrefixLength = Prefix.length();
    if (ModID.substr(0, PrefixLength) != Prefix)
      return false;
        std::string CacheSubdir = ModID.substr(PrefixLength);
#if defined(_WIN32)
        // Transform "X:\foo" => "/X\foo" for convenience.
        if (isalpha(CacheSubdir[0]) && CacheSubdir[1] == ':') {
          CacheSubdir[1] = CacheSubdir[0];
          CacheSubdir[0] = '/';
        }
#endif
    CacheName = CacheDir + CacheSubdir;
    size_t pos = CacheName.rfind('.');
    CacheName.replace(pos, CacheName.length() - pos, ".o");
    return true;
  }
};

// On Mingw and Cygwin, an external symbol named '__main' is called from the
// generated 'main' function to allow static initialization.  To avoid linking
// problems with remote targets (because lli's remote target support does not
// currently handle external linking) we add a secondary module which defines
// an empty '__main' function.
static void addCygMingExtraModule(ExecutionEngine &EE, LLVMContext &Context,
                                  StringRef TargetTripleStr) {
  IRBuilder<> Builder(Context);
  Triple TargetTriple(TargetTripleStr);

  // Create a new module.
  std::unique_ptr<Module> M = make_unique<Module>("CygMingHelper", Context);
  M->setTargetTriple(TargetTripleStr);

  // Create an empty function named "__main".
  Function *Result;
  if (TargetTriple.isArch64Bit()) {
    Result = Function::Create(
      TypeBuilder<int64_t(void), false>::get(Context),
      GlobalValue::ExternalLinkage, "__main", M.get());
  } else {
    Result = Function::Create(
      TypeBuilder<int32_t(void), false>::get(Context),
      GlobalValue::ExternalLinkage, "__main", M.get());
  }
  BasicBlock *BB = BasicBlock::Create(Context, "__main", Result);
  Builder.SetInsertPoint(BB);
  Value *ReturnVal;
  if (TargetTriple.isArch64Bit())
    ReturnVal = ConstantInt::get(Context, APInt(64, 0));
  else
    ReturnVal = ConstantInt::get(Context, APInt(32, 0));
  Builder.CreateRet(ReturnVal);

  // Add this new module to the ExecutionEngine.
  EE.addModule(std::move(M));
}

CodeGenOpt::Level getOptLevel() {
  switch (OptLevel) {
  default:
    errs() << "lli: Invalid optimization level.\n";
    exit(1);
  case '0': return CodeGenOpt::None;
  case '1': return CodeGenOpt::Less;
  case ' ':
  case '2': return CodeGenOpt::Default;
  case '3': return CodeGenOpt::Aggressive;
  }
  llvm_unreachable("Unrecognized opt level.");
}

LLVM_ATTRIBUTE_NORETURN
static void reportError(SMDiagnostic Err, const char *ProgName) {
  Err.print(ProgName, errs());
  exit(1);
}
*/







//std::unique_ptr<CloverJIT> TheJIT;

extern "C" 
{
struct sCLVALUEAndBoolResult gCLValueAndBoolStructMemory;

sCLClass* get_class_with_load_and_initialize_in_jit(char* class_name);

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
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(4)");
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

        sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

        if(klass == NULL) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(3)");
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
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(6)");
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

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(7)");
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

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(9)");
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

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(11)");
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

struct sCLVALUEAndBoolResult* run_create_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject array_object = create_carray_object();
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_carray_object(array_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_equalable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject array_object = create_equalable_carray_object();
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_equalable_carray_object(array_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_sortable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject array_object = create_sortable_carray_object();
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_sortable_carray_object(array_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject list_object = create_list_object();
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_list_object(list_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = list_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_sortable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject list_object = create_sortable_list_object();
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_sortable_list_object(list_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = list_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_equalable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject list_object = create_equalable_list_object();
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_equalable_list_object(list_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = list_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_tuple(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    CLObject tuple_object = create_tuple_object(num_elements);

    (*stack_ptr)->mObjectValue = tuple_object; // push object
    (*stack_ptr)++;

    CLObject items[TUPLE_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_tuple_object(tuple_object, num_elements, items, stack, var_num, stack_ptr, info))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = tuple_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_hash(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int class_name_offset2, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);
    char* class_name2 = CONS_str(constant, class_name_offset2);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(14)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLClass* klass2 = get_class_with_load_and_initialize_in_jit(class_name2);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(15)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject keys[HASH_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        keys[i] = ((*stack_ptr) - num_elements * 2 + i * 2)->mObjectValue;
    }

    CLObject items[HASH_VALUE_ELEMENT_MAX];

    for(i=0; i<num_elements; i++) {
        items[i] = ((*stack_ptr) - num_elements * 2 + i * 2 + 1)->mObjectValue;
    }

    CLObject hash_object = create_hash_object();
    (*stack_ptr)->mObjectValue = hash_object; // push object
    (*stack_ptr)++;

    if(!initialize_hash_object(hash_object, num_elements, keys, items, stack, var_num, stack_ptr, info, klass, klass2))
    {
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements*2;

    result->result1.mObjectValue = hash_object;
    result->result2 = TRUE;

    return result;
}

CLObject run_create_block_object(CLVALUE** stack_ptr, CLVALUE* stack, sConst* constant, int code_offset, int code_len, int constant_offset, int constant_len, int block_var_num, int parent_var_num, BOOL lambda, sVMInfo* info)
{
    sByteCode codes2;
    codes2.mCodes = CONS_str(constant, code_offset);
    codes2.mLen = code_len;

    sConst constant2;
    constant2.mConst = CONS_str(constant, constant_offset);
    constant2.mLen = constant_len;

    CLVALUE* parent_stack = stack;

    CLObject block_object = create_block_object(&codes2, &constant2, parent_stack, parent_var_num, block_var_num, info->stack_id, lambda);

    return block_object;
}

struct sPointerAndBoolResult run_load_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, CLObject obj)
{
    struct sPointerAndBoolResult result;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(4)");
        result.result1 = NULL;
        result.result2 = FALSE;
        return result;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(5)");
        result.result1 = NULL;
        result.result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(5)");
        result.result1 = NULL;
        result.result2 = FALSE;
        return result;
    }

    char* value = (char*)&object_pointer->mFields[field_index];
    result.result1 = value;
    result.result2 = TRUE;
    return result;
}

struct sPointerAndBoolResult run_load_class_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    struct sPointerAndBoolResult result;

    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(8)");
        result.result1 = NULL;
        result.result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(6)");
        result.result1 = NULL;
        result.result2 = FALSE;
        return result;
    }

    sCLField* field = klass->mClassFields + field_index;
    char* value = (char*)&field->mValue;

    result.result1 = value;
    result.result2 = TRUE;

    return result;
}

CLObject run_int_to_string_cast(int n)
{
    char buf[32];
    snprintf(buf, 32, "%d", n);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_long_to_string_cast(long l)
{
    char buf[32];
    snprintf(buf, 32, "%ld", l);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_uint_to_string_cast(unsigned int n)
{
    char buf[32];
    snprintf(buf, 32, "%u", n);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_ulong_to_string_cast(long l)
{
    char buf[32];
    snprintf(buf, 32, "%lu", l);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_float_to_string_cast(float f)
{
    char buf[32];
    snprintf(buf, 32, "%f", f);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_double_to_string_cast(double d)
{
    char buf[32];
    snprintf(buf, 32, "%lf", d);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_char_to_string_cast(wchar_t c)
{
    char buf[32];
    snprintf(buf, 32, "%lc", c);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_regex_to_string_cast(CLObject regex)
{
    sRegexObject* object_data = CLREGEX(regex);

    CLObject str = create_string_object(object_data->mRegexString);

    return str;
}

CLObject run_bool_to_string_cast(BOOL b)
{
    char buf[32];
    if(b) {
        snprintf(buf, 32, "true");
    }
    else {
        snprintf(buf, 32, "false");
    }

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_pointer_to_string_cast(char* p)
{
    char buf[32];
    snprintf(buf, 32, "%p", p);

    CLObject str = create_string_object(buf);

    return str;
}

int run_integer_to_int_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mIntValue;

    return value;
}

unsigned int run_uinteger_to_uint_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUIntValue;

    return value;
}

char run_cbyte_to_byte_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mByteValue;

    return value;
}

unsigned char run_cubyte_to_ubyte_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUByteValue;

    return value;
}

short run_cshort_to_short_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mShortValue;

    return value;
}

unsigned short run_cushort_to_ushort_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

    return value;
}

long run_clong_to_long_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mLongValue;

    return value;
}

unsigned long run_culong_to_ulong_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mLongValue;

    return value;
}

char* run_cpointer_to_pointer_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    char* value = (char*)obj_data->mFields[0].mPointerValue;

    return value;
}

int run_cfloat_to_int_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mFloatValue;

    return value;
}

float run_cfloat_to_float_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mFloatValue;

    return value;
}

int run_cdouble_to_int_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mDoubleValue;

    return value;
}

double run_cdouble_to_double_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mDoubleValue;

    return value;
}

struct sCLVALUEAndBoolResult* run_array_to_carray_cast(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, char* class_name)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(10)");
        result->result1.mIntValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* array_data = CLOBJECT(array);
    int array_num = array_data->mArrayNum;

    sCLClass* klass2 = get_class("Array");
    MASSERT(klass2 != NULL);

    CLObject new_array = create_object(klass2);

    gGlobalStackPtr->mObjectValue = new_array;
    gGlobalStackPtr++;

    CLObject new_primitive_array;
    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        new_primitive_array = create_array_object(klass->mBoxingClass, array_num);
    }
    else {
        new_primitive_array = create_array_object(klass, array_num);
    }

    sCLObject* new_array_data = CLOBJECT(new_array);

    new_array_data->mFields[0].mObjectValue = new_primitive_array;

    /// boxing element ///
    int i;
    for(i=0; i<array_num; i++ ) {
        array_data = CLOBJECT(array);           // reget for GC

        CLVALUE element;
        boxing_primitive_value_to_object(array_data->mFields[i], &element, klass);

        sCLObject* new_primitive_array_data = CLOBJECT(new_primitive_array);
        new_primitive_array_data->mFields[i] = element;
    }

    gGlobalStackPtr--;

    result->result1.mObjectValue = new_array;
    result->result2 = TRUE;

    return result;
}

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

int llvm_module_main(int argc, char** argv, char* const * envp)
{
    return 0;
}

/*
int llvm_module_main(int argc, char **argv, char * const *envp) 
{
  sys::PrintStackTraceOnErrorSignal(argv[0]);
  PrettyStackTraceProgram X(argc, argv);

  atexit(llvm_shutdown); // Call llvm_shutdown() on exit.

  if (argc > 1)
    ExitOnErr.setBanner(std::string(argv[0]) + ": ");

  // If we have a native target, initialize it to ensure it is linked in and
  // usable by the JIT.
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();

  cl::ParseCommandLineOptions(argc, argv,
                              "llvm interpreter & dynamic compiler\n");

  // If the user doesn't want core files, disable them.
  if (DisableCoreFiles)
    sys::Process::PreventCoreFiles();

  LLVMContext Context;

  // Load the bitcode...
  SMDiagnostic Err;
  std::unique_ptr<Module> Owner = parseIRFile(InputFile, Err, Context);
  Module *Mod = Owner.get();
  if (!Mod) {
puts("AAA");
    reportError(Err, argv[0]);
}


  if (EnableCacheManager) {
    std::string CacheName("file:");
    CacheName.append(InputFile);
    Mod->setModuleIdentifier(CacheName);
  }

  // If not jitting lazily, load the whole bitcode file eagerly too.
  if (NoLazyCompilation) {
    // Use *argv instead of argv[0] to work around a wrong GCC warning.
    ExitOnError ExitOnErr(std::string(*argv) +
                          ": bitcode didn't read correctly: ");
    ExitOnErr(Mod->materializeAll());
  }

  std::string ErrorMsg;
  EngineBuilder builder(std::move(Owner));
  builder.setMArch(MArch);
  builder.setMCPU(MCPU);
  builder.setMAttrs(MAttrs);
  if (RelocModel.getNumOccurrences())
    builder.setRelocationModel(RelocModel);
  builder.setCodeModel(CMModel);
  builder.setErrorStr(&ErrorMsg);
  builder.setEngineKind(ForceInterpreter
                        ? EngineKind::Interpreter
                        : EngineKind::JIT);
  builder.setUseOrcMCJITReplacement(UseJITKind == JITKind::OrcMCJITReplacement);

  // If we are supposed to override the target triple, do so now.
  if (!TargetTriple.empty())
    Mod->setTargetTriple(Triple::normalize(TargetTriple));

  // Enable MCJIT if desired.
  RTDyldMemoryManager *RTDyldMM = nullptr;
  if (!ForceInterpreter) {
      RTDyldMM = new SectionMemoryManager();

    // Deliberately construct a temp std::unique_ptr to pass in. Do not null out
    // RTDyldMM: We still use it below, even though we don't own it.
    builder.setMCJITMemoryManager(
      std::unique_ptr<RTDyldMemoryManager>(RTDyldMM));
  } else if (RemoteMCJIT) {
    errs() << "error: Remote process execution does not work with the "
              "interpreter.\n";
    exit(1);
  }

  builder.setOptLevel(getOptLevel());

  TargetOptions Options;
  if (FloatABIForCalls != FloatABI::Default)
    Options.FloatABIType = FloatABIForCalls;

  builder.setTargetOptions(Options);

  std::unique_ptr<ExecutionEngine> EE(builder.create());
  if (!EE) {
    if (!ErrorMsg.empty())
      errs() << argv[0] << ": error creating EE: " << ErrorMsg << "\n";
    else
      errs() << argv[0] << ": unknown error creating EE!\n";
    exit(1);
  }

  std::unique_ptr<LLIObjectCache> CacheManager;
  if (EnableCacheManager) {
    CacheManager.reset(new LLIObjectCache(ObjectCacheDir));
    EE->setObjectCache(CacheManager.get());
  }

  // Load any additional modules specified on the command line.
  for (unsigned i = 0, e = ExtraModules.size(); i != e; ++i) {
    std::unique_ptr<Module> XMod = parseIRFile(ExtraModules[i], Err, Context);
    if (!XMod)
      reportError(Err, argv[0]);
    if (EnableCacheManager) {
      std::string CacheName("file:");
      CacheName.append(ExtraModules[i]);
      XMod->setModuleIdentifier(CacheName);
    }
    EE->addModule(std::move(XMod));
  }

  for (unsigned i = 0, e = ExtraObjects.size(); i != e; ++i) {
    Expected<object::OwningBinary<object::ObjectFile>> Obj =
        object::ObjectFile::createObjectFile(ExtraObjects[i]);
    if (!Obj) {
      // TODO: Actually report errors helpfully.
      consumeError(Obj.takeError());
      reportError(Err, argv[0]);
    }
    object::OwningBinary<object::ObjectFile> &O = Obj.get();
    EE->addObjectFile(std::move(O));
  }

  for (unsigned i = 0, e = ExtraArchives.size(); i != e; ++i) {
    ErrorOr<std::unique_ptr<MemoryBuffer>> ArBufOrErr =
        MemoryBuffer::getFileOrSTDIN(ExtraArchives[i]);
    if (!ArBufOrErr)
      reportError(Err, argv[0]);
    std::unique_ptr<MemoryBuffer> &ArBuf = ArBufOrErr.get();

    Expected<std::unique_ptr<object::Archive>> ArOrErr =
        object::Archive::create(ArBuf->getMemBufferRef());
    if (!ArOrErr) {
      std::string Buf;
      raw_string_ostream OS(Buf);
      logAllUnhandledErrors(ArOrErr.takeError(), OS, "");
      OS.flush();
      errs() << Buf;
      exit(1);
    }
    std::unique_ptr<object::Archive> &Ar = ArOrErr.get();

    object::OwningBinary<object::Archive> OB(std::move(Ar), std::move(ArBuf));

    EE->addArchive(std::move(OB));
  }

  // If the target is Cygwin/MingW and we are generating remote code, we
  // need an extra module to help out with linking.
  if (RemoteMCJIT && Triple(Mod->getTargetTriple()).isOSCygMing()) {
    addCygMingExtraModule(*EE, Context, Mod->getTargetTriple());
  }

  // The following functions have no effect if their respective profiling
  // support wasn't enabled in the build configuration.
  EE->RegisterJITEventListener(
                JITEventListener::createOProfileJITEventListener());
  EE->RegisterJITEventListener(
                JITEventListener::createIntelJITEventListener());

  if (!NoLazyCompilation && RemoteMCJIT) {
    errs() << "warning: remote mcjit does not support lazy compilation\n";
    NoLazyCompilation = true;
  }
  EE->DisableLazyCompilation(NoLazyCompilation);

  // If the user specifically requested an argv[0] to pass into the program,
  // do it now.
  if (!FakeArgv0.empty()) {
    InputFile = static_cast<std::string>(FakeArgv0);
  } else {
    // Otherwise, if there is a .bc suffix on the executable strip it off, it
    // might confuse the program.
    if (StringRef(InputFile).endswith(".bc"))
      InputFile.erase(InputFile.length() - 3);
  }

  // Add the module's name to the start of the vector of arguments to main().
  InputArgv.insert(InputArgv.begin(), InputFile);

  // Call the main function from M as if its signature were:
  //   int main (int argc, char **argv, const char **envp)
  // using the contents of Args to determine argc & argv, and the contents of
  // EnvVars to determine envp.
  //
  Function *EntryFn = Mod->getFunction(EntryFunc);
  if (!EntryFn) {
    errs() << '\'' << EntryFunc << "\' function not found in module.\n";
    return -1;
  }

  // Reset errno to zero on entry to main.
  errno = 0;

  int Result = -1;

  // Sanity check use of remote-jit: LLI currently only supports use of the
  // remote JIT on Unix platforms.
  if (RemoteMCJIT) {
#ifndef LLVM_ON_UNIX
    errs() << "Warning: host does not support external remote targets.\n"
           << "  Defaulting to local execution\n";
    return -1;
#else
    if (ChildExecPath.empty()) {
      errs() << "-remote-mcjit requires -mcjit-remote-process.\n";
      exit(1);
    } else if (!sys::fs::can_execute(ChildExecPath)) {
      errs() << "Unable to find usable child executable: '" << ChildExecPath
             << "'\n";
      return -1;
    }
#endif
  }

  if (!RemoteMCJIT) {
    // If the program doesn't explicitly call exit, we will need the Exit
    // function later on to make an explicit call, so get the function now.
    Constant *Exit = Mod->getOrInsertFunction("exit", Type::getVoidTy(Context),
                                                      Type::getInt32Ty(Context),
                                                      nullptr);

    // Run static constructors.
    if (!ForceInterpreter) {
      // Give MCJIT a chance to apply relocations and set page permissions.
      EE->finalizeObject();
    }
    EE->runStaticConstructorsDestructors(false);

    // Trigger compilation separately so code regions that need to be
    // invalidated will be known.
    (void)EE->getPointerToFunction(EntryFn);
    // Clear instruction cache before code will be executed.
    if (RTDyldMM)
      static_cast<SectionMemoryManager*>(RTDyldMM)->invalidateInstructionCache();

    // Run main.
    Result = EE->runFunctionAsMain(EntryFn, InputArgv, envp);

    // Run static destructors.
    EE->runStaticConstructorsDestructors(true);

    // If the program didn't call exit explicitly, we should call it now.
    // This ensures that any atexit handlers get called correctly.
    if (Function *ExitF = dyn_cast<Function>(Exit)) {
      std::vector<GenericValue> Args;
      GenericValue ResultGV;
      ResultGV.IntVal = APInt(32, Result);
      Args.push_back(ResultGV);
      EE->runFunction(ExitF, Args);
      errs() << "ERROR: exit(" << Result << ") returned!\n";
      abort();
    } else {
      errs() << "ERROR: exit defined with wrong prototype!\n";
      abort();
    }
  }

  return Result;
}
*/

BOOL load_bc_file(sCLClass* klass)
{
    if(!klass->mModuleLoaded) {
        char* class_name = CLASS_NAME(klass);

        char class_bc_file_name[PATH_MAX+1];
        if(!search_for_bc_file(class_name, class_bc_file_name, PATH_MAX)) {
            return FALSE;
        }

        SMDiagnostic err;

printf("class_bc_file_name %s\n", class_bc_file_name);
        int argc = 2;
        char* argv[2];
        argv[0] = "jit";
        argv[1] = class_bc_file_name;

        if(strcmp(CLASS_NAME(klass), "Hash") == 0) {
            (void)llvm_module_main(argc, argv, gEnvp);
        }

/*
        if(module == NULL) {
            fprintf(stderr, "bc file not found error %s.bc\n", class_name);
        }
        else {
printf("class name %s\n", class_name);
module->dump();
sleep(1);

            TheJIT->addModule(std::move(module));

            klass->mModuleLoaded = TRUE;
        }
*/
    }

    return TRUE;
}

sCLClass* get_class_with_load_and_initialize_in_jit(char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize_in_jit(class_name);

    if(klass == NULL) {
        fprintf(stderr, "class not found error %s\n", class_name);
    }

    if(!klass->mModuleLoaded) {
        if(!load_bc_file(klass)) {
            return NULL;
        }
    }

    return klass;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info, CLVALUE** stack_ptr)
{
    int num_jit_objects = gNumJITObjects;

/*
    if(klass->mModuleLoaded && strcmp(METHOD_NAME2(klass, method), "initialize") != 0 && strcmp(METHOD_NAME2(klass, method), "finalize") != 0 && !(method->mFlags & METHOD_FLAGS_NATIVE)) 
    {
        char method_path2[METHOD_NAME_MAX + 128];
        create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);
        
        auto ExprSymbol = TheJIT->findSymbol(method_path2);

        fJITMethodType function = nullptr;

        if(ExprSymbol) {
            function = (fJITMethodType)ExprSymbol.getAddress();
        }

        if(function != nullptr) {
            CLVALUE* stack_ptr = stack + var_num;
            CLVALUE* lvar = stack;

            long stack_id = append_stack_to_stack_list(stack, &stack_ptr);

            info->current_stack = stack;        // for invoking_block in native method
            info->current_var_num = var_num;
            info->stack_id = stack_id;

            BOOL result = function(stack_ptr, lvar, info, stack, &stack_ptr, var_num, constant, code);
            if(!result) {
                remove_stack_to_stack_list(stack, &stack_ptr);
                gNumJITObjects = num_jit_objects;
                return FALSE;
            }

            remove_stack_to_stack_list(stack, &stack_ptr);
        }
        else {
            BOOL result = vm(code, constant, stack, var_num, klass, info);

            if(!result) {
                gNumJITObjects = num_jit_objects;
                return FALSE;
            }
        }
    }
    else {
*/
        BOOL result = vm(code, constant, stack, var_num, klass, info);

        if(!result) {
            gNumJITObjects = num_jit_objects;
            return FALSE;
        }
//    }

    gNumJITObjects = num_jit_objects;

    return TRUE;
}

void jit_init_on_runtime()
{
    gCLValueAndBoolStructMemory.result1.mIntValue = 0;
    gCLValueAndBoolStructMemory.result2 = 0;
/*
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
*/

//    TheJIT = llvm::make_unique<CloverJIT>();

    init_jit_objects();
}

void jit_final_on_runtime()
{
    free_jit_objects();
}


} // extern "C"
