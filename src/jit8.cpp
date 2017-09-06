#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code8(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_BYTE_TO_STRING_CAST: 
        case OP_SHORT_TO_STRING_CAST :
        case OP_INT_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_int_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_LONG_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_long_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 64);

            params2.push_back(value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_UBYTE_TO_STRING_CAST :
        case OP_USHORT_TO_STRING_CAST :
        case OP_UINT_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uint_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_ULONG_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_ulong_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 64);

            params2.push_back(value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_FLOAT_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_float_to_string_cast");

            std::vector<Value*> params2;

            params2.push_back(value->value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_DOUBLE_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_double_to_string_cast");

            std::vector<Value*> params2;

            params2.push_back(value->value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_CHAR_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_char_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);
            
            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_REGEX_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_regex_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_BOOL_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_bool_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_POINTER_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_pointer_to_string_cast");

            std::vector<Value*> params2;

            params2.push_back(value->value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;
    }

    return TRUE;
}

}
