#include "jit_common.hpp"

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
std::unique_ptr<Module> TheModule;
std::unique_ptr<legacy::FunctionPassManager> TheFPM;
std::unique_ptr<CloverJIT> TheJIT;
std::map<std::string, BasicBlock*> TheLabels;

std::map<std::string, std::unique_ptr<FunctionAST>> LLVMFunctions;

//////////////////////////////////////////////////////////////////////
// JIT main
//////////////////////////////////////////////////////////////////////
#define MAX_COND_JUMP 128

extern "C"
{

//////////////////////////////////////////////////////////////////////
// LLVM debug functions
//////////////////////////////////////////////////////////////////////
void show_stack_for_llvm_stack(LVALUE* llvm_stack, LVALUE* llvm_stack_ptr, int var_num)
{
    printf("llvm_stack %p\n", llvm_stack);
    printf("llvm_stack_ptr %p\n", llvm_stack_ptr);
    printf("llvm_stack_ptr - llvm_stack %d\n", llvm_stack_ptr - llvm_stack);
    printf("var_num %d\n", var_num);

    int i;
    for(i=0; i<10; i++) {
        printf("stack[%d] %p %d (VM stack value %d)\n", i, llvm_stack[i].value, llvm_stack[i].value, llvm_stack[i].vm_stack);
    }
}

//////////////////////////////////////////////////////////////////////
// LLVM operation functions
//////////////////////////////////////////////////////////////////////
static LVALUE* get_stack_ptr_value_from_index(LVALUE* llvm_stack_ptr, int index)
{
    return llvm_stack_ptr + index;
}

static void dec_stack_ptr(LVALUE** llvm_stack_ptr, int value)
{
    int i;
    for(i=0; i<value; i++) {
        (*llvm_stack_ptr)->value = 0;
        (*llvm_stack_ptr)->vm_stack = FALSE;

        (*llvm_stack_ptr)--;
    }

    (*llvm_stack_ptr)->value = 0;
    (*llvm_stack_ptr)->vm_stack = FALSE;
}

static void push_value_to_stack_ptr(LVALUE** llvm_stack_ptr, LVALUE* value)
{
    (**llvm_stack_ptr) = *value;
    (*llvm_stack_ptr)++;
}

static void store_llvm_value_to_lvar_with_offset(LVALUE* llvm_stack, int index, LVALUE* llvm_value)
{
    /// 0 clear align 8 byte ///
    Value* llvm_value2 = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateStore(llvm_value2, llvm_stack[index].value);

    /// store ///
    Builder.CreateStore(llvm_value->value, llvm_stack[index].value);
    llvm_stack[index].vm_stack = llvm_value->vm_stack;
}

static LVALUE get_llvm_value_from_lvar_with_offset(LVALUE* llvm_stack, int index)
{
    LVALUE* llvm_value = llvm_stack + index;
    LVALUE result;
    result.value = Builder.CreateLoad(llvm_value->value, "lvar");
    result.vm_stack = llvm_value->vm_stack;

    return result;
}

static LVALUE get_vm_stack_ptr_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* stack_pointer_offset_value = Builder.CreateAdd(lvalue, rvalue, "stack_pointer_offset_value", true, true);

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(stack_pointer_offset_value, align, "stack_pointer_offset_value");

    switch(align) {
        case 1:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            break;

        case 2:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            break;

        case 4:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            break;
    }

    result.vm_stack = TRUE;

    return result;
}

static void inc_vm_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* current_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");


    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* inc_ptr_value = Builder.CreateAdd(lvalue, rvalue, "inc_ptr_value", false, false);

    std::string stack_ptr_arg_name("stack_ptr");
    params[stack_ptr_arg_name] = inc_ptr_value;

    Builder.CreateStore(inc_ptr_value, stack_ptr_address_value);
}

