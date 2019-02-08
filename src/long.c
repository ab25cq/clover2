#include "common.h"

CLObject create_long(clint64 value, sVMInfo* info)
{
    sCLClass* klass = get_class("Long", FALSE);
    CLObject obj = create_object(klass, "Long", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mLongValue = value;

    return obj;
}

CLObject create_ulong(unsigned clint64 value, sVMInfo* info)
{
    sCLClass* klass = get_class("ULong", FALSE);
    CLObject obj = create_object(klass, "ULong", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mULongValue = value;

    return obj;
}

