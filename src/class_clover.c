#include "common.h"

BOOL Clover_load(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* file_name = lvar;

    if(file_name->mObjectValue) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* file_name_value = ALLOC string_object_to_char_array(file_name->mObjectValue);

    /// go ///
    BOOL result = eval_file(file_name_value, CLOVER_STACK_SIZE);

    if(!result) {
        MFREE(file_name_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Clover.load is faield");
        return FALSE;
    }

    MFREE(file_name_value);

    return TRUE;
}

BOOL Clover_initialize_lang(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* clover = get_class("Clover");

    clover->mClassFields[0].mValue.mIntValue = gARGC;

    sCLClass* string_class = get_class("String");

    CLObject array = create_array_object(string_class, gARGC);

    CLVALUE value;
    value.mObjectValue = array;
    push_value_to_global_stack(value);

    int i;
    for(i=0; i<gARGC; i++) {
        CLObject obj = create_string_object(gARGV[i]);

        sCLObject* object_data = CLOBJECT(array);

        object_data->mFields[i].mObjectValue = obj;
    }

    clover->mClassFields[1].mValue.mObjectValue = array;
    clover->mClassFields[2].mValue.mObjectValue = create_string_object(gVersion);
    clover->mClassFields[3].mValue.mULongValue = sizeof(sCLObject) - sizeof(CLVALUE) * DUMMY_ARRAY_SIZE;
    clover->mClassFields[4].mValue.mULongValue = sizeof(CLVALUE);

    pop_global_stack();

    return TRUE;
}

BOOL Clover_initialize_reflection(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* clover = get_class("Clover");

    clover->mClassFields[5].mValue.mLongValue = FIELD_FLAGS_PRIVATE;
    clover->mClassFields[6].mValue.mLongValue = FIELD_FLAGS_PROTECTED;

    clover->mClassFields[7].mValue.mLongValue = CLASS_FLAGS_PRIMITIVE;
    clover->mClassFields[8].mValue.mLongValue = CLASS_FLAGS_INTERFACE;
    clover->mClassFields[9].mValue.mLongValue = CLASS_FLAGS_MODIFIED;
    clover->mClassFields[10].mValue.mLongValue = CLASS_FLAGS_ALLOCATED;
    clover->mClassFields[11].mValue.mLongValue = CLASS_FLAGS_DYNAMIC_CLASS;
    clover->mClassFields[12].mValue.mLongValue = CLASS_FLAGS_NO_FREE_OBJECT;

    return TRUE;
}


BOOL Clover_getField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;
    CLVALUE* index = lvar + 1;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    int index_value = index->mIntValue;

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    if(index_value < 0 || index_value >= klass2->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid field index");
        MFREE(class_name_value);
        return FALSE;
    }

    /// prepare for the body ///
    sCLClass* field_class = get_class("Field");

    CLVALUE cl_value;
    CLObject result = create_object(field_class, "Field");

    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    sCLField* field = &klass2->mFields[index_value];

    clint64 field_flags = field->mFlags;

    char* field_name = CONS_str(&klass2->mConst, field->mNameOffset);

    CLObject field_name_object = create_string_object(field_name);

    cl_value.mObjectValue = field_name_object;
    push_value_to_global_stack(cl_value);

    sCLType* cl_type = field->mResultType;

    char* field_result_type = ALLOC cl_type_to_string(cl_type, klass2);

    CLObject field_result_type_object = create_string_object(field_result_type);

    cl_value.mObjectValue = field_result_type_object;
    push_value_to_global_stack(cl_value);

    /// go ///
    sCLObject* obj_data = CLOBJECT(result);
    obj_data->mFields[0].mLongValue = field_flags;                  // flags
    obj_data->mFields[1].mObjectValue = field_name_object;          // name
    obj_data->mFields[2].mObjectValue = field_result_type_object;   // result type

    (*stack_ptr)->mObjectValue = result;
    (*stack_ptr)++;

    pop_global_stack();
    pop_global_stack();
    pop_global_stack();

    MFREE(class_name_value);
    MFREE(field_result_type);

    return TRUE;
}

