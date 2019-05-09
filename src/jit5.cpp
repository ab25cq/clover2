#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code5(sByteCode* code, sConst* constant, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_BYTE_TO_INT_CAST:
        case OP_SHORT_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_INT_CAST:
        case OP_USHORT_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_INT_CAST:
        case OP_DOUBLE_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_UINT_CAST:
        case OP_DOUBLE_TO_UINT_CAST: 
        case OP_FLOAT_TO_CHAR_CAST:
        case OP_DOUBLE_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_POINTER_TO_INT_CAST:
        case OP_POINTER_TO_UINT_CAST:
        case OP_POINTER_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_BYTE_CAST:
        case OP_DOUBLE_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_UBYTE_CAST:
        case OP_DOUBLE_TO_UBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_POINTER_TO_BYTE_CAST: 
        case OP_POINTER_TO_UBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_SHORT_CAST:
        case OP_DOUBLE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_USHORT_CAST:
        case OP_DOUBLE_TO_USHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BYTE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;
            
        case OP_UBYTE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;
           
        case OP_BYTE_TO_USHORT_CAST:
        case OP_UBYTE_TO_USHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BYTE_TO_LONG_CAST:
        case OP_SHORT_TO_LONG_CAST:
        case OP_INT_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SExt, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_LONG_CAST:
        case OP_USHORT_TO_LONG_CAST:
        case OP_UINT_TO_LONG_CAST:
        case OP_CHAR_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::ZExt, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_ULONG_CAST:
        case OP_DOUBLE_TO_ULONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_POINTER_TO_LONG_CAST: 
        case OP_POINTER_TO_ULONG_CAST:  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DOUBLE_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPTrunc, value->value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BYTE_TO_DOUBLE_CAST:
        case OP_SHORT_TO_DOUBLE_CAST:
        case OP_INT_TO_DOUBLE_CAST:
        case OP_LONG_TO_DOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, value->value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_DOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::FPExt, value->value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LONG_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_long_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 64);

            params2.push_back(value2.value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ULONG_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_ulong_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 64);

            params2.push_back(value2.value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_float_to_string_cast");

            std::vector<Value*> params2;

            params2.push_back(value->value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DOUBLE_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_double_to_string_cast");

            std::vector<Value*> params2;

            params2.push_back(value->value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CHAR_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_char_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_REGEX_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_regex_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BOOL_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_bool_to_string_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            params2.push_back(value2.value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_POINTER_TO_STRING_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_pointer_to_string_cast");

            std::vector<Value*> params2;

            params2.push_back(value->value);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_INTEGER_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value(value, 32);

            Function* fun = TheModule->getFunction("create_integer");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_INTEGER_CAST:
        case OP_DOUBLE_TO_INTEGER_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            value->value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt32Ty(TheContext));
            value->kind = kLVKindInt32;

            Function* fun = TheModule->getFunction("create_integer");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_UINTEGER_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value(value, 32);

            Function* fun = TheModule->getFunction("create_uinteger");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_UINTEGER_CAST:
        case OP_DOUBLE_TO_UINTEGER_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            value->value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt32Ty(TheContext));
            value->kind = kLVKindUInt32;

            Function* fun = TheModule->getFunction("create_uinteger");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_CBYTE_CAST:  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value(value, 8);

            Function* fun = TheModule->getFunction("create_byte");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CBYTE_CAST:
        case OP_DOUBLE_TO_CBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt8Ty(TheContext));
            value2.kind = kLVKindInt8;

            Function* fun = TheModule->getFunction("create_byte");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_CUBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2 = trunc_value(value, 8);

            Function* fun = TheModule->getFunction("create_ubyte");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CUBYTE_CAST:
        case OP_DOUBLE_TO_CUBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt8Ty(TheContext));
            value2.kind = kLVKindUInt8;

            Function* fun = TheModule->getFunction("create_ubyte");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_CSHORT_CAST:  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2 = trunc_value(value, 16);

            Function* fun = TheModule->getFunction("create_short");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CSHORT_CAST:
        case OP_DOUBLE_TO_CSHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt16Ty(TheContext));
            value2.kind = kLVKindInt16;

            Function* fun = TheModule->getFunction("create_short");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_CUSHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2 = trunc_value(value, 16);

            Function* fun = TheModule->getFunction("create_ushort");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CUSHORT_CAST:
        case OP_DOUBLE_TO_CUSHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt16Ty(TheContext));
            value2.kind = kLVKindUInt16;

            Function* fun = TheModule->getFunction("create_ushort");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_CLONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2 = trunc_value(value, 64);

            Function* fun = TheModule->getFunction("create_long");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CLONG_CAST:
        case OP_DOUBLE_TO_CLONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::FPToSI, value->value, Type::getInt64Ty(TheContext));
            value2.kind = kLVKindInt64;

            Function* fun = TheModule->getFunction("create_long");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_BOOL_TO_CULONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2 = trunc_value(value, 64);

            Function* fun = TheModule->getFunction("create_ulong");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CULONG_CAST:
        case OP_DOUBLE_TO_CULONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt64Ty(TheContext));
            value2.kind = kLVKindUInt64;

            Function* fun = TheModule->getFunction("create_ulong");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BYTE_TO_CFLOAT_CAST:
        case OP_SHORT_TO_CFLOAT_CAST:
        case OP_INT_TO_CFLOAT_CAST:
        case OP_LONG_TO_CFLOAT_CAST:
        case OP_BOOL_TO_CFLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::SIToFP, value->value, Type::getFloatTy(TheContext), "fvalue");
            value2.kind = kLVKindFloat;

            Function* fun = TheModule->getFunction("create_float");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_CFLOAT_CAST:
        case OP_USHORT_TO_CFLOAT_CAST:
        case OP_UINT_TO_CFLOAT_CAST:
        case OP_CHAR_TO_CFLOAT_CAST:
        case OP_ULONG_TO_CFLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2.value = Builder.CreateCast(Instruction::UIToFP, value->value, Type::getFloatTy(TheContext), "fvalue");
            value2.kind = kLVKindFloat;

            Function* fun = TheModule->getFunction("create_float");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CFLOAT_CAST:  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value_to_float_or_double(value, 32);

            Function* fun = TheModule->getFunction("create_float");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DOUBLE_TO_CFLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value_to_float_or_double(value, 32);

            Function* fun = TheModule->getFunction("create_float");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BYTE_TO_CDOUBLE_CAST:
        case OP_SHORT_TO_CDOUBLE_CAST:
        case OP_INT_TO_CDOUBLE_CAST:
        case OP_LONG_TO_CDOUBLE_CAST:
        case OP_BOOL_TO_CDOUBLE_CAST:  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            value->value = Builder.CreateCast(Instruction::SIToFP, value->value, Type::getFloatTy(TheContext), "fvalue");
            value->value = Builder.CreateCast(Instruction::FPExt, value->value, Type::getDoubleTy(TheContext), "fvalue");

            Function* fun = TheModule->getFunction("create_double");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_CDOUBLE_CAST:
        case OP_USHORT_TO_CDOUBLE_CAST:
        case OP_UINT_TO_CDOUBLE_CAST:
        case OP_CHAR_TO_CDOUBLE_CAST:
        case OP_ULONG_TO_CDOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            value->value = Builder.CreateCast(Instruction::UIToFP, value->value, Type::getFloatTy(TheContext), "fvalue");
            value->value = Builder.CreateCast(Instruction::FPExt, value->value, Type::getDoubleTy(TheContext), "fvalue");

            Function* fun = TheModule->getFunction("create_double");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CDOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            value->value = Builder.CreateCast(Instruction::FPExt, value->value, Type::getDoubleTy(TheContext), "fvalue");

            Function* fun = TheModule->getFunction("create_double");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DOUBLE_TO_CDOUBLE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

