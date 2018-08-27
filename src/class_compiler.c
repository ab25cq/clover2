#include "common.h"
#include <libgen.h>

static BOOL skip_block(sParserInfo* info)
{
    if(*info->p == '{') {
        info->p++;

        BOOL dquort = FALSE;
        BOOL squort = FALSE;
        int sline = 0;
        int nest = 0;
        while(1) {
            if(dquort) {
                if(*info->p == '\\') {
                    info->p++;
                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                    info->p++;
                }
                else if(*info->p == '"') {
                    info->p++;
                    dquort = !dquort;
                }
                else {
                    info->p++;

                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                }
            }
            else if(squort) {
                if(*info->p == '\\') {
                    info->p++;
                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                    info->p++;
                }
                else if(*info->p == '\'') {
                    info->p++;
                    squort = !squort;
                }
                else {
                    info->p++;

                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                }
            }
            else if(*info->p == '\'') {
                sline = info->sline;
                info->p++;
                squort = !squort;
            }
            else if(*info->p == '"') {
                sline = info->sline;
                info->p++;
                dquort = !dquort;
            }
            else if(*info->p == '{') {
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

static BOOL parse_generics_params(sGenericsParamInfo* ginfo, sParserInfo* info)
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

static BOOL parse_class_name_and_attributes(char* class_name, int class_name_size, sParserInfo* info, sCompileInfo* cinfo, sCLClass** unboxing_class)
{
    /// class name ///
    if(!parse_word(class_name, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    /// generics ///
    sGenericsParamInfo ginfo;
    memset(&ginfo, 0, sizeof(sGenericsParamInfo));

    if(!parse_generics_params(&ginfo, info)) 
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

            if(strcmp(buf, "unboxing") == 0) {
                if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                    return FALSE;
                }

                *unboxing_class = get_class(buf);
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
    sCLClass* unboxing_class = NULL;

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, info, cinfo, &unboxing_class))
    {
        return FALSE;
    }

    info->klass = get_class(class_name);

    if(info->klass == NULL) {
        info->klass = alloc_class(class_name, FALSE, -1, -1, info->generics_info.mNumParams, info->generics_info.mParamNames, info->generics_info.mInterface, interface, dynamic_class, FALSE, FALSE, unboxing_class);
        info->klass->mFlags |= CLASS_FLAGS_ALLOCATED;
    }

    info->klass->mFlags |= CLASS_FLAGS_MODIFIED;

    if(!skip_block(info)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL parse_word_with_dot(char* buf, int buf_size, sParserInfo* info)
{
    buf[0] = 0;

    char* p2 = buf;

    if(isalpha(*info->p) || *info->p == '_') {
        while(isalnum(*info->p) || *info->p == '_' || *info->p == '.') {
            if(p2 - buf < buf_size-1) {
                *p2++ = *info->p;
                info->p++;
            }
            else {
                parser_err_msg(info, "length of word is too long");
                return FALSE;
            }
        }
    }

    *p2 = 0;
    skip_spaces_and_lf(info);

    if(*info->p == 0 && buf[0] == 0) {
        parser_err_msg(info, "require word(alphabet or number). this is the end of source");
        return FALSE;
    }

    if(buf[0] == 0) {
        parser_err_msg(info, "require word(alphabet or _ or number). this is (%c)", *info->p);
        info->err_num++;

        if(*info->p == '\n') info->sline++;

        info->p++;
    }

    return TRUE;
}

static BOOL parse_throws_and_clibrary(sParserInfo* info, BOOL* throw_existance, char* clibrary_path, size_t clibrary_path_size)
{
    *throw_existance = FALSE;
    clibrary_path[0] = '\0';

    char buf[32];

    while(1) {
        char* p_saved = info->p;
        int sline_saved = info->sline;

        if(!parse_word(buf, 32, info, FALSE, FALSE)) {
            return FALSE;
        }

        if(strcmp(buf, "from") == 0) {
            char buf2[PATH_MAX];
            if(!parse_word_with_dot(buf2, PATH_MAX, info)) {
                return FALSE;
            }

            xstrncpy(clibrary_path, buf2, clibrary_path_size);
        }
        else if(strcmp(buf, "throws") == 0) {
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
            info->p = p_saved;
            info->sline = sline_saved;
            break;
        }
    }

    return TRUE;
}

BOOL parse_method_name_and_params(char* method_name, int method_name_max, sParserParam* params, int* num_params, sNodeType** result_type, BOOL* native_, BOOL* static_, sParserInfo* info, char* clibrary_path, size_t clibrary_path_size)
{
    /// method generics ///
    if(*info->p == '<') {
        sGenericsParamInfo ginfo;
        memset(&ginfo, 0, sizeof(sGenericsParamInfo));

        if(!parse_generics_params(&ginfo, info)) 
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
            if(!parse_throws_and_clibrary(info, &throw_existance, clibrary_path, clibrary_path_size)) {
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
    if(!parse_throws_and_clibrary(info, &throw_existance, clibrary_path, clibrary_path_size)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL parse_field_attributes_and_type(BOOL* private_, BOOL* protected_, BOOL* static_, BOOL* delegate_, sNodeType** result_type, sParserInfo* info, sCompileInfo* cinfo, char* header_path, int header_path_size)
{
    header_path[0] = '\0';

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

    char* source_end = info->source + strlen(info->source);

    if(info->p < source_end -5 && strstr(info->p, "from") == info->p) {
        info->p += 4;
        skip_spaces_and_lf(info);

        if(!parse_word_with_dot(header_path, header_path_size, info)) {
            return FALSE;
        }
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
                memset(parser_params, 0, sizeof(sParserParam)*PARAMS_MAX);

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
                memset(&method_generics_info, 0, sizeof(sGenericsParamInfo));

                method_generics_info.mNumParams = method->mNumGenerics;
                for(j=0; j<method_generics_info.mNumParams; j++) {
                    int offset = method->mGenericsParamTypeOffsets[j];

                    char* interface_name = CONS_str(&field_class->mConst, offset);
                    sCLClass* interface = get_class(interface_name);

                    MASSERT(interface != NULL);

                    method_generics_info.mInterface[j] = interface;

                    xstrncpy(method_generics_info.mParamNames[j], "dummy", VAR_NAME_MAX); // no use in add_method_to_class
                }

                char clibrary_path[PATH_MAX];
                clibrary_path[0] = '\0';

                sCLMethod* appended_method = NULL;
                if(!add_method_to_class(klass, method_name, parser_params, num_params, result_type, native_, static_, &method_generics_info, &appended_method, clibrary_path, info)) 
                {
                    parser_err_msg(info, "add_method_to_class failed");
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

static BOOL setter_and_getter(sParserInfo* info, sCompileInfo* cinfo, sCLClass* klass, sCLField* field, char* field_name, BOOL private_)
{
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
        /// getter ///
        char* method_name = field_name;

        sParserParam parser_params[PARAMS_MAX];
        int num_params = 0;
        memset(parser_params, 0, sizeof(sParserParam)*PARAMS_MAX);

        sNodeType* result_type = field_type;

        BOOL native_ = FALSE;
        BOOL static_ = FALSE;

        char clibrary_path[PATH_MAX];
        clibrary_path[0] = '\0';

        sCLMethod* appended_method = NULL;
        if(!add_method_to_class(klass, method_name, parser_params, num_params, result_type, native_, static_, NULL, &appended_method, clibrary_path, info))
        {
            parser_err_msg(info, "add_method_to_class failed");
            return FALSE;
        }

        field->mNumGetterMethodIndex = klass->mNumMethods -1;

        /// setter ///
        if(!private_) {
            /// getter ///
            char* method_name = field_name;

            sParserParam parser_params[PARAMS_MAX];
            memset(parser_params, 0, sizeof(sParserParam)*PARAMS_MAX);

            int num_params = 1;

            xstrncpy(parser_params[0].mName, "value", VAR_NAME_MAX);
            parser_params[0].mType = field_type;
            parser_params[0].mDefaultValue[0] = '\0';

            sNodeType* result_type = create_node_type_with_class_name("Null");

            BOOL native_ = FALSE;
            BOOL static_ = FALSE;

            char clibrary_path[PATH_MAX];
            clibrary_path[0] = '\0';

            sCLMethod* appended_method = NULL;
            if(!add_method_to_class(klass, method_name, parser_params, num_params, result_type, native_, static_, NULL, &appended_method, clibrary_path, info))
            {
                parser_err_msg(info, "add_method_to_class failed");
                return FALSE;
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
        char method_name[METHOD_NAME_MAX+1];
        sParserParam params[PARAMS_MAX+1];
        memset(params, 0, sizeof(sParserParam)*(PARAMS_MAX+1));

        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;
        char clibrary_path[PATH_MAX+1];

        clibrary_path[0] = '\0';

        if(!parse_method_name_and_params(method_name, METHOD_NAME_MAX, params, &num_params, &result_type, &native_, &static_, info, clibrary_path, PATH_MAX)) 
        {
            return FALSE;
        }

        if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
            sCLMethod* appended_method = NULL;
            if(!add_method_to_class(info->klass, method_name, params, num_params, result_type, native_, static_, &info->method_generics_info, &appended_method, clibrary_path, info)) 
            {
                parser_err_msg(info, "add_method_to_class failed");
                return FALSE;
            }
        }

        if(native_ || interface || strcmp(clibrary_path, "") != 0) {
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

            char header_path[PATH_MAX];
            header_path[0] = '\0';

            if(!add_class_field_to_class(info->klass, element_name, private_, protected_, field_type, num_enum++, header_path)) 
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
        if(strcmp(buf, "var") == 0) {
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }
        }

        BOOL private_ = FALSE;
        BOOL protected_ = FALSE;
        BOOL static_ = FALSE;
        BOOL delegate_ = FALSE;
        sNodeType* result_type = NULL;
        char header_path[PATH_MAX];

        expect_next_character_with_one_forward(":", info);

        if(!parse_field_attributes_and_type(&private_, &protected_, &static_, &delegate_, &result_type, info, cinfo, header_path, PATH_MAX)) {
            return FALSE;
        }

        if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
            if(static_) {
                if(!add_class_field_to_class(info->klass, buf, private_, protected_, result_type, -1, header_path)) {
                    return FALSE;
                }
            }
            else {
                if(header_path[0] != '\0') {
                    parser_err_msg(info, "Require class field for \"from\" keyword");
                    info->err_num++;
                }

                if(!add_field_to_class(info->klass, buf, private_, protected_, result_type)) {
                    return FALSE;
                }
            }
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        sCLClass* klass = info->klass;
        char* field_name = buf;

        int field_index = search_for_field(klass, field_name);

        if(field_index != -1) {
            sCLField* field = klass->mFields + field_index;

            if(!setter_and_getter(info, cinfo, klass, field, field_name, private_)) {
                return FALSE;
            }
        }

        if(delegate_) {
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
    sCLClass* unboxing_class = NULL;

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, info, cinfo, &unboxing_class))
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

static BOOL setter_and_getter_on_compile_time(sParserInfo* info, sCompileInfo* cinfo, sCLClass* klass, sCLField* field, char* field_name, BOOL private_)
{
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    sVarTable* lv_table_before = info->lv_table;

    if(info->err_num == 0 && (info->klass->mFlags & CLASS_FLAGS_ALLOCATED)) {
        /// getter ///
        char* method_name = field_name;

        sParserParam parser_params[PARAMS_MAX];
        memset(parser_params, 0, sizeof(parser_params));
        int num_params = 0;

        sNodeType* result_type = field_type;

        BOOL native_ = FALSE;
        BOOL static_ = FALSE;

        sParserInfo info2;

        memset(&info2, 0, sizeof(sParserInfo));

        char source[1024];
        snprintf(source, 1024, "return self.%s } ", field_name);

        info2.p = source;
        info2.source = source;
        info2.sname = "getter";
        info2.sline = 1;
        info2.err_num = 0;
        info2.lv_table = info->lv_table;
        info2.parse_phase = info->parse_phase;
        info2.klass = info->klass;
        info2.generics_info = info->generics_info;
        info2.method_generics_info = info->method_generics_info;
        info2.cinfo = cinfo;

        info2.included_source = FALSE;
        info2.get_type_for_interpreter = FALSE;
        info2.next_command_is_to_bool = FALSE;
        info2.exist_block_object_err = FALSE;

        sCLMethod* method = klass->mMethods + field->mNumGetterMethodIndex;

        if(!compile_method(method, parser_params, num_params, &info2, cinfo)) {
            info->lv_table = lv_table_before;
            cinfo->lv_table = lv_table_before;
            return FALSE;
        }

        info->err_num += info2.err_num;
        info->klass->mMethodIndexOnCompileTime++;

        /// setter ///
        if(!private_) {
            /// getter ///
            char* method_name = field_name;

            sParserParam parser_params[PARAMS_MAX];
            memset(parser_params, 0, sizeof(parser_params));
            int num_params = 1;

            xstrncpy(parser_params[0].mName, "value", VAR_NAME_MAX);
            parser_params[0].mType = field_type;
            parser_params[0].mDefaultValue[0] = '\0';

            sNodeType* result_type = create_node_type_with_class_name("Null");

            BOOL native_ = FALSE;
            BOOL static_ = FALSE;

            sParserInfo info2;

            memset(&info2, 0, sizeof(sParserInfo));

            char source[1024];
            snprintf(source, 1024, "self.%s = value; }", field_name);

            info2.p = source;
            info2.source = source;
            info2.sname = "setter";
            info2.sline = 1;
            info2.err_num = 0;
            info2.lv_table = info->lv_table;
            info2.parse_phase = info->parse_phase;
            info2.klass = info->klass;
            info2.generics_info = info->generics_info;
            info2.method_generics_info = info->method_generics_info;
            info2.cinfo = cinfo;

            info2.included_source = FALSE;
            info2.get_type_for_interpreter = FALSE;
            info2.next_command_is_to_bool = FALSE;
            info2.exist_block_object_err = FALSE;

            sCLMethod* method = klass->mMethods + field->mNumGetterMethodIndex + 1;

            if(!compile_method(method, parser_params, num_params, &info2, cinfo)) {
                info->lv_table = lv_table_before;
                cinfo->lv_table = lv_table_before;
                return FALSE;
            }

            info->err_num += info2.err_num;
            info->klass->mMethodIndexOnCompileTime++;
        }
    }

    info->lv_table = lv_table_before;
    cinfo->lv_table = lv_table_before;

    return TRUE;
}

static BOOL field_delegation_on_compile_time(sParserInfo* info, sCompileInfo* cinfo, sCLClass* klass, sCLField* field, char* field_name)
{
    sNodeType* field_type = create_node_type_from_cl_type(field->mResultType, klass);

    sCLClass* field_class = field_type->mClass;

    sVarTable* lv_table_before = info->lv_table;

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
            memset(&method_generics_info, 0, sizeof(sGenericsParamInfo));

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
            memset(parser_params, 0, sizeof(sParserParam)*PARAMS_MAX);

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
            info2.source = source;
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
                info->lv_table = lv_table_before;
                cinfo->lv_table = lv_table_before;
                return FALSE;
            }

            info->err_num += info2.err_num;
            info->klass->mMethodIndexOnCompileTime++;
        }
    }

    info->lv_table = lv_table_before;
    cinfo->lv_table = lv_table_before;

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
        memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;
        char clibrary_path[PATH_MAX];

        clibrary_path[0] = '\0';

        if(!parse_method_name_and_params(method_name, METHOD_NAME_MAX, params, &num_params, &result_type, &native_, &static_, info, clibrary_path, PATH_MAX)) 
        {
            return FALSE;
        }

        sCLMethod* method = info->klass->mMethods + info->klass->mMethodIndexOnCompileTime;
        info->klass->mMethodIndexOnCompileTime++;

        if(info->klass->mFlags & CLASS_FLAGS_ALLOCATED) {
            if(native_ || interface || strcmp(clibrary_path, "") != 0) {
                if(*info->p == ';') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
            }
            else {
                if(*info->p == '{') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    sVarTable* lv_table_before = info->lv_table;

                    if(!compile_method(method, params, num_params, info, cinfo)) {
                        info->lv_table = lv_table_before;
                        cinfo->lv_table = lv_table_before;
                        return FALSE;
                    }

                    info->lv_table = lv_table_before;
                    cinfo->lv_table = lv_table_before;
                }
                else {
                    parser_err_msg(info, "The next character is required {");
                    info->err_num++;
                }
            }
        }
        else {
            if(native_ || interface || strcmp(clibrary_path, "") != 0) {
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
        if(strcmp(buf, "var") == 0) {
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }
        }

        BOOL private_ = FALSE;
        BOOL protected_ = FALSE;
        BOOL static_ = FALSE;
        BOOL delegate_ = FALSE;
        sNodeType* result_type = NULL;
        char header_path[PATH_MAX];

        expect_next_character_with_one_forward(":", info);

        if(!parse_field_attributes_and_type(&private_, &protected_, &static_, &delegate_, &result_type, info, cinfo, header_path, PATH_MAX)) {
            return FALSE;
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(info->klass->mFlags & CLASS_FLAGS_ALLOCATED) {
            sCLClass* klass = info->klass;
            char* field_name = buf;

            int field_index = search_for_field(klass, field_name);

            if(field_index != -1) {
                sCLField* field = klass->mFields + field_index;

                if(!setter_and_getter_on_compile_time(info, cinfo, klass, field, field_name, private_))
                {
                    return FALSE;
                }
            }

            if(delegate_) {
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
    sCLClass* unboxing_class = NULL;

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, info, cinfo, &unboxing_class))
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

static BOOL search_for_include_file(char* file_name, char* include_file_path, size_t include_file_path_size)
{
    /// script file directory ///
    if(gScriptDirPath[0] != '\0') {
        snprintf(include_file_path, include_file_path_size, "%s/%s", gScriptDirPath, file_name);

        if(access(include_file_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// current working directory ///
    char* cwd = getenv("PWD");

    if(cwd) {
        snprintf(include_file_path, include_file_path_size, "%s/%s", cwd, file_name);

        if(access(include_file_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// home directory ///
    char* home = getenv("HOME");

    if(home) {
        snprintf(include_file_path, include_file_path_size, "%s/.clover2/%s", home, file_name);

        if(access(include_file_path, F_OK) == 0) {
            return TRUE;
        }
    }

    /// system shared directory ///
    snprintf(include_file_path, include_file_path_size, "%s/share/clover2/%s", PREFIX, file_name);

    if(access(include_file_path, F_OK) == 0) {
        return TRUE;
    }

    return FALSE;
}

static BOOL include_file(sParserInfo* info, sCompileInfo* cinfo)
{
    char script_dir_path[PATH_MAX];

    xstrncpy(script_dir_path, gScriptDirPath, PATH_MAX);

    /// get including file name ///
    char file_name[PATH_MAX+1];

    expect_next_character_with_one_forward("\"", info);

    char* p = file_name;

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

    char file_path[PATH_MAX+1];

    if(!search_for_include_file(file_name, file_path, PATH_MAX)) {
        parser_err_msg(info, "can't search for the file(%s).", file_name);
        return FALSE;
    }

    char tmp[PATH_MAX];

    xstrncpy(tmp, file_path, PATH_MAX);
    char* dname = dirname(tmp);

    xstrncpy(gScriptDirPath, dname, PATH_MAX);

    /// load source file ///
    sBuf source;
    sBuf_init(&source);

    if(!read_source(file_path, &source)) {
        MFREE(source.mBuf);

        xstrncpy(gScriptDirPath, script_dir_path, PATH_MAX);
        return FALSE;
    }

    sBuf source2;
    sBuf_init(&source2);

    if(!delete_comment(&source, &source2)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);

        xstrncpy(gScriptDirPath, script_dir_path, PATH_MAX);
        return FALSE;
    }

    char* info_p_before = info->p;
    info->p = source2.mBuf;

    char* info_sname_before = info->sname;
    info->sname = file_path;

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

        xstrncpy(gScriptDirPath, script_dir_path, PATH_MAX);
        return FALSE;
    }

    info->p = info_p_before;
    info->sname = info_sname_before;
    info->sline = info_sline_before;
    info->included_source = info_included_source_before;

    MFREE(source.mBuf);
    MFREE(source2.mBuf);

    xstrncpy(gScriptDirPath, script_dir_path, PATH_MAX);

    return TRUE;
}

static BOOL parse_class_source(sParserInfo* info, sCompileInfo* cinfo)
{
    while(*info->p) {
        skip_spaces_and_lf(info);

        char* p_before = info->p;
        char buf[VAR_NAME_MAX+1];

        if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE)) {
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
        else if(strcmp(buf, "__BEGIN__") == 0) {
            while(*info->p) {
                if(*info->p == '_' && *(info->p+1) == '_' && *(info->p+2) == 'E' && *(info->p+3) == 'N' && *(info->p + 4) == 'D' && *(info->p + 5) == '_' && *(info->p + 6) == '_')
                {
                    info->p += 7;
                    break;
                }
                else if(*info->p == '\n') {
                    info->sline++;
                    info->p++;
                }
                else {
                    info->p++;
                }
            }
        }
        else {
            info->p = p_before;

            if(info->parse_phase == PARSE_PHASE_DO_COMPILE_CODE) {
                cinfo->no_output = FALSE;
            }
            else {
                cinfo->no_output = TRUE;
            }

            info->exist_block_object_err = FALSE;
            info->next_command_is_to_bool = FALSE;
            unsigned int node = 0;
            if(!expression(&node, info)) {
                return FALSE;
            }

            cinfo->sname = gNodes[node].mSName;
            cinfo->sline = gNodes[node].mLine;

            if(info->err_num == 0 && node != 0 && info->parse_phase == PARSE_PHASE_DO_COMPILE_CODE) {
                append_opecode_to_code(cinfo->code, OP_HEAD_OF_EXPRESSION, cinfo->no_output);

                append_opecode_to_code(cinfo->code, OP_MARK_SOURCE_CODE_POSITION, cinfo->no_output);
                append_str_to_constant_pool_and_code(cinfo->constant, cinfo->code, cinfo->sname, cinfo->no_output);
                append_int_value_to_code(cinfo->code, cinfo->sline, cinfo->no_output);

                if(!compile(node, cinfo)) {
                    return FALSE;
                }

                arrange_stack(cinfo);
            }

            if(*info->p == ';') {
                info->p++;
                skip_spaces_and_lf(info);
            }
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

BOOL call_compile_time_script_method_on_declare()
{
    sCLClass* clover_class = get_class("Clover");

    sNodeType* result_type = NULL;
    sNodeType* result_method_generics_types = NULL;
    int method_index = search_for_method(clover_class, "compileTimeScriptingOnDeclareTime", NULL, 0, TRUE, clover_class->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, &result_method_generics_types, NULL);
    sCLMethod* method = clover_class->mMethods + method_index;
    
    const int stack_size = 512;
    CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
    CLVALUE* stack_ptr = stack;

    sVMInfo info;
    memset(&info, 0, sizeof(sVMInfo));

    create_global_stack_and_append_it_to_stack_list(&info);

    int var_num = 0;

    if(!invoke_method(clover_class, method, stack, var_num, &stack_ptr, &info)) {
        free_global_stack(&info);
        MFREE(stack);
        return FALSE;
    }

    free_global_stack(&info);
    MFREE(stack);

    return TRUE;
}

static BOOL eval_str(char* source, char* fname, sVarTable* lv_table, CLVALUE* stack, int sline)
{
    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.source = source;
    info.sname = fname;
    info.sline = sline;
    info.lv_table = lv_table;
    info.parse_phase = 0;
    info.get_type_for_interpreter = FALSE;

    sCompileInfo cinfo;
    
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sByteCode code;
    sByteCode_init(&code);
    cinfo.code = &code;

    sConst constant;
    sConst_init(&constant);
    cinfo.constant = &constant;

    cinfo.lv_table = lv_table;
    cinfo.no_output = FALSE;
    cinfo.pinfo = &info;

    info.cinfo = &cinfo;

    while(*info.p) {
        unsigned int node = 0;

        info.next_command_is_to_bool = FALSE;
        info.exist_block_object_err = FALSE;

        if(!expression(&node, &info)) {
            return FALSE;
        }

        cinfo.sname = gNodes[node].mSName;
        cinfo.sline = gNodes[node].mLine;

        if(info.err_num == 0 && node != 0) {
            append_opecode_to_code(cinfo.code, OP_HEAD_OF_EXPRESSION, cinfo.no_output);

            append_opecode_to_code(cinfo.code, OP_MARK_SOURCE_CODE_POSITION, cinfo.no_output);
            append_str_to_constant_pool_and_code(cinfo.constant, cinfo.code, cinfo.sname, cinfo.no_output);
            append_int_value_to_code(cinfo.code, cinfo.sline, cinfo.no_output);

            if(!compile(node, &cinfo)) {
                return FALSE;
            }

            arrange_stack(&cinfo);
        }

        if(*info.p == ';') {
            info.p++;
            skip_spaces_and_lf(&info);
        }
    }

    if(info.err_num > 0 || cinfo.err_num > 0) {
        fprintf(stderr, "Parser error number is %d. Compile error number is %d\n", info.err_num, cinfo.err_num);
        return FALSE;
    }

    int var_num = get_var_num(info.lv_table);

    sVMInfo vinfo;
    memset(&vinfo, 0, sizeof(sVMInfo));

    create_global_stack_and_append_it_to_stack_list(&vinfo);

    vinfo.running_class_name = "none";
    vinfo.running_method_name = "eval_str";

    vm_mutex_on();

    if(!vm(&code, &constant, stack, var_num, NULL, &vinfo)) {
        free_global_stack(&vinfo);
        vm_mutex_off();

        return FALSE;
    }

    free_global_stack(&vinfo);

    vm_mutex_off(); // see OP_RETURN

    return TRUE;
}

BOOL compile_class_source(char* fname, char* source)
{
    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.source = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = NULL;
    info.parse_phase = 0;
    info.included_source = FALSE;

    sCompileInfo cinfo;
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sByteCode code;
    sByteCode_init(&code);

    cinfo.code = &code;
    //cinfo.code = NULL;

    sConst constant;
    sConst_init(&constant);
    cinfo.constant = &constant;
    //cinfo.constant = NULL;

    //cinfo.lv_table = NULL;
    cinfo.no_output = FALSE;
    cinfo.pinfo = &info;

    info.cinfo = &cinfo;

    sCLClass* clover_class = get_class("Clover");

    if(clover_class) {
        sNodeType* result_type = NULL;
        sNodeType* result_method_generics_types = NULL;
        int method_index = search_for_method(clover_class, "compileTimeScripting", NULL, 0, TRUE, clover_class->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, &result_method_generics_types, NULL);

        if(method_index >= 0) {
            append_opecode_to_code(cinfo.code, OP_INVOKE_METHOD, cinfo.no_output);

            append_class_name_to_constant_pool_and_code(&cinfo, clover_class);
            append_int_value_to_code(cinfo.code, method_index, cinfo.no_output);
            int size = get_var_size(result_type);
            append_int_value_to_code(cinfo.code, size, cinfo.no_output);

            cinfo.type = result_type;
        }
    }

    sBuf precompile_source;
    sBuf_init(&precompile_source);

    char* p = source;

    int sline = 1;

    while(*p) {
        if(*p == '\n') {
            p++;
            sline++;
        }
        else if(*p == '_' && *(p+1) == '_' && *(p+2) == 'B' && *(p+3) == 'E' && *(p + 4) == 'G' && *(p + 5) == 'I' && *(p + 6) == 'N' && *(p + 7) == '_' && *(p + 8) == '_')
        {
            p += 9;

            while(*p) {
                if(*p == '_' && *(p+1) == '_' && *(p+2) == 'E' && *(p+3) == 'N' && *(p + 4) == 'D' && *(p + 5) == '_' && *(p + 6) == '_')
                {
                    p += 7;
                    break;
                }
                else {
                    sBuf_append_char(&precompile_source, *p);
                    p++;
                }
            }

            break;
        }
        else {
            p++;
        }
    }

    sBuf_append_char(&precompile_source, '\0');

    char* source2 = precompile_source.mBuf;

    if(strcmp(source2, "") != 0 && !gCompilingCore) {
        call_all_class_initializer();

        sVarTable* lv_table = init_var_table();
        int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);

        if(!eval_str(source2, fname, lv_table, stack, sline)) {
            MFREE(stack);
            MFREE(precompile_source.mBuf);
            return FALSE;
        }
        MFREE(stack);
    }

    MFREE(precompile_source.mBuf);

    int i;
    for(i=PARSE_PHASE_ALLOC_CLASSES; i<PARSE_PHASE_MAX; i++) {
        info.parse_phase = i;
        info.p = source;
        info.sline = 1;
        info.exist_block_object_err = FALSE;

        reset_method_index_on_compile_time();

        info.lv_table = init_var_table();
        cinfo.lv_table = info.lv_table;

        if(!parse_class_source(&info, &cinfo)) {
            return FALSE;
        }

        if(info.err_num > 0 || cinfo.err_num > 0) {
            fprintf(stderr, "Parser error number is %d. Compile error number is %d\n", info.err_num, cinfo.err_num);
            return FALSE;
        }

        if(i == PARSE_PHASE_ADD_METHODS_AND_FIELDS) {
            if(!gCompilingCore) {
                call_all_class_initializer();
                if(!call_compile_time_script_method_on_declare()) {
                    fprintf(stderr, "error on compile time script\n");
                    exit(1);
                }
            }
        }

    }

    if(info.err_num > 0 || cinfo.err_num > 0) {
        fprintf(stderr, "Parser error number is %d. Compile error number is %d\n", info.err_num, cinfo.err_num);
        return FALSE;
    }

    if(!gCompilingCore) {
        call_all_class_initializer();

        int var_num = get_var_num(info.lv_table);

        sVMInfo vinfo;
        memset(&vinfo, 0, sizeof(sVMInfo));

        create_global_stack_and_append_it_to_stack_list(&vinfo);

        int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);

        vinfo.running_class_name = "none";
        vinfo.running_method_name = "compile_class_source";

        vm_mutex_on();

        if(!vm(&code, &constant, stack, var_num, NULL, &vinfo)) {
            free_global_stack(&vinfo);
            sByteCode_free(&code);
            sConst_free(&constant);
            vm_mutex_off();
            MFREE(stack);
            return FALSE;
        }

        free_global_stack(&vinfo);
        MFREE(stack);

        vm_mutex_off();  // see OP_RETURN
    }

    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}
