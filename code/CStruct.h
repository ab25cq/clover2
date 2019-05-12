
struct CStruct {
    char a;
    int b;
    long c;
};

extern void fun(struct CStruct data);
extern void fun2(char data[5]);
extern void fun3(int a, int b);
extern void fun4(char data[3]);
extern void fun5(struct CStruct data);
extern char* fun6();
extern struct CStruct fun7();
extern void fun8(char* str);
extern int fun9(int x, int y);
int fun10(int x);
void fun11();

void fun12(char c);

int gVar;
float gVar2;
double gVar3;
long gVar4;
char gVar5;

long* gVar6;

char gVar7[3];
int gVar8[3];

void fun13(int* data);
void fun14(int data[3]);

void fun15(char data[3]);

struct CStruct gVar9;

void fun16(struct CStruct data);

struct CStruct2 {
    struct {
        int a;
        int b;
    } XXX;

    union {
        long zzz;
        long zzz2;
    } ZZZ;

    long c;
};

void fun17(struct CStruct2 data);

union CUnion {
    int a;
    long b;

    union {
        struct {
            long c;
            long d;

        } XXX;
        int g;
    } YYY;
};

struct CStruct2 gVar10;

void fun18();

struct CStruct2 fun19();

