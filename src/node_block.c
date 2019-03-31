#include "common.h"

sNodeBlock* sNodeBlock_alloc(BOOL clone)
{
    sNodeBlock* block = MCALLOC(1, sizeof(sNodeBlock));

    block->mSizeNodes = 32;
    block->mNumNodes = 0;
    if(clone) {
        block->mNodes = NULL;
    }
    else {
        block->mNodes = MCALLOC(1, sizeof(unsigned int)*block->mSizeNodes);
    }
    block->mLVTable = NULL;
    block->mUnClosedBlock = FALSE;
    if(!clone) {
        sBuf_init(&block->mSource);
    }

    return block;
}

void sNodeBlock_free(sNodeBlock* block)
{
    if(block->mNodes) MFREE(block->mNodes);
    MFREE(block->mSource.mBuf);
    MFREE(block);
}

sNodeBlock* sNodeBlock_clone(sNodeBlock* block)
{
    sNodeBlock* result = sNodeBlock_alloc(TRUE);

    result->mNumNodes = block->mNumNodes;
    result->mSizeNodes = block->mSizeNodes;
    result->mNodes = MCALLOC(1, sizeof(unsigned int)*block->mSizeNodes);

    int i;
    for(i=0; i<block->mNumNodes; i++) {
        result->mNodes[i] = block->mNodes[i];
    }

    result->mLVTable = clone_var_table(block->mLVTable);

    result->mUnClosedBlock = block->mUnClosedBlock;

    sBuf_clone(&result->mSource, &block->mSource);

    result->mSName = block->mSName;
    result->mSLine = block->mSLine;

    return result;
}

void append_node_to_node_block(sNodeBlock* node_block, unsigned int node)
{
    if(node_block->mSizeNodes <= node_block->mNumNodes) {
        int new_size = node_block->mSizeNodes * 2;
        node_block->mNodes = MREALLOC(node_block->mNodes, sizeof(unsigned int)*new_size);
        memset(node_block->mNodes + node_block->mSizeNodes, 0, sizeof(unsigned int)*(new_size-node_block->mSizeNodes));
    }

    node_block->mNodes[node_block->mNumNodes] = node;
    node_block->mNumNodes++;
}

BOOL parse_block(ALLOC sNodeBlock** node_block, sParserInfo* info, sVarTable* new_table, BOOL block_object, BOOL string_expression, unsigned int pre_block_node, char* for_in_item_name)
{
    //expect_next_character_with_one_forward("{", info);

    *node_block = sNodeBlock_alloc(FALSE);

    sVarTable* old_vtable = info->lv_table;
    if(new_table) {
        info->lv_table = new_table;
    }
    else {
        info->lv_table = init_block_vtable(old_vtable);
    }

    if(for_in_item_name) {
        check_already_added_variable(info->lv_table, for_in_item_name, info);
        add_variable_to_table(info->lv_table, for_in_item_name, NULL, FALSE);
    }

    if(pre_block_node != 0) {
        append_node_to_node_block(*node_block, pre_block_node);
    }

    (*node_block)->mSName = info->sname;
    (*node_block)->mSLine = info->sline;
    
    char* source_head = info->p;

    while(1) {
        if(*info->p == '}') {
            info->p++;
            if(!string_expression) skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            (*node_block)->mUnClosedBlock = TRUE;

            if(!block_object) {
                set_max_block_var_num(info->lv_table, old_vtable);
            }
            (*node_block)->mLVTable = info->lv_table;

            //info->lv_table = old_vtable;   // for interpreter completion

            char* source_end = info->p;

            sBuf_append(&(*node_block)->mSource, source_head, source_end - source_head);
            sBuf_append_char(&(*node_block)->mSource, '\0');

            return TRUE;
        }

        unsigned int node = 0;

        if(!expression(&node, info)) {
            sNodeBlock_free(*node_block);

            //info->lv_table = old_vtable;   // for interpreter completion
            return FALSE;
        }

        if(node == 0) {
            if(info->get_type_for_interpreter) {
                return FALSE;
            }
            else {
                parser_err_msg(info, "require an expression");
                info->err_num++;
                break;
            }
        }

        append_node_to_node_block(*node_block, node);

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(*info->p == '}') {
            info->p++;
            if(!string_expression) skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "require } before the source end");
            info->err_num++;

            (*node_block)->mUnClosedBlock = TRUE;

            if(!block_object) {
                set_max_block_var_num(info->lv_table, old_vtable);
            }
            (*node_block)->mLVTable = info->lv_table;

            //info->lv_table = old_vtable;   // for interpreter completion

            char* source_end = info->p;

            sBuf_append(&(*node_block)->mSource, source_head, source_end - source_head);
            sBuf_append_char(&(*node_block)->mSource, '\0');

            return TRUE;
        }
    }

    char* source_end = info->p;

    sBuf_append(&(*node_block)->mSource, source_head, source_end - source_head);
    sBuf_append_char(&(*node_block)->mSource, '\0');

    if(!block_object) {
        set_max_block_var_num(info->lv_table, old_vtable);
    }
    (*node_block)->mLVTable = info->lv_table;
    info->lv_table = old_vtable;

    return TRUE;
}

