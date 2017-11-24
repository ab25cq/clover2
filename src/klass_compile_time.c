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
}

BOOL add_method_to_class(sCLClass* klass, char* method_name, sParserParam* params, int num_params, sNodeType* result_type, BOOL native_, BOOL static_, sGenericsParamInfo* ginfo)
{
    if(klass->mNumMethods == klass->mSizeMethods) {
        int new_size = klass->mSizeMethods * 2;
        klass->mMethods = MREALLOC(klass->mMethods, sizeof(sCLMethod)*new_size);
        memset(klass->mMethods + klass->mSizeMethods, 0, sizeof(sCLMethod)*(new_size - klass->mSizeMethods));
        klass->mSizeMethods = new_size;
    }

    const int num_methods = klass->mNumMethods;

    klass->mMethods[num_methods].mFlags = (native_ ? METHOD_FLAGS_NATIVE : 0) | (static_ ? METHOD_FLAGS_CLASS_METHOD:0);
    klass->mMethods[num_methods].mNameOffset = append_str_to_constant_pool(&klass->mConst, method_name, FALSE);

    BOOL method_arg_default_value = FALSE;

    int i;
    for(i=0; i<num_params; i++) {
        sParserParam* param = params + i;

        /// メソッドパラメータのデフォルトの値があった場合、その後にも無いといけない
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

    klass->mMethods[num_methods].mNumGenerics = ginfo->mNumParams;
    for(i=0; i<ginfo->mNumParams; i++) {
        char* interface_name = CLASS_NAME(ginfo->mInterface[i]);
        klass->mMethods[num_methods].mGenericsParamTypeOffsets[i] = append_str_to_constant_pool(&klass->mConst, interface_name, FALSE);
    }

    klass->mNumMethods++;

    if(klass->mNumMethods >= METHOD_NUM_MAX) {
        fprintf(stderr, "overflow method number\n");
        return FALSE;
    }

    set_method_index_to_class(klass);
    
    return TRUE;
}

BOOL add_typedef_to_class(sCLClass* klass, char* class_name1, char* class_name2)
{
    klass->mTypedefClassName1Offsets[klass->mNumTypedef] = append_str_to_constant_pool(&klass->mConst, class_name1, FALSE);
    klass->mTypedefClassName2Offsets[klass->mNumTypedef] = append_str_to_constant_pool(&klass->mConst, class_name2, FALSE);
    klass->mNumTypedef++;

    if(klass->mNumTypedef >= TYPEDEF_MAX) {
        return FALSE;
    }

    sCLClass* klass2 = get_class_with_load_on_compile_time(class_name2);

    if(klass2) {
        put_class_to_table(class_name1, klass2);
    }
    else {
        return FALSE;
    }

    return TRUE;
}

BOOL add_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, sNodeType* result_type)
{
    if(klass->mNumFields == klass->mSizeFields) {
        int new_size = klass->mSizeFields * 2;
        klass->mFields = MREALLOC(klass->mFields, sizeof(sCLField)*new_size);
        memset(klass->mFields + klass->mSizeFields, 0, sizeof(sCLField)*(new_size - klass->mSizeFields));
        klass->mSizeFields = new_size;
    }

    const int num_fields = klass->mNumFields;

    klass->mFields[num_fields].mFlags = (private_ ? FIELD_FLAGS_PRIVATE : 0) | (protected_ ? FIELD_FLAGS_PROTECTED:0);
    klass->mFields[num_fields].mNameOffset = append_str_to_constant_pool(&klass->mConst, name, FALSE);

    klass->mFields[num_fields].mNumDelegatedMethod = 0;
    memset(&klass->mFields[num_fields].mDelegatedMethodIndex, 0, sizeof(int)*METHOD_NUM_MAX);

    node_type_to_cl_type(result_type, ALLOC &klass->mFields[num_fields].mResultType, klass);

    klass->mNumFields++;
    
    return TRUE;
}

