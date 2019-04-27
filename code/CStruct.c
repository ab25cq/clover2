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
    printf("HELLO array %c %c %c\n", data[0], data[1], data[4]);
}

void fun3(int a, int b)
{
    printf("fun3 %d\n", a + b);
}
