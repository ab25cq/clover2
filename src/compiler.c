#include "common.h"

static void clover_init()
{
    init_nodes();
    init_node_types();
    class_init();
    init_vtable();
}

static void clover_final()
{
    free_nodes();
    free_node_types();
    class_final();
    final_vtable();
}

static BOOL read_source(char* fname, sBuf* source)
{
    int f = open(fname, O_RDONLY);

    while(1) {
        char buf[BUFSIZ];
        int size = read(f, buf, BUFSIZ);

        if(size < 0) {
            fprintf(stderr, "unexpected error\n");
            close(f);
            return FALSE;
        }

        buf[size] = 0;
        sBuf_append_str(source, buf);

        if(size < BUFSIZ) {
            break;
        }
    }

    close(f);

    return TRUE;
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

    if(!compile_script(fname, source.mBuf)) {
        MFREE(source.mBuf);
        return FALSE;
    }

    MFREE(source.mBuf);

    return TRUE;
}

int main(int argc, char** argv)
{
    int i;
    for(i=1; i<argc; i++) {
        clover_init();
        if(!compiler(argv[i])) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            clover_final();
            return 1;
        }
        clover_final();
    }

    return 0;
}
