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
    Type* param10_type;
    Type* param11_type;
    Type* param12_type;
    FunctionType* function_type;

    /// create_string_object ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_string_object", TheModule.get());

    /// create_byte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_byte", TheModule.get());

    /// create_ubyte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ubyte", TheModule.get());

    /// create_short ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_short", TheModule.get());

    /// create_ushort ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ushort", TheModule.get());

    /// create_integer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_integer", TheModule.get());

    /// create_integer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_uinteger", TheModule.get());

    /// create_long ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_long", TheModule.get());

    /// create_ulong ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ulong", TheModule.get());

    /// create_float ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getFloatTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_float", TheModule.get());

    /// create_double ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getDoubleTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_double", TheModule.get());

    /// create_pointer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_pointer", TheModule.get());

    /// create_char ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_char", TheModule.get());

    /// create_bool ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_bool", TheModule.get());

    /// create_buffer_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_buffer_object", TheModule.get());

    /// create_path_object ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_path_object", TheModule.get());

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

    /// get_string_object_of_object_name ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_string_object_of_object_name", TheModule.get());

    /// object_implements_interface ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);
    
    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "object_implements_interface", TheModule.get());

    /// invoke_virtual_method ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "invoke_virtual_method", TheModule.get());

    /// invoke_dynamic_method ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
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

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    param10_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param10_type);

    param11_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param11_type);

    param12_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param12_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "invoke_dynamic_method", TheModule.get());

    /// invoke_block_in_jit ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "invoke_block_in_jit", TheModule.get());

    /// run_load_field_adrress ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_load_field_address", TheModule.get());

    /// run_store_field ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_store_field", TheModule.get());

    /// run_load_class_field ///
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

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_class_field", TheModule.get());

    /// run_load_class_field_address ///
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

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_class_field_address", TheModule.get());

    /// run_store_class_field ///
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

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_store_class_field", TheModule.get());

    /// run_load_element ///
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

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_element", TheModule.get());

    /// run_store_element ///
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

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_store_element", TheModule.get());

    /// run_get_array_length ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_array_length", TheModule.get());

    /// run_get_regex_global ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_global", TheModule.get());

    /// run_get_regex_ignorecase ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_ignorecase", TheModule.get());

    /// run_get_regex_multiline ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_multiline", TheModule.get());

    /// run_get_regex_extended ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_extended", TheModule.get());

    /// run_get_regex_dotall ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_dotall", TheModule.get());

    /// run_get_regex_anchored ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_anchored", TheModule.get());

    /// run_get_regex_dollar_endonly ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_dollar_endonly", TheModule.get());

    /// run_get_regex_ungreedy ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_ungreedy", TheModule.get());

    /// run_get_regex_anchored ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_get_regex_multiline", TheModule.get());

    /// run_char_uppercase ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_char_uppercase", TheModule.get());

    /// run_char_lowercase ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_char_lowercase", TheModule.get());

    /// run_create_array ///
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

    param5_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_array", TheModule.get());

    /// run_create_carray ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_carray", TheModule.get());

    /// run_create_equalable_carray ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_carray", TheModule.get());

    /// run_create_sortable_carray ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_carray", TheModule.get());

    /// run_create_list ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_list", TheModule.get());

    /// run_create_sortable_list ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_list", TheModule.get());

    /// run_create_equalable_list ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_list", TheModule.get());

    /// run_create_tuple ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_tuple", TheModule.get());

    /// run_create_hash ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_hash", TheModule.get());

    /// run_create_block_object ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
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

    param10_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param10_type);

    param11_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param11_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_block_object", TheModule.get());

    /// run_byte_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_byte_to_string_cast", TheModule.get());

    /// run_short_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_short_to_string_cast", TheModule.get());

    /// run_int_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_int_to_string_cast", TheModule.get());

    /// run_long_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_long_to_string_cast", TheModule.get());

    /// run_ubyte_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ubyte_to_string_cast", TheModule.get());

    /// run_ushort_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ushort_to_string_cast", TheModule.get());
    /// run_uint_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uint_to_string_cast", TheModule.get());

    /// run_ulong_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ulong_to_string_cast", TheModule.get());

    /// run_float_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_float_to_string_cast", TheModule.get());

    /// run_double_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_double_to_string_cast", TheModule.get());
    /// run_bool_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_bool_to_string_cast", TheModule.get());

    /// run_regex_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_regex_to_string_cast", TheModule.get());

    /// run_pointer_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_pointer_to_string_cast", TheModule.get());

    /// run_char_to_string_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_char_to_string_cast", TheModule.get());

    /// run_cbyte_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_byte_cast", TheModule.get());

    /// run_cubyte_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_byte_cast", TheModule.get());

    /// run_cshort_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_byte_cast", TheModule.get());

    /// run_cushort_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_byte_cast", TheModule.get());

    /// run_integer_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_byte_cast", TheModule.get());

    /// run_uinteger_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_byte_cast", TheModule.get());

    /// run_clong_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_byte_cast", TheModule.get());

    /// run_culong_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_byte_cast", TheModule.get());

    /// run_cfloat_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_byte_cast", TheModule.get());

    /// run_cdouble_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_byte_cast", TheModule.get());

    /// run_cpointer_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_byte_cast", TheModule.get());

    /// run_cchar_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_byte_cast", TheModule.get());

    /// run_cbool_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_byte_cast", TheModule.get());

    /// run_cbyte_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_short_cast", TheModule.get());

    /// run_cubyte_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_short_cast", TheModule.get());

    /// run_cshort_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_short_cast", TheModule.get());

    /// run_cushort_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_short_cast", TheModule.get());

    /// run_integer_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_short_cast", TheModule.get());

    /// run_uinteger_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_short_cast", TheModule.get());

    /// run_clong_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_short_cast", TheModule.get());

    /// run_culong_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_short_cast", TheModule.get());

    /// run_cfloat_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_short_cast", TheModule.get());

    /// run_cdouble_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_short_cast", TheModule.get());
    /// run_cpointer_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_short_cast", TheModule.get());
    /// run_cchar_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_short_cast", TheModule.get());

    /// run_cbool_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_short_cast", TheModule.get());

    /// run_cbyte_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_int_cast", TheModule.get());

    /// run_cubyte_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_int_cast", TheModule.get());

    /// run_cshort_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_int_cast", TheModule.get());

    /// run_cushort_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_int_cast", TheModule.get());

    /// run_integer_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_int_cast", TheModule.get());

    /// run_uinteger_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_int_cast", TheModule.get());

    /// run_clong_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_int_cast", TheModule.get());

    /// run_culong_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_int_cast", TheModule.get());

    /// run_cfloat_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_int_cast", TheModule.get());

    /// run_cdouble_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_int_cast", TheModule.get());

    /// run_cpointer_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_int_cast", TheModule.get());

    /// run_cchar_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_int_cast", TheModule.get());

    /// run_cbool_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_int_cast", TheModule.get());


    /// run_cbyte_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_long_cast", TheModule.get());

    /// run_cubyte_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_long_cast", TheModule.get());

    /// run_cshort_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_long_cast", TheModule.get());

    /// run_cushort_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_long_cast", TheModule.get());

    /// run_integer_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_long_cast", TheModule.get());

    /// run_uinteger_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_long_cast", TheModule.get());

    /// run_clong_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_long_cast", TheModule.get());

    /// run_culong_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_long_cast", TheModule.get());

    /// run_cfloat_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_long_cast", TheModule.get());

    /// run_cdouble_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_long_cast", TheModule.get());

    /// run_cpointer_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_long_cast", TheModule.get());

    /// run_cchar_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_long_cast", TheModule.get());

    /// run_cbool_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_long_cast", TheModule.get());

    /// run_cbyte_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_ubyte_cast", TheModule.get());

    /// run_cubyte_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ubyte_cast", TheModule.get());

    /// run_cshort_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_ubyte_cast", TheModule.get());

    /// run_cushort_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ubyte_cast", TheModule.get());

    /// run_integer_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_ubyte_cast", TheModule.get());

    /// run_uinteger_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_ubyte_cast", TheModule.get());

    /// run_clong_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_ubyte_cast", TheModule.get());

    /// run_culong_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ubyte_cast", TheModule.get());

    /// run_cfloat_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_ubyte_cast", TheModule.get());

    /// run_cdouble_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_ubyte_cast", TheModule.get());

    /// run_cpointer_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_ubyte_cast", TheModule.get());

    /// run_cchar_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_ubyte_cast", TheModule.get());

    /// run_cbool_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_ubyte_cast", TheModule.get());

    /// run_cbyte_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_ushort_cast", TheModule.get());

    /// run_cubyte_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ushort_cast", TheModule.get());

    /// run_cshort_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_ushort_cast", TheModule.get());

    /// run_cushort_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ushort_cast", TheModule.get());

    /// run_integer_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_ushort_cast", TheModule.get());

    /// run_uinteger_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_ushort_cast", TheModule.get());

    /// run_clong_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_ushort_cast", TheModule.get());

    /// run_culong_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ushort_cast", TheModule.get());

    /// run_cfloat_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_ushort_cast", TheModule.get());

    /// run_cdouble_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_ushort_cast", TheModule.get());
    /// run_cpointer_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_ushort_cast", TheModule.get());
    /// run_cchar_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_ushort_cast", TheModule.get());

    /// run_cbool_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_ushort_cast", TheModule.get());

    /// run_cbyte_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_uint_cast", TheModule.get());

    /// run_cubyte_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_uint_cast", TheModule.get());

    /// run_cshort_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_uint_cast", TheModule.get());

    /// run_cushort_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_uint_cast", TheModule.get());

    /// run_integer_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_uint_cast", TheModule.get());

    /// run_uinteger_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_uint_cast", TheModule.get());

    /// run_clong_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_uint_cast", TheModule.get());

    /// run_culong_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_uint_cast", TheModule.get());

    /// run_cfloat_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_uint_cast", TheModule.get());

    /// run_cdouble_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_uint_cast", TheModule.get());

    /// run_cpointer_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_uint_cast", TheModule.get());

    /// run_cchar_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_uint_cast", TheModule.get());

    /// run_cbool_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_uint_cast", TheModule.get());

    /// run_cbyte_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_ulong_cast", TheModule.get());

    /// run_cubyte_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ulong_cast", TheModule.get());

    /// run_cshort_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_ulong_cast", TheModule.get());

    /// run_cushort_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ulong_cast", TheModule.get());

    /// run_integer_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_ulong_cast", TheModule.get());

    /// run_uinteger_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_ulong_cast", TheModule.get());

    /// run_clong_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_ulong_cast", TheModule.get());

    /// run_culong_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ulong_cast", TheModule.get());

    /// run_cfloat_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_ulong_cast", TheModule.get());

    /// run_cdouble_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_ulong_cast", TheModule.get());

    /// run_cpointer_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_ulong_cast", TheModule.get());

    /// run_cchar_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_ulong_cast", TheModule.get());

    /// run_cbool_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_ulong_cast", TheModule.get());

    /// run_cbyte_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_float_cast", TheModule.get());

    /// run_cubyte_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_float_cast", TheModule.get());

    /// run_cshort_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_float_cast", TheModule.get());

    /// run_cushort_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_float_cast", TheModule.get());

    /// run_integer_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_float_cast", TheModule.get());

    /// run_uinteger_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_float_cast", TheModule.get());

    /// run_clong_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_float_cast", TheModule.get());

    /// run_culong_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_float_cast", TheModule.get());

    /// run_cfloat_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_float_cast", TheModule.get());

    /// run_cdouble_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_float_cast", TheModule.get());


    /// run_cchar_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_float_cast", TheModule.get());

    /// run_cbool_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_float_cast", TheModule.get());

    /// run_cbyte_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_double_cast", TheModule.get());

    /// run_cubyte_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_double_cast", TheModule.get());

    /// run_cshort_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_double_cast", TheModule.get());

    /// run_cushort_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_double_cast", TheModule.get());

    /// run_integer_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_double_cast", TheModule.get());

    /// run_uinteger_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_double_cast", TheModule.get());

    /// run_clong_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_double_cast", TheModule.get());

    /// run_culong_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_double_cast", TheModule.get());

    /// run_cfloat_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_double_cast", TheModule.get());

    /// run_cdouble_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_double_cast", TheModule.get());


    /// run_cchar_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_double_cast", TheModule.get());

    /// run_cbool_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_double_cast", TheModule.get());
}

