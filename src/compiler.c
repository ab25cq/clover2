#include "common.h"

static void compiler_init(BOOL no_load_fudamental_classes)
{
    init_nodes();
    init_node_types();
    init_node_block_types();
    class_init();

    if(!no_load_fudamental_classes) {
        class_init_on_runtime();
        class_init_on_runtime_for_js();
    }

    init_vtable();
    module_init();
    parser_init();
}

static void clover2_init()
{
    class_system_init();
    thread_init();
#ifdef ENABLE_JIT
    jit_init_on_runtime();
#endif
    native_method_init();
    heap_init(HEAP_INIT_SIZE, HEAP_HANDLE_INIT_SIZE);
    stack_init();
}

static void clover2_final()
{
    thread_final();
    class_final_on_runtime();
    heap_final();
    stack_final();
    native_method_final();
#ifdef ENABLE_JIT
    jit_final_on_runtime();
#endif
}

static void compiler_final()
{
    parser_final();
    module_final();
    free_nodes();
    free_node_block_types();
    free_node_types();
    class_final();
    final_vtable();
//    dependency_final();
}

static BOOL compiler(char* fname, BOOL js)
{
    if(access(fname, F_OK) != 0) {
        fprintf(stderr, "%s doesn't exist\n", fname);
        return FALSE;
    }

    sBuf source;
    sBuf_init(&source);
    if(!read_source(fname, &source)) {
        MFREE(source.mBuf);
        return FALSE;
    }

    sBuf source2;
    sBuf_init(&source2);

    if(!delete_comment(&source, &source2)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    if(!compile_script(fname, source2.mBuf, js)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    MFREE(source.mBuf);
    MFREE(source2.mBuf);

    return TRUE;
}

#ifdef ENABLE_JIT
static BOOL jit_class_compiler(char* class_name) 
{
    sCLClass* klass = get_class_with_load(class_name, FALSE);

    if(!jit_compile_class(klass)) {
        fprintf(stderr, "faield in jit compile\n");
        return FALSE;
    }

    return TRUE;
}
#endif

static BOOL class_compiler(char* fname)
{
    if(access(fname, F_OK) != 0) {
        fprintf(stderr, "%s doesn't exist\n", fname);
        return FALSE;
    }

    sBuf source;
    sBuf_init(&source);
    if(!read_source(fname, &source)) {
        MFREE(source.mBuf);
        return FALSE;
    }

    sBuf source2;
    sBuf_init(&source2);

    if(!delete_comment(&source, &source2)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    if(!compile_class_source(fname, source2.mBuf)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    if(!write_all_modified_classes()) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    write_all_modified_modules();

    MFREE(source.mBuf);
    MFREE(source2.mBuf);

    return TRUE;
}

int gARGC;
char** gARGV;
char* gVersion = "10.2.8";

char gScriptDirPath[PATH_MAX];
BOOL gRunningCompiler = TRUE;
BOOL gCompilingCore = FALSE;

int main(int argc, char** argv)
{
    int i;

    gARGC = argc;
    gARGV = argv;

    xstrncpy(gScriptDirPath, "", PATH_MAX);

    setlocale(LC_ALL, "");

    BOOL no_load_fudamental_classes = FALSE;
    char sname[PATH_MAX];
    xstrncpy(sname, "", PATH_MAX);
    BOOL jit_compile = FALSE;

    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "-core") == 0) {
            no_load_fudamental_classes = TRUE;
            gCompilingCore = TRUE;
        }
        else if(strcmp(argv[i], "-jit") == 0) {
            jit_compile = TRUE;
        }
        else if(strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-version") == 0 || strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-V") == 0)
        {
            printf("clover2 version %s\n", gVersion);
            exit(0);
        }
        else {
            xstrncpy(sname, argv[i], PATH_MAX);
        }
    }

    char* p = sname + strlen(sname);

    while(p >= sname) {
        if(*p == '.') {
            break;
        }
        else {
            p--;
        }
    }

    if(p < sname) {
        p = NULL;
    }

    char* ext_sname = p;

    clover2_init();
    compiler_init(no_load_fudamental_classes);

    if(ext_sname && (strcmp(ext_sname, ".clcl") == 0 || strcmp(ext_sname, ".jsclcl") == 0)) {
        if(!class_compiler(sname)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover2_final();
            compiler_final();
            return 1;
        }
    }
    else if(ext_sname && strcmp(ext_sname, ".cl") == 0) 
    {
        if(!compiler(sname, FALSE)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover2_final();
            compiler_final();
            return 1;
        }
    }
    else if(ext_sname && strcmp(ext_sname, ".ojsclcl") == 0) 
    {
        if(!js_class_compiler(sname)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover2_final();
            compiler_final();
            return 1;
        }
    }
    else if(ext_sname && strcmp(ext_sname, ".jscl") == 0) 
    {
        if(!compiler(sname, TRUE)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover2_final();
            compiler_final();
            return 1;
        }
    }
    else if(ext_sname && strcmp(ext_sname, ".ojscl") == 0) 
    {
        if(!js_compiler(sname)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover2_final();
            compiler_final();
            return 1;
        }
    }
#ifdef ENABLE_JIT
    else if(jit_compile) {
        char* p = sname + strlen(sname);

        while(p >= sname) {
            if(*p == '.') {
                break;
            }
            else {
                p--;
            }
        }

        if(p != sname) {
            *p = '\0';
        }

        if(!jit_class_compiler(sname)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover2_final();
            compiler_final();
            return 1;
        }
    }
#endif
    else {
        if(!compiler(sname, FALSE)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover2_final();
            compiler_final();
            return 1;
        }
    }

    clover2_final();
    compiler_final();

    return 0;
}
