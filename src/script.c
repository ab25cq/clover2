#include "common.h"

sCLBlockObject* gBlockObjects;
int gNumBlockObjects;
int gSizeBlockObjects;

void script_init()
{
    gBlockObjects = MCALLOC(1, sizeof(sCLBlockObject)*4);
    gSizeBlockObjects = 4;
    gNumBlockObjects = 0;
}

void script_final()
{
/*
    int i;
    for(i=0; i<gNumBlockObjects; i++) {
        sCLBlockObject* block_object = gBlockObjects + i;

        sByteCode_free(&block_object->mByteCodes);
        sConst_free(&block_object->mConst);
    }
*/
    MFREE(gBlockObjects);
}

int add_block_object_to_script(sByteCode codes, sConst constant, int var_num, int num_params, BOOL lambda)
{
    if(gNumBlockObjects == gSizeBlockObjects) {
        int new_size = gSizeBlockObjects * 2;
        gBlockObjects = MREALLOC(gBlockObjects, sizeof(sCLMethod)*new_size);
        memset(gBlockObjects + gSizeBlockObjects, 0, sizeof(sCLMethod)*(new_size - gSizeBlockObjects));
        gSizeBlockObjects = new_size;
    }

    int num_block_objects = gNumBlockObjects;

    sCLBlockObject* block_object = gBlockObjects + gNumBlockObjects;

    block_object->mByteCodes = codes;
    block_object->mConst = constant;
    block_object->mVarNum = var_num;
    block_object->mNumParams = num_params;
    block_object->mLambda = lambda;

    gNumBlockObjects++;

    
    return num_block_objects;
}

void add_block_object_to_script2(sCLBlockObject* block_object)
{
    if(gNumBlockObjects == gSizeBlockObjects) {
        int new_size = gSizeBlockObjects * 2;
        gBlockObjects = MREALLOC(gBlockObjects, sizeof(sCLMethod)*new_size);
        memset(gBlockObjects + gSizeBlockObjects, 0, sizeof(sCLMethod)*(new_size - gSizeBlockObjects));
        gSizeBlockObjects = new_size;
    }

    sCLBlockObject* block_object2 = gBlockObjects + gNumBlockObjects;

    *block_object2 = *block_object;

    gNumBlockObjects++;
}

BOOL read_source(char* fname, sBuf* source)
{
    int f = open(fname, O_RDONLY);

    if(f < 0) {
        fprintf(stderr, "%s doesn't exist(2)\n", fname);
        return FALSE;
    }

    while(1) {
        char buf[BUFSIZ+1];
        int size = read(f, buf, BUFSIZ);

        if(size == 0) {
            break;
        }
        else if(size < 0) {
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

BOOL eval_file(char* fname, int stack_size)
{
    int fd = open(fname, O_RDONLY);

    if(fd < 0) {
        fprintf(stderr, "%s doesn't exist(1)\n", fname);
        return FALSE;
    }

    /// magic number ///
    char c;
    if(!read_from_file(fd, &c, 1) || c != 10) { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 12) { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 34) { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 55) { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 'C') { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 'L') { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 'O') { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 'V') { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 'E') { close(fd); return FALSE; }
    if(!read_from_file(fd, &c, 1) || c != 'R') { close(fd); return FALSE; }

    int var_num;
    if(!read_int_from_file(fd, &var_num)) {
        close(fd);
        fprintf(stderr, "Clover2 can't read variable number\n");
        return FALSE;
    }

    sByteCode code;
    if(!read_code_from_file(fd, &code))
    {
        close(fd);
        fprintf(stderr, "Clover2 can't read variable number\n");
        return FALSE;
    }

    sConst constant;
    if(!read_const_from_file(fd, &constant))
    {
        close(fd);
        fprintf(stderr, "Clover2 can't read variable number\n");
        return FALSE;
    }

    int n;
    if(!read_int_from_file(fd, &n)) {
        close(fd);
        fprintf(stderr, "Clover2 can't read variable number\n");
        return FALSE;
    }

    int i;
    for(i=0; i<n; i++) {
        sCLBlockObject block_object;

        if(!read_block_from_file(fd, &block_object)) {
            close(fd);
            fprintf(stderr, "Clover2 can't read variable number\n");
            return FALSE;
        }

        add_block_object_to_script2(&block_object);
    }

    CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);

    sVMInfo info;
    memset(&info, 0, sizeof(info));

    info.stack = stack;

    create_global_stack_and_append_it_to_stack_list(&info);

    info.running_class_name = MSTRDUP("none");
    info.running_method_name = MSTRDUP("eval_file");

    vm_mutex_on();

    if(!vm(&code, &constant, stack, var_num, NULL, &info)) {
        MFREE(info.running_class_name);
        MFREE(info.running_method_name);
        free_global_stack(&info);
        close(fd);
        MFREE(stack);
        sByteCode_free(&code);
        sConst_free(&constant);
        vm_mutex_off();
        return FALSE;
    }

    MFREE(info.running_class_name);
    MFREE(info.running_method_name);

    free_global_stack(&info);

    vm_mutex_off(); // see OP_RETURN

    close(fd);
    MFREE(stack);
    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}
