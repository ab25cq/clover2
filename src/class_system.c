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
        entry_exception_object_with_class_name(*stack_ptr, "Exception", "System.assert failed");
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
