#include "common.h"

static BOOL expression_substitution(unsigned int* node, sParserInfo* info);

void parser_err_msg(sParserInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    fprintf(stderr, "%s %d: %s\n", info->sname, info->sline, msg2);
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
    char buf[128];
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

        if(*info->p == 'b') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_byte_value(atoi(buf), 0, 0, 0);
        }
        else if(*info->p == 'u' && *(info->p+1) == 'b') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_ubyte_value(atoi(buf), 0, 0, 0);
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
    if(!parse_normal_block(ALLOC &if_node_block, info)) {
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
            if(!parse_normal_block(ALLOC &else_node_block, info)) {
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

            if(!parse_normal_block(ALLOC &elif_node_blocks[elif_num], info)) {
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
    if(!parse_normal_block(ALLOC &while_node_block, info)) {
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
    if(!parse_normal_block(ALLOC &for_node_block, info)) {
        return FALSE;
    }

    *node = sNodeTree_for_expression(expression_node, expression_node2, expression_node3, MANAGED for_node_block);

    return TRUE;
}

static BOOL return_expression(unsigned int* node, sParserInfo* info)
{
    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);
    }

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(*info->p == ')') {
        info->p++;
        skip_spaces_and_lf(info);
    }

    *node = sNodeTree_create_return_expression(expression_node);

    return TRUE;
}

static BOOL new_expression(unsigned int* node, sParserInfo* info)
{
    sNodeType* node_type = NULL;

    if(!parse_type(&node_type, info)) {
        return FALSE;
    }

    unsigned int params[PARAMS_MAX];
    int num_params = 0;

    if(!parse_method_params(&num_params, params, info)) {
        return FALSE;
    }

    *node = sNodeTree_create_new_operator(node_type, params, num_params);

    return TRUE;
}

BOOL parse_type(sNodeType** result_type, sParserInfo* info)
{
    char type_name[CLASS_NAME_MAX];

    if(!parse_word(type_name, CLASS_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    *result_type = create_node_type_with_class_name(type_name);

    if(*result_type == NULL || (*result_type)->mClass == NULL) {
        parser_err_msg(info, "%s is not defined class", type_name);
        info->err_num++;
    }

    return TRUE;
}

static BOOL postposition_operator(unsigned int* node, sParserInfo* info)
{
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        /// call method or access field ///
        if(*info->p == '.' && *(info->p+1) != '.') {
            info->p++;
            skip_spaces_and_lf(info);

            if(isalpha(*info->p)) {
                char buf[VAR_NAME_MAX];

                if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
                    return FALSE;
                }
                skip_spaces_and_lf(info);

                /// call methods ///
                if(*info->p == '(') {
                }
                /// access fields ///
                else {
                    if(*info->p == '=' && *(info->p +1) != '=') {
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
/*
        /// indexing ///
        else if(**info->p == '[') {
            unsigned int param_node;
            unsigned int block_object;
            unsigned int block_node;

            if(quote) {
                parser_err_msg_format(info->sname, sline_top, "can't quote [ operand");
                (*info->err_num)++;
                *node = 0;
                return TRUE;
            }
            
            param_node = 0;
            if(!get_params(info, &param_node, '[', ']', lv_table, &block_object, &block_node, FALSE)) {
                return FALSE;
            }

            if(block_object != 0 || block_node != 0) {
                parser_err_msg_format(info->sname, *info->sline, "Clover can't get block with indexing operator");
                (*info->err_num)++;
            }

            *node = sNodeTree_create_operand(kOpIndexing, *node, param_node, 0, quote);
        }
*/
        else if(**info->p == '+' && *(*info->p+1) == '+') {
            (*info->p)+=2;
            skip_spaces_and_lf(info->p, info->sline);

            *node = sNodeTree_create_increment_operand(*node);
        }
        else if(**info->p == '-' && *(*info->p+1) == '-') {
            (*info->p)+=2;
            skip_spaces_and_lf(info->p, info->sline);

            *node = sNodeTree_create_decment_operand(*node);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL expression_node(unsigned int* node, sParserInfo* info)
{
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
    else if(isdigit(*info->p)) {
        if(!get_number(FALSE, node, info)) {
            return FALSE;
        }
    }
    else if(isalpha(*info->p)) {
        char buf[VAR_NAME_MAX];

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
                    add_variable_to_table(info->lv_table, buf, node_type);
                }
            }
            else {
                node_type = NULL;
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
                    *node = sNodeTree_create_assign_variable(buf, node_type, right_node, info->klass);
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
                *node = sNodeTree_create_assign_variable(buf, NULL, right_node, info->klass);
            }
        }
        else {
            sCLClass* klass = get_class(buf);

            if(klass == NULL) {
                klass = load_class(buf);
            }

            /// class name ///
            if(klass) {
                /// class field or class method ///
                if(*info->p == '.') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    char buf[VAR_NAME_MAX];

                    /// name ///
                    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
                        return FALSE;
                    }

                    /// class method ///
                    if(*info->p == '(') {
                        unsigned int params[PARAMS_MAX];
                        int num_params = 0;

                        if(!parse_method_params(&num_params, params, info)) {
                            return FALSE;
                        }

                        *node = sNodeTree_create_class_method_call(klass, buf, params, num_params);
                    }
                    /// class field ///
                    else {
                        if(*info->p == '=' && *(info->p +1) != '=') {
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
                }
            }
            /// load variable ///
            else {
                *node = sNodeTree_create_load_variable(buf);
            }
        }
    }
    /// comment ///
    else if(*info->p == '/' && *(info->p+1) == '*') {
        info->p+=2;
        int nest = 0;

        while(*info->p) {
            if(*info->p == '*' && *(info->p+1) == '/') {
                info->p+=2;

                if(nest == 0) {
                    break;
                }

                nest--;
            }
            else if(*info->p == '/' && *(info->p+1) == '*') {
                info->p+=2;
                nest++;
            }
            else if(*info->p == '\n') {
                info->p++;
                info->sline++;
            }
            else {
                info->p++;
            }
        }
    }
    /// comment2 ///
    else if(*info->p == '#') {
        info->p++;

        while(*info->p) {
            if(*info->p == '\n') {
                info->p++;
                info->sline++;
                break;
            }
            else {
                info->p++;
            }
        }
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
    if(!postposition_operator(node, info))
    {
        return FALSE;
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

// from left to right order
static BOOL expression_mult_div(unsigned int* node, sParserInfo* info)
{
    if(!expression_monadic_operator(node, info)) {
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
            if(!expression_monadic_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator *");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpMult, *node, right, 0);
        }
        else if(*info->p == '/' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_monadic_operator(&right, info)) {
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
            if(!expression_monadic_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator ^");
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

            *node = sNodeTree_create_operand(kOpAndAnd, *node, right, 0);
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

            *node = sNodeTree_create_operand(kOpOrOr, *node, right, 0);
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

            *node = sNodeTree_create_operand(kOpConditional, *node, right, middle);
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

