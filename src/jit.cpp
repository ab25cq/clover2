#include "jit_common.hpp"

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule;
std::unique_ptr<FunctionPassManager> TheFPM;
std::map<std::string, BasicBlock*> TheLabels;
FunctionAnalysisManager TheFAM;

GlobalVariable* gSigIntValue;

extern "C"
{

void jit_init()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
}

void jit_final()
{
}



//////////////////////////////////////////////////////////////
// LLVM core
//////////////////////////////////////////////////////////////
Function* create_llvm_function(const std::string& name)
{
    std::vector<Type *> params;

    Type* param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    params.push_back(param1_type);
    Type* param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    params.push_back(param2_type);
    Type* param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    params.push_back(param3_type);
    Type* param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    params.push_back(param4_type);
    Type* param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    params.push_back(param5_type);
    Type* param6_type = IntegerType::get(TheContext, 32);
    params.push_back(param6_type);
    Type* param7_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    params.push_back(param7_type);
    Type* param8_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    params.push_back(param8_type);
    Type* param9_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    params.push_back(param9_type);
    Type* param10_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    params.push_back(param10_type);

    Type* result_type = IntegerType::get(TheContext, 32);
    FunctionType* function_type = FunctionType::get(result_type, params, false);

    Function* function = Function::Create(function_type, Function::ExternalLinkage, name, TheModule);
    std::vector<std::string> args;

    std::string stack_ptr_name("stack_ptr");
    args.push_back(stack_ptr_name);
    std::string lvar_name("lvar");
    args.push_back(lvar_name);
    std::string info_name("info");
    args.push_back(info_name);
    std::string stack_name("stack");
    args.push_back(stack_name);
    std::string stack_ptr_address_name("stack_ptr_address");
    args.push_back(stack_ptr_address_name);
    std::string var_num_name("var_num");
    args.push_back(var_num_name);
    std::string constant_name("constant");
    args.push_back(constant_name);
    std::string code_name("code");
    args.push_back(code_name);
    std::string global_stack_ptr_address_name("global_stack_ptr_address");
    args.push_back(global_stack_ptr_address_name);
    std::string stack_plus_var_num_name("stack_plus_var_num");
    args.push_back(stack_plus_var_num_name);

    unsigned index = 0;
    for (auto &arg : function->args()) {
        arg.setName(args[index++]);
    }

    return function;
}

