#include "common.h"

void array_mark_fun(CLObject self, unsigned char* mark_flg)
{
    sCLObject* object = CLOBJECT(self);

    int array_num = object->mArrayNum;

    CLVALUE* elements = (CLVALUE*)object->mFields;

    int i;
    for(i=0; i<array_num; i++) {
        mark_object(elements->mObjectValue, mark_flg);
        elements++;
    }
}

static unsigned int object_size(sCLClass* klass, int array_num)
{
    unsigned int size;

    size = sizeof(sCLObject) - sizeof(CLVALUE) * DUMMY_ARRAY_SIZE;
    size += (unsigned int)sizeof(CLVALUE) * array_num;

    /// align to 4 byte boundry
    size = (size + 3) & ~3;

    return size;
}

CLObject create_array_object(sCLClass* klass, int array_num)
{
    int size = object_size(klass, array_num);

    CLObject obj = alloc_heap_mem(size, klass, array_num);

    return obj;
}

