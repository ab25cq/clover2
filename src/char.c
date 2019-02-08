#include "common.h"

CLObject create_char(wchar_t value, sVMInfo* info)
{
    sCLClass* klass = get_class("Char", FALSE);
    CLObject obj = create_object(klass, "Char", info);

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mCharValue = value;

    return obj;
}