BOOL compile_to_native_code(sByteCode* code, sConst* constant, sCLClass* klass, int var_num, int real_param_num, char* func_path, BOOL closure, BOOL block)
{
    char* try_catch_label_name = NULL;

    std::string func_name(func_path);
    Function* function = create_llvm_function(func_name);

    // Create a new basic block to start insertion into.
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(current_block);
  
    char* pc = code->mCodes;

    std::map<std::string, Value *> params;
    for(auto &param : function->args()) {
        params[param.getName()] = &param;
    }

    /// Stack to LLVM ///
    LVALUE llvm_stack[CLOVER_STACK_SIZE];
    memset(llvm_stack, 0, sizeof(LVALUE)*CLOVER_STACK_SIZE);

    LVALUE* llvm_stack_ptr = llvm_stack + var_num;

/*
    /// parametor from VM stack ptr ///
    int i;
    for(i=0; i<real_param_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 64);

        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }

    /// clear local variable ///
    for(i=real_param_num; i<var_num; i++) {
        LVALUE llvm_value;
        llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
        llvm_value.kind = kLVKindInt64;

        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }
*/

    int num_cond_jump = 0;
    char* cond_jump_labels[MAX_COND_JUMP];
    BasicBlock* entry_condends[MAX_COND_JUMP];

    int num_cond_not_jump = 0;
    char* cond_not_jump_labels[MAX_COND_JUMP];
    BasicBlock* entry_condnotends[MAX_COND_JUMP];

    while(pc - code->mCodes < code->mLen) {
        int k;
        for(k=num_cond_jump-1; k>= 0; k--) {
            if(pc == cond_jump_labels[k]) {
                Builder.CreateBr(entry_condends[k]);
                Builder.SetInsertPoint(entry_condends[k]);
                current_block = entry_condends[k];

                int j;
                for(j=k; j<num_cond_jump-1; j++) {
                    cond_jump_labels[j] = cond_jump_labels[j+1];
                    entry_condends[j] = entry_condends[j+1];
                }
                cond_jump_labels[j] = NULL;
                entry_condends[j] = NULL;
                num_cond_jump--;
            }
        }
        for(k=num_cond_not_jump-1; k>=0; k--) {
            if(pc == cond_not_jump_labels[k]) {
                Builder.CreateBr(entry_condnotends[k]);
                Builder.SetInsertPoint(entry_condnotends[k]);
                current_block = entry_condnotends[k];

                int j;
                for(j=k; j<num_cond_not_jump-1; j++) {
                    cond_not_jump_labels[j] = cond_not_jump_labels[j+1];
                    entry_condnotends[j] = entry_condnotends[j+1];
                }
                cond_not_jump_labels[j] = NULL;
                entry_condnotends[j] = NULL;
                num_cond_not_jump--;
            }
        }

        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);
//show_inst(inst);
//show_int_value_on_runtime(inst);

        switch(inst) {
            case OP_NOP:
                break;

            case OP_POP:
                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);
                break;

            case OP_POP_N:
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    dec_stack_ptr(&llvm_stack_ptr, value);
                    inc_vm_stack_ptr(params, current_block, -value);
                }
                break;


            case OP_REVERSE: {
                LVALUE llvm_value = *get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE llvm_value2 = *get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                
                dec_stack_ptr(&llvm_stack_ptr, 1);
                dec_stack_ptr(&llvm_stack_ptr, 1);

                inc_vm_stack_ptr(params, current_block, -2);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value2);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_THROW: {
                std::string stack_plus_var_num_param_name("stack_plus_var_num");
                Value* stack_value = params[stack_plus_var_num_param_name];

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(llvm_value, 64);

                Builder.CreateAlignedStore(llvm_value2.value, stack_value, 8);

                Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object");

                LVALUE llvm_value3;
                llvm_value3 = trunc_value(llvm_value, 32);

                std::vector<Value*> params2;

                Value* param1 = llvm_value3.value;
                params2.push_back(param1);

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                (void)Builder.CreateCall(entry_exception_object_fun, params2);

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
                Builder.CreateRet(ret_value);

                current_block = BasicBlock::Create(TheContext, "entry_after_throw", function);
                Builder.SetInsertPoint(current_block);
                }
                break;

            case OP_TRY: {
                int try_offset = *(int*)pc;
                pc += sizeof(int);

                int catch_label_name_offset = *(int*)pc;
                pc += sizeof(int);
                
                try_catch_label_name = CONS_str(constant, catch_label_name_offset);

                Function* try_fun = TheModule->getFunction("try_function");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Value* catch_label_name_offset_value  = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)catch_label_name_offset);
                params2.push_back(catch_label_name_offset_value);

                Value* try_offset_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)try_offset);
                params2.push_back(try_offset_value);

                std::string code_value_name("code");
                Value* code_value = params[code_value_name];
                params2.push_back(code_value);

                std::string constant_value_name("constant");
                Value* constant_value = params[constant_value_name];
                params2.push_back(constant_value);

                (void)Builder.CreateCall(try_fun, params2);
                }
                break;

            case OP_TRY_END: {
                try_catch_label_name = NULL;

                Function* try_end_fun = TheModule->getFunction("try_end_function");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Value* catch_label_name_offset_value  = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
                params2.push_back(catch_label_name_offset_value);

                Value* try_offset_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
                params2.push_back(try_offset_value);

                std::string code_value_name("code");
                Value* code_value = params[code_value_name];
                params2.push_back(code_value);

                std::string constant_value_name("constant");
                Value* constant_value = params[constant_value_name];
                params2.push_back(constant_value);

                (void)Builder.CreateCall(try_end_fun, params2);
                }
                break;

            case OP_CATCH_POP: {
                inc_vm_stack_ptr(params, current_block, -1);
                }
                break;

            case OP_CATCH_STORE: {
                int index = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 64);
                trunc_variable(&llvm_value, 4);

                store_value_to_lvar_with_offset(params, current_block, index, &llvm_value);
                }
                break;

            case OP_CATCH_END:
                break;

            case OP_DUPE: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, llvm_value);
                }
                break;

            case OP_LDCINT: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
                llvm_value.kind = kLVKindConstantInt32;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCBYTE: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(8, value, true)); 
                llvm_value.kind = kLVKindConstantInt8;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCUBYTE: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(8, value, false)); 
                llvm_value.kind = kLVKindConstantUInt8;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCSHORT: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(16, value, true)); 
                llvm_value.kind = kLVKindConstantInt16;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCUSHORT: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(16, value, false)); 
                llvm_value.kind = kLVKindConstantUInt16;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCUINT: {
                unsigned int value = *(unsigned int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, false)); 
                llvm_value.kind = kLVKindConstantUInt32;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCLONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                clint64 lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, true)); 
                llvm_value.kind = kLVKindConstantInt64;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCULONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                clint64 lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, false)); 
                llvm_value.kind = kLVKindConstantUInt64;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCPOINTER: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                clint64 lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, false)); 
                llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));
                llvm_value.kind = kLVKindPointer64;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCFLOAT: {
                float value1 = *(float*)pc;
                pc += sizeof(float);

                LVALUE llvm_value;
                llvm_value.value = ConstantFP::get(TheContext, llvm::APFloat(value1)); 
                llvm_value.kind = kLVKindConstantFloat;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCDOUBLE: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                double lvalue;

                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                LVALUE llvm_value;
                llvm_value.value = ConstantFP::get(TheContext, llvm::APFloat(lvalue)); 
                llvm_value.kind = kLVKindConstantDouble;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;


            case OP_ANDAND: {
                LVALUE lvalue = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                LVALUE rvalue = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAnd(lvalue.value, rvalue.value, "ANDAND");
                llvm_value.kind = kLVKindInt1;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                inc_vm_stack_ptr(params, current_block, -2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_OROR: {
                LVALUE lvalue = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                LVALUE rvalue = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateOr(lvalue.value, rvalue.value, "OROR");
                llvm_value.kind = kLVKindInt1;

                dec_stack_ptr(&llvm_stack_ptr, 2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                inc_vm_stack_ptr(params, current_block, -2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_INC_ANDAND_OROR_ARRAY: {
                Function* inc_andand_oror_value_fun = TheModule->getFunction("inc_andand_oror_array");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* param1 = params[info_value_name];
                params2.push_back(param1);

                Builder.CreateCall(inc_andand_oror_value_fun, params2);
                }
                break;

            case OP_DEC_ANDAND_OROR_ARRAY: {
                Function* dec_andand_oror_array_fun = TheModule->getFunction("dec_andand_oror_array");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* param1 = params[info_value_name];
                params2.push_back(param1);

                Builder.CreateCall(dec_andand_oror_array_fun, params2);
                }
                break;

            case OP_STORE_ANDAND_OROR_VALUE_LEFT: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value = trunc_value(value, 32);

                Function* set_andand_oror_left_value_fun = TheModule->getFunction("set_andand_oror_left_value");

                std::vector<Value*> params2;

                Value* param1 = llvm_value.value;
                params2.push_back(param1);

                std::string info_value_name("info");
                Value* param2 = params[info_value_name];
                params2.push_back(param2);

                Builder.CreateCall(set_andand_oror_left_value_fun, params2);

                inc_vm_stack_ptr(params, current_block, -1);
                dec_stack_ptr(&llvm_stack_ptr, 1);
                }
                break;

            case OP_STORE_ANDAND_OROR_VALUE_RIGHT: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value;
                llvm_value = trunc_value(value, 32);

                Function* set_andand_oror_right_value_fun = TheModule->getFunction("set_andand_oror_right_value");

                std::vector<Value*> params2;

                Value* param1 = llvm_value.value;
                params2.push_back(param1);

                std::string info_value_name("info");
                Value* param2 = params[info_value_name];
                params2.push_back(param2);

                Builder.CreateCall(set_andand_oror_right_value_fun, params2);

                inc_vm_stack_ptr(params, current_block, -1);
                dec_stack_ptr(&llvm_stack_ptr, 1);
                }
                break;

            case OP_GET_ANDAND_OROR_RESULT_LEFT: {
                Function* get_andand_oror_left_value_fun = TheModule->getFunction("get_andand_oror_left_value");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* param1 = params[info_value_name];
                params2.push_back(param1);

                Value* value = Builder.CreateCall(get_andand_oror_left_value_fun, params2);

                LVALUE llvm_value;
                llvm_value.value = value;
                llvm_value.kind = kLVKindInt32;

                trunc_variable(&llvm_value, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_ANDAND_OROR_RESULT_RIGHT: {
                Function* get_andand_oror_right_value_fun = TheModule->getFunction("get_andand_oror_right_value");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* param1 = params[info_value_name];
                params2.push_back(param1);

                Value* value = Builder.CreateCall(get_andand_oror_right_value_fun, params2);

                LVALUE llvm_value;
                llvm_value.value = value;
                llvm_value.kind = kLVKindInt32;

                trunc_variable(&llvm_value, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCNULL: {
                int value = 0;

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
                llvm_value.kind = kLVKindConstantInt32;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LDCBOOL: {
                int value = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
                llvm_value.kind = kLVKindConstantInt32;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);

                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_RETURN: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(llvm_value, 64);

                std::string stack_param_name("stack");
                Value* stack_value = params[stack_param_name];

                std::string var_num_param_name("var_num");
                Value* var_num_value = params[var_num_param_name];

                Value* lvalue = stack_value;
                Value* rvalue = var_num_value;
                Value* store_address_value = Builder.CreateGEP(lvalue, rvalue, "store_address_value");

                Builder.CreateAlignedStore(llvm_value2.value, store_address_value, 8);

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));
                Builder.CreateRet(ret_value);

                BasicBlock* entry_after_return = BasicBlock::Create(TheContext, "entry_after_return", function);
                Builder.SetInsertPoint(entry_after_return);
                current_block = entry_after_return;
                }
                break;

            case OP_HEAD_OF_EXPRESSION: {
                Value* sig_int_value = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                Builder.CreateStore(sig_int_value, gSigIntValue);
                }
                break;

            case OP_COND_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                LVALUE* conditional_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                BasicBlock* cond_jump_then_block = BasicBlock::Create(TheContext, "cond_jump_then", function);
                entry_condends[num_cond_jump] = BasicBlock::Create(TheContext, "entry_condend", function);

                LVALUE llvm_value;
                llvm_value = trunc_value(conditional_value, 1);

                inc_vm_stack_ptr(params, current_block, -1);

                Builder.CreateCondBr(llvm_value.value, entry_condends[num_cond_jump], cond_jump_then_block);

                Builder.SetInsertPoint(cond_jump_then_block);

                current_block = cond_jump_then_block;

                cond_jump_labels[num_cond_jump] = pc + jump_value;
                num_cond_jump++;

                if(num_cond_jump >= MAX_COND_JUMP) {
                    fprintf(stderr, "overflow number of condjump\n");
                    return FALSE;
                }

                dec_stack_ptr(&llvm_stack_ptr, 1);
                }
                break;

            case OP_JS_IF: {
                /// nothing to do, this is for JS compile
                }
                break;

            case OP_JS_ELSE_IF: {
                /// nothing to do, this is for JS compile
                }
                break;

            case OP_JS_ELSE: {
                /// nothing to do, this is for JS compile
                }
                break;

            case OP_JS_BLOCK_CLOSE: {
                /// nothing to do, this is for JS compile
                }
                break;

            case OP_JS_LOOP: {
                /// nothing to do, this opecode is for JS Compile
                }
                break;

            case OP_JS_BREAK: {
                /// nothing to do, this opecode is for JS Compile
                }
                break;

            case OP_COND_NOT_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                LVALUE* conditional_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                BasicBlock* cond_not_jump_then_block = BasicBlock::Create(TheContext, "cond_not_jump_then", function);
                entry_condnotends[num_cond_not_jump] = BasicBlock::Create(TheContext, "entry_condnotend", function);
                LVALUE llvm_value;
                llvm_value = trunc_value(conditional_value, 1);

                inc_vm_stack_ptr(params, current_block, -1);

                Builder.CreateCondBr(llvm_value.value, cond_not_jump_then_block, entry_condnotends[num_cond_not_jump]);

                Builder.SetInsertPoint(cond_not_jump_then_block);

                current_block = cond_not_jump_then_block;

                cond_not_jump_labels[num_cond_not_jump] = pc + jump_value;
                num_cond_not_jump++;

                if(num_cond_not_jump >= MAX_COND_JUMP) {
                    fprintf(stderr, "overflow number of condnotjump\n");
                    return FALSE;
                }

                dec_stack_ptr(&llvm_stack_ptr, 1);
                }
                break;

            case OP_GOTO: {
                //int jump_value = *(int*)pc;
                pc += sizeof(int);

                int label_offset = *(int*)pc;
                pc += sizeof(int);

                char* label_name = CONS_str(constant, label_offset);
                std::string label_name_string(label_name);

                BasicBlock* label = TheLabels[label_name_string];
                if(label == nullptr) {
                    label = BasicBlock::Create(TheContext, label_name, function);
                    TheLabels[label_name_string] = label;
                }

                Builder.CreateBr(label);

                Builder.SetInsertPoint(label);
                current_block = label;
                
                BasicBlock* entry_after_goto = BasicBlock::Create(TheContext, "entry_after_goto", function);
                Builder.SetInsertPoint(entry_after_goto);
                current_block = entry_after_goto;
                }
                break;

            case OP_LABEL: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* label_name = CONS_str(constant, offset);

                std::string label_name_string(label_name);

                BasicBlock* label = TheLabels[label_name_string];
                if(label == nullptr) {
                    label = BasicBlock::Create(TheContext, label_name, function);
                    TheLabels[label_name_string] = label;
                }

                Builder.CreateBr(label);
                Builder.SetInsertPoint(label);
                current_block = label;
                }
                break;

            case OP_STORE_VALUE_TO_GLOBAL: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                /// trunc ///
                LVALUE llvm_value;
                llvm_value = trunc_value(value, 64);

                /// fun ///
                Function* fun = TheModule->getFunction("push_value_to_global_stack");

                std::vector<Value*> params2;

                Value* param1 = llvm_value.value;
                params2.push_back(param1);

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                (void)Builder.CreateCall(fun, params2);

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);
                }
                break;

            case OP_POP_VALUE_FROM_GLOBAL: {
                int size = *(int*)pc;
                pc += sizeof(int);

                /// load from global stack ptr ///
                std::string global_stack_ptr_address_name("global_stack_ptr_address");
                Value* global_stack_ptr_address_value = params[global_stack_ptr_address_name];

                Value* loaded_global_stack_ptr_address_value = Builder.CreateAlignedLoad(global_stack_ptr_address_value, 8, "loaded_global_stack_ptr_address");

                int index = 1;

                Value* lvalue = loaded_global_stack_ptr_address_value;
                Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, -index, true));
                Value* dec_ptr_value = Builder.CreateGEP(lvalue, rvalue, "dec_ptr_value");

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(dec_ptr_value, 8, "value");
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2 = llvm_value;
                trunc_variable(&llvm_value2, size);

                /// dec global stack ptr ///
                Builder.CreateAlignedStore(dec_ptr_value, global_stack_ptr_address_value, 8);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_SIGINT: {
                Value* sig_int_value = Builder.CreateAlignedLoad(gSigIntValue, 4, "sig_int_value");

                Value* value = Builder.CreateCast(Instruction::Trunc, sig_int_value, Type::getInt1Ty(TheContext));

                BasicBlock* then_block = BasicBlock::Create(TheContext, "sigint_then_block", function);
                BasicBlock* else_block = BasicBlock::Create(TheContext, "entry_after_sigint", function);

                Builder.CreateCondBr(value, then_block, else_block);

                Builder.SetInsertPoint(then_block);

                Value* llvm_value1 = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                Builder.CreateStore(llvm_value1, gSigIntValue);

                call_entry_exception_object_with_class_name2(params, (char*)"Exception", (char*)"Signal Interrupt");

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
                Builder.CreateRet(ret_value);

                Builder.SetInsertPoint(else_block);
                current_block = else_block;
                }
                break;

            case OP_MARK_SOURCE_CODE_POSITION: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int sline = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("mark_source_position");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Value* sname_value = llvm_create_string(sname);
                params2.push_back(sname_value);

                Value* sline_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)sline);
                params2.push_back(sline_value);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_MARK_SOURCE_CODE_POSITION2: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int sline = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("mark_source_position2");

                std::vector<Value*> params2;

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];
                params2.push_back(vminfo_value);

                Value* sname_value = llvm_create_string(sname);
                params2.push_back(sname_value);

                Value* sline_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)sline);
                params2.push_back(sline_value);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_STORE: {
                int index = *(int*)pc;
                pc += sizeof(int);

                //BOOL value_is_object = *(int*)pc;
                pc += sizeof(int);

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                store_value_to_lvar_with_offset(params, current_block, index, llvm_value);
                }
                break;

            case OP_STORE_TO_BUFFER: {
                int index = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value = load_value_from_lvar_with_offset(params, current_block, index);

                LVALUE* llvm_value2 = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value_32;
                llvm_value_32 = trunc_value(&llvm_value, 32);

                LVALUE llvm_value2_64;
                llvm_value2_64 = trunc_value(llvm_value2, 64);

                Value* llvm_value2_pointer = Builder.CreateCast(Instruction::BitCast, llvm_value2->value, PointerType::get(IntegerType::get(TheContext, 8), 0));

                Function* fun = TheModule->getFunction("run_store_to_buffer");

                std::vector<Value*> params2;

                Value* param1 = llvm_value_32.value;
                params2.push_back(param1);

                Value* param2 = llvm_value2_pointer;
                params2.push_back(param2);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param3 = params[stack_ptr_address_name];
                params2.push_back(param3);

                std::string stack_value_name("stack");
                Value* param4 = params[stack_value_name];
                params2.push_back(param4);

                std::string var_num_value_name("var_num");
                Value* param5 = params[var_num_value_name];
                params2.push_back(param5);

                std::string info_value_name("info");
                Value* param6 = params[info_value_name];
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);
                }
                break;


            case OP_LOAD: {
                int index = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                LVALUE llvm_value = load_value_from_lvar_with_offset(params, current_block, index);

                trunc_variable(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LOAD_FIELD_ADDRESS: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                LVALUE* obj_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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

                LVALUE object_value2;
                object_value2 = trunc_value(obj_value, 32);

                Value* param6 = object_value2.value;
                params2.push_back(param6);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param7 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                Value* address_value = Builder.CreateAlignedLoad(param7, 8);

                LVALUE llvm_value;
                llvm_value.value = address_value;
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2.value = Builder.CreateCast(Instruction::IntToPtr, address_value, PointerType::get(IntegerType::get(TheContext, 8), 0));
                llvm_value2.kind = kLVKindPointer8;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_INVOKE_METHOD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int method_index = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load(class_name, FALSE);

                if(klass == NULL) {
                    fprintf(stderr, "class not found(2) (%s)\n", class_name);
                    return FALSE;
                }

                if(method_index < 0 || method_index >= klass->mNumMethods) {
                    fprintf(stderr, "OP_INVOKE_METHOD: Method not found");
                    return FALSE;
                }

                sCLMethod* method = klass->mMethods + method_index;

//printf("class_name2 %s %s\n", class_name, METHOD_NAME2(klass, method));
//show_str_value_on_runtime(METHOD_NAME2(klass, method));

                /// load class in runtime ///
                char* class_name2 = CONS_str(constant, offset);
                
                Function* load_class_fun = TheModule->getFunction("get_class_with_load_and_initialize");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(class_name2);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), APInt(32, 0, true));
                params2.push_back(param2);

                Value* klass_value = Builder.CreateCall(load_class_fun, params2);

                if_value_is_null_ret_zero(klass_value, 64, params, function, &current_block, llvm_stack, var_num);

                int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);

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

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);
                
                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, real_param_num);

                /// vm stack_ptr to llvm stack ///
                LVALUE llvm_value = get_method_call_result(params, current_block);

                trunc_variable(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INVOKE_VIRTUAL_METHOD: {
                int num_real_params = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                int class_method = *(int*)pc;
                pc += sizeof(int);

                int native_method = *(int*)pc;
                pc += sizeof(int);

                int pure_native_method = *(int*)pc;
                pc += sizeof(int);

                BOOL result_type_is_bool = *(int*)pc;
                pc += sizeof(int);

                unsigned int offset2 = *(unsigned int*)pc;
                pc += sizeof(int);

                int offset3 = *(int*)pc;
                pc += sizeof(int);

                /// get object value from llvm stack ///
                LVALUE* object_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -num_real_params);

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

                Value* param9 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)class_method);
                params2.push_back(param9);

                Value* param10 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset2);
                params2.push_back(param10);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);
                
                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_real_params);

                /// vm stack_ptr to llvm stack ///
                LVALUE llvm_value = get_method_call_result(params, current_block);

                trunc_variable(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INVOKE_DYNAMIC_METHOD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int num_params = *(int*)pc;
                pc += sizeof(int);

                BOOL static_ = *(int*)pc;
                pc += sizeof(int);

                int num_method_chains = *(int*)pc;
                pc += sizeof(int);

                int max_method_chains = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                int num_real_params = num_params + (static_ ? 0:1);

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

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_real_params);

                /// vm stack_ptr to llvm stack ///
                LVALUE llvm_value = get_method_call_result(params, current_block);

                trunc_variable(&llvm_value, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_INVOKE_BLOCK: {
                int num_params = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                LVALUE* block_object_value = llvm_stack_ptr - num_params -1;

                /// go ///
                Function* fun = TheModule->getFunction("invoke_block");

                std::vector<Value*> params2;

                Value* param1 = block_object_value->value;
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                std::string var_num_value_name("var_num");
                Value* param3 = params[var_num_value_name];
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_params);
                params2.push_back(param4);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param5 = params[stack_ptr_address_name];
                params2.push_back(param5);

                std::string info_value_name("info");
                Value* param6 = params[info_value_name];
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE result_value = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 64);
                trunc_variable(&result_value, size);

                /// dec stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_params+1);
                inc_vm_stack_ptr(params, current_block, -num_params-1-1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &result_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &result_value);
                }
                break;

            case OP_NEW: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int flg_array = *(int*)pc;
                pc += sizeof(int);

                int num_params = *(int*)pc;
                pc += sizeof(int);

                /// load class in runtime ///
                char* class_name2 = CONS_str(constant, offset);
                Function* load_class_fun = TheModule->getFunction("get_class_with_load_and_initialize");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(class_name2);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), APInt(32, 0, true));
                params2.push_back(param2);

                Value* klass_value = Builder.CreateCall(load_class_fun, params2);

                if_value_is_null_ret_zero(klass_value, 64, params, function, &current_block, llvm_stack, var_num);

                char* type_name = CONS_str(constant, offset2);

                /// go ///
                if(flg_array) {
                    LVALUE* array_num_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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
                    llvm_value.kind = kLVKindInt32;

                    inc_vm_stack_ptr(params, current_block, -1);
                    dec_stack_ptr(&llvm_stack_ptr, 1);

                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
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
                    llvm_value.kind = kLVKindInt32;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                }
                break;

            case OP_LOAD_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                unsigned int field_name_offset = *(unsigned int*)pc;
                pc += sizeof(int);

                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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
                param5 = value2.value;
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param6);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param7 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param7);

                Value* result = Builder.CreateCall(get_field_fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                Value* field_value = Builder.CreateAlignedLoad(param7, 8);

                LVALUE llvm_value;
                llvm_value.value = field_value;
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2 = llvm_value;
                trunc_variable(&llvm_value2, size);

                inc_vm_stack_ptr(params, current_block, -1);
                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_STORE_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                unsigned int field_name_offset = *(unsigned int*)pc;
                pc += sizeof(int);

                LVALUE* obj = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param10 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param10);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                Value* field_value = Builder.CreateAlignedLoad(param10, 8);

                LVALUE llvm_value;
                llvm_value.value = field_value;
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2 = llvm_value;
                trunc_variable(&llvm_value2, size);

                inc_vm_stack_ptr(params, current_block, -2);
                dec_stack_ptr(&llvm_stack_ptr, 2);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_STORE_FIELD_OF_BUFFER: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                unsigned int field_name_offset = *(unsigned int*)pc;
                pc += sizeof(int);

                LVALUE* obj = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param8 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param8);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param8, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2 = llvm_value;
                trunc_variable(&llvm_value2, size);

                inc_vm_stack_ptr(params, current_block, -2);
                dec_stack_ptr(&llvm_stack_ptr, 2);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_STORE_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);
                }
                break;

            case OP_STORE_CLASS_FIELD_OF_BUFFER: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);
                }
                break;


            case OP_LOAD_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

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

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param8 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param8);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param8, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2 = llvm_value;
                trunc_variable(&llvm_value2, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LOAD_CLASS_FIELD_ADDRESS: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

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

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param8 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param8);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                Value* address_value = Builder.CreateAlignedLoad(param8, 8);

                LVALUE llvm_value;
                llvm_value.value = address_value;
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2.value = Builder.CreateCast(Instruction::IntToPtr, address_value, PointerType::get(IntegerType::get(TheContext, 8), 0));
                llvm_value2.kind = kLVKindPointer8;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_SPLIT_TUPLE: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int size[GENERICS_TYPES_MAX];

                int i;
                for(i = 0; i<num_elements; i++) {
                    size[i] = *(int*)pc;
                    pc += sizeof(int);
                }

                LVALUE* tuple = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                inc_vm_stack_ptr(params, current_block, -1);

                Function* split_tuple_fun = TheModule->getFunction("split_tuple");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string info_value_name("info");
                Value* param2 = params[info_value_name];
                params2.push_back(param2);

                LVALUE tuple2 = trunc_value(tuple, 32);
                Value* param3 = tuple2.value;
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(TheContext, llvm::APInt(32, num_elements, true));
                params2.push_back(param4);

                std::string stack_value_name("stack");
                Value* param5 = params[stack_value_name];
                params2.push_back(param5);

                std::string var_num_value_name("var_num");
                Value* param6 = params[var_num_value_name];
                params2.push_back(param6);

                Value* result = Builder.CreateCall(split_tuple_fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                dec_stack_ptr(&llvm_stack_ptr, 1);

                for(i=0; i<num_elements; i++) {
                    LVALUE llvm_value = get_vm_stack_ptr_value_from_index_with_aligned(params, current_block, -num_elements+i, 64);

                    trunc_variable(&llvm_value, size[i]);

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                }
                break;

            case OP_LOAD_ADDRESS: {
                int index = *(int*)pc;
                pc += sizeof(int);

                std::string lvar_arg_name("lvar");
                Value* lvar_value = params[lvar_arg_name];

                LVALUE llvm_value;
                Value* add_value = ConstantInt::get(TheContext, llvm::APInt(64, index, true)); 
                llvm_value.value = Builder.CreateGEP(lvar_value, add_value, "gepaddtmp");
                llvm_value.kind = kLVKindAddress;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CLASSNAME: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(value, 32);

                if_value_is_zero_entry_exception_object(llvm_value2.value, 32, FALSE, FALSE, params, function, &current_block, (char*)"Exception", (char*)"Null pointer exception(1)", llvm_stack, var_num);

                Function* fun = TheModule->getFunction("get_string_object_of_object_name");

                std::vector<Value*> params2;

                params2.push_back(llvm_value2.value);

                std::string info_value_name("info");
                Value* param2 = params[info_value_name];
                params2.push_back(param2);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                LVALUE llvm_value3;
                llvm_value3 = trunc_value(&llvm_value, 32);

                inc_vm_stack_ptr(params, current_block, -1);
                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value3);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value3);
                }
                break;

            case OP_OBJ_ALLOCATED_SIZE: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(value, 32);

                if_value_is_zero_entry_exception_object(llvm_value2.value, 32, FALSE, FALSE, params, function, &current_block, (char*)"Exception", (char*)"Null pointer exception(1)", llvm_stack, var_num);

                Function* fun = TheModule->getFunction("get_object_allocated_size");

                std::vector<Value*> params2;

                params2.push_back(llvm_value2.value);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                LVALUE llvm_value3;
                llvm_value3 = trunc_value(&llvm_value, 32);

                inc_vm_stack_ptr(params, current_block, -1);
                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value3);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value3);
                }
                break;

            case OP_OBJ_HEAD_OF_MEMORY: {
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(value, 32);

                if_value_is_zero_entry_exception_object(llvm_value2.value, 32, FALSE, FALSE, params, function, &current_block, (char*)"Exception", (char*)"Null pointer exception(1)", llvm_stack, var_num);

                Function* fun = TheModule->getFunction("get_object_head_of_memory");

                std::vector<Value*> params2;

                params2.push_back(llvm_value2.value);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindPointer8;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_IS: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* rvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                LVALUE lvalue2;
                lvalue2 = trunc_value(lvalue, 32);

                LVALUE rvalue2;
                rvalue2 = trunc_value(rvalue, 32);

                if_value_is_zero_entry_exception_object(lvalue2.value, 32, FALSE, FALSE, params, function, &current_block, (char*)"Exception", (char*)"Null pointer exception(1)", llvm_stack, var_num);

                Function* fun = TheModule->getFunction("op_is_fun");

                std::vector<Value*> params2;

                params2.push_back(lvalue2.value);
                params2.push_back(rvalue2.value);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                dec_stack_ptr(&llvm_stack_ptr, 2);
                inc_vm_stack_ptr(params, current_block, -2);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_IMPLEMENTS: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                /// load class in runtime ///
                char* class_name2 = CONS_str(constant, offset);
                Function* load_class_fun = TheModule->getFunction("get_class_with_load_and_initialize");

                std::vector<Value*> params2;

                Value* param1 = llvm_create_string(class_name2);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), APInt(32, 0, true));
                params2.push_back(param2);

                Value* klass_value = Builder.CreateCall(load_class_fun, params2);

                if_value_is_null_ret_zero(klass_value, 64, params, function, &current_block, llvm_stack, var_num);

                /// go ///
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                if_value_is_zero_entry_exception_object(value->value, 32, FALSE, FALSE, params, function, &current_block, (char*)"Exception", (char*)"Null pointer exception(2)", llvm_stack, var_num);

                Function* fun = TheModule->getFunction("object_implements_interface");

                params2.clear();

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(value, 32);
                params2.push_back(llvm_value2.value);

                params2.push_back(klass_value);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LOGICAL_DENIAL: {
                LVALUE* lvalue = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                *lvalue = trunc_value(lvalue, 32);

                LVALUE rvalue;
                rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue.value, "LOGICAL_DIANEAL");
                llvm_value.kind = kLVKindInt1;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_LOAD_ELEMENT: {
                int size = *(int*)pc;
                pc += sizeof(int);

                LVALUE* array = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* element_num = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param7 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                dec_stack_ptr(&llvm_stack_ptr, 2);
                inc_vm_stack_ptr(params, current_block, -2);

                Value* element_value = Builder.CreateAlignedLoad(param7, 8);

                LVALUE llvm_value;
                llvm_value.value = element_value;
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2 = llvm_value;
                trunc_variable(&llvm_value2, size);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_STORE_ELEMENT: {
                LVALUE* array = get_stack_ptr_value_from_index(llvm_stack_ptr, -3);
                LVALUE* element_num = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

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

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value = *value;

                dec_stack_ptr(&llvm_stack_ptr, 3);
                inc_vm_stack_ptr(params, current_block, -3);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_STORE_ELEMENT_OF_BUFFER: {
                LVALUE* array = get_stack_ptr_value_from_index(llvm_stack_ptr, -3);
                LVALUE* element_num = get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE* value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("run_store_element_of_buffer");

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

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value = *value;

                dec_stack_ptr(&llvm_stack_ptr, 3);
                inc_vm_stack_ptr(params, current_block, -3);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_ARRAY_LENGTH: {
                LVALUE* array_ = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_array_length");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(array_, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_GLOBAL: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_global");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_IGNORE_CASE: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_ignorecase");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_MULTILINE: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_multiline");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_EXTENDED: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_extended");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_DOTALL: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_dotall");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_ANCHORED: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_anchored");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_DOLLAR_ENDONLY: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_dollar_endonly");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_GET_REGEX_UNGREEDY: {
                LVALUE* regex = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("get_regex_ungreedy");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(regex, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CHAR_UPPERCASE: {
                LVALUE* c = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("char_uppercase");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(c, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindUInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CHAR_LOWERCASE: {
                LVALUE* c = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                Function* fun = TheModule->getFunction("char_lowercase");

                std::vector<Value*> params2;

                LVALUE value2;
                value2 = trunc_value(c, 32);

                Value* param1 = value2.value;
                params2.push_back(param1);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateCall(fun, params2);
                llvm_value.kind = kLVKindUInt32;

                dec_stack_ptr(&llvm_stack_ptr, 1);
                inc_vm_stack_ptr(params, current_block, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_STRING: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int num_string_expression = *(int*)pc;
                pc += sizeof(int);

                char* str = CONS_str(constant, offset);

                if(num_string_expression == 0) {
                    Function* function = TheModule->getFunction("create_string_object");

                    std::vector<Value*> params2;

                    Value* param1 = llvm_create_string(str);
                    params2.push_back(param1);

                    std::string info_value_name("info");
                    Value* param2 = params[info_value_name];
                    params2.push_back(param2);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                else {
                    int string_expression_offsets[STRING_EXPRESSION_MAX];

                    int i;
                    for(i=0; i<num_string_expression; i++) {
                        string_expression_offsets[i] = *(int*)pc;
                        pc += sizeof(int);
                    }

                    Type* element_type = IntegerType::getInt32Ty(TheContext);
                    ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                    Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");
                    Value* string_expression_offsets_value2 = Builder.CreateCast(Instruction::BitCast, string_expression_offsets_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    for(i=0; i<num_string_expression; i++) {
                        Value* lvalue = string_expression_offsets_value2;
                        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                        Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                        Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i]));
                        Builder.CreateAlignedStore(element_value, element_address_value, 4);
                    }

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

                    std::string info_value_name("info");
                    Value* param5 = params[info_value_name];
                    params2.push_back(param5);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    /// dec llvm stack pointer ///
                    dec_stack_ptr(&llvm_stack_ptr, num_string_expression);
                    inc_vm_stack_ptr(params, current_block, -num_string_expression);

                    /// vm stack_ptr to llvm stack ///
                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                }
                break;

            case OP_CREATE_BUFFER: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                int num_string_expression = *(int*)pc;
                pc += sizeof(int);

                char* str = CONS_str(constant, offset);

                if(num_string_expression == 0) {
                    Function* function = TheModule->getFunction("create_buffer_object");

                    std::vector<Value*> params2;
                    Value* param1 = llvm_create_buffer(str, size);
                    params2.push_back(param1);

                    Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)size);
                    params2.push_back(param2);

                    std::string info_value_name("info");
                    Value* param3 = params[info_value_name];
                    params2.push_back(param3);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                else {
                    int string_expression_offsets[STRING_EXPRESSION_MAX];

                    int i;
                    for(i=0; i<num_string_expression; i++) {
                        string_expression_offsets[i] = *(int*)pc;
                        pc += sizeof(int);
                    }

                    Type* element_type = IntegerType::getInt32Ty(TheContext);
                    ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                    Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");
                    Value* string_expression_offsets_value2 = Builder.CreateCast(Instruction::BitCast, string_expression_offsets_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    for(i=0; i<num_string_expression; i++) {
                        Value* lvalue = string_expression_offsets_value2;
                        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                        Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                        Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i]));
                        Builder.CreateAlignedStore(element_value, element_address_value, 4);
                    }

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

                    std::string info_value_name("info");
                    Value* param5 = params[info_value_name];
                    params2.push_back(param5);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    /// dec llvm stack pointer ///
                    dec_stack_ptr(&llvm_stack_ptr, num_string_expression);
                    inc_vm_stack_ptr(params, current_block, -num_string_expression);

                    /// vm stack_ptr to llvm stack ///
                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                }
                break;

            case OP_CREATE_PATH: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int num_string_expression = *(int*)pc;
                pc += sizeof(int);

                char* str = CONS_str(constant, offset);

                if(num_string_expression == 0) {
                    Function* function = TheModule->getFunction("create_path_object");

                    std::vector<Value*> params2;
                    Value* param1 = llvm_create_string(str);
                    params2.push_back(param1);

                    std::string info_value_name("info");
                    Value* param2 = params[info_value_name];
                    params2.push_back(param2);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                else {
                    int string_expression_offsets[STRING_EXPRESSION_MAX];

                    int i;
                    for(i=0; i<num_string_expression; i++) {
                        string_expression_offsets[i] = *(int*)pc;
                        pc += sizeof(int);
                    }

                    Type* element_type = IntegerType::getInt32Ty(TheContext);
                    ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                    Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");
                    Value* string_expression_offsets_value2 = Builder.CreateCast(Instruction::BitCast, string_expression_offsets_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    for(i=0; i<num_string_expression; i++) {
                        Value* lvalue = string_expression_offsets_value2;
                        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                        Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                        Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i]));
                        Builder.CreateAlignedStore(element_value, element_address_value, 4);
                    }

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

                    std::string info_value_name("info");
                    Value* param5 = params[info_value_name];
                    params2.push_back(param5);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    /// dec llvm stack pointer ///
                    dec_stack_ptr(&llvm_stack_ptr, num_string_expression);
                    inc_vm_stack_ptr(params, current_block, -num_string_expression);

                    /// vm stack_ptr to llvm stack ///
                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                }
                break;

            case OP_CREATE_ARRAY: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;

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

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param8 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param8);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param8, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;

                int type_name_offset = offset2;

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

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)type_name_offset);
                params2.push_back(param7);

                std::string constant_value_name("constant");
                Value* param8 = params[constant_value_name];
                params2.push_back(param8);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param9 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param9);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param9, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_SORTABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int type_name_offset = offset2;

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

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)type_name_offset);
                params2.push_back(param7);

                std::string constant_value_name("constant");
                Value* param8 = params[constant_value_name];
                params2.push_back(param8);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param9 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param9);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param9, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_EQUALABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int type_name_offset = offset2;

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

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)type_name_offset);
                params2.push_back(param7);

                std::string constant_value_name("constant");
                Value* param8 = params[constant_value_name];
                params2.push_back(param8);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param9 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param9);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param9, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;

                int type_name_offset = offset2;

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

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)type_name_offset);
                params2.push_back(param7);

                std::string constant_value_name("constant");
                Value* param8 = params[constant_value_name];
                params2.push_back(param8);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param9 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param9);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param9, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_SORTABLE_LIST: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;

                int type_name_offset = offset2;

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

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)type_name_offset);
                params2.push_back(param7);

                std::string constant_value_name("constant");
                Value* param8 = params[constant_value_name];
                params2.push_back(param8);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param9 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param9);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param9, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_EQUALABLE_LIST: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;
                int type_name_offset = offset2;

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

                Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)type_name_offset);
                params2.push_back(param7);

                std::string constant_value_name("constant");
                Value* param8 = params[constant_value_name];
                params2.push_back(param8);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param9 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param9);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param9, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_TUPLE: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* type_name = CONS_str(constant, offset);

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

                Value* param6 = llvm_create_string(type_name);
                params2.push_back(param6);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param7 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param7, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements);
                inc_vm_stack_ptr(params, current_block, -num_elements);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_HASH: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                int offset3 = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = offset;
                int class_name_offset2 = offset2;
                int type_name_offset = offset3;

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

                Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)type_name_offset);
                params2.push_back(param8);

                std::string constant_value_name("constant");
                Value* param9 = params[constant_value_name];
                params2.push_back(param9);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param10 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param10);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param10, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// dec llvm stack pointer ///
                dec_stack_ptr(&llvm_stack_ptr, num_elements*2);
                inc_vm_stack_ptr(params, current_block, -num_elements*2);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_BLOCK_OBJECT : {
                int code_offset = *(int*)pc;
                pc += sizeof(int);

                int code_len = *(int*)pc;
                pc += sizeof(int);

                int constant_offset = *(int*)pc;
                pc += sizeof(int);

                int constant_len = *(int*)pc;
                pc += sizeof(int);

                int block_var_num = *(int*)pc;
                pc += sizeof(int);

                int parent_var_num = *(int*)pc;
                pc += sizeof(int);

                int lambda = *(int*)pc;
                pc += sizeof(int);

                int block_id = *(int*)pc;
                pc += sizeof(int);

                int class_name_offset = *(int*)pc;
                pc += sizeof(int);

                int num_params = *(int*)pc;
                pc += sizeof(int);

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

                Value* param11 = ConstantInt::get(Type::getInt32Ty(TheContext), (int32_t)block_id);
                params2.push_back(param11);

                Value* param12 = ConstantInt::get(Type::getInt32Ty(TheContext), (int32_t)class_name_offset);
                params2.push_back(param12);

                std::string info_value_name("info");
                Value* param13 = params[info_value_name];
                params2.push_back(param13);

                std::string var_num_value_name("var_num");
                Value* param14 = params[var_num_value_name];
                params2.push_back(param14);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                Value* param15 = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "MACHINE_STACK_VALUE");
                params2.push_back(param15);

                Value* result = Builder.CreateCall(fun, params2);

                finish_method_call(result, params, &current_block, function, &try_catch_label_name, llvm_stack, var_num);

                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(param15, 8);
                llvm_value.kind = kLVKindInt64;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(&llvm_value, 32);

                /// vm stack_ptr to llvm stack ///
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                break;

            case OP_CREATE_REGEX: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                BOOL global = *(int*)pc;
                pc += sizeof(int);

                BOOL ignore_case = *(int*)pc;
                pc += sizeof(int);

                BOOL multiline = *(int*)pc;
                pc += sizeof(int);

                BOOL extended = *(int*)pc;
                pc += sizeof(int);

                BOOL dotall = *(int*)pc;
                pc += sizeof(int);

                BOOL anchored = *(int*)pc;
                pc += sizeof(int);

                BOOL dollar_endonly = *(int*)pc;
                pc += sizeof(int);

                BOOL ungreedy = *(int*)pc;
                pc += sizeof(int);

                int num_string_expression = *(int*)pc;
                pc += sizeof(int);

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

                    std::string info_value_name("info");
                    Value* param10 = params[info_value_name];
                    params2.push_back(param10);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                else {
                    int string_expression_offsets[STRING_EXPRESSION_MAX];

                    int i;
                    for(i=0; i<num_string_expression; i++) {
                        string_expression_offsets[i] = *(int*)pc;
                        pc += sizeof(int);
                    }

                    Type* element_type = IntegerType::getInt32Ty(TheContext);
                    ArrayType* array_type = ArrayType::get(element_type, STRING_EXPRESSION_MAX);

                    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                    Value* string_expression_offsets_value = builder.CreateAlloca(array_type, 0, "string_expression_offsets");
                    Value* string_expression_offsets_value2 = Builder.CreateCast(Instruction::BitCast, string_expression_offsets_value, PointerType::get(IntegerType::get(TheContext, 32), 0));

                    for(i=0; i<num_string_expression; i++) {
                        Value* lvalue = string_expression_offsets_value2;
                        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(32, i));
                        Value* element_address_value = Builder.CreateGEP(lvalue, rvalue);

                        Value* element_value = ConstantInt::get(TheContext, llvm::APInt(32, string_expression_offsets[i]));
                        Builder.CreateAlignedStore(element_value, element_address_value, 4);
                    }

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

                    std::string info_value_name("info");
                    Value* param5 = params[info_value_name];
                    params2.push_back(param5);

                    Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)global);
                    params2.push_back(param6);
                    Value* param7 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)ignore_case);
                    params2.push_back(param7);
                    Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)multiline);
                    params2.push_back(param8);
                    Value* param9 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)extended);
                    params2.push_back(param9);
                    Value* param10 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)dotall);
                    params2.push_back(param10);
                    Value* param11 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)anchored);
                    params2.push_back(param11);
                    Value* param12 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)dollar_endonly);
                    params2.push_back(param12);
                    Value* param13 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)ungreedy);
                    params2.push_back(param13);

                    LVALUE llvm_value;
                    llvm_value.value = Builder.CreateCall(function, params2);
                    llvm_value.kind = kLVKindObject;

                    /// dec llvm stack pointer ///
                    dec_stack_ptr(&llvm_stack_ptr, num_string_expression);
                    inc_vm_stack_ptr(params, current_block, -num_string_expression);

                    /// vm stack_ptr to llvm stack ///
                    push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                    push_value_to_vm_stack_ptr_with_aligned(params, current_block, &llvm_value);
                }
                }
                break;

            default:
                if(!compile_to_native_code2(code, constant, klass, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
        }

//show_vm_stack_on_runtime(params);
    }

    // Finish off the function.
    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));

    //Builder.SetInsertPoint(current_block);
    Builder.CreateRet(ret_value);

    // Validate the generated code, checking for consistency.
    verifyFunction(*function);

    // Run the optimizer on the function.
    TheFPM->run(*function, TheFAM);

    return TRUE;
}

