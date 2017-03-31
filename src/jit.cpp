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

        Type* result_type = IntegerType::get(TheContext, 32);
        FunctionType* function_type = FunctionType::get(result_type, params, false);

        Function* function = Function::Create(function_type, Function::ExternalLinkage, name, TheModule.get());
        std::vector<std::string> args;

        std::string arg1("stack_ptr");
        args.push_back(arg1);
        std::string arg2("lvar");
        args.push_back(arg2);
        std::string arg3("info");
        args.push_back(arg3);
        std::string arg4("stack");
        args.push_back(arg4);

        unsigned index = 0;
        for (auto &arg : function->args()) {
            arg.setName(args[index++]);
        }

        this->llvmFunction = function;
    }
};

static std::map<std::string, std::unique_ptr<FunctionAST>> LLVMFunctions;

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

static Value* stack_value_to_llvm_value(int offset)
{
    return nullptr;
}

static BOOL invoke_method_in_jit(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    if(method->mFlags & METHOD_FLAGS_NATIVE) {
        CLVALUE* lvar = *stack_ptr - method->mNumParams;

        if(method->uCode.mNativeMethod == NULL) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Native method not found");
            return FALSE;
        }

        info->current_stack = stack;        // for invoking_block in native method
        info->current_var_num = var_num;

        Type* result_type = IntegerType::get(TheContext, 32);

        std::vector<Type *> type_params;
        Type* param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
        type_params.push_back(param1_type);
        Type* param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
        type_params.push_back(param2_type);
        Type* param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
        type_params.push_back(param3_type);

        FunctionType* function_type = FunctionType::get(result_type, type_params, false);
        char* native_fun_name = method->uCode.mNativeFunName;

        Function* native_method = Function::Create(function_type, Function::ExternalLinkage, native_fun_name, TheModule.get());

        std::vector<Value*> params;

        Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)stack_ptr);
        params.push_back(param1);
        Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)lvar);
        params.push_back(param2);
        Value* param3 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
        params.push_back(param3);

        Value* result = Builder.CreateCall(native_method, params);

        if(is_void_type(method->mResultType, klass)) {
            *stack_ptr = lvar;
            (*stack_ptr)->mIntValue = 0;
            (*stack_ptr)++;
        }
        else {
            *stack_ptr = lvar;
            (*stack_ptr)->LLVMValue = (void*)result;
            (*stack_ptr)++;
        }
    }
/*
    else {
        int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);
        CLVALUE* lvar = *stack_ptr - real_param_num;

        sByteCode* code = &method->uCode.mByteCodes;
        sConst* constant = &klass->mConst;
        CLVALUE* new_stack = lvar;
        int new_var_num = method->mVarNum;

        /// initialize local var except params ///
        memset(lvar + real_param_num, 0, sizeof(CLVALUE)* (new_var_num - real_param_num));

        if(!vm(code, constant, new_stack, new_var_num, klass, info)) {
            *stack_ptr = lvar;
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            return FALSE;
        }

        *stack_ptr = lvar;      // see OP_RETURN
        **stack_ptr = *new_stack;
        (*stack_ptr)++;
    }
*/

    return TRUE;
}

static void inc_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* block, int value)
{
    std::string arg_name("stack_ptr");
    Value* stack_ptr_value = params[arg_name];

    Value* stack_ptr_value_address = ConstantExpr::getIntToPtr(cast<Constant>(stack_ptr_value), PointerType::getUnqual(Builder.getInt64Ty()));

    Value* lvalue = stack_ptr_value_address;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* inc_ptr_value = Builder.CreateAdd(lvalue, rvalue, "inc_ptr_value", false, false);

    params[arg_name] = inc_ptr_value;
}

static void dec_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* block, int value)
{
    std::string arg_name("stack_ptr");
    Value* stack_ptr_value = params[arg_name];

    Value* stack_ptr_value_address = ConstantExpr::getIntToPtr(cast<Constant>(stack_ptr_value), PointerType::getUnqual(Builder.getInt64Ty()));

    Value* lvalue = stack_ptr_value_address;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* dec_ptr_value = Builder.CreateSub(lvalue, rvalue, "dec_ptr_value", false, false);

    params[arg_name] = dec_ptr_value;
}

static void push_value_to_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* block, Value* value)
{
    std::string arg_name("stack_ptr");
    Value* stack_ptr_value = params[arg_name];

    StoreInst* store_inst = new StoreInst(value, stack_ptr_value);
    store_inst->setAlignment(8);
    block->getInstList().push_back(store_inst);

    inc_stack_ptr(params, block, 1);
}

