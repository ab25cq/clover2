#include "common.h"

sNodeTree* gNodes;

static unsigned int gSizeNodes = 0;
static unsigned int gUsedNodes = 0;

void init_nodes()
{
    const int node_size = 32;

    if(gUsedNodes == 0) {
        gNodes = MCALLOC(1, sizeof(sNodeTree)*node_size);
        gSizeNodes = node_size;
        gUsedNodes = 1;   // 0 of index means null
    }
}

void free_nodes()
{
    if(gUsedNodes > 0) {
        int i;
        for(i=1; i<gUsedNodes; i++) {
            switch(gNodes[i].mNodeType) {
                case kNodeTypeIf:
                    {
                    if(gNodes[i].uValue.sIf.mIfNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sIf.mIfNodeBlock);
                    }
                    int j;
                    for(j=0; j<gNodes[i].uValue.sIf.mElifNum; j++) {
                        sNodeBlock* node_block = gNodes[i].uValue.sIf.mElifNodeBlocks[j];
                        if(node_block) {
                            sNodeBlock_free(node_block);
                        }
                    }
                    if(gNodes[i].uValue.sIf.mElseNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sIf.mElseNodeBlock);
                    }
                    }
                    break;

                case kNodeTypeWhile:
                    if(gNodes[i].uValue.sWhile.mWhileNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sWhile.mWhileNodeBlock);
                    }
                    break;

                case kNodeTypeTry:
                    if(gNodes[i].uValue.sTry.mTryNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sTry.mTryNodeBlock);
                    }
                    if(gNodes[i].uValue.sTry.mCatchNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sTry.mCatchNodeBlock);
                    }
                    break;

                case kNodeTypeFor:
                    if(gNodes[i].uValue.sFor.mForNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sFor.mForNodeBlock);
                    }
                    break;

                case kNodeTypeString:
                    MFREE(gNodes[i].uValue.mString);
                    break;

                case kNodeTypeBuffer:
                    MFREE(gNodes[i].uValue.mString);
                    break;

                case kNodeTypeBlockObject:
                    if(gNodes[i].uValue.sBlockObject.mBlockObjectCode) {
                        sNodeBlock_free(gNodes[i].uValue.sBlockObject.mBlockObjectCode);
                    }
                    break;

                case kNodeTypeNormalBlock:
                    if(gNodes[i].uValue.mBlock) {
                        sNodeBlock_free(gNodes[i].uValue.mBlock);
                    }
                    break;

                case kNodeTypeRegex:
                    MFREE(gNodes[i].uValue.sRegex.mRegexStr);
                    break;

                default:
                    break;
            }
        }

        MFREE(gNodes);

        gSizeNodes = 0;
        gUsedNodes = 0;
    }
}

// return node index
static unsigned int alloc_node()
{
    if(gSizeNodes == gUsedNodes) {
        int new_size = (gSizeNodes+1) * 2;
        gNodes = MREALLOC(gNodes, sizeof(sNodeTree)*new_size);
        memset(gNodes + gSizeNodes, 0, sizeof(sNodeTree)*(new_size - gSizeNodes));

        gSizeNodes = new_size;
    }

    return gUsedNodes++;
}

unsigned int clone_node(unsigned int node)
{
    unsigned int result = alloc_node();

    memcpy(gNodes + result, gNodes + node, sizeof(sNodeTree));

    return result;
}

static void err_msg_for_method_not_found(sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL class_method, sCompileInfo* info)
{
    parser_err_msg(info->pinfo, "%s.%s(%d prametors) is not found", CLASS_NAME(klass), method_name, num_params);
    int i;
    for(i=0; i<num_params; i++) {
        parser_err_msg(info->pinfo, "parametor#%d is %s", i, CLASS_NAME(param_types[i]->mClass));
    }
}