static void InitializeModuleAndPassManager() 
{
    TheModule = llvm::make_unique<Module>("Clover2 jit", TheContext);
    TheModule->setDataLayout(TheJIT->getTargetMachine().createDataLayout());
    
    TheFPM = llvm::make_unique<legacy::FunctionPassManager>(TheModule.get());
    
    //TheFPM->add(createInstructionCombiningPass()); // --> Segmentation Fault
    TheFPM->add(createReassociatePass());
    TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->doInitialization();

    create_internal_functions();
    TheLabels.clear();
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

static void call_show_value_in_jit(Value* value)
{
    Function* show_number = TheModule->getFunction("show_number_in_jit");

    std::vector<Value*> params2;
    Value* param1 = value;
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

    store_value_with_aligned(llvm_value, lvar_offset_value, current_block, 8);
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

CLObject get_string_object_of_object_name(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    CLObject object2 = create_string_object(CLASS_NAME(object_data->mClass));

    return object2;
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

BOOL invoke_virtual_method(int num_real_params, int offset, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant)
{
    CLObject object = ((*stack_ptr)-num_real_params)->mObjectValue;

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
            if(*info->try_offset != 0) {
                *info->pc = code->mCodes + *info->try_offset;
                *info->try_offset = *info->try_offset_before;
            }
            else {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL invoke_dynamic_method(int offset, int offset2, int num_params, int static_, int num_method_chains, int max_method_chains, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant)
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
            if(*info->try_offset != 0) {
                *info->pc = code->mCodes + *info->try_offset;
                *info->try_offset = *info->try_offset_before;
            }
            else {
                return FALSE;
            }
        }
    }
    /// static method ///
    else {
        char* class_name = CONS_str(constant, offset);
        char* method_name = CONS_str(constant, offset2);

        sCLClass* klass = get_class_with_load_and_initialize(class_name);

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
            if(*info->try_offset != 0) {
                *info->pc = code->mCodes + *info->try_offset;
                *info->try_offset = *info->try_offset_before;
            }
            else {
                return FALSE;
            }
        }
    }

    return TRUE;
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

BOOL run_load_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index)
{
    CLObject obj = ((*stack_ptr) -1)->mObjectValue;
    (*stack_ptr)--;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(4)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(5)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    char* value = (char*)&object_pointer->mFields[field_index];
    (*stack_ptr)->mPointerValue = value;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_store_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index)
{
    CLObject obj = ((*stack_ptr) -2)->mObjectValue;
    CLVALUE value = *(*(stack_ptr)-1);

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
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    object_pointer->mFields[field_index] = value;
    (*stack_ptr)-=2;
    **stack_ptr = value;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_load_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(7)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    sCLField* field = klass->mClassFields + field_index;

    **stack_ptr = field->mValue;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_load_class_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(8)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    sCLField* field = klass->mClassFields + field_index;
    char* value = (char*)&field->mValue;

    (*stack_ptr)->mPointerValue = value;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_store_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(9)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    CLVALUE value = *((*stack_ptr)-1);

    sCLField* field = klass->mClassFields + field_index;
    field->mValue = value;

    return TRUE;
}

BOOL run_load_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    CLObject array = ((*stack_ptr) -2)->mObjectValue;
    int element_num = ((*stack_ptr) -1)->mIntValue;
    (*stack_ptr)-=2;

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(7)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "element index is invalid");
        return FALSE;
    }

    CLVALUE value = object_pointer->mFields[element_num];
    **stack_ptr = value;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_store_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    CLObject array = ((*stack_ptr) -3)->mObjectValue;
    int element_num = ((*stack_ptr) -2)->mIntValue;
    CLVALUE value = *((*stack_ptr)-1);

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(8)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "element index is invalid");
        return FALSE;
    }

    object_pointer->mFields[element_num] = value;

    (*stack_ptr)-=3;

    **stack_ptr = value;
    (*stack_ptr)++;

    return TRUE;
}