BOOL add_class_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, sNodeType* result_type, int initialize_value)
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
    /// ホームディレクトリのClover2のクラスファイルの置き場所にクラスファイルはありますか？ ///
    char* home = getenv("HOME");

    if(home) {
        snprintf(class_file_path, class_file_path_size, "%s/.clover2/%s.oclcl", home, class_name);

        if(access(class_file_path, F_OK) == 0) {
            return TRUE;  // ありました。真を返します
        }
    }

    /// カレントワーキングディレクトリにクラスファイルが存在しますか？ ///
    char* cwd = getenv("PWD");

    if(cwd) {
        snprintf(class_file_path, class_file_path_size, "%s/%s.oclcl", cwd, class_name);

        if(access(class_file_path, F_OK) == 0) {
            /// ソース・ファイルのパスを得る ///
            char source_path[PATH_MAX];
            snprintf(source_path, PATH_MAX, "%s/%s.clcl", cwd, class_name);

            char source_path2[PATH_MAX];
            if(strstr(gCompilingSourceFileName, "/"))  // gCompilingSourceFileNameは絶対パスじゃないこともある
            {
                char* source_dir = dirname(gCompilingSourceFileName);

                snprintf(source_path2, PATH_MAX, "%s/%s.clcl", source_dir, class_name);
            }
            else {
                source_path2[0] = '\0';
            }

            /// 自動コンパイル機能を行う ///
            struct stat class_file_path_stat;

            if(stat(class_file_path, &class_file_path_stat) != 0) {
                return FALSE;
            }

            if(access(source_path, F_OK) == 0) {
                struct stat source_path_stat;

                if(stat(source_path, &source_path_stat) != 0) {
                    return FALSE;
                }

                /// ソースファイルのほうが新しいならコンパイルする
                if(class_file_path_stat.st_mtime < source_path_stat.st_mtime) {
                    /// コンパイル ///
                    char command[PATH_MAX+128];

                    snprintf(command, PATH_MAX+128, "cclover2 %s/%s.clcl", cwd, class_name);

                    int rc = system(command);

                    /// 一応クラスファイルがあるかどうかチェックして、あるなら真を返します ///
                    if(rc == 0) {
                        snprintf(class_file_path, class_file_path_size, "%s/%s.oclcl", cwd, class_name);

                        if(access(class_file_path, F_OK) == 0) {
                            return TRUE;
                        }
                    }
                }
                else {
                    return TRUE;
                }
            }
            else if(access(source_path2, F_OK) == 0) {
                struct stat source_path_stat;

                if(stat(source_path, &source_path_stat) != 0) {
                    return FALSE;
                }

                if(class_file_path_stat.st_mtime < source_path_stat.st_mtime) {
                    /// コンパイル ///
                    char command[PATH_MAX+128];

                    char* source_dir = dirname(gCompilingSourceFileName);

                    snprintf(command, PATH_MAX+128, "cclover2 %s/%s.clcl", source_dir, class_name);

                    int rc = system(command);

                    /// 一応クラスファイルがあるかどうかチェックして、あるなら真を返します ///
                    if(rc == 0) {
                        snprintf(class_file_path, class_file_path_size, "%s/%s.oclcl", cwd, class_name);

                        if(access(class_file_path, F_OK) == 0) {
                            return TRUE;
                        }
                    }
                }
                else {
                    return TRUE;
                }
            }
            else {
                return TRUE;
            }
        }
        else {
            /// クラスファイルが無いならクラス名.clclファイルのコンパイルを試してみます ///
            char path[PATH_MAX];

            snprintf(path, PATH_MAX, "%s/%s.clcl", cwd, class_name);

            if(access(path, F_OK) == 0) {           // クラス名.clclファイルはありますか？
                /// コンパイル ///
                char command[PATH_MAX+128];

                snprintf(command, PATH_MAX+128, "cclover2 %s/%s.clcl", cwd, class_name);

                int rc = system(command);

                /// 一応クラスファイルがあるかどうかチェックして、あるなら真を返します ///
                if(rc == 0) {
                    snprintf(class_file_path, class_file_path_size, "%s/%s.oclcl", cwd, class_name);

                    if(access(class_file_path, F_OK) == 0) {
                        return TRUE;
                    }
                }
            }

            /// ソースファイルのディレクトリも一応探しておく ///
            if(strstr(gCompilingSourceFileName, "/")) {  // gCompilingSourceFileNameは絶対パスじゃないこともある
                char source_path[PATH_MAX];

                char* p = gCompilingSourceFileName + strlen(gCompilingSourceFileName);

                while(*p != '/') {
                    p--;
                }

                memcpy(source_path, gCompilingSourceFileName, p - gCompilingSourceFileName);
                source_path[p - gCompilingSourceFileName] = '\0';

                snprintf(path, PATH_MAX, "%s/%s.clcl", source_path, class_name);

                /// ありゃ、dirname使えばいいのかな、、

                if(access(path, F_OK) == 0) {
                    /// コンパイル ///
                    char command[PATH_MAX+128];

                    snprintf(command, PATH_MAX+128, "cclover2 %s/%s.clcl", source_path, class_name);

                    int rc = system(command);

                    /// 一応クラスファイルがあるかどうかチェックして、あるなら真を返します ///
                    if(rc == 0) {
                        snprintf(class_file_path, class_file_path_size, "%s/%s.oclcl", cwd, class_name);

                        if(access(class_file_path, F_OK) == 0) {
                            return TRUE;
                        }
                    }
                }
            }
        }
    }

    return FALSE; // 失敗。クラスファイルは見つかりませんね、、、。
}

