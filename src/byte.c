#include "common.h"

CLObject create_byte(char value)
{
    sCLClass* klass = get_class("Byte");
    CLObject obj = create_object(klass);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mByteValue = value;
    
    return obj;
}

CLObject create_ubyte(unsigned char value)
{
    sCLClass* klass = get_class("UByte");
    CLObject obj = create_object(klass);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mUByteValue = value;
    
    return obj;
}

