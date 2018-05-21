#include "common.h"

void alignment(unsigned int* size)
{
    *size = (*size + 3) & ~3;
}
