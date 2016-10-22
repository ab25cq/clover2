#include "common.h"
#include <wchar.h>

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

ALLOC char* string_object_to_char_array(CLObject string_object)
{
    wchar_t* wstr = ALLOC string_object_to_wchar_array(string_object);
    int len = wcslen(wstr);

    int size = sizeof(char)* MB_LEN_MAX * (len + 1);
    char* result = MCALLOC(1, size);

    (void)wcstombs(result, wstr, size);

    MFREE(wstr);

    return result;
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

NULLABLE CLVALUE* get_element_from_Array(CLObject array, int index)
{
    sCLObject* array_data = CLOBJECT(array);

    CLObject items = array_data->mFields[0].mObjectValue;

    return get_element_from_array(items, index);
}

int get_element_number_from_Array(CLObject array)
{
    sCLObject* array_data = CLOBJECT(array);

    CLObject items = array_data->mFields[0].mObjectValue;

    sCLObject* items_data = CLOBJECT(items);

    return items_data->mArrayNum;
}

char get_value_from_Byte(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);
    return object_data->mFields[0].mByteValue;
}

unsigned char get_value_from_UByte(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mUByteValue;
}

short get_value_from_Short(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mShortValue;
}

unsigned short get_value_from_UShort(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mUShortValue;
}

int get_value_from_Integer(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mIntValue;
}

unsigned int get_value_from_UInteger(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mUIntValue;
}

long get_value_from_Long(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mLongValue;
}

unsigned long get_value_from_ULong(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mULongValue;
}

wchar_t get_value_from_Char(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mCharValue;
}

float get_value_from_Float(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mFloatValue;
}

double get_value_from_Double(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mDoubleValue;
}

BOOL get_value_from_Bool(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mBoolValue;
}

char* get_value_from_Pointer(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields[0].mPointerValue;
}

sCLClass* get_class_from_object(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);
    return object_data->mClass;
}
