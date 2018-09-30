#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code4(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_INVOKE_METHOD: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int method_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            char* class_name = CONS_str(constant, offset);

            sCLClass* klass = get_class_with_load(class_name);

            if(klass == NULL) {
                fprintf(stderr, "class not found(2) (%s)\n", class_name);
                return FALSE;
            }

            if(method_index < 0 || method_index >= klass->mNumMethods) {
                fprintf(stderr, "OP_INVOKE_METHOD: Method not found");
                return FALSE;
            }

            sCLMethod* method = klass->mMethods + method_index;

            /// load class in runtime ///
            Function* load_class_fun = TheModule->getFunction("get_class_with_load_and_initialize_in_jit");
            std::vector<Value*> params2;

            std::string constant_value_name("constant");
            Value* param1 = params[constant_value_name];
            params2.push_back(param1);

            Value* param2 = ConstantInt::get(TheContext, llvm::APInt(32, offset, true));
            params2.push_back(param2);

            Value* klass_value = Builder.CreateCall(load_class_fun, params2);

            if_value_is_null_ret_zero(klass_value, 64, params, *function, current_block);

            /// llvm stack to VM stack ///
            llvm_lvar_to_vm_lvar(llvm_stack, params, *current_block, var_num);

            int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);
            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, real_param_num);

            /// go ///
            Function* fun = TheModule->getFunction("call_invoke_method");

            params2.clear();

            param1 = klass_value;
            params2.push_back(param1);

            param2 = ConstantInt::get(Type::getInt32Ty(TheContext), APInt(32, method_index, true));
            params2.push_back(param2);

            std::string stack_value_name("stack");
            Value* param3 = params[stack_value_name];
            params2.push_back(param3);

            std::string var_num_value_name("var_num");
            Value* param4 = params[var_num_value_name];
            params2.push_back(param4);

            std::string stack_ptr_address_name("stack_ptr_address");
            Value* param5 = params[stack_ptr_address_name];
            params2.push_back(param5);

            std::string info_value_name("info");
            Value* param6 = params[info_value_name];
            params2.push_back(param6);

            Value* result = Builder.CreateCall(fun, params2);

            finish_method_call(result, params, current_block, *function, try_catch_label_name);
            
            /// VM stack to llvm stack ///
            vm_lvar_to_llvm_lvar(llvm_stack, params, *current_block, var_num);

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, real_param_num);

            /// vm stack_ptr to llvm stack ///
            LVALUE llvm_value = get_method_call_result(params, *current_block);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// delete result from vm stack ///
            inc_vm_stack_ptr(params, *current_block, -1);
            }
            break;

        case OP_INVOKE_VIRTUAL_METHOD: {
            int num_real_params = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            /// llvm stack to VM stack ///
            llvm_lvar_to_vm_lvar(llvm_stack, params, *current_block, var_num);

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_real_params);

            /// get object value from llvm stack ///
            LVALUE* object_value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -num_real_params);

            /// go ///
            Function* fun = TheModule->getFunction("call_invoke_virtual_method");

            std::vector<Value*> params2;

            Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
            params2.push_back(param1);

            std::string stack_value_name("stack");
            Value* param2 = params[stack_value_name];
            params2.push_back(param2);

            std::string var_num_value_name("var_num");
            Value* param3 = params[var_num_value_name];
            params2.push_back(param3);

            std::string stack_ptr_address_name("stack_ptr_address");
            Value* param4 = params[stack_ptr_address_name];
            params2.push_back(param4);

            std::string info_value_name("info");
            Value* param5 = params[info_value_name];
            params2.push_back(param5);

            std::string constant_value_name("constant");
            Value* param6 = params[constant_value_name];
            params2.push_back(param6);

            LVALUE object_value2;
            object_value2 = trunc_value(object_value, 32);

            Value* param7 = object_value2.value;
            params2.push_back(param7);

            Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_real_params);
            params2.push_back(param8);

            Value* result = Builder.CreateCall(fun, params2);

            finish_method_call(result, params, current_block, *function, try_catch_label_name);
            
            /// VM stack to llvm stack ///
            vm_lvar_to_llvm_lvar(llvm_stack, params, *current_block, var_num);

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_real_params);

            /// vm stack_ptr to llvm stack ///
            LVALUE llvm_value = get_method_call_result(params, *current_block);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// delete result from vm stack ///
            inc_vm_stack_ptr(params, *current_block, -1);
            }
            break;

        case OP_INVOKE_DYNAMIC_METHOD: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset2 = *(int*)(*pc);
            (*pc) += sizeof(int);

            int num_params = *(int*)(*pc);
            (*pc) += sizeof(int);

            BOOL static_ = *(int*)(*pc);
            (*pc) += sizeof(int);

            int num_method_chains = *(int*)(*pc);
            (*pc) += sizeof(int);

            int max_method_chains = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            int num_real_params = num_params + (static_ ? 0:1);

            /// llvm stack to VM stack ///
            llvm_lvar_to_vm_lvar(llvm_stack, params, *current_block, var_num);

            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_real_params);

            /// go ///
            Function* fun = TheModule->getFunction("call_invoke_dynamic_method");

            std::vector<Value*> params2;

            Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
            params2.push_back(param1);

            Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset2);
            params2.push_back(param2);

            Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_params);
            params2.push_back(param3);

            Value* param4 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)static_);
            params2.push_back(param4);

            Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_method_chains);
            params2.push_back(param5);

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)max_method_chains);
            params2.push_back(param6);

            std::string stack_value_name("stack");
            Value* param7 = params[stack_value_name];
            params2.push_back(param7);

            std::string var_num_value_name("var_num");
            Value* param8 = params[var_num_value_name];
            params2.push_back(param8);

            std::string stack_ptr_address_name("stack_ptr_address");
            Value* param9 = params[stack_ptr_address_name];
            params2.push_back(param9);

            std::string info_value_name("info");
            Value* param10 = params[info_value_name];
            params2.push_back(param10);

            std::string code_value_name("code");
            Value* param11 = params[code_value_name];
            params2.push_back(param11);

            std::string constant_value_name("constant");
            Value* param12 = params[constant_value_name];
            params2.push_back(param12);

            Value* result = Builder.CreateCall(fun, params2);

            finish_method_call(result, params, current_block, *function, try_catch_label_name);

            /// VM stack to llvm stack ///
            vm_lvar_to_llvm_lvar(llvm_stack, params, *current_block, var_num);

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_real_params);

            /// vm stack_ptr to llvm stack ///
            LVALUE llvm_value = get_method_call_result(params, *current_block);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// delete result from vm stack ///
            inc_vm_stack_ptr(params, *current_block, -1);
            }
            break;

        case OP_INVOKE_BLOCK: {
            int num_params = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* obj_value = (*llvm_stack_ptr) - num_params -1;

            int parent_var_num = obj_value->parent_var_num;
            Value* parent_stack = obj_value->parent_stack;
            LVALUE* parent_llvm_stack = obj_value->parent_llvm_stack;

            /// llvm stack to VM stack ///
            parent_llvm_stack_to_parent_vm_stack(parent_stack, parent_llvm_stack, *current_block, parent_var_num);
            llvm_stack_to_vm_stack(*llvm_stack_ptr, params, *current_block, num_params + 1);

            /// go ///
            Function* fun = TheModule->getFunction("invoke_block_in_jit");

            std::vector<Value*> params2;

            Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_params);
            params2.push_back(param1);

            std::string stack_value_name("stack");
            Value* param2 = params[stack_value_name];
            params2.push_back(param2);

            std::string var_num_value_name("var_num");
            Value* param3 = params[var_num_value_name];
            params2.push_back(param3);

            std::string stack_ptr_address_name("stack_ptr_address");
            Value* param4 = params[stack_ptr_address_name];
            params2.push_back(param4);

            std::string info_value_name("info");
            Value* param5 = params[info_value_name];
            params2.push_back(param5);

            Value* result = Builder.CreateCall(fun, params2);

            finish_method_call(result, params, current_block, *function, try_catch_label_name);

            /// parent vm stack for parent llvm stack ///
            parent_vm_stack_to_parent_llvm_stack(parent_stack, parent_llvm_stack, *current_block, parent_var_num);

            /// dec llvm stack pointer ///
            dec_stack_ptr(llvm_stack_ptr, num_params+1);

            /// vm stack_ptr to llvm stack ///
            LVALUE llvm_value = get_method_call_result(params, *current_block);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            /// delete result from vm stack ///
            inc_vm_stack_ptr(params, *current_block, -num_params-1-1);
            }
            break;

        case OP_NEW: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int offset2 = *(int*)(*pc);
            (*pc) += sizeof(int);

            int flg_array = *(int*)(*pc);
            (*pc) += sizeof(int);

            /// load class in runtime ///
            Function* load_class_fun = TheModule->getFunction("get_class_with_load_and_initialize_in_jit");

            std::vector<Value*> params2;

            std::string constant_value_name("constant");
            Value* param1 = params[constant_value_name];
            params2.push_back(param1);

            Value* param2 = ConstantInt::get(TheContext, llvm::APInt(32, offset, true));
            params2.push_back(param2);

            Value* klass_value = Builder.CreateCall(load_class_fun, params2);

            if_value_is_null_ret_zero(klass_value, 64, params, *function, current_block);

            char* type_name = CONS_str(constant, offset2);

            /// go ///
            if(flg_array) {
                LVALUE* array_num_value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

                Function* function = TheModule->getFunction("create_array_object");

                std::vector<Value*> params2;
                params2.push_back(klass_value);

                LVALUE array_num_value2 = trunc_value(array_num_value, 32);

                params2.push_back(array_num_value2.value);

                std::string info_value_name("info");
                Value* param3 = params[info_value_name];
                params2.push_back(param3);

                Value* value = Builder.CreateCall(function, params2);

                LVALUE llvm_value;
                llvm_value.value = value;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindInt32;
                llvm_value.parent_var_num = 0;
                llvm_value.parent_stack = NULL;
                llvm_value.parent_llvm_stack = NULL;

                dec_stack_ptr(llvm_stack_ptr, 1);
                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            else {
                Function* function = TheModule->getFunction("create_object");

                std::vector<Value*> params2;
                params2.push_back(klass_value);

                Value* type_value = llvm_create_string(type_name);
                params2.push_back(type_value);

                std::string info_value_name("info");
                Value* param3 = params[info_value_name];
                params2.push_back(param3);

                Value* value = Builder.CreateCall(function, params2);

                LVALUE llvm_value;
                llvm_value.value = value;
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.kind = kLVKindInt32;
                llvm_value.parent_var_num = 0;
                llvm_value.parent_stack = NULL;
                llvm_value.parent_llvm_stack = NULL;

                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            }
            break;

        case OP_LOAD_FIELD: {
            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* get_field_fun = TheModule->getFunction("get_field_from_object");

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

            LVALUE value2 = trunc_value(value, 32);

            Value* param5; // CLObject
            param5 = Builder.CreateCast(Instruction::Trunc, value2.value, Type::getInt32Ty(TheContext));
            params2.push_back(param5);

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param6);

            Value* result = Builder.CreateCall(get_field_fun, params2);

            Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1,  8);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);
            //if_value_is_zero_ret_zero(result2, params, *function, current_block);
            finish_method_call(result2, params, current_block, *function, try_catch_label_name);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 1);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_FIELD_ADDRESS: {
            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* obj_value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("run_load_field_address");

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

            Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param5);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(obj_value, 32);

            Value* param6 = llvm_value2.value;
            params2.push_back(param6);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1, 8);
            Value* result2 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2, 4);

            //if_value_is_zero_ret_zero(result2, params, *function, current_block);
            finish_method_call(result2, params, current_block, *function, try_catch_label_name);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindPointer8;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 1);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_STORE_FIELD: {
            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            int class_name_offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* obj = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("store_field");

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

            LVALUE obj2 = trunc_value(obj, 32);

            Value* param5 = obj2.value;
            params2.push_back(param5);

            LVALUE value2;
            value2 = trunc_value(value, 64);

            Value* param6 = value2.value;
            params2.push_back(param6);

            Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param7);

            Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_name_offset);
            params2.push_back(param8);

            std::string constant_value_name("constant");
            Value* param9 = params[constant_value_name];
            params2.push_back(param9);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1,  8);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);
            //if_value_is_zero_ret_zero(result2, params, *function, current_block);
            finish_method_call(result2, params, current_block, *function, try_catch_label_name);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_STORE_FIELD_OF_BUFFER: {
            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* obj = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("store_field_of_buffer");

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

            LVALUE obj2 = trunc_value(obj, 32);

            Value* param5 = obj2.value;
            params2.push_back(param5);

            LVALUE value2;
            value2 = trunc_value(value, 64);

            Value* param6 = value2.value;
            params2.push_back(param6);

            Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param7);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1,  8);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);
            //if_value_is_zero_ret_zero(result2, params, *function, current_block);
            finish_method_call(result2, params, current_block, *function, try_catch_label_name);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_CLASS_FIELD: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            Function* fun = TheModule->getFunction("load_class_field");

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

            Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param5);

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1,  8);
            Value* result2 = Builder.CreateStructGEP(gCLValueAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2,  4);

            //if_value_is_zero_ret_zero(result2, params, *function, current_block);
            finish_method_call(result2, params, current_block, *function, try_catch_label_name);

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

        case OP_LOAD_CLASS_FIELD_ADDRESS: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            Function* fun = TheModule->getFunction("run_load_class_field_address");

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

            Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param5);

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

            Value* result = Builder.CreateCall(fun, params2);

            Value* result1 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 0);
            result1  = Builder.CreateAlignedLoad(result1, 8);
            Value* result2 = Builder.CreateStructGEP(gPointerAndBoolStruct, result, 1);
            result2  = Builder.CreateAlignedLoad(result2, 4);

            //if_value_is_zero_ret_zero(result2, params, *function, current_block);
            finish_method_call(result2, params, current_block, *function, try_catch_label_name);

            LVALUE llvm_value;
            llvm_value.value = result1;
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindPointer8;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_STORE_CLASS_FIELD: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* llvm_value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("store_class_field");

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

            Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param5);

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

            LVALUE value2;
            value2 = trunc_value(llvm_value, 64);

            Value* param8 = value2.value;
            params2.push_back(param8);

            Value* result = Builder.CreateCall(fun, params2);

            //if_value_is_zero_ret_zero(result, params, *function, current_block);
            finish_method_call(result, params, current_block, *function, try_catch_label_name);
            }
            break;

        case OP_STORE_CLASS_FIELD_OF_BUFFER: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            int field_index = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE* llvm_value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            Function* fun = TheModule->getFunction("store_class_field_of_buffer");

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

            Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
            params2.push_back(param5);

            Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
            params2.push_back(param6);

            std::string constant_value_name("constant");
            Value* param7 = params[constant_value_name];
            params2.push_back(param7);

            LVALUE value2;
            value2 = trunc_value(llvm_value, 64);

            Value* param8 = value2.value;
            params2.push_back(param8);

            Value* result = Builder.CreateCall(fun, params2);

            //if_value_is_zero_ret_zero(result, params, *function, current_block);
            finish_method_call(result, params, current_block, *function, try_catch_label_name);
            }
            break;
    }

    return TRUE;
}

}
