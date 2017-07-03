
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

BOOL run_load_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLVALUE* lvar, int index)
{
    (*stack_ptr)->mPointerValue = (char*)&lvar[index];
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

BOOL invoke_virtual_method(int num_real_params, int offset, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant)
{
    CLObject object = ((*stack_ptr)-num_real_params)->mObjectValue;

    sCLObject* object_data = CLOBJECT(object);

    sCLClass* klass = object_data->mClass;

    MASSERT(klass != NULL);

    char* method_name_and_params = CONS_str(constant, offset);

    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    if(method == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_VIRTUAL_METHOD: Method not found");
        return FALSE;
    }
    else {
        if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
            if(*info->try_offset != 0) {
                *info->pc = code->mCodes + *info->try_offset;
                *info->try_offset = *info->try_offset_before;
            }
            else {
                return FALSE;
            }
        }
    }

    return TRUE;
}



BOOL run_load_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index)
{
    CLObject obj = ((*stack_ptr) -1)->mObjectValue;
    (*stack_ptr)--;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(4)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(5)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    char* value = (char*)&object_pointer->mFields[field_index];
    (*stack_ptr)->mPointerValue = value;
    (*stack_ptr)++;

    return TRUE;
}



BOOL run_load_class_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(8)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
        return FALSE;
    }

    sCLField* field = klass->mClassFields + field_index;
    char* value = (char*)&field->mValue;

    (*stack_ptr)->mPointerValue = value;
    (*stack_ptr)++;

    return TRUE;
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

BOOL run_store_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    CLObject array = ((*stack_ptr) -3)->mObjectValue;
    int element_num = ((*stack_ptr) -2)->mIntValue;
    CLVALUE value = *((*stack_ptr)-1);

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(8)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "element index is invalid");
        return FALSE;
    }

    object_pointer->mFields[element_num] = value;

    (*stack_ptr)-=3;

    **stack_ptr = value;
    (*stack_ptr)++;

    return TRUE;
}

void run_get_array_length(CLVALUE** stack_ptr)
{
    CLObject array_ = ((*stack_ptr)-1)->mObjectValue;
    sCLObject* array_data = CLOBJECT(array_);
    (*stack_ptr)--;

    (*stack_ptr)->mIntValue = array_data->mArrayNum;
    (*stack_ptr)++;
}

void run_get_regex_global(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mGlobal;
    (*stack_ptr)++;
}

void run_get_regex_ignorecase(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mIgnoreCase;
    (*stack_ptr)++;
}

void run_get_regex_multiline(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mMultiline;
    (*stack_ptr)++;
}

void run_get_regex_extended(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mExtended;
    (*stack_ptr)++;
}

void run_get_regex_dotall(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mDotAll;
    (*stack_ptr)++;
}

void run_get_regex_anchored(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mAnchored;
    (*stack_ptr)++;
}

void run_get_regex_dollar_endonly(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mDollarEndOnly;
    (*stack_ptr)++;
}

void run_get_regex_ungreedy(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;
    sRegexObject* regex_object = CLREGEX(regex);
    (*stack_ptr)--;

    (*stack_ptr)->mBoolValue = regex_object->mUngreedy;
    (*stack_ptr)++;
}

void run_char_uppercase(CLVALUE** stack_ptr)
{
    wchar_t c = ((*stack_ptr)-1)->mCharValue;

    wchar_t result = c;
    if(c >= 'a' && c <= 'z') {
        result = c - 'a' + 'A';
    }

    ((*stack_ptr)-1)->mCharValue = result;
}

void run_char_lowercase(CLVALUE** stack_ptr)
{
    wchar_t c = ((*stack_ptr)-1)->mCharValue;

    wchar_t result = c;
    if(c >= 'A' && c <= 'Z') {
        result = c - 'A' + 'a';
    }

    ((*stack_ptr)-1)->mCharValue = result;
}

BOOL run_create_array(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, char* class_name, int num_elements)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(11)");
        return FALSE;
    }

    CLObject array_object = create_array_object(klass, num_elements);
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    sCLObject* object_data = CLOBJECT(array_object);

    int i;
    for(i=0; i<num_elements; i++) {
        object_data->mFields[i] = *((*stack_ptr)-1-num_elements+i);
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        return FALSE;
    }

    CLObject array_object = create_carray_object();
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_carray_object(array_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}


