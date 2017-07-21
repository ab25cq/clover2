
#include "jit_common.hpp"

extern "C" 
{

//////////////////////////////////////////////////////////////////////
// VM functions
//////////////////////////////////////////////////////////////////////
BOOL run_load_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index)
{
    CLObject obj = ((*stack_ptr) -1)->mObjectValue;
    (*stack_ptr)--;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(4)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    CLVALUE value = object_pointer->mFields[field_index];
    **stack_ptr = value;
    (*stack_ptr)++;

    return TRUE;
}


void run_ldclong(CLVALUE** stack_ptr, int value1, int value2)
{
    long lvalue;

    memcpy(&lvalue, &value1, sizeof(int));
    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

    (*stack_ptr)->mLongValue = lvalue;
    (*stack_ptr)++;
}

void run_ldcpointer(CLVALUE** stack_ptr, int value1, int value2)
{
    void* lvalue;

    memcpy(&lvalue, &value1, sizeof(int));
    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

    (*stack_ptr)->mPointerValue = (char*)lvalue;
    (*stack_ptr)++;
}

void run_ldculong(CLVALUE** stack_ptr, int value1, int value2)
{
    long lvalue;

    memcpy(&lvalue, &value1, sizeof(int));
    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

    (*stack_ptr)->mULongValue = lvalue;
    (*stack_ptr)++;
}

char* get_try_catch_label_name(sVMInfo* info)
{
    return info->try_catch_label_name;
}


BOOL run_load_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    CLObject array = ((*stack_ptr) -2)->mObjectValue;
    int element_num = ((*stack_ptr) -1)->mIntValue;
    (*stack_ptr)-=2;

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(7)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "element index is invalid");
        return FALSE;
    }

    CLVALUE value = object_pointer->mFields[element_num];
    **stack_ptr = value;
    (*stack_ptr)++;

    return TRUE;
}





void run_byte_to_string_cast(CLVALUE** stack_ptr)
{
    char value = ((*stack_ptr)-1)->mCharValue;

    char buf[32];
    snprintf(buf, 32, "%d", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_short_to_string_cast(CLVALUE** stack_ptr)
{
    short value = ((*stack_ptr)-1)->mShortValue;

    char buf[32];
    snprintf(buf, 32, "%d", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}


void run_ubyte_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned char value = ((*stack_ptr)-1)->mUByteValue;

    char buf[32];
    snprintf(buf, 32, "%u", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_ushort_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned short value = ((*stack_ptr)-1)->mUShortValue;

    char buf[32];
    snprintf(buf, 32, "%u", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}




void run_cubyte_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cshort_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cushort_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_integer_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_uinteger_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_clong_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_culong_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cfloat_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cdouble_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cpointer_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)0;// obj_data->mFields[0].mPointerValue; 

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cchar_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cbool_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mByteValue = value;
}

void run_cbyte_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cubyte_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cushort_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_integer_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_uinteger_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_clong_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_culong_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cfloat_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cdouble_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cpointer_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cchar_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cbool_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mShortValue = value;
}

void run_cbyte_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cubyte_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cshort_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cushort_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_uinteger_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_clong_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_culong_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mIntValue = value;

}

void run_cpointer_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cchar_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cbool_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cbyte_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cubyte_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cshort_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cushort_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_integer_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_uinteger_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mLongValue = value;
}


void run_culong_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cfloat_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cdouble_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cpointer_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cchar_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cbool_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mLongValue = value;
}

void run_cbyte_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cshort_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cushort_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_integer_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_uinteger_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_clong_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_culong_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cfloat_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cdouble_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cpointer_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)0;// obj_data->mFields[0].mPointerValue; 

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cchar_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cbool_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mUByteValue = value;
}

void run_cbyte_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cubyte_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cshort_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cushort_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_integer_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_uinteger_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_clong_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_culong_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cfloat_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cdouble_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cpointer_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cchar_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cbool_to_ushort_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mUShortValue = value;
}

void run_cbyte_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cubyte_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cshort_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cushort_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_integer_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}


void run_clong_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_culong_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mUIntValue = value;

}

void run_cfloat_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cdouble_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cpointer_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)0; //obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cchar_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cbool_to_uint_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mUIntValue = value;
}

