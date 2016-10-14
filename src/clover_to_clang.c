#include "common.h"

ALLOC wchar_t* string_object_to_wchar_array(CLObject string_object)
{
    sCLObject* string_object_data = CLOBJECT(string_object);
    CLObject wstr_array = string_object_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_data = CLOBJECT(wstr_array);

    int len = wstr_array_data->mArrayNum;

    wchar_t* wstr = MCALLOC(1, sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wstr_array_data->mFields[i].mCharValue;
    }
    wstr[i] = '\0';

    return wstr;
}

NULLABLE CLVALUE* get_element_from_array(CLObject array, int index)
{
    sCLObject* array_data = CLOBJECT(array);

    if(index < array_data->mArrayNum) {
        return array_data->mFields + index;
    }
    else {
        return NULL;
    }
}
