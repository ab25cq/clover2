#include "common.h"

static unsigned int object_size()
{
    unsigned int size;

    size = sizeof(sBlockObject);

    /// align to 4 byte boundry
    size = (size + 3) & ~3;

    return size;
}

CLObject create_block_object(sByteCode* codes, sConst* constant, CLVALUE* parent_stack, int parent_var_num, int block_var_num)
{
    int size = object_size();

    sCLClass* klass = get_class("block");

    MASSERT(klass != NULL);

    CLObject obj = alloc_heap_mem(size, klass, -1);

    sBlockObject* object_data = CLBLOCK(obj);

    object_data->mCodes = *codes; // copy struct
    object_data->mConstant = *constant; // copy struct
    object_data->mParentStack = parent_stack;
    object_data->mParentVarNum = parent_var_num;
    object_data->mBlockVarNum = block_var_num;

    return obj;
}

