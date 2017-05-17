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
static std::map<std::string, BasicBlock*> TheLabels;

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
    Type* param8_type;
    Type* param9_type;
    FunctionType* function_type;

    /// create_string_object ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_string_object", TheModule.get());

    /// create_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_object", TheModule.get());

    /// create_regex_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_regex_object", TheModule.get());

    /// create_array_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_array_object", TheModule.get());

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

    /// run_load_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_field", TheModule.get());

    /// run_load_address ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_address", TheModule.get());

    /// run_ldclong ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ldclong", TheModule.get());

    /// run_ldcpointer ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ldcpointer", TheModule.get());

    /// run_lduclong ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ldculong", TheModule.get());

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

    /// show_str ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_str_in_jit", TheModule.get());

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

    /// try_function ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "try_function", TheModule.get());

    /// get_try_catch_label_name ///
    type_params.clear();

    result_type = PointerType::get(IntegerType::get(TheContext,8), 0);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_try_catch_label_name", TheModule.get());

    /// entry_exception_object ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object", TheModule.get());

    /// run_load_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_field", TheModule.get());

    /// regex_equals ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "regex_equals", TheModule.get());

    /// entry_exception_object_with_class_name ///
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

    param5_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object_with_class_name2", TheModule.get());
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
    //TheLabels.clear();
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
void show_stack_stat(CLVALUE** stack_ptr, CLVALUE* stack)
{
    printf("stack_ptr %p\n", stack_ptr);
    printf("*stack_ptr %p\n", *stack_ptr);
    printf("stack_ptr - stack %d\n", (int)(*stack_ptr - stack));
}

