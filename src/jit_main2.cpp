#include "jit_common.hpp"
#include <signal.h>
#include <libgen.h>

extern "C" 
{
extern void clover2_init();
extern void clover2_final();
extern void set_signal();

extern int gARGC;
extern char** gARGV;

extern BOOL clover2_main(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address, int var_num, sConst* constant, sByteCode* code, CLVALUE** global_stack_ptr_address, CLVALUE* stack_plus_var_num);

int main(int argc, char** argv)
{
    gARGC = argc;
    gARGV = argv;

    set_signal();

    clover2_init();

    int stack_size = CLOVER_STACK_SIZE;

    CLVALUE* stack = (CLVALUE*)MCALLOC(1, sizeof(CLVALUE)*stack_size);

    sVMInfo info;
    memset(&info, 0, sizeof(info));

    info.stack = stack;

    info.running_class_name = MSTRDUP("none");
    info.running_method_name = MSTRDUP("jit_main");

    create_global_stack_and_append_it_to_stack_list(&info);

    vm_mutex_on();

    int var_num = METHOD_VAR_NUM_MAX;

    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    sCLStack* stack_id = append_stack_to_stack_list(info.stack, &stack_ptr, FALSE);

    info.current_stack = stack;        // for invoking_block in native method
    info.current_var_num = var_num;
    info.stack_id = stack_id;

    CLVALUE** stack_ptr_address = &stack_ptr;

    CLVALUE** global_stack_ptr_address = &info.mTmpGlobalStackPtr;

    sByteCode codes;
    sConst constant;

    BOOL result = clover2_main(stack_ptr, lvar, &info, stack, stack_ptr_address, var_num, &constant, &codes, global_stack_ptr_address, stack + var_num);

    if(!result) {
        remove_stack_to_stack_list(stack_id);
        clover2_final();
        exit(1);
    }

    vm_mutex_off(); // see OP_RETURN

    MFREE(stack);

    remove_stack_to_stack_list(stack_id);

    clover2_final();

    return 0;
}
}
