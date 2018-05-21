#include "common.h"

sNodeTree* gNodes;

static unsigned int gSizeNodes = 0;
static unsigned int gUsedNodes = 0;
static unsigned int gLabelNum = 0;

void init_nodes()
{
    const int node_size = 32;
    gLabelNum = 0;

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
        int j;
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
                    MFREE(gNodes[i].uValue.sString.mString);
                    for(j=0; j<gNodes[i].uValue.sString.mNumStringExpression; j++) {
                        sNodeBlock_free(gNodes[i].uValue.sString.mStringExpressions[j]);
                    }
                    break;

                case kNodeTypePath:
                    MFREE(gNodes[i].uValue.sString.mString);
                    for(j=0; j<gNodes[i].uValue.sString.mNumStringExpression; j++) {
                        sNodeBlock_free(gNodes[i].uValue.sString.mStringExpressions[j]);
                    }
                    break;

                case kNodeTypeBuffer:
                    MFREE(gNodes[i].uValue.sBuffer.mBuffer);
                    for(j=0; j<gNodes[i].uValue.sBuffer.mNumStringExpression; j++) {
                        sNodeBlock_free(gNodes[i].uValue.sBuffer.mStringExpressions[j]);
                    }
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
                    for(j=0; j<gNodes[i].uValue.sRegex.mNumStringExpression; j++) {
                        sNodeBlock_free(gNodes[i].uValue.sRegex.mStringExpressions[j]);
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

int get_var_size(sNodeType* var_type)
{
    int size = 0;
    if(var_type->mClass->mFlags & CLASS_FLAGS_INTERFACE) {
        size = 32;
    }
    else if(type_identify_with_class_name(var_type, "byte") || type_identify_with_class_name(var_type, "ubyte"))
    {
        size = 8;
    }
    else if(type_identify_with_class_name(var_type, "short") || type_identify_with_class_name(var_type, "ushort"))
    {
        size = 16;
    }
    else if(type_identify_with_class_name(var_type, "int") || type_identify_with_class_name(var_type, "uint"))
    {
        size = 32;
    }
    else if(type_identify_with_class_name(var_type, "long") || type_identify_with_class_name(var_type, "ulong"))
    {
        size = 64;
    }
    else if(type_identify_with_class_name(var_type, "float"))
    {
        size = 128;
    }
    else if(type_identify_with_class_name(var_type, "double"))
    {
        size = 256;
    }
    else if(type_identify_with_class_name(var_type, "bool"))
    {
        size = 1;
    }
    else if(type_identify_with_class_name(var_type, "char"))
    {
        size = 32;
    }
    else if(type_identify_with_class_name(var_type, "pointer"))
    {
        size = 1024;
    }
    else {
        size = 32;
    }

    return size;
}

#define LABEL_NAME_MAX 512

static void create_label_name(char* prefix, char* result, size_t result_size, int num)
{
    xstrncpy(result, prefix, result_size);

    int n = num;
    while(1) {
        if(n > 'z' - 'a') {
            xstrncat(result, "z", result_size);
            n -= 'z' - 'a';
        }
        else {
            char str[2];
            str[0] = n + 'a';
            str[1] = 0;
            xstrncat(result, str, result_size);
            break;
        }
    }
}

static void create_label_name2(char* prefix, char* result, size_t result_size, int num, int num2)
{
    xstrncpy(result, prefix, result_size);

    int n = num;
    while(1) {
        if(n > 'z' - 'a') {
            xstrncat(result, "z", result_size);
            n -= 'z' - 'a';
        }
        else {
            char str[2];
            str[0] = n + 'a';
            str[1] = 0;
            xstrncat(result, str, result_size);
            break;
        }
    }

    char buf[128];
    snprintf(buf, 128, "%da", num2);

    xstrncat(result, buf, result_size);
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

    switch(gNodes[node].mNodeType) {
        case kNodeTypeIf:
            {
            if(gNodes[node].uValue.sIf.mIfNodeBlock) {
                gNodes[result].uValue.sIf.mIfNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sIf.mIfNodeBlock);
            }
            int j;
            for(j=0; j<gNodes[node].uValue.sIf.mElifNum; j++) {
                sNodeBlock* node_block = gNodes[node].uValue.sIf.mElifNodeBlocks[j];
                if(node_block) {
                    gNodes[result].uValue.sIf.mElifNodeBlocks[j] = sNodeBlock_clone(node_block);
                }
            }
            if(gNodes[node].uValue.sIf.mElseNodeBlock) {
                gNodes[result].uValue.sIf.mElseNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sIf.mElseNodeBlock);
            }
            }
            break;

        case kNodeTypeWhile:
            if(gNodes[node].uValue.sWhile.mWhileNodeBlock) {
                gNodes[result].uValue.sWhile.mWhileNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sWhile.mWhileNodeBlock);
            }
            break;

        case kNodeTypeTry:
            if(gNodes[node].uValue.sTry.mTryNodeBlock) {
                gNodes[result].uValue.sTry.mTryNodeBlock= sNodeBlock_clone(gNodes[node].uValue.sTry.mTryNodeBlock);
            }
            if(gNodes[node].uValue.sTry.mCatchNodeBlock) {
                gNodes[result].uValue.sTry.mCatchNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sTry.mCatchNodeBlock);
            }
            break;

        case kNodeTypeFor:
            if(gNodes[node].uValue.sFor.mForNodeBlock) {
                gNodes[result].uValue.sFor.mForNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sFor.mForNodeBlock);
            }
            break;

        case kNodeTypeString:
            gNodes[result].uValue.sString.mString = MSTRDUP(gNodes[node].uValue.sString.mString);
            break;

        case kNodeTypePath:
            gNodes[result].uValue.sString.mString = MSTRDUP(gNodes[node].uValue.sString.mString);
            break;

        case kNodeTypeBuffer: {
            int len = gNodes[node].uValue.sBuffer.mLen;
            gNodes[result].uValue.sBuffer.mBuffer = MCALLOC(1, len);
            memcpy(gNodes[result].uValue.sBuffer.mBuffer, gNodes[node].uValue.sBuffer.mBuffer, len);
            }
            break;

        case kNodeTypeBlockObject:
            if(gNodes[node].uValue.sBlockObject.mBlockObjectCode) {
                gNodes[result].uValue.sBlockObject.mBlockObjectCode = sNodeBlock_clone(gNodes[node].uValue.sBlockObject.mBlockObjectCode);
            }
            break;

        case kNodeTypeNormalBlock:
            if(gNodes[node].uValue.mBlock) {
                gNodes[result].uValue.mBlock = sNodeBlock_clone(gNodes[node].uValue.mBlock);
            }
            break;

        case kNodeTypeRegex:
            gNodes[result].uValue.sRegex.mRegexStr = MSTRDUP(gNodes[node].uValue.sRegex.mRegexStr);
            break;

        default:
            break;
    }

    return result;
}

void append_class_name_to_constant_pool_and_code(sCompileInfo* info, sCLClass* klass)
{
    char class_name[CLASS_NAME_MAX];
    xstrncpy(class_name, CLASS_NAME(klass), CLASS_NAME_MAX);

    append_str_to_constant_pool_and_code(info->constant, info->code, class_name, info->no_output);
}

static void append_type_name_to_constant_pool_and_code(sCompileInfo* info, sNodeType* node_type)
{
    char type_name[OBJECT_TYPE_NAME_MAX];

    xstrncpy(type_name, "", OBJECT_TYPE_NAME_MAX);
    
    create_type_name_from_node_type(type_name, OBJECT_TYPE_NAME_MAX, node_type);

    append_str_to_constant_pool_and_code(info->constant, info->code, type_name, info->no_output);
}

static void append_method_name_and_params_to_constant_pool_and_code(sCompileInfo* info, sCLClass* klass, sCLMethod* method)
{
    int size_method_name_and_params = METHOD_NAME_MAX + PARAMS_MAX * CLASS_NAME_MAX + 256;
    char method_name_and_params[size_method_name_and_params];

    xstrncpy(method_name_and_params, METHOD_NAME_AND_PARAMS(klass, method), size_method_name_and_params);

    append_str_to_constant_pool_and_code(info->constant, info->code, method_name_and_params, info->no_output);
}

void compile_err_msg(sCompileInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    if(!info->pinfo->get_type_for_interpreter) {
        fprintf(stderr, "%s %d: %s\n", info->sname, info->sline, msg2);
    }
}

