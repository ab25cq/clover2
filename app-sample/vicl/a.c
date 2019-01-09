#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(int a, int b) 
{
    return a + b;
}

int helloWorld()
{
    printf("helloWorld\n");
}

int main() 
{
    int a = func(1, 2);
    
    exit(0);
}