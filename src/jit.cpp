extern "C" 
{
#include "common.h"
}

#include "llvm/ADT/APFloat.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

#include "llvm/ADT/iterator_range.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/RuntimeDyld.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/LambdaResolver.h"
#include "llvm/ExecutionEngine/Orc/ObjectLinkingLayer.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Mangler.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;
using namespace llvm::orc;

class CloverJIT {
public:
    typedef ObjectLinkingLayer<> ObjLayerT;
    typedef IRCompileLayer<ObjLayerT> CompileLayerT;
    typedef CompileLayerT::ModuleSetHandleT ModuleHandleT;
    
    CloverJIT()
        : TM(EngineBuilder().selectTarget()), DL(TM->createDataLayout()),
          CompileLayer(ObjectLayer, SimpleCompiler(*TM)) 
    {
        llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);
    }
    
    TargetMachine &getTargetMachine() { return *TM; }
    
    ModuleHandleT addModule(std::unique_ptr<Module> M) 
    {
        // We need a memory manager to allocate memory and resolve symbols for this
        // new module. Create one that resolves symbols by looking back into the
        // JIT.
        auto Resolver = createLambdaResolver(
            [&](const std::string &Name) {
              if (auto Sym = findMangledSymbol(Name))
                return Sym;
              return JITSymbol(nullptr);
            },
            [](const std::string &S) { return nullptr; });
        auto H = CompileLayer.addModuleSet(singletonSet(std::move(M)),
                                           make_unique<SectionMemoryManager>(),
                                           std::move(Resolver));
        
        ModuleHandles.push_back(H);
        return H;
    }

    void removeModule(ModuleHandleT H) {
        ModuleHandles.erase(find(ModuleHandles, H));
        CompileLayer.removeModuleSet(H);
    }
    
    JITSymbol findSymbol(const std::string Name) {
        return findMangledSymbol(mangle(Name));
    }

private:
    std::string mangle(const std::string &Name) 
    {
        std::string MangledName;
        {
             raw_string_ostream MangledNameStream(MangledName);
             Mangler::getNameWithPrefix(MangledNameStream, Name, DL);
        }
        return MangledName;
    }
    
    template <typename T> static std::vector<T> singletonSet(T t) 
    {
        std::vector<T> Vec;
        Vec.push_back(std::move(t));
        return Vec;
    }
    
    JITSymbol findMangledSymbol(const std::string &Name) {
        // Search modules in reverse order: from last added to first added.
        // This is the opposite of the usual search order for dlsym, but makes more
        // sense in a REPL where we want to bind to the newest available definition.
        for (auto H : make_range(ModuleHandles.rbegin(), ModuleHandles.rend())) {
            if (auto Sym = CompileLayer.findSymbolIn(H, Name, true)) {
              return Sym;
            }
        }
    
        // If we can't find the symbol in the JIT, try looking in the host process.
        if (auto SymAddr = RTDyldMemoryManager::getSymbolAddressInProcess(Name)) {
            return JITSymbol(SymAddr, JITSymbolFlags::Exported);
        }
    
        return nullptr;
    }
    
    std::unique_ptr<TargetMachine> TM;
    const DataLayout DL;
    ObjLayerT ObjectLayer;
    CompileLayerT CompileLayer;
    std::vector<ModuleHandleT> ModuleHandles;
};

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;
static std::unique_ptr<CloverJIT> TheJIT;

class FunctionAST {
public:
    std::string name;
    Function* llvmFunction;

    FunctionAST(const std::string &name)
        : name(name)
    {
        std::vector<Type *> params;

        Type* param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
        params.push_back(param1_type);
        Type* param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
        params.push_back(param2_type);
        Type* param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
        params.push_back(param3_type);
        Type* param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
        params.push_back(param4_type);
        Type* param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
        params.push_back(param5_type);

        Type* result_type = IntegerType::get(TheContext, 32);
        FunctionType* function_type = FunctionType::get(result_type, params, false);

        Function* function = Function::Create(function_type, Function::ExternalLinkage, name, TheModule.get());
        std::vector<std::string> args;

        std::string stack_ptr_name("stack_ptr");
        args.push_back(stack_ptr_name);
        std::string lvar_name("lvar");
        args.push_back(lvar_name);
        std::string info_name("info");
        args.push_back(info_name);
        std::string stack_name("stack");
        args.push_back(stack_name);
        std::string stack_ptr_address_name("stack_ptr_address");
        args.push_back(stack_ptr_address_name);

        unsigned index = 0;
        for (auto &arg : function->args()) {
            arg.setName(args[index++]);
        }

        this->llvmFunction = function;
    }
};

