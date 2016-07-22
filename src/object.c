#include "common.h"

void object_mark_fun(CLObject self, unsigned char* mark_flg)
{
    sCLObject* object = CLOBJECT(self);

    int i;
    for(i=0; i<object->mNumFields; i++) {
        mark_object(object->mFields[i].mObjectValue, mark_flg);
    }
}

BOOL free_object(CLObject self)
{
    sCLObject* object = CLOBJECT(self);
    sCLClass* klass = object->mClass;


    if(!call_finalize_method_on_free_object(klass, self)) {
        return FALSE;
    }

    return TRUE;
}

static unsigned int object_size(sCLClass* klass)
{
    unsigned int size;

    size = sizeof(sCLObject) - sizeof(CLVALUE) * DUMMY_ARRAY_SIZE;
    size += (unsigned int)sizeof(CLVALUE) * klass->mNumFields;

    /// align to 4 byte boundry
    size = (size + 3) & ~3;

    return size;
}

CLObject create_object(sCLClass* klass)
{
    int size = object_size(klass);

    CLObject obj = alloc_heap_mem(size, klass, -1);

    return obj;
}

