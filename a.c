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
    long a;
    int b = 1;
    int c = 0;
    memcpy(&a, &b, sizeof(int));
    memcpy((char*)&a + sizeof(int), &c, sizeof(int));

    if(a == 1) {
        puts("YES");
    }
    else {
        puts("NO");
    }

    exit(0);
}