void run_get_array_length(CLVALUE** stack_ptr)
{
    CLObject array_ = ((*stack_ptr)-1)->mObjectValue;
    sCLObject* array_data = CLOBJECT(array_);
    (*stack_ptr)--;

    (*stack_ptr)->mIntValue = array_data->mArrayNum;
    (*stack_ptr)++;
}

void run_get_regex_global(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mGlobal;
    (*stack_ptr)++;
}

void run_get_regex_ignorecase(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mIgnoreCase;
    (*stack_ptr)++;
}

void run_get_regex_multiline(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mMultiline;
    (*stack_ptr)++;
}

void run_get_regex_extended(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mExtended;
    (*stack_ptr)++;
}

void run_get_regex_dotall(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mDotAll;
    (*stack_ptr)++;
}

void run_get_regex_anchored(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mAnchored;
    (*stack_ptr)++;
}

void run_get_regex_dollar_endonly(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mDollarEndOnly;
    (*stack_ptr)++;
}

void run_get_regex_ungreedy(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mUngreedy;
    (*stack_ptr)++;
}

void run_char_uppercase(CLVALUE** stack_ptr)
{
    wchar_t c = ((*stack_ptr)-1)->mCharValue;

    wchar_t result = c;
    if(c >= 'a' && c <= 'z') {
        result = c - 'a' + 'A';
    }

    ((*stack_ptr)-1)->mCharValue = result;
}