unsigned int sNodeTree_create_operand(enum eOperand operand, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOperand;
    gNodes[node].uValue.mOperand = operand;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL single_operator(sNodeType* type, int byte_operand, int ubyte_operand, int short_operand, int ushort_operand, int int_operand, int uint_operand, int long_operand, int ulong_operand, sCompileInfo* info)
{
    if(type_identify_with_class_name(type, "byte")) {
        append_opecode_to_code(info->code, byte_operand, info->no_output);

        info->type = create_node_type_with_class_name("byte");
    }
    else if(type_identify_with_class_name(type, "ubyte")) {
        append_opecode_to_code(info->code, ubyte_operand, info->no_output);

        info->type = create_node_type_with_class_name("ubyte");
    }
    else if(type_identify_with_class_name(type, "short")) {
        append_opecode_to_code(info->code, short_operand, info->no_output);

        info->type = create_node_type_with_class_name("short");
    }
    else if(type_identify_with_class_name(type, "ushort")) {
        append_opecode_to_code(info->code, ushort_operand, info->no_output);

        info->type = create_node_type_with_class_name("ushort");
    }
    else if(type_identify_with_class_name(type, "int")) {
        append_opecode_to_code(info->code, int_operand, info->no_output);

        info->type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(type, "uint")) {
        append_opecode_to_code(info->code, uint_operand, info->no_output);

        info->type = create_node_type_with_class_name("uint");
    }
    else if(type_identify_with_class_name(type, "long")) {
        append_opecode_to_code(info->code, long_operand, info->no_output);

        info->type = create_node_type_with_class_name("long");
    }
    else if(type_identify_with_class_name(type, "ulong")) {
        append_opecode_to_code(info->code, ulong_operand, info->no_output);

        info->type = create_node_type_with_class_name("ulong");
    }

    return TRUE;
}

static BOOL no_cast_types(sNodeType* left_type, sNodeType* right_type)
{
    return type_identify_with_class_name(left_type, "pointer") && type_identify_with_class_name(right_type, "int");
}

static BOOL binary_operator(sNodeType* left_type, sNodeType* right_type, int byte_operand, int ubyte_operand, int short_operand, int ushort_operand, int int_operand, int uint_operand, int long_operand, int ulong_operand, int float_operand, int double_operand, int pointer_operand, int null_operand, int char_operand, int bool_operand, char* op_string, sCompileInfo* info)
{
    if(!no_cast_types(left_type, right_type))
    {
        cast_right_type_to_left_type(left_type, &right_type, info);
    }

    if(!operand_posibility(left_type, right_type, op_string))
    {
        parser_err_msg(info->pinfo, "Invalid type for operand(%s). The left type is %s. The right type is %s.", op_string,CLASS_NAME(left_type->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(type_identify_with_class_name(left_type, "byte") && byte_operand != -1) {
        append_opecode_to_code(info->code, byte_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("byte");
    }
    else if(type_identify_with_class_name(left_type, "ubyte") && ubyte_operand != -1) {
        append_opecode_to_code(info->code, ubyte_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("ubyte");
    }
    else if(type_identify_with_class_name(left_type, "short") && short_operand != -1) {
        append_opecode_to_code(info->code, short_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("short");
    }
    else if(type_identify_with_class_name(left_type, "ushort") && ushort_operand != -1) {
        append_opecode_to_code(info->code, ushort_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("ushort");
    }
    else if(type_identify_with_class_name(left_type, "int") && int_operand != -1) {
        append_opecode_to_code(info->code, int_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(left_type, "uint") && uint_operand != -1) {
        append_opecode_to_code(info->code, uint_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("uint");
    }
    else if(type_identify_with_class_name(left_type, "long") && long_operand != -1) {
        append_opecode_to_code(info->code, long_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("long");
    }
    else if(type_identify_with_class_name(left_type, "ulong") && ulong_operand != -1) {
        append_opecode_to_code(info->code, ulong_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("ulong");
    }
    else if(type_identify_with_class_name(left_type, "float") && float_operand != -1) {
        append_opecode_to_code(info->code, float_operand, info->no_output);

        info->stack_num--;

        info->type = create_node_type_with_class_name("float");
    }
    else if(type_identify_with_class_name(left_type, "double") && double_operand != -1) {
        append_opecode_to_code(info->code, double_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("double");
    }
    else if(type_identify_with_class_name(left_type, "Null") && null_operand != -1) {
        append_opecode_to_code(info->code, null_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("null");
    }
    else if(type_identify_with_class_name(left_type, "pointer") && pointer_operand != -1) {
        append_opecode_to_code(info->code, pointer_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("pointer");
    }
    else if(type_identify_with_class_name(left_type, "char") && char_operand != -1) {
        append_opecode_to_code(info->code, char_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("char");
    }
    else if(type_identify_with_class_name(left_type, "bool") && bool_operand != -1) {
        append_opecode_to_code(info->code, bool_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("bool");
    }
    else {
        parser_err_msg(info->pinfo, "%s.%s is not implemented", CLASS_NAME(left_type->mClass), op_string);
        info->err_num++;
    }

    return TRUE;
}

static BOOL binary_operator_for_bool(sNodeType* type, int bool_operand, sCompileInfo* info)
{
    if(type_identify_with_class_name(type, "bool")) {
        append_opecode_to_code(info->code, bool_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("bool");
    }

    return TRUE;
}


static BOOL compile_operand(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    if(unboxig_posibility(left_type->mClass)) {
        if(!unboxing_to_primitive_type(&left_type, info)) {
            return FALSE;
        }
    }

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;
    sNodeType* node_type = left_type;

    switch(gNodes[node].uValue.mOperand) {
        case kOpAdd:
            if(!binary_operator(left_type, right_type, OP_BADD, OP_UBADD, OP_SADD, OP_USADD, OP_IADD, OP_UIADD, OP_LADD, OP_ULADD, OP_FADD, OP_DADD, OP_PADD, -1, OP_CADD, -1, "+", info))
            {
                return FALSE;
            }
            break;

        case kOpSub:
            if(!binary_operator(left_type, right_type, OP_BSUB, OP_UBSUB, OP_SSUB, OP_USSUB, OP_ISUB, OP_UISUB, OP_LSUB, OP_ULSUB, OP_FSUB, OP_DSUB, OP_PSUB, -1, OP_CSUB, -1, "-", info))
            {
                return FALSE;
            }
            break;
            
        case kOpMult:
            if(!binary_operator(left_type, right_type, OP_BMULT, OP_UBMULT, OP_SMULT, OP_USMULT, OP_IMULT, OP_UIMULT, OP_LMULT, OP_ULMULT, OP_FMULT, OP_DMULT, -1, -1, -1, -1, "*", info))
            {
                return FALSE;
            }
            break;
            
        case kOpDiv:
            if(!binary_operator(left_type, right_type, OP_BDIV, OP_UBDIV, OP_SDIV, OP_USDIV, OP_IDIV, OP_UIDIV, OP_LDIV, OP_ULDIV, OP_FDIV, OP_DDIV, -1, -1, -1, -1, "/", info))
            {
                return FALSE;
            }
            break;
            
        case kOpMod:
            if(!binary_operator(left_type, right_type, OP_BMOD, OP_UBMOD, OP_SMOD, OP_USMOD, OP_IMOD, OP_UIMOD, OP_LMOD, OP_ULMOD, -1, -1, -1, -1, -1, -1, "%", info))
            {
                return FALSE;
            }
            break;
            
        case kOpLeftShift:
            if(!binary_operator(left_type, right_type, OP_BLSHIFT, OP_UBLSHIFT, OP_SLSHIFT, OP_USLSHIFT, OP_ILSHIFT, OP_UILSHIFT, OP_LLSHIFT, OP_ULLSHIFT, -1, -1, -1, -1, -1, -1, "<<", info))
            {
                return FALSE;
            }
            break;
            
        case kOpRightShift:
            if(!binary_operator(left_type, right_type, OP_BRSHIFT, OP_UBRSHIFT, OP_SRSHIFT, OP_USRSHIFT, OP_IRSHIFT, OP_UIRSHIFT, OP_LRSHIFT, OP_ULRSHIFT, -1, -1, -1, -1, -1, -1, ">>", info))
            {
                return FALSE;
            }
            break;
            
        case kOpComparisonEqual:
            if(!binary_operator(left_type, right_type, OP_BEQ, OP_UBEQ, OP_SEQ, OP_USEQ, OP_IEQ, OP_UIEQ, OP_LEQ, OP_ULEQ, OP_FEQ, OP_DEQ, OP_PEQ, OP_IEQ, OP_CEQ, OP_IEQ, "==", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonNotEqual:
            if(!binary_operator(left_type, right_type, OP_BNOTEQ, OP_UBNOTEQ, OP_SNOTEQ, OP_USNOTEQ, OP_INOTEQ, OP_UINOTEQ, OP_LNOTEQ, OP_ULNOTEQ, OP_FNOTEQ, OP_DNOTEQ, OP_PNOTEQ, OP_INOTEQ, OP_CNOTEQ, OP_INOTEQ, "!=", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonGreaterEqual:
            if(!binary_operator(left_type, right_type, OP_BGTEQ, OP_UBGTEQ, OP_SGTEQ, OP_USGTEQ, OP_IGTEQ, OP_UIGTEQ, OP_LGTEQ, OP_ULGTEQ, OP_FGTEQ, OP_DGTEQ, OP_PGTEQ, -1, OP_CGTEQ, -1, ">=", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonLesserEqual:
            if(!binary_operator(left_type, right_type, OP_BLEEQ, OP_UBLEEQ, OP_SLEEQ, OP_USLEEQ, OP_ILEEQ, OP_UILEEQ, OP_LLEEQ, OP_ULLEEQ, OP_FLEEQ, OP_DLEEQ, OP_PLEEQ, -1, OP_CLEEQ, -1, "<=", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonGreater:
            if(!binary_operator(left_type, right_type, OP_BGT, OP_UBGT, OP_SGT, OP_USGT, OP_IGT, OP_UIGT, OP_LGT, OP_ULGT, OP_FGT, OP_DGT, OP_PGT, -1, OP_CGT, -1, ">", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonLesser:
            if(!binary_operator(left_type, right_type, OP_BLE, OP_UBLE, OP_SLE, OP_USLE, OP_ILE, OP_UILE, OP_LLE, OP_ULLE, OP_FLE, OP_DLE, OP_PLE, -1, OP_CLE, -1, "<", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpAnd:
            if(!binary_operator(left_type, right_type, OP_BAND, OP_UBAND, OP_SAND, OP_USAND, OP_IAND, OP_UIAND, OP_LAND, OP_ULAND, -1, -1, -1, -1, -1, -1, "&", info))
            {
                return FALSE;
            }
            break;
            
        case kOpXor:
            if(!binary_operator(left_type, right_type, OP_BXOR, OP_UBXOR, OP_SXOR, OP_USXOR, OP_IXOR, OP_UIXOR, OP_LXOR, OP_ULXOR, -1, -1, -1, -1, -1, -1, "^", info))
            {
                return FALSE;
            }
            break;
            
        case kOpOr:
            if(!binary_operator(left_type, right_type, OP_BOR, OP_UBOR, OP_SOR, OP_USOR, OP_IOR, OP_UIOR, OP_LOR, OP_ULOR, -1, -1, -1, -1, -1, -1, "|", info))
            {
                return FALSE;
            }
            break;

        case kOpComplement:
            if(!single_operator(node_type, OP_BCOMPLEMENT, OP_UBCOMPLEMENT, OP_SCOMPLEMENT, OP_USCOMPLEMENT, OP_ICOMPLEMENT, OP_UICOMPLEMENT, OP_LCOMPLEMENT, OP_ULCOMPLEMENT, info))
            {
                return FALSE;
            }
            break;

        case kOpLogicalDenial:
            if(!type_identify_with_class_name(node_type, "bool")) {
                parser_err_msg(info->pinfo, "require bool type for operator !");
                info->err_num++;
            }
            else {
                append_opecode_to_code(info->code, OP_LOGICAL_DENIAL, info->no_output);

                info->type = create_node_type_with_class_name("bool");
            }
            break;
    }

    return TRUE;
}

unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAndAnd;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_and_and(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(unboxig_posibility(left_type->mClass)) {
        if(!unboxing_to_primitive_type(&left_type, info)) {
            return FALSE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        parser_err_msg(info->pinfo, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_DUPE, info->no_output);
    info->stack_num++;

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*2, info->no_output);
    info->stack_num--;

    /// goto end point ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the left expression is false, jump to the end of and and expression
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(unboxig_posibility(right_type->mClass)) {
        if(!unboxing_to_primitive_type(&right_type, info)) {
            return FALSE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        parser_err_msg(info->pinfo, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_ANDAND, info->no_output);
    info->stack_num--;

    *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

    info->type = create_node_type_with_class_name("bool");
    
    return TRUE;
}

unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOrOr;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_or_or(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(unboxig_posibility(left_type->mClass)) {
        if(!unboxing_to_primitive_type(&left_type, info)) {
            return FALSE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        parser_err_msg(info->pinfo, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_DUPE, info->no_output);
    info->stack_num++;

    append_opecode_to_code(info->code, OP_COND_NOT_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*2, info->no_output);
    info->stack_num--;

    /// goto end point ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the left expression is true, jump to the end of || expression
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(unboxig_posibility(right_type->mClass)) {
        if(!unboxing_to_primitive_type(&right_type, info)) {
            return FALSE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        parser_err_msg(info->pinfo, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_OROR, info->no_output);
    info->stack_num--;

    *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

    info->type = create_node_type_with_class_name("bool");
    
    return TRUE;
}

unsigned int sNodeTree_conditional_expression(unsigned int expression_node, unsigned int true_expression_node, unsigned int false_expression_node)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeConditional;

    gNodes[node].mLeft = true_expression_node;
    gNodes[node].mRight = false_expression_node;
    gNodes[node].mMiddle = expression_node;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_conditional_operator(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int expression_node = gNodes[node].mMiddle;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* bool_type = create_node_type_with_class_name("bool");
    cast_right_type_to_left_type(bool_type, &info->type, info);

    if(!type_identify_with_class_name(info->type, "bool")) {
        parser_err_msg(info->pinfo, "This conditional expression type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*2, info->no_output);
    info->stack_num--;

    /// if expression ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    /// compile true expression ///
    unsigned int true_expression_node = gNodes[node].mLeft;

    if(!compile(true_expression_node, info)) {
        return FALSE;
    }

    info->stack_num--;

    sNodeType* true_expression_type = info->type;

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    int end_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

    /// compile false expression ///
    unsigned int false_expression_node = gNodes[node].mRight;

    if(!compile(false_expression_node, info)) {
        return FALSE;
    }

    info->stack_num--;

    sNodeType* false_expression_type = info->type;

    *(int*)(info->code->mCodes + end_point) = info->code->mLen;

    /// check result ///
    if(!type_identify(true_expression_type, false_expression_type)) {
        parser_err_msg(info->pinfo, "True expression type and false expression type are different");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->type = true_expression_type;
    info->stack_num++;
    
    return TRUE;
}

unsigned int sNodeTree_create_byte_value(char value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeByteValue;

    gNodes[node].uValue.mByteValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("byte");

    return node;
}

static BOOL compile_byte_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCBYTE, info->no_output);
    append_int_value_to_code(info->code, gNodes[node].uValue.mByteValue, info->no_output);

    info->stack_num++;

    info->type = gNodes[node].mType;

    return TRUE;
}

unsigned int sNodeTree_create_ubyte_value(unsigned char value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUByteValue;

    gNodes[node].uValue.mUByteValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("ubyte");

    return node;
}

static BOOL compile_ubyte_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCUBYTE, info->no_output);
    append_int_value_to_code(info->code, gNodes[node].uValue.mUByteValue, info->no_output);

    info->stack_num++;

    info->type = gNodes[node].mType;

    return TRUE;
}

unsigned int sNodeTree_create_short_value(short value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeShortValue;

    gNodes[node].uValue.mShortValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("short");

    return node;
}

static BOOL compile_short_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCSHORT, info->no_output);
    append_int_value_to_code(info->code, gNodes[node].uValue.mShortValue, info->no_output);

    info->stack_num++;

    info->type = gNodes[node].mType;

    return TRUE;
}

unsigned int sNodeTree_create_ushort_value(unsigned short value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUShortValue;

    gNodes[node].uValue.mUShortValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("ushort");

    return node;
}

static BOOL compile_ushort_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCUSHORT, info->no_output);
    append_int_value_to_code(info->code, gNodes[node].uValue.mUShortValue, info->no_output);

    info->stack_num++;

    info->type = gNodes[node].mType;

    return TRUE;
}

unsigned int sNodeTree_create_int_value(int value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIntValue;

    gNodes[node].uValue.mIntValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("int");

    return node;
}

static BOOL compile_int_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCINT, info->no_output);
    append_int_value_to_code(info->code, gNodes[node].uValue.mIntValue, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("int");

    return TRUE;
}

unsigned int sNodeTree_create_uint_value(unsigned int value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUIntValue;

    gNodes[node].uValue.mUIntValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("uint");

    return node;
}

static BOOL compile_uint_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCUINT, info->no_output);
    append_int_value_to_code(info->code, gNodes[node].uValue.mUIntValue, info->no_output);

    info->stack_num++;

    info->type = gNodes[node].mType;

    return TRUE;
}

unsigned int sNodeTree_create_long_value(long value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLongValue;

    gNodes[node].uValue.mLongValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("long");

    return node;
}

static BOOL compile_long_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCLONG, info->no_output);
    append_long_value_to_code(info->code, gNodes[node].uValue.mLongValue, info->no_output);

    info->stack_num++;

    info->type = gNodes[node].mType;

    return TRUE;
}

unsigned int sNodeTree_create_ulong_value(unsigned long value, unsigned int left, unsigned int right, unsigned int middle)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeULongValue;

    gNodes[node].uValue.mULongValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("ulong");

    return node;
}

static BOOL compile_ulong_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCULONG, info->no_output);
    append_long_value_to_code(info->code, gNodes[node].uValue.mULongValue, info->no_output);

    info->stack_num++;

    info->type = gNodes[node].mType;

    return TRUE;
}

unsigned int sNodeTree_create_store_variable(char* var_name, sNodeType* node_type, int right, sCLClass* klass)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAssignVariable;

    xstrncpy(gNodes[node].uValue.sAssignVariable.mVarName, var_name, VAR_NAME_MAX);
    gNodes[node].uValue.sAssignVariable.mClass = klass;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = node_type;

    return node;
}

static BOOL compile_store_variable(unsigned int node, sCompileInfo* info)
{
    sVar* var = get_variable_from_table(info->lv_table, gNodes[node].uValue.sAssignVariable.mVarName);

    if(var == NULL) {
        parser_err_msg(info->pinfo, "undeclared variable %s", gNodes[node].uValue.sAssignVariable.mVarName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    /// type inference ///
    if(gNodes[node].mType == NULL) {
        gNodes[node].mType = right_type;
        var->mType = right_type;
    }

    sNodeType* left_type = var->mType;
    if(gNodes[node].mType->mClass == NULL || left_type == NULL || right_type == NULL || left_type->mClass == NULL || right_type->mClass == NULL) 
    {
        parser_err_msg(info->pinfo, "invalid type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type2;
    solve_generics_for_variable(left_type, &left_type2, info->pinfo->klass);

    cast_right_type_to_left_type(left_type2, &right_type, info);

    if(!substitution_posibility(left_type2, right_type, NULL, NULL)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type(1). Left type is %s. Right type is %s.", CLASS_NAME(left_type2->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;

    }

    int var_index = get_variable_index(info->lv_table, gNodes[node].uValue.sAssignVariable.mVarName);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    info->type = left_type2;

    return TRUE;
}

unsigned int sNodeTree_create_load_variable(char* var_name)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadVariable;

    xstrncpy(gNodes[node].uValue.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_load_variable(unsigned int node, sCompileInfo* info)
{
    sVar* var = get_variable_from_table(info->lv_table, gNodes[node].uValue.mVarName);

    if(var == NULL) {
        parser_err_msg(info->pinfo, "undeclared variable %s", gNodes[node].uValue.mVarName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    gNodes[node].mType = var->mType;

    int var_index = get_variable_index(info->lv_table, gNodes[node].uValue.mVarName);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_LOAD, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    info->stack_num++;

    /// solve generics types ///
    sNodeType* result_type = var->mType;

    if(result_type == NULL) {
        parser_err_msg(info->pinfo, "null type %s", gNodes[node].uValue.mVarName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* result_type2;
    solve_generics_for_variable(result_type, &result_type2, info->pinfo->klass);

    info->type = result_type2;

    return TRUE;
}

unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED sNodeBlock* if_node_block, unsigned int* elif_expression_nodes, MANAGED sNodeBlock** elif_node_blocks, int elif_num, MANAGED sNodeBlock* else_node_block)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIf;

    gNodes[node].uValue.sIf.mExpressionNode = expression_node;
    gNodes[node].uValue.sIf.mIfNodeBlock = MANAGED if_node_block;
    memcpy(gNodes[node].uValue.sIf.mElifExpressionNodes, elif_expression_nodes, sizeof(unsigned int)*elif_num);
    memcpy(gNodes[node].uValue.sIf.mElifNodeBlocks, MANAGED elif_node_blocks, sizeof(sNodeBlock*)*elif_num);
    gNodes[node].uValue.sIf.mElifNum = elif_num;
    gNodes[node].uValue.sIf.mElseNodeBlock = MANAGED else_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_if_expression(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sIf.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    if(!type_identify_with_class_name(info->type, "bool")) {
        parser_err_msg(info->pinfo, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*2, info->no_output);
    info->stack_num--;

    /// block of if expression ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    sNodeBlock* if_block = gNodes[node].uValue.sIf.mIfNodeBlock;
    if(!compile_block(if_block, info)) {
        return FALSE;
    }

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    int num_end_points = 1;
    int end_points[ELIF_NUM_MAX+1];
    end_points[0] = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

    if(gNodes[node].uValue.sIf.mElifNum > 0) {
        int j;
        for(j=0; j<gNodes[node].uValue.sIf.mElifNum; j++) {
            /// compile expression ///
            unsigned int elif_expression_node = gNodes[node].uValue.sIf.mElifExpressionNodes[j];

            if(!compile(elif_expression_node, info)) {
                return FALSE;
            }

            if(!type_identify_with_class_name(info->type, "bool")) {
                parser_err_msg(info->pinfo, "This conditional type is not bool");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
            append_int_value_to_code(info->code, sizeof(int)*2, info->no_output);

            info->stack_num--;

            /// block of if expression ///
            append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
            int goto_point = info->code->mLen;
            append_int_value_to_code(info->code, 0, info->no_output);

            sNodeBlock* elif_block = gNodes[node].uValue.sIf.mElifNodeBlocks[j];
            if(!compile_block(elif_block, info)) {
                return FALSE;
            }

            append_opecode_to_code(info->code, OP_GOTO, info->no_output);
            end_points[num_end_points] = info->code->mLen;
            num_end_points++;
            append_int_value_to_code(info->code, 0, info->no_output);

            MASSERT(num_end_points <= ELIF_NUM_MAX+1);

            *(int*)(info->code->mCodes + goto_point) = info->code->mLen;
        }
    }

    /// else block ///
    sNodeBlock* else_node_block = gNodes[node].uValue.sIf.mElseNodeBlock;
    if(else_node_block) {
        if(!compile_block(else_node_block, info)) {
            return FALSE;
        }
    }

    int i;
    for(i=0; i<num_end_points; i++) {
        *(int*)(info->code->mCodes + end_points[i]) = info->code->mLen;
    }

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED sNodeBlock* while_node_block)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWhile;

    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = MANAGED while_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_while_expression(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    int start_point = info->code->mLen;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    if(!type_identify_with_class_name(info->type, "bool")) {
        parser_err_msg(info->pinfo, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*2, info->no_output);
    info->stack_num--;

    /// block of while expression ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
    int end_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    int num_break_points = 0;
    int break_points[BREAK_NUM_MAX+1];
    memset(break_points, 0, sizeof(int)*BREAK_NUM_MAX);

    int* num_break_points_before = info->num_break_points;
    int* break_points_before = info->break_points;

    info->num_break_points = &num_break_points;
    info->break_points = break_points;

    sNodeBlock* while_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;
    if(!compile_block(while_block, info)) {
        return FALSE;
    }

    info->num_break_points = num_break_points_before;
    info->break_points = break_points_before;

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    append_int_value_to_code(info->code, start_point, info->no_output);

    *(int*)(info->code->mCodes + end_point) = info->code->mLen;

    int i;
    for(i=0; i<num_break_points; i++) {
        *(int*)(info->code->mCodes + break_points[i]) = info->code->mLen;
    }

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED sNodeBlock* for_node_block)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFor;

    gNodes[node].uValue.sFor.mExpressionNode = expression_node1;
    gNodes[node].uValue.sFor.mExpressionNode2 = expression_node2;
    gNodes[node].uValue.sFor.mExpressionNode3 = expression_node3;
    gNodes[node].uValue.sFor.mForNodeBlock = MANAGED for_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_for_expression(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sFor.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    arrange_stack(info);

    /// compile expression ///
    unsigned int expression_node2 = gNodes[node].uValue.sFor.mExpressionNode2;

    int start_point = info->code->mLen;

    if(!compile(expression_node2, info)) {
        return FALSE;
    }

    if(!type_identify_with_class_name(info->type, "bool")) {
        parser_err_msg(info->pinfo, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*2, info->no_output);
    info->stack_num--;

    /// block of for expression ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
    int end_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    int num_break_points = 0;
    int break_points[BREAK_NUM_MAX+1];
    memset(break_points, 0, sizeof(int)*BREAK_NUM_MAX);

    int* num_break_points_before = info->num_break_points;
    int* break_points_before = info->break_points;

    info->num_break_points = &num_break_points;
    info->break_points = break_points;

    sNodeBlock* for_block = gNodes[node].uValue.sFor.mForNodeBlock;
    if(!compile_block(for_block, info)) {
        return FALSE;
    }

    info->num_break_points = num_break_points_before;
    info->break_points = break_points_before;

    /// expression 3 ///
    unsigned int expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;

    if(!compile(expression_node3, info)) {
        return FALSE;
    }

    arrange_stack(info);

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    append_int_value_to_code(info->code, start_point, info->no_output);

    *(int*)(info->code->mCodes + end_point) = info->code->mLen;

    int i;
    for(i=0; i<num_break_points; i++) {
        *(int*)(info->code->mCodes + break_points[i]) = info->code->mLen;
    }

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_break_expression()
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBreak;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_break_expression(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    info->break_points[*info->num_break_points] = info->code->mLen;
    (*info->num_break_points)++;

    if(*info->num_break_points >= BREAK_NUM_MAX) {
        parser_err_msg(info->pinfo, "overflow break number");
        return FALSE;
    }

    append_int_value_to_code(info->code, 0, info->no_output);

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_true_expression()
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTrue;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_true_expression(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCINT, info->no_output);
    append_int_value_to_code(info->code, 1, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("bool");
    
    return TRUE;
}

unsigned int sNodeTree_false_expression()
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFalse;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_false_expression(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCINT, info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("bool");
    
    return TRUE;
}

unsigned int sNodeTree_null_expression()
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNull;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_null_expression(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCINT, info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_create_class_method_call(sCLClass* klass, char* method_name, unsigned int* params, int num_params)
{
    unsigned int node = alloc_node();

    gNodes[node].uValue.sClassMethodCall.mClass = klass;
    xstrncpy(gNodes[node].uValue.sClassMethodCall.mMethodName, method_name, METHOD_NAME_MAX);
    gNodes[node].uValue.sClassMethodCall.mNumParams = num_params;
    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sClassMethodCall.mParams[i] = params[i];
    }

    gNodes[node].mNodeType = kNodeTypeClassMethodCall;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_class_method_call(unsigned int node, sCompileInfo* info)
{
    sNodeType* param_types[PARAMS_MAX];

    sCLClass* klass = gNodes[node].uValue.sClassMethodCall.mClass;
    int num_params = gNodes[node].uValue.sClassMethodCall.mNumParams;
    char* method_name = gNodes[node].uValue.sClassMethodCall.mMethodName;

    int i;
    for(i=0; i<num_params; i++) {
        int node2 = gNodes[node].uValue.sClassMethodCall.mParams[i];
        if(!compile(node2, info)) {
            return FALSE;
        }

        param_types[i] = info->type;
    }

    sNodeType* result_type;
    int method_index = search_for_method(klass, method_name, param_types, num_params, TRUE, klass->mNumMethods-1, NULL, NULL, &result_type);

    if(method_index == -1) {
        parser_err_msg(info->pinfo, "method not found(1)");
        info->err_num++;

        err_msg_for_method_not_found(klass, method_name, param_types, num_params, TRUE, info);

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);
    append_int_value_to_code(info->code, method_index, info->no_output);

    info->stack_num-=num_params;
    info->stack_num++;

    info->type = result_type;
    
    return TRUE;
}

unsigned int sNodeTree_create_method_call(unsigned int object_node, char* method_name, unsigned int* params, int num_params)
{
    unsigned int node = alloc_node();

    xstrncpy(gNodes[node].uValue.sMethodCall.mMethodName, method_name, METHOD_NAME_MAX);
    gNodes[node].uValue.sMethodCall.mNumParams = num_params;
    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sMethodCall.mParams[i] = params[i];
    }

    gNodes[node].mNodeType = kNodeTypeMethodCall;

    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_params(sCLClass* klass, char* method_name, int num_params, unsigned int params[PARAMS_MAX], sNodeType* param_types[PARAMS_MAX], sNodeType* generics_types, sCompileInfo* info)
{
    int size_method_indexes = 128;
    int method_indexes[size_method_indexes];
    int num_methods = 0;
    if(!search_for_methods_from_method_name(method_indexes, size_method_indexes, &num_methods, klass, method_name, klass->mNumMethods-1))
    {
        parser_err_msg(info->pinfo, "overflow number of the same name methods");
        return FALSE;
    }

    int i;
    for(i=0; i<num_params; i++) {
        int node2 = params[i];
        if(!compile(node2, info)) {
            return FALSE;
        }

        param_types[i] = info->type;

        /// cast params for the method if it is requires ///
        int j;
        for(j=0; j<num_methods; j++) {
            sCLMethod* method = klass->mMethods + method_indexes[j];

            if(i < method->mNumParams) {
                sNodeType* param;
                sNodeType* solved_param;

                param = create_node_type_from_cl_type(method->mParams[i].mType, klass);

                if(!solve_generics_types_for_node_type(param, ALLOC &solved_param, generics_types)) 
                {
                    return FALSE;
                }

                if(boxing_posibility(solved_param, param_types[i])) {
                    cast_right_type_to_left_type(solved_param, &param_types[i], info);
                }

                if(type_identify_with_class_name(param_types[i], "Null")) {
                    param_types[i] = solved_param;
                }
            }
        }
    }

    return TRUE;
}

static BOOL compile_method_call(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if(info->type == NULL 
        || type_identify_with_class_name(info->type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for method call");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// boxing if the class is primitive ///
    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        boxing_to_lapper_class(&info->type, info);
    }

    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        parser_err_msg(info->pinfo, "primitive class can't be called to method");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* generics_types = info->type;
    sCLClass* klass = generics_types->mClass;

    sNodeType* param_types[PARAMS_MAX];

    int num_params = gNodes[node].uValue.sMethodCall.mNumParams;
    char* method_name = gNodes[node].uValue.sMethodCall.mMethodName;
    unsigned int params[PARAMS_MAX];

    memcpy(params, gNodes[node].uValue.sMethodCall.mParams, sizeof(unsigned int)*PARAMS_MAX);

    if(!compile_params(klass, method_name, num_params, params, param_types, generics_types, info)) {
        return FALSE;
    }

    /// special methods ///
    if(strcmp(method_name, "identifyWith") == 0) {
        if(num_params != 1) {
            parser_err_msg(info->pinfo, "identify method require one none primitive class param");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
        sCLClass* param_class = param_types[0]->mClass;
        if((param_class->mFlags & CLASS_FLAGS_PRIMITIVE) && !type_identify_with_class_name(param_types[0], "Null")) {
            parser_err_msg(info->pinfo, "identify method require one none primitive class param");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_OBJ_IDENTIFY, info->no_output);

        info->stack_num-=num_params + 1;
        info->stack_num++;

        info->type = create_node_type_with_class_name("bool");
    }
    else if(strcmp(method_name, "className") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "className method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_CLASSNAME, info->no_output);

        info->stack_num-=num_params + 1;
        info->stack_num++;

        info->type = create_node_type_with_class_name("String");
    }
    else if(strcmp(method_name, "toAnonymous") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "toAnonymous method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = create_node_type_with_class_name("Anonymous");
    }
    else if(strcmp(method_name, "to_byte") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_byte(&info->type, info);
    }
    else if(strcmp(method_name, "to_ubyte") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_ubyte(&info->type, info);
    }
    else if(strcmp(method_name, "to_short") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_short(&info->type, info);
    }
    else if(strcmp(method_name, "to_ushort") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_ushort(&info->type, info);
    }
    else if(strcmp(method_name, "to_int") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_int(&info->type, info);
    }
    else if(strcmp(method_name, "to_uint") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_uint(&info->type, info);
    }
    else if(strcmp(method_name, "to_long") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_long(&info->type, info);
    }
    else if(strcmp(method_name, "to_ulong") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_ulong(&info->type, info);
    }
    else if(strcmp(method_name, "to_float") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_float(&info->type, info);
    }
    else if(strcmp(method_name, "to_double") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_double(&info->type, info);
    }
    else if(strcmp(method_name, "to_char") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_char(&info->type, info);
    }
    else if(strcmp(method_name, "to_pointer") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_pointer(&info->type, info);
    }
    else if(strcmp(method_name, "to_bool") == 0) {
        if(num_params != 0) {
            parser_err_msg(info->pinfo, "cast method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = generics_types;
        cast_right_type_to_bool(&info->type, info);
    }
    /// normal methods ///
    else {
        sNodeType* result_type;
        int method_index2 = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types, generics_types, &result_type);

        if(method_index2 == -1) {
            parser_err_msg(info->pinfo, "method not found(2)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLMethod* method = klass->mMethods + method_index2;

        if(klass->mFlags & CLASS_FLAGS_INTERFACE || klass == info->pinfo->klass) { // Interface is called virtually and the inner method is called virtually for mixin
            int num_real_params = method->mNumParams + 1;

            append_opecode_to_code(info->code, OP_INVOKE_VIRTUAL_METHOD, info->no_output);
            append_int_value_to_code(info->code, num_real_params, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, METHOD_NAME_AND_PARAMS(klass, method), info->no_output);
        }
        else {
            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);
            append_int_value_to_code(info->code, method_index2, info->no_output);
        }

        info->stack_num-=num_params + 1;
        info->stack_num++;

        info->type = result_type;
    }
    
    return TRUE;
}

unsigned int sNodeTree_create_new_operator(sNodeType* node_type, unsigned int* params, int num_params, unsigned int array_num)
{
    unsigned int node = alloc_node();

    gNodes[node].uValue.sNewOperator.mType = node_type;
    gNodes[node].uValue.sNewOperator.mNumParams = num_params;
    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sNewOperator.mParams[i] = params[i];
    }
    gNodes[node].uValue.sNewOperator.mArrayNum = array_num;

    gNodes[node].mNodeType = kNodeTypeNewOperator;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_new_operator(unsigned int node, sCompileInfo* info)
{
    sNodeType* generics_types = gNodes[node].uValue.sNewOperator.mType;

    sNodeType* generics_types2;
    solve_generics_for_variable(generics_types, &generics_types2, info->pinfo->klass);

    sCLClass* klass = generics_types2->mClass;
    unsigned int array_num = gNodes[node].uValue.sNewOperator.mArrayNum;

    if(array_num > 0) {
        if(!compile(array_num, info)) {
            return FALSE;
        }
    }

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);
    append_int_value_to_code(info->code, array_num ? 1:0, info->no_output);

    info->stack_num++;

    if(array_num > 0) {
        int num_params = gNodes[node].uValue.sNewOperator.mNumParams;

        if(num_params > 0) {
            parser_err_msg(info->pinfo, "Array can't create with initialize method");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;

        }

        info->type = generics_types2;
        info->type->mArray = TRUE;

        info->stack_num--;
    }
    else {
        sNodeType* param_types[PARAMS_MAX];

        int num_params = gNodes[node].uValue.sNewOperator.mNumParams;

        char* method_name = "initialize";

        unsigned int params[PARAMS_MAX];

        memcpy(params, gNodes[node].uValue.sNewOperator.mParams, sizeof(unsigned int)*PARAMS_MAX);

        if(!compile_params(klass, method_name, num_params, params, param_types, generics_types2, info)) {
            return FALSE;
        }

        sNodeType* result_type;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, &result_type);

        if(method_index == -1) {
            parser_err_msg(info->pinfo, "method not found(3)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);
        append_int_value_to_code(info->code, method_index, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = generics_types2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_return_expression(unsigned int expression_node)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReturn;

    gNodes[node].mLeft = expression_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_return_expression(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int expression_node = gNodes[node].mLeft;

    sNodeType* result_value_type;
    if(expression_node != 0) {
        if(!compile(expression_node, info)) {
            return FALSE;
        }
        result_value_type = info->type;
    }
    else {
        result_value_type = NULL;
    }

    if(info->method == NULL && info->block_result_type == NULL) {
        parser_err_msg(info->pinfo, "Return expression should be in a method definition or in a block object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* result_type = NULL;
    if(info->block_result_type) {
        result_type = info->block_result_type;
    }
    else { // info->method != NULL
        result_type = create_node_type_from_cl_type(info->method->mResultType, info->pinfo->klass);
    }

    sNodeType* result_type2 = NULL;
    solve_generics_for_variable(result_type, &result_type2, info->pinfo->klass);

    if((!type_identify_with_class_name(result_type2, "Null") && expression_node == 0)
        || (type_identify_with_class_name(result_type2, "Null") && expression_node != 0))
    {
        parser_err_msg(info->pinfo, "Invalid type of return value(1)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(type_identify_with_class_name(result_type2, "Null")) {
        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);

        info->stack_num++;
    }
    else {
        cast_right_type_to_left_type(result_type2, &result_value_type, info);

        if(!substitution_posibility(result_type2, result_value_type, NULL, NULL)) {
            parser_err_msg(info->pinfo, "Invalid type of return value(2). Left type is %s. Right type is %s.", CLASS_NAME(result_type2->mClass), CLASS_NAME(result_value_type->mClass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(info->stack_num != 1) {
        parser_err_msg(info->pinfo, "Invalid type of return value(4)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_RETURN, info->no_output);

    info->stack_num = 0;   // no pop 

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_create_throw_expression(unsigned int expression_node)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeThrow;

    gNodes[node].mLeft = expression_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_throw_expression(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int expression_node = gNodes[node].mLeft;

    if(expression_node != 0) {
        if(!compile(expression_node, info)) {
            return FALSE;
        }
    }

    if(info->method == NULL) {
        parser_err_msg(info->pinfo, "Throw expressioin should be in a method definition");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* exception_type = info->type;

    if(!is_exception_type(exception_type))
    {
        parser_err_msg(info->pinfo, "Invalid type of exception value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_THROW, info->no_output);

    info->stack_num = 0;   // no pop 

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_try_expression(MANAGED sNodeBlock* try_node_block, MANAGED sNodeBlock* catch_node_block, char* exception_var_name)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTry;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sTry.mTryNodeBlock = MANAGED try_node_block;
    gNodes[node].uValue.sTry.mCatchNodeBlock = MANAGED catch_node_block;
    gNodes[node].uValue.sTry.mCatchNodeBlock = MANAGED catch_node_block;
    xstrncpy(gNodes[node].uValue.sTry.mExceptionVarName, exception_var_name, VAR_NAME_MAX);

    return node;
}

static BOOL compile_try_expression(unsigned int node, sCompileInfo* info)
{
    /// try ///
    append_opecode_to_code(info->code, OP_TRY, info->no_output);

    int try_offset_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    sNodeBlock* try_node_block = gNodes[node].uValue.sTry.mTryNodeBlock;
    if(!compile_block(try_node_block, info)) {
        return FALSE;
    }

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    *(int*)(info->code->mCodes + try_offset_point) = info->code->mLen;

    /// catch ///
    sNodeBlock* catch_node_block = gNodes[node].uValue.sTry.mCatchNodeBlock;

    sVarTable* catch_block_var_table = catch_node_block->mLVTable;
    char* var_name = gNodes[node].uValue.sTry.mExceptionVarName;

    int var_index = get_variable_index(catch_block_var_table, var_name);
    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    append_opecode_to_code(info->code, OP_POP, info->no_output);

    if(!compile_block(catch_node_block, info)) {
        return FALSE;
    }

    *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_create_fields(char* name, unsigned int left_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadField;

    xstrncpy(gNodes[node].uValue.mVarName, name, VAR_NAME_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_load_field(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if(info->type == NULL 
        || type_identify_with_class_name(info->type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for loading field");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = info->type->mClass;;
    char* field_name = gNodes[node].uValue.mVarName;
    BOOL array = info->type->mArray;
    sNodeType* generics_types = info->type;

    if(klass->mGenericsParamClassNum != -1) {
        sGenericsParamInfo* generics_info = &info->pinfo->generics_info;
        if(klass->mGenericsParamClassNum < generics_info->mNumParams) {
            klass = generics_info->mInterface[klass->mGenericsParamClassNum];
        }
        else {
            parser_err_msg(info->pinfo, "invalid generics interface method call");
            info->err_num++;
        }
    }

    sCLClass* regex_class = get_class("regex");

    /// special field ///
    if(array && strcmp(field_name, "length") == 0) {
        append_opecode_to_code(info->code, OP_GET_ARRAY_LENGTH, info->no_output);

        info->stack_num--;
        info->stack_num++;

        info->type = create_node_type_with_class_name("int");
    }
    else if(array && strcmp(field_name, "toArray") == 0) {
        cast_right_type_to_Array(&info->type, info);
    }
    else if(klass == regex_class && strcmp(field_name, "global") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_GLOBAL, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if(klass == regex_class && strcmp(field_name, "ignoreCase") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_IGNORE_CASE, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if(klass == regex_class && strcmp(field_name, "multiline") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_MULTILINE, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if(klass == regex_class && strcmp(field_name, "extended") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_EXTENDED, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if(klass == regex_class && strcmp(field_name, "dotAll") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_DOTALL, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if(klass == regex_class && strcmp(field_name, "anchored") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_ANCHORED, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if(klass == regex_class && strcmp(field_name, "dollarEndOnly") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_DOLLAR_ENDONLY, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if(klass == regex_class && strcmp(field_name, "ungreedy") == 0) {
        append_opecode_to_code(info->code, OP_GET_REGEX_UNGREEDY, info->no_output);

        info->type = create_node_type_with_class_name("bool");
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toString") == 0) {
        cast_right_type_to_String(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toByte") == 0) {
        cast_right_type_to_Byte(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toUByte") == 0) {
        cast_right_type_to_UByte(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toShort") == 0) {
        cast_right_type_to_Short(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toUShort") == 0) {
        cast_right_type_to_UShort(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toInteger") == 0) {
        cast_right_type_to_Integer(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toUInteger") == 0) {
        cast_right_type_to_UInteger(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toLong") == 0) {
        cast_right_type_to_Long(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toULong") == 0) {
        cast_right_type_to_ULong(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toFloat") == 0) {
        cast_right_type_to_Float(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toDouble") == 0) {
        cast_right_type_to_Double(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toPointer") == 0) {
        cast_right_type_to_Pointer(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toChar") == 0) {
        cast_right_type_to_Char(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toBool") == 0) {
        cast_right_type_to_Bool(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_byte") == 0)
    {
        cast_right_type_to_byte(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_ubyte") == 0)
    {
        cast_right_type_to_ubyte(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_short") == 0)
    {
        cast_right_type_to_short(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_ushort") == 0)
    {
        cast_right_type_to_ushort(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_int") == 0)
    {
        cast_right_type_to_int(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_uint") == 0)
    {
        cast_right_type_to_uint(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_long") == 0)
    {
        cast_right_type_to_long(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_ulong") == 0) 
    {
        cast_right_type_to_ulong(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_float") == 0) 
    {
        cast_right_type_to_float(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_double") == 0) 
    {
        cast_right_type_to_double(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_char") == 0) 
    {
        cast_right_type_to_char(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_pointer") == 0) 
    {
        cast_right_type_to_pointer(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "to_bool") == 0) 
    {
        cast_right_type_to_bool(&info->type, info);
    }
    else {
        int field_index = search_for_field(klass, field_name);

        if(field_index == -1) {
            parser_err_msg(info->pinfo, "There is no field(%s) in this class(%s)", field_name, CLASS_NAME(klass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLField* field = klass->mFields + field_index;
        sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

        /// solve generics ///
        sNodeType* solved_field_type;
        if(!solve_generics_types_for_node_type(field_type, ALLOC &solved_field_type, generics_types)) 
        {
            return FALSE;
        }

        /// generate code ///
        append_opecode_to_code(info->code, OP_LOAD_FIELD, info->no_output);
        append_int_value_to_code(info->code, field_index, info->no_output);

        info->stack_num--;
        info->stack_num++;

        info->type = solved_field_type;
    }

    return TRUE;
}

unsigned int sNodeTree_create_assign_field(char* var_name, unsigned int left_node, unsigned int right_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreField;

    xstrncpy(gNodes[node].uValue.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_store_field(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;
    sNodeType* generics_types = left_type;

    if(left_type == NULL 
        || type_identify_with_class_name(left_type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(right_type == NULL)
    {
        parser_err_msg(info->pinfo, "no type for right object type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = left_type->mClass;
    char* field_name = gNodes[node].uValue.mVarName;

    int field_index = search_for_field(klass, field_name);

    if(field_index == -1) {
        parser_err_msg(info->pinfo, "There is no field(%s) in this class(%s)", field_name, CLASS_NAME(klass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLField* field = klass->mFields + field_index;
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    /// solve generics ///
    sNodeType* solved_field_type;
    if(!solve_generics_types_for_node_type(field_type, ALLOC &solved_field_type, generics_types)) 
    {
        return FALSE;
    }

    cast_right_type_to_left_type(solved_field_type, &right_type, info);

    if(!substitution_posibility(solved_field_type, right_type, generics_types, NULL)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type(2). %s and %s", CLASS_NAME(solved_field_type->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;

    }

    append_opecode_to_code(info->code, OP_STORE_FIELD, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->stack_num--;

    info->type = solved_field_type;

    return TRUE;
}

unsigned int sNodeTree_create_class_fields(sCLClass* klass, char* name)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadClassField;

    xstrncpy(gNodes[node].uValue.sClassField.mVarName, name, VAR_NAME_MAX);
    gNodes[node].uValue.sClassField.mClass = klass;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_load_class_field(unsigned int node, sCompileInfo* info)
{
    sCLClass* klass = gNodes[node].uValue.sClassField.mClass;
    char* field_name = gNodes[node].uValue.sClassField.mVarName;

    int field_index = search_for_class_field(klass, field_name);

    if(field_index == -1) {
        parser_err_msg(info->pinfo, "There is no field(%s) in this class(%s)", field_name, CLASS_NAME(klass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLField* field = klass->mClassFields + field_index;
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    append_opecode_to_code(info->code, OP_LOAD_CLASS_FIELD, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->stack_num++;

    info->type = field_type;

    return TRUE;
}

unsigned int sNodeTree_create_assign_class_field(sCLClass* klass, char* name , unsigned int right_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreClassField;

    xstrncpy(gNodes[node].uValue.sClassField.mVarName, name, VAR_NAME_MAX);
    gNodes[node].uValue.sClassField.mClass = klass;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_store_class_field(unsigned int node, sCompileInfo* info)
{
    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(right_type == NULL)
    {
        parser_err_msg(info->pinfo, "no type for right object type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = gNodes[node].uValue.sClassField.mClass;
    char* field_name = gNodes[node].uValue.sClassField.mVarName;

    int field_index = search_for_class_field(klass, field_name);

    if(field_index == -1) {
        parser_err_msg(info->pinfo, "There is no field(%s) in this class(%s)", field_name, CLASS_NAME(klass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLField* field = klass->mClassFields + field_index;
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    cast_right_type_to_left_type(field_type, &right_type, info);

    if(!substitution_posibility(field_type, right_type, NULL, NULL)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type(3). Left type is %s. Right type is %s.", CLASS_NAME(field_type->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;

    }

    append_opecode_to_code(info->code, OP_STORE_CLASS_FIELD, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->type = field_type;

    return TRUE;
}

unsigned int sNodeTree_create_store_value_to_pointer(unsigned int left_node, sNodeType* node_type, unsigned int right_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreValueToPointer;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = node_type;

    return node;
}

BOOL compile_store_value_to_pointer(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].mType;

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(left_type == NULL 
        || !type_identify_with_class_name(left_type, "pointer"))
    {
        parser_err_msg(info->pinfo, "Left node requires the pointer class");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(right_type == NULL 
        || !substitution_posibility(node_type, right_type, NULL, NULL))
    {
        parser_err_msg(info->pinfo, "The different type between left type and right type(4)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// check node_type ///
    if(node_type->mArray) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_OBJECT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "int")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_INT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "uint")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_UINT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "byte")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_BYTE_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_UBYTE_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "short")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_SHORT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "ushort")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_USHORT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "long")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_LONG_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "ulong")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_ULONG_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "float")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_FLOAT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "double")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_DOUBLE_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "pointer")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_POINTER_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "char")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_CHAR_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "bool")) {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_BOOL_ADDRESS, info->no_output);
    }
    else {
        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_OBJECT_ADDRESS, info->no_output);
    }

    info->stack_num--;

    info->type = right_type;

    return TRUE;
}

unsigned int sNodeTree_create_load_value_from_pointer(unsigned int left_node, sNodeType* node_type)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadValueFromPointer;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = node_type;

    return node;
}

BOOL compile_load_value_from_pointer(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].mType;

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(left_type == NULL 
        || !type_identify_with_class_name(left_type, "pointer"))
    {
        parser_err_msg(info->pinfo, "Left node requires the pointer class");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// check node_type ///
    if(node_type->mArray) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_OBJECT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "int")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_INT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "uint")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_UINT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "byte")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_BYTE_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "ubyte")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_UBYTE_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "short")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_SHORT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "ushort")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_USHORT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "long")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_LONG_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "ulong")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_ULONG_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "float")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_FLOAT_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "double")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "pointer")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_POINTER_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "char")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_CHAR_ADDRESS, info->no_output);
    }
    else if(type_identify_with_class_name(node_type, "bool")) {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_BOOL_ADDRESS, info->no_output);
    }
    else {
        append_opecode_to_code(info->code, OP_LOAD_VALUE_FROM_OBJECT_ADDRESS, info->no_output);
    }

    info->type = node_type;

    return TRUE;
}

BOOL sNodeTree_create_increment_operand(unsigned int left_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIncrementOperand;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static void increment_operand_core(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic, BOOL with_value)
{
    if(!with_value) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;
    }

    append_opecode_to_code(info->code, add_operand, info->no_output);

    info->stack_num--;

    char* var_name = gNodes[lnode].uValue.mVarName;
    int var_index = get_variable_index(info->lv_table, var_name);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    if(!monadic) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;

        append_opecode_to_code(info->code, sub_operand, info->no_output);

        info->stack_num--;
    }
}

static BOOL increment_operand_core_for_field(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic, BOOL with_value)
{
    if(!with_value) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;
    }

    append_opecode_to_code(info->code, add_operand, info->no_output);

    info->stack_num--;

    /// compile left node of left node for getting object ///
    unsigned int llnode = gNodes[lnode].mLeft;

    if(!compile(llnode, info)) {
        return FALSE;
    }

    sCLClass* klass = info->type->mClass;
    char* field_name = gNodes[lnode].uValue.mVarName;

    int field_index = search_for_field(klass, field_name);

    MASSERT(field_index != -1);

    sCLField* field = klass->mFields + field_index;

    append_opecode_to_code(info->code, OP_REVERSE, info->no_output);

    append_opecode_to_code(info->code, OP_STORE_FIELD, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->stack_num--;

    if(!monadic) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;

        append_opecode_to_code(info->code, sub_operand, info->no_output);

        info->stack_num--;
    }

    return TRUE;
}

BOOL compile_increment_operand(unsigned int node, sCompileInfo* info) 
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if((gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField )|| info->type == NULL) {
        parser_err_msg(info->pinfo, "Invalid increment operand");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* node_type = info->type;

    if(gNodes[lnode].mNodeType == kNodeTypeLoadVariable) {
        if(type_identify_with_class_name(node_type, "int")) {
            increment_operand_core(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            increment_operand_core(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            increment_operand_core(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, FALSE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            increment_operand_core(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, FALSE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            increment_operand_core(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            increment_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            increment_operand_core(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, FALSE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            increment_operand_core(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, FALSE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            increment_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            increment_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else { // gNodes[lnode].mNodeType == kNodeTypeLoadField
        if(type_identify_with_class_name(node_type, "int")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_monadic_increment_operand(unsigned int right_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMonadicIncrementOperand;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_monadic_increment_operand(unsigned int node, sCompileInfo* info)
{
    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    if((gNodes[rnode].mNodeType != kNodeTypeLoadVariable && gNodes[rnode].mNodeType != kNodeTypeLoadField )|| info->type == NULL) 
    {
        parser_err_msg(info->pinfo, "Invalid monadic increment operand");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* node_type = info->type;

    if(gNodes[rnode].mNodeType == kNodeTypeLoadVariable) {
        if(type_identify_with_class_name(node_type, "int")) {
            increment_operand_core(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            increment_operand_core(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            increment_operand_core(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE, FALSE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            increment_operand_core(node, info, rnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, TRUE, FALSE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            increment_operand_core(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            increment_operand_core(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            increment_operand_core(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE, FALSE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            increment_operand_core(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE, FALSE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            increment_operand_core(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            increment_operand_core(node, info, rnode, OP_CADD, OP_CSUB, OP_LDCINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else { // gNodes[rnode].mNodeType == kNodeTypeLoadField
        if(type_identify_with_class_name(node_type, "int")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_CADD, OP_CSUB, OP_LDCINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_increment_operand_with_value(unsigned int left_node, unsigned int value)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIncrementWithValueOperand;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = value;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

BOOL compile_increment_operand_with_value(unsigned int node, sCompileInfo* info) 
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if((gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField )|| info->type == NULL) {
        parser_err_msg(info->pinfo, "Invalid increment operand");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type = info->type;

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    cast_right_type_to_left_type(left_type, &right_type, info);

    if(!substitution_posibility(left_type, right_type, NULL, NULL)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type(5). Left type is %s. Right type is %s.", CLASS_NAME(left_type->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(gNodes[lnode].mNodeType == kNodeTypeLoadVariable) {
        if(type_identify_with_class_name(left_type, "int")) {
            increment_operand_core(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(left_type, "uint")) {
            increment_operand_core(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(left_type, "byte")) {
            increment_operand_core(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, TRUE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(left_type, "ubyte")) {
            increment_operand_core(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, TRUE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(left_type, "short")) {
            increment_operand_core(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(left_type, "ushort")) {
            increment_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(left_type, "long")) {
            increment_operand_core(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, TRUE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(left_type, "ulong")) {
            increment_operand_core(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, TRUE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(left_type, "pointer")) {
            increment_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(left_type, "char")) {
            increment_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else { // gNodes[lnode].mNodeType == kNodeTypeLoadField
        if(type_identify_with_class_name(left_type, "int")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(left_type, "uint")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(left_type, "byte")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(left_type, "ubyte")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(left_type, "short")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(left_type, "ushort")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(left_type, "long")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(left_type, "ulong")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(left_type, "pointer")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(left_type, "char")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

static void decrement_operand_core(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic, BOOL with_value)
{
    if(!with_value) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
    }

    append_opecode_to_code(info->code, sub_operand, info->no_output);

    info->stack_num--;

    char* var_name = gNodes[lnode].uValue.mVarName;
    int var_index = get_variable_index(info->lv_table, var_name);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    if(!monadic) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;

        append_opecode_to_code(info->code, add_operand, info->no_output);

        info->stack_num--;
    }
}

static BOOL decrement_operand_core_for_field(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic, BOOL with_value)
{
    if(!with_value) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;
    }

    append_opecode_to_code(info->code, sub_operand, info->no_output);

    info->stack_num--;

    /// compile left node of left node for getting object ///
    unsigned int llnode = gNodes[lnode].mLeft;

    if(!compile(llnode, info)) {
        return FALSE;
    }

    sCLClass* klass = info->type->mClass;
    char* field_name = gNodes[lnode].uValue.mVarName;

    int field_index = search_for_field(klass, field_name);

    MASSERT(field_index != -1);

    sCLField* field = klass->mFields + field_index;

    append_opecode_to_code(info->code, OP_REVERSE, info->no_output);

    append_opecode_to_code(info->code, OP_STORE_FIELD, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->stack_num--;

    if(!monadic) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            append_int_value_to_code(info->code, 1, info->no_output);
            append_int_value_to_code(info->code, 0, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;

        append_opecode_to_code(info->code, add_operand, info->no_output);

        info->stack_num--;
    }

    return TRUE;
}

BOOL sNodeTree_create_decrement_operand(unsigned int left_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDecrementOperand;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

BOOL compile_decrement_operand(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if((gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField )|| info->type == NULL) {
        parser_err_msg(info->pinfo, "Invalid increment operand");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* node_type = info->type;

    if(gNodes[lnode].mNodeType == kNodeTypeLoadVariable) {
        if(type_identify_with_class_name(node_type, "int")) {
            decrement_operand_core(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            decrement_operand_core(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            decrement_operand_core(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, FALSE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            decrement_operand_core(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, FALSE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            decrement_operand_core(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            decrement_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCSHORT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            decrement_operand_core(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, FALSE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            decrement_operand_core(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, FALSE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            decrement_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCPOINTER, FALSE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            decrement_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else { // gNodes[lnode].mNodeType == kNodeTypeLoadField
        if(type_identify_with_class_name(node_type, "int")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_monadic_decrement_operand(unsigned int right_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMonadicDecrementOperand;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_monadic_decrement_operand(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    if((gNodes[rnode].mNodeType != kNodeTypeLoadVariable && gNodes[rnode].mNodeType != kNodeTypeLoadField )|| info->type == NULL) {
        parser_err_msg(info->pinfo, "Invalid increment operand");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* node_type = info->type;

    if(gNodes[rnode].mNodeType == kNodeTypeLoadVariable) {
        if(type_identify_with_class_name(node_type, "int")) {
            decrement_operand_core(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            decrement_operand_core(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            decrement_operand_core(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE, FALSE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            decrement_operand_core(node, info, rnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, TRUE, FALSE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            decrement_operand_core(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            decrement_operand_core(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCSHORT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            decrement_operand_core(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE, FALSE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            decrement_operand_core(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE, FALSE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            decrement_operand_core(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCPOINTER, TRUE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            decrement_operand_core(node, info, rnode, OP_CADD, OP_CSUB, OP_LDCINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else { // gNodes[rnode].mNodeType == kNodeTypeLoadField
        if(type_identify_with_class_name(node_type, "int")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_CADD, OP_CSUB, OP_LDCINT, TRUE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_decrement_operand_with_value(unsigned int left_node, unsigned int value)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDecrementWithValueOperand;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = value;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

BOOL compile_decrement_operand_with_value(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if((gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField )|| info->type == NULL) {
        parser_err_msg(info->pinfo, "Invalid increment operand");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type = info->type;

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    cast_right_type_to_left_type(left_type, &right_type, info);

    if(!substitution_posibility(left_type, right_type, NULL, NULL)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type(6). Left type is %s. Right type is %s.", CLASS_NAME(left_type->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(gNodes[lnode].mNodeType == kNodeTypeLoadVariable) {
        if(type_identify_with_class_name(left_type, "int")) {
            decrement_operand_core(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(left_type, "uint")) {
            decrement_operand_core(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(left_type, "byte")) {
            decrement_operand_core(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, TRUE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(left_type, "ubyte")) {
            decrement_operand_core(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, TRUE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(left_type, "short")) {
            decrement_operand_core(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(left_type, "ushort")) {
            decrement_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCSHORT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(left_type, "long")) {
            decrement_operand_core(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, TRUE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(left_type, "ulong")) {
            decrement_operand_core(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, TRUE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(left_type, "pointer")) {
            decrement_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCPOINTER, FALSE, TRUE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(left_type, "char")) {
            decrement_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else { // gNodes[lnode].mNodeType == kNodeTypeLoadField
        if(type_identify_with_class_name(left_type, "int")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(left_type, "uint")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(left_type, "byte")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(left_type, "ubyte")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(left_type, "short")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(left_type, "ushort")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(left_type, "long")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(left_type, "ulong")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(left_type, "pointer")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(left_type, "char")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadArrayElement;

    gNodes[node].mLeft = array;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = index_node;

    gNodes[node].mType = NULL;

    return node;
}

BOOL compile_load_array_element(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(left_type == NULL 
        || type_identify_with_class_name(left_type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for loading element");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(left_type->mArray == FALSE) {
        parser_err_msg(info->pinfo, "Clover2 can't get an element from this type.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile middle node ///
    unsigned int mnode = gNodes[node].mMiddle;

    if(!compile(mnode, info)) {
        return FALSE;
    }

    sNodeType* middle_type = info->type;

    /// check ///
    if(middle_type == NULL 
        || type_identify_with_class_name(middle_type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for element index");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* int_type = create_node_type_with_class_name("int");

    cast_right_type_to_left_type(int_type, &middle_type, info);

    if(!substitution_posibility_with_class_name(middle_type, "int")) {
        parser_err_msg(info->pinfo, "Type of index should be number");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// generate code ///
    append_opecode_to_code(info->code, OP_LOAD_ELEMENT, info->no_output);

    info->stack_num-=2;
    info->stack_num++;

    info->type = clone_node_type(left_type);
    info->type->mArray = FALSE;

    return TRUE;
}

unsigned int sNodeTree_create_store_array_element(unsigned int array, unsigned int index_node, unsigned int right_node)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreArrayElement;

    gNodes[node].mLeft = array;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = index_node;

    gNodes[node].mType = NULL;

    return node;
}

BOOL compile_store_array_element(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(left_type == NULL 
        || type_identify_with_class_name(left_type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(left_type->mArray == FALSE) {
        parser_err_msg(info->pinfo, "Clover2 can't get an element from this type.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile middle node ///
    unsigned int mnode = gNodes[node].mMiddle;

    if(!compile(mnode, info)) {
        return FALSE;
    }

    sNodeType* middle_type = info->type;

    if(middle_type == NULL 
        || type_identify_with_class_name(middle_type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for element index");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* int_type = create_node_type_with_class_name("int");

    cast_right_type_to_left_type(int_type, &middle_type, info);

    if(!substitution_posibility_with_class_name(middle_type, "int")) {
        parser_err_msg(info->pinfo, "Type of index should be number");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    if(right_type == NULL)
    {
        parser_err_msg(info->pinfo, "no type for right object type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type2 = clone_node_type(left_type);
    left_type2->mArray = FALSE;

    cast_right_type_to_left_type(left_type2, &right_type, info);

    if(!substitution_posibility(left_type2, right_type, NULL, NULL)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type(7). %s and %s", CLASS_NAME(left_type2->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    //// generate code ///
    append_opecode_to_code(info->code, OP_STORE_ELEMENT, info->no_output);

    info->stack_num-=2;

    info->type = right_type;

    return TRUE;
}

unsigned int sNodeTree_create_character_value(wchar_t c)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeChar;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.mCharacter = c;

    return node;
}

BOOL compile_char_value(unsigned int node, sCompileInfo* info)
{
    wchar_t c = gNodes[node].uValue.mCharacter;

    append_opecode_to_code(info->code, OP_LDCINT, info->no_output);
    append_int_value_to_code(info->code, (int)c, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("char");

    return TRUE;
}

unsigned int sNodeTree_create_string_value(MANAGED char* value)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeString;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.mString = MANAGED value;

    return node;
}

BOOL compile_string_value(unsigned int node, sCompileInfo* info)
{
    char* str = gNodes[node].uValue.mString;

    append_opecode_to_code(info->code, OP_CREATE_STRING, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, str, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("String");

    return TRUE;
}

unsigned int sNodeTree_create_buffer_value(MANAGED char* value)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBuffer;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.mString = MANAGED value;

    return node;
}

BOOL compile_buffer_value(unsigned int node, sCompileInfo* info)
{
    char* str = gNodes[node].uValue.mString;

    append_opecode_to_code(info->code, OP_CREATE_BUFFER, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, str, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("Buffer");

    return TRUE;
}

unsigned int sNodeTree_create_get_address(unsigned int rnode)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGetAddress;

    gNodes[node].mLeft = rnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

BOOL compile_get_address(unsigned int node, sCompileInfo* info)
{
    unsigned int lnode = gNodes[node].mLeft;

    if(gNodes[lnode].mNodeType == kNodeTypeLoadVariable) {
        sVar* var = get_variable_from_table(info->lv_table, gNodes[lnode].uValue.mVarName);

        if(var == NULL) {
            parser_err_msg(info->pinfo, "undeclared variable %s", gNodes[lnode].uValue.mVarName);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }

        int var_index = get_variable_index(info->lv_table, gNodes[lnode].uValue.mVarName);

        MASSERT(var_index != -1);

        append_opecode_to_code(info->code, OP_LOAD_ADDRESS, info->no_output);
        append_int_value_to_code(info->code, var_index, info->no_output);

        info->stack_num++;

        info->type = create_node_type_with_class_name("pointer");
    }
    else if(gNodes[lnode].mNodeType == kNodeTypeLoadField) {
        unsigned int llnode = gNodes[lnode].mLeft;

        if(!compile(llnode, info)) {
            return FALSE;
        }

        if(info->type == NULL 
            || type_identify_with_class_name(info->type, "Null"))
        {
            parser_err_msg(info->pinfo, "no type for loading field address");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLClass* klass = info->type->mClass;
        char* field_name = gNodes[lnode].uValue.mVarName;

        int field_index = search_for_field(klass, field_name);

        if(field_index == -1) {
            parser_err_msg(info->pinfo, "There is no field(%s) in this class(%s)", field_name, CLASS_NAME(klass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        /// generate code ///
        append_opecode_to_code(info->code, OP_LOAD_FIELD_ADDRESS, info->no_output);
        append_int_value_to_code(info->code, field_index, info->no_output);

        info->stack_num--;
        info->stack_num++;

        info->type = create_node_type_with_class_name("pointer");
    }
    else if(gNodes[lnode].mNodeType == kNodeTypeLoadClassField) {
        sCLClass* klass = gNodes[lnode].uValue.sClassField.mClass;
        char* field_name = gNodes[lnode].uValue.sClassField.mVarName;

        int field_index = search_for_class_field(klass, field_name);

        if(field_index == -1) {
            parser_err_msg(info->pinfo, "There is no field(%s) in this class(%s)", field_name, CLASS_NAME(klass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLField* field = klass->mClassFields + field_index;

        append_opecode_to_code(info->code, OP_LOAD_CLASS_FIELD_ADDRESS, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);
        append_int_value_to_code(info->code, field_index, info->no_output);

        info->stack_num++;

        info->type = create_node_type_with_class_name("pointer");
    }
    else {
        parser_err_msg(info->pinfo, "Require variable name for getting address");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

unsigned int sNodeTree_create_array_value(int num_elements, unsigned int array_elements[])
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeArrayValue;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements, array_elements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;

    return node;
}

BOOL compile_array_value(unsigned int node, sCompileInfo* info)
{
    unsigned int* elements = gNodes[node].uValue.sArrayValue.mArrayElements;
    int num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;

    if(num_elements == 0) {
        parser_err_msg(info->pinfo, "require element in array value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    unsigned int first_element_node = elements[0];

    if(!compile(first_element_node, info)) {
        return FALSE;
    }

    sNodeType* element_type = info->type;

    int i;
    for(i=1; i<num_elements; i++) {
        unsigned int element_node = elements[i];

        if(!compile(element_node, info)) {
            return FALSE;
        }

        if(!type_identify(element_type, info->type)) {
            parser_err_msg(info->pinfo, "Invalid element type. Left type is %s. Right type is %s", CLASS_NAME(element_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_ARRAY, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(element_type->mClass), info->no_output);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = element_type;
    info->type->mArray = TRUE;

    return TRUE;
}

unsigned int sNodeTree_create_carray_value(int num_elements, unsigned int array_elements[])
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCArrayValue;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements, array_elements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;

    return node;
}

static BOOL compile_carray_value(unsigned int node, sCompileInfo* info)
{
    unsigned int* elements = gNodes[node].uValue.sArrayValue.mArrayElements;
    int num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;

    if(num_elements == 0) {
        parser_err_msg(info->pinfo, "require element in array value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    unsigned int first_element_node = elements[0];

    if(!compile(first_element_node, info)) {
        return FALSE;
    }

    boxing_to_lapper_class(&info->type, info);

    sNodeType* element_type = info->type;

    BOOL generics_type_is_object = FALSE;

    int i;
    for(i=1; i<num_elements; i++) {
        unsigned int element_node = elements[i];

        if(!compile(element_node, info)) {
            return FALSE;
        }

        boxing_to_lapper_class(&info->type, info);

        if(!type_identify(element_type, info->type)) {
            generics_type_is_object = TRUE;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_CARRAY, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(element_type->mClass), info->no_output);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = create_node_type_with_class_name("Array");
    info->type->mNumGenericsTypes = 1;
    if(generics_type_is_object) {
        info->type->mGenericsTypes[0] = create_node_type_with_class_name("Object");
    }
    else {
        info->type->mGenericsTypes[0] = element_type;
    }

    return TRUE;
}

unsigned int sNodeTree_create_hash_value(int num_elements, unsigned int hash_keys[], unsigned int hash_items[])
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeHashValue;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sHashValue.mHashKeys, hash_keys, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    memcpy(gNodes[node].uValue.sHashValue.mHashItems, hash_items, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sHashValue.mNumHashElements = num_elements;

    return node;
}

unsigned int sNodeTree_create_list_value(int num_elements, unsigned int list_elements[])
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeListValue;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sListValue.mListElements, list_elements, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sListValue.mNumListElements = num_elements;

    return node;
}

BOOL compile_list_value(unsigned int node, sCompileInfo* info)
{
    unsigned int* elements = gNodes[node].uValue.sListValue.mListElements;
    int num_elements = gNodes[node].uValue.sListValue.mNumListElements;

    if(num_elements == 0) {
        parser_err_msg(info->pinfo, "require element in list value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    unsigned int first_element_node = elements[0];

    if(!compile(first_element_node, info)) {
        return FALSE;
    }

    boxing_to_lapper_class(&info->type, info);

    sNodeType* element_type = info->type;

    int i;
    for(i=1; i<num_elements; i++) {
        unsigned int element_node = elements[i];

        if(!compile(element_node, info)) {
            return FALSE;
        }

        boxing_to_lapper_class(&info->type, info);

        if(!type_identify(element_type, info->type)) {
            parser_err_msg(info->pinfo, "Invalid element type. Left type is %s. Right type is %s", CLASS_NAME(element_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_LIST, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(element_type->mClass), info->no_output);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = create_node_type_with_class_name("List");
    info->type->mNumGenericsTypes = 1;
    info->type->mGenericsTypes[0] = element_type;

    return TRUE;
}

unsigned int sNodeTree_create_tuple_value(int num_elements, unsigned int tuple_elements[])
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTupleValue;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sTupleValue.mTupleElements, tuple_elements, sizeof(unsigned int)*TUPLE_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sTupleValue.mNumTupleElements = num_elements;

    return node;
}

static BOOL compile_tuple_value(unsigned int node, sCompileInfo* info)
{
    unsigned int* elements = gNodes[node].uValue.sTupleValue.mTupleElements;
    int num_elements = gNodes[node].uValue.sTupleValue.mNumTupleElements;

    if(num_elements == 0) {
        parser_err_msg(info->pinfo, "require element in tuple value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* element_types[TUPLE_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        unsigned int element_node = elements[i];

        if(!compile(element_node, info)) {
            return FALSE;
        }

        boxing_to_lapper_class(&info->type, info);

        element_types[i] = info->type;
    }

    append_opecode_to_code(info->code, OP_CREATE_TUPLE, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);

    info->stack_num-= num_elements;
    info->stack_num++;

    char class_name[CLASS_NAME_MAX+1];

    snprintf(class_name, CLASS_NAME_MAX, "Tuple%d", num_elements);

    info->type = create_node_type_with_class_name(class_name);
    info->type->mNumGenericsTypes = num_elements;
    for(i=0; i<num_elements; i++) {
        info->type->mGenericsTypes[i] = element_types[i];
    }

    return TRUE;
}

BOOL compile_hash_value(unsigned int node, sCompileInfo* info)
{
    unsigned int* keys = gNodes[node].uValue.sHashValue.mHashKeys;
    unsigned int* items = gNodes[node].uValue.sHashValue.mHashItems;
    int num_elements = gNodes[node].uValue.sHashValue.mNumHashElements;

    if(num_elements == 0) {
        parser_err_msg(info->pinfo, "require element in hash value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    unsigned int first_key_node = keys[0];

    if(!compile(first_key_node, info)) {
        return FALSE;
    }

    sNodeType* key_type = info->type;

    boxing_to_lapper_class(&key_type, info);

    unsigned int first_item_node = items[0];

    if(!compile(first_item_node, info)) {
        return FALSE;
    }

    sNodeType* item_type = info->type;

    boxing_to_lapper_class(&item_type, info);

    int i;
    for(i=1; i<num_elements; i++) {
        unsigned int key = keys[i];

        if(!compile(key, info)) {
            return FALSE;
        }

        boxing_to_lapper_class(&info->type, info);

        if(!type_identify(key_type, info->type)) {
            parser_err_msg(info->pinfo, "Invalid key type. Left type is %s. Right type is %s", CLASS_NAME(key_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }

        unsigned int item = items[i];

        if(!compile(item, info)) {
            return FALSE;
        }

        boxing_to_lapper_class(&info->type, info);

        if(!type_identify(item_type, info->type)) {
            parser_err_msg(info->pinfo, "Invalid item type. Left type is %s. Right type is %s", CLASS_NAME(item_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_HASH, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(key_type->mClass), info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(item_type->mClass), info->no_output);

    info->stack_num-= num_elements * 2;
    info->stack_num++;

    info->type = create_node_type_with_class_name("Hash");
    info->type->mNumGenericsTypes = 2;
    info->type->mGenericsTypes[0] = key_type;
    info->type->mGenericsTypes[1] = item_type;

    return TRUE;
}

unsigned int sNodeTree_create_block_object(sParserParam* params, int num_params, sNodeType* result_type, MANAGED sNodeBlock* node_block, BOOL lambda)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBlockObject;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sBlockObject.mParams[i] = params[i]; // copy struct
    }

    gNodes[node].uValue.sBlockObject.mNumParams = num_params;
    gNodes[node].uValue.sBlockObject.mResultType = result_type;
    gNodes[node].uValue.sBlockObject.mBlockObjectCode = MANAGED node_block;
    gNodes[node].uValue.sBlockObject.mLambda = lambda;

    return node;
}

BOOL compile_block_object(unsigned int node, sCompileInfo* info)
{
    /// rename variables ///
    int num_params = gNodes[node].uValue.sBlockObject.mNumParams;
    sParserParam* params[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sBlockObject.mParams + i;
    }

    sNodeType* result_type = gNodes[node].uValue.sBlockObject.mResultType;
    sNodeBlock* node_block = gNodes[node].uValue.sBlockObject.mBlockObjectCode;
    BOOL lambda = gNodes[node].uValue.sBlockObject.mLambda;

    /// compile block ///
    sByteCode codes;
    sConst constant;

    sByteCode_init(&codes);
    sConst_init(&constant);

    sByteCode* codes_before = info->code;
    sConst* constant_before = info->constant;

    info->code = &codes;
    info->constant = &constant;

    sNodeType* block_result_type_before = info->block_result_type;
    info->block_result_type = result_type;

    if(!compile_block(node_block, info)) {
        info->code = codes_before;
        info->constant = constant_before;
        info->block_result_type = block_result_type_before;
        return FALSE;
    }

    info->code = codes_before;
    info->constant = constant_before;
    info->block_result_type = block_result_type_before;

    /// make block object ///
    append_opecode_to_code(info->code, OP_CREATE_BLOCK_OBJECT, info->no_output);

    int offset = sConst_append(info->constant, codes.mCodes, codes.mLen, info->no_output);
    append_int_value_to_code(info->code, offset, info->no_output);
    append_int_value_to_code(info->code, codes.mLen, info->no_output);

    int offset2 = sConst_append(info->constant, constant.mConst, constant.mLen, info->no_output);
    append_int_value_to_code(info->code, offset2, info->no_output);
    append_int_value_to_code(info->code, constant.mLen, info->no_output);

    int var_num;
    if(node_block->mLVTable) {
        var_num = get_var_num(node_block->mLVTable);
    }
    else {
        var_num = 0;
    }

    append_int_value_to_code(info->code, var_num, info->no_output);

    if(lambda) {
        int parent_var_num = 0;
        append_int_value_to_code(info->code, parent_var_num, info->no_output);
        append_int_value_to_code(info->code, TRUE, info->no_output);
    }
    else {
        int parent_var_num = get_var_num(node_block->mLVTable->mParent);
        append_int_value_to_code(info->code, parent_var_num, info->no_output);
        append_int_value_to_code(info->code, FALSE, info->no_output);
    }

    info->stack_num++;

    /// make info->type ///
    info->type = create_node_type_with_class_name("lambda");

    sNodeBlockType* node_block_type = alloc_node_block_type();

    node_block_type->mNumParams = num_params;
    node_block_type->mResultType = result_type;
    for(i=0; i<num_params; i++) {
        node_block_type->mParams[i] = params[i]->mType;
    }

    info->type->mBlockType = node_block_type;

    return TRUE;
}

unsigned int sNodeTree_create_normal_block(MANAGED sNodeBlock* node_block)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNormalBlock;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.mBlock = MANAGED node_block;

    return node;
}

static BOOL compile_normal_block(unsigned int node, sCompileInfo* info)
{
    /// rename variables ///
    sNodeBlock* node_block = gNodes[node].uValue.mBlock;

    /// compile block ///
    if(!compile_block(node_block, info)) {
        return FALSE;
    }

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");

    return TRUE;
}

unsigned int sNodeTree_create_block_call(unsigned int block, int num_params, unsigned int params[])
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBlockCall;

    gNodes[node].mLeft = block;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sBlockCall.mNumParams = num_params;

    int i;
    for(i=0; i<gNodes[node].uValue.sBlockCall.mNumParams; i++) {
        gNodes[node].uValue.sBlockCall.mParams[i] = params[i];
    }

    return node;
}

BOOL compile_block_call(unsigned int node, sCompileInfo* info)
{
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if(info->type == NULL 
        || type_identify_with_class_name(info->type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for block call");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* var_type = info->type;

    if(!type_identify_with_class_name(var_type, "lambda")) {
        parser_err_msg(info->pinfo, "No block type, clover2 can call block object only");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    /// compile params ///
    sNodeType* param_types[PARAMS_MAX];

    int num_params = gNodes[node].uValue.sBlockCall.mNumParams;

    int i;
    for(i=0; i<num_params; i++) {
        unsigned int node2 = gNodes[node].uValue.sBlockCall.mParams[i];
        if(!compile(node2, info)) {
            return FALSE;
        }

        param_types[i] = info->type;
    }

    if(num_params != var_type->mBlockType->mNumParams) {
        parser_err_msg(info->pinfo, "Type error for block call");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    /// type check compile params ///
    for(i=0; i<num_params; i++) {
        sNodeType* left_type = var_type->mBlockType->mParams[i];
        sNodeType* right_type = param_types[i];

        sCLClass* klass = info->pinfo->klass;
        if(klass) {
            sNodeType* generics_types = create_generics_types_from_generics_params(klass);

            if(!substitution_posibility(left_type, right_type, generics_types, NULL)) {
                parser_err_msg(info->pinfo, "Type error for block call");
                info->err_num++;
            }
        }
        else {
            if(!substitution_posibility(left_type, right_type, NULL, NULL)) {
                parser_err_msg(info->pinfo, "Type error for block call");
                info->err_num++;
            }
        }
    }

    /// invoke block ///
    sNodeBlockType* block_type = var_type->mBlockType;

    append_opecode_to_code(info->code, OP_INVOKE_BLOCK, info->no_output);
    append_int_value_to_code(info->code, num_params, info->no_output);

    info->stack_num-=(num_params+1);
    info->stack_num++;

    info->type = block_type->mResultType;

    return TRUE;
}

unsigned int sNodeTree_create_regex(MANAGED char* regex_str, BOOL global, BOOL ignore_case, BOOL multiline, BOOL extended, BOOL dotall, BOOL anchored, BOOL dollar_endonly, BOOL ungreedy)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRegex;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sRegex.mRegexStr = MANAGED regex_str;
    gNodes[node].uValue.sRegex.mGlobal = global;
    gNodes[node].uValue.sRegex.mIgnoreCase = ignore_case;
    gNodes[node].uValue.sRegex.mMultiline = multiline;
    gNodes[node].uValue.sRegex.mExtended = extended;
    gNodes[node].uValue.sRegex.mDotAll = dotall;
    gNodes[node].uValue.sRegex.mAnchored = anchored;
    gNodes[node].uValue.sRegex.mDollarEndOnly = dollar_endonly;
    gNodes[node].uValue.sRegex.mUngreedy = ungreedy;

    return node;
}

static BOOL compile_regex(unsigned int node, sCompileInfo* info)
{
    char* str = gNodes[node].uValue.sRegex.mRegexStr;
    BOOL global = gNodes[node].uValue.sRegex.mGlobal;
    BOOL ignore_case = gNodes[node].uValue.sRegex.mIgnoreCase;
    BOOL multiline = gNodes[node].uValue.sRegex.mMultiline;
    BOOL extended = gNodes[node].uValue.sRegex.mExtended;
    BOOL dotall = gNodes[node].uValue.sRegex.mDotAll;
    BOOL anchored = gNodes[node].uValue.sRegex.mAnchored;
    BOOL dollar_endonly = gNodes[node].uValue.sRegex.mDollarEndOnly;
    BOOL ungreedy = gNodes[node].uValue.sRegex.mUngreedy;

    append_opecode_to_code(info->code, OP_CREATE_REGEX, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, str, info->no_output);
    append_int_value_to_code(info->code, global, info->no_output);
    append_int_value_to_code(info->code, ignore_case, info->no_output);
    append_int_value_to_code(info->code, multiline, info->no_output);
    append_int_value_to_code(info->code, extended, info->no_output);
    append_int_value_to_code(info->code, dotall, info->no_output);
    append_int_value_to_code(info->code, anchored, info->no_output);
    append_int_value_to_code(info->code, dollar_endonly, info->no_output);
    append_int_value_to_code(info->code, ungreedy, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("regex");

    return TRUE;
}

unsigned int sNodeTree_create_implements(unsigned int lnode, char* interface_name)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeImplements;

    gNodes[node].mLeft = lnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    xstrncpy(gNodes[node].uValue.mVarName, interface_name, VAR_NAME_MAX);

    return node;
}

static BOOL compile_implements(unsigned int node, sCompileInfo* info)
{
    char* interface_name = gNodes[node].uValue.mVarName;

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    if(info->type == NULL 
        || type_identify_with_class_name(info->type, "Null"))
    {
        parser_err_msg(info->pinfo, "no type for implements");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = info->type->mClass;

    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        parser_err_msg(info->pinfo, "Primitive value doesn't have class info");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->stack_num--;

    append_opecode_to_code(info->code, OP_IMPLMENTS, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, interface_name, info->no_output);

    info->type = create_node_type_with_class_name("bool");
    info->stack_num++;

    return TRUE;
}

void show_node(unsigned int node)
{
    if(node == 0) {
        return;
    }

    switch(gNodes[node].mNodeType) {
        case kNodeTypeOperand:
            printf("operand value %d\n", gNodes[node].uValue.mOperand);
            puts("left");
            show_node(gNodes[node].mLeft);
            puts("right");
            show_node(gNodes[node].mRight);
            break;

        case kNodeTypeConditional:
            puts("conditional operator");
            break;

        case kNodeTypeAndAnd:
            puts("and and operator");
            break;

        case kNodeTypeOrOr:
            puts("or or operator");
            break;

        case kNodeTypeByteValue:
            printf("byte value %d\n", gNodes[node].uValue.mByteValue);
            break;

        case kNodeTypeUByteValue:
            printf("ubyte value %u\n", gNodes[node].uValue.mUByteValue);
            break;

        case kNodeTypeShortValue:
            printf("short value %d\n", gNodes[node].uValue.mShortValue);
            break;

        case kNodeTypeUShortValue:
            printf("ushort value %u\n", gNodes[node].uValue.mUShortValue);
            break;

        case kNodeTypeIntValue:
            printf("int value %d\n", gNodes[node].uValue.mIntValue);
            break;

        case kNodeTypeUIntValue:
            printf("uint value %u\n", gNodes[node].uValue.mUIntValue);
            break;

        case kNodeTypeLongValue:
            printf("long value %ld\n", gNodes[node].uValue.mLongValue);
            break;

        case kNodeTypeULongValue:
            printf("long value %lu\n", gNodes[node].uValue.mULongValue);
            break;

        case kNodeTypeAssignVariable:
            printf("var name %s\n", gNodes[node].uValue.mVarName);
            break;

        case kNodeTypeLoadVariable:
            printf("var name %s\n", gNodes[node].uValue.mVarName);
            break;

        case kNodeTypeIf:
            puts("if expression");
            break;

        case kNodeTypeWhile:
            puts("while expression");
            break;

        case kNodeTypeFor:
            puts("for expression");
            break;

        case kNodeTypeBreak:
            puts("break");
            break;

        case kNodeTypeTrue:
            puts("true");
            break;

        case kNodeTypeFalse:
            puts("false");
            break;

        case kNodeTypeNull:
            puts("null");
            break;

        case kNodeTypeClassMethodCall:
            puts("class method call");
            break;

        case kNodeTypeMethodCall:
            puts("method call");
            break;

        case kNodeTypeNewOperator:
            puts("new operator");
            break;

        case kNodeTypeReturn:
            puts("return");
            break;

        case kNodeTypeThrow:
            puts("throw");
            break;

        case kNodeTypeLoadField: {
            puts("load field");
            //char* field_name = gNodes[node].uValue.mVarName;
            //printf("field name %s\n", field_name);
            }
            break;

        case kNodeTypeStoreField:
            puts("store field");
            break;

        case kNodeTypeLoadClassField:
            puts("load field");
            break;

        case kNodeTypeStoreClassField:
            puts("store class field");
            break;

        case kNodeTypeStoreValueToPointer:
            puts("store value to pointer");
            break;

        case kNodeTypeLoadValueFromPointer:
            puts("load value from pointer");
            break;

        case kNodeTypeIncrementOperand:
            puts("increment operand");
            break;

        case kNodeTypeDecrementOperand:
            puts("decrement operand");
            break;

        case kNodeTypeIncrementWithValueOperand:
            puts("increment operand with value");
            break;

        case kNodeTypeDecrementWithValueOperand:
            puts("decrement operand with value");
            break;

        case kNodeTypeMonadicIncrementOperand:
            puts("monadic increment operand");
            break;

        case kNodeTypeMonadicDecrementOperand:
            puts("monadic decrement operand");
            break;

        case kNodeTypeStoreArrayElement:
            puts("load element");
            break;

        case kNodeTypeChar:
            puts("char");
            break;

        case kNodeTypeString:
            puts("string");
            break;

        case kNodeTypeBuffer:
            puts("buffer");
            break;

        case kNodeTypeGetAddress:
            puts("get address");
            break;

        case kNodeTypeArrayValue:
            puts("array value");
            break;

        case kNodeTypeCArrayValue:
            puts("carray value");
            break;

        case kNodeTypeHashValue:
            puts("hash value");
            break;

        case kNodeTypeListValue:
            puts("list value");
            break;

        case kNodeTypeTupleValue:
            puts("tuple value");
            break;

        case kNodeTypeTry:
            puts("try");
            break;

        case kNodeTypeBlockObject:
            puts("lambda");
            break;

        case kNodeTypeNormalBlock:
            puts("block");
            break;

        case kNodeTypeLoadArrayElement:
            puts("load element");
            break;

        case kNodeTypeBlockCall:
            puts("block call");
            break;

        case kNodeTypeRegex:
            puts("regex");
            break;

        case kNodeTypeImplements:
            puts("implements");
            break;
    }
}

BOOL compile(unsigned int node, sCompileInfo* info)
{
    if(node == 0) {
        return TRUE;
    }

    switch(gNodes[node].mNodeType) {
        case kNodeTypeOperand:
            if(!compile_operand(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeConditional:
            if(!compile_conditional_operator(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAndAnd:
            if(!compile_and_and(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOrOr:
            if(!compile_or_or(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeByteValue:
            if(!compile_byte_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUByteValue:
            if(!compile_ubyte_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeShortValue:
            if(!compile_short_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUShortValue:
            if(!compile_ushort_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIntValue:
            if(!compile_int_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUIntValue:
            if(!compile_uint_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLongValue:
            if(!compile_long_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeULongValue:
            if(!compile_ulong_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAssignVariable:
            if(!compile_store_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadVariable:
            if(!compile_load_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIf:
            if(!compile_if_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeWhile:
            if(!compile_while_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFor:
            if(!compile_for_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBreak:
            if(!compile_break_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeTrue:
            if(!compile_true_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFalse:
            if(!compile_false_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNull:
            if(!compile_null_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeClassMethodCall:
            if(!compile_class_method_call(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMethodCall:
            if(!compile_method_call(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNewOperator:
            if(!compile_new_operator(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeReturn:
            if(!compile_return_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeThrow:
            if(!compile_throw_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadField:
            if(!compile_load_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreField:
            if(!compile_store_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadClassField:
            if(!compile_load_class_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreClassField:
            if(!compile_store_class_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreValueToPointer:
            if(!compile_store_value_to_pointer(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadValueFromPointer:
            if(!compile_load_value_from_pointer(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIncrementOperand:
            if(!compile_increment_operand(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDecrementOperand:
            if(!compile_decrement_operand(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIncrementWithValueOperand:
            if(!compile_increment_operand_with_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDecrementWithValueOperand:
            if(!compile_decrement_operand_with_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMonadicIncrementOperand:
            if(!compile_monadic_increment_operand(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMonadicDecrementOperand:
            if(!compile_monadic_decrement_operand(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadArrayElement:
            if(!compile_load_array_element(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreArrayElement:
            if(!compile_store_array_element(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeChar:
            if(!compile_char_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeString:
            if(!compile_string_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBuffer:
            if(!compile_buffer_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeGetAddress:
            if(!compile_get_address(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeArrayValue:
            if(!compile_array_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCArrayValue:
            if(!compile_carray_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeListValue:
            if(!compile_list_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeTupleValue:
            if(!compile_tuple_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeHashValue:
            if(!compile_hash_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeTry:
            if(!compile_try_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBlockObject:
            if(!compile_block_object(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNormalBlock:
            if(!compile_normal_block(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeBlockCall:
            if(!compile_block_call(node,info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRegex:
            if(!compile_regex(node,info)) {
                return FALSE;
            }
            break;

        case kNodeTypeImplements:
            if(!compile_implements(node,info)) {
                return FALSE;
            }
            break;
    }

    return TRUE;
}

void arrange_stack(sCompileInfo* cinfo)
{
    if(cinfo->stack_num < 0) {
        parser_err_msg(cinfo->pinfo, "Unexpected error. Stack pointer is invalid(stack number is %d)", cinfo->stack_num);
        cinfo->err_num++;
    }
    else if(cinfo->stack_num == 0) {
    }
    else if(cinfo->stack_num == 1) {
        append_opecode_to_code(cinfo->code, OP_POP, cinfo->no_output);
    }
    else {
        append_opecode_to_code(cinfo->code, OP_POP_N, cinfo->no_output);
        append_int_value_to_code(cinfo->code, cinfo->stack_num, cinfo->no_output);
    }

    cinfo->stack_num = 0;
}

BOOL check_node_is_variable(unsigned int node)
{
    return gNodes[node].mNodeType == kNodeTypeLoadVariable;
}

