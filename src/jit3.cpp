#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code3(sByteCode* code, sConst* constant, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
{
    switch(inst)
    {
        case OP_BEQ:
        case OP_UBEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_SEQ:
        case OP_USEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_IEQ:
        case OP_UIEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LEQ: 
        case OP_ULEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_PEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_OBJ_IDENTIFY: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_OBJ_IDENTIFY_NOT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "not_eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BNOTEQ:
        case OP_UBNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_SNOTEQ:
        case OP_USNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_INOTEQ: 
        case OP_UINOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LNOTEQ: 
        case OP_ULNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_PNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_SGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_IGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_USGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UIGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ULGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_PGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_SLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ILE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_USLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UILE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ULLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_PLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;
        
        case OP_BGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_SGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_IGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_USGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UIGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ULGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_PGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_BLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_SLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ILEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_LLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UBLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_USLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_UILEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_ULLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_PLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_CLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpONE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpONE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.kind = kLVKindInt1;
            
            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_FLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLE(lvalue->value, rvalue->value, "leeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_DLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLE(lvalue->value, rvalue->value, "leeqtmp");
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_REGEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            Function* function = TheModule->getFunction("regex_equals");

            std::vector<Value*> params2;
            params2.push_back(lvalue->value);
            params2.push_back(rvalue->value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(function, params2);
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        case OP_REGNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            Function* function = TheModule->getFunction("regex_equals");

            std::vector<Value*> params2;
            params2.push_back(lvalue->value);
            params2.push_back(rvalue->value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(function, params2);
            llvm_value.value = Builder.CreateICmpEQ(llvm_value.value, ConstantInt::get(TheContext, llvm::APInt(32, 0, true)), "bool_value_reverse");
            llvm_value.kind = kLVKindInt32;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);

            inc_vm_stack_ptr(params, *current_block, -2);
            push_value_to_vm_stack_ptr_with_aligned(params, *current_block, &llvm_value);
            }
            break;

        default:
            if(!compile_to_native_code4(code, constant, inst, pc, llvm_stack_ptr, llvm_stack, params, current_block, function, var_num, try_catch_label_name))
            {
                return FALSE;
            }
            break;
    }

    return TRUE;
}

}
