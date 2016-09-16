#include "common.h"

CLObject create_bool(BOOL value)
{
    sCLClass* klass = get_class("Bool");
    CLObject obj = create_object(klass);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mBoolValue = value;
    
    return obj;
}
