#include "common.h"

BOOL js(sByteCode* code, sConst* constant, int var_num, int param_num, sCLClass* klass, sVMInfo* info);
void load_js_class(char* class_name, sVMInfo* info);

BOOL js_class_compiler(char* sname) 
{
    char* class_name = sname;
    char* p = sname + strlen(sname);

    while(p >= sname) {
        if(*p == '.') {
            break;
        }
        else {
            p--;
        }
    }

    if(p != sname) {
        *p = '\0';
    }

    sCLClass* klass = get_class_with_load(class_name, TRUE);

    if(klass == NULL) {
        fprintf(stderr, "can't load classs(%s)\n", class_name);
        return FALSE;
    }

    if(!(klass->mFlags & CLASS_FLAGS_JS)) {
        fprintf(stderr, "can't compile none java script class(%s)\n", class_name);
        return FALSE;
    }

    sBuf output;
    sBuf_init(&output);

    sVMInfo info;
    memset(&info, 0, sizeof(info));

    info.running_class_name = MSTRDUP(class_name);

    sConst js_const;

    sConst_init(&js_const);

    info.js_source = &output;
    info.js_const = &js_const;

    sBuf js_class_source;
    sBuf_init(&js_class_source);

    info.js_class_source = &js_class_source;
    info.js_compiling_class_source = TRUE;

    if(klass->mFlags & CLASS_FLAGS_NATIVE) {
        char line[1024];

        int i;
        for(i=0; i<klass->mNumMethods; i++) {
            sCLMethod* method = klass->mMethods + i;

            info.running_method_name = MSTRDUP(METHOD_NAME2(klass, method));

            if((method->mFlags & METHOD_FLAGS_PURE_NATIVE) && method->mNativeCodes == NULL)
            {
            }
            else if((method->mFlags & METHOD_FLAGS_NATIVE) || (method->mFlags & METHOD_FLAGS_PURE_NATIVE)) 
            {
                if(method->mFlags & METHOD_FLAGS_PURE_NATIVE) 
                {
                    snprintf(line ,1024, "%s.prototype.%s = function (", class_name, METHOD_NAME2(klass, method));
                }
                else {
                    snprintf(line ,1024, "%s.prototype.%s = function (", class_name, CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset));
                }

                sBuf_append_str(info.js_source, line);

                int j;
                for(j=0; j<method->mNumParams; j++) {
                    sCLParam* param = method->mParams + j;

                    char* field_name = CONS_str(&klass->mConst, param->mNameOffset);

                    sBuf_append_str(info.js_source, field_name);

                    if(j < method->mNumParams-1) {
                        sBuf_append_str(info.js_source, ",");
                    }
                }
                sBuf_append_str(info.js_source, ")");

                sBuf_append_str(info.js_source, "\n");
                
                sBuf_append(info.js_source, method->mNativeCodes->mBuf, method->mNativeCodes->mLen);
                sBuf_append_str(info.js_source, "\n");

                if(method->mFlags & METHOD_FLAGS_PURE_NATIVE) 
                {
                    snprintf(line ,1024, "%s.prototype.%s = function (", class_name, CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset));

                    sBuf_append_str(info.js_source, line);

                    int j;
                    for(j=0; j<method->mNumParams; j++) {
                        sCLParam* param = method->mParams + j;

                        char* field_name = CONS_str(&klass->mConst, param->mNameOffset);

                        sBuf_append_str(info.js_source, field_name);

                        if(j < method->mNumParams-1) {
                            sBuf_append_str(info.js_source, ",");
                        }
                    }
                    sBuf_append_str(info.js_source, ")");

                    sBuf_append_str(info.js_source, "\n");
                    
                    sBuf_append(info.js_source, method->mNativeCodes->mBuf, method->mNativeCodes->mLen);
                    sBuf_append_str(info.js_source, "\n");
                }
            }
            else {
                if(method->mFlags & METHOD_FLAGS_CLASS_METHOD) 
                {
                    sBuf_append_str(info.js_source, "static ");
                }

                sByteCode* code = &method->mByteCodes;
                sConst* constant = &klass->mConst;
                int var_num = method->mVarNum;
                int param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);

                snprintf(line ,1024, "%s.prototype.%s = function (clover2Stack, clover2StackIndex, exception) {", class_name, CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset));
                sBuf_append_str(info.js_source, line);
                sBuf_append_str(info.js_source, "\n");

                if(!js(code, constant, var_num, param_num, klass, &info)) {
                    MFREE(info.running_class_name);
                    MFREE(info.running_method_name);
                    MFREE(output.mBuf);
                    sConst_free(&js_const);
                    MFREE(js_class_source.mBuf);
                    return FALSE;
                }

                snprintf(line ,1024, "}");
                sBuf_append_str(info.js_source, line);
                sBuf_append_str(info.js_source, "\n");
            }

            MFREE(info.running_method_name);
        }
        sBuf_append_str(info.js_source, "\n");
    }
    else {
        char line[1024];

        snprintf(line ,1024, "class %s {", class_name);
        sBuf_append_str(info.js_source, line);
        sBuf_append_str(info.js_source, "\n");

        snprintf(line ,1024, "constructor() {");
        sBuf_append_str(info.js_source, line);
        sBuf_append_str(info.js_source, "\n");

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sCLField* field = klass->mFields + i;
            char* field_name = CONS_str(&klass->mConst, field->mNameOffset);

            snprintf(line, 1024, "this.%s = null;", field_name);

            sBuf_append_str(info.js_source, line);
            sBuf_append_str(info.js_source, "\n");
        }

        sBuf_append_str(info.js_source, "}");
        sBuf_append_str(info.js_source, "\n");

        for(i=0; i<klass->mNumMethods; i++) {
            sCLMethod* method = klass->mMethods + i;

            info.running_method_name = MSTRDUP(METHOD_NAME2(klass, method));

            if((method->mFlags & METHOD_FLAGS_PURE_NATIVE) && method->mNativeCodes == NULL)
            {
            }
            else if((method->mFlags & METHOD_FLAGS_NATIVE) || (method->mFlags & METHOD_FLAGS_PURE_NATIVE)) 
            {
                if(method->mFlags & METHOD_FLAGS_CLASS_METHOD)
                {
                    sBuf_append_str(info.js_source, "static ");
                }

                if(method->mFlags & METHOD_FLAGS_PURE_NATIVE) 
                {
                    snprintf(line ,1024, "%s(", METHOD_NAME2(klass, method));
                }
                else {
                    snprintf(line ,1024, "%s(", CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset));
                }

                sBuf_append_str(info.js_source, line);

                int j;
                for(j=0; j<method->mNumParams; j++) {
                    sCLParam* param = method->mParams + j;

                    char* field_name = CONS_str(&klass->mConst, param->mNameOffset);

                    sBuf_append_str(info.js_source, field_name);

                    if(j < method->mNumParams-1) {
                        sBuf_append_str(info.js_source, ",");
                    }
                }
                sBuf_append_str(info.js_source, ")");

                sBuf_append_str(info.js_source, "\n");
                
                sBuf_append(info.js_source, method->mNativeCodes->mBuf, method->mNativeCodes->mLen);
                sBuf_append_str(info.js_source, "\n");

                if(method->mFlags & METHOD_FLAGS_PURE_NATIVE) 
                {
                    if(method->mFlags & METHOD_FLAGS_CLASS_METHOD)
                    {
                        sBuf_append_str(info.js_source, "static ");
                    }

                    snprintf(line ,1024, "%s(", CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset));

                    sBuf_append_str(info.js_source, line);

                    int j;
                    for(j=0; j<method->mNumParams; j++) {
                        sCLParam* param = method->mParams + j;

                        char* field_name = CONS_str(&klass->mConst, param->mNameOffset);

                        sBuf_append_str(info.js_source, field_name);

                        if(j < method->mNumParams-1) {
                            sBuf_append_str(info.js_source, ",");
                        }
                    }
                    sBuf_append_str(info.js_source, ")");

                    sBuf_append_str(info.js_source, "\n");
                    
                    sBuf_append(info.js_source, method->mNativeCodes->mBuf, method->mNativeCodes->mLen);
                    sBuf_append_str(info.js_source, "\n");
                }
            }
            else {
                if(method->mFlags & METHOD_FLAGS_CLASS_METHOD) {
                    sBuf_append_str(info.js_source, "static ");
                }

                sByteCode* code = &method->mByteCodes;
                sConst* constant = &klass->mConst;
                int var_num = method->mVarNum;
                int param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);

                snprintf(line ,1024, "%s(clover2Stack, clover2StackIndex, exception){", CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset));
                sBuf_append_str(info.js_source, line);
                sBuf_append_str(info.js_source, "\n");

                if(!js(code, constant, var_num, param_num, klass, &info)) {
                    MFREE(info.running_class_name);
                    MFREE(info.running_method_name);
                    MFREE(output.mBuf);
                    sConst_free(&js_const);
                    MFREE(js_class_source.mBuf);
                    return FALSE;
                }


                snprintf(line ,1024, "}");
                sBuf_append_str(info.js_source, line);
                sBuf_append_str(info.js_source, "\n");

                /// normal name ///
                if(strcmp(METHOD_NAME2(klass, method), "constructor") != 0) {
                    if(method->mFlags & METHOD_FLAGS_CLASS_METHOD) {
                        sBuf_append_str(info.js_source, "static ");
                    }

                    snprintf(line ,1024, "%s(clover2Stack, clover2StackIndex, exception){", CONS_str(&klass->mConst, method->mMethodNameAndParamsOffset));
                    sBuf_append_str(info.js_source, line);
                    sBuf_append_str(info.js_source, "\n");

                    if(!js(code, constant, var_num, param_num, klass, &info)) {
                        MFREE(info.running_class_name);
                        MFREE(info.running_method_name);
                        MFREE(output.mBuf);
                        sConst_free(&js_const);
                        MFREE(js_class_source.mBuf);
                        return FALSE;
                    }
                    snprintf(line, 1024, "return clover2Stack[clover2StackIndex-1];");

                    sBuf_append_str(info.js_source, line);
                    sBuf_append_str(info.js_source, "\n");

                    snprintf(line ,1024, "}");
                    sBuf_append_str(info.js_source, line);
                    sBuf_append_str(info.js_source, "\n");
                }
            }

            MFREE(info.running_method_name);
        }

        snprintf(line ,1024, "}");
        sBuf_append_str(info.js_source, line);
        sBuf_append_str(info.js_source, "\n");
    }

    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.js", class_name);

    FILE* f2 = fopen(path, "w");
    fprintf(f2, "%s", js_class_source.mBuf);
    fprintf(f2, "%s", output.mBuf);
    fclose(f2);

    MFREE(info.running_class_name);
    MFREE(output.mBuf);
    sConst_free(&js_const);
    MFREE(js_class_source.mBuf);

    return TRUE;
}

