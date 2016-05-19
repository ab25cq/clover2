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

static BOOL parse_class_name_and_attributes(char* class_name, int class_name_size, BOOL* final_, int* class_version, sParserInfo* info, sCompileInfo* cinfo)
{
    /// class name ///
    if(!parse_word(class_name, VAR_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    char* p_saved = info->p;
    int sline_saved = info->sline;

    char buf[128];

    if(!parse_word(buf, 128, info, FALSE)) {
        return FALSE;
    }

    if(strcmp(buf, "version") == 0) {
        *class_version = 0;
        while(isdigit(*info->p)) {
            info->p++;
            *class_version = *class_version * 10 + *info->p - '0';
        }
    }
    else {
        info->p = p_saved;
        info->sline = sline_saved;
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

            if(strcmp(buf, "final") == 0) {
                *final_ = TRUE;
            }
            else {
                parser_err_msg(info, "%s is not class attribute", buf);
                info->err_num++;
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

static BOOL parse_class_on_alloc_classes_phase(sParserInfo* info, sCompileInfo* cinfo)
{
    char class_name[VAR_NAME_MAX];
    BOOL final_ = FALSE;
    int class_version = 1;

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, &final_, &class_version, info, cinfo))
    {
        return FALSE;
    }

    if(class_version > 1) {
        info->klass = load_class_with_version(class_name, class_version-1);
        info->klass->mFlags |= CLASS_FLAGS_MODIFIED;
        info->klass->mNumMethodsOnLoadTime = info->klass->mNumMethods;
    }
    else {
        info->klass = alloc_class(class_name, FALSE, final_, -1);
        info->klass->mFlags |= CLASS_FLAGS_MODIFIED;
        info->klass->mNumMethodsOnLoadTime = 0;
    }

    if(!skip_block(info)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL parse_param(sParserParam* param, sParserInfo* info)
{
    /// variable name ///
    if(!parse_word(param->mName, VAR_NAME_MAX, info, TRUE)) {
        return FALSE;
    }

    expect_next_character_with_one_forward(":", info);

    if(!parse_type(&param->mType, info)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info)
{
    if(*info->p == ')') {
        info->p++;
        skip_spaces_and_lf(info);

        *num_params = 0;

        return TRUE;
    }

    while(1) {
        if(!parse_param(params + *num_params, info)) {
            return FALSE;
        }

        (*num_params)++;

        if(*num_params > PARAMS_MAX) {
            parser_err_msg(info, "overflow params number");
            return FALSE;
        }

        if(*info->p == ',') {
            info->p++;
            skip_spaces_and_lf(info);
        }
        else if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "It is required to ',' or ')' before the source end");
            info->err_num++;
            break;
        }
        else {
            parser_err_msg(info, "Unexpected character(%c). It is required to ',' or ')' character", *info->p);
            if(*info->p == '\n') {
                info->sline++;
            }
            info->p++;

            info->err_num++;
        }
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

        if(isalpha(*info->p)) {
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

    return TRUE;
}

static BOOL parse_field_attributes_and_type(BOOL* private_, BOOL* protected_, sNodeType** result_type, sParserInfo* info, sCompileInfo* cinfo)
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

static BOOL parse_class_on_add_methods_and_fields(sParserInfo* info, sCompileInfo* cinfo)
{
    char class_name[VAR_NAME_MAX];
    BOOL final_ = FALSE;
    int class_version = 1;

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, &final_, &class_version, info, cinfo))
    {
        return FALSE;
    }

    info->klass = get_class(class_name);

    expect_next_character_with_one_forward("{", info);

    while(1) {
        char buf[VAR_NAME_MAX];
        BOOL native_ = FALSE;
        BOOL static_ = FALSE;

        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
            return FALSE;
        }

        /// function ///
        if(strcmp(buf, "def") == 0) {
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

            if(!add_method_to_class(info->klass, method_name, params, num_params, result_type, native_, static_)) {
                return FALSE;
            }

            if(native_) {
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
            sNodeType* result_type = NULL;

            expect_next_character_with_one_forward(":", info);

            if(!parse_field_attributes_and_type(&private_, &protected_, &result_type, info, cinfo)) {
                return FALSE;
            }

            if(!add_field_to_class(info->klass, buf, private_, protected_, result_type)) {
                return FALSE;
            }

            if(*info->p == ';') {
                info->p++;
                skip_spaces_and_lf(info);
            }
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

    return TRUE;
}

static BOOL parse_class_on_compile_code(sParserInfo* info, sCompileInfo* cinfo)
{
    char class_name[VAR_NAME_MAX];
    BOOL final_ = FALSE;
    int class_version = 1;

    if(!parse_class_name_and_attributes(class_name, VAR_NAME_MAX, &final_, &class_version, info, cinfo))
    {
        return FALSE;
    }

    info->klass = get_class(class_name);

    expect_next_character_with_one_forward("{", info);

    while(1) {
        char buf[VAR_NAME_MAX];

        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE)) {
            return FALSE;
        }

        /// function ///
        if(strcmp(buf, "def") == 0) {
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

            sCLMethod* method = info->klass->mMethods + info->klass->mMethodIndexOnCompileTime + info->klass->mNumMethodsOnLoadTime;
            info->klass->mMethodIndexOnCompileTime++;

            if(native_) {
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
        /// variable ///
        else {
            BOOL private_ = FALSE;
            BOOL protected_ = FALSE;
            sNodeType* result_type = NULL;

            expect_next_character_with_one_forward(":", info);

            if(!parse_field_attributes_and_type(&private_, &protected_, &result_type, info, cinfo)) {
                return FALSE;
            }

            if(*info->p == ';') {
                info->p++;
                skip_spaces_and_lf(info);
            }
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

    return TRUE;
}

static BOOL parse_class(sParserInfo* info, sCompileInfo* cinfo)
{
    switch(info->parse_phase) {
        case PARSE_PHASE_ALLOC_CLASSES:
            if(!parse_class_on_alloc_classes_phase(info, cinfo)) {
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
            if(!parse_class_on_add_methods_and_fields(info, cinfo)) {
                return FALSE;
            }
            break;

        case PARSE_PHASE_COMPILE_PARAM_INITIALIZER:
            while(*info->p) {
                info->p++;
            }
            break;

        case PARSE_PHASE_DO_COMPILE_CODE:
            if(!parse_class_on_compile_code(info, cinfo)) {
                return FALSE;
            }
            break;
    }

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
            if(!parse_class(info, cinfo)) {
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

    sCompileInfo cinfo;
    
    memset(&cinfo, 0, sizeof(sCompileInfo));

    cinfo.code = NULL;
    cinfo.constant = NULL;

    cinfo.lv_table = NULL;
    cinfo.no_output = FALSE;
    cinfo.pinfo = &info;

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