static void push_value_to_vm_stack_ptr_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, Value* value, int align)
{
    Builder.SetInsertPoint(current_block);

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateAlignedLoad(stack_ptr_address_value, align, "loaded_stack_ptr_address_value");

    Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
    Builder.CreateAlignedStore(zero, loaded_stack_ptr_address_value, 8);

    Builder.CreateAlignedStore(value, loaded_stack_ptr_address_value, align);

    inc_vm_stack_ptr(params, current_block, 1);
}

static LVALUE get_stack_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_name("stack");
    Value* stack_address_value = params[stack_name];

    Value* lvalue = stack_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* stack_offset_address_value = Builder.CreateAdd(lvalue, rvalue, "stack_offset_address_value", true, true);

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(stack_offset_address_value, align, "stack_offset_value");

    switch(align) {
        case 1:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            break;

        case 2:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            break;

        case 4:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            break;
    }

    result.vm_stack = TRUE;

    return result;
}

//////////////////////////////////////////////////////////////////////
// method call
//////////////////////////////////////////////////////////////////////
static void llvm_stack_to_vm_stack(LVALUE* llvm_stack_ptr, std::map<std::string, Value*> params, BasicBlock* current_block, int num)
{
    int i;
    for(i=0; i<num; i++) {
        Value* llvm_value = llvm_stack_ptr[i-num].value;
        push_value_to_vm_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
    }
}

static void finish_method_call(Value* result, sCLClass* klass, sCLMethod* method, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char* try_catch_label_name)
{
    // if result is FALSE ret 0
    Value* comp = Builder.CreateICmpNE(result, ConstantInt::get(TheContext, llvm::APInt(32, 1, true)), "ifcond");

    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Function* try_catch_label_name_fun = TheModule->getFunction("get_try_catch_label_name");

    std::vector<Value*> params2;

    std::string info_value_name("info");
    Value* info_value = params[info_value_name];
    params2.push_back(info_value);

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
}

BOOL call_invoke_method(sCLClass* klass, sCLMethod* method, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char* try_catch_label_name, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack)
{
    /// llvm stack to VM stack ///
    int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);
    llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, real_param_num);
    
    /// go ///
    Function* llvm_function = TheModule->getFunction("invoke_method");

    MASSERT(llvm_function != null_ptr);

    std::vector<Value*> params2;

    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
    params2.push_back(klass_value);

    Value* method_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)method);
    params2.push_back(method_value);

    std::string stack_value_name("stack");
    Value* stack_value = params[stack_value_name];
    params2.push_back(stack_value);

    std::string var_num_value_name("var_num");
    Value* var_num_value = params[var_num_value_name];
    params2.push_back(var_num_value);

    std::string stack_ptr_address_value_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_value_name];
    params2.push_back(stack_ptr_address_value);

    std::string info_value_name("info");
    Value* info_value = params[info_value_name];
    params2.push_back(info_value);

    /// go ///
    Value* result = Builder.CreateCall(llvm_function, params2);

    finish_method_call(result, klass, method, params, current_block, function, try_catch_label_name);

    /// dec llvm stack pointer ///
    dec_stack_ptr(llvm_stack_ptr, real_param_num);

    /// vm stack_ptr to llvm stack ///
    LVALUE llvm_value = get_vm_stack_ptr_value_from_index_with_aligned(params, *current_block, -1, 8);

    push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

    return TRUE;
}

void if_value_is_zero_ret_zero(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block)
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

Value* get_value_from_char_array(char* str)
{
    Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
    return ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
}

static void store_value_to_lvar_with_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, Value* llvm_value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];
    
    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* lvar_offset_value = Builder.CreateAdd(lvalue, rvalue, "lvar_offset_value", true, true);

    Builder.CreateAlignedStore(llvm_value, lvar_offset_value, 8);
}

