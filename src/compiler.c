#include "common.h"

static void compiler_init()
{
    init_nodes();
    init_node_types();
    class_init();
    init_vtable();
}

static void compiler_final()
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

static BOOL delete_comment(sBuf* source, sBuf* source2)
{
    char* p;
    BOOL in_string;

    p = source->mBuf;

    in_string = FALSE;

    while(*p) {
        if(*p == '"') {
            in_string = !in_string;
            sBuf_append_char(source2, *p);
            p++;
        }
        else if(!in_string && *p =='#')
        {
            p++;

            while(1) {
                if(*p == 0) {
                    break;
                }
                else if(*p == '\n') {
                    //p++;      // no delete line field for error message
                    break;
                }
                else {
                    p++;
                }
            }
        }
        else if(!in_string && *p == '/' && *(p+1) == '*') {
            int nest;

            p+=2;
            nest = 0;
            while(1) {
                if(*p == '"') {
                    p++;
                    in_string = !in_string;
                }
                else if(*p == 0) {
                    fprintf(stderr, "there is not a comment end until source end\n");
                    return FALSE;
                }
                else if(!in_string && *p == '/' && *(p+1) == '*') {
                    p+=2;
                    nest++;
                }
                else if(!in_string && *p == '*' && *(p+1) == '/') {
                    p+=2;
                    if(nest == 0) {
                        break;
                    }

                    nest--;
                }
                else if(*p == '\n') {
                    sBuf_append_char(source2, *p);   // no delete line field for error message
                    p++;
                }
                else {
                    p++;
                }
            }
        }
        else {
            sBuf_append_char(source2, *p);
            p++;
        }
    }

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

    MFREE(source.mBuf);
    MFREE(source2.mBuf);

    return TRUE;
}

int main(int argc, char** argv)
{
    int i;

    for(i=1; i<argc; i++) {
        compiler_init();
        if(strcmp(argv[i], "-class") == 0) {
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