BOOL Clover_getClassField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;
    CLVALUE* index = lvar + 1;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    int index_value = index->mIntValue;

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    if(index_value < 0 || index_value >= klass2->mNumFields) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid field index");
        MFREE(class_name_value);
        return FALSE;
    }

    /// prepare for the body ///
    sCLClass* field_class = get_class("Field");

    CLVALUE cl_value;
    CLObject result = create_object(field_class, "Field");

    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    sCLField* field = &klass2->mClassFields[index_value];

    clint64 field_flags = field->mFlags;

    char* field_name = CONS_str(&klass2->mConst, field->mNameOffset);

    CLObject field_name_object = create_string_object(field_name);

    cl_value.mObjectValue = field_name_object;
    push_value_to_global_stack(cl_value);

    sCLType* cl_type = field->mResultType;

    char* field_result_type = ALLOC cl_type_to_string(cl_type, klass2);

    CLObject field_result_type_object = create_string_object(field_result_type);

    cl_value.mObjectValue = field_result_type_object;
    push_value_to_global_stack(cl_value);

    /// go ///
    sCLObject* obj_data = CLOBJECT(result);
    obj_data->mFields[0].mLongValue = field_flags;                  // flags
    obj_data->mFields[1].mObjectValue = field_name_object;          // name
    obj_data->mFields[2].mObjectValue = field_result_type_object;   // result type

    (*stack_ptr)->mObjectValue = result;
    (*stack_ptr)++;

    pop_global_stack();
    pop_global_stack();
    pop_global_stack();

    MFREE(class_name_value);
    MFREE(field_result_type);

    return TRUE;
}

