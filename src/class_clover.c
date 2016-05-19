#include "common.h"

BOOL Clover_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* size = lvar;

    (*stack_ptr)->mPointerValue = MMALLOC(size->mIntValue);
    (*stack_ptr)++;

    return TRUE;
}

BOOL Clover_free(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pointer = lvar;

    MFREE(pointer->mPointerValue);

    return TRUE;
}

BOOL Clover_GC_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* size = lvar;

    (*stack_ptr)->mPointerValue = malloc(size->mIntValue);
    (*stack_ptr)++;

    return TRUE;
}

