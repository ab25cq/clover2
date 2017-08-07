#include "jit_common.hpp"

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
std::unique_ptr<Module> TheModule;
std::unique_ptr<legacy::FunctionPassManager> TheFPM;
std::unique_ptr<CloverJIT> TheJIT;
std::map<std::string, BasicBlock*> TheLabels;

std::map<std::string, std::unique_ptr<FunctionAST>> LLVMFunctions;

/////////////////////////////////////////////////////////////
// JIT main
//////////////////////////////////////////////////////////////
#define MAX_COND_JUMP 128

extern "C"
{

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

/////////////////////////////////////////////////////////////
// LLVM debug functions
/////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////
// LLVM operation functions
//////////////////////////////////////////////////////////////
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
        (*llvm_stack_ptr)->lvar_address_index = -1;
        (*llvm_stack_ptr)->lvar_stored = FALSE;

        (*llvm_stack_ptr)--;
    }

    (*llvm_stack_ptr)->value = 0;
    (*llvm_stack_ptr)->vm_stack = FALSE;
    (*llvm_stack_ptr)->lvar_address_index = -1;
    (*llvm_stack_ptr)->lvar_stored = FALSE;
}

static void push_value_to_stack_ptr(LVALUE** llvm_stack_ptr, LVALUE* value)
{
    (**llvm_stack_ptr) = *value;
    (*llvm_stack_ptr)++;
}

static void insert_value_to_stack_ptr_with_offset(LVALUE** llvm_stack_ptr, LVALUE* value, int offset)
{
    (*(*llvm_stack_ptr+offset)) = *value;
}

static void store_llvm_value_to_lvar_with_offset(LVALUE* llvm_stack, int index, LVALUE* llvm_value)
{
    /// 0 clear align 8 byte ///
    Value* llvm_value2 = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateStore(llvm_value2, llvm_stack[index].value);

    /// store ///
    Builder.CreateStore(llvm_value->value, llvm_stack[index].value);
    llvm_stack[index].vm_stack = llvm_value->vm_stack;
    llvm_stack[index].lvar_address_index = llvm_value->lvar_address_index;
    llvm_stack[index].lvar_stored = TRUE;
}

static void get_llvm_value_from_lvar_with_offset(LVALUE* result, LVALUE* llvm_stack, int index)
{
    LVALUE* llvm_value = llvm_stack + index;
    result->value = Builder.CreateLoad(llvm_value->value, "lvar");
    result->vm_stack = llvm_value->vm_stack;
    result->lvar_address_index = llvm_value->lvar_address_index;
    result->lvar_stored = llvm_value->lvar_stored;
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
    result.lvar_address_index = -1;
    result.lvar_stored = FALSE;

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
    result.lvar_address_index = -1;
    result.lvar_stored = FALSE;

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

char* get_try_catch_label_name(sVMInfo* info)
{
    return info->try_catch_label_name;
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
    result.lvar_address_index = -1;
    result.lvar_stored = TRUE;

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

void try_function(sVMInfo* info, char* try_catch_label, int try_offset, sByteCode* code)
{
    info->try_catch_label_name = try_catch_label;
    info->try_offset = try_offset;
    info->try_code = code;
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
    Type* field_type6 = IntegerType::get(TheContext, 32);                       // try_offset
    fields.push_back(field_type6);
    Type* field_type7 = PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0); // try_pc
    fields.push_back(field_type7);
    Type* field_type8 = PointerType::get(IntegerType::get(TheContext, 64), 0);      // try_code
    fields.push_back(field_type7);
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

struct sCLVALUEAndBoolResult {
    CLVALUE result1;
    BOOL result2;
};

struct sCLVALUEAndBoolResult get_field_from_object(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject obj, int field_index)
{
    struct sCLVALUEAndBoolResult result;

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
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(1)");
        result.result1.mLongValue = 0;
        result.result2 = 0;
        return result;
    }

    CLVALUE value = object_pointer->mFields[field_index];

    result.result1 = value;
    result.result2 = 1;

    return result;
}

static void call_entry_exception_object_with_class_name2(std::map<std::string, Value *> params, char* class_name, char* message)
{
    Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object_with_class_name2");

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

    Value* param5 = get_value_from_char_array(class_name);
    params2.push_back(param5);

    Value* param6 = get_value_from_char_array(message);
    params2.push_back(param6);

    (void)Builder.CreateCall(entry_exception_object_fun, params2);
}

void if_value_is_zero_entry_exception_object(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block, char* class_name, char* message)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* comp = Builder.CreateICmpEQ(value, ConstantInt::get(TheContext, llvm::APInt(32, 0, true)), "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    call_entry_exception_object_with_class_name2(params, class_name, message);

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

BOOL call_invoke_method(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code)
{
    return invoke_method(klass, method, stack, var_num, stack_ptr, info);
}

BOOL call_invoke_virtual_method(int num_real_params, int offset, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant, CLObject object)
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

static void vm_lvar_to_llvm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);
        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }
}

static void finish_method_call(Value* result, sCLClass* klass, sCLMethod* method, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char** try_catch_label_name, sByteCode* code, int real_param_num, int var_num, LVALUE* llvm_stack, LVALUE* llvm_stack_ptr)
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

    if(*try_catch_label_name == nullptr) {
/*
        Function* catch_function = TheModule->getFunction("catch_function");

        std::vector<Value*> params2;

        std::string info_value_name("info");
        Value* info_value = params[info_value_name];
        params2.push_back(info_value);

        Value* try_code = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
        params2.push_back(try_code);

        Builder.CreateCall(catch_function, params2);
*/

        Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
        Builder.CreateRet(ret_value);
    }
    else {
        std::string try_catch_label_name_string(*try_catch_label_name);
        BasicBlock* label = TheLabels[try_catch_label_name_string];
        if(label == nullptr) {
            label = BasicBlock::Create(TheContext, *try_catch_label_name, function);
            TheLabels[try_catch_label_name_string] = label;
        }

        if(label == nullptr) {
/*
            Function* catch_function = TheModule->getFunction("catch_function");

            std::vector<Value*> params2;

            std::string info_value_name("info");
            Value* info_value = params[info_value_name];
            params2.push_back(info_value);

            Value* try_code = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
            params2.push_back(try_code);

            Builder.CreateCall(catch_function, params2);
*/

            Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
            Builder.CreateRet(ret_value);
        }
        else {
            Function* try_fun = TheModule->getFunction("try_function");

            std::vector<Value*> params2;

            std::string info_value_name("info");
            Value* vminfo_value = params[info_value_name];
            params2.push_back(vminfo_value);

            Value* try_catch_label_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)NULL);
            params2.push_back(try_catch_label_value);

            Value* try_offset_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
            params2.push_back(try_offset_value);

            (void)Builder.CreateCall(try_fun, params2);

            Builder.CreateBr(label);
        }
    }

    Builder.SetInsertPoint(entry_ifend2);
    
    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend); 
    *current_block = entry_ifend;
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

struct sCLVALUEAndBoolResult load_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult result;

    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(7)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(3)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    sCLField* field = klass->mClassFields + field_index;

    result.result1 = field->mValue;
    result.result2 = TRUE;

    return result;
}

BOOL store_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant, CLVALUE value)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

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

static void lvar_of_vm_to_lvar_of_llvm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);
        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }
}

static void lvar_of_llvm_to_lvar_of_vm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value;
        get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, i);

        if(llvm_value.value != 0) {
            store_value_to_lvar_with_offset(params, current_block, i, llvm_value.value);
        }
    }
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

struct sCLVALUEAndBoolResult load_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, int element_num, int size)
{
    struct sCLVALUEAndBoolResult result;

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(7)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "element index is invalid(2)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    result.result1 = object_pointer->mFields[element_num];
    result.result2 = TRUE;

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

struct sCLVALUEAndBoolResult run_create_array(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, char* class_name, int num_elements)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(11)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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

    result.result1.mObjectValue = array_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result.result1.mObjectValue = array_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_equalable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result.result1.mObjectValue = array_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_sortable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result.result1.mObjectValue = array_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result.result1.mObjectValue = list_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_sortable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result.result1.mObjectValue = list_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_equalable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result.result1.mObjectValue = list_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_tuple(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements)
{
    struct sCLVALUEAndBoolResult result;

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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result.result1.mObjectValue = tuple_object;
    result.result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult run_create_hash(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name, char* class_name2)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(14)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(15)");
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
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
        result.result1.mLongValue = 0;
        result.result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements*2;

    result.result1.mObjectValue = hash_object;
    result.result2 = TRUE;

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

struct sPointerAndBoolResult {
    char* result1;
    BOOL result2;
};

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

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

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

void trunc_vm_stack_value(LVALUE* value, int inst) 
{
    if(value->vm_stack) {
        switch(inst) {
            case OP_BADD:
            case OP_BSUB:
            case OP_BMULT:
            case OP_BDIV:
            case OP_BMOD: 
            case OP_BLSHIFT:
            case OP_BRSHIFT:
            case OP_BAND: 
            case OP_BXOR: 
            case OP_BOR: 
            case OP_BCOMPLEMENT:
            case OP_BEQ:
            case OP_BNOTEQ:
            case OP_BGT:
            case OP_BLE:
            case OP_BGTEQ:
            case OP_BLEEQ:
            case OP_UBADD: 
            case OP_UBSUB:
            case OP_UBMULT:
            case OP_UBDIV:
            case OP_UBMOD:
            case OP_UBLSHIFT:
            case OP_UBRSHIFT: 
            case OP_UBAND:
            case OP_UBXOR:
            case OP_UBOR:
            case OP_UBCOMPLEMENT:
            case OP_UBEQ:
            case OP_UBNOTEQ:
            case OP_UBGT:
            case OP_UBLE: 
            case OP_UBGTEQ: 
            case OP_UBLEEQ:
                value->value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt8Ty(TheContext));
                break;

            case OP_SADD:
            case OP_SSUB:
            case OP_SMULT:
            case OP_SDIV:
            case OP_SMOD:
            case OP_SLSHIFT:
            case OP_SRSHIFT:
            case OP_SAND:
            case OP_SXOR:
            case OP_SOR:
            case OP_SCOMPLEMENT:
            case OP_SEQ:
            case OP_SNOTEQ:
            case OP_SGT:
            case OP_SLE:
            case OP_SGTEQ:
            case OP_SLEEQ:
            case OP_USADD:
            case OP_USSUB:
            case OP_USMULT:
            case OP_USDIV:
            case OP_USMOD:
            case OP_USLSHIFT:
            case OP_USRSHIFT:
            case OP_USAND:
            case OP_USXOR:
            case OP_USOR:
            case OP_USCOMPLEMENT:
            case OP_USEQ:
            case OP_USNOTEQ:
            case OP_USGT:
            case OP_USLE:
            case OP_USGTEQ:
            case OP_USLEEQ:
                value->value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt16Ty(TheContext));
                break;

            case OP_IADD: 
            case OP_ISUB:
            case OP_IMULT:
            case OP_IDIV:
            case OP_IMOD:
            case OP_ILSHIFT: 
            case OP_IRSHIFT:
            case OP_IAND:
            case OP_IXOR: 
            case OP_IOR:
            case OP_ICOMPLEMENT:
            case OP_IEQ:
            case OP_INOTEQ: 
            case OP_IGT: 
            case OP_ILE: 
            case OP_ILEEQ: 
            case OP_IGTEQ: 
            case OP_UIADD:
            case OP_UISUB:
            case OP_UIMULT:
            case OP_UIDIV:
            case OP_UIMOD:
            case OP_UILSHIFT:
            case OP_UIRSHIFT:
            case OP_UIAND:
            case OP_UIXOR:
            case OP_UIOR:
            case OP_UICOMPLEMENT:
            case OP_UIEQ:
            case OP_UINOTEQ:
            case OP_UILE:
            case OP_UIGT:
            case OP_UIGTEQ:
            case OP_UILEEQ: 
            case OP_CADD:
            case OP_CSUB:
            case OP_CEQ:
            case OP_CNOTEQ:
            case OP_CGT:
            case OP_CLE:
            case OP_CGTEQ:
            case OP_CLEEQ:
            case OP_OBJ_IDENTIFY:
            case OP_ANDAND: 
            case OP_OROR:
            case OP_LOGICAL_DENIAL:
                value->value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt32Ty(TheContext));
                break;

            case OP_LADD:
            case OP_LSUB:
            case OP_LMULT:
            case OP_LMOD: 
            case OP_LDIV:
            case OP_LLSHIFT: 
            case OP_LRSHIFT:
            case OP_LAND: 
            case OP_LXOR: 
            case OP_LOR: 
            case OP_LCOMPLEMENT:
            case OP_LEQ: 
            case OP_LNOTEQ: 
            case OP_LGT:
            case OP_LLE:
            case OP_LGTEQ:
            case OP_LLEEQ:
            case OP_ULADD: 
            case OP_ULMOD:
            case OP_ULLSHIFT:
            case OP_ULRSHIFT:
            case OP_ULAND:
            case OP_ULXOR:
            case OP_ULOR:
            case OP_ULCOMPLEMENT:
            case OP_ULEQ: 
            case OP_ULNOTEQ: 
            case OP_ULGT: 
            case OP_ULLE: 
            case OP_ULGTEQ: 
            case OP_ULLEEQ:
                value->value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt64Ty(TheContext));
                break;

