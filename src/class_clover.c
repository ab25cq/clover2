#include "common.h"

BOOL Clover_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* size = lvar;

    char* memory = MMALLOC(size->mIntValue);

printf("malloc %p\n", memory);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL Clover_free(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pointer = lvar;

printf("free %p\n", pointer->mPointerValue);

    MFREE(pointer->mPointerValue);

    return TRUE;
}
