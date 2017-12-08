#include "jit_common.hpp"

extern "C"
{
Value* llvm_create_string(char* str)
{
    Constant* str_constant = ConstantDataArray::getString(TheModule->getContext(), str, true);

    GlobalVariable* gvar = new GlobalVariable(*TheModule, ArrayType::get(IntegerType::get(TheContext, 8), strlen(str)+1), true, GlobalValue::PrivateLinkage, 0, "global_string");
    gvar->setAlignment(1);

    gvar->setInitializer(str_constant);

    Value* value = Builder.CreateCast(Instruction::BitCast, gvar, PointerType::get(IntegerType::get(TheContext, 8), 0));

    return value;
}

LVALUE* get_stack_ptr_value_from_index(LVALUE* llvm_stack_ptr, int index)
{
    return llvm_stack_ptr + index;
}

void dec_stack_ptr(LVALUE** llvm_stack_ptr, int value)
{
    int i;
    for(i=0; i<value; i++) {
        (*llvm_stack_ptr)->value = 0;
        (*llvm_stack_ptr)->lvar_address_index = -1;
        (*llvm_stack_ptr)->lvar_stored = FALSE;
        (*llvm_stack_ptr)->constant_int_value = FALSE;
        (*llvm_stack_ptr)->constant_float_value = FALSE;
        (*llvm_stack_ptr)->float_value = FALSE;

        (*llvm_stack_ptr)--;
    }

    (*llvm_stack_ptr)->value = 0;
    (*llvm_stack_ptr)->lvar_address_index = -1;
    (*llvm_stack_ptr)->lvar_stored = FALSE;
    (*llvm_stack_ptr)->constant_int_value = FALSE;
    (*llvm_stack_ptr)->constant_float_value = FALSE;
    (*llvm_stack_ptr)->float_value = FALSE;
}

void push_value_to_stack_ptr(LVALUE** llvm_stack_ptr, LVALUE* value)
{
    (**llvm_stack_ptr) = *value;
    (*llvm_stack_ptr)++;
}

void insert_value_to_stack_ptr_with_offset(LVALUE** llvm_stack_ptr, LVALUE* value, int offset)
{
    (*(*llvm_stack_ptr+offset)) = *value;
}

void store_llvm_value_to_lvar_with_offset(LVALUE* llvm_stack, int index, LVALUE* llvm_value)
{
    /// 0 clear align 8 byte ///
    Value* zero = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateStore(zero, llvm_stack[index].value);

    /// store ///
    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);
    
    /// go ///
    Builder.CreateAlignedStore(llvm_value2.value, llvm_stack[index].value, 8);

    llvm_stack[index].lvar_address_index = llvm_value->lvar_address_index;
    llvm_stack[index].lvar_stored = TRUE;
    llvm_stack[index].constant_int_value = FALSE;
    llvm_stack[index].constant_float_value = FALSE;
    llvm_stack[index].float_value = FALSE;
}

void get_llvm_value_from_lvar_with_offset(LVALUE* result, LVALUE* llvm_stack, int index)
{
    LVALUE* llvm_value = llvm_stack + index;





    result->value = Builder.CreateLoad(llvm_value->value, "lvar"); // load from allocated value






    result->lvar_address_index = llvm_value->lvar_address_index;
    result->lvar_stored = llvm_value->lvar_stored;
    result->constant_int_value = FALSE;
    result->constant_float_value = FALSE;
    result->float_value = FALSE;
}

LVALUE get_vm_stack_ptr_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

/*
    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* stack_pointer_offset_value = Builder.CreateAdd(lvalue, rvalue, "stack_pointer_offset_value", true, true);
*/
    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
    Value* stack_pointer_offset_value = Builder.CreateGEP(lvalue, rvalue, "stack_pointer_offset_value");

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(stack_pointer_offset_value, align, "stack_pointer_offset_value");

    switch(align) {
        case 1:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            break;

        case 2:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            break;

        case 4:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            break;
    }

    result.lvar_address_index = -1;
    result.lvar_stored = FALSE;
    result.constant_int_value = FALSE;
    result.constant_float_value = FALSE;
    result.float_value= FALSE;

    return result;
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
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            break;

        case 2:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            break;

        case 4:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            break;
    }

    result.lvar_address_index = -1;
    result.lvar_stored = FALSE;
    result.constant_int_value = FALSE;
    result.constant_float_value = FALSE;
    result.float_value= FALSE;

    return result;
}

