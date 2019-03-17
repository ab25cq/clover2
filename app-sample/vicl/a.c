#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    printf("1 %d\n", (12363 & 0x80) >> 7);
    printf("2 %d\n", (12363 & 0x40) >> 6);
    printf("3 %d\n", (12363 & 0x20) >> 5);
    printf("4 %d\n", (12363 & 0x10) >> 4);

    printf("5 %d\n", (12363 & 128) >> 7);
    printf("6 %d\n", (12363 & 64) >> 6);
    printf("7 %d\n", (12363 & 32) >> 5);
    printf("8 %d\n", (12363 & 16) >> 4);
    
    exit(0);
}
