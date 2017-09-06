#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code11(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_ARRAY_TO_CARRAY_CAST: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            char* class_name = CONS_str(constant, offset);

            LVALUE* array = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

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

            LVALUE array2 = trunc_value(array, 32);
            Value* param5 = array2.value;
            params2.push_back(param5);

            Value* param6 = llvm_create_string(class_name);
            params2.push_back(param6);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1,  4);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);

            if_value_is_zero_ret_zero(result2, params, *function, current_block);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);
            }
            break;

        case OP_GET_ARRAY_LENGTH: {
            LVALUE* array_ = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_array_length");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(array_, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);
            }
            break;

        case OP_GET_REGEX_GLOBAL: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_global");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_GET_REGEX_IGNORE_CASE: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_ignorecase");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_GET_REGEX_MULTILINE: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_multiline");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_GET_REGEX_EXTENDED: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_extended");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_GET_REGEX_DOTALL: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_dotall");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_GET_REGEX_ANCHORED: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_anchored");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_GET_REGEX_DOLLAR_ENDONLY: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_dollar_endonly");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;


        case OP_GET_REGEX_UNGREEDY: {
            LVALUE* regex = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("get_regex_ungreedy");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(regex, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CHAR_UPPERCASE: {
            LVALUE* c = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("char_uppercase");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(c, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CHAR_LOWERCASE: {
            LVALUE* c = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("char_lowercase");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(c, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
    }

    return TRUE;
}

}
