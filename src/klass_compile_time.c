#include "common.h"
#include <libgen.h>

static void node_type_to_cl_type(sNodeType* node_type, ALLOC sCLType** cl_type, sCLClass* klass)
{
    *cl_type = create_cl_type(node_type->mClass, klass);

    (*cl_type)->mNumGenericsTypes = node_type->mNumGenericsTypes;

    int i;
    for(i=0; i<node_type->mNumGenericsTypes; i++) {
        node_type_to_cl_type(node_type->mGenericsTypes[i], ALLOC &(*cl_type)->mGenericsTypes[i], klass);
    }

    (*cl_type)->mArray = node_type->mArray;
    (*cl_type)->mNullable = node_type->mNullable;

    if(node_type->mBlockType) {
        (*cl_type)->mBlockType = MCALLOC(1, sizeof(sCLBlockType));
        (*cl_type)->mBlockType->mNumParams = node_type->mBlockType->mNumParams;
        int i;
        for(i=0; i<node_type->mBlockType->mNumParams; i++) {
             node_type_to_cl_type(node_type->mBlockType->mParams[i], ALLOC &(*cl_type)->mBlockType->mParams[i], klass);
        }
        node_type_to_cl_type(node_type->mBlockType->mResultType, ALLOC &(*cl_type)->mBlockType->mResultType, klass);
    }
    else {
        (*cl_type)->mBlockType = NULL;
    }
}

static void parser_param_to_cl_param(sParserParam* param, sCLParam* type, sCLClass* klass)
{
    type->mNameOffset = append_str_to_constant_pool(&klass->mConst, param->mName, FALSE);
    node_type_to_cl_type(param->mType, ALLOC &type->mType, klass);
    type->mDefaultValueOffset = append_str_to_constant_pool(&klass->mConst, param->mDefaultValue, FALSE);
}

static void create_method_path(char* result, int result_size, sCLMethod* method, sCLClass* klass)
{
    int i;

    xstrncpy(result, CLASS_NAME(klass), result_size);
    xstrncat(result, ".", result_size);
    xstrncat(result, METHOD_NAME2(klass, method), result_size);

    xstrncat(result, "(", result_size);

    for(i=0; i<method->mNumParams; i++) {
        xstrncat(result, CONS_str(&klass->mConst, method->mParams[i].mType->mClassNameOffset), result_size);
        if(method->mParams[i].mType->mArray) {
            xstrncat(result, "[]", result_size);
        }
        if(method->mParams[i].mType->mNullable) {
            xstrncat(result, "?", result_size);
        }

        if(i != method->mNumParams-1) xstrncat(result, ",", result_size);
    }

    xstrncat(result, ")", result_size);

/*
    for(i=0; i<method->mNumBlockType; i++) {
        int j;

        xstrncat(result, CONS_str(&klass->mConstPool, method->mBlockType.mResultType.mClassNameOffset), result_size);

        xstrncat(result, "{", result_size);

        for(j=0; j<method->mBlockType.mNumParams; j++) {
            xstrncat(result, CONS_str(&klass->mConstPool, method->mBlockType.mParamTypes[j].mClassNameOffset), result_size);
            if(j != method->mBlockType.mNumParams-1) {
                xstrncat(result, ",", result_size);
            }
        }

        xstrncat(result, "}", result_size);
    }
*/
}

void create_method_name_and_params(char* result, int size_result, sCLClass* klass, char* method_name, sNodeType* param_types[PARAMS_MAX], int num_params)
{
    *result = 0;

    xstrncpy(result, method_name, size_result);
    xstrncat(result, "(", size_result);

    int i;
    for(i=0; i<num_params; i++) {
        sNodeType* param_type = param_types[i];
        sCLClass* klass2 = param_type->mClass;
        BOOL array = param_type->mArray;
        BOOL nullable = param_type->mNullable;

        if(klass2 == klass) {
            xstrncat(result, "Self", size_result);
        }
        else {
            xstrncat(result, CLASS_NAME(klass2), size_result);
        }

        if(array) {
            xstrncat(result, "[]", size_result);
        }

        if(nullable) {
            xstrncat(result, "?", size_result);
        }

        if(i != num_params-1) {
            xstrncat(result, ",", size_result);
        }
    }

    xstrncat(result, ")", size_result);
}

