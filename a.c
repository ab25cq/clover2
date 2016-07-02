#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union ValueUnion {
    int ivalue;
    long lvalue;
};

typedef union ValueUnion Value;

int main() {
    long l = 5;
    int a = 5;

    if(l == a) {
        puts("YES");
    }
    else {
        puts("NO");
    }

    exit(0);
}