static BOOL compile_jit_methods(sCLClass* klass)
{
    char module_name[PATH_MAX + 128];
    snprintf(module_name, PATH_MAX, "Module %s", CLASS_NAME(klass));
    TheModule = new Module(module_name, TheContext);

    TheFPM = llvm::make_unique<FunctionPassManager>(TheModule);

    llvm::PassBuilder passBuilder;

    passBuilder.registerFunctionAnalyses(TheFAM);

#ifndef MDEBUG
#if LLVM_VERSION_MAJOR >= 7
    passBuilder.buildFunctionSimplificationPipeline(llvm::PassBuilder::OptimizationLevel::O3, llvm::PassBuilder::ThinLTOPhase::None, false);
#else
    passBuilder.buildFunctionSimplificationPipeline(llvm::PassBuilder::OptimizationLevel::O3, false);
#endif
#endif

    create_internal_functions();
    TheLabels.clear();

    int i;
    int num_compiled_method = 0;

    if(!(klass->mFlags & CLASS_FLAGS_INTERFACE)) {
        for(i=0; i<klass->mNumMethods; i++) {
            sCLMethod* method = klass->mMethods + i;

            if(!(method->mFlags & METHOD_FLAGS_NATIVE) && !(method->mFlags & METHOD_FLAGS_C_FUNCTION) && !(method->mFlags & METHOD_FLAGS_JS))
            {
                char method_path2[METHOD_NAME_MAX + 128];
                create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);

                sByteCode* code = &method->mByteCodes;
                sConst* constant = &klass->mConst;

                int var_num = method->mVarNum;
                int real_param_num = method->mNumParams + ((method->mFlags & METHOD_FLAGS_CLASS_METHOD) ? 0:1);

                if(!compile_to_native_code(code, constant, klass, var_num, real_param_num, method_path2, FALSE, FALSE)) {
                    return FALSE;
                }

                num_compiled_method++;
            }
        }

        for(i=0; i<klass->mNumBlockObjects; i++) {
            sCLBlockObject* block_object = klass->mBlockObjects + i;

            char func_path[METHOD_NAME_MAX + 128];
            create_block_path_for_jit(klass, i, func_path, METHOD_NAME_MAX + 128);

            sByteCode* code = &block_object->mByteCodes;
            sConst* constant = &block_object->mConst;

            int var_num = block_object->mVarNum;
            int real_param_num = block_object->mNumParams;

            if(!compile_to_native_code(code, constant, klass, var_num, real_param_num, func_path, !block_object->mLambda, TRUE)) 
            {
                return FALSE;
            }

            num_compiled_method++;
        }
    }

    if(num_compiled_method > 0) {
#if LLVM_VERSION_MAJOR >= 7
        char path[PATH_MAX];
        snprintf(path, PATH_MAX, "%s.bc", CLASS_NAME(klass));

        (void)unlink(path);

        std::error_code ecode;
        llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

        std::string err_str;
        raw_string_ostream err_ostream(err_str);

        verifyModule(*TheModule);

        llvm::WriteBitcodeToFile(*TheModule, output_stream, true);
        output_stream.flush();
#elif LLVM_VERSION_MAJOR >= 4
        char path[PATH_MAX];
        snprintf(path, PATH_MAX, "%s.bc", CLASS_NAME(klass));

        (void)unlink(path);

        std::error_code ecode;
        llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

        std::string err_str;
        raw_string_ostream err_ostream(err_str);

        verifyModule(*TheModule);

        llvm::WriteBitcodeToFile(TheModule, output_stream, true);
        output_stream.flush();
#else
        char path[PATH_MAX];
        snprintf(path, PATH_MAX, "%s.bc", CLASS_NAME(klass));

        (void)unlink(path);

        std::error_code ecode;
        llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

        std::string err_str;
        raw_string_ostream err_ostream(err_str);

        verifyModule(*TheModule);

        llvm::WriteBitcodeToFile(TheModule, output_stream, true);
        output_stream.flush();
#endif
    }

    delete TheModule;

    return TRUE;
}