static std::map<std::string, std::unique_ptr<FunctionAST>> LLVMFunctions;

static void create_internal_functions()
{
    Type* result_type;
    std::vector<Type *> type_params;
    Type* param1_type;
    Type* param2_type;
    Type* param3_type;
    Type* param4_type;
    Type* param5_type;
    Type* param6_type;
    Type* param7_type;
    FunctionType* function_type;

    /// create_string_object ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_string_object", TheModule.get());

    /// run_head_of_expression ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_head_of_expression", TheModule.get());

    /// run_sigint ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_sigint", TheModule.get());

    /// show_inst ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_inst_in_jit", TheModule.get());

    /// show_number ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_number_in_jit", TheModule.get());

    /// show_stack_stat ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_stack_stat", TheModule.get());

    /// show_stack_in_jit ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_stack_in_jit", TheModule.get());

    /// invoke_none_native_method_in_jit ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);
    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);
    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);
    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);
    param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param5_type);
    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);

    Function::Create(function_type, Function::ExternalLinkage, "invoke_none_native_method_in_jit", TheModule.get());
}

static void InitializeModuleAndPassManager() 
{
    TheModule = llvm::make_unique<Module>("Clover2 jit", TheContext);
    TheModule->setDataLayout(TheJIT->getTargetMachine().createDataLayout());
    
    TheFPM = llvm::make_unique<legacy::FunctionPassManager>(TheModule.get());
    
    TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->doInitialization();

    create_internal_functions();
}


extern "C"
{
void jit_init()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    TheJIT = llvm::make_unique<CloverJIT>();

    InitializeModuleAndPassManager();
}

void jit_final()
{
}


/////////////////////////////////////////////////////////////////////////////
/// JIT debug functions
/////////////////////////////////////////////////////////////////////////////
BOOL show_stack_in_jit(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    printf("var_num %d\n", var_num);

    int i;
    for(i=0; i<10; i++) {
        if(*stack_ptr == stack + i) {
            printf("! stack [%d] %d on %p\n", i, stack[i].mIntValue, stack + i);
        }
        else {
            printf("  stack [%d] %d on %p\n", i, stack[i].mIntValue, stack + i);
        }
    }

    return TRUE;
}

void show_inst_in_jit(int opecode)
{
    switch(opecode) {
        case OP_POP:
            puts("OP_POP");
            break;

        case OP_LOAD:
            puts("OP_LOAD");
            break;

        case OP_STORE:
            puts("OP_STORE");
            break;

        case OP_LDCINT: 
            puts("OP_LDCINT");
            break;

        case OP_LDCNULL:
            puts("OP_LDCNULL");
            break;

        case OP_IADD: 
            puts("OP_IADD");
            break;

        case OP_RETURN: 
            puts("OP_RETURN");
            break;

        case OP_INVOKE_METHOD:
            puts("OP_INVOKE_METHOD");
            break;

        case OP_CREATE_STRING:
            puts("OP_CREATE_STRING");
            break;

        case OP_HEAD_OF_EXPRESSION: 
            puts("OP_HEAD_OF_EXPRESSION");
            break;

        case OP_SIGINT:
            puts("OP_SIGINT");
            break;

        default:
            printf("opecode %d\n", opecode);
            break;
    }
}

void show_number_in_jit(int number)
{
    printf("%d\n", number);
}

void show_stack_stat(CLVALUE** stack_ptr)
{
    printf("stack_ptr %p\n", stack_ptr);
    printf("*stack_ptr %p\n", *stack_ptr);
}

static void call_show_number_in_jit(int number)
{
    Function* show_number = TheModule->getFunction("show_number_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)number);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_number, params2);
}

static void call_show_stack_stat(std::map<std::string, Value *> params)
{
    Function* show_address_fun = TheModule->getFunction("show_stack_stat");

    std::string stack_ptr_address_arg_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_arg_name];

    std::vector<Value*> params2;
    Value* param1 = stack_ptr_address_value;
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_address_fun, params2);
}


