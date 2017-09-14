#include "jit_common.hpp"

extern "C"
{

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
        printf("stack[%d] %p %d\n", i, llvm_stack[i].value, llvm_stack[i].value);
    }
}

void call_show_number_in_jit(clint64 number)
{
    Function* show_number = TheModule->getFunction("show_number_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)number);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_number, params2);
}

void call_show_value_in_jit(Value* value)
{
    Function* show_number = TheModule->getFunction("show_number_in_jit");

    LVALUE llvm_value;
    llvm_value.value = value;
    llvm_value.lvar_address_index = -1;
    llvm_value.lvar_stored = FALSE;
    llvm_value.constant_int_value = FALSE;
    llvm_value.constant_float_value = FALSE;
    llvm_value.float_value = FALSE;

    LVALUE llvm_value2;
    llvm_value2 = trunc_value(&llvm_value, 64);

    std::vector<Value*> params2;
    Value* param1 = llvm_value2.value;
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_number, params2);
}

void call_show_str_in_jit(Value* value)
{
    Function* show_str = TheModule->getFunction("show_str_in_jit");

    std::vector<Value*> params2;
    params2.push_back(value);

    Value* result = Builder.CreateCall(show_str, params2);
}

void call_show_stack_stat(std::map<std::string, Value *> params)
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


void call_show_inst_in_jit(int opecode)
{
    Function* show_inst = TheModule->getFunction("show_inst_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)opecode);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_inst, params2);
}

void call_show_stack(std::map<std::string, Value *> params)
{
    Function* show_stack_fun = TheModule->getFunction("show_stack_in_jit");

    std::vector<Value*> params2;

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];
    Value* param1 = stack_ptr_address_value;
    params2.push_back(param1);

    std::string stack_name("stack");
    Value* stack_value = params[stack_name];
    Value* param2 = stack_value;
    params2.push_back(param2);

    std::string var_num_value_name("var_num");
    Value* param3 = params[var_num_value_name];
    params2.push_back(param3);

    std::string info_value_name("info");
    Value* param4 = params[info_value_name];
    params2.push_back(param4);

    Value* result = Builder.CreateCall(show_stack_fun, params2);
}




}
