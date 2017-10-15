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
            llvm_value.kind = kLVKindAddress;

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
                llvm_value.kind = kLVKindConstantInt8;

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
                llvm_value.kind = kLVKindConstantUInt8;

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
                llvm_value.kind = kLVKindConstantInt16;

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
                llvm_value.kind = kLVKindConstantUInt16;

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
            llvm_value.kind = kLVKindConstantInt32;

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
            llvm_value.kind = kLVKindConstantUInt32;

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
            llvm_value.kind = kLVKindConstantInt64;

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
            llvm_value.kind = kLVKindConstantUInt64;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDCNULL: {
            int value = 0;

            LVALUE llvm_value;
            llvm_value.value = ConstantInt::get(TheContext, llvm::APInt(32, value, true)); 
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindConstantInt32;

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

            llvm_value.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value.value, PointerType::get(IntegerType::get(TheContext, 64), 0));

            llvm_value.kind = kLVKindPointer;

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
            llvm_value.kind = kLVKindConstantFloat;

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
            llvm_value.kind = kLVKindConstantDouble;

            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 8);
            rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAdd(lvalue->value, rvalue->value, "baddtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
            }
            break;

        case OP_SADD:
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 16);
            rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAdd(lvalue->value, rvalue->value, "saddtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 32);
            rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAdd(lvalue->value, rvalue->value, "iaddtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 64);
            rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAdd(lvalue->value, rvalue->value, "laddtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 8);
            rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value  = Builder.CreateAdd(lvalue->value, rvalue->value, "ubaddtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 16);
            rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value  = Builder.CreateAdd(lvalue->value, rvalue->value, "usaddtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 32);
            rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value  = Builder.CreateAdd(lvalue->value, rvalue->value, "usaddtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 64);
            rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value  = Builder.CreateAdd(lvalue->value, rvalue->value, "usaddtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 32);
            rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value  = Builder.CreateAdd(lvalue->value, rvalue->value, "usaddtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);

            LVALUE rvalue2;
            rvalue2 = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateGEP(lvalue->value, rvalue2.value, "addtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindPointer;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 8);
            rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SSUB:
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 16);
            rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ISUB:
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 32);
            rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            lvalue = trunc_value(lvalue, 64);
            rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

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
            llvm_value.kind = kLVKindPointer;

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
            llvm_value.kind = kLVKindInt64;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 64);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);
            }
            break;

        case OP_UBSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UISUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSub(lvalue->value, rvalue->value, "subtmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateMul(lvalue->value, rvalue->value, "multmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            int value_size = 8;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            int value_size = 16;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            int value_size = 32;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            int value_size = 64;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            int value_size = 8;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateUDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.float_value = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            int value_size = 16;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateUDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.float_value = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            int value_size = 32;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateUDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            int value_size = 64;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateUDiv(lvalue->value, rvalue->value, "divtmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            int value_size = 8;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSRem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            int value_size = 16;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSRem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            int value_size = 32;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSRem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            int value_size = 64;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateSRem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            int value_size = 8;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateURem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            int value_size = 16;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateURem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            int value_size = 32;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateURem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULMOD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            int value_size = 64;

            if_value_is_zero_entry_exception_object(rvalue->value, value_size, FALSE, FALSE, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateURem(lvalue->value, rvalue->value, "remtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ILSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", true, false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);
            
            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);
            
            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UILSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);
            
            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULLSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);
            
            LVALUE llvm_value;
            llvm_value.value = Builder.CreateShl(lvalue->value, rvalue->value, "lshifttmp", false, true);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateLShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateLShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateLShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULRSHIFT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateLShr(lvalue->value, rvalue->value, "rshifttmp", false);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "andtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULXOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue->value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULOR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "ortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue= trunc_value(lvalue, 8);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt8Ty(TheContext), (uint8_t)0xFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt8;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0xFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt16Ty(TheContext), (uint16_t)0xFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt16;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ICOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0xFFFFFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UICOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0xFFFFFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt32;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0xFFFFFFFFFFFFFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULCOMPLEMENT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0xFFFFFFFFFFFFFFFF);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateXor(lvalue->value, rvalue.value, "xortmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindUInt64;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFAdd(lvalue->value, rvalue->value, "faddtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DADD: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFAdd(lvalue->value, rvalue->value, "daddtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFSub(lvalue->value, rvalue->value, "fsubtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DSUB: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFSub(lvalue->value, rvalue->value, "fsubtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFMul(lvalue->value, rvalue->value, "fmulttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DMULT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFMul(lvalue->value, rvalue->value, "fmulttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            BOOL value_is_float = inst == OP_FDIV;
            BOOL value_is_double = inst == OP_DDIV;

            if_value_is_zero_entry_exception_object(rvalue->value, 0, value_is_float, value_is_double, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFDiv(lvalue->value, rvalue->value, "fdivtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindFloat;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DDIV: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            BOOL value_is_float = inst == OP_FDIV;
            BOOL value_is_double = inst == OP_DDIV;

            if_value_is_zero_entry_exception_object(rvalue->value, 0, value_is_float, value_is_double, params, *function, current_block, "Exception", "division by zero");

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFDiv(lvalue->value, rvalue->value, "fdivtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindDouble;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
    }

    return TRUE;
}

}
