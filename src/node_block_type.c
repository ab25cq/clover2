#include "common.h"

static sNodeBlockType** gNodeBlockTypes = NULL;
static int gUsedPageNodeBlockTypes = 0;
static int gSizePageNodeBlockTypes = 0;
static int gUsedNodeBlockTypes = 0;

#define NODE_TYPE_PAGE_SIZE 64

void init_node_block_types()
{
    const int size_page_node_block_types = 4;

    if(gSizePageNodeBlockTypes == 0) {
        gNodeBlockTypes = MCALLOC(1, sizeof(sNodeBlockType*)*size_page_node_block_types);

        int i;
        for(i=0; i<size_page_node_block_types; i++) {
            gNodeBlockTypes[i] = MCALLOC(1, sizeof(sNodeBlockType)*NODE_TYPE_PAGE_SIZE);
        }

        gSizePageNodeBlockTypes = size_page_node_block_types;
        gUsedPageNodeBlockTypes = 0;
        gUsedNodeBlockTypes = 0;
    }
}

void free_node_block_types()
{
    if(gSizePageNodeBlockTypes > 0) {
        int i;
        for(i=0; i<gSizePageNodeBlockTypes; i++) {
            MFREE(gNodeBlockTypes[i]);
        }
        MFREE(gNodeBlockTypes);

        gSizePageNodeBlockTypes = 0;
        gUsedPageNodeBlockTypes = 0;
        gUsedNodeBlockTypes = 0;
    }
}

sNodeBlockType* alloc_node_block_type()
{
    MASSERT(gNodeBlockTypes != NULL && gSizePageNodeBlockTypes > 0); // Is the node block types initialized ?

    if(gUsedNodeBlockTypes == NODE_TYPE_PAGE_SIZE) {
        gUsedNodeBlockTypes = 0;
        gUsedPageNodeBlockTypes++;

        if(gUsedPageNodeBlockTypes == gSizePageNodeBlockTypes) {
            int new_size = (gSizePageNodeBlockTypes+1) * 2;
            gNodeBlockTypes = MREALLOC(gNodeBlockTypes, sizeof(sNodeBlockType*)*new_size);
            memset(gNodeBlockTypes + gSizePageNodeBlockTypes, 0, sizeof(sNodeBlockType*)*(new_size - gSizePageNodeBlockTypes));

            int i;
            for(i=gSizePageNodeBlockTypes; i<new_size; i++) {
                gNodeBlockTypes[i] = MCALLOC(1, sizeof(sNodeBlockType)*NODE_TYPE_PAGE_SIZE);
            }

            gSizePageNodeBlockTypes = new_size;
        }
    }

    return &gNodeBlockTypes[gUsedPageNodeBlockTypes][gUsedNodeBlockTypes++];
}

ALLOC sNodeBlockType* clone_node_block_type(sNodeBlockType* block)
{
    sNodeBlockType* self = alloc_node_block_type();

    self->mNumParams = block->mNumParams;

    int i;
    for(i=0; i<block->mNumParams; i++) {
        self->mParams[i] = clone_node_type(block->mParams[i]);
    }

    self->mResultType = clone_node_type(block->mResultType);

    self->mLambda = block->mLambda;

    return self;
}

BOOL substitution_posibility_for_node_block_type(sNodeBlockType* left_block, sNodeBlockType* right_block, sNodeType* left_generics_types, sNodeType* right_generics_types, BOOL output_message)
{
    /// result type ///
    if(substitution_posibility(left_block->mResultType, right_block->mResultType, NULL, NULL, NULL, NULL, output_message)) {
        if(left_block->mNumParams == right_block->mNumParams) {
            int i;
            for(i=0; i<left_block->mNumParams; i++) {
                sNodeType* left_solved_param;
                sNodeType* right_solved_param;

                if(left_generics_types) {
                    sNodeType* param = left_block->mParams[i];

                    if(!solve_generics_types_for_node_type(param, ALLOC &left_solved_param, left_generics_types, TRUE, FALSE)) 
                    {
                        return FALSE;
                    }
                }
                else {
                    left_solved_param = left_block->mParams[i];
                }

                if(right_generics_types) {
                    sNodeType* param = right_block->mParams[i];

                    if(!solve_generics_types_for_node_type(param, ALLOC &right_solved_param, left_generics_types, TRUE, FALSE)) 
                    {
                        return FALSE;
                    }
                }
                else {
                    right_solved_param = right_block->mParams[i];
                }

                if(!substitution_posibility(left_solved_param, right_solved_param, NULL, NULL, NULL, NULL, output_message))
                {
                    return FALSE;
                }
            }

            return TRUE;
        }
    }

    return FALSE;
}