BOOL jit_compile_class(sCLClass* klass)
{
    if(!(klass->mFlags & CLASS_FLAGS_INTERFACE)) {
        jit_init();

        if(!compile_jit_methods(klass)) {
            jit_final();
            return FALSE;
        }

        jit_final();
    }

    return TRUE;
}

LVALUE trunc_value(LVALUE* llvm_value, int size)
{
    LVALUE result = *llvm_value;

    if(llvm_value->kind == kLVKindMemory) {
        Value* value = Builder.CreateAlignedLoad(llvm_value->value, 8);

        switch(size) {
            case 1: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt1Ty(TheContext));
                result.kind = kLVKindInt1;
            }
            break;

            case 8: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext));
                result.kind = kLVKindInt8;
            }
            break;

            case 16: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext));
                result.kind = kLVKindInt16;
            }
            break;

            case 32: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext));
                result.kind = kLVKindInt32;
            }
            break;

            case 64: {
                result.value = Builder.CreateCast(Instruction::BitCast, value, Type::getInt64Ty(TheContext));
                result.kind = kLVKindInt64;
            }
            break;
        }
    }
    else {
        Type* llvm_type = llvm_value->value->getType();
        Type::TypeID type_id = llvm_type->getTypeID();

        /// Constant Int ///
        if(llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantUInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantUInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantUInt32 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantUInt64) 
        {
#if LLVM_VERSION_MAJOR >= 5
            ConstantInt* constant_int_value = (ConstantInt*)llvm_value->value;
            APInt apint_value = constant_int_value->getValue();

            //bool signed_value = llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantInt64;
            bool signed_value = apint_value.isSignBitSet();
#else
            ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
            bool signed_value = apint_value.isSignBit();
#endif

            switch(size) {
                case 1:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(1));
                        result.kind = kLVKindConstantInt1;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(1));
                        result.kind = kLVKindConstantInt1;
                    }
                    break;

                case 8:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(8));
                        result.kind = kLVKindConstantInt8;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(8));
                        result.kind = kLVKindConstantUInt8;
                    }
                    break;

                case 16:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(16));
                        result.kind = kLVKindConstantInt16;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(16));
                        result.kind = kLVKindConstantUInt16;
                    }
                    break;

                case 32:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(32));
                        result.kind = kLVKindConstantInt32;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(32));
                        result.kind = kLVKindConstantUInt32;
                    }
                    break;

                case 64:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(64));
                        result.kind = kLVKindConstantInt64;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(64));
                        result.kind = kLVKindConstantUInt64;
                    }
                    break;
            }
        }
        else if(llvm_value->kind == kLVKindConstantFloat || llvm_value->kind == kLVKindConstantDouble) {
#if LLVM_VERSION_MAJOR >= 5
            ConstantFP* constant_float_value = (ConstantFP*)llvm_value->value;
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#else
            ConstantFP* constant_float_value = dynamic_cast<ConstantFP*>(llvm_value->value);
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#endif

            switch(size) {
                case 1: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(1));
                    result.kind = kLVKindConstantInt1;
                    }
                    break;

                case 8: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(8));
                    result.kind = kLVKindConstantInt8;
                    }
                    break;

                case 16: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(16));
                    result.kind = kLVKindConstantInt16;
                    }
                    break;

                case 32: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(32));
                    result.kind = kLVKindConstantInt32;
                    }
                    break;

                case 64: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(64));
                    result.kind = kLVKindConstantInt64;
                    }
                    break;
            }
        }
        /// Memory ///
        else if(type_id == Type::TypeID::FloatTyID) {
            switch(size) {
                case 1:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt1Ty(TheContext));
                    result.kind = kLVKindInt1;
                    break;

                case 8:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt8Ty(TheContext));
                    result.kind = kLVKindInt8;
                    break;

                case 16:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt16Ty(TheContext));
                    result.kind = kLVKindInt16;
                    break;

                case 32:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.kind = kLVKindInt32;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::ZExt, result.value, Type::getInt64Ty(TheContext));
                    result.kind = kLVKindInt64;
                    break;
            }
        }
        else if(type_id == Type::TypeID::DoubleTyID) {
            switch(size) {
                case 1:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt1Ty(TheContext));
                    result.kind = kLVKindInt1;
                    break;

                case 8:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
                    result.kind = kLVKindInt8;
                    break;

                case 16:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
                    result.kind = kLVKindInt16;
                    break;

                case 32:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
                    result.kind = kLVKindInt32;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.kind = kLVKindInt64;
                    break;
            }
        }
        else if(llvm_type->isPointerTy()) {
            switch(size) {
                case 1:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt1Ty(TheContext));
                    result.kind = kLVKindInt1;
                    break;

                case 8:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt8Ty(TheContext));
                    result.kind = kLVKindInt8;
                    break;

                case 16:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt16Ty(TheContext));
                    result.kind = kLVKindInt16;
                    break;

                case 32:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.kind = kLVKindInt32;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.kind = kLVKindInt64;
                    break;
            }
        }
        else {
            switch(size) {
                case 1:
                    if(!llvm_type->isIntegerTy(1)) {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt1Ty(TheContext));
                        result.kind = kLVKindInt1;
                    }
                    break;

                case 8:
                    if(llvm_type->isIntegerTy(1)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt8Ty(TheContext));
                        result.kind = kLVKindInt8;
                    }
                    else if(!llvm_type->isIntegerTy(8)) {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext));
                        result.kind = kLVKindInt8;
                    }
                    break;

                case 16:
                    if(llvm_type->isIntegerTy(1) || llvm_type->isIntegerTy(8)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt16Ty(TheContext));
                        result.kind = kLVKindInt16;
                    }
                    else if(llvm_type->isIntegerTy(16)) {
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext));
                        result.kind = kLVKindInt16;
                    }
                    break;

                case 32:
                    if(llvm_type->isIntegerTy(1) ||llvm_type->isIntegerTy(8) || llvm_type->isIntegerTy(16)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt32Ty(TheContext));
                        result.kind = kLVKindInt32;
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
                        result.kind = kLVKindInt32;
                    }
                    break;

                case 64:
                    if(!llvm_type->isIntegerTy(64)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt64Ty(TheContext));
                        result.kind = kLVKindInt64;
                    }
                    break;
            }
        }
    }

    return result;
}

