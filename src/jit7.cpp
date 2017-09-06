#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code7(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_FLOAT_TO_LONG_CAST:
        case OP_DOUBLE_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_ULONG_CAST:
        case OP_DOUBLE_TO_ULONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_POINTER_TO_LONG_CAST: 
        case OP_POINTER_TO_ULONG_CAST:  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            }
            break;

        case OP_BYTE_TO_FLOAT_CAST:
        case OP_SHORT_TO_FLOAT_CAST:
        case OP_INT_TO_FLOAT_CAST:
        case OP_LONG_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, value->value, Type::getFloatTy(TheContext));
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_FLOAT_CAST:
        case OP_USHORT_TO_FLOAT_CAST:
        case OP_UINT_TO_FLOAT_CAST:
        case OP_ULONG_TO_FLOAT_CAST:
        case OP_CHAR_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, value->value, Type::getFloatTy(TheContext));
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DOUBLE_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPTrunc, value->value, Type::getFloatTy(TheContext));
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BYTE_TO_DOUBLE_CAST:
        case OP_SHORT_TO_DOUBLE_CAST:
        case OP_INT_TO_DOUBLE_CAST:
        case OP_LONG_TO_DOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, value->value, Type::getDoubleTy(TheContext));
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_DOUBLE_CAST:
        case OP_USHORT_TO_DOUBLE_CAST:
        case OP_UINT_TO_DOUBLE_CAST:
        case OP_ULONG_TO_DOUBLE_CAST:
        case OP_CHAR_TO_DOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, value->value, Type::getDoubleTy(TheContext));
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_DOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPExt, value->value, Type::getDoubleTy(TheContext));
            llvm_value.lvar_address_index = value->lvar_address_index;
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