void set_method_index_to_class(sCLClass* klass)
{
    klass->mClassInitializeMethodIndex = -1;

    int i;
    for(i=klass->mNumMethods-1; i>=0; i--) {
        sCLMethod* method = klass->mMethods + i;

        if((method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
            && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "initialize") == 0
            && method->mNumParams == 0)
        {
            klass->mClassInitializeMethodIndex = i;
            break;
        }
    }

    klass->mClassFinalizeMethodIndex = -1;

    for(i=klass->mNumMethods-1; i>=0; i--) {
        sCLMethod* method = klass->mMethods + i;

        if((method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
            && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "finalize") == 0
            && method->mNumParams == 0)
        {
            klass->mClassFinalizeMethodIndex = i;
            break;
        }
    }

    klass->mFinalizeMethodIndex = -1;

    for(i=klass->mNumMethods-1; i>=0; i--) {
        sCLMethod* method = klass->mMethods + i;

        if(!(method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
            && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "finalize") == 0
            && method->mNumParams == 0)
        {
            klass->mFinalizeMethodIndex = i;
            break;
        }
    }

    klass->mCallingClassMethodIndex = -1;

    for(i=klass->mNumMethods-1; i>=0; i--) {
        sCLMethod* method = klass->mMethods + i;

        if((method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
            && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "callingMethod") == 0
            && method->mNumParams == 4)
        {
            /// check params ///
            sNodeType* param1 = create_node_type_from_cl_type(method->mParams[0].mType, klass);
            sNodeType* param2 = create_node_type_from_cl_type(method->mParams[1].mType, klass);
            sNodeType* param3 = create_node_type_from_cl_type(method->mParams[2].mType, klass);
            sNodeType* param4 = create_node_type_from_cl_type(method->mParams[3].mType, klass);

            if(type_identify_with_class_name(param1, "String") && type_identify_with_class_name(param2, "Array") && type_identify_with_class_name(param3, "int") && type_identify_with_class_name(param4, "int"))
            {
                klass->mCallingClassMethodIndex = i;
                break;
            }
        }
    }

    klass->mCallingMethodIndex = -1;

    for(i=klass->mNumMethods-1; i>=0; i--) {
        sCLMethod* method = klass->mMethods + i;

        if(!(method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
            && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "callingMethod") == 0
            && method->mNumParams == 4)
        {
            /// check params ///
            sNodeType* param1 = create_node_type_from_cl_type(method->mParams[0].mType, klass);
            sNodeType* param2 = create_node_type_from_cl_type(method->mParams[1].mType, klass);
            sNodeType* param3 = create_node_type_from_cl_type(method->mParams[2].mType, klass);
            sNodeType* param4 = create_node_type_from_cl_type(method->mParams[3].mType, klass);

            if(type_identify_with_class_name(param1, "String") && type_identify_with_class_name(param2, "Array") && type_identify_with_class_name(param3, "int") && type_identify_with_class_name(param4, "int"))
            {
                klass->mCallingMethodIndex = i;
                break;
            }
        }
    }

    klass->mAllocSizeMethodIndex = -1;

    for(i=klass->mNumMethods-1; i>=0; i--) {
        sCLMethod* method = klass->mMethods + i;

        if((method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
            && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "allocSize") == 0
            && method->mNumParams == 0)
        {
            sNodeType* result_type = create_node_type_from_cl_type(method->mResultType, klass);

            if(type_identify_with_class_name(result_type, "ulong")) {
                klass->mAllocSizeMethodIndex = i;
                break;
            }
        }
    }
}

BOOL add_method_to_class(sCLClass* klass, char* method_name, sParserParam* params, int num_params, sNodeType* result_type, BOOL native_, BOOL static_, BOOL dynamic_, sGenericsParamInfo* ginfo, sCLMethod** appended_method, char* clibrary_path, sParserInfo* info)
{
    if(klass->mNumMethods == klass->mSizeMethods) {
        int new_size = klass->mSizeMethods * 2;
        klass->mMethods = MREALLOC(klass->mMethods, sizeof(sCLMethod)*new_size);
        memset(klass->mMethods + klass->mSizeMethods, 0, sizeof(sCLMethod)*(new_size - klass->mSizeMethods));
        klass->mSizeMethods = new_size;
    }

    const int num_methods = klass->mNumMethods;

    *appended_method = klass->mMethods + num_methods;

    klass->mMethods[num_methods].mFlags = (native_ ? METHOD_FLAGS_NATIVE : 0) | ((static_||native_||strcmp(clibrary_path, "") != 0) ? METHOD_FLAGS_CLASS_METHOD:0) | (strcmp(clibrary_path, "") != 0 ? METHOD_FLAGS_C_FUNCTION:0) | (dynamic_ ? METHOD_FLAGS_DYNAMIC:0);
    klass->mMethods[num_methods].mNameOffset = append_str_to_constant_pool(&klass->mConst, method_name, FALSE);

    if(strcmp(clibrary_path, "") != 0) {
        klass->mMethods[num_methods].mCLibraryOffset = append_str_to_constant_pool(&klass->mConst, clibrary_path, FALSE);
    }
    else {
        klass->mMethods[num_methods].mCLibraryOffset = 0;
    }

    if(num_params >= PARAMS_MAX) {
        fprintf(stderr, "overflow param number\n");
        return FALSE;
    }

    if(strcmp(method_name, "initialize") == 0 || strcmp(method_name, "finalize") == 0 || native_)
    {
        klass->mMethods[num_methods].mFlags |= METHOD_FLAGS_NON_NATIVE_CODE;
    }

    BOOL method_arg_default_value = FALSE;

    if(num_params >= PARAMS_MAX) {
        fprintf(stderr, "overflow param number\n");
        return FALSE;
    }

    int i;
    for(i=0; i<num_params; i++) {
        sParserParam* param = params + i;

        /// If method parametor default value exists, it must continue to exist
        if(param->mDefaultValue[0] != '\0') {
            method_arg_default_value = TRUE;
        }
        else {
            if(method_arg_default_value) {
                fprintf(stderr, "invalid method arg default value\n");
                return FALSE;
            }
        }

        parser_param_to_cl_param(param, klass->mMethods[num_methods].mParams + i, klass);
    }

    klass->mMethods[num_methods].mNumParams = num_params;

    char method_path[METHOD_PATH_MAX+1];
    create_method_path(method_path, METHOD_PATH_MAX, &klass->mMethods[num_methods], klass);
    klass->mMethods[num_methods].mPathOffset = append_str_to_constant_pool(&klass->mConst, method_path, FALSE);

    if(result_type == NULL) {
        fprintf(stderr, "Invalid result type of method(%s.%s)\n", CLASS_NAME(klass), method_name);
        return FALSE;
    }
    node_type_to_cl_type(result_type, ALLOC &klass->mMethods[num_methods].mResultType, klass);

    int size_method_name_and_params = METHOD_NAME_MAX + PARAMS_MAX * CLASS_NAME_MAX + 256;
    char method_name_and_params[size_method_name_and_params];

    sNodeType* param_types[PARAMS_MAX];
    for(i=0; i<num_params; i++) {
        param_types[i] = params[i].mType;
    }
    create_method_name_and_params(method_name_and_params, size_method_name_and_params, klass, method_name, param_types, num_params);

    klass->mMethods[num_methods].mMethodNameAndParamsOffset = append_str_to_constant_pool(&klass->mConst, method_name_and_params, FALSE);

    klass->mMethods[num_methods].mMethodIndex = num_methods;

    if(ginfo) {
        if(ginfo->mNumParams >= GENERICS_TYPES_MAX) {
            fprintf(stderr, "overflow generics types number\n");
            return FALSE;
        }

        klass->mMethods[num_methods].mNumGenerics = ginfo->mNumParams;
        for(i=0; i<ginfo->mNumParams; i++) {
            char* interface_name = CLASS_NAME(ginfo->mInterface[i]);
            klass->mMethods[num_methods].mGenericsParamTypeOffsets[i] = append_str_to_constant_pool(&klass->mConst, interface_name, FALSE);
        }
    }
    else {
        klass->mMethods[num_methods].mNumGenerics = 0;
    }

    klass->mNumMethods++;

    if(klass->mNumMethods >= METHOD_NUM_MAX) {
        fprintf(stderr, "overflow method number\n");
        return FALSE;
    }

    if(!create_virtual_method_table(klass)) {
        fprintf(stderr, "overflow method number\n");
        return FALSE;
    }

    set_method_index_to_class(klass);
    
    return TRUE;
}

