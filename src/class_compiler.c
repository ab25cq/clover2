#include "common.h"

static BOOL skip_block(sParserInfo* info)
{
    if(*info->p == '{') {
        info->p++;

        int nest = 0;
        while(1) {
            if(*info->p == '{') {
                info->p++;

                nest++;
            }
            else if(*info->p == '}') {
                info->p++;

                if(nest == 0) {
                    skip_spaces_and_lf(info);
                    break;
                }

                nest--;
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "The block requires } character for closing block");
                info->err_num++;
                return TRUE;
            }
            else if(*info->p == '\n') {
                info->p++;
                info->sline++;
            }
            else {
                info->p++;
            }
        }
    }

    return TRUE;
}

static BOOL parse_generics_params(sGenericsParamInfo* ginfo, sParserInfo* info, sCompileInfo* cinfo)
{
    ginfo->mNumParams = 0;

    if(*info->p == '<') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            if(isalpha(*info->p)) {
                char buf[VAR_NAME_MAX];
                if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) 
                {
                    return FALSE;
                }

                int num_generics_params = ginfo->mNumParams;
                xstrncpy(ginfo->mParamNames[num_generics_params], buf, VAR_NAME_MAX);

                expect_next_character_with_one_forward(":", info);

                sCLClass* interface = NULL;
                if(!parse_class_type(&interface, info)) {
                    return FALSE;
                }

                if(interface && !(interface->mFlags & CLASS_FLAGS_INTERFACE)) {
                    parser_err_msg(info, "This is not interface(%s)\n", CLASS_NAME(ginfo->mInterface[num_generics_params]));
                    info->err_num++;
                }

                ginfo->mInterface[num_generics_params] = interface;

                ginfo->mNumParams++;

                if(ginfo->mNumParams >= GENERICS_TYPES_MAX) {
                    parser_err_msg(info, "overflow generics params number");
                    return FALSE;
                }

                if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }

        expect_next_character_with_one_forward(">", info);
    }

    return TRUE;
}

static BOOL parse_class_name_and_attributes(char* class_name, int class_name_size, sParserInfo* info, sCompileInfo* cinfo)
{
    /// class name ///
    if(!parse_word(class_name, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    /// generics ///
    sGenericsParamInfo ginfo;
    if(!parse_generics_params(&ginfo, info, cinfo)) 
    {
        return FALSE;
    }

    info->generics_info = ginfo;   // struct copy

    /// class attribute ///
    if(*info->p == ':') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            char buf[VAR_NAME_MAX];

            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }

            if(*info->p == '\0') {
                parser_err_msg(info, "It is the source end. Close class definition");
                info->err_num++;
                return TRUE;
            }
            else if(*info->p == '{') {
                break;
            }
        }
    }

    return TRUE;
}

static BOOL parse_class_on_alloc_classes_phase(sParserInfo* info, sCompileInfo* cinfo, BOOL interface, BOOL dynamic_class)
{
    char class_name[VAR_NAME_MAX];

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, info, cinfo))
    {
        return FALSE;
    }

    info->klass = get_class(class_name);

    if(info->klass == NULL) {
        info->klass = alloc_class(class_name, FALSE, -1, -1, info->generics_info.mNumParams, info->generics_info.mInterface, interface, dynamic_class);
        info->klass->mFlags |= CLASS_FLAGS_ALLOCATED;
    }

    info->klass->mFlags |= CLASS_FLAGS_MODIFIED;

    if(!skip_block(info)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL parse_throws(sParserInfo* info, sCompileInfo* cinfo, BOOL* throw_existance)
{
    /// throws ///
    char* p_saved = info->p;
    int sline_saved = info->sline;

    char buf[32];
    
    if(!parse_word(buf, 32, info, FALSE, FALSE)) {
        return FALSE;
    }

    if(strcmp(buf, "throws") == 0) {
        *throw_existance = TRUE;

        while(1) {
            if(isalpha(*info->p)) {
                sNodeType* exception;

                if(!parse_type(&exception, info)) {
                    return FALSE;
                }
            }
            else if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else {
                break;
            }
        }
    }
    else {
        *throw_existance = FALSE;
        info->p = p_saved;
        info->sline = sline_saved;
    }

    return TRUE;
}

static BOOL parse_method_name_and_params(char* method_name, int method_name_max, sParserParam* params, int* num_params, sNodeType** result_type, BOOL* native_, BOOL* static_, sParserInfo* info, sCompileInfo* cinfo)
{
    /// method generics ///
    if(*info->p == '<') {
        sGenericsParamInfo ginfo;
        if(!parse_generics_params(&ginfo, info, cinfo)) 
        {
            return FALSE;
        }
        info->method_generics_info = ginfo;   // struct copy
    }
    else {
        memset(&info->method_generics_info, 0, sizeof(sGenericsParamInfo));
    }

    /// method name ///
    if(!parse_word(method_name, method_name_max, info, TRUE, FALSE)) {
        return FALSE;
    }

    expect_next_character_with_one_forward("(", info);

    /// parse_params ///
    if(!parse_params(params, num_params, info, 0)) {
        return FALSE;
    }

    /// attributes and result type ///
    if(*info->p == ':') {
        info->p++;
        skip_spaces_and_lf(info);

        /// atributes ///
        while(1) {
            char* p_saved = info->p;
            int sline_saved = info->sline;

            char buf[32];

            if(!parse_word(buf, 32, info, FALSE, FALSE)) {
                return FALSE;
            }

            if(strcmp(buf, "native") == 0) {
                *native_ = TRUE;
            }
            else if(strcmp(buf, "static") == 0) {
                *static_ = TRUE;
            }
            else {
                info->p = p_saved;
                info->sline = sline_saved;
                break;
            }
        }

        /// throw or result type ///
        if(isalpha(*info->p)) {
            BOOL throw_existance = FALSE;
            if(!parse_throws(info, cinfo, &throw_existance)) {
                return FALSE;
            }

            if(!throw_existance) {
                /// parse result type ///
                if(!parse_type(result_type, info)) {
                    return FALSE;
                }
            }
            else {
                *result_type = create_node_type_with_class_name("Null");
            }
        }
        else {
            *result_type = create_node_type_with_class_name("Null");
        }
    }
    else {
        *result_type = create_node_type_with_class_name("Null");
    }

    /// throw ///
    BOOL throw_existance = FALSE;
    if(!parse_throws(info, cinfo, &throw_existance)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL parse_field_attributes_and_type(BOOL* private_, BOOL* protected_, BOOL* static_, BOOL* delegate_, sNodeType** result_type, sParserInfo* info, sCompileInfo* cinfo)
{
    /// atributes ///
    while(1) {
        char* p_saved = info->p;
        int sline_saved = info->sline;

        char buf[32];

        if(!parse_word(buf, 32, info, FALSE, FALSE)) {
            return FALSE;
        }

        if(strcmp(buf, "private") == 0) {
            *private_ = TRUE;
        }
        else if(strcmp(buf, "protected") == 0) {
            *protected_ = TRUE;
        }
        else if(strcmp(buf, "delegate") == 0) {
            *delegate_ = TRUE;
        }
        else if(strcmp(buf, "static") == 0) {
            *static_ = TRUE;
        }
        else {
            info->p = p_saved;
            info->sline = sline_saved;
            break;
        }
    }

    /// parse result type ///
    if(!parse_type(result_type, info)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL field_delegation(sParserInfo* info, sCompileInfo* cinfo, sCLClass* klass, sCLField* field)
{
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    sCLClass* field_class = field_type->mClass;

    if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
        field->mNumDelegatedMethod = 0;

        int i;
        for(i=0; i<field_class->mNumMethods; i++) {
            sCLMethod* method = field_class->mMethods + i;

            if(!(method->mFlags & METHOD_FLAGS_CLASS_METHOD) && !(method->mFlags & METHOD_FLAGS_NATIVE) && strcmp(METHOD_NAME2(field_class, method), "initialize") != 0 && strcmp(METHOD_NAME2(field_class,method), "finalize") != 0) 
            {
                char* method_name = METHOD_NAME2(field_class, method);

                sNodeType* params[PARAMS_MAX];
                int j;
                for(j=0; j<method->mNumParams; j++) {
                    sCLParam* param = method->mParams + j;
                    params[j] = create_node_type_from_cl_type(param->mType, field_class);
                }

                sParserParam parser_params[PARAMS_MAX];
                for(j=0; j<method->mNumParams; j++) {
                    char param_name[VAR_NAME_MAX];
                    snprintf(param_name, VAR_NAME_MAX, "param%d", j);
                    xstrncpy(parser_params[j].mName, param_name, VAR_NAME_MAX);
                    parser_params[j].mType = params[j];
                }

                int num_params = method->mNumParams;

                sNodeType* result_type = create_node_type_from_cl_type(method->mResultType, field_class);

                BOOL native_ = FALSE;
                BOOL static_ = FALSE;

                sGenericsParamInfo method_generics_info;

                method_generics_info.mNumParams = method->mNumGenerics;
                for(j=0; j<method_generics_info.mNumParams; j++) {
                    int offset = method->mGenericsParamTypeOffsets[j];

                    char* interface_name = CONS_str(&field_class->mConst, offset);
                    sCLClass* interface = get_class(interface_name);

                    MASSERT(interface != NULL);

                    method_generics_info.mInterface[j] = interface;

                    xstrncpy(method_generics_info.mParamNames[j], "dummy", VAR_NAME_MAX); // no use in add_method_to_class
                }

                if(!add_method_to_class(klass, method_name, parser_params, num_params, result_type, native_, static_, &method_generics_info)) 
                {
                    return FALSE;
                }

                int num_methods = field->mNumDelegatedMethod;
                field->mDelegatedMethodIndex[num_methods] = klass->mNumMethods -1;  // compile time variable
                field->mNumDelegatedMethod++;
            }
        }
    }

    return TRUE;
}

static BOOL parse_methods_and_fields(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    BOOL native_ = FALSE;
    BOOL static_ = FALSE;

    char buf[VAR_NAME_MAX];
    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    if(strcmp(buf, "include") == 0) {
        char module_name[CLASS_NAME_MAX+1];

        if(!parse_word(module_name, CLASS_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }

        sCLModule* module = get_module(module_name);

        if(module == NULL) {
            parser_err_msg(info, "The module named %s is not defined", module_name);
            info->err_num++;
        }
        else {
            char* body = get_module_body(module);

            char* p_saved = info->p;
            int sline_saved = info->sline;
            char* sname_saved = info->sname;
            int err_num_saved = info->err_num;
            int cinfo_err_num_saved = info->cinfo->err_num;

            info->p = body;
            info->sline = module->mSLine;
            info->sname = module->mSName;

            while(*info->p) {
                skip_spaces_and_lf(info);
                if(!parse_methods_and_fields(info, cinfo, interface)) {
                    return FALSE;
                }
                skip_spaces_and_lf(info);
            }

            info->p = p_saved;
            info->sline = sline_saved;
            info->sname = sname_saved;

            if(info->err_num > err_num_saved || info->cinfo->err_num > cinfo_err_num_saved) {
                parser_err_msg(info, "at including Module %s", module_name);
            }
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }
    }

    /// function ///
    else if(strcmp(buf, "def") == 0) {
        char method_name[METHOD_NAME_MAX];
        sParserParam params[PARAMS_MAX];
        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;

        if(!parse_method_name_and_params(method_name, METHOD_NAME_MAX, params, &num_params, &result_type, &native_, &static_, info, cinfo)) 
        {
            return FALSE;
        }

        if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
            if(!add_method_to_class(info->klass, method_name, params, num_params, result_type, native_, static_, &info->method_generics_info)) 
            {
                return FALSE;
            }
        }

        if(native_ || interface) {
            if(*info->p == ';') {
                info->p++;
                skip_spaces_and_lf(info);
            }
        }
        else {
            if(!skip_block(info)) {
                return FALSE;
            }
        }
    }
    else if(strcmp(buf, "typedef") == 0) {
        char class_name1[CLASS_NAME_MAX+1];
        char class_name2[CLASS_NAME_MAX+1];

        if(!parse_word(class_name1, CLASS_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        if(!parse_word(class_name2, CLASS_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(info->err_num == 0) {
            if(!add_typedef_to_class(info->klass, class_name1, class_name2)) {
                parser_err_msg(info, "overflow typedef number or invalid class name");
                info->err_num++;
                return FALSE;
            }
        }
    }
    else if(strcmp(buf, "enum") == 0) {
        expect_next_character_with_one_forward("{", info);

        int num_enum = 0;

        while(1) {
            char element_name[VAR_NAME_MAX+1];

            if(!parse_word(element_name, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }

            BOOL private_ = FALSE;
            BOOL protected_ = FALSE;
            sNodeType* field_type = create_node_type_with_class_name("int");

            if(!add_class_field_to_class(info->klass, element_name, private_, protected_, field_type, num_enum++)) 
            {
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "unexpected source end");
                return FALSE;
            }
        }

    }
    /// variable ///
    else {
        BOOL private_ = FALSE;
        BOOL protected_ = FALSE;
        BOOL static_ = FALSE;
        BOOL delegate_ = FALSE;
        sNodeType* result_type = NULL;

        expect_next_character_with_one_forward(":", info);

        if(!parse_field_attributes_and_type(&private_, &protected_, &static_, &delegate_, &result_type, info, cinfo)) {
            return FALSE;
        }

        if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
            if(static_) {
                if(!add_class_field_to_class(info->klass, buf, private_, protected_, result_type, -1)) {
                    return FALSE;
                }
            }
            else {
                if(!add_field_to_class(info->klass, buf, private_, protected_, result_type)) {
                    return FALSE;
                }
            }
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(delegate_) {
            sCLClass* klass = info->klass;
            char* field_name = buf;

            int field_index = search_for_field(klass, field_name);

            if(field_index != -1) {
                sCLField* field = klass->mFields + field_index;

                if(!field_delegation(info, cinfo, klass, field)) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

static BOOL parse_class_on_add_methods_and_fields(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    char class_name[VAR_NAME_MAX];

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, info, cinfo))
    {
        return FALSE;
    }

    info->klass = get_class(class_name);

    expect_next_character_with_one_forward("{", info);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!parse_methods_and_fields(info, cinfo, interface)) {
                return FALSE;
            }

            if(*info->p == '\0') {
                parser_err_msg(info, "It is the source end. Close class definition with }");
                info->err_num++;
                return TRUE;
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    return TRUE;
}

static BOOL field_delegation_on_compile_time(sParserInfo* info, sCompileInfo* cinfo, sCLClass* klass, sCLField* field, char* field_name)
{
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    sCLClass* field_class = field_type->mClass;

    if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
        int i;
        for(i=0; i<field->mNumDelegatedMethod; i++) {
            sCLMethod* method = klass->mMethods + field->mDelegatedMethodIndex[i];

            char* method_name = METHOD_NAME2(klass, method);

            sNodeType* params[PARAMS_MAX];
            int j;
            for(j=0; j<method->mNumParams; j++) {
                sCLParam* param = method->mParams + j;
                params[j] = create_node_type_from_cl_type(param->mType, klass);
            }

            int num_params = method->mNumParams;

            sGenericsParamInfo method_generics_info;

            method_generics_info.mNumParams = method->mNumGenerics;
            for(j=0; j<method_generics_info.mNumParams; j++) {
                int offset = method->mGenericsParamTypeOffsets[j];

                char* interface_name = CONS_str(&klass->mConst, offset);
                sCLClass* interface = get_class(interface_name);

                MASSERT(interface != NULL);

                method_generics_info.mInterface[j] = interface;

                xstrncpy(method_generics_info.mParamNames[j], "dummy", VAR_NAME_MAX); // no use in add_method_to_class
            }

            sParserParam parser_params[PARAMS_MAX];
            for(j=0; j<num_params; j++) {
                char param_name[VAR_NAME_MAX];
                snprintf(param_name, VAR_NAME_MAX, "param%d", j);
                xstrncpy(parser_params[j].mName, param_name, VAR_NAME_MAX);
                parser_params[j].mType = params[j];
            }

            sParserInfo info2;

            memset(&info2, 0, sizeof(sParserInfo));

            char source[1024];
            snprintf(source, 1024, "self.%s.%s(", field_name, method_name);
            for(j=0; j<num_params; j++) {
                char param_name[VAR_NAME_MAX];
                snprintf(param_name, VAR_NAME_MAX, "param%d", j);

                xstrncat(source, param_name, 1024);

                if(j != num_params-1) {
                    xstrncat(source, ",", 1024);
                }
            }

            xstrncat(source, "); }", 1024);

            info2.p = source;
            info2.sname = "field_delegation";
            info2.sline = 1;
            info2.err_num = 0;
            info2.lv_table = info->lv_table;
            info2.parse_phase = info->parse_phase;
            info2.klass = info->klass;
            info2.generics_info = info->generics_info;
            info2.method_generics_info = method_generics_info;
            info2.cinfo = cinfo;

            info2.included_source = FALSE;
            info2.get_type_for_interpreter = FALSE;
            info2.next_command_is_to_bool = FALSE;
            info2.exist_block_object_err = FALSE;

            if(!compile_method(method, parser_params, num_params, &info2, cinfo)) {
                return FALSE;
            }

            info->err_num += info2.err_num;
            info->klass->mMethodIndexOnCompileTime++;
        }
    }

    return TRUE;
}

BOOL parse_methods_and_fields_on_compile_time(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    char buf[VAR_NAME_MAX];

    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    /// incldue ///
    if(strcmp(buf, "include") == 0) {
        char module_name[CLASS_NAME_MAX+1];

        if(!parse_word(module_name, CLASS_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }

        sCLModule* module = get_module(module_name);

        if(module == NULL) {
            parser_err_msg(info, "The module named %s is not defined", module_name);
            info->err_num++;
        }
        else {
            char* body = get_module_body(module);

            char* p_saved = info->p;
            int sline_saved = info->sline;
            char* sname_saved = info->sname;
            int err_num_saved = info->err_num;
            int cinfo_err_num_saved = info->cinfo->err_num;

            info->p = body;
            info->sline = module->mSLine;
            info->sname = module->mSName;

            while(*info->p) {
                skip_spaces_and_lf(info);
                if(!parse_methods_and_fields_on_compile_time(info, cinfo, interface)) {
                    return FALSE;
                }
                skip_spaces_and_lf(info);
            }

            info->p = p_saved;
            info->sline = sline_saved;
            info->sname = sname_saved;

            if(info->err_num > err_num_saved || info->cinfo->err_num > cinfo_err_num_saved) {
                parser_err_msg(info, "at including Module %s", module_name);
            }
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }
    }

    /// function ///
    else if(strcmp(buf, "def") == 0) {
        char method_name[METHOD_NAME_MAX];
        sParserParam params[PARAMS_MAX];
        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;

        if(!parse_method_name_and_params(method_name, METHOD_NAME_MAX, params, &num_params, &result_type, &native_, &static_, info, cinfo)) 
        {
            return FALSE;
        }

        sCLMethod* method = info->klass->mMethods + info->klass->mMethodIndexOnCompileTime;
        info->klass->mMethodIndexOnCompileTime++;

        if(info->klass->mFlags & CLASS_FLAGS_ALLOCATED) {
            if(native_ || interface) {
                if(*info->p == ';') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
            }
            else {
                if(*info->p == '{') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    if(!compile_method(method, params, num_params, info, cinfo)) {
                        return FALSE;
                    }
                }
                else {
                    parser_err_msg(info, "The next character is required {");
                    info->err_num++;
                }
            }
        }
        else {
            if(native_ || interface) {
                if(*info->p == ';') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
            }
            else {
                if(!skip_block(info)) {
                    return FALSE;
                }
            }
        }
    }
    else if(strcmp(buf, "typedef") == 0) {
        char class_name1[CLASS_NAME_MAX+1];
        char class_name2[CLASS_NAME_MAX+1];

        if(!parse_word(class_name1, CLASS_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        if(!parse_word(class_name2, CLASS_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }
    }
    else if(strcmp(buf, "enum") == 0) {
        expect_next_character_with_one_forward("{", info);

        while(1) {
            char element_name[VAR_NAME_MAX+1];

            if(!parse_word(element_name, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "unexpected source end");
                return FALSE;
            }
        }
    }
    /// variable ///
    else {
        BOOL private_ = FALSE;
        BOOL protected_ = FALSE;
        BOOL static_ = FALSE;
        BOOL delegate_ = FALSE;
        sNodeType* result_type = NULL;

        expect_next_character_with_one_forward(":", info);

        if(!parse_field_attributes_and_type(&private_, &protected_, &static_, &delegate_, &result_type, info, cinfo)) {
            return FALSE;
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(info->klass->mFlags & CLASS_FLAGS_ALLOCATED) {
            if(delegate_) {
                sCLClass* klass = info->klass;
                char* field_name = buf;

                int field_index = search_for_field(klass, field_name);

                if(field_index != -1) {
                    sCLField* field = klass->mFields + field_index;

                    if(!field_delegation_on_compile_time(info, cinfo, klass, field, field_name)) {
                        return FALSE;
                    }
                }
            }
        }
    }

    return TRUE;
}

static BOOL parse_class_on_compile_code(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    char class_name[VAR_NAME_MAX];

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, info, cinfo))
    {
        return FALSE;
    }

    info->klass = get_class(class_name);

    expect_next_character_with_one_forward("{", info);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!parse_methods_and_fields_on_compile_time(info, cinfo, interface)) {
                return FALSE;
            }

            if(*info->p == '\0') {
                parser_err_msg(info, "It is the source end. Close class definition with }");
                info->err_num++;
                return TRUE;
            }
            else if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    return TRUE;
}

static BOOL parse_class(sParserInfo* info, sCompileInfo* cinfo, BOOL interface, BOOL dynamic_class)
{
    switch(info->parse_phase) {
        case PARSE_PHASE_ALLOC_CLASSES:
            if(!parse_class_on_alloc_classes_phase(info, cinfo, interface, dynamic_class)) {
                return FALSE;
            }
            break;
            
        case PARSE_PHASE_ADD_SUPER_CLASSES:
            while(*info->p) {
                info->p++;
            }
            break;

        case PARSE_PHASE_CALCULATE_SUPER_CLASSES:
            while(*info->p) {
                info->p++;
            }
            break;

        case PARSE_PHASE_ADD_GENERICS_TYPES:
            while(*info->p) {
                info->p++;
            }
            break;

        case PARSE_PHASE_ADD_METHODS_AND_FIELDS:
            if(!parse_class_on_add_methods_and_fields(info, cinfo, interface)) {
                return FALSE;
            }
            break;

        case PARSE_PHASE_COMPILE_PARAM_INITIALIZER:
            while(*info->p) {
                info->p++;
            }
            break;

        case PARSE_PHASE_DO_COMPILE_CODE:
            if(!parse_class_on_compile_code(info, cinfo, interface)) {
                return FALSE;
            }

            break;
    }

    return TRUE;
}

static BOOL parse_module(sParserInfo* info, sCompileInfo* cinfo)
{
    char module_name[CLASS_NAME_MAX];
    if(!parse_word(module_name, CLASS_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    if(info->parse_phase == PARSE_PHASE_ALLOC_CLASSES) {
        char* sname = info->sname;
        int sline = info->sline;

        if(*info->p == '{') {
            info->p++;
            //skip_spaces_and_lf(info);  for module format
        }
        else {
            parser_err_msg(info, "expected that next character is {, but it is %c(%d)", *info->p, *info->p);
            info->err_num++;
            info->p++;
            skip_spaces_and_lf(info);
        }

        sCLModule* module = create_module(module_name, sname, sline);
        
        if(module == NULL) {
            parser_err_msg(info, "overflow the module table or the same name module exists(%s)", module_name);
            return FALSE;
        }

        this_module_is_modified(module);

        int block_num = 0;

        while(*info->p) {
            if(*info->p == '{') {
                block_num++;
                append_character_to_module(module, *info->p);
                info->p++;
            }
            else if(*info->p == '}') {
                if(block_num == 0) {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else {
                    block_num--;
                    append_character_to_module(module, *info->p);
                    info->p++;
                }
            }
            else if(*info->p == '\n') {
                append_character_to_module(module, *info->p);
                info->p++;
                info->sline++;
            }
            else {
                append_character_to_module(module, *info->p);
                info->p++;
            }
        }
    }
    else {
        if(!skip_block(info)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);
    }

    return TRUE;
}

static BOOL parse_class_source(sParserInfo* info, sCompileInfo* cinfo);

static BOOL include_file(sParserInfo* info, sCompileInfo* cinfo)
{
    /// includeするファイル名を得る ///
    char file_name[PATH_MAX+1];

    expect_next_character_with_one_forward("\"", info);

    char* p = file_name;

    /// ファイル名を絶対パスにしておく ///
    if(*info->p != '/') {
        char* pwd = getenv("PWD");

        if(pwd) {
            char* p2 = pwd;

            while(*p2) {
                *p++ = *p2++;
            }

            *p++ = '/';
        }
    }

    while(1) {
        if(*info->p == '"') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "requires to close \" for including file name");
            return FALSE;
        }
        else {
            *p++ = *info->p++;

            if(p - file_name >= PATH_MAX) {
                parser_err_msg(info, "overflow file name");
                return FALSE;
            }
        }
    }
    *p = '\0';

    if(strcmp(gCompilingSourceFileName, file_name) != 0) { /// コンパイル中のファイルのincludeは禁止させる
        /// load source file ///
        sBuf source;
        sBuf_init(&source);

        if(!read_source(file_name, &source)) {
            MFREE(source.mBuf);
            return FALSE;
        }

        sBuf source2;
        sBuf_init(&source2);

        if(!delete_comment(&source, &source2)) {
            MFREE(source.mBuf);
            MFREE(source2.mBuf);
            return FALSE;
        }

        char* info_p_before = info->p;
        info->p = source2.mBuf;

        char* info_sname_before = info->sname;
        info->sname = file_name;

        int info_sline_before = info->sline;
        info->sline = 1;

        BOOL info_included_source_before = info->included_source;
        info->included_source = TRUE;

        if(!parse_class_source(info, cinfo)) {
            info->p = info_p_before;
            info->sname = info_sname_before;
            info->sline = info_sline_before;
            info->included_source = info_included_source_before;
            MFREE(source.mBuf);
            return FALSE;
        }

        info->p = info_p_before;
        info->sname = info_sname_before;
        info->sline = info_sline_before;
        info->included_source = info_included_source_before;

        MFREE(source.mBuf);
        MFREE(source2.mBuf);
    }

    return TRUE;
}

static BOOL parse_class_source(sParserInfo* info, sCompileInfo* cinfo)
{
    skip_spaces_and_lf(info);

    while(*info->p) {
        char buf[VAR_NAME_MAX+1];

        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }

        if(strcmp(buf, "class") == 0) {
            if(!parse_class(info, cinfo, FALSE, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "dynamic_class") == 0) {
            if(!parse_class(info, cinfo, FALSE, TRUE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "interface") == 0) {
            if(!parse_class(info, cinfo, TRUE, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "module") == 0) {
            if(!parse_module(info, cinfo)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "include") == 0) {
            if(!include_file(info, cinfo)) {
                return FALSE;
            }
        }
        else {
            parser_err_msg(info, "Require class keyword. It is %s", buf);
            info->err_num++;
            return FALSE;
        }
    }

    return TRUE;
}

static void reset_method_index_on_compile_time()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        p->mItem->mMethodIndexOnCompileTime = 0;
        p = p->mNextClass;
    }
}

BOOL compile_class_source(char* fname, char* source)
{
    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = NULL;
    info.parse_phase = 0;
    info.included_source = FALSE;

    char fname2[PATH_MAX+1];

    append_cwd_for_path(fname, fname2);         // ファイル名を絶対パスにしておく

    xstrncpy(gCompilingSourceFileName, fname2, PATH_MAX);  // コンパイル中のソースファイル名を保存

    sCompileInfo cinfo;
    
    memset(&cinfo, 0, sizeof(sCompileInfo));

    cinfo.code = NULL;
    cinfo.constant = NULL;

    cinfo.lv_table = NULL;
    cinfo.no_output = FALSE;
    cinfo.pinfo = &info;

    info.cinfo = &cinfo;

    int i;
    for(i=PARSE_PHASE_ALLOC_CLASSES; i<PARSE_PHASE_MAX; i++) {
        info.parse_phase = i;
        info.p = source;
        info.sline = 1;
        info.exist_block_object_err = FALSE;

        reset_method_index_on_compile_time();

        if(!parse_class_source(&info, &cinfo)) {
            return FALSE;
        }

        if(info.err_num > 0 || cinfo.err_num > 0) {
            fprintf(stderr, "Parser error number is %d. Compile error number is %d\n", info.err_num, cinfo.err_num);
            return FALSE;
        }
    }

    return TRUE;
}
