#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 123;
    int* p = &a;
    
    p++;

    printf("%p\n", p);

    exit(0);
}