int add_block_object_to_class(sCLClass* klass, sByteCode codes, sConst constant, int var_num, int num_params, BOOL lambda)
{
    if(klass->mNumBlockObjects == klass->mSizeBlockObjects) {
        int new_size = klass->mSizeBlockObjects * 2;
        klass->mBlockObjects = MREALLOC(klass->mBlockObjects, sizeof(sCLMethod)*new_size);
        memset(klass->mBlockObjects + klass->mSizeBlockObjects, 0, sizeof(sCLMethod)*(new_size - klass->mSizeBlockObjects));
        klass->mSizeBlockObjects = new_size;
    }

    int num_block_objects = klass->mNumBlockObjects;

    sCLBlockObject* block_object = klass->mBlockObjects + num_block_objects;

    block_object->mByteCodes = codes;
    block_object->mConst = constant;
    block_object->mVarNum = var_num;
    block_object->mNumParams = num_params;
    block_object->mLambda = lambda;

    klass->mNumBlockObjects++;
    
    return num_block_objects;
}

BOOL add_typedef_to_class(sCLClass* klass, char* class_name1, char* class_name2)
{
    klass->mTypedefClassName1Offsets[klass->mNumTypedef] = append_str_to_constant_pool(&klass->mConst, class_name1, FALSE);
    klass->mTypedefClassName2Offsets[klass->mNumTypedef] = append_str_to_constant_pool(&klass->mConst, class_name2, FALSE);
    klass->mNumTypedef++;

    if(klass->mNumTypedef >= TYPEDEF_MAX) {
        fprintf(stderr, "overflow typedef max\n");
        return FALSE;
    }

    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

    if(klass2) {
        put_class_to_table(class_name1, klass2);
    }
    else {
        return FALSE;
    }

    return TRUE;
}


#include <stdio.h>

#define BIG_ENOUGH  1024*2*2

static int get_value_from_header(char* header_path, char* field_name)
{
    char buffer[BIG_ENOUGH];

    char command_line[PATH_MAX + 128];
    snprintf(command_line, PATH_MAX +128, "cc -E -dM -x c %s", header_path);
    FILE *fp = popen(command_line, "r");
    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        char identifier[BIG_ENOUGH];
        int value;
        if(sscanf(buffer, "#define %s %d", identifier, &value) == 2) {
            if(strcmp(identifier, field_name) == 0) {
                fclose(fp);
                return value;
            }
        }
    }
    fclose(fp);

    return -1;
}

BOOL add_class_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, sNodeType* result_type, int initialize_value, char* header_path)
{
    if(klass->mNumClassFields == klass->mSizeClassFields) {
        int new_size = klass->mSizeClassFields * 2;
        klass->mClassFields = MREALLOC(klass->mClassFields, sizeof(sCLField)*new_size);
        memset(klass->mClassFields + klass->mSizeClassFields, 0, sizeof(sCLField)*(new_size - klass->mSizeClassFields));
        klass->mSizeClassFields = new_size;
    }

    const int num_fields = klass->mNumClassFields;

    klass->mClassFields[num_fields].mFlags = (private_ ? FIELD_FLAGS_PRIVATE : 0) | (protected_ ? FIELD_FLAGS_PROTECTED:0);
    klass->mClassFields[num_fields].mNameOffset = append_str_to_constant_pool(&klass->mConst, name, FALSE);

    if(header_path[0] != '\0') {
        klass->mClassFields[num_fields].mInitializeValue = get_value_from_header(header_path, name);
    }
    else {
        klass->mClassFields[num_fields].mInitializeValue = initialize_value;
    }

    node_type_to_cl_type(result_type, ALLOC &klass->mClassFields[num_fields].mResultType, klass);

    klass->mNumClassFields++;

    return TRUE;
}

