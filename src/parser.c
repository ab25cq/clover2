#include "common.h"

static BOOL expression_substitution(unsigned int* node, sParserInfo* info);
BOOL parse_type_for_new(sNodeType** result_type, unsigned int* array_num, sParserInfo* info);

void parser_err_msg(sParserInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    if(!info->get_type_for_interpreter) {
        fprintf(stderr, "%s %d: %s\n", info->sname, info->sline, msg2);
    }
}

void skip_spaces_and_lf(sParserInfo* info)
{
    while(*info->p == ' ' || *info->p == '\t' || (*info->p == '\n' && (info->sline)++)) {
        info->p++;
    }
}

BOOL parse_word(char* buf, int buf_size, sParserInfo* info, BOOL print_out_err_msg)
{
    buf[0] = 0;

    char* p2 = buf;

    if(isalpha(*info->p)) {
        while(isalnum(*info->p) || *info->p == '_') {
            if(p2 - buf < buf_size-1) {
                *p2++ = *info->p;
                info->p++;
            }
            else {
                parser_err_msg(info, "length of word is too long");
                return FALSE;
            }
        }
    }

    *p2 = 0;
    skip_spaces_and_lf(info);

    if(*info->p == 0 && buf[0] == 0) {
        if(print_out_err_msg) {
            parser_err_msg(info, "require word(alphabet or number). this is the end of source");
        }
        return FALSE;
    }

    if(buf[0] == 0) {
        if(print_out_err_msg) {
            parser_err_msg(info, "require word(alphabet or _ or number). this is (%c)", *info->p);
            info->err_num++;
        }

        if(*info->p == '\n') info->sline++;

        info->p++;
    }

    return TRUE;
}

void expect_next_character_with_one_forward(char* characters, sParserInfo* info)
{
    skip_spaces_and_lf(info);

    BOOL found = FALSE;
    char* p2 = characters;
    while(*p2) {
        if(*info->p == *p2) {
            found = TRUE;
        }
        p2++;
    }

    if(found) {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        parser_err_msg(info, "expected that next character is %s, but it is %c(%d)", characters, *info->p, *info->p);
        info->err_num++;
        info->p++;
        skip_spaces_and_lf(info);
    }
}

BOOL expect_next_character(char* characters, sParserInfo* info)
{
    int sline_top = info->sline;

    char err_characters[128];
    char* perr_characters = err_characters;
    
    BOOL err = FALSE;
    while(1) {
        BOOL found;
        char* p2;

        if(*info->p == '\0') {
            parser_err_msg(info, "clover has expected that next characters are '%s', but it arrived at source end", characters);
            info->err_num++;
            return TRUE;
        }

        found = FALSE;
        p2 = characters;
        while(*p2) {
            if(*info->p == *p2) {
                found = TRUE;
                break;
            }
            else {
                p2++;
            }
        }

        if(found) {
            break;
        }
        else {
            err = TRUE;
            if(perr_characters - err_characters < 127) {
                *perr_characters = *info->p;
                perr_characters++;
            }
            if(*info->p == '\n') { info->sline++; }
            info->p++;
        }
    }

    if(err) {
        *perr_characters = 0;
        parser_err_msg(info, "Clover has expected that next characters are '%s', but there are some characters(%s) before them", characters, err_characters);
        info->err_num++;
        info->p++;
    }

    return TRUE;
}

static BOOL parse_method_params(int* num_params, unsigned int* params, sParserInfo* info)
{
    *num_params = 0;

    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
        }
        else {
            while(1) {
                unsigned int node = 0;
                if(!expression(&node, info)) {
                    return FALSE;
                }

                if(node == 0) {
                    parser_err_msg(info, "require expression");
                    info->err_num++;
                    break;
                }

                params[*num_params] = node;
                (*num_params)++;

                if(*num_params >= PARAMS_MAX) {
                    parser_err_msg(info, "overflow parametor number for method call");
                    return FALSE;
                }

                if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == ')') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else if(*info->p == '\0') {
                    parser_err_msg(info, "unexpected the source end");
                    info->err_num++;
                    break;
                }
                else {
                    parser_err_msg(info, "Clover2 requires , or ) for method call");
                    info->err_num++;
                    break;
                }
            }
        }
    }

    return TRUE;
}

static BOOL get_number(BOOL minus, unsigned int* node, sParserInfo* info)
{
    const int buf_size = 128;
    char buf[128+1];
    char* p2 = buf;

    if(minus) {
        *p2 = '-';
        p2++;
    }

    if(isdigit(*info->p)) {
        while(isdigit(*info->p)) {
            *p2++ = *info->p;
            info->p++;

            if(p2 - buf >= buf_size) {
                parser_err_msg(info, "overflow node of number");
                return FALSE;
            }
        }
        *p2 = 0;
        skip_spaces_and_lf(info);

        if(*info->p == '.' && isdigit(*(info->p+1))) {
            info->p++;
            *p2++ = '.';

            if(p2 - buf >= buf_size) {
                parser_err_msg(info, "overflow node of number");
                return FALSE;
            }

            while(isdigit(*info->p)) {
                *p2++ = *info->p;
                info->p++;

                if(p2 - buf >= buf_size) {
                    parser_err_msg(info, "overflow node of number");
                    return FALSE;
                }
            }
            *p2 = 0;

            if(*info->p == 'f' || *info->p == 'F') {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_float_value(atof(buf), 0, 0, 0);
            }
            else {
                *node = sNodeTree_create_double_value(strtod(buf, NULL), 0, 0, 0);
            }

            skip_spaces_and_lf(info);
        }
        else if(*info->p == 'b') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_byte_value(atoi(buf), 0, 0, 0);
        }
        else if(*info->p == 'u' && *(info->p+1) == 'b') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_ubyte_value(atoi(buf), 0, 0, 0);
        }
        else if(*info->p == 'l' || *info->p == 'L') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_long_value(atol(buf), 0, 0, 0);
        }
        else {
            *node = sNodeTree_create_int_value(atoi(buf), 0, 0, 0);
        }
    }
    else {
        parser_err_msg(info, "require digits after + or -");
        info->err_num++;

        *node = 0;
    }

    return TRUE;
}

