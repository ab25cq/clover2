#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code6(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_BYTE_TO_INT_CAST:
        case OP_SHORT_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_INT_CAST:
        case OP_USHORT_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_INT_CAST:
        case OP_DOUBLE_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_UINT_CAST:
        case OP_DOUBLE_TO_UINT_CAST: 
        case OP_FLOAT_TO_CHAR_CAST:
        case OP_DOUBLE_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_POINTER_TO_INT_CAST:
        case OP_POINTER_TO_UINT_CAST:
        case OP_POINTER_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_BYTE_CAST:
        case OP_DOUBLE_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_UBYTE_CAST:
        case OP_DOUBLE_TO_UBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_POINTER_TO_BYTE_CAST: 
        case OP_POINTER_TO_UBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_SHORT_CAST:
        case OP_DOUBLE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_USHORT_CAST:
        case OP_DOUBLE_TO_USHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BYTE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
            
        case OP_UBYTE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
           
        case OP_BYTE_TO_USHORT_CAST:
        case OP_UBYTE_TO_USHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SHORT_TO_USHORT_CAST:
        case OP_USHORT_TO_SHORT_CAST:
            break;

        case OP_POINTER_TO_SHORT_CAST:
        case OP_POINTER_TO_USHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BYTE_TO_LONG_CAST:
        case OP_SHORT_TO_LONG_CAST:
        case OP_INT_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULONG_TO_LONG_CAST:
            break;

        case OP_LONG_TO_ULONG_CAST:
            break;
    }

    return TRUE;
}

}
