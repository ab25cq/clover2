#include "jit_common.hpp"

#include <cerrno>

using namespace llvm;

BOOL gAndAndOrOr = FALSE;
BOOL gConditional = FALSE;

extern "C" 
{
struct sCLVALUEAndBoolResult gCLValueAndBoolStructMemory;
struct sPointerAndBoolResult gCLPointerAndBoolStructMemory;

//////////////////////////////////////////////////
// JIT runtime functions
//////////////////////////////////////////////////
char* get_try_catch_label_name(sVMInfo* info)
{
    return info->try_catch_label_name;
}

void reset_andand_oror(sVMInfo* info)
{
    info->num_andand_oror = 0;
}

int get_andand_oror_left_value(sVMInfo* info)
{
    return info->andand_oror_left_value[info->num_andand_oror-1];
}

void set_andand_oror_left_value(BOOL flag, sVMInfo* info)
{
    info->andand_oror_left_value[info->num_andand_oror-1] = flag;
}

int get_andand_oror_right_value(sVMInfo* info)
{
    return info->andand_oror_right_value[info->num_andand_oror-1];
}

void set_andand_oror_right_value(BOOL flag, sVMInfo* info)
{
    info->andand_oror_right_value[info->num_andand_oror-1] = flag;
}

void inc_andand_oror_array(sVMInfo* info)
{
    info->num_andand_oror++;

    if(info->num_andand_oror >= ANDAND_OROR_MAX) {
        fprintf(stderr, "overflow and and or or value\n");
        exit(1);
    }
}

void dec_andand_oror_array(sVMInfo* info)
{
    info->num_andand_oror--;

    if(info->num_andand_oror < 0) {
        fprintf(stderr, "invalid and and or or value\n");
        exit(1);
    }
}

void try_function(sVMInfo* info, int catch_label_name_offset, int try_offset, sByteCode* code, sConst* constant)
{
    info->try_catch_label_name_before = info->try_catch_label_name;
    info->try_offset_before = info->try_offset;
    info->try_code_before = info->try_code;

    if(catch_label_name_offset != 0) {
        info->try_catch_label_name = CONS_str(constant, catch_label_name_offset);
    }
    else {
        info->try_catch_label_name = NULL;
    }
    info->try_offset = try_offset;
    info->try_code = code;
}

void try_end_function(sVMInfo* info, int catch_label_name_offset, int try_offset, sByteCode* code, sConst* constant)
{
    info->try_catch_label_name = info->try_catch_label_name_before;
    info->try_offset = info->try_offset_before;
    info->try_code = info->try_code_before;

    info->try_catch_label_name_before = NULL;
    info->try_offset_before = 0;
    info->try_code_before = NULL;
}

struct sCLVALUEAndBoolResult* get_field_from_object(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject obj, int field_index)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(3)");
        result->result1.mLongValue = 0;
        result->result2 = 0;

        return result;
    }
    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(37)");
        result->result1.mLongValue = 0;
        result->result2 = 0;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(1)");
        result->result1.mLongValue = 0;
        result->result2 = 0;
        return result;
    }

    CLVALUE value = object_pointer->mFields[field_index];

    result->result1 = value;
    result->result2 = 1;

    return result;
}

CLObject get_string_object_of_object_name(CLObject object, sVMInfo* info)
{
    sCLObject* object_data = CLOBJECT(object);

    CLObject object2 = create_string_object(object_data->mType, info);

    return object2;
}

int get_object_allocated_size(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mSize;
}

void* get_object_head_of_memory(CLObject object)
{
    sCLObject* object_data = CLOBJECT(object);

    return object_data->mFields;
}

BOOL call_invoke_method(sCLClass* klass, int method_index, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    sCLMethod* method = klass->mMethods + method_index;
    return invoke_method(klass, method, stack, var_num, stack_ptr, info);
}