static BOOL get_hex_number(unsigned int* node, sParserInfo* info)
{
    int buf_size = 128;
    char buf[128+1];
    char* p = buf;

    *p++ = '0';
    *p++ = 'x';

    while((*info->p >= '0' && *info->p <= '9') || (*info->p >= 'a' && *info->p <= 'f') || (*info->p >= 'A' && *info->p <= 'F')) 
    {
        *p++ = *info->p;
        info->p++;

        if(p - buf >= buf_size-1) {
            parser_err_msg(info, "overflow node of number");
            return FALSE;
        }
    }
    *p = 0;
    skip_spaces_and_lf(info);

    unsigned long value = strtol(buf, NULL, 0);

    *node = sNodeTree_create_int_value((int)value, 0, 0, 0);

    return TRUE;
}

static BOOL get_oct_number(unsigned int* node, sParserInfo* info)
{
    int buf_size = 128;
    char buf[128+1];
    char* p = buf;

    *p++ = '0';

    while(*info->p >= '0' && *info->p <= '7') {
        *p++ = *info->p++;

        if(p - buf >= buf_size-1) {
            parser_err_msg(info, "overflow node of number");
            return FALSE;
        }
    }
    *p = 0;
    skip_spaces_and_lf(info);

    unsigned long value = strtoul(buf, NULL, 0);

    *node = sNodeTree_create_int_value((int)value, 0, 0, 0);

    return TRUE;
}

static BOOL if_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for if");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);

    sNodeBlock* if_node_block = NULL;
    if(!parse_block(ALLOC &if_node_block, info, NULL, FALSE)) {
        return FALSE;
    }

    unsigned int elif_expression_nodes[ELIF_NUM_MAX];
    memset(elif_expression_nodes, 0, sizeof(unsigned int)*ELIF_NUM_MAX);

    sNodeBlock* elif_node_blocks[ELIF_NUM_MAX];
    memset(elif_node_blocks, 0, sizeof(sNodeBlock*)*ELIF_NUM_MAX);

    int elif_num = 0;

    sNodeBlock* else_node_block = NULL;

    while(1) {
        char* saved_p = info->p;
        int saved_sline = info->sline;

        char buf[VAR_NAME_MAX];

        /// else ///
        if(!isalpha(*info->p)) {
            break;
        }
        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
            return FALSE;
        }

        if(strcmp(buf, "else") == 0) {
            if(!parse_block(ALLOC &else_node_block, info, NULL, FALSE)) {
                return FALSE;
            }
            break;
        }
        else if(strcmp(buf, "elif") == 0) {
            expect_next_character_with_one_forward("(", info);

            /// expression ///
            if(!expression(&elif_expression_nodes[elif_num], info)) {
                return FALSE;
            }

            if(elif_expression_nodes[elif_num] == 0) {
                parser_err_msg(info, "require elif expression");
                info->err_num++;
                return TRUE;
            }

            expect_next_character_with_one_forward(")", info);

            if(!parse_block(ALLOC &elif_node_blocks[elif_num], info, NULL, FALSE)) {
                return FALSE;
            }

            elif_num++;
            if(elif_num >= ELIF_NUM_MAX) {
                parser_err_msg(info, "overflow elif num");
                info->err_num++;
                return FALSE;
            }
        }
        else {
            info->p = saved_p;
            info->sline = saved_sline;
            break;
        }
    }

    *node = sNodeTree_if_expression(expression_node, MANAGED if_node_block, elif_expression_nodes, elif_node_blocks, elif_num, MANAGED else_node_block);

    return TRUE;
}

