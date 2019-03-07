#include "common.h"

BOOL Clover_appendField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* klass = lvar;
    CLVALUE* name = lvar + 1;
    CLVALUE* class_name = lvar + 2;
    CLVALUE* js = lvar + 3;

    if(klass->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* klass_value = ALLOC string_object_to_char_array(klass->mObjectValue);
    char* name_value = ALLOC string_object_to_char_array(name->mObjectValue);
    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    BOOL js_value = js->mBoolValue;

    sCLClass* klass2 = get_class_with_load_and_initialize(klass_value, js_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(klass_value);
        MFREE(name_value);
        MFREE(class_name_value);
        return FALSE;
    }

    /// go ///
    if(!add_field_to_class_with_class_name(klass2, name_value, FALSE, FALSE, FALSE, class_name_value)) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid class name");
        MFREE(klass_value);
        MFREE(name_value);
        MFREE(class_name_value);
        return FALSE;
    }

    MFREE(klass_value);
    MFREE(name_value);
    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_appendClassField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* klass = lvar;
    CLVALUE* name = lvar + 1;
    CLVALUE* class_name = lvar + 2;
    CLVALUE* js = lvar + 3;

    if(klass->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(class_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* klass_value = ALLOC string_object_to_char_array(klass->mObjectValue);
    char* name_value = ALLOC string_object_to_char_array(name->mObjectValue);
    char* class_name_value = ALLOC string_object_to_char_array(class_name->mObjectValue);

    BOOL js_value = js->mBoolValue;

    sCLClass* klass2 = get_class_with_load_and_initialize(klass_value, js_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(klass_value);
        MFREE(name_value);
        MFREE(class_name_value);
        return FALSE;
    }

    /// go ///
    if(!add_class_field_to_class_with_class_name(klass2, name_value, FALSE, FALSE, class_name_value, 0)) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid class name");
        MFREE(klass_value);
        MFREE(name_value);
        MFREE(class_name_value);
        return FALSE;
    }

    MFREE(klass_value);
    MFREE(name_value);
    MFREE(class_name_value);

    return TRUE;
}

BOOL Clover_declareMethod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* klass = lvar;
    CLVALUE* code = lvar + 1;

    if(klass->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(code->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* klass_value = ALLOC string_object_to_char_array(klass->mObjectValue);
    char* code_value = ALLOC string_object_to_char_array(code->mObjectValue);

    sCLClass* klass2 = get_class_with_load_and_initialize(klass_value, FALSE);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    /// go ///
    int result = -1;

    sParserInfo pinfo;
    memset(&pinfo, 0, sizeof(sParserInfo));

    pinfo.p = code_value;
    pinfo.source = code_value;
    pinfo.sname = "appendMethod";
    pinfo.sline = 1;
    pinfo.lv_table = init_var_table();
    pinfo.parse_phase = 0;
    pinfo.included_source = FALSE;
    pinfo.klass = klass2;
    pinfo.err_num = 0;

    sGenericsParamInfo ginfo;
    memset(&ginfo, 0, sizeof(sGenericsParamInfo));
    ginfo.mNumParams = klass2->mNumGenerics;

    int i;
    for(i=0; i<klass2->mNumGenerics; i++) {
        char* class_name = CONS_str(&klass2->mConst, klass2->mGenericsParamTypeOffsets[i]);

        sCLClass* interface = get_class_with_load_and_initialize(class_name, FALSE);

        if(interface == NULL) {
            entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
            MFREE(klass_value);
            MFREE(code_value);
            return FALSE;
        }

        ginfo.mInterface[i] = interface;

        char* param_name = CONS_str(&klass2->mConst, klass2->mGenericsParamNameOffsets[i]);

        xstrncpy(ginfo.mParamNames[i], param_name, VAR_NAME_MAX);
    }
    
    pinfo.generics_info = ginfo; // strcuct copy
    pinfo.cinfo = NULL;

    char buf[VAR_NAME_MAX];

    if(!parse_word(buf, VAR_NAME_MAX, &pinfo, TRUE, FALSE)) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(1)");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    /// function ///
    if(strcmp(buf, "def") == 0) {
        BOOL interface = klass2->mFlags & CLASS_FLAGS_INTERFACE;

        char method_name[METHOD_NAME_MAX];
        sParserParam params[PARAMS_MAX];
        memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;
        BOOL dynamic_ = FALSE;
        BOOL pure_native = FALSE;
        char clibrary_path[PATH_MAX];

        if(!parse_method_name_and_params(method_name, METHOD_NAME_MAX, params, &num_params, &result_type, &native_, &static_, &dynamic_, &pure_native, &pinfo, clibrary_path, PATH_MAX)) 
        {
            entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(2)");
            MFREE(klass_value);
            MFREE(code_value);
            return FALSE;
        }

        sCLMethod* appended_method = NULL;
        if(pinfo.err_num == 0) {
            if(!add_method_to_class(klass2, method_name, params, num_params, result_type, native_, static_, dynamic_, pure_native, &pinfo.method_generics_info, &appended_method, clibrary_path, NULL))
            {
                entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Can't add method to class");
                MFREE(klass_value);
                MFREE(code_value);
                return FALSE;
            }

            result = klass2->mNumMethods -1;
        }

        if(native_ || interface || strcmp(clibrary_path, "") != 0) {
            if(*pinfo.p == ';') {
                pinfo.p++;
            }
        }
        else {
            sCLMethod* method = appended_method;

            if(method) {
                if(*pinfo.p == ';') {
                    pinfo.p++;
                    skip_spaces_and_lf(&pinfo);
                }
                else if(*pinfo.p == '{') {
                    pinfo.p++;
                    skip_spaces_and_lf(&pinfo);
                }
                else {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(3)");
                    MFREE(klass_value);
                    MFREE(code_value);
                    return FALSE;
                }
            }
        }
    }
    else {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(4)");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    MFREE(klass_value);
    MFREE(code_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL Clover_appendMethod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* klass = lvar;
    CLVALUE* code = lvar + 1;
    CLVALUE* js = lvar + 2;

    if(klass->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(code->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* klass_value = ALLOC string_object_to_char_array(klass->mObjectValue);
    char* code_value = ALLOC string_object_to_char_array(code->mObjectValue);
    BOOL js_value = js->mBoolValue;

    sCLClass* klass2 = get_class_with_load_and_initialize(klass_value, js_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    sParserInfo pinfo;
    memset(&pinfo, 0, sizeof(sParserInfo));

    sCompileInfo cinfo;
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sGenericsParamInfo ginfo;
    memset(&ginfo, 0, sizeof(sGenericsParamInfo));
    ginfo.mNumParams = klass2->mNumGenerics;

    int i;
    for(i=0; i<klass2->mNumGenerics; i++) {
        char* class_name = CONS_str(&klass2->mConst, klass2->mGenericsParamTypeOffsets[i]);

        sCLClass* interface = get_class_with_load_and_initialize(class_name, FALSE);

        if(interface == NULL) {
            entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
            MFREE(klass_value);
            MFREE(code_value);
            return FALSE;
        }

        ginfo.mInterface[i] = interface;

        char* param_name = CONS_str(&klass2->mConst, klass2->mGenericsParamNameOffsets[i]);

        xstrncpy(ginfo.mParamNames[i], param_name, VAR_NAME_MAX);
    }
    
    pinfo.p = code_value;
    pinfo.sname = "appendMethod";
    pinfo.source = code_value;
    pinfo.sline = 1;
    pinfo.err_num = 0;
    pinfo.lv_table = init_var_table();
    pinfo.parse_phase = 0;
    pinfo.klass = klass2;
    pinfo.generics_info = ginfo; // strcuct copy
    pinfo.cinfo = &cinfo;

    char buf[VAR_NAME_MAX];

    if(!parse_word(buf, VAR_NAME_MAX, &pinfo, TRUE, FALSE)) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "appendMethod Exception");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    /// function ///
    if(strcmp(buf, "def") == 0) {
        BOOL interface = klass2->mFlags & CLASS_FLAGS_INTERFACE;

        char method_name[METHOD_NAME_MAX];
        sParserParam params[PARAMS_MAX];
        memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;
        BOOL dynamic_ = FALSE;
        BOOL pure_native = FALSE;
        char clibrary_path[PATH_MAX];

        if(!parse_method_name_and_params(method_name, METHOD_NAME_MAX, params, &num_params, &result_type, &native_,  &static_, &dynamic_, &pure_native, &pinfo, clibrary_path, PATH_MAX)) 
        {
            entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "appendMethod Exception");
            MFREE(klass_value);
            MFREE(code_value);
            return FALSE;
        }

        sCLMethod* appended_method = NULL;
        if(pinfo.err_num == 0) {
            if(!add_method_to_class(klass2, method_name, params, num_params, result_type, native_, static_, dynamic_, pure_native, &pinfo.method_generics_info, &appended_method, clibrary_path, NULL))
            {
                entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "appendMethod Exception");
                MFREE(klass_value);
                MFREE(code_value);
                return FALSE;
            }
        }

        if(native_ || interface || strcmp(clibrary_path, "") != 0) {
            if(*pinfo.p == ';') {
                pinfo.p++;
            }
        }
        else {
            sCLMethod* method = appended_method;

            if(method) {
                if(*pinfo.p == '{') {
                    pinfo.p++;
                    skip_spaces_and_lf(&pinfo);

                    if(!compile_method(method, params, num_params, &pinfo, &cinfo)) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(5)");
                        MFREE(klass_value);
                        MFREE(code_value);
                        return FALSE;
                    }

                    if(cinfo.err_num != 0) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(6)");
                        MFREE(klass_value);
                        MFREE(code_value);
                        return FALSE;
                    }
                }
                else {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(7)");
                    MFREE(klass_value);
                    MFREE(code_value);
                    return FALSE;
                }
            }
        }
    }
    else {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(8)");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    MFREE(klass_value);
    MFREE(code_value);

    return TRUE;
}

BOOL Clover_appendMethod2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* klass = lvar;
    CLVALUE* method_index = lvar + 1;
    CLVALUE* code = lvar + 2;
    CLVALUE* js = lvar + 3;

    if(klass->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(code->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* klass_value = ALLOC string_object_to_char_array(klass->mObjectValue);
    int method_index_value = method_index->mIntValue;
    char* code_value = ALLOC string_object_to_char_array(code->mObjectValue);

    BOOL js_value = js->mBoolValue;

    sCLClass* klass2 = get_class_with_load_and_initialize(klass_value, js_value);

    if(klass2 == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    sParserInfo pinfo;
    memset(&pinfo, 0, sizeof(sParserInfo));

    sCompileInfo cinfo;
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sGenericsParamInfo ginfo;
    memset(&ginfo, 0, sizeof(sGenericsParamInfo));
    ginfo.mNumParams = klass2->mNumGenerics;

    int i;
    for(i=0; i<klass2->mNumGenerics; i++) {
        char* class_name = CONS_str(&klass2->mConst, klass2->mGenericsParamTypeOffsets[i]);

        sCLClass* interface = get_class_with_load_and_initialize(class_name, FALSE);

        if(interface == NULL) {
            entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Class not found");
            MFREE(klass_value);
            MFREE(code_value);
            return FALSE;
        }

        ginfo.mInterface[i] = interface;

        char* param_name = CONS_str(&klass2->mConst, klass2->mGenericsParamNameOffsets[i]);

        xstrncpy(ginfo.mParamNames[i], param_name, VAR_NAME_MAX);
    }
    
    pinfo.p = code_value;
    pinfo.source = code_value;
    pinfo.sname = "appendMethod";
    pinfo.sline = 1;
    pinfo.err_num = 0;
    pinfo.lv_table = init_var_table();
    pinfo.parse_phase = 0;
    pinfo.klass = klass2;
    pinfo.generics_info = ginfo; // strcuct copy
    pinfo.cinfo = &cinfo;

    char buf[VAR_NAME_MAX];

    if(!parse_word(buf, VAR_NAME_MAX, &pinfo, TRUE, FALSE)) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "appendMethod Exception");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    /// function ///
    if(strcmp(buf, "def") == 0) {
        BOOL interface = klass2->mFlags & CLASS_FLAGS_INTERFACE;

        char method_name[METHOD_NAME_MAX];
        sParserParam params[PARAMS_MAX];
        memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;
        BOOL dynamic_ = FALSE;
        BOOL pure_native = FALSE;
        char clibrary_path[PATH_MAX];

        if(!parse_method_name_and_params(method_name, METHOD_NAME_MAX, params, &num_params, &result_type, &native_, &static_, &dynamic_, &pure_native, &pinfo, clibrary_path, PATH_MAX)) 
        {
            entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "appendMethod Exception");
            MFREE(klass_value);
            MFREE(code_value);
            return FALSE;
        }

        sCLMethod* appended_method = NULL;
        if(pinfo.err_num == 0) {
            appended_method = klass2->mMethods + method_index_value;
        }

        if(native_ || interface || strcmp(clibrary_path, "") != 0) {
            if(*pinfo.p == ';') {
                pinfo.p++;
            }
        }
        else {
            sCLMethod* method = appended_method;

            if(method) {
                if(*pinfo.p == '{') {
                    pinfo.p++;
                    skip_spaces_and_lf(&pinfo);

                    if(!compile_method(method, params, num_params, &pinfo, &cinfo)) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(9)");
                        MFREE(klass_value);
                        MFREE(code_value);
                        return FALSE;
                    }

                    if(cinfo.err_num != 0) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(10)");
                        MFREE(klass_value);
                        MFREE(code_value);
                        return FALSE;
                    }
                }
                else {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(11)");
                    MFREE(klass_value);
                    MFREE(code_value);
                    return FALSE;
                }
            }
        }
    }
    else {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Invalid method definition(12)");
        MFREE(klass_value);
        MFREE(code_value);
        return FALSE;
    }

    MFREE(klass_value);
    MFREE(code_value);

    return TRUE;
}

BOOL Clover_appendClass(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* code = lvar;

    if(code->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* code_value = ALLOC string_object_to_char_array(code->mObjectValue);

    if(!compile_class_source("appendClass", code_value)) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "appendClass Exception");
        MFREE(code_value);
        return FALSE;
    }

    MFREE(code_value);

    return TRUE;
}