static void flush_vm_stack_lvar_from_llvm_lvar(LVALUE* llvm_stack, int var_num, std::map<std::string, Value*> params, BasicBlock* current_block)
{
    int i;
    for(i=0; i<var_num; i++) {
        Value* llvm_value = llvm_stack[i].value;
        if(llvm_stack[i].value != 0) {
            store_value_to_lvar_with_offset(params, current_block, i, llvm_value);
        }
    }
}

static void flush_vm_stack_from_llvm_stack(LVALUE* llvm_stack, int var_num, LVALUE* llvm_stack_ptr, std::map<std::string, Value*> params, BasicBlock* current_block)
{
    flush_vm_stack_lvar_from_llvm_lvar(llvm_stack, var_num, params, current_block);

    int stack_value_num = llvm_stack_ptr - llvm_stack;

    stack_value_num -= var_num;
    
    int i;
    for(i=0; i<stack_value_num; i++) {
        Value* llvm_value = llvm_stack_ptr[i-stack_value_num].value;
        push_value_to_vm_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
    }
}

static void dec_vm_stack_ptr(std::map<std::string, Value*>& params, BasicBlock* current_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*value, true));
    Value* dec_ptr_value = Builder.CreateSub(lvalue, rvalue, "dec_ptr_value", true, true);

    std::string stack_ptr_arg_name("stack_ptr");
    params[stack_ptr_arg_name] = dec_ptr_value;

    Builder.CreateStore(dec_ptr_value, stack_ptr_address_value);
}

static LVALUE get_lvar_value_from_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*offset, true));
    Value* offset_lvar = Builder.CreateAdd(lvalue, rvalue, "offset_lvar", true, true);

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(offset_lvar, 8, "offset_lvar");
    result.vm_stack = TRUE;

    return result;
}

static void restore_lvar_of_llvm_stack_from_lvar_of_vm_stack(LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value = get_lvar_value_from_offset(params, current_block, i);
        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }
}

void try_function(sVMInfo* info, char* try_cach_label)
{
    info->try_catch_label_name = try_cach_label;
}

StructType* get_vm_info_struct_type()
{
    StructType* result_type = StructType::create(TheContext, "vm_info_struct");
    std::vector<Type*> fields;
    Type* field_type1 = PointerType::get(IntegerType::get(TheContext, 8), 0); // try_catch_label_name
    fields.push_back(field_type1);
    Type* field_type2 = PointerType::get(IntegerType::get(TheContext, 64), 0); // current_stack
    fields.push_back(field_type2);
    Type* field_type3 = IntegerType::get(TheContext, 32); // current_var_num
    fields.push_back(field_type3);
    Type* field_type4 = PointerType::get(IntegerType::get(TheContext, 8), 0); // sname
    fields.push_back(field_type4);
    Type* field_type5 = IntegerType::get(TheContext, 32);                       // sline
    fields.push_back(field_type5);
    Type* field_type6 = PointerType::get(IntegerType::get(TheContext, 32), 0); // try_offset
    fields.push_back(field_type6);
    Type* field_type7 = PointerType::get(IntegerType::get(TheContext, 32), 0); // try_offset_before
    fields.push_back(field_type7);
    Type* field_type8 = PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0); // pc
    fields.push_back(field_type8);
    Type* field_type9 = IntegerType::get(TheContext, 64);                           // stack_id
    fields.push_back(field_type9);
    Type* field_type10 = ArrayType::get(IntegerType::get(TheContext, 8), EXCEPTION_MESSAGE_MAX);  // exception_message
    fields.push_back(field_type10);

    if(result_type->isOpaque()) {
        result_type->setBody(fields, false);
    }

    return result_type;
}

static AllocaInst* create_entry_block_alloca(Function* function, int index)
{
    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
    char var_name[128];
    snprintf(var_name, 128, "lvar$%d$", index);
    return builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, var_name);
}

struct sGetFieldFromObjectResultStruct {
    CLVALUE result1;
    BOOL result2;
};

