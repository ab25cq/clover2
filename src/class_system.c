#include "common.h"

BOOL System_exit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* num = lvar;

    exit(num->mIntValue);

    return TRUE;
}

BOOL System_assert(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* exp = lvar;

    if(!exp->mBoolValue) {
        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "System.assert failed");
        return FALSE;
    }

    return TRUE;
}

BOOL System_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* size = lvar;

    char* memory = MMALLOC(size->mIntValue);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_calloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* number = lvar;
    CLVALUE* size = lvar + 1;

    char* memory = MCALLOC(number->mIntValue, size->mIntValue);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_free(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pointer = lvar;

    MFREE(pointer->mPointerValue);

    return TRUE;
}

BOOL System_strlen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    (*stack_ptr)->mIntValue = strlen(str->mPointerValue);
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strcpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;

    strcpy(str1->mPointerValue, str2->mPointerValue);

    (*stack_ptr)->mPointerValue = str2->mPointerValue;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strncpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;
    CLVALUE* size = lvar + 2;

    xstrncpy(str1->mPointerValue, str2->mPointerValue, size->mIntValue);

    (*stack_ptr)->mPointerValue = str2->mPointerValue;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strdup(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    char* result = MSTRDUP(str->mPointerValue);

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_print(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = wstr_array_object_data->mArrayNum;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    printf("%ls", wstr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_println(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = wstr_array_object_data->mArrayNum;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    printf("%ls\n", wstr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_printToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = wstr_array_object_data->mArrayNum;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    fprintf(stderr, "%ls", wstr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_printlnToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = wstr_array_object_data->mArrayNum;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    fprintf(stderr, "%ls\n", wstr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_sleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* time = lvar;

    unsigned int result = sleep(lvar->mIntValue);

    (*stack_ptr)->mUIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

#define OVECCOUNT (10*3)

BOOL System_pcre_exec(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* regex = lvar;

    CLVALUE* str = (lvar+1);

    /// convert Clover value to C value ///
    sRegexObject* regex_object_data = CLREGEX(regex->mObjectValue);

    pcre* regex_value = regex_object_data->mRegex;
    BOOL global_value = regex_object_data->mGlobal;
    BOOL ignore_case_value = regex_object_data->mIgnoreCase;

    sCLObject* str_object_data = CLOBJECT(str->mObjectValue);
    CLObject wstr_array = str_object_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_data = CLOBJECT(wstr_array);

    int len = wstr_array_data->mArrayNum;

    wchar_t* wstr = MCALLOC(1, sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wstr_array_data->mFields[i].mCharValue;
    }
    wstr[i] = '\0';
    
    char* str_value = ALLOC xwcstombs(wstr, len);

    MFREE(wstr);

    /// go ///
    int Ovector[OVECCOUNT];
    int result = pcre_exec(regex_value, NULL, str_value, len, 0, 0, Ovector, OVECCOUNT);

    MFREE(str_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