static void call_show_inst_in_jit(int opecode)
{
    Function* show_inst = TheModule->getFunction("show_inst_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)opecode);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_inst, params2);
}

static void call_show_stack(CLVALUE* stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    Function* show_stack_fun = TheModule->getFunction("show_stack_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)stack_ptr);
    params2.push_back(param1);

    Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)stack);
    params2.push_back(param2);

    Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
    params2.push_back(param3);

    Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
    params2.push_back(param4);

    Value* result = Builder.CreateCall(show_stack_fun, params2);
}

//////////////////////////////////////////////////////////////////////
// VM functions
//////////////////////////////////////////////////////////////////////
void run_head_of_expression(sVMInfo* info, char* sname, int sline)
{
    info->sname = sname;
    info->sline = sline;

    gSigInt = FALSE;
}

BOOL run_sigint(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    if(gSigInt) {
        gSigInt = FALSE;
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Signal Interrupt");
        return FALSE;
    }

    return TRUE;
}

BOOL invoke_none_native_method_in_jit(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);
    CLVALUE* lvar = *stack_ptr - real_param_num;

    sByteCode* code = &method->uCode.mByteCodes;
    sConst* constant = &klass->mConst;
    CLVALUE* new_stack = lvar;
    int new_var_num = method->mVarNum;

    /// initialize local var except params ///
    memset(lvar + real_param_num, 0, sizeof(CLVALUE)* (new_var_num - real_param_num));

    if(method->mFlags & METHOD_FLAGS_JIT) {
        if(!jit(code, constant, new_stack, new_var_num, klass, method, info))
        {
            *stack_ptr = lvar;
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            return FALSE;
        }
    }
    else {
        if(!vm(code, constant, new_stack, new_var_num, klass, info)) {
            *stack_ptr = lvar;
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            return FALSE;
        }
    }

puts("*");
show_stack_in_jit(stack_ptr, stack, var_num, info);
printf("stack_ptr - stack %d\n", (int)(*stack_ptr - stack));

    *stack_ptr = lvar;      // see OP_RETURN
    **stack_ptr = *new_stack;
    (*stack_ptr)++;

puts("*");
show_stack_in_jit(stack_ptr, stack, var_num, info);
printf("stack_ptr - stack %d\n", (int)(*stack_ptr - stack));

    return TRUE;
}

//////////////////////////////////////////////////////////////////////
// LLVM operation functions
//////////////////////////////////////////////////////////////////////
static void store_value(Value* llvm_value, Value* stored_value, BasicBlock* basic_block)
{
    StoreInst* store_inst = new StoreInst(llvm_value, stored_value);
    store_inst->setAlignment(8);
    basic_block->getInstList().push_back(store_inst);
}

static void inc_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* basic_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");


    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* inc_ptr_value = Builder.CreateAdd(lvalue, rvalue, "inc_ptr_value", false, false);

    std::string stack_ptr_arg_name("stack_ptr");
    params[stack_ptr_arg_name] = inc_ptr_value;

    store_value(inc_ptr_value, stack_ptr_address_value, basic_block);
}

static void dec_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* basic_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* dec_ptr_value = Builder.CreateSub(lvalue, rvalue, "dec_ptr_value", true, true);

    std::string stack_ptr_arg_name("stack_ptr");
    params[stack_ptr_arg_name] = dec_ptr_value;

    store_value(dec_ptr_value, stack_ptr_address_value, basic_block);
}

static Value* get_stack_ptr_value_from_offset(std::map<std::string, Value*>& params, BasicBlock* basic_block, int offset)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*offset, true));
    return Builder.CreateSub(lvalue, rvalue, "offset_stack_ptr", true, true);
}

static Value* get_lvar_value_from_offset(std::map<std::string, Value*>& params, BasicBlock* basic_block, int offset)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*offset, true));
    Value* offset_lvar = Builder.CreateAdd(lvalue, rvalue, "offset_lvar", true, true);

    return Builder.CreateLoad(offset_lvar, "offset_lvar");
}

static void store_value_to_lvar_with_offset(std::map<std::string, Value*>& params, BasicBlock* basic_block, int index, Value* llvm_value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* lvar_offset_value = Builder.CreateAdd(lvalue, rvalue, "lvar_offset_value", true, true);

    store_value(llvm_value, lvar_offset_value, basic_block);
}