struct sGetFieldFromObjectResultStruct get_field_from_object(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject obj, int field_index)
{
    struct sGetFieldFromObjectResultStruct result;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3)");
        result.result1.mLongValue = 0;
        result.result2 = 0;

        return result;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(4)");
        result.result1.mLongValue = 0;
        result.result2 = 0;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        result.result1.mLongValue = 0;
        result.result2 = 0;
        return result;
    }

    CLVALUE value = object_pointer->mFields[field_index];

    result.result1 = value;
    result.result2 = 1;

    return result;
}

//////////////////////////////////////////////////////////////////////
// LLVM core
//////////////////////////////////////////////////////////////////////
BOOL compile_to_native_code(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2)
{
    std::string func_name(method_path2);
    std::unique_ptr<FunctionAST> llvm_func = llvm::make_unique<FunctionAST>(func_name);

    char* try_catch_label_name = NULL;

    LLVMFunctions[func_name] = std::move(llvm_func);

    Function* function = TheModule->getFunction(func_name);

    // Create a new basic block to start insertion into.
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(current_block);
  
    register char* pc = code->mCodes;

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

    /// Stack to LLVM ///
    int var_num = method->mVarNum;

    LVALUE llvm_stack[CLOVER_STACK_SIZE];
    memset(llvm_stack, 0, sizeof(LVALUE*)*CLOVER_STACK_SIZE);

    LVALUE* llvm_stack_ptr = llvm_stack + var_num;

    /// alloc local variables ///
    int i;
    for(i=0; i<var_num; i++) {
        llvm_stack[i].value = create_entry_block_alloca(function, i);
        llvm_stack[i].vm_stack = FALSE;
    }

    /// parametor from VM stack ptr ///
    int real_param_num = method->mNumParams + ((method->mFlags & METHOD_FLAGS_CLASS_METHOD) ? 0:1);
    for(i=0; i<real_param_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);

        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }

    while(pc - code->mCodes < code->mLen) {
        int k;
        for(k=0; k<num_cond_jump; k++) {
            if(pc == cond_jump_labels[k]) {
                Builder.SetInsertPoint(entry_condends[k]);
                current_block = entry_condends[k];

                int j;
                for(j=k; j<num_cond_jump; j++) {
                    cond_jump_labels[j] = cond_jump_labels[j+1];
                    entry_condends[j] = entry_condends[j+1];
                }
                num_cond_jump--;
            }
        }
        for(k=0; k<num_cond_not_jump; k++) {
            if(pc == cond_not_jump_labels[k]) {
                Builder.SetInsertPoint(entry_condnotends[k]);
                current_block = entry_condnotends[k];

                int j;
                for(j=k; j<num_cond_not_jump; j++) {
                    cond_not_jump_labels[j] = cond_not_jump_labels[j+1];
                    entry_condnotends[j] = entry_condnotends[j+1];
                }
                num_cond_not_jump--;
            }
        }

        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);