value->value = Builder.CreateCast(Instruction::BitCast, value->value, Type::getDoubleTy(TheContext));

            Function* fun = TheModule->getFunction("create_double");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BYTE_TO_CPOINTER_CAST:
        case OP_SHORT_TO_CPOINTER_CAST:
        case OP_INT_TO_CPOINTER_CAST:
        case OP_LONG_TO_CPOINTER_CAST:
        case OP_BOOL_TO_CPOINTER_CAST:
        case OP_UBYTE_TO_CPOINTER_CAST:
        case OP_USHORT_TO_CPOINTER_CAST:
        case OP_UINT_TO_CPOINTER_CAST:
        case OP_ULONG_TO_CPOINTER_CAST:
        case OP_CHAR_TO_CPOINTER_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            value->value = Builder.CreateCast(Instruction::IntToPtr, value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            Function* fun = TheModule->getFunction("create_pointer");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BUFFER_TO_POINTER_CAST:
            {
            LVALUE* llvm_value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_buffer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE llvm_value2 = trunc_value(llvm_value, 32);

            Value* param1 = llvm_value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value3;
            llvm_value3.value = Builder.CreateCall(fun, params2);
            llvm_value3.kind = kLVKindPointer8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            inc_vm_stack_ptr(params, *current_block, -1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value3);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value3);
            }
            break;

        case OP_POINTER_TO_CPOINTER_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("create_pointer");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Function* fun = TheModule->getFunction("create_bool");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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
        case OP_CHAR_TO_CCHAR_CAST:
        case OP_POINTER_TO_CCHAR_CAST:
        case OP_BOOL_TO_CCHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Function* fun = TheModule->getFunction("create_char");

            std::vector<Value*> params2;

            Value* param1 = value2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_CCHAR_CAST:
        case OP_DOUBLE_TO_CCHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            value->value = Builder.CreateCast(Instruction::FPToUI, value->value, Type::getInt32Ty(TheContext));
            value->kind = kLVKindUInt32;

            Function* fun = TheModule->getFunction("create_char");

            std::vector<Value*> params2;

            Value* param1 = value->value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindObject;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_BYTE_CAST:
        case OP_CBYTE_TO_UBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_USHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_UINT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_ULONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_BYTE_CAST:
        case OP_CUBYTE_TO_UBYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_USHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_INT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_LONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_UINT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_ULONG_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindUInt8;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_SHORT_CAST:
        case OP_CSHORT_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_UINT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_FLOAT_CAST:  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_SHORT_CAST:
        case OP_CUSHORT_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_UINT_CAST :{
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindUInt16;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_INT_CAST : 
        case OP_INTEGER_TO_UINT_CAST :
        case OP_CBOOL_TO_UINT_CAST :
        case OP_INTEGER_TO_CHAR_CAST:
        case OP_CBOOL_TO_CHAR_CAST: 
        case OP_CBOOL_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_BYTE_CAST:
        case OP_CBOOL_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_SHORT_CAST: 
        case OP_CBOOL_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_LONG_CAST : 
        case OP_CBOOL_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_UBYTE_CAST : 
        case OP_CBOOL_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_USHORT_CAST : 
        case OP_CBOOL_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_ULONG_CAST :
        case OP_CBOOL_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_FLOAT_CAST:
        case OP_CBOOL_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_DOUBLE_CAST:
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
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;


        case OP_UINTEGER_TO_BYTE_CAST:
        case OP_CCHAR_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_SHORT_CAST:
        case OP_CCHAR_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_INT_CAST :  
        case OP_CCHAR_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_LONG_CAST : 
        case OP_CCHAR_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_UBYTE_CAST :
        case OP_CCHAR_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_USHORT_CAST :
        case OP_CCHAR_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_UINT_CAST :
        case OP_CCHAR_TO_UINT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_ULONG_CAST :
        case OP_CCHAR_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_CHAR_CAST:
        case OP_CCHAR_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_FLOAT_CAST: 
        case OP_CCHAR_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_DOUBLE_CAST:
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
            llvm_value.kind = kLVKindUInt32;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;
            
        case OP_CLONG_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_UINT_CAST :
        case OP_CLONG_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::SIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_UINT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_CHAR_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CULONG_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindUInt64;

            llvm_value.value = Builder.CreateCast(Instruction::UIToFP, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_LONG_CAST :  {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_UINT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_UINT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CFLOAT_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_float_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindFloat;

            llvm_value.value = Builder.CreateCast(Instruction::FPExt, llvm_value.value, Type::getDoubleTy(TheContext));
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_BYTE_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_SHORT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_INT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_LONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::SExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_UBYTE_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_USHORT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_UINT_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_ULONG_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt64Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindInt32;

            llvm_value.value = Builder.CreateCast(Instruction::ZExt, llvm_value.value, Type::getInt32Ty(TheContext), "value2");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_FLOAT_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_double_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.kind = kLVKindDouble;

            llvm_value.value = Builder.CreateCast(Instruction::FPTrunc, llvm_value.value, Type::getFloatTy(TheContext));
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

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
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
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

            IRBuilder<> builder(&(*function)->getEntryBlock(), (*function)->getEntryBlock().begin());
            Value* param7 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
            params2.push_back(param7);

            Value* result = Builder.CreateCall(fun, params2);

            finish_method_call(result, params, current_block, *function, try_catch_label_name, llvm_stack, var_num);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(param7, 8);
            llvm_value.kind = kLVKindInt64;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ARRAY_TO_CLANG_ARRAY_CAST: {
            LVALUE* array = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_array_to_clang_array_cast");

            std::vector<Value*> params2;

            LVALUE array2 = trunc_value(array, 32);
            Value* param1 = array2.value;
            params2.push_back(param1);

            std::string info_value_name("info");
            Value* param2 = params[info_value_name];
            params2.push_back(param2);

            Value* result = Builder.CreateCall(fun, params2);

            LVALUE llvm_value;
            llvm_value.value = result;
            llvm_value.kind = kLVKindPointer8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLANG_ARRAY_TO_CLANG_POINTER: {
            LVALUE* array = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCast(Instruction::BitCast, array->value, PointerType::get(IntegerType::get(TheContext, 8), 0), "value");
            llvm_value.kind = kLVKindPointer8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BYTE_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBYTE_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_SHORT_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_USHORT_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INT_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINT_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LONG_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ULONG_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue, "ANDAND");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLOAT_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DOUBLE_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_POINTER_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CHAR_TO_BOOL_CAST: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBYTE_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindInt8;

            Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUBYTE_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindUInt8;

            Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CSHORT_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindInt16;

            Value* rvalue = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CUSHORT_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindUInt16;

            Value* rvalue = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INTEGER_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindInt32;

            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UINTEGER_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindUInt32;

            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLONG_TO_BOOL_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_clong_to_long_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindInt64;

            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);

            }
            break;

        case OP_CULONG_TO_BOOL_CAST : {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindInt64;

            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);

            }
            break;

        case OP_CFLOAT_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cfloat_to_float_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindFloat;

            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CDOUBLE_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cdouble_to_double_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindDouble;

            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CPOINTER_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_cpointer_to_pointer_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindPointer8;

            Value* rvalue = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CCHAR_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindInt32;

            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CBOOL_TO_BOOL_CAST: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_integer_to_int_cast");

            std::vector<Value*> params2;

            LVALUE value2;
            value2 = trunc_value(value, 32);

            Value* param1 = value2.value;
            params2.push_back(param1);

            LVALUE lvalue;
            lvalue.value = Builder.CreateCall(fun, params2);
            lvalue.kind = kLVKindInt32;

            Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue.value, rvalue, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        default:
            fprintf(stderr, "invalid inst code(%d)\n", inst);
            exit(1);
    }

    return TRUE;
}

}