static Value* get_stack_ptr_value_from_index(std::map<std::string, Value*>& params, BasicBlock* basic_block, int index)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* stack_pointer_offset_value = Builder.CreateAdd(lvalue, rvalue, "stack_pointer_offset_value", true, true);

    return Builder.CreateLoad(stack_pointer_offset_value, "stack_pointer_offset_value");
}

static void push_value_to_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* basic_block, Value* value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    store_value(value, loaded_stack_ptr_address_value, basic_block);

    inc_stack_ptr(params, basic_block, 1);
}

static BOOL compile_invoking_method(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, std::map<std::string, Value *> params, BasicBlock* basic_block)
{
    int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);

    if(method->mFlags & METHOD_FLAGS_NATIVE) {
        if(method->uCode.mNativeMethod == NULL) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Native method not found");
            return FALSE;
        }

        std::string func_name(METHOD_PATH(klass, method));

        Function* native_method = TheModule->getFunction(func_name);

        if(native_method == nullptr) {
            Type* result_type = IntegerType::get(TheContext, 32);

            std::vector<Type *> type_params;
            Type* param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext,64), 0), 0);
            type_params.push_back(param1_type);
            Type* param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
            type_params.push_back(param2_type);
            Type* param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
            type_params.push_back(param3_type);

            FunctionType* function_type = FunctionType::get(result_type, type_params, false);
            char* native_fun_name = method->uCode.mNativeFunName;

            native_method = Function::Create(function_type, Function::ExternalLinkage, native_fun_name, TheModule.get());
        }

        std::vector<Value*> params2;

        std::string stack_ptr_address_value_name("stack_ptr_address");
        Value* stack_ptr_address_value = params[stack_ptr_address_value_name];
        params2.push_back(stack_ptr_address_value);

        Value* new_lvar = get_stack_ptr_value_from_offset(params, basic_block, method->mNumParams);
        Value* lvar_value = new_lvar;
        params2.push_back(lvar_value);

        Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
        params2.push_back(vminfo_value);

        Value* result = Builder.CreateCall(native_method, params2);

        /// if result == FALSE then; ret 0

        if(is_void_type(method->mResultType, klass)) {
            std::string stack_ptr_arg_name("stack_ptr");
            std::string lvar_arg_name("lvar");

            params[stack_ptr_arg_name] = params[lvar_arg_name];

            int value = 0;
            Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

            push_value_to_stack_ptr(params, basic_block, llvm_value);
        }
        else {
            std::string stack_ptr_arg_name("stack_ptr");
            std::string lvar_arg_name("lvar");

            params[stack_ptr_arg_name] = params[lvar_arg_name];

            Value* result = get_stack_ptr_value_from_index(params, basic_block, -1);
            push_value_to_stack_ptr(params, basic_block, result);
        }
    }
    else {
        Function* llvm_function = TheModule->getFunction("invoke_none_native_method_in_jit");

        MASSERT(llvm_function != null_ptr);

        std::vector<Value*> params2;

        Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
        params2.push_back(klass_value);

        Value* method_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)method);
        params2.push_back(method_value);

        std::string stack_value_name("stack");
        Value* stack_value = params[stack_value_name];
        params2.push_back(stack_value);

        Value* var_num_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint64_t)var_num);
        params2.push_back(var_num_value);

        std::string stack_ptr_address_value_name("stack_ptr_address");
        Value* stack_ptr_address_value = params[stack_ptr_address_value_name];
        params2.push_back(stack_ptr_address_value);

        Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
        params2.push_back(vminfo_value);

        Value* result = Builder.CreateCall(llvm_function, params2);

        // if result is FALSE ret 0

        if(is_void_type(method->mResultType, klass)) {
            std::string stack_ptr_arg_name("stack_ptr");
            std::string lvar_arg_name("lvar");

            params[stack_ptr_arg_name] = params[lvar_arg_name];

            int value = 0;
            Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

            push_value_to_stack_ptr(params, basic_block, llvm_value);
        }
        else {
            std::string stack_ptr_arg_name("stack_ptr");
            std::string lvar_arg_name("lvar");

            params[stack_ptr_arg_name] = params[lvar_arg_name];

            Value* result = get_stack_ptr_value_from_index(params, basic_block, -1);

            push_value_to_stack_ptr(params, basic_block, result);
        }
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////
// JIT main
//////////////////////////////////////////////////////////////////////
static BOOL compile_to_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    std::string func_name(METHOD_PATH(klass, method));
    std::unique_ptr<FunctionAST> llvm_func = llvm::make_unique<FunctionAST>(func_name);

    LLVMFunctions[func_name] = std::move(llvm_func);

    Function* function = TheModule->getFunction(func_name);

    // Create a new basic block to start insertion into.
    BasicBlock *basic_block = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(basic_block);
  
    register char* pc = code->mCodes;
    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    int try_offset_before = 0;
    int try_offset = 0;

    std::map<std::string, Value *> params;
    for(auto &param : function->args()) {
        params[param.getName()] = &param;
    }

    BOOL flag_last_opecode_is_return = FALSE;

    while(pc - code->mCodes < code->mLen) {
        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);

        if(inst != OP_SIGINT) {
            flag_last_opecode_is_return = FALSE;
        }

        switch(inst) {
            case OP_POP:
puts("OP_POP");
call_show_inst_in_jit(inst);
                dec_stack_ptr(params, basic_block, 1);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
call_show_stack(stack_ptr, stack, var_num, info);
                break;

            case OP_LOAD:
                {
puts("OP_LOAD");
call_show_inst_in_jit(inst);
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = get_lvar_value_from_offset(params, basic_block, index);

                    push_value_to_stack_ptr(params, basic_block, llvm_value);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
call_show_stack(stack_ptr, stack, var_num, info);
                }
                break;

            case OP_STORE:
                {
puts("OP_STORE");
call_show_inst_in_jit(inst);
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = get_stack_ptr_value_from_index(params, basic_block, -1);

                    store_value_to_lvar_with_offset(params, basic_block, index, llvm_value);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
call_show_stack(stack_ptr, stack, var_num, info);
                }
                break;

            case OP_LDCINT: 
                {
puts("OP_LDCINT");
call_show_inst_in_jit(inst);
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

                    push_value_to_stack_ptr(params, basic_block, llvm_value);
call_show_stack(stack_ptr, stack, var_num, info);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
                }
                break;

            case OP_LDCNULL:
                {
puts("OP_LDCNULL");
call_show_inst_in_jit(inst);
                    int value = 0;
                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

                    push_value_to_stack_ptr(params, basic_block, llvm_value);
call_show_stack(stack_ptr, stack, var_num, info);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
                }
                break;

            case OP_IADD: 
                {
puts("OP_IADD");
call_show_inst_in_jit(inst);
                    Value* lvalue = get_stack_ptr_value_from_index(params, basic_block, -2);
                    Value* rvalue = get_stack_ptr_value_from_index(params, basic_block, -1);

                    Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, false);

                    dec_stack_ptr(params, basic_block, 2);
                    push_value_to_stack_ptr(params, basic_block, llvm_value);

call_show_stack(stack_ptr, stack, var_num, info);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
                }
                break;

            case OP_RETURN: {
puts("OP_RETURN");
call_show_inst_in_jit(inst);
                    std::string stack_param_name("stack");
                    Value* stack_value = params[stack_param_name];

call_show_number_in_jit(777);
call_show_stack(stack_ptr, stack, var_num, info);
                    Value* llvm_value = get_stack_ptr_value_from_index(params, basic_block, -1);

                    store_value(llvm_value, stack_value, basic_block);
call_show_number_in_jit(666);
call_show_stack(stack_ptr, stack, var_num, info);

                    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));
                    Builder.CreateRet(ret_value);

                    flag_last_opecode_is_return = TRUE;
