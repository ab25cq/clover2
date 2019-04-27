#include "jit_common.hpp"
#include <signal.h>
#include <libgen.h>

extern "C" 
{

void clover2_init()
{
    class_system_init();
    thread_init();
    jit_init_on_runtime();
    native_method_init();
    class_init();
    heap_init(HEAP_INIT_SIZE, HEAP_HANDLE_INIT_SIZE);
    stack_init();
    script_init();
    class_init_on_runtime();
}

void clover2_final()
{
    script_final();
    thread_final();
    class_final_on_runtime();
    heap_final();
    stack_final();
    class_final();
    native_method_final();
    jit_final_on_runtime();
}

void set_signal()
{
    struct sigaction sa;
    sigset_t signal_set;

    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGTTOU);
    sigaddset(&signal_set, SIGTTIN);
    sigaddset(&signal_set, SIGPIPE);

    sigprocmask(SIG_BLOCK, &signal_set, NULL);
}

int gARGC;
char** gARGV;
char* gVersion = "10.4.1";
BOOL gCompilingCore = FALSE;

char gScriptDirPath[PATH_MAX];
BOOL gRunningCompiler = FALSE;

}
