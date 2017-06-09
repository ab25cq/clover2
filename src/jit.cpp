#include "jit_common.hpp"


LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
std::unique_ptr<Module> TheModule;
std::unique_ptr<legacy::FunctionPassManager> TheFPM;
std::unique_ptr<CloverJIT> TheJIT;
std::map<std::string, BasicBlock*> TheLabels;

std::map<std::string, std::unique_ptr<FunctionAST>> LLVMFunctions;

//////////////////////////////////////////////////////////////////////
// JIT main
//////////////////////////////////////////////////////////////////////
#define MAX_COND_JUMP 128

extern "C"
{

static BOOL compile_to_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info, char* method_path2)
{
    std::string func_name(method_path2);
    std::unique_ptr<FunctionAST> llvm_func = llvm::make_unique<FunctionAST>(func_name);

    char* try_catch_label_name = NULL;

    LLVMFunctions[func_name] = std::move(llvm_func);

    Function* function = TheModule->getFunction(func_name);

    // Create a new basic block to start insertion into.
    BasicBlock* current_block = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(current_block);
  
    register char* pc = code->mCodes;
    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

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

    while(pc - code->mCodes < code->mLen) {
        int k;
        for(k=0; k<num_cond_jump; k++) {
            if(pc == cond_jump_labels[k]) {
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

#ifdef MDEBUG
/*
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
call_show_inst_in_jit(inst);
show_inst_in_jit(inst);
}
*/
#endif

        switch(inst) {
            case OP_POP:
                dec_stack_ptr(params, current_block, 1);
                break;

            case OP_POP_N:
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    dec_stack_ptr(params, current_block, value);
                }
                break;

            case OP_REVERSE: {
                Value* llvm_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* llvm_value2 = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                
                dec_stack_ptr(params, current_block, 2);

                push_value_to_stack_ptr(params, current_block, llvm_value2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DUPE: {
                Value* llvm_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_COND_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                Value* conditinal_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                BasicBlock* cond_jump_then_block = BasicBlock::Create(TheContext, "cond_jump_then", function);
                entry_condends[num_cond_jump] = BasicBlock::Create(TheContext, "entry_condend", function);

                Builder.CreateCondBr(conditinal_value, entry_condends[num_cond_jump], cond_jump_then_block);

                Builder.SetInsertPoint(cond_jump_then_block);

                current_block = cond_jump_then_block;

                cond_jump_labels[num_cond_jump] = pc + jump_value;
                num_cond_jump++;

                if(num_cond_jump >= MAX_COND_JUMP) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "overflow number of condjump");
                    return FALSE;
                }
                }
                break;

            case OP_COND_NOT_JUMP: {
                int jump_value = *(int*)pc;
                pc += sizeof(int);

                Value* conditinal_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                BasicBlock* cond_not_jump_then_block = BasicBlock::Create(TheContext, "cond_not_jump_then", function);
                entry_condnotends[num_cond_not_jump] = BasicBlock::Create(TheContext, "entry_condnotend", function);

                Builder.CreateCondBr(conditinal_value, cond_not_jump_then_block, entry_condnotends[num_cond_not_jump]);

                Builder.SetInsertPoint(cond_not_jump_then_block);
                current_block = cond_not_jump_then_block;

                cond_not_jump_labels[num_cond_not_jump] = pc + jump_value;
                num_cond_not_jump++;

                if(num_cond_not_jump >= MAX_COND_JUMP) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "overflow number of condnotjump");
                    return FALSE;
                }
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
                std::string stack_param_name("stack");
                Value* stack_value = params[stack_param_name];

                Value* llvm_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                store_value(llvm_value, stack_value, current_block);

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

                Value* llvm_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                store_value(llvm_value, stack_value, current_block);

                Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object");

                std::vector<Value*> params2;

                Value* param1 = llvm_value;
                params2.push_back(param1);

                Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(vminfo_value);

                (void)Builder.CreateCall(entry_exception_object_fun, params2);

                Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
                Builder.CreateRet(ret_value);

                current_block = BasicBlock::Create(TheContext, "entry_after_throw", function);
                Builder.SetInsertPoint(current_block);
                }
                break;

            case OP_TRY: {
                int tmp = *(int*)pc;
                pc += sizeof(int);

                int catch_label_name_offset = *(int*)pc;
                pc += sizeof(int);

                try_catch_label_name = CONS_str(constant, catch_label_name_offset);

                Function* try_fun = TheModule->getFunction("try_function");

                std::vector<Value*> params2;

                Value* vminfo_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(vminfo_value);

                Value* try_catch_label_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)try_catch_label_name);
                params2.push_back(try_catch_label_value);

                (void)Builder.CreateCall(try_fun, params2);
                }
                break;

            case OP_HEAD_OF_EXPRESSION: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                Function* function = TheModule->getFunction("run_head_of_expression");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param1);

                Value* param2 = get_value_from_char_array(sname);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)sline);
                params2.push_back(param3);

                Builder.CreateCall(function, params2);
                }
                break;

            case OP_SIGINT: {
                Function* sigint_function = TheModule->getFunction("run_sigint");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* result = Builder.CreateCall(sigint_function, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
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

            case OP_STORE: {
                int index = *(int*)pc;
                pc += sizeof(int);

                Value* llvm_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                store_value_to_lvar_with_offset(params, current_block, index, llvm_value);
                }
                break;

            case OP_LOAD: {
                int index = *(int*)pc;
                pc += sizeof(int);

                Value* llvm_value = get_lvar_value_from_offset(params, current_block, index);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LOAD_ADDRESS: {
                int index = *(int*)pc;
                pc += sizeof(int);

                Function* load_address_fun = TheModule->getFunction("run_load_address");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                std::string lvar_arg_name("lvar");
                Value* param5 = params[lvar_arg_name];
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)index);
                params2.push_back(param6);

                Builder.CreateCall(load_address_fun, params2);
                }
                break;

            case OP_LDCBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(8, value, true)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCUBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(8, value, false)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(16, value, true)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCUSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(16, value, false)); 

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCINT: {
                int value = *(int*)pc;
                pc += sizeof(int);

                Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCUINT: {
                unsigned int value = *(unsigned int*)pc;
                pc += sizeof(int);

                Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, false)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCLONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                Function* run_ldclong_fun = TheModule->getFunction("run_ldclong");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value1);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value2);
                params2.push_back(param3);

                Builder.CreateCall(run_ldclong_fun, params2);
                }
                break;

            case OP_LDCULONG: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                Function* run_ldculong_fun = TheModule->getFunction("run_ldculong");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value1);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value2);
                params2.push_back(param3);

                Builder.CreateCall(run_ldculong_fun, params2);
                }
                break;

            case OP_LDCNULL: {
                int value = 0;
                Value* llvm_value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_LDCPOINTER: {
                int value1 = *(int*)pc;
                pc += sizeof(int);

                int value2 = *(int*)pc;
                pc += sizeof(int);

                Function* run_ldclong_fun = TheModule->getFunction("run_ldcpointer");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value1);
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)value2);
                params2.push_back(param3);

                Builder.CreateCall(run_ldclong_fun, params2);
                }
                break;

            case OP_LDCFLOAT: {
                float value1 = *(float*)pc;
                pc += sizeof(float);

                stack_ptr->mFloatValue = value1;
                stack_ptr++;

                Value* llvm_value = ConstantFP::get(TheContext, llvm::APFloat(value1)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
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

                Value* llvm_value = ConstantFP::get(TheContext, llvm::APFloat(lvalue)); 

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_BADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_BOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_SADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_SOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_IADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ISUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ILSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIADD: 
            case OP_CADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UISUB: 
            case OP_CSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UILSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateSRem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", true, false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULADD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULSUB: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULMULT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateMul(lvalue, rvalue, "multmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULDIV: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateUDiv(lvalue, rvalue, "divtmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULMOD: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateURem(lvalue, rvalue, "remtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULLSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateShl(lvalue, rvalue, "lshifttmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULRSHIFT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateLShr(lvalue, rvalue, "rshifttmp", false);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateAnd(lvalue, rvalue, "andtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULXOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULOR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateOr(lvalue, rvalue, "ortmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_BCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_UBCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_SCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_USCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_ICOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UICOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFFFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_ULCOMPLEMENT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                Value* rvalue = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFFFFFFFFFFFFFFFF);

                Value* llvm_value = Builder.CreateXor(lvalue, rvalue, "xortmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_FADD: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFAdd(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_FSUB: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFSub(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_FMULT: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFMul(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_FDIV: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateFDiv(lvalue, rvalue, "divtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DADD: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFAdd(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DSUB: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFSub(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DMULT: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFMul(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_DDIV: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                if_value_is_zero_entry_exception_object(rvalue, params, var_num, info, function, &current_block, "Exception", "division by zero");

                Value* llvm_value = Builder.CreateFDiv(lvalue, rvalue, "divtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_PADD: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateAdd(lvalue, rvalue, "addtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_PSUB: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_PPSUB: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateSub(lvalue, rvalue, "subtmp", false, true);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_BEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_BLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_UBGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UBGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_UBLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 1);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_SLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_USGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_USGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_USLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 2);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_IEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateICmpEQ(lvalue, rvalue, "IEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_INOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1 ,4);

                Value* result = Builder.CreateICmpNE(lvalue, rvalue, "INOTEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_IGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateICmpSGT(lvalue, rvalue, "IGT");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, result, 4);
                }
                break;

            case OP_ILE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateICmpSLT(lvalue, rvalue, "ILE");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;
            
            case OP_IGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateICmpSGE(lvalue, rvalue, "IGETQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_ILEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateICmpSLE(lvalue, rvalue, "ILEEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_UIEQ:
            case OP_CEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UINOTEQ: 
            case OP_CNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_UIGT:
            case OP_CGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UILE: 
            case OP_CLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UIGTEQ:
            case OP_CGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_UILEEQ: 
            case OP_CLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "noteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_ULGT: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpUGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULLE: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpULT(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_ULGTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpUGE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;
                
            case OP_ULLEEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateICmpULE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFCmpOEQ(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FNOTEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFCmpONE(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FGT: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFCmpOGT(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FLE: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFCmpOLT(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FGTEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFCmpOGE(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_FLEEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* llvm_value = Builder.CreateFCmpOLE(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFCmpOEQ(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DNOTEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFCmpONE(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DGT: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFCmpOGT(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DLE: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFCmpOLT(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DGTEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFCmpOGE(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_DLEEQ: {
                Value* lvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -2, 8);
                Value* rvalue = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                Value* llvm_value = Builder.CreateFCmpOLE(lvalue, rvalue, "addtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PEQ: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PNOTEQ: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateICmpNE(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PGT: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateICmpSGT(lvalue, rvalue, "gttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PLE: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateICmpSLT(lvalue, rvalue, "lttmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PGTEQ: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateICmpSGE(lvalue, rvalue, "gteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_PLEEQ: {
                Value* lvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* rvalue = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateICmpSLE(lvalue, rvalue, "lteqtmp");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_REGEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Function* function = TheModule->getFunction("regex_equals");

                std::vector<Value*> params2;
                params2.push_back(lvalue);
                params2.push_back(rvalue);

                Value* result = Builder.CreateCall(function, params2);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;


            case OP_REGNOTEQ: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Function* function = TheModule->getFunction("regex_equals");

                std::vector<Value*> params2;
                params2.push_back(lvalue);
                params2.push_back(rvalue);

                Value* result = Builder.CreateCall(function, params2);

                Value* result2 = Builder.CreateICmpEQ(result, ConstantInt::get(TheContext, llvm::APInt(32, 0, true)), "ifcond");


                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result2);
                }
                break;

            case OP_OBJ_IDENTIFY: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateICmpEQ(lvalue, rvalue, "IEQ");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_CLASSNAME: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                if_value_is_zero_entry_exception_object(value, params, var_num, info, function, &current_block, "Exception", "Null pointer exception(1)");

                Function* fun = TheModule->getFunction("get_string_object_of_object_name");

                std::vector<Value*> params2;
                params2.push_back(value);

                Value* result = Builder.CreateCall(fun, params2);

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_IMPLEMENTS: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(1)");
                    return FALSE;
                }

                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                if_value_is_zero_entry_exception_object(value, params, var_num, info, function, &current_block, "Exception", "Null pointer exception(2)");

                Function* fun = TheModule->getFunction("object_implements_interface");

                std::vector<Value*> params2;

                params2.push_back(value);

                Value* param2 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                params2.push_back(param2);

                Value* result = Builder.CreateCall(fun, params2);

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_ANDAND: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateAnd(lvalue, rvalue, "ANDAND");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_OROR: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -2, 4);
                Value* rvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* result = Builder.CreateOr(lvalue, rvalue, "OROR");

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr(params, current_block, result);
                }
                break;

            case OP_LOGICAL_DENIAL: {
                Value* lvalue = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                Value* rvalue = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

                Value* llvm_value = Builder.CreateICmpEQ(lvalue, rvalue, "eqtmp");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_INVOKE_METHOD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int method_index = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);
                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(2)");
                    return FALSE;
                }

                if(method_index < 0 || method_index >= klass->mNumMethods) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_METHOD: Method not found");
                    return FALSE;
                }

                sCLMethod* method = klass->mMethods + method_index;

                if(!compile_invoking_method(klass, method, stack, var_num, &stack_ptr, info, params, &current_block, function, try_catch_label_name))
                {
                    return FALSE;
                }
                }
                break;

            case OP_INVOKE_VIRTUAL_METHOD: {
                int num_real_params = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("invoke_virtual_method");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_real_params);
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param2);

                std::string stack_value_name("stack");
                Value* param3 = params[stack_value_name];
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param4);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param5 = params[stack_ptr_address_name];
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(param7);

                Value* param8 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param8);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
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

                Function* fun = TheModule->getFunction("invoke_dynamic_method");

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

                Value* param8 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param8);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param9 = params[stack_ptr_address_name];
                params2.push_back(param9);

                Value* param10 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param10);

                Value* param11 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)code);
                params2.push_back(param11);

                Value* param12 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param12);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_INVOKE_BLOCK: {
                int num_params = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("invoke_block_in_jit");

                std::vector<Value*> params2;

                Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_params);
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param4 = params[stack_ptr_address_name];
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_NEW: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                BOOL flg_array = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(3)");
                    return FALSE;
                }

                if(flg_array) {
                    Value* array_num_value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                    dec_stack_ptr(params, current_block, 1);

                    Function* function = TheModule->getFunction("create_array_object");

                    std::vector<Value*> params2;
                    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                    params2.push_back(klass_value);
                    params2.push_back(array_num_value);

                    Value* llvm_value = Builder.CreateCall(function, params2);

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                else {
                    Function* function = TheModule->getFunction("create_object");

                    std::vector<Value*> params2;
                    Value* klass_value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)klass);
                    params2.push_back(klass_value);

                    Value* llvm_value = Builder.CreateCall(function, params2);

                    push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                }
                break;

            case OP_LOAD_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* load_field_fun = TheModule->getFunction("run_load_field");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(load_field_fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_LOAD_FIELD_ADDRESS: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_load_field_address");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_FIELD: {
                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_store_field");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_LOAD_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_load_class_field");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
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

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_CLASS_FIELD: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int field_index = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_store_class_field");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)field_index);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)offset);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_LOAD_ELEMENT: {
                Function* fun = TheModule->getFunction("run_load_element");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_ELEMENT: {
                Function* fun = TheModule->getFunction("run_store_element");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_STORE_VALUE_TO_INT_ADDRESS: 
            case OP_STORE_VALUE_TO_UINT_ADDRESS:
            case OP_STORE_VALUE_TO_CHAR_ADDRESS:
            case OP_STORE_VALUE_TO_BOOL_ADDRESS:
            case OP_STORE_VALUE_TO_OBJECT_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);

                store_value_with_aligned(value, address, current_block, 4);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;
            
            case OP_STORE_VALUE_TO_BYTE_ADDRESS:
            case OP_STORE_VALUE_TO_UBYTE_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);

                store_value_with_aligned(value, address, current_block, 1);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 1);
                }
                break;

            case OP_STORE_VALUE_TO_SHORT_ADDRESS:
            case OP_STORE_VALUE_TO_USHORT_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);

                store_value_with_aligned(value, address, current_block, 2);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 1);
                }
                break;

            case OP_STORE_VALUE_TO_LONG_ADDRESS:
            case OP_STORE_VALUE_TO_ULONG_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);

                store_value_with_aligned(value, address, current_block, 8);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 1);
                }
                break;

            case OP_STORE_VALUE_TO_FLOAT_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);

                store_value_with_aligned(value, address, current_block, 4);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

            case OP_STORE_VALUE_TO_DOUBLE_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);

                store_value_with_aligned(value, address, current_block, 8);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 4);
                }
                break;

            case OP_STORE_VALUE_TO_POINTER_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -2);
                Value* value = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                store_value_with_aligned(value, address, current_block, 8);

                dec_stack_ptr(params, current_block, 2);
                push_value_to_stack_ptr_with_aligned(params, current_block, value, 8);
                }
                break;

            case OP_LOAD_VALUE_FROM_INT_ADDRESS:
            case OP_LOAD_VALUE_FROM_UINT_ADDRESS:
            case OP_LOAD_VALUE_FROM_CHAR_ADDRESS:
            case OP_LOAD_VALUE_FROM_BOOL_ADDRESS:
            case OP_LOAD_VALUE_FROM_OBJECT_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 4, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LOAD_VALUE_FROM_BYTE_ADDRESS:
            case OP_LOAD_VALUE_FROM_UBYTE_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 1, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 1);
                }
                break;

            case OP_LOAD_VALUE_FROM_SHORT_ADDRESS:
            case OP_LOAD_VALUE_FROM_USHORT_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 2, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 2);
                }
                break;

            case OP_LOAD_VALUE_FROM_LONG_ADDRESS:
            case OP_LOAD_VALUE_FROM_ULONG_ADDRESS:
            case OP_LOAD_VALUE_FROM_POINTER_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 8, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_LOAD_VALUE_FROM_FLOAT_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 4, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 4);
                }
                break;

            case OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS: {
                Value* address = get_stack_ptr_pointer_value_from_index(params, current_block, -1);

                Value* llvm_value = Builder.CreateAlignedLoad(address, 8, "llvm_value");

                dec_stack_ptr(params, current_block, 1);
                push_value_to_stack_ptr_with_aligned(params, current_block, llvm_value, 8);
                }
                break;

            case OP_BYTE_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;
                
            case OP_ULONG_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_FLOAT_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_pointer_value_from_index(params, current_block, -1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::PtrToInt, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_BOOL_TO_INTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;
                
            case OP_ULONG_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_FLOAT_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_pointer_value_from_index(params, current_block, -1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::PtrToInt, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_BOOL_TO_UINTEGER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_uinteger");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;



            case OP_BYTE_TO_CBYTE_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_byte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt8Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CUBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ubyte");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_short");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt16Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CUSHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ushort");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CLONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_long");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt64Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_ulong");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue2 = Builder.CreateCast(Instruction::FPTrunc, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CFLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_float");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, value, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CDOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "fvalue");
                Value* fvalue2 = Builder.CreateCast(Instruction::FPExt, fvalue, Type::getDoubleTy(TheContext), "fvalue");

                Function* fun = TheModule->getFunction("create_double");

                std::vector<Value*> params2;

                Value* param1 = fvalue2;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CPOINTER_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CPOINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_pointer");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CCHAR_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getFloatTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* fvalue = Builder.CreateCast(Instruction::Trunc, value, Type::getDoubleTy(TheContext), "fvalue");

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, fvalue, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_integer");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BOOL_TO_CCHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_char");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;
                
            case OP_ULONG_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_FLOAT_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_DOUBLE_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_CHAR_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value2;
                params2.push_back(param1);

                Value* value3 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value3, 4);
                }
                break;

            case OP_BOOL_TO_CBOOL_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Function* fun = TheModule->getFunction("create_bool");

                std::vector<Value*> params2;

                Value* param1 = value;
                params2.push_back(param1);

                Value* value2 = Builder.CreateCall(fun, params2);

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_STRING_CAST: {
                Function* fun = TheModule->getFunction("run_byte_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_SHORT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_short_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_int_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_LONG_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_long_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UBYTE_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_ubyte_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_USHORT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_ushort_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_uint_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_ULONG_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_ulong_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_FLOAT_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_float_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_DOUBLE_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_double_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_BOOL_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_bool_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_REGEX_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_regex_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_POINTER_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_pointer_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CHAR_TO_STRING_CAST : {
                Function* fun = TheModule->getFunction("run_char_to_string_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_BYTE_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_BYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_byte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_SHORT_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_SHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_short_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_INT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_int_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_LONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_long_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_UBYTE_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_UBYTE_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_ubyte_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_USHORT_CAST: {
                Function* fun = TheModule->getFunction("run_cbyte_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_USHORT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_ushort_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_UINT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_ULONG_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_ulong_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;


            case OP_CCHAR_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_FLOAT_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_float_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;


            case OP_CCHAR_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_DOUBLE_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_double_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBYTE_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cbyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUBYTE_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cubyte_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CSHORT_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cshort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CUSHORT_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cushort_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_INTEGER_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_integer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UINTEGER_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_uinteger_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CLONG_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_clong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CULONG_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_culong_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CFLOAT_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cfloat_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CDOUBLE_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cdouble_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CPOINTER_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cpointer_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CCHAR_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cchar_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CBOOL_TO_CHAR_CAST : {
                Function* fun = TheModule->getFunction("run_cbool_to_uint_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_UBYTE_TO_BYTE_CAST: {
                }
                break;

            case OP_FLOAT_TO_BYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;

            case OP_DOUBLE_TO_BYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;

            case OP_POINTER_TO_BYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;

            case OP_CHAR_TO_BYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;

            case OP_BYTE_TO_SHORT_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_UBYTE_TO_SHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_USHORT_TO_SHORT_CAST : {
                }
                break;

            case OP_FLOAT_TO_SHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_DOUBLE_TO_SHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_POINTER_TO_SHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_CHAR_TO_SHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_BYTE_TO_INT_CAST: {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_INT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_INT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_INT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_INT_CAST : {
                }
                break;

            case OP_FLOAT_TO_INT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_INT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_INT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_INT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UBYTE_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_SHORT_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_USHORT_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_INT_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value3");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UINT_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_ULONG_TO_LONG_CAST : {
                }
                break;

            case OP_FLOAT_TO_LONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_DOUBLE_TO_LONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToSI, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_POINTER_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_CHAR_TO_LONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_BYTE_TO_UBYTE_CAST : {
                }
                break;
                
            case OP_SHORT_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_USHORT_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_INT_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_UINT_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_LONG_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_ULONG_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_FLOAT_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_DOUBLE_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_POINTER_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;
                
            case OP_CHAR_TO_UBYTE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 1);
                }
                break;

            case OP_BYTE_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_UBYTE_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_SHORT_TO_USHORT_CAST : {
                }
                break;

            case OP_INT_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_UINT_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_LONG_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_ULONG_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_FLOAT_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_DOUBLE_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_POINTER_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_CHAR_TO_USHORT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 2);
                }
                break;

            case OP_BYTE_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_UINT_CAST : {
                }
                break;

            case OP_LONG_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_UINT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_UINT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_UINT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UBYTE_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_SHORT_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_USHORT_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_INT_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UINT_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_LONG_TO_ULONG_CAST : {
                }
                break;

            case OP_FLOAT_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_DOUBLE_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_POINTER_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_CHAR_TO_ULONG_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_BYTE_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPTrunc, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_CHAR_TO_FLOAT_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getFloatTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_BYTE_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UBYTE_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_SHORT_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_USHORT_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_INT_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UINT_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_LONG_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::SIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_ULONG_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_FLOAT_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPExt, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_CHAR_TO_DOUBLE_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::UIToFP, value, Type::getDoubleTy(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_BYTE_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UBYTE_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_SHORT_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_USHORT_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_INT_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_UINT_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_LONG_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_ULONG_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_CHAR_TO_POINTER_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt64Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 8);
                }
                break;

            case OP_BYTE_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UBYTE_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 1);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_SHORT_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_USHORT_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 2);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_INT_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_UINT_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_LONG_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ULONG_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_FLOAT_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 4);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_DOUBLE_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_float_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::FPToUI, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_POINTER_TO_CHAR_CAST : {
                Value* value = get_stack_ptr_value_from_index_with_aligned(params, current_block, -1, 8);
                dec_stack_ptr(params, current_block, 1);

                Value* value2 = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext), "value2");

                push_value_to_stack_ptr_with_aligned(params, current_block, value2, 4);
                }
                break;

            case OP_ARRAY_TO_CARRAY_CAST: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_array_to_carray_cast");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_GET_ARRAY_LENGTH: {
                Function* fun = TheModule->getFunction("run_get_array_length");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_GLOBAL: {
                Function* fun = TheModule->getFunction("run_get_regex_global");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_IGNORE_CASE: {
                Function* fun = TheModule->getFunction("run_get_regex_ignorecase");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_MULTILINE: {
                Function* fun = TheModule->getFunction("run_get_regex_multiline");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_EXTENDED: {
                Function* fun = TheModule->getFunction("run_get_regex_extended");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_DOTALL: {
                Function* fun = TheModule->getFunction("run_get_regex_dotall");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_ANCHORED: {
                Function* fun = TheModule->getFunction("run_get_regex_anchored");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_DOLLAR_ENDONLY: {
                Function* fun = TheModule->getFunction("run_get_regex_dollar_endonly");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_GET_REGEX_UNGREEDY: {
                Function* fun = TheModule->getFunction("run_get_regex_ungreedy");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CHAR_UPPERCASE: {
                Function* fun = TheModule->getFunction("run_char_uppercase");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CHAR_LOWERCASE: {
                Function* fun = TheModule->getFunction("run_char_lowercase");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                (void)Builder.CreateCall(fun, params2);
                }
                break;

            case OP_CREATE_STRING: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* str = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_string_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(param1);

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_CREATE_BUFFER: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                int size = *(int*)pc;
                pc += sizeof(int);

                char* str = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_buffer_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)str);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(param1);

                Value* param2 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)size);
                params2.push_back(param2);

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_CREATE_PATH: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* buf = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_path_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)buf);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
                params2.push_back(param1);

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            case OP_CREATE_ARRAY: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_array");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_carray");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_SORTABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_sortable_carray");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_EQUALABLE_CARRAY : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_equalable_carray");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_list");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_SORTALBE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_sortable_list");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_EQUALABLE_LIST : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                Function* fun = TheModule->getFunction("run_create_equalable_list");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_TUPLE : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                Function* fun = TheModule->getFunction("run_create_tuple");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
                }
                break;

            case OP_CREATE_HASH : {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int offset = *(int*)pc;
                pc += sizeof(int);

                int offset2 = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);
                char* class_name2 = CONS_str(constant, offset2);

                Function* fun = TheModule->getFunction("run_create_hash");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)var_num);
                params2.push_back(param3);

                Value* param4 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param4);

                Value* param5 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)num_elements);
                params2.push_back(param5);

                Value* param6 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name);
                params2.push_back(param6);

                Value* param7 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)class_name2);
                params2.push_back(param7);

                Value* result = Builder.CreateCall(fun, params2);

                if_value_is_zero_ret_zero(result, params, var_num, info, function, &current_block);
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

                Function* fun = TheModule->getFunction("run_create_block_object");

                std::vector<Value*> params2;

                std::string stack_ptr_address_name("stack_ptr_address");
                Value* param1 = params[stack_ptr_address_name];
                params2.push_back(param1);

                std::string stack_value_name("stack");
                Value* param2 = params[stack_value_name];
                params2.push_back(param2);

                Value* param3 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)constant);
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

                Value* param11 = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)info);
                params2.push_back(param11);

                Builder.CreateCall(fun, params2);
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

                char* regex_str = CONS_str(constant, offset);

                Function* function = TheModule->getFunction("create_regex_object");

                std::vector<Value*> params2;
                Constant* str_constant = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)regex_str);
                Value* param1 = ConstantExpr::getIntToPtr(str_constant, PointerType::get(IntegerType::get(TheContext,8), 0));
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

                Value* llvm_value = Builder.CreateCall(function, params2);

                push_value_to_stack_ptr(params, current_block, llvm_value);
                }
                break;

            default:
                printf("inst %d\n", inst);
                exit(1);
        }