show_stack_in_jit(&stack_ptr, stack, var_num, info);
                }
                break;

            case OP_INVOKE_METHOD: {
puts("OP_INVOKE_METHOD");
call_show_inst_in_jit(inst);
call_show_stack(stack_ptr, stack, var_num, info);
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int method_index = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);
                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(2)");
                        return FALSE;
                    }

                    if(method_index < 0 || method_index >= klass->mNumMethods) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_METHOD: Method not found");
                        return FALSE;
                    }

                    sCLMethod* method = klass->mMethods + method_index;

                    if(!compile_invoking_method(klass, method, stack, var_num, &stack_ptr, info, params, basic_block))
                    {
                        return FALSE;
                    }
call_show_stack(stack_ptr, stack, var_num, info);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
                }
                break;

            case OP_CREATE_STRING: {
puts("OP_CREATE_STRING");
call_show_inst_in_jit(inst);
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    Function* function = TheModule->getFunction("create_string_object");

                    std::vector<Value*> params2;
                    Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
                    Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                    params2.push_back(param1);

                    Value* llvm_value = Builder.CreateCall(function, params2);

                    push_value_to_stack_ptr(params, basic_block, llvm_value);

call_show_stack(stack_ptr, stack, var_num, info);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
                }
                break;

            case OP_HEAD_OF_EXPRESSION: {
call_show_inst_in_jit(inst);
puts("OP_HEAD_OF_EXPRESSION");
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

/*
                Function* function = TheModule->getFunction("run_head_of_expression");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)sname);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)sline);
                params2.push_back(param3);

                Value* result = Builder.CreateCall(function, params2);
//call_show_stack(stack_ptr, stack, var_num, info);
*/
call_show_stack(stack_ptr, stack, var_num, info);
                }
                break;

            case OP_SIGINT: {
puts("OP_SIGINT");
call_show_inst_in_jit(inst);
/*
                Function* sigint_function = TheModule->getFunction("run_sigint");

                std::vector<Value*> params2;
                Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)stack_ptr);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)stack);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* result = Builder.CreateCall(sigint_function, params2);

/*
                Value* comp = Builder.CreateICmpNE(result, ConstantInt::get(TheContext, llvm::APInt(32, 1, true)), "ifcond");

                BasicBlock* then_block = BasicBlock::Create(TheContext, "then", function);
                BasicBlock* merge_block = BasicBlock::Create(TheContext, "ifcont");

                Builder.CreateCondBr(comp, then_block, nullptr);

                Builder.SetInsertPoint(then_block);
                
                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
                Builder.CreateRet(ret_value);

                Builder.CreateBr(merge_block);

                then_block = Builder.GetInsertBlock();

                function->getBasicBlockList().push_back(merge_block);
                Builder.SetInsertPoint(merge_block);

                PHINode* pnode = Builder.CreatePHI(Type::getInt32Ty(TheContext), 1, "iftmp");
                pnode->addIncoming(then_block, basic_block);
*/
call_show_stack(stack_ptr, stack, var_num, info);
show_stack_in_jit(&stack_ptr, stack, var_num, info);
                }
                break;

            default:
                printf("inst %d\n", inst);
                exit(1);
        }
    }

    if(!flag_last_opecode_is_return) {
        // Finish off the function.
        Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));

        //Builder.SetInsertPoint(basic_block);
        Builder.CreateRet(ret_value);
    }

    // Validate the generated code, checking for consistency.
    verifyFunction(*function);

    // Run the optimizer on the function.
    //TheFPM->run(*function);

    return TRUE;
}

