#include "jit_common.hpp"

extern "C"
{

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

void show_llvm_value(LVALUE* llvm_value)
{
    Function* fun;
    std::vector<Value*> params2;

    switch(llvm_value->kind) {
        case kLVKindNone: {
            fun = TheModule->getFunction("show_str_in_jit");

            Value* param1 = llvm_create_string("None");
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindInt1: 
        case kLVKindConstantInt1: {
            fun = TheModule->getFunction("show_int8");

            Value* param1 = llvm_value->value;
            param1 = Builder.CreateCast(Instruction::ZExt, param1, Type::getInt8Ty(TheContext));
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindInt8:
        case kLVKindUInt8:
        case kLVKindConstantInt8:
        case kLVKindConstantUInt8: {
            fun = TheModule->getFunction("show_int8");

            Value* param1 = llvm_value->value;
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindInt16:
        case kLVKindUInt16:
        case kLVKindConstantInt16:
        case kLVKindConstantUInt16: {
            fun = TheModule->getFunction("show_int16");

            Value* param1 = llvm_value->value;
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindInt32:
        case kLVKindUInt32:
        case kLVKindConstantInt32:
        case kLVKindConstantUInt32: {
            fun = TheModule->getFunction("show_int32");

            Value* param1 = llvm_value->value;
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindInt64: 
        case kLVKindUInt64:
        case kLVKindConstantInt64:
        case kLVKindConstantUInt64: {
            fun = TheModule->getFunction("show_int64");

            Value* param1 = llvm_value->value;
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindMemory: {
            fun = TheModule->getFunction("show_int64");

            Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindAddress: {
            fun = TheModule->getFunction("show_str_in_jit");

            Value* param1 = llvm_create_string("Address");
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindFloat:
        case kLVKindConstantFloat: {
            fun = TheModule->getFunction("show_float");

            Value* param1 = llvm_value->value;
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindDouble:
        case kLVKindConstantDouble: {
            fun = TheModule->getFunction("show_double");

            Value* param1 = llvm_value->value;
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindPointer8: {
            fun = TheModule->getFunction("show_str_in_jit");

            Value* param1 = llvm_create_string("Pointer8");
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindPointer32: {
            fun = TheModule->getFunction("show_str_in_jit");

            Value* param1 = llvm_create_string("Pointer32");
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindPointer64: {
            fun = TheModule->getFunction("show_str_in_jit");

            Value* param1 = llvm_create_string("Pointer64");
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindPointerDouble: {
            fun = TheModule->getFunction("show_str_in_jit");

            Value* param1 = llvm_create_string("PointerDouble");
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;

        case kLVKindObject: {
            fun = TheModule->getFunction("show_int32");

            Value* param1 = llvm_value->value;
            params2.push_back(param1);

            Builder.CreateCall(fun, params2);
            }
            break;
    }
}

void show_llvm_stack(LVALUE* llvm_stack, LVALUE* llvm_stack_ptr, int var_num, std::map<std::string, Value*>& params, BasicBlock* current_block)
{
    /// var ///
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value;
        get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, i);

        show_llvm_value(&llvm_value);
    }

    /// stack ///
    int stack_num = llvm_stack_ptr - llvm_stack - var_num;

    char buf[128];
    snprintf(buf, 128, "stack num %d", stack_num);

/*
    call_show_str_in_jit(llvm_create_string(buf));

    for(i=0; i<stack_num; i++) {
        LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1-i);

        show_llvm_value(llvm_value);
    }
*/
}

}
