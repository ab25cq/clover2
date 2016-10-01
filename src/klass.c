#include "common.h"

static void free_class(sCLClass* klass);
ALLOC sCLType* create_cl_type(sCLClass* klass, sCLClass* klass2);
void free_cl_type(sCLType* cl_type);

sClassTable* gHeadClassTable = NULL;

#define CLASS_NUM_MAX 512

static sClassTable gClassTable[CLASS_NUM_MAX];

fGetNativeMethod gGetNativeMethod = NULL;

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

/*
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
*/

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

static BOOL read_cl_type_from_file(int fd, sCLType** cl_type);

static BOOL read_cl_block_type_from_file(int fd, sCLBlockType** cl_block_type)
{
    int num_params;
    if(!read_int_from_file(fd, &num_params)) {
        return FALSE;
    }

    (*cl_block_type)->mNumParams = num_params;

    int i;
    for(i=0; i<num_params; i++) {
        if(!read_cl_type_from_file(fd, &(*cl_block_type)->mParams[i])) {
            return FALSE;
        }
    }

    if(!read_cl_type_from_file(fd, &(*cl_block_type)->mResultType)) {
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

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }

    (*cl_type)->mArray = n;

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }

    if(n) {
        (*cl_type)->mBlockType = MCALLOC(1, sizeof(sCLBlockType));
        if(!read_cl_block_type_from_file(fd, &(*cl_type)->mBlockType)) {
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

        method->mMethodNameAndParamsOffset = n;

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

            if(gGetNativeMethod) { // if running Virtual Matchine,  gGetNativeMethod is not NULL
                fNativeMethod native_method = gGetNativeMethod(path);

                if(native_method == NULL) {
                    fprintf(stderr, "%s is not found\n", path);
                    return FALSE;
                }

                method->uCode.mNativeMethod = native_method;
            }

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
    klass->mNumGenerics = n;

    int i;
    for(i=0; i<klass->mNumGenerics; i++) {
        if(!read_int_from_file(fd, &n)) {
            MFREE(klass);
            return NULL;
        }

        klass->mGenericsParamTypeOffsets[i] = n;
    }

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
    klass->mClassInitializeMethodIndex = n;

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mClassFinalizeMethodIndex = n;

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mFinalizeMethodIndex = n;

    return klass;
}

static BOOL create_virtual_method_table(sCLClass* klass)
{
    int i;
    for(i=0; i<klass->mNumMethods; i++) {
        sCLMethod* method = klass->mMethods + i;

        char* method_name_and_params = CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset);

        /// insert method to vritual method table ///
        unsigned int hash_key = get_hash_key(method_name_and_params, METHOD_NUM_MAX);

        sCLMethod** it = klass->mVirtualMethodTable + hash_key;

        while(1) {
            if(*it == NULL) {
                *it = method;
                break;
            }
            else {
                it++;

                if(it == klass->mVirtualMethodTable + METHOD_NUM_MAX) {
                    it = klass->mVirtualMethodTable;
                }
                else if(it == klass->mVirtualMethodTable + hash_key) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

sCLMethod* search_for_method_from_virtual_method_table(sCLClass* klass, char* method_name_and_params)
{
    unsigned int hash_key = get_hash_key(method_name_and_params, METHOD_NUM_MAX);

    sCLMethod** it = klass->mVirtualMethodTable + hash_key;

    while(1) {
        if(*it == NULL) {
            return NULL;
        }
        else {
            sCLMethod* method = *it;

            char* method_name_and_params2 = CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset);

            if(strcmp(method_name_and_params, method_name_and_params2) == 0) {
                return method;
            }
            else {
                it++;

                if(it == klass->mVirtualMethodTable + METHOD_NUM_MAX) {
                    it = klass->mVirtualMethodTable;
                }
                else if(it == klass->mVirtualMethodTable + hash_key) {
                    return NULL;
                }
            }
        }
    }

    return NULL;
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

    memset(klass->mVirtualMethodTable, 0, sizeof(sCLMethod*)*METHOD_NUM_MAX);

    if(!create_virtual_method_table(klass)) {
        free_class(klass);
        return NULL;
    }

    put_class_to_table(class_name, klass);

    klass->mBoxingClass = NULL;
    klass->mUnboxingClass = NULL;

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

sCLClass* alloc_class(char* class_name, BOOL primitive_, int generics_param_class_num, int generics_number, sCLClass** type_of_generics_params, BOOL interface)
{
    sCLClass* klass = MCALLOC(1, sizeof(sCLClass));

    klass->mFlags |= (primitive_ ? CLASS_FLAGS_PRIMITIVE:0) | (interface ? CLASS_FLAGS_INTERFACE:0);
    klass->mVersion = 1;
    klass->mGenericsParamClassNum = generics_param_class_num;

    klass->mNumGenerics = generics_number;

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

    klass->mClassInitializeMethodIndex = -1;
    klass->mClassFinalizeMethodIndex = -1;
    klass->mFinalizeMethodIndex = -1;

    klass->mNumMethodsOnLoadTime = 0;
    klass->mMethodIndexOnCompileTime = 0;

    int i;
    for(i=0; i<generics_number; i++) {
        if(type_of_generics_params[i]) {
            klass->mGenericsParamTypeOffsets[i] = append_str_to_constant_pool(&klass->mConst, CLASS_NAME(type_of_generics_params[i]), FALSE);
        }
        else {
            klass->mGenericsParamTypeOffsets[i] = 0;
        }
    }

    put_class_to_table(class_name, klass);

    klass->mBoxingClass = NULL;
    klass->mUnboxingClass = NULL;

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

        if(!(method->mFlags & METHOD_FLAGS_NATIVE) && !(klass->mFlags & CLASS_FLAGS_INTERFACE) && method->uCode.mByteCodes.mCodes) {
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

static void free_cl_block_type(sCLBlockType* block_type)
{
    int i;
    for(i=0; i<block_type->mNumParams; i++) {
        free_cl_type(block_type->mParams[i]);
    }
    free_cl_type(block_type->mResultType);

    MFREE(block_type);
}

void free_cl_type(sCLType* cl_type)
{
    int i;
    for(i=0; i<cl_type->mNumGenericsTypes; i++) {
        free_cl_type(cl_type->mGenericsTypes[i]);
    }
    if(cl_type->mBlockType) {
        free_cl_block_type(cl_type->mBlockType);
    }
    MFREE(cl_type);
}

static void load_fundamental_classes()
{
    (void)load_class("System");
    (void)load_class("Clover");

    (void)load_class("Byte");
    (void)load_class("UByte");
    (void)load_class("Short");
    (void)load_class("UShort");
    (void)load_class("Integer");
    (void)load_class("UInteger");
    (void)load_class("Long");
    (void)load_class("ULong");
    (void)load_class("Float");
    (void)load_class("Double");
    (void)load_class("Pointer");
    (void)load_class("Char");
    (void)load_class("Bool");

    (void)load_class("String");

    (void)load_class("Exception");
    (void)load_class("SystemException");
}

static void set_boxing_and_unboxing_class(char* primitive_class_name, char* lapper_class_name)
{
    sCLClass* klass = get_class(primitive_class_name);

    MASSERT(klass != NULL || klass == NULL);            // when compiling Fundamental.clc, klass is NULL

    sCLClass* klass2 = get_class(lapper_class_name);

    MASSERT(klass2 != NULL || klass == NULL);

    klass->mBoxingClass = klass2;
    klass2->mUnboxingClass = klass;
}

static void set_boxing_and_unboxing_classes()
{
    set_boxing_and_unboxing_class("int", "Integer");
    set_boxing_and_unboxing_class("uint", "UInteger");
    set_boxing_and_unboxing_class("byte", "Byte");
    set_boxing_and_unboxing_class("ubyte", "UByte");
    set_boxing_and_unboxing_class("short", "Short");
    set_boxing_and_unboxing_class("ushort", "UShort");
    set_boxing_and_unboxing_class("long", "Long");
    set_boxing_and_unboxing_class("ulong", "ULong");
    set_boxing_and_unboxing_class("float", "Float");
    set_boxing_and_unboxing_class("double", "Double");
    set_boxing_and_unboxing_class("pointer", "Pointer");
    set_boxing_and_unboxing_class("char", "Char");
    set_boxing_and_unboxing_class("bool", "Bool");
}

void class_init()
{
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);

    alloc_class("int", TRUE, -1, 0, NULL, FALSE);
    alloc_class("uint", TRUE, -1, 0, NULL, FALSE);
    alloc_class("byte", TRUE, -1, 0, NULL, FALSE);
    alloc_class("ubyte", TRUE, -1, 0, NULL, FALSE);
    alloc_class("short", TRUE, -1, 0, NULL, FALSE);
    alloc_class("ushort", TRUE, -1, 0, NULL, FALSE);
    alloc_class("long", TRUE, -1, 0, NULL, FALSE);
    alloc_class("ulong", TRUE, -1, 0, NULL, FALSE);
    alloc_class("float", TRUE, -1, 0, NULL, FALSE);
    alloc_class("double", TRUE, -1, 0, NULL, FALSE);
    alloc_class("pointer", TRUE, -1, 0, NULL, FALSE);
    alloc_class("char", TRUE, -1, 0, NULL, FALSE);
    alloc_class("bool", TRUE, -1, 0, NULL, FALSE);
    alloc_class("Null", TRUE, -1, 0, NULL, FALSE);
    alloc_class("lambda", TRUE, -1, 0, NULL, FALSE);

    alloc_class("SELF", FALSE, -1, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass0", FALSE, 0, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass1", FALSE, 1, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass2", FALSE, 2, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass3", FALSE, 3, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass4", FALSE, 4, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass5", FALSE, 5, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass6", FALSE, 6, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass7", FALSE, 7, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass8", FALSE, 8, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass9", FALSE, 9, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass10", FALSE, 10, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass11", FALSE, 11, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass12", FALSE, 12, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass13", FALSE, 13, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass14", FALSE, 14, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass15", FALSE, 15, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass16", FALSE, 16, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass17", FALSE, 17, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass18", FALSE, 18, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass19", FALSE, 19, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass20", FALSE, 20, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass21", FALSE, 21, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass22", FALSE, 22, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass23", FALSE, 23, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass24", FALSE, 24, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass25", FALSE, 25, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass26", FALSE, 26, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass27", FALSE, 27, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass28", FALSE, 28, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass29", FALSE, 29, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass30", FALSE, 30, 0, NULL, FALSE);
    alloc_class("GenericsParametorClass31", FALSE, 31, 0, NULL, FALSE);

    load_fundamental_classes();
    set_boxing_and_unboxing_classes();
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