BOOL show_stack_in_jit(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    printf("var_num %d\n", var_num);
    show_stack_stat(stack_ptr, stack);

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

        case OP_DUPE:
            puts("OP_DUPE");
            break;

        case OP_COND_JUMP :
            puts("OP_COND_JUMP");
            break;

        case OP_COND_NOT_JUMP:
            puts("OP_COND_NOT_JUMP");
            break;

        case OP_GOTO:
            puts("OP_GOTO");
            break;

        case OP_LABEL:
            puts("OP_LABEL");
            break;

        case OP_LOAD:
            puts("OP_LOAD");
            break;

        case OP_STORE:
            puts("OP_STORE");
            break;

        case OP_LDCBYTE: 
            puts("OP_LDCBYTE");
            break;

        case OP_LDCINT: 
            puts("OP_LDCINT");
            break;

        case OP_LDCNULL:
            puts("OP_LDCNULL");
            break;

        case OP_BADD:
            puts("OP_BAND");
            break;

        case OP_BSUB:
            puts("OP_BSUB");
            break;

        case OP_BMULT:
            puts("OP_BMULT");
            break;

        case OP_BDIV:
            puts("OP_BDIV");
            break;

        case OP_BMOD:
            puts("OP_BMOD");
            break;

        case OP_BLSHIFT:
            puts("OP_BLSHIFT");
            break;

        case OP_BRSHIFT:
            puts("OP_BRSHIFT");
            break;

        case OP_BAND:
            puts("OP_BAND");
            break;

        case OP_BXOR:
            puts("OP_BXOR");
            break;

        case OP_BOR:
            puts("OP_BOR");
            break;

        case OP_UBADD:
            puts("OP_UBAND");
            break;

        case OP_UBSUB:
            puts("OP_UBSUB");
            break;

        case OP_UBMULT:
            puts("OP_UBMULT");
            break;

        case OP_UBDIV:
            puts("OP_UBDIV");
            break;

        case OP_UBMOD:
            puts("OP_UBMOD");
            break;

        case OP_UBLSHIFT:
            puts("OP_UBLSHIFT");
            break;

        case OP_UBRSHIFT:
            puts("OP_UBRSHIFT");
            break;

        case OP_UBAND:
            puts("OP_UBAND");
            break;

        case OP_UBXOR:
            puts("OP_UBXOR");
            break;

        case OP_UBOR:
            puts("OP_BOR");
            break;

        case OP_SADD:
            puts("OP_SADD");
            break;

        case OP_SSUB:
            puts("OP_SSUB");
            break;

        case OP_SMULT: 
            puts("OP_SMULT");
            break;

        case OP_SDIV: 
            puts("OP_SDIV");
            break;

        case OP_SMOD: 
            puts("OP_SMOD");
            break;

        case OP_SLSHIFT: 
            puts("OP_SLSHIFT");
            break;

        case OP_SRSHIFT: 
            puts("OP_SRSHIFT");
            break;

        case OP_SAND: 
            puts("OP_SAND");
            break;

        case OP_SXOR: 
            puts("OP_SXOR");
            break;

        case OP_SOR: 
            puts("OP_SOR");
            break;

        case OP_USADD: 
            puts("OP_USADD");
            break;

        case OP_USSUB: 
            puts("OP_USSUB");
            break;

        case OP_USMULT: 
            puts("OP_USMULT");
            break;

        case OP_USDIV: 
            puts("OP_USDIV");
            break;

        case OP_USMOD: 
            puts("OP_USMOD");
            break;

        case OP_USLSHIFT: 
            puts("OP_USLSHIFT");
            break;

        case OP_USRSHIFT: 
            puts("OP_USRSHIFT");
            break;

        case OP_USAND: 
            puts("OP_USAND");
            break;

        case OP_USXOR: 
            puts("OP_USXOR");
            break;

        case OP_USOR: 
            puts("OP_USOR");
            break;

        case OP_IADD: 
            puts("OP_IADD");
            break;

        case OP_ISUB: 
            puts("OP_ISUB");
            break;

        case OP_IMULT: 
            puts("OP_IMULT");
            break;

        case OP_IDIV: 
            puts("OP_IDIV");
            break;

        case OP_IMOD: 
            puts("OP_IMOD");
            break;

        case OP_ILSHIFT: 
            puts("OP_ILSHIFT");
            break;

        case OP_IRSHIFT: 
            puts("OP_IRSHIFT");
            break;

        case OP_IAND: 
            puts("OP_IAND");
            break;

        case OP_IXOR: 
            puts("OP_IXOR");
            break;

        case OP_IOR: 
            puts("OP_IOR");
            break;

        case OP_UIADD: 
            puts("OP_UIADD");
            break;

        case OP_UISUB: 
            puts("OP_UISUB");
            break;

        case OP_UIMULT: 
            puts("OP_UIMULT");
            break;

        case OP_UIDIV: 
            puts("OP_UIDIV");
            break;

        case OP_UIMOD: 
            puts("OP_UIMOD");
            break;

        case OP_UILSHIFT: 
            puts("OP_UILSHIFT");
            break;

        case OP_UIRSHIFT: 
            puts("OP_UIRSHIFT");
            break;

        case OP_UIAND: 
            puts("OP_UIAND");
            break;

        case OP_UIXOR: 
            puts("OP_UIXOR");
            break;

        case OP_UIOR: 
            puts("OP_UIOR");
            break;

        case OP_LADD: 
            puts("OP_LADD");
            break;

        case OP_LSUB: 
            puts("OP_LSUB");
            break;

        case OP_LMULT: 
            puts("OP_LMULT");
            break;

        case OP_LDIV: 
            puts("OP_LDIV");
            break;

        case OP_LMOD: 
            puts("OP_LMOD");
            break;

        case OP_LLSHIFT: 
            puts("OP_LLSHIFT");
            break;

        case OP_LRSHIFT: 
            puts("OP_LRSHIFT");
            break;

        case OP_LAND: 
            puts("OP_LAND");
            break;

        case OP_LXOR: 
            puts("OP_LXOR");
            break;

        case OP_LOR: 
            puts("OP_LOR");
            break;

        case OP_ULADD: 
            puts("OP_ULADD");
            break;

        case OP_ULSUB: 
            puts("OP_ULSUB");
            break;

        case OP_ULMULT: 
            puts("OP_ULMULT");
            break;

        case OP_ULDIV: 
            puts("OP_ULDIV");
            break;

        case OP_ULMOD: 
            puts("OP_ULMOD");
            break;

        case OP_ULLSHIFT: 
            puts("OP_ULLSHIFT");
            break;

        case OP_ULRSHIFT: 
            puts("OP_ULRSHIFT");
            break;

        case OP_ULAND: 
            puts("OP_ULAND");
            break;

        case OP_ULXOR: 
            puts("OP_ULXOR");
            break;

        case OP_UBCOMPLEMENT:
            puts("OP_UBCOMPLEMENT");
            break;

        case OP_SCOMPLEMENT:
            puts("OP_SCOMPLEMENT");
            break;

        case OP_USCOMPLEMENT:
            puts("OP_USCOMPLEMENT");
            break;

        case OP_ICOMPLEMENT:
            puts("OP_ICOMPLEMENT");
            break;

        case OP_UICOMPLEMENT:
            puts("OP_UICOMPLEMENT");
            break;

        case OP_LCOMPLEMENT:
            puts("OP_LCOMPLEMENT");
            break;

        case OP_ULCOMPLEMENT:
            puts("OP_ULCOMPLEMENT");
            break;


        case OP_FADD:
            puts("OP_FADD");
            break;

        case OP_FSUB:
            puts("OP_FSUB");
            break;

        case OP_FMULT:
            puts("OP_FMULT");
            break;

        case OP_FDIV:
            puts("OP_FDIV");
            break;


        case OP_DADD:
            puts("OP_DADD");
            break;

        case OP_DSUB:
            puts("OP_DSUB");
            break;

        case OP_DMULT:
            puts("OP_DMULT");
            break;

        case OP_DDIV:
            puts("OP_DDIV");
            break;


        case OP_PADD:
            puts("OP_PADD");
            break;

        case OP_PSUB:
            puts("OP_PSUB");
            break;

        case OP_PPSUB:
            puts("OP_PPSUB");
            break;


        case OP_CADD:
            puts("OP_CADD");
            break;

        case OP_CSUB:
            puts("OP_CSUB");
            break;


        case OP_BEQ :
            puts("OP_BEQ ");
            break;

        case OP_BNOTEQ :
            puts("OP_BNOTEQ ");
            break;

        case OP_BGT :
            puts("OP_BGT ");
            break;

        case OP_BLE :
            puts("OP_BLE ");
            break;

        case OP_BGTEQ :
            puts("OP_BGTEQ ");
            break;

        case OP_BLEEQ :
            puts("OP_BLEEQ ");
            break;


        case OP_UBEQ :
            puts("OP_UBEQ ");
            break;

        case OP_UBNOTEQ :
            puts("OP_UBNOTEQ ");
            break;

        case OP_UBGT :
            puts("OP_UBGT ");
            break;

        case OP_UBLE :
            puts("OP_UBLE ");
            break;

        case OP_UBGTEQ :
            puts("OP_UBGTEQ ");
            break;

        case OP_UBLEEQ :
            puts("OP_UBLEEQ ");
            break;


        case OP_SEQ :
            puts("OP_SEQ ");
            break;

        case OP_SNOTEQ :
            puts("OP_SNOTEQ ");
            break;

        case OP_SGT :
            puts("OP_SGT ");
            break;

        case OP_SLE :
            puts("OP_SLE ");
            break;

        case OP_SGTEQ :
            puts("OP_SGTEQ ");
            break;

        case OP_SLEEQ :
            puts("OP_SLEEQ ");
            break;


        case OP_USEQ :
            puts("OP_USEQ ");
            break;

        case OP_USNOTEQ :
            puts("OP_USNOTEQ ");
            break;

        case OP_USGT :
            puts("OP_USGT ");
            break;

        case OP_USLE :
            puts("OP_USLE ");
            break;

        case OP_USGTEQ :
            puts("OP_USGTEQ ");
            break;

        case OP_USLEEQ :
            puts("OP_USLEEQ ");
            break;

        case OP_INOTEQ :
            puts("OP_INOTEQ ");
            break;

        case OP_IGT :
            puts("OP_IGT ");
            break;

        case OP_UIEQ :
            puts("OP_UIEQ ");
            break;

        case OP_UINOTEQ :
            puts("OP_UINOTEQ ");
            break;

        case OP_UIGT :
            puts("OP_UIGT ");
            break;

        case OP_UILE :
            puts("OP_UILE ");
            break;

        case OP_UIGTEQ :
            puts("OP_UIGTEQ ");
            break;

        case OP_UILEEQ :
            puts("OP_UILEEQ ");
            break;



        case OP_LEQ :
            puts("OP_LEQ ");
            break;

        case OP_LNOTEQ :
            puts("OP_LNOTEQ ");
            break;

        case OP_LGT :
            puts("OP_LGT ");
            break;

        case OP_LLE :
            puts("OP_LLE ");
            break;

        case OP_LGTEQ :
            puts("OP_LGTEQ ");
            break;

        case OP_LLEEQ :
            puts("OP_LLEEQ ");
            break;


        case OP_ULEQ :
            puts("OP_ULEQ ");
            break;

        case OP_ULNOTEQ :
            puts("OP_ULNOTEQ ");
            break;

        case OP_ULGT :
            puts("OP_ULGT ");
            break;

        case OP_ULLE :
            puts("OP_ULLE ");
            break;

        case OP_ULGTEQ :
            puts("OP_ULGTEQ ");
            break;

        case OP_ULLEEQ :
            puts("OP_ULLEEQ ");
            break;



        case OP_FEQ :
            puts("OP_FEQ ");
            break;

        case OP_FNOTEQ :
            puts("OP_FNOTEQ ");
            break;

        case OP_FGT :
            puts("OP_FGT ");
            break;

        case OP_FLE :
            puts("OP_FLE ");
            break;

        case OP_FGTEQ :
            puts("OP_FGTEQ ");
            break;

        case OP_FLEEQ :
            puts("OP_FLEEQ ");
            break;



        case OP_DEQ :
            puts("OP_DEQ ");
            break;

        case OP_DNOTEQ :
            puts("OP_DNOTEQ ");
            break;

        case OP_DGT :
            puts("OP_DGT ");
            break;

        case OP_DLE :
            puts("OP_DLE ");
            break;

        case OP_DGTEQ :
            puts("OP_DGTEQ ");
            break;

        case OP_DLEEQ :
            puts("OP_DLEEQ ");
            break;



        case OP_PEQ :
            puts("OP_PEQ ");
            break;

        case OP_PNOTEQ :
            puts("OP_PNOTEQ ");
            break;

        case OP_PGT :
            puts("OP_PGT ");
            break;

        case OP_PLE :
            puts("OP_PLE ");
            break;

        case OP_PGTEQ :
            puts("OP_PGTEQ ");
            break;

        case OP_PLEEQ :
            puts("OP_PLEEQ ");
            break;


        case OP_CEQ :
            puts("OP_CEQ ");
            break;

        case OP_CNOTEQ :
            puts("OP_CNOTEQ ");
            break;

        case OP_CGT :
            puts("OP_CGT ");
            break;

        case OP_CLE :
            puts("OP_CLE ");
            break;

        case OP_CGTEQ :
            puts("OP_CGTEQ ");
            break;

        case OP_CLEEQ :
            puts("OP_CLEEQ ");
            break;

        case OP_REGEQ :
            puts("OP_REGEQ ");
            break;

        case OP_REGNOTEQ :
            puts("OP_REGNOTEQ ");
            break;

        case OP_ULOR: 
            puts("OP_ULOR");
            break;

        case OP_RETURN: 
            puts("OP_RETURN");
            break;

        case OP_TRY:
            puts("OP_TRY");
            break;

        case OP_INVOKE_METHOD:
            puts("OP_INVOKE_METHOD");
            break;

        case OP_THROW:
            puts("OP_THROW");
            break;

        case OP_CREATE_STRING:
            puts("OP_CREATE_STRING");
            break;

        case OP_CREATE_REGEX:
            puts("OP_CREATE_REGEX");
            break;

        case OP_HEAD_OF_EXPRESSION: 
            puts("OP_HEAD_OF_EXPRESSION");
            break;

        case OP_SIGINT:
            puts("OP_SIGINT");
            break;

        case OP_NEW:
            puts("OP_NEW");
            break;

        case OP_BCOMPLEMENT:
            puts("OP_BCOMPLEMENT");
            break;

        case OP_IEQ:
            puts("OP_IEQ");
            break;

        case OP_ILE:
            puts("OP_ILE");
            break;

        case OP_IGTEQ:
            puts("OP_IGTEQ");
            break;

        case OP_ANDAND:
            puts("OP_ANDAND");
            break;

        case OP_LOAD_FIELD:
            puts("OP_LOAD_FIELD");
            break;

        case OP_BYTE_TO_INT_CAST:
            puts("OP_BYTE_TO_INT_CAST");
            break;

/*
        case OP_INT_TO_BYTE_CAST:
            puts("OP_INT_TO_BYTE_CAST");
            break;
*/

        default:
            printf("opecode %d\n", opecode);
            break;
    }
}