static BOOL while_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for while");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);

    sNodeBlock* while_node_block = NULL;
    if(!parse_block(ALLOC &while_node_block, info, NULL, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_while_expression(expression_node, MANAGED while_node_block);

    return TRUE;
}

static BOOL for_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression1 ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for \"for\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(";", info);

    /// expression2 ///
    unsigned int expression_node2 = 0;
    if(!expression(&expression_node2, info)) {
        return FALSE;
    }

    if(expression_node2 == 0) {
        parser_err_msg(info, "require expression2 for \"for\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(";", info);

    /// expression3 ///
    unsigned int expression_node3 = 0;
    if(!expression(&expression_node3, info)) {
        return FALSE;
    }

    if(expression_node3 == 0) {
        parser_err_msg(info, "require expression3 for \"for\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);

    sNodeBlock* for_node_block = NULL;
    if(!parse_block(ALLOC &for_node_block, info, NULL, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_for_expression(expression_node, expression_node2, expression_node3, MANAGED for_node_block);

    return TRUE;
}

static BOOL return_expression(unsigned int* node, sParserInfo* info)
{
/*
    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);
    }
*/

    unsigned int expression_node = 0;
    if(*info->p != ';') {
        /// expression ///
        if(!expression(&expression_node, info)) {
            return FALSE;
        }
    }

/*
    if(*info->p == ')') {
        info->p++;
        skip_spaces_and_lf(info);
    }
*/

    *node = sNodeTree_create_return_expression(expression_node);

    return TRUE;
}

static BOOL new_expression(unsigned int* node, sParserInfo* info)
{
    sNodeType* node_type = NULL;
    unsigned int array_num = 0;

    if(!parse_type_for_new(&node_type, &array_num, info)) {
        return FALSE;
    }

    unsigned int params[PARAMS_MAX];
    int num_params = 0;

    if(!parse_method_params(&num_params, params, info)) {
        return FALSE;
    }

    *node = sNodeTree_create_new_operator(node_type, params, num_params, array_num);

    return TRUE;
}

static BOOL throw_expression(unsigned int* node, sParserInfo* info)
{
    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    *node = sNodeTree_create_throw_expression(expression_node);

    return TRUE;
}

static BOOL expect_next_word(char* word, sParserInfo* info)
{
    char buf[32];

    if(!parse_word(buf, 32, info, TRUE)) {
        return FALSE;
    }

    if(strcmp(buf, word) != 0) {
        parser_err_msg(info, "Expected next word is %s\n", word);
        info->err_num++;
    }

    return TRUE;
}

static BOOL parse_param(sParserParam* param, sParserInfo* info)
{
    /// variable name ///
    if(!parse_word(param->mName, VAR_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    expect_next_character_with_one_forward(":", info);

    if(!parse_type(&param->mType, info)) {
        return FALSE;
    }

    return TRUE;
}

BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info)
{
    if(*info->p == ')') {
        info->p++;
        skip_spaces_and_lf(info);

        *num_params = 0;

        return TRUE;
    }

    while(1) {
        if(!parse_param(params + *num_params, info)) {
            return FALSE;
        }

        (*num_params)++;

        if(*num_params > PARAMS_MAX) {
            parser_err_msg(info, "overflow params number");
            return FALSE;
        }

        if(*info->p == ',') {
            info->p++;
            skip_spaces_and_lf(info);
        }
        else if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "It is required to ',' or ')' before the source end");
            info->err_num++;
            break;
        }
        else {
            parser_err_msg(info, "Unexpected character(%c). It is required to ',' or ')' character", *info->p);
            if(*info->p == '\n') {
                info->sline++;
            }
            info->p++;

            info->err_num++;
        }
    }

    return TRUE;
}

static BOOL parse_params_and_entry_to_lvtable(sParserParam* params, int* num_params, sParserInfo* info, sVarTable** new_table, sVarTable* parent_lv_table)
{
    if(!parse_params(params, num_params, info)) {
        return FALSE;
    }

    *new_table = init_block_vtable(parent_lv_table);

    int i;
    for(i=0; i<*num_params; i++) {
        sParserParam* param = params + i;

        if(!add_variable_to_table(*new_table, param->mName, param->mType)) {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL try_expression(unsigned int* node, sParserInfo* info)
{
    /// try ///
    sNodeBlock* try_node_block = NULL;
    if(!parse_block(ALLOC &try_node_block, info, NULL, FALSE)) {
        return FALSE;
    }

    /// catch ///
    expect_next_word("catch", info);

    expect_next_character_with_one_forward("(", info);

    sParserParam params[PARAMS_MAX];
    int num_params = 0;

    /// parse_params ///
    sVarTable* new_table = NULL;

    if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, info->lv_table)) {
        return FALSE;
    }

    if(num_params != 1 || !is_exception_type(params[0].mType)) {
        parser_err_msg(info, "Require the type of a catch param should be a exception type");
        info->err_num++;
    }

    sNodeBlock* catch_node_block = NULL;
    if(!parse_block(ALLOC &catch_node_block, info, new_table, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_try_expression(MANAGED try_node_block, MANAGED catch_node_block, params[0].mName);

    return TRUE;
}

BOOL parse_class_type(sCLClass** klass, sParserInfo* info)
{
    char class_name[CLASS_NAME_MAX];

    if(!parse_word(class_name, CLASS_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    if(strcmp(class_name, "SELF") == 0) {
        *klass = info->klass;
    }
    else {
        *klass = get_class_with_load(class_name);
    }

    if(*klass == NULL) {
        parser_err_msg(info, "%s is not defined class", class_name);
        info->err_num++;
    }

    return TRUE;
}

BOOL parse_type(sNodeType** result_type, sParserInfo* info)
{
    char type_name[CLASS_NAME_MAX];

    if(!parse_word(type_name, CLASS_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    int i;
    for(i=0; i<info->generics_info.mNumParams; i++) {
        if(strcmp(type_name, info->generics_info.mParamNames[i]) == 0) {
            *result_type = create_node_type_with_generics_number(i);
            break;
        }
    }

    if(i == info->generics_info.mNumParams) {
        if(strcmp(type_name, "SELF") == 0) {
            *result_type = create_node_type_with_class_pointer(info->klass);
        }
        else {
            *result_type = create_node_type_with_class_name(type_name);
        }
    }

    if(*result_type == NULL || (*result_type)->mClass == NULL) {
        parser_err_msg(info, "%s is not defined class", type_name);
        info->err_num++;
    }

    int generics_num = 0;

    if(type_identify_with_class_name(*result_type, "lambda")) {
        sNodeBlockType* node_block_type = alloc_node_block_type();

        if(*info->p == '(') {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == ')') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else {
                while(1) {
                    sNodeType* node_type = NULL;
                    if(!parse_type(&node_type, info)) {
                        return FALSE;
                    }

                    node_block_type->mParams[node_block_type->mNumParams] = node_type;
                    node_block_type->mNumParams++;

                    if(node_block_type->mNumParams >= PARAMS_MAX) {
                        parser_err_msg(info, "oveflow block object type params");
                        return FALSE;
                    }

                    if(*info->p == ')') {
                        info->p++;
                        skip_spaces_and_lf(info);
                        break;
                    }
                    else if(*info->p == ',') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    else {
                        parser_err_msg(info, "invalid character in block type name(%c)", *info->p);
                        break;
                    }
                }
            }
        }

        if(*info->p == ':') {
            info->p++;
            skip_spaces_and_lf(info);

            sNodeType* node_type = NULL;
            if(!parse_type(&node_type, info)) {
                return FALSE;
            }

            node_block_type->mResultType = node_type;
        }
        else {
            node_block_type->mResultType = create_node_type_with_class_name("Null");
        }

        (*result_type)->mBlockType = node_block_type;
    }
    else if(*info->p == '<') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            if(!parse_type(&(*result_type)->mGenericsTypes[generics_num], info)) {
                return FALSE;
            }

            generics_num++;

            if(generics_num >= GENERICS_TYPES_MAX) {
                parser_err_msg(info, "overflow generics parametor number");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '>') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else {
                parser_err_msg(info, "invalid character(%c) in generics types", *info->p);
                info->err_num++;
                break;
            }
        }
    }

    if(*info->p == '[' && *(info->p+1) == ']') {
        info->p+=2;
        skip_spaces_and_lf(info);

        (*result_type)->mArray = TRUE;
    }

    (*result_type)->mNumGenericsTypes = generics_num;

    /// anotation ///
    if(*info->p == '@') {
        info->p++;

        if(isalpha(*info->p)) {
            while(isalnum(*info->p) || *info->p == '-' || *info->p == '_' || *info->p == '[' || *info->p == ']') {
                info->p++;
            }
            skip_spaces_and_lf(info);
        }
        else {
            parser_err_msg(info, "require alphabets for anotation");
            info->err_num++;
        }
    }

    /// check generics type ///
    if(info->err_num == 0) {
        sCLClass* klass = (*result_type)->mClass;

        for(i=0; i<generics_num; i++) {
            sCLClass* left_type = get_class_with_load(CONS_str(&klass->mConst, klass->mGenericsParamTypeOffsets[i]));

            sCLClass* right_type = (*result_type)->mGenericsTypes[i]->mClass;
            sCLClass* right_type2;
            solve_generics_for_variable_to_class(right_type, &right_type2, info->klass);

            if(!check_implemented_methods_for_interface(left_type, right_type2)) {
                parser_err_msg(info, "%s is not implemented %s interface" , CLASS_NAME(right_type2), CLASS_NAME(left_type));
                info->err_num++;
            }
        }
    }

    return TRUE;
}

BOOL parse_type_for_new(sNodeType** result_type, unsigned int* array_num, sParserInfo* info)
{
    char type_name[CLASS_NAME_MAX];

    if(!parse_word(type_name, CLASS_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    int i;
    for(i=0; i<info->generics_info.mNumParams; i++) {
        if(strcmp(type_name, info->generics_info.mParamNames[i]) == 0) {
            *result_type = create_node_type_with_generics_number(i);
            break;
        }
    }

    if(i == info->generics_info.mNumParams) {
        if(strcmp(type_name, "SELF") == 0) {
            *result_type = create_node_type_with_class_pointer(info->klass);
        }
        else {
            *result_type = create_node_type_with_class_name(type_name);
        }
    }

    if(*result_type == NULL || (*result_type)->mClass == NULL) {
        parser_err_msg(info, "%s is not defined class", type_name);
        info->err_num++;
    }

    *array_num = 0;

    int generics_num = 0;

    if(*info->p == '<') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            if(!parse_type(&(*result_type)->mGenericsTypes[generics_num], info)) {
                return FALSE;
            }

            generics_num++;

            if(generics_num >= GENERICS_TYPES_MAX) {
                parser_err_msg(info, "overflow generics parametor number");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '>') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else {
                parser_err_msg(info, "invalid character(%c) in generics types", *info->p);
                info->err_num++;
                break;
            }
        }
    }

    if(*info->p == '[') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression(array_num, info)) {
            return FALSE;
        }

        expect_next_character_with_one_forward("]", info);

        (*result_type)->mArray = TRUE;
    }

    (*result_type)->mNumGenericsTypes = generics_num;

    /// check generics type ///
    sCLClass* klass = (*result_type)->mClass;

    for(i=0; i<generics_num; i++) {
        int generics_paramType_offset = klass->mGenericsParamTypeOffsets[i];
        sCLClass* left_type = get_class_with_load(CONS_str(&klass->mConst, generics_paramType_offset));

        sCLClass* right_type = (*result_type)->mGenericsTypes[i]->mClass;
        sCLClass* right_type2;
        solve_generics_for_variable_to_class(right_type, &right_type2, info->klass);

        if(!check_implemented_methods_for_interface(left_type, right_type2)) {
            parser_err_msg(info, "%s is not implemented %s interface" , CLASS_NAME(right_type2), CLASS_NAME(left_type));
            info->err_num++;
        }
    }

    return TRUE;
}

static BOOL is_assign_operator(sParserInfo* info) 
{
    return (*info->p == '+' && *(info->p+1) == '=')
        || (*info->p == '-' && *(info->p+1) == '=')
        || (*info->p == '*' && *(info->p+1) == '=')
        || (*info->p == '/' && *(info->p+1) == '=')
        || (*info->p == '%' && *(info->p+1) == '=')
        || (*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) == '=')
        || (*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) == '=')
        || (*info->p == '&' && *(info->p+1) == '=')
        || (*info->p == '^' && *(info->p+1) == '=')
        || (*info->p == '|' && *(info->p+1) == '=');
}

static BOOL assign_operator(unsigned int* node, sParserInfo* info)
{
    if(*info->p == '+' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpAdd, *node, right, 0);
    }
    else if(*info->p == '-' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpSub, *node, right, 0);
    }
    else if(*info->p == '*' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpMult, *node, right, 0);
    }
    else if(*info->p == '/' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpDiv, *node, right, 0);
    }
    else if(*info->p == '%' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpMod, *node, right, 0);
    }
    else if(*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) == '=') {
        info->p += 3;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpLeftShift, *node, right, 0);
    }
    else if(*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) == '=') {
        info->p += 3;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpRightShift, *node, right, 0);
    }
    else if(*info->p == '&' && *(info->p+1) == '=') {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpAnd, *node, right, 0);
    }
    else if(*info->p == '^' && *(info->p+1) == '=') {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpXor, *node, right, 0);
    }
    else if(*info->p == '|' && *(info->p+1) == '=') {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpOr, *node, right, 0);
    }

    return TRUE;
}

