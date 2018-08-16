#include "common.h"

CLObject create_bool(BOOL value, sVMInfo* info)
{
    sCLClass* klass = get_class("Bool");
    CLObject obj = create_object(klass, "Bool", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mBoolValue = (value ? 1:0);
    
    return obj;
}
