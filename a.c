#include <stdio.h>
#include <stdlib.h>

int main() 
{
    float a = atof("123.123");
    float b = 123.123f;

    if(a == b) {
        puts("YES");
    }
    else {
        puts("NO");
    }

    exit(0);
}