static BOOL postposition_operator(unsigned int* node, sParserInfo* info, int* num_method_chains, unsigned int max_method_chains_node[METHOD_CHAIN_MAX])
{
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        /// call method or access field ///
        if(*info->p == '.' && *(info->p+1) != '.') {
            info->p++;
            skip_spaces_and_lf(info);

            if(info->get_type_for_interpreter && *info->p == '\0') {
                return TRUE;
            }

            if(isalpha(*info->p)) {
                char buf[METHOD_NAME_MAX];

                if(!parse_word(buf, METHOD_NAME_MAX, info, TRUE)) {
                    return FALSE;
                }
                skip_spaces_and_lf(info);

                if(info->get_type_for_interpreter && *info->p == '\0') {
                    return TRUE;
                }

                /// call methods ///
                if(*info->p == '(') {
                    unsigned int params[PARAMS_MAX];
                    int num_params = 0;

                    if(!parse_method_params(&num_params, params, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_method_call(*node, buf, params, num_params, *num_method_chains);
                    max_method_chains_node[*num_method_chains] = *node;

                    (*num_method_chains)++;

                    if(*num_method_chains >= METHOD_CHAIN_MAX) {
                        parser_err_msg(info, "overflow method chain");
                        return FALSE;
                    }
                }
                /// access fields ///
                else {
                    if(is_assign_operator(info)) {
                        unsigned int node2 = clone_node(*node);
                        unsigned int node3 = clone_node(*node);

                        /// load field ///
                        *node = sNodeTree_create_fields(buf, node2);

                        /// go 
                        if(!assign_operator(node, info)) {
                            return FALSE;
                        }

                        *node = sNodeTree_create_assign_field(buf, node3, *node);
                    }
                    else if(*info->p == '=' && *(info->p +1) != '=') {
                        info->p++;
                        skip_spaces_and_lf(info);

                        unsigned int right_node = 0;

                        if(!expression(&right_node, info)) {
                            return FALSE;
                        }

                        if(right_node == 0) {
                            parser_err_msg(info, "Require right value");
                            info->err_num++;

                            *node = 0;
                        }
                        else {
                            *node = sNodeTree_create_assign_field(buf, *node, right_node);
                        }
                    }
                    else {
                        *node = sNodeTree_create_fields(buf, *node);
                    }
                }
            }
            else {
                parser_err_msg(info, "require method name or field name after .");
                info->err_num++;
                *node = 0;
                break;
            }
        }
        /// access element ///
        else if(*info->p == '[') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int index_node = 0;

            if(!expression(&index_node, info)) {
                return FALSE;
            }

            if(index_node == 0) {
                parser_err_msg(info, "Require index value");
                info->err_num++;

                *node = 0;
            }
            else {
                expect_next_character_with_one_forward("]", info);

                if(is_assign_operator(info)) {
                    unsigned int node2 = clone_node(*node);
                    unsigned int index_node2 = clone_node(index_node);

                    /// load field ///
                    *node = sNodeTree_create_load_array_element(*node, index_node);

                    /// go 
                    if(!assign_operator(node, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_store_array_element(node2, index_node2, *node);
                }
                else if(*info->p == '=' && *(info->p+1) != '=') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    unsigned int right_node = 0;

                    if(!expression(&right_node, info)) {
                        return FALSE;
                    }

                    if(right_node == 0) {
                        parser_err_msg(info, "Require right value");
                        info->err_num++;

                        *node = 0;
                    }
                    else {
                        *node = sNodeTree_create_store_array_element(*node, index_node, right_node);
                    }
                }
                else {
                    *node = sNodeTree_create_load_array_element(*node, index_node);
                }
            }
        }
        /// get value from pointer ///
        else if(*info->p == '-' && *(info->p+1) == '>')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            sNodeType* node_type = NULL;

            if(!parse_type(&node_type, info)) {
                return FALSE;
            }

            if(node_type == NULL) {
                parser_err_msg(info, "require a type for the pointer value");
                info->err_num++;
                *node = 0;
                return TRUE;
            }

            if(*info->p == '=' && *(info->p + 1) != '=') {
                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    *node = sNodeTree_create_store_value_to_pointer(*node, node_type, right_node);
                }
            }
            else {
                *node = sNodeTree_create_load_value_from_pointer(*node, node_type);
            }
        }
        else if(*info->p == '+' && *(info->p+1) == '+') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_increment_operand(*node);
        }
        else if(*info->p == '-' && *(info->p+1) == '-') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_decrement_operand(*node);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL parse_block_object(unsigned int* node, sParserInfo* info, BOOL lambda)
{
    sParserParam params[PARAMS_MAX];
    int num_params = 0;

    /// parse_params ///
    sVarTable* new_table = NULL;

    if(lambda) {
        if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, NULL)) {
            return FALSE;
        }
    }
    else {
        if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, info->lv_table)) {
            return FALSE;
        }
    }

    sNodeType* result_type = NULL;
    if(*info->p == ':') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!parse_type(&result_type, info)) {
            return FALSE;
        }
    }
    else {
        result_type = create_node_type_with_class_name("Null");
    }

    sNodeBlock* node_block = NULL;
    if(!parse_block(ALLOC &node_block, info, new_table, TRUE)) {
        return FALSE;
    }

    *node = sNodeTree_create_block_object(params, num_params, result_type, MANAGED node_block, lambda);

    return TRUE;
}