BOOL call_invoke_virtual_method(int offset, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sConst* constant, CLObject object, int num_real_params)
{
    if(object == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(3)");
        return FALSE;
    }

    /// go ///
    sCLObject* object_data = CLOBJECT(object);

    sCLClass* klass = object_data->mClass;

    MASSERT(klass != NULL);

    char* method_name_and_params = CONS_str(constant, offset);

    int n = METHOD_NAME_MAX + num_real_params * CLASS_NAME_MAX + 128;
    char method_name_and_params2[n];
    Self_convertion_of_method_name_and_params(method_name_and_params, method_name_and_params2, CLASS_NAME(klass));

    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params2);

    if(method == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"OP_INVOKE_VIRTUAL_METHOD: Method not found");
        return FALSE;
    }
    else {
        if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL call_invoke_dynamic_method(int offset, int offset2, int num_params, int static_, int num_method_chains, int max_method_chains, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sByteCode* code, sConst* constant)
{
    /// none static method ////
    if(static_ == 0) {
        int num_real_params = num_params + 1;
        char* method_name = CONS_str(constant, offset2);

        CLObject object = ((*stack_ptr)-num_real_params)->mObjectValue;

        if(object == 0) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(3)");
            return FALSE;
        }

        sCLObject* object_data = CLOBJECT(object);

        sCLClass* klass = object_data->mClass;

        MASSERT(klass != NULL);

        if(klass->mCallingMethodIndex == -1) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"OP_INVOKE_DYNAMIC_METHOD: Method not found(1)");
            return FALSE;
        }

        sCLMethod* method = klass->mMethods + klass->mCallingMethodIndex;

        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            CLObject object = ((*stack_ptr)-num_params + i)->mObjectValue;

            elements[i] = object;
        }

        CLObject carray = create_carray_object_with_elements(num_params, elements ,info);

        inc_refference_count(carray, 0, FALSE);

        CLVALUE cl_value;
        cl_value.mObjectValue = carray;
        push_value_to_global_stack(cl_value, info);

        (*stack_ptr)-=num_params;

        (*stack_ptr)->mObjectValue = create_string_object(method_name, info);
        inc_refference_count((*stack_ptr)->mObjectValue, 0, FALSE);
        (*stack_ptr)++;
        (*stack_ptr)->mObjectValue = carray;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = num_method_chains;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = max_method_chains;
        (*stack_ptr)++;

        pop_global_stack(info);

        if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
            return FALSE;
        }
    }
    /// static method ///
    else {
        char* class_name = CONS_str(constant, offset);
        char* method_name = CONS_str(constant, offset2);

        sCLClass* klass = get_class_with_load_and_initialize(class_name);

        if(klass == NULL) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(38)");
            return FALSE;
        }

        if(klass->mCallingClassMethodIndex == -1) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"OP_INVOKE_DYNAMIC_METHOD: Method not found(2)");
            return FALSE;
        }

        sCLMethod* method = klass->mMethods + klass->mCallingClassMethodIndex;

        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            CLObject object = ((*stack_ptr)-num_params + i)->mObjectValue;

            elements[i] = object;
        }

        CLObject carray = create_carray_object_with_elements(num_params, elements, info);
        inc_refference_count(carray, 0, FALSE);

        CLVALUE cl_value;
        cl_value.mObjectValue = carray;

        push_value_to_global_stack(cl_value, info);

        (*stack_ptr)-=num_params;

        (*stack_ptr)->mObjectValue = create_string_object(method_name, info);
        inc_refference_count((*stack_ptr)->mObjectValue, 0, FALSE);
        (*stack_ptr)++;
        (*stack_ptr)->mObjectValue = carray;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = num_method_chains;
        (*stack_ptr)++;
        (*stack_ptr)->mIntValue = max_method_chains;
        (*stack_ptr)++;

        pop_global_stack(info);

        if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
            return FALSE;
        }
    }

    return TRUE;
}

void catch_function(sVMInfo* info, sByteCode* code) 
{
    if(info->try_code == code && info->try_offset != 0) {
        *info->try_pc = info->try_code->mCodes + info->try_offset;
        info->try_offset = 0;
        info->try_code = NULL;
    }
}

BOOL invoke_block_in_jit(int num_params, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    CLObject block_object = ((*stack_ptr)-num_params-1)->mObjectValue;

    if(!invoke_block(block_object, stack, var_num, num_params, stack_ptr, info, TRUE)) 
    {
        return FALSE;
    }

    return TRUE;
}