void show_number_in_jit(int number)
{
    printf("%d\n", number);
}

static void call_show_number_in_jit(int number)
{
    Function* show_number = TheModule->getFunction("show_number_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)number);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_number, params2);
}

void show_str_in_jit(char* str)
{
    printf("%s\n", str);
}

static void call_show_str_in_jit(char* str)
{
    Function* show_str = TheModule->getFunction("show_str_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_str, params2);
}

static void call_show_stack_stat(std::map<std::string, Value *> params)
{
    Function* show_address_fun = TheModule->getFunction("show_stack_stat");

    std::vector<Value*> params2;

    std::string stack_ptr_address_arg_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_arg_name];
    Value* param1 = stack_ptr_address_value;
    params2.push_back(param1);

    std::string stack_arg_name("stack");
    Value* stack_value = params[stack_arg_name];
    Value* param2 = stack_value;
    params2.push_back(param2);

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

static void call_show_stack(int var_num, sVMInfo* info, std::map<std::string, Value *> params)
{
    Function* show_stack_fun = TheModule->getFunction("show_stack_in_jit");

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");
    std::string stack_name("stack");
    Value* stack_value = params[stack_name];

    std::vector<Value*> params2;
    Value* param1 = stack_ptr_address_value;
    params2.push_back(param1);

    Value* param2 = stack_value;
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

BOOL run_load_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index)
{
    CLObject obj = ((*stack_ptr) -1)->mObjectValue;
    (*stack_ptr)--;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(4)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    CLVALUE value = object_pointer->mFields[field_index];
    **stack_ptr = value;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_load_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLVALUE* lvar, int index)
{
    (*stack_ptr)->mPointerValue = (char*)&lvar[index];
    (*stack_ptr)++;

    return TRUE;
}

void run_ldclong(CLVALUE** stack_ptr, int value1, int value2)
{
    long lvalue;

    memcpy(&lvalue, &value1, sizeof(int));
    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

    (*stack_ptr)->mLongValue = lvalue;
    (*stack_ptr)++;
}

void run_ldcpointer(CLVALUE** stack_ptr, int value1, int value2)
{
    void* lvalue;

    memcpy(&lvalue, &value1, sizeof(int));
    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

    (*stack_ptr)->mPointerValue = (char*)lvalue;
    (*stack_ptr)++;
}

void run_ldculong(CLVALUE** stack_ptr, int value1, int value2)
{
    long lvalue;

    memcpy(&lvalue, &value1, sizeof(int));
    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

    (*stack_ptr)->mULongValue = lvalue;
    (*stack_ptr)++;
}

void try_function(sVMInfo* info, char* try_cach_label)
{
    info->try_catch_label_name = try_cach_label;
}

char* get_try_catch_label_name(sVMInfo* info)
{
    return info->try_catch_label_name;
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

    *stack_ptr = lvar;      // see OP_RETURN
    **stack_ptr = *new_stack;
    (*stack_ptr)++;

    return TRUE;
}

//////////////////////////////////////////////////////////////////////
// LLVM operation functions
//////////////////////////////////////////////////////////////////////
static void store_value(Value* llvm_value, Value* stored_value, BasicBlock* current_block)
{
    Builder.CreateStore(llvm_value, stored_value);
}

static void store_value_with_aligned(Value* llvm_value, Value* stored_value, BasicBlock* current_block, int align)
{
    Builder.CreateAlignedStore(llvm_value, stored_value, align);
}

static void inc_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* current_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");


    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* inc_ptr_value = Builder.CreateAdd(lvalue, rvalue, "inc_ptr_value", false, false);

    std::string stack_ptr_arg_name("stack_ptr");
    params[stack_ptr_arg_name] = inc_ptr_value;

    store_value(inc_ptr_value, stack_ptr_address_value, current_block);
}

static void dec_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* current_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* dec_ptr_value = Builder.CreateSub(lvalue, rvalue, "dec_ptr_value", true, true);

    std::string stack_ptr_arg_name("stack_ptr");
    params[stack_ptr_arg_name] = dec_ptr_value;

    store_value(dec_ptr_value, stack_ptr_address_value, current_block);
}

static Value* get_stack_ptr_value_from_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*offset, true));
    return Builder.CreateSub(lvalue, rvalue, "offset_stack_ptr", true, true);
}

static Value* get_lvar_value_from_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*offset, true));
    Value* offset_lvar = Builder.CreateAdd(lvalue, rvalue, "offset_lvar", true, true);

    return Builder.CreateLoad(offset_lvar, "offset_lvar");
}

static void store_value_to_lvar_with_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, Value* llvm_value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* lvar_offset_value = Builder.CreateAdd(lvalue, rvalue, "lvar_offset_value", true, true);

    store_value(llvm_value, lvar_offset_value, current_block);
}

static Value* get_stack_ptr_value_from_index(std::map<std::string, Value*>& params, BasicBlock* current_block, int index)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* stack_pointer_offset_value = Builder.CreateAdd(lvalue, rvalue, "stack_pointer_offset_value", true, true);

    return Builder.CreateLoad(stack_pointer_offset_value, "stack_pointer_offset_value");
}

static Value* get_stack_ptr_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* stack_pointer_offset_value = Builder.CreateAdd(lvalue, rvalue, "stack_pointer_offset_value", true, true);

    return Builder.CreateAlignedLoad(stack_pointer_offset_value, align, "stack_pointer_offset_value");
}

