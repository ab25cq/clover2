#include "common.h"

static void node_type_to_cl_type(sNodeType* node_type, ALLOC sCLType** cl_type, sCLClass* klass)
{
    *cl_type = create_cl_type(node_type->mClass, klass);

    (*cl_type)->mNumGenericsTypes = node_type->mNumGenericsTypes;

    int i;
    for(i=0; i<node_type->mNumGenericsTypes; i++) {
        node_type_to_cl_type(node_type->mGenericsTypes[i], ALLOC &(*cl_type)->mGenericsTypes[i], klass);
    }
}

static void parser_param_to_cl_param(sParserParam* param, sCLParam* type, sCLClass* klass)
{
    type->mNameOffset = append_str_to_constant_pool(&klass->mConst, param->mName, FALSE);
    node_type_to_cl_type(param->mType, ALLOC &type->mType, klass);
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

BOOL add_method_to_class(sCLClass* klass, char* method_name, sParserParam* params, int num_params, sNodeType* result_type, BOOL native_, BOOL static_)
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

    int i;
    for(i=0; i<num_params; i++) {
        sParserParam* param = params + i;

        parser_param_to_cl_param(param, klass->mMethods[num_methods].mParams + i, klass);
    }

    klass->mMethods[num_methods].mNumParams = num_params;

    char method_path[METHOD_PATH_MAX+1];
    create_method_path(method_path, METHOD_PATH_MAX, &klass->mMethods[num_methods], klass);

    klass->mMethods[num_methods].mPathOffset = append_str_to_constant_pool(&klass->mConst, method_path, FALSE);

    node_type_to_cl_type(result_type, ALLOC &klass->mMethods[num_methods].mResultType, klass);

    klass->mNumMethods++;
    
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

    node_type_to_cl_type(result_type, ALLOC &klass->mFields[num_fields].mResultType, klass);

    klass->mNumFields++;
    
    return TRUE;
}

BOOL add_class_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, sNodeType* result_type)
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

    node_type_to_cl_type(result_type, ALLOC &klass->mClassFields[num_fields].mResultType, klass);

    klass->mNumClassFields++;
    
    return TRUE;
}

void add_code_to_method(sCLMethod* method, sByteCode* code, int var_num)
{
    method->uCode.mByteCodes = *code;
    method->mVarNum = var_num;
}

static BOOL check_method_params(sCLMethod* method, sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, sNodeType* generics_type)
{
    if(strcmp(METHOD_NAME2(klass, method), method_name) == 0) 
    {
        if((search_for_class_method && (method->mFlags & METHOD_FLAGS_CLASS_METHOD)) || (!search_for_class_method && !(method->mFlags & METHOD_FLAGS_CLASS_METHOD))) 
        {
            if(num_params == method->mNumParams) {
                int j, k;

                for(j=0; j<num_params; j++ ) {
                    sNodeType* param;
                    sNodeType* solved_param;

                    param = create_node_type_from_cl_type(method->mParams[j].mType, klass);

                    if(!solve_generics_types_for_node_type(param, ALLOC &solved_param, generics_type)) 
                    {
                        return FALSE;
                    }
                    if(!substitution_posibility(solved_param, param_types[j])) {
                        return FALSE;
                    }
                }
                
                return TRUE;
            }
        }
    }

    return FALSE;
}