struct sCLVALUEAndBoolResult* store_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject obj, CLVALUE value, int field_index, int field_class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(5)");
        result->result1 = value;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(39)");
        result->result1 = value;
        result->result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(2)");
        result->result1 = value;
        result->result2 = FALSE;
        return result;
    }

    char* field_class_name = CONS_str(constant, field_class_name_offset);

    sCLClass* field_class = get_class(field_class_name);

    if(field_class == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(39)");
        result->result1 = value;
        result->result2 = FALSE;
        return result;
    }

    BOOL value_is_object = field_class->mFlags & CLASS_FLAGS_NO_FREE_OBJECT;

    CLObject prev_obj = object_pointer->mFields[field_index].mObjectValue;

    object_pointer->mFields[field_index] = value;

    inc_refference_count(value.mObjectValue, prev_obj, value_is_object);

    result->result1 = value;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* store_field_of_buffer(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject obj, CLVALUE value, int field_index)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(5)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(39)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(2)");
        return FALSE;
    }

    CLObject object2 = object_pointer->mFields[field_index].mObjectValue;

    sCLObject* object_data2 = CLOBJECT(object2);

    char* pointer = value.mPointerValue;

    if(pointer < object_data2->mFields[0].mPointerValue || pointer >= object_data2->mFields[0].mPointerValue + object_data2->mFields[2].mULongValue) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Out of range on memory safe pointer(1)");
        return FALSE;
    }

    object_data2->mFields[3].mPointerValue = value.mPointerValue;

    result->result1 = value;
    result->result2 = TRUE;

    return result;
}

struct sCLVALUEAndBoolResult* load_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(40)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(3)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLField* field = klass->mClassFields + field_index;

    result->result1 = field->mValue;
    result->result2 = TRUE;

    return result;
}

BOOL store_class_field(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant, CLVALUE value)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(41)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(4)");
        return FALSE;
    }

    mark_and_store_class_field(klass, field_index, value);

    return TRUE;
}

BOOL store_class_field_of_buffer(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, int offset, sConst* constant, CLVALUE value)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(41)");
        return FALSE;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(4)");
        return FALSE;
    }

    sCLField* field = klass->mClassFields + field_index;

    CLObject object = field->mValue.mObjectValue;

    sCLObject* object_data = CLOBJECT(object);

    char* pointer = value.mPointerValue;

    if(pointer < object_data->mFields[0].mPointerValue || pointer >= object_data->mFields[0].mPointerValue + object_data->mFields[2].mULongValue) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Out of range on memory safe pointer(2)");
        return FALSE;
    }

    object_data->mFields[3].mPointerValue = value.mPointerValue;

    return TRUE;
}

BOOL run_store_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, int element_num, CLVALUE value)
{
    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(8)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"element index is invalid(1)");
        return FALSE;
    }

    sCLClass* klass = object_pointer->mClass;

    BOOL value_is_object = klass->mFlags & CLASS_FLAGS_NO_FREE_OBJECT;

    CLObject prev_obj = object_pointer->mFields[element_num].mObjectValue;

    object_pointer->mFields[element_num] = value;
    inc_refference_count(value.mObjectValue, prev_obj, value_is_object);

    return TRUE;
}

BOOL run_store_element_of_buffer(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, int element_num, CLVALUE value)
{
    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(8)");
        return FALSE;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"element index is invalid(1)");
        return FALSE;
    }

    CLObject object = object_pointer->mFields[element_num].mObjectValue;
    sCLObject* object_data = CLOBJECT(object);

    char* pointer = value.mPointerValue;

    if(pointer < object_data->mFields[0].mPointerValue || pointer >= object_data->mFields[0].mPointerValue + object_data->mFields[2].mULongValue) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Out of range on memory safe pointer(3)");
        return FALSE;
    }

    object_data->mFields[3].mPointerValue = value.mPointerValue;

    return TRUE;
}

int get_array_length(CLObject array_)
{
    sCLObject* array_data = CLOBJECT(array_);
    return array_data->mArrayNum;
}

struct sCLVALUEAndBoolResult* load_element(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, CLObject array, int element_num, int size)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(7)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* object_pointer = CLOBJECT(array);

    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"element index is invalid(2)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    result->result1 = object_pointer->mFields[element_num];
    result->result2 = TRUE;

    return result;
}

