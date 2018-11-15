#include "common.h"

static void free_class(sCLClass* klass);
ALLOC sCLType* create_cl_type(sCLClass* klass, sCLClass* klass2);
void free_cl_type(sCLType* cl_type);

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

BOOL put_class_to_table(char* class_name, sCLClass* klass)
{
    remove_class(class_name);

/*
    if(get_class(class_name)) {
        return TRUE;
    }
*/

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
                sCLClass* result = p->mItem;
                return result;
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

BOOL search_for_class_file(char* class_name, char* class_file_name, size_t class_file_name_size)
{
    /// script file directory ///
    if(gScriptDirPath[0] != '\0') {
        snprintf(class_file_name, class_file_name_size, "%s/%s.oclcl", gScriptDirPath, class_name);

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    /// current working directory ///
    char* cwd = getenv("PWD");

    if(cwd) {
        snprintf(class_file_name, class_file_name_size, "%s/%s.oclcl", cwd, class_name);

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    /// home directory ///
    char* home = getenv("HOME");

    if(home) {
        snprintf(class_file_name, class_file_name_size, "%s/.clover2/%s.oclcl", home, class_name);

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    /// system shared directory ///
    snprintf(class_file_name, class_file_name_size, "%s/share/clover2/%s.oclcl", PREFIX, class_name);

    if(access(class_file_name, F_OK) == 0) {
        return TRUE;
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
;
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

static BOOL read_long_from_file(int fd, clint64* n)
{
    return read_from_file(fd, n, sizeof(clint64));
}

static BOOL read_const_from_file(int fd, sConst* constant, char* class_name)
{
    int len;
    if(!read_int_from_file(fd, &len)) {
        return FALSE;
    }

    sConst_init_with_size(constant, len+1);
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
    (*cl_type)->mNullable = n;

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
    clint64 l;

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }

    if(n == 0) {
        *size_methods = 4;
        *num_methods = 0;
    }
    else {
        *size_methods = *num_methods = n;
    }

    *methods = MCALLOC(1, sizeof(sCLMethod)*(*size_methods));

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

        method->mMethodIndex = n;

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

            if(!read_int_from_file(fd, &n)) {
                return FALSE;
            }

            param->mDefaultValueOffset = n;
        }

        if(!read_cl_type_from_file(fd, &method->mResultType)) {
            return FALSE;
        }

        method->mNativeMethod = NULL;   // Native methods are loaded on the calling time
        method->mNativeFunName = NULL;

        if(method->mFlags & METHOD_FLAGS_NATIVE) {
            memset(&method->mByteCodes, 0, sizeof(sByteCode));

            method->mVarNum = 0;
        } else {
            if(!read_code_from_file(fd, &method->mByteCodes)) {
                return FALSE;
            }

            if(!read_int_from_file(fd, &n)) {
                return FALSE;
            }

            method->mVarNum = n;
        }

        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }

        method->mNumGenerics = n;
        for(j=0; j<method->mNumGenerics; j++) {
            if(!read_int_from_file(fd, &n)) {
                return FALSE;
            }

            method->mGenericsParamTypeOffsets[j] = n;
        }

        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }

        method->mCLibraryOffset = n;

        if(method->mCLibraryOffset != 0) {
            char* dynamic_library_name = CONS_str(&klass->mConst, method->mCLibraryOffset);

            void* dynamic_library = dlopen(dynamic_library_name, RTLD_LAZY);

            if(dynamic_library) {
                char* method_name = CONS_str(&klass->mConst, method->mNameOffset);
                method->mCFunctionPointer = dlsym(dynamic_library, method_name);
            }
        }
    }

    return TRUE;
}

static BOOL read_fields_from_file(int fd, sCLField** fields, int* num_fields, int* size_fields, sCLClass* klass)
{
    int n;
    clint64 l;

    if(!read_int_from_file(fd, &n)) {
        return FALSE;
    }
    if(n == 0) {
        *size_fields = 4;
        *num_fields = 0;
    }
    else {
        *size_fields = *num_fields = n;
    }

    *fields = MCALLOC(1, sizeof(sCLField)*(*size_fields));

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

        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }
        field->mInitializeValue = n;
    }

    return TRUE;
}

