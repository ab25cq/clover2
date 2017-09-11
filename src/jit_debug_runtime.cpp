#include "jit_common.hpp"

extern "C"
{

void show_number_in_jit(clint64 number)
{
    printf("%ld(%p)\n", number, number);
}

}