sCLClass* load_class_on_compile_time(char* class_name)
{
    sCLClass* klass = get_class(class_name);
    if(klass != NULL) {
        remove_class(class_name);
    }

    char class_file_name[PATH_MAX+1];
    if(!search_for_class_file_on_compile_time(class_name, class_file_name, PATH_MAX)) {
        return NULL;
    }

    return load_class_from_class_file(class_name, class_file_name);
}

static BOOL check_method_params(sCLMethod* method, sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, sNodeType* left_generics_type, sNodeType* right_generics_type, sNodeType* left_method_generics, sNodeType* right_method_generics, sNodeType* method_generics_types, BOOL lazy_lambda_compile)
{
    if(strcmp(METHOD_NAME2(klass, method), method_name) == 0) 
    {
        if((search_for_class_method && (method->mFlags & METHOD_FLAGS_CLASS_METHOD)) || (!search_for_class_method && !(method->mFlags & METHOD_FLAGS_CLASS_METHOD))) 
        {
            if(num_params == method->mNumParams) {
                int j;

                for(j=0; j<num_params; j++ ) {
                    sNodeType* param = create_node_type_from_cl_type(method->mParams[j].mType, klass);

                    if(lazy_lambda_compile && j == num_params-1) {
                        if(!type_identify_with_class_name(param, "lambda")) {
                            return FALSE;
                        }
                    }
                    else {
                        if(!substitution_posibility(param, param_types[j], left_generics_type, right_generics_type, left_method_generics, right_method_generics)) 
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

int search_for_method(sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, int start_point, sNodeType* left_generics_type, sNodeType* right_generics_type, sNodeType* right_method_generics, sNodeType** result_type, BOOL lazy_lambda_compile, BOOL lazy_lambda_compile2, sNodeType** method_generics_types)
{
    int i;
    if(*method_generics_types == NULL) {
        *method_generics_types = alloc_node_type();
    }

    if(start_point < klass->mNumMethods) {
        for(i=start_point; i>=0; i--) {           // search for the method in reverse order because we want to get last defined method
            sCLMethod* method = klass->mMethods + i;

            sNodeType* left_method_generics = get_method_genercs_from_method(klass, method);

            if(lazy_lambda_compile2) {
                right_method_generics = *method_generics_types;
            }

            if(check_method_params(method, klass, method_name, param_types, num_params, search_for_class_method, left_generics_type, right_generics_type, left_method_generics, right_method_generics, *method_generics_types, lazy_lambda_compile))
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

BOOL method_name_existance(sCLClass* klass, char* method_name)
{
    int i;
    for(i=0; i<klass->mNumMethods; i++) {
        sCLMethod* method = klass->mMethods + i;

        if(strcmp(METHOD_NAME2(klass, method), method_name) == 0) {
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

BOOL check_implemented_methods_for_interface(sCLClass* left_class, sCLClass* right_class)
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
                return FALSE;
            }
        }
    }

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// write class to a class file 
////////////////////////////////////////////////////////////////////////////////

static void append_const_to_buffer(sBuf* buf, sConst* constant, sCLClass* klass)
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

static void write_class_to_buffer(sCLClass* klass, sBuf* buf)
{
    sBuf_append_int(buf, klass->mNumGenerics);
    int i;
    for(i=0; i<klass->mNumGenerics; i++ ) {
        sBuf_append_int(buf, klass->mGenericsParamTypeOffsets[i]);
    }
    sBuf_append_int(buf, klass->mGenericsParamClassNum);
    sBuf_append_int(buf, klass->mMethodGenericsParamClassNum);
    sBuf_append_long(buf, klass->mFlags);
    append_const_to_buffer(buf, &klass->mConst,klass);
    sBuf_append_int(buf, klass->mClassNameOffset);
    append_methods_to_buffer(buf, klass->mMethods, klass, klass->mNumMethods);
    append_fields_to_buffer(buf, klass->mFields, klass->mNumFields);
    append_fields_to_buffer(buf, klass->mClassFields, klass->mNumClassFields);
    sBuf_append_int(buf, klass->mClassInitializeMethodIndex);
    sBuf_append_int(buf, klass->mClassFinalizeMethodIndex);
    sBuf_append_int(buf, klass->mFinalizeMethodIndex);
    sBuf_append_int(buf, klass->mCallingClassMethodIndex);
    sBuf_append_int(buf, klass->mCallingMethodIndex);

    sBuf_append_int(buf, klass->mNumTypedef);
    for(i=0; i<klass->mNumTypedef; i++) {
        sBuf_append_int(buf, klass->mTypedefClassName1Offsets[i]);
        sBuf_append_int(buf, klass->mTypedefClassName2Offsets[i]);
    }
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

static void load_fundamental_classes_on_compile_time()
{
    load_class_on_compile_time("PcreOVec");
    load_class_on_compile_time("System");
    load_class_on_compile_time("Global");

    load_class_on_compile_time("Buffer");
    load_class_on_compile_time("String");

    load_class_on_compile_time("Exception");

    load_class_on_compile_time("Object");

    load_class_on_compile_time("Byte");
    load_class_on_compile_time("UByte");
    load_class_on_compile_time("Short");
    load_class_on_compile_time("UShort");
    load_class_on_compile_time("Integer");
    load_class_on_compile_time("UInteger");
    load_class_on_compile_time("Long");
    load_class_on_compile_time("ULong");

    load_class_on_compile_time("Float");
    load_class_on_compile_time("Double");

    load_class_on_compile_time("Pointer");
    load_class_on_compile_time("Char");
    load_class_on_compile_time("Bool");

    load_class_on_compile_time("Array");
    load_class_on_compile_time("EqualableArray");
    load_class_on_compile_time("SortableArray");

    load_class_on_compile_time("IHashKey");
    load_class_on_compile_time("IEqualable");
    load_class_on_compile_time("ISortable");

    load_class_on_compile_time("HashItem");
    load_class_on_compile_time("Hash");

    load_class_on_compile_time("ListItem");
    load_class_on_compile_time("List");
    load_class_on_compile_time("SortableList");
    load_class_on_compile_time("EqualableList");

    load_class_on_compile_time("Tuple1");
    load_class_on_compile_time("Tuple2");
    load_class_on_compile_time("Tuple3");
    load_class_on_compile_time("Tuple4");
    load_class_on_compile_time("Tuple5");
    load_class_on_compile_time("Tuple6");
    load_class_on_compile_time("Tuple7");
    load_class_on_compile_time("Tuple8");
    load_class_on_compile_time("Tuple9");
    load_class_on_compile_time("Tuple10");

    load_class_on_compile_time("File");
    load_class_on_compile_time("Path");
    load_class_on_compile_time("tm");
    load_class_on_compile_time("stat");
    load_class_on_compile_time("Directory");
    load_class_on_compile_time("termios");
    load_class_on_compile_time("Job");
    load_class_on_compile_time("Command");

    load_class_on_compile_time("Clover");
}

void class_init_on_compile_time()
{
    load_fundamental_classes_on_compile_time();
    set_boxing_and_unboxing_classes();
}

sCLClass* get_class_with_load_on_compile_time(char* class_name)
{
    sCLClass* result = get_class(class_name);
    
    if(result == NULL) {
        result = load_class_on_compile_time(class_name);
    }

    return result;
}
