#include "common.h"
#include <locale.h>
#define _GNU_SOURCE
#include <stdio.h>

#ifdef HAVE_READLINE_H
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>

static void clover2_init()
{
    class_system_init();
    thread_init();
#ifdef ENABLE_JIT
    jit_init_on_runtime();
#endif
    native_method_init();
    class_init();
    heap_init(HEAP_INIT_SIZE, HEAP_HANDLE_INIT_SIZE);
    stack_init();
    (void)class_init_on_runtime();
}

static void clover2_final()
{
    thread_final();
    class_final_on_runtime();
    heap_final();
    stack_final();
    class_final();
    native_method_final();
#ifdef ENABLE_JIT
    jit_final_on_runtime();
#endif
}

static void compiler_init(BOOL no_load_fudamental_classes)
{
    init_nodes();
    module_init();
}

static void compiler_final()
{
    module_final();
    free_nodes();
}

static BOOL get_type(char* class_name, char* source, char* fname, sVarTable* lv_table, sNodeType** type_, sVarTable** result_lv_table)
{
    sCLClass* klass = NULL;
    if(class_name) {
        klass = get_class_with_load_and_initialize(class_name);

        if(klass == NULL) {
            *type_ = NULL;
            return FALSE;
        }
    }

    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.source = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = lv_table;
    info.parse_phase = 0;
    info.get_type_for_interpreter = TRUE;
    info.klass = klass;

    sCompileInfo cinfo;
    
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sByteCode code;
    sByteCode_init(&code);
    cinfo.code = &code;

    sConst constant;
    sConst_init(&constant);
    cinfo.constant = &constant;

    cinfo.lv_table = lv_table;
    cinfo.no_output = TRUE;
    cinfo.pinfo = &info;

    info.cinfo = &cinfo;

    while(*info.p) {
        info.exist_block_object_err = FALSE;

        unsigned int node = 0;
        (void)expression(&node, &info);

        *result_lv_table = info.lv_table;

        if(node != 0) {
            if(!compile(node, &cinfo)) {
                *type_ = cinfo.type;
                break;
            }

            *type_ = cinfo.type;

            if(*info.p == ';') {
                info.p++;
                skip_spaces_and_lf(&info);
            }
        }
    }

    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}


static void tyclover_get_type(char* source_value, char* fname_object_value, char* type_name, int type_name_size, char* class_name)
{
    sVarTable* lv_table = init_var_table();
    sVarTable* result_lv_table;
    sNodeType* type_ = NULL;

    (void)get_type(class_name, source_value, fname_object_value, lv_table, &type_, &result_lv_table);

    if(type_ == NULL || type_->mClass == NULL) {
        type_name[0] = '\0';
    }
    else {
        type_name[0] = '\0';
        create_type_name_from_node_type(type_name, type_name_size, type_);
    }
}

static void tyclover_print_local_variable(char* source_value, char* fname_object_value, char* class_name)
{
    sVarTable* lv_table = init_var_table();
    sVarTable* result_lv_table;
    sNodeType* type_ = NULL;

    (void)get_type(class_name, source_value, fname_object_value, lv_table, &type_, &result_lv_table);

    sVarTable* it = result_lv_table;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                printf("%s\n", p->mName);
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        it = it->mParent;
    }
}

int gARGC;
char** gARGV;
char* gVersion = "7.0.9";

char gScriptDirPath[PATH_MAX];
BOOL gRunningCompiler = FALSE;
BOOL gCompilingCore = FALSE;

static char gInitInputString[1024];
static int gInitInputCursorPosition;

int main(int argc, char** argv)
{
    init_vtable();
    init_node_types();
    init_node_block_types();
    clover2_init();
    parser_init();
    compiler_init(FALSE);

    sBuf buf;
    sBuf_init(&buf);

    char* class_name = NULL;

    BOOL get_class_name = FALSE;
    BOOL get_command_name = FALSE;
    BOOL get_local_variable = FALSE;

    int i;
    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "--class") == 0) {
            get_class_name = TRUE;
        }
        else if(strcmp(argv[i], "--command") == 0) {
            get_command_name = TRUE;
        }
        else if(strcmp(argv[i], "--lvar") == 0) {
            get_local_variable = TRUE;
        }
        else {
            class_name = argv[i];
        }
    }

    if(get_local_variable) {
        while(!feof(stdin)) {
            char buf2[BUFSIZ];

            int result = fread(buf2, 1, BUFSIZ, stdin);
            
            if(result < 0) {
                fprintf(stderr, "invalid stdin\n");
                exit(1);
            }

            sBuf_append(&buf, buf2, result);
        }

        tyclover_print_local_variable(buf.mBuf, "tyclover2", class_name);
    }
    else if(get_class_name) {
        sClassTable* p = gHeadClassTable;

        while(p) {
            sCLClass* klass = p->mItem;

            printf("%s\n", CLASS_NAME(klass));

            p = p->mNextClass;
        }
    }
    else if(get_command_name) {
        int i;
        for(i=0; i<gNumCommandNames; i++) {
            printf("%s\n", gCommandNames[i]);
        }
    }
    else {
        while(!feof(stdin)) {
            char buf2[BUFSIZ];

            int result = fread(buf2, 1, BUFSIZ, stdin);
            
            if(result < 0) {
                fprintf(stderr, "invalid stdin\n");
                exit(1);
            }

            sBuf_append(&buf, buf2, result);
        }

        char type_name[1024];
        tyclover_get_type(buf.mBuf, "tyclover2", type_name, 1024, class_name);

        printf("%s\n", type_name);
    }

    compiler_final();
    parser_final();
    clover2_final();
    final_vtable();
    free_node_types();
    free_node_block_types();

    exit(0);
}

