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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindUInt32;

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
            llvm_value.kind = kLVKindUInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindUInt32;

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
            llvm_value.kind = kLVKindInt32;

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
        case OP_CHAR_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindUInt8;

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
            llvm_value.kind = kLVKindInt8;

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
            llvm_value.kind = kLVKindUInt8;

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
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_INT_TO_SHORT_CAST:
        case OP_UINT_TO_SHORT_CAST:
        case OP_LONG_TO_SHORT_CAST:
        case OP_ULONG_TO_SHORT_CAST:
        case OP_CHAR_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::Trunc, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindUInt16;

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
            llvm_value.kind = kLVKindInt16;

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
            llvm_value.kind = kLVKindUInt16;

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
            llvm_value.kind = kLVKindInt16;

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
            llvm_value.kind = kLVKindInt16;

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
            llvm_value.kind = kLVKindUInt16;

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
            llvm_value.kind = kLVKindInt16;

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
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_LONG_CAST:
        case OP_USHORT_TO_LONG_CAST:
        case OP_UINT_TO_LONG_CAST:
        case OP_CHAR_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULONG_TO_LONG_CAST:
            break;

        case OP_LONG_TO_ULONG_CAST:
            break;

        case OP_FLOAT_TO_LONG_CAST:
        case OP_DOUBLE_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.lvar_address_index = value->lvar_address_index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

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
            llvm_value.kind = kLVKindUInt64;

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
            llvm_value.kind = kLVKindInt64;

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
            llvm_value.kind = kLVKindFloat;

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
            llvm_value.kind = kLVKindFloat;

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
            llvm_value.kind = kLVKindFloat;

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
            llvm_value.kind = kLVKindDouble;

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
            llvm_value.kind = kLVKindDouble;

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
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindObject;

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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_integer");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_uinteger");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_byte");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_ubyte");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");


            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_short");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_ushort");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_long");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_ulong");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_float");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            llvm_value.float_value = FALSE;
            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_double");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_pointer");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_bool");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
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
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            cast_llvm_value_from_inst(value, inst);

            Function* fun = TheModule->getFunction("create_char");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;
    }

    return TRUE;
}

}