wchar_t char_uppercase(wchar_t c)
{
    wchar_t result = c;
    if(c >= 'a' && c <= 'z') {
        result = c - 'a' + 'A';
    }

    return result;
}

wchar_t char_lowercase(wchar_t c)
{
    wchar_t result = c;
    if(c >= 'A' && c <= 'Z') {
        result = c - 'A' + 'a';
    }

    return result;
}

BOOL get_regex_global(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mGlobal;
}

BOOL get_regex_ignorecase(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mIgnoreCase;
}

BOOL get_regex_multiline(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mMultiline;
}

BOOL get_regex_extended(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mExtended;
}

BOOL get_regex_dotall(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mDotAll;
}

BOOL get_regex_anchored(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mAnchored;
}

BOOL get_regex_dollar_endonly(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mDollarEndOnly;
}

BOOL get_regex_ungreedy(CLObject regex)
{
    sRegexObject* regex_object = CLREGEX(regex);
    return regex_object->mUngreedy;
}

struct sCLVALUEAndBoolResult* run_create_array(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(42)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject array_object = create_array_object(klass, num_elements, info);
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    sCLObject* object_data = CLOBJECT(array_object);

    int i;
    for(i=0; i<num_elements; i++) {
//        CLObject prev_obj = object_data->mFields[i].mObjectValue;

        CLVALUE cl_value = *((*stack_ptr)-1-num_elements+i);
        object_data->mFields[i] = cl_value;

//        inc_refference_count(cl_value.mObjectValue, prev_obj);
    }

    (*stack_ptr)--; // pop_object

//    (*stack_ptr)-=num_elements;

    result->result1.mObjectValue = array_object;
    result->result2 = TRUE;

    return result;
}

