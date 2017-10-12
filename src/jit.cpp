#include "jit_common.hpp"

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule;
std::unique_ptr<legacy::FunctionPassManager> TheFPM;
std::map<std::string, BasicBlock*> TheLabels;

extern "C"
{

void jit_init()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    /// CLVALUE and BOOL Struct type ///
    gCLValueAndBoolStruct = StructType::create(TheContext, "clvalue_and_bool_struct");

    std::vector<Type*> fields;
    Type* field_type1 = IntegerType::get(TheContext, 64);
    fields.push_back(field_type1);
    Type* field_type2 = IntegerType::get(TheContext, 32);
    fields.push_back(field_type2);

    //if(gCLValueAndBoolStruct->isOpaque()) {
        gCLValueAndBoolStruct->setBody(fields, false);
    //}

    /// CLVALUE and BOOL Struct type ///
    fields.clear();

    gPointerAndBoolStruct = StructType::create(TheContext, "pointer_and_bool_struct");

    field_type1 = PointerType::get(IntegerType::get(TheContext, 8), 0);
    fields.push_back(field_type1);
    field_type2 = IntegerType::get(TheContext, 32);
    fields.push_back(field_type2);

    //if(gPointerAndBoolStruct->isOpaque()) {
        gPointerAndBoolStruct->setBody(fields, false);
    //}
}

void jit_final()
{
}

//////////////////////////////////////////////////////////////
// LLVM core
//////////////////////////////////////////////////////////////
#define ANDAND_OROR_MAX 128

BOOL compile_to_native_code(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2)
{
    char* try_catch_label_name = NULL;

    std::string func_name(method_path2);
    Function* function = create_llvm_function(func_name);

    // Create a new basic block to start insertion into.
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(current_block);
  
    char* pc = code->mCodes;

    std::map<std::string, Value *> params;
    for(auto &param : function->args()) {
        params[param.getName()] = &param;
    }

    int num_cond_jump = 0;
    char* cond_jump_labels[MAX_COND_JUMP];
    BasicBlock* entry_condends[MAX_COND_JUMP];

    int num_cond_not_jump = 0;
    char* cond_not_jump_labels[MAX_COND_JUMP];
    BasicBlock* entry_condnotends[MAX_COND_JUMP];

    /// Stack to LLVM ///
    int var_num = method->mVarNum;

    LVALUE llvm_stack[CLOVER_STACK_SIZE];
    memset(llvm_stack, 0, sizeof(LVALUE)*CLOVER_STACK_SIZE);

    LVALUE* llvm_stack_ptr = llvm_stack + var_num;

    /// alloc local variables ///
    int i;
    for(i=0; i<var_num; i++) {
        llvm_stack[i].value = create_entry_block_alloca(function, i);

        llvm_stack[i].lvar_address_index = -1;
        llvm_stack[i].lvar_stored = FALSE;
        llvm_stack[i].constant_int_value = FALSE;
        llvm_stack[i].constant_float_value = FALSE;
        llvm_stack[i].float_value = FALSE;
    }

    /// parametor from VM stack ptr ///
    int real_param_num = method->mNumParams + ((method->mFlags & METHOD_FLAGS_CLASS_METHOD) ? 0:1);
    for(i=0; i<real_param_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);

        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }

    /// clear local variable ///
    for(i=real_param_num; i<var_num; i++) {
        LVALUE llvm_value;
        llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
        llvm_stack[i].lvar_address_index = -1;
        llvm_stack[i].lvar_stored = FALSE;
        llvm_stack[i].constant_int_value = FALSE;
        llvm_stack[i].constant_float_value = FALSE;
        llvm_stack[i].float_value = FALSE;

        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }

    Value* value_for_andand_oror[ANDAND_OROR_MAX];
    memset(value_for_andand_oror, 0, sizeof(Value*)*ANDAND_OROR_MAX);
    int num_value_for_andand_oror = 0;

    while(pc - code->mCodes < code->mLen) {
        int k;
        for(k=0; k<num_cond_jump; k++) {
            if(pc == cond_jump_labels[k]) {
                //Builder.CreateBr(entry_condends[k]);
                Builder.SetInsertPoint(entry_condends[k]);
                current_block = entry_condends[k];

                int j;
                for(j=k; j<num_cond_jump; j++) {
                    cond_jump_labels[j] = cond_jump_labels[j+1];
                    entry_condends[j] = entry_condends[j+1];
                }
                num_cond_jump--;
            }
        }
        for(k=0; k<num_cond_not_jump; k++) {
            if(pc == cond_not_jump_labels[k]) {
                //Builder.CreateBr(entry_condnotends[k]);
                Builder.SetInsertPoint(entry_condnotends[k]);
                current_block = entry_condnotends[k];

                int j;
                for(j=k; j<num_cond_not_jump; j++) {
                    cond_not_jump_labels[j] = cond_not_jump_labels[j+1];
                    entry_condnotends[j] = entry_condnotends[j+1];
                }
                num_cond_not_jump--;
            }
        }

        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);