static BOOL compile_to_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    std::string func_name("__anon_expr");
    std::unique_ptr<FunctionAST> llvm_func = llvm::make_unique<FunctionAST>(func_name);

    LLVMFunctions[func_name] = std::move(llvm_func);

    Function* function = TheModule->getFunction(func_name);

    // Create a new basic block to start insertion into.
    BasicBlock *block = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(block);
  
    register char* pc = code->mCodes;
    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    Value* values[CLOVER_STACK_SIZE];

    Value** value_ptr = values;

    int try_offset_before = 0;
    int try_offset = 0;

    std::map<std::string, Value *> params;
    for(auto &param : function->args()) {
        params[param.getName()] = &param;
    }

    while(pc - code->mCodes < code->mLen) {
        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);

        switch(inst) {
            case OP_POP:
puts("OP_POP");
                value_ptr--;
                dec_stack_ptr(params, block, 1);
                break;

            case OP_LDCINT: 
                {
puts("OP_LDCINT");
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

                    *value_ptr = llvm_value;
                    value_ptr++;

                    push_value_to_stack_ptr(params, block, llvm_value);
                }
                break;

            case OP_IADD: 
                {
puts("OP_IADD");
                    Value* lvalue = *(value_ptr-2);
                    Value* rvalue = *(value_ptr-1);

                    Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, false);

                    dec_stack_ptr(params, block, 2);
                    push_value_to_stack_ptr(params, block, llvm_value);
                }
                break;

/*
            case OP_RETURN:
                {
puts("OP_RETURN");
                std::string arg_name("stack_ptr");
                Value* stack_ptr_value = params[arg_name];
                Value* stack_ptr_value_address = Builder.CreateLoad(stack_ptr_value, "var_tmp");

                Value* lvalue = stack_ptr_value_address;
                Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 1, true));

                Value* stack_ptr_minus_1_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, false);

                Value* stack_ptr_minus_1_value_address = Builder.CreateLoad(stack_ptr_minus_1_value, "stack_ptr_minus_1");
                std::string arg_name2("stack");
                Value* stack_value = params[arg_name2];
                Value* stack_value_address = Builder.CreateLoad(stack_ptr_value, "stack");

                StoreInst* store_inst = new StoreInst(stack_value_address, stack_ptr_minus_1_value);
                store_inst->setAlignment(4);
                block->getInstList().push_back(store_inst);
                }
                return TRUE;

            case OP_INVOKE_METHOD:
                {
puts("OP_INVOKE_METHOD");
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

                    if(!invoke_method_in_jit(klass, method, stack, var_num, &stack_ptr, info)) {
                        if(try_offset != 0) {
                            pc = code->mCodes + try_offset;
                            try_offset = try_offset_before;
                        }
                        else {
                            return FALSE;
                        }
                    }
                }
                break;

            case OP_CREATE_STRING:
                {
puts("OP_CREATE_STRING");
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    Type* result_type = PointerType::get(IntegerType::get(TheContext, sizeof(Value)), 0);

                    std::vector<Type *> type_params;
                    Type* param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
                    type_params.push_back(param1_type);

                    FunctionType* function_type = FunctionType::get(result_type, type_params, false);

                    Function* create_str_fun = Function::Create(function_type, Function::ExternalLinkage, "create_string_object", TheModule.get());

                    std::vector<Value*> params;
                    Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
                    params.push_back(param1);

                    Value* result = Builder.CreateCall(create_str_fun, params);

                    stack_ptr->LLVMValue = result;
                    stack_ptr++;
                }
                break;
*/
        }
    }

    // Finish off the function.
    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));

    //Builder.SetInsertPoint(block);
    Builder.CreateRet(ret_value);

    // Validate the generated code, checking for consistency.
    verifyFunction(*function);

    // Run the optimizer on the function.
    //TheFPM->run(*function);

    return TRUE;
}

typedef BOOL (*fJITMethodType)(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack);

static BOOL run_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    long stack_id = append_stack_to_stack_list(stack, &stack_ptr);

    //InitializeModuleAndPassManager();
    
    auto ExprSymbol = TheJIT->findSymbol("__anon_expr");
    assert(ExprSymbol && "Function not found");

    fJITMethodType function = (fJITMethodType)ExprSymbol.getAddress();
    if(!function(stack_ptr, lvar, info, stack)) {
        remove_stack_to_stack_list(stack);
        return FALSE;
    }
    
    remove_stack_to_stack_list(stack);

puts("OK");

    return TRUE;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    auto ExprSymbol = TheJIT->findSymbol("__anon_expr");
    if(!ExprSymbol) {
        if(!compile_to_native_code(code, constant, stack, var_num, klass, method, info)) {
            return FALSE;
        }

        TheModule->dump();
        auto H = TheJIT->addModule(std::move(TheModule));
    }

    if(!run_native_code(code, constant, stack, var_num, klass, method, info)) {
        return FALSE;
    }

printf("var_num %d\n", var_num);

int i;
for(i=0; i<10; i++) {
    printf("stack [%d] %d\n", i, stack[i].mIntValue);
}

    return TRUE;
}

} // extern "C"
