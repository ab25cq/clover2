#include "common.h"

BOOL ExtTest_hello(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* num = lvar;

    int num_value = num->mIntValue;

    printf("HELLO CLOVER2 EXTENSION %d\n", num_value);

    (*stack_ptr)->mIntValue = num_value * 2;
    (*stack_ptr)++;

    return TRUE;
}
