#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code2(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_STORE: {
            int index = *(int*)*pc;
            (*pc) += sizeof(int);

            LVALUE* llvm_value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            store_llvm_value_to_lvar_with_offset(llvm_stack, index, llvm_value);

            }
            break;

        case OP_LOAD: {
            int index = *(int*)*pc;
            (*pc) += sizeof(int);

            int size = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE llvm_value;
            get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, index);

            trunc_variable(&llvm_value, size);

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOAD_ADDRESS: {
            int index = *(int*)(*pc);
            (*pc) += sizeof(int);

            std::string lvar_arg_name("lvar");
            Value* lvar_value = params[lvar_arg_name];

            LVALUE llvm_value;
            Value* add_value = ConstantInt::get(TheContext, llvm::APInt(64, index, true)); 
            llvm_value.value = Builder.CreateGEP(lvar_value, add_value, "gepaddtmp");
            llvm_value.lvar_address_index = index;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCBYTE: 
            {
                int value = *(int*)(*pc);
                (*pc) += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(8, value, true)); 
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.constant_int_value = TRUE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCUBYTE: 
            {
                int value = *(int*)(*pc);
                (*pc) += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(8, value, false)); 
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.constant_int_value = TRUE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCSHORT: 
            {
                int value = *(int*)(*pc);
                (*pc) += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(16, value, true)); 
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.constant_int_value = TRUE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCUSHORT: 
            {
                int value = *(int*)(*pc);
                (*pc) += sizeof(int);

                LVALUE llvm_value;
                llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(16, value, false)); 
                llvm_value.lvar_address_index = -1;
                llvm_value.lvar_stored = FALSE;
                llvm_value.constant_int_value = TRUE;
                llvm_value.constant_float_value = FALSE;
                llvm_value.float_value = FALSE;

                push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCINT: {
            int value = *(int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE llvm_value;
            llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = TRUE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCUINT: {
            unsigned int value = *(unsigned int*)(*pc);
            (*pc) += sizeof(int);

            LVALUE llvm_value;
            llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, false)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = TRUE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCLONG: {
            int value1 = *(int*)(*pc);
            (*pc) += sizeof(int);

            int value2 = *(int*)(*pc);
            (*pc) += sizeof(int);

            clint64 lvalue;

            memcpy(&lvalue, &value1, sizeof(int));
            memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

            LVALUE llvm_value;
            llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, true)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = TRUE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCULONG: {
            int value1 = *(int*)(*pc);
            (*pc) += sizeof(int);

            int value2 = *(int*)(*pc);
            (*pc) += sizeof(int);

            clint64 lvalue;

            memcpy(&lvalue, &value1, sizeof(int));
            memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

            LVALUE llvm_value;
            llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, false)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = TRUE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCNULL: {
            int value = 0;

            LVALUE llvm_value;
            llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = TRUE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCPOINTER: {
            int value1 = *(int*)(*pc);
            (*pc) += sizeof(int);

            int value2 = *(int*)(*pc);
            (*pc) += sizeof(int);

            clint64 lvalue;

            memcpy(&lvalue, &value1, sizeof(int));
            memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

            LVALUE llvm_value;
            llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(64, lvalue, false)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCFLOAT: {
            float value1 = *(float*)(*pc);
            (*pc) += sizeof(float);

            LVALUE llvm_value;
            llvm_value.value = ConstantFP::get(TheContext, llvm::APFloat(value1)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = TRUE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCDOUBLE: {
            int value1 = *(int*)(*pc);
            (*pc) += sizeof(int);

            int value2 = *(int*)(*pc);
            (*pc) += sizeof(int);

            double lvalue;

            memcpy(&lvalue, &value1, sizeof(int));
            memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

            LVALUE llvm_value;
            llvm_value.value = ConstantFP::get(TheContext, llvm::APFloat(lvalue)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = TRUE;
            llvm_value.float_value = FALSE;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BADD:
        case OP_SADD:
        case OP_IADD: 
        case OP_LADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAdd(lvalue->value, rvalue->value, "addtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBADD: 
        case OP_USADD:
        case OP_UIADD:
        case OP_ULADD: 
        case OP_CADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value  = Builder.CreateAdd(lvalue->value, rvalue->value, "addtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);

            LVALUE rvalue2;
            rvalue2 = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateGEP(lvalue->value, rvalue2.value, "addtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
            break;

        case OP_BSUB:
        case OP_SSUB:
        case OP_ISUB:
        case OP_LSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue->value = Builder.CreateCast(Instruction::PtrToInt, lvalue->value, Type::getInt64Ty(TheContext), "value2");

            LVALUE rvalue2;
            rvalue2 = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue2.value, "subtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PPSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue->value = Builder.CreateCast(Instruction::PtrToInt, lvalue->value, Type::getInt64Ty(TheContext), "value2");
            rvalue->value = Builder.CreateCast(Instruction::PtrToInt, rvalue->value, Type::getInt64Ty(TheContext), "value2");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 64);

            //llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 8), 0));

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);
            }
            break;

        case OP_UBSUB: 
        case OP_USSUB:
        case OP_UISUB:
        case OP_ULSUB: 
        case OP_CSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BMULT:
        case OP_SMULT:
        case OP_IMULT: 
        case OP_LMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBMULT: 
        case OP_USMULT:
        case OP_UIMULT:
        case OP_ULMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BDIV:
        case OP_SDIV:
        case OP_IDIV: 
        case OP_LDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            int value_size;
            if(inst == OP_BDIV) {
                value_size = 8;
            }
            else if(inst == OP_SDIV) {
                value_size = 16;
            }
            else if(inst == OP_IDIV) {
                value_size = 32;
            }
            else {
                value_size = 64;
            }

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBDIV: 
        case OP_USDIV:
        case OP_UIDIV:
        case OP_ULDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            int value_size;
            if(inst == OP_UBDIV) {
                value_size = 8;
            }
            else if(inst == OP_USDIV) {
                value_size = 16;
            }
            else if(inst == OP_UIDIV) {
                value_size = 32;
            }
            else {
                value_size = 64;
            }

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateUDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BMOD: 
        case OP_SMOD:
        case OP_IMOD:
        case OP_LMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            int value_size;
            if(inst == OP_BMOD) {
                value_size = 8;
            }
            else if(inst == OP_SMOD) {
                value_size = 16;
            }
            else if(inst == OP_IMOD) {
                value_size = 32;
            }
            else {
                value_size = 64;
            }

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSRem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBMOD:
        case OP_USMOD:
        case OP_UIMOD:
        case OP_ULMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            int value_size;

            if(inst == OP_UBMOD) {
                value_size = 8;
            }
            else if(inst == OP_USMOD) {
                value_size = 16;
            }
            else if(inst == OP_UIMOD) {
                value_size = 32;
            }
            else {
                value_size = 64;
            }

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateURem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BLSHIFT:
        case OP_SLSHIFT:
        case OP_ILSHIFT: 
        case OP_LLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBLSHIFT: 
        case OP_USLSHIFT:
        case OP_UILSHIFT:
        case OP_ULLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BRSHIFT:
        case OP_SRSHIFT:
        case OP_IRSHIFT:
        case OP_LRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBRSHIFT: 
        case OP_USRSHIFT:
        case OP_UIRSHIFT:
        case OP_ULRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateLShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BAND: 
        case OP_UBAND:
        case OP_SAND:
        case OP_USAND:
        case OP_IAND:
        case OP_UIAND:
        case OP_LAND: 
        case OP_ULAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BXOR: 
        case OP_UBXOR:
        case OP_SXOR:
        case OP_USXOR:
        case OP_IXOR: 
        case OP_UIXOR:
        case OP_LXOR: 
        case OP_ULXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BOR: 
        case OP_UBOR:
        case OP_SOR:
        case OP_USOR:
        case OP_IOR:
        case OP_UIOR:
        case OP_LOR: 
        case OP_ULOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BCOMPLEMENT:
        case OP_UBCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            trunc_value_from_inst(lvalue, inst);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SCOMPLEMENT:
        case OP_USCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            trunc_value_from_inst(lvalue, inst);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0xFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ICOMPLEMENT:
        case OP_UICOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            trunc_value_from_inst(lvalue, inst);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0xFFFFFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;

            llvm_value.float_value = FALSE;
            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LCOMPLEMENT:
        case OP_ULCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            trunc_value_from_inst(lvalue, inst);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0xFFFFFFFFFFFFFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = FALSE;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FADD:
        case OP_DADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFAdd(lvalue->value, rvalue->value, "faddtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = TRUE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FSUB: 
        case OP_DSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFSub(lvalue->value, rvalue->value, "fsubtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = TRUE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FMULT:
        case OP_DMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFMul(lvalue->value, rvalue->value, "fmulttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = TRUE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FDIV:
        case OP_DDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            trunc_value_from_inst(lvalue, inst);
            trunc_value_from_inst(rvalue, inst);

            BOOL value_is_float = inst == OP_FDIV;
            BOOL value_is_double = inst == OP_DDIV;

            if_value_is_zero_entry_exception_object(rvalue->value, 0, value_is_float, value_is_double, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFDiv(lvalue->value, rvalue->value, "fdivtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.constant_int_value = FALSE;
            llvm_value.constant_float_value = FALSE;
            llvm_value.float_value = TRUE;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
    }

    return TRUE;
}

}