void llvm_stack_to_vm_stack(LVALUE* llvm_stack_ptr, std::map<std::string, Value*> params, BasicBlock* current_block, int num)
{
    int i;
    for(i=0; i<num; i++) {
        LVALUE* llvm_value = llvm_stack_ptr + i - num;
        push_value_to_vm_stack_ptr_with_aligned(params, current_block, llvm_value);
    }
}

void if_value_is_zero_ret_zero(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* zero = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));

    Value* comp = Builder.CreateICmpEQ(value, zero, "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

void if_value_is_null_ret_zero(Value* value, int value_bit, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block)
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


LVALUE get_lvar_value_from_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*offset, true));
    Value* offset_lvar = Builder.CreateAdd(lvalue, rvalue, "offset_lvar", true, true);

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(offset_lvar, 8, "offset_lvar");
    result.lvar_address_index = -1;
    result.lvar_stored = TRUE;
    result.constant_int_value = FALSE;
    result.constant_float_value = FALSE;
    result.float_value = FALSE;

    return result;
}

AllocaInst* create_entry_block_alloca(Function* function, int index)
{
    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
    char var_name[128];
    snprintf(var_name, 128, "lvar$%d$", index);
    return builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, var_name);
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

void if_value_is_zero_entry_exception_object(Value* value, int value_size, BOOL value_is_float, BOOL value_is_double, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block, char* class_name, char* message)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* rvalue;
    if(value_is_float) {
        double value = 0.0;
        rvalue = ConstantFP::get(TheContext, llvm::APFloat(value)); 
        //rvalue = Builder.CreateCast(Instruction::FPTrunc, rvalue, Type::getFloatTy(TheContext));
    }
    else if(value_is_double) {
        double value = 0.0;
        rvalue = ConstantFP::get(TheContext, llvm::APFloat(value)); 
    }
    else {
        rvalue = ConstantInt::get(TheContext, llvm::APInt(value_size, 0, true));
    }

    Value* comp = Builder.CreateICmpEQ(value, rvalue, "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    call_entry_exception_object_with_class_name2(params, class_name, message);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

void vm_lvar_to_llvm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);
        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }
}

void finish_method_call(Value* result, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char** try_catch_label_name, sByteCode* code, int real_param_num, int var_num, LVALUE* llvm_stack, LVALUE* llvm_stack_ptr)
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

void lvar_of_vm_to_lvar_of_llvm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);
        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value);
    }
}

void lvar_of_llvm_to_lvar_of_vm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value;
        get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, i);

        if(llvm_value.value != 0) {
            store_value_to_lvar_with_offset(params, current_block, i, &llvm_value);
        }
    }
}