BOOL js_compiler(char* fname) 
{
    FILE* f = fopen(fname, "r");

    if(f == NULL) {
        fprintf(stderr, "%s doesn't exist(1)\n", fname);
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

    sBuf output;
    sBuf_init(&output);

    sVMInfo info;
    memset(&info, 0, sizeof(info));

    create_global_stack_and_append_it_to_stack_list(&info);

    info.running_class_name = MSTRDUP("none");
    info.running_method_name = MSTRDUP(fname);

    sConst js_const;

    sConst_init(&js_const);

    info.js_source = &output;
    info.js_const = &js_const;

    char line[1024];
    snprintf(line, 1024, "var clover2Stack = new Array(256); var clover2StackIndex = 0;");

    sBuf_append_str(info.js_source, line);
    sBuf_append_str(info.js_source, "\n");

    sBuf js_class_source;
    sBuf_init(&js_class_source);

    info.js_class_source = &js_class_source;
    info.js_compiling_class_source = FALSE;

    snprintf(line, 1024, "var exception = new Object()");

    sBuf_append_str(info.js_source, line);
    sBuf_append_str(info.js_source, "\n");

    snprintf(line, 1024, "function typeOf(obj) { return Object.prototype.toString.call(obj).slice(8, -1).toLowerCase(); }");
    sBuf_append_str(info.js_source, line);
    sBuf_append_str(info.js_source, "\n");

    snprintf(line, 1024, "function typeOfNativeObject(obj) { var object_type = typeOf(obj); return object_type == 'array' || object_type == 'number' || object_type == 'string' || object_type == 'map'; }");

    sBuf_append_str(info.js_source, line);
    sBuf_append_str(info.js_source, "\n");

    int param_num = 0;

    if(!js(&code, &constant, var_num, param_num, NULL, &info)) {
        MFREE(info.running_class_name);
        MFREE(info.running_method_name);
        fclose(f);
        MFREE(code_contents);
        MFREE(code_contents2);
        MFREE(output.mBuf);
        sByteCode_free(&code);
        sConst_free(&constant);
        sConst_free(&js_const);
        MFREE(js_class_source.mBuf);
        return FALSE;
    }

    char* p = fname + strlen(fname);

    while(p >= fname) {
        if(*p == '.') {
            break;
        }
        else {
            p--;
        }
    }

    if(p != fname) {
        *p = '\0';
    }

    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s.js", fname);

    FILE* f2 = fopen(path, "w");
    fprintf(f2, "%s", js_class_source.mBuf);
    fprintf(f2, "%s", output.mBuf);
    fclose(f2);

    fclose(f);

    MFREE(code_contents);
    MFREE(code_contents2);
    sByteCode_free(&code);
    sConst_free(&constant);
    MFREE(output.mBuf);
    MFREE(info.running_class_name);
    MFREE(info.running_method_name);
    sConst_free(&js_const);
    MFREE(js_class_source.mBuf);

    return TRUE;
}

static BOOL search_for_js_class_file(char* class_name, char* class_file_name, size_t class_file_name_size)
{
    /// current working directory ///
    char* cwd = getenv("PWD");

    if(cwd) {
        snprintf(class_file_name, class_file_name_size, "%s/%s.js", cwd, class_name);

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    /// home directory ///
    char* home = getenv("HOME");

    if(home) {
        snprintf(class_file_name, class_file_name_size, "%s/.clover2/%s.js", home, class_name);

        if(access(class_file_name, F_OK) == 0) {
            return TRUE;
        }
    }

    /// system shared directory ///
    snprintf(class_file_name, class_file_name_size, "%s/share/clover2/%s.js", PREFIX, class_name);

    if(access(class_file_name, F_OK) == 0) {
        return TRUE;
    }

    return FALSE;
}

void load_js_class(char* class_name, sVMInfo* info)
{
    sCLClass* klass = get_class_with_load_and_initialize(class_name, TRUE);

    if(klass == NULL) {
        fprintf(stderr, "can't load %s\n", class_name);
        exit(2);
    }

    if(!info->js_compiling_class_source) {
        char class_file_name[PATH_MAX];

        if(!search_for_js_class_file(class_name, class_file_name, PATH_MAX))
        {
            fprintf(stderr, "can't load %s\n", class_name);
            exit(2);
        }

        if(!klass->mAlreadyLoadedJSClass) 
        {
            sBuf source_file;
            sBuf_init(&source_file);

            FILE* f = fopen(class_file_name, "r");

            while(!feof(f)) {
                char buf[BUFSIZ];

                int size = fread(buf, 1, BUFSIZ, f);

                if(size < 0) {
                    fprintf(stderr, "invalid file\n");
                    exit(1);
                }

                sBuf_append(&source_file, buf, size);
            }

            fclose(f);

            sBuf_append_str(info->js_class_source, source_file.mBuf);

            MFREE(source_file.mBuf);

            klass->mAlreadyLoadedJSClass = TRUE;
        }
    }
}

static void load_js_fundamental_classes(sVMInfo* info)
{
    load_js_class("Number", info);
    load_js_class("Bool", info);
    load_js_class("String", info);
    load_js_class("Lambda", info);
    load_js_class("Map", info);
    load_js_class("Tuple1", info);
    load_js_class("Tuple2", info);
    load_js_class("Tuple3", info);
    load_js_class("Tuple4", info);
    load_js_class("Tuple5", info);
    load_js_class("Tuple6", info);
    load_js_class("Tuple7", info);
    load_js_class("Tuple8", info);
    load_js_class("Tuple9", info);
    load_js_class("System", info);
    load_js_class("Clover", info);
    load_js_class("Exception", info);
    load_js_class("Array", info);
}


int create_js_int_value(int value, sVMInfo* info)
{
    char buf[1024];
    snprintf(buf, 1024, "%d", value);

    return sConst_append(info->js_const, buf, strlen(buf)+1, FALSE);
}

int create_js_null_value(sVMInfo* info)
{
    char buf[1024];
    snprintf(buf, 1024, "null");

    return sConst_append(info->js_const, buf, strlen(buf)+1, FALSE);
}

int create_js_string_value(char* value, sVMInfo* info)
{
    char buf[1024];
    snprintf(buf, 1024, "\"%s\"", value);

    return sConst_append(info->js_const, buf, strlen(buf)+1, FALSE);
}

int create_js_value_from_souce(char* source, sVMInfo* info)
{
    return sConst_append(info->js_const, source, strlen(source)+1, FALSE);
}

void js_err_msg(sVMInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    fprintf(stderr, "%s %d %s %d: %s", info->sname, info->sline, info->sname2, info->sline2, msg2);
}

void js_dec_stack_ptr(int index, sVMInfo* info)
{
    char line[1024];

    snprintf(line, 1024, "clover2StackIndex -= %d", index);

    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");
}

char* get_value(int offset, sVMInfo* info)
{
    return CONS_str(info->js_const, offset);
}



void print_inst(char* str, sVMInfo* info)
{
    char line[1024];

    snprintf(line, 1024, "console.log('%s');", str);

    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");
}

void show_js_stack(sVMInfo* info)
{
    char line[1024];

    snprintf(line, 1024, "console.log(clover2Stack); console.log(clover2StackIndex); console.log(lvar)");

    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");
}

static BOOL string_expression(char* str, int str_len, sBuf* buf, int* string_expression_offsets, char string_expression_object[STRING_EXPRESSION_MAX][128], int num_string_expression, int var_num, sVMInfo* info)
{
    int offset_before = 0;

    int i;
    for(i=0; i<num_string_expression; i++) {
        int offset = string_expression_offsets[i];

        sBuf_append(buf, str + offset_before, offset - offset_before);

        char* object = string_expression_object[i];

        char object_str[128];

        snprintf(object_str, 128, "${%s}", object);

        sBuf_append_str(buf, object_str);

        offset_before = offset;
    }

    sBuf_append(buf, str + offset_before, str_len - offset_before);

    return TRUE;
}


BOOL invoke_js_method(sCLClass* klass, BOOL native, sBuf* native_codes, BOOL class_method, BOOL result_type_is_bool, char* method_name_and_params, int num_params, BOOL pure_native, char* method_name, sVMInfo* info)
{
    char line[1024];

    if(native || pure_native)
    {
        if(class_method)
        {
            sBuf buf;
            sBuf_init(&buf);

            sBuf_append_str(&buf, CLASS_NAME(klass));
            sBuf_append_str(&buf, ".");

            if(pure_native) {
                sBuf_append_str(&buf, method_name);
                sBuf_append_str(&buf, "(");
            }
            else {
                sBuf_append_str(&buf, method_name_and_params);
                sBuf_append_str(&buf, "(");
            }

            int i = 0;
            for(i=0; i<num_params; i++)
            {
                snprintf(line, 1024, "clover2Stack[clover2StackIndex+%d]", -num_params + i);

                sBuf_append_str(&buf, line);

                if(i < num_params-1) {
                    sBuf_append_str(&buf, ",");
                }
            }

            sBuf_append_str(&buf, ")");

            snprintf(line, 1024, "tmp = %s; clover2StackIndex -= %d; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++", buf.mBuf, num_params);

            sBuf_append_str(info->js_source, line);
            sBuf_append_str(info->js_source, "\n");

            MFREE(buf.mBuf);
        }
        else {
            sBuf buf;
            sBuf_init(&buf);

            snprintf(line, 1024, "clover2Stack[clover2StackIndex-%d]", num_params+1);

            sBuf_append_str(&buf, line);

            sBuf_append_str(&buf, ".");

            if(pure_native) {
                sBuf_append_str(&buf, method_name);
                sBuf_append_str(&buf, "(");
            }
            else {
                sBuf_append_str(&buf, method_name_and_params);
                sBuf_append_str(&buf, "(");
            }

            int i = 0;
            for(i=0; i<num_params; i++)
            {
                snprintf(line, 1024, "clover2Stack[clover2StackIndex+%d]", -num_params + i);

                sBuf_append_str(&buf, line);

                if(i < num_params-1) {
                    sBuf_append_str(&buf, ",");
                }
            }

            sBuf_append_str(&buf, ")");

            snprintf(line, 1024, "tmp = %s; clover2StackIndex -= %d; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++", buf.mBuf, num_params+1);

            sBuf_append_str(info->js_source, line);
            sBuf_append_str(info->js_source, "\n");

            MFREE(buf.mBuf);
        }
    }
    else {
        if(class_method)
        {
            sBuf buf;
            sBuf_init(&buf);

            sBuf_append_str(&buf, CLASS_NAME(klass));
            sBuf_append_str(&buf, ".");

            sBuf_append_str(&buf, method_name_and_params);
            sBuf_append_str(&buf, "(clover2Stack, clover2StackIndex, exception);");

            snprintf(line, 1024, "tmp = %s; clover2StackIndex -= %d; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++", buf.mBuf, num_params);

            sBuf_append_str(info->js_source, line);
            sBuf_append_str(info->js_source, "\n");

            MFREE(buf.mBuf);
        }
        else {
            sBuf buf;
            sBuf_init(&buf);

            snprintf(line, 1024, "clover2Stack[clover2StackIndex-%d].", 1+num_params);

            sBuf_append_str(&buf, line);

            sBuf_append_str(&buf, method_name_and_params);
            sBuf_append_str(&buf, "(clover2Stack, clover2StackIndex, exception);");

            snprintf(line, 1024, "tmp = %s; clover2StackIndex -= %d; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++", buf.mBuf, num_params+1);

            sBuf_append_str(info->js_source, line);
            sBuf_append_str(info->js_source, "\n");

            MFREE(buf.mBuf);
        }
    }

    if(result_type_is_bool) {
        snprintf(line ,256, "if(clover2Stack[clover2StackIndex-1]) { clover2Stack[clover2StackIndex-1] = true; } else {clover2Stack[clover2StackIndex-1] = false; }");
        sBuf_append_str(info->js_source, line);
        sBuf_append_str(info->js_source, "\n");
    }

    return TRUE;
}

BOOL js(sByteCode* code, sConst* constant, int var_num, int param_num, sCLClass* klass, sVMInfo* info)
{
    reset_js_load_class();

    load_js_fundamental_classes(info);

    register char* pc = code->mCodes;

    int try_offset_before = 0;
    char** try_pc_before = NULL;
    sByteCode* try_code_before = NULL;

    char line[1024];
    snprintf(line, 1024, "var clover2GlobalStack = new Array(256); var clover2GlobalStackIndex = 0;");

    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");

    snprintf(line, 1024, "var tmp;");

    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");

    snprintf(line, 1024, "var lvar = clover2StackIndex-%d", param_num);
    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");

    snprintf(line, 1024, "clover2StackIndex = lvar + %d", var_num);
    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");

    while(pc - code->mCodes < code->mLen) {
        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);
//show_inst(inst);

        switch(inst) {
            case OP_POP: {
//print_inst("OP_POP", info);
                js_dec_stack_ptr(1, info);
                }
                break;

            case OP_STORE_TO_BUFFER: {
                snprintf(line, 1024, "var message = 'No support to OP_STORE_TO_BUFFER opecode on JS'; exception.data = new Exception().initializse(message)");
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");

                snprintf(line, 1024, "throw new Error('null message')");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_POP_N:
                {
//print_inst("OP_POP_N", info);
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    js_dec_stack_ptr(value, info);
                }
                break;

            case OP_DUPE: {
                snprintf(line, 1024, "clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex-1]; clover2StackIndex++;");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");

//show_js_stack(info);
                }
                break;

            case OP_REVERSE: {
//print_inst("OP_REVERSE", info);
                snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-1] = clover2Stack[clover2StackIndex-2]; clover2Stack[clover2Stack-2] = tmp;");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_RETURN: {
//print_inst("OP_RETURN", info);
                snprintf(line, 1024, "return clover2Stack[clover2StackIndex-1];");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_NOP:
//print_inst("OP_NOP", info);
                break;

            case OP_HEAD_OF_EXPRESSION:
//print_inst("OP_HEAD_OF_EXPRESSION", info);
                break;

            case OP_MARK_SOURCE_CODE_POSITION: {
//print_inst("OP_MARK_SOURCE_CODE_POSITION", info);
                unsigned int offset = *(unsigned int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                xstrncpy(info->sname, sname, 128);
                info->sline = sline;
                }
                break;

            case OP_MARK_SOURCE_CODE_POSITION2: {
//print_inst("OP_MARK_SOURCE_CODE_POSITION2", info);
                unsigned int offset = *(unsigned int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                xstrncpy(info->sname2, sname, 128);
                info->sline2 = sline;
                }
                break;

            case OP_LABEL: {
//print_inst("OP_LABEL", info);
                int offset = *(int*)pc;
                pc += sizeof(int);

                /// nothing to do, this opecode is for Just In Time Compile
                }
                break;

            case OP_SIGINT: {
//print_inst("OP_SIGINT", info);
                }
                break;

            case OP_STORE_VALUE_TO_GLOBAL: {
//print_inst("OP_STORE_VALUE_TO_GLOBAL", info);
                snprintf(line, 1024, "clover2GlobalStack[clover2GlobalStackIndex] = clover2Stack[clover2StackIndex-1]; clover2GlobalStackIndex++; clover2StackIndex--;");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_POP_VALUE_FROM_GLOBAL: {
//print_inst("OP_POP_VALUE_FROM_GLOBAL", info);
                int size = *(int*)pc;
                pc += sizeof(int);

                snprintf(line, 1024, "clover2Stack[clover2StackIndex] = clover2GlobalStack[clover2GlobalStackIndex-1]; clover2StackIndex++; clover2GlobalStackIndex--");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");

                char buf[1024];
                snprintf(buf, 1024, "clover2Stack[clover2StackIndex]");
                }
                break;

            case OP_LDCNULL:
//print_inst("OP_LDCNULL", info);
                snprintf(line, 1024, "clover2Stack[clover2StackIndex] = null; clover2StackIndex++;");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");

                break;

            case OP_LDCINT: 
                {
//print_inst("OP_LDCINT", info);
                    int value = *(int*)pc;
                    pc += sizeof(int);
                    
                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = %d; clover2StackIndex++", value);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                    }
                    break;

            case OP_IADD: 
                {
//print_inst("OP_IADD", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] + clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

//show_js_stack(info);
                }
                break;

            case OP_ISUB: 
                {
//print_inst("OP_ISUB", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] - clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IMULT: 
                {
//print_inst("OP_IMULT", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] * clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IDIV: 
                {
//print_inst("OP_IDIV", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] / clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IMOD: 
                {
//print_inst("OP_IMOD", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] %% clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_ILSHIFT: 
                {
//print_inst("OP_LSHIFT", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] << clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IRSHIFT: 
                {
//print_inst("OP_RSHIFT", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] >> clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IAND: 
                {
//print_inst("OP_IAND", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] & clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IOR: 
                {
//print_inst("OP_IOR", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] | clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IXOR: 
                {
//print_inst("OP_IXOR", info);
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] ^ clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_ICOMPLEMENT:
                {
//print_inst("OP_ICOMPLEMENT", info);
                    snprintf(line, 1024, "clover2Stack[clover2StackIndex-1] = ~clover2Stack[clover2StackIndex-1]");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_LOGICAL_DENIAL: 
                {
//print_inst("OP_LOGICAL_DENIAL", info);
                    snprintf(line, 1024, "clover2Stack[clover2StackIndex-1] = !clover2Stack[clover2StackIndex-1]");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_INVOKE_METHOD:
                {
//print_inst("OP_INVOKE_METHOD", info);
                    unsigned int offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    int method_index = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name, TRUE);

                    if(klass == NULL) {
                        js_err_msg(info, "class not found(%s)\n", class_name);
                        return FALSE;
                    }

                    if(method_index < 0 || method_index >= klass->mNumMethods) 
                    {
                        js_err_msg(info, "OP_INVOKE_METHOD: Method not found");
                        return FALSE;
                    }

                    sCLMethod method = klass->mMethods[method_index]; // struct copy for realloc

                    if(!(method.mFlags & METHOD_FLAGS_JS)) {
                        js_err_msg(info, "OP_INVOKE_METHOD: This method is not Java Script Method", info, info, info);
                        return FALSE;
                    }

                    char* result_class_name = CONS_str(&klass->mConst, method.mResultType->mClassNameOffset);

                    BOOL result_type_is_bool = strcmp(result_class_name, "bool") == 0;

                    if(!invoke_js_method(klass, method.mFlags & METHOD_FLAGS_NATIVE, method.mNativeCodes, method.mFlags & METHOD_FLAGS_CLASS_METHOD, result_type_is_bool, CONS_str(&klass->mConst, method.mMethodNameAndParamsOffset), method.mNumParams, method.mFlags & METHOD_FLAGS_PURE_NATIVE, METHOD_NAME2(klass, &method), info))
                    {
                        return FALSE;
                    }
                }
                break;

            case OP_INVOKE_VIRTUAL_METHOD:
                {
//print_inst("OP_INVOKE_VIRTUAL_METHOD", info);
                    int num_real_params = *(int*)pc;
                    pc += sizeof(int);

                    unsigned int offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    int class_method = *(int*)pc;
                    pc += sizeof(int);

                    int native_method = *(int*)pc;
                    pc += sizeof(int);

                    int pure_native_method = *(int*)pc;
                    pc += sizeof(int);

                    BOOL result_type_is_bool = *(int*)pc;
                    pc += sizeof(int);

                    unsigned int offset2 = *(unsigned int*)pc;
                    pc += sizeof(int);

                    unsigned int offset3 = *(unsigned int*)pc;
                    pc += sizeof(int);

                    sCLClass* klass;
                    if(class_method) {
                        char* class_name = CONS_str(constant, offset2);

                        klass = get_class_with_load_and_initialize(class_name, TRUE);
                        if(klass == NULL) {
                            js_err_msg(info, "Class not found(%s)", class_name);
                            return FALSE;
                        }
                    }
                    else {
                        klass = NULL;
                    }

                    char* method_name_and_params = CONS_str(constant, offset);
                    char* method_name = CONS_str(constant, offset3);

                    if(!invoke_js_method(klass, native_method, NULL, class_method, result_type_is_bool, method_name_and_params, num_real_params - (!class_method?1:0), pure_native_method, method_name, info)) 
                    {
                        return FALSE;
                    }
                }
                break;

            case OP_STORE_FIELD:
                {
//print_inst("OP_STORE_FIELD", info);
                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    unsigned int class_name_offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    int field_name_offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    char* field_name = CONS_str(constant, field_name_offset);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-1]; clover2Stack[clover2StackIndex-2].%s = tmp; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;", field_name);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_LOAD_FIELD:
                {
//print_inst("OP_LOAD_FIELD", info);
                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    int field_name_offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    char* field_name = CONS_str(constant, field_name_offset);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-1].%s; clover2StackIndex--; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;", field_name);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IEQ:
                {
//print_inst("OP_IEQ", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] == clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_INOTEQ:
                {
//print_inst("OP_IEQ", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] != clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_ILE:
                {
//print_inst("OP_ILE", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] < clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_ILEEQ:
                {
//print_inst("OP_ILE", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] <= clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IGT:
                {
//print_inst("OP_ILE", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] > clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_IGTEQ:
                {
//print_inst("OP_ILE", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] >= clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_OBJ_IDENTIFY:
                {
//print_inst("OP_IEQ", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] == clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_OBJ_IDENTIFY_NOT:
                {
//print_inst("OP_IEQ", info);
                    snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-2] != clover2Stack[clover2StackIndex-1]; clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_CREATE_STRING:
                {
//print_inst("OP_CREATE_STRING", info);
                    unsigned int offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    int num_string_expression = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    if(num_string_expression == 0) {
                        sBuf buf;
                        sBuf_init(&buf);

                        snprintf(line, 1024, "clover2Stack[clover2StackIndex] = \"");

                        sBuf_append_str(&buf, line);

                        sBuf_append_str(&buf, str);

                        snprintf(line, 1024,"\"; clover2StackIndex++");

                        sBuf_append_str(&buf, line);

                        sBuf_append_str(info->js_source, buf.mBuf);
                        sBuf_append_str(info->js_source, "\n");
                    }
                    else {
                        int string_expression_offsets[STRING_EXPRESSION_MAX];
                        char string_expression_object[STRING_EXPRESSION_MAX][128];

                        int i;
                        for(i=0; i<num_string_expression; i++) {
                            string_expression_offsets[i] = *(int*)pc;
                            pc += sizeof(int);

                            snprintf(string_expression_object[i], 128, "clover2Stack[clover2StackIndex+%d]", -num_string_expression + i);
                        }

                        sBuf buf;
                        sBuf_init(&buf);

                        if(!string_expression(str, strlen(str), &buf, string_expression_offsets, string_expression_object, num_string_expression, var_num, info))
                        {
                            js_err_msg(info, "invalid string expression\n");
                            return FALSE;
                        }

                        sBuf buf2;
                        sBuf_init(&buf2);

                        snprintf(line, 1024, "tmp = `");

                        sBuf_append_str(&buf2, line);

                        sBuf_append_str(&buf2, buf.mBuf);

                        snprintf(line, 1024,"`;");

                        sBuf_append_str(&buf2, line);

                        sBuf_append_str(info->js_source, buf2.mBuf);
                        sBuf_append_str(info->js_source, "\n");

                        snprintf(line, 1024, "clover2StackIndex -= %d", num_string_expression);
                        sBuf_append_str(info->js_source, line);
                        sBuf_append_str(info->js_source, "\n");

                        snprintf(line, 1024, "clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");

                        sBuf_append_str(info->js_source, line);
                        sBuf_append_str(info->js_source, "\n");

                        MFREE(buf2.mBuf);
                        MFREE(buf.mBuf);
                    }
                }
                break;

            case OP_CREATE_REGEX:
                {
//print_inst("OP_CREATE_REGEX", info);
                    unsigned int offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    BOOL global = *(int*)pc;
                    pc += sizeof(int);

                    BOOL ignore_case = *(int*)pc;
                    pc += sizeof(int);

                    BOOL multiline = *(int*)pc;
                    pc += sizeof(int);

                    BOOL extended = *(int*)pc;
                    pc += sizeof(int);

                    BOOL dotall = *(int*)pc;
                    pc += sizeof(int);

                    BOOL anchored = *(int*)pc;
                    pc += sizeof(int);

                    BOOL dollar_endonly = *(int*)pc;
                    pc += sizeof(int);

                    BOOL ungreedy = *(int*)pc;
                    pc += sizeof(int);

                    int num_string_expression = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    char attr[128];

                    attr[0] = '\0';

                    if(global) {
                        xstrncat(attr, "g", 128);
                    }
                    if(ignore_case) {
                        xstrncat(attr, "i", 128);
                    }
                    if(multiline) {
                        xstrncat(attr, "m", 128);
                    }
                    if(extended) {
                        xstrncat(attr, "x", 128);
                    }
                    if(dotall) {
                        xstrncat(attr, "s", 128);
                    }
                    if(anchored) {
                        xstrncat(attr, "A", 128);
                    }
                    if(dollar_endonly) {
                        xstrncat(attr, "D", 128);
                    }
                    if(ungreedy) {
                        xstrncat(attr, "U", 128);
                    }

                    if(num_string_expression == 0) {
                        snprintf(line, 1024, "clover2Stack[clover2StackIndex] = /%s/%s; clover2StackIndex++", str, attr);

                        sBuf_append_str(info->js_source, line);
                        sBuf_append_str(info->js_source, "\n");
                    }
                    else {
                        int string_expression_offsets[STRING_EXPRESSION_MAX];
                        char string_expression_object[STRING_EXPRESSION_MAX][128];

                        int i;
                        for(i=0; i<num_string_expression; i++) {
                            string_expression_offsets[i] = *(int*)pc;
                            pc += sizeof(int);

                            snprintf(string_expression_object[i], 128, "clover2Stack[clover2StackIndex+%d]", -num_string_expression + i);
                        }

                        sBuf buf;
                        sBuf_init(&buf);

                        if(!string_expression(str, strlen(str), &buf, string_expression_offsets, string_expression_object, num_string_expression, var_num, info))
                        {
                            js_err_msg(info, "invalid string expression\n");
                            return FALSE;
                        }

                        sBuf buf2;
                        sBuf_init(&buf2);

                        snprintf(line, 1024, "tmp = `");

                        sBuf_append_str(&buf2, line);

                        sBuf_append_str(&buf2, buf.mBuf);

                        snprintf(line, 1024,"`;");

                        sBuf_append_str(&buf2, line);

                        sBuf_append_str(info->js_source, buf2.mBuf);
                        sBuf_append_str(info->js_source, "\n");

                        snprintf(line, 1024, "clover2StackIndex -= %d", num_string_expression);
                        sBuf_append_str(info->js_source, line);
                        sBuf_append_str(info->js_source, "\n");

                        snprintf(line, 1024, "clover2Stack[clover2StackIndex] = new RegExp(tmp, %s); clover2StackIndex++", attr);

                        sBuf_append_str(info->js_source, line);
                        sBuf_append_str(info->js_source, "\n");

                        MFREE(buf2.mBuf);
                        MFREE(buf.mBuf);
                    }
                }
                break;

            case OP_STORE:
                {
//print_inst("OP_STORE", info);
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    BOOL value_is_object = *(int*)pc;
                    pc += sizeof(int);

                    snprintf(line, 1024, "clover2Stack[lvar+%d] = clover2Stack[clover2StackIndex-1]", index);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_LOAD:
                {
//print_inst("OP_LOAD", info);
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    int tmp = *(int*)pc;
                    pc += sizeof(int);
/*
snprintf(line, 1024, "console.log('index %d')", index);

sBuf_append_str(info->js_source, line);
sBuf_append_str(info->js_source, "\n");

show_js_stack(info);
*/
                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = clover2Stack[lvar+%d]; clover2StackIndex++", index);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
//show_js_stack(info);
                }
                break;

            case OP_GOTO:
                {
//print_inst("OP_GOTO", info);
                    int jump_value = *(int*)pc;
                    pc += sizeof(int);
                    int label_offset = *(int*)pc;
                    pc += sizeof(int);
                }
                break;

            case OP_COND_JUMP:
                {
//print_inst("OP_COND_JUMP", info);
                    int jump_value = *(int*)pc;
                    pc += sizeof(int);
                }
                break;

            case OP_COND_NOT_JUMP:
                {
                    int jump_value = *(int*)pc;
                    pc += sizeof(int);
                }
                break;

            case OP_JS_IF:
                {
//print_inst("OP_JS_IF", info);
                    snprintf(line, 1024, "if(clover2Stack[--clover2StackIndex]) { ");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_JS_NOT_IF:
                {
//print_inst("OP_JS_IF", info);
                    snprintf(line, 1024, "if(!clover2Stack[--clover2StackIndex]) { ");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_JS_ELSE: {
                snprintf(line, 1024, "else { ");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_JS_BLOCK_CLOSE: {
//print_inst("OP_JS_BLOCK_CLOSE", info);
                snprintf(line, 1024, "}");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_JS_LOOP: {
                snprintf(line, 1024, "while(true) {");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_JS_BREAK: {
                snprintf(line, 1024, "break;");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_STORE_ANDAND_OROR_VALUE_LEFT:
                snprintf(line, 1024, "clover2StackIndex--;");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                break;

            case OP_INC_ANDAND_OROR_ARRAY:
                break;

            case OP_DEC_ANDAND_OROR_ARRAY:
                break;

            case OP_NEW: {
//print_inst("OP_NEW", info);
                unsigned int offset = *(unsigned int*)pc;
                pc += sizeof(int);

                unsigned int offset2 = *(unsigned int*)pc;
                pc += sizeof(int);

                BOOL flg_array = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load(class_name, TRUE);
//print_inst(class_name, info);

                load_js_class(class_name, info);

                if(klass == NULL) {
                    js_err_msg(info, "class not found(%s)\n", class_name);
                    return FALSE;
                }

                if(flg_array) {
                }
                else {
                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = new %s(); clover2StackIndex++;", class_name);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                }
                break;

            case OP_CREATE_SORTABLE_LIST:
                {
//print_inst("OP_CREATE_SORTABLE_LIST", info);
                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    unsigned int offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    unsigned int offset2 = *(unsigned int*)pc;
                    pc += sizeof(int);

                    snprintf(line, 1024, "tmp = [");
                    sBuf_append_str(info->js_source, line);

                    int i;
                    for(i=0; i<num_elements; i++) {
                        snprintf(line, 1024, "clover2Stack[clover2StackIndex+%d]", i-num_elements);

                        sBuf_append_str(info->js_source, line);

                        if(i < num_elements-1) {
                            sBuf_append_str(info->js_source, ",");
                        }
                    }

                    sBuf_append_str(info->js_source, "]\n");

                    snprintf(line, 1024, "clover2StackIndex -= %d;", num_elements);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = new SortableList().constructor__Array(tmp); clover2StackIndex++;");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_CREATE_HASH:
                {
//print_inst("OP_CREATE_HASH", info);
                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    unsigned int offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    unsigned int offset2 = *(unsigned int*)pc;
                    pc += sizeof(int);

                    unsigned int offset3 = *(unsigned int*)pc;
                    pc += sizeof(int);

                    snprintf(line, 1024, "tmp = new Map([");
                    sBuf_append_str(info->js_source, line);

                    int i;
                    for(i=0; i<num_elements; i++) {
                        snprintf(line, 1024, "[ clover2Stack[clover2StackIndex+%d], clover2Stack[clover2StackIndex+%d] ]", i*2-num_elements*2, i*2 + 1 - num_elements * 2);

                        sBuf_append_str(info->js_source, line);

                        if(i < num_elements-1) {
                            sBuf_append_str(info->js_source, ",");
                        }
                    }

                    sBuf_append_str(info->js_source, "])\n");

                    snprintf(line, 1024, "clover2StackIndex -= %d;", num_elements*2);
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_CREATE_TUPLE:
                {
                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    unsigned int offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    char* type_name = CONS_str(constant, offset);
                    snprintf(line, 1024, "tmp = new Tuple%d(); clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;\n", num_elements);
                    sBuf_append_str(info->js_source, line);

                    int i;
                    for(i=0; i<num_elements; i++) {
                        snprintf(line, 1024, "var tmp2 = clover2Stack[clover2StackIndex-%d-2]; clover2Stack[clover2StackIndex-%d-2] = clover2Stack[clover2StackIndex-%d-1]; clover2Stack[clover2StackIndex-%d-1] = tmp2;\n", i, i, i, i);
                        sBuf_append_str(info->js_source, line);
                    }

                    snprintf(line, 1024, "tmp.initialize__");
                    sBuf_append_str(info->js_source, line);

                    for(i=0; i<num_elements; i++) {
                        snprintf(line, 1024, "GenericsParametorClass%d", i);

                        sBuf_append_str(info->js_source, line);
                        if(i < num_elements-1) {
                            sBuf_append_str(info->js_source, "_");
                        }
                    }
                    sBuf_append_str(info->js_source, "(clover2Stack, clover2StackIndex, exception)\n");

                    snprintf(line, 1024, "clover2StackIndex -= %d;", num_elements);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                    
                }
                break;

            case OP_JS_ARRAY:
                {
//print_inst("OP_JS_ARRAY", info);
                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    snprintf(line, 1024, "tmp = [");
                    sBuf_append_str(info->js_source, line);

                    int i;
                    for(i=0; i<num_elements; i++) {
                        snprintf(line, 1024, "clover2Stack[clover2StackIndex+%d]", i-num_elements);

                        sBuf_append_str(info->js_source, line);

                        if(i < num_elements-1) {
                            sBuf_append_str(info->js_source, ",");
                        }
                    }

                    sBuf_append_str(info->js_source, "]\n");

                    snprintf(line, 1024, "clover2StackIndex -= %d;", num_elements);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++;");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_INTEGER_TO_INT_CAST:
//print_inst("OP_INTEGER_TO_INT_CAST", info);
                js_err_msg(info, "OP_INTEGER_TO_INT_CAST operand is not supported in JS");
                return FALSE;

            case OP_INT_TO_INTEGER_CAST:
//print_inst("OP_INT_TO_INTEGER_CAST", info);
                js_err_msg(info, "OP_INT_TO_INTEGER operand is not supported in JS");
                break;

            case OP_BOOL_TO_CBOOL_CAST:
//print_inst("OP_BOOL_TO_CBOOL_CAST", info);

                snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex--; clover2Stack[clover2StackIndex] = new Bool().constructor__bool(tmp); clover2StackIndex++;");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                break;

            case OP_CREATE_BLOCK_OBJECT:
                {
                    unsigned int code_offset = *(unsigned int*)pc;
                    pc += sizeof(int);

                    unsigned int code_len = *(unsigned int*)pc;
                    pc += sizeof(int);

                    sByteCode codes2;
                    codes2.mCodes = CONS_str(constant, code_offset);
                    codes2.mLen = code_len;


                    int constant_offset = *(int*)pc;
                    pc += sizeof(int);

                    int constant_len = *(int*)pc;
                    pc += sizeof(int);

                    sConst constant2;
                    constant2.mConst = CONS_str(constant, constant_offset);
                    constant2.mLen = constant_len;

                    int block_var_num = *(int*)pc;
                    pc += sizeof(int);

                    int parent_var_num = *(int*)pc;
                    pc += sizeof(int);

                    int lambda = *(int*)pc;
                    pc += sizeof(int);

                    int block_id = *(int*)pc;
                    pc += sizeof(int);

                    int class_name_offset = *(int*)pc;
                    pc += sizeof(int);

                    int num_params = *(int*)pc;
                    pc += sizeof(int);

                    snprintf(line, 1024, "var lambda__ = function (clover2Stack, clover2StackIndex, exception) {");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    if(!js(&codes2, &constant2, block_var_num, num_params + parent_var_num, klass, info))
                    {
                        return FALSE;
                    }

                    snprintf(line, 1024, "return clover2Stack[clover2StackIndex-1];");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "}\n");
                    sBuf_append_str(info->js_source, line);

                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = new Lambda().constructor__Function_bool_Number(lambda__, %s, %d); clover2StackIndex++;", lambda ? "true":"false", parent_var_num);

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_ANDAND:
                {
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] && clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_OROR:
                {
                    snprintf(line, 1024, "clover2StackIndex -= 2; clover2Stack[clover2StackIndex] = clover2Stack[clover2StackIndex] || clover2Stack[clover2StackIndex+1]; clover2StackIndex++");

                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_INVOKE_BLOCK:
                {
//print_inst("OP_INVOKE_BLOCK", info);
                    int num_params = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    snprintf(line, 1024, "var stack_point = clover2StackIndex");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

//show_js_stack(info);

                    snprintf(line, 1024, "var params_top = clover2StackIndex-%d; var lambda_object = clover2Stack[params_top]", num_params+1);
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "var lambda_params = clover2Stack.slice(params_top+1, params_top+1+%d)", num_params);
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "var parent_var_num = lambda_object.parentVarNum;");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "if(!lambda_object.lamda_) { for(var i=0; i<parent_var_num; i++) { clover2Stack[clover2StackIndex] = clover2Stack[lvar+i]; clover2StackIndex++ }}");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "var index_point = clover2StackIndex;");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "for(var i=0; i<lambda_params.length; i++) { clover2Stack[clover2StackIndex] = lambda_params[i]; clover2StackIndex++; }");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "tmp = lambda_object.function_(clover2Stack, clover2StackIndex, exception);");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "clover2StackIndex = stack_point");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "if(!lambda_object.lambda_) {for(var i=0; i<parent_var_num; i++) { clover2Stack[lvar+i] = clover2Stack[stack_point+i]}}");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "clover2StackIndex -= %d", num_params+1);
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = tmp; clover2StackIndex++");
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");

//show_js_stack(info);
                }
                break;

            case OP_TRY: {
                try_offset_before = info->try_offset;
                try_code_before = info->try_code;

                info->try_offset = *(int*)pc;
                pc += sizeof(int);

                int catch_label_name_offset = *(int*)pc;
                pc += sizeof(int);

                int try_exception_var_index = *(int*)pc;
                pc += sizeof(int);

                snprintf(line, 1024, "try {");
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_THROW: {
                snprintf(line, 1024, "exception.data = clover2Stack[clover2StackIndex-1]; clover2StackIndex--;");
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");

                snprintf(line, 1024, "throw new Error('null message')");

                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_CATCH_STORE: {
                int index = *(int*)pc;
                pc += sizeof(int);

                snprintf(line, 1024, "clover2Stack[lvar+%d] = exception.data", index);
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_CATCH_POP:
                break;

            case OP_TRY_END:
                snprintf(line, 1024, "} catch (error) {");
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");

                info->try_code = try_code_before;
                info->try_offset = try_offset_before;
                break;

            case OP_CATCH_END: {
                snprintf(line, 1024, "}");
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_LDCBOOL: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    if(value) {
                        snprintf(line, 1024, "clover2Stack[clover2StackIndex] = true; clover2StackIndex++");
                        sBuf_append_str(info->js_source, line);
                        sBuf_append_str(info->js_source, "\n");
                    }
                    else {
                        snprintf(line, 1024, "clover2Stack[clover2StackIndex] = false; clover2StackIndex++");
                        sBuf_append_str(info->js_source, line);
                        sBuf_append_str(info->js_source, "\n");
                    }
                }
                break;

            case OP_CLASSNAME: {
                snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex--; tmp = typeof(tmp); var clover2ClassName = tmp; clover2Stack[clover2StackIndex] = clover2ClassName; clover2StackIndex++");
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");
                }
                break;

            case OP_SPLIT_TUPLE: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int size[GENERICS_TYPES_MAX];

                int i;
                for(i = 0; i<num_elements; i++) {
                    size[i] = *(int*)pc;
                    pc += sizeof(int);
                }

                snprintf(line, 1024, "tmp = clover2Stack[clover2StackIndex-1]; clover2StackIndex--;");
                sBuf_append_str(info->js_source, line);
                sBuf_append_str(info->js_source, "\n");

                for(i=0; i<num_elements; i++) {
                    snprintf(line, 1024, "clover2Stack[clover2StackIndex] = tmp.value%d; clover2StackIndex++", i+1);
                    sBuf_append_str(info->js_source, line);
                    sBuf_append_str(info->js_source, "\n");
                }
                }
                break;

            default:
                fprintf(stderr, "invalid opecode (%d)\n", inst);
                exit(2);
        }
/*
unsigned int next_inst = *(unsigned int*)pc;
if(next_inst != OP_JS_ELSE && inst != OP_JS_BLOCK_CLOSE) {
show_js_stack(info);
}
*/
    }

/*
    snprintf(line, 1024, "clover2StackIndex = lvar");
    sBuf_append_str(info->js_source, line);
    sBuf_append_str(info->js_source, "\n");
*/

    return TRUE;
}
