#include "common.h"

CLObject create_integer(int value)
{
    sCLClass* klass = get_class("Integer");
    CLObject obj = create_object(klass, "Integer");

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mIntValue = value;
    
    return obj;
}


CLObject create_uinteger(unsigned int value)
{
    sCLClass* klass = get_class("UInteger");
    CLObject obj = create_object(klass, "UInteger");

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mUIntValue = value;
    
    return obj;
}