typedef BOOL (*fJITMethodType)(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address);

static BOOL run_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
printf("run_native_code %s\n", METHOD_NAME2(klass, method));
    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    long stack_id = append_stack_to_stack_list(stack, &stack_ptr);

    info->current_stack = stack;        // for invoking_block in native method
    info->current_var_num = var_num;
    
    auto ExprSymbol = TheJIT->findSymbol(METHOD_PATH(klass, method));
    assert(ExprSymbol && "Function not found");

    fJITMethodType function = (fJITMethodType)ExprSymbol.getAddress();
    if(!function(stack_ptr, lvar, info, stack, &stack_ptr)) {
        remove_stack_to_stack_list(stack);
        return FALSE;
    }
    
    remove_stack_to_stack_list(stack);

    return TRUE;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    auto ExprSymbol = TheJIT->findSymbol(METHOD_PATH(klass, method));
    if(!ExprSymbol) {
printf("compiling %s\n", METHOD_PATH(klass, method));
        if(!compile_to_native_code(code, constant, stack, var_num, klass, method, info)) {
            return FALSE;
        }

        TheModule->dump();
        auto H = TheJIT->addModule(std::move(TheModule));
        InitializeModuleAndPassManager();
    }

    if(!run_native_code(code, constant, stack, var_num, klass, method, info)) {
        return FALSE;
    }

    return TRUE;
}

} // extern "C"
