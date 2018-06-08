#include "jit_common.hpp"

extern "C"
{

void show_int8(char number)
{
    printf("int8 %d\n", number);
}

void show_int16(short number)
{
    printf("int16 %d\n", number);
}

void show_int32(int number)
{
    printf("int32 %d\n", number);
}

void show_int64(clint64 number)
{
    printf("int64 %lld\n", number);
}

void show_float(float number)
{
    printf("float %f\n", number);
}

void show_double(double number)
{
    printf("double %lf\n", number);
}

void show_str_in_jit(char* str)
{
    printf("%s\n", str);
}

void show_stack_stat(CLVALUE** stack_ptr, CLVALUE* stack)
{
    printf("stack_ptr %p\n", (void*)*stack_ptr);
    printf("stack %p\n", (void*)stack);
    printf("stack_ptr - stack %d\n", (int)((*stack_ptr) - stack));
}

}
