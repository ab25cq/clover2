#include "jit_common.hpp"

extern "C" 
{

//////////////////////////////////////////////////
// JIT runtime functions
//////////////////////////////////////////////////

struct sCLVALUEAndBoolResult* run_create_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(43)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_equalable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(44)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_sortable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(45)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(46)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = list_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_sortable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(47)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = list_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_equalable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(48)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = list_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_tuple(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = tuple_object;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* run_create_hash(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int class_name_offset2, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);
    char* class_name2 = CONS_str(constant, class_name_offset2);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(49)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(50)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
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
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    (*stack_ptr)--; // pop_object

    (*stack_ptr)-=num_elements*2;

    result->result1.mObjectValue = hash_object;
    result->result2 = TRUE;

    return result;
}

CLObject run_create_block_object(CLVALUE** stack_ptr, CLVALUE* stack, sConst* constant, int code_offset, int code_len, int constant_offset, int constant_len, int block_var_num, int parent_var_num, BOOL lambda, sVMInfo* info)
{
    sByteCode codes2;
    codes2.mCodes = CONS_str(constant, code_offset);
    codes2.mLen = code_len;

    sConst constant2;
    constant2.mConst = CONS_str(constant, constant_offset);
    constant2.mLen = constant_len;

    CLVALUE* parent_stack = stack;

    CLObject block_object = create_block_object(&codes2, &constant2, parent_stack, parent_var_num, block_var_num, info->stack_id, lambda);

    return block_object;
}

struct sPointerAndBoolResult* run_load_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, CLObject obj)
{
    struct sPointerAndBoolResult* result = &gCLPointerAndBoolStructMemory;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(4)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(51)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(5)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    char* value = (char*)&object_pointer->mFields[field_index];
    result->result1 = value;
    result->result2 = TRUE;

    return result;
}

struct sPointerAndBoolResult* run_load_class_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    struct sPointerAndBoolResult* result = &gCLPointerAndBoolStructMemory;

    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(52)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "field index is invalid(6)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    sCLField* field = klass->mClassFields + field_index;
    char* value = (char*)&field->mValue;

    result->result1 = value;
    result->result2 = TRUE;

    return result;
}

CLObject run_int_to_string_cast(int n)
{
    char buf[32];
    snprintf(buf, 32, "%d", n);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_long_to_string_cast(clint64 l)
{
    char buf[32];
    snprintf(buf, 32, "%ld", l);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_uint_to_string_cast(unsigned int n)
{
    char buf[32];
    snprintf(buf, 32, "%u", n);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_ulong_to_string_cast(clint64 l)
{
    char buf[32];
    snprintf(buf, 32, "%lu", l);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_float_to_string_cast(float f)
{
    char buf[32];
    snprintf(buf, 32, "%f", f);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_double_to_string_cast(double d)
{
    char buf[32];
    snprintf(buf, 32, "%lf", d);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_char_to_string_cast(wchar_t c)
{
    char buf[32];
    snprintf(buf, 32, "%lc", c);

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_regex_to_string_cast(CLObject regex)
{
    sRegexObject* object_data = CLREGEX(regex);

    CLObject str = create_string_object(object_data->mRegexString);

    return str;
}

CLObject run_bool_to_string_cast(BOOL b)
{
    char buf[32];
    if(b) {
        snprintf(buf, 32, "true");
    }
    else {
        snprintf(buf, 32, "false");
    }

    CLObject str = create_string_object(buf);

    return str;
}

CLObject run_pointer_to_string_cast(char* p)
{
    char buf[32];
    snprintf(buf, 32, "%p", p);

    CLObject str = create_string_object(buf);

    return str;
}

int run_integer_to_int_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mIntValue;

    return value;
}

unsigned int run_uinteger_to_uint_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned int value = (unsigned int)obj_data->mFields[0].mUIntValue;

    return value;
}

char run_cbyte_to_byte_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    char value = (char)obj_data->mFields[0].mByteValue;

    return value;
}

unsigned char run_cubyte_to_ubyte_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned char value = (unsigned char)obj_data->mFields[0].mUByteValue;

    return value;
}

short run_cshort_to_short_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    short value = (short)obj_data->mFields[0].mShortValue;

    return value;
}

unsigned short run_cushort_to_ushort_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

    return value;
}

clint64 run_clong_to_long_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    clint64 value = (clint64)obj_data->mFields[0].mLongValue;

    return value;
}

unsigned clint64 run_culong_to_ulong_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mLongValue;

    return value;
}

char* run_cpointer_to_pointer_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    char* value = (char*)obj_data->mFields[0].mPointerValue;

    return value;
}

int run_cfloat_to_int_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mFloatValue;

    return value;
}

float run_cfloat_to_float_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    float value = (float)obj_data->mFields[0].mFloatValue;

    return value;
}

int run_cdouble_to_int_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    int value = (int)obj_data->mFields[0].mDoubleValue;

    return value;
}

double run_cdouble_to_double_cast(CLObject obj)
{
    sCLObject* obj_data = CLOBJECT(obj);

    double value = (double)obj_data->mFields[0].mDoubleValue;

    return value;
}