            case OP_FADD:
            case OP_FSUB:
            case OP_FMULT:
            case OP_FDIV:
            case OP_FEQ:
            case OP_FNOTEQ:
            case OP_FGT:
            case OP_FLE:
            case OP_FGTEQ:
            case OP_FLEEQ:
                value->value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getFloatTy(TheContext));
                break;

            case OP_DADD:
            case OP_DSUB:
            case OP_DMULT:
            case OP_DDIV:
            case OP_DEQ:
            case OP_DNOTEQ:
            case OP_DGT:
            case OP_DLE:
            case OP_DGTEQ:
            case OP_DLEEQ:
                value->value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getDoubleTy(TheContext));
                break;

            case OP_PADD: 
            case OP_PEQ: 
            case OP_PNOTEQ: 
            case OP_PGT: 
            case OP_PLE:
            case OP_PGTEQ: 
            case OP_PLEEQ: 
                value->value = Builder.CreateCast(Instruction::IntToPtr, value->value, PointerType::get(IntegerType::get(TheContext, 64), 0));
                break;
        }

        value->vm_stack = FALSE;
    }
}

Value* llvm_make_str_value(char* str)
{
    Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
    Value* value = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));

    return value;
}

void trunc_vm_stack_value2(LVALUE* llvm_value, int size)
{
    switch(size) {
        case 1:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext));

            break;

        case 2:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext));
            break;

        case 4:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
            break;

        case 8:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt64Ty(TheContext));
            break;

        case 16:
            //llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            break;

        case 32:
            //llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
            break;

        case 64:
            llvm_value->value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 64), 0));
            break;
    }

    //llvm_value->vm_stack = FALSE;
}

void cast_llvm_value_from_inst(LVALUE* llvm_value, int inst) 
{
    switch(inst) {
        case OP_BYTE_TO_CDOUBLE_CAST:
        case OP_SHORT_TO_CDOUBLE_CAST:
        case OP_INT_TO_CDOUBLE_CAST:
        case OP_LONG_TO_CDOUBLE_CAST:
        case OP_BOOL_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            break;

        case OP_UBYTE_TO_CDOUBLE_CAST:
        case OP_USHORT_TO_CDOUBLE_CAST:
        case OP_UINT_TO_CDOUBLE_CAST:
        case OP_CHAR_TO_CDOUBLE_CAST:
        case OP_ULONG_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            break;

        case OP_FLOAT_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            break;

        case OP_DOUBLE_TO_CDOUBLE_CAST:
            break;

        case OP_BYTE_TO_CFLOAT_CAST:
        case OP_SHORT_TO_CFLOAT_CAST:
        case OP_INT_TO_CFLOAT_CAST:
        case OP_LONG_TO_CFLOAT_CAST:
        case OP_BOOL_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            break;

        case OP_UBYTE_TO_CFLOAT_CAST:
        case OP_USHORT_TO_CFLOAT_CAST:
        case OP_UINT_TO_CFLOAT_CAST:
        case OP_CHAR_TO_CFLOAT_CAST:
        case OP_ULONG_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            break;

        case OP_BYTE_TO_CULONG_CAST:
        case OP_UBYTE_TO_CULONG_CAST:
        case OP_SHORT_TO_CULONG_CAST:
        case OP_USHORT_TO_CULONG_CAST:
        case OP_INT_TO_CULONG_CAST:
        case OP_UINT_TO_CULONG_CAST:
        case OP_LONG_TO_CULONG_CAST:
        case OP_ULONG_TO_CULONG_CAST:
        case OP_CHAR_TO_CULONG_CAST:
        case OP_POINTER_TO_CULONG_CAST:
        case OP_BOOL_TO_CULONG_CAST:
            break;

        case OP_FLOAT_TO_CULONG_CAST:
        case OP_DOUBLE_TO_CULONG_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt64Ty(TheContext));
            break;

        case OP_BYTE_TO_CLONG_CAST:
        case OP_UBYTE_TO_CLONG_CAST:
        case OP_SHORT_TO_CLONG_CAST:
        case OP_USHORT_TO_CLONG_CAST:
        case OP_INT_TO_CLONG_CAST:
        case OP_UINT_TO_CLONG_CAST:
        case OP_LONG_TO_CLONG_CAST:
        case OP_ULONG_TO_CLONG_CAST:
        case OP_CHAR_TO_CLONG_CAST:
        case OP_POINTER_TO_CLONG_CAST:
        case OP_BOOL_TO_CLONG_CAST: 
            break;

        case OP_FLOAT_TO_CLONG_CAST:
        case OP_DOUBLE_TO_CLONG_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt64Ty(TheContext));
            break;

        case OP_FLOAT_TO_CUSHORT_CAST:
        case OP_DOUBLE_TO_CUSHORT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt16Ty(TheContext));
            break;

        case OP_FLOAT_TO_CSHORT_CAST:
        case OP_DOUBLE_TO_CSHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt16Ty(TheContext));
            break;

        case OP_FLOAT_TO_CUBYTE_CAST:
        case OP_DOUBLE_TO_CUBYTE_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt8Ty(TheContext));
            break;

        case OP_FLOAT_TO_CBYTE_CAST:
        case OP_DOUBLE_TO_CBYTE_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt8Ty(TheContext));
            break;

        case OP_FLOAT_TO_UINTEGER_CAST:
        case OP_DOUBLE_TO_UINTEGER_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt32Ty(TheContext));
            break;

        case OP_FLOAT_TO_INTEGER_CAST:
        case OP_DOUBLE_TO_INTEGER_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt32Ty(TheContext));
            break;






        case OP_FLOAT_TO_CFLOAT_CAST:
            break;

        case OP_DOUBLE_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            break;


        case OP_CBYTE_TO_SHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_INT_CAST:
        case OP_CSHORT_TO_INT_CAST : 
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_LONG_CAST:
        case OP_CSHORT_TO_LONG_CAST : 
        case OP_INTEGER_TO_LONG_CAST:
        case OP_CBOOL_TO_LONG_CAST:
        case OP_CFLOAT_TO_LONG_CAST : 
        case OP_CDOUBLE_TO_LONG_CAST : 
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_USHORT_CAST:
        case OP_CUBYTE_TO_SHORT_CAST:
        case OP_CUBYTE_TO_USHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_UINT_CAST:
        case OP_CBYTE_TO_CHAR_CAST:
        case OP_CUBYTE_TO_INT_CAST:
        case OP_CUBYTE_TO_UINT_CAST:
        case OP_CUBYTE_TO_CHAR_CAST:
        case OP_CSHORT_TO_UINT_CAST :
        case OP_CSHORT_TO_CHAR_CAST:
        case OP_CUSHORT_TO_INT_CAST : 
        case OP_CUSHORT_TO_UINT_CAST :
        case OP_CUSHORT_TO_CHAR_CAST:
        case OP_CFLOAT_TO_CHAR_CAST:
        case OP_CDOUBLE_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_ULONG_CAST:
        case OP_CUBYTE_TO_LONG_CAST:
        case OP_CUBYTE_TO_ULONG_CAST:
        case OP_CSHORT_TO_ULONG_CAST :
        case OP_CUSHORT_TO_LONG_CAST : 
        case OP_CUSHORT_TO_ULONG_CAST :
        case OP_INTEGER_TO_ULONG_CAST:
        case OP_UINTEGER_TO_LONG_CAST : 
        case OP_UINTEGER_TO_ULONG_CAST:
        case OP_CBOOL_TO_ULONG_CAST:
        case OP_CCHAR_TO_LONG_CAST : 
        case OP_CFLOAT_TO_ULONG_CAST :
        case OP_CDOUBLE_TO_ULONG_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            break;


        case OP_CBYTE_TO_FLOAT_CAST:
        case OP_CSHORT_TO_FLOAT_CAST:
        case OP_INTEGER_TO_FLOAT_CAST:
        case OP_CLONG_TO_FLOAT_CAST: 
        case OP_CBOOL_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            break;



        case OP_CBYTE_TO_DOUBLE_CAST:
        case OP_CSHORT_TO_DOUBLE_CAST:
        case OP_INTEGER_TO_DOUBLE_CAST:
        case OP_CLONG_TO_DOUBLE_CAST: 
        case OP_CBOOL_TO_DOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
            break;




        case OP_CUBYTE_TO_FLOAT_CAST:
        case OP_CUSHORT_TO_FLOAT_CAST:
        case OP_UINTEGER_TO_FLOAT_CAST:
        case OP_CULONG_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            break;





        case OP_CUBYTE_TO_DOUBLE_CAST: 
        case OP_CUSHORT_TO_DOUBLE_CAST:
        case OP_UINTEGER_TO_DOUBLE_CAST:
        case OP_CULONG_TO_DOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
            break;





            
        case OP_CSHORT_TO_BYTE_CAST:
        case OP_CSHORT_TO_UBYTE_CAST :
        case OP_CUSHORT_TO_BYTE_CAST:
        case OP_CUSHORT_TO_UBYTE_CAST :
        case OP_INTEGER_TO_BYTE_CAST:
        case OP_INTEGER_TO_UBYTE_CAST:
        case OP_UINTEGER_TO_BYTE_CAST:
        case OP_UINTEGER_TO_UBYTE_CAST:
        case OP_CLONG_TO_BYTE_CAST:
        case OP_CLONG_TO_UBYTE_CAST:
        case OP_CULONG_TO_UBYTE_CAST:
        case OP_CULONG_TO_BYTE_CAST:
        case OP_CBOOL_TO_BYTE_CAST:
        case OP_CBOOL_TO_UBYTE_CAST:
        case OP_CCHAR_TO_BYTE_CAST:
        case OP_CCHAR_TO_UBYTE_CAST :
        case OP_CFLOAT_TO_BYTE_CAST:
        case OP_CFLOAT_TO_UBYTE_CAST :
        case OP_CDOUBLE_TO_BYTE_CAST:
        case OP_CDOUBLE_TO_UBYTE_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext), "value2");
            break;


        case OP_INTEGER_TO_SHORT_CAST:
        case OP_INTEGER_TO_USHORT_CAST:
        case OP_UINTEGER_TO_SHORT_CAST:
        case OP_UINTEGER_TO_USHORT_CAST:
        case OP_CLONG_TO_SHORT_CAST:
        case OP_CLONG_TO_USHORT_CAST:
        case OP_CULONG_TO_USHORT_CAST:
        case OP_CULONG_TO_SHORT_CAST:
        case OP_CBOOL_TO_SHORT_CAST:
        case OP_CBOOL_TO_USHORT_CAST:
        case OP_CCHAR_TO_SHORT_CAST:
        case OP_CCHAR_TO_USHORT_CAST :
        case OP_CFLOAT_TO_SHORT_CAST:
        case OP_CFLOAT_TO_USHORT_CAST :
        case OP_CDOUBLE_TO_SHORT_CAST:
        case OP_CDOUBLE_TO_USHORT_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            break;

        case OP_CLONG_TO_INT_CAST:
        case OP_CLONG_TO_UINT_CAST:
        case OP_CULONG_TO_INT_CAST:
        case OP_CULONG_TO_UINT_CAST:
        case OP_CULONG_TO_CHAR_CAST:
        case OP_CCHAR_TO_INT_CAST : 
        case OP_CLONG_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            break;


        case OP_CPOINTER_TO_BYTE_CAST:
        case OP_CPOINTER_TO_UBYTE_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt8Ty(TheContext), "value2");
            break;

        case OP_CPOINTER_TO_SHORT_CAST:
        case OP_CPOINTER_TO_USHORT_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            break;

        case OP_CPOINTER_TO_INT_CAST : 
        case OP_CPOINTER_TO_UINT_CAST :
        case OP_CPOINTER_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            break;

        case OP_CPOINTER_TO_LONG_CAST : 
        case OP_CPOINTER_TO_ULONG_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            break;




        case OP_CFLOAT_TO_DOUBLE_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext));
            break;

        case OP_CDOUBLE_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext));
            break;



        case OP_CBYTE_TO_BYTE_CAST:
        case OP_CBYTE_TO_UBYTE_CAST:
        case OP_CUBYTE_TO_BYTE_CAST:
        case OP_CUBYTE_TO_UBYTE_CAST:

        case OP_CSHORT_TO_SHORT_CAST:
        case OP_CSHORT_TO_USHORT_CAST :
        case OP_CUSHORT_TO_SHORT_CAST:
        case OP_CUSHORT_TO_USHORT_CAST :

        case OP_INTEGER_TO_INT_CAST:
        case OP_INTEGER_TO_UINT_CAST:
        case OP_UINTEGER_TO_INT_CAST:
        case OP_UINTEGER_TO_UINT_CAST:

        case OP_CLONG_TO_LONG_CAST:
        case OP_CLONG_TO_ULONG_CAST:
        case OP_CULONG_TO_LONG_CAST:
        case OP_CULONG_TO_ULONG_CAST:

        case OP_INTEGER_TO_CHAR_CAST:
        case OP_UINTEGER_TO_CHAR_CAST:

        case OP_CBOOL_TO_INT_CAST : 
        case OP_CBOOL_TO_UINT_CAST :
        case OP_CBOOL_TO_CHAR_CAST: 

        case OP_CCHAR_TO_CHAR_CAST:
        case OP_CCHAR_TO_UINT_CAST :

        case OP_CFLOAT_TO_INT_CAST : 
        case OP_CFLOAT_TO_UINT_CAST :

        case OP_CFLOAT_TO_FLOAT_CAST:
        case OP_CDOUBLE_TO_INT_CAST : 
        case OP_CDOUBLE_TO_UINT_CAST :
            break;

    }
}


