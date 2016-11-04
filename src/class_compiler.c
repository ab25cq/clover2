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

static BOOL parse_generics_params(sParserInfo* info, sCompileInfo* cinfo)
{
    info->generics_info.mNumParams = 0;

    if(*info->p == '<') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            if(isalpha(*info->p)) {
                int num_generics_params = info->generics_info.mNumParams;
                if(!parse_word(info->generics_info.mParamNames[num_generics_params], VAR_NAME_MAX, info, TRUE)) 
                {
                    return FALSE;
                }

                expect_next_character_with_one_forward(":", info);

                sCLClass* interface = NULL;
                if(!parse_class_type(&interface, info)) {
                    return FALSE;
                }

                if(interface && !(interface->mFlags & CLASS_FLAGS_INTERFACE)) {
                    parser_err_msg(info, "This is not interface(%s)\n", CLASS_NAME(info->generics_info.mInterface[num_generics_params]));
                    info->err_num++;
                }

                info->generics_info.mInterface[num_generics_params] = interface;

                info->generics_info.mNumParams++;

                if(info->generics_info.mNumParams >= GENERICS_TYPES_MAX) {
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
    if(!parse_word(class_name, VAR_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    /// generics ///
    if(!parse_generics_params(info, cinfo)) 
    {
        return FALSE;
    }

    /// class attribute ///
    if(*info->p == ':') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            char buf[VAR_NAME_MAX];

            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
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

static BOOL parse_class_on_alloc_classes_phase(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    char class_name[VAR_NAME_MAX];

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, info, cinfo))
    {
        return FALSE;
    }

    if(info->included_source) {
        info->klass = load_class(class_name);

        if(info->klass) {
printf("(%s)\n", class_name);
            info->klass->mFlags |= CLASS_FLAGS_LOADED;
        }
        else {
            info->klass = alloc_class(class_name, FALSE, -1, info->generics_info.mNumParams, info->generics_info.mInterface, interface);
            info->klass->mFlags |= CLASS_FLAGS_MODIFIED;
        }
    }
    else {
        info->klass = alloc_class(class_name, FALSE, -1, info->generics_info.mNumParams, info->generics_info.mInterface, interface);
        info->klass->mFlags |= CLASS_FLAGS_MODIFIED;
    }

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
    
    if(!parse_word(buf, 32, info, FALSE)) {
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
    /// method name ///
    if(!parse_word(method_name, method_name_max, info, TRUE)) {
        return FALSE;
    }

    expect_next_character_with_one_forward("(", info);

    /// parse_params ///
    if(!parse_params(params, num_params, info)) {
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

            if(!parse_word(buf, 32, info, FALSE)) {
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

static BOOL parse_field_attributes_and_type(BOOL* private_, BOOL* protected_, BOOL* static_, sNodeType** result_type, sParserInfo* info, sCompileInfo* cinfo)
{
    /// atributes ///
    while(1) {
        char* p_saved = info->p;
        int sline_saved = info->sline;

        char buf[32];

        if(!parse_word(buf, 32, info, FALSE)) {
            return FALSE;
        }

        if(strcmp(buf, "private") == 0) {
            *private_ = TRUE;
        }
        else if(strcmp(buf, "protected") == 0) {
            *protected_ = TRUE;
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

static BOOL parse_methods_and_fields(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    BOOL native_ = FALSE;
    BOOL static_ = FALSE;

    char buf[VAR_NAME_MAX];
    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    if(strcmp(buf, "include") == 0) {
        char module_name[CLASS_NAME_MAX+1];

        if(!parse_word(module_name, CLASS_NAME_MAX, info, TRUE)) {
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
            info->sline = 1;
            info->sname = module_name;

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
        char method_name[VAR_NAME_MAX];
        sParserParam params[PARAMS_MAX];
        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;

        if(!parse_method_name_and_params(method_name, VAR_NAME_MAX, params, &num_params, &result_type, &native_, &static_, info, cinfo)) 
        {
            return FALSE;
        }

        if(info->err_num == 0 && !(info->klass->mFlags & CLASS_FLAGS_LOADED)) {
            if(!add_method_to_class(info->klass, method_name, params, num_params, result_type, native_, static_)) {
                fprintf(stderr, "overflow method number\n");
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
    /// variable ///
    else {
        BOOL private_ = FALSE;
        BOOL protected_ = FALSE;
        BOOL static_ = FALSE;
        sNodeType* result_type = NULL;

        expect_next_character_with_one_forward(":", info);

        if(!parse_field_attributes_and_type(&private_, &protected_, &static_, &result_type, info, cinfo)) {
            return FALSE;
        }

        if(info->err_num == 0 && !(info->klass->mFlags & CLASS_FLAGS_LOADED)) {
            if(static_) {
                if(!add_class_field_to_class(info->klass, buf, private_, protected_, result_type)) {
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

BOOL parse_methods_and_fields_on_compile_time(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    char buf[VAR_NAME_MAX];

    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    /// incldue ///
    if(strcmp(buf, "include") == 0) {
        char module_name[CLASS_NAME_MAX+1];

        if(!parse_word(module_name, CLASS_NAME_MAX, info, TRUE)) {
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
            info->sline = 1;
            info->sname = module_name;

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
        char method_name[VAR_NAME_MAX];
        sParserParam params[PARAMS_MAX];
        int num_params = 0;
        sNodeType* result_type = NULL;
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;

        if(!parse_method_name_and_params(method_name, VAR_NAME_MAX, params, &num_params, &result_type, &native_, &static_, info, cinfo)) 
        {
            return FALSE;
        }

        sCLMethod* method = info->klass->mMethods + info->klass->mMethodIndexOnCompileTime;
        info->klass->mMethodIndexOnCompileTime++;

        if(info->klass->mFlags & CLASS_FLAGS_LOADED) {
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
        else {
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
    }
    /// variable ///
    else {
        BOOL private_ = FALSE;
        BOOL protected_ = FALSE;
        BOOL static_ = FALSE;
        sNodeType* result_type = NULL;

        expect_next_character_with_one_forward(":", info);

        if(!parse_field_attributes_and_type(&private_, &protected_, &static_, &result_type, info, cinfo)) {
            return FALSE;
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
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

static BOOL parse_class(sParserInfo* info, sCompileInfo* cinfo, BOOL interface)
{
    switch(info->parse_phase) {
        case PARSE_PHASE_ALLOC_CLASSES:
            if(!parse_class_on_alloc_classes_phase(info, cinfo, interface)) {
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
    if(!parse_word(module_name, CLASS_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    if(info->parse_phase == PARSE_PHASE_ALLOC_CLASSES) {
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

        sCLModule* module = create_module(module_name);
        
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
    /// get file name ///
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

    /// load source file ///
    sBuf source;
    sBuf_init(&source);

    if(!read_source(file_name, &source)) {
        MFREE(source.mBuf);
        return FALSE;
    }

    sParserInfo info2;

    memset(&info2, 0, sizeof(sParserInfo));

    info2.p = source.mBuf;
    info2.sname = file_name;
    info2.sline = 1;
    info2.lv_table = info->lv_table;
    info2.parse_phase = info->parse_phase;
    info2.included_source = TRUE;

    sCompileInfo cinfo2;
    
    memset(&cinfo2, 0, sizeof(sCompileInfo));

    cinfo2.code = cinfo->code;
    cinfo2.constant = cinfo->constant;

    cinfo2.lv_table = cinfo->lv_table;
    cinfo2.no_output = cinfo->no_output;
    cinfo2.pinfo = &info2;

    info2.cinfo = &cinfo2;

    if(!parse_class_source(&info2, &cinfo2)) {
        MFREE(source.mBuf);
        return FALSE;
    }

    MFREE(source.mBuf);

    return TRUE;
}

static BOOL parse_class_source(sParserInfo* info, sCompileInfo* cinfo)
{
    skip_spaces_and_lf(info);

    while(*info->p) {
        char buf[VAR_NAME_MAX];

        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
            return FALSE;
        }

        if(strcmp(buf, "class") == 0) {
            if(!parse_class(info, cinfo, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "interface") == 0) {
            if(!parse_class(info, cinfo, TRUE)) {
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
