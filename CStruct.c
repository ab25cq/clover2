#include <stdio.h>
#include <stdlib.h>

struct CStruct {
    char a;
    int b;
    long c;
};

void fun(struct CStruct data)
{
    printf("HELLO STRUCT %c %d %ld\n", data.a, data.b, data.c);
}

void fun2(char data[5])
{
printf("fun2 data %p\n", data);
    printf("HELLO array %c %c %c\n", data[0], data[1], data[4]);
}