BOOL Clover_getMethod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;
    CLVALUE* index = lvar + 1;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    int index_value = index->mIntValue;

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    if(index_value < 0 || index_value >= klass2->mNumMethods) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method index");
        MFREE(class_name_value);
        return FALSE;
    }

    /// prepare for the body ///
    sCLClass* method_class = get_class("Method");

    MASSERT(method_class != NULL);

    CLVALUE cl_value;
    CLObject result = create_object(method_class, "Method");

    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    sCLMethod* method = &klass2->mMethods[index_value];

    clint64 method_flags = method->mFlags;

    char* method_name = CONS_str(&klass2->mConst, method->mNameOffset);

    CLObject method_name_object = create_string_object(method_name);

    cl_value.mObjectValue = method_name_object;
    push_value_to_global_stack(cl_value);

    char* path_name = CONS_str(&klass2->mConst, method->mPathOffset);

    CLObject path_name_object = create_string_object(path_name);

    cl_value.mObjectValue = path_name_object;
    push_value_to_global_stack(cl_value);

    char* method_name_and_params = CONS_str(&klass2->mConst, method->mMethodNameAndParamsOffset);

    CLObject method_name_and_params_object = create_string_object(method_name_and_params);

    cl_value.mObjectValue = method_name_and_params_object;
    push_value_to_global_stack(cl_value);

    int method_index = method->mMethodIndex;

    sCLClass* method_param_class = get_class("MethodParam");

    CLObject params_object = create_array_object(method_param_class, method->mNumParams);

    cl_value.mObjectValue = params_object;
    push_value_to_global_stack(cl_value);

    int i;
    for(i=0; i<method->mNumParams; i++) {
        sCLParam* param = method->mParams + i;

        CLObject param_object = create_object(method_param_class, "MethodParam");

        sCLObject* object_data = CLOBJECT(params_object);
        object_data->mFields[i].mObjectValue = param_object;

        char* name = CONS_str(&klass2->mConst, param->mNameOffset);
        CLObject name_object = create_string_object(name);

        sCLObject* object_data2 = CLOBJECT(param_object);
        object_data2->mFields[0].mObjectValue = name_object;

        sCLType* cl_type = param->mType;
        char* type = ALLOC cl_type_to_string(cl_type, klass2);
        CLObject type_name_object = create_string_object(type);
        MFREE(type);

        object_data2 = CLOBJECT(param_object);   // prepend from memory move on GC
        object_data2->mFields[1].mObjectValue = type_name_object;
    }

    sCLType* cl_type = method->mResultType;
    char* type = ALLOC cl_type_to_string(cl_type, klass2);
    CLObject type_name_object = create_string_object(type);
    MFREE(type);

    cl_value.mObjectValue = type_name_object;
    push_value_to_global_stack(cl_value);

    int var_num = method->mVarNum;

    sCLClass* string_class = get_class("String");

    MASSERT(string_class != NULL);

    CLObject generics_param_types_object = create_array_object(string_class, method->mNumGenerics);

    cl_value.mObjectValue = generics_param_types_object;
    push_value_to_global_stack(cl_value);

    for(i=0; i<method->mNumGenerics; i++) {
        char* generics_param_class_name = CONS_str(&klass2->mConst, method->mGenericsParamTypeOffsets[i]);
        CLObject generics_param_class_name_object = create_string_object(generics_param_class_name);

        sCLObject* object_data3 = CLOBJECT(generics_param_types_object);
        object_data3->mFields[i].mObjectValue = generics_param_class_name_object;
    }

    /// go ///
    sCLObject* obj_data = CLOBJECT(result);
    obj_data->mFields[0].mLongValue = method_flags;         // flags
    obj_data->mFields[1].mObjectValue = method_name_object; // name
    obj_data->mFields[2].mObjectValue = path_name_object;   // path
    obj_data->mFields[3].mObjectValue = method_name_and_params_object;
                                                            // methodNameAndParams
    obj_data->mFields[4].mIntValue = method_index;          // index
    obj_data->mFields[5].mObjectValue = params_object;      // MethodParam[]
    obj_data->mFields[6].mObjectValue = type_name_object;   // resultType
    obj_data->mFields[7].mIntValue = var_num;               // varNum
    obj_data->mFields[8].mObjectValue = generics_param_types_object; // genericsParamTypes

    (*stack_ptr)->mObjectValue = result;
    (*stack_ptr)++;

    pop_global_stack();
    pop_global_stack();
    pop_global_stack();
    pop_global_stack();
    pop_global_stack();
    pop_global_stack();
    pop_global_stack();

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_getClassFlags(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    /// go ///
    (*stack_ptr)->mLongValue = klass2->mFlags;
    (*stack_ptr)++;

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_getClassGenericsParamTypes(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    /// prepare for the body ///
    sCLClass* string_class = get_class("String");

    MASSERT(string_class != NULL);

    CLObject generics_param_types_object = create_array_object(string_class, klass2->mNumGenerics);

    CLVALUE cl_value;
    cl_value.mObjectValue = generics_param_types_object;
    push_value_to_global_stack(cl_value);

    int i;
    for(i=0; i<klass2->mNumGenerics; i++) {
        char* generics_param_class_name = CONS_str(&klass2->mConst, klass2->mGenericsParamTypeOffsets[i]);
        CLObject generics_param_class_name_object = create_string_object(generics_param_class_name);

        sCLObject* object_data3 = CLOBJECT(generics_param_types_object);
        object_data3->mFields[i].mObjectValue = generics_param_class_name_object;
    }

    /// go ///
    (*stack_ptr)->mObjectValue = generics_param_types_object;
    (*stack_ptr)++;

    pop_global_stack();

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_getClassGenericsParamNames(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    /// prepare for the body ///
    sCLClass* string_class = get_class("String");

    MASSERT(string_class != NULL);

    CLObject generics_param_names_object = create_array_object(string_class, klass2->mNumGenerics);

    CLVALUE cl_value;
    cl_value.mObjectValue = generics_param_names_object;
    push_value_to_global_stack(cl_value);

    int i;
    for(i=0; i<klass2->mNumGenerics; i++) {
        char* generics_param_name = CONS_str(&klass2->mConst, klass2->mGenericsParamNameOffsets[i]);
        CLObject generics_param_name_object = create_string_object(generics_param_name);

        sCLObject* object_data3 = CLOBJECT(generics_param_names_object);
        object_data3->mFields[i].mObjectValue = generics_param_name_object;
    }

    /// go ///
    (*stack_ptr)->mObjectValue = generics_param_names_object;
    (*stack_ptr)++;

    pop_global_stack();

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_getNumFields(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    /// go ///
    (*stack_ptr)->mIntValue = klass2->mNumFields;
    (*stack_ptr)++;

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_getNumClassFields(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    /// go ///
    (*stack_ptr)->mIntValue = klass2->mNumClassFields;
    (*stack_ptr)++;

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_getNumMethods(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(class_name_value);
        return FALSE;
    }

    /// go ///
    (*stack_ptr)->mIntValue = klass2->mNumMethods;
    (*stack_ptr)++;

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_isLoadedClass(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    sCLClass* klass2 = get_class(class_name_value);

    /// go ///
    (*stack_ptr)->mIntValue = klass2 != NULL;
    (*stack_ptr)++;

    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_isDefinedClass(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* class_name = lvar;

    /// Clover to c value ///
    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    /// go ///
    char class_file_name[PATH_MAX];

    (*stack_ptr)->mIntValue = search_for_class_file(class_name_value, class_file_name, PATH_MAX);
    (*stack_ptr)++;

    MFREE(class_name_value);

    return TRUE;
}
