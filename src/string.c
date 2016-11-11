#include "common.h"

CLObject create_string_object(char* str)
{
    /// convert str to wstr ///
    int len = strlen(str);

    wchar_t* wstr = MCALLOC(1, sizeof(wchar_t)*(len+1));

    (void)mbstowcs(wstr, str, len+1);

    /// create object ///
    sCLClass* string_class = get_class("String");
    MASSERT(string_class != NULL);

    CLObject obj = create_object(string_class);

    /// push object ///
    gGlobalStackPtr->mObjectValue = obj;
    gGlobalStackPtr++;

    /// create char array ///
    sCLClass* char_class = get_class("char");
    MASSERT(char_class != NULL);

    CLObject buffer = create_array_object(char_class, len+1);
    sCLObject* buffer_data = CLOBJECT(buffer);

    int i;
    for(i=0; i<len; i++) {
        buffer_data->mFields[i].mCharValue = wstr[i];
    }
    buffer_data->mFields[i].mCharValue = '\0';

    /// entry char array to object ///
    sCLObject* obj_data = CLOBJECT(obj);
    obj_data->mFields[0].mObjectValue = buffer;
    obj_data->mFields[1].mIntValue = len + 1;
    obj_data->mFields[2].mIntValue = len;

    /// pop object ///
    gGlobalStackPtr--;

    MFREE(wstr);

    return obj;
}

CLObject create_buffer_object(char* str)
{
    /// create object ///
    sCLClass* buffer_class = get_class("Buffer");
    MASSERT(buffer_class != NULL);

    CLObject obj = create_object(buffer_class);

    sCLObject* object_data = CLOBJECT(obj);

    int len = strlen(str);

    object_data->mFields[0].mPointerValue = MSTRDUP(str);       // buffer
    object_data->mFields[1].mIntValue = len;                   // len
    object_data->mFields[2].mIntValue = len+1;                 // size

    return obj;
}

