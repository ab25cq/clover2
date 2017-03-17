#include "common.h"

static sNodeBlock* sNodeBlock_alloc()
{
    sNodeBlock* block = MCALLOC(1, sizeof(sNodeBlock));

    block->mSizeNodes = 32;
    block->mNumNodes = 0;
    block->mNodes = MCALLOC(1, sizeof(unsigned int)*block->mSizeNodes);
    block->mLVTable = NULL;

    return block;
}

void sNodeBlock_free(sNodeBlock* block)
{
    if(block->mNodes) MFREE(block->mNodes);
    MFREE(block);
}

static void append_node_to_node_block(sNodeBlock* node_block, unsigned int node)
{
    if(node_block->mSizeNodes <= node_block->mNumNodes) {
        int new_size = node_block->mSizeNodes * 2;
        node_block->mNodes = MREALLOC(node_block->mNodes, sizeof(unsigned int)*new_size);
        memset(node_block->mNodes + node_block->mSizeNodes, 0, sizeof(unsigned int)*(new_size-node_block->mSizeNodes));
    }

    node_block->mNodes[node_block->mNumNodes] = node;
    node_block->mNumNodes++;
}

BOOL parse_block(ALLOC sNodeBlock** node_block, sParserInfo* info, sVarTable* new_table, BOOL block_object)
{
    expect_next_character_with_one_forward("{", info);

    *node_block = sNodeBlock_alloc();

    sVarTable* old_vtable = info->lv_table;
    if(new_table) {
        info->lv_table = new_table;
    }
    else {
        info->lv_table = init_block_vtable(old_vtable);
    }

    while(1) {
        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }

        unsigned int node = 0;

        if(!expression(&node, info)) {
            sNodeBlock_free(*node_block);

            info->lv_table = old_vtable;
            return FALSE;
        }

        if(node == 0) {
            parser_err_msg(info, "require an expression");
            info->err_num++;
            break;
        }

        append_node_to_node_block(*node_block, node);

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "require } before the source end");
            info->err_num++;

            info->lv_table = old_vtable;
            return TRUE;
        }
    }

    if(!block_object) {
        set_max_block_var_num(info->lv_table, old_vtable);
    }
    (*node_block)->mLVTable = info->lv_table;
    info->lv_table = old_vtable;

    return TRUE;
}

BOOL compile_block(sNodeBlock* block, sCompileInfo* info)
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
        append_str_to_constant_pool_and_code(info->constant, info->code, info->sname, info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);

        if(!compile(node, info)) {
            info->lv_table = old_table;
            info->stack_num = stack_num_before;
            return FALSE;
        }
        arrange_stack(info);

#ifdef ENABLE_INTERPRETER
        append_opecode_to_code(info->code, OP_SIGINT, info->no_output);
#endif
    }

    info->stack_num = stack_num_before;

    info->lv_table = old_table;

    return TRUE;
}