void run_char_lowercase(CLVALUE** stack_ptr)
{
    wchar_t c = ((*stack_ptr)-1)->mCharValue;

    wchar_t result = c;
    if(c >= 'A' && c <= 'Z') {
        result = c - 'A' + 'a';
    }

    ((*stack_ptr)-1)->mCharValue = result;
}

BOOL run_create_array(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, char* class_name, int num_elements)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(11)");
        return FALSE;
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
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        return FALSE;
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}


BOOL run_create_equalable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        return FALSE;
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_sortable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        return FALSE;
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        return FALSE;
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = list_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_sortable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        return FALSE;
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = list_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_equalable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        return FALSE;
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = list_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_tuple(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements)
{
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = tuple_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_hash(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name, char* class_name2)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(14)");
        return FALSE;
    }

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(15)");
        return FALSE;
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
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements*2;
    (*stack_ptr)->mObjectValue = hash_object;
    (*stack_ptr)++;

    return TRUE;
}

void run_create_block_object(CLVALUE** stack_ptr, CLVALUE* stack, sConst* constant, int code_offset, int code_len, int constant_offset, int constant_len, int block_var_num, int parent_var_num, BOOL lambda, sVMInfo* info)

{
    sByteCode codes2;
    codes2.mCodes = CONS_str(constant, code_offset);
    codes2.mLen = code_len;

    sConst constant2;
    constant2.mConst = CONS_str(constant, constant_offset);
    constant2.mLen = constant_len;

    CLVALUE* parent_stack = stack;

    CLObject block_object = create_block_object(&codes2, &constant2, parent_stack, parent_var_num, block_var_num, info->stack_id, lambda);

    (*stack_ptr)->mObjectValue = block_object;
    (*stack_ptr)++;
}

