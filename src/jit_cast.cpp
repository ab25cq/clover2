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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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

            dec_stack_ptr(llvm_stack_ptr, 1);

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
            llvm_value.kind = kLVKindInt8;

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
            llvm_value.kind = kLVKindUInt8;

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
            llvm_value.kind = kLVKindInt16;

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
            llvm_value.kind = kLVKindUInt16;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindUInt32;

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
            llvm_value.kind = kLVKindInt64;

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
            llvm_value.kind = kLVKindUInt64;

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

            Function* fun = TheModule->getFunction("un_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindPointer8;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindFloat;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);

            cast_llvm_value_from_inst(&llvm_value, inst);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

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
            result1  = Builder.CreateAlignedLoad(result1,  8);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);

            if_value_is_zero_ret_zero(result2, params, *function, current_block);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindInt32;

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
            llvm_value.kind = kLVKindUInt32;

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
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CREATE_STRING: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int num_string_expression = *(int*)(*pc);
            (*pc) += sizeof(int);

            char* str = CONS_str(constant, offset);

            if(num_string_expression == 0) {
                Function* function = TheModule->getFunction("create_string_object");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(str);
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

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
            else {
                int string_expression_offsets[STRING_EXPRESSION_MAX];

                int i;
                for(i=0; i<num_string_expression; i++) {
                    string_expression_offsets[i] = *(int*)(*pc);
                    (*pc) += sizeof(int);
                }

                Type* element_type = IntegerType::getInt32Ty(TheContext);
                ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                IRBuilder<> builder(&(*function)->getEntryBlock(), (*function)->getEntryBlock().begin());
                Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");

                for(i=0; i<num_string_expression; i++) {
                    Value* lvalue = string_expression_offsets_value;
                    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                    Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                    element_address_value = Builder.CreateCast(Instruction::BitCast, element_address_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i], "element_value"));
                    Builder.CreateAlignedStore(element_value, element_address_value, 4);
                }

                llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_string_expression);

                Function* function = TheModule->getFunction("run_op_string_with_string_expression");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(str);
                params2.push_back(param1);
                
                Value* param2 = string_expression_offsets_value;
                param2 = Builder.CreateCast(Instruction::BitCast, param2, PointerType::get(IntegerType::get(TheContext, 32), 0));

                params2.push_back(param2);

                Value* param3 = ConstantInt::get(TheContext, llvm::APInt(32, num_string_expression, true));
                params2.push_back(param3);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param4 = params[stack_ptr_address_name];
                params2.push_back(param4);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

                /// dec llvm stack pointer ///
                dec_stack_ptr(llvm_stack_ptr, num_string_expression);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            }
            break;

        case OP_CREATE_BUFFER: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            int num_string_expression = *(int*)(*pc);
            (*pc) += sizeof(int);

            char* str = CONS_str(constant, offset);

            if(num_string_expression == 0) {
                Function* function = TheModule->getFunction("create_buffer_object");

                std::vector<Value*> params2;
                Value* param1 = llvm_create_string(str);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)size);
                params2.push_back(param2);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

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
            else {
                int string_expression_offsets[STRING_EXPRESSION_MAX];

                int i;
                for(i=0; i<num_string_expression; i++) {
                    string_expression_offsets[i] = *(int*)(*pc);
                    (*pc) += sizeof(int);
                }

                Type* element_type = IntegerType::getInt32Ty(TheContext);
                ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                IRBuilder<> builder(&(*function)->getEntryBlock(), (*function)->getEntryBlock().begin());
                Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");

                for(i=0; i<num_string_expression; i++) {
                    Value* lvalue = string_expression_offsets_value;
                    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                    Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                    element_address_value = Builder.CreateCast(Instruction::BitCast, element_address_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i], "element_value"));
                    Builder.CreateAlignedStore(element_value, element_address_value, 4);
                }

                llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_string_expression);

                Function* function = TheModule->getFunction("run_op_buffer_with_string_expression");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(str);
                params2.push_back(param1);
                
                Value* param2 = string_expression_offsets_value;
                param2 = Builder.CreateCast(Instruction::BitCast, param2, PointerType::get(IntegerType::get(TheContext, 32), 0));

                params2.push_back(param2);

                Value* param3 = ConstantInt::get(TheContext, llvm::APInt(32, num_string_expression, true));
                params2.push_back(param3);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param4 = params[stack_ptr_address_name];
                params2.push_back(param4);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

                /// dec llvm stack pointer ///
                dec_stack_ptr(llvm_stack_ptr, num_string_expression);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            }
            break;

        case OP_CREATE_PATH: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int num_string_expression = *(int*)(*pc);
            (*pc) += sizeof(int);

            char* str = CONS_str(constant, offset);

            if(num_string_expression == 0) {
                Function* function = TheModule->getFunction("create_path_object");

                std::vector<Value*> params2;
                Value* param1 = llvm_create_string(str);
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

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
            else {
                int string_expression_offsets[STRING_EXPRESSION_MAX];

                int i;
                for(i=0; i<num_string_expression; i++) {
                    string_expression_offsets[i] = *(int*)(*pc);
                    (*pc) += sizeof(int);
                }

                Type* element_type = IntegerType::getInt32Ty(TheContext);
                ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                IRBuilder<> builder(&(*function)->getEntryBlock(), (*function)->getEntryBlock().begin());
                Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");

                for(i=0; i<num_string_expression; i++) {
                    Value* lvalue = string_expression_offsets_value;
                    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                    Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                    element_address_value = Builder.CreateCast(Instruction::BitCast, element_address_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i], "element_value"));
                    Builder.CreateAlignedStore(element_value, element_address_value, 4);
                }

                llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_string_expression);

                Function* function = TheModule->getFunction("run_op_path_with_string_expression");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(str);
                params2.push_back(param1);
                
                Value* param2 = string_expression_offsets_value;
                param2 = Builder.CreateCast(Instruction::BitCast, param2, PointerType::get(IntegerType::get(TheContext, 32), 0));

                params2.push_back(param2);

                Value* param3 = ConstantInt::get(TheContext, llvm::APInt(32, num_string_expression, true));
                params2.push_back(param3);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param4 = params[stack_ptr_address_name];
                params2.push_back(param4);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

                /// dec llvm stack pointer ///
                dec_stack_ptr(llvm_stack_ptr, num_string_expression);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            }
            break;

        case OP_CREATE_ARRAY: {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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

            Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
            params2.push_back(param5);

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1,  8);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);

            if_value_is_zero_ret_zero(result2, params, *function, current_block);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            param1 = llvm_value2.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);

            /// delete vm stack ///
            inc_vm_stack_ptr(params, *current_block, -num_elements);
            }
            break;

        case OP_CREATE_CARRAY : {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

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
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_SORTABLE_CARRAY : {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

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
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_EQUALABLE_CARRAY : {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

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
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_LIST : {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

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
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_SORTALBE_LIST: {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

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
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_EQUALABLE_LIST: {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

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
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_TUPLE: {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements);

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
            result1  = Builder.CreateAlignedLoad(result1,  4);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);

            if_value_is_zero_ret_zero(result2, params, *function, current_block);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_HASH: {
            int num_elements = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset2 = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = offset;
            int class_name_offset2 = offset2;

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_elements*2);

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

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param6);

            Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset2);
            params2.push_back(param7);

            std::string constant_value_name("constant");
            Value* param8 = params[constant_value_name];
            params2.push_back(param8);

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
            llvm_value.kind = kLVKindInt64;

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_elements*2);

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_BLOCK_OBJECT : {
            int code_offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int code_len = *(int*)(*pc);
            (*pc) += sizeof(int);

            int constant_offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int constant_len = *(int*)(*pc);
            (*pc) += sizeof(int);

            int block_var_num = *(int*)(*pc);
            (*pc) += sizeof(int);

            int parent_var_num = *(int*)(*pc);
            (*pc) += sizeof(int);

            int lambda = *(int*)(*pc);
            (*pc) += sizeof(int);

            Function* fun = TheModule->getFunction("run_create_block_object");

            std::vector<Value*> params2;

            std::string stack_ptr_address_name("stack_ptr_address");
            Value* param1 = params[stack_ptr_address_name];
            params2.push_back(param1);

            std::string stack_value_name("stack");
            Value* param2 = params[stack_value_name];
            params2.push_back(param2);

            std::string constant_value_name("constant");
            Value* param3 = params[constant_value_name];
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindObject;

            /// vm stack_ptr to llvm stack ///
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

        case OP_CREATE_REGEX: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL global = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL ignore_case = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL multiline = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL extended = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL dotall = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL anchored = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL dollar_endonly = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL ungreedy = *(int*)(*pc);
            (*pc) += sizeof(int);

            int num_string_expression = *(int*)(*pc);
            (*pc) += sizeof(int);

            char* str = CONS_str(constant, offset);

            if(num_string_expression == 0) {
                Function* function = TheModule->getFunction("create_regex_object");

                std::vector<Value*> params2;
                Value* param1 = llvm_create_string(str);
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
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

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
            else {
                int string_expression_offsets[STRING_EXPRESSION_MAX];

                int i;
                for(i=0; i<num_string_expression; i++) {
                    string_expression_offsets[i] = *(int*)(*pc);
                    (*pc) += sizeof(int);
                }

                Type* element_type = IntegerType::getInt32Ty(TheContext);
                ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                IRBuilder<> builder(&(*function)->getEntryBlock(), (*function)->getEntryBlock().begin());
                Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");

                for(i=0; i<num_string_expression; i++) {
                    Value* lvalue = string_expression_offsets_value;
                    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                    Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                    element_address_value = Builder.CreateCast(Instruction::BitCast, element_address_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i], "element_value"));
                    Builder.CreateAlignedStore(element_value, element_address_value, 4);
                }

                llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_string_expression);

                Function* function = TheModule->getFunction("run_op_regex_with_string_expression");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(str);
                params2.push_back(param1);
                
                Value* param2 = string_expression_offsets_value;
                param2 = Builder.CreateCast(Instruction::BitCast, param2, PointerType::get(IntegerType::get(TheContext, 32), 0));

                params2.push_back(param2);

                Value* param3 = ConstantInt::get(TheContext, llvm::APInt(32, num_string_expression, true));
                params2.push_back(param3);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param4 = params[stack_ptr_address_name];
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)global);
                params2.push_back(param5);
                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)ignore_case);
                params2.push_back(param6);
                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)multiline);
                params2.push_back(param7);
                Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)extended);
                params2.push_back(param8);
                Value* param9 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)dotall);
                params2.push_back(param9);
                Value* param10 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)anchored);
                params2.push_back(param10);
                Value* param11 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)dollar_endonly);
                params2.push_back(param11);
                Value* param12 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)ungreedy);
                params2.push_back(param12);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(function, params2);
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindObject;

                /// dec llvm stack pointer ///
                dec_stack_ptr(llvm_stack_ptr, num_string_expression);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            }
            break;
    }

    return TRUE;
}

}
