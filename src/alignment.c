#include "common.h"

void alignment(unsigned int* size)
{
    *size = (*size + 3) & ~3;
}

void alignment_pointer(char** p, char* head)
{
    unsigned int len = *p - head;

    alignment(&len);

    *p = head + len;
}
