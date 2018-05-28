#include "jit_common.hpp"

extern "C"
{
BOOL compile_to_native_code3(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name)
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_OBJ_IDENTIFY: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpNE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGT(lvalue->value, rvalue->value, "ugttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ILE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UILE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULT(lvalue->value, rvalue->value, "uletmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
        
        case OP_BGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_IGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UIGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpUGE(lvalue->value, rvalue->value, "ugeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_BLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_SLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ILEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_LLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpSLE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UBLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 8);
            *rvalue = trunc_value(rvalue, 8);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_USLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 16);
            *rvalue = trunc_value(rvalue, 16);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_UILEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ULLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 64);
            *rvalue = trunc_value(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_PLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_pointer(lvalue);
            *rvalue = trunc_value_to_pointer(rvalue);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);
            *rvalue = trunc_value(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpULE(lvalue->value, rvalue->value, "lteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOEQ(lvalue->value, rvalue->value, "eqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpONE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DNOTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpONE(lvalue->value, rvalue->value, "noteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;
            
            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DGT: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGT(lvalue->value, rvalue->value, "gttmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DLE: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLT(lvalue->value, rvalue->value, "letmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DGTEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOGE(lvalue->value, rvalue->value, "gteqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_FLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 32);
            *rvalue = trunc_value_to_float_or_double(rvalue, 32);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLE(lvalue->value, rvalue->value, "leeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_DLEEQ: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value_to_float_or_double(lvalue, 64);
            *rvalue = trunc_value_to_float_or_double(rvalue, 64);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateFCmpOLE(lvalue->value, rvalue->value, "leeqtmp");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
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
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_CLASSNAME: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(value, 32);

            if_value_is_zero_entry_exception_object(llvm_value2.value, 32, FALSE, FALSE, params, *function, current_block, "Exception", "Null pointer exception(1)");

            Function* fun = TheModule->getFunction("get_string_object_of_object_name");

            std::vector<Value*> params2;

            params2.push_back(llvm_value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;

            LVALUE llvm_value3;
            llvm_value3 = trunc_value(&llvm_value, 32);

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value3);

            /// push object to jit objects ///
            Function* fun2 = TheModule->getFunction("push_jit_object");

            std::vector<Value*> params3;

            Value* param1 = llvm_value3.value;
            params3.push_back(param1);

            (void)Builder.CreateCall(fun2, params3);
            }
            break;

        case OP_OBJ_ALLOCATED_SIZE: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(value, 32);

            if_value_is_zero_entry_exception_object(llvm_value2.value, 32, FALSE, FALSE, params, *function, current_block, "Exception", "Null pointer exception(1)");

            Function* fun = TheModule->getFunction("get_object_allocated_size");

            std::vector<Value*> params2;

            params2.push_back(llvm_value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;

            LVALUE llvm_value3;
            llvm_value3 = trunc_value(&llvm_value, 32);

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value3);
            }
            break;

        case OP_OBJ_HEAD_OF_MEMORY: {
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(value, 32);

            if_value_is_zero_entry_exception_object(llvm_value2.value, 32, FALSE, FALSE, params, *function, current_block, "Exception", "Null pointer exception(1)");

            Function* fun = TheModule->getFunction("get_object_head_of_memory");

            std::vector<Value*> params2;

            params2.push_back(llvm_value2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;

            LVALUE llvm_value3;
            llvm_value3 = trunc_value(&llvm_value, 64);

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value3);
            }
            break;

        case OP_IS: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            LVALUE lvalue2;
            lvalue2 = trunc_value(lvalue, 32);

            LVALUE rvalue2;
            rvalue2 = trunc_value(rvalue, 32);

            if_value_is_zero_entry_exception_object(lvalue2.value, 32, FALSE, FALSE, params, *function, current_block, "Exception", "Null pointer exception(1)");
            if_value_is_zero_entry_exception_object(rvalue2.value, 32, FALSE, FALSE, params, *function, current_block, "Exception", "Null pointer exception(1)");

            Function* fun = TheModule->getFunction("op_is_fun");

            std::vector<Value*> params2;

            params2.push_back(lvalue2.value);
            params2.push_back(rvalue2.value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 32);

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);
            }
            break;

        case OP_IMPLEMENTS: {
            int offset = *(int*)(*pc);
            (*pc) += sizeof(int);

            char* class_name = CONS_str(constant, offset);

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

            /// go ///
            LVALUE* value = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);
            if_value_is_zero_entry_exception_object(value->value, 32, FALSE, FALSE, params, *function, current_block, "Exception", "Null pointer exception(2)");

            Function* fun = TheModule->getFunction("object_implements_interface");

            params2.clear();

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(value, 32);
            params2.push_back(llvm_value2.value);

            params2.push_back(klass_value);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateCall(fun, params2);
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt32;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;

        case OP_ANDAND: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);


            *lvalue = trunc_value(lvalue, 1);
            *rvalue = trunc_value(rvalue, 1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateAnd(lvalue->value, rvalue->value, "ANDAND");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            IRBuilder<> builder(&(*function)->getEntryBlock(), (*function)->getEntryBlock().begin());
            Value* value = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "VALUE_FOR_ANDAND");
            Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
            Builder.CreateAlignedStore(zero, value, 8);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 64);

            Builder.CreateAlignedStore(llvm_value2.value, value, 8);

            llvm_value2.value = value;
            llvm_value2.kind = kLVKindMemory;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);
            }
            break;

        case OP_OROR: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -2);
            LVALUE* rvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 1);
            *rvalue = trunc_value(rvalue, 1);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateOr(lvalue->value, rvalue->value, "OROR");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            IRBuilder<> builder(&(*function)->getEntryBlock(), (*function)->getEntryBlock().begin());
            Value* value = builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, "VALUE_FOR_OROR");
            Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
            Builder.CreateAlignedStore(zero, value, 8);

            LVALUE llvm_value2;
            llvm_value2 = trunc_value(&llvm_value, 64);

            Builder.CreateAlignedStore(llvm_value2.value, value, 8);

            llvm_value2.value = value;
            llvm_value2.kind = kLVKindMemory;

            dec_stack_ptr(llvm_stack_ptr, 2);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value2);
            }
            break;

        case OP_LOGICAL_DENIAL: {
            LVALUE* lvalue = get_stack_ptr_value_from_index(*llvm_stack_ptr, -1);

            *lvalue = trunc_value(lvalue, 32);

            LVALUE rvalue;
            rvalue.value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);

            LVALUE llvm_value;
            llvm_value.value = Builder.CreateICmpEQ(lvalue->value, rvalue.value, "LOGICAL_DIANEAL");
            llvm_value.lvar_address_index = -1;
            llvm_value.lvar_stored = FALSE;
            llvm_value.kind = kLVKindInt1;
            llvm_value.parent_var_num = 0;
            llvm_value.parent_stack = NULL;
            llvm_value.parent_llvm_stack = NULL;

            dec_stack_ptr(llvm_stack_ptr, 1);
            push_value_to_stack_ptr(llvm_stack_ptr, &llvm_value);
            }
            break;
    }

    return TRUE;
}

}
