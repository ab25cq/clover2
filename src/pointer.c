#include "common.h"

CLObject create_pointer(char* value)
{
    sCLClass* klass = get_class("Pointer");
    CLObject obj = create_object(klass, "Pointer");

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mPointerValue = value;

    return obj;
}
