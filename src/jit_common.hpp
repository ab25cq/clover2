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
#include "llvm-c/BitWriter.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/MemoryBuffer.h"
#include <fstream>
#include <iostream>

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

extern LLVMContext TheContext;
extern IRBuilder<> Builder;
extern std::unique_ptr<Module> TheModule;
extern std::unique_ptr<legacy::FunctionPassManager> TheFPM;
extern std::unique_ptr<CloverJIT> TheJIT;
extern std::map<std::string, BasicBlock*> TheLabels;

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
        Type* param6_type = IntegerType::get(TheContext, 32);
        params.push_back(param6_type);
        Type* param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
        params.push_back(param7_type);
        Type* param8_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
        params.push_back(param8_type);

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
        std::string var_num_name("var_num");
        args.push_back(var_num_name);
        std::string object_stack_name("object_stack");
        args.push_back(object_stack_name);
        std::string object_stack_ptr_name("object_stack_ptr");
        args.push_back(object_stack_ptr_name);

        unsigned index = 0;
        for (auto &arg : function->args()) {
            arg.setName(args[index++]);
        }

        this->llvmFunction = function;
    }
};

extern std::map<std::string, std::unique_ptr<FunctionAST>> LLVMFunctions;

extern "C" 
{

struct LVALUEStruct {
    Value* value;
    BOOL vm_stack;
    int lvar_address_index;
};

typedef struct LVALUEStruct LVALUE;

void create_internal_functions();
void InitializeModuleAndPassManager();

typedef BOOL (*fJITMethodType)(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address, int var_num, CLVALUE* object_stack, CLVALUE** object_stack_ptr);

/// jit.cpp ///
BOOL compile_to_native_code(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2);
void if_value_is_zero_ret_zero(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block);

/// jit_sub.cpp ///
void create_internal_functions();
void create_method_path_for_jit(sCLClass* klass, sCLMethod* method, char* result, int size_result);
void show_stack_stat(CLVALUE** stack_ptr, CLVALUE* stack);
BOOL show_stack_in_jit(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info);
void show_inst_in_jit(int opecode);
void show_number_in_jit(int number);
void call_show_number_in_jit(int number);
void call_show_value_in_jit(Value* value);
void show_str_in_jit(char* str);
void call_show_str_in_jit(Value* value);
void call_show_stack_stat(std::map<std::string, Value *> params);
void call_show_inst_in_jit(int opecode);
void call_show_stack(std::map<std::string, Value *> params);
void store_value(Value* llvm_value, Value* stored_value, BasicBlock* current_block);
void store_value_with_aligned(Value* llvm_value, Value* stored_value, BasicBlock* current_block, int align);
void inc_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* current_block, int value);
Value* get_stack_ptr_value_from_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset);
Value* get_stack_ptr_float_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align);
Value* get_stack_ptr_pointer_value_from_index(std::map<std::string, Value*>& params, BasicBlock* current_block, int index);
void push_value_to_stack_ptr_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, Value* value, int align);
void push_value_to_stack_ptr_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, Value* value, int align);
Value* get_value_from_char_array(char* str);
void run_entry_exception_object_with_class_name2(std::map<std::string, Value *> params, char* class_name, char* message);
void if_value_is_zero_entry_exception_object(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block, char* class_name, char* message);
void if_value_is_zero_ret_zero(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block);
CLObject get_string_object_of_object_name(CLObject object);
BOOL invoke_virtual_method(int num_real_params, int offset, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant);
BOOL invoke_dynamic_method(int offset, int offset2, int num_params, int static_, int num_method_chains, int max_method_chains, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant);
BOOL invoke_block_in_jit(int num_params, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info);
BOOL get_vm_stack_ptr_flag(BOOL* llvm_stack_from_vm_stack_flag, Value** llvm_stack_ptr, Value* llvm_stack , int index);

extern GlobalVariable* gSigIntValue;
extern StructType* gCLValueAndBoolStruct;
extern StructType* gPointerAndBoolStruct;
}
