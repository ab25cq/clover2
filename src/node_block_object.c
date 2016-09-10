#include "common.h"

sNodeBlockObject* alloc_node_block_object()
{
    sNodeBlockObject* block = MCALLOC(1, sizeof(sNodeBlockObject));
    return block;
}

void free_node_block_object(sNodeBlockObject* block)
{
    MFREE(block);
}

sNodeBlockObject* clone_node_block_object(sNodeBlockObject* block)
{
    sNodeBlockObject* self = alloc_node_block_object();

    self->mNumParams = block->mNumParams;

    int i;
    for(i=0; i<block->mNumParams; i++) {
        self->mParams[i] = clone_node_type(block->mParams[i]);
    }

    self->mResultType = clone_node_type(block->mResultType);

    return self;
}

BOOL substitution_posibility_for_node_block_object(sNodeBlockObject* left_block, sNodeBlockObject* right_block)
{
    if(type_identify(left_block->mResultType, right_block->mResultType)) {
        if(left_block->mNumParams == right_block->mNumParams) {
            int i;
            for(i=0; i<left_block->mNumParams; i++) {
                if(!type_identify(left_block->mParams[i], right_block->mParams[i]))
                {
                    return FALSE;
                }
            }

            return TRUE;
        }
    }

    return FALSE;
}