struct sCLVALUEAndBoolResult* run_array_to_carray_cast(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, char* class_name)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "class not found(53)");
        result->result1.mIntValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* array_data = CLOBJECT(array);
    int array_num = array_data->mArrayNum;

    sCLClass* klass2 = get_class("Array");
    MASSERT(klass2 != NULL);

    CLObject new_array = create_object(klass2);

    gGlobalStackPtr->mObjectValue = new_array;
    gGlobalStackPtr++;

    CLObject new_primitive_array;
    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        new_primitive_array = create_array_object(klass->mBoxingClass, array_num, 0);
    }
    else {
        new_primitive_array = create_array_object(klass, array_num, 0);
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

    gGlobalStackPtr--;

    result->result1.mObjectValue = new_array;
    result->result2 = TRUE;

    return result;
}

void show_method_parametor_address(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address, int var_num, sConst* constant, sByteCode* code)
{
    printf("stack_ptr %p lvar %p info %p stack %p stack_ptr_address %p var_num %d constant %p code %p\n", stack_ptr, lvar, info, stack, stack_ptr_address, var_num, constant, code);
}

CLObject run_op_string_with_string_expression(char* str, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr)
{
    CLObject string_expression_object[STRING_EXPRESSION_MAX];

    sBuf buf;
    sBuf_init(&buf);

    int offset_before = 0;

    int i;
    for(i=0; i<num_string_expression; i++) {
        int offset = string_expression_offsets[i];
        string_expression_object[i] = ((*stack_ptr) - num_string_expression + i)->mObjectValue;

        sBuf_append(&buf, str + offset_before, offset - offset_before);

        CLObject object = string_expression_object[i];

        if(object != 0 ) {
            char* str2 = ALLOC string_object_to_char_array(string_expression_object[i]);
            sBuf_append_str(&buf, str2);
            MFREE(str2);
        }

        offset_before = offset;
    }

    sBuf_append(&buf, str + offset_before, strlen(str) - offset_before);

    (*stack_ptr) -= num_string_expression;

    CLObject string_object = create_string_object(buf.mBuf);

    MFREE(buf.mBuf);

    return string_object;
}

CLObject run_op_buffer_with_string_expression(char* str, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr)
{
    CLObject string_expression_object[STRING_EXPRESSION_MAX];

    sBuf buf;
    sBuf_init(&buf);

    int offset_before = 0;

    int i;
    for(i=0; i<num_string_expression; i++) {
        int offset = string_expression_offsets[i];
        string_expression_object[i] = ((*stack_ptr) - num_string_expression + i)->mObjectValue;

        sBuf_append(&buf, str + offset_before, offset - offset_before);

        char* str2 = ALLOC string_object_to_char_array(string_expression_object[i]);
        sBuf_append_str(&buf, str2);
        MFREE(str2);

        offset_before = offset;
    }

    sBuf_append(&buf, str + offset_before, strlen(str) - offset_before);

    (*stack_ptr) -= num_string_expression;

    CLObject buffer_object = create_buffer_object(buf.mBuf, buf.mLen);

    MFREE(buf.mBuf);

    return buffer_object;
}

CLObject run_op_path_with_string_expression(char* str, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr)
{
    CLObject string_expression_object[STRING_EXPRESSION_MAX];

    sBuf buf;
    sBuf_init(&buf);

    int offset_before = 0;

    int i;
    for(i=0; i<num_string_expression; i++) {
        int offset = string_expression_offsets[i];
        string_expression_object[i] = ((*stack_ptr) - num_string_expression + i)->mObjectValue;

        sBuf_append(&buf, str + offset_before, offset - offset_before);

        char* str2 = ALLOC string_object_to_char_array(string_expression_object[i]);
        sBuf_append_str(&buf, str2);
        MFREE(str2);

        offset_before = offset;
    }

    sBuf_append(&buf, str + offset_before, strlen(str) - offset_before);

    (*stack_ptr) -= num_string_expression;

    CLObject path_object = create_path_object(buf.mBuf);

    MFREE(buf.mBuf);

    return path_object;
}

CLObject run_op_regex_with_string_expression(char* str, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr, BOOL global, BOOL ignore_case, BOOL multiline, BOOL extended, BOOL dotall, BOOL anchored, BOOL dollar_endonly, BOOL ungreedy)
{
    CLObject string_expression_object[STRING_EXPRESSION_MAX];

    sBuf buf;
    sBuf_init(&buf);

    int offset_before = 0;

    int i;
    for(i=0; i<num_string_expression; i++) {
        int offset = string_expression_offsets[i];
        string_expression_object[i] = ((*stack_ptr) - num_string_expression + i)->mObjectValue;

        sBuf_append(&buf, str + offset_before, offset - offset_before);

        char* str2 = ALLOC string_object_to_char_array(string_expression_object[i]);
        sBuf_append_str(&buf, str2);
        MFREE(str2);

        offset_before = offset;
    }

    sBuf_append(&buf, str + offset_before, strlen(str) - offset_before);

    (*stack_ptr) -= num_string_expression;

    CLObject regex_object = create_regex_object(buf.mBuf, global, ignore_case, multiline, extended, dotall, anchored, dollar_endonly, ungreedy);

    MFREE(buf.mBuf);

    return regex_object;
}

}
