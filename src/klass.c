#include "common.h"

static void free_class(sCLClass* klass);
ALLOC sCLType* create_cl_type(sCLClass* klass, sCLClass* klass2);
void free_cl_type(sCLType* cl_type);

#define CLASS_NUM_MAX 512

sClassTable* gHeadClassTable = NULL;

static sClassTable gClassTable[CLASS_NUM_MAX];

unsigned int get_hash_key(char* name, unsigned int max)
{
    unsigned int result = 0;
    char* p = name;
    while(*p) {
        result += *p;
        p++;
    }

    return result % max;
}

static void remove_class(char* class_name)
{
    unsigned int hash_key = get_hash_key(class_name, CLASS_NUM_MAX);
    sClassTable* p = gClassTable + hash_key;

    while(1) {
        if(p->mName == NULL) {
            break;
        }
        else if(strcmp(p->mName, class_name) == 0) {
            /// remove from liked list ///
            sClassTable* p2 = gHeadClassTable;
            sClassTable* p2_before = p2;

            while(p2) {
                if(p2->mItem == p->mItem) {
                    if(p2_before == gHeadClassTable) {
                        gHeadClassTable = p2->mNextClass;
                    }
                    else {
                        p2_before->mNextClass = p2->mNextClass;
                    }
                    break;
                }

                p2_before = p2;
                p2 = p2->mNextClass;
            }

            /// remove found class ///
            MFREE(p->mName);
            free_class(p->mItem);

            p->mName = NULL;
            p->mItem = NULL;
            break;
        }
        else {
            p++;

            if(p == gClassTable + CLASS_NUM_MAX) {
                p = gClassTable;
            }
            else if(p == gClassTable + hash_key) {
                break;
            }
        }
    }
}

