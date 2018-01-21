#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code5(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_STORE_VALUE_TO_INT_ADDRESS: 
        case OP_STORE_VALUE_TO_UINT_ADDRESS:
        case OP_STORE_VALUE_TO_CHAR_ADDRESS:
        case OP_STORE_VALUE_TO_BOOL_ADDRESS:
        case OP_STORE_VALUE_TO_OBJECT_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 32), 0));

            LVALUE value2 = trunc_value(value, 32);

            Builder.CreateAlignedStore(value2.value, address->value, 4);

            dec_stack_ptr(llvm_stack_ptr, 2);

            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            /// lvar of vm stack to lvar of llvm stack ///
            lvar_of_vm_to_lvar_of_llvm(params, *current_block, llvm_stack, var_num);
            }
            break;

        case OP_STORE_VALUE_TO_FLOAT_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(Type::getFloatTy(TheContext), 0));

            LVALUE value2 = trunc_value_to_float_or_double(value, 32);

            Builder.CreateAlignedStore(value2.value, address->value, 4);

            dec_stack_ptr(llvm_stack_ptr, 2);

            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            /// lvar of vm stack to lvar of llvm stack ///
            lvar_of_vm_to_lvar_of_llvm(params, *current_block, llvm_stack, var_num);
            }

        case OP_STORE_VALUE_TO_BYTE_ADDRESS:
        case OP_STORE_VALUE_TO_UBYTE_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            LVALUE value2 = trunc_value_to_float_or_double(value, 8);

            Builder.CreateAlignedStore(value2.value, address->value, 1);

            dec_stack_ptr(llvm_stack_ptr, 2);

            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            /// lvar of vm stack to lvar of llvm stack ///
            lvar_of_vm_to_lvar_of_llvm(params, *current_block, llvm_stack, var_num);
            }
            break;

        case OP_STORE_VALUE_TO_SHORT_ADDRESS:
        case OP_STORE_VALUE_TO_USHORT_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE value2 = trunc_value_to_float_or_double(value, 16);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 16), 0));

            Builder.CreateAlignedStore(value2.value, address->value, 2);

            dec_stack_ptr(llvm_stack_ptr, 2);

            push_value_to_stack_ptr(llvm_stack_ptr, &value2);

            /// lvar of vm stack to lvar of llvm stack ///
            lvar_of_vm_to_lvar_of_llvm(params, *current_block, llvm_stack, var_num);
            }
            break;

        case OP_LOAD_VALUE_FROM_INT_ADDRESS: 
        case OP_LOAD_VALUE_FROM_UINT_ADDRESS: 
        case OP_LOAD_VALUE_FROM_CHAR_ADDRESS: 
        case OP_LOAD_VALUE_FROM_BOOL_ADDRESS: 
        case OP_LOAD_VALUE_FROM_OBJECT_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 32), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 4, "llvm_value");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;
            
            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt32Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_FLOAT_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(Type::getFloatTy(TheContext), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 4, "llvm_value");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;
            
            llvm_value.value = Builder.CreateCast(Instruction::BitCast, llvm_value.value, Type::getFloatTy(TheContext));
            //llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getFloatTy(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_BYTE_ADDRESS: 
        case OP_LOAD_VALUE_FROM_UBYTE_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 1, "llvm_value");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt8Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_SHORT_ADDRESS:
        case OP_LOAD_VALUE_FROM_USHORT_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 16), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 2, "llvm_value");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt16Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_LONG_ADDRESS:
        case OP_LOAD_VALUE_FROM_ULONG_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            llvm_value.value = Builder.CreateCast(Instruction::Trunc, llvm_value.value, Type::getInt64Ty(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_POINTER_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindPointer8;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS: {
            /// lvar of llvm stack to lvar of vm stack ///
            lvar_of_llvm_to_lvar_of_vm(params, *current_block, llvm_stack, var_num);

            /// go ///
            LVALUE* address = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            address->value = Builder.CreateCast(Instruction::BitCast, address->value, PointerType::get(Type::getDoubleTy(TheContext), 0));

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAlignedLoad(address->value, 8, "llvm_value");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindPointerDouble;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            llvm_value.value = Builder.CreateCast(Instruction::BitCast, llvm_value.value, Type::getDoubleTy(TheContext));

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_ELEMENT: {
            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* array = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* element_num = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("load_element");

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

            LVALUE element_num2 = trunc_value(element_num, 32);

            Value* param6 = element_num2.value;
            params2.push_back(param6);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
            result1 = Builder.CreateAlignedLoad(result1,  8);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);

            if_value_is_zero_ret_zero(result2, params, *function, current_block);

            dec_stack_ptr(llvm_stack_ptr, 2);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_STORE_ELEMENT: {
            LVALUE* array = get_stack_ptr_value_from_index(*llvm_stack_ptr, -3);
            LVALUE* element_num = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_store_element");

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

            LVALUE element_num2 = trunc_value(element_num, 32);
            Value* param6 = element_num2.value;
            params2.push_back(param6);

            LVALUE value2 = trunc_value(value, 64);
            Value* param7 = value2.value;
            params2.push_back(param7);

            Value* result = Builder.CreateCall(fun, params2);

            if_value_is_zero_ret_zero(result, params, *function, current_block);

            LVALUE llvm_value = *value;

            dec_stack_ptr(llvm_stack_ptr, 3);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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

            /// lvar of vm stack to lvar of llvm stack ///
            lvar_of_vm_to_lvar_of_llvm(params, *current_block, llvm_stack, var_num);
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

            /// lvar of vm stack to lvar of llvm stack ///
            lvar_of_vm_to_lvar_of_llvm(params, *current_block, llvm_stack, var_num);
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

            /// lvar of vm stack to lvar of llvm stack ///
            lvar_of_vm_to_lvar_of_llvm(params, *current_block, llvm_stack, var_num);
            }
            break;
    }

    return TRUE;
}

}
