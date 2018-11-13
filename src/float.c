#include "common.h"

CLObject create_float(float value, sVMInfo* info)
{
    sCLClass* klass = get_class("Float");
    CLObject obj = create_object(klass, "Float", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mFloatValue = value;
    
    return obj;
}

CLObject create_double(double value, sVMInfo* info)
{
    sCLClass* klass = get_class("Double");
    CLObject obj = create_object(klass, "Double", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mDoubleValue = value;

    return obj;
}
