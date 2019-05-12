#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CStruct.h"

int gVar;

void fun(struct CStruct data)
{
    printf("CFFI test1-a...");
    assert(data.a == 'C' && data.b == 123 && data.c == 234);
    puts("OK");
}

void fun2(char data[5])
{
    printf("CFFI test2...");
    assert(data[0] == 'A' && data[1] == 'B' && data[4] == 'E');
    puts("OK");
}

void fun3(int a, int b)
{
    printf("CFFI test3...");
    assert(a == 1 && b == 2);
    puts("OK");
}

void fun4(char data[3])
{
    printf("CFFI test4...");
    assert(data[0] == 'A' && data[1] == 'B' && data[2] == 'C');
    puts("OK");
}

void fun5(struct CStruct data)
{
    printf("CFFI test5...");
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
    printf("CFFI test8...");
    assert(strcmp(str, "ABC") == 0);
    puts("OK");
}

int fun9(int x, int y)
{
    return x + y;
}

int fun10(int x)
{
    return x;
}

void fun11()
{
    gVar = 123;
}

void fun12(char c)
{
    printf("%c %d\n", c, c);
}

void fun13(int* data)
{
    printf("data[0] %d data[1] %d data[2] %d\n", data[0], data[1], data[2]);
}

void fun14(int data[3])
{
    printf("data[0] %d data[1] %d data[2] %d\n", data[0], data[1], data[2]);
}

void fun15(char data[3])
{
    printf("data[0] %d data[1] %d data[2] %d\n", data[0], data[1], data[2]);
}

void fun16(struct CStruct data)
{
    printf("CFFI Test...");
    assert(data.a == 'C' && data.b == 123 && data.c == 234);
    puts("OK");
}

void fun17(struct CStruct2 data)
{
    printf("CFFI Test...");
    assert(data.XXX.a == 111 && data.XXX.b == 222 && data.ZZZ.zzz == 333 && data.c == 444);
    puts("OK");
}

void fun18()
{
    struct CStruct2 data;
    data.XXX.a = 111;
    data.XXX.b = 222;
    data.ZZZ.zzz = 333;
    data.c = 444;
    fun17(data);
}

struct CStruct2 fun19()
{
    struct CStruct2 data;

    data.XXX.a = 111;
    data.XXX.b = 222;
    data.ZZZ.zzz = 333;
    data.c = 444;

    return data;
}

void fun20()
{
    struct CStruct2 data = fun19();
}