#ifdef MDEBUG
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
//call_show_inst_in_jit(inst);
show_inst_in_jit(inst);
}
#endif

        switch(inst) {
            case OP_POP:
                dec_stack_ptr(&llvm_stack_ptr, 1);
                break;

            case OP_POP_N:
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    dec_stack_ptr(&llvm_stack_ptr, value);
                }
                break;

            case OP_REVERSE: {
                LVALUE llvm_value = *get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE llvm_value2 = *get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                
                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_DUPE: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, llvm_value);
                }
                break;

            case OP_COND_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                LVALUE* conditional_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                BasicBlock* cond_jump_then_block = BasicBlock::Create(TheContext, "cond_jump_then", function);
                entry_condends[num_cond_jump] = BasicBlock::Create(TheContext, "entry_condend", function);

                Builder.CreateCondBr(conditional_value->value, entry_condends[num_cond_jump], cond_jump_then_block);

                Builder.SetInsertPoint(cond_jump_then_block);

                current_block = cond_jump_then_block;

                cond_jump_labels[num_cond_jump] = pc + jump_value;
                num_cond_jump++;

                if(num_cond_jump >= MAX_COND_JUMP) {
                    fprintf(stderr, "overflow number of condjump\n");
                    return FALSE;
                }

                dec_stack_ptr(&llvm_stack_ptr, 1);
                }
                break;

            case OP_COND_NOT_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                LVALUE* conditional_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                BasicBlock* cond_not_jump_then_block = BasicBlock::Create(TheContext, "cond_not_jump_then", function);
                entry_condnotends[num_cond_not_jump] = BasicBlock::Create(TheContext, "entry_condnotend", function);

                Builder.CreateCondBr(conditional_value->value, cond_not_jump_then_block, entry_condnotends[num_cond_not_jump]);

                Builder.SetInsertPoint(cond_not_jump_then_block);

                current_block = cond_not_jump_then_block;

                cond_not_jump_labels[num_cond_not_jump] = pc + jump_value;
                num_cond_not_jump++;

                if(num_cond_not_jump >= MAX_COND_JUMP) {
                    fprintf(stderr, "overflow number of condnotjump\n");
                    return FALSE;
                }

                dec_stack_ptr(&llvm_stack_ptr, 1);
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

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                Builder.CreateStore(llvm_value->value, stack_value);

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

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Builder.CreateStore(llvm_value->value, stack_value);

                Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object");

                std::vector<Value*> params2;

                Value* param1 = llvm_value->value;
                params2.push_back(param1);

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
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