static void push_value_to_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* current_block, Value* value)
{
    Builder.SetInsertPoint(current_block);

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
    store_value(zero, loaded_stack_ptr_address_value, current_block);

    store_value(value, loaded_stack_ptr_address_value, current_block);

    inc_stack_ptr(params, current_block, 1);
}

static void push_value_to_stack_ptr_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, Value* value, int align)
{
    Builder.SetInsertPoint(current_block);

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateAlignedLoad(stack_ptr_address_value, align, "loaded_stack_ptr_address_value");

    Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
    store_value_with_aligned(zero, loaded_stack_ptr_address_value, current_block, 8);

    store_value_with_aligned(value, loaded_stack_ptr_address_value, current_block, align);

    inc_stack_ptr(params, current_block, 1);
}

static Value* get_value_from_char_array(char* str)
{
    Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
    return ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
}

static void run_entry_exception_object_with_class_name2(std::map<std::string, Value *> params, int var_num, sVMInfo* info, char* class_name, char* message)
{
    Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object_with_class_name2");

    std::vector<Value*> params2;

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* param1 = params[stack_ptr_address_name];
    params2.push_back(param1);

    std::string stack_value_name("stack");
    Value* param2 = params[stack_value_name];
    params2.push_back(param2);

    Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
    params2.push_back(param3);

    Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
    params2.push_back(param4);

    Value* param5 = get_value_from_char_array(class_name);
    params2.push_back(param5);

    Value* param6 = get_value_from_char_array(message);
    params2.push_back(param6);

    (void)Builder.CreateCall(entry_exception_object_fun, params2);
}

