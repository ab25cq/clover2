#include "common.h"

static sNodeBlock* sNodeBlock_alloc()
{
    sNodeBlock* block = MCALLOC(1, sizeof(sNodeBlock));

    block->mSizeNodes = 32;
    block->mNumNodes = 0;
    block->mNodes = MCALLOC(1, sizeof(unsigned int)*block->mSizeNodes);

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

BOOL parse_normal_block(ALLOC sNodeBlock** node_block, sParserInfo* info)
{
    expect_next_character_with_one_forward("{", info);

    *node_block = sNodeBlock_alloc();

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);

        return TRUE;
    }

    while(1) {
        unsigned int node = 0;

        if(!expression(&node, info)) {
            sNodeBlock_free(*node_block);
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
        else if(*info->p == 0) {
            parser_err_msg(info, "require } before the source end");
            break;
        }
    }

    return TRUE;
}

BOOL compile_normal_block(sNodeBlock* block, sCompileInfo* info)
{
    int i;
    for(i=0; i<block->mNumNodes; i++) {
        unsigned int node = block->mNodes[i];

        if(!compile(node, info)) {
            return FALSE;
        }

        arrange_stack(info);
    }

    return TRUE;
}