struct sCLVALUEAndBoolResult run_array_to_carray_cast(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, char* class_name)
{
    struct sCLVALUEAndBoolResult result;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(10)");
        result.result1.mIntValue = 0;
        result.result2 = FALSE;
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

    result.result1.mObjectValue = new_array;
    result.result2 = TRUE;

    return result;
}

void store_value_to_vm_lvar(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset, Value* value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*offset, true));
    Value* lvar_offset_value = Builder.CreateAdd(lvalue, rvalue, "lvar_offset_value", true, true);
    /// 0 clear align 8 byte ///
    Value* zero = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateAlignedStore(zero, lvar_offset_value, 8);

    /// go ///
    Builder.CreateStore(value, lvar_offset_value);
}

static void llvm_lvar_to_vm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value;
        get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, i);

        if(llvm_value.lvar_stored) {
            store_value_to_vm_lvar(params, current_block, i, llvm_value.value);
        }
    }
}


//////////////////////////////////////////////////////////////
// LLVM core
//////////////////////////////////////////////////////////////
#define ANDAND_OROR_MAX 128

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
    memset(llvm_stack, 0, sizeof(LVALUE)*CLOVER_STACK_SIZE);

    LVALUE* llvm_stack_ptr = llvm_stack + var_num;

    /// alloc local variables ///
    int i;
    for(i=0; i<var_num; i++) {
        llvm_stack[i].value = create_entry_block_alloca(function, i);

        llvm_stack[i].vm_stack = TRUE;
        llvm_stack[i].lvar_address_index = -1;
        llvm_stack[i].lvar_stored = FALSE;
    }

    /// parametor from VM stack ptr ///
    int real_param_num = method->mNumParams + ((method->mFlags & METHOD_FLAGS_CLASS_METHOD) ? 0:1);
    for(i=0; i<real_param_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);

        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }

    /// clear local variable ///
    for(i=real_param_num; i<var_num; i++) {
        LVALUE llvm_value;
        llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
        llvm_stack[i].vm_stack = TRUE;
        llvm_stack[i].lvar_address_index = -1;
        llvm_stack[i].lvar_stored = FALSE;

        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }

    Value* value_for_andand_oror[ANDAND_OROR_MAX];
    memset(value_for_andand_oror, 0, sizeof(Value*)*ANDAND_OROR_MAX);
    int num_value_for_andand_oror = 0;

    while(pc - code->mCodes < code->mLen) {
        int k;
        for(k=0; k<num_cond_jump; k++) {
            if(pc == cond_jump_labels[k]) {
                //Builder.CreateBr(entry_condends[k]);
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
                //Builder.CreateBr(entry_condnotends[k]);
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
//show_inst_in_jit(inst);
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

//call_show_str_in_jit(llvm_make_str_value("OP_COND_JUMP"));
//call_show_value_in_jit(conditional_value->value);

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

                /// 0 clear align 8 byte ///
                Value* llvm_value2 = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
                Builder.CreateStore(llvm_value2, stack_value);

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
                int try_offset = *(int*)pc;
                pc += sizeof(int);

                int catch_label_name_offset = *(int*)pc;
                pc += sizeof(int);

                try_catch_label_name = CONS_str(constant, catch_label_name_offset);

                Function* try_fun = TheModule->getFunction("try_function");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Value* try_catch_label_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)try_catch_label_name);
                params2.push_back(try_catch_label_value);

                Value* try_offset_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)try_offset);
                params2.push_back(try_offset_value);

                Value* try_code = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(try_code);

                (void)Builder.CreateCall(try_fun, params2);
                }
                break;

            case OP_TRY_END: {
                try_catch_label_name = NULL;

                Function* try_fun = TheModule->getFunction("try_function");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Value* try_catch_label_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)NULL);
                params2.push_back(try_catch_label_value);

                Value* try_offset_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
                params2.push_back(try_offset_value);

                Value* try_code = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)NULL);
                params2.push_back(try_code);

                (void)Builder.CreateCall(try_fun, params2);

                }
                break;

            case OP_CATCH_POP:
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

                call_entry_exception_object_with_class_name2(params, "Exception", "Signal Interrupt");

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

            case OP_VALUE_FOR_ANDAND_OROR: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                value_for_andand_oror[num_value_for_andand_oror] = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "VALUE_FOR_ANDAND_OROR");
                Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
                Builder.CreateAlignedStore(zero, value_for_andand_oror[num_value_for_andand_oror], 8);
                Builder.CreateAlignedStore(llvm_value->value, value_for_andand_oror[num_value_for_andand_oror], 8);

                trunc_vm_stack_value2(llvm_value, 4);

//call_show_str_in_jit(llvm_make_str_value("OP_VALUE_FOR_ANDAND_OROR value"));
//call_show_value_in_jit(llvm_value->value);

                num_value_for_andand_oror++;

                MASSERT(num_value_for_andand_oror >= ANDAND_OROR_MAX);
                }
                break;

            case OP_STORE_VALUE_FOR_ANDAND_OROR: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                num_value_for_andand_oror--;

                Builder.CreateAlignedStore(llvm_value->value, value_for_andand_oror[num_value_for_andand_oror], 8);

