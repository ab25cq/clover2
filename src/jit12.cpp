#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code12(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

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