void make_block_for_for_expresssion(ALLOC sNodeBlock** node_block, sParserInfo* info, unsigned int for_expression)
{
    *node_block = sNodeBlock_alloc(FALSE);

    sVarTable* old_vtable = info->lv_table;
    info->lv_table = init_block_vtable(old_vtable);
}

BOOL create_null_block(ALLOC sNodeBlock** node_block, sParserInfo* info, sVarTable* new_table, BOOL block_object)
{
    *node_block = sNodeBlock_alloc(FALSE);

    sVarTable* old_vtable = info->lv_table;
    if(new_table) {
        info->lv_table = new_table;
    }
    else {
        info->lv_table = init_block_vtable(old_vtable);
    }

    (*node_block)->mSName = info->sname;
    (*node_block)->mSLine = info->sline;

    sBuf_append_char(&(*node_block)->mSource, '\0');

    if(!block_object) {
        set_max_block_var_num(info->lv_table, old_vtable);
    }
    (*node_block)->mLVTable = info->lv_table;
    info->lv_table = old_vtable;

    return TRUE;
}

BOOL parse_question_operator_block(unsigned int object_node, int num_method_chains, ALLOC sNodeBlock** node_block, sParserInfo* info)
{
    *node_block = ALLOC sNodeBlock_alloc(FALSE);

    sVarTable* old_vtable = info->lv_table;
    info->lv_table = init_block_vtable(old_vtable);

    (*node_block)->mSName = info->sname;
    (*node_block)->mSLine = info->sline;

    char* source_head = info->p;

    unsigned int node2 = object_node;

    while(*info->p == '.') {
        info->p++;
        skip_spaces_and_lf(info);

        char buf[METHOD_NAME_MAX];

        if(!parse_word(buf, METHOD_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        unsigned int params[PARAMS_MAX];
        int num_params = 0;

        if(!parse_method_params(&num_params, params, info)) {
            return FALSE;
        }

        node2 = sNodeTree_create_method_call(node2, buf, params, num_params, num_method_chains, info);
    }

    append_node_to_node_block(*node_block, node2);

    char* source_end = info->p;

    sBuf_append(&(*node_block)->mSource, source_head, source_end - source_head);
    sBuf_append_char(&(*node_block)->mSource, '\0');

    (*node_block)->mLVTable = info->lv_table;
    info->lv_table = old_vtable;

    return TRUE;
}

BOOL compile_block(sNodeBlock* block, sCompileInfo* info, sNodeType* result_type, sNodeType** block_last_type)
{
    sVarTable* old_table = info->lv_table;
    info->lv_table = block->mLVTable;

    int stack_num_before = info->stack_num;
    info->stack_num = 0;

    int i;
    for(i=0; i<block->mNumNodes; i++) {
        unsigned int node = block->mNodes[i];

        info->sname = gNodes[node].mSName;
        info->sline = gNodes[node].mLine;

        append_opecode_to_code(info->code, OP_HEAD_OF_EXPRESSION, info->no_output);

        if(!compile(node, info)) {
            info->lv_table = old_table;
            info->stack_num = stack_num_before;
            return FALSE;
        }

        append_opecode_to_code(info->code, OP_SIGINT, info->no_output);

        *block_last_type = info->type;

        if(i == block->mNumNodes -1 && result_type) {
            if(boxing_posibility(result_type, *block_last_type)) {
                boxing_to_lapper_class(block_last_type, info);
            }

            if(info->stack_num > 1) {
                append_opecode_to_code(info->code, OP_POP_N, info->no_output);
                append_int_value_to_code(info->code, info->stack_num-1, info->no_output);
            }
        }
        else {
            arrange_stack(info);
        }
    }

    if(block->mNumNodes == 0) {
        append_opecode_to_code(info->code, OP_HEAD_OF_EXPRESSION, info->no_output);

        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
        info->stack_num++;

        append_opecode_to_code(info->code, OP_SIGINT, info->no_output);;

        info->type = create_node_type_with_class_name("Null", info->pinfo->mJS);

        arrange_stack(info);

        *block_last_type = info->type;
    }

    info->stack_num = stack_num_before;
    info->lv_table = old_table;

    return TRUE;
}

BOOL compile_block_with_result(sNodeBlock* block, sCompileInfo* info)
{
    sVarTable* old_table = info->lv_table;
    info->lv_table = block->mLVTable;

    int stack_num_before = info->stack_num;
    info->stack_num = 0;

    int i;
    for(i=0; i<block->mNumNodes; i++) {
        unsigned int node = block->mNodes[i];

        info->sname = gNodes[node].mSName;
        info->sline = gNodes[node].mLine;

        append_opecode_to_code(info->code, OP_HEAD_OF_EXPRESSION, info->no_output);

        if(!compile(node, info)) {
            info->lv_table = old_table;
            info->stack_num = stack_num_before;
            return FALSE;
        }

        append_opecode_to_code(info->code, OP_SIGINT, info->no_output);

        if(i == block->mNumNodes-1) {
            if(info->stack_num == 0) {
                append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
                info->stack_num++;

                info->type = create_node_type_with_class_name("Null", info->pinfo->mJS);
            }
            else if(info->stack_num < 0) {
                compile_err_msg(info, "Unexpected error. Stack pointer is invalid(stack number is %d)", info->stack_num);
                info->err_num++;
            }
            else if(info->stack_num == 1) {
            }
            else {
                int i;
                for(i=0; i<info->stack_num-1; i++) {
                    append_opecode_to_code(info->code, OP_REVERSE, info->no_output);
                    append_opecode_to_code(info->code, OP_POP, info->no_output);
                    info->stack_num--;
                }
            }
        }
        else {
            arrange_stack(info);
        }
    }

    if(block->mNumNodes == 0) {
        append_opecode_to_code(info->code, OP_HEAD_OF_EXPRESSION, info->no_output);

        append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
        info->stack_num++;

        info->type = create_node_type_with_class_name("Null", info->pinfo->mJS);

        append_opecode_to_code(info->code, OP_SIGINT, info->no_output);

        if(info->stack_num == 0) {
            append_opecode_to_code(info->code, OP_LDCNULL, info->no_output);
            info->stack_num++;

            info->type = create_node_type_with_class_name("Null", info->pinfo->mJS);
        }
        else if(info->stack_num < 0) {
            compile_err_msg(info, "Unexpected error. Stack pointer is invalid(stack number is %d)", info->stack_num);
            info->err_num++;
        }
        else if(info->stack_num == 1) {
        }
        else {
            int i;
            for(i=0; i<info->stack_num-1; i++) {
                append_opecode_to_code(info->code, OP_REVERSE, info->no_output);
                append_opecode_to_code(info->code, OP_POP, info->no_output);
                info->stack_num--;
            }
        }
    }

    info->stack_num = stack_num_before;
    info->stack_num++;
    info->lv_table = old_table;

    return TRUE;
}