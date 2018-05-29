#include "clover2-debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/ioctl.h>

char* xstrncpy(char* des, char* src, int size)
{
    char* result;

    result = strncpy(des, src, size-1);
    des[size-1] = 0;

    return result;
}

char* xstrncat(char* des, char* str, int size)
{
    char* result;

    result = strncat(des, str, size-1);
    des[size-1] = 0;

    return result;
}

ALLOC char* xwcstombs(wchar_t* wstr, int len)
{
    char* result = MCALLOC(1, MB_LEN_MAX * (len + 1));

    if((int)wcstombs(result, wstr, MB_LEN_MAX * (len+1)) < 0) {
        result[0] = '\0';
    }

    return result;
}
