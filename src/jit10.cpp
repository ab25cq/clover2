#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code10(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            cast_llvm_value_from_inst(&llvm_value, inst);

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            cast_llvm_value_from_inst(&llvm_value, inst);

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            dec_stack_ptr(llvm_stack_ptr, 1);

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_FLOAT_CAST:
        case OP_CFLOAT_TO_DOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_float_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_FLOAT_CAST:
        case OP_CDOUBLE_TO_DOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_double_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

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

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
    }

    return TRUE;
}

}