static BOOL parse_normal_block(unsigned int* node, sParserInfo* info)
{
    sNodeBlock* node_block = NULL;
    if(!parse_block(ALLOC &node_block, info, NULL, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_create_normal_block(MANAGED node_block);

    return TRUE;
}

static BOOL parse_array_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(array_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_array_value(num_elements, array_elements);

    return TRUE;
}

static BOOL parse_carray_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(array_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_carray_value(num_elements, array_elements);

    return TRUE;
}

static BOOL parse_equalable_carray_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(array_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_equalable_carray_value(num_elements, array_elements);

    return TRUE;
}

static BOOL parse_sortable_carray_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(array_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_sortable_carray_value(num_elements, array_elements);

    return TRUE;
}

static BOOL parse_hash_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int hash_keys[HASH_VALUE_ELEMENT_MAX+1];
    unsigned int hash_items[HASH_VALUE_ELEMENT_MAX+1];

    memset(hash_keys, 0, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    memset(hash_items, 0, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(hash_keys + num_elements, info)) {
                return FALSE;
            }

            expect_next_character_with_one_forward(":", info);

            if(!expression(hash_items + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= HASH_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow hash value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_hash_value(num_elements, hash_keys, hash_items);

    return TRUE;
}

static BOOL parse_list_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int list_elements[LIST_VALUE_ELEMENT_MAX];
    memset(list_elements, 0, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(list_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= LIST_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_list_value(num_elements, list_elements);

    return TRUE;
}

static BOOL parse_equalable_list_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int list_elements[LIST_VALUE_ELEMENT_MAX];
    memset(list_elements, 0, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(list_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= LIST_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_equalable_list_value(num_elements, list_elements);

    return TRUE;
}

static BOOL parse_sortable_list_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int list_elements[LIST_VALUE_ELEMENT_MAX];
    memset(list_elements, 0, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(list_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= LIST_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_sortable_list_value(num_elements, list_elements);

    return TRUE;
}

static BOOL parse_tuple_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int tuple_element[LIST_VALUE_ELEMENT_MAX];
    memset(tuple_element, 0, sizeof(unsigned int)*TUPLE_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(tuple_element + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= TUPLE_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    *node = sNodeTree_create_tuple_value(num_elements, tuple_element);

    return TRUE;
}

BOOL parse_iniherit(unsigned int* node, sParserInfo* info)
{
    unsigned int params[PARAMS_MAX];
    int num_params = 0;

    if(!parse_method_params(&num_params, params, info)) {
        return FALSE;
    }

    *node = sNodeTree_create_inherit_call(num_params, params, info->klass->mMethodIndexOnCompileTime-1);

    return TRUE;
}

static BOOL expression_node(unsigned int* node, sParserInfo* info)
{
    int num_method_chains = 0;
    unsigned int max_method_chains_node[METHOD_CHAIN_MAX];

    if((*info->p == '-' && *(info->p+1) != '=' && *(info->p+1) != '-' && *(info->p+1) != '>') || (*info->p == '+' && *(info->p+1) != '=' && *(info->p+1) != '+')) 
    {
        if(*info->p == '-') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!get_number(TRUE, node, info)) {
                return FALSE;
            }
        }
        else if(*info->p =='+') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!get_number(FALSE, node, info)) {
                return FALSE;
            }
        }
    }
    else if(*info->p == '0' && *(info->p+1) == 'x') {
        info->p += 2;

        if(!get_hex_number(node, info)) {
            return FALSE;
        }
    }
    else if(*info->p == '0') {
        info->p++;

        if(!get_oct_number(node, info)) {
            return FALSE;
        }
    }
    else if(isdigit(*info->p)) {
        if(!get_number(FALSE, node, info)) {
            return FALSE;
        }
    }
    else if(*info->p == '"') {
        info->p++;

        sBuf value;
        sBuf_init(&value);

        while(1) {
            if(*info->p == '"') {
                info->p++;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;
                switch(*info->p) {
                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make string value");
                return FALSE;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_string_value(MANAGED value.mBuf);
    }
    else if((*info->p == 'B' || *info->p == 'b') && *(info->p+1) == '"') {
        info->p+=2;

        sBuf value;
        sBuf_init(&value);

        while(1) {
            if(*info->p == '"') {
                info->p++;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;
                switch(*info->p) {
                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    case '0':
                        sBuf_append_char(&value, '\0');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make string buffer value");
                return FALSE;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_buffer_value(MANAGED value.mBuf, value.mLen);
    }
    else if((*info->p == 'P' || *info->p == 'p') && *(info->p+1) == '"') {
        info->p+=2;

        sBuf value;
        sBuf_init(&value);

        while(1) {
            if(*info->p == '"') {
                info->p++;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;
                switch(*info->p) {
                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    case '0':
                        sBuf_append_char(&value, '\0');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make string buffer value");
                return FALSE;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_path_value(MANAGED value.mBuf, value.mLen);
    }
    else if(*info->p == '\'') {
        info->p++;

        wchar_t c;

        if(*info->p == '\\') {
            info->p++;

            switch(*info->p) {
                case 'n':
                    c = '\n';
                    info->p++;
                    break;

                case 't':
                    c = '\t';
                    info->p++;
                    break;

                case 'r':
                    c = '\r';
                    info->p++;
                    break;

                case 'a':
                    c = '\a';
                    info->p++;
                    break;

                case '\\':
                    c = '\\';
                    info->p++;
                    break;

                case '0':
                    c = '\0';
                    info->p++;
                    break;

                default:
                    c = *info->p;
                    info->p++;
                    break;
            }
        }
        else {
            unsigned char p2 = *(unsigned char*)info->p;

            /// utf-8 character ///
            if(p2 > 127) {
                int size;
                char str[MB_LEN_MAX+1];

                size = ((p2 & 0x80) >> 7) + ((p2 & 0x40) >> 6) + ((p2 & 0x20) >> 5) + ((p2 & 0x10) >> 4);

                if(size > MB_LEN_MAX) {
                    parser_err_msg(info, "invalid utf-8 character. MB_LEN_MAX");
                    info->err_num++;
                }
                else {
                    memcpy(str, info->p, size);
                    str[size] = 0;

                    if(mbtowc(&c, str, size) < 0) {
                        parser_err_msg(info, "invalid utf-8 character. mbtowc");
                        info->err_num++;
                        c = 0;
                    }

                    info->p += size;
                }
            }
            /// ASCII character ///
            else {
                c = *info->p;
                info->p++;
            }
        }

        if(*info->p != '\'') {
            parser_err_msg(info, "close \' to make character value");
            info->err_num++;
        }
        else {
            info->p++;

            skip_spaces_and_lf(info);

            *node = sNodeTree_create_character_value(c);
        }
    }
    else if(*info->p == '{') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!parse_array_value(node, info)) {
            return FALSE;
        }
    }
    else if(isalpha(*info->p)) {
        char buf[VAR_NAME_MAX];

        char* p_before = info->p;
        int sline_before = info->sline;

        /// name ///
        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
            return FALSE;
        }

        if(strcmp(buf, "if") == 0) {
            if(!if_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "while") == 0) {
            if(!while_expression(node, info)) {
                return FALSE;
            }

        }
        else if(strcmp(buf, "for") == 0) {
            if(!for_expression(node, info)) {
                return FALSE;
            }

        }
        else if(strcmp(buf, "break") == 0) {
            *node = sNodeTree_break_expression();
        }
        else if(strcmp(buf, "true") == 0) {
            *node = sNodeTree_true_expression();
        }
        else if(strcmp(buf, "false") == 0) {
            *node = sNodeTree_false_expression();
        }
        else if(strcmp(buf, "null") == 0) {
            *node = sNodeTree_null_expression();
        }
        else if(strcmp(buf, "throw") == 0) {
            if(!throw_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "try") == 0) {
            if(!try_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "return") == 0) {
            if(!return_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "new") == 0) {
            if(!new_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "closure") == 0 && *info->p == '(') {
            expect_next_character_with_one_forward("(", info);

            if(!parse_block_object(node, info, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "lambda") == 0 && *info->p == '(') {
            expect_next_character_with_one_forward("(", info);

            if(!parse_block_object(node, info, TRUE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "block") == 0 && *info->p == '{') {
            if(!parse_normal_block(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "inherit") == 0) {
            if(!parse_iniherit(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "list") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_list_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "equalable_list") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_equalable_list_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "sortable_list") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_sortable_list_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "tuple") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_tuple_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "hash") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_hash_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "array") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_carray_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "equalable_array") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_equalable_carray_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "sortable_array") == 0 && *info->p == '{') {
            expect_next_character_with_one_forward("{", info);

            if(!parse_sortable_carray_value(node, info)) {
                return FALSE;
            }
        }

        /// add variable ///
        else if(*info->p == ':') {
            info->p++;
            skip_spaces_and_lf(info);

            sNodeType* node_type;
            if(*info->p != '=') {
                if(!parse_type(&node_type, info)) {
                    return FALSE;
                }

                if(node_type->mClass == NULL) {
                    *node = 0;
                    return TRUE;
                }
                if(node_type) {
                    check_already_added_variable(info->lv_table, buf, info);
                    add_variable_to_table(info->lv_table, buf, node_type);
                }
            }
            else {
                node_type = NULL;
                check_already_added_variable(info->lv_table, buf, info);
                add_variable_to_table(info->lv_table, buf, node_type);
            }

            /// assign the value to a variable ///
            if(*info->p == '=' && *(info->p+1) != '=') {
                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    *node = sNodeTree_create_store_variable(buf, node_type, right_node, info->klass);
                }
            }
            else {
                parser_err_msg(info, "A variable should be initialized");
                info->err_num++;
            }
        }
        /// substitution ///
        else if(*info->p == '=' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;

            if(!expression(&right_node, info)) {
                return FALSE;
            }

            if(right_node == 0) {
                parser_err_msg(info, "Require right value");
                info->err_num++;

                *node = 0;
            }
            else {
                *node = sNodeTree_create_store_variable(buf, NULL, right_node, info->klass);
            }
        }
        else if(is_assign_operator(info)) {
            *node = sNodeTree_create_load_variable(buf);

            /// go ///
            if(!assign_operator(node, info)) {
                return FALSE;
            }

            *node = sNodeTree_create_store_variable(buf, NULL, *node, info->klass);
        }
        else {
            sCLClass* klass = get_class(buf);

            if(klass == NULL) {
                klass = load_class(buf);
            }

            sCLClass* global_klass = get_class("Global");

            /// class name ///
            if(klass) {
                info->p = p_before;
                info->sline = sline_before;

                sNodeType* klass2;

                if(!parse_type(&klass2, info)) {
                    return FALSE;
                }

                /// class field or class method ///
                if(*info->p == '.') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    char buf[METHOD_NAME_MAX];

                    /// name ///
                    if(!parse_word(buf, METHOD_NAME_MAX, info, TRUE)) {
                        return FALSE;
                    }

                    /// class method ///
                    if(*info->p == '(') {
                        unsigned int params[PARAMS_MAX];
                        int num_params = 0;

                        if(!parse_method_params(&num_params, params, info)) {
                            return FALSE;
                        }

                        *node = sNodeTree_create_class_method_call(klass2, buf, params, num_params);
                        max_method_chains_node[num_method_chains] = *node;
                        num_method_chains++;

                        if(num_method_chains >= METHOD_CHAIN_MAX) {
                            parser_err_msg(info, "overflow method chain");
                            return FALSE;
                        }
                    }
                    /// class field ///
                    else {
                        if(is_assign_operator(info)) {
                            /// load field ///
                            *node = sNodeTree_create_class_fields(klass, buf);

                            /// go 
                            if(!assign_operator(node, info)) {
                                return FALSE;
                            }

                            *node = sNodeTree_create_assign_class_field(klass, buf, *node);
                        }
                        else if(*info->p == '=' && *(info->p +1) != '=') {
                            info->p++;
                            skip_spaces_and_lf(info);

                            unsigned int right_node = 0;

                            if(!expression(&right_node, info)) {
                                return FALSE;
                            }

                            if(right_node == 0) {
                                parser_err_msg(info, "Require right value");
                                info->err_num++;

                                *node = 0;
                            }
                            else {
                                *node = sNodeTree_create_assign_class_field(klass, buf, right_node);
                            }
                        }
                        else {
                            *node = sNodeTree_create_class_fields(klass, buf);
                        }
                    }
                }
                /// class name ///
                else {
                    parser_err_msg(info, "require . operator");
                    info->err_num++;
                }
            }
            /// global class ///
            else if(method_name_existance(global_klass, buf))
            {
                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_method_params(&num_params, params, info)) {
                    return FALSE;
                }

                sNodeType* global_klass_type = alloc_node_type();

                global_klass_type->mClass = global_klass;
                global_klass_type->mNumGenericsTypes = 0;

                *node = sNodeTree_create_class_method_call(global_klass_type, buf, params, num_params);
                max_method_chains_node[num_method_chains] = *node;
                num_method_chains++;
                if(num_method_chains >= METHOD_CHAIN_MAX) {
                    parser_err_msg(info, "overflow method chain");
                    return FALSE;
                }
            }
            /// Command class method call ///
            else if(get_variable_index(info->lv_table, buf) == -1) {
                unsigned int params[PARAMS_MAX];
                int num_params = 0;

/*
                if(*info->p != '(') {
                    parser_err_msg(info, "Require ( to call command class method");
                    info->err_num++;
                }
                else {
*/
                    if(!parse_method_params(&num_params, params, info)) {
                        return FALSE;
                    }

                    sCLClass* command_klass = get_class("Command");

                    sNodeType* command_klass_type = alloc_node_type();

                    command_klass_type->mClass = command_klass;
                    command_klass_type->mNumGenericsTypes = 0;

                    *node = sNodeTree_create_class_method_call(command_klass_type, buf, params, num_params);
                    max_method_chains_node[num_method_chains] = *node;
                    num_method_chains++;

                    if(num_method_chains >= METHOD_CHAIN_MAX) {
                        parser_err_msg(info, "overflow method chain");
                        return FALSE;
                    }
                //}
            }
            else {
                *node = sNodeTree_create_load_variable(buf);

                /// lamda call ///
                if(*info->p == '(') {
                    unsigned int params[PARAMS_MAX];
                    int num_params = 0;

                    if(!parse_method_params(&num_params, params, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_block_call(*node, num_params, params);
                }
            }
        }
    }
    /// regex ///
    else if(*info->p == '/' && *(info->p+1) != '*') {
        info->p++;
        skip_spaces_and_lf(info);

        sBuf regex;
        sBuf_init(&regex);

        while(1) {
            if(*info->p == '/') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "Require / to close regex");
                info->err_num++;
                break;
            }
            else {
                sBuf_append_char(&regex, *info->p);
                info->p++;
            }
        }

        BOOL global = FALSE;
        BOOL ignore_case = FALSE;
        BOOL multiline = FALSE;
        BOOL extended = FALSE;
        BOOL dotall = FALSE;
        BOOL anchored = FALSE;
        BOOL dollar_endonly = FALSE;
        BOOL ungreedy = FALSE;
        while(1) {
            if(*info->p == 'g') {
                info->p++;
                global = TRUE;
            }
            else if(*info->p == 'i') {
                info->p++;
                ignore_case = TRUE;
            }
            else if(*info->p == 's') {
                info->p++;
                dotall = TRUE;
            }
            else if(*info->p == 'm') {
                info->p++;
                multiline = TRUE;
            }
            else if(*info->p == 'A') {
                info->p++;
                anchored = TRUE;
            }
            else if(*info->p == 'D') {
                info->p++;
                dollar_endonly = TRUE;
            }
            else if(*info->p == 'U') {
                info->p++;
                ungreedy = TRUE;
            }
            else if(*info->p == 'x') {
                info->p++;
                extended = TRUE;
            }
            else {
                break;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_regex(MANAGED regex.mBuf, global, ignore_case, multiline, extended, dotall, anchored, dollar_endonly, ungreedy);
    }
    else if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression(node, info)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        if(!expect_next_character(")", info)) {
            return FALSE;
        }
        info->p++;
        skip_spaces_and_lf(info);

        if(*node == 0) {
            parser_err_msg(info, "require expression as ( operand");
            info->err_num++;
        }
    }
    else if(*info->p == '&') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression(node, info)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_get_address(*node);
    }
    else if(*info->p == 0) {
        *node = 0;
        return TRUE;
    }
    else {
        parser_err_msg(info, "invalid character (character code %d) (%c)", *info->p, *info->p);

        if(*info->p == '\n') info->sline++;
        info->p++;
        skip_spaces_and_lf(info);

        info->err_num++;

        *node = 0;
    }

    /// postposition operator ///
    if(!postposition_operator(node, info, &num_method_chains, max_method_chains_node))
    {
        return FALSE;
    }

    gNodes[*node].mMaxMethodChains = num_method_chains;

    int i;
    for(i=0; i<num_method_chains; i++) {
        gNodes[max_method_chains_node[i]].mMaxMethodChains = num_method_chains;
    }

    return TRUE;
}

// from right to left order 
static BOOL expression_monadic_operator(unsigned int* node, sParserInfo* info)
{
    while(*info->p) {
        if(*info->p == '+' && *(info->p+1) == '+') {
            info->p +=2;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for operator ++");
                info->err_num++;
            }

            if(!check_node_is_variable(*node)) {
                parser_err_msg(info, "require the variable name for operator ++");
                info->err_num++;
            }

            *node = sNodeTree_create_monadic_increment_operand(*node);
            break;
        }
        else if(*info->p == '-' && *(info->p+1) == '-') {
            info->p +=2;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for operator --");
                info->err_num++;
            }

            if(!check_node_is_variable(*node)) {
                parser_err_msg(info, "require the variable name for operator ++");
                info->err_num++;
            }

            *node = sNodeTree_create_monadic_decrement_operand(*node);
            break;
        }
        else if(*info->p == '~') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for operator ~");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComplement, *node, 0, 0);
            break;
        }
        else if(*info->p == '!') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for !");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpLogicalDenial, *node, 0, 0);
            break;
        }
        else {
            if(!expression_node(node, info)) {
                return FALSE;
            }
            break;
        }
    }


    return TRUE;
}

