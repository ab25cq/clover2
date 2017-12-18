#include "common.h"

CLObject create_char(wchar_t value)
{
    sCLClass* klass = get_class("Char");
    CLObject obj = create_object(klass, "Char");

    sCLObject* obj_data = CLOBJECT(obj);

    obj_data->mFields[0].mCharValue = value;
    
    return obj;
}