void store_llvm_value_to_lvar_with_offset(LVALUE* llvm_stack, int index, LVALUE* llvm_value)
{
/*
    /// 0 clear align 8 byte ///
    Value* zero = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateStore(zero, llvm_stack[index].value);

    /// store ///
    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);
*/
    
    /// go ///
    llvm_stack[index].value = llvm_value->value;
    llvm_stack[index].kind = llvm_value->kind;
}

LVALUE get_vm_stack_ptr_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
    Value* stack_pointer_offset_value = Builder.CreateGEP(lvalue, rvalue, "stack_pointer_offset_value");

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(stack_pointer_offset_value, align, "stack_pointer_offset_value");

    switch(align) {
        case 1:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt1Ty(TheContext));
            result.kind = kLVKindInt1;
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            result.kind = kLVKindInt8;
            break;

        case 16:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            result.kind = kLVKindInt16;
            break;

        case 32:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            result.kind = kLVKindInt32;
            break;

        case 64:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            result.kind = kLVKindInt64;
            break;
    }

    return result;
}

LVALUE get_stack_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_name("stack");
    Value* stack_address_value = params[stack_name];

    LVALUE result;
    if(index > 0) {
        Value* lvalue = stack_address_value;
        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
        Value* stack_offset_address_value = Builder.CreateGEP(lvalue, rvalue, "stack_offset_address_value");


        result.value = Builder.CreateAlignedLoad(stack_offset_address_value, align, "stack_offset_value");
    }
    else {
        result.value = Builder.CreateAlignedLoad(stack_address_value, align, "stack_offset_value");
    }


    switch(align) {
        case 1:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt1Ty(TheContext));
            result.kind = kLVKindInt1;
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            result.kind = kLVKindInt8;
            break;

        case 16:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            result.kind = kLVKindInt16;
            break;

        case 32:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            result.kind = kLVKindInt32;
            break;

        case 64:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            result.kind = kLVKindInt64;
            break;
    }

    return result;
}