static void if_value_is_zero_entry_exception_object(Value* value, std::map<std::string, Value *> params, int var_num, sVMInfo* info, Function* function, BasicBlock** current_block, char* class_name, char* message)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* comp = Builder.CreateICmpEQ(value, ConstantInt::get(TheContext, llvm::APInt(32, 0, true)), "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    run_entry_exception_object_with_class_name2(params, var_num, info, class_name, message);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

static void if_value_is_zero_ret_zero(Value* value, std::map<std::string, Value *> params, int var_num, sVMInfo* info, Function* function, BasicBlock** current_block)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* comp = Builder.CreateICmpEQ(value, ConstantInt::get(TheContext, llvm::APInt(32, 0, true)), "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

////////////////////////////////////////////////////////////
// LLVM invoking method
////////////////////////////////////////////////////////////
static void finish_method_call(Value* result, sCLClass* klass, sCLMethod* method, sVMInfo* info, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char* try_catch_label_name)
{
    // if result is FALSE ret 0
    Value* comp = Builder.CreateICmpNE(result, ConstantInt::get(TheContext, llvm::APInt(32, 1, true)), "ifcond");

    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Function* try_catch_label_name_fun = TheModule->getFunction("get_try_catch_label_name");

    std::vector<Value*> params2;

    Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
    params2.push_back(vminfo_value);

    Value* try_catch_label_name_value = Builder.CreateCall(try_catch_label_name_fun, params2);

    Value* comp2 = Builder.CreateICmpNE(try_catch_label_name_value, ConstantInt::get(TheContext, llvm::APInt(32, 0, false)), "catchcond");

    BasicBlock* then_block2 = BasicBlock::Create(TheContext, "then_block_b", function);
    BasicBlock* entry_ifend2 = BasicBlock::Create(TheContext, "entry_ifend_b", function);

    Builder.CreateCondBr(comp2, then_block2, entry_ifend2);

    Builder.SetInsertPoint(then_block2);

    if(try_catch_label_name == nullptr) {
        Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
        Builder.CreateRet(ret_value);
    }
    else {
        std::string try_catch_label_name_string(try_catch_label_name);
        BasicBlock* label = TheLabels[try_catch_label_name_string];
        if(label == nullptr) {
            label = BasicBlock::Create(TheContext, try_catch_label_name, function);
            TheLabels[try_catch_label_name_string] = label;
        }

        if(label == nullptr) {
            Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
            Builder.CreateRet(ret_value);
        }
        else {
            Builder.CreateBr(label);
        }
    }

    Builder.SetInsertPoint(entry_ifend2);
    
    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend); 
    *current_block = entry_ifend;

    /// result ///
    if(is_void_type(method->mResultType, klass) && strcmp(METHOD_NAME2(klass, method), "initialize") != 0) {
        std::string stack_ptr_address_name("stack_ptr_address");
        Value* stack_ptr_address_value = params[stack_ptr_address_name];

        std::string lvar_arg_name("lvar");
        Value* lvar_address_value = params[lvar_arg_name];

        std::string stack_ptr_arg_name("stack_ptr");
        params[stack_ptr_arg_name] = params[lvar_arg_name];

        store_value(lvar_address_value, stack_ptr_address_value, *current_block);

        int value = 0;
        Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

        push_value_to_stack_ptr_with_aligned(params, *current_block, llvm_value, 4);
    }
    else {
        Value* result = get_stack_ptr_value_from_index(params, entry_ifend, -1);

        std::string stack_ptr_address_name("stack_ptr_address");
        Value* stack_ptr_address_value = params[stack_ptr_address_name];

        std::string lvar_arg_name("lvar");
        Value* lvar_address_value = params[lvar_arg_name];

        store_value(lvar_address_value, stack_ptr_address_value, *current_block);

        push_value_to_stack_ptr(params, *current_block, result);

        std::string stack_ptr_arg_name("stack_ptr");
        params[stack_ptr_arg_name] = params[lvar_arg_name];
    }
}

static BOOL compile_invoking_method(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char* try_catch_label_name)
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

        Value* new_lvar = get_stack_ptr_value_from_offset(params, *current_block, method->mNumParams);
        Value* lvar_value = new_lvar;
        params2.push_back(lvar_value);

        Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
        params2.push_back(vminfo_value);

        Value* result = Builder.CreateCall(native_method, params2);

        finish_method_call(result, klass, method, info, params, current_block, function, try_catch_label_name);
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

        finish_method_call(result, klass, method, info, params, current_block, function, try_catch_label_name);
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////
// JIT main
//////////////////////////////////////////////////////////////////////
#define MAX_COND_JUMP 128

static BOOL compile_to_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    std::string func_name(METHOD_PATH(klass, method));
    std::unique_ptr<FunctionAST> llvm_func = llvm::make_unique<FunctionAST>(func_name);

    char* try_catch_label_name = NULL;

    LLVMFunctions[func_name] = std::move(llvm_func);

    Function* function = TheModule->getFunction(func_name);

    // Create a new basic block to start insertion into.
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(current_block);
  
    register char* pc = code->mCodes;
    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    std::map<std::string, Value *> params;
    for(auto &param : function->args()) {
        params[param.getName()] = &param;
    }

    int num_cond_jump = 0;
    char* cond_jump_labels[MAX_COND_JUMP];
    BasicBlock* entry_condends[MAX_COND_JUMP];

    int num_cond_not_jump = 0;
    char* cond_not_jump_labels[MAX_COND_JUMP];
    BasicBlock* entry_condnotends[MAX_COND_JUMP];

    while(pc - code->mCodes < code->mLen) {
        if(pc == cond_jump_labels[num_cond_jump-1]) {
            Builder.SetInsertPoint(entry_condends[num_cond_jump-1]);
            current_block = entry_condends[num_cond_jump-1];
            num_cond_jump--;
        }
        if(pc == cond_not_jump_labels[num_cond_not_jump-1]) {
            Builder.SetInsertPoint(entry_condnotends[num_cond_not_jump-1]);
            current_block = entry_condnotends[num_cond_not_jump-1];
            num_cond_not_jump--;
        }

        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);

#ifdef MDEBUG
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
call_show_inst_in_jit(inst);
show_inst_in_jit(inst);
}
#endif

        switch(inst) {
            case OP_POP:
                dec_stack_ptr(params, current_block, 1);
                break;

            case OP_POP_N:
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    dec_stack_ptr(params, current_block, value);
                }
                break;

            case OP_REVERSE: {
                Value* llvm_value = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* llvm_value2 = get_stack_ptr_value_from_index(params, current_block, -1);
                
                dec_stack_ptr(params, current_block, 2);

                push_value_to_stack_ptr(params, current_block, llvm_value2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DUPE: {
                Value* llvm_value = get_stack_ptr_value_from_index(params, current_block, -1);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_COND_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                Value* conditinal_value = get_stack_ptr_value_from_index(params, current_block, -1);
                dec_stack_ptr(params, current_block, 1);

                BasicBlock* cond_jump_then_block = BasicBlock::Create(TheContext, "cond_jump_then", function);
                entry_condends[num_cond_jump] = BasicBlock::Create(TheContext, "entry_condend", function);

                Builder.CreateCondBr(conditinal_value, entry_condends[num_cond_jump], cond_jump_then_block);

                Builder.SetInsertPoint(cond_jump_then_block);

                current_block = cond_jump_then_block;

                cond_jump_labels[num_cond_jump] = pc + jump_value;
                num_cond_jump++;

                if(num_cond_jump >= MAX_COND_JUMP) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "overflow number of condjump");
                    return FALSE;
                }
                }
                break;

            case OP_COND_NOT_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                Value* conditinal_value = get_stack_ptr_value_from_index(params, current_block, -1);
                dec_stack_ptr(params, current_block, 1);

                BasicBlock* cond_not_jump_then_block = BasicBlock::Create(TheContext, "cond_not_jump_then", function);
                entry_condnotends[num_cond_not_jump] = BasicBlock::Create(TheContext, "entry_condnotend", function);

                Builder.CreateCondBr(conditinal_value, cond_not_jump_then_block, entry_condnotends[num_cond_not_jump]);

                Builder.SetInsertPoint(cond_not_jump_then_block);
                current_block = cond_not_jump_then_block;

                cond_not_jump_labels[num_cond_not_jump] = pc + jump_value;
                num_cond_not_jump++;

                if(num_cond_not_jump >= MAX_COND_JUMP) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "overflow number of condnotjump");
                    return FALSE;
                }
                }
                break;

            case OP_GOTO: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                int label_offset = *(int*)pc;
                pc += sizeof(int);

                char* label_name = CONS_str(constant, label_offset);
                std::string label_name_string(label_name);

                BasicBlock* label = TheLabels[label_name_string];
                if(label == nullptr) {
                    label = BasicBlock::Create(TheContext, label_name, function);
                    TheLabels[label_name_string] = label;

                }

                Builder.CreateBr(label);

                Builder.SetInsertPoint(label);
                current_block = label;
                
                BasicBlock* entry_after_goto = BasicBlock::Create(TheContext, "entry_after_goto", function);
                Builder.SetInsertPoint(entry_after_goto);
                current_block = entry_after_goto;
                }
                break;

            case OP_RETURN: {
                std::string stack_param_name("stack");
                Value* stack_value = params[stack_param_name];

                Value* llvm_value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value(llvm_value, stack_value, current_block);

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));
                Builder.CreateRet(ret_value);

                BasicBlock* entry_after_return = BasicBlock::Create(TheContext, "entry_after_return", function);
                Builder.SetInsertPoint(entry_after_return);
                current_block = entry_after_return;
                }
                break;

            case OP_THROW: {
                std::string stack_param_name("stack");
                Value* stack_value = params[stack_param_name];

                Value* llvm_value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value(llvm_value, stack_value, current_block);

                Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object");

                std::vector<Value*> params2;

                Value* param1 = llvm_value;
                params2.push_back(param1);

                Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(vminfo_value);

                (void)Builder.CreateCall(entry_exception_object_fun, params2);

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
                Builder.CreateRet(ret_value);

                current_block = BasicBlock::Create(TheContext, "entry_after_throw", function);
                Builder.SetInsertPoint(current_block);
                }
                break;

            case OP_TRY: {
                int tmp = *(int*)pc;
                pc += sizeof(int);

                int catch_label_name_offset = *(int*)pc;
                pc += sizeof(int);

                try_catch_label_name = CONS_str(constant, catch_label_name_offset);

                Function* try_fun = TheModule->getFunction("try_function");

                std::vector<Value*> params2;

                Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(vminfo_value);

                Value* try_catch_label_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)try_catch_label_name);
                params2.push_back(try_catch_label_value);

                (void)Builder.CreateCall(try_fun, params2);
                }
                break;

            case OP_HEAD_OF_EXPRESSION: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                Function* function = TheModule->getFunction("run_head_of_expression");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param1);

                Value* param2 = get_value_from_char_array(sname);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)sline);
                params2.push_back(param3);

                Builder.CreateCall(function, params2);
                }
                break;

            case OP_SIGINT: {
                Function* sigint_function = TheModule->getFunction("run_sigint");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* result = Builder.CreateCall(sigint_function, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_LABEL: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* label_name = CONS_str(constant, offset);

                std::string label_name_string(label_name);

                BasicBlock* label = TheLabels[label_name_string];
                if(label == nullptr) {
                    label = BasicBlock::Create(TheContext, label_name, function);
                    TheLabels[label_name_string] = label;
                }

                Builder.CreateBr(label);
                Builder.SetInsertPoint(label);
                current_block = label;
                }
                break;

            case OP_STORE: {
                int index = *(int*)pc;
                pc += sizeof(int);

                Value* llvm_value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_to_lvar_with_offset(params, current_block, index, llvm_value);
                }
                break;

            case OP_LOAD: {
                int index = *(int*)pc;
                pc += sizeof(int);

                Value* llvm_value = get_lvar_value_from_offset(params, current_block, index);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LOAD_ADDRESS: {
                int index = *(int*)pc;
                pc += sizeof(int);

                Function* load_address_fun = TheModule->getFunction("run_load_address");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                std::string lvar_arg_name("lvar");
                Value* param5 = params[lvar_arg_name];
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)index);
                params2.push_back(param6);

                Builder.CreateCall(load_address_fun, params2);
                }
                break;

            case OP_LDCBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(8, value, true)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCUBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(8, value, false)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(16, value, true)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCUSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(16, value, false)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCINT: {
                int value = *(int*)pc;
                pc += sizeof(int);

                Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCUINT: {
                unsigned int value = *(unsigned int*)pc;
                pc += sizeof(int);

                Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, false)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCLONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                Function* run_ldclong_fun = TheModule->getFunction("run_ldclong");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value1);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value2);
                params2.push_back(param3);

                Builder.CreateCall(run_ldclong_fun, params2);
                }
                break;

            case OP_LDCULONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                Function* run_ldculong_fun = TheModule->getFunction("run_ldculong");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value1);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value2);
                params2.push_back(param3);

                Builder.CreateCall(run_ldculong_fun, params2);
                }
                break;

            case OP_LDCNULL: {
                int value = 0;
                Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCPOINTER: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                Function* run_ldclong_fun = TheModule->getFunction("run_ldcpointer");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value1);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value2);
                params2.push_back(param3);

                Builder.CreateCall(run_ldclong_fun, params2);
                }
                break;

            case OP_LDCFLOAT: {
                float value1 = *(float*)pc;
                pc += sizeof(float);

                stack_ptr->mFloatValue = value1;
                stack_ptr++;

                Value* llvm_value = ConstantFP::get(TheContext, llvm::APFloat(value1)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCDOUBLE: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                double lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                Value* llvm_value = ConstantFP::get(TheContext, llvm::APFloat(lvalue)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_BADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_SADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_IADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ISUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ILSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UISUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UILSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_BCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_SCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_ICOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UICOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFFFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFFFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_FADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFAdd(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_FSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFSub(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_FMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFMul(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_FDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                if_value_is_zero_entry_exception_object(frvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateFDiv(flvalue, frvalue, "divtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* dlvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* drvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFAdd(dlvalue, drvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* dlvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* drvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFSub(dlvalue, drvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* dlvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* drvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFMul(dlvalue, drvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* dlvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* drvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                if_value_is_zero_entry_exception_object(drvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateFDiv(dlvalue, drvalue, "divtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_PADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_PSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_PPSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_CADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_CSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_UBGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_UBLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_USGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_USLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IEQ: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateICmpEQ(lvalue, rvalue, "IEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_INOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateICmpNE(lvalue, rvalue, "INOTEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_IGT: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateICmpSGT(lvalue, rvalue, "IGT");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_ILE: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateICmpSLT(lvalue, rvalue, "ILE");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;
            
            case OP_IGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateICmpSGE(lvalue, rvalue, "IGETQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_ILEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateICmpSLE(lvalue, rvalue, "ILEEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_UIEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UINOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_UIGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UILE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UILEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_ULGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_ULLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOEQ(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpONE(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOGT(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOLT(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOGE(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getFloatTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getFloatTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOLE(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOEQ(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpONE(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOGT(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOLT(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOGE(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* flvalue = Builder.CreateCast(Instruction::Trunc, lvalue, Type::getDoubleTy(TheContext), "flvalue");
                Value* frvalue = Builder.CreateCast(Instruction::Trunc, rvalue, Type::getDoubleTy(TheContext), "frvalue");

                Value* llvm_value = Builder.CreateFCmpOLE(flvalue, frvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_REGEQ: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Function* function = TheModule->getFunction("regex_equals");

                std::vector<Value*> params2;
                params2.push_back(lvalue);
                params2.push_back(rvalue);

                Value* result = Builder.CreateCall(function, params2);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_CEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_CNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_CGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_CLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_CGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_CLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_REGNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Function* function = TheModule->getFunction("regex_equals");

                std::vector<Value*> params2;
                params2.push_back(lvalue);
                params2.push_back(rvalue);

                Value* result = Builder.CreateCall(function, params2);

                Value* result2 = Builder.CreateICmpEQ(result, ConstantInt::get(TheContext, llvm::APInt(32, 0, true)), "ifcond");


                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result2);
                }
                break;

            case OP_OBJ_IDENTIFY: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateICmpEQ(lvalue, rvalue, "IEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_CLASSNAME: {
                puts("OP_CLASSNAME is not defined");
                exit(3);
                }
                break;

            case OP_IMPLEMENTS: {
                puts("OP_IMPLEMENTS is not defined");
                exit(3);
                }
                break;

            case OP_ANDAND: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateAnd(lvalue, rvalue, "ANDAND");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_OROR: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* result = Builder.CreateAnd(lvalue, rvalue, "OROR");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_LOGICAL_DENIAL: {
                Value* lvalue = get_stack_ptr_value_from_index(params, current_block, -1);

                Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_INVOKE_METHOD: {
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

                if(!compile_invoking_method(klass, method, stack, var_num, &stack_ptr, info, params, &current_block, function, try_catch_label_name))
                {
                    return FALSE;
                }
                }
                break;

            case OP_CREATE_STRING: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* str = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_string_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(param1);

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_CREATE_REGEX: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                BOOL global = *(int*)pc;
                pc += sizeof(int);

                BOOL ignore_case = *(int*)pc;
                pc += sizeof(int);

                BOOL multiline = *(int*)pc;
                pc += sizeof(int);

                BOOL extended = *(int*)pc;
                pc += sizeof(int);

                BOOL dotall = *(int*)pc;
                pc += sizeof(int);

                BOOL anchored = *(int*)pc;
                pc += sizeof(int);

                BOOL dollar_endonly = *(int*)pc;
                pc += sizeof(int);

                BOOL ungreedy = *(int*)pc;
                pc += sizeof(int);

                char* regex_str = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_regex_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)regex_str);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(param1);
                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)global);
                params2.push_back(param2);
                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)ignore_case);
                params2.push_back(param3);
                Value* param4 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)multiline);
                params2.push_back(param4);
                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)extended);
                params2.push_back(param5);
                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)dotall);
                params2.push_back(param6);
                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)anchored);
                params2.push_back(param7);
                Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)dollar_endonly);
                params2.push_back(param8);
                Value* param9 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)ungreedy);
                params2.push_back(param9);

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;


            case OP_NEW: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                BOOL flg_array = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(3)");
                    return FALSE;
                }

                if(flg_array) {
                    Value* array_num_value = get_stack_ptr_value_from_index(params, current_block, -1);
                    dec_stack_ptr(params, current_block, 1);

                    Function* function = TheModule->getFunction("create_array_object");

                    std::vector<Value*> params2;
                    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                    params2.push_back(klass_value);
                    params2.push_back(array_num_value);

                    Value* llvm_value = Builder.CreateCall(function, params2);

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                else {
                    Function* function = TheModule->getFunction("create_object");

                    std::vector<Value*> params2;
                    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                    params2.push_back(klass_value);

                    Value* llvm_value = Builder.CreateCall(function, params2);

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                }
                break;



            case OP_LOAD_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* load_field_fun = TheModule->getFunction("run_load_field");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(load_field_fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_BYTE_TO_INT_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

/*
            case OP_INT_TO_BYTE_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                push_value_to_stack_ptr_with_aligned(params, current_block, value, 2);
                }
                break;
*/

            default:
                printf("inst %d\n", inst);
                exit(1);
        }

#ifdef MDEBUG
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
    call_show_stack(var_num, info, params);
}
#endif
    }

    // Finish off the function.
    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));

    //Builder.SetInsertPoint(current_block);
    Builder.CreateRet(ret_value);

    // Validate the generated code, checking for consistency.
    verifyFunction(*function);

    // Run the optimizer on the function.
    //TheFPM->run(*function);

    return TRUE;
}

typedef BOOL (*fJITMethodType)(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address);

static BOOL run_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
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
#ifdef MDEBUG
printf("compiling %s\n", METHOD_PATH(klass, method));
#endif
        if(!compile_to_native_code(code, constant, stack, var_num, klass, method, info)) {
            return FALSE;
        }

#ifdef MDEBUG
        TheModule->dump();
#endif
        auto H = TheJIT->addModule(std::move(TheModule));
        InitializeModuleAndPassManager();
    }

#ifdef MDEBUG
printf("run_native_code %s\n", METHOD_NAME2(klass, method));
#endif
    if(!run_native_code(code, constant, stack, var_num, klass, method, info)) {
        return FALSE;
    }

    return TRUE;
}

} // extern "C"
