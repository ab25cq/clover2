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

    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "-clean") == 0) {
            system("rm -rf *.oclcl *.ocl");
            continue;
        }

        char* p = strstr(argv[i], ".");

        char base_name[PATH_MAX];

        memcpy(base_name, argv[i], p - argv[i]);
        base_name[p - argv[i]] = '\0';

        char sname[PATH_MAX];
        snprintf(sname, PATH_MAX, "%s.ocl", base_name);

        if(strcmp(argv[i], sname) != 0) {
            if(access(sname, R_OK) != 0) {
                char cmd[PATH_MAX+20];
                sprintf(cmd, "cclover2 %s", argv[i]);
                (void)system(cmd);
            }
            else {
                struct stat stat_;
                struct stat stat_2;

                if(stat(argv[i], &stat_) == 0 && stat(sname, &stat_2) == 0) {
                    if(stat_.st_mtime >= stat_2.st_mtime) {
                        char cmd[PATH_MAX+20];
                        sprintf(cmd, "cclover2 %s", argv[i]);
                        (void)system(cmd);
                    }
                }
            }
        }

        clover2_init();
        if(!eval_file(sname, CLOVER_STACK_SIZE)) {
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