void dec_stack_ptr(LVALUE** llvm_stack_ptr, int value)
{
    int i;
    for(i=0; i<value; i++) {
        (*llvm_stack_ptr)->value = 0;
        (*llvm_stack_ptr)->kind = kLVKindNone;

        (*llvm_stack_ptr)--;
    }

    (*llvm_stack_ptr)->value = 0;
    (*llvm_stack_ptr)->kind = kLVKindNone;
}

void inc_vm_stack_ptr(std::map<std::string, Value*> params, BasicBlock* current_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, value, true));
    Value* inc_ptr_value = Builder.CreateGEP(lvalue, rvalue, "inc_ptr_value(1)");

    Builder.CreateStore(inc_ptr_value, stack_ptr_address_value);
}

void push_value_to_stack_ptr(LVALUE** llvm_stack_ptr, LVALUE* value)
{
    (**llvm_stack_ptr) = *value;
    (*llvm_stack_ptr)++;
}

void push_value_to_vm_stack_ptr_with_aligned(std::map<std::string, Value*> params, BasicBlock* current_block, LVALUE* llvm_value)
{
    Builder.SetInsertPoint(current_block);

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateAlignedLoad(stack_ptr_address_value, 8, "loaded_stack_ptr_address_value");

    /// zero clear///
    Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
    Builder.CreateAlignedStore(zero, loaded_stack_ptr_address_value, 8);

    /// trunc ///
    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);

    /// store ///
    Builder.CreateAlignedStore(llvm_value2.value, loaded_stack_ptr_address_value, 8);

    inc_vm_stack_ptr(params, current_block, 1);
}

