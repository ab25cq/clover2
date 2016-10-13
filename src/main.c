#include "common.h"

static void clover2_init()
{
    native_method_init();
    class_init();
    (void)class_init_on_runtime();
    heap_init(128, 128);
    stack_init();
}

static void clover2_final()
{
    native_method_final();
    stack_final();
    heap_final();
    class_final_on_runtime();
}

static BOOL eval_file(char* fname, int stack_size)
{
    FILE* f = fopen(fname, "r");

    if(f == NULL) {
        fprintf(stderr, "%s doesn't exist\n", fname);
        return FALSE;
    }

    /// magic number ///
    char buf[BUFSIZ];
    if(fread(buf, 1, 18, f) < 18) {
        fclose(f);
        fprintf(stderr, "%s is not clover script file\n", fname);
        return FALSE;
    }
    buf[18] = 0;
    if(strcmp(buf, "CLOVER SCRIPT FILE") != 0) {
        fclose(f);
        fprintf(stderr, "%s is not clover script file\n", fname);
        return FALSE;
    }

    int var_num;
    if(fread(&var_num, sizeof(int), 1, f) < 1) {
        fclose(f);
        fprintf(stderr, "Clover2 can't read variable number\n");
        return FALSE;
    }

    int code_len = 0;
    if(fread(&code_len, sizeof(int), 1, f) < 1) {
        fclose(f);
        fprintf(stderr, "Clover2 can't read byte code size\n");
        return FALSE;
    }

    char* code_contents = MMALLOC(code_len);
    if(fread(code_contents, 1, code_len, f) < code_len) {
        fclose(f);
        MFREE(code_contents);
        fprintf(stderr, "Clover2 can't read byte code\n");
        return FALSE;
    }

    int code_len2 = 0;
    if(fread(&code_len2, sizeof(int), 1, f) < 1) {
        fclose(f);
        MFREE(code_contents);
        fprintf(stderr, "Clover2 can't read constant size\n");
        return FALSE;
    }

    char* code_contents2 = MMALLOC(code_len2);
    if(fread(code_contents2, 1, code_len2, f) < code_len2) {
        fclose(f);
        MFREE(code_contents);
        MFREE(code_contents2);
        fprintf(stderr, "Clover2 can't read byte code\n");
        return FALSE;
    }

    sByteCode code;
    sByteCode_init(&code);
    append_value_to_code(&code, code_contents, code_len, FALSE);

    sConst constant;
    sConst_init(&constant);
    sConst_append(&constant, code_contents2, code_len2, FALSE);

    CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);

    sVMInfo info;
    memset(&info, 0, sizeof(sVMInfo));

    if(!vm(&code, &constant, stack, var_num, NULL, &info)) {
        show_exception_message(info.exception_message);
        fclose(f);
        MFREE(stack);
        MFREE(code_contents);
        MFREE(code_contents2);
        sByteCode_free(&code);
        sConst_free(&constant);
        return FALSE;
    }

    fclose(f);
    MFREE(code_contents);
    MFREE(code_contents2);
    MFREE(stack);
    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}

int main(int argc, char** argv)
{
    int i;

    CHECKML_BEGIN;
    setlocale(LC_ALL, "");

    for(i=1; i<argc; i++) {
        clover2_init();
        if(!eval_file(argv[i], 512)) {
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

