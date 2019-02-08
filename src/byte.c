#include "common.h"

CLObject create_byte(char value, sVMInfo* info)
{
    sCLClass* klass = get_class("Byte", FALSE);
    CLObject obj = create_object(klass, "Byte", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mByteValue = value;

    return obj;
}

CLObject create_ubyte(unsigned char value, sVMInfo* info)
{
    sCLClass* klass = get_class("UByte", FALSE);
    CLObject obj = create_object(klass, "UByte", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mUByteValue = value;
    
    return obj;
}