void run_cbyte_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cubyte_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cshort_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cushort_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_integer_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_uinteger_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_clong_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_culong_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cfloat_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cdouble_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cpointer_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mPointerValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cchar_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cbool_to_ulong_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned long value = (unsigned long)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mULongValue = value;
}

void run_cbyte_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cubyte_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cshort_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cushort_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_integer_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_uinteger_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_clong_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_culong_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}


void run_cdouble_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cchar_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cbool_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mFloatValue = value;
}

void run_cbyte_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cubyte_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mUByteValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cshort_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mShortValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cushort_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mUShortValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_integer_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mIntValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_uinteger_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mUIntValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_clong_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mLongValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_culong_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mULongValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cfloat_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mDoubleValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}


void run_cchar_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mCharValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

void run_cbool_to_double_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mBoolValue;

    ((*stack_ptr)-1)->mDoubleValue = value;
}

BOOL run_array_to_carray_cast(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(10)");
        return FALSE;
    }

    CLObject array = ((*stack_ptr)-1)->mObjectValue;
    sCLObject* array_data = CLOBJECT(array);
    int array_num = array_data->mArrayNum;

    sCLClass* klass2 = get_class("Array");
    MASSERT(klass2 != NULL);

    CLObject new_array = create_object(klass2);

    (*stack_ptr)->mObjectValue = new_array;   // push object
    (*stack_ptr)++;

    CLObject new_primitive_array;
    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        new_primitive_array = create_array_object(klass->mBoxingClass, array_num);
    }
    else {
        new_primitive_array = create_array_object(klass, array_num);
    }

    sCLObject* new_array_data = CLOBJECT(new_array);

    new_array_data->mFields[0].mObjectValue = new_primitive_array;

    /// boxing element ///
    int i;
    for(i=0; i<array_num; i++ ) {
        array_data = CLOBJECT(array);           // reget for GC

        CLVALUE element;
        boxing_primitive_value_to_object(array_data->mFields[i], &element, klass);

        sCLObject* new_primitive_array_data = CLOBJECT(new_primitive_array);
        new_primitive_array_data->mFields[i] = element;
    }

    (*stack_ptr)-=2;
    (*stack_ptr)->mObjectValue = new_array;
    (*stack_ptr)++;

    return TRUE;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    if(!compile_jit_method(klass, method)) {
        return FALSE;
    }

    int object_stack_size = 1024;
    CLVALUE* object_stack = (CLVALUE*)MCALLOC(1, sizeof(CLVALUE)*object_stack_size);
    CLVALUE* object_stack_ptr = object_stack;

    long object_stack_id = append_stack_to_stack_list(object_stack, &object_stack_ptr);

    char method_path2[METHOD_NAME_MAX + 128];
    create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);
    
    auto ExprSymbol = TheJIT->findSymbol(method_path2);
    fJITMethodType function = nullptr;

    if(ExprSymbol) {
        function = (fJITMethodType)ExprSymbol.getAddress();
    }

    if(function != nullptr) {
        CLVALUE* stack_ptr = stack + var_num;
        CLVALUE* lvar = stack;

        long stack_id = append_stack_to_stack_list(stack, &stack_ptr);

        info->current_stack = stack;        // for invoking_block in native method
        info->current_var_num = var_num;
        info->stack_id = stack_id;

        BOOL result = function(stack_ptr, lvar, info, stack, &stack_ptr, var_num, object_stack, &object_stack_ptr);
        if(!result) {
            remove_stack_to_stack_list(stack, &stack_ptr);
            remove_stack_to_stack_list(object_stack, &object_stack_ptr);
            MFREE(object_stack);
            return FALSE;
        }

        remove_stack_to_stack_list(stack, &stack_ptr);
    }
    else {
        BOOL result = vm(code, constant, stack, var_num, klass, info);

        if(!result) {
            remove_stack_to_stack_list(object_stack, &object_stack_ptr);
            MFREE(object_stack);
            return FALSE;
        }
    }

    remove_stack_to_stack_list(object_stack, &object_stack_ptr);
    MFREE(object_stack);

    return TRUE;
}

} // extern "C"
