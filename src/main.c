#include "common.h"
#include <signal.h>

static void clover2_init()
{
    native_method_init();
    class_init();
    heap_init(128, 128);
    stack_init();
    (void)class_init_on_runtime();
#ifdef ENABLE_JIT
    jit_init();
#endif
}

static void clover2_final()
{
#ifdef ENABLE_JIT
    jit_final();
#endif
    native_method_final();
    stack_final();
    heap_final();
    class_final_on_runtime();
}

static void set_signal()
{
    struct sigaction sa;
    sigset_t signal_set;

    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGTTOU);

    sigprocmask(SIG_BLOCK, &signal_set, NULL);
}

int main(int argc, char** argv)
{
    int i;

    CHECKML_BEGIN;
    setlocale(LC_ALL, "");

    set_signal();

    for(i=1; i<argc; i++) {
        clover2_init();
        if(!eval_file(argv[i], CLOVER_STACK_SIZE)) {
            fprintf(stderr, "script file(%s) is abort\n", argv[i]);
            clover2_final();
            CHECKML_END;
            exit(1);
        }
        clover2_final();
    }
    CHECKML_END;

    return 0;
}