/*
                std::vector<Type*> args_type;
                args_type.push_back(PointerType::get(structTy, 0));

                v = builder->CreateStructGEP(v, 1);
                v = builder->CreateLoad(v, "load0");
                v = builder->CreateStructGEP(v, 0);
                v = builder->CreateLoad(v, "load1");
                builder->CreateRet(v);
*/

                Function* try_fun = TheModule->getFunction("try_function");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Value* try_catch_label_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)try_catch_label_name);
                params2.push_back(try_catch_label_value);

                (void)Builder.CreateCall(try_fun, params2);
                }
                break;

            case OP_HEAD_OF_EXPRESSION: {
                Value* sig_int_value = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                Builder.CreateStore(sig_int_value, gSigIntValue);
                }
                break;

            case OP_SIGINT: {
                Value* sig_int_value = Builder.CreateLoad(gSigIntValue, "sig_int_value");

                BasicBlock* then_block = BasicBlock::Create(TheContext, "sigint_then_block", function);
                BasicBlock* else_block = BasicBlock::Create(TheContext, "entry_after_sigint", function);

                Builder.CreateCondBr(sig_int_value, then_block, else_block);

                Builder.SetInsertPoint(then_block);

                Value* llvm_value1 = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                Builder.CreateStore(llvm_value1, gSigIntValue);

                Function* entry_exception_object_with_class_name_fun = TheModule->getFunction("entry_exception_object_with_class_name2");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                std::string var_num_value_name("var_num");
                Value* param3 = params[var_num_value_name];
                params2.push_back(param3);

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)"Exception");
                Value* exception_class_name = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(exception_class_name);

                Constant* str_constant2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)"Signal Interrupt");
                Value* exception_msg = ConstantExpr::getIntToPtr(str_constant2, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(exception_msg);

                (void)Builder.CreateCall(entry_exception_object_with_class_name_fun, params2);

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
                Builder.CreateRet(ret_value);

                Builder.SetInsertPoint(else_block);
                current_block = else_block;
                }
                break;

            case OP_MARK_SOURCE_CODE_POSITION: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];

                StructType* vm_info_struct_type = get_vm_info_struct_type();

                Value* sname_field = Builder.CreateStructGEP(vm_info_struct_type, vminfo_value, 3);
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)sname);
                Value* sname_value = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                Builder.CreateStore(sname_value, sname_field, "sname_store");

                Value* sline_field = Builder.CreateStructGEP(vm_info_struct_type, vminfo_value, 4);
                Value* sline_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)sline);
                Builder.CreateStore(sline_value, sline_field, "sline_store");
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

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                store_llvm_value_to_lvar_with_offset(llvm_stack, index, llvm_value);
                }
                break;

            case OP_LOAD: {
                int index = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value = get_llvm_value_from_lvar_with_offset(llvm_stack, index);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCINT: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
                llvm_value.vm_stack = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCNULL: {
                int value = 0;

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
                llvm_value.vm_stack = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_IADD: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAdd(lvalue->value, rvalue->value, "addtmp", true, false);
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ISUB: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", true, false);
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_IEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "IEQ");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INOTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "INOTEQ");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_IGT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "IGT");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ILE: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "ILE");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;
            
            case OP_IGTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "IGE");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ILEEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "ILE");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ANDAND: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "ANDAND");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_OROR: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ANDAND");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOGICAL_DENIAL: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE rvalue;
                rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
                rvalue.vm_stack = FALSE;

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue.value, "LOGICAL_DIANEAL");
                llvm_value.vm_stack = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
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
                    fprintf(stderr, "class not found(2) (%s)\n", class_name);
                    return FALSE;
                }

                if(method_index < 0 || method_index >= klass->mNumMethods) {
                    fprintf(stderr, "OP_INVOKE_METHOD: Method not found");
                    return FALSE;
                }

                sCLMethod* method = klass->mMethods + method_index;

                if(!call_invoke_method(klass, method, params, &current_block, function, try_catch_label_name, &llvm_stack_ptr, llvm_stack))
                {
                    return FALSE;
                }
                }
                break;

            case OP_NEW: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int flg_array = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    fprintf(stderr, "class not found(3)(%s)\n", class_name);
                    return FALSE;
                }

                if(flg_array) {
                    LVALUE* array_num_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                    Function* function = TheModule->getFunction("create_array_object");

                    std::vector<Value*> params2;
                    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                    params2.push_back(klass_value);
                    params2.push_back(array_num_value->value);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.vm_stack = TRUE;

                    dec_stack_ptr(&llvm_stack_ptr, 1);
                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                else {
                    Function* function = TheModule->getFunction("create_object");

                    std::vector<Value*> params2;
                    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                    params2.push_back(klass_value);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.vm_stack = TRUE;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                }
                break;

            case OP_LOAD_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* get_field_fun = TheModule->getFunction("get_field_from_object");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                std::string var_num_value_name("var_num");
                Value* param3 = params[var_num_value_name];
                params2.push_back(param3);

                std::string info_value_name("info");
                Value* param4 = params[info_value_name];
                params2.push_back(param4);

                Value* param5; // CLObject
                param5 = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt32Ty(TheContext));
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(get_field_fun, params2);


                StructType* get_field_from_object_result_struct_type = StructType::create(TheContext, "get_field_from_object_result_struct_type");
                std::vector<Type*> fields;
                Type* field_type1 = IntegerType::get(TheContext, 64);
                fields.push_back(field_type1);
                Type* field_type2 = IntegerType::get(TheContext, 32);
                fields.push_back(field_type2);

                if(get_field_from_object_result_struct_type->isOpaque()) {
                    get_field_from_object_result_struct_type->setBody(fields, false);
                }

                Value* result1 = Builder.CreateStructGEP(get_field_from_object_result_struct_type, result, 0);
                Value* result2 = Builder.CreateStructGEP(get_field_from_object_result_struct_type, result, 1);
                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = TRUE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INT_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_int_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);
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

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.vm_stack = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            default:
                printf("inst %d\n", inst);
                exit(1);
        }

#ifdef MDEBUG
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
    show_stack_for_llvm_stack(llvm_stack, llvm_stack_ptr, var_num);
    //call_show_stack(params);
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


} // extern "C"