////////////////////////////////////////
// JIT main
////////////////////////////////////////
static BOOL search_for_dl_file(char* class_name, char* dynamic_library_path, size_t dynamic_library_path_size)
{
    /// script file directory ///
    if(gScriptDirPath[0] != '\0') {
        snprintf(dynamic_library_path, dynamic_library_path_size, "%s/lib%s.so", gScriptDirPath, class_name);

        if(access(dynamic_library_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// current working directory ///
    char* cwd = getenv("PWD");

    if(cwd) {
        snprintf(dynamic_library_path, dynamic_library_path_size, "%s/lib%s.so", cwd, class_name);

        if(access(dynamic_library_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// home directory ///
    char* home = getenv("HOME");

    if(home) {
        snprintf(dynamic_library_path, dynamic_library_path_size, "%s/.clover2/lib%s.so", home, class_name);

        if(access(dynamic_library_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// system shared directory ///
    snprintf(dynamic_library_path, dynamic_library_path_size, "%s/share/clover2/lib%s.so", PREFIX, class_name);

    if(access(dynamic_library_path, F_OK) == 0) {
        return TRUE;
    }

    return FALSE;
}

static void llvm_load_dynamic_library(sCLClass* klass)
{
    char* class_name = CLASS_NAME(klass);

    char class_dynamic_library_path[PATH_MAX+1];
    if(search_for_dl_file(class_name, class_dynamic_library_path, PATH_MAX)) 
    {
        klass->mDynamicLibrary = dlopen(class_dynamic_library_path, RTLD_LAZY);

        if(klass->mDynamicLibrary == NULL) {
            fprintf(stderr, "%s\n", dlerror());
        }
    }
}

sCLClass* get_class_with_load_and_initialize_in_jit(sConst* constant, int offset)
{
    char* class_name = CONS_str(constant, offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        fprintf(stderr, "class not found error %s(54)\n", class_name);
        return NULL;
    }

    return klass;
}

BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info, CLVALUE** stack_ptr)
{
    if(method->mFlags & METHOD_FLAGS_NON_NATIVE_CODE || info->running_thread)
    {
        BOOL result = vm(code, constant, stack, var_num, klass, info);

        if(!result) {
            return FALSE;
        }
    }
    else {
        if(klass->mDynamicLibrary == NULL) {
            llvm_load_dynamic_library(klass);
        }

        if(klass->mDynamicLibrary && method->mJITDynamicSym == NULL) {
            char method_path2[METHOD_NAME_MAX + 128];
            create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);

            method->mJITDynamicSym = dlsym(klass->mDynamicLibrary, method_path2);

            if(method->mJITDynamicSym == NULL) {
                fprintf(stderr, "%s\n", dlerror());
            }
        }

        if(method->mJITDynamicSym) 
        {
            CLVALUE* stack_ptr = stack + var_num;
            CLVALUE* lvar = stack;

            sCLStack* stack_id = append_stack_to_stack_list(stack, &stack_ptr);

            info->current_stack = stack;        // for invoking_block in native method
            info->current_var_num = var_num;
            info->stack_id = stack_id;

            CLVALUE** stack_ptr_address = &stack_ptr;
            fJITMethodType fun2 = (fJITMethodType)method->mJITDynamicSym;

            CLVALUE** global_stack_ptr_address = &info->mTmpGlobalStackPtr;

            BOOL result = fun2(stack_ptr, lvar, info, stack, stack_ptr_address, var_num, constant, code, global_stack_ptr_address, stack + var_num);

            if(!result) {
                remove_stack_to_stack_list(stack_id);
                return FALSE;
            }

            remove_stack_to_stack_list(stack_id);
        }
        else {
            BOOL result = vm(code, constant, stack, var_num, klass, info);

            if(!result) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

void jit_init_on_runtime()
{
    gCLValueAndBoolStructMemory.result1.mIntValue = 0;
    gCLValueAndBoolStructMemory.result2 = 0;

    gCLPointerAndBoolStructMemory.result1 = NULL;
    gCLPointerAndBoolStructMemory.result2 = FALSE;
}

void jit_final_on_runtime()
{
}


} // extern "C"

extern "C" 
{

//////////////////////////////////////////////////
// JIT runtime functions
//////////////////////////////////////////////////

struct sCLVALUEAndBoolResult* run_create_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int type_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(43)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    char* type_name = CONS_str(constant, type_name_offset);

    CLObject array_object = create_carray_object(type_name, info);
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;

        inc_refference_count(items[i], 0, FALSE);
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

struct sCLVALUEAndBoolResult* run_create_equalable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int type_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(44)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    char* type_name = CONS_str(constant, type_name_offset);

    CLObject array_object = create_equalable_carray_object(type_name, info);
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
        inc_refference_count(items[i], 0, FALSE);
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

struct sCLVALUEAndBoolResult* run_create_sortable_carray(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int type_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(45)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    char* type_name = CONS_str(constant, type_name_offset);

    CLObject array_object = create_sortable_carray_object(type_name, info);
    (*stack_ptr)->mObjectValue = array_object; // push object
    (*stack_ptr)++;

    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
        inc_refference_count(items[i], 0, FALSE);
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

struct sCLVALUEAndBoolResult* run_create_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int type_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(46)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    char* type_name = CONS_str(constant, type_name_offset);

    CLObject list_object = create_list_object(type_name, info);
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        CLObject object = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;
        items[i] = object;

        inc_refference_count(object, 0, FALSE);
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

struct sCLVALUEAndBoolResult* run_create_sortable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int type_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(47)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    char* type_name = CONS_str(constant, type_name_offset);

    CLObject list_object = create_sortable_list_object(type_name, info);
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;

        inc_refference_count(items[i], 0, FALSE);
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

struct sCLVALUEAndBoolResult* run_create_equalable_list(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int type_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(48)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    char* type_name = CONS_str(constant, type_name_offset);

    CLObject list_object = create_equalable_list_object(type_name, info);
    (*stack_ptr)->mObjectValue = list_object; // push object
    (*stack_ptr)++;

    CLObject items[LIST_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;

        inc_refference_count(items[i], 0, FALSE);
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

struct sCLVALUEAndBoolResult* run_create_tuple(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, char* type_name)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    CLObject tuple_object = create_tuple_object(num_elements, type_name, info);

    (*stack_ptr)->mObjectValue = tuple_object; // push object
    (*stack_ptr)++;

    CLObject items[TUPLE_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        items[i] = (*((*stack_ptr)-1-num_elements+i)).mObjectValue;

        inc_refference_count(items[i], 0, FALSE);
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

struct sCLVALUEAndBoolResult* run_create_hash(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int num_elements, int class_name_offset, int class_name_offset2, int type_name_offset, sConst* constant)
{
    struct sCLVALUEAndBoolResult* result = &gCLValueAndBoolStructMemory;

    char* class_name = CONS_str(constant, class_name_offset);
    char* class_name2 = CONS_str(constant, class_name_offset2);
    char* type_name = CONS_str(constant, type_name_offset);

    sCLClass* klass = get_class_with_load_and_initialize(class_name);

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(49)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(50)");
        result->result1.mLongValue = 0;
        result->result2 = FALSE;
        return result;
    }

    CLObject keys[HASH_VALUE_ELEMENT_MAX];

    int i;
    for(i=0; i<num_elements; i++) {
        keys[i] = ((*stack_ptr) - num_elements * 2 + i * 2)->mObjectValue;

        inc_refference_count(keys[i], 0, FALSE);
    }

    CLObject items[HASH_VALUE_ELEMENT_MAX];

    for(i=0; i<num_elements; i++) {
        items[i] = ((*stack_ptr) - num_elements * 2 + i * 2 + 1)->mObjectValue;

        inc_refference_count(items[i], 0, FALSE);
    }

    CLObject hash_object = create_hash_object(type_name, info);
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

    CLObject block_object = create_block_object(&codes2, &constant2, parent_stack, parent_var_num, block_var_num, lambda, info);

    return block_object;
}

struct sPointerAndBoolResult* run_load_field_address(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, int field_index, CLObject obj)
{
    struct sPointerAndBoolResult* result = &gCLPointerAndBoolStructMemory;

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(4)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* object_pointer = CLOBJECT(obj);
    sCLClass* klass = object_pointer->mClass;

    if(klass == NULL) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(51)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(5)");
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
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(52)");
        result->result1 = NULL;
        result->result2 = FALSE;
        return result;
    }

    if(field_index < 0 || field_index >= klass->mNumClassFields) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"field index is invalid(6)");
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

void* run_buffer_to_pointer_cast(CLObject object, sVMInfo* info)
{
    sCLObject* object_data = CLOBJECT(object);

    char* pointer_value = object_data->mFields[3].mPointerValue;

    push_object_to_global_stack(object, info);

    return (void*)pointer_value;
}

CLObject run_int_to_string_cast(int n, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%d", n);

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_long_to_string_cast(clint64 l, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%lld", l);

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_uint_to_string_cast(unsigned int n, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%u", n);

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_ulong_to_string_cast(clint64 l, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%lld", l);

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_float_to_string_cast(float f, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%f", f);

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_double_to_string_cast(double d, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%lf", d);

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_char_to_string_cast(wchar_t c, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%lc", c);

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_regex_to_string_cast(CLObject regex, sVMInfo* info)
{
    sRegexObject* object_data = CLREGEX(regex);

    CLObject str = create_string_object(object_data->mRegexString, info);

    return str;
}

CLObject run_bool_to_string_cast(BOOL b, sVMInfo* info)
{
    char buf[32];
    if(b) {
        snprintf(buf, 32, "true");
    }
    else {
        snprintf(buf, 32, "false");
    }

    CLObject str = create_string_object(buf, info);

    return str;
}

CLObject run_pointer_to_string_cast(char* p, sVMInfo* info)
{
    char buf[32];
    snprintf(buf, 32, "%p", (void*)p);

    CLObject str = create_string_object(buf, info);

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
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"class not found(53)");
        result->result1.mIntValue = 0;
        result->result2 = FALSE;
        return result;
    }

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Null pointer exception(9)");
        result->result1.mIntValue = 0;
        result->result2 = FALSE;
        return result;
    }

    sCLObject* array_data = CLOBJECT(array);
    int array_num = array_data->mArrayNum;

    sCLClass* klass2 = get_class((char*)"Array");
    MASSERT(klass2 != NULL);

    char type_name[OBJECT_TYPE_NAME_MAX];
    snprintf(type_name, OBJECT_TYPE_NAME_MAX, "Array<%s>", CLASS_NAME(klass));

    CLObject new_array = create_object(klass2, type_name, info);

    CLVALUE cl_value;
    cl_value.mObjectValue = new_array;
    push_value_to_global_stack(cl_value, info);

    CLObject new_primitive_array;
    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        new_primitive_array = create_array_object(klass->mBoxingClass, array_num, info);
    }
    else {
        new_primitive_array = create_array_object(klass, array_num, info);
    }

    inc_refference_count(new_primitive_array, 0, FALSE);

    sCLObject* new_array_data = CLOBJECT(new_array);

    new_array_data->mFields[0].mObjectValue = new_primitive_array;

    /// boxing element ///
    int i;
    for(i=0; i<array_num; i++ ) {
        array_data = CLOBJECT(array);           // reget for GC

        CLVALUE element;
        boxing_primitive_value_to_object(array_data->mFields[i], &element, klass, info);

        sCLObject* new_primitive_array_data = CLOBJECT(new_primitive_array);
        new_primitive_array_data->mFields[i] = element;

        inc_refference_count(element.mObjectValue, 0, FALSE);
    }

    pop_global_stack(info);

    result->result1.mObjectValue = new_array;
    result->result2 = TRUE;

    return result;
}

void show_method_parametor_address(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address, int var_num, sConst* constant, sByteCode* code)
{
    printf("stack_ptr %p lvar %p info %p stack %p stack_ptr_address %p var_num %d constant %p code %p\n", (void*)stack_ptr, (void*)lvar, (void*)info, (void*)stack, (void*)stack_ptr_address, var_num, (void*)constant, (void*)code);
}

CLObject run_op_string_with_string_expression(char* str, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr, sVMInfo* info)
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

    CLObject string_object = create_string_object(buf.mBuf, info);

    MFREE(buf.mBuf);

    return string_object;
}

CLObject run_op_buffer_with_string_expression(char* str, int len, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr, sVMInfo* info)
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

    sBuf_append(&buf, str + offset_before, len - offset_before);

    (*stack_ptr) -= num_string_expression;

    CLObject buffer_object = create_buffer_object(buf.mBuf, buf.mLen, info);

    MFREE(buf.mBuf);

    return buffer_object;
}

CLObject run_op_path_with_string_expression(char* str, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr, sVMInfo* info)
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

    CLObject path_object = create_path_object(buf.mBuf, info);

    MFREE(buf.mBuf);

    return path_object;
}

CLObject run_op_regex_with_string_expression(char* str, int* string_expression_offsets, int num_string_expression, CLVALUE** stack_ptr, BOOL global, BOOL ignore_case, BOOL multiline, BOOL extended, BOOL dotall, BOOL anchored, BOOL dollar_endonly, BOOL ungreedy, sVMInfo* info)
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

    CLObject regex_object = create_regex_object(buf.mBuf, global, ignore_case, multiline, extended, dotall, anchored, dollar_endonly, ungreedy, info);

    MFREE(buf.mBuf);

    return regex_object;
}

void mark_source_position(sVMInfo* info, char* sname, int sline)
{
    info->sname2 = sname;
    info->sline2 = sline;
}

BOOL op_is_fun(CLObject left, CLObject right)
{
    sCLObject* object_data = CLOBJECT(left);

    char* left_class_name = object_data->mType;
    char* right_class_name = ALLOC string_object_to_char_array(right);

    BOOL result = strcmp(left_class_name, right_class_name) == 0;

    MFREE(right_class_name);

    return result;
}

void split_tuple(CLVALUE** stack_ptr, sVMInfo* info, CLObject tuple, int num_elements)
{
    sCLObject* object_data = CLOBJECT(tuple);

    int i;
    for(i=0; i<num_elements; i++) {
        **stack_ptr = object_data->mFields[i];
        (*stack_ptr)++;
    }
}

void vm_mutex_on_in_jit(sVMInfo* info)
{
    if(!info->no_mutex_in_vm) {
        vm_mutex_on();
    }
}

void vm_mutex_off_in_jit(sVMInfo* info)
{
    if(!info->no_mutex_in_vm) {
        vm_mutex_off();
    }
}

BOOL run_store_to_buffer(CLObject object, char* pointer, CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    sCLObject* object_data = CLOBJECT(object);

    if(pointer < object_data->mFields[0].mPointerValue || pointer >= object_data->mFields[0].mPointerValue + object_data->mFields[2].mULongValue) {
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, (char*)"Exception", (char*)"Out of range on memory safe pointer(4)");
        return FALSE;
    }

    object_data->mFields[3].mPointerValue = pointer;

    return TRUE;
}

}