BOOL run_create_equalable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        return FALSE;
    }

    CLObject array_object = create_equalable_carray_object();
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_equalable_carray_object(array_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_sortable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
        return FALSE;
    }

    CLObject array_object = create_sortable_carray_object();
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_sortable_carray_object(array_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = array_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        return FALSE;
    }

    CLObject list_object = create_list_object();
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_list_object(list_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = list_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_sortable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        return FALSE;
    }

    CLObject list_object = create_sortable_list_object();
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_sortable_list_object(list_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = list_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_equalable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
        return FALSE;
    }

    CLObject list_object = create_equalable_list_object();
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_equalable_list_object(list_object, num_elements, items, stack, var_num, stack_ptr, info, klass))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = list_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_tuple(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements)
{
    CLObject tuple_object = create_tuple_object(num_elements);

    (*stack_ptr)->mObjectValue = tuple_object; // push object
    (*stack_ptr)++;

    CLObject items[TUPLE_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLVALUE element = *((*stack_ptr)-1-num_elements+i);
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
    }

    if(!initialize_tuple_object(tuple_object, num_elements, items, stack, var_num, stack_ptr, info))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;
    (*stack_ptr)->mObjectValue = tuple_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL run_create_hash(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* class_name, char* class_name2)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(14)");
        return FALSE;
    }

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(15)");
        return FALSE;
    }

    CLObject keys[HASH_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        keys[i] = ((*stack_ptr) - num_elements * 2 + i * 2)->mObjectValue;
    }

    CLObject items[HASH_VALUE_ELEMENT_MAX];

    for(i=0; i<num_elements; i++) {
        items[i] = ((*stack_ptr) - num_elements * 2 + i * 2 + 1)->mObjectValue;
    }

    CLObject hash_object = create_hash_object();
    (*stack_ptr)->mObjectValue = hash_object; // push object
    (*stack_ptr)++;

    if(!initialize_hash_object(hash_object, num_elements, keys, items, stack, var_num, stack_ptr, info, klass, klass2))
    {
        return FALSE;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements*2;
    (*stack_ptr)->mObjectValue = hash_object;
    (*stack_ptr)++;

    return TRUE;
}

void run_create_block_object(CLVALUE** stack_ptr, CLVALUE* stack, sConst* constant, int code_offset, int code_len, int constant_offset, int constant_len, int block_var_num, int parent_var_num, BOOL lambda, sVMInfo* info)

{
    sByteCode codes2;
    codes2.mCodes = CONS_str(constant, code_offset);
    codes2.mLen = code_len;

    sConst constant2;
    constant2.mConst = CONS_str(constant, constant_offset);
    constant2.mLen = constant_len;

    CLVALUE* parent_stack = stack;

    CLObject block_object = create_block_object(&codes2, &constant2, parent_stack, parent_var_num, block_var_num, info->stack_id, lambda);

    (*stack_ptr)->mObjectValue = block_object;
    (*stack_ptr)++;
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

CLObject run_int_to_string_cast(int value)
{
    char buf[32];
    snprintf(buf, 32, "%d", value);

    CLObject str = create_string_object(buf);

    return str;
}

void run_long_to_string_cast(CLVALUE** stack_ptr)
{
    long value = ((*stack_ptr)-1)->mLongValue;

    char buf[32];
    snprintf(buf, 32, "%ld", value);

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

void run_uint_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned int value = ((*stack_ptr)-1)->mUIntValue;

    char buf[32];
    snprintf(buf, 32, "%u", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_ulong_to_string_cast(CLVALUE** stack_ptr)
{
    unsigned long value = ((*stack_ptr)-1)->mULongValue;

    char buf[32];
    snprintf(buf, 32, "%lu", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_float_to_string_cast(CLVALUE** stack_ptr)
{
    float value = ((*stack_ptr)-1)->mFloatValue;

    char buf[32];
    snprintf(buf, 32, "%f", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_double_to_string_cast(CLVALUE** stack_ptr)
{
    double value = ((*stack_ptr)-1)->mDoubleValue;

    char buf[32];
    snprintf(buf, 32, "%lf", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_bool_to_string_cast(CLVALUE** stack_ptr)
{
    BOOL value = ((*stack_ptr)-1)->mBoolValue;

    char buf[32];
    if(value) {
        snprintf(buf, 32, "true");
    }
    else {
        snprintf(buf, 32, "false");
    }

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_regex_to_string_cast(CLVALUE** stack_ptr)
{
    CLObject regex = ((*stack_ptr)-1)->mObjectValue;

    sRegexObject* object_data = CLREGEX(regex);

    CLObject str = create_string_object(object_data->mRegexString);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_pointer_to_string_cast(CLVALUE** stack_ptr)
{
    char* value = ((*stack_ptr)-1)->mPointerValue;

    char buf[32];
    snprintf(buf, 32, "%p", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_char_to_string_cast(CLVALUE** stack_ptr)
{
    wchar_t value = ((*stack_ptr)-1)->mCharValue;

    char buf[32];
    snprintf(buf, 32, "%lc", value);

    CLObject str = create_string_object(buf);

    ((*stack_ptr)-1)->mObjectValue = str;
}

void run_cbyte_to_byte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mByteValue;

    ((*stack_ptr)-1)->mByteValue = value;
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

void run_cshort_to_short_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mShortValue;

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

void run_integer_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mIntValue;

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

void run_cfloat_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mFloatValue;

    ((*stack_ptr)-1)->mIntValue = value;
}

void run_cdouble_to_int_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mDoubleValue;

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

void run_clong_to_long_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    long value = (long)obj_data->mFields[0].mLongValue;

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

void run_cubyte_to_ubyte_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUByteValue;

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

void run_uinteger_to_uint_cast(CLVALUE** stack_ptr)
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

void run_cfloat_to_float_cast(CLVALUE** stack_ptr)
{
    CLObject obj = ((*stack_ptr)-1)->mObjectValue;

    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mFloatValue;

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

void run_cdouble_to_double_cast(CLVALUE** stack_ptr)
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

        if(!function(stack_ptr, lvar, info, stack, &stack_ptr, var_num)) {
            remove_stack_to_stack_list(stack, &stack_ptr);
            return FALSE;
        }

        remove_stack_to_stack_list(stack, &stack_ptr);
    }
    else {
        if(!vm(code, constant, stack, var_num, klass, info)) {
            return FALSE;
        }
    }

    return TRUE;
}

} // extern "C"
