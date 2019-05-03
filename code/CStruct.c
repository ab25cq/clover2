#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CStruct.h"

void fun(struct CStruct data)
{
    printf("struct test1-a...");
    assert(data.a == 'C' && data.b == 123 && data.c == 234);
    puts("OK");
}

void fun2(char data[5])
{
    printf("struct test2...");
    assert(data[0] == 'A' && data[1] == 'B' && data[4] == 'E');
    puts("OK");
}

void fun3(int a, int b)
{
    printf("struct test3...");
    assert(a == 1 && b == 2);
    puts("OK");
}

void fun4(char data[3])
{
    printf("struct test4...");
    assert(data[0] == 'A' && data[1] == 'B' && data[2] == 'C');
    puts("OK");
}

void fun5(struct CStruct data)
{
    printf("struct test5...");
    assert(data.a == 'C' && data.b == 123 && data.c == 234);
    puts("OK");
}

char* fun6()
{
    return "fun6";
}

struct CStruct fun7()
{
    struct CStruct data;
 
    data.a = 'a';
    data.b = 123;;
    data.c = 234;

    return data;
}

void fun8(char* str)
{
    printf("struct test8...");
    assert(strcmp(str, "ABC") == 0);
    puts("OK");
}

int fun9(int x, int y)
{
    return x + y;
}
