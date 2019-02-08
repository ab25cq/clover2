#include "common.h"

static unsigned int object_size()
{
    unsigned int size;

    size = sizeof(sBlockObject);

    alignment(&size);

    return size;
}

void block_mark_fun(CLObject self, unsigned char* mark_flg)
{
    sBlockObject* object_data = CLBLOCK(self);

    CLVALUE* value = object_data->mParentStack;
    int parent_var_num = object_data->mParentVarNum;
    int i;
    for(i=0; i<parent_var_num; i++) {
        mark_object(value[i].mObjectValue, mark_flg);
    }
}

void free_block(CLObject self)
{
    sBlockObject* object_data = CLBLOCK(self);

    sConst_free(&object_data->mConstant);
    sByteCode_free(&object_data->mCodes);
}

CLObject create_block_object(sByteCode* codes, sConst* constant, CLVALUE* parent_stack, int parent_var_num, int block_var_num, BOOL lambda, int block_id, sCLClass* klass, sVMInfo* info)
{
    unsigned int size = object_size();

    sCLClass* lambda_klass = get_class("lambda", FALSE);

    MASSERT(lambda_klass != NULL);

    CLObject obj = alloc_heap_mem(size, lambda_klass, -2, info);

    sBlockObject* object_data = CLBLOCK(obj);

    sByteCode_clone(&object_data->mCodes, codes);
    sConst_clone(&object_data->mConstant, constant);

    object_data->mParentStack = parent_stack;
    object_data->mParentVarNum = parent_var_num;
    object_data->mBlockVarNum = block_var_num;
    object_data->mLambda = lambda;
    object_data->mBlockID = block_id;
    object_data->mClass2 = klass;

//printf("create_block_object %d\n", obj);

    return obj;
}
