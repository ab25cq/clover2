#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code4(sByteCode* code, sConst* constant, sCLClass* klass, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_STORE_VALUE_TO_INT_ADDRESS: 
        case OP_STORE_VALUE_TO_UINT_ADDRESS:
        case OP_STORE_VALUE_TO_CHAR_ADDRESS:
        case OP_STORE_VALUE_TO_BOOL_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 32), 0));

            LVALUE value2 = trunc_value(value, 32);

            Builder.CreateAlignedStore(value2.value, address->value, 4);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;

        case OP_STORE_VALUE_TO_OBJECT_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 32), 0));

            LVALUE value2 = trunc_value(value, 32);

            Builder.CreateAlignedStore(value2.value, address->value, 4);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;

        case OP_STORE_VALUE_TO_FLOAT_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(Type::getFloatTy(TheContext), 0));

            LVALUE value2 = trunc_value_to_float_or_double(value, 32);

            Builder.CreateAlignedStore(value2.value, address->value, 4);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;

        case OP_STORE_VALUE_TO_BYTE_ADDRESS:
        case OP_STORE_VALUE_TO_UBYTE_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            LVALUE value2 = trunc_value_to_float_or_double(value, 8);

            Builder.CreateAlignedStore(value2.value, address->value, 1);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;

        case OP_STORE_VALUE_TO_SHORT_ADDRESS:
        case OP_STORE_VALUE_TO_USHORT_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value_to_float_or_double(value, 16);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 16), 0));

            Builder.CreateAlignedStore(value2.value, address->value, 2);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;

        case OP_LOAD_VALUE_FROM_INT_ADDRESS: 
        case OP_LOAD_VALUE_FROM_UINT_ADDRESS: 
        case OP_LOAD_VALUE_FROM_CHAR_ADDRESS: 
        case OP_LOAD_VALUE_FROM_BOOL_ADDRESS: 
        case OP_LOAD_VALUE_FROM_OBJECT_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 32), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 4, "llvm_value");
            llvm_value.kind = kLVKindInt32;
            
            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_FLOAT_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(Type::getFloatTy(TheContext), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 4, "llvm_value");
            llvm_value.kind = kLVKindInt32;
            
            llvm_value.value = Builder.CreateCast(Instruction::BitCast, llvm_value.value, Type::getFloatTy(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_BYTE_ADDRESS: 
        case OP_LOAD_VALUE_FROM_UBYTE_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 1, "llvm_value");
            llvm_value.kind = kLVKindInt8;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_SHORT_ADDRESS:
        case OP_LOAD_VALUE_FROM_USHORT_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 16), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 2, "llvm_value");
            llvm_value.kind = kLVKindInt16;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_LONG_ADDRESS:
        case OP_LOAD_VALUE_FROM_ULONG_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
            llvm_value.kind = kLVKindInt64;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt64Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_POINTER_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
            llvm_value.kind = kLVKindPointer8;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(Type::getDoubleTy(TheContext), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
            llvm_value.kind = kLVKindPointerDouble;

            llvm_value.value = Builder.CreateCast(Instruction::BitCast, llvm_value.value, Type::getDoubleTy(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -1);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_STORE_VALUE_TO_LONG_ADDRESS:
        case OP_STORE_VALUE_TO_ULONG_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value(value, 64);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            Builder.CreateAlignedStore(value2.value, address->value, 8);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;

        case OP_STORE_VALUE_TO_DOUBLE_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(Type::getDoubleTy(TheContext), 0));

            LVALUE value2 = trunc_value_to_float_or_double(value, 64);

            Builder.CreateAlignedStore(value2.value, address->value, 8);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;

        case OP_STORE_VALUE_TO_POINTER_ADDRESS: {
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0));

            LVALUE value2 = trunc_value(value, 8);

            Builder.CreateAlignedStore(value2.value, address->value, 8);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &value2);
            }
            break;
            

        default:
            if(!compile_to_native_code5(code, constant, klass, inst, pc, llvm_stack_ptr, llvm_stack, params, current_block, function, var_num, try_catch_label_name))
            {
                return FALSE;
            }
            break;
    }

    return TRUE;
}

}
