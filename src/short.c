#include "common.h"

CLObject create_short(short value)
{
    sCLClass* klass = get_class("Short");
    CLObject obj = create_object(klass);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mShortValue = value;
    
    return obj;
}


CLObject create_ushort(unsigned short value)
{
    sCLClass* klass = get_class("UShort");
    CLObject obj = create_object(klass);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mUShortValue = value;
    
    return obj;
}