void arrange_stack(sCompileInfo* cinfo)
{
    if(cinfo->no_pop_next) {
        cinfo->no_pop_next = FALSE;
    }
    else if(cinfo->stack_num < 0) {
        compile_err_msg(cinfo, "Unexpected error. Stack pointer is invalid(stack number is %d)", cinfo->stack_num);
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

static void err_msg_for_method_not_found(sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL class_method, sCompileInfo* info)
{
    compile_err_msg(info, "%s.%s(%d prametors) is not found", CLASS_NAME(klass), method_name, num_params);
    int i;
    for(i=0; i<num_params; i++) {
        if(param_types[i] == NULL || param_types[i]->mClass == NULL) {
            compile_err_msg(info, "parametor#%d is NULL(unexpected parametor)", i);
        }
        else {
            compile_err_msg(info, "parametor#%d is %s", i, CLASS_NAME(param_types[i]->mClass));
        }
    }
}

unsigned int sNodeTree_create_operand(enum eOperand operand, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOperand;
    gNodes[node].uValue.mOperand = operand;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

static BOOL binary_operator(sNodeType* left_type, sNodeType* right_type, int byte_operand, int ubyte_operand, int short_operand, int ushort_operand, int int_operand, int uint_operand, int long_operand, int ulong_operand, int float_operand, int double_operand, int pointer_operand, int null_operand, int char_operand, int bool_operand, int regex_operand, char* op_string, sCompileInfo* info)
{
    if(!no_cast_types_for_binary_operator(left_type, right_type))
    {
        cast_right_type_to_left_type(left_type, &right_type, info);
    }

    if(!operand_posibility(left_type, right_type, op_string))
    {
        compile_err_msg(info, "Invalid type for operand(%s). The left type is %s. The right type is %s.", op_string,CLASS_NAME(left_type->mClass), CLASS_NAME(right_type->mClass));
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
    else if(type_identify_with_class_name(left_type, "regex") && regex_operand != -1) {
        append_opecode_to_code(info->code, regex_operand, info->no_output);
        info->stack_num--;

        info->type = create_node_type_with_class_name("bool");
    }
    else if(type_identify_with_class_name(left_type, "pointer") && pointer_operand != -1) {
        if(strcmp(op_string, "-") == 0) {
            if(type_identify_with_class_name(right_type, "pointer")) {
                append_opecode_to_code(info->code, OP_PPSUB, info->no_output);
                info->stack_num--;

                info->type = create_node_type_with_class_name("ulong");
            }
            else {
                sNodeType* ulong_type = create_node_type_with_class_name("ulong");
                cast_right_type_to_left_type(ulong_type, &right_type, info);

                if(!type_identify_with_class_name(right_type, "ulong")) {
                    compile_err_msg(info, "Invalid pointer operand type(%s)", CLASS_NAME(right_type->mClass));
                    info->err_num++;
                }
                else {
                    append_opecode_to_code(info->code, pointer_operand, info->no_output);
                    info->stack_num--;

                    info->type = create_node_type_with_class_name("pointer");
                }
            }
        }
        else if(strcmp(op_string, "==") == 0 || strcmp(op_string, "!=") == 0) {
            append_opecode_to_code(info->code, pointer_operand, info->no_output);
            info->stack_num--;

            info->type = create_node_type_with_class_name("pointer");
        }
        else {
            sNodeType* ulong_type = create_node_type_with_class_name("ulong");
            cast_right_type_to_left_type(ulong_type, &right_type, info);

            if(!type_identify_with_class_name(right_type, "ulong")) {
                compile_err_msg(info, "Invalid pointer operand type(%s)", CLASS_NAME(right_type->mClass));
                info->err_num++;
            }
            else {
                append_opecode_to_code(info->code, pointer_operand, info->no_output);
                info->stack_num--;
            }

            info->type = create_node_type_with_class_name("pointer");
        }
    }
    else {
        compile_err_msg(info, "%s.%s is not implemented", CLASS_NAME(left_type->mClass), op_string);
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
            if(!binary_operator(left_type, right_type, OP_BADD, OP_UBADD, OP_SADD, OP_USADD, OP_IADD, OP_UIADD, OP_LADD, OP_ULADD, OP_FADD, OP_DADD, OP_PADD, -1, OP_CADD, -1, -1, "+", info))
            {
                return FALSE;
            }
            break;

        case kOpSub: {
            if(!binary_operator(left_type, right_type, OP_BSUB, OP_UBSUB, OP_SSUB, OP_USSUB, OP_ISUB, OP_UISUB, OP_LSUB, OP_ULSUB, OP_FSUB, OP_DSUB, OP_PSUB, -1, OP_CSUB, -1, -1, "-", info))
            {
                return FALSE;
            }
            }
            break;
            
        case kOpMult:
            if(!binary_operator(left_type, right_type, OP_BMULT, OP_UBMULT, OP_SMULT, OP_USMULT, OP_IMULT, OP_UIMULT, OP_LMULT, OP_ULMULT, OP_FMULT, OP_DMULT, -1, -1, -1, -1, -1, "*", info))
            {
                return FALSE;
            }
            break;
            
        case kOpDiv:
            if(!binary_operator(left_type, right_type, OP_BDIV, OP_UBDIV, OP_SDIV, OP_USDIV, OP_IDIV, OP_UIDIV, OP_LDIV, OP_ULDIV, OP_FDIV, OP_DDIV, -1, -1, -1, -1, -1, "/", info))
            {
                return FALSE;
            }
            break;
            
        case kOpMod:
            if(!binary_operator(left_type, right_type, OP_BMOD, OP_UBMOD, OP_SMOD, OP_USMOD, OP_IMOD, OP_UIMOD, OP_LMOD, OP_ULMOD, -1, -1, -1, -1, -1, -1, -1, "%", info))
            {
                return FALSE;
            }
            break;
            
        case kOpLeftShift:
            if(!binary_operator(left_type, right_type, OP_BLSHIFT, OP_UBLSHIFT, OP_SLSHIFT, OP_USLSHIFT, OP_ILSHIFT, OP_UILSHIFT, OP_LLSHIFT, OP_ULLSHIFT, -1, -1, -1, -1, -1, -1, -1, "<<", info))
            {
                return FALSE;
            }
            break;
            
        case kOpRightShift:
            if(!binary_operator(left_type, right_type, OP_BRSHIFT, OP_UBRSHIFT, OP_SRSHIFT, OP_USRSHIFT, OP_IRSHIFT, OP_UIRSHIFT, OP_LRSHIFT, OP_ULRSHIFT, -1, -1, -1, -1, -1, -1, -1, ">>", info))
            {
                return FALSE;
            }
            break;
            
        case kOpComparisonEqual:
            if(!binary_operator(left_type, right_type, OP_BEQ, OP_UBEQ, OP_SEQ, OP_USEQ, OP_IEQ, OP_UIEQ, OP_LEQ, OP_ULEQ, OP_FEQ, OP_DEQ, OP_PEQ, OP_IEQ, OP_CEQ, OP_IEQ, OP_REGEQ, "==", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonNotEqual:
            if(!binary_operator(left_type, right_type, OP_BNOTEQ, OP_UBNOTEQ, OP_SNOTEQ, OP_USNOTEQ, OP_INOTEQ, OP_UINOTEQ, OP_LNOTEQ, OP_ULNOTEQ, OP_FNOTEQ, OP_DNOTEQ, OP_PNOTEQ, OP_INOTEQ, OP_CNOTEQ, OP_INOTEQ, OP_REGNOTEQ, "!=", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonGreaterEqual:
            if(!binary_operator(left_type, right_type, OP_BGTEQ, OP_UBGTEQ, OP_SGTEQ, OP_USGTEQ, OP_IGTEQ, OP_UIGTEQ, OP_LGTEQ, OP_ULGTEQ, OP_FGTEQ, OP_DGTEQ, OP_PGTEQ, -1, OP_CGTEQ, -1, -1, ">=", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonLesserEqual:
            if(!binary_operator(left_type, right_type, OP_BLEEQ, OP_UBLEEQ, OP_SLEEQ, OP_USLEEQ, OP_ILEEQ, OP_UILEEQ, OP_LLEEQ, OP_ULLEEQ, OP_FLEEQ, OP_DLEEQ, OP_PLEEQ, -1, OP_CLEEQ, -1, -1, "<=", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonGreater:
            if(!binary_operator(left_type, right_type, OP_BGT, OP_UBGT, OP_SGT, OP_USGT, OP_IGT, OP_UIGT, OP_LGT, OP_ULGT, OP_FGT, OP_DGT, OP_PGT, -1, OP_CGT, -1, -1, ">", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpComparisonLesser:
            if(!binary_operator(left_type, right_type, OP_BLE, OP_UBLE, OP_SLE, OP_USLE, OP_ILE, OP_UILE, OP_LLE, OP_ULLE, OP_FLE, OP_DLE, OP_PLE, -1, OP_CLE, -1, -1, "<", info))
            {
                return FALSE;
            }

            info->type = create_node_type_with_class_name("bool");
            break;
            
        case kOpAnd:
            if(!binary_operator(left_type, right_type, OP_BAND, OP_UBAND, OP_SAND, OP_USAND, OP_IAND, OP_UIAND, OP_LAND, OP_ULAND, -1, -1, -1, -1, -1, -1, -1, "&", info))
            {
                return FALSE;
            }
            break;
            
        case kOpXor:
            if(!binary_operator(left_type, right_type, OP_BXOR, OP_UBXOR, OP_SXOR, OP_USXOR, OP_IXOR, OP_UIXOR, OP_LXOR, OP_ULXOR, -1, -1, -1, -1, -1, -1, -1, "^", info))
            {
                return FALSE;
            }
            break;
            
        case kOpOr:
            if(!binary_operator(left_type, right_type, OP_BOR, OP_UBOR, OP_SOR, OP_USOR, OP_IOR, OP_UIOR, OP_LOR, OP_ULOR, -1, -1, -1, -1, -1, -1, -1, "|", info))
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
                compile_err_msg(info, "require bool type for operator !");
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

unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAndAnd;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_and_and(unsigned int node, sCompileInfo* info)
{
    int label_num = gLabelNum++;

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
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_DUPE, info->no_output);
    info->stack_num++;

    append_opecode_to_code(info->code, OP_RESET_ANDAND_OROR_VALUE, info->no_output);

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*4, info->no_output);
    info->stack_num--;

    append_opecode_to_code(info->code, OP_STORE_ANDAND_OROR_VALUE, info->no_output);

    int stack_num_before = info->stack_num;

    /// goto the end point ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the left expression is false, jump to the end of and and expression
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    char label_end_point[LABEL_NAME_MAX];
    create_label_name("label_and_endpoint", label_end_point, LABEL_NAME_MAX, label_num);

    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    /// right value ///
    append_opecode_to_code(info->code, OP_STORE_ANDAND_OROR_VALUE2, info->no_output);

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
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_RESTORE_ANDAND_OROR_VALUE2, info->no_output);
    append_int_value_to_code(info->code, -2, info->no_output);

    append_opecode_to_code(info->code, OP_ANDAND, info->no_output);
    info->stack_num--;

    append_opecode_to_code(info->code, OP_STORE_ANDAND_OROR_VALUE2, info->no_output);

    /// the end point ///
    info->stack_num = stack_num_before;

    *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    append_opecode_to_code(info->code, OP_GET_ANDAND_OROR_RESULT, info->no_output);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOrOr;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_or_or(unsigned int node, sCompileInfo* info)
{
    int label_num = gLabelNum++;

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
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_DUPE, info->no_output);
    info->stack_num++;

    append_opecode_to_code(info->code, OP_RESET_ANDAND_OROR_VALUE, info->no_output);

    append_opecode_to_code(info->code, OP_COND_NOT_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*4, info->no_output);
    info->stack_num--;

    append_opecode_to_code(info->code, OP_STORE_ANDAND_OROR_VALUE2, info->no_output);

    int stack_num_before = info->stack_num;

    /// goto the end point ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the left expression is true, jump to the end of || expression
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    char label_end_point[LABEL_NAME_MAX];
    create_label_name("label_or_endpoint", label_end_point, LABEL_NAME_MAX, label_num);

    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    /// compile right expression ///
    append_opecode_to_code(info->code, OP_STORE_ANDAND_OROR_VALUE, info->no_output);

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
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_RESTORE_ANDAND_OROR_VALUE, info->no_output);
    append_int_value_to_code(info->code, -2, info->no_output);

    append_opecode_to_code(info->code, OP_OROR, info->no_output);
    info->stack_num--;

    append_opecode_to_code(info->code, OP_STORE_ANDAND_OROR_VALUE, info->no_output);

    /// the end point ///
    info->stack_num = stack_num_before;
    
    *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    append_opecode_to_code(info->code, OP_GET_ANDAND_OROR_RESULT, info->no_output);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_byte_value(char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeByteValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_cbyte_value(char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCByteValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mByteValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("byte");

    return node;
}

static BOOL compile_cbyte_value(unsigned int node, sCompileInfo* info)
{
    char bvalue = gNodes[node].uValue.mByteValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("Byte");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "Byte", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCBYTE, info->no_output);
    append_int_value_to_code(info->code, gNodes[node].uValue.mByteValue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("byte");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(11)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("Byte");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_float_value(float value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFloatValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mFloatValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_float_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCFLOAT, info->no_output);
    append_float_value_to_code(info->code, gNodes[node].uValue.mFloatValue, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("float");

    return TRUE;
}

unsigned int sNodeTree_create_cfloat_value(float value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCFloatValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mFloatValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_cfloat_value(unsigned int node, sCompileInfo* info)
{
    float fvalue = gNodes[node].uValue.mFloatValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("Float");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "Float", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCFLOAT, info->no_output);
    append_float_value_to_code(info->code, fvalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("float");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(12)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("Float");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_double_value(double value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDoubleValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mDoubleValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_double_value(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCDOUBLE, info->no_output);
    append_double_value_to_code(info->code, gNodes[node].uValue.mDoubleValue, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("double");

    return TRUE;
}

unsigned int sNodeTree_create_cdouble_value(double value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCDoubleValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mDoubleValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_cdouble_value(unsigned int node, sCompileInfo* info)
{
    double dvalue = gNodes[node].uValue.mDoubleValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("Double");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "Double", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCDOUBLE, info->no_output);
    append_double_value_to_code(info->code, dvalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("double");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(13)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("Double");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_ubyte_value(unsigned char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUByteValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_cubyte_value(unsigned char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCUByteValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mUByteValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("ubyte");

    return node;
}

static BOOL compile_cubyte_value(unsigned int node, sCompileInfo* info)
{
    unsigned char ubvalue = gNodes[node].uValue.mUByteValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("UByte");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "UByte", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCUBYTE, info->no_output);
    append_double_value_to_code(info->code, ubvalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("ubyte");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(14)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("UByte");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_short_value(short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeShortValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_cshort_value(short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCShortValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mShortValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("short");

    return node;
}

static BOOL compile_cshort_value(unsigned int node, sCompileInfo* info)
{
    short svalue = gNodes[node].uValue.mShortValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("Short");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "UByte", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCSHORT, info->no_output);
    append_int_value_to_code(info->code, svalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("short");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(15)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("Short");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_ushort_value(unsigned short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUShortValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_cushort_value(unsigned short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCUShortValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mUShortValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("ushort");

    return node;
}

static BOOL compile_cushort_value(unsigned int node, sCompileInfo* info)
{
    unsigned short usvalue = gNodes[node].uValue.mUShortValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("UShort");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "UShort", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCUSHORT, info->no_output);
    append_int_value_to_code(info->code, usvalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("ushort");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(16)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("UShort");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_int_value(int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIntValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_cint_value(int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCIntValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mIntValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("int");

    return node;
}

static BOOL compile_cint_value(unsigned int node, sCompileInfo* info)
{
    int ivalue = gNodes[node].uValue.mIntValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("Integer");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "Integer", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCINT, info->no_output);
    append_int_value_to_code(info->code, ivalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("int");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(17)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("Integer");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_uint_value(unsigned int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUIntValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_cuint_value(unsigned int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCUIntValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mUIntValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("uint");

    return node;
}

static BOOL compile_cuint_value(unsigned int node, sCompileInfo* info)
{
    unsigned int uivalue = gNodes[node].uValue.mUIntValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("UInteger");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "UInteger", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCUINT, info->no_output);
    append_int_value_to_code(info->code, uivalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("uint");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(18)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("UInteger");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}


unsigned int sNodeTree_create_long_value(clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLongValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_clong_value(clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCLongValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mLongValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("long");

    return node;
}

static BOOL compile_clong_value(unsigned int node, sCompileInfo* info)
{
    long lvalue = gNodes[node].uValue.mLongValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("Long");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "Long", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCLONG, info->no_output);
    append_long_value_to_code(info->code, lvalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("long");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(19)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("Long");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_ulong_value(unsigned clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeULongValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_culong_value(unsigned clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCULongValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mULongValue = value;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    gNodes[node].mType = create_node_type_with_class_name("ulong");

    return node;
}

static BOOL compile_culong_value(unsigned int node, sCompileInfo* info)
{
    unsigned long ulvalue = gNodes[node].uValue.mULongValue;

    sNodeType* generics_types2 = NULL;

    sCLClass* klass = get_class("ULong");

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "ULong", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    int num_params = 1;
    sNodeType* param_types[PARAMS_MAX];

    char* method_name = "initialize";

    append_opecode_to_code(info->code, OP_LDCULONG, info->no_output);
    append_long_value_to_code(info->code, ulvalue, info->no_output);

    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("ulong");

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* right_method_generics_types = NULL;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index == -1) {
            compile_err_msg(info, "method not found(20)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        sNodeType* result_type2 = create_node_type_with_class_name("ULong");
        int size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = result_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_store_variable(char* var_name, sNodeType* node_type, int right, sCLClass* klass, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAssignVariable;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "undeclared variable %s(5)", gNodes[node].uValue.sAssignVariable.mVarName);
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
    }
    if(var->mType == NULL) {
        var->mType = right_type;
    }

    sNodeType* left_type = var->mType;
    if(gNodes[node].mType->mClass == NULL || left_type == NULL || right_type == NULL || left_type->mClass == NULL || right_type->mClass == NULL) 
    {
        compile_err_msg(info, "invalid type(1)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type2;
    solve_generics_for_variable(left_type, &left_type2, info->pinfo);

    if(cast_posibility(left_type2, right_type)) {
        cast_right_type_to_left_type(left_type2, &right_type, info);
    }

    if(!substitution_posibility(left_type2, right_type, NULL, NULL, NULL, NULL)) {
        compile_err_msg(info, "The different type between left type and right type(1). Left type is %s. Right type is %s.", CLASS_NAME(left_type2->mClass), CLASS_NAME(right_type->mClass));
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

unsigned int sNodeTree_create_load_variable(char* var_name, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadVariable;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "undeclared variable %s(6)", gNodes[node].uValue.mVarName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    gNodes[node].mType = var->mType;

    int var_index = get_variable_index(info->lv_table, gNodes[node].uValue.mVarName);

    if(var_index == -1 || var == NULL || var->mType == NULL) {
        compile_err_msg(info, "can't get type of %s", gNodes[node].uValue.mVarName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    MASSERT(var_index != -1);

    sNodeType* var_type = var->mType;

    append_opecode_to_code(info->code, OP_LOAD, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);
    int size = get_var_size(var_type);
    append_int_value_to_code(info->code, size, info->no_output);

    info->stack_num++;

    /// solve generics types ///
    sNodeType* result_type = var->mType;

    if(result_type == NULL || result_type->mClass == NULL) {
        compile_err_msg(info, "null type %s", gNodes[node].uValue.mVarName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* result_type2;
    solve_generics_for_variable(result_type, &result_type2, info->pinfo);

    info->type = result_type2;

    return TRUE;
}

unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED sNodeBlock* if_node_block, unsigned int* elif_expression_nodes, MANAGED sNodeBlock** elif_node_blocks, int elif_num, MANAGED sNodeBlock* else_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIf;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    int label_num = gLabelNum++;
    sNodeBlock* else_node_block = gNodes[node].uValue.sIf.mElseNodeBlock;

    char label_name_elif[LABEL_NAME_MAX];
    create_label_name2("label_elif", label_name_elif, LABEL_NAME_MAX, label_num, 1);

    char label_name_else[LABEL_NAME_MAX];
    create_label_name("label_else", label_name_else, LABEL_NAME_MAX, label_num);

    char label_end_point[LABEL_NAME_MAX];
    create_label_name("label_if_end", label_end_point, LABEL_NAME_MAX, label_num);

    /// compile expression ///
    sVarTable* lv_table = clone_var_table(info->lv_table);
    unsigned int expression_node = gNodes[node].uValue.sIf.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    if(!type_identify_with_class_name(info->type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*3, info->no_output);

    info->stack_num--;

    /// block of if expression ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block

    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    if(gNodes[node].uValue.sIf.mElifNum > 0) {
        append_str_to_constant_pool_and_code(info->constant, info->code, label_name_elif, info->no_output);
    }
    else {
        append_str_to_constant_pool_and_code(info->constant, info->code, label_name_else, info->no_output);
    }

    sNodeBlock* if_block = gNodes[node].uValue.sIf.mIfNodeBlock;
    if(!compile_block_with_result(if_block, info)) {
        return FALSE;
    }

    restore_var_table(info->lv_table, lv_table);

    append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
    info->stack_num--;

    sNodeType* if_result_type = info->type;

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    int end_points[ELIF_NUM_MAX+1];
    end_points[0] = info->code->mLen;
    int num_end_points = 1;

    append_int_value_to_code(info->code, 0, info->no_output);

    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    //// elif ///
    if(gNodes[node].uValue.sIf.mElifNum > 0) {
        *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

        append_opecode_to_code(info->code, OP_LABEL, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, label_name_elif, info->no_output);

        int j;
        for(j=0; j<gNodes[node].uValue.sIf.mElifNum; j++) {
            lv_table = clone_var_table(info->lv_table);

            /// compile expression ///
            unsigned int elif_expression_node = gNodes[node].uValue.sIf.mElifExpressionNodes[j];

            if(!compile(elif_expression_node, info)) {
                return FALSE;
            }

            if(!type_identify_with_class_name(info->type, "bool")) {
                compile_err_msg(info, "This conditional type is not bool");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
            append_int_value_to_code(info->code, sizeof(int)*5, info->no_output);

            info->stack_num--;

            append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
            info->stack_num++;

            append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
            info->stack_num--;

            /// block of if expression ///
            append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
            int goto_point = info->code->mLen;
            append_int_value_to_code(info->code, 0, info->no_output);

            char label_name[LABEL_NAME_MAX];
            create_label_name2("label_if_elif", label_name, LABEL_NAME_MAX, label_num, j);
            append_str_to_constant_pool_and_code(info->constant, info->code, label_name, info->no_output);

            sNodeBlock* elif_block = gNodes[node].uValue.sIf.mElifNodeBlocks[j];
            if(!compile_block_with_result(elif_block, info)) {
                return FALSE;
            }

            restore_var_table(info->lv_table, lv_table);

            append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
            info->stack_num--;

            sNodeType* elif_result_type = info->type;

            if(!type_identify(if_result_type, elif_result_type)) {
                if_result_type = create_node_type_with_class_name("Anonymous");
            }

            append_opecode_to_code(info->code, OP_GOTO, info->no_output);
            end_points[num_end_points] = info->code->mLen;
            num_end_points++;
            append_int_value_to_code(info->code, 0, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

            MASSERT(num_end_points <= ELIF_NUM_MAX+1);

            *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

            append_opecode_to_code(info->code, OP_LABEL, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, label_name, info->no_output);
        }
    }
    else {
        *(int*)(info->code->mCodes + goto_point) = info->code->mLen;
    }

    /// else block ///
    if(else_node_block) {
        append_opecode_to_code(info->code, OP_LABEL, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, label_name_else, info->no_output);

        if(!compile_block_with_result(else_node_block, info)) {
            return FALSE;
        }

        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
        info->stack_num--;

        sNodeType* else_result_type = info->type;

        if(!type_identify(if_result_type, else_result_type)) {
            if_result_type = create_node_type_with_class_name("Anonymous");
        }

        append_opecode_to_code(info->code, OP_GOTO, info->no_output);
        end_points[num_end_points] = info->code->mLen;
        num_end_points++;
        append_int_value_to_code(info->code, 0, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);
    }
    else {
        append_opecode_to_code(info->code, OP_LABEL, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, label_name_else, info->no_output);

        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
        info->stack_num++;

        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
        info->stack_num--;

        append_opecode_to_code(info->code, OP_GOTO, info->no_output);
        end_points[num_end_points] = info->code->mLen;
        num_end_points++;
        append_int_value_to_code(info->code, 0, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);
    }

    int i;
    for(i=0; i<num_end_points; i++) {
        *(int*)(info->code->mCodes + end_points[i]) = info->code->mLen;
    }

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

/*
if(!else_node_block) {
    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
    info->stack_num--;
}
*/

    if(info->pinfo->err_num == 0) { // for interpreter completion
        append_opecode_to_code(info->code, OP_POP_VALUE_FROM_GLOBAL, info->no_output);
        int size = get_var_size(if_result_type);

        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num++;

        info->type = if_result_type;
    }

    return TRUE;
}

unsigned int sNodeTree_when_expression(unsigned int expression_node, unsigned int value_nodes[WHEN_BLOCK_MAX][WHEN_BLOCK_MAX], int num_values[WHEN_BLOCK_MAX], sNodeBlock* when_blocks[WHEN_BLOCK_MAX], int num_when_block, sNodeBlock* else_block, sNodeType* when_types[WHEN_BLOCK_MAX], sNodeType* when_types2[WHEN_BLOCK_MAX], BOOL when_match[WHEN_BLOCK_MAX], sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWhen;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sWhen.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhen.mNumWhenBlock = num_when_block;
    gNodes[node].uValue.sWhen.mElseBlock = else_block;

    int i;
    for(i=0; i<num_when_block; i++) {
        gNodes[node].uValue.sWhen.mWhenBlocks[i] = when_blocks[i];

        gNodes[node].uValue.sWhen.mNumValues[i] = num_values[i];

        gNodes[node].uValue.sWhen.mWhenTypes[i] = when_types[i];
        gNodes[node].uValue.sWhen.mWhenTypes2[i] = when_types2[i];
        gNodes[node].uValue.sWhen.mMatch[i] = when_match[i];

        int j;
        for(j=0; j<num_values[i]; j++) {
            gNodes[node].uValue.sWhen.mValueNodes[i][j] = value_nodes[i][j];
        }
    }

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_when_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int expression_node = gNodes[node].uValue.sWhen.mExpressionNode;
    int num_when_block = gNodes[node].uValue.sWhen.mNumWhenBlock;
    sNodeBlock* else_block = gNodes[node].uValue.sWhen.mElseBlock;

    unsigned int value_nodes[WHEN_BLOCK_MAX][WHEN_BLOCK_MAX];

    int num_values[WHEN_BLOCK_MAX];

    sNodeBlock* when_blocks[WHEN_BLOCK_MAX];

    sNodeType* when_types[WHEN_BLOCK_MAX];
    sNodeType* when_types2[WHEN_BLOCK_MAX];
    BOOL when_match[WHEN_BLOCK_MAX];

    int i;
    for(i=0; i<num_when_block; i++) {
        num_values[i] = gNodes[node].uValue.sWhen.mNumValues[i];
        when_blocks[i] = gNodes[node].uValue.sWhen.mWhenBlocks[i];
        when_types[i] = gNodes[node].uValue.sWhen.mWhenTypes[i];
        when_types2[i] = gNodes[node].uValue.sWhen.mWhenTypes2[i];
        when_match[i] = gNodes[node].uValue.sWhen.mMatch[i];

        int j;
        for(j=0; j<num_values[i]; j++) {
            value_nodes[i][j] = gNodes[node].uValue.sWhen.mValueNodes[i][j];
        }
    }

    char label_end_point[LABEL_NAME_MAX];
    create_label_name("label_when_end", label_end_point, LABEL_NAME_MAX, gLabelNum++);

    sNodeType* when_result_type = NULL;

    int end_points[WHEN_BLOCK_MAX][WHEN_BLOCK_MAX];

    for(i=0; i<num_when_block; i++) {
        if(when_types[i] || when_types2[i]) {
            sNodeType* node_type;

            if(when_types[i]) {
                node_type = when_types[i];
            }
            else {
                node_type = when_types2[i];
            }

            /// left value ///
            if(!compile(expression_node, info)) {
                return FALSE;
            }

            append_opecode_to_code(info->code, OP_CLASSNAME, info->no_output);

            info->type = create_node_type_with_class_name("String");

            info->stack_num--;
            info->stack_num++;

            char* str = CLASS_NAME(node_type->mClass);
            int num_string_expression = 0;

            append_opecode_to_code(info->code, OP_CREATE_STRING, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, str, info->no_output);
            append_int_value_to_code(info->code, num_string_expression, info->no_output);

            info->stack_num++;

            info->type = create_node_type_with_class_name("String");

            /// String.equals ///
            sCLClass* string_class = get_class("String");
            char* method_name = "equals";

            sNodeType* param_types[PARAMS_MAX];
            int num_params = 1;

            param_types[0] = create_node_type_with_class_name("String");

            sNodeType* result_type = NULL;
            sNodeType* result_method_generics_types = NULL;
            int method_index = search_for_method(string_class, "equals", param_types, num_params, FALSE, string_class->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

            if(method_index == -1) {
                compile_err_msg(info, "method not found(4)");
                info->err_num++;

                err_msg_for_method_not_found(string_class, method_name, param_types, num_params, FALSE, info);

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);

            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

            append_class_name_to_constant_pool_and_code(info, string_class);
            append_int_value_to_code(info->code, method_index, info->no_output);

            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num-=2;
            info->stack_num++;

            info->type = result_type;

            //// go ///
            sNodeType* var_type = NULL;
            if(when_types[i]) {
                if(gNodes[expression_node].mNodeType == kNodeTypeLoadVariable) {
                    sVar* var = get_variable_from_table(info->lv_table, gNodes[expression_node].uValue.mVarName);

                    var_type = var->mType;

                    var->mType = node_type;
                }
            }

            if(when_types[i]) {
                append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
            }
            else {
                append_opecode_to_code(info->code, OP_COND_NOT_JUMP, info->no_output);
            }

            append_int_value_to_code(info->code, sizeof(int)*3, info->no_output);

            info->stack_num--;

            /// block of when expression ///
            append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of the block

            int goto_point = info->code->mLen;
            append_int_value_to_code(info->code, 0, info->no_output);

            int label_num = gLabelNum++;

            char label_name_next_when[LABEL_NAME_MAX];
            create_label_name2("label_name_next_when", label_name_next_when, LABEL_NAME_MAX, label_num, 1);

            append_str_to_constant_pool_and_code(info->constant, info->code, label_name_next_when, info->no_output);

            if(!compile_block_with_result(when_blocks[i], info)) {
                return FALSE;
            }

            append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
            info->stack_num--;

            if(when_result_type && type_identify_with_class_name(when_result_type, "Anonymous")) {
            }
            else if(when_result_type && !type_identify(info->type, when_result_type)) {
                when_result_type = create_node_type_with_class_name("Anonymous");
            }
            else {
                when_result_type = info->type;
            }

            append_opecode_to_code(info->code, OP_GOTO, info->no_output);
            end_points[i][0] = info->code->mLen;

            append_int_value_to_code(info->code, 0, info->no_output);

            append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

            /// next when value ///
            *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

            append_opecode_to_code(info->code, OP_LABEL, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, label_name_next_when, info->no_output);

            /// restore var type ///
            if(var_type) {
                sVar* var = get_variable_from_table(info->lv_table, gNodes[expression_node].uValue.mVarName);

                var->mType = var_type;
            }
        }
        /// when match ///
        else if(when_match[i]) {
            int j;
            for(j=0; j<num_values[i]; j++) {
                /// left value ///
                if(!compile(expression_node, info)) {
                    return FALSE;
                }

                sNodeType* left_type = info->type;
                sCLClass* klass = left_type->mClass;

                if(!type_identify_with_class_name(left_type, "String")) {
                    compile_err_msg(info, "Require String value for when match statment");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

                /// right value ///
                if(!compile(value_nodes[i][j], info)) {
                    return FALSE;
                }

                sNodeType* right_type = info->type;

                if(!type_identify_with_class_name(right_type, "regex")) {
                    compile_err_msg(info, "When match value type should be regex.");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                sNodeType* param_types[PARAMS_MAX];
                int num_params = 1;

                char* method_name = "match";
                sNodeType* result_type = NULL;

                param_types[0] = right_type;

                sNodeType* result_method_generics_types = NULL;
                int method_index2 = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

                sCLMethod* method = klass->mMethods + method_index2;

                append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                append_int_value_to_code(info->code, info->sline, info->no_output);


                append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

                append_class_name_to_constant_pool_and_code(info, klass);
                append_int_value_to_code(info->code, method_index2, info->no_output);

                int size = get_var_size(result_type);
                append_int_value_to_code(info->code, size, info->no_output);

                info->stack_num -= num_params + 1;
                info->stack_num++;

                info->type = result_type;

                append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
                append_int_value_to_code(info->code, sizeof(int)*3, info->no_output);

                info->stack_num--;

                /// block of when expression ///
                append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of the block

                int goto_point = info->code->mLen;
                append_int_value_to_code(info->code, 0, info->no_output);

                int label_num = gLabelNum++;

                char label_name_next_when[LABEL_NAME_MAX];
                create_label_name2("label_name_next_when", label_name_next_when, LABEL_NAME_MAX, label_num, 1);

                append_str_to_constant_pool_and_code(info->constant, info->code, label_name_next_when, info->no_output);

                if(!compile_block_with_result(when_blocks[i], info)) {
                    return FALSE;
                }

                append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
                info->stack_num--;

                if(when_result_type && type_identify_with_class_name(when_result_type, "Anonymous")) {
                }
                else if(when_result_type && !type_identify(info->type, when_result_type)) {
                    when_result_type = create_node_type_with_class_name("Anonymous");
                }
                else {
                    when_result_type = info->type;
                }

                append_opecode_to_code(info->code, OP_GOTO, info->no_output);
                end_points[i][j] = info->code->mLen;

                append_int_value_to_code(info->code, 0, info->no_output);

                append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

                /// next when value ///
                *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

                append_opecode_to_code(info->code, OP_LABEL, info->no_output);
                append_str_to_constant_pool_and_code(info->constant, info->code, label_name_next_when, info->no_output);
            }
        }
        else {
            int j;
            for(j=0; j<num_values[i]; j++) {
                /// left value ///
                if(!compile(expression_node, info)) {
                    return FALSE;
                }

                sNodeType* left_type = info->type;
                sCLClass* klass = left_type->mClass;

                if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                    /// right value ///
                    if(!compile(value_nodes[i][j], info)) {
                        return FALSE;
                    }

                    sNodeType* right_type = info->type;

                    if(!type_identify(left_type, right_type)) {
                        compile_err_msg(info, "When value type and when type is the different.");
                        info->err_num++;

                        info->type = create_node_type_with_class_name("int"); // dummy

                        return TRUE;
                    }

                    if(!binary_operator(left_type, right_type, OP_BEQ, OP_UBEQ, OP_SEQ, OP_USEQ, OP_IEQ, OP_UIEQ, OP_LEQ, OP_ULEQ, OP_FEQ, OP_DEQ, OP_PEQ, OP_IEQ, OP_CEQ, OP_IEQ, OP_REGEQ, "==", info))
                    {
                        return FALSE;
                    }

                    info->type = create_node_type_with_class_name("bool");
                }
                else {
                    /// check interface ///
                    sCLClass* iequalable = get_class("IEqualable");
                    if(!check_implemented_methods_for_interface(iequalable, klass)) {
                        compile_err_msg(info, "Require IEqualable implemented for when value classs(%s)", CLASS_NAME(klass));
                        info->err_num++;
                    }

                    if(klass->mFlags & CLASS_FLAGS_DYNAMIC_CLASS) {
                        compile_err_msg(info, "Dynamic class type can't be when argument");
                        info->err_num++;

                        info->type = create_node_type_with_class_name("int"); // dummy

                        return TRUE;
                    }
                    else if(class_identify_with_class_name(klass, "Anonymous")) {
                        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

                        /// right value ///
                        if(!compile(value_nodes[i][j], info)) {
                            return FALSE;
                        }

                        sNodeType* right_type = info->type;

                        sNodeType* param_types[PARAMS_MAX];
                        int num_params = 1;

                        char* method_name = "equals";

                        param_types[0] = right_type;

                        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
                            int num_real_params = num_params + 1;

                            int size_method_name_and_params = METHOD_NAME_MAX + PARAMS_MAX * CLASS_NAME_MAX + 256;
                            char method_name_and_params[size_method_name_and_params];
                            create_method_name_and_params(method_name_and_params, size_method_name_and_params, klass, method_name, param_types, num_params);

                            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                            append_int_value_to_code(info->code, info->sline, info->no_output);

                            append_opecode_to_code(info->code, OP_INVOKE_VIRTUAL_METHOD, info->no_output);
                            append_int_value_to_code(info->code, num_real_params, info->no_output);
                            append_str_to_constant_pool_and_code(info->constant, info->code, method_name_and_params, info->no_output);

                            sNodeType* result_type = create_node_type_with_class_name("bool");
                            int size = get_var_size(result_type);
                            append_int_value_to_code(info->code, size, info->no_output);

                            info->stack_num -= num_params + 1;
                            info->stack_num++;

                            info->type = result_type;
                        }
                    }
                    else if(klass->mFlags & CLASS_FLAGS_INTERFACE)
                    {
                        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

                        /// right value ///
                        if(!compile(value_nodes[i][j], info)) {
                            return FALSE;
                        }

                        sNodeType* right_type = info->type;

                        if(!type_identify(left_type, right_type)) {
                            compile_err_msg(info, "When value type and when type is the different.");
                            info->err_num++;

                            info->type = create_node_type_with_class_name("int"); // dummy

                            return TRUE;
                        }

                        sNodeType* param_types[PARAMS_MAX];
                        int num_params = 1;

                        char* method_name = "equals";

                        param_types[0] = right_type;

                        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
                            int num_real_params = num_params + 1;

                            int size_method_name_and_params = METHOD_NAME_MAX + PARAMS_MAX * CLASS_NAME_MAX + 256;
                            char method_name_and_params[size_method_name_and_params];
                            create_method_name_and_params(method_name_and_params, size_method_name_and_params, klass, method_name, param_types, num_params);

                            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                            append_int_value_to_code(info->code, info->sline, info->no_output);


                            append_opecode_to_code(info->code, OP_INVOKE_VIRTUAL_METHOD, info->no_output);
                            append_int_value_to_code(info->code, num_real_params, info->no_output);
                            append_str_to_constant_pool_and_code(info->constant, info->code, method_name_and_params, info->no_output);

                            sNodeType* result_type = create_node_type_with_class_name("bool");
                            int size = get_var_size(result_type);
                            append_int_value_to_code(info->code, size, info->no_output);

                            info->stack_num -= num_params + 1;
                            info->stack_num++;

                            info->type = result_type;
                        }
                    }
                    else {
                        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

                        /// right value ///
                        if(!compile(value_nodes[i][j], info)) {
                            return FALSE;
                        }

                        sNodeType* right_type = info->type;

                        if(!type_identify(left_type, right_type)) {
                            compile_err_msg(info, "When value type and when type is the different.");
                            info->err_num++;

                            info->type = create_node_type_with_class_name("int"); // dummy

                            return TRUE;
                        }

                        sNodeType* param_types[PARAMS_MAX];
                        int num_params = 1;

                        char* method_name = "equals";
                        sNodeType* result_type = NULL;

                        param_types[0] = right_type;

                        sNodeType* result_method_generics_types = NULL;
                        int method_index2 = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

                        sCLMethod* method = klass->mMethods + method_index2;

                        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                        append_int_value_to_code(info->code, info->sline, info->no_output);


                        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

                        append_class_name_to_constant_pool_and_code(info, klass);
                        append_int_value_to_code(info->code, method_index2, info->no_output);

                        int size = get_var_size(result_type);
                        append_int_value_to_code(info->code, size, info->no_output);

                        info->stack_num -= num_params + 1;
                        info->stack_num++;

                        info->type = result_type;
                    }
                }

                append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
                append_int_value_to_code(info->code, sizeof(int)*3, info->no_output);

                info->stack_num--;

                /// block of when expression ///
                append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of the block

                int goto_point = info->code->mLen;
                append_int_value_to_code(info->code, 0, info->no_output);

                int label_num = gLabelNum++;

                char label_name_next_when[LABEL_NAME_MAX];
                create_label_name2("label_name_next_when", label_name_next_when, LABEL_NAME_MAX, label_num, 1);

                append_str_to_constant_pool_and_code(info->constant, info->code, label_name_next_when, info->no_output);

                if(!compile_block_with_result(when_blocks[i], info)) {
                    return FALSE;
                }

                append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
                info->stack_num--;

                if(when_result_type && type_identify_with_class_name(when_result_type, "Anonymous")) {
                }
                else if(when_result_type && !type_identify(info->type, when_result_type)) {
                    when_result_type = create_node_type_with_class_name("Anonymous");
                }
                else {
                    when_result_type = info->type;
                }

                append_opecode_to_code(info->code, OP_GOTO, info->no_output);
                end_points[i][j] = info->code->mLen;

                append_int_value_to_code(info->code, 0, info->no_output);

                append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

                /// next when value ///
                *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

                append_opecode_to_code(info->code, OP_LABEL, info->no_output);
                append_str_to_constant_pool_and_code(info->constant, info->code, label_name_next_when, info->no_output);
            }
        }
    }

    if(else_block) {
        if(!compile_block_with_result(else_block, info)) {
            return FALSE;
        }

        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
        info->stack_num--;

        if(when_result_type && type_identify_with_class_name(when_result_type, "Anonymous")) {
        }
        else if(when_result_type && !type_identify(info->type, when_result_type)) {
            when_result_type = create_node_type_with_class_name("Anonymous");
        }
        else {
            when_result_type = info->type;
        }
    }
    else {
        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
        info->stack_num++;

        append_opecode_to_code(info->code, OP_STORE_VALUE_TO_GLOBAL, info->no_output);
        info->stack_num--;
    }

    for(i=0; i<num_when_block; i++) {
        int j;
        for(j=0; j<num_values[i]; j++) {
            *(int*)(info->code->mCodes + end_points[i][j]) = info->code->mLen;
        }
    }

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    if(info->pinfo->err_num == 0) { // for interpreter completion
        append_opecode_to_code(info->code, OP_POP_VALUE_FROM_GLOBAL, info->no_output);

        if(when_result_type == NULL) {
            compile_err_msg(info, "When result type is NULL");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        int size = get_var_size(when_result_type);

        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num++;

        info->type = when_result_type;
    }

    return TRUE;
}

unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED sNodeBlock* while_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWhile;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    int label_num = gLabelNum++;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    int start_point = info->code->mLen;

    char start_point_label_name[LABEL_NAME_MAX];
    create_label_name("while_start_point", start_point_label_name, LABEL_NAME_MAX, label_num);

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, start_point_label_name, info->no_output);

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    if(!type_identify_with_class_name(info->type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*3, info->no_output);
    info->stack_num--;

    /// block of while expression ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
    int end_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    char label_end_point[LABEL_NAME_MAX];
    create_label_name("label_while", label_end_point, LABEL_NAME_MAX, label_num);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    char* break_point_label_name_before = info->break_point_label_name;
    info->break_point_label_name = label_end_point;

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
    info->break_point_label_name = break_point_label_name_before;

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    append_int_value_to_code(info->code, start_point, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, start_point_label_name, info->no_output);

    *(int*)(info->code->mCodes + end_point) = info->code->mLen;

    int i;
    for(i=0; i<num_break_points; i++) {
        *(int*)(info->code->mCodes + break_points[i]) = info->code->mLen;
    }

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    if(info->pinfo->err_num == 0) { // for interpreter completion
        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
        info->stack_num++;

        info->type = create_node_type_with_class_name("Null");
    }

    return TRUE;
}

unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED sNodeBlock* for_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFor;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    int label_num = gLabelNum++;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sFor.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    arrange_stack(info);

    /// compile expression ///
    unsigned int expression_node2 = gNodes[node].uValue.sFor.mExpressionNode2;

    int start_point = info->code->mLen;
    char start_point_label_name[LABEL_NAME_MAX];
    create_label_name("for_start_point", start_point_label_name, LABEL_NAME_MAX, label_num);

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, start_point_label_name, info->no_output);
    if(!compile(expression_node2, info)) {
        return FALSE;
    }

    if(!type_identify_with_class_name(info->type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_COND_JUMP, info->no_output);
    append_int_value_to_code(info->code, sizeof(int)*3, info->no_output);
    info->stack_num--;

    /// block of for expression ///
    append_opecode_to_code(info->code, OP_GOTO, info->no_output); // if the conditional expression is false, jump to the end of if block
    int end_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    char label_end_point[LABEL_NAME_MAX];
    create_label_name("label_for_end", label_end_point, LABEL_NAME_MAX, label_num);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    char* break_point_label_name_before = info->break_point_label_name;
    info->break_point_label_name = label_end_point;

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

    sNodeType* expresson_type_in_block = info->type;        // for interpreter completion

    info->num_break_points = num_break_points_before;
    info->break_points = break_points_before;
    info->break_point_label_name = break_point_label_name_before;

    /// expression 3 ///
    unsigned int expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;

    if(!compile(expression_node3, info)) {
        return FALSE;
    }

    arrange_stack(info);

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    append_int_value_to_code(info->code, start_point, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, start_point_label_name, info->no_output);
    *(int*)(info->code->mCodes + end_point) = info->code->mLen;

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_end_point, info->no_output);

    int i;
    for(i=0; i<num_break_points; i++) {
        *(int*)(info->code->mCodes + break_points[i]) = info->code->mLen;
    }

    if(info->pinfo->err_num == 0) { // for interpreter completion
        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
        info->stack_num++;
        info->type = create_node_type_with_class_name("Null");
    }
    else {
        info->type = expresson_type_in_block;   // for interpreter completion 
    }

    return TRUE;
}

unsigned int sNodeTree_break_expression(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBreak;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_break_expression(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    if(info->num_break_points == NULL) {
        compile_err_msg(info, "call break in the out of loop");
        return FALSE;
    }
    info->break_points[*info->num_break_points] = info->code->mLen;
    (*info->num_break_points)++;

    if(*info->num_break_points >= BREAK_NUM_MAX) {
        compile_err_msg(info, "overflow break number");
        return FALSE;
    }

    append_int_value_to_code(info->code, 0, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, info->break_point_label_name, info->no_output);

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_true_expression(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTrue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_false_expression(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFalse;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_null_expression(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNull;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_null_expression(unsigned int node, sCompileInfo* info)
{
    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_wildcard_expression(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWildCard;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_wildcard_expression(unsigned int node, sCompileInfo* info)
{
    sCLClass* klass = get_class("WildCard");

    MASSERT(klass != NULL);

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant, info->code, "WildCard", info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    info->type = create_node_type_with_class_name("WildCard");
    
    return TRUE;
}

unsigned int sNodeTree_create_class_method_call(sNodeType* klass, char* method_name, unsigned int* params, int num_params, sParserInfo* info)
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

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static sNodeType* get_generics_type_of_inner_class(sParserInfo* pinfo)
{
    sNodeType* result = NULL;
    if(pinfo->generics_info.mNumParams != 0) {
        sGenericsParamInfo* generics_param = &pinfo->generics_info;

        result = alloc_node_type();
        result->mNumGenericsTypes = generics_param->mNumParams;

        int i;
        for(i=0;i<generics_param->mNumParams; i++) {
            result->mGenericsTypes[i] = create_node_type_with_class_pointer(generics_param->mInterface[i]);
        }
    }

    return result;
}

static sNodeType* get_methocs_generics_type(sParserInfo* info)
{
    sNodeType* result = NULL;
    if(info->method_generics_info.mNumParams != 0) {
        sGenericsParamInfo* generics_param = &info->method_generics_info;

        result = alloc_node_type();
        result->mNumGenericsTypes = generics_param->mNumParams;

        int i;
        for(i=0;i<generics_param->mNumParams; i++) {
            result->mGenericsTypes[i] = create_node_type_with_class_pointer(generics_param->mInterface[i]);
        }
    }

    return result;
}

/// メソッドのデフォルト引数 ///
BOOL compile_params_method_default_value(sCLClass* klass, char* method_name, int* num_params, unsigned int params[PARAMS_MAX], sNodeType* param_types[PARAMS_MAX], sNodeType* generics_types, sCompileInfo* info, int size_method_indexes, int method_indexes[], int num_methods)
{
    int i;
    for(i=0; i<num_methods; i++) {
        sCLMethod* method = klass->mMethods + method_indexes[i];

        if(method->mNumParams > *num_params) {
            int j;
            for(j=0; j<*num_params; j++) {
                sNodeType* param;
                sNodeType* solved_param;

                param = create_node_type_from_cl_type(method->mParams[j].mType, klass);

                if(!solve_generics_types_for_node_type(param, ALLOC &solved_param, generics_types, TRUE, FALSE)) 
                {
                    return FALSE;
                }

                if(!substitution_posibility(solved_param, param_types[j], NULL, NULL, NULL, NULL))
                {
                    break;
                }
            }

            /// 対象のメソッドが見つかった（全部のsubstitution_posibilityが通っている)
            if(j == *num_params) {
                int k;
                for(k=*num_params; k < method->mNumParams; k++) {
                    sCLParam* param = method->mParams + k;

                    char* source = CONS_str(&klass->mConst, param->mDefaultValueOffset);

                    if(source[0] != '\0') {
                        sParserInfo info2;

                        info2.p = source;
                        info2.source = source;

                        info2.sname = info->pinfo->sname;
                        info2.sline = info->pinfo->sline;
                        info2.err_num = info->pinfo->err_num;
                        info2.lv_table = NULL;
                        info2.parse_phase = info->pinfo->parse_phase;
                        info2.klass = info->pinfo->klass;
                        info2.generics_info = info->pinfo->generics_info;
                        info2.method_generics_info = info->pinfo->method_generics_info;
                        info2.cinfo = info;
                        info2.included_source = FALSE;
                        info2.get_type_for_interpreter = info->pinfo->get_type_for_interpreter;
                        info2.next_command_is_to_bool = FALSE;
                        info2.exist_block_object_err = info->pinfo->exist_block_object_err;

                        unsigned int node = 0;
                        if(!expression(&node, &info2)) {
                            return FALSE;
                        }

                        if(!compile(node, info)) {
                            return FALSE;
                        }

                        param_types[k] = info->type;

                        (*num_params)++;
                    }
                }
                break;
            }
        }
    }

    return TRUE;
}

static BOOL compile_params(sCLClass* klass, char* method_name, int* num_params, unsigned int params[PARAMS_MAX], sNodeType* param_types[PARAMS_MAX], sNodeType* generics_types, sCompileInfo* info, BOOL lazy_lambda_compile, BOOL* exist_lazy_lamda_compile, BOOL class_method)
{
    /// preparing for argument boxing ///
    int size_method_indexes = 128;
    int method_indexes[size_method_indexes];
    int num_methods = 0;
    if(!search_for_methods_from_method_name(method_indexes, size_method_indexes, &num_methods, klass, method_name, klass->mNumMethods-1, class_method))
    {
        compile_err_msg(info, "overflow number of the same name methods");
        return FALSE;
    }

    int i;
    for(i=0; i<*num_params; i++) {
        int node2 = params[i];

        enum eNodeType node2_type = gNodes[node2].mNodeType;

        /// If the last argument is a block, do lazy lambda compiling ///
        if(lazy_lambda_compile && i == *num_params-1 && node2_type == kNodeTypeBlockObject) {
            *exist_lazy_lamda_compile = TRUE;
        }
        /// The other is compiling normaly ///
        else {
            if(!compile(node2, info)) {
                return FALSE;
            }

            param_types[i] = info->type;

            /// 引数をboxingすればメソッドが見つかるならboxingしないといけない ///
            int j;
            for(j=0; j<num_methods; j++) {
                sCLMethod* method = klass->mMethods + method_indexes[j];

                if(*num_params == method->mNumParams 
                    && i < method->mNumParams) 
                {
                    sNodeType* param;
                    sNodeType* solved_param;

                    param = create_node_type_from_cl_type(method->mParams[i].mType, klass);

                    if(!solve_generics_types_for_node_type(param, ALLOC &solved_param, generics_types, TRUE, FALSE)) 
                    {
                        return FALSE;
                    }

                    /// メソッド側の引数の型がインターフェースならboxingする。
                    if(solved_param->mClass->mFlags & CLASS_FLAGS_INTERFACE) {
                        boxing_to_lapper_class(&param_types[i], info);
                    }
                    /// メソッド側の引数がユーザークラスで引数がプリミティブ型ならboxingする。
                    else {
                        if(boxing_posibility(solved_param, param_types[i])) {
                            cast_right_type_to_left_type(solved_param, &param_types[i], info);
                        }

                        /// Nullを代入しているなら戻り値の引数の型はメソッド側の型にする。Null型ではメソッドサーチが通らないため
                        if(substitution_posibility_with_class_name(solved_param, "Null")) {
                            if(type_identify_with_class_name(param_types[i], "Null")) {
                                param_types[i] = solved_param;
                            }
                        }
                    }
                }
            }

            /// 引数をunboxingすればメソッドが見つかるならunboxingしないといけない ///
            for(j=0; j<num_methods; j++) {
                sCLMethod* method = klass->mMethods + method_indexes[j];

                if(*num_params == method->mNumParams 
                    && i < method->mNumParams) 
                {
                    sNodeType* param;
                    sNodeType* solved_param;

                    param = create_node_type_from_cl_type(method->mParams[i].mType, klass);

                    if(!solve_generics_types_for_node_type(param, ALLOC &solved_param, generics_types, TRUE, FALSE)) 
                    {
                        return FALSE;
                    }

                    if(unboxing_posibility(solved_param, param_types[i])) {
                        cast_right_type_to_left_type(solved_param, &param_types[i], info);
                    }
                    else if(cast_posibility(solved_param, param_types[i])) {
                        cast_right_type_to_left_type(solved_param, &param_types[i], info);
                    }
                }
            }
        }
    }

    /// method default value ///
    if(!*exist_lazy_lamda_compile) {
        if(!compile_params_method_default_value(klass, method_name, num_params, params, param_types, generics_types, info, size_method_indexes, method_indexes, num_methods))
        {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL compile_class_method_call(unsigned int node, sCompileInfo* info)
{
    sNodeType* param_types[PARAMS_MAX];

    sNodeType* klass_type = gNodes[node].uValue.sClassMethodCall.mClass;
    sCLClass* klass = klass_type->mClass;
    int num_params = gNodes[node].uValue.sClassMethodCall.mNumParams;
    char method_name[METHOD_NAME_MAX];
    xstrncpy(method_name, gNodes[node].uValue.sClassMethodCall.mMethodName, METHOD_NAME_MAX);

    sNodeType* generics_types;
    if(info->pinfo->klass && klass == info->pinfo->klass) {
        generics_types = get_generics_type_of_inner_class(info->pinfo);
    }
    else {
        generics_types = klass_type;
    }

    sNodeType* right_method_generics_types = get_methocs_generics_type(info->pinfo);

    info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

    unsigned int params[PARAMS_MAX];
    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sClassMethodCall.mParams[i];
    }

    /// compile params ///
    BOOL exist_lazy_lamda_compile = FALSE;
    if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types, info, FALSE, &exist_lazy_lamda_compile, TRUE))
    {
        return FALSE;
    }

    sNodeType* result_type;
    sNodeType* result_method_generics_types = NULL;
    int method_index = search_for_method(klass, method_name, param_types, num_params, TRUE, klass->mNumMethods-1, generics_types, NULL, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

    if(method_index != -1) {
        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);

            /// generate code ////
            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code, method_index, info->no_output);

            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num-=num_params;
            info->stack_num++;

            info->type = result_type;
        }
    }
    else {
        if(klass->mFlags & CLASS_FLAGS_DYNAMIC_CLASS) {
            int num_method_chains = 0;
            int max_method_chains = gNodes[node].mMaxMethodChains;

/*
            /// compile params ///
            info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

            int i;
            for(i=0; i<num_params; i++) {
                int node2 = gNodes[node].uValue.sClassMethodCall.mParams[i];
                if(!compile(node2, info)) {
                    return FALSE;
                }

                /// boxing if the class is primitive ///
                if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                    boxing_to_lapper_class(&info->type, info);
                }

                param_types[i] = info->type;
            }
*/

            if(!info->pinfo->exist_block_object_err) { // for interpreter completion
                /// generate code ////
                if(klass->mCallingClassMethodIndex == -1) {
                    compile_err_msg(info, "require calllingClasMethod class method for dynamic class");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }

                sCLMethod* method = klass->mMethods + klass->mCallingClassMethodIndex;

                if(num_params >= ARRAY_VALUE_ELEMENT_MAX) {
                    compile_err_msg(info, "overflow parametor number");
                    return FALSE;
                }

                append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                append_int_value_to_code(info->code, info->sline, info->no_output);


                append_opecode_to_code(info->code, OP_INVOKE_DYNAMIC_METHOD, info->no_output);
                append_class_name_to_constant_pool_and_code(info, klass);
                append_str_to_constant_pool_and_code(info->constant, info->code, method_name, info->no_output);
                append_int_value_to_code(info->code, num_params, info->no_output);
                append_int_value_to_code(info->code, 1, info->no_output);
                append_int_value_to_code(info->code, num_method_chains, info->no_output);
                append_int_value_to_code(info->code, max_method_chains, info->no_output);

                sNodeType* result_type = create_node_type_from_cl_type(method->mResultType, klass);
                int size = get_var_size(result_type);
                append_int_value_to_code(info->code, size, info->no_output);

                info->stack_num -= num_params;
                info->stack_num++;

                info->type = result_type;
            }
        }
        else {
            if(info->pinfo->exist_block_object_err == FALSE) { // for interpreter completion
                compile_err_msg(info, "method not found(1)");
                info->err_num++;

                err_msg_for_method_not_found(klass, method_name, param_types, num_params, TRUE, info);

                info->type = create_node_type_with_class_name("int"); // dummy
            }

            return TRUE;
        }
    }
    
    return TRUE;
}

unsigned int sNodeTree_create_method_call(unsigned int object_node, char* method_name, unsigned int* params, int num_params, int num_method_chains, sParserInfo* info)
{
    unsigned int node = alloc_node();

    xstrncpy(gNodes[node].uValue.sMethodCall.mMethodName, method_name, METHOD_NAME_MAX);
    gNodes[node].uValue.sMethodCall.mNumParams = num_params;
    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sMethodCall.mParams[i] = params[i];
    }

    gNodes[node].uValue.sMethodCall.mNumMethodChains = num_method_chains;

    gNodes[node].mNodeType = kNodeTypeMethodCall;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}


struct sCastMethods {
    char* method_name;
    char* type_;
};

struct sCastMethods gCastMethods[] = {
    { "to_byte", "byte" },
    { "to_ubyte", "ubyte" },
    { "to_short", "short" },
    { "to_ushort", "ushort" },
    { "to_int", "int" },
    { "to_uint", "uint" },
    { "to_long", "long" },
    { "to_ulong", "ulong" },
    { "to_float", "float" },
    { "to_double", "double" },
    { "to_char", "char" },
    { "to_pointer", "pointer" },
    { "to_bool", "bool" },
    { NULL, NULL },
};

static BOOL call_normal_method(unsigned int node, sCompileInfo* info, sNodeType* object_type, sNodeType* generics_types, sCLClass* klass, sNodeType* param_types[PARAMS_MAX], int num_params, char* method_name, unsigned int params[PARAMS_MAX], int num_method_chains, int max_method_chains)
{
    if(klass->mFlags & CLASS_FLAGS_DYNAMIC_CLASS) {
        /// get type of params without generating code ///
        BOOL no_output_before = info->no_output;
        info->no_output = TRUE;
        int stack_num_before = info->stack_num;

        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

        BOOL exist_lazy_lamda_compile = FALSE;
        if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types, info, FALSE, &exist_lazy_lamda_compile, FALSE)) {
            return FALSE;
        }

        info->no_output = no_output_before;
        info->stack_num = stack_num_before;

        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
            sNodeType* right_method_generics_types = get_methocs_generics_type(info->pinfo);

            /// get method ///
            sNodeType* result_type;
            sNodeType* result_method_generics_types = NULL;
            int method_index2 = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types, generics_types, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

            /// Searching for the method can be determined by statically ///
            if(method_index2 != -1) {
                info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

                BOOL exist_lazy_lamda_compile = FALSE;
                if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types, info, FALSE, &exist_lazy_lamda_compile, FALSE)) {
                    return FALSE;
                }

                if(!info->pinfo->exist_block_object_err) { // for interpreter completion
                    sCLMethod* method = klass->mMethods + method_index2;

                    append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                    append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                    append_int_value_to_code(info->code, info->sline, info->no_output);


                    append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
                    append_class_name_to_constant_pool_and_code(info, klass);
                    append_int_value_to_code(info->code, method_index2, info->no_output);

                    int size = get_var_size(result_type);
                    append_int_value_to_code(info->code, size, info->no_output);

                    info->stack_num -= num_params + 1;
                    info->stack_num++;

                    info->type = result_type;
                }
            }
            /// invoke callingMethod method ///
            else if(klass->mCallingMethodIndex != -1) {
                info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

                /// compile params ///
                int i;
                for(i=0; i<num_params; i++) {
                    int node2 = gNodes[node].uValue.sMethodCall.mParams[i];
                    if(!compile(node2, info)) {
                        return FALSE;
                    }

                    /// Do boxing if the class of a param is primitive ///
                    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                        boxing_to_lapper_class(&info->type, info);
                    }

                    param_types[i] = info->type;
                }

                /// invoke dynamic method ///
                sCLMethod* method = klass->mMethods + klass->mCallingMethodIndex;

                if(num_params >= ARRAY_VALUE_ELEMENT_MAX) {
                    compile_err_msg(info, "overflow parametor number");
                    return FALSE;
                }

                int num_real_params = num_params + 1;

                if(num_params >= ARRAY_VALUE_ELEMENT_MAX) {
                    compile_err_msg(info, "overflow parametor number");
                    return FALSE;
                }

                if(!info->pinfo->exist_block_object_err) { // for interpreter completion
                    append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                    append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                    append_int_value_to_code(info->code, info->sline, info->no_output);

                    append_opecode_to_code(info->code, OP_INVOKE_DYNAMIC_METHOD, info->no_output);
                    append_class_name_to_constant_pool_and_code(info, klass);
                    append_str_to_constant_pool_and_code(info->constant, info->code, method_name, info->no_output);
                    append_int_value_to_code(info->code, num_params, info->no_output);
                    append_int_value_to_code(info->code, 0, info->no_output);
                    append_int_value_to_code(info->code, num_method_chains, info->no_output);
                    append_int_value_to_code(info->code, max_method_chains, info->no_output);

                    sNodeType* result_type = create_node_type_from_cl_type(method->mResultType, klass);
                    int size = get_var_size(result_type);
                    append_int_value_to_code(info->code, size, info->no_output);

                    info->stack_num -= num_real_params;
                    info->stack_num++;

                    info->type = result_type;
                }
            }
            else {
                compile_err_msg(info, "Require the calllingMethod method for dynamic class");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }
    }
    else if(class_identify_with_class_name(klass, "Anonymous")) {
        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

        /// compile params ///
        BOOL exist_lazy_lamda_compile = FALSE;
        if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types, info, FALSE, &exist_lazy_lamda_compile, FALSE)) {
            return FALSE;
        }

        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
            int num_real_params = num_params + 1;

            int size_method_name_and_params = METHOD_NAME_MAX + PARAMS_MAX * CLASS_NAME_MAX + 256;
            char method_name_and_params[size_method_name_and_params];
            create_method_name_and_params(method_name_and_params, size_method_name_and_params, klass, method_name, param_types, num_params);

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);


            append_opecode_to_code(info->code, OP_INVOKE_VIRTUAL_METHOD, info->no_output);
            append_int_value_to_code(info->code, num_real_params, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, method_name_and_params, info->no_output);

            sNodeType* result_type = create_node_type_with_class_name("Anonymous");
            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num -= num_params + 1;
            info->stack_num++;

            info->type = result_type;
        }
    }
    else if(klass->mFlags & CLASS_FLAGS_INTERFACE)
    {
        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

        /// compile params ///
        BOOL exist_lazy_lamda_compile = FALSE;
        if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types, info, FALSE, &exist_lazy_lamda_compile, FALSE)) {
            return FALSE;
        }

        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
            sNodeType* right_method_generics_types = get_methocs_generics_type(info->pinfo);

            /// get method ///
            sNodeType* result_type;
            sNodeType* result_method_generics_types = NULL;
            int method_index2 = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types, generics_types, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

            if(method_index2 == -1) {
                compile_err_msg(info, "method not found(2)");
                info->err_num++;

                err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            sCLMethod* method = klass->mMethods + method_index2;

            int num_real_params = method->mNumParams + 1;

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);


            append_opecode_to_code(info->code, OP_INVOKE_VIRTUAL_METHOD, info->no_output);
            append_int_value_to_code(info->code, num_real_params, info->no_output);
            append_method_name_and_params_to_constant_pool_and_code(info, klass, method);

            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num -= num_params + 1;
            info->stack_num++;

            info->type = result_type;
        }
    }
    else {
        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

        /// compile params ///
        BOOL lazy_lambda_compile = TRUE;
        BOOL exist_lazy_lamda_compile = FALSE;
        if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types, info, lazy_lambda_compile, &exist_lazy_lamda_compile, FALSE)) 
        {
            return FALSE;
        }

        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
            sNodeType* right_method_generics_types = get_methocs_generics_type(info->pinfo);

            /// get method ///
            sNodeType* result_type;
            sNodeType* result_method_generics_types = NULL;
            int method_index2 = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types, generics_types, right_method_generics_types, &result_type, exist_lazy_lamda_compile, FALSE, &result_method_generics_types);

            /// lazy lambda compile ///
            if(method_index2 != -1 && exist_lazy_lamda_compile) {
                int node2 = params[num_params-1];

                /// determine block type and block params from getted method ///
                sCLMethod* method2 = klass->mMethods + method_index2;

                unsigned int tmp = clone_node(node2); // prevent realloc bug

                sNodeTree* node_tree = gNodes + tmp;
                BOOL omit_block_result_type = FALSE;
                sCLParam* param = method2->mParams + method2->mNumParams -1;
                sNodeType* node_type = create_node_type_from_cl_type(param->mType, klass);

                sNodeBlockType* node_block_type = node_type->mBlockType;

                sNodeType* block_result_type = node_block_type->mResultType;
                sNodeBlock* node_block = node_tree->uValue.sBlockObject.mBlockObjectCode;
                int num_block_params = node_block_type->mNumParams;

                if(node_tree->uValue.sBlockObject.mOmitResultType) {
                    if(!type_identify_with_class_name(block_result_type, "Null")) {
                        omit_block_result_type = TRUE;
                    }
                }

                BOOL omit_params = node_tree->uValue.sBlockObject.mOmitParams;
                BOOL result_type_boxing = FALSE;

                if(num_block_params > 0 && omit_params) {
                    sNodeType* method_generics_types = result_method_generics_types;
                    sNodeType* generics_types = info->type;

                    sVarTable* old_table = node_tree->uValue.sBlockObject.mOldTable;
                    sVarTable* new_table = init_block_vtable(old_table);

                    sParserParam block_params[PARAMS_MAX];

                    if(num_block_params >= METHOD_BLOCK_PARAM_MAX) {
                        compile_err_msg(info, "overflow method block parametor max");
                        info->err_num++;
                        return FALSE;
                    }

                    int i;
                    for(i=0; i<num_block_params; i++) {
                        if(i == 0) {
                            snprintf(block_params[i].mName, VAR_NAME_MAX, "it");
                        }
                        else {
                            snprintf(block_params[i].mName, VAR_NAME_MAX, "it%d", i+1);
                        }

                        sNodeType* block_param = node_block_type->mParams[i];

                        sNodeType* block_param2 = NULL;
                        if(method_generics_types) {
                            if(!solve_generics_types_for_node_type(block_param, ALLOC &block_param2, method_generics_types, FALSE, TRUE))
                            {
                                return FALSE;
                            }
                        }
                        else {
                            block_param2 = block_param;
                        }

                        sNodeType* block_param3 = NULL;
                        if(generics_types) {
                            if(!solve_generics_types_for_node_type(block_param2, ALLOC &block_param3, generics_types, FALSE, FALSE))
                            {
                                return FALSE;
                            }
                        }
                        else {
                            block_param3 = block_param2;
                        }

                        block_params[i].mType = block_param3;

                        if(!add_variable_to_table(new_table, block_params[i].mName, block_params[i].mType)) 
                        {
                            return FALSE;
                        }
                    }

                    /// parse_params ///
                    sParserInfo info2;

                    info2.p = node_block->mSource.mBuf;
                    info2.source = node_block->mSource.mBuf;

                    info2.sname = node_block->mSName;
                    info2.sline = node_block->mSLine;
                    info2.err_num = 0;
                    info2.lv_table = old_table;
                    info2.parse_phase = 0;
                    info2.klass = info->pinfo->klass;
                    info2.generics_info = info->pinfo->generics_info;
                    info2.method_generics_info = info->pinfo->method_generics_info;
                    info2.cinfo = info;
                    info2.included_source = FALSE;
                    info2.get_type_for_interpreter = info->pinfo->get_type_for_interpreter;
                    info2.next_command_is_to_bool = FALSE;
                    info2.exist_block_object_err = info->pinfo->exist_block_object_err;

                    BOOL lambda = FALSE;

                    sNodeBlock* node_block = NULL;
                    if(!parse_block(ALLOC &node_block, &info2, new_table, TRUE)) {
                        return FALSE;
                    }

                    info->err_num += info2.err_num;
                    info->pinfo->exist_block_object_err = info2.exist_block_object_err;

                    BOOL omit_result_type = FALSE;
                    sNodeType* result_type = block_result_type;

                    sNodeType* result_type2 = NULL;
                    if(method_generics_types) {
                        if(!solve_generics_types_for_node_type(result_type, ALLOC &result_type2, method_generics_types, FALSE, TRUE))
                        {
                            return FALSE;
                        }
                    }
                    else {
                        result_type2 = result_type;
                    }

                    sNodeType* result_type3 = NULL;
                    if(generics_types) {
                        if(!solve_generics_types_for_node_type(result_type2, ALLOC &result_type3, generics_types, FALSE, FALSE))
                        {
                            return FALSE;
                        }
                    }
                    else {
                        result_type3 = result_type2;
                    }

                    if(result_type3 && result_type3->mClass 
                        && !(result_type3->mClass->mFlags & CLASS_FLAGS_PRIMITIVE)) 
                    {
                        result_type_boxing = TRUE;
                    }
                    node2 = sNodeTree_create_block_object(block_params, num_block_params, result_type3, MANAGED node_block, lambda, &info2, omit_result_type, FALSE, old_table);
                }

                sNodeType* block_last_type_before = info->block_last_type;
                info->block_last_type = NULL;
                BOOL result_type_boxing_before = info->result_type_boxing;
                info->result_type_boxing = result_type_boxing;

                BOOL omit_block_result_type_before = info->omit_block_result_type;
                info->omit_block_result_type2 = omit_block_result_type;
                sNodeType* return_type2_before = info->return_type2;
                info->return_type2 = NULL;
                info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

                /// compile ///
                if(!compile(node2, info)) {
                    info->block_last_type = block_last_type_before;
                    info->result_type_boxing = result_type_boxing_before;
                    info->omit_block_result_type2 = omit_block_result_type_before;
                    info->return_type2 = return_type2_before;
                    return FALSE;
                }

                if(!info->pinfo->exist_block_object_err) { // for interpreter completion
                    if(omit_block_result_type) {
                        sNodeType* node_type = info->type;

                        if(node_type) {
                            sNodeBlockType* node_block_type = node_type->mBlockType;

                            if(node_block_type && info->return_type2 != NULL) {
                                node_block_type->mResultType = info->return_type2;
                            }
                            else if(node_block_type && type_identify_with_class_name(node_block_type->mResultType, "Null"))
                            {
                                node_block_type->mResultType = info->block_last_type;
                            }
                        }

                        int param_class_num = block_result_type->mClass->mMethodGenericsParamClassNum;
                        if(param_class_num != -1) {
                            result_method_generics_types->mGenericsTypes[param_class_num] = info->block_last_type;

                            result_method_generics_types->mNumGenericsTypes = param_class_num +1;
                        }
                    }

                    param_types[num_params-1] = info->type;

                    info->block_last_type = block_last_type_before;
                    info->result_type_boxing = result_type_boxing_before;
                    info->omit_block_result_type2 = omit_block_result_type_before;
                    info->return_type2 = return_type2_before;

                    method_index2 = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types, generics_types, right_method_generics_types, &result_type, FALSE, TRUE, &result_method_generics_types);
                }
            }
            else {
                if(exist_lazy_lamda_compile) {
                    int node2 = params[num_params-1];

                    /// compile ///
                    if(!compile(node2, info)) {
                        return FALSE;
                    }
                }
            }

            if(!info->pinfo->exist_block_object_err) { // for interpreter completion
                if(method_index2 == -1) {
                    /// Is cast method ? ////
                    int cast_method_index = -1;
                    int i;
                    for(i=0; gCastMethods[i].method_name != NULL; i++) {
                        if(strcmp(method_name, gCastMethods[i].method_name) == 0) {
                            cast_method_index = i;
                            break;
                        }
                    }

                    /// cast methods ///
                    if(cast_method_index != -1) {
                        /// check ///
                        if(num_params != 0) {
                            compile_err_msg(info, "A cast method doesn't require params");
                            info->err_num++;

                            info->type = create_node_type_with_class_name("int"); // dummy

                            return TRUE;
                        }

                        /// go ///
                        char* cast_type_name = gCastMethods[cast_method_index].type_;

                        sNodeType* left_type = object_type;
                        sNodeType* right_type = create_node_type_with_class_name(cast_type_name);

                        cast_right_type_to_left_type(left_type, &right_type, info);
                        info->type = right_type;

                        return TRUE;
                    }
                    else {
                        compile_err_msg(info, "method not found(5)");
                        info->err_num++;

                        if(!exist_lazy_lamda_compile) {
                            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);
                        }

                        info->type = create_node_type_with_class_name("int"); // dummy

                        return TRUE;
                    }
                }

                sCLMethod* method = klass->mMethods + method_index2;

                append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
                append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
                append_int_value_to_code(info->code, info->sline, info->no_output);


                append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

                append_class_name_to_constant_pool_and_code(info, klass);
                append_int_value_to_code(info->code, method_index2, info->no_output);

                int size = get_var_size(result_type);
                append_int_value_to_code(info->code, size, info->no_output);

                info->stack_num -= num_params + 1;
                info->stack_num++;

                info->type = result_type;
            }
        }
    }

    return TRUE;
}

void boxing_before_method_call(char* method_name, sCompileInfo* info)
{
    /// Do boxing if the class of left object is primitive ///
    if(info->type->mArray) {
        if(strcmp(method_name, "identifyWith") == 0) {
        }
        else if(strcmp(method_name, "className") == 0) {
        }
        else if(strcmp(method_name, "toNull") == 0) {
        }
        else if(strcmp(method_name, "ID") == 0) {
        }
        else if(strcmp(method_name, "toAnonymous") == 0) {
        }
        else if(strcmp(method_name, "allocatedSize") == 0) {
        }
        else if(strcmp(method_name, "headOfMemory") == 0) {
        }
        else {
            boxing_to_lapper_class(&info->type, info);
        }
    }
    else if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        boxing_to_lapper_class(&info->type, info);
    }
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
        compile_err_msg(info, "no type for method call");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int num_method_chains = gNodes[node].uValue.sMethodCall.mNumMethodChains;
    int max_method_chains = gNodes[node].mMaxMethodChains;

    char method_name[METHOD_NAME_MAX];
    xstrncpy(method_name, gNodes[node].uValue.sMethodCall.mMethodName, METHOD_NAME_MAX);

    /// Do boxing if the class of left object is primitive ///
    boxing_before_method_call(method_name, info);

    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        compile_err_msg(info, "Primitive class can't be called to method");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* method_generics_types;
    if(info->pinfo->klass) {
        method_generics_types = get_methocs_generics_type(info->pinfo);
    }
    else {
        method_generics_types = NULL;
    }

    sNodeType* generics_types = info->type;
    sNodeType* generics_types2;

    if(!solve_generics_types_for_node_type(generics_types, ALLOC &generics_types2, method_generics_types, TRUE, TRUE)) {
        return FALSE;
    }

    sCLClass* klass = generics_types2->mClass;
    sNodeType* object_type = generics_types2;

    sNodeType* param_types[PARAMS_MAX];

    int num_params = gNodes[node].uValue.sMethodCall.mNumParams;
    unsigned int params[PARAMS_MAX];

    memcpy(params, gNodes[node].uValue.sMethodCall.mParams, sizeof(unsigned int)*PARAMS_MAX);

    /// special methods ///
    if(strcmp(method_name, "identifyWith") == 0) {
        /// compile params ///
        BOOL exist_lazy_lamda_compile = FALSE;
        if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types2, info, FALSE, &exist_lazy_lamda_compile, FALSE)) {
            return FALSE;
        }

        //// go ///
        if(num_params != 1) {
            compile_err_msg(info, "identify method require one none primitive class param");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
        sCLClass* param_class = param_types[0]->mClass;
        if((param_class->mFlags & CLASS_FLAGS_PRIMITIVE) && !type_identify_with_class_name(param_types[0], "Null")) {
            compile_err_msg(info, "Identify method require one none primitive class param");
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
        //// go ///
        if(num_params != 0) {
            compile_err_msg(info, "className method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_CLASSNAME, info->no_output);

        info->stack_num-=num_params + 1;
        info->stack_num++;

        info->type = create_node_type_with_class_name("String");
    }
    else if(strcmp(method_name, "toNull") == 0) {
        //// go ///
        if(num_params != 0) {
            compile_err_msg(info, "toNull method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_POP, info->no_output);

        info->stack_num--;

        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
        info->stack_num++;

        info->type = create_node_type_with_class_name("Null");
        
        return TRUE;
    }
    else if(strcmp(method_name, "ID") == 0) {
        //// go ///
        if(num_params != 0) {
            compile_err_msg(info, "ID method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = create_node_type_with_class_name("int");
        
        return TRUE;
    }
    else if(strcmp(method_name, "allocatedSize") == 0) {
        //// go ///
        if(num_params != 0) {
            compile_err_msg(info, "allocatedSize method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_OBJ_ALLOCATED_SIZE, info->no_output);

        info->stack_num-=num_params + 1;
        info->stack_num++;

        info->type = create_node_type_with_class_name("int");
    }
    else if(strcmp(method_name, "headOfMemory") == 0) {
        //// go ///
        if(num_params != 0) {
            compile_err_msg(info, "headOfMemory method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_OBJ_HEAD_OF_MEMORY, info->no_output);

        info->stack_num-=num_params + 1;
        info->stack_num++;

        info->type = create_node_type_with_class_name("pointer");
    }
    else if(strcmp(method_name, "toAnonymous") == 0) {
        //// go ///
        if(num_params != 0) {
            compile_err_msg(info, "toAnonymous method doesn't require params");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        info->type = create_node_type_with_class_name("Anonymous");
    }
    else if(type_identify_with_class_name(object_type, "Anonymous") && strcmp(method_name, "cast") == 0) {
        //// go ///
        if(!(num_params == 1 && gNodes[params[0]].mNodeType == kNodeTypeString)) {
            compile_err_msg(info, "cast method require one String Constant param");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        char* class_name = gNodes[params[0]].uValue.sString.mString;

        info->type = create_node_type_with_class_name(class_name);

        return TRUE;
    }
    else if(strcmp(method_name, "is") == 0) {
        /// check param ///
        if(!(num_params == 1 && gNodes[params[0]].mNodeType == kNodeTypeString)) {
            compile_err_msg(info, "is method require one String Constant param");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        /// compile params ///
        BOOL exist_lazy_lamda_compile = FALSE;
        if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types2, info, FALSE, &exist_lazy_lamda_compile, FALSE)) {
            return FALSE;
        }

        append_opecode_to_code(info->code, OP_IS, info->no_output);

        info->stack_num-=2;
        info->stack_num++;

        info->type = create_node_type_with_class_name("bool");

        //// go ///
        char* class_name = gNodes[params[0]].uValue.sString.mString;
        if(gNodes[lnode].mNodeType == kNodeTypeLoadVariable) {
            sVar* var = get_variable_from_table(info->lv_table, gNodes[lnode].uValue.mVarName);

            var->mType = create_node_type_with_class_name(class_name);
        }
    }
    /// normal methods ///
    else {
        if(!call_normal_method(node, info, object_type, generics_types2, klass, param_types, num_params, method_name, params, num_method_chains, max_method_chains))
        {
            return FALSE;;
        }
    }
    
    return TRUE;
}

unsigned int sNodeTree_create_new_operator(sNodeType* node_type, unsigned int* params, int num_params, unsigned int array_num, sParserInfo* info)
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

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_new_operator(unsigned int node, sCompileInfo* info)
{
    sNodeType* generics_types = gNodes[node].uValue.sNewOperator.mType;

    if(generics_types->mClass == NULL) {
        compile_err_msg(info, "Class not found for new operator");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* generics_types2;
    solve_generics_for_variable(generics_types, &generics_types2, info->pinfo);

    sCLClass* klass = generics_types2->mClass;
    unsigned int array_num = gNodes[node].uValue.sNewOperator.mArrayNum;

    if(array_num > 0) {
        if(!compile(array_num, info)) {
            return FALSE;
        }
    }

    sNodeType* node_type = generics_types2;


    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_type_name_to_constant_pool_and_code(info, node_type);
    append_int_value_to_code(info->code, array_num ? 1:0, info->no_output);

    info->stack_num++;

    if(array_num > 0) {
        int num_params = gNodes[node].uValue.sNewOperator.mNumParams;

        if(num_params > 0) {
            compile_err_msg(info, "Array can't create with initialize method");
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

        info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

        BOOL exist_lazy_lamda_compile = FALSE;
        if(!compile_params(klass, method_name, &num_params, params, param_types, generics_types2, info, FALSE, &exist_lazy_lamda_compile, FALSE)) {
            return FALSE;
        }

        if(!info->pinfo->exist_block_object_err) { // for interpreter completion
            sNodeType* right_method_generics_types = get_methocs_generics_type(info->pinfo);

            sNodeType* result_type;
            sNodeType* result_method_generics_types = NULL;
            int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

            if(method_index == -1) {
                compile_err_msg(info, "method not found(6)");
                info->err_num++;

                err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);

            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code, method_index, info->no_output);

            int size = get_var_size(generics_types2);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num-=num_params+1;
            info->stack_num++;

            info->type = generics_types2;
        }
    }

    return TRUE;
}

unsigned int sNodeTree_create_return_expression(unsigned int expression_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReturn;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

    sNodeType* value_result_type;
    if(expression_node != 0) {
        if(!compile(expression_node, info)) {
            return FALSE;
        }
        value_result_type = info->type;
    }
    else {
        value_result_type = create_node_type_with_class_name("Null");
    }

    sCLClass* klass = info->pinfo->klass;
    sCLMethod* method = info->method;

    /// check return statment in not method or block object ///
    if(method == NULL && !info->in_block) {
        compile_err_msg(info, "Return expression should be in a method definition or in a block object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// check return statment in initialize method ///
    if(!info->in_block && klass && (!(method->mFlags & METHOD_FLAGS_CLASS_METHOD) && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "initialize") == 0) && (!(method->mFlags & METHOD_FLAGS_CLASS_METHOD) && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "finalize") == 0))
    {
        compile_err_msg(info, "There is in the initialize or finalize method");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// result type ///
    sNodeType* result_type = NULL;

    if(info->omit_block_result_type2) {
        info->return_type = value_result_type;
        result_type = value_result_type;
    }
    else if(info->omit_block_result_type) {
        info->return_type = value_result_type; // hand over to compile_block_object
        result_type = value_result_type;
    }
    else if(info->in_block) {
        result_type = info->block_result_type;
    }
    else { // info->method != NULL
        result_type = create_node_type_from_cl_type(info->method->mResultType, info->pinfo->klass);
    }

    /// check result type ///
    sNodeType* result_type2 = NULL;
    solve_generics_for_variable(result_type, &result_type2, info->pinfo);

    if((!type_identify_with_class_name(result_type2, "Null") && expression_node == 0)
        || (type_identify_with_class_name(result_type2, "Null") && expression_node != 0))
    {
        compile_err_msg(info, "Invalid type of return value(1)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(type_identify_with_class_name(result_type2, "Null")) {
        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);

        info->stack_num++;
    }
    else {
        if(cast_posibility(result_type2, value_result_type)) {
            cast_right_type_to_left_type(result_type2, &value_result_type, info);
        }

        if(!substitution_posibility(result_type2, value_result_type, NULL, NULL, NULL, NULL)) {
            compile_err_msg(info, "Invalid type of return value(2). Left type is %s. Right type is %s.", CLASS_NAME(result_type2->mClass), CLASS_NAME(value_result_type->mClass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(info->stack_num != 1) {
        compile_err_msg(info, "Invalid type of return value(4)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_RETURN, info->no_output);

    if(info->pinfo->err_num == 0) { // for interpreter completion
        info->stack_num = 0;  // no pop
        info->type = create_node_type_with_class_name("Null");
    }

    return TRUE;
}

unsigned int sNodeTree_create_throw_expression(unsigned int expression_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeThrow;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Throw expressioin should be in a method definition");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* exception_type = info->type;

    if(!is_exception_type(exception_type))
    {
        compile_err_msg(info, "Invalid type of exception value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(info->stack_num != 1) {
        compile_err_msg(info, "Invalid stack num in the throw expression");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    append_opecode_to_code(info->code, OP_THROW, info->no_output);
    info->stack_num = 0;  // no pop
    info->type = create_node_type_with_class_name("Null");
    
    return TRUE;
}

unsigned int sNodeTree_try_expression(MANAGED sNodeBlock* try_node_block, MANAGED sNodeBlock* catch_node_block, char* exception_var_name, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTry;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sTry.mTryNodeBlock = MANAGED try_node_block;
    gNodes[node].uValue.sTry.mCatchNodeBlock = MANAGED catch_node_block;
    xstrncpy(gNodes[node].uValue.sTry.mExceptionVarName, exception_var_name, VAR_NAME_MAX);

    return node;
}

static BOOL compile_try_expression(unsigned int node, sCompileInfo* info)
{
    int label_num = gLabelNum++;

    /// try ///
    append_opecode_to_code(info->code, OP_TRY, info->no_output);

    int try_offset_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    char label_catch_name[LABEL_NAME_MAX];
    create_label_name("catch_label", label_catch_name, LABEL_NAME_MAX, label_num);

    append_str_to_constant_pool_and_code(info->constant, info->code, label_catch_name, info->no_output);

    sNodeBlock* try_node_block = gNodes[node].uValue.sTry.mTryNodeBlock;
    if(!compile_block(try_node_block, info)) {
        return FALSE;
    }

    append_opecode_to_code(info->code, OP_TRY_END, info->no_output);

    append_opecode_to_code(info->code, OP_GOTO, info->no_output);
    int goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);

    char label_name[LABEL_NAME_MAX];
    create_label_name("try_end", label_name, LABEL_NAME_MAX, label_num);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_name, info->no_output);

    *(int*)(info->code->mCodes + try_offset_point) = info->code->mLen;

    append_opecode_to_code(info->code, OP_LABEL, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, label_catch_name, info->no_output);

    /// catch ///
    sNodeBlock* catch_node_block = gNodes[node].uValue.sTry.mCatchNodeBlock;

    if(catch_node_block) {
        sVarTable* catch_block_var_table = catch_node_block->mLVTable;
        char* var_name = gNodes[node].uValue.sTry.mExceptionVarName;

        int var_index = get_variable_index(catch_block_var_table, var_name);
        MASSERT(var_index != -1);

        append_opecode_to_code(info->code, OP_CATCH_STORE, info->no_output);
        append_int_value_to_code(info->code, var_index, info->no_output);

        append_opecode_to_code(info->code, OP_CATCH_POP, info->no_output); // for none JIT code

        if(!compile_block(catch_node_block, info)) {
            return FALSE;
        }

        *(int*)(info->code->mCodes + goto_point) = info->code->mLen;

        append_opecode_to_code(info->code, OP_LABEL, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, label_name, info->no_output);

        if(info->pinfo->err_num == 0) { // for interpreter completion
            append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
            info->stack_num++;

            info->type = create_node_type_with_class_name("Null");
        }
    }

    return TRUE;
}

unsigned int sNodeTree_create_fields(char* name, unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadField;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "no type for loading field");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = info->type->mClass;
    char field_name[VAR_NAME_MAX];
    xstrncpy(field_name, gNodes[node].uValue.mVarName, VAR_NAME_MAX);
    BOOL array = info->type->mArray;
    sNodeType* generics_types = info->type;

    if(klass->mGenericsParamClassNum != -1) {
        sGenericsParamInfo* generics_info = &info->pinfo->generics_info;
        if(klass->mGenericsParamClassNum < generics_info->mNumParams) {
            klass = generics_info->mInterface[klass->mGenericsParamClassNum];
        }
        else {
            compile_err_msg(info, "invalid generics interface method call");
            info->err_num++;
        }
    }

    sCLClass* regex_class = get_class("regex");
    sCLClass* char_class = get_class("char");

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
    else if(klass == char_class && strcmp(field_name, "to_upper") == 0) {
        append_opecode_to_code(info->code, OP_CHAR_UPPERCASE, info->no_output);

        info->type = create_node_type_with_class_name("char");
    }
    else if(klass == char_class && strcmp(field_name, "to_lower") == 0) {
        append_opecode_to_code(info->code, OP_CHAR_LOWERCASE, info->no_output);

        info->type = create_node_type_with_class_name("char");
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
    else if(((klass->mFlags & CLASS_FLAGS_PRIMITIVE) || strcmp(CLASS_NAME(klass), "regex") == 0) && strcmp(field_name, "toString") == 0) {
        cast_right_type_to_String(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toString") == 0) {
        cast_right_type_to_String(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toByte") == 0) {
        cast_right_type_to_Byte(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toUByte") == 0) {
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
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toUInteger") == 0) {
        cast_right_type_to_UInteger(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toLong") == 0) {
        cast_right_type_to_Long(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toULong") == 0) {
        cast_right_type_to_ULong(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toFloat") == 0) {
        cast_right_type_to_Float(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toDouble") == 0) {
        cast_right_type_to_Double(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && strcmp(field_name, "toPointer") == 0) {
        cast_right_type_to_Pointer(&info->type, info);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE)&& strcmp(field_name, "toChar") == 0) {
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
            compile_err_msg(info, "There is no field(%s) in this class(%s)(6)", field_name, CLASS_NAME(klass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLField* field = klass->mFields + field_index;
        sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

        /// solve generics ///
        sNodeType* solved_field_type;
        if(!solve_generics_types_for_node_type(field_type, ALLOC &solved_field_type, generics_types, TRUE, FALSE)) 
        {
            return FALSE;
        }

        /// generate code ///
        append_opecode_to_code(info->code, OP_LOAD_FIELD, info->no_output);
        append_int_value_to_code(info->code, field_index, info->no_output);
        int size = get_var_size(field_type);

        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num--;
        info->stack_num++;

        info->type = solved_field_type;

    }

    return TRUE;
}

unsigned int sNodeTree_create_assign_field(char* var_name, unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreField;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "no type for object");
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
        compile_err_msg(info, "no type for right object type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = left_type->mClass;
    char field_name[VAR_NAME_MAX];
    xstrncpy(field_name, gNodes[node].uValue.mVarName, VAR_NAME_MAX);

    int field_index = search_for_field(klass, field_name);

    if(field_index == -1) {
        compile_err_msg(info, "There is no field(%s) in this class(%s)(1)", field_name, CLASS_NAME(klass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLField* field = klass->mFields + field_index;
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    /// solve generics ///
    sNodeType* solved_field_type;
    if(!solve_generics_types_for_node_type(field_type, ALLOC &solved_field_type, generics_types, TRUE, FALSE)) 
    {
        return FALSE;
    }

    if(cast_posibility(solved_field_type, right_type)) {
        cast_right_type_to_left_type(solved_field_type, &right_type, info);
    }

    if(!substitution_posibility(solved_field_type, right_type, generics_types, NULL, NULL, NULL)) {
        compile_err_msg(info, "The different type between left type and right type(2). %s and %s", CLASS_NAME(solved_field_type->mClass), CLASS_NAME(right_type->mClass));
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

unsigned int sNodeTree_create_class_fields(sCLClass* klass, char* name, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadClassField;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    char field_name[VAR_NAME_MAX];
    xstrncpy(field_name, gNodes[node].uValue.sClassField.mVarName, VAR_NAME_MAX);

    int field_index = search_for_class_field(klass, field_name);

    if(field_index == -1) {
        compile_err_msg(info, "There is no field(%s) in this class(%s)(2)", field_name, CLASS_NAME(klass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLField* field = klass->mClassFields + field_index;
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    append_opecode_to_code(info->code, OP_LOAD_CLASS_FIELD, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_int_value_to_code(info->code, field_index, info->no_output);

    int size = get_var_size(field_type);

    append_int_value_to_code(info->code, size, info->no_output);

    info->stack_num++;

    info->type = field_type;

    return TRUE;
}

unsigned int sNodeTree_create_assign_class_field(sCLClass* klass, char* name , unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreClassField;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "no type for right object type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = gNodes[node].uValue.sClassField.mClass;
    char field_name[VAR_NAME_MAX];
    xstrncpy(field_name, gNodes[node].uValue.sClassField.mVarName, VAR_NAME_MAX);

    int field_index = search_for_class_field(klass, field_name);

    if(field_index == -1) {
        compile_err_msg(info, "There is no field(%s) in this class(%s)(3)", field_name, CLASS_NAME(klass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLField* field = klass->mClassFields + field_index;
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    if(cast_posibility(field_type, right_type)) {
        cast_right_type_to_left_type(field_type, &right_type, info);
    }

    if(!substitution_posibility(field_type, right_type, NULL, NULL, NULL, NULL)) {
        compile_err_msg(info, "The different type between left type and right type(3). Left type is %s. Right type is %s.", CLASS_NAME(field_type->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;

    }

    append_opecode_to_code(info->code, OP_STORE_CLASS_FIELD, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_int_value_to_code(info->code, field_index, info->no_output);

    info->type = field_type;

    return TRUE;
}

unsigned int sNodeTree_create_store_value_to_pointer(unsigned int left_node, sNodeType* node_type, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreValueToPointer;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Left node requires the pointer class");
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
        || !substitution_posibility(node_type, right_type, NULL, NULL, NULL, NULL))
    {
        if(right_type == NULL || node_type->mClass == NULL) {
            compile_err_msg(info, "The different type between left type and right type(4). NULL type.");
        }
        else {
            compile_err_msg(info, "The different type between left type and right type(4). Left type is %s. right type is %s", CLASS_NAME(node_type->mClass), CLASS_NAME(right_type->mClass));
        }
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

unsigned int sNodeTree_create_load_value_from_pointer(unsigned int left_node, sNodeType* node_type, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadValueFromPointer;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Left node requires the pointer class");
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

BOOL sNodeTree_create_increment_operand(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIncrementOperand;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }

        info->stack_num++;
    }

    append_opecode_to_code(info->code, add_operand, info->no_output);

    info->stack_num--;

    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[lnode].uValue.mVarName, VAR_NAME_MAX);
    int var_index = get_variable_index(info->lv_table, var_name);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    if(!monadic) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
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
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
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
    char field_name[VAR_NAME_MAX];
    xstrncpy(field_name, gNodes[lnode].uValue.mVarName, VAR_NAME_MAX);

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
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
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
        compile_err_msg(info, "Invalid increment operand");
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
            increment_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            increment_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            compile_err_msg(info, "Invalid type for increment operand");
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
            if(!increment_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, FALSE)) {
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
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_monadic_increment_operand(unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMonadicIncrementOperand;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Invalid monadic increment operand");
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
            increment_operand_core(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCULONG, TRUE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            increment_operand_core(node, info, rnode, OP_CADD, OP_CSUB, OP_LDCINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            compile_err_msg(info, "Invalid type for increment operand");
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
            if(!increment_operand_core_for_field(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCULONG, TRUE, FALSE)) {
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
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_increment_operand_with_value(unsigned int left_node, unsigned int value, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIncrementWithValueOperand;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Invalid increment operand");
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

    if(cast_posibility(left_type, right_type)) {
        cast_right_type_to_left_type(left_type, &right_type, info);
    }

    if(!substitution_posibility(left_type, right_type, NULL, NULL, NULL, NULL)) {
        compile_err_msg(info, "The different type between left type and right type(5). Left type is %s. Right type is %s.", CLASS_NAME(left_type->mClass), CLASS_NAME(right_type->mClass));
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
            increment_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, TRUE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(left_type, "char")) {
            increment_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            compile_err_msg(info, "Invalid type for increment operand");
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
            if(!increment_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, TRUE)) {
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
            compile_err_msg(info, "Invalid type for increment operand");
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
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG || ldc_operand == OP_LDCPOINTER) {
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
    }

    append_opecode_to_code(info->code, sub_operand, info->no_output);

    info->stack_num--;

    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[lnode].uValue.mVarName, VAR_NAME_MAX);
    int var_index = get_variable_index(info->lv_table, var_name);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    if(!monadic) {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG) {
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
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
        if(ldc_operand == OP_LDCLONG || ldc_operand == OP_LDCULONG || ldc_operand == OP_LDCPOINTER) {
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
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
    char field_name[VAR_NAME_MAX];
    xstrncpy(field_name, gNodes[lnode].uValue.mVarName, VAR_NAME_MAX);

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
            clint64 lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
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

BOOL sNodeTree_create_decrement_operand(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDecrementOperand;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Invalid increment operand");
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
            decrement_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, FALSE);
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
            decrement_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            decrement_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            compile_err_msg(info, "Invalid type for increment operand");
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
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, FALSE)) {
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
            if(!decrement_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, FALSE)) {
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
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_monadic_decrement_operand(unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMonadicDecrementOperand;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Invalid increment operand");
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
            decrement_operand_core(node, info, rnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, TRUE, FALSE);
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
            decrement_operand_core(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCULONG, TRUE, FALSE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(node_type, "char")) {
            decrement_operand_core(node, info, rnode, OP_CADD, OP_CSUB, OP_LDCINT, TRUE, FALSE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            compile_err_msg(info, "Invalid type for increment operand");
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
            if(!decrement_operand_core_for_field(node, info, rnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, TRUE, FALSE)) {
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
            if(!decrement_operand_core_for_field(node, info, rnode, OP_PADD, OP_PSUB, OP_LDCULONG, TRUE, FALSE)) {
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
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

BOOL sNodeTree_create_decrement_operand_with_value(unsigned int left_node, unsigned int value, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDecrementWithValueOperand;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "Invalid increment operand");
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

    if(cast_posibility(left_type, right_type)) {
        cast_right_type_to_left_type(left_type, &right_type, info);
    }

    if(!substitution_posibility(left_type, right_type, NULL, NULL, NULL, NULL)) {
        compile_err_msg(info, "The different type between left type and right type(6). Left type is %s. Right type is %s.", CLASS_NAME(left_type->mClass), CLASS_NAME(right_type->mClass));
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
            decrement_operand_core(node, info, lnode, OP_USADD, OP_USSUB, OP_LDCUSHORT, FALSE, TRUE);
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
            decrement_operand_core(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, TRUE);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if(type_identify_with_class_name(left_type, "char")) {
            decrement_operand_core(node, info, lnode, OP_CADD, OP_CSUB, OP_LDCINT, FALSE, TRUE);
            info->type = create_node_type_with_class_name("char");
        }
        else {
            compile_err_msg(info, "Invalid type for increment operand");
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
            if(!decrement_operand_core_for_field(node, info, lnode, OP_UBADD, OP_UBSUB, OP_LDCUBYTE, FALSE, TRUE)) {
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
            if(!decrement_operand_core_for_field(node, info, lnode, OP_PADD, OP_PSUB, OP_LDCULONG, FALSE, TRUE)) {
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
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    return TRUE;
}

unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadArrayElement;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "no type for loading element");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(left_type->mArray == FALSE) {
        compile_err_msg(info, "Clover2 can't get an element from this type.");
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
        compile_err_msg(info, "no type for element index");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* int_type = create_node_type_with_class_name("int");

    cast_right_type_to_left_type(int_type, &middle_type, info);

    if(!substitution_posibility_with_class_name(middle_type, "int")) {
        compile_err_msg(info, "Type of index should be number");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// generate code ///
    sNodeType* var_type = clone_node_type(left_type);

    var_type->mArray = FALSE;

    append_opecode_to_code(info->code, OP_LOAD_ELEMENT, info->no_output);

    int size = get_var_size(var_type);
    append_int_value_to_code(info->code, size, info->no_output);

    info->stack_num-=2;
    info->stack_num++;

    info->type = clone_node_type(left_type);
    info->type->mArray = FALSE;

    return TRUE;
}

unsigned int sNodeTree_create_store_array_element(unsigned int array, unsigned int index_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreArrayElement;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "no type for object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(left_type->mArray == FALSE) {
        compile_err_msg(info, "Clover2 can't get an element from this type.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type2;
    solve_generics_for_variable(left_type, &left_type2, info->pinfo);

    /// compile middle node ///
    unsigned int mnode = gNodes[node].mMiddle;

    if(!compile(mnode, info)) {
        return FALSE;
    }

    sNodeType* middle_type = info->type;

    if(middle_type == NULL 
        || type_identify_with_class_name(middle_type, "Null"))
    {
        compile_err_msg(info, "no type for element index");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* int_type = create_node_type_with_class_name("int");

    cast_right_type_to_left_type(int_type, &middle_type, info);

    if(!substitution_posibility_with_class_name(middle_type, "int")) {
        compile_err_msg(info, "Type of index should be number");
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
        compile_err_msg(info, "no type for right object type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* right_type2;
    solve_generics_for_variable(right_type, &right_type2, info->pinfo);

    sNodeType* left_type3 = clone_node_type(left_type2);
    left_type3->mArray = FALSE;

    if(cast_posibility(left_type3, right_type2)) {
        cast_right_type_to_left_type(left_type3, &right_type2, info);
    }

    if(!substitution_posibility(left_type3, right_type2, NULL, NULL, NULL, NULL)) {
        compile_err_msg(info, "The different type between left type and right type(7). %s and %s", CLASS_NAME(left_type3->mClass), CLASS_NAME(right_type2->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    //// generate code ///
    append_opecode_to_code(info->code, OP_STORE_ELEMENT, info->no_output);

    info->stack_num-=2;

    info->type = right_type2;

    return TRUE;
}

unsigned int sNodeTree_create_character_value(wchar_t c, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeChar;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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

unsigned int sNodeTree_create_string_value(MANAGED char* value, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeString;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sString.mString = MANAGED value;
    int i;
    for(i=0; i<num_string_expression; i++) {
        gNodes[node].uValue.sString.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sString.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sString.mNumStringExpression = num_string_expression;

    return node;
}

BOOL compile_string_value(unsigned int node, sCompileInfo* info)
{
    char* str = gNodes[node].uValue.sString.mString;

    int num_string_expression = gNodes[node].uValue.sString.mNumStringExpression;

    sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
    memcpy(string_expressions, gNodes[node].uValue.sString.mStringExpressions, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

    int string_expression_offsets[STRING_EXPRESSION_MAX];
    memcpy(string_expression_offsets, gNodes[node].uValue.sString.mStringExpressionOffsets, sizeof(int)*STRING_EXPRESSION_MAX);

    int i;

    for(i=0; i<num_string_expression; i++) {
        sNodeBlock* node_block = string_expressions[i];
        if(!compile_block_with_result(node_block, info)) {
            return FALSE;
        }

        if(info->type == NULL) {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLClass* klass = info->type->mClass;

        if(!type_identify_with_class_name(info->type, "String")) 
        {
            boxing_to_lapper_class(&info->type, info);

            klass = info->type->mClass;

            sNodeType* result_type = NULL;
            sNodeType* result_method_generics_types = NULL;
            int method_index = search_for_method(klass, "toString", NULL, 0, FALSE, klass->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

            if(method_index == -1) {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);

            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code, method_index, info->no_output);

            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num--;
            info->stack_num++;

            info->type = result_type;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_STRING, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, str, info->no_output);
    append_int_value_to_code(info->code, num_string_expression, info->no_output);

    for(i=0; i<num_string_expression; i++) {
        append_int_value_to_code(info->code, string_expression_offsets[i], info->no_output);
    }

    info->stack_num++;
    info->stack_num -= num_string_expression;

    info->type = create_node_type_with_class_name("String");

    return TRUE;
}

unsigned int sNodeTree_create_buffer_value(MANAGED char* value, int len, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBuffer;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sBuffer.mBuffer = MANAGED value;
    gNodes[node].uValue.sBuffer.mLen = len;
    int i;
    for(i=0; i<num_string_expression; i++) {
        gNodes[node].uValue.sBuffer.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sBuffer.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sBuffer.mNumStringExpression = num_string_expression;

    return node;
}

BOOL compile_buffer_value(unsigned int node, sCompileInfo* info)
{
    char* buf = gNodes[node].uValue.sBuffer.mBuffer;

    int size = gNodes[node].uValue.sBuffer.mLen;

    int num_string_expression = gNodes[node].uValue.sBuffer.mNumStringExpression;
    
    sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
    memcpy(string_expressions, gNodes[node].uValue.sBuffer.mStringExpressions, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

    int string_expression_offsets[STRING_EXPRESSION_MAX];
    memcpy(string_expression_offsets, gNodes[node].uValue.sBuffer.mStringExpressionOffsets, sizeof(int)*STRING_EXPRESSION_MAX);

    int i;

    for(i=0; i<num_string_expression; i++) {
        sNodeBlock* node_block = string_expressions[i];
        if(!compile_block_with_result(node_block, info)) {
            return FALSE;
        }


        if(info->type == NULL) {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(info->type == NULL) {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLClass* klass = info->type->mClass;

        if(!type_identify_with_class_name(info->type, "String")) 
        {
            boxing_to_lapper_class(&info->type, info);

            klass = info->type->mClass;

            sNodeType* result_type = NULL;
            sNodeType* result_method_generics_types = NULL;
            int method_index = search_for_method(klass, "toString", NULL, 0, FALSE, klass->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

            if(method_index == -1) {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);

            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code, method_index, info->no_output);

            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num--;
            info->stack_num++;

            info->type = result_type;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_BUFFER, info->no_output);
    append_buffer_to_constant_pool_and_code(info->constant, info->code, buf, size, info->no_output);
    append_int_value_to_code(info->code, size, info->no_output);

    append_int_value_to_code(info->code, num_string_expression, info->no_output);
    for(i=0; i<num_string_expression; i++) {
        append_int_value_to_code(info->code, string_expression_offsets[i], info->no_output);
    }

    info->stack_num++;
    info->stack_num -= num_string_expression;

    info->type = create_node_type_with_class_name("Buffer");

    return TRUE;
}

unsigned int sNodeTree_create_path_value(MANAGED char* value, int len, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypePath;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sString.mString = MANAGED value;

    int i;
    for(i=0; i<num_string_expression; i++) {
        gNodes[node].uValue.sString.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sString.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sString.mNumStringExpression = num_string_expression;

    return node;
}

BOOL compile_path_value(unsigned int node, sCompileInfo* info)
{
    char* buf = gNodes[node].uValue.sString.mString;

    int num_string_expression = gNodes[node].uValue.sString.mNumStringExpression;
    
    sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
    memcpy(string_expressions, gNodes[node].uValue.sString.mStringExpressions, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

    int string_expression_offsets[STRING_EXPRESSION_MAX];
    memcpy(string_expression_offsets, gNodes[node].uValue.sString.mStringExpressionOffsets, sizeof(int)*STRING_EXPRESSION_MAX);

    int i;

    for(i=0; i<num_string_expression; i++) {
        sNodeBlock* node_block = string_expressions[i];
        if(!compile_block_with_result(node_block, info)) {
            return FALSE;
        }

        if(info->type == NULL) {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(info->type == NULL) {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLClass* klass = info->type->mClass;

        if(!type_identify_with_class_name(info->type, "String")) 
        {
            boxing_to_lapper_class(&info->type, info);

            klass = info->type->mClass;

            sNodeType* result_type = NULL;
            sNodeType* result_method_generics_types = NULL;
            int method_index = search_for_method(klass, "toString", NULL, 0, FALSE, klass->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

            if(method_index == -1) {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);


            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code, method_index, info->no_output);

            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num--;
            info->stack_num++;

            info->type = result_type;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_PATH, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, buf, info->no_output);

    append_int_value_to_code(info->code, num_string_expression, info->no_output);
    for(i=0; i<num_string_expression; i++) {
        append_int_value_to_code(info->code, string_expression_offsets[i], info->no_output);
    }

    info->stack_num++;
    info->stack_num -= num_string_expression;

    info->type = create_node_type_with_class_name("Path");

    return TRUE;
}

unsigned int sNodeTree_create_get_address(unsigned int rnode, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGetAddress;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
            compile_err_msg(info, "undeclared variable %s(7)", gNodes[lnode].uValue.mVarName);
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
            compile_err_msg(info, "no type for loading field address");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLClass* klass = info->type->mClass;
        char field_name[VAR_NAME_MAX];
        xstrncpy(field_name, gNodes[lnode].uValue.mVarName, VAR_NAME_MAX);

        int field_index = search_for_field(klass, field_name);

        if(field_index == -1) {
            compile_err_msg(info, "There is no field(%s) in this class(%s)(4)", field_name, CLASS_NAME(klass));
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
        char field_name[VAR_NAME_MAX];
        xstrncpy(field_name, gNodes[lnode].uValue.sClassField.mVarName, VAR_NAME_MAX);

        int field_index = search_for_class_field(klass, field_name);

        if(field_index == -1) {
            compile_err_msg(info, "There is no field(%s) in this class(%s)(5)", field_name, CLASS_NAME(klass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLField* field = klass->mClassFields + field_index;

        append_opecode_to_code(info->code, OP_LOAD_CLASS_FIELD_ADDRESS, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, field_index, info->no_output);

        info->stack_num++;

        info->type = create_node_type_with_class_name("pointer");
    }
    else {
        compile_err_msg(info, "Require variable name for getting address");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
    }

    return TRUE;
}

unsigned int sNodeTree_create_array_value(int num_elements, unsigned int array_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeArrayValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    unsigned int elements[ARRAY_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sArrayValue.mArrayElements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in array value");
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
            compile_err_msg(info, "Invalid element type. Left type is %s. Right type is %s", CLASS_NAME(element_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    append_opecode_to_code(info->code, OP_CREATE_ARRAY, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, element_type->mClass);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = element_type;
    info->type->mArray = TRUE;

    return TRUE;
}

unsigned int sNodeTree_create_carray_value(int num_elements, unsigned int array_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCArrayValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    unsigned int elements[ARRAY_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sArrayValue.mArrayElements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in array value");
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

    sNodeType* array_type = create_node_type_with_class_name("Array");
    array_type->mNumGenericsTypes = 1;
    if(generics_type_is_object) {
        array_type->mGenericsTypes[0] = create_node_type_with_class_name("Object");
    }
    else {
        array_type->mGenericsTypes[0] = element_type;
    }

    append_opecode_to_code(info->code, OP_CREATE_CARRAY, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, element_type->mClass);

    append_type_name_to_constant_pool_and_code(info, array_type);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = array_type;

    return TRUE;
}

unsigned int sNodeTree_create_equalable_carray_value(int num_elements, unsigned int array_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualableCArrayValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements, array_elements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;

    return node;
}

static BOOL compile_equalable_carray_value(unsigned int node, sCompileInfo* info)
{
    unsigned int elements[ARRAY_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sArrayValue.mArrayElements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in array value");
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

    /// check implemeted interface ///
    sCLClass* iequalable = get_class("IEqualable");
    if(!check_implemented_methods_for_interface(iequalable, element_type->mClass)) {
        compile_err_msg(info, "Require IEqualable implemented for array element type(%s).", CLASS_NAME(element_type->mClass));
        info->err_num++;
    }

    sNodeType* array_type = create_node_type_with_class_name("EqualableArray");
    array_type->mNumGenericsTypes = 1;
    if(generics_type_is_object) {
        array_type->mGenericsTypes[0] = create_node_type_with_class_name("Object");
    }
    else {
        array_type->mGenericsTypes[0] = element_type;
    }

    append_opecode_to_code(info->code, OP_CREATE_EQUALABLE_CARRAY, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, element_type->mClass);

    append_type_name_to_constant_pool_and_code(info, array_type);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = array_type;

    return TRUE;
}

unsigned int sNodeTree_create_sortable_carray_value(int num_elements, unsigned int array_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSortableCArrayValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements, array_elements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;

    return node;
}

static BOOL compile_sortable_carray_value(unsigned int node, sCompileInfo* info)
{
    unsigned int elements[ARRAY_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sArrayValue.mArrayElements, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in array value");
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

    /// check implemeted interface ///
    sCLClass* isortable = get_class("ISortable");
    if(!check_implemented_methods_for_interface(isortable, element_type->mClass)) {
        compile_err_msg(info, "Require IEqualable implemented for array element type(%s).", CLASS_NAME(element_type->mClass));
        info->err_num++;
    }

    sNodeType* array_type = create_node_type_with_class_name("SortableArray");
    array_type->mNumGenericsTypes = 1;
    if(generics_type_is_object) {
        array_type->mGenericsTypes[0] = create_node_type_with_class_name("Object");
    }
    else {
        array_type->mGenericsTypes[0] = element_type;
    }

    append_opecode_to_code(info->code, OP_CREATE_SORTABLE_CARRAY, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, element_type->mClass);

    append_type_name_to_constant_pool_and_code(info, array_type);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = array_type;

    return TRUE;
}

unsigned int sNodeTree_create_hash_value(int num_elements, unsigned int hash_keys[], unsigned int hash_items[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeHashValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sHashValue.mHashKeys, hash_keys, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    memcpy(gNodes[node].uValue.sHashValue.mHashItems, hash_items, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sHashValue.mNumHashElements = num_elements;

    return node;
}

unsigned int sNodeTree_create_list_value(int num_elements, unsigned int list_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeListValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    unsigned int elements[LIST_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sListValue.mListElements, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sListValue.mNumListElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in list value");
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
            compile_err_msg(info, "Invalid element type. Left type is %s. Right type is %s", CLASS_NAME(element_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    sNodeType* list_type = create_node_type_with_class_name("List");
    list_type->mNumGenericsTypes = 1;
    list_type->mGenericsTypes[0] = element_type;

    append_opecode_to_code(info->code, OP_CREATE_LIST, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, list_type);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = list_type;

    return TRUE;
}

unsigned int sNodeTree_create_sortable_list_value(int num_elements, unsigned int list_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSortableListValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sListValue.mListElements, list_elements, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sListValue.mNumListElements = num_elements;

    return node;
}

BOOL compile_sortable_list_value(unsigned int node, sCompileInfo* info)
{
    unsigned int elements[LIST_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sListValue.mListElements, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sListValue.mNumListElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in list value");
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
            compile_err_msg(info, "Invalid element type. Left type is %s. Right type is %s", CLASS_NAME(element_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    /// check implemeted interface ///
    sCLClass* isortable = get_class("ISortable");
    if(!check_implemented_methods_for_interface(isortable, element_type->mClass)) {
        compile_err_msg(info, "Require ISortable implemented for list element type(%s).", CLASS_NAME(element_type->mClass));
        info->err_num++;
    }

    sNodeType* list_type = create_node_type_with_class_name("SortableList");
    list_type->mNumGenericsTypes = 1;
    list_type->mGenericsTypes[0] = element_type;

    append_opecode_to_code(info->code, OP_CREATE_SORTALBE_LIST, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, list_type);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = list_type;

    return TRUE;
}

unsigned int sNodeTree_create_equalable_list_value(int num_elements, unsigned int list_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualableListValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sListValue.mListElements, list_elements, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sListValue.mNumListElements = num_elements;

    return node;
}

BOOL compile_equalable_list_value(unsigned int node, sCompileInfo* info)
{
    unsigned int elements[LIST_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sListValue.mListElements, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sListValue.mNumListElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in list value");
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
            compile_err_msg(info, "Invalid element type. Left type is %s. Right type is %s", CLASS_NAME(element_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    /// check implemeted interface ///
    sCLClass* iequalable = get_class("IEqualable");
    if(!check_implemented_methods_for_interface(iequalable, element_type->mClass)) {
        compile_err_msg(info, "Require IEqualable implemented for list element type(%s).", CLASS_NAME(element_type->mClass));
        info->err_num++;
    }

    sNodeType* list_type = create_node_type_with_class_name("EqualableList");
    list_type->mNumGenericsTypes = 1;
    list_type->mGenericsTypes[0] = element_type;

    append_opecode_to_code(info->code, OP_CREATE_EQUALABLE_LIST, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, list_type);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = list_type;

    return TRUE;
}

unsigned int sNodeTree_create_tuple_value(int num_elements, unsigned int tuple_elements[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTupleValue;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    unsigned int elements[TUPLE_VALUE_ELEMENT_MAX];
    memcpy(elements, gNodes[node].uValue.sTupleValue.mTupleElements, sizeof(unsigned int)*TUPLE_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sTupleValue.mNumTupleElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in tuple value");
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

    char class_name[CLASS_NAME_MAX+1];

    snprintf(class_name, CLASS_NAME_MAX, "Tuple%d", num_elements);

    sNodeType* tuple_type = create_node_type_with_class_name(class_name);
    tuple_type->mNumGenericsTypes = num_elements;
    for(i=0; i<num_elements; i++) {
        tuple_type->mGenericsTypes[i] = element_types[i];
    }

    append_opecode_to_code(info->code, OP_CREATE_TUPLE, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_type_name_to_constant_pool_and_code(info, tuple_type);

    info->stack_num-= num_elements;
    info->stack_num++;

    info->type = tuple_type;

    return TRUE;
}

unsigned int sNodeTree_create_multiple_asignment(int num_elements, unsigned int tuple_elements[], int right_value, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMultipleAsignment;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right_value;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    memcpy(gNodes[node].uValue.sTupleValue.mTupleElements, tuple_elements, sizeof(unsigned int)*TUPLE_VALUE_ELEMENT_MAX);
    gNodes[node].uValue.sTupleValue.mNumTupleElements = num_elements;

    return node;
}

static BOOL compile_multiple_asignment(unsigned int node, sCompileInfo* info)
{
    unsigned int* left_element_nodes = gNodes[node].uValue.sTupleValue.mTupleElements;
    int num_left_elements = gNodes[node].uValue.sTupleValue.mNumTupleElements;

    if(num_left_elements == 0) {
        compile_err_msg(info, "require element for left value");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile right value ///
    unsigned int right_value = gNodes[node].mRight;

    if(!compile(right_value, info)) {
        return FALSE;
    }

    sNodeType* right_value_type = info->type;

    if(right_value_type->mNumGenericsTypes != num_left_elements) {
        compile_err_msg(info, "right type is invalid. type error");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// Determine type for multiple assignment varialbles or check type ///
    int i;
    for(i=0; i<num_left_elements; i++) {
        unsigned int left_element_node = left_element_nodes[i];

        char* var_name = gNodes[left_element_node].uValue.mVarName;

        sNodeType* right_element_type = right_value_type->mGenericsTypes[i];

        if(gNodes[left_element_node].mNodeType == kNodeTypeLoadVariable) {
            sVar* left_element_var = get_variable_from_table(info->lv_table, var_name);

            if(left_element_var->mType == NULL) {
                left_element_var->mType = right_element_type;
            }
            else {
                sNodeType* left_element_type = left_element_var->mType;

                sCLClass* left_class = left_element_type->mClass;

                if(left_class->mFlags & CLASS_FLAGS_PRIMITIVE) {
                    if(left_class->mBoxingClass != NULL) {
                        left_element_type = create_node_type_with_class_pointer(left_class->mBoxingClass);
                    }
                    else {
                        parser_err_msg(info->pinfo, "primitive class without boxing %s", CLASS_NAME(left_class));
                        info->err_num++;
                    }
                }

                if(!substitution_posibility(left_element_type, right_element_type, NULL, NULL, NULL, NULL)) 
                {
                    compile_err_msg(info, "right element type is invalid. type error (%s,%s)", CLASS_NAME(left_element_var->mType->mClass), CLASS_NAME(right_element_type->mClass));
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }
        }
/*
        else if(gNodes[left_element_node].mNodeType == kNodeTypeLoadField) {
        }
        else if(gNodes[left_element_node].mNodeType == kNodeTypeLoadClassField) {
        }
*/
    }

    append_opecode_to_code(info->code, OP_SPLIT_TUPLE, info->no_output);
    append_int_value_to_code(info->code, right_value_type->mNumGenericsTypes, info->no_output);
    info->stack_num --;
    info->stack_num += right_value_type->mNumGenericsTypes;

    for(i=0; i<right_value_type->mNumGenericsTypes; i++) {
        unsigned int left_element_node = left_element_nodes[right_value_type->mNumGenericsTypes-i-1];

        sNodeType* right_element_type = right_value_type->mGenericsTypes[i];

        char* var_name = gNodes[left_element_node].uValue.mVarName;
        
        sVar* left_element_var 
            = get_variable_from_table(info->lv_table, var_name);
            
        sNodeType* left_element_type = left_element_var->mType;

        sCLClass* left_class = left_element_type->mClass;
        
        if(left_class->mFlags & CLASS_FLAGS_PRIMITIVE) {
            if(unboxig_posibility(right_element_type->mClass)) {
                if(!unboxing_to_primitive_type(&right_element_type, info)) {
                    return FALSE;
                }
            }
        }

        int var_index = get_variable_index(info->lv_table, var_name);

        MASSERT(var_index != -1);

        append_opecode_to_code(info->code, OP_STORE, info->no_output);
        append_int_value_to_code(info->code, var_index, info->no_output);

        append_opecode_to_code(info->code, OP_POP, info->no_output);
        info->stack_num --;
    }

    append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
    info->stack_num++;

    info->type = create_node_type_with_class_name("Null");

    return TRUE;
}

BOOL compile_hash_value(unsigned int node, sCompileInfo* info)
{
    unsigned int keys[HASH_VALUE_ELEMENT_MAX];
    memcpy(keys, gNodes[node].uValue.sHashValue.mHashKeys, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    unsigned int items[HASH_VALUE_ELEMENT_MAX];
    memcpy(items, gNodes[node].uValue.sHashValue.mHashItems, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    int num_elements = gNodes[node].uValue.sHashValue.mNumHashElements;

    if(num_elements == 0) {
        compile_err_msg(info, "require element in hash value");
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
            compile_err_msg(info, "Invalid key type. Left type is %s. Right type is %s", CLASS_NAME(key_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }

        unsigned int item = items[i];

        if(!compile(item, info)) {
            return FALSE;
        }

        boxing_to_lapper_class(&info->type, info);

        if(!type_identify(item_type, info->type)) {
            compile_err_msg(info, "Invalid item type. Left type is %s. Right type is %s", CLASS_NAME(item_type->mClass), CLASS_NAME(info->type->mClass));
            info->err_num++;
        }
    }

    sNodeType* hash_type = create_node_type_with_class_name("Hash");
    hash_type->mNumGenericsTypes = 2;
    hash_type->mGenericsTypes[0] = key_type;
    hash_type->mGenericsTypes[1] = item_type;

    append_opecode_to_code(info->code, OP_CREATE_HASH, info->no_output);
    append_int_value_to_code(info->code, num_elements, info->no_output);
    append_class_name_to_constant_pool_and_code(info, key_type->mClass);
    append_class_name_to_constant_pool_and_code(info, item_type->mClass);
    append_type_name_to_constant_pool_and_code(info, hash_type);

    info->stack_num-= num_elements * 2;
    info->stack_num++;

    info->type = hash_type;

    return TRUE;
}

unsigned int sNodeTree_create_block_object(sParserParam* params, int num_params, sNodeType* result_type, MANAGED sNodeBlock* node_block, BOOL lambda, sParserInfo* info, BOOL omit_result_type, BOOL omit_params, sVarTable* old_table)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBlockObject;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    gNodes[node].uValue.sBlockObject.mOmitResultType = omit_result_type;
    gNodes[node].uValue.sBlockObject.mOmitParams = omit_params;
    gNodes[node].uValue.sBlockObject.mOldTable = old_table;

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
    BOOL omit_result_type = gNodes[node].uValue.sBlockObject.mOmitResultType;
    BOOL lambda = gNodes[node].uValue.sBlockObject.mLambda;
    sVarTable* old_table = gNodes[node].uValue.sBlockObject.mOldTable;

    /// compile block ///
    sByteCode codes;
    sConst constant;

    sByteCode_init(&codes);
    sConst_init(&constant);

    sByteCode* codes_before = info->code;
    sConst* constant_before = info->constant;

    info->code = &codes;
    info->constant = &constant;

    BOOL in_block_before = info->in_block;
    info->in_block = TRUE;

    sNodeType* block_result_type_before = info->block_result_type;
    info->block_result_type = result_type;

    sNodeType* return_type_before = info->return_type;
    info->return_type = NULL;

    BOOL omit_block_result_type_before = info->omit_block_result_type;
    info->omit_block_result_type = omit_result_type;

    if(!compile_block(node_block, info)) {
        sByteCode_free(&codes);
        sConst_free(&constant);
        info->code = codes_before;
        info->constant = constant_before;
        info->block_result_type = block_result_type_before;
        info->in_block = in_block_before;
        info->omit_block_result_type = omit_block_result_type_before;
        info->return_type = return_type_before;
        return FALSE;
    }

    sNodeType* return_type = info->return_type;

    info->return_type2 = info->return_type;
        
    info->code = codes_before;
    info->constant = constant_before;
    info->block_result_type = block_result_type_before;
    info->in_block = in_block_before;
    info->omit_block_result_type = omit_block_result_type_before;
    info->return_type = return_type_before;

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
        int parent_var_num = get_parent_var_num_of_sum(node_block->mLVTable);
        append_int_value_to_code(info->code, parent_var_num, info->no_output);
        append_int_value_to_code(info->code, FALSE, info->no_output);
    }

    info->stack_num++;

    /// make info->type ///
    if(!node_block->mUnClosedBlock) { // for interpreter completion
        info->type = create_node_type_with_class_name("lambda");

        sNodeBlockType* node_block_type = alloc_node_block_type();

        node_block_type->mNumParams = num_params;
        if(omit_result_type) 
        {
            if(return_type == NULL) {
                node_block_type->mResultType = create_node_type_with_class_name("Null");
            }
            else {
                node_block_type->mResultType = return_type;
            }
        }
        else {
            node_block_type->mResultType = result_type;
        }
        for(i=0; i<num_params; i++) {
            node_block_type->mParams[i] = params[i]->mType;
        }

        node_block_type->mLambda = lambda;

        info->type->mBlockType = node_block_type;
    }

    sByteCode_free(&codes);
    sConst_free(&constant);

    info->pinfo->exist_block_object_err = node_block->mUnClosedBlock; // for interpreter completion

    return TRUE;
}

unsigned int sNodeTree_create_function(char* fun_name, sParserParam* params, int num_params, sNodeType* result_type, MANAGED sNodeBlock* node_block, BOOL lambda, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunction;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunction.mParams[i] = params[i]; // copy struct
    }

    gNodes[node].uValue.sFunction.mNumParams = num_params;
    gNodes[node].uValue.sFunction.mResultType = result_type;
    gNodes[node].uValue.sFunction.mBlockObjectCode = MANAGED node_block;
    gNodes[node].uValue.sFunction.mLambda = lambda;

    return node;
}

BOOL compile_function(unsigned int node, sCompileInfo* info)
{
    /// rename variables ///
    int num_params = gNodes[node].uValue.sFunction.mNumParams;
    sParserParam* params[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunction.mParams + i;
    }

    sNodeType* result_type = gNodes[node].uValue.sFunction.mResultType;
    sNodeBlock* node_block = gNodes[node].uValue.sFunction.mBlockObjectCode;
    BOOL lambda = gNodes[node].uValue.sFunction.mLambda;

    /// make info->type ///
    sNodeType* lambda_type = create_node_type_with_class_name("lambda");

    sNodeBlockType* node_block_type = alloc_node_block_type();

    node_block_type->mNumParams = num_params;
    node_block_type->mResultType = result_type;
    for(i=0; i<num_params; i++) {
        node_block_type->mParams[i] = params[i]->mType;
    }

    node_block_type->mLambda = lambda;

    lambda_type->mBlockType = node_block_type;

    /// store local variable ///
    sVar* var = get_variable_from_table(info->lv_table, gNodes[node].uValue.sFunction.mName);

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable %s(8)", gNodes[node].uValue.sFunction.mName);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* right_type = lambda_type;

    /// type inference ///
    if(gNodes[node].mType == NULL) {
        gNodes[node].mType = right_type;
    }
    if(var->mType == NULL) {
        var->mType = right_type;
    }

    /// compile block ///
    sByteCode codes;
    sConst constant;

    sByteCode_init(&codes);
    sConst_init(&constant);

    sByteCode* codes_before = info->code;
    sConst* constant_before = info->constant;

    info->code = &codes;
    info->constant = &constant;

    BOOL in_block_before = info->in_block;
    info->in_block = TRUE;

    sNodeType* block_result_type_before = info->block_result_type;
    info->block_result_type = result_type;

    if(!compile_block(node_block, info)) {
        sByteCode_free(&codes);
        sConst_free(&constant);
        info->code = codes_before;
        info->constant = constant_before;
        info->block_result_type = block_result_type_before;
        info->in_block = in_block_before;
        return FALSE;
    }

    info->block_result_type = block_result_type_before;
    info->in_block = in_block_before;

    sNodeType* expresson_type_in_block = info->type;

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
        int parent_var_num = get_parent_var_num_of_sum(node_block->mLVTable);
        append_int_value_to_code(info->code, parent_var_num, info->no_output);
        append_int_value_to_code(info->code, FALSE, info->no_output);
    }

    info->stack_num++;

    sByteCode_free(&codes);
    sConst_free(&constant);

    /// type check ///
    sNodeType* left_type = var->mType;
    if(gNodes[node].mType->mClass == NULL || left_type == NULL || right_type == NULL || left_type->mClass == NULL || right_type->mClass == NULL) 
    {
        compile_err_msg(info, "invalid type(2)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* left_type2;
    solve_generics_for_variable(left_type, &left_type2, info->pinfo);

    cast_right_type_to_left_type(left_type2, &right_type, info);

    if(!substitution_posibility(left_type2, right_type, NULL, NULL, NULL, NULL)) {
        compile_err_msg(info, "The different type between left type and right type(1). Left type is %s. Right type is %s.", CLASS_NAME(left_type2->mClass), CLASS_NAME(right_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int var_index = get_variable_index(info->lv_table, gNodes[node].uValue.sFunction.mName);

    MASSERT(var_index != -1);

    append_opecode_to_code(info->code, OP_STORE, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);

    if(info->pinfo->err_num == 0) { // for interpreter completion
        info->type = left_type2;
    }
    else {
        info->type = expresson_type_in_block;
    }

    return TRUE;
}


unsigned int sNodeTree_create_normal_block(MANAGED sNodeBlock* node_block, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNormalBlock;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    if(!compile_block_with_result(node_block, info)) {
        return FALSE;
    }

    return TRUE;
}

unsigned int sNodeTree_create_block_call(unsigned int block, int num_params, unsigned int params[], sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBlockCall;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "no type for block call");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* var_type = info->type;

    if(var_type == NULL || !type_identify_with_class_name(var_type, "lambda")) {
        compile_err_msg(info, "No block type, clover2 can call block object only");
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
        compile_err_msg(info, "Type error for block call");
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

            sNodeType* method_generics_types;
            if(info->pinfo->klass) {
                method_generics_types = get_methocs_generics_type(info->pinfo);
            }
            else {
                method_generics_types = NULL;
            }

            if(!substitution_posibility(left_type, right_type, generics_types, NULL, method_generics_types, method_generics_types)) {
                compile_err_msg(info, "Type error for block call");
                info->err_num++;
            }
        }
        else {
            if(!substitution_posibility(left_type, right_type, NULL, NULL, NULL, NULL)) {
                compile_err_msg(info, "Type error for block call");
                info->err_num++;
            }
        }
    }

    /// invoke block ///
    sNodeBlockType* block_type = var_type->mBlockType;

    append_opecode_to_code(info->code, OP_INVOKE_BLOCK, info->no_output);
    append_int_value_to_code(info->code, num_params, info->no_output);

    sNodeType* result_type2 = block_type->mResultType;
    int size = get_var_size(result_type2);
    append_int_value_to_code(info->code, size, info->no_output);

    info->stack_num-=(num_params+1);
    info->stack_num++;

    info->type = block_type->mResultType;

    return TRUE;
}

unsigned int sNodeTree_create_regex(MANAGED char* regex_str, BOOL global, BOOL ignore_case, BOOL multiline, BOOL extended, BOOL dotall, BOOL anchored, BOOL dollar_endonly, BOOL ungreedy, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRegex;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
    int i;
    for(i=0; i<num_string_expression; i++) {
        gNodes[node].uValue.sRegex.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sRegex.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sRegex.mNumStringExpression = num_string_expression;

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

    int num_string_expression = gNodes[node].uValue.sRegex.mNumStringExpression;
    
    sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
    memcpy(string_expressions, gNodes[node].uValue.sRegex.mStringExpressions, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);
    int string_expression_offsets[STRING_EXPRESSION_MAX];
    memcpy(string_expression_offsets, gNodes[node].uValue.sRegex.mStringExpressionOffsets, sizeof(int)*STRING_EXPRESSION_MAX);

    int i;

    for(i=0; i<num_string_expression; i++) {
        sNodeBlock* node_block = string_expressions[i];
        if(!compile_block_with_result(node_block, info)) {
            return FALSE;
        }

        if(info->type == NULL) {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(info->type == NULL) {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sCLClass* klass = info->type->mClass;

        if(!type_identify_with_class_name(info->type, "String")) 
        {
            boxing_to_lapper_class(&info->type, info);

            klass = info->type->mClass;

            sNodeType* result_type = NULL;
            sNodeType* result_method_generics_types = NULL;
            int method_index = search_for_method(klass, "toString", NULL, 0, FALSE, klass->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

            if(method_index == -1) {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
            append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);


            append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);

            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code, method_index, info->no_output);

            int size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);

            info->stack_num--;
            info->stack_num++;

            info->type = result_type;
        }
    }

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

    append_int_value_to_code(info->code, num_string_expression, info->no_output);
    for(i=0; i<num_string_expression; i++) {
        append_int_value_to_code(info->code, string_expression_offsets[i], info->no_output);
    }

    info->stack_num++;
    info->stack_num -= num_string_expression;

    info->type = create_node_type_with_class_name("regex");

    return TRUE;
}


unsigned int sNodeTree_create_implements(unsigned int lnode, char* interface_name, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeImplements;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

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
        compile_err_msg(info, "no type for implements");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sCLClass* klass = info->type->mClass;

    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        compile_err_msg(info, "Primitive value doesn't have class info");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->stack_num--;

    append_opecode_to_code(info->code, OP_IMPLEMENTS, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, interface_name, info->no_output);

    info->type = create_node_type_with_class_name("bool");
    info->stack_num++;

    return TRUE;
}

unsigned int sNodeTree_create_inherit_call(int num_params, unsigned int params[], int method_index, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeInheritCall;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    gNodes[node].uValue.sInheritCall.mNumParams = num_params;

    int i;
    for(i=0; i<gNodes[node].uValue.sInheritCall.mNumParams; i++) {
        gNodes[node].uValue.sInheritCall.mParams[i] = params[i];
    }

    gNodes[node].uValue.sInheritCall.mMethodIndex = method_index;

    return node;
}

static BOOL compile_inherit_call(unsigned int node, sCompileInfo* info)
{
    sCLClass* klass = info->pinfo->klass;
    sCLMethod* method = info->method;
    char* method_name = METHOD_NAME2(klass, method);

    if(method == NULL) {
        compile_err_msg(info, "inherit call must be in method");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int method_index = gNodes[node].uValue.sInheritCall.mMethodIndex;
    BOOL class_method = method->mFlags & METHOD_FLAGS_CLASS_METHOD;

    /// load self if the method is none class method ///
    if(!class_method) {
        append_opecode_to_code(info->code, OP_LOAD, info->no_output);
        append_int_value_to_code(info->code, 0, info->no_output);     // self
        append_int_value_to_code(info->code, 4, info->no_output);

        info->stack_num++;
    }

    /// compile params ///
    info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

    sNodeType* param_types[PARAMS_MAX];
    int num_params = gNodes[node].uValue.sInheritCall.mNumParams;

    int i;
    for(i=0; i<num_params; i++) {
        int node2 = gNodes[node].uValue.sInheritCall.mParams[i];
        if(!compile(node2, info)) {
            return FALSE;
        }

        param_types[i] = info->type;
    }

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        sNodeType* generics_types;
        if(info->pinfo->klass) {
            generics_types = get_generics_type_of_inner_class(info->pinfo);
        }
        else {
            generics_types = NULL;
        }

        sNodeType* right_method_generics_types = get_methocs_generics_type(info->pinfo);

        /// search for the method ///
        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index2 = search_for_method(klass, method_name, param_types, num_params, class_method, method_index-1, generics_types, NULL, right_method_generics_types, &result_type, FALSE, FALSE, &result_method_generics_types);

        if(method_index2 == -1) {
            compile_err_msg(info, "method not found(30)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, TRUE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index2, info->no_output);

        int size = get_var_size(result_type);
        append_int_value_to_code(info->code, size, info->no_output);

        if(!class_method) {
            info->stack_num-=num_params+1;
        }
        else {
            info->stack_num-=num_params;
        }

        info->stack_num++;

        info->type = result_type;
    }
    
    return TRUE;
}

unsigned int sNodeTree_create_range(unsigned int head, unsigned int tail, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRange;

    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = head;
    gNodes[node].mRight = tail;
    gNodes[node].mMiddle = 0;

    gNodes[node].mType = NULL;

    return node;
}

static BOOL compile_range(unsigned int node, sCompileInfo* info)
{
    sCLClass* klass = get_class("Range");

    sNodeType* param_types[PARAMS_MAX];
    int num_params = 2;

    MASSERT(klass != NULL);

    /// get type of value without generating code ///
    BOOL no_output_before = info->no_output;
    info->no_output = TRUE;
    int stack_num_before = info->stack_num;

    info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

    int head_node = gNodes[node].mLeft;
    if(!compile(head_node, info)) {
        return FALSE;
    }

    /// Do boxing if the class of a param is primitive ///
    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        boxing_to_lapper_class(&info->type, info);
    }

    sNodeType* head_type = info->type;

    info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

    int tail_node = gNodes[node].mRight;
    if(!compile(tail_node, info)) {
        return FALSE;
    }

    /// Do boxing if the class of a param is primitive ///
    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        boxing_to_lapper_class(&info->type, info);
    }

    sNodeType* tail_type = info->type;

    info->no_output = no_output_before;
    info->stack_num = stack_num_before;

    if(!type_identify(head_type, tail_type)) {
        compile_err_msg(info, "Range value type is the diffrent.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// create range object ///
    sNodeType* node_type = create_node_type_with_class_name("Range");
    node_type->mNumGenericsTypes = 1;
    node_type->mGenericsTypes[0] = head_type;

    append_opecode_to_code(info->code, OP_NEW, info->no_output);
    append_str_to_constant_pool_and_code(info->constant, info->code, "Range", info->no_output);
    append_type_name_to_constant_pool_and_code(info, node_type);
    append_int_value_to_code(info->code, 0, info->no_output);

    info->stack_num++;

    /// compile head ///
    info->pinfo->exist_block_object_err = FALSE; // for interpreter completion

    if(!compile(head_node, info)) {
        return FALSE;
    }

    /// Do boxing if the class of a param is primitive ///
    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        boxing_to_lapper_class(&info->type, info);
    }

    param_types[0] = info->type;

    if(!compile(tail_node, info)) {
        return FALSE;
    }

    /// Do boxing if the class of a param is primitive ///
    if(info->type->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        boxing_to_lapper_class(&info->type, info);
    }

    param_types[1] = info->type;

    if(!info->pinfo->exist_block_object_err) { // for interpreter completion
        char* method_name = "initialize";

        sNodeType* generics_types2 = node_type;

        sNodeType* result_type;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(klass, method_name, param_types, num_params, FALSE, klass->mNumMethods-1, generics_types2, generics_types2, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);
        if(method_index == -1) {
            compile_err_msg(info, "method not found(30)");
            info->err_num++;

            err_msg_for_method_not_found(klass, method_name, param_types, num_params, FALSE, info);

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        append_opecode_to_code(info->code, OP_MARK_SOURCE_CODE_POSITION2, info->no_output);
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        append_opecode_to_code(info->code, OP_INVOKE_METHOD, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, method_index, info->no_output);

        int size = get_var_size(node_type);
        append_int_value_to_code(info->code, size, info->no_output);

        info->stack_num-=num_params+1;
        info->stack_num++;

        info->type = node_type;
    }
    
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

        case kNodeTypeAndAnd:
            puts("and and operator");
            break;

        case kNodeTypeOrOr:
            puts("or or operator");
            break;

        case kNodeTypeByteValue:
            printf("byte value %d\n", gNodes[node].uValue.mByteValue);
            break;

        case kNodeTypeCByteValue:
            printf("cbyte value %d\n", gNodes[node].uValue.mByteValue);
            break;

        case kNodeTypeUByteValue:
            printf("ubyte value %u\n", gNodes[node].uValue.mUByteValue);
            break;

        case kNodeTypeCUByteValue:
            printf("ubyte value %u\n", gNodes[node].uValue.mUByteValue);
            break;

        case kNodeTypeShortValue:
            printf("short value %d\n", gNodes[node].uValue.mShortValue);
            break;

        case kNodeTypeCShortValue:
            printf("short value %d\n", gNodes[node].uValue.mShortValue);
            break;

        case kNodeTypeUShortValue:
            printf("ushort value %u\n", gNodes[node].uValue.mUShortValue);
            break;

        case kNodeTypeCUShortValue:
            printf("ushort value %u\n", gNodes[node].uValue.mUShortValue);
            break;

        case kNodeTypeIntValue:
            printf("int value %d\n", gNodes[node].uValue.mIntValue);
            break;

        case kNodeTypeCIntValue:
            printf("int value %d\n", gNodes[node].uValue.mIntValue);
            break;

        case kNodeTypeUIntValue:
            printf("uint value %u\n", gNodes[node].uValue.mUIntValue);
            break;

        case kNodeTypeCUIntValue:
            printf("uint value %u\n", gNodes[node].uValue.mUIntValue);
            break;

        case kNodeTypeLongValue:
            printf("long value %lld\n", gNodes[node].uValue.mLongValue);
            break;

        case kNodeTypeCLongValue:
            printf("long value %lld\n", gNodes[node].uValue.mLongValue);
            break;

        case kNodeTypeULongValue:
            printf("long value %llu\n", gNodes[node].uValue.mULongValue);
            break;

        case kNodeTypeCULongValue:
            printf("long value %llu\n", gNodes[node].uValue.mULongValue);
            break;

        case kNodeTypeFloatValue:
            printf("float value %f\n", gNodes[node].uValue.mFloatValue);
            break;

        case kNodeTypeDoubleValue:
            printf("double value %lf\n", gNodes[node].uValue.mDoubleValue);
            break;

        case kNodeTypeCFloatValue:
            printf("Float value %f\n", gNodes[node].uValue.mFloatValue);
            break;

        case kNodeTypeCDoubleValue:
            printf("Double value %lf\n", gNodes[node].uValue.mDoubleValue);
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

        case kNodeTypeWhen:
            puts("when expression");
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

        case kNodeTypeWildCard:
            puts("wildcard");
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

        case kNodeTypePath:
            puts("path");
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

        case kNodeTypeEqualableCArrayValue:
            puts("equalable carray value");
            break;

        case kNodeTypeSortableCArrayValue:
            puts("sortable carray value");
            break;

        case kNodeTypeHashValue:
            puts("hash value");
            break;

        case kNodeTypeListValue:
            puts("list value");
            break;

        case kNodeTypeSortableListValue:
            puts("sortable list value");
            break;

        case kNodeTypeEqualableListValue:
            puts("equalable list value");
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

        case kNodeTypeFunction:
            puts("function");
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

        case kNodeTypeInheritCall:
            puts("inherit");
            break;

        case kNodeTypeRange:
            puts("range");
            break;

        case kNodeTypeMultipleAsignment:
            puts("multiple asignment");
            break;
    }
}

BOOL compile(unsigned int node, sCompileInfo* info)
{
    if(node == 0) {
        return TRUE;
    }

    info->sname = gNodes[node].mSName;
    info->sline = gNodes[node].mLine;

    switch(gNodes[node].mNodeType) {
        case kNodeTypeOperand:
            if(!compile_operand(node, info)) {
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

        case kNodeTypeCByteValue:
            if(!compile_cbyte_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUByteValue:
            if(!compile_ubyte_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCUByteValue:
            if(!compile_cubyte_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFloatValue:
            if(!compile_float_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDoubleValue:
            if(!compile_double_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCFloatValue:
            if(!compile_cfloat_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCDoubleValue:
            if(!compile_cdouble_value(node, info)) {
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

        case kNodeTypeCShortValue:
            if(!compile_cshort_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCUShortValue:
            if(!compile_cushort_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIntValue:
            if(!compile_int_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCIntValue:
            if(!compile_cint_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUIntValue:
            if(!compile_uint_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCUIntValue:
            if(!compile_cuint_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLongValue:
            if(!compile_long_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCLongValue:
            if(!compile_clong_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeULongValue:
            if(!compile_ulong_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCULongValue:
            if(!compile_culong_value(node, info)) {
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

        case kNodeTypeWhen:
            if(!compile_when_expression(node, info)) {
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

        case kNodeTypeWildCard:
            if(!compile_wildcard_expression(node, info)) {
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

        case kNodeTypePath:
            if(!compile_path_value(node, info)) {
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

        case kNodeTypeEqualableCArrayValue:
            if(!compile_equalable_carray_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeSortableCArrayValue:
            if(!compile_sortable_carray_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeListValue:
            if(!compile_list_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeEqualableListValue:
            if(!compile_equalable_list_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeSortableListValue:
            if(!compile_sortable_list_value(node, info)) {
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

        case kNodeTypeFunction:
            if(!compile_function(node, info)) {
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

        case kNodeTypeInheritCall:
            if(!compile_inherit_call(node,info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRange:
            if(!compile_range(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMultipleAsignment:
            if(!compile_multiple_asignment(node, info)) {
                return FALSE;
            }
            break;
    }

    return TRUE;
}

BOOL check_node_is_variable(unsigned int node)
{
    return gNodes[node].mNodeType == kNodeTypeLoadVariable;
}

void create_type_name_from_node_type(char* type_name, int type_name_max, sNodeType* node_type)
{
    sCLClass* klass = node_type->mClass;

    xstrncat(type_name, CLASS_NAME(klass), type_name_max);

    if(node_type->mBlockType) {
        sNodeBlockType* node_block_type = node_type->mBlockType;

        xstrncat(type_name, "(", type_name_max);

        if(node_block_type->mNumParams > 0) {
            int i;
            for(i=0; i<node_block_type->mNumParams; i++) {
                create_type_name_from_node_type(type_name, type_name_max, node_block_type->mParams[i]);
                
                if(i != node_block_type->mNumParams-1) {
                    xstrncat(type_name, ",", type_name_max);
                }
            }
        }
        xstrncat(type_name, ")", type_name_max);

        xstrncat(type_name, ":", type_name_max);

        create_type_name_from_node_type(type_name, type_name_max, node_block_type->mResultType);
    }
    if(node_type->mArray) {
        xstrncat(type_name, "[]", type_name_max);
    }
    if(node_type->mNullable) {
        xstrncat(type_name, "?", type_name_max);
    }
    if(node_type->mNumGenericsTypes > 0) {
        xstrncat(type_name, "<", type_name_max);

        int i;
        for(i=0; i<node_type->mNumGenericsTypes; i++) {
            create_type_name_from_node_type(type_name, type_name_max, node_type->mGenericsTypes[i]);

            if(i != node_type->mNumGenericsTypes-1) {
                xstrncat(type_name, ",", type_name_max);
            }
        }

        xstrncat(type_name, ">", type_name_max);
    }
}