//call_show_str_in_jit(llvm_make_str_value("OP_STORE_VALUE_FOR_ANDAND_OROR value"));
//call_show_value_in_jit(llvm_value->value);

                MASSERT(num_value_for_andand_oror >= 0);
                }
                break;

            case OP_LOAD_VALUE_FOR_ANDAND_OROR: {
                dec_stack_ptr(&llvm_stack_ptr, 1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateLoad(value_for_andand_oror[num_value_for_andand_oror], "value_for_andand_oror");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

//call_show_str_in_jit(llvm_make_str_value("OP_LOAD_VALUE_FOR_ANDAND_OROR value"));
//call_show_value_in_jit(llvm_value.value);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
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

                int size = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, index);

                trunc_vm_stack_value2(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_ADDRESS: {
                int index = *(int*)pc;
                pc += sizeof(int);

                std::string lvar_arg_name("lvar");
                Value* lvar_value = params[lvar_arg_name];

                LVALUE llvm_value;
                Value* add_value = ConstantInt::get(TheContext, llvm::APInt(64, index * 8, true)); 
                llvm_value.value = Builder.CreateAdd(lvar_value, add_value, "addtmp", false, true);
                llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = index;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    LVALUE llvm_value;
                    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(8, value, true)); 
                    llvm_value.vm_stack = FALSE;
                    llvm_value.lvar_address_index = -1;
                    llvm_value.lvar_stored = FALSE;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCUBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    LVALUE llvm_value;
                    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(8, value, false)); 
                    llvm_value.vm_stack = FALSE;
                    llvm_value.lvar_address_index = -1;
                    llvm_value.lvar_stored = FALSE;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    LVALUE llvm_value;
                    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(16, value, true)); 
                    llvm_value.vm_stack = FALSE;
                    llvm_value.lvar_address_index = -1;
                    llvm_value.lvar_stored = FALSE;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCUSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    LVALUE llvm_value;
                    llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(16, value, false)); 
                    llvm_value.vm_stack = FALSE;
                    llvm_value.lvar_address_index = -1;
                    llvm_value.lvar_stored = FALSE;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCINT: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCUINT: {
                unsigned int value = *(unsigned int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, false)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCLONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                long lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, true)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCULONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                long lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, false)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCNULL: {
                int value = 0;

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCPOINTER: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                long lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, false)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LDCFLOAT: {
                float value1 = *(float*)pc;
                pc += sizeof(float);

                LVALUE llvm_value;
                llvm_value.value = ConstantFP::get(TheContext, llvm::APFloat(value1)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
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

                LVALUE llvm_value;
                llvm_value.value = ConstantFP::get(TheContext, llvm::APFloat(lvalue)); 
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BADD:
            case OP_SADD:
            case OP_IADD: 
            case OP_LADD: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAdd(lvalue->value, rvalue->value, "addtmp", true, false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBADD: 
            case OP_USADD:
            case OP_UIADD:
            case OP_ULADD: 
            case OP_CADD:
            case OP_PADD: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value  = Builder.CreateAdd(lvalue->value, rvalue->value, "addtmp", false, true);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BSUB:
            case OP_SSUB:
            case OP_ISUB: 
            case OP_LSUB:
            case OP_PSUB:
            case OP_PPSUB: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", true, false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBSUB: 
            case OP_USSUB:
            case OP_UISUB:
            case OP_ULSUB: 
            case OP_CSUB: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", false, true);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BMULT:
            case OP_SMULT:
            case OP_IMULT: 
            case OP_LMULT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", true, false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBMULT: 
            case OP_USMULT:
            case OP_UIMULT:
            case OP_ULMULT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", false, true);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BDIV:
            case OP_SDIV:
            case OP_IDIV: 
            case OP_LDIV: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                if_value_is_zero_entry_exception_object(rvalue->value, params, function, &current_block, "Exception", "division by zero");

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateSDiv(lvalue->value, rvalue->value, "divtmp", false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBDIV: 
            case OP_USDIV:
            case OP_UIDIV:
            case OP_ULDIV: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                if_value_is_zero_entry_exception_object(rvalue->value, params, function, &current_block, "Exception", "division by zero");

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateUDiv(lvalue->value, rvalue->value, "divtmp", false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BMOD: 
            case OP_SMOD:
            case OP_IMOD:
            case OP_LMOD: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                if_value_is_zero_entry_exception_object(rvalue->value, params, function, &current_block, "Exception", "division by zero");

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateSRem(lvalue->value, rvalue->value, "remtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBMOD:
            case OP_USMOD:
            case OP_UIMOD:
            case OP_ULMOD: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                if_value_is_zero_entry_exception_object(rvalue->value, params, function, &current_block, "Exception", "division by zero");

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateURem(lvalue->value, rvalue->value, "remtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BLSHIFT:
            case OP_SLSHIFT:
            case OP_ILSHIFT: 
            case OP_LLSHIFT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", true, false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBLSHIFT: 
            case OP_USLSHIFT:
            case OP_UILSHIFT:
            case OP_ULLSHIFT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", false, true);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BRSHIFT:
            case OP_SRSHIFT:
            case OP_IRSHIFT:
            case OP_LRSHIFT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAShr(lvalue->value, rvalue->value, "rshifttmp", false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBRSHIFT: 
            case OP_USRSHIFT:
            case OP_UIRSHIFT:
            case OP_ULRSHIFT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateLShr(lvalue->value, rvalue->value, "rshifttmp", false);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BAND: 
            case OP_UBAND:
            case OP_SAND:
            case OP_USAND:
            case OP_IAND:
            case OP_UIAND:
            case OP_LAND: 
            case OP_ULAND: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BXOR: 
            case OP_UBXOR:
            case OP_SXOR:
            case OP_USXOR:
            case OP_IXOR: 
            case OP_UIXOR:
            case OP_LXOR: 
            case OP_ULXOR: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BOR: 
            case OP_UBOR:
            case OP_SOR:
            case OP_USOR:
            case OP_IOR:
            case OP_UIOR:
            case OP_LOR: 
            case OP_ULOR: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BCOMPLEMENT:
            case OP_UBCOMPLEMENT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                trunc_vm_stack_value(lvalue, inst);

                LVALUE rvalue;
                rvalue.value = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);
                rvalue.vm_stack = FALSE;

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_SCOMPLEMENT:
            case OP_USCOMPLEMENT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                trunc_vm_stack_value(lvalue, inst);

                LVALUE rvalue;
                rvalue.value = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0xFFFF);
                rvalue.vm_stack = FALSE;

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ICOMPLEMENT:
            case OP_UICOMPLEMENT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                trunc_vm_stack_value(lvalue, inst);

                LVALUE rvalue;
                rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0xFFFFFFFF);
                rvalue.vm_stack = FALSE;

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LCOMPLEMENT:
            case OP_ULCOMPLEMENT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                trunc_vm_stack_value(lvalue, inst);

                LVALUE rvalue;
                rvalue.value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0xFFFFFFFFFFFFFFFF);
                rvalue.vm_stack = FALSE;

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FADD:
            case OP_DADD: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFAdd(lvalue->value, rvalue->value, "faddtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FSUB: 
            case OP_DSUB: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFSub(lvalue->value, rvalue->value, "fsubtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FMULT:
            case OP_DMULT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFMul(lvalue->value, rvalue->value, "fmulttmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FDIV:
            case OP_DDIV: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                if_value_is_zero_entry_exception_object(rvalue->value, params, function, &current_block, "Exception", "division by zero");

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFDiv(lvalue->value, rvalue->value, "fdivtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BEQ:
            case OP_UBEQ:
            case OP_SEQ:
            case OP_USEQ:
            case OP_IEQ:
            case OP_UIEQ:
            case OP_LEQ: 
            case OP_ULEQ: 
            case OP_PEQ: 
            case OP_OBJ_IDENTIFY:
            case OP_CEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmpx");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BNOTEQ:
            case OP_UBNOTEQ:
            case OP_SNOTEQ:
            case OP_USNOTEQ:
            case OP_INOTEQ: 
            case OP_UINOTEQ:
            case OP_LNOTEQ: 
            case OP_ULNOTEQ: 
            case OP_PNOTEQ: 
            case OP_CNOTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BGT:
            case OP_SGT:
            case OP_IGT: 
            case OP_LGT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBGT:
            case OP_USGT:
            case OP_UIGT:
            case OP_ULGT: 
            case OP_PGT: 
            case OP_CGT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BLE:
            case OP_SLE:
            case OP_ILE: 
            case OP_LLE: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBLE: 
            case OP_USLE:
            case OP_UILE:
            case OP_ULLE: 
            case OP_PLE:
            case OP_CLE: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;
            
            case OP_BGTEQ:
            case OP_SGTEQ:
            case OP_IGTEQ: 
            case OP_LGTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBGTEQ: 
            case OP_USGTEQ:
            case OP_UIGTEQ:
            case OP_ULGTEQ: 
            case OP_PGTEQ: 
            case OP_CGTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BLEEQ:
            case OP_SLEEQ:
            case OP_ILEEQ: 
            case OP_LLEEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBLEEQ:
            case OP_USLEEQ:
            case OP_UILEEQ: 
            case OP_ULLEEQ:
            case OP_PLEEQ: 
            case OP_CLEEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FEQ:
            case OP_DEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFCmpOEQ(lvalue->value, rvalue->value, "eqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FNOTEQ:
            case OP_DNOTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFCmpONE(lvalue->value, rvalue->value, "noteqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FGT:
            case OP_DGT: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFCmpOGT(lvalue->value, rvalue->value, "gttmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLE:
            case OP_DLE: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFCmpOLT(lvalue->value, rvalue->value, "letmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FGTEQ:
            case OP_DGTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFCmpOGE(lvalue->value, rvalue->value, "gteqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLEEQ:
            case OP_DLEEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateFCmpOLE(lvalue->value, rvalue->value, "leeqtmp");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_REGEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* function = TheModule->getFunction("regex_equals");

                std::vector<Value*> params2;
                params2.push_back(lvalue->value);
                params2.push_back(rvalue->value);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_REGNOTEQ: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* function = TheModule->getFunction("regex_equals");

                std::vector<Value*> params2;
                params2.push_back(lvalue->value);
                params2.push_back(rvalue->value);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.value = Builder.CreateICmpEQ(llvm_value.value, ConstantInt::get(TheContext, llvm::APInt(32, 0, true)), "bool_value_reverse");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CLASSNAME: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                if_value_is_zero_entry_exception_object(value->value, params, function, &current_block, "Exception", "Null pointer exception(1)");

                Function* fun = TheModule->getFunction("get_string_object_of_object_name");

                std::vector<Value*> params2;
                params2.push_back(value->value);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_IMPLEMENTS: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    fprintf(stderr, "class not found(1) (%s)", class_name);
                    return FALSE;
                }

                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                if_value_is_zero_entry_exception_object(value->value, params, function, &current_block, "Exception", "Null pointer exception(2)");

                Function* fun = TheModule->getFunction("object_implements_interface");

                std::vector<Value*> params2;

                params2.push_back(value->value);

                Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                params2.push_back(param2);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ANDAND: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "ANDAND");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_OROR: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);
                trunc_vm_stack_value(rvalue, inst);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "OROR");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOGICAL_DENIAL: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                trunc_vm_stack_value(lvalue, inst);

                LVALUE rvalue;
                rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
                rvalue.vm_stack = FALSE;

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue.value, "LOGICAL_DIANEAL");
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

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

                /// llvm stack to VM stack ///
                llvm_lvar_to_vm_lvar(llvm_stack, params, current_block, var_num);

                int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);
                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, real_param_num);

                /// go ///
                Function* fun = TheModule->getFunction("call_invoke_method");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)method);
                params2.push_back(param2);

                std::string stack_value_name("stack");
                Value* param3 = params[stack_value_name];
                params2.push_back(param3);

                std::string var_num_value_name("var_num");
                Value* param4 = params[var_num_value_name];
                params2.push_back(param4);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param5 = params[stack_ptr_address_name];
                params2.push_back(param5);

                std::string info_value_name("info");
                Value* param6 = params[info_value_name];
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, klass, method, params, &current_block, function, &try_catch_label_name, code, real_param_num, var_num, llvm_stack, llvm_stack_ptr);
                

                /// the pointer of lvar syncs to llvm stack ///
                for(i=0; i<real_param_num; i++) {
                    LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -i-1);
                    if(llvm_value->lvar_address_index != -1) {
                        LVALUE llvm_value_of_vm_stack = get_stack_value_from_index_with_aligned(params, current_block, llvm_value->lvar_address_index, 8);
                        store_llvm_value_to_lvar_with_offset(llvm_stack, llvm_value->lvar_address_index, &llvm_value_of_vm_stack);
                        llvm_value->lvar_address_index = -1;
                    }
                }

                /// VM stack to llvm stack ///
                vm_lvar_to_llvm_lvar(llvm_stack, params, current_block, var_num);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, real_param_num);

                /// vm stack_ptr to llvm stack ///
                LVALUE llvm_value = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);

                /// delete result from vm stack ///
                dec_vm_stack_ptr(params, current_block, 1);
                }
                break;

            case OP_INVOKE_VIRTUAL_METHOD: {
                int num_real_params = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                /// llvm stack to VM stack ///
                llvm_lvar_to_vm_lvar(llvm_stack, params, current_block, var_num);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_real_params);

                /// get object value from llvm stack ///
                LVALUE* object_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -num_real_params);

                /// go ///
                Function* fun = TheModule->getFunction("call_invoke_virtual_method");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_real_params);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param2);

                std::string stack_value_name("stack");
                Value* param3 = params[stack_value_name];
                params2.push_back(param3);

                std::string var_num_value_name("var_num");
                Value* param4 = params[var_num_value_name];
                params2.push_back(param4);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param5 = params[stack_ptr_address_name];
                params2.push_back(param5);

                std::string info_value_name("info");
                Value* param6 = params[info_value_name];
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(param7);

                Value* param8 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param8);

                Value* param9 = object_value->value;
                params2.push_back(param9);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, klass, method, params, &current_block, function, &try_catch_label_name, code, num_real_params-1, var_num, llvm_stack, llvm_stack_ptr);
                
                /// the pointer of lvar syncs to llvm stack ///
                int i;
                for(i=0; i<num_real_params-1; i++) {
                    LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -i-1);
                    if(llvm_value->lvar_address_index != -1) {
                        LVALUE llvm_value_of_vm_stack = get_stack_value_from_index_with_aligned(params, current_block, llvm_value->lvar_address_index, 8);
                        store_llvm_value_to_lvar_with_offset(llvm_stack, llvm_value->lvar_address_index, &llvm_value_of_vm_stack);
                    }
                }

                /// VM stack to llvm stack ///
                vm_lvar_to_llvm_lvar(llvm_stack, params, current_block, var_num);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_real_params);

                /// vm stack_ptr to llvm stack ///
                LVALUE llvm_value = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);

                /// delete result from vm stack ///
                dec_vm_stack_ptr(params, current_block, 1);
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

                int num_real_params = num_params + (static_ ? 0:1);

                /// llvm stack to VM stack ///
                llvm_lvar_to_vm_lvar(llvm_stack, params, current_block, var_num);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_real_params);

                /// go ///
                Function* fun = TheModule->getFunction("call_invoke_dynamic_method");

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

                std::string var_num_value_name("var_num");
                Value* param8 = params[var_num_value_name];
                params2.push_back(param8);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param9 = params[stack_ptr_address_name];
                params2.push_back(param9);

                std::string info_value_name("info");
                Value* param10 = params[info_value_name];
                params2.push_back(param10);

                Value* param11 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(param11);

                Value* param12 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param12);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, klass, method, params, &current_block, function, &try_catch_label_name, code, num_real_params-1, var_num, llvm_stack, llvm_stack_ptr);
                
                /// the pointer of lvar syncs to llvm stack ///
                int i;
                for(i=0; i<num_real_params-1; i++) {
                    LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -i-1);
                    if(llvm_value->lvar_address_index != -1) {
                        LVALUE llvm_value_of_vm_stack = get_stack_value_from_index_with_aligned(params, current_block, llvm_value->lvar_address_index, 8);
                        store_llvm_value_to_lvar_with_offset(llvm_stack, llvm_value->lvar_address_index, &llvm_value_of_vm_stack);
                    }
                }

                /// VM stack to llvm stack ///
                vm_lvar_to_llvm_lvar(llvm_stack, params, current_block, var_num);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_real_params);

                /// vm stack_ptr to llvm stack ///
                LVALUE llvm_value = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);

                /// delete result from vm stack ///
                dec_vm_stack_ptr(params, current_block, 1);
                }
                break;

            case OP_INVOKE_BLOCK: {
                int num_params = *(int*)pc;
                pc += sizeof(int);

                /// llvm stack to VM stack ///
                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_params + 1);

                /// go ///
                Function* fun = TheModule->getFunction("invoke_block_in_jit");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_params);
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                std::string var_num_value_name("var_num");
                Value* param3 = params[var_num_value_name];
                params2.push_back(param3);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param4 = params[stack_ptr_address_name];
                params2.push_back(param4);

                std::string info_value_name("info");
                Value* param5 = params[info_value_name];
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, function, &current_block);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_params+1);

                /// vm stack_ptr to llvm stack ///
                LVALUE llvm_value = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);

                /// delete result from vm stack ///
                dec_vm_stack_ptr(params, current_block, 1);
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
                    llvm_value.lvar_address_index = -1;
                    llvm_value.lvar_stored = FALSE;

                    dec_stack_ptr(&llvm_stack_ptr, 1);
                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                    /// push object to jit objects ///
                    Function* fun2 = TheModule->getFunction("push_jit_object");

                    std::vector<Value*> params3;

                    Value* param1 = llvm_value.value;
                    params3.push_back(param1);

                    (void)Builder.CreateCall(fun2, params3);
                }
                else {
                    Function* function = TheModule->getFunction("create_object");

                    std::vector<Value*> params2;
                    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                    params2.push_back(klass_value);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.vm_stack = TRUE;
                    llvm_value.lvar_address_index = -1;
                    llvm_value.lvar_stored = FALSE;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                    /// push object to jit objects ///
                    Function* fun2 = TheModule->getFunction("push_jit_object");

                    std::vector<Value*> params3;

                    Value*param1 = llvm_value.value;
                    params3.push_back(param1);

                    (void)Builder.CreateCall(fun2, params3);
                }
                }
                break;

            case OP_LOAD_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
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

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                trunc_vm_stack_value2(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_FIELD_ADDRESS: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                LVALUE* obj_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_load_field_address");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* param6 = obj_value->value;
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_STORE_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                LVALUE* obj = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("store_field");

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

                Value* param5 = obj->value;
                params2.push_back(param5);

                Value* param6 = value->value;
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, function, &current_block);
                }
                break;

            case OP_LOAD_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("load_class_field");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                trunc_vm_stack_value2(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
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

                std::string var_num_value_name("var_num");
                Value* param3 = params[var_num_value_name];
                params2.push_back(param3);

                std::string info_value_name("info");
                Value* param4 = params[info_value_name];
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_STORE_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("store_class_field");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* param8 = llvm_value->value;
                params2.push_back(param8);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, function, &current_block);
                }
                break;

            case OP_STORE_VALUE_TO_INT_ADDRESS: 
            case OP_STORE_VALUE_TO_UINT_ADDRESS:
            case OP_STORE_VALUE_TO_CHAR_ADDRESS:
            case OP_STORE_VALUE_TO_BOOL_ADDRESS:
            case OP_STORE_VALUE_TO_OBJECT_ADDRESS:
            case OP_STORE_VALUE_TO_FLOAT_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Builder.CreateAlignedStore(value->value, address->value, 4);

                dec_stack_ptr(&llvm_stack_ptr, 2);

                push_value_to_stack_ptr(&llvm_stack_ptr, value);

                /// lvar of vm stack to lvar of llvm stack ///
                lvar_of_vm_to_lvar_of_llvm(params, current_block, llvm_stack, var_num);
                }
                break;

            case OP_STORE_VALUE_TO_BYTE_ADDRESS:
            case OP_STORE_VALUE_TO_UBYTE_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Builder.CreateAlignedStore(value->value, address->value, 1);

                dec_stack_ptr(&llvm_stack_ptr, 2);

                push_value_to_stack_ptr(&llvm_stack_ptr, value);

                /// lvar of vm stack to lvar of llvm stack ///
                lvar_of_vm_to_lvar_of_llvm(params, current_block, llvm_stack, var_num);
                }
                break;

            case OP_STORE_VALUE_TO_SHORT_ADDRESS:
            case OP_STORE_VALUE_TO_USHORT_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Builder.CreateAlignedStore(value->value, address->value, 2);

                dec_stack_ptr(&llvm_stack_ptr, 2);

                push_value_to_stack_ptr(&llvm_stack_ptr, value);

                /// lvar of vm stack to lvar of llvm stack ///
                lvar_of_vm_to_lvar_of_llvm(params, current_block, llvm_stack, var_num);
                }
                break;

            case OP_LOAD_VALUE_FROM_INT_ADDRESS: 
            case OP_LOAD_VALUE_FROM_UINT_ADDRESS: 
            case OP_LOAD_VALUE_FROM_CHAR_ADDRESS: 
            case OP_LOAD_VALUE_FROM_BOOL_ADDRESS: 
            case OP_LOAD_VALUE_FROM_OBJECT_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                address->value = Builder.CreateCast(Instruction::IntToPtr, address->value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(address->value, 4, "llvm_value");
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                
                llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_VALUE_FROM_FLOAT_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                address->value = Builder.CreateCast(Instruction::IntToPtr, address->value, PointerType::get(Type::getFloatTy(TheContext), 0));

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(address->value, 4, "llvm_value");
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                
                llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getFloatTy(TheContext));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_VALUE_FROM_BYTE_ADDRESS: 
            case OP_LOAD_VALUE_FROM_UBYTE_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                address->value = Builder.CreateCast(Instruction::IntToPtr, address->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(address->value, 1, "llvm_value");
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_VALUE_FROM_SHORT_ADDRESS:
            case OP_LOAD_VALUE_FROM_USHORT_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                address->value = Builder.CreateCast(Instruction::IntToPtr, address->value, PointerType::get(IntegerType::get(TheContext, 16), 0));

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(address->value, 2, "llvm_value");
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_VALUE_FROM_LONG_ADDRESS:
            case OP_LOAD_VALUE_FROM_ULONG_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                address->value = Builder.CreateCast(Instruction::IntToPtr, address->value, PointerType::get(IntegerType::get(TheContext, 64), 0));

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt64Ty(TheContext));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_VALUE_FROM_POINTER_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                address->value = Builder.CreateCast(Instruction::IntToPtr, address->value, PointerType::get(IntegerType::get(TheContext, 64), 0));

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS: {
                /// lvar of llvm stack to lvar of vm stack ///
                lvar_of_llvm_to_lvar_of_vm(params, current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                address->value = Builder.CreateCast(Instruction::IntToPtr, address->value, PointerType::get(Type::getDoubleTy(TheContext), 0));

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getDoubleTy(TheContext));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_LOAD_ELEMENT: {
                int size = *(int*)pc;
                pc += sizeof(int);

                LVALUE* array = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* element_num = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("load_element");

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

                Value* param5 = array->value;
                params2.push_back(param5);

                Value* param6 = element_num->value;
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                dec_stack_ptr(&llvm_stack_ptr, 2);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;


                trunc_vm_stack_value2(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_STORE_ELEMENT: {
                LVALUE* array = get_stack_ptr_value_from_index(llvm_stack_ptr, -3);
                LVALUE* element_num = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_store_element");

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

                Value* param5 = array->value;
                params2.push_back(param5);

                Value* param6 = element_num->value;
                params2.push_back(param6);

                Value* param7 = value->value;
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, function, &current_block);

                LVALUE llvm_value = *value;

                dec_stack_ptr(&llvm_stack_ptr, 3);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_STORE_VALUE_TO_LONG_ADDRESS:
            case OP_STORE_VALUE_TO_ULONG_ADDRESS:
            case OP_STORE_VALUE_TO_DOUBLE_ADDRESS:
            case OP_STORE_VALUE_TO_POINTER_ADDRESS: {
                LVALUE* address = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Builder.CreateAlignedStore(value->value, address->value, 8);

                dec_stack_ptr(&llvm_stack_ptr, 2);

                push_value_to_stack_ptr(&llvm_stack_ptr, value);

                /// lvar of vm stack to lvar of llvm stack ///
                lvar_of_vm_to_lvar_of_llvm(params, current_block, llvm_stack, var_num);
                }
                break;

            case OP_BYTE_TO_INT_CAST:
            case OP_SHORT_TO_INT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBYTE_TO_INT_CAST:
            case OP_USHORT_TO_INT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BYTE_TO_UINT_CAST:
            case OP_UBYTE_TO_UINT_CAST:
            case OP_SHORT_TO_UINT_CAST:
            case OP_USHORT_TO_UINT_CAST: 
            case OP_BYTE_TO_CHAR_CAST:
            case OP_UBYTE_TO_CHAR_CAST:
            case OP_SHORT_TO_CHAR_CAST:
            case OP_USHORT_TO_CHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INT_TO_CHAR_CAST:
            case OP_UINT_TO_CHAR_CAST:
            case OP_INT_TO_UINT_CAST :
            case OP_UINT_TO_INT_CAST:
            case OP_CHAR_TO_UINT_CAST:
            case OP_CHAR_TO_INT_CAST:
                break;

            case OP_LONG_TO_INT_CAST:
            case OP_ULONG_TO_INT_CAST:
            case OP_LONG_TO_UINT_CAST:
            case OP_ULONG_TO_UINT_CAST:
            case OP_LONG_TO_CHAR_CAST:
            case OP_ULONG_TO_CHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_INT_CAST:
            case OP_DOUBLE_TO_INT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_UINT_CAST:
            case OP_DOUBLE_TO_UINT_CAST: 
            case OP_FLOAT_TO_CHAR_CAST:
            case OP_DOUBLE_TO_CHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_POINTER_TO_INT_CAST:
            case OP_POINTER_TO_UINT_CAST:
            case OP_POINTER_TO_CHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BYTE_TO_UBYTE_CAST:
            case OP_UBYTE_TO_BYTE_CAST:
                break;

            case OP_SHORT_TO_BYTE_CAST:
            case OP_USHORT_TO_BYTE_CAST:
            case OP_INT_TO_BYTE_CAST:
            case OP_UINT_TO_BYTE_CAST:
            case OP_LONG_TO_BYTE_CAST:
            case OP_ULONG_TO_BYTE_CAST:
            case OP_CHAR_TO_BYTE_CAST: 
            case OP_SHORT_TO_UBYTE_CAST:
            case OP_USHORT_TO_UBYTE_CAST:
            case OP_INT_TO_UBYTE_CAST:
            case OP_UINT_TO_UBYTE_CAST:
            case OP_LONG_TO_UBYTE_CAST:
            case OP_ULONG_TO_UBYTE_CAST:
            case OP_CHAR_TO_UBYTE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt8Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_BYTE_CAST:
            case OP_DOUBLE_TO_BYTE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt8Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_UBYTE_CAST:
            case OP_DOUBLE_TO_UBYTE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt8Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_POINTER_TO_BYTE_CAST: 
            case OP_POINTER_TO_UBYTE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt8Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INT_TO_SHORT_CAST:
            case OP_UINT_TO_SHORT_CAST:
            case OP_LONG_TO_SHORT_CAST:
            case OP_ULONG_TO_SHORT_CAST:
            case OP_CHAR_TO_SHORT_CAST: 
            case OP_INT_TO_USHORT_CAST:
            case OP_UINT_TO_USHORT_CAST:
            case OP_LONG_TO_USHORT_CAST:
            case OP_ULONG_TO_USHORT_CAST:
            case OP_CHAR_TO_USHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt16Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_SHORT_CAST:
            case OP_DOUBLE_TO_SHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt16Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_USHORT_CAST:
            case OP_DOUBLE_TO_USHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt16Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BYTE_TO_SHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;
                
            case OP_UBYTE_TO_SHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;
               
            case OP_BYTE_TO_USHORT_CAST:
            case OP_UBYTE_TO_USHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt32Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_SHORT_TO_USHORT_CAST:
            case OP_USHORT_TO_SHORT_CAST:
                break;

            case OP_POINTER_TO_SHORT_CAST:
            case OP_POINTER_TO_USHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt16Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BYTE_TO_LONG_CAST:
            case OP_SHORT_TO_LONG_CAST:
            case OP_INT_TO_LONG_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt64Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBYTE_TO_LONG_CAST:
            case OP_USHORT_TO_LONG_CAST:
            case OP_UINT_TO_LONG_CAST:
            case OP_CHAR_TO_LONG_CAST:
            case OP_BYTE_TO_ULONG_CAST:
            case OP_UBYTE_TO_ULONG_CAST:
            case OP_SHORT_TO_ULONG_CAST:
            case OP_USHORT_TO_ULONG_CAST:
            case OP_INT_TO_ULONG_CAST:
            case OP_UINT_TO_ULONG_CAST:
            case OP_CHAR_TO_ULONG_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt64Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ULONG_TO_LONG_CAST:
                break;

            case OP_FLOAT_TO_LONG_CAST:
            case OP_DOUBLE_TO_LONG_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt64Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_ULONG_CAST:
            case OP_DOUBLE_TO_ULONG_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt64Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_POINTER_TO_LONG_CAST: 
            case OP_POINTER_TO_ULONG_CAST:  {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt64Ty(TheContext), "value2");
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BYTE_TO_POINTER_CAST :
            case OP_UBYTE_TO_POINTER_CAST:
            case OP_SHORT_TO_POINTER_CAST:
            case OP_USHORT_TO_POINTER_CAST:
            case OP_INT_TO_POINTER_CAST:
            case OP_UINT_TO_POINTER_CAST:
            case OP_LONG_TO_POINTER_CAST:
            case OP_ULONG_TO_POINTER_CAST:
            case OP_CHAR_TO_POINTER_CAST: {
/*
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
*/
                }
                break;

            case OP_BYTE_TO_FLOAT_CAST:
            case OP_SHORT_TO_FLOAT_CAST:
            case OP_INT_TO_FLOAT_CAST:
            case OP_LONG_TO_FLOAT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::SIToFP, value->value, Type::getFloatTy(TheContext));
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBYTE_TO_FLOAT_CAST:
            case OP_USHORT_TO_FLOAT_CAST:
            case OP_UINT_TO_FLOAT_CAST:
            case OP_ULONG_TO_FLOAT_CAST:
            case OP_CHAR_TO_FLOAT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::UIToFP, value->value, Type::getFloatTy(TheContext));
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_DOUBLE_TO_FLOAT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPTrunc, value->value, Type::getFloatTy(TheContext));
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_BYTE_TO_DOUBLE_CAST:
            case OP_SHORT_TO_DOUBLE_CAST:
            case OP_INT_TO_DOUBLE_CAST:
            case OP_LONG_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::SIToFP, value->value, Type::getDoubleTy(TheContext));
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UBYTE_TO_DOUBLE_CAST:
            case OP_USHORT_TO_DOUBLE_CAST:
            case OP_UINT_TO_DOUBLE_CAST:
            case OP_ULONG_TO_DOUBLE_CAST:
            case OP_CHAR_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::UIToFP, value->value, Type::getDoubleTy(TheContext));
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_FLOAT_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCast(Instruction::FPExt, value->value, Type::getDoubleTy(TheContext));
                llvm_value.vm_stack = value->vm_stack;
                llvm_value.lvar_address_index = value->lvar_address_index;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;




            case OP_BYTE_TO_STRING_CAST: 
            case OP_SHORT_TO_STRING_CAST :
            case OP_INT_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_int_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_LONG_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_long_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_UBYTE_TO_STRING_CAST :
            case OP_USHORT_TO_STRING_CAST :
            case OP_UINT_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_uint_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_ULONG_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_ulong_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_FLOAT_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_float_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_DOUBLE_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_double_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CHAR_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_char_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_REGEX_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_regex_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BOOL_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_bool_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_POINTER_TO_STRING_CAST : {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_pointer_to_string_cast");

                std::vector<Value*> params2;

                params2.push_back(llvm_value->value);

                LVALUE result;
                result.value = Builder.CreateCall(fun, params2);
                result.vm_stack = TRUE;
                result.lvar_address_index = -1;
                result.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &result);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                Value* param1 = result.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;


            case OP_BYTE_TO_INTEGER_CAST:
            case OP_UBYTE_TO_INTEGER_CAST:
            case OP_SHORT_TO_INTEGER_CAST:
            case OP_USHORT_TO_INTEGER_CAST:
            case OP_INT_TO_INTEGER_CAST:
            case OP_UINT_TO_INTEGER_CAST:
            case OP_LONG_TO_INTEGER_CAST:
            case OP_ULONG_TO_INTEGER_CAST:
            case OP_CHAR_TO_INTEGER_CAST:
            case OP_POINTER_TO_INTEGER_CAST:
            case OP_BOOL_TO_INTEGER_CAST:
            case OP_FLOAT_TO_INTEGER_CAST:
            case OP_DOUBLE_TO_INTEGER_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;


            case OP_BYTE_TO_UINTEGER_CAST:
            case OP_UBYTE_TO_UINTEGER_CAST:
            case OP_SHORT_TO_UINTEGER_CAST:
            case OP_USHORT_TO_UINTEGER_CAST:
            case OP_INT_TO_UINTEGER_CAST:
            case OP_UINT_TO_UINTEGER_CAST:
            case OP_LONG_TO_UINTEGER_CAST:
            case OP_ULONG_TO_UINTEGER_CAST:
            case OP_CHAR_TO_UINTEGER_CAST:
            case OP_POINTER_TO_UINTEGER_CAST:
            case OP_BOOL_TO_UINTEGER_CAST:
            case OP_FLOAT_TO_UINTEGER_CAST:
            case OP_DOUBLE_TO_UINTEGER_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CBYTE_CAST:
            case OP_UBYTE_TO_CBYTE_CAST:
            case OP_SHORT_TO_CBYTE_CAST:
            case OP_USHORT_TO_CBYTE_CAST:
            case OP_INT_TO_CBYTE_CAST:
            case OP_UINT_TO_CBYTE_CAST:
            case OP_LONG_TO_CBYTE_CAST:
            case OP_ULONG_TO_CBYTE_CAST:
            case OP_CHAR_TO_CBYTE_CAST:
            case OP_POINTER_TO_CBYTE_CAST:
            case OP_BOOL_TO_CBYTE_CAST: 
            case OP_FLOAT_TO_CBYTE_CAST:
            case OP_DOUBLE_TO_CBYTE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;


            case OP_BYTE_TO_CUBYTE_CAST:
            case OP_UBYTE_TO_CUBYTE_CAST:
            case OP_SHORT_TO_CUBYTE_CAST:
            case OP_USHORT_TO_CUBYTE_CAST:
            case OP_INT_TO_CUBYTE_CAST:
            case OP_UINT_TO_CUBYTE_CAST:
            case OP_LONG_TO_CUBYTE_CAST:
            case OP_ULONG_TO_CUBYTE_CAST:
            case OP_CHAR_TO_CUBYTE_CAST:
            case OP_POINTER_TO_CUBYTE_CAST:
            case OP_BOOL_TO_CUBYTE_CAST:
            case OP_FLOAT_TO_CUBYTE_CAST:
            case OP_DOUBLE_TO_CUBYTE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;


            case OP_BYTE_TO_CSHORT_CAST:
            case OP_UBYTE_TO_CSHORT_CAST:
            case OP_SHORT_TO_CSHORT_CAST:
            case OP_USHORT_TO_CSHORT_CAST:
            case OP_INT_TO_CSHORT_CAST:
            case OP_UINT_TO_CSHORT_CAST:
            case OP_LONG_TO_CSHORT_CAST:
            case OP_ULONG_TO_CSHORT_CAST:
            case OP_CHAR_TO_CSHORT_CAST:
            case OP_POINTER_TO_CSHORT_CAST:
            case OP_BOOL_TO_CSHORT_CAST: 
            case OP_FLOAT_TO_CSHORT_CAST:
            case OP_DOUBLE_TO_CSHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CUSHORT_CAST:
            case OP_UBYTE_TO_CUSHORT_CAST:
            case OP_SHORT_TO_CUSHORT_CAST:
            case OP_USHORT_TO_CUSHORT_CAST:
            case OP_INT_TO_CUSHORT_CAST:
            case OP_UINT_TO_CUSHORT_CAST:
            case OP_LONG_TO_CUSHORT_CAST:
            case OP_ULONG_TO_CUSHORT_CAST:
            case OP_CHAR_TO_CUSHORT_CAST:
            case OP_POINTER_TO_CUSHORT_CAST:
            case OP_BOOL_TO_CUSHORT_CAST:
            case OP_FLOAT_TO_CUSHORT_CAST:
            case OP_DOUBLE_TO_CUSHORT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CLONG_CAST:
            case OP_UBYTE_TO_CLONG_CAST:
            case OP_SHORT_TO_CLONG_CAST:
            case OP_USHORT_TO_CLONG_CAST:
            case OP_INT_TO_CLONG_CAST:
            case OP_UINT_TO_CLONG_CAST:
            case OP_LONG_TO_CLONG_CAST:
            case OP_ULONG_TO_CLONG_CAST:
            case OP_CHAR_TO_CLONG_CAST:
            case OP_POINTER_TO_CLONG_CAST:
            case OP_BOOL_TO_CLONG_CAST: 
            case OP_FLOAT_TO_CLONG_CAST:
            case OP_DOUBLE_TO_CLONG_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CULONG_CAST:
            case OP_UBYTE_TO_CULONG_CAST:
            case OP_SHORT_TO_CULONG_CAST:
            case OP_USHORT_TO_CULONG_CAST:
            case OP_INT_TO_CULONG_CAST:
            case OP_UINT_TO_CULONG_CAST:
            case OP_LONG_TO_CULONG_CAST:
            case OP_ULONG_TO_CULONG_CAST:
            case OP_CHAR_TO_CULONG_CAST:
            case OP_POINTER_TO_CULONG_CAST:
            case OP_BOOL_TO_CULONG_CAST:
            case OP_FLOAT_TO_CULONG_CAST:
            case OP_DOUBLE_TO_CULONG_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CFLOAT_CAST:
            case OP_SHORT_TO_CFLOAT_CAST:
            case OP_INT_TO_CFLOAT_CAST:
            case OP_LONG_TO_CFLOAT_CAST:
            case OP_BOOL_TO_CFLOAT_CAST:
            case OP_UBYTE_TO_CFLOAT_CAST:
            case OP_USHORT_TO_CFLOAT_CAST:
            case OP_UINT_TO_CFLOAT_CAST:
            case OP_CHAR_TO_CFLOAT_CAST:
            case OP_ULONG_TO_CFLOAT_CAST:
            case OP_FLOAT_TO_CFLOAT_CAST: 
            case OP_DOUBLE_TO_CFLOAT_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CDOUBLE_CAST:
            case OP_SHORT_TO_CDOUBLE_CAST:
            case OP_INT_TO_CDOUBLE_CAST:
            case OP_LONG_TO_CDOUBLE_CAST:
            case OP_BOOL_TO_CDOUBLE_CAST: 
            case OP_UBYTE_TO_CDOUBLE_CAST:
            case OP_USHORT_TO_CDOUBLE_CAST:
            case OP_UINT_TO_CDOUBLE_CAST:
            case OP_CHAR_TO_CDOUBLE_CAST:
            case OP_ULONG_TO_CDOUBLE_CAST:
            case OP_FLOAT_TO_CDOUBLE_CAST: 
            case OP_DOUBLE_TO_CDOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                cast_llvm_value_from_inst(value, inst);

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CPOINTER_CAST:
            case OP_UBYTE_TO_CPOINTER_CAST:
            case OP_SHORT_TO_CPOINTER_CAST:
            case OP_USHORT_TO_CPOINTER_CAST:
            case OP_INT_TO_CPOINTER_CAST:
            case OP_UINT_TO_CPOINTER_CAST:
            case OP_LONG_TO_CPOINTER_CAST:
            case OP_ULONG_TO_CPOINTER_CAST:
            case OP_CHAR_TO_CPOINTER_CAST: 
            case OP_POINTER_TO_CPOINTER_CAST:
            case OP_BOOL_TO_CPOINTER_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CBOOL_CAST :
            case OP_UBYTE_TO_CBOOL_CAST:
            case OP_SHORT_TO_CBOOL_CAST:
            case OP_USHORT_TO_CBOOL_CAST:
            case OP_INT_TO_CBOOL_CAST:
            case OP_UINT_TO_CBOOL_CAST:
            case OP_LONG_TO_CBOOL_CAST:
            case OP_ULONG_TO_CBOOL_CAST:
            case OP_FLOAT_TO_CBOOL_CAST:
            case OP_DOUBLE_TO_CBOOL_CAST:
            case OP_CHAR_TO_CBOOL_CAST:
            case OP_POINTER_TO_CBOOL_CAST:
            case OP_BOOL_TO_CBOOL_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_BYTE_TO_CCHAR_CAST :
            case OP_UBYTE_TO_CCHAR_CAST:
            case OP_SHORT_TO_CCHAR_CAST:
            case OP_USHORT_TO_CCHAR_CAST:
            case OP_INT_TO_CCHAR_CAST:
            case OP_UINT_TO_CCHAR_CAST:
            case OP_LONG_TO_CCHAR_CAST:
            case OP_ULONG_TO_CCHAR_CAST:
            case OP_FLOAT_TO_CCHAR_CAST:
            case OP_DOUBLE_TO_CCHAR_CAST:
            case OP_CHAR_TO_CCHAR_CAST:
            case OP_POINTER_TO_CCHAR_CAST:
            case OP_BOOL_TO_CCHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CBYTE_TO_BYTE_CAST:
            case OP_CBYTE_TO_SHORT_CAST:
            case OP_CBYTE_TO_INT_CAST:
            case OP_CBYTE_TO_LONG_CAST:
            case OP_CBYTE_TO_UBYTE_CAST:
            case OP_CBYTE_TO_USHORT_CAST:
            case OP_CBYTE_TO_UINT_CAST:
            case OP_CBYTE_TO_ULONG_CAST:
            case OP_CBYTE_TO_CHAR_CAST:
            case OP_CBYTE_TO_FLOAT_CAST:
            case OP_CBYTE_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                cast_llvm_value_from_inst(&llvm_value, inst);

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CUBYTE_TO_BYTE_CAST:
            case OP_CUBYTE_TO_SHORT_CAST:
            case OP_CUBYTE_TO_INT_CAST:
            case OP_CUBYTE_TO_LONG_CAST:
            case OP_CUBYTE_TO_UBYTE_CAST:
            case OP_CUBYTE_TO_USHORT_CAST:
            case OP_CUBYTE_TO_UINT_CAST:
            case OP_CUBYTE_TO_ULONG_CAST:
            case OP_CUBYTE_TO_CHAR_CAST:
            case OP_CUBYTE_TO_FLOAT_CAST:
            case OP_CUBYTE_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                cast_llvm_value_from_inst(&llvm_value, inst);

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CSHORT_TO_BYTE_CAST:
            case OP_CSHORT_TO_SHORT_CAST:
            case OP_CSHORT_TO_INT_CAST : 
            case OP_CSHORT_TO_LONG_CAST : 
            case OP_CSHORT_TO_UBYTE_CAST :
            case OP_CSHORT_TO_USHORT_CAST :
            case OP_CSHORT_TO_UINT_CAST :
            case OP_CSHORT_TO_ULONG_CAST :
            case OP_CSHORT_TO_CHAR_CAST:
            case OP_CSHORT_TO_FLOAT_CAST: 
            case OP_CSHORT_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CUSHORT_TO_BYTE_CAST:
            case OP_CUSHORT_TO_SHORT_CAST:
            case OP_CUSHORT_TO_INT_CAST : 
            case OP_CUSHORT_TO_LONG_CAST : 
            case OP_CUSHORT_TO_UBYTE_CAST :
            case OP_CUSHORT_TO_USHORT_CAST :
            case OP_CUSHORT_TO_UINT_CAST :
            case OP_CUSHORT_TO_ULONG_CAST :
            case OP_CUSHORT_TO_CHAR_CAST:
            case OP_CUSHORT_TO_FLOAT_CAST:
            case OP_CUSHORT_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INTEGER_TO_BYTE_CAST:
            case OP_INTEGER_TO_SHORT_CAST:
            case OP_INTEGER_TO_INT_CAST : 
            case OP_INTEGER_TO_LONG_CAST : 
            case OP_INTEGER_TO_UBYTE_CAST :
            case OP_INTEGER_TO_USHORT_CAST :
            case OP_INTEGER_TO_UINT_CAST :
            case OP_INTEGER_TO_ULONG_CAST :
            case OP_INTEGER_TO_CHAR_CAST:
            case OP_INTEGER_TO_FLOAT_CAST:
            case OP_INTEGER_TO_DOUBLE_CAST:
            case OP_CBOOL_TO_BYTE_CAST:
            case OP_CBOOL_TO_SHORT_CAST:
            case OP_CBOOL_TO_INT_CAST : 
            case OP_CBOOL_TO_LONG_CAST : 
            case OP_CBOOL_TO_UBYTE_CAST :
            case OP_CBOOL_TO_USHORT_CAST :
            case OP_CBOOL_TO_UINT_CAST :
            case OP_CBOOL_TO_ULONG_CAST :
            case OP_CBOOL_TO_CHAR_CAST: 
            case OP_CBOOL_TO_FLOAT_CAST:
            case OP_CBOOL_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_integer_to_int_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_UINTEGER_TO_BYTE_CAST:
            case OP_UINTEGER_TO_SHORT_CAST:
            case OP_UINTEGER_TO_INT_CAST : 
            case OP_UINTEGER_TO_LONG_CAST : 
            case OP_UINTEGER_TO_UBYTE_CAST :
            case OP_UINTEGER_TO_USHORT_CAST :
            case OP_UINTEGER_TO_UINT_CAST :
            case OP_UINTEGER_TO_ULONG_CAST :
            case OP_UINTEGER_TO_CHAR_CAST:
            case OP_UINTEGER_TO_FLOAT_CAST: 
            case OP_UINTEGER_TO_DOUBLE_CAST:
            case OP_CCHAR_TO_BYTE_CAST:
            case OP_CCHAR_TO_SHORT_CAST:
            case OP_CCHAR_TO_INT_CAST : 
            case OP_CCHAR_TO_LONG_CAST : 
            case OP_CCHAR_TO_UBYTE_CAST :
            case OP_CCHAR_TO_USHORT_CAST :
            case OP_CCHAR_TO_UINT_CAST :
            case OP_CCHAR_TO_ULONG_CAST :
            case OP_CCHAR_TO_CHAR_CAST:
            case OP_CCHAR_TO_FLOAT_CAST:
            case OP_CCHAR_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CLONG_TO_BYTE_CAST:
            case OP_CLONG_TO_SHORT_CAST:
            case OP_CLONG_TO_INT_CAST : 
            case OP_CLONG_TO_LONG_CAST : 
            case OP_CLONG_TO_UBYTE_CAST :
            case OP_CLONG_TO_USHORT_CAST :
            case OP_CLONG_TO_UINT_CAST :
            case OP_CLONG_TO_ULONG_CAST :
            case OP_CLONG_TO_CHAR_CAST:
            case OP_CLONG_TO_FLOAT_CAST: 
            case OP_CLONG_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_clong_to_long_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CULONG_TO_BYTE_CAST:
            case OP_CULONG_TO_SHORT_CAST:
            case OP_CULONG_TO_INT_CAST : 
            case OP_CULONG_TO_LONG_CAST : 
            case OP_CULONG_TO_UBYTE_CAST :
            case OP_CULONG_TO_USHORT_CAST :
            case OP_CULONG_TO_UINT_CAST :
            case OP_CULONG_TO_ULONG_CAST :
            case OP_CULONG_TO_CHAR_CAST:
            case OP_CULONG_TO_FLOAT_CAST:
            case OP_CULONG_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CPOINTER_TO_BYTE_CAST:
            case OP_CPOINTER_TO_SHORT_CAST:
            case OP_CPOINTER_TO_INT_CAST : 
            case OP_CPOINTER_TO_LONG_CAST : 
            case OP_CPOINTER_TO_UBYTE_CAST :
            case OP_CPOINTER_TO_USHORT_CAST :
            case OP_CPOINTER_TO_UINT_CAST :
            case OP_CPOINTER_TO_ULONG_CAST :
            case OP_CPOINTER_TO_CHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CFLOAT_TO_BYTE_CAST:
            case OP_CFLOAT_TO_SHORT_CAST:
            case OP_CFLOAT_TO_INT_CAST : 
            case OP_CFLOAT_TO_LONG_CAST : 
            case OP_CFLOAT_TO_UBYTE_CAST :
            case OP_CFLOAT_TO_USHORT_CAST :
            case OP_CFLOAT_TO_UINT_CAST :
            case OP_CFLOAT_TO_ULONG_CAST :
            case OP_CFLOAT_TO_CHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CFLOAT_TO_FLOAT_CAST:
            case OP_CFLOAT_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cfloat_to_float_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CDOUBLE_TO_BYTE_CAST:
            case OP_CDOUBLE_TO_SHORT_CAST:
            case OP_CDOUBLE_TO_INT_CAST : 
            case OP_CDOUBLE_TO_LONG_CAST : 
            case OP_CDOUBLE_TO_UBYTE_CAST :
            case OP_CDOUBLE_TO_USHORT_CAST :
            case OP_CDOUBLE_TO_UINT_CAST :
            case OP_CDOUBLE_TO_ULONG_CAST :
            case OP_CDOUBLE_TO_CHAR_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CDOUBLE_TO_FLOAT_CAST:
            case OP_CDOUBLE_TO_DOUBLE_CAST: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_cdouble_to_double_cast");

                std::vector<Value*> params2;

                Value* param1 = value->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                cast_llvm_value_from_inst(&llvm_value, inst);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_ARRAY_TO_CARRAY_CAST: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                LVALUE* array = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_array_to_carray_cast");

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

                Value* param5 = array->value;
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                trunc_vm_stack_value2(&llvm_value, 4);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_ARRAY_LENGTH: {
                LVALUE* array_ = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_array_length");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = array_->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                trunc_vm_stack_value2(&llvm_value, 4);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_REGEX_GLOBAL: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_global");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_REGEX_IGNORE_CASE: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_ignorecase");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_REGEX_MULTILINE: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_multiline");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_REGEX_EXTENDED: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_extended");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_REGEX_DOTALL: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_dotall");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_REGEX_ANCHORED: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_anchored");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_GET_REGEX_DOLLAR_ENDONLY: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_dollar_endonly");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;


            case OP_GET_REGEX_UNGREEDY: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_ungreedy");

                std::vector<Value*> params2;

                Value* param1 = regex->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CHAR_UPPERCASE: {
                LVALUE* c = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("char_uppercase");

                std::vector<Value*> params2;
                Value* param1 = c->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_CHAR_LOWERCASE: {
                LVALUE* c = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("char_lowercase");

                std::vector<Value*> params2;
                Value* param1 = c->value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
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
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
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

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
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

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_ARRAY: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_array");

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

                Value* param5 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);

                /// delete vm stack ///
                dec_vm_stack_ptr(params, current_block, num_elements);
                }
                break;

            case OP_CREATE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_carray");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_SORTABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_sortable_carray");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_EQUALABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_equalable_carray");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_list");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_SORTALBE_LIST: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_sortable_list");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_EQUALABLE_LIST: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_equalable_list");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_TUPLE: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements);

                Function* fun = TheModule->getFunction("run_create_tuple");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            case OP_CREATE_HASH: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);
                char* class_name2 = CONS_str(constant, offset2);

                llvm_stack_to_vm_stack(llvm_stack_ptr, params, current_block, num_elements*2);

                Function* fun = TheModule->getFunction("run_create_hash");

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

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name2);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
                Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);

                if_value_is_zero_ret_zero(result2, params, function, &current_block);

                LVALUE llvm_value;
                llvm_value.value = result1;
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements*2);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
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

                std::string info_value_name("info");
                Value* param11 = params[info_value_name];
                params2.push_back(param11);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.vm_stack = FALSE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
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

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.vm_stack = TRUE;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                /// push object to jit objects ///
                Function* fun2 = TheModule->getFunction("push_jit_object");

                std::vector<Value*> params3;

                param1 = llvm_value.value;
                params3.push_back(param1);

                (void)Builder.CreateCall(fun2, params3);
                }
                break;

            default:
                printf("inst %d\n", inst);
                exit(1);
        }

#ifdef MDEBUG
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
    //show_stack_for_llvm_stack(llvm_stack, llvm_stack_ptr, var_num);
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
    TheFPM->run(*function);

    return TRUE;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info, CLVALUE** stack_ptr)
{
    int num_jit_objects = gNumJITObjects;

    if(!compile_jit_method(klass, method)) {
        gNumJITObjects = num_jit_objects;
        return FALSE;
    }

    if(method->mJITCompiled) {
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

            BOOL result = function(stack_ptr, lvar, info, stack, &stack_ptr, var_num);
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
        BOOL result = vm(code, constant, stack, var_num, klass, info);

        if(!result) {
            gNumJITObjects = num_jit_objects;
            return FALSE;
        }
    }

    gNumJITObjects = num_jit_objects;

    return TRUE;
}


} // extern "C"