void trunc_value_from_inst(LVALUE* value, int inst) 
{
    switch(inst) {
        case OP_ANDAND: 
        case OP_OROR:
            *value = trunc_value(value, 1);
            break;

        case OP_BADD:
        case OP_BSUB:
        case OP_BMULT:
        case OP_BDIV:
        case OP_BMOD: 
        case OP_BLSHIFT:
        case OP_BRSHIFT:
        case OP_BAND: 
        case OP_BXOR: 
        case OP_BOR: 
        case OP_BCOMPLEMENT:
        case OP_BEQ:
        case OP_BNOTEQ:
        case OP_BGT:
        case OP_BLE:
        case OP_BGTEQ:
        case OP_BLEEQ:
        case OP_UBADD: 
        case OP_UBSUB:
        case OP_UBMULT:
        case OP_UBDIV:
        case OP_UBMOD:
        case OP_UBLSHIFT:
        case OP_UBRSHIFT: 
        case OP_UBAND:
        case OP_UBXOR:
        case OP_UBOR:
        case OP_UBCOMPLEMENT:
        case OP_UBEQ:
        case OP_UBNOTEQ:
        case OP_UBGT:
        case OP_UBLE: 
        case OP_UBGTEQ: 
        case OP_UBLEEQ:
            *value = trunc_value(value, 8);
            break;

        case OP_SADD:
        case OP_SSUB:
        case OP_SMULT:
        case OP_SDIV:
        case OP_SMOD:
        case OP_SLSHIFT:
        case OP_SRSHIFT:
        case OP_SAND:
        case OP_SXOR:
        case OP_SOR:
        case OP_SCOMPLEMENT:
        case OP_SEQ:
        case OP_SNOTEQ:
        case OP_SGT:
        case OP_SLE:
        case OP_SGTEQ:
        case OP_SLEEQ:
        case OP_USADD:
        case OP_USSUB:
        case OP_USMULT:
        case OP_USDIV:
        case OP_USMOD:
        case OP_USLSHIFT:
        case OP_USRSHIFT:
        case OP_USAND:
        case OP_USXOR:
        case OP_USOR:
        case OP_USCOMPLEMENT:
        case OP_USEQ:
        case OP_USNOTEQ:
        case OP_USGT:
        case OP_USLE:
        case OP_USGTEQ:
        case OP_USLEEQ:
            *value = trunc_value(value, 16);
            break;

        case OP_IADD: 
        case OP_ISUB:
        case OP_IMULT:
        case OP_IDIV:
        case OP_IMOD:
        case OP_ILSHIFT: 
        case OP_IRSHIFT:
        case OP_IAND:
        case OP_IXOR: 
        case OP_IOR:
        case OP_ICOMPLEMENT:
        case OP_IEQ:
        case OP_INOTEQ: 
        case OP_IGT: 
        case OP_ILE: 
        case OP_ILEEQ: 
        case OP_IGTEQ: 
        case OP_UIADD:
        case OP_UISUB:
        case OP_UIMULT:
        case OP_UIDIV:
        case OP_UIMOD:
        case OP_UILSHIFT:
        case OP_UIRSHIFT:
        case OP_UIAND:
        case OP_UIXOR:
        case OP_UIOR:
        case OP_UICOMPLEMENT:
        case OP_UIEQ:
        case OP_UINOTEQ:
        case OP_UILE:
        case OP_UIGT:
        case OP_UIGTEQ:
        case OP_UILEEQ: 
        case OP_CADD:
        case OP_CSUB:
        case OP_CEQ:
        case OP_CNOTEQ:
        case OP_CGT:
        case OP_CLE:
        case OP_CGTEQ:
        case OP_CLEEQ:
        case OP_OBJ_IDENTIFY:
        case OP_LOGICAL_DENIAL:
        case OP_REGEQ: 
        case OP_REGNOTEQ:
            *value = trunc_value(value, 32);
            break;

        case OP_LADD:
        case OP_LSUB:
        case OP_LMULT:
        case OP_LMOD: 
        case OP_LDIV:
        case OP_LLSHIFT: 
        case OP_LRSHIFT:
        case OP_LAND: 
        case OP_LXOR: 
        case OP_LOR: 
        case OP_LCOMPLEMENT:
        case OP_LEQ: 
        case OP_LNOTEQ: 
        case OP_LGT:
        case OP_LLE:
        case OP_LGTEQ:
        case OP_LLEEQ:
        case OP_ULADD: 
        case OP_ULMOD:
        case OP_ULLSHIFT:
        case OP_ULRSHIFT:
        case OP_ULAND:
        case OP_ULXOR:
        case OP_ULOR:
        case OP_ULCOMPLEMENT:
        case OP_ULEQ: 
        case OP_ULNOTEQ: 
        case OP_ULGT: 
        case OP_ULLE: 
        case OP_ULGTEQ: 
        case OP_ULLEEQ:
            *value = trunc_value(value, 64);
            break;

        case OP_FADD:
        case OP_FSUB:
        case OP_FMULT:
        case OP_FDIV:
        case OP_FEQ:
        case OP_FNOTEQ:
        case OP_FGT:
        case OP_FLE:
        case OP_FGTEQ:
        case OP_FLEEQ:
            *value = trunc_value_to_float_or_double(value, 32);
            break;

        case OP_DADD:
        case OP_DSUB:
        case OP_DMULT:
        case OP_DDIV:
        case OP_DEQ:
        case OP_DNOTEQ:
        case OP_DGT:
        case OP_DLE:
        case OP_DGTEQ:
        case OP_DLEEQ:
            *value = trunc_value_to_float_or_double(value, 64);
            break;

        case OP_PADD: 
        case OP_PEQ: 
        case OP_PNOTEQ: 
        case OP_PGT: 
        case OP_PLE:
        case OP_PGTEQ: 
        case OP_PLEEQ: 
            *value = trunc_value_to_pointer(value);
            break;
    }
}

void store_value_to_vm_lvar(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset, LVALUE* llvm_value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, offset, true));
    Value* lvar_offset_value = Builder.CreateGEP(lvalue, rvalue, "lvar_offset_value");

    /// 0 clear align 8 byte ///
    Value* zero = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateAlignedStore(zero, lvar_offset_value, 8);

    /// trunc ///
    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);

    /// go ///
    Builder.CreateAlignedStore(llvm_value2.value, lvar_offset_value, 8);
}

void llvm_lvar_to_vm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value;
        get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, i);

        if(llvm_value.lvar_stored) {
            store_value_to_vm_lvar(params, current_block, i, &llvm_value);
        }
    }
}
}
