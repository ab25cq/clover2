#include "common.h"

static void compiler_init(BOOL no_load_fudamental_classes)
{
    init_nodes();
    init_node_types();
    init_node_block_types();
    class_init();
    if(!no_load_fudamental_classes) class_init_on_compile_time();
    init_vtable();
    module_init();
}

static void compiler_final()
{
    module_final();
    free_nodes();
    free_node_block_types();
    free_node_types();
    class_final();
    final_vtable();
}

static BOOL compiler(char* fname)
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

    if(!compile_script(fname, source2.mBuf)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    MFREE(source.mBuf);
    MFREE(source2.mBuf);

    return TRUE;
}


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

int main(int argc, char** argv)
{
    int i;
    
    setlocale(LC_ALL, "");

    BOOL no_load_fudamental_classes = FALSE;
    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "-no-load-fundamental-classes") == 0) {
            no_load_fudamental_classes = TRUE;
        }
    }

    for(i=1; i<argc; i++) {
        compiler_init(no_load_fudamental_classes);
        if(strcmp(argv[i], "-no-load-fundamental-classes") == 0) {
        }
        else if(strcmp(argv[i], "-class") == 0) {
            if(i+1 < argc) {
                if(!class_compiler(argv[i+1])) {
                    fprintf(stderr, "cclover2 can't compile %s\n", argv[i+1]);
                    compiler_final();
                    return 1;
                }
                i++;
            }
        }
        else if(!compiler(argv[i])) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            compiler_final();
            return 1;
        }
        compiler_final();
    }

    return 0;
}
