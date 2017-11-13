#include "common.h"
#include <signal.h>


static void clover2_init()
{
#ifdef ENABLE_JIT
    jit_init_on_runtime();
#endif
    native_method_init();
    class_init();
    heap_init(128, 128);
    stack_init();
    (void)class_init_on_runtime();
}

static void clover2_final()
{
    class_final_on_runtime();
    heap_final();
    stack_final();
    class_final();
    native_method_final();
#ifdef ENABLE_JIT
    jit_final_on_runtime();
#endif
}

static void set_signal()
{
    struct sigaction sa;
    sigset_t signal_set;

    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGTTOU);
    sigaddset(&signal_set, SIGPIPE);

    sigprocmask(SIG_BLOCK, &signal_set, NULL);
}

int main(int argc, char** argv, char* const * envp)
{
    int i;


    CHECKML_BEGIN;
    setlocale(LC_ALL, "");

    set_signal();
    char sname[PATH_MAX];

    for(i=1; i<argc; i++) {
        xstrncpy(sname, argv[i], PATH_MAX);
        char* ext_sname = strstr(sname, ".");
        if(ext_sname == NULL) {
            xstrncat(sname,".cl", PATH_MAX);
            ext_sname = strstr(sname, ".");
        }
        if(ext_sname != NULL && (strcmp(ext_sname,".cl")==0 || strcmp(ext_sname,".clc")==0)) {
            char cmd[PATH_MAX+20];
            sprintf(cmd, "cclover2 %s", sname);
            int rc = system(cmd);
            if(rc != 0) exit(rc);
            if(strcmp(ext_sname,".clc")==0) continue;
            xstrncpy(ext_sname,".clo", PATH_MAX);
        }
        clover2_init();
        if(!eval_file(sname, CLOVER_STACK_SIZE)) {
            fprintf(stderr, "script file(%s) is abort\n", sname);
            clover2_final();
            CHECKML_END;
            exit(1);
        }
        clover2_final();
    }
    CHECKML_END;

    return 0;
}