static BOOL expression_implements(unsigned int* node, sParserInfo* info)
{
    if(!expression_monadic_operator(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(memcmp(info->p, "implements", 10) == 0) {
            info->p+=10;
            skip_spaces_and_lf(info);

            char buf[VAR_NAME_MAX+1];

            /// name ///
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
                return FALSE;
            }

            *node = sNodeTree_create_implements(*node, buf);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_mult_div(unsigned int* node, sParserInfo* info)
{
    if(!expression_implements(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '*' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_implements(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator *");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpMult, *node, right, 0);
        }
        else if(*info->p == '/' && *(info->p+1) != '=' && *(info->p+1) != '*') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_implements(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator /");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpDiv, *node, right, 0);
        }
        else if(*info->p == '%' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_implements(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator ^");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpMod, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_add_sub(unsigned int* node, sParserInfo* info)
{
    if(!expression_mult_div(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '+' && *(info->p+1) != '=' && *(info->p+1) != '+') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_mult_div(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator +");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpAdd, *node, right, 0);
        }
        else if(*info->p == '-' && *(info->p+1) != '=' && *(info->p+1) != '-' && *(info->p+1) != '>') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_mult_div(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator -");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpSub, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_shift(unsigned int* node, sParserInfo* info)
{
    if(!expression_add_sub(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) != '=') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_add_sub(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator <<");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpLeftShift, *node, right, 0);
        }
        else if(*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) != '=') {
            info->p+=2;
            skip_spaces_and_lf(info);
            
            unsigned int right = 0;
            if(!expression_add_sub(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator >>");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpRightShift, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_comparison_operator(unsigned int* node, sParserInfo* info)
{
    if(!expression_shift(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '>' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for >= operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonGreaterEqual, *node, right, 0);
        }
        else if(*info->p == '<' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for <= operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonLesserEqual, *node, right, 0);
        }
        else if(*info->p == '>' && *(info->p+1) != '>') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for > operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonGreater, *node, right, 0);
        }
        else if(*info->p == '<' && *(info->p+1) != '<') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for < operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonLesser, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_comparison_equal_operator(unsigned int* node, sParserInfo* info)
{
    if(!expression_comparison_operator(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '=' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_comparison_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for == operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonEqual, *node, right, 0);
        }
        else if(*info->p == '!' && *(info->p+1) == '=') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_comparison_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for != operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonNotEqual, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_and(unsigned int* node, sParserInfo* info)
{
    if(!expression_comparison_equal_operator(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '&' && *(info->p+1) != '&' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_comparison_equal_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for & operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpAnd, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_xor(unsigned int* node, sParserInfo* info)
{
    if(!expression_and(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '^' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_and(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for ^ operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpXor, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_or(unsigned int* node, sParserInfo* info)
{
    if(!expression_xor(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '|' && *(info->p+1) != '=' && *(info->p+1) != '|') {
            (info->p)++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_xor(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for | operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpOr, *node, right, 0);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_and_and(unsigned int* node, sParserInfo* info)
{
    if(!expression_or(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '&' && *(info->p+1) == '&') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_or(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for && operator");
                info->err_num++;
            }

            *node = sNodeTree_create_and_and(*node, right);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL expression_or_or(unsigned int* node, sParserInfo* info)
{
    if(!expression_and_and(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '|' && *(info->p+1) == '|') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_and_and(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator ||");
                info->err_num++;
            }

            *node = sNodeTree_create_or_or(*node, right);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_conditional_operator(unsigned int* node, sParserInfo* info)
{
    if(!expression_or_or(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '?') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned middle = 0;
            if(!expression(&middle, info)) {
                return FALSE;
            }

            expect_next_character_with_one_forward(":", info);

            unsigned right = 0;
            if(!expression(&right, info)) {
                return FALSE;
            }

            if(middle == 0) {
                parser_err_msg(info, "require middle value for operator ?");
                info->err_num++;
            }
            if(right == 0) {
                parser_err_msg(info, "require right value for operator ?");
                info->err_num++;
            }

            *node = sNodeTree_conditional_expression(*node, middle, right);
        }
        else {
            break;
        }
    }

    return TRUE;
}

BOOL expression(unsigned int* node, sParserInfo* info) 
{
    skip_spaces_and_lf(info);

    if(!expression_conditional_operator(node, info)) {
        return FALSE;
    }

    return TRUE;
}

