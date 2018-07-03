#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getValue(int x, int y) 
{
    return x + y;
}

long getValue2(long x, long y)
{
    return x + y;
}

char* getStr(char* x, char* y) 
{
    size_t len = strlen(x) + strlen(y) + 1;

    char* result = calloc(1, len);

    strcpy(result, x);
    strcat(result, y);

    return result;
}