static BOOL put_class_to_table(char* class_name, sCLClass* klass)
{
    remove_class(class_name);

    unsigned int hash_key = get_hash_key(class_name, CLASS_NUM_MAX);
    sClassTable* p = gClassTable + hash_key;

    while(1) {
        if(p->mName == NULL) {
            p->mName = MSTRDUP(class_name);
            p->mItem = klass;

            p->mNextClass = gHeadClassTable;
            gHeadClassTable = p;
            break;
        }
        else {
            p++;

            if(p == gClassTable + CLASS_NUM_MAX) {
                p = gClassTable;
            }
            else if(p == gClassTable + hash_key) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

sCLClass* get_class(char* class_name)
{
    unsigned int hash_key = get_hash_key(class_name, CLASS_NUM_MAX);
    sClassTable* p = gClassTable + hash_key;

    while(1) {
        if(p->mName) {
            if(strcmp(p->mName, class_name) == 0) {
                return p->mItem;
            }
            else {
                p++;

                if(p == gClassTable + CLASS_NUM_MAX) {
                    p = gClassTable;
                }
                else if(p == gClassTable + hash_key) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return NULL;
}

static BOOL search_for_class_file_with_version(char* class_name, char* class_file_name, size_t class_file_name_size, int class_version)
{
    char* cwd = getenv("PWD");

    /// current working directory ///
    if(cwd) {
        if(class_version == 1) {
            snprintf(class_file_name, class_file_name_size, "%s/%s.clcl", cwd, class_name);
        }
        else {
            snprintf(class_file_name, class_file_name_size, "%s/%s@%d.clcl", cwd, class_name, class_version);
        }

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    char* home = getenv("HOME");

    /// .clover directory ///
    if(home) {
        if(class_version == 1) {
            snprintf(class_file_name, class_file_name_size, "%s/%s.clcl", home, class_name);
        }
        else {
            snprintf(class_file_name, class_file_name_size, "%s/%s@%d.clcl", home, class_name, class_version);
        }

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    /// default search path ///
    if(class_version == 1) {
        snprintf(class_file_name, class_file_name_size, "%s/%s.clo", DATAROOTDIR, class_name);
    }
    else {
        snprintf(class_file_name, class_file_name_size, "%s/%s@%d.clo", DATAROOTDIR, class_name, class_version);
    }

    if(access(class_file_name, F_OK) == 0) {
        return TRUE;
    }

    return FALSE;
}

static BOOL search_for_class_file(char* class_name, char* class_file_name, size_t class_file_name_size)
{
    int i;
    for(i=CLASS_VERSION_MAX-1; i>=1; i--) {
        if(search_for_class_file_with_version(class_name, class_file_name, class_file_name_size, i)) {
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL read_from_file(int fd, void* buf, size_t size)
{
    size_t size2;

    size2 = read(fd, buf, size);

    if(size2 < size) {
        return FALSE;
    }

    return TRUE;
}

static BOOL read_char_from_file(int fd, char* c)
{
    return read_from_file(fd, c, sizeof(char));
}

static BOOL read_int_from_file(int fd, int* n)
{
    return read_from_file(fd, n, sizeof(int));
}

static BOOL read_long_from_file(int fd, long* n)
{
    return read_from_file(fd, n, sizeof(long long));
}

static BOOL read_const_from_file(int fd, sConst* constant)
{
    int len;
    if(!read_int_from_file(fd, &len)) {
        return FALSE;
    }

    sConst_init_with_size(constant, len);
    constant->mLen = len;

    if(!read_from_file(fd, constant->mConst, len)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL read_cl_type_from_file(int fd, sCLType** cl_type)
{
    *cl_type = MCALLOC(1, sizeof(sCLType));

    int n;
    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }

    (*cl_type)->mClassNameOffset = n;

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }

    (*cl_type)->mNumGenericsTypes = n;

    int i;
    for(i=0; i<(*cl_type)->mNumGenericsTypes; i++) {
        if(!read_cl_type_from_file(fd, &(*cl_type)->mGenericsTypes[i])) {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL read_code_from_file(int fd, sByteCode* code)
{
    int n;

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }

    sByteCode_init_with_size(code, n);
    code->mLen = n;

    if(!read_from_file(fd, code->mCodes, n)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL read_methods_from_file(int fd, sCLMethod** methods, int* num_methods, int* size_methods, sCLClass* klass)
{
    int n;
    long l;

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }
    *size_methods = *num_methods = n;

    *methods = MCALLOC(1, sizeof(sCLMethod)*(*num_methods));

    int i;
    for(i=0; i<*num_methods; i++) {
        sCLMethod* method = (*methods) + i;

        if(!read_long_from_file(fd, &l))  {
            return FALSE;
        }

        method->mFlags = l;

        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }
        method->mNameOffset = n;

        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }
        method->mPathOffset = n;

        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }
        method->mNumParams = n;

        int j;
        for(j=0; j<method->mNumParams; j++) {
            sCLParam* param = method->mParams + j;

            if(!read_int_from_file(fd, &n)) {
                return FALSE;
            }

            param->mNameOffset = n;

            if(!read_cl_type_from_file(fd, &param->mType)) {
                return FALSE;
            }
        }

        if(!read_cl_type_from_file(fd, &method->mResultType)) {
            return FALSE;
        }

        if(method->mFlags & METHOD_FLAGS_NATIVE) {
            char* path = CONS_str(&klass->mConst, method->mPathOffset);

            fNativeMethod native_method = get_native_method(path);

            if(native_method == NULL) {
                fprintf(stderr, "%s is not found\n", path);
                return FALSE;
            }

            method->uCode.mNativeMethod = native_method;

            method->mVarNum = 0;
        }
        else {
            if(!read_code_from_file(fd, &method->uCode.mByteCodes)) {
                return FALSE;
            }

            if(!read_int_from_file(fd, &n)) {
                return FALSE;
            }

            method->mVarNum = n;
        }
    }

    return TRUE;
}

static BOOL read_fields_from_file(int fd, sCLField** fields, int* num_fields, int* size_fields, sCLClass* klass)
{
    int n;
    long l;

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }
    *size_fields = *num_fields = n;

    *fields = MCALLOC(1, sizeof(sCLField)*(*num_fields));

    int i;
    for(i=0; i<*num_fields; i++) {
        sCLField* field = (*fields) + i;

        if(!read_long_from_file(fd, &l))  {
            return FALSE;
        }

        field->mFlags = l;

        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }
        field->mNameOffset = n;

        if(!read_cl_type_from_file(fd, &field->mResultType)) {
            return FALSE;
        }
    }

    return TRUE;
}

static sCLClass* read_class_from_file(int fd)
{
    sCLClass* klass = MCALLOC(1, sizeof(sCLClass));

    int n;
    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mVersion = n;

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mGenericsParamClassNum = n;

    long l;
    if(!read_long_from_file(fd, &l)) {
        MFREE(klass);
        return NULL;
    }
    klass->mFlags = l;
    klass->mFlags &= ~CLASS_FLAGS_MODIFIED;

    if(!read_const_from_file(fd, &klass->mConst)) {
        MFREE(klass);
        return NULL;
    }

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mClassNameOffset = n;

    if(!read_methods_from_file(fd, &klass->mMethods, &klass->mNumMethods, &klass->mSizeMethods, klass)) {
        MFREE(klass);
        return NULL;
    }

    if(!read_fields_from_file(fd, &klass->mFields, &klass->mNumFields, &klass->mSizeFields, klass)) {
        MFREE(klass);
        return NULL;
    }

    if(!read_fields_from_file(fd, &klass->mClassFields, &klass->mNumClassFields, &klass->mSizeClassFields, klass)) {
        MFREE(klass);
        return NULL;
    }

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mInitializeMethodIndex = n;

    klass->mFreeFun = NULL;
    klass->mMarkFun = object_mark_fun;

    return klass;
}

static sCLClass* load_class_from_class_file(char* class_name, char* class_file_name)
{
    /// check the existance of the load class ///
    int fd = open(class_file_name, O_RDONLY);

    if(fd < 0) {
        return NULL;
    }

    /// check magic number. Is this Clover object file? ///
    char c;

    if(!read_from_file(fd, &c, 1) || c != 11) { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 12) { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 34) { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 55) { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 'C') { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 'L') { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 'O') { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 'V') { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 'E') { close(fd); return NULL; }
    if(!read_from_file(fd, &c, 1) || c != 'R') { close(fd); return NULL; }

    sCLClass* klass = read_class_from_file(fd);
    close(fd);

    if(klass == NULL) {
        fprintf(stderr, "Clover2 can't load class %s because of class file\n", class_name);
        return NULL;
    }

    put_class_to_table(class_name, klass);

    return klass;
}

sCLClass* load_class_with_version(char* class_name, int class_version)
{
    sCLClass* klass = get_class(class_name);
    if(klass != NULL) {
        remove_class(class_name);
    }

    char class_file_name[CLASS_NAME_MAX+1];
    if(!search_for_class_file_with_version(class_name, class_file_name, CLASS_NAME_MAX, class_version))
    {
        return NULL;
    }

    return load_class_from_class_file(class_name, class_file_name);
}

sCLClass* get_class_with_load(char* class_name)
{
    sCLClass* result = get_class(class_name);
    
    if(result == NULL) {
        result = load_class(class_name);
    }

    return result;
}

sCLClass* load_class(char* class_name)
{
    sCLClass* klass = get_class(class_name);
    if(klass != NULL) {
        remove_class(class_name);
    }

    char class_file_name[PATH_MAX+1];
    if(!search_for_class_file(class_name, class_file_name, PATH_MAX)) {
        return NULL;
    }

    return load_class_from_class_file(class_name, class_file_name);
}

sCLClass* alloc_class(char* class_name, BOOL primitive_, BOOL final_, int generics_param_class_num)
{
    sCLClass* klass = MCALLOC(1, sizeof(sCLClass));

    klass->mFlags |= (primitive_ ? CLASS_FLAGS_PRIMITIVE:0) | (final_ ? CLASS_FLAGS_FINAL:0);
    klass->mVersion = 1;
    klass->mGenericsParamClassNum = generics_param_class_num;

    sConst_init(&klass->mConst);

    klass->mClassNameOffset = append_str_to_constant_pool(&klass->mConst, class_name, FALSE);

    klass->mMethods = MCALLOC(1, sizeof(sCLMethod)*4);
    klass->mSizeMethods = 4;
    klass->mNumMethods = 0;

    klass->mFields = MCALLOC(1, sizeof(sCLField)*4);
    klass->mSizeFields = 4;
    klass->mNumFields = 0;

    klass->mClassFields = MCALLOC(1, sizeof(sCLField)*4);
    klass->mSizeClassFields = 4;
    klass->mNumClassFields = 0;

    klass->mFreeFun = NULL;
    klass->mMarkFun = object_mark_fun;

    put_class_to_table(class_name, klass);

    return klass;
}

static void free_class(sCLClass* klass)
{
    sConst_free(&klass->mConst);
    int i;
    for(i=0; i<klass->mNumMethods; i++) {
        sCLMethod* method = klass->mMethods + i;

        int j;
        for(j=0; j<method->mNumParams; j++) {
            free_cl_type(method->mParams[j].mType);
        }

        free_cl_type(method->mResultType);

        if(!(method->mFlags & METHOD_FLAGS_NATIVE)) {
            sByteCode_free(&method->uCode.mByteCodes);
        }
    }
    MFREE(klass->mMethods);
    for(i=0; i<klass->mNumFields; i++) {
        sCLField* field = klass->mFields + i;

        free_cl_type(field->mResultType);
    }
    MFREE(klass->mFields);
    for(i=0; i<klass->mNumClassFields; i++) {
        sCLField* field = klass->mClassFields + i;

        free_cl_type(field->mResultType);
    }
    MFREE(klass->mClassFields);

    MFREE(klass);
}

ALLOC sCLType* create_cl_type(sCLClass* klass, sCLClass* klass2)
{
    sCLType* cl_type = MCALLOC(1, sizeof(sCLType));

    cl_type->mClassNameOffset = append_str_to_constant_pool(&klass2->mConst, CLASS_NAME(klass), FALSE);

    return cl_type;
}

void free_cl_type(sCLType* cl_type)
{
    int i;
    for(i=0; i<cl_type->mNumGenericsTypes; i++) {
        free_cl_type(cl_type->mGenericsTypes[i]);
    }
    MFREE(cl_type);
}

static void load_fundamental_classes()
{
    (void)load_class("System");
    (void)load_class("Clover");
}

void mark_all_class_fields(unsigned char* mark_flg)
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        sCLClass* klass = p->mItem;

        int i;
        for(i=0; i<klass->mNumClassFields; i++) {
            sCLField* field = klass->mClassFields + i;

            mark_object(field->mValue.mObjectValue, mark_flg);
        }

        p = p->mNextClass;
    }
}

void class_init()
{
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);

    alloc_class("int", TRUE, TRUE, -1);
    alloc_class("uint", TRUE, TRUE, -1);
    alloc_class("byte", TRUE, TRUE, -1);
    alloc_class("ubyte", TRUE, TRUE, -1);
    alloc_class("short", TRUE, TRUE, -1);
    alloc_class("ushort", TRUE, TRUE, -1);
    alloc_class("long", TRUE, TRUE, -1);
    alloc_class("ulong", TRUE, TRUE, -1);
    alloc_class("float", TRUE, TRUE, -1);
    alloc_class("double", TRUE, TRUE, -1);
    alloc_class("bool", TRUE, TRUE, -1);
    alloc_class("Null", TRUE, TRUE, -1);
    alloc_class("pointer", TRUE, TRUE, -1);

    alloc_class("GenericsParametorClass1", TRUE, TRUE, 1);
    alloc_class("GenericsParametorClass2", TRUE, TRUE, 2);
    alloc_class("GenericsParametorClass3", TRUE, TRUE, 3);
    alloc_class("GenericsParametorClass4", TRUE, TRUE, 4);
    alloc_class("GenericsParametorClass5", TRUE, TRUE, 5);
    alloc_class("GenericsParametorClass6", TRUE, TRUE, 6);
    alloc_class("GenericsParametorClass7", TRUE, TRUE, 7);
    alloc_class("GenericsParametorClass8", TRUE, TRUE, 8);
    alloc_class("GenericsParametorClass9", TRUE, TRUE, 9);
    alloc_class("GenericsParametorClass10", TRUE, TRUE, 10);
    alloc_class("GenericsParametorClass11", TRUE, TRUE, 11);
    alloc_class("GenericsParametorClass12", TRUE, TRUE, 12);
    alloc_class("GenericsParametorClass13", TRUE, TRUE, 13);
    alloc_class("GenericsParametorClass14", TRUE, TRUE, 14);
    alloc_class("GenericsParametorClass15", TRUE, TRUE, 15);
    alloc_class("GenericsParametorClass16", TRUE, TRUE, 16);
    alloc_class("GenericsParametorClass17", TRUE, TRUE, 17);
    alloc_class("GenericsParametorClass18", TRUE, TRUE, 18);
    alloc_class("GenericsParametorClass19", TRUE, TRUE, 19);
    alloc_class("GenericsParametorClass20", TRUE, TRUE, 20);
    alloc_class("GenericsParametorClass21", TRUE, TRUE, 21);
    alloc_class("GenericsParametorClass22", TRUE, TRUE, 22);
    alloc_class("GenericsParametorClass23", TRUE, TRUE, 23);
    alloc_class("GenericsParametorClass24", TRUE, TRUE, 24);
    alloc_class("GenericsParametorClass25", TRUE, TRUE, 25);
    alloc_class("GenericsParametorClass26", TRUE, TRUE, 26);
    alloc_class("GenericsParametorClass27", TRUE, TRUE, 27);
    alloc_class("GenericsParametorClass28", TRUE, TRUE, 28);
    alloc_class("GenericsParametorClass29", TRUE, TRUE, 29);
    alloc_class("GenericsParametorClass30", TRUE, TRUE, 30);
    alloc_class("GenericsParametorClass31", TRUE, TRUE, 31);
    alloc_class("GenericsParametorClass32", TRUE, TRUE, 32);

    load_fundamental_classes();
}

void class_final()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        free_class(p->mItem);
        MFREE(p->mName);
        p = p->mNextClass;
    }

    gHeadClassTable = NULL;
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);
}