static sCLClass* read_class_from_file(char* class_name, int fd)
{
    sCLClass* klass = MCALLOC(1, sizeof(sCLClass));

    int n;
    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mNumGenerics = n;

    int i;
    for(i=0; i<klass->mNumGenerics; i++) {
        if(!read_int_from_file(fd, &n)) {
            return FALSE;
        }

        klass->mGenericsParamNameOffsets[i] = n;

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

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mMethodGenericsParamClassNum = n;

    clint64 l;
    if(!read_long_from_file(fd, &l)) {
        MFREE(klass);
        return NULL;
    }
    klass->mFlags = l;
    klass->mFlags &= ~CLASS_FLAGS_MODIFIED;

    if(!read_const_from_file(fd, &klass->mConst, class_name)) {
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

    klass->mBlockObjects = MCALLOC(1, sizeof(sCLBlockObject)*4); // requiring compile time info
    klass->mSizeBlockObjects = 4;
    klass->mNumBlockObjects = 0;

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

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mCallingClassMethodIndex = n;

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mCallingMethodIndex = n;

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mAllocSizeMethodIndex = n;

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }
    klass->mNumTypedef = n;

    for(i=0; i<klass->mNumTypedef; i++) {
        if(!read_int_from_file(fd, &n)) {
            MFREE(klass);
            return NULL;
        }

        klass->mTypedefClassName1Offsets[i] = n;

        if(!read_int_from_file(fd, &n)) {
            MFREE(klass);
            return NULL;
        }

        klass->mTypedefClassName2Offsets[i] = n;
    }

    if(!read_int_from_file(fd, &n)) {
        MFREE(klass);
        return NULL;
    }

    klass->mUnboxingClassNameOffset = n;

    return klass;
}

BOOL create_virtual_method_table(sCLClass* klass)
{
    memset(klass->mVirtualMethodTable, 0, sizeof(sCLMethod*)*METHOD_NUM_MAX);

    if(klass->mNumMethods >= METHOD_NUM_MAX) {
        fprintf(stderr, "overflow method number\n");
        return FALSE;
    }

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

sCLClass* get_class_with_load(char* class_name)
{
    sCLClass* result = get_class(class_name);
    
    if(result == NULL) {
        result = load_class(class_name);
    }

    return result;
}

static BOOL ready_for_typedef(sCLClass* klass)
{
    int i;
    for(i=0; i<klass->mNumTypedef; i++) {
        char* class_name1 = CONS_str(&klass->mConst, klass->mTypedefClassName1Offsets[i]);
        char* class_name2 = CONS_str(&klass->mConst, klass->mTypedefClassName2Offsets[i]);

        sCLClass* klass = get_class_with_load(class_name2);
        if(klass) {
            put_class_to_table(class_name1, klass);
        }
        else {
            return FALSE;
        }
    }

    return TRUE;
}

static void set_boxing_and_unboxing_class(char* primitive_class_name, char* lapper_class_name)
{
    sCLClass* klass = get_class(primitive_class_name);

    MASSERT(klass != NULL || klass == NULL);            // when compiling Fundamental.clc, klass is NULL

    sCLClass* klass2 = get_class(lapper_class_name);

    MASSERT(klass2 != NULL || klass2 == NULL);

    if(klass) { klass->mBoxingClass = klass2; }
    if(klass2) { klass2->mUnboxingClass = klass; }
}

sCLClass* load_class_from_class_file(char* class_name, char* class_file_name)
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

    sCLClass* klass = read_class_from_file(class_name, fd);
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

    if(!ready_for_typedef(klass)) {
        free_class(klass);
        return NULL;
    }

    put_class_to_table(class_name, klass);

    klass->mBoxingClass = NULL;
    klass->mUnboxingClass = NULL;
    klass->mDynamicLibrary = NULL;
    klass->mInitialized = FALSE;

    if(klass->mUnboxingClassNameOffset != -1) {
        char* primitive_class_name = CONS_str(&klass->mConst, klass->mUnboxingClassNameOffset);
        char* lapper_class_name = CLASS_NAME(klass);

        set_boxing_and_unboxing_class(primitive_class_name, lapper_class_name);
    }

    klass->mFreeFun = NULL;
    klass->mInitMethodIndexOnCompileTime = klass->mNumMethods;

    return klass;
}

BOOL is_class_file_existance(char* class_name)
{
    char class_file_name[PATH_MAX+1];
    return search_for_class_file(class_name, class_file_name, PATH_MAX);
}

sCLClass* load_class(char* class_name)
{
    sCLClass* klass = get_class(class_name);
    if(klass != NULL) {
        return klass;
    }

    char class_file_name[PATH_MAX+1];
    if(!search_for_class_file(class_name, class_file_name, PATH_MAX)) {
        return NULL;
    }

    sCLClass* result = load_class_from_class_file(class_name, class_file_name);

    return result;
}

sCLClass* alloc_class(char* class_name, BOOL primitive_, int generics_param_class_num, int method_generics_param_class_num, int generics_number, char name_of_generics_params[GENERICS_TYPES_MAX][VAR_NAME_MAX], sCLClass** type_of_generics_params, BOOL interface, BOOL dynamic_class, BOOL no_free_object, BOOL lambda, sCLClass* unboxing_class)
{
    sCLClass* klass = MCALLOC(1, sizeof(sCLClass));

    klass->mFlags |= (primitive_ ? CLASS_FLAGS_PRIMITIVE:0) | (interface ? CLASS_FLAGS_INTERFACE:0) | (dynamic_class ? CLASS_FLAGS_DYNAMIC_CLASS:0) | ((strcmp(class_name, "Null") == 0 || no_free_object) ? CLASS_FLAGS_NO_FREE_OBJECT:0) | (lambda ? CLASS_FLAGS_LAMBDA:0);
    klass->mGenericsParamClassNum = generics_param_class_num;
    klass->mMethodGenericsParamClassNum = method_generics_param_class_num;

    klass->mNumGenerics = generics_number;

    if(generics_number >= GENERICS_TYPES_MAX) {
        fprintf(stderr, "overflow generics number\n");
        exit(1);
    }

    sConst_init(&klass->mConst);

    klass->mClassNameOffset = append_str_to_constant_pool(&klass->mConst, class_name, FALSE);

    klass->mMethods = MCALLOC(1, sizeof(sCLMethod)*4);
    klass->mSizeMethods = 4;
    klass->mNumMethods = 0;

    klass->mFields = MCALLOC(1, sizeof(sCLField)*4);
    klass->mSizeFields = 4;
    klass->mNumFields = 0;

    klass->mBlockObjects = MCALLOC(1, sizeof(sCLBlockObject)*4);
    klass->mSizeBlockObjects = 4;
    klass->mNumBlockObjects = 0;

    klass->mClassFields = MCALLOC(1, sizeof(sCLField)*4);
    klass->mSizeClassFields = 4;
    klass->mNumClassFields = 0;

    klass->mClassInitializeMethodIndex = -1;
    klass->mClassFinalizeMethodIndex = -1;
    klass->mFinalizeMethodIndex = -1;
    klass->mCallingMethodIndex = -1;
    klass->mCallingClassMethodIndex = -1;
    klass->mAllocSizeMethodIndex = -1;

    klass->mMethodIndexOnCompileTime = 0;

    int i;
    for(i=0; i<generics_number; i++) {
        if(type_of_generics_params[i]) {
            klass->mGenericsParamNameOffsets[i] = append_str_to_constant_pool(&klass->mConst, name_of_generics_params[i], FALSE);
            klass->mGenericsParamTypeOffsets[i] = append_str_to_constant_pool(&klass->mConst, CLASS_NAME(type_of_generics_params[i]), FALSE);
        }
        else {
            klass->mGenericsParamNameOffsets[i] = 0;
            klass->mGenericsParamTypeOffsets[i] = 0;
        }
    }

    put_class_to_table(class_name, klass);

    klass->mBoxingClass = NULL;
    klass->mUnboxingClass = unboxing_class;
    if(unboxing_class) unboxing_class->mBoxingClass = klass;
    klass->mDynamicLibrary = NULL;

    klass->mFreeFun = NULL;
    klass->mNumTypedef = 0;
    memset(klass->mTypedefClassName1Offsets, 0, sizeof(int)*TYPEDEF_MAX);
    memset(klass->mTypedefClassName2Offsets, 0, sizeof(int)*TYPEDEF_MAX);
    klass->mInitialized = FALSE;

    if(unboxing_class) {
        klass->mUnboxingClassNameOffset = append_str_to_constant_pool(&klass->mConst, CLASS_NAME(klass->mUnboxingClass), FALSE);
    }
    else {
        klass->mUnboxingClassNameOffset = -1;
    }

    klass->mInitMethodIndexOnCompileTime = 0;

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

        if(!(method->mFlags & METHOD_FLAGS_NATIVE) && method->mByteCodes.mCodes != NULL) {
            sByteCode_free(&method->mByteCodes);
        }
    }
    MFREE(klass->mMethods);

    for(i=0; i<klass->mNumBlockObjects; i++) {
        sCLBlockObject* block_object = klass->mBlockObjects + i;

        sByteCode_free(&block_object->mByteCodes);
        sConst_free(&block_object->mConst);
    }
    MFREE(klass->mBlockObjects);

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

#ifdef ENABLE_JIT
    if(klass->mDynamicLibrary) {
        dlclose(klass->mDynamicLibrary);
    }
#endif

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

void class_init()
{
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);

    alloc_class("int", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("uint", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("byte", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("ubyte", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("short", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("ushort", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("long", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("ulong", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("float", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("double", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);

    alloc_class("pointer", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("char", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);
    alloc_class("bool", TRUE, -1, -1, 0, NULL, NULL, FALSE, FALSE, TRUE, FALSE, NULL);

    alloc_class("lambda", FALSE, -1, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, TRUE, NULL);
    alloc_class("regex", FALSE, -1, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);

    alloc_class("WildCard", FALSE, -1, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("Anonymous", FALSE, -1, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("Self", FALSE, -1, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);

    alloc_class("GenericsParametorClass0", FALSE, 0, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass1", FALSE, 1, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass2", FALSE, 2, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass3", FALSE, 3, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass4", FALSE, 4, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass5", FALSE, 5, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass6", FALSE, 6, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass7", FALSE, 7, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass8", FALSE, 8, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass9", FALSE, 9, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass10", FALSE, 10, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass11", FALSE, 11, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass12", FALSE, 12, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass13", FALSE, 13, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass14", FALSE, 14, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass15", FALSE, 15, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass16", FALSE, 16, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass17", FALSE, 17, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass18", FALSE, 18, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass19", FALSE, 19, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass20", FALSE, 20, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass21", FALSE, 21, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass22", FALSE, 22, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass23", FALSE, 23, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass24", FALSE, 24, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass25", FALSE, 25, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass26", FALSE, 26, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass27", FALSE, 27, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass28", FALSE, 28, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass29", FALSE, 29, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass30", FALSE, 30, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("GenericsParametorClass31", FALSE, 31, -1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);

    alloc_class("MethodGenericsParametorClass0", FALSE, -1, 0, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass1", FALSE, -1, 1, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass2", FALSE, -1, 2, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass3", FALSE, -1, 3, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass4", FALSE, -1, 4, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass5", FALSE, -1, 5, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass6", FALSE, -1, 6, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass7", FALSE, -1, 7, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass8", FALSE, -1, 8, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass9", FALSE, -1, 9, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass10", FALSE, -1, 10, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass11", FALSE, -1, 11, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
    alloc_class("MethodGenericsParametorClass12", FALSE, -1, 12, 0, NULL, NULL, FALSE, FALSE, FALSE, FALSE, NULL);
}

void class_final()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        if(p->mFreed == FALSE) {
            sClassTable* p2 = gHeadClassTable;
            while(p2) {
                if(p->mItem == p2->mItem) {   // typedef class
                    p2->mFreed = TRUE;
                }
                p2 = p2->mNextClass;
            }
            free_class(p->mItem);
            MFREE(p->mName);
        }
        else {
            MFREE(p->mName);
        }
        p = p->mNextClass;
    }

    gHeadClassTable = NULL;
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);
}

BOOL is_valid_class(sCLClass* klass)
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        if(klass == p->mItem) {
            return TRUE;
        }
        p = p->mNextClass;
    }

    return FALSE;
}