void add_code_to_method(sCLMethod* method, sByteCode* code, int var_num)
{
    method->mByteCodes = *code;
    method->mVarNum = var_num;
}

BOOL determine_method_generics_types(sNodeType* left_param, sNodeType* right_param, sNodeType* method_generics_types)
{
    if(left_param == NULL || right_param == NULL) {
        return FALSE;
    }

    sCLClass* left_param_class = left_param->mClass;
    sCLClass* right_param_class = right_param->mClass;

    int left_param_class_num = left_param_class->mMethodGenericsParamClassNum;
    int right_param_class_num = right_param_class->mMethodGenericsParamClassNum;

    if(left_param_class_num != -1 && right_param_class_num == -1) {
        method_generics_types->mGenericsTypes[left_param_class_num] = right_param;

        method_generics_types->mNumGenericsTypes = left_param_class_num +1;
    }

    int i;
    for(i=0; i<left_param->mNumGenericsTypes; i++) {
        if(!determine_method_generics_types(left_param->mGenericsTypes[i], right_param->mGenericsTypes[i], method_generics_types))
        {
            return FALSE;
        }
    }

    sNodeBlockType* left_block_type = left_param->mBlockType;
    sNodeBlockType* right_block_type = right_param->mBlockType;

    if(left_block_type != NULL) {
        for(i=0; i<left_block_type->mNumParams; i++) {
            if(!determine_method_generics_types(left_block_type->mParams[i], right_block_type->mParams[i], method_generics_types))
            {
                return FALSE;
            }
        }

        if(!determine_method_generics_types(left_block_type->mResultType, right_block_type->mResultType, method_generics_types))
        {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL search_for_class_file_on_compile_time(char* class_name, char* class_file_path, size_t class_file_path_size)
{
    /// script file directory ///
    if(gScriptDirPath[0] != '\0') {
        snprintf(class_file_path, class_file_path_size, "%s/%s.oclcl", gScriptDirPath, class_name);

        if(access(class_file_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// current working directory ///
    char* cwd = getenv("PWD");

    if(cwd) {
        snprintf(class_file_path, class_file_path_size, "%s/%s.oclcl", cwd, class_name);

        if(access(class_file_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// home directory ///
    char* home = getenv("HOME");

    if(home) {
        snprintf(class_file_path, class_file_path_size, "%s/.clover2/%s.oclcl", home, class_name);

        if(access(class_file_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// system shared directory ///
    snprintf(class_file_path, class_file_path_size, "%s/share/clover2/%s.oclcl", PREFIX, class_name);

    if(access(class_file_path, F_OK) == 0) {
        return TRUE;
    }

    return FALSE;
}

static BOOL check_method_params(sCLMethod* method, sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, sNodeType* left_generics_type, sNodeType* right_generics_type, sNodeType* left_method_generics, sNodeType* right_method_generics, sNodeType* method_generics_types, BOOL lazy_lambda_compile, struct sParserInfoStruct* info)
{
    if(strcmp(METHOD_NAME2(klass, method), method_name) == 0) 
    {
        if((search_for_class_method && (method->mFlags & METHOD_FLAGS_CLASS_METHOD)) || (!search_for_class_method && !(method->mFlags & METHOD_FLAGS_CLASS_METHOD))) 
        {
            if(num_params == method->mNumParams) {
                int j;

                for(j=0; j<num_params; j++ ) {
                    sNodeType* param = create_node_type_from_cl_type(method->mParams[j].mType, klass);

                    if(lazy_lambda_compile 
                        && j == num_params-1 
                        && type_identify_with_class_name(param, "lambda")) 
                    {
                        break;
                    }
                    else {
                        if(!substitution_posibility(param, param_types[j], left_generics_type, right_generics_type, left_method_generics, right_method_generics, FALSE)) 
                        {
                            return FALSE;
                        }

                        if(!determine_method_generics_types(param, param_types[j], method_generics_types)) 
                        {
                            return FALSE;
                        }
                    }
                }
                
                return TRUE;
            }
        }
    }

    return FALSE;
}

static sNodeType* get_method_genercs_from_method(sCLClass* klass, sCLMethod* method)
{
    sNodeType* result = alloc_node_type();

    result->mClass = NULL;

    int i;
    for(i=0; i<method->mNumGenerics; i++) {
        char* interface_name = CONS_str(&klass->mConst, method->mGenericsParamTypeOffsets[i]);
        result->mGenericsTypes[i] = create_node_type_with_class_name(interface_name);
    }

    result->mNumGenericsTypes = method->mNumGenerics;

    return result;
}

int search_for_method(sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, int start_point, sNodeType* left_generics_type, sNodeType* right_generics_type, sNodeType* right_method_generics, sNodeType** result_type, BOOL lazy_lambda_compile, sNodeType** method_generics_types, struct sParserInfoStruct* info)
{
    int i;
    if(*method_generics_types == NULL) {
        *method_generics_types = alloc_node_type();
    }

    if(start_point < klass->mNumMethods) {
        for(i=start_point; i>=0; i--) {           // search for the method in reverse order because we want to get last defined method
            sCLMethod* method = klass->mMethods + i;

            sNodeType* left_method_generics = get_method_genercs_from_method(klass, method);

            if(check_method_params(method, klass, method_name, param_types, num_params, search_for_class_method, left_generics_type, right_generics_type, left_method_generics, right_method_generics, *method_generics_types, lazy_lambda_compile, info))
            {
                sNodeType* result_type2 = ALLOC create_node_type_from_cl_type(method->mResultType, klass);

                sNodeType* result_type3;

                if(!solve_generics_types_for_node_type(result_type2, &result_type3, *method_generics_types, FALSE, TRUE))
                {
                    return -1;
                }

                if(!solve_generics_types_for_node_type(result_type3, result_type, left_generics_type, TRUE, FALSE))
                {
                    return -1;
                }

                return i;
            }
        }
    }

    return -1;
}

BOOL search_for_methods_from_method_name(int method_indexes[], int size_method_indexes, int* num_methods, sCLClass* klass, char* method_name, int start_point, BOOL class_method)
{
    int i;

    *num_methods = 0;

    if(start_point < klass->mNumMethods) {
        for(i=start_point; i>=0; i--) {           // search for the method in reverse order because we want to get last defined method
            sCLMethod* method;
            
            method = klass->mMethods + i;

            if(strcmp(METHOD_NAME2(klass, method), method_name) == 0 && ((method->mFlags & METHOD_FLAGS_CLASS_METHOD) ? 1:0) == class_method) 
            {
                method_indexes[*num_methods] = i;
                (*num_methods)++;

                if(*num_methods >= size_method_indexes) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

int search_for_field(sCLClass* klass, char* field_name)
{
    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sCLField* field = klass->mFields + i;

        if(strcmp(CONS_str(&klass->mConst, field->mNameOffset), field_name) == 0) {
            return i;
        }
    }

    return -1;
}

int search_for_class_field(sCLClass* klass, char* field_name)
{
    int i;
    for(i=0; i<klass->mNumClassFields; i++) {
        sCLField* field = klass->mClassFields + i;

        if(strcmp(CONS_str(&klass->mConst, field->mNameOffset), field_name) == 0) {
            return i;
        }
    }

    return -1;
}

BOOL class_method_name_existance(sCLClass* klass, char* method_name)
{
    int i;
    for(i=0; i<klass->mNumMethods; i++) {
        sCLMethod* method = klass->mMethods + i;

        if((method->mFlags & METHOD_FLAGS_CLASS_METHOD ) && strcmp(METHOD_NAME2(klass, method), method_name) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL none_class_method_name_existance(sCLClass* klass, char* method_name)
{
    int i;
    for(i=0; i<klass->mNumMethods; i++) {
        sCLMethod* method = klass->mMethods + i;

        if(!(method->mFlags & METHOD_FLAGS_CLASS_METHOD ) && strcmp(METHOD_NAME2(klass, method), method_name) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL class_field_name_existance(sCLClass* klass, char* field_name)
{
    int i;
    for(i=0; i<klass->mNumClassFields; i++) {
        sCLField* field = klass->mClassFields + i;

        if(strcmp(FIELD_NAME(klass, field), field_name) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL field_name_existance(sCLClass* klass, char* field_name)
{
    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sCLField* field = klass->mFields + i;

        if(strcmp(FIELD_NAME(klass, field), field_name) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL is_method_param_name(char* name)
{
    if(strcmp(name, "it") == 0) {
        return TRUE;
    }

    int i;
    for(i=2; i<METHOD_BLOCK_PARAM_MAX; i++) {
        char buf[128];

        snprintf(buf, 128, "it%d", i);

        if(strcmp(buf, name) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL check_same_interface_of_two_methods(sCLMethod* method1, sCLClass* klass1, sCLMethod* method2, sCLClass* klass2)
{
    char* name1 = METHOD_NAME2(klass1, method1);
    char* name2 = METHOD_NAME2(klass2, method2);

    if(strcmp(name1, name2) != 0) {
        return FALSE;
    }

    sNodeType* result_type1 = create_node_type_from_cl_type(method1->mResultType, klass1);
    sNodeType* result_type2 = create_node_type_from_cl_type(method2->mResultType, klass2);

    if(!type_identify_with_class_name(result_type1, "Self") && !type_identify_with_class_name(result_type2, "Self"))
    {
        if(type_identify_with_class_name(result_type1, "Self")) {
            result_type1 = create_node_type_with_class_pointer(klass2);
        }

        if(!type_identify(result_type1, result_type2)) {
            return FALSE;
        }
    }

    if(method1->mNumParams != method2->mNumParams) {
        return FALSE;
    }

    int i;
    for(i=0; i<method1->mNumParams; i++) {
        sCLParam* param1 = method1->mParams + i;
        sCLParam* param2 = method2->mParams + i;

        sNodeType* param1_type = create_node_type_from_cl_type(param1->mType, klass1);
        sNodeType* param2_type = create_node_type_from_cl_type(param2->mType, klass2);

        if(!type_identify_with_class_name(param1_type, "Self") && !type_identify_with_class_name(param2_type, "Self"))
        {
            if(type_identify_with_class_name(param1_type, "Self")) {
                param1_type = create_node_type_with_class_pointer(klass2);
            }
            if(!type_identify(param1_type, param2_type)) {
                return FALSE;
            }
        }
    }

    return TRUE;
}


BOOL check_implemented_methods_for_interface(sCLClass* left_class, sCLClass* right_class, BOOL output_message)
{
    sCLClass* anonymous_class = get_class("Anonymous");
    if(right_class == anonymous_class) {
        return TRUE;
    }
    else if(right_class->mFlags & CLASS_FLAGS_PRIMITIVE) {
        return FALSE;
    }
    else if(left_class != right_class) {
        int i;
        for(i=0; i<left_class->mNumMethods; i++) {
            sCLMethod* method = left_class->mMethods + i;

            BOOL found = FALSE;

            int j;
            for(j=0; j<right_class->mNumMethods; j++) {
                sCLMethod* method2 = right_class->mMethods + j;

                if(check_same_interface_of_two_methods(method, left_class, method2, right_class)) {
                    found = TRUE;
                }
            }

            if(!found) {
                if(output_message) {
                    fprintf(stderr, "method %s %s is not implemted\n", CLASS_NAME(left_class), METHOD_NAME2(left_class, method));
                }
                return FALSE;
            }
        }
    }

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// write class to a class file 
////////////////////////////////////////////////////////////////////////////////

static void append_const_to_buffer(sBuf* buf, sConst* constant)
{
    sBuf_append_int(buf, constant->mLen);
    sBuf_append(buf, constant->mConst, sizeof(char)*constant->mLen);
}

static void append_cl_type_to_buffer(sBuf* buf, sCLType* cl_type);

static void append_cl_block_type(sBuf* buf, sCLBlockType* cl_block_type)
{
    sBuf_append_int(buf, cl_block_type->mNumParams);
    int i;
    for(i=0; i<cl_block_type->mNumParams; i++) {
        append_cl_type_to_buffer(buf, cl_block_type->mParams[i]);
    }

    append_cl_type_to_buffer(buf, cl_block_type->mResultType);
}

static void append_cl_type_to_buffer(sBuf* buf, sCLType* cl_type)
{
    sBuf_append_int(buf, cl_type->mClassNameOffset);
    sBuf_append_int(buf, cl_type->mNumGenericsTypes);
    int i;
    for(i=0; i<cl_type->mNumGenericsTypes; i++) {
        append_cl_type_to_buffer(buf, cl_type->mGenericsTypes[i]);
    }

    sBuf_append_int(buf, cl_type->mArray);
    sBuf_append_int(buf, cl_type->mNullable);

    if(cl_type->mBlockType) {
        sBuf_append_int(buf, 1);
        append_cl_block_type(buf, cl_type->mBlockType);
    }
    else {
        sBuf_append_int(buf, 0);
    }
}

static void append_byte_codes_to_buffer(sBuf* buf, sByteCode* code)
{
    sBuf_append_int(buf, code->mLen);
    sBuf_append(buf, code->mCodes, code->mLen);
}

static void append_methods_to_buffer(sBuf* buf, sCLMethod* methods, sCLClass* klass, int num_methods)
{
    sBuf_append_int(buf, num_methods);
    int i;
    for(i=0; i<num_methods; i++) {
        sCLMethod* method = methods + i;

        sBuf_append_long(buf, method->mFlags);
        sBuf_append_int(buf, method->mNameOffset);
        sBuf_append_int(buf, method->mPathOffset);
        sBuf_append_int(buf, method->mMethodNameAndParamsOffset);
        sBuf_append_int(buf, method->mMethodIndex);

        sBuf_append_int(buf, method->mNumParams);

        int j;
        for(j=0; j<method->mNumParams; j++) {
            sCLParam* param = method->mParams + j;

            sBuf_append_int(buf, param->mNameOffset);
            append_cl_type_to_buffer(buf, param->mType);
            sBuf_append_int(buf, param->mDefaultValueOffset);
        }

        append_cl_type_to_buffer(buf, method->mResultType);

        if(!(method->mFlags & METHOD_FLAGS_NATIVE)) {
            append_byte_codes_to_buffer(buf, &method->mByteCodes);
            sBuf_append_int(buf, method->mVarNum);
        }

        sBuf_append_int(buf, method->mNumGenerics);
        for(j=0; j<method->mNumGenerics; j++) {
            int n = method->mGenericsParamTypeOffsets[j];
            sBuf_append_int(buf, n);
        }

        sBuf_append_int(buf, method->mCLibraryOffset);
    }
}

static void append_fields_to_buffer(sBuf* buf, sCLField* fields, int num_fields)
{
    sBuf_append_int(buf, num_fields);

    int i;
    for(i=0; i<num_fields; i++) {
        sCLField* field = fields + i;

        sBuf_append_long(buf, field->mFlags);
        sBuf_append_int(buf, field->mNameOffset);

        append_cl_type_to_buffer(buf, field->mResultType);

        sBuf_append_int(buf, field->mInitializeValue);
    }
}

static void append_block_to_buffer(sBuf* buf, sCLBlockObject* block_object)
{
    append_byte_codes_to_buffer(buf, &block_object->mByteCodes);
    append_const_to_buffer(buf, &block_object->mConst);
    sBuf_append_int(buf, block_object->mVarNum);
    sBuf_append_int(buf, block_object->mNumParams);
    sBuf_append_int(buf, block_object->mLambda);
}

static void write_class_to_buffer(sCLClass* klass, sBuf* buf)
{
    sBuf_append_int(buf, klass->mNumGenerics);
    int i;
    for(i=0; i<klass->mNumGenerics; i++ ) {
        sBuf_append_int(buf, klass->mGenericsParamNameOffsets[i]);
        sBuf_append_int(buf, klass->mGenericsParamTypeOffsets[i]);
    }
    sBuf_append_int(buf, klass->mGenericsParamClassNum);
    sBuf_append_int(buf, klass->mMethodGenericsParamClassNum);
    sBuf_append_long(buf, klass->mFlags);
    append_const_to_buffer(buf, &klass->mConst);
    sBuf_append_int(buf, klass->mClassNameOffset);
    append_methods_to_buffer(buf, klass->mMethods, klass, klass->mNumMethods);
    append_fields_to_buffer(buf, klass->mFields, klass->mNumFields);
    append_fields_to_buffer(buf, klass->mClassFields, klass->mNumClassFields);
    sBuf_append_int(buf, klass->mClassInitializeMethodIndex);
    sBuf_append_int(buf, klass->mClassFinalizeMethodIndex);
    sBuf_append_int(buf, klass->mFinalizeMethodIndex);
    sBuf_append_int(buf, klass->mCallingClassMethodIndex);
    sBuf_append_int(buf, klass->mCallingMethodIndex);
    sBuf_append_int(buf, klass->mAllocSizeMethodIndex);

    sBuf_append_int(buf, klass->mNumTypedef);
    for(i=0; i<klass->mNumTypedef; i++) {
        sBuf_append_int(buf, klass->mTypedefClassName1Offsets[i]);
        sBuf_append_int(buf, klass->mTypedefClassName2Offsets[i]);
    }

    sBuf_append_int(buf, klass->mUnboxingClassNameOffset);

    sBuf_append_int(buf, klass->mLabelNum);

    sBuf_append_int(buf, klass->mNumBlockObjects);

    for(i=0; i<klass->mNumBlockObjects; i++) {
        sCLBlockObject* block_object = klass->mBlockObjects + i;

        append_block_to_buffer(buf, block_object);
    }

    sBuf_append_int(buf, klass->mVersion);
}

BOOL write_class_to_class_file(sCLClass* klass)
{
    sBuf buf;

    sBuf_init(&buf);

    char magic_number[128];

    magic_number[0] = 11;
    magic_number[1] = 12;
    magic_number[2] = 34;
    magic_number[3] = 55;

    strcpy(magic_number + 4, "CLOVER");
    sBuf_append(&buf, magic_number, sizeof(char)*10);

    write_class_to_buffer(klass, &buf);

    /// write ///
    char file_name[PATH_MAX];
    if(klass->mVersion > 0) {
        snprintf(file_name, PATH_MAX, "%s@%d.oclcl", CLASS_NAME(klass), klass->mVersion);

        int f = open(file_name, O_WRONLY|O_TRUNC|O_CREAT, 0644);
        int total_size = 0;
        while(total_size < buf.mLen) {
            int size;

            if(buf.mLen - total_size < BUFSIZ) {
                size = write(f, buf.mBuf + total_size, buf.mLen - total_size);
            }
            else {
                size = write(f, buf.mBuf + total_size, BUFSIZ);
            }

            if(size < 0) {
                MFREE(buf.mBuf);
                close(f);
                return FALSE;
            }

            total_size += size;
        }
        close(f);
    }

    snprintf(file_name, PATH_MAX, "%s.oclcl", CLASS_NAME(klass));

    int f = open(file_name, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    int total_size = 0;
    while(total_size < buf.mLen) {
        int size;

        if(buf.mLen - total_size < BUFSIZ) {
            size = write(f, buf.mBuf + total_size, buf.mLen - total_size);
        }
        else {
            size = write(f, buf.mBuf + total_size, BUFSIZ);
        }

        if(size < 0) {
            MFREE(buf.mBuf);
            close(f);
            return FALSE;
        }

        total_size += size;
    }
    close(f);

    MFREE(buf.mBuf);

    return TRUE;
}

BOOL write_all_modified_classes()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        sCLClass* klass = p->mItem;

        if(klass->mFlags & CLASS_FLAGS_MODIFIED) {
            if(!write_class_to_class_file(klass)) {
                fprintf(stderr, "Clover failed to write class file(%s)\n", CLASS_NAME(klass));
                return FALSE;
            }
        }

        p = p->mNextClass;
    }

    return TRUE;
}

BOOL add_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, BOOL delegated, sNodeType* result_type)
{
    if(klass->mNumFields == klass->mSizeFields) {
        int new_size = klass->mSizeFields * 2;
        klass->mFields = MREALLOC(klass->mFields, sizeof(sCLField)*new_size);
        memset(klass->mFields + klass->mSizeFields, 0, sizeof(sCLField)*(new_size - klass->mSizeFields));
        klass->mSizeFields = new_size;
    }

    const int num_fields = klass->mNumFields;

    klass->mFields[num_fields].mFlags = (private_ ? FIELD_FLAGS_PRIVATE : 0) | (protected_ ? FIELD_FLAGS_PROTECTED:0) | (delegated ? FIELD_FLAGS_DELEGATED:0);
    klass->mFields[num_fields].mNameOffset = append_str_to_constant_pool(&klass->mConst, name, FALSE);

    klass->mFields[num_fields].mNumDelegatedMethod = 0;
    memset(&klass->mFields[num_fields].mDelegatedMethodIndex, 0, sizeof(int)*METHOD_NUM_MAX);

    node_type_to_cl_type(result_type, ALLOC &klass->mFields[num_fields].mResultType, klass);

    klass->mNumFields++;
    
    return TRUE;
}

static BOOL type_name_to_cl_type(char** p, ALLOC sCLType** cl_type, sCLClass* klass)
{
    char class_name[CLASS_NAME_MAX];

    char* p2 = class_name;

    while(isalnum(**p) || **p == '_') {
        *p2++ = **p;
        (*p)++;
    }
    *p2 = '\0';

    sCLClass* cl_type_class = get_class_with_load_and_initialize(class_name);

    if(cl_type_class == NULL) {
        return FALSE;
    }

    *cl_type = create_cl_type(cl_type_class, klass);

    (*cl_type)->mNumGenericsTypes = 0;

    if(strcmp(class_name, "lambda") == 0) {
        (*cl_type)->mBlockType = MCALLOC(1, sizeof(sCLBlockType));

        if(**p == '(') {
            (*p)++;

            if(**p == ')') {
                (*p)++;
            }
            else {
                int num_params = 0;
                while(1) {
                    sCLType* cl_block_param = NULL;
                    if(!type_name_to_cl_type(p, ALLOC &cl_block_param, klass)) 
                    {
                        return FALSE;
                    }

                    (*cl_type)->mBlockType->mParams[num_params] = cl_block_param;
                    num_params++;

                    if(num_params >= PARAMS_MAX) {
                        return FALSE;
                    }

                    if(**p == ')') {
                        (*p)++;
                        break;
                    }
                    else if(**p == ',') {
                        (*p)++;
                    }
                    else {
                        break;
                    }
                }
                (*cl_type)->mBlockType->mNumParams = num_params;
            }
        }

        if(**p == ':') {
            (*p)++;

            sCLType* result_type = NULL;
            if(!type_name_to_cl_type(p, ALLOC &result_type, klass)) 
            {
                return FALSE;
            }

            (*cl_type)->mBlockType->mResultType = result_type;
        }
        else {
            sCLClass* null_class = get_class("Null");
            (*cl_type)->mBlockType->mResultType = create_cl_type(null_class, klass);
        }
    }
    else if(**p == '<') {
        while(1) {
            if(!type_name_to_cl_type(p, ALLOC (*cl_type)->mGenericsTypes + (*cl_type)->mNumGenericsTypes, klass)) {
                return FALSE;
            }

            (*cl_type)->mNumGenericsTypes++;

            if((*cl_type)->mNumGenericsTypes >= GENERICS_TYPES_MAX) {
                return FALSE;
            }

            if(**p == ',') {
                (*p)++;
            }
            else if(**p == '>') {
                (*p)++;
                break;
            }
            else if(**p == '\0') {
                return FALSE;
            }
        }
    }
    else if(**p == '[' && *(*p+1) == ']') {
        (*p) += 2;
        (*cl_type)->mArray = TRUE;
    }

    (*cl_type)->mNullable = FALSE;

    return TRUE;
}

BOOL add_field_to_class_with_class_name(sCLClass* klass, char* name, BOOL private_, BOOL protected_, BOOL delegated, char* field_type_name)
{
    if(klass->mNumFields == klass->mSizeFields) {
        int new_size = klass->mSizeFields * 2;
        klass->mFields = MREALLOC(klass->mFields, sizeof(sCLField)*new_size);
        memset(klass->mFields + klass->mSizeFields, 0, sizeof(sCLField)*(new_size - klass->mSizeFields));
        klass->mSizeFields = new_size;
    }

    const int num_fields = klass->mNumFields;

    klass->mFields[num_fields].mFlags = (private_ ? FIELD_FLAGS_PRIVATE : 0) | (protected_ ? FIELD_FLAGS_PROTECTED:0) | (delegated ? FIELD_FLAGS_DELEGATED : 0);
    klass->mFields[num_fields].mNameOffset = append_str_to_constant_pool(&klass->mConst, name, FALSE);

    klass->mFields[num_fields].mNumDelegatedMethod = 0;
    memset(&klass->mFields[num_fields].mDelegatedMethodIndex, 0, sizeof(int)*METHOD_NUM_MAX);

    char* p = field_type_name;
    if(!type_name_to_cl_type(&p, ALLOC &klass->mFields[num_fields].mResultType, klass)) {
        return FALSE;
    }

    klass->mNumFields++;

    return TRUE;
}

BOOL add_class_field_to_class_with_class_name(sCLClass* klass, char* name, BOOL private_, BOOL protected_, char* field_type_name, int initialize_value)
{
    if(klass->mNumClassFields == klass->mSizeClassFields) {
        int new_size = klass->mSizeClassFields * 2;
        klass->mClassFields = MREALLOC(klass->mClassFields, sizeof(sCLField)*new_size);
        memset(klass->mClassFields + klass->mSizeClassFields, 0, sizeof(sCLField)*(new_size - klass->mSizeClassFields));
        klass->mSizeClassFields = new_size;
    }

    const int num_fields = klass->mNumClassFields;

    klass->mClassFields[num_fields].mFlags = (private_ ? FIELD_FLAGS_PRIVATE : 0) | (protected_ ? FIELD_FLAGS_PROTECTED:0);
    klass->mClassFields[num_fields].mNameOffset = append_str_to_constant_pool(&klass->mConst, name, FALSE);

    klass->mClassFields[num_fields].mInitializeValue = initialize_value;

    char* p = field_type_name;
    if(!type_name_to_cl_type(&p, ALLOC &klass->mClassFields[num_fields].mResultType, klass)) {
        return FALSE;
    }

    klass->mNumClassFields++;

    return TRUE;
}
