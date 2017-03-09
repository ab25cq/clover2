#include "common.h"
#include <wchar.h>

CLObject create_string_object(char* str)
{
    /// convert str to wstr ///
    int len = strlen(str);

    wchar_t* wstr = MCALLOC(1, sizeof(wchar_t)*(len+1));

    int size_wcs = mbstowcs(wstr, str, len+1);
    
    if(size_wcs < 0) {
        MFREE(wstr);
        return 0;
    }

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

    CLObject buffer = create_array_object(char_class, size_wcs+1);
    sCLObject* buffer_data = CLOBJECT(buffer);

    int i;
    for(i=0; i<size_wcs; i++) {
        buffer_data->mFields[i].mCharValue = wstr[i];
    }
    buffer_data->mFields[i].mCharValue = L'\0';

    /// entry char array to object ///
    sCLObject* obj_data = CLOBJECT(obj);
    obj_data->mFields[0].mObjectValue = buffer;
    obj_data->mFields[1].mIntValue = size_wcs;
    obj_data->mFields[2].mIntValue = size_wcs+1;

    /// pop object ///
    gGlobalStackPtr--;

    MFREE(wstr);

    return obj;
}

CLObject create_buffer_object(char* buffer, size_t size)
{
    /// create object ///
    sCLClass* buffer_class = get_class("Buffer");
    MASSERT(buffer_class != NULL);

    CLObject obj = create_object(buffer_class);

    sCLObject* object_data = CLOBJECT(obj);

    object_data->mFields[0].mPointerValue = MCALLOC(1, size);  // bufffer
    memcpy(object_data->mFields[0].mPointerValue, buffer, size);

    object_data->mFields[1].mULongValue = size;                  // len
    object_data->mFields[2].mULongValue = size;                  // size

    return obj;
}

CLObject create_path_object(char* path)
{
    /// create object ///
    sCLClass* path_class = get_class("Path");
    MASSERT(path_class != NULL);

    CLObject str_object = create_string_object(path);

    gGlobalStackPtr->mObjectValue = str_object;
    gGlobalStackPtr++;

    CLObject obj = create_object(path_class);

    sCLObject* object_data = CLOBJECT(obj);

    object_data->mFields[0].mObjectValue = str_object;

    gGlobalStackPtr--;

    return obj;
}