int search_for_method(sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, int start_point, sNodeType* generics_type, sNodeType** result_type)
{
    int i;

    if(start_point < klass->mNumMethods) {
        for(i=start_point; i>=0; i--) {           // search for the method in reverse order because we want to get last defined method
            sCLMethod* method;
            
            method = klass->mMethods + i;

            if(check_method_params(method, klass, method_name, param_types, num_params, search_for_class_method, generics_type))
            {
                sNodeType* result_type2;
                
                result_type2 = ALLOC create_node_type_from_cl_type(method->mResultType, klass);

                if(!solve_generics_types_for_node_type(result_type2, result_type, generics_type))
                {
                    return -1;
                }

                return i;
            }
        }
    }

    return -1;
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

/// write class to a class file ///

static void append_const_to_buffer(sBuf* buf, sConst* constant)
{
    sBuf_append_int(buf, constant->mLen);
    sBuf_append(buf, constant->mConst, sizeof(char)*constant->mLen);
}

static void append_cl_type_to_buffer(sBuf* buf, sCLType* cl_type)
{
    sBuf_append_int(buf, cl_type->mClassNameOffset);
    sBuf_append_int(buf, cl_type->mNumGenericsTypes);
    int i;
    for(i=0; i<cl_type->mNumGenericsTypes; i++) {
        append_cl_type_to_buffer(buf, cl_type->mGenericsTypes[i]);
    }
}

static void append_byte_codes_to_buffer(sBuf* buf, sByteCode* code)
{
    sBuf_append_int(buf, code->mLen);
    sBuf_append(buf, code->mCodes, code->mLen);
}

static void append_methods_to_buffer(sBuf* buf, sCLMethod* methods, int num_methods)
{
    sBuf_append_int(buf, num_methods);
    int i;
    for(i=0; i<num_methods; i++) {
        sCLMethod* method = methods + i;

        sBuf_append_long(buf, method->mFlags);
        sBuf_append_int(buf, method->mNameOffset);
        sBuf_append_int(buf, method->mPathOffset);

        sBuf_append_int(buf, method->mNumParams);

        int j;
        for(j=0; j<method->mNumParams; j++) {
            sCLParam* param = method->mParams + j;

            sBuf_append_int(buf, param->mNameOffset);
            append_cl_type_to_buffer(buf, param->mType);
        }

        append_cl_type_to_buffer(buf, method->mResultType);

        if(!(method->mFlags & METHOD_FLAGS_NATIVE)) {
            append_byte_codes_to_buffer(buf, &method->uCode.mByteCodes);
            sBuf_append_int(buf, method->mVarNum);
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
    }
}

static void write_class_to_buffer(sCLClass* klass, sBuf* buf)
{
    sBuf_append_int(buf, klass->mVersion);
    sBuf_append_int(buf, klass->mGenericsParamClassNum);
    sBuf_append_long(buf, klass->mFlags);
    append_const_to_buffer(buf, &klass->mConst);
    sBuf_append_int(buf, klass->mClassNameOffset);
    append_methods_to_buffer(buf, klass->mMethods, klass->mNumMethods);
    append_fields_to_buffer(buf, klass->mFields, klass->mNumFields);
    append_fields_to_buffer(buf, klass->mClassFields, klass->mNumClassFields);
    sBuf_append_int(buf, klass->mInitializeMethodIndex);
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
    if(klass->mVersion == 1) {
        snprintf(file_name, PATH_MAX, "%s.clcl", CLASS_NAME(klass));
    }
    else {
        snprintf(file_name, PATH_MAX, "%s@%d.clcl", CLASS_NAME(klass), klass->mVersion);
    }

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

void set_method_index_to_class(sCLClass* klass)
{
    klass->mInitializeMethodIndex = -1;

    int i;
    for(i=klass->mNumMethods-1; i>=0; i--) {
        sCLMethod* method = klass->mMethods + i;

        if((method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
            && strcmp(CONS_str(&klass->mConst, method->mNameOffset), "initialize") == 0
            && method->mNumParams == 0)
        {
            klass->mInitializeMethodIndex = i;
        }
    }
}

BOOL write_all_modified_classes()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        sCLClass* klass = p->mItem;

        if(klass->mFlags & CLASS_FLAGS_MODIFIED) {
            set_method_index_to_class(klass);
            if(!write_class_to_class_file(klass)) {
                fprintf(stderr, "Clover failed to write class file(%s)\n", CLASS_NAME(klass));
                return FALSE;
            }
        }

        p = p->mNextClass;
    }

    return TRUE;
}