void run_byte_to_string_cast(CLVALUE** stack_ptr)
{
    char value = ((*stack_ptr)-1)->mCharValue;

    char buf[32];
    snprintf(buf, 32, "%d", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_short_to_string_cast(CLVALUE** stack_ptr)
{
    short value = ((*stack_ptr)-1)->mShortValue;

    char buf[32];
    snprintf(buf, 32, "%d", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_int_to_string_cast(CLVALUE** stack_ptr)
{
    int value = ((*stack_ptr)-1)->mIntValue;

    char buf[32];
    snprintf(buf, 32, "%d", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_long_to_string_cast(CLVALUE** stack_ptr)
{
    long value = ((*stack_ptr)-1)->mLongValue;

    char buf[32];
    snprintf(buf, 32, "%ld", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_ubyte_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned char value = ((*stack_ptr)-1)->mUByteValue;

    char buf[32];
    snprintf(buf, 32, "%u", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_ushort_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned short value = ((*stack_ptr)-1)->mUShortValue;

    char buf[32];
    snprintf(buf, 32, "%u", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_uint_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned int value = ((*stack_ptr)-1)->mUIntValue;

    char buf[32];
    snprintf(buf, 32, "%u", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_ulong_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned long value = ((*stack_ptr)-1)->mULongValue;

    char buf[32];
    snprintf(buf, 32, "%lu", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_float_to_string_cast(CLVALUE** stack_ptr)
{
    float value = ((*stack_ptr)-1)->mFloatValue;

    char buf[32];
    snprintf(buf, 32, "%f", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_double_to_string_cast(CLVALUE** stack_ptr)
{
    double value = ((*stack_ptr)-1)->mDoubleValue;

    char buf[32];
    snprintf(buf, 32, "%lf", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_bool_to_string_cast(CLVALUE** stack_ptr)
{
    BOOL value = ((*stack_ptr)-1)->mBoolValue;

    char buf[32];
    if(value) {
        snprintf(buf, 32, "true");
    }
    else {
        snprintf(buf, 32, "false");
    }

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_regex_to_string_cast(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;

    sRegexObject* object_data = CLREGEX(regex);

    CLObject str = create_string_object(object_data->mRegexString);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_pointer_to_string_cast(CLVALUE** stack_ptr)
{
    char* value = ((*stack_ptr)-1)->mPointerValue;

    char buf[32];
    snprintf(buf, 32, "%p", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_char_to_string_cast(CLVALUE** stack_ptr)
{
    wchar_t value = ((*stack_ptr)-1)->mCharValue;

    char buf[32];
    snprintf(buf, 32, "%lc", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_cbyte_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cubyte_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cshort_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cushort_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_integer_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_uinteger_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_clong_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_culong_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cfloat_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cdouble_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cpointer_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)0;// obj_data->mFields[0].mPointerValue; 

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cchar_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cbool_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cbyte_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cubyte_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cshort_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cushort_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_integer_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_uinteger_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_clong_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_culong_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cfloat_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cdouble_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cpointer_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cchar_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cbool_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cbyte_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cubyte_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cshort_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cushort_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_integer_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_uinteger_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_clong_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_culong_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mIntValue = value;

}

void run_cfloat_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cdouble_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cpointer_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cchar_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cbool_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cbyte_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cubyte_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cshort_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cushort_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_integer_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_uinteger_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_clong_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_culong_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cfloat_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cdouble_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cpointer_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cchar_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cbool_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cbyte_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cubyte_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cshort_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cushort_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_integer_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_uinteger_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_clong_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_culong_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cfloat_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cdouble_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cpointer_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)0;// obj_data->mFields[0].mPointerValue; 

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cchar_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cbool_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cbyte_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cubyte_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cshort_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cushort_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_integer_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_uinteger_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_clong_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_culong_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cfloat_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cdouble_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cpointer_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cchar_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cbool_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cbyte_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cubyte_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cshort_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cushort_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_integer_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_uinteger_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_clong_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_culong_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mUIntValue = value;

}

void run_cfloat_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cdouble_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cpointer_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cchar_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cbool_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cbyte_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cubyte_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cshort_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cushort_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_integer_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_uinteger_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_clong_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_culong_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cfloat_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cdouble_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cpointer_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cchar_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cbool_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cbyte_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cubyte_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cshort_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cushort_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_integer_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_uinteger_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_clong_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_culong_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cfloat_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cdouble_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cchar_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cbool_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cbyte_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cubyte_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cshort_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cushort_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_integer_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_uinteger_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_clong_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_culong_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cfloat_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cdouble_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cchar_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cbool_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
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
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);
                if_value_is_zero_entry_exception_object(value, params, var_num, info, function, &current_block, "Exception", "Null pointer exception(1)");

                Function* fun = TheModule->getFunction("get_string_object_of_object_name");

                std::vector<Value*> params2;
                params2.push_back(value);

                Value* result = Builder.CreateCall(fun, params2);

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_IMPLEMENTS: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(1)");
                    return FALSE;
                }

                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);
                if_value_is_zero_entry_exception_object(value, params, var_num, info, function, &current_block, "Exception", "Null pointer exception(2)");

                Function* fun = TheModule->getFunction("object_implements_interface");

                std::vector<Value*> params2;

                params2.push_back(value);

                Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                params2.push_back(param2);

                Value* result = Builder.CreateCall(fun, params2);

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr(params, current_block, result);
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

            case OP_INVOKE_VIRTUAL_METHOD: {
                int num_real_params = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("invoke_virtual_method");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_real_params);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param2);

                std::string stack_value_name("stack");
                Value* param3 = params[stack_value_name];
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param4);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param5 = params[stack_ptr_address_name];
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(param7);

                Value* param8 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param8);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_INVOKE_DYNAMIC_METHOD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int num_params = *(int*)pc;
                pc += sizeof(int);

                BOOL static_ = *(int*)pc;
                pc += sizeof(int);

                int num_method_chains = *(int*)pc;
                pc += sizeof(int);

                int max_method_chains = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("invoke_dynamic_method");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset2);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_params);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)static_);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_method_chains);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)max_method_chains);
                params2.push_back(param6);

                std::string stack_value_name("stack");
                Value* param7 = params[stack_value_name];
                params2.push_back(param7);

                Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param8);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param9 = params[stack_ptr_address_name];
                params2.push_back(param9);

                Value* param10 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param10);

                Value* param11 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(param11);

                Value* param12 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param12);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_INVOKE_BLOCK: {
                int num_params = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("invoke_block_in_jit");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_params);
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param4 = params[stack_ptr_address_name];
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
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

            case OP_LOAD_FIELD_ADDRESS: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_load_field_address");

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

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_store_field");

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

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_LOAD_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_load_class_field");

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

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_LOAD_CLASS_FIELD_ADDRESS: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_load_class_field_address");

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

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_store_class_field");

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

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_LOAD_ELEMENT: {
                Function* fun = TheModule->getFunction("run_load_element");

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

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_ELEMENT: {
                Function* fun = TheModule->getFunction("run_store_element");

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

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_VALUE_TO_INT_ADDRESS: 
            case OP_STORE_VALUE_TO_UINT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 4);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;
            
            case OP_STORE_VALUE_TO_BYTE_ADDRESS:
            case OP_STORE_VALUE_TO_UBYTE_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 1);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 1);
                }
                break;

            case OP_STORE_VALUE_TO_SHORT_ADDRESS:
            case OP_STORE_VALUE_TO_USHORT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 2);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 1);
                }
                break;

            case OP_STORE_VALUE_TO_LONG_ADDRESS:
            case OP_STORE_VALUE_TO_ULONG_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 8);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 1);
                }
                break;

            case OP_STORE_VALUE_TO_FLOAT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 4);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

            case OP_STORE_VALUE_TO_DOUBLE_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 8);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

            case OP_STORE_VALUE_TO_POINTER_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 8);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

            case OP_STORE_VALUE_TO_CHAR_ADDRESS:
            case OP_STORE_VALUE_TO_BOOL_ADDRESS:
            case OP_STORE_VALUE_TO_OBJECT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 4);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

            case OP_LOAD_VALUE_FROM_INT_ADDRESS:
            case OP_LOAD_VALUE_FROM_UINT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 4, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LOAD_VALUE_FROM_BYTE_ADDRESS:
            case OP_LOAD_VALUE_FROM_UBYTE_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 1, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_LOAD_VALUE_FROM_SHORT_ADDRESS:
            case OP_LOAD_VALUE_FROM_USHORT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 2, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_LOAD_VALUE_FROM_LONG_ADDRESS:
            case OP_LOAD_VALUE_FROM_ULONG_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 8, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LOAD_VALUE_FROM_FLOAT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 4, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS:
            case OP_LOAD_VALUE_FROM_POINTER_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 8, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LOAD_VALUE_FROM_CHAR_ADDRESS:
            case OP_LOAD_VALUE_FROM_BOOL_ADDRESS:
            case OP_LOAD_VALUE_FROM_OBJECT_ADDRESS: {
                Value* address = get_stack_ptr_value_from_index(params, current_block, -2);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 4, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BYTE_TO_INT_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

            case OP_BYTE_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;
                
            case OP_ULONG_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_FLOAT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_BOOL_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;
                
            case OP_ULONG_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_FLOAT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_BOOL_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;



            case OP_BYTE_TO_CBYTE_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");
                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");
                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");
                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPTrunc, fvalue, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CPOINTER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CCHAR_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;
                
            case OP_ULONG_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_FLOAT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_BOOL_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_STRING_CAST: {
                Function* fun = TheModule->getFunction("run_byte_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_SHORT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_short_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_int_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_LONG_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_long_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UBYTE_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_ubyte_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_USHORT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_ushort_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_uint_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_ULONG_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_ulong_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_FLOAT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_float_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_DOUBLE_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_double_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_BOOL_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_bool_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_REGEX_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_regex_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_POINTER_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_pointer_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CHAR_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_char_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_BYTE_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_SHORT_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_UBYTE_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_USHORT_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;


            case OP_CCHAR_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;


            case OP_CCHAR_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

/*
#define OP_UBYTE_TO_BYTE_CAST 7000
#define OP_FLOAT_TO_BYTE_CAST 7007
#define OP_DOUBLE_TO_BYTE_CAST 7008
#define OP_POINTER_TO_BYTE_CAST 7009
#define OP_CHAR_TO_BYTE_CAST 7010

#define OP_BYTE_TO_SHORT_CAST 7030
#define OP_UBYTE_TO_SHORT_CAST 7031
#define OP_USHORT_TO_SHORT_CAST 7032
#define OP_FLOAT_TO_SHORT_CAST 7037
#define OP_DOUBLE_TO_SHORT_CAST 7038
#define OP_POINTER_TO_SHORT_CAST 7039
#define OP_CHAR_TO_SHORT_CAST 7040

#define OP_BYTE_TO_INT_CAST 7060
#define OP_UBYTE_TO_INT_CAST 7061
#define OP_SHORT_TO_INT_CAST 7062
#define OP_USHORT_TO_INT_CAST 7063
#define OP_UINT_TO_INT_CAST 7064
#define OP_FLOAT_TO_INT_CAST 7067
#define OP_DOUBLE_TO_INT_CAST 7068
#define OP_POINTER_TO_INT_CAST 7069
#define OP_CHAR_TO_INT_CAST 7070

#define OP_BYTE_TO_LONG_CAST 7090
#define OP_UBYTE_TO_LONG_CAST 7091
#define OP_SHORT_TO_LONG_CAST 7092
#define OP_USHORT_TO_LONG_CAST 7093
#define OP_INT_TO_LONG_CAST 7094
#define OP_UINT_TO_LONG_CAST 7095
#define OP_ULONG_TO_LONG_CAST 7096
#define OP_FLOAT_TO_LONG_CAST 7097
#define OP_DOUBLE_TO_LONG_CAST 7098
#define OP_POINTER_TO_LONG_CAST 7099
#define OP_CHAR_TO_LONG_CAST 7100

#define OP_BYTE_TO_UBYTE_CAST 7120
#define OP_SHORT_TO_UBYTE_CAST 7121
#define OP_USHORT_TO_UBYTE_CAST 7122
#define OP_INT_TO_UBYTE_CAST 7123
#define OP_UINT_TO_UBYTE_CAST 7124
#define OP_LONG_TO_UBYTE_CAST 7125
#define OP_ULONG_TO_UBYTE_CAST 7126
#define OP_FLOAT_TO_UBYTE_CAST 7127
#define OP_DOUBLE_TO_UBYTE_CAST 7128
#define OP_POINTER_TO_UBYTE_CAST 7129
#define OP_CHAR_TO_UBYTE_CAST 7130

#define OP_BYTE_TO_USHORT_CAST 7150
#define OP_UBYTE_TO_USHORT_CAST 7151
#define OP_SHORT_TO_USHORT_CAST 7152
#define OP_INT_TO_USHORT_CAST 7153
#define OP_UINT_TO_USHORT_CAST 7154
#define OP_LONG_TO_USHORT_CAST 7155
#define OP_ULONG_TO_USHORT_CAST 7156
#define OP_FLOAT_TO_USHORT_CAST 7157
#define OP_DOUBLE_TO_USHORT_CAST 7158
#define OP_POINTER_TO_USHORT_CAST 7159
#define OP_CHAR_TO_USHORT_CAST 7160

#define OP_BYTE_TO_UINT_CAST 7200
#define OP_UBYTE_TO_UINT_CAST 7201
#define OP_SHORT_TO_UINT_CAST 7202
#define OP_USHORT_TO_UINT_CAST 7203
#define OP_INT_TO_UINT_CAST 7204
#define OP_LONG_TO_UINT_CAST 7205
#define OP_ULONG_TO_UINT_CAST 7206
#define OP_FLOAT_TO_UINT_CAST 7207
#define OP_DOUBLE_TO_UINT_CAST 7208
#define OP_POINTER_TO_UINT_CAST 7209
#define OP_CHAR_TO_UINT_CAST 7210

#define OP_BYTE_TO_ULONG_CAST 7230
#define OP_UBYTE_TO_ULONG_CAST 7231
#define OP_SHORT_TO_ULONG_CAST 7232
#define OP_USHORT_TO_ULONG_CAST 7233
#define OP_INT_TO_ULONG_CAST 7234
#define OP_UINT_TO_ULONG_CAST 7235
#define OP_LONG_TO_ULONG_CAST 7236
#define OP_FLOAT_TO_ULONG_CAST 7237
#define OP_DOUBLE_TO_ULONG_CAST 7238
#define OP_POINTER_TO_ULONG_CAST 7239
#define OP_CHAR_TO_ULONG_CAST 7240

#define OP_BYTE_TO_FLOAT_CAST 7260
#define OP_UBYTE_TO_FLOAT_CAST 7261
#define OP_SHORT_TO_FLOAT_CAST 7262
#define OP_USHORT_TO_FLOAT_CAST 7263
#define OP_INT_TO_FLOAT_CAST 7264
#define OP_UINT_TO_FLOAT_CAST 7265
#define OP_LONG_TO_FLOAT_CAST 7266
#define OP_ULONG_TO_FLOAT_CAST 7267
#define OP_DOUBLE_TO_FLOAT_CAST 7268
#define OP_CHAR_TO_FLOAT_CAST 7269

#define OP_BYTE_TO_DOUBLE_CAST 7290
#define OP_UBYTE_TO_DOUBLE_CAST 7291
#define OP_SHORT_TO_DOUBLE_CAST 7292
#define OP_USHORT_TO_DOUBLE_CAST 7293
#define OP_INT_TO_DOUBLE_CAST 7294
#define OP_UINT_TO_DOUBLE_CAST 7295
#define OP_LONG_TO_DOUBLE_CAST 7296
#define OP_ULONG_TO_DOUBLE_CAST 7297
#define OP_FLOAT_TO_DOUBLE_CAST 7298
#define OP_CHAR_TO_DOUBLE_CAST 7299

#define OP_BYTE_TO_POINTER_CAST 7320
#define OP_UBYTE_TO_POINTER_CAST 7321
#define OP_SHORT_TO_POINTER_CAST 7322
#define OP_USHORT_TO_POINTER_CAST 7323
#define OP_INT_TO_POINTER_CAST 7324
#define OP_UINT_TO_POINTER_CAST 7325
#define OP_LONG_TO_POINTER_CAST 7326
#define OP_ULONG_TO_POINTER_CAST 7327
#define OP_CHAR_TO_POINTER_CAST 7328

#define OP_BYTE_TO_CHAR_CAST 7330
#define OP_UBYTE_TO_CHAR_CAST 7331
#define OP_SHORT_TO_CHAR_CAST 7332
#define OP_USHORT_TO_CHAR_CAST 7333
#define OP_INT_TO_CHAR_CAST 7334
#define OP_UINT_TO_CHAR_CAST 7335
#define OP_LONG_TO_CHAR_CAST 7336
#define OP_ULONG_TO_CHAR_CAST 7337
#define OP_FLOAT_TO_CHAR_CAST 7338
#define OP_DOUBLE_TO_CHAR_CAST 7339
#define OP_POINTER_TO_CHAR_CAST 7340

#define OP_ARRAY_TO_CARRAY_CAST 7700
*/

            case OP_GET_ARRAY_LENGTH: {
                Function* fun = TheModule->getFunction("run_get_array_length");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_GLOBAL: {
                Function* fun = TheModule->getFunction("run_get_regex_global");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_IGNORE_CASE: {
                Function* fun = TheModule->getFunction("run_get_regex_ignorecase");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_MULTILINE: {
                Function* fun = TheModule->getFunction("run_get_regex_multiline");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_EXTENDED: {
                Function* fun = TheModule->getFunction("run_get_regex_extended");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_DOTALL: {
                Function* fun = TheModule->getFunction("run_get_regex_dotall");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_ANCHORED: {
                Function* fun = TheModule->getFunction("run_get_regex_anchored");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_DOLLAR_ENDONLY: {
                Function* fun = TheModule->getFunction("run_get_regex_dollar_endonly");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_UNGREEDY: {
                Function* fun = TheModule->getFunction("run_get_regex_ungreedy");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CHAR_UPPERCASE: {
                Function* fun = TheModule->getFunction("run_char_uppercase");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CHAR_LOWERCASE: {
                Function* fun = TheModule->getFunction("run_char_lowercase");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
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

            case OP_CREATE_BUFFER: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                char* str = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_buffer_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)size);
                params2.push_back(param2);

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_CREATE_PATH: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* buf = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_path_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)buf);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(param1);

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_CREATE_ARRAY: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_array");

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

                Value* param5 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_carray");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_SORTABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_sortable_carray");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_EQUALABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_equalable_carray");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_list");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_SORTALBE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_sortable_list");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_EQUALABLE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_equalable_list");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_TUPLE : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_create_tuple");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_HASH : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);
                char* class_name2 = CONS_str(constant, offset2);

                Function* fun = TheModule->getFunction("run_create_hash");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name2);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_BLOCK_OBJECT : {
                int code_offset = *(int*)pc;
                pc += sizeof(int);

                int code_len = *(int*)pc;
                pc += sizeof(int);

                int constant_offset = *(int*)pc;
                pc += sizeof(int);

                int constant_len = *(int*)pc;
                pc += sizeof(int);

                int block_var_num = *(int*)pc;
                pc += sizeof(int);

                int parent_var_num = *(int*)pc;
                pc += sizeof(int);

                int lambda = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_create_block_object");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)code_offset);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)code_len);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)constant_offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)constant_len);
                params2.push_back(param7);

                Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)block_var_num);
                params2.push_back(param8);

                Value* param9 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)parent_var_num);
                params2.push_back(param9);

                Value* param10 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)lambda);
                params2.push_back(param10);

                Value* param11 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param11);

                Builder.CreateCall(fun, params2);
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
    TheFPM->run(*function);

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
    info->stack_id = stack_id;
    
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