void create_internal_functions()
{
    Type* result_type;
    std::vector<Type *> type_params;
    Type* param1_type;
    Type* param2_type;
    Type* param3_type;
    Type* param4_type;
    Type* param5_type;
    Type* param6_type;
    Type* param7_type;
    Type* param8_type;
    Type* param9_type;
    Type* param10_type;
    Type* param11_type;
    Type* param12_type;
    Type* param13_type;
    Type* param14_type;
    Type* param15_type;
    FunctionType* function_type;

    /// gSigInt ///
    Type* variable_type = IntegerType::get(TheContext, 32);
    gSigIntValue = new GlobalVariable(*TheModule, variable_type, false, GlobalValue::ExternalLinkage, nullptr, "gSigInt");

    /// entry_exception_object ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object", TheModule);

    /// entry_exception_object_with_class_name2 ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object_with_class_name2", TheModule);

    /// inc_andand_oror_array ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "inc_andand_oror_array", TheModule);

    /// dec_andand_oror_array ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "dec_andand_oror_array", TheModule);

    /// set_andand_oror_right_value ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "set_andand_oror_right_value", TheModule);

    /// get_andand_oror_right_value ///
    type_params.clear();

    result_type = IntegerType::get(TheContext,32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_andand_oror_right_value", TheModule);

    /// set_andand_oror_left_value ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "set_andand_oror_left_value", TheModule);

    /// get_andand_oror_left_value ///
    type_params.clear();

    result_type = IntegerType::get(TheContext,32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_andand_oror_left_value", TheModule);

    /// get_class_with_load_and_initialize ///
    type_params.clear();
    
    result_type = PointerType::get(IntegerType::get(TheContext, 64), 0);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);


    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_class_with_load_and_initialize", TheModule);

    /// get_try_catch_label_name ///
    type_params.clear();

    result_type = PointerType::get(IntegerType::get(TheContext,8), 0);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_try_catch_label_name", TheModule);

    /// try_function ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext,32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext,32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "try_function", TheModule);

    /// call_invoke_method ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);
    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "call_invoke_method", TheModule);

    /// mark_source_position ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext,32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "mark_source_position", TheModule);

    /// mark_source_position2 ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext,32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "mark_source_position2", TheModule);

    /// get_field_from_object ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_field_from_object", TheModule);

    /// create_array_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_array_object", TheModule);

    /// create_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_object", TheModule);

    /// store_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    param10_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param10_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "store_field", TheModule);

    /// try_end_function ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext,32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext,32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "try_end_function", TheModule);

    /// run_store_to_buffer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_store_to_buffer", TheModule);

    /// split_tuple ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "split_tuple", TheModule);


    /// call_invoke_virtual_method ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param9_type);

    param10_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param10_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "call_invoke_virtual_method", TheModule);

    /// call_invoke_dynamic_method ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param9_type);

    param10_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param10_type);

    param11_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param11_type);

    param12_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param12_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "call_invoke_dynamic_method", TheModule);

    /// invoke_block ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "invoke_block", TheModule);

    /// run_load_field_address ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_field_address", TheModule);

    /// store_field_of_buffer ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "store_field_of_buffer", TheModule);

    /// load_class_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "load_class_field", TheModule);

    /// run_load_class_field_address ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_class_field_address", TheModule);

    /// store_class_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "store_class_field", TheModule);

    /// store_class_field_of_buffer ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "store_class_field_of_buffer", TheModule);

    /// get_string_object_of_object_name ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_string_object_of_object_name", TheModule);

    /// get_object_allocated_size ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_object_allocated_size", TheModule);

    /// op_is_fun ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "op_is_fun", TheModule);

    /// object_implements_interface ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);
    
    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "object_implements_interface", TheModule);

    /// load_element ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "load_element", TheModule);

    /// run_store_element ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_store_element", TheModule);

    /// run_store_element_of_buffer ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_store_element_of_buffer", TheModule);

    /// get_array_length ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_array_length", TheModule);

    /// get_regex_global ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_global", TheModule);

    /// get_regex_ignorecase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_ignorecase", TheModule);

    /// get_regex_multiline ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_multiline", TheModule);

    /// get_regex_extended ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_extended", TheModule);

    /// get_regex_dotall ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_dotall", TheModule);

    /// get_regex_anchored ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_anchored", TheModule);

    /// get_regex_dollar_endonly ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_dollar_endonly", TheModule);

    /// get_regex_ungreedy ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_ungreedy", TheModule);

    /// get_regex_multiline ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_multiline", TheModule);

    /// char_uppercase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "char_uppercase", TheModule);

    /// char_lowercase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "char_lowercase", TheModule);

    /// create_string ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_string_object", TheModule);

    /// run_op_string_with_string_expression ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 32), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_op_string_with_string_expression", TheModule);

    /// run_op_buffer_with_string_expression ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 32), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_op_buffer_with_string_expression", TheModule);

    /// run_op_path_with_string_expression ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 32), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_op_path_with_string_expression", TheModule);

    /// create_buffer_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_buffer_object", TheModule);

    /// create_path_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_path_object", TheModule);

    /// run_create_array ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_array", TheModule);

    /// run_create_carray ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_carray", TheModule);

    /// run_create_equalable_carray ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_carray", TheModule);

    /// run_create_list ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_list", TheModule);

    /// run_create_sortable_list ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_list", TheModule);

    /// run_create_equalable_list ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_list", TheModule);

    /// run_create_tuple ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_tuple", TheModule);

    /// run_create_hash ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    param10_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param10_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_hash", TheModule);

    /// run_create_block_object ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param9_type);

    param10_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param10_type);

    param11_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param11_type);

    param12_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param12_type);

    param13_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param13_type);

    param14_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param14_type);

    param15_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param15_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_block_object", TheModule);

    /// create_regex_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param9_type);

    param10_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param10_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_regex_object", TheModule);

    /// run_op_regex_with_string_expression ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 32), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0); // sVMInfo*
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);  // global
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);  // ignore case
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);  // multiline
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);  // exteneded
    type_params.push_back(param9_type);

    param10_type = IntegerType::get(TheContext, 32);  // dotall
    type_params.push_back(param10_type);

    param11_type = IntegerType::get(TheContext, 32);  // anchored
    type_params.push_back(param11_type);

    param12_type = IntegerType::get(TheContext, 32);  // dollar_endonly
    type_params.push_back(param12_type);

    param13_type = IntegerType::get(TheContext, 32);  // ungreedy
    type_params.push_back(param13_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_op_regex_with_string_expression", TheModule);

    /// run_int_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_int_to_string_cast", TheModule);

    /// run_long_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_long_to_string_cast", TheModule);

    /// run_uint_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uint_to_string_cast", TheModule);

    /// run_ulong_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ulong_to_string_cast", TheModule);

    /// run_float_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getFloatTy(TheContext);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_float_to_string_cast", TheModule);

    /// run_double_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getDoubleTy(TheContext);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_double_to_string_cast", TheModule);

    /// run_bool_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_bool_to_string_cast", TheModule);

    /// run_regex_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_regex_to_string_cast", TheModule);

    /// run_pointer_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_pointer_to_string_cast", TheModule);

    /// run_char_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_char_to_string_cast", TheModule);

    /// create_integer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_integer", TheModule);

    /// create_uinteger ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_uinteger", TheModule);

    /// create_long ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_long", TheModule);

    /// create_ulong ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ulong", TheModule);

    /// create_float ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getFloatTy(TheContext);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_float", TheModule);

    /// create_double ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getDoubleTy(TheContext);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_double", TheModule);

    /// create_pointer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_pointer", TheModule);

    /// create_char ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_char", TheModule);

    /// create_bool ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_bool", TheModule);

    /// create_byte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_byte", TheModule);

    /// create_ubyte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ubyte", TheModule);

    /// create_short ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_short", TheModule);

    /// create_ushort ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ushort", TheModule);

    /// run_array_to_carray_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_array_to_carray_cast", TheModule);

    /// run_buffer_to_pointer_cast ///
    type_params.clear();

    result_type = PointerType::get(IntegerType::get(TheContext,8), 0);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_buffer_to_pointer_cast", TheModule);

    /// run_cbyte_to_byte_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 8);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_byte_cast", TheModule);

    /// run_cubyte_to_ubyte_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 8);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ubyte_cast", TheModule);

    /// run_cshort_to_short_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 16);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_short_cast", TheModule);

    /// run_cushort_to_ushort_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 16);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ushort_cast", TheModule);

    /// run_integer_to_int_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_int_cast", TheModule);

    /// run_uinteger_to_uint_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_uint_cast", TheModule);

    /// run_clong_to_long_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_long_cast", TheModule);

    /// run_culong_to_ulong_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ulong_cast", TheModule);

    /// run_cfloat_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getFloatTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_float_cast", TheModule);

    /// run_cdouble_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getDoubleTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_double_cast", TheModule);

    /// print_value ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "print_value", TheModule);

    /// print_str_value ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "print_str_value", TheModule);

    /// regex_equals ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "regex_equals", TheModule);

    /// run_create_sortable_carray ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_carray", TheModule);

    /// get_head_of_memory ///
    type_params.clear();
    
    result_type = PointerType::get(IntegerType::get(TheContext, 8), 0);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_object_head_of_memory", TheModule);

    /// show_stack ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_vm_stack", TheModule);

    /// push_value_to_global_stack ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "push_value_to_global_stack", TheModule);
}

LVALUE* get_stack_ptr_value_from_index(LVALUE* llvm_stack_ptr, int index)
{
    return llvm_stack_ptr + index;
}

LVALUE load_value_from_lvar_with_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int index)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];
    
    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
    Value* lvar_offset_value = Builder.CreateGEP(lvalue, rvalue, "lvar_offset_value");

    LVALUE llvm_value;
    llvm_value.value = Builder.CreateAlignedLoad(lvar_offset_value, 8);
    llvm_value.kind = kLVKindInt64;

    return llvm_value;
}

void store_value_to_lvar_with_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, LVALUE* llvm_value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];
    
    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
    Value* lvar_offset_value = Builder.CreateGEP(lvalue, rvalue, "lvar_offset_value");

    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);

    Builder.CreateAlignedStore(llvm_value2.value, lvar_offset_value, 8);
}

void trunc_variable(LVALUE* llvm_value, int size)
{
    if(llvm_value->kind == kLVKindInt64) {
        switch(size) {
            case 1:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt1Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt1;
                break;

            case 8:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt8;
                break;

            case 16:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt16;
                break;

            case 32:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt32;
                break;

            case 64:
//                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt64Ty(TheContext), "trunc_variable");
//                llvm_value->kind = kLVKindInt64;
                break;

            case 128:
#if LLVM_VERSION_MAJOR >= 5
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
                llvm_value->value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getFloatTy(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindFloat;
#else
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
                llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindFloat;
#endif
                break;

            case 256:
                llvm_value->value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getDoubleTy(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindDouble;
                break;

            case 1024:
                llvm_value->value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0), "trunc_variable");
                llvm_value->kind = kLVKindPointer8;
                break;
        }
    }
}

Value* llvm_create_string(char* str)
{
    Constant* str_constant = ConstantDataArray::getString(TheModule->getContext(), str, true);

    GlobalVariable* gvar = new GlobalVariable(*TheModule, ArrayType::get(IntegerType::get(TheContext, 8), strlen(str)+1), true, GlobalValue::PrivateLinkage, 0, "global_string");
    gvar->setAlignment(1);

    gvar->setInitializer(str_constant);

    Value* value = Builder.CreateCast(Instruction::BitCast, gvar, PointerType::get(IntegerType::get(TheContext, 8), 0));

    return value;
}

void call_entry_exception_object_with_class_name2(std::map<std::string, Value *> params, char* class_name, char* message)
{
    Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object_with_class_name2");

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

    Value* param5 = llvm_create_string(class_name);
    params2.push_back(param5);

    Value* param6 = llvm_create_string(message);
    params2.push_back(param6);

    (void)Builder.CreateCall(entry_exception_object_fun, params2);
}

LVALUE get_method_call_result(std::map<std::string, Value*>& params, BasicBlock* current_block)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, -1, true));
    Value* stack_pointer_offset_value = Builder.CreateGEP(lvalue, rvalue, "stack_pointer_offset_value");

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(stack_pointer_offset_value, 8, "stack_pointer_offset_value");

    //result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
    result.kind = kLVKindInt64;

    return result;
}

void if_value_is_null_ret_zero(Value* value, int value_bit, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block, LVALUE* llvm_stack, int var_num)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* zero = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Value* null_ptr = Builder.CreateCast(Instruction::IntToPtr, zero, PointerType::get(IntegerType::get(TheContext, value_bit), 0));

    Value* comp = Builder.CreateICmpEQ(value, null_ptr, "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}


void finish_method_call(Value* result, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char** try_catch_label_name, LVALUE* llvm_stack, int var_num)
{
    // if result is FALSE ret 0
    Value* comp = Builder.CreateICmpNE(result, ConstantInt::get(TheContext, llvm::APInt(32, 1, true)), "ifcond");

    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Function* try_catch_label_name_fun = TheModule->getFunction("get_try_catch_label_name");

    std::vector<Value*> params2;

    std::string info_value_name("info");
    Value* info_value = params[info_value_name];
    params2.push_back(info_value);

    Value* try_catch_label_name_value = Builder.CreateCall(try_catch_label_name_fun, params2);

    Value* zero = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Value* null_ptr = Builder.CreateCast(Instruction::IntToPtr, zero, PointerType::get(IntegerType::get(TheContext, 8), 0));

    Value* comp2 = Builder.CreateICmpNE(try_catch_label_name_value, null_ptr, "catchcond");

    BasicBlock* then_block2 = BasicBlock::Create(TheContext, "then_block_b", function);
    BasicBlock* entry_ifend2 = BasicBlock::Create(TheContext, "entry_ifend_b", function);

    Builder.CreateCondBr(comp2, then_block2, entry_ifend2);

    Builder.SetInsertPoint(then_block2);

    if(*try_catch_label_name == nullptr) {
        Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
        Builder.CreateRet(ret_value);
    }
    else {
        std::string try_catch_label_name_string(*try_catch_label_name);
        BasicBlock* label = TheLabels[try_catch_label_name_string];
        if(label == nullptr) {
            label = BasicBlock::Create(TheContext, *try_catch_label_name, function);
            TheLabels[try_catch_label_name_string] = label;
        }

        if(label == nullptr) {
            Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
            Builder.CreateRet(ret_value);
        }
        else {
            Function* try_fun = TheModule->getFunction("try_function");

            std::vector<Value*> params2;

            std::string info_value_name("info");
            Value* vminfo_value = params[info_value_name];
            params2.push_back(vminfo_value);

            Value* catch_label_name_offset_value  = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
            params2.push_back(catch_label_name_offset_value);

            Value* try_offset_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
            params2.push_back(try_offset_value);

            std::string code_value_name("code");
            Value* code_value = params[code_value_name];
            params2.push_back(code_value);

            std::string constant_value_name("constant");
            Value* constant_value = params[constant_value_name];
            params2.push_back(constant_value);

            (void)Builder.CreateCall(try_fun, params2);

            Builder.CreateBr(label);
        }
    }

    Builder.SetInsertPoint(entry_ifend2);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend); 
    *current_block = entry_ifend;
}

