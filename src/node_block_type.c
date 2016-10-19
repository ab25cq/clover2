#include "common.h"

sNodeBlockType* alloc_node_block_type()
{
    sNodeBlockType* block = MCALLOC(1, sizeof(sNodeBlockType));
    return block;
}

void free_node_block_type(sNodeBlockType* block)
{
    MFREE(block);
}

sNodeBlockType* clone_node_block_type(sNodeBlockType* block)
{
    sNodeBlockType* self = alloc_node_block_type();

    self->mNumParams = block->mNumParams;

    int i;
    for(i=0; i<block->mNumParams; i++) {
        self->mParams[i] = clone_node_type(block->mParams[i]);
    }

    self->mResultType = clone_node_type(block->mResultType);

    return self;
}

BOOL substitution_posibility_for_node_block_type(sNodeBlockType* left_block, sNodeBlockType* right_block, sNodeType* left_generics_types, sNodeType* right_generics_types)
{
    if(type_identify(left_block->mResultType, right_block->mResultType)) {
        if(left_block->mNumParams == right_block->mNumParams) {
            int i;
            for(i=0; i<left_block->mNumParams; i++) {
                sNodeType* left_solved_param;
                sNodeType* right_solved_param;

                if(left_generics_types) {
                    sNodeType* param = left_block->mParams[i];

                    if(!solve_generics_types_for_node_type(param, ALLOC &left_solved_param, left_generics_types)) 
                    {
                        return FALSE;
                    }
                }
                else {
                    left_solved_param = left_block->mParams[i];
                }

                if(right_generics_types) {
                    sNodeType* param = right_block->mParams[i];

                    if(!solve_generics_types_for_node_type(param, ALLOC &right_solved_param, left_generics_types)) 
                    {
                        return FALSE;
                    }
                }
                else {
                    right_solved_param = right_block->mParams[i];
                }

                if(!type_identify(left_solved_param, right_solved_param))
                {
                    return FALSE;
                }
            }

            return TRUE;
        }
    }

    return FALSE;
}

