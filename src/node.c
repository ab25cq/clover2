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

                case kNodeTypeFor:
                    if(gNodes[i].uValue.sFor.mForNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sFor.mForNodeBlock);
                    }
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

static BOOL single_operator(sNodeType* type, int byte_operand, int short_operand, int int_operand, int long_operand, sCompileInfo* info)
{
    if(type_identify_with_class_name(type, "byte")) {
        append_opecode_to_code(info->code, byte_operand, info->no_output);

        info->type = create_node_type_with_class_name("byte");
    }
    else if(type_identify_with_class_name(type, "short")) {
        append_opecode_to_code(info->code, short_operand, info->no_output);

        info->type = create_node_type_with_class_name("short");
    }
    else if(type_identify_with_class_name(type, "int")) {
        append_opecode_to_code(info->code, int_operand, info->no_output);

        info->type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(type, "long")) {
        append_opecode_to_code(info->code, long_operand, info->no_output);

        info->type = create_node_type_with_class_name("long");
    }

    return TRUE;
}

static void cast_right_type_to_byte(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte");
    }
    else if(type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_INT_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte");
    }
    else if(type_identify_with_class_name(*right_type, "long") || type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_LONG_TO_BYTE_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("byte");
    }
}

static void cast_right_type_to_short(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte") || type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short");
    }
    else if(type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_INT_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short");
    }
    else if(type_identify_with_class_name(*right_type, "long") || type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_LONG_TO_SHORT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("short");
    }
}

static void cast_right_type_to_int(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte") || type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(*right_type, "long") || type_identify_with_class_name(*right_type, "ulong")) 
    {
        append_opecode_to_code(info->code, OP_LONG_TO_INT_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("int");
    }
}

static void cast_right_type_to_long(sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(*right_type, "byte") || type_identify_with_class_name(*right_type, "ubyte")) 
    {
        append_opecode_to_code(info->code, OP_BYTE_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long");
    }
    else if(type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "ushort")) 
    {
        append_opecode_to_code(info->code, OP_SHORT_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long");
    }
    else if(type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "uint")) 
    {
        append_opecode_to_code(info->code, OP_INT_TO_LONG_CAST, info->no_output);

        *right_type = create_node_type_with_class_name("long");
    }
}

static void cast_right_type_to_left_type(sNodeType* left_type, sNodeType** right_type, sCompileInfo* info)
{
    if(type_identify_with_class_name(left_type, "byte") || type_identify_with_class_name(left_type, "ubyte")) 
    {
        cast_right_type_to_byte(right_type, info);
        *right_type = create_node_type_with_class_name("byte");
    }
    else if(type_identify_with_class_name(left_type, "short") || type_identify_with_class_name(left_type, "ushort"))
    {
        cast_right_type_to_short(right_type, info);
        *right_type = create_node_type_with_class_name("short");
    }
    else if(type_identify_with_class_name(left_type, "int") || type_identify_with_class_name(left_type, "uint"))
    {
        cast_right_type_to_int(right_type, info);
        *right_type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(left_type, "long") || type_identify_with_class_name(left_type, "ulong"))
    {
        cast_right_type_to_long(right_type, info);
        *right_type = create_node_type_with_class_name("long");
    }
}