/*
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
    if(strcmp(METHOD_NAME2(klass, method), "initialize") != 0 && strcmp(METHOD_NAME2(klass, method), "finalize") != 0) {
call_show_inst_in_jit(inst);
    }
}
*/

        switch(inst) {
            case OP_POP:
                dec_stack_ptr(&llvm_stack_ptr, 1);
                break;

            case OP_POP_N:
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    dec_stack_ptr(&llvm_stack_ptr, value);
                }
                break;

            case OP_REVERSE: {
                LVALUE llvm_value = *get_stack_ptr_value_from_index(llvm_stack_ptr, -2);
                LVALUE llvm_value2 = *get_stack_ptr_value_from_index(llvm_stack_ptr, -1);
                
                dec_stack_ptr(&llvm_stack_ptr, 1);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value2);
                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;

            case OP_DUPE: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                push_value_to_stack_ptr(&llvm_stack_ptr, llvm_value);
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

            case OP_COND_NOT_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                LVALUE* conditional_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                BasicBlock* cond_not_jump_then_block = BasicBlock::Create(TheContext, "cond_not_jump_then", function);
                entry_condnotends[num_cond_not_jump] = BasicBlock::Create(TheContext, "entry_condnotend", function);
                LVALUE llvm_value;
                llvm_value = trunc_value(conditional_value, 1);

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
                int jump_value = *(int*)pc;
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
                Value* store_address_value = Builder.CreateGEP(lvalue, rvalue, "store_address_value_LLLLL");

                Builder.CreateAlignedStore(llvm_value2.value, store_address_value, 8);

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));
                Builder.CreateRet(ret_value);

                BasicBlock* entry_after_return = BasicBlock::Create(TheContext, "entry_after_return", function);
                Builder.SetInsertPoint(entry_after_return);
                current_block = entry_after_return;
                }
                break;

            case OP_THROW: {
                std::string stack_param_name("stack");
                Value* stack_value = params[stack_param_name];

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

                }
                break;

            case OP_CATCH_POP:
                break;

            case OP_CATCH_STORE: {
                pc += sizeof(int);
                }
                break;

            case OP_HEAD_OF_EXPRESSION: {
                Value* sig_int_value = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                Builder.CreateStore(sig_int_value, gSigIntValue);
                }
                break;

            case OP_SIGINT: {
                Value* sig_int_value = Builder.CreateAlignedLoad(gSigIntValue, 4, "sig_int_value");

                BasicBlock* then_block = BasicBlock::Create(TheContext, "sigint_then_block", function);
                BasicBlock* else_block = BasicBlock::Create(TheContext, "entry_after_sigint", function);

                Value* value = Builder.CreateCast(Instruction::Trunc, sig_int_value, Type::getInt1Ty(TheContext));

                Builder.CreateCondBr(value, then_block, else_block);

                Builder.SetInsertPoint(then_block);

                Value* llvm_value1 = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
                Builder.CreateStore(llvm_value1, gSigIntValue);

                call_entry_exception_object_with_class_name2(params, "Exception", "Signal Interrupt");

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
                Builder.CreateRet(ret_value);

                Builder.SetInsertPoint(else_block);
                current_block = else_block;
                }
                break;

            case OP_MARK_SOURCE_CODE_POSITION: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                std::string info_value_name("info");
                Value* vminfo_value = params[info_value_name];

                StructType* vm_info_struct_type = get_vm_info_struct_type();

                Value* sname_field = Builder.CreateStructGEP(vm_info_struct_type, vminfo_value, 3);
                Value* sname_value = llvm_create_string(sname);
                Builder.CreateStore(sname_value, sname_field, "sname_store");

                Value* sline_field = Builder.CreateStructGEP(vm_info_struct_type, vminfo_value, 4);
                Value* sline_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)sline);
                Builder.CreateStore(sline_value, sline_field, "sline_store");
                }
                break;

            case OP_VALUE_FOR_ANDAND_OROR: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
                value_for_andand_oror[num_value_for_andand_oror] = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "VALUE_FOR_ANDAND_OROR");
                Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
                Builder.CreateAlignedStore(zero, value_for_andand_oror[num_value_for_andand_oror], 8);

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(llvm_value, 64);

                Builder.CreateAlignedStore(llvm_value2.value, value_for_andand_oror[num_value_for_andand_oror], 8);

                num_value_for_andand_oror++;

                MASSERT(num_value_for_andand_oror >= ANDAND_OROR_MAX);
                }
                break;

            case OP_STORE_VALUE_FOR_ANDAND_OROR: {
                LVALUE* llvm_value = get_stack_ptr_value_from_index(llvm_stack_ptr, -1);

                num_value_for_andand_oror--;

                LVALUE llvm_value2;
                llvm_value2 = trunc_value(llvm_value, 64);

                Builder.CreateAlignedStore(llvm_value2.value, value_for_andand_oror[num_value_for_andand_oror], 8);

                MASSERT(num_value_for_andand_oror >= 0);
                }
                break;

            case OP_LOAD_VALUE_FOR_ANDAND_OROR: {
                dec_stack_ptr(&llvm_stack_ptr, 1);

                LVALUE llvm_value;
                //llvm_value.value = value_for_andand_oror[num_value_for_andand_oror];
                llvm_value.value = Builder.CreateLoad(value_for_andand_oror[num_value_for_andand_oror], "value_for_andand_oror");
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
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

                std::string global_stack_ptr_address_name("global_stack_ptr_address");
                Value* global_stack_ptr_address_value = params[global_stack_ptr_address_name];

                Value* loaded_global_stack_ptr_address_value = Builder.CreateAlignedLoad(global_stack_ptr_address_value, 8, "loaded_global_stack_ptr_address");

                /// zero clear///
                Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
                Builder.CreateAlignedStore(zero, loaded_global_stack_ptr_address_value, 8);

                /// store ///
                Builder.CreateAlignedStore(llvm_value.value, loaded_global_stack_ptr_address_value, 8);

                /// inc pointer ///
                Value* lvalue = loaded_global_stack_ptr_address_value;
                Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 1, true));
                Value* inc_ptr_value = Builder.CreateGEP(lvalue, rvalue, "inc_ptr_value");

                Builder.CreateStore(inc_ptr_value, global_stack_ptr_address_value);

                dec_stack_ptr(&llvm_stack_ptr, 1);
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

                //Value* dec_ptr_value2 = Builder.CreateCast(Instruction::IntToPtr, dec_ptr_value, PointerType::get(IntegerType::get(TheContext, 8), 0));


    
                LVALUE llvm_value;
                llvm_value.value = Builder.CreateAlignedLoad(dec_ptr_value, 8, "value");
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.constant_int_value = FALSE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

                trunc_variable(&llvm_value, size);

                /// dec global stack ptr ///
                Builder.CreateAlignedStore(dec_ptr_value, global_stack_ptr_address_value, 8);

                push_value_to_stack_ptr(&llvm_stack_ptr, &llvm_value);
                }
                break;


            default:
                if(!compile_to_native_code2(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code3(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code4(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code5(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code6(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code7(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code8(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code9(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code10(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code11(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                if(!compile_to_native_code12(code, constant, klass, method, method_path2, inst, &pc, &llvm_stack_ptr, llvm_stack, params, &current_block, &function, var_num, &try_catch_label_name))
                {
                    return FALSE;
                }
                break;
        }

/*
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT && strcmp(METHOD_NAME2(klass, method), "initialize") != 0 && strcmp(METHOD_NAME2(klass, method), "finalize") != 0) {
    LVALUE* p = llvm_stack;

    while(p < llvm_stack_ptr) {
        call_show_value_in_jit(p->value);
        p++;
    }
}
*/
    }

    // Finish off the function.
    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 1, true));

    //Builder.SetInsertPoint(current_block);
    Builder.CreateRet(ret_value);

    // Validate the generated code, checking for consistency.
    verifyFunction(*function);

    // Run the optimizer on the function.
    TheFPM->run(*function);

    return TRUE;
}


} // extern "C"
