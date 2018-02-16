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
        /// 出力ファイルのクリーン
        if(strcmp(argv[i], "-clean") == 0) {
            system("rm -rf *.oclcl *.ocl");
            continue;
        }
        else if(strcmp(argv[i], "-version") == 0 || strcmp(argv[i], "--version") == 0) {
            printf("clover2 version 3.6.1\n");
            exit(0);
        }

        char* source = argv[i];

        /// oclファイル名を得る
        char* p = source + strlen(source);

        while(p >= source) {
            if(*p == '.') {
                break;
            }
            else {
                p--;
            }
        }

        if(p < source) {
            p = NULL;
        }

        if(p == NULL) {
            p = source + strlen(source);
        }

        char base_name[PATH_MAX];

        memcpy(base_name, source, p - source);
        base_name[p - source] = '\0';

        char object_file_name[PATH_MAX];
        snprintf(object_file_name, PATH_MAX, "%s.ocl", base_name);

        /// 自動コンパイル機能 ///
        if(strcmp(source, object_file_name) != 0) {
            if(access(object_file_name, R_OK) != 0) {
                char cmd[PATH_MAX+20];

                char command_path[PATH_MAX+1];
                snprintf(command_path, PATH_MAX, "./cclover2");

                if(access(command_path, X_OK) == 0) {
                    sprintf(cmd, "./cclover2 %s", source);
                }
                else {
                    sprintf(cmd, "cclover2 %s", source);
                }
                int rc = system(cmd);

                if(rc != 0) {
                    fprintf(stderr, "automatically compile faield\n");
                    exit(1);
                }
            }
            else {
                struct stat source_stat;
                struct stat object_file_stat;

                if(stat(source, &source_stat) == 0 && stat(object_file_name, &object_file_stat) == 0) 
                {
                    if(source_stat.st_mtime >= object_file_stat.st_mtime) {
                        char cmd[PATH_MAX+20];

                        char command_path[PATH_MAX+1];
                        snprintf(command_path, PATH_MAX, "./cclover2");

                        if(access(command_path, X_OK) == 0) {
                            sprintf(cmd, "./cclover2 %s", source);
                        }
                        else {
                            sprintf(cmd, "cclover2 %s", source);
                        }
                        int rc = system(cmd);

                        if(rc != 0) {
                            fprintf(stderr, "automatically compile faield\n");
                            exit(1);
                        }
                    }
                }
                else {
                    fprintf(stderr, "automatically compile faield\n");
                    exit(1);
                }
            }
        }

        clover2_init();
        if(!eval_file(object_file_name, CLOVER_STACK_SIZE)) {
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