static BOOL binary_operator(sNodeType* left_type, sNodeType* right_type, int byte_operand, int ubyte_operand, int short_operand, int ushort_operand, int int_operand, int uint_operand, int long_operand, int ulong_operand, int float_operand, int double_operand, int pointer_operand, int null_operand, char* op_string, sCompileInfo* info)
{
    cast_right_type_to_left_type(left_type, &right_type, info);

    if(!operand_posibility(left_type, right_type)) {
        parser_err_msg(info->pinfo, "Invalid type for operand. The left type is %s. The right type is %s.", CLASS_NAME(left_type->mClass), CLASS_NAME(right_type->mClass));
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

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;
    sNodeType* node_type = left_type;

    switch(gNodes[node].uValue.mOperand) {
        case kOpAdd:
            if(!binary_operator(left_type, right_type, OP_BADD, OP_UBADD, OP_SADD, OP_USADD, OP_IADD, OP_UIADD, OP_LADD, OP_ULADD, OP_FADD, OP_DADD, OP_PADD, -1, "+", info))
            {
                return FALSE;
            }
            break;

        case kOpSub:
            if(!binary_operator(left_type, right_type, OP_BSUB, OP_UBSUB, OP_SSUB, OP_USSUB, OP_ISUB, OP_UISUB, OP_LSUB, OP_ULSUB, OP_FSUB, OP_DSUB, OP_PSUB, -1, "-", info))
            {
                return FALSE;
            }
            break;

        case kOpComplement:
            break;
            
        case kOpLogicalDenial:
            break;
            
        case kOpMult:
            break;
            
        case kOpDiv:
            break;
            
        case kOpMod:
            break;
            
        case kOpLeftShift:
            break;
            
        case kOpRightShift:
            break;
            
        case kOpComparisonEqual:
            if(!binary_operator(left_type, right_type, OP_BEQ, OP_UBEQ, OP_SEQ, OP_USEQ, OP_IEQ, OP_UIEQ, OP_LEQ, OP_ULEQ, OP_FEQ, OP_DEQ, OP_PEQ, OP_IEQ, "==", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonNotEqual:
            if(!binary_operator(left_type, right_type, OP_BNOTEQ, OP_UBNOTEQ, OP_SNOTEQ, OP_USNOTEQ, OP_INOTEQ, OP_UINOTEQ, OP_LNOTEQ, OP_ULNOTEQ, OP_FNOTEQ, OP_DNOTEQ, OP_PNOTEQ, OP_INOTEQ, "!=", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonGreaterEqual:
            break;
            
        case kOpComparisonLesserEqual:
            break;
            
        case kOpComparisonGreater:
            break;
            
        case kOpComparisonLesser:
            break;
            
        case kOpAnd:
            break;
            
        case kOpXor:
            break;
            
        case kOpOr:
            break;
            
        case kOpAndAnd:
            if(!binary_operator_for_bool(left_type, OP_ANDAND, info))
            {
                return FALSE;
            }
            break;
            
        case kOpOrOr:
            if(!binary_operator_for_bool(left_type, OP_OROR, info))
            {
                return FALSE;
            }
            break;
            
        case kOpConditional:
            break;

/*
        case kOpComplement:
            if(!single_operator(node_type, OP_BCOMPLEMENT, OP_SHCOMPLEMENT, OP_ICOMPLEMENT, OP_LCOMPLEMENT, info))
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

        case kOpComparisonEqual:
            {
                if(type_identify_with_class_name(node_type, "int")) {
                    append_opecode_to_code(info->code, OP_IEQ, info->no_output);
                    info->stack_num--;

                    info->type = create_node_type_with_class_name("bool");
                }
            }
            break;

        case kOpComparisonNotEqual:
            {
                if(type_identify_with_class_name(node_type, "int")) {
                    append_opecode_to_code(info->code, OP_INOTEQ, info->no_output);
                    info->stack_num--;

                    info->type = create_node_type_with_class_name("bool");
                }
            }
            break;
*/
    }

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

    cast_right_type_to_left_type(left_type, &right_type, info);

    if(!substitution_posibility(left_type, right_type)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;

    }

    int var_index = get_variable_index(info->lv_table, gNodes[node].uValue.sAssignVariable.mVarName);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    info->type = gNodes[node].mType;

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

    info->type = gNodes[node].mType;

    if(info->type == NULL) {
        parser_err_msg(info->pinfo, "null type %s", gNodes[node].uValue.mVarName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

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
    if(!compile_normal_block(if_block, info)) {
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
            if(!compile_normal_block(elif_block, info)) {
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
        if(!compile_normal_block(else_node_block, info)) {
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
    if(!compile_normal_block(while_block, info)) {
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
    if(!compile_normal_block(for_block, info)) {
        return FALSE;
    }

    info->num_break_points = num_break_points_before;
    info->break_points = break_points_before;

    /// expression 3 ///
    unsigned int expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;

    if(!compile(expression_node3, info)) {
        return FALSE;
    }

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
    int method_index = search_for_method(klass, method_name, param_types, num_params, TRUE, klass->mNumMethods-1, NULL, &result_type);

    if(method_index == -1) {
        parser_err_msg(info->pinfo, "method not found");
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

unsigned int sNodeTree_create_new_operator(sNodeType* node_type, unsigned int* params, int num_params)
{
    unsigned int node = alloc_node();

    gNodes[node].uValue.sNewOperator.mType = node_type;
    gNodes[node].uValue.sNewOperator.mNumParams = num_params;
    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sNewOperator.mParams[i] = params[i];
    }

    gNodes[node].mNodeType = kNodeTypeNewOperator;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_new_operator(unsigned int node, sCompileInfo* info)
{
    sCLClass* klass = gNodes[node].uValue.sNewOperator.mType->mClass;

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, CLASS_NAME(klass), info->no_output);

    info->stack_num++;

    sNodeType* param_types[PARAMS_MAX];

    int num_params = gNodes[node].uValue.sNewOperator.mNumParams;

    int i;
    for(i=0; i<num_params; i++) {
        int node2 = gNodes[node].uValue.sNewOperator.mParams[i];
        if(!compile(node2, info)) {
            return FALSE;
        }

        param_types[i] = info->type;
    }

    char* method_name = "initialize";

    sNodeType* result_type;
    int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, NULL, &result_type);

    if(method_index == -1) {
        parser_err_msg(info->pinfo, "method not found");
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

    info->type = gNodes[node].uValue.sNewOperator.mType;
    
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

    if(expression_node != 0) {
        if(!compile(expression_node, info)) {
            return FALSE;
        }
    }

    if(info->method == NULL) {
        parser_err_msg(info->pinfo, "Return expressioin should be in a method definition");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* result_type = create_node_type_from_cl_type(info->method->mResultType, info->pinfo->klass);

    if((!type_identify_with_class_name(result_type, "Null") && expression_node == 0)
        || (type_identify_with_class_name(result_type, "Null") && expression_node != 0))
    {
        parser_err_msg(info->pinfo, "Invalid type of return value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* value_type = info->type;
    cast_right_type_to_left_type(result_type, &value_type, info);

    if(!substitution_posibility(result_type, value_type)) {
        parser_err_msg(info->pinfo, "Invalid type of return value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(type_identify_with_class_name(result_type, "Null")) {
        if(info->stack_num != 0) {
            parser_err_msg(info->pinfo, "Invalid type of return value");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else {
        if(info->stack_num != 1) {
            parser_err_msg(info->pinfo, "Invalid type of return value");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    append_opecode_to_code(info->code, OP_RETURN, info->no_output);

    info->stack_num = 0;   // no pop 

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

    sCLClass* klass = info->type->mClass;
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

    append_opecode_to_code(info->code, OP_LOAD_FIELD, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->stack_num--;
    info->stack_num++;

    info->type = field_type;

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

    if(right_type == NULL 
        || type_identify_with_class_name(right_type, "Null"))
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

    cast_right_type_to_left_type(field_type, &right_type, info);

    if(!substitution_posibility(field_type, right_type)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;

    }

    append_opecode_to_code(info->code, OP_STORE_FIELD, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->stack_num--;

    info->type = field_type;

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

    if(right_type == NULL 
        || type_identify_with_class_name(right_type, "Null"))
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

    if(!substitution_posibility(field_type, right_type)) {
        parser_err_msg(info->pinfo, "The different type between left type and right type");
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
        || !substitution_posibility(node_type, right_type))
    {
        parser_err_msg(info->pinfo, "The different type between left type and right type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// check node_type ///
    if(node_type && !(node_type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE)) {
        parser_err_msg(info->pinfo, "Pointer class can't cast for none primitive class");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(type_identify_with_class_name(node_type, "int")) {
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
    else {
        parser_err_msg(info->pinfo, "Invalid type for pointer cast");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
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
    if(node_type && !(node_type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE)) {
        parser_err_msg(info->pinfo, "Pointer class can't cast for none primitive class");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(type_identify_with_class_name(node_type, "int")) {
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
    else {
        parser_err_msg(info->pinfo, "Invalid type for pointer cast");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
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

static void increment_operand_core(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic)
{
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

static BOOL increment_operand_core_for_field(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic)
{
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
            increment_operand_core(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            increment_operand_core(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            increment_operand_core(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            increment_operand_core(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            increment_operand_core(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            increment_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            increment_operand_core(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            increment_operand_core(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            increment_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE);
            info->type = create_node_type_with_class_name("pointer");
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
            if(!increment_operand_core_for_field(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!increment_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
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

static void decrement_operand_core(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic)
{
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

static BOOL decrement_operand_core_for_field(unsigned int node, sCompileInfo* info, unsigned int lnode, int add_operand, int sub_operand, int ldc_operand, BOOL monadic)
{
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
            decrement_operand_core(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            decrement_operand_core(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            decrement_operand_core(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            decrement_operand_core(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            decrement_operand_core(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            decrement_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCSHORT, FALSE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            decrement_operand_core(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            decrement_operand_core(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            decrement_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCPOINTER, FALSE);
            info->type = create_node_type_with_class_name("pointer");
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
            if(!decrement_operand_core_for_field(node, info, lnode, OP_IADD, OP_ISUB, OP_LDCINT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_BADD, OP_BSUB, OP_LDCBYTE, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UIADD, OP_UISUB, OP_LDCUINT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_SADD, OP_SSUB, OP_LDCSHORT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_LADD, OP_LSUB, OP_LDCLONG, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!decrement_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCINT, FALSE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
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
    return TRUE;
}

BOOL sNodeTree_create_decrement_operand_with_value(unsigned int left_node, unsigned int value)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDecrementOperand;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = value;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

BOOL compile_decrement_operand_with_value(unsigned int node, sCompileInfo* info)
{
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
            increment_operand_core(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            increment_operand_core(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            increment_operand_core(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            increment_operand_core(node, info, rnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, TRUE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            increment_operand_core(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            increment_operand_core(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, TRUE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            increment_operand_core(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            increment_operand_core(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            increment_operand_core(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCINT, TRUE);
            info->type = create_node_type_with_class_name("pointer");
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
            if(!increment_operand_core_for_field(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!increment_operand_core_for_field(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCINT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
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
            decrement_operand_core(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE);
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            decrement_operand_core(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE);
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            decrement_operand_core(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE);
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            decrement_operand_core(node, info, rnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, TRUE);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            decrement_operand_core(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE);
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            decrement_operand_core(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCSHORT, TRUE);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            decrement_operand_core(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE);
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            decrement_operand_core(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            decrement_operand_core(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCPOINTER, TRUE);
            info->type = create_node_type_with_class_name("pointer");
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
            if(!decrement_operand_core_for_field(node, info, rnode, OP_IADD, OP_ISUB, OP_LDCINT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if(type_identify_with_class_name(node_type, "uint")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if(type_identify_with_class_name(node_type, "byte")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_BADD, OP_BSUB, OP_LDCBYTE, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if(type_identify_with_class_name(node_type, "ubyte")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_UIADD, OP_UISUB, OP_LDCUINT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if(type_identify_with_class_name(node_type, "short")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_SADD, OP_SSUB, OP_LDCSHORT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if(type_identify_with_class_name(node_type, "ushort")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if(type_identify_with_class_name(node_type, "long")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_LADD, OP_LSUB, OP_LDCLONG, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if(type_identify_with_class_name(node_type, "ulong")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_ULADD, OP_ULSUB, OP_LDCULONG, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if(type_identify_with_class_name(node_type, "pointer")) {
            if(!decrement_operand_core_for_field(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCINT, TRUE)) {
                return FALSE;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else {
            parser_err_msg(info->pinfo, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
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

        case kNodeTypeNewOperator:
            puts("new operator");
            break;

        case kNodeTypeReturn:
            puts("return");
            break;

        case kNodeTypeLoadField:
            puts("load field");
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
    }

    return TRUE;
}

void arrange_stack(sCompileInfo* cinfo)
{
    if(cinfo->stack_num < 0) {
        parser_err_msg(cinfo->pinfo, "Unexpected error. Stack pointer is invalid");
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

