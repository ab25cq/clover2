#include "common.h"

CLObject create_long(clint64 value)
{
    sCLClass* klass = get_class("Long");
    CLObject obj = create_object(klass, "Long");

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mLongValue = value;
    
    return obj;
}

CLObject create_ulong(unsigned clint64 value)
{
    sCLClass* klass = get_class("ULong");
    CLObject obj = create_object(klass, "ULong");

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mULongValue = value;
    
    return obj;
}