StructType* get_vm_info_struct_type()
{
    StructType* result_type = StructType::create(TheContext, "vm_info_struct");
    std::vector<Type*> fields;
    Type* field_type1 = PointerType::get(IntegerType::get(TheContext, 8), 0); // try_catch_label_name
    fields.push_back(field_type1);
    Type* field_type2 = PointerType::get(IntegerType::get(TheContext, 64), 0); // current_stack
    fields.push_back(field_type2);
    Type* field_type3 = IntegerType::get(TheContext, 32); // current_var_num
    fields.push_back(field_type3);
    Type* field_type4 = PointerType::get(IntegerType::get(TheContext, 8), 0); // sname
    fields.push_back(field_type4);
    Type* field_type5 = IntegerType::get(TheContext, 32);                       // sline
    fields.push_back(field_type5);
    Type* field_type6 = PointerType::get(IntegerType::get(TheContext, 8), 0);   // sname2
    fields.push_back(field_type6);
    Type* field_type7 = IntegerType::get(TheContext, 32);                       // sline2
    fields.push_back(field_type7);
    Type* field_type8 = IntegerType::get(TheContext, 32);                       // try_offset
    fields.push_back(field_type8);
    Type* field_type9 = PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0); // try_pc
    fields.push_back(field_type9);
    Type* field_type10 = PointerType::get(IntegerType::get(TheContext, 64), 0);      // try_code
    fields.push_back(field_type10);
    Type* field_type11 = PointerType::get(IntegerType::get(TheContext, 64), 0);      // running_class
    fields.push_back(field_type11);
    Type* field_type12 = PointerType::get(IntegerType::get(TheContext, 64), 0);      // running_method
    fields.push_back(field_type12);
    Type* field_type13 = IntegerType::get(TheContext, 64);                           // stack_id
    fields.push_back(field_type13);
    Type* field_type14 = ArrayType::get(IntegerType::get(TheContext, 8), EXCEPTION_MESSAGE_MAX);  // exception_message
    fields.push_back(field_type14);
    Type* field_type15 = ArrayType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), STACK_TRACE_MAX);  // running_class_for_stack_trace
    fields.push_back(field_type15);
    Type* field_type16 = ArrayType::get(IntegerType::get(TheContext, 32), STACK_TRACE_MAX);  // running_method_for_stack_trace
    fields.push_back(field_type16);

    if(result_type->isOpaque()) {
        result_type->setBody(fields, false);
    }

    return result_type;
}

void if_value_is_zero_entry_exception_object(Value* value, int value_size, BOOL value_is_float, BOOL value_is_double, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block, char* class_name, char* message, LVALUE* llvm_stack, int var_num)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* rvalue;
    Value* comp;
    if(value_is_float) {
        double dvalue = 0.0;
        rvalue = ConstantFP::get(TheContext, llvm::APFloat(dvalue)); 
        rvalue = Builder.CreateCast(Instruction::FPTrunc, rvalue, Type::getFloatTy(TheContext));

        comp = Builder.CreateFCmpOEQ(value, rvalue, "ifcond");
    }
    else if(value_is_double) {
        double dvalue = 0.0;
        rvalue = ConstantFP::get(TheContext, llvm::APFloat(dvalue)); 
        rvalue = Builder.CreateCast(Instruction::FPExt, rvalue, Type::getDoubleTy(TheContext));

        comp = Builder.CreateFCmpOEQ(value, rvalue, "ifcond");
    }
    else {
        rvalue = ConstantInt::get(TheContext, llvm::APInt(value_size, 0, true));

        comp = Builder.CreateICmpEQ(value, rvalue, "ifcond");
    }

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    call_entry_exception_object_with_class_name2(params, class_name, message);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

// size --> 32: float 64:double
LVALUE trunc_value_to_float_or_double(LVALUE* llvm_value, int size)
{
    LVALUE result = *llvm_value;

    if(llvm_value->kind == kLVKindMemory) {
        Value* value = Builder.CreateAlignedLoad(llvm_value->value, 8);

        switch(size) {
            case 32:
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext));
                result.value = Builder.CreateCast(Instruction::BitCast, result.value, Type::getFloatTy(TheContext));
                result.kind = kLVKindFloat;
                break;

            case 64:
                result.value = Builder.CreateCast(Instruction::BitCast, value, Type::getDoubleTy(TheContext));
                result.kind = kLVKindDouble;
                break;
        }
    }
    else {
        Type* llvm_type = llvm_value->value->getType();
        Type::TypeID type_id = llvm_type->getTypeID();

        /// Constant Int ///
        if(llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantUInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantUInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantUInt32 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantUInt64) 
        {
#if LLVM_VERSION_MAJOR >= 5
            ConstantInt* constant_int_value = (ConstantInt*)(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();

            bool signed_value = apint_value.isSignBitSet();
            //bool signed_value = llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantInt64;
#else
            ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
            bool signed_value = apint_value.isSignBit();
#endif

            switch(size) {
                case 32:
                    if(signed_value) {
                        result.value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                        result.kind = kLVKindFloat;
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                        result.kind = kLVKindFloat;
                    }
                    break;

                case 64:
                    if(signed_value) {
                        result.value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                        result.kind = kLVKindDouble;
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                        result.kind = kLVKindDouble;
                    }
                    break;
            }
        }
        else if(llvm_value->kind == kLVKindConstantFloat || type_id == Type::TypeID::FloatTyID || llvm_value->kind == kLVKindFloat) {
            switch(size) {
                case 64:
                    result.value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext));
                    result.kind = kLVKindDouble;
                    break;
            }
        }
        else if(type_id == Type::TypeID::DoubleTyID || llvm_value->kind == kLVKindConstantDouble || llvm_value->kind == kLVKindDouble) {
            switch(size) {
                case 32:
                    result.value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext));
                    result.kind = kLVKindFloat;
                    break;

                case 64:
                    break;
            }
        }
        else if(llvm_type->isPointerTy()) {
            switch(size) {
                case 32:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::UIToFP, result.value, Type::getFloatTy(TheContext));
                    result.kind = kLVKindFloat;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::UIToFP, result.value, Type::getDoubleTy(TheContext));
                    result.kind = kLVKindDouble;
                    break;
            }
        }
        else {
            switch(size) {
                case 32:
                    result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                    result.kind = kLVKindFloat;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                    result.kind = kLVKindDouble;
                    break;
            }
        }
    }

    return result;
}

LVALUE trunc_value_to_pointer(LVALUE* llvm_value)
{
    LVALUE result = *llvm_value;

    if(llvm_value->kind == kLVKindMemory) {
        Value* value = Builder.CreateAlignedLoad(llvm_value->value, 8);

        result.value = Builder.CreateCast(Instruction::IntToPtr, value, PointerType::get(IntegerType::get(TheContext, 8), 0));
        result.kind = kLVKindPointer8;
    }
    else {
        Type* llvm_type = llvm_value->value->getType();
        Type::TypeID type_id = llvm_type->getTypeID();

        /// Constant Int ///
        if(llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantUInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantUInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantUInt32 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantUInt64) 
        {
#if LLVM_VERSION_MAJOR >= 5
            ConstantInt* constant_int_value = (ConstantInt*)(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
#else
            ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
#endif

            result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        else if(llvm_value->kind == kLVKindConstantFloat || llvm_value->kind == kLVKindConstantDouble) {
#if LLVM_VERSION_MAJOR >= 4
            ConstantFP* constant_float_value = (ConstantFP*)(llvm_value->value);
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#else
            ConstantFP* constant_float_value = dynamic_cast<ConstantFP*>(llvm_value->value);
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#endif

            result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        /// Memory ///
        else if(type_id == Type::TypeID::FloatTyID || llvm_value->kind == kLVKindFloat) {
            result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
            result.value = Builder.CreateCast(Instruction::IntToPtr, result.value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        else if(type_id == Type::TypeID::DoubleTyID || llvm_value->kind == kLVKindDouble) {
            result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
            result.value = Builder.CreateCast(Instruction::IntToPtr, result.value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        else if(llvm_type->isPointerTy()) {
        }
        else {
            result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
    }

    return result;
}

Value* llvm_create_buffer(char* str, int len)
{
    uint8_t* str2 = (uint8_t*)str;
    ArrayRef<uint8_t> str_array(str2, len);
    Constant* str_constant = ConstantDataArray::get(TheModule->getContext(), str_array);

    GlobalVariable* gvar = new GlobalVariable(*TheModule, ArrayType::get(IntegerType::get(TheContext, 8), len) , true, GlobalValue::PrivateLinkage, 0, "global_buffer");
    gvar->setAlignment(1);

    gvar->setInitializer(str_constant);

    Value* value = Builder.CreateCast(Instruction::BitCast, gvar, PointerType::get(IntegerType::get(TheContext, 8), 0));

    return value;
}

void show_value_on_runtime(Value* value) 
{
    Function* fun = TheModule->getFunction("print_value");

    std::vector<Value*> params3;

    Value* param3_1 = value;
    params3.push_back(param3_1);

    (void)Builder.CreateCall(fun, params3);
}

void show_str_value_on_runtime(char* str)
{
    Function* fun = TheModule->getFunction("print_str_value");

    std::vector<Value*> params3;

    Value* param3_1 = llvm_create_string(str);
    params3.push_back(param3_1);

    (void)Builder.CreateCall(fun, params3);
}

void show_int_value_on_runtime(int n)
{
    Function* fun = TheModule->getFunction("print_value");

    std::vector<Value*> params3;

    Value* param3_1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)n);
    params3.push_back(param3_1);

    (void)Builder.CreateCall(fun, params3);
}

void show_vm_stack_on_runtime(std::map<std::string, Value*>& params)
{
    Function* fun = TheModule->getFunction("show_vm_stack");

    std::vector<Value*> params2;

    std::string stack_value_name("stack");
    Value* param1 = params[stack_value_name];
    params2.push_back(param1);

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* param2 = params[stack_ptr_address_name];
    params2.push_back(param2);

    std::string info_value_name("info");
    Value* vminfo_value = params[info_value_name];
    params2.push_back(vminfo_value);

    std::string var_num_param_name("var_num");
    Value* var_num_value = params[var_num_param_name];
    params2.push_back(var_num_value);

    (void)Builder.CreateCall(fun, params2);
}

} // extern "C"