#ifdef MDEBUG
/*
if(inst != OP_HEAD_OF_EXPRESSION && inst != OP_SIGINT) {
    call_show_stack(var_num, info, params);
}
*/
#endif
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

static BOOL run_native_code(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    long stack_id = append_stack_to_stack_list(stack, &stack_ptr);

    info->current_stack = stack;        // for invoking_block in native method
    info->current_var_num = var_num;
    info->stack_id = stack_id;

    char method_path2[METHOD_NAME_MAX + 128];
    create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);
    
    auto ExprSymbol = TheJIT->findSymbol(method_path2);
    assert(ExprSymbol && "Function not found");


    fJITMethodType function = (fJITMethodType)ExprSymbol.getAddress();
    if(!function(stack_ptr, lvar, info, stack, &stack_ptr)) {
        remove_stack_to_stack_list(stack, &stack_ptr);
        return FALSE;
    }

    remove_stack_to_stack_list(stack, &stack_ptr);

    return TRUE;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    char method_path2[METHOD_NAME_MAX + 128];
    create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);

    auto ExprSymbol = TheJIT->findSymbol(method_path2);
    if(!ExprSymbol) {
#ifdef MDEBUG
//printf("compiling %s\n", method_path2);
#endif
        if(!compile_to_native_code(code, constant, stack, var_num, klass, method, info, method_path2)) {
            return FALSE;
        }
#ifdef MDEBUG
//printf("compiling %s end\n", method_path2);
#endif

#ifdef MDEBUG
//        TheModule->dump();
#endif
        auto H = TheJIT->addModule(std::move(TheModule));
        InitializeModuleAndPassManager();
    }

#ifdef MDEBUG
//printf("run_native_code %s.%s%d\n", CLASS_NAME(klass), METHOD_NAME2(klass, method), method->mMethodIndex);
#endif
    if(!run_native_code(code, constant, stack, var_num, klass, method, info)) {
        return FALSE;
    }

    return TRUE;
}

} // extern "C"
