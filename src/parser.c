#include "common.h"
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>

BOOL gInterpreter = FALSE;

static BOOL expression_substitution(unsigned int* node, sParserInfo* info);
BOOL parse_type_for_new(sNodeType** result_type, unsigned int* array_num, sParserInfo* info);

char** gCommandNames = NULL;
int gNumCommandNames = 0;

void parser_init()
{
    int size = 128;
    gCommandNames = MCALLOC(1, sizeof(char*)*size);
    int i;
    int n = 0;

    char* env = getenv("PATH");
    char path[PATH_MAX];

    char* p = path;
    int len = strlen(env);

    for(i= 0; i<len; i++) {
        if(env[i] == ':') {
            *p = '\0';

            if(access(path, F_OK) == 0) {
                struct stat stat_;

                if(stat(path, &stat_) == 0 && S_ISDIR(stat_.st_mode)) {
                    DIR* dir = opendir(path);

                    if(dir) {
                        while(1) {
                            struct dirent* entry = readdir(dir);

                            if(entry == NULL) {
                                break;
                            }

                            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
                            {
                                char path2[PATH_MAX];
                                xstrncpy(path2, path, PATH_MAX);

                                if(path[strlen(path)-1] != '/') {
                                    xstrncat(path2, "/", PATH_MAX);
                                }
                                xstrncat(path2, entry->d_name, PATH_MAX);

                                struct stat stat_;
                                if(stat(path2, &stat_) == 0) {
                                    if(stat_.st_mode & S_IXUSR) {
                                        char candidate[PATH_MAX];
                                        snprintf(candidate, PATH_MAX, "%s(", entry->d_name);
                                        gCommandNames[n++] = MANAGED MSTRDUP(candidate);

                                        if(n >= size) {
                                            size *= 2;
                                            gCommandNames = MREALLOC(gCommandNames, sizeof(char*)*size);
                                        }

                                        snprintf(candidate, PATH_MAX, "%s", entry->d_name);
                                        gCommandNames[n++] = MANAGED MSTRDUP(candidate);

                                        if(n >= size) {
                                            size *= 2;
                                            gCommandNames = MREALLOC(gCommandNames, sizeof(char*)*size);
                                        }
                                    }
                                }
                            }
                        }

                        closedir(dir);
                    }
                }
            }

            p = path;
        }
        else {
            *p++ = env[i];

            if(p - path >= PATH_MAX) {
                fprintf(stderr, "The element of path in PATH environment variable is too long");
                return;
            }
        }
    }

    gCommandNames[n++] = MANAGED MSTRDUP("cd");

    if(n >= size) {
        size *= 2;
        gCommandNames = MREALLOC(gCommandNames, sizeof(char*)*size);
    }

    gCommandNames[n++] = MANAGED MSTRDUP("jobs");

    if(n >= size) {
        size *= 2;
        gCommandNames = MREALLOC(gCommandNames, sizeof(char*)*size);
    }

    gCommandNames[n++] = MANAGED MSTRDUP("fg");

    if(n >= size) {
        size *= 2;
        gCommandNames = MREALLOC(gCommandNames, sizeof(char*)*size);
    }

    gCommandNames[n] = NULL;
    gNumCommandNames = n;
}

void parser_final()
{
    int i;
    for(i=0; i<gNumCommandNames; i++) {
        MFREE(gCommandNames[i]);
    }
    MFREE(gCommandNames);
}

static BOOL is_command_name(char* name)
{
    int i;
    for(i=0; i<gNumCommandNames; i++) {
        if(strcmp(gCommandNames[i], name) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

void parser_err_msg(sParserInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    if(!info->get_type_for_interpreter) {
        fprintf(stderr, "%s %d: %s\n", info->sname, info->sline, msg2);
    }
}

void skip_spaces_and_lf(sParserInfo* info)
{
    while(*info->p == ' ' || *info->p == '\t' || (*info->p == '\n' && (info->sline)++)) {
        info->p++;
    }
}

void skip_spaces(sParserInfo* info)
{
    while(*info->p == ' ' || *info->p == '\t') {
        info->p++;
    }
}


BOOL parse_word(char* buf, int buf_size, sParserInfo* info, BOOL print_out_err_msg, BOOL no_skip_lf)
{
    buf[0] = 0;

    char* p2 = buf;

    if(isalpha(*info->p) || *info->p == '_') {
        while(isalnum(*info->p) || *info->p == '_') {
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
    if(no_skip_lf) {
        skip_spaces(info);
    }
    else {
        skip_spaces_and_lf(info);
    }

    if(*info->p == 0 && buf[0] == 0) {
        if(print_out_err_msg) {
            parser_err_msg(info, "require word(alphabet or number). this is the end of source");
        }
        return FALSE;
    }

    if(buf[0] == 0) {
        if(print_out_err_msg) {
            parser_err_msg(info, "require word(alphabet or _ or number). this is (%c)", *info->p);
            info->err_num++;
        }

        if(*info->p == '\n') info->sline++;

        info->p++;
    }

    return TRUE;
}

void expect_next_character_with_one_forward(char* characters, sParserInfo* info)
{
    skip_spaces_and_lf(info);

    BOOL found = FALSE;
    char* p2 = characters;
    while(*p2) {
        if(*info->p == *p2) {
            found = TRUE;
        }
        p2++;
    }

    if(found) {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        parser_err_msg(info, "expected that next character is %s, but it is %c(%d)", characters, *info->p, *info->p);
        info->err_num++;
        info->p++;
        skip_spaces_and_lf(info);
    }
}

BOOL expect_next_character(char* characters, sParserInfo* info)
{
    int sline_top = info->sline;

    char err_characters[128];
    char* perr_characters = err_characters;
    
    BOOL err = FALSE;
    while(1) {
        BOOL found;
        char* p2;

        if(*info->p == '\0') {
            parser_err_msg(info, "clover has expected that next characters are '%s', but it arrived at source end", characters);
            info->err_num++;
            return TRUE;
        }

        found = FALSE;
        p2 = characters;
        while(*p2) {
            if(*info->p == *p2) {
                found = TRUE;
                break;
            }
            else {
                p2++;
            }
        }

        if(found) {
            break;
        }
        else {
            err = TRUE;
            if(perr_characters - err_characters < 127) {
                *perr_characters = *info->p;
                perr_characters++;
            }
            if(*info->p == '\n') { info->sline++; }
            info->p++;
        }
    }

    if(err) {
        *perr_characters = 0;
        parser_err_msg(info, "Clover has expected that next characters are '%s', but there are some characters(%s) before them", characters, err_characters);
        info->err_num++;
        info->p++;
    }

    return TRUE;
}


static BOOL parse_simple_lambda_params(unsigned int* node, sParserInfo* info, BOOL lambda)
{
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    int num_params = 0;

    /// parse_params ///
    sNodeType* result_type = NULL;
    sVarTable* new_table = NULL;
    BOOL omit_result_type = FALSE;
    BOOL omit_params = FALSE;
    sVarTable* old_table = info->lv_table;

    if(*info->p == '|') {
        info->p++;
        skip_spaces_and_lf(info);

        if(lambda) {
            if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, NULL, 1)) {
                return FALSE;
            }
        }
        else {
            if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, info->lv_table, 1)) {
                return FALSE;
            }
        }

        if(*info->p == ':') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!parse_type(&result_type, info)) {
                return FALSE;
            }
        }
        else {
            omit_result_type = TRUE;
            result_type = create_node_type_with_class_name("Null");
        }
    }
    else {
        result_type = create_node_type_with_class_name("Null");
        if(lambda) {
            new_table = init_block_vtable(NULL);
        }
        else {
            new_table = init_block_vtable(info->lv_table);
        }

        omit_params = TRUE;
        omit_result_type = TRUE;
    }

    sNodeBlock* node_block = NULL;
    if(!parse_block(ALLOC &node_block, info, new_table, TRUE, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_create_block_object(params, num_params, result_type, MANAGED node_block, lambda, info, omit_result_type, omit_params, old_table, FALSE);

    return TRUE;
}

BOOL parse_method_params(int* num_params, unsigned int* params, sParserInfo* info)
{
    *num_params = 0;

    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
        }
        else {
            while(1) {
                unsigned int node = 0;
                if(!expression(&node, info)) {
                    return FALSE;
                }

                if(node == 0) {
                    parser_err_msg(info, "require expression");
                    info->err_num++;
                    break;
                }

                params[*num_params] = node;
                (*num_params)++;

                if(*num_params >= PARAMS_MAX) {
                    parser_err_msg(info, "overflow parametor number for method call");
                    return FALSE;
                }

                if(*info->p == '@') {
                    info->p++;
                    while(isalnum(*info->p) || *info->p == '_') {
                        info->p++;
                    }
                    skip_spaces_and_lf(info);
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
                    parser_err_msg(info, "unexpected the source end");
                    info->err_num++;
                    break;
                }
                else {
                    parser_err_msg(info, "Clover2 requires , or ) for method call");
                    info->err_num++;
                    break;
                }
            }
        }
    }

    /// simple lambda params ///
    if(*info->p == '{') {
        info->p++;
        skip_spaces_and_lf(info);

        unsigned int node = 0;
        if(!parse_simple_lambda_params(&node, info, FALSE)) {
            return FALSE;
        }

        if(node == 0) {
            parser_err_msg(info, "require expression");
            info->err_num++;
            return TRUE;
        }

        params[*num_params] = node;
        (*num_params)++;

        if(*num_params >= PARAMS_MAX) {
            parser_err_msg(info, "overflow parametor number for method call");
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL parse_command_method_params(int* num_params, unsigned int* params, sParserInfo* info, BOOL class_method, char* method_name)
{
    *num_params = 0;

    if(*info->p == ';' || *info->p == '\n') {
    }
    else if(*info->p != '\0') {
        while(1) {
            sBuf param;

            sBuf_init(&param);

            BOOL squort = FALSE;
            BOOL dquort = FALSE;

            while(1) {
                if(!squort && *info->p == '$') {
                    info->p++;

                    sBuf env_name;
                    sBuf_init(&env_name);

                    if(*info->p == '{') {
                        info->p++;

                        while(1) {
                            if(*info->p == '}') {
                                info->p++;
                                break;
                            }
                            else if(*info->p == '\0') {
                                parser_err_msg(info, "require } to close ${ENV}");
                                info->err_num++;
                                break;
                            }
                            else {
                                sBuf_append_char(&env_name, *info->p);
                                info->p++;
                            }
                        }
                    }
                    else {
                        while(isalnum(*info->p) || *info->p == '_') {
                            sBuf_append_char(&env_name, *info->p);
                            info->p++;
                        }
                    }

                    char* env = getenv(env_name.mBuf);

                    if(env) {
                        sBuf_append(&param, env, strlen(env));
                    }

                    MFREE(env_name.mBuf);
                }
                else if(*info->p == '\\') {
                    info->p++;
                    sBuf_append_char(&param, *info->p);
                    info->p++;
                }
                else if(!squort && *info->p == '"') {
                    info->p++;
                    dquort = !dquort;
                }
                else if(!dquort && *info->p == '\'') {
                    info->p++;
                    squort = !squort;
                }
                else if(squort || dquort) {
                    sBuf_append_char(&param, *info->p);
                    info->p++;
                }
                else if(*info->p == ' ' || *info->p == '\t' || *info->p == '\n' || *info->p == ';' || *info->p == '\0' || *info->p == '|' || *info->p == '&') 
                {
                    break;
                }
                else {
                    sBuf_append_char(&param, *info->p);
                    info->p++;
                }
            }
            skip_spaces(info);

            if(param.mLen > 0) {
                unsigned int node = 0;
                node = sNodeTree_create_string_value(MANAGED param.mBuf, NULL, NULL, 0, info);

                sNodeType* command_class = create_node_type_with_class_name("Command");

                MASSERT(command_class != NULL);

                unsigned int params2[PARAMS_MAX];
                int num_params2 = 1;

                params2[0] = node;

                node = sNodeTree_create_class_method_call(command_class, "expandArg", params2, num_params2, info);

                params[*num_params] = node;
                (*num_params)++;

                if(*num_params >= PARAMS_MAX) {
                    parser_err_msg(info, "overflow parametor number for method call");
                    return FALSE;
                }
            }
            else {
                MFREE(param.mBuf);
            }

            if(*info->p == '\0' || *info->p == '\n' || *info->p == ';' 
                || *info->p == '|' || *info->p == '&') 
            {
                break;
            }
        }
    }

    if(class_method) {
        sCLClass* command_class = get_class("Command");

        if(!class_method_name_existance(command_class, method_name)) {
            params[*num_params] = sNodeTree_create_string_value(MANAGED MSTRDUP("--controlling-terminal"), NULL, NULL, 0, info);
            (*num_params)++;

            if(*num_params >= PARAMS_MAX) {
                parser_err_msg(info, "overflow parametor number for method call");
                return FALSE;
            }
        }
    }
    else {
        sCLClass* command_class = get_class("Command");

        if(!none_class_method_name_existance(command_class, method_name)) {
            params[*num_params] = sNodeTree_create_string_value(MANAGED MSTRDUP("--controlling-terminal"), NULL, NULL, 0, info);
            (*num_params)++;

            if(*num_params >= PARAMS_MAX) {
                parser_err_msg(info, "overflow parametor number for method call");
                return FALSE;
            }
        }
    }

    return TRUE;
}

static BOOL get_number(BOOL minus, unsigned int* node, sParserInfo* info)
{
    const int buf_size = 128;
    char buf[128+1];
    char* p2 = buf;

    if(minus) {
        *p2 = '-';
        p2++;
    }

    if(isdigit(*info->p)) {
        while(isdigit(*info->p)) {
            *p2++ = *info->p;
            info->p++;

            if(p2 - buf >= buf_size) {
                parser_err_msg(info, "overflow node of number");
                return FALSE;
            }
        }
        *p2 = 0;
        skip_spaces_and_lf(info);

        if(*info->p == '.' && isdigit(*(info->p+1))) {
            info->p++;
            *p2++ = '.';

            if(p2 - buf >= buf_size) {
                parser_err_msg(info, "overflow node of number");
                return FALSE;
            }

            while(isdigit(*info->p)) {
                *p2++ = *info->p;
                info->p++;

                if(p2 - buf >= buf_size) {
                    parser_err_msg(info, "overflow node of number");
                    return FALSE;
                }
            }
            *p2 = 0;

            if(*info->p == 'f') {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_float_value(atof(buf), 0, 0, 0, info);
            }
            else if(*info->p == 'F') {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_cfloat_value(atof(buf), 0, 0, 0, info);
            }
            else if(*info->p == 'D') {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_cdouble_value(strtod(buf, NULL), 0, 0, 0, info);
            }
            else {
                *node = sNodeTree_create_double_value(strtod(buf, NULL), 0, 0, 0, info);
            }

            skip_spaces_and_lf(info);
        }
        else if(*info->p == 'y') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_byte_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'Y') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_cbyte_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'u' && *(info->p+1) == 'y') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_ubyte_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'U' && *(info->p+1) == 'Y') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_cubyte_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 's') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_short_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'S') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_cshort_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'u' && *(info->p+1) == 's') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_ushort_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'U' && *(info->p+1) == 'S') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_cushort_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'l') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_long_value(atol(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'L') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_clong_value(atol(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'u' && *(info->p+1) == 'l') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_ulong_value(atol(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'U' && *(info->p+1) == 'L') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_culong_value(atol(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'u') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_uint_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'U') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_cuint_value(atoi(buf), 0, 0, 0, info);
        }
        else if(*info->p == 'I') {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_cint_value(atoi(buf), 0, 0, 0, info);
        }
        else {
            *node = sNodeTree_create_int_value(atoi(buf), 0, 0, 0, info);
        }
    }
    else {
        parser_err_msg(info, "require digits after + or -");
        info->err_num++;

        *node = 0;
    }

    return TRUE;
}

static BOOL get_hex_number(unsigned int* node, sParserInfo* info)
{
    int buf_size = 128;
    char buf[128+1];
    char* p = buf;

    *p++ = '0';
    *p++ = 'x';

    while((*info->p >= '0' && *info->p <= '9') || (*info->p >= 'a' && *info->p <= 'f') || (*info->p >= 'A' && *info->p <= 'F')) 
    {
        *p++ = *info->p;
        info->p++;

        if(p - buf >= buf_size-1) {
            parser_err_msg(info, "overflow node of number");
            return FALSE;
        }
    }
    *p = 0;
    skip_spaces_and_lf(info);

    unsigned clint64 value = strtoll(buf, NULL, 0);

    if(*info->p == 'y') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_byte_value((char)value, 0, 0, 0, info);
    }
    else if(*info->p == 'Y') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cbyte_value((char)value, 0, 0, 0, info);
    }
    else if(*info->p == 'u' && *(info->p+1) == 'y') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_ubyte_value((unsigned char)value, 0, 0, 0, info);
    }
    else if(*info->p == 'U' && *(info->p+1) == 'Y') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cubyte_value((unsigned char)value, 0, 0, 0, info);
    }
    else if(*info->p == 's') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_short_value((short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'S') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cshort_value((short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'u' && *(info->p+1) == 's') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_ushort_value((unsigned short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'U' && *(info->p+1) == 'S') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cushort_value((unsigned short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'l') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_long_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'L') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_ulong_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'u' && *(info->p+1) == 'l') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_ulong_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'U' && *(info->p+1) == 'L') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_culong_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'u') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_uint_value((unsigned int)value, 0, 0, 0, info);
    }
    else if(*info->p == 'U') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cuint_value((unsigned int)value, 0, 0, 0, info);
    }
    else if(*info->p == 'I') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cint_value((int)value, 0, 0, 0, info);
    }
    else {
        *node = sNodeTree_create_int_value((int)value, 0, 0, 0, info);
    }

    return TRUE;
}

static BOOL get_oct_number(unsigned int* node, sParserInfo* info)
{
    int buf_size = 128;
    char buf[128+1];
    char* p = buf;

    *p++ = '0';

    while(*info->p >= '0' && *info->p <= '7') {
        *p++ = *info->p++;

        if(p - buf >= buf_size-1) {
            parser_err_msg(info, "overflow node of number");
            return FALSE;
        }
    }
    *p = 0;
    skip_spaces_and_lf(info);

    unsigned clint64 value = strtoul(buf, NULL, 0);

    if(*info->p == 'y') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_byte_value((char)value, 0, 0, 0, info);
    }
    else if(*info->p == 'Y') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cbyte_value((char)value, 0, 0, 0, info);
    }
    else if(*info->p == 'u' && *(info->p+1) == 'y') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_ubyte_value((unsigned char)value, 0, 0, 0, info);
    }
    else if(*info->p == 'U' && *(info->p+1) == 'Y') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cubyte_value((unsigned char)value, 0, 0, 0, info);
    }
    else if(*info->p == 's') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_short_value((short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'S') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cshort_value((short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'u' && *(info->p+1) == 's') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_ushort_value((unsigned short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'U' && *(info->p+1) == 'S') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cushort_value((unsigned short)value, 0, 0, 0, info);
    }
    else if(*info->p == 'l') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_long_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'L') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_clong_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'u' && *(info->p+1) == 'l') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_ulong_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'U' && *(info->p+1) == 'L') {
        info->p+=2;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_culong_value(value, 0, 0, 0, info);
    }
    else if(*info->p == 'u')  {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_uint_value((unsigned int)value, 0, 0, 0, info);
    }
    else if(*info->p == 'U')  {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cuint_value((unsigned int)value, 0, 0, 0, info);
    }
    else if(*info->p == 'I') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_cint_value((int)value, 0, 0, 0, info);
    }
    else {
        *node = sNodeTree_create_int_value((int)value, 0, 0, 0, info);
    }

    return TRUE;
}

static BOOL if_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for if");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);
    expect_next_character_with_one_forward("{", info);

    sNodeBlock* if_node_block = NULL;
    if(!parse_block(ALLOC &if_node_block, info, NULL, FALSE, FALSE)) {
        return FALSE;
    }

    unsigned int elif_expression_nodes[ELIF_NUM_MAX];
    memset(elif_expression_nodes, 0, sizeof(unsigned int)*ELIF_NUM_MAX);

    sNodeBlock* elif_node_blocks[ELIF_NUM_MAX];
    memset(elif_node_blocks, 0, sizeof(sNodeBlock*)*ELIF_NUM_MAX);

    int elif_num = 0;

    sNodeBlock* else_node_block = NULL;

    while(1) {
        char* saved_p = info->p;
        int saved_sline = info->sline;

        char buf[VAR_NAME_MAX];

        /// else ///
        if(!isalpha(*info->p)) {
            break;
        }
        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }

        if(strcmp(buf, "else") == 0) {
            expect_next_character_with_one_forward("{", info);

            if(!parse_block(ALLOC &else_node_block, info, NULL, FALSE, FALSE)) {
                return FALSE;
            }
            break;
        }
        else if(strcmp(buf, "elif") == 0) {
            expect_next_character_with_one_forward("(", info);

            /// expression ///
            if(!expression(&elif_expression_nodes[elif_num], info)) {
                return FALSE;
            }

            if(elif_expression_nodes[elif_num] == 0) {
                parser_err_msg(info, "require elif expression");
                info->err_num++;
                return TRUE;
            }

            expect_next_character_with_one_forward(")", info);
            expect_next_character_with_one_forward("{", info);

            if(!parse_block(ALLOC &elif_node_blocks[elif_num], info, NULL, FALSE, FALSE)) {
                return FALSE;
            }

            elif_num++;
            if(elif_num >= ELIF_NUM_MAX) {
                parser_err_msg(info, "overflow elif num");
                info->err_num++;
                return FALSE;
            }
        }
        else {
            info->p = saved_p;
            info->sline = saved_sline;
            break;
        }
    }

    *node = sNodeTree_if_expression(expression_node, MANAGED if_node_block, elif_expression_nodes, elif_node_blocks, elif_num, MANAGED else_node_block, info);

    return TRUE;
}

static BOOL while_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for while");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);
    expect_next_character_with_one_forward("{", info);

    sNodeBlock* while_node_block = NULL;
    if(!parse_block(ALLOC &while_node_block, info, NULL, FALSE, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_while_expression(expression_node, MANAGED while_node_block, info);

    return TRUE;
}

static BOOL for_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression1 ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for \"for\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(";", info);

    /// expression2 ///
    unsigned int expression_node2 = 0;
    if(!expression(&expression_node2, info)) {
        return FALSE;
    }

    if(expression_node2 == 0) {
        parser_err_msg(info, "require expression2 for \"for\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(";", info);

    /// expression3 ///
    unsigned int expression_node3 = 0;
    if(!expression(&expression_node3, info)) {
        return FALSE;
    }

    if(expression_node3 == 0) {
        parser_err_msg(info, "require expression3 for \"for\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);
    expect_next_character_with_one_forward("{", info);

    sNodeBlock* for_node_block = NULL;
    if(!parse_block(ALLOC &for_node_block, info, NULL, FALSE, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_for_expression(expression_node, expression_node2, expression_node3, MANAGED for_node_block, info);

    return TRUE;
}

static BOOL when_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression1 ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for when");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);
    expect_next_character_with_one_forward("{", info);
    skip_spaces_and_lf(info);

    unsigned int value_nodes[WHEN_BLOCK_MAX][WHEN_BLOCK_MAX];
    int num_values[WHEN_BLOCK_MAX];
    sNodeBlock* when_blocks[WHEN_BLOCK_MAX];
    sNodeType* when_types[WHEN_BLOCK_MAX];
    sNodeType* when_types2[WHEN_BLOCK_MAX];
    BOOL when_match[WHEN_BLOCK_MAX];
    sNodeBlock* else_block = NULL;
    int num_when_block = 0;

    memset(when_types, 0, sizeof(sNodeType*)*WHEN_BLOCK_MAX);
    memset(when_types2, 0, sizeof(sNodeType*)*WHEN_BLOCK_MAX);
    memset(when_match, 0, sizeof(BOOL*)*WHEN_BLOCK_MAX);

    /// value1 ///
    while(1) {
        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "Unexpected the source end");
            info->err_num++;
            return TRUE;
        }

        if(*info->p == 'i' && *(info->p+1) == 's') {
            info->p+=2;
            skip_spaces_and_lf(info);

            sNodeType* node_type = NULL;
            if(!parse_type(&node_type, info)) {
                return FALSE;
            }

            when_types[num_when_block] = node_type;

            expect_next_character_with_one_forward("{", info);

            sNodeBlock* when_block = NULL;
            if(!parse_block(ALLOC &when_block, info, NULL, FALSE, FALSE)) {
                return FALSE;
            }
            when_blocks[num_when_block] = when_block;

            num_values[num_when_block] = 1;

            num_when_block++;

            if(num_when_block >= WHEN_BLOCK_MAX) {
                parser_err_msg(info, "overflow when block number");
                return FALSE;
            }
        }
        else if(*info->p == '!' && *(info->p+1) == 'i' && *(info->p+2) == 's') {
            info->p+=3;
            skip_spaces_and_lf(info);

            sNodeType* node_type = NULL;
            if(!parse_type(&node_type, info)) {
                return FALSE;
            }

            when_types2[num_when_block] = node_type;

            expect_next_character_with_one_forward("{", info);

            sNodeBlock* when_block = NULL;
            if(!parse_block(ALLOC &when_block, info, NULL, FALSE, FALSE)) {
                return FALSE;
            }
            when_blocks[num_when_block] = when_block;

            num_values[num_when_block] = 1;

            num_when_block++;

            if(num_when_block >= WHEN_BLOCK_MAX) {
                parser_err_msg(info, "overflow when block number");
                return FALSE;
            }
        }
        else if(*info->p == 'e' && *(info->p+1) == 'l' && *(info->p+2) == 's' && *(info->p+3) == 'e') {
            info->p+=4;
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(else_block != NULL) {
                parser_err_msg(info, "else block should be one");
                info->err_num++;
                return TRUE;
            }

            if(!parse_block(ALLOC &else_block, info, NULL, FALSE, FALSE)) {
                return FALSE;
            }
        }
        else if(*info->p == 'm' && *(info->p+1) == 'a' && *(info->p+2) == 't' && *(info->p+3) == 'c' && *(info->p+4) == 'h') 
        {
            info->p+=5;
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("(", info);

            int num_value = 0;

            while(1) {
                unsigned int node = 0;
                if(!expression(&node, info)) {
                    return FALSE;
                }

                if(node == 0) {
                    parser_err_msg(info, "require expression for when");
                    info->err_num++;
                    return TRUE;
                }

                value_nodes[num_when_block][num_value] = node;
                num_value++;

                if(num_value >= WHEN_BLOCK_MAX) {
                    parser_err_msg(info, "overflow when value number");
                    return FALSE;
                }

                num_values[num_when_block] = num_value;

                if(*info->p == '\0') {
                    parser_err_msg(info, "Unexpected the source end");
                    info->err_num++;
                    return TRUE;
                }
                else if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == ')') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
            }

            expect_next_character_with_one_forward("{", info);

            sNodeBlock* when_block = NULL;
            if(!parse_block(ALLOC &when_block, info, NULL, FALSE, FALSE)) {
                return FALSE;
            }
            when_blocks[num_when_block] = when_block;
            when_match[num_when_block] = TRUE;

            num_when_block++;

            if(num_when_block >= WHEN_BLOCK_MAX) {
                parser_err_msg(info, "overflow when block number");
                return FALSE;
            }
        }
        else if(*info->p == 'c' && *(info->p+1) == 'a' && *(info->p+2) == 's' && *(info->p+3) == 'e') {
            info->p+=4;
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("(", info);

            int num_value = 0;

            while(1) {
                unsigned int node = 0;
                if(!expression(&node, info)) {
                    return FALSE;
                }

                if(node == 0) {
                    parser_err_msg(info, "require expression for when");
                    info->err_num++;
                    return TRUE;
                }

                value_nodes[num_when_block][num_value] = node;
                num_value++;

                if(num_value >= WHEN_BLOCK_MAX) {
                    parser_err_msg(info, "overflow when value number");
                    return FALSE;
                }

                num_values[num_when_block] = num_value;

                if(*info->p == '\0') {
                    parser_err_msg(info, "Unexpected the source end");
                    info->err_num++;
                    return TRUE;
                }
                else if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == ')') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
            }

            expect_next_character_with_one_forward("{", info);

            sNodeBlock* when_block = NULL;
            if(!parse_block(ALLOC &when_block, info, NULL, FALSE, FALSE)) {
                return FALSE;
            }
            when_blocks[num_when_block] = when_block;

            num_when_block++;

            if(num_when_block >= WHEN_BLOCK_MAX) {
                parser_err_msg(info, "overflow when block number");
                return FALSE;
            }
        }
        else {
            parser_err_msg(info, "when requires is or !is or case");
            return FALSE;
        }
    }

    *node = sNodeTree_when_expression(expression_node, value_nodes, num_values, when_blocks, num_when_block, else_block, when_types, when_types2, when_match, info);

    return TRUE;
}

static BOOL return_expression(unsigned int* node, sParserInfo* info)
{
/*
    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);
    }
*/

    unsigned int expression_node = 0;
    if(*info->p != ';') {
        /// expression ///
        if(!expression(&expression_node, info)) {
            return FALSE;
        }
    }

/*
    if(*info->p == ')') {
        info->p++;
        skip_spaces_and_lf(info);
    }
*/

    *node = sNodeTree_create_return_expression(expression_node, info);

    return TRUE;
}

static BOOL new_expression(unsigned int* node, sParserInfo* info)
{
    sNodeType* node_type = NULL;
    unsigned int array_num = 0;

    if(!parse_type_for_new(&node_type, &array_num, info)) {
        return FALSE;
    }

    unsigned int params[PARAMS_MAX];
    int num_params = 0;

    if(!parse_method_params(&num_params, params, info)) {
        return FALSE;
    }

    *node = sNodeTree_create_new_operator(node_type, params, num_params, array_num, info);

    return TRUE;
}

static BOOL throw_expression(unsigned int* node, sParserInfo* info)
{
    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, info)) {
        return FALSE;
    }

    *node = sNodeTree_create_throw_expression(expression_node, info);

    return TRUE;
}

static BOOL expect_next_word(char* word, sParserInfo* info)
{
    char buf[32];

    if(!parse_word(buf, 32, info, TRUE, FALSE)) {
        return FALSE;
    }

    if(strcmp(buf, word) != 0) {
        parser_err_msg(info, "Expected next word is %s\n", word);
        info->err_num++;
    }

    return TRUE;
}

static BOOL parse_param(sParserParam* param, sParserInfo* info)
{
    /// variable name ///
    if(!parse_word(param->mName, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    expect_next_character_with_one_forward(":", info);

    if(!parse_type(&param->mType, info)) {
        return FALSE;
    }

    /// get default argment. ///
    if(*info->p == '=') {
        info->p++;
        skip_spaces_and_lf(info);

        char* p = info->p;

        unsigned int node = 0;
        if(!expression(&node, info)) {
            return FALSE;
        }

        char* p2 = info->p;

        if(p2 - p > METHOD_DEFAULT_PARAM_MAX) {
            parser_err_msg(info, "overflow method default param character");
            return FALSE;
        }

        memcpy(param->mDefaultValue, p, p2 - p);
        param->mDefaultValue[p2 -p] = '\0';
    }
    else {
        param->mDefaultValue[0] = '\0';
    }

    return TRUE;
}

/// character_type --> 0: () 1: ||
BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info, int character_type)
{
    if((character_type == 0 && *info->p == ')') || (character_type == 1 && *info->p == '|')) {
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

        if(*num_params >= PARAMS_MAX) {
            parser_err_msg(info, "overflow params number");
            return FALSE;
        }

        if(*info->p == ',') {
            info->p++;
            skip_spaces_and_lf(info);
        }
        else if((character_type == 0 && *info->p == ')') || (character_type == 1 && *info->p == '|')) {
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
            parser_err_msg(info, "Unexpected character(%c). It is required to ',' or ')' or '|' character", *info->p);
            if(*info->p == '\n') {
                info->sline++;
            }
            info->p++;

            info->err_num++;
        }
    }

    return TRUE;
}

BOOL parse_params_and_entry_to_lvtable(struct sParserParamStruct* params, int* num_params, sParserInfo* info, sVarTable** new_table, sVarTable* parent_lv_table, int character_type)
{
    if(!parse_params(params, num_params, info, character_type)) {
        return FALSE;
    }

    *new_table = init_block_vtable(parent_lv_table);

    int i;
    for(i=0; i<*num_params; i++) {
        sParserParam* param = params + i;

        if(!add_variable_to_table(*new_table, param->mName, param->mType, FALSE)) {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL try_expression(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("{", info);

    /// try ///
    sNodeBlock* try_node_block = NULL;
    if(!parse_block(ALLOC &try_node_block, info, NULL, FALSE, FALSE)) {
        return FALSE;
    }

    sNodeBlock* catch_node_block = NULL;
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    int num_params = 0;
    params[0].mName[0] = '\0';

    if(info->err_num == 0) { // for interpreter completion
        /// catch ///
        expect_next_word("catch", info);

        expect_next_character_with_one_forward("(", info);

        /// parse_params ///
        sVarTable* new_table = NULL;

        if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, info->lv_table, 0)) {
            return FALSE;
        }

        if(num_params != 1 || !is_exception_type(params[0].mType)) {
            parser_err_msg(info, "Require the type of a catch param should be a exception type");
            info->err_num++;
        }

        expect_next_character_with_one_forward("{", info);

        if(!parse_block(ALLOC &catch_node_block, info, new_table, FALSE, FALSE)) {
            return FALSE;
        }
    }

    *node = sNodeTree_try_expression(MANAGED try_node_block, MANAGED catch_node_block, params[0].mName, info);

    return TRUE;
}

BOOL parse_class_type(sCLClass** klass, sParserInfo* info)
{
    char class_name[CLASS_NAME_MAX];

    if(!parse_word(class_name, CLASS_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    if(strcmp(class_name, "SELF") == 0) {
        *klass = info->klass;
    }
    else {
        *klass = get_class_with_load_and_initialize(class_name);
    }

    if(*klass == NULL) {
        parser_err_msg(info, "%s is not defined class", class_name);
        info->err_num++;
    }

    return TRUE;
}

BOOL parse_type(sNodeType** result_type, sParserInfo* info)
{
    char type_name[CLASS_NAME_MAX];

    *result_type = NULL;

    if(!parse_word(type_name, CLASS_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    int generics_num = 0;

    int i;
    for(i=0; i<info->method_generics_info.mNumParams; i++) {
        if(strcmp(type_name, info->method_generics_info.mParamNames[i]) == 0) {
            *result_type = create_node_type_with_method_generics_number(i);
            break;
        }
    }

    for(i=0; i<info->generics_info.mNumParams; i++) {
        if(strcmp(type_name, info->generics_info.mParamNames[i]) == 0) {
            *result_type = create_node_type_with_generics_number(i);
            break;
        }
    }

    if(*result_type == NULL) {
        if(strcmp(type_name, "SELF") == 0) {
            *result_type = create_node_type_with_class_pointer(info->klass);


            if(*info->p != '<') {
                int i;
                for(i=0; i< info->generics_info.mNumParams; i++) {
                    (*result_type)->mGenericsTypes[i] = create_node_type_with_class_pointer(info->generics_info.mInterface[i]);
                }

                generics_num = info->generics_info.mNumParams;
            }
        }
        else {
            *result_type = create_node_type_with_class_name(type_name);
        }
    }

    if(*result_type == NULL) {
        *result_type = alloc_node_type();
    }

    if(*result_type != NULL) {
        (*result_type)->mNullable = FALSE;
    }

    if(strcmp(type_name, "lambda") == 0) {
        if(*info->p == '[' && *(info->p+1) == ']') {
            info->p+=2;
            skip_spaces_and_lf(info);

            (*result_type)->mArray = TRUE;
        }

        if(*info->p == '?') {
            info->p++;
            skip_spaces_and_lf(info);

            (*result_type)->mNullable = TRUE;
        }
    }

    if(*result_type == NULL || (*result_type)->mClass == NULL) {
        parser_err_msg(info, "%s is not defined class", type_name);
        info->err_num++;
    }

    if(strcmp(type_name, "lambda") == 0) {
        sNodeBlockType* node_block_type = alloc_node_block_type();

        if(*info->p == '(') {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == ')') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else {
                while(1) {
                    sNodeType* node_type = NULL;
                    if(!parse_type(&node_type, info)) {
                        return FALSE;
                    }

                    node_block_type->mParams[node_block_type->mNumParams] = node_type;
                    node_block_type->mNumParams++;

                    if(node_block_type->mNumParams >= PARAMS_MAX) {
                        parser_err_msg(info, "oveflow block object type params");
                        return FALSE;
                    }

                    if(*info->p == ')') {
                        info->p++;
                        skip_spaces_and_lf(info);
                        break;
                    }
                    else if(*info->p == ',') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    else {
                        parser_err_msg(info, "invalid character in block type name(%c)", *info->p);
                        break;
                    }
                }
            }
        }

        if(*info->p == ':') {
            info->p++;
            skip_spaces_and_lf(info);

            sNodeType* node_type = NULL;
            if(!parse_type(&node_type, info)) {
                return FALSE;
            }

            node_block_type->mResultType = node_type;
        }
        else {
            node_block_type->mResultType = create_node_type_with_class_name("Null");
        }

        (*result_type)->mBlockType = node_block_type;
    }
    else if(*info->p == '<' && *(info->p+1) != '<' && *(info->p+1) != '=') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            if(!parse_type(&(*result_type)->mGenericsTypes[generics_num], info)) {
                return FALSE;
            }

            generics_num++;

            if(generics_num >= GENERICS_TYPES_MAX) {
                parser_err_msg(info, "overflow generics parametor number");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '>') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else {
                parser_err_msg(info, "invalid character(%c) in generics types", *info->p);
                info->err_num++;
                break;
            }
        }
    }

    if(*info->p == '[' && *(info->p+1) == ']') {
        info->p+=2;
        skip_spaces_and_lf(info);

        (*result_type)->mArray = TRUE;
    }


    if(*result_type != NULL) {
        (*result_type)->mNumGenericsTypes = generics_num;
    }

    /// nullable ///
    if(*info->p == '?') {
        info->p++;
        skip_spaces_and_lf(info);

        (*result_type)->mNullable = TRUE;
    }

    /// anotation ///
    if(*info->p == '@') {
        info->p++;

        if(isalpha(*info->p)) {
            while(isalnum(*info->p) || *info->p == '-' || *info->p == '_' || *info->p == '[' || *info->p == ']') {
                info->p++;
            }
            skip_spaces_and_lf(info);
        }
        else {
            parser_err_msg(info, "require alphabets for anotation");
            info->err_num++;
        }
    }

    /// check generics type ///
    if(info->err_num == 0) {
        sCLClass* klass = (*result_type)->mClass;

        int i;
        for(i=0; i<generics_num; i++) {
            sCLClass* left_type = get_class_with_load_and_initialize(CONS_str(&klass->mConst, klass->mGenericsParamTypeOffsets[i]));

            sCLClass* right_type = (*result_type)->mGenericsTypes[i]->mClass;

            sCLClass* right_type2;
            solve_method_generics_for_variable_to_class(right_type, &right_type2, info);

            sCLClass* right_type3;
            solve_generics_for_variable_to_class(right_type2, &right_type3, info);

            if(!check_implemented_methods_for_interface(left_type, right_type3)) {
                parser_err_msg(info, "%s is not implemented %s interface" , CLASS_NAME(right_type2), CLASS_NAME(left_type));
                info->err_num++;
            }
        }
    }

    return TRUE;
}

BOOL parse_type_for_new(sNodeType** result_type, unsigned int* array_num, sParserInfo* info)
{
    char type_name[CLASS_NAME_MAX];

    *result_type = NULL;

    if(!parse_word(type_name, CLASS_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    int i;
    for(i=0; i<info->generics_info.mNumParams; i++) {
        if(strcmp(type_name, info->generics_info.mParamNames[i]) == 0) {
            *result_type = create_node_type_with_generics_number(i);
            break;
        }
    }

    for(i=0; i<info->method_generics_info.mNumParams; i++) {
        if(strcmp(type_name, info->method_generics_info.mParamNames[i]) == 0) {
            *result_type = create_node_type_with_method_generics_number(i);
            break;
        }
    }

    int generics_num = 0;

    if(*result_type == NULL) {
        if(strcmp(type_name, "SELF") == 0) {
            *result_type = create_node_type_with_class_pointer(info->klass);

            if(*info->p != '<') {
                int i;
                for(i=0; i< info->generics_info.mNumParams; i++) {
                    (*result_type)->mGenericsTypes[i] = create_node_type_with_class_pointer(info->generics_info.mInterface[i]);
                }

                generics_num = info->generics_info.mNumParams;
            }
        }
        else {
            *result_type = create_node_type_with_class_name(type_name);
        }
    }

    if(*result_type == NULL || (*result_type)->mClass == NULL) {
        parser_err_msg(info, "%s is not defined class", type_name);
        info->err_num++;
        return TRUE;
    }

    *array_num = 0;

    if(type_identify_with_class_name(*result_type, "lambda")) {
        if(*info->p == '[') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!expression(array_num, info)) {
                return FALSE;
            }

            expect_next_character_with_one_forward("]", info);

            (*result_type)->mArray = TRUE;
        }

        sNodeBlockType* node_block_type = alloc_node_block_type();

        if(*info->p == '(') {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == ')') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else {
                while(1) {
                    sNodeType* node_type = NULL;
                    if(!parse_type(&node_type, info)) {
                        return FALSE;
                    }

                    node_block_type->mParams[node_block_type->mNumParams] = node_type;
                    node_block_type->mNumParams++;

                    if(node_block_type->mNumParams >= PARAMS_MAX) {
                        parser_err_msg(info, "oveflow block object type params");
                        return FALSE;
                    }

                    if(*info->p == ')') {
                        info->p++;
                        skip_spaces_and_lf(info);
                        break;
                    }
                    else if(*info->p == ',') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    else {
                        parser_err_msg(info, "invalid character in block type name(%c)", *info->p);
                        break;
                    }
                }
            }
        }

        if(*info->p == ':') {
            info->p++;
            skip_spaces_and_lf(info);

            sNodeType* node_type = NULL;
            if(!parse_type(&node_type, info)) {
                return FALSE;
            }

            node_block_type->mResultType = node_type;
        }
        else {
            node_block_type->mResultType = create_node_type_with_class_name("Null");
        }

        (*result_type)->mBlockType = node_block_type;
    }
    else if(*info->p == '<' && *(info->p+1) != '<' && *(info->p+1) != '=') {
        info->p++;
        skip_spaces_and_lf(info);

        while(1) {
            if(!parse_type(&(*result_type)->mGenericsTypes[generics_num], info)) {
                return FALSE;
            }

            generics_num++;

            if(generics_num >= GENERICS_TYPES_MAX) {
                parser_err_msg(info, "overflow generics parametor number");
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '>') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else {
                parser_err_msg(info, "invalid character(%c) in generics types", *info->p);
                info->err_num++;
                break;
            }
        }
    }

    if(*info->p == '[') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression(array_num, info)) {
            return FALSE;
        }

        expect_next_character_with_one_forward("]", info);

        (*result_type)->mArray = TRUE;
    }

    (*result_type)->mNumGenericsTypes = generics_num;

    /// check generics type ///
    sCLClass* klass = (*result_type)->mClass;

    for(i=0; i<generics_num; i++) {
        int generics_paramType_offset = klass->mGenericsParamTypeOffsets[i];
        sCLClass* left_type = get_class_with_load_and_initialize(CONS_str(&klass->mConst, generics_paramType_offset));

        sCLClass* right_type = (*result_type)->mGenericsTypes[i]->mClass;

        sCLClass* right_type2;
        solve_method_generics_for_variable_to_class(right_type, &right_type2, info);

        sCLClass* right_type3;
        solve_generics_for_variable_to_class(right_type2, &right_type3, info);

        if(!check_implemented_methods_for_interface(left_type, right_type3)) {
            parser_err_msg(info, "%s is not implemented %s interface" , CLASS_NAME(right_type2), CLASS_NAME(left_type));
            info->err_num++;
        }
    }

    return TRUE;
}

static BOOL is_assign_operator(sParserInfo* info) 
{
    return (*info->p == '+' && *(info->p+1) == '=')
        || (*info->p == '-' && *(info->p+1) == '=')
        || (*info->p == '*' && *(info->p+1) == '=')
        || (*info->p == '/' && *(info->p+1) == '=')
        || (*info->p == '%' && *(info->p+1) == '=')
        || (*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) == '=')
        || (*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) == '=')
        || (*info->p == '&' && *(info->p+1) == '=')
        || (*info->p == '^' && *(info->p+1) == '=')
        || (*info->p == '|' && *(info->p+1) == '=');
}

static BOOL assign_operator(unsigned int* node, sParserInfo* info)
{
    if(*info->p == '+' && *(info->p+1) == '+') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = sNodeTree_create_int_value(1, 0, 0, 0, info);

        *node = sNodeTree_create_operand(kOpAdd, *node, right, 0, info);
    }
    else if(*info->p == '-' && *(info->p+1) == '-') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = sNodeTree_create_int_value(1, 0, 0, 0, info);

        *node = sNodeTree_create_operand(kOpSub, *node, right, 0, info);
    }
    else if(*info->p == '+' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpAdd, *node, right, 0, info);
    }
    else if(*info->p == '-' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpSub, *node, right, 0, info);;
    }
    else if(*info->p == '*' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpMult, *node, right, 0, info);
    }
    else if(*info->p == '/' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpDiv, *node, right, 0, info);
    }
    else if(*info->p == '%' && *(info->p+1) == '=') {
        info->p += 2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpMod, *node, right, 0, info);
    }
    else if(*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) == '=') {
        info->p += 3;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpLeftShift, *node, right, 0, info);
    }
    else if(*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) == '=') {
        info->p += 3;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpRightShift, *node, right, 0, info);
    }
    else if(*info->p == '&' && *(info->p+1) == '=') {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpAnd, *node, right, 0, info);
    }
    else if(*info->p == '^' && *(info->p+1) == '=') {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpXor, *node, right, 0, info);
    }
    else if(*info->p == '|' && *(info->p+1) == '=') {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int right = 0;
        if(!expression(&right, info)) {
            return FALSE;
        }

        if(right == 0) {
            parser_err_msg(info, "require right value for operator +=");
            info->err_num++;
        }

        *node = sNodeTree_create_operand(kOpOr, *node, right, 0, info);
    }

    return TRUE;
}

static BOOL postposition_operator(unsigned int* node, sParserInfo* info, int* num_method_chains, unsigned int max_method_chains_node[METHOD_CHAIN_MAX])
{
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '.' && *(info->p+1) == '.') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int tail = 0;
            if(!expression(&tail, info)) {
                return FALSE;
            }

            *node = sNodeTree_create_range(*node, tail, info);
        }
        /// call method or access field ///
        else if(*info->p == '.' && *(info->p+1) != '.') {
            info->p++;
            skip_spaces_and_lf(info);

            if(info->get_type_for_interpreter && *info->p == '\0') {
                return TRUE;
            }

            if(isalpha(*info->p) || *info->p == '_') {
                char buf[METHOD_NAME_MAX];

                if(!parse_word(buf, METHOD_NAME_MAX, info, TRUE, FALSE)) {
                    return FALSE;
                }
                skip_spaces_and_lf(info);

                if(info->get_type_for_interpreter && *info->p == '\0') {
                    return TRUE;
                }

                /// call methods ///
                if(*info->p == '(' || *info->p == '{') {
                    unsigned int params[PARAMS_MAX];
                    int num_params = 0;

                    if(!parse_method_params(&num_params, params, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_method_call(*node, buf, params, num_params, *num_method_chains, info);
                    max_method_chains_node[*num_method_chains] = *node;

                    (*num_method_chains)++;

                    if(*num_method_chains >= METHOD_CHAIN_MAX) {
                        parser_err_msg(info, "overflow method chain");
                        return FALSE;
                    }
                }
                /// access fields ///
                else {
                    if(is_assign_operator(info)) {
                        unsigned int node2 = clone_node(*node);
                        unsigned int node3 = clone_node(*node);

                        /// load field ///
                        *node = sNodeTree_create_fields(buf, node2, info);

                        /// go 
                        if(!assign_operator(node, info)) {
                            return FALSE;
                        }

                        *node = sNodeTree_create_assign_field(buf, node3, *node, info);
                    }
                    else if(*info->p == '=' && *(info->p +1) != '=') {
                        info->p++;
                        skip_spaces_and_lf(info);

                        unsigned int right_node = 0;

                        if(!expression(&right_node, info)) {
                            return FALSE;
                        }

                        if(right_node == 0) {
                            parser_err_msg(info, "Require right value");
                            info->err_num++;

                            *node = 0;
                        }
                        else {
                            *node = sNodeTree_create_assign_field(buf, *node, right_node, info);
                        }
                    }
                    else {
                        *node = sNodeTree_create_fields(buf, *node, info);
                    }
                }
            }
            else {
                parser_err_msg(info, "require method name or field name after .");
                info->err_num++;
                *node = 0;
                break;
            }
        }
        /// access element ///
        else if(*info->p == '[') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int index_node = 0;

            if(!expression(&index_node, info)) {
                return FALSE;
            }

            if(index_node == 0) {
                parser_err_msg(info, "Require index value");
                info->err_num++;

                *node = 0;
            }
            else {
                expect_next_character_with_one_forward("]", info);

                /// calling lambda or closure ///
                if(*info->p == '(') {
                    *node = sNodeTree_create_load_array_element(*node, index_node, info);

                    unsigned int params[PARAMS_MAX];
                    int num_params = 0;

                    if(!parse_method_params(&num_params, params, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_block_call(*node, num_params, params, info);
                }
                else if(is_assign_operator(info)) {
                    unsigned int node2 = clone_node(*node);
                    unsigned int index_node2 = clone_node(index_node);

                    /// load field ///
                    *node = sNodeTree_create_load_array_element(*node, index_node, info);

                    /// go 
                    if(!assign_operator(node, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_store_array_element(node2, index_node2, *node, info);
                }
                else if(*info->p == '=' && *(info->p+1) != '=') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    unsigned int right_node = 0;

                    if(!expression(&right_node, info)) {
                        return FALSE;
                    }

                    if(right_node == 0) {
                        parser_err_msg(info, "Require right value");
                        info->err_num++;

                        *node = 0;
                    }
                    else {
                        *node = sNodeTree_create_store_array_element(*node, index_node, right_node, info);
                    }
                }
                else {
                    *node = sNodeTree_create_load_array_element(*node, index_node, info);
                }
            }
        }
        /// get value from pointer ///
        else if(*info->p == '-' && *(info->p+1) == '>')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            sNodeType* node_type = NULL;

            if(!parse_type(&node_type, info)) {
                return FALSE;
            }

            if(node_type == NULL) {
                parser_err_msg(info, "require a type for the pointer value");
                info->err_num++;
                *node = 0;
                return TRUE;
            }

            if(*info->p == '=' && *(info->p + 1) != '=') {
                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    *node = sNodeTree_create_store_value_to_pointer(*node, node_type, right_node, info);
                }
            }
            else {
                *node = sNodeTree_create_load_value_from_pointer(*node, node_type, info);
            }
        }
        else if(*info->p == '+' && *(info->p+1) == '+') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_increment_operand(*node, info);
        }
        else if(*info->p == '-' && *(info->p+1) == '-') {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_decrement_operand(*node, info);
        }
        else if(*info->p == '?') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int object_node = *node;

            unsigned int params[PARAMS_MAX];
            int num_params = 1;

            params[0] = sNodeTree_null_expression(info);

            *node = sNodeTree_create_method_call(*node, "identifyWith", params, num_params, *num_method_chains, info);

            *node = sNodeTree_create_method_call(*node, "negative", NULL, 0, *num_method_chains, info);

            sNodeBlock* node_block;
            if(!parse_question_operator_block(object_node, *num_method_chains, ALLOC &node_block, info)) {
                return FALSE;
            }

            BOOL lambda = FALSE;
            sNodeType* result_type = create_node_type_with_class_name("Null");

            num_params = 1;
            params[0] = sNodeTree_create_block_object(NULL, 0, result_type, MANAGED node_block, lambda, info, FALSE, FALSE, NULL, TRUE);

            *node = sNodeTree_create_method_call(*node, "if", params, num_params, *num_method_chains, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL parse_block_object(unsigned int* node, sParserInfo* info, BOOL lambda)
{
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    int num_params = 0;

    /// parse_params ///
    sVarTable* new_table = NULL;

    if(lambda) {
        if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, NULL, 0)) {
            return FALSE;
        }
    }
    else {
        if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, info->lv_table, 0)) {
            return FALSE;
        }
    }

    sNodeType* result_type = NULL;
    BOOL omit_result_type = FALSE;
    if(*info->p == ':') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!parse_type(&result_type, info)) {
            return FALSE;
        }
    }
    else {
        result_type = create_node_type_with_class_name("Null");
        omit_result_type = TRUE;
    }

    expect_next_character_with_one_forward("{", info);

    sNodeBlock* node_block = NULL;
    if(!parse_block(ALLOC &node_block, info, new_table, TRUE, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_create_block_object(params, num_params, result_type, MANAGED node_block, lambda, info, omit_result_type, FALSE, NULL, FALSE);

    return TRUE;
}

static BOOL parse_var(unsigned int* node, sParserInfo* info, BOOL readonly)
{
    /// function name ///
    char buf[VAR_NAME_MAX];

    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    expect_next_character_with_one_forward(":", info);

    sNodeType* node_type;
    if(*info->p != '=') {
        if(!parse_type(&node_type, info)) {
            return FALSE;
        }

        if(node_type->mClass == NULL) {
            *node = 0;
            return TRUE;
        }
        if(node_type) {
            check_already_added_variable(info->lv_table, buf, info);
            add_variable_to_table(info->lv_table, buf, node_type, readonly);
        }
    }
    else {
        node_type = NULL;
        check_already_added_variable(info->lv_table, buf, info);
        add_variable_to_table(info->lv_table, buf, node_type, readonly);
    }

    /// assign the value to a variable ///
    if(*info->p == '=' && *(info->p+1) != '=') {
        info->p++;
        skip_spaces_and_lf(info);

        unsigned int right_node = 0;

        if(!expression(&right_node, info)) {
            return FALSE;
        }

        if(right_node == 0) {
            parser_err_msg(info, "Require right value");
            info->err_num++;

            *node = 0;
        }
        else {
            *node = sNodeTree_create_store_variable(buf, node_type, right_node, info->klass, info);
        }
    }
    else {
        parser_err_msg(info, "A variable should be initialized");
        info->err_num++;
    }

    return TRUE;
}

static BOOL parse_function(unsigned int* node, sParserInfo* info, BOOL lambda)
{
    /// function name ///
    char fun_name[VAR_NAME_MAX];

    if(!parse_word(fun_name, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    expect_next_character_with_one_forward("(", info);

    sNodeType* node_type = NULL;
    check_already_added_variable(info->lv_table, fun_name, info);
    add_variable_to_table(info->lv_table, fun_name, node_type, FALSE);

    /// params ///
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    int num_params = 0;

    /// parse_params ///
    sVarTable* new_table = NULL;

    if(!parse_params_and_entry_to_lvtable(params, &num_params, info, &new_table, info->lv_table, 0)) {
        return FALSE;
    }

    sNodeType* result_type = NULL;
    if(*info->p == ':') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!parse_type(&result_type, info)) {
            return FALSE;
        }
    }
    else {
        result_type = create_node_type_with_class_name("Null");
    }

    expect_next_character_with_one_forward("{", info);

    sNodeBlock* node_block = NULL;
    if(!parse_block(ALLOC &node_block, info, new_table, TRUE, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_create_function(fun_name, params, num_params, result_type, MANAGED node_block, lambda, info);

    return TRUE;
}

static BOOL parse_normal_block(unsigned int* node, sParserInfo* info)
{
    sNodeBlock* node_block = NULL;
    if(!parse_block(ALLOC &node_block, info, NULL, FALSE, FALSE)) {
        return FALSE;
    }

    *node = sNodeTree_create_normal_block(MANAGED node_block, info);

    return TRUE;
}

static BOOL parse_array_value_or_hash_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    unsigned int hash_keys[HASH_VALUE_ELEMENT_MAX+1];
    unsigned int hash_items[HASH_VALUE_ELEMENT_MAX+1];

    memset(hash_keys, 0, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    memset(hash_items, 0, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);

    if(*info->p == ']') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            unsigned int node = 0;
            if(!expression(&node, info)) {
                return FALSE;
            }

            if(*info->p == '=' && *(info->p+1) == '>') {
                info->p+=2;
                skip_spaces_and_lf(info);

                hash_keys[num_elements] = node;

                unsigned int node2 = 0;
                if(!expression(&node2, info)) {
                    return FALSE;
                }

                hash_items[num_elements] = node2;

                num_elements++;

                if(num_elements >= HASH_VALUE_ELEMENT_MAX) {
                    parser_err_msg(info, "overflow hash value elements");
                    return FALSE;
                }

                if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == ']') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else {
                    parser_err_msg(info, "invalid hash value");
                    info->err_num++;
                }
            }
            else {
                array_elements[num_elements] = node;

                num_elements++;

                if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                    parser_err_msg(info, "overflow array value elements");
                    return FALSE;
                }

                if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == ']') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else {
                    parser_err_msg(info, "invalid array value");
                    info->err_num++;
                }
            }
        }
    }

    if(array_elements[0] != 0 && hash_keys[0] != 0) {
        parser_err_msg(info, "invalid hash or array value");
        info->err_num++;
    }
    else if(array_elements[0] != 0) {
        *node = sNodeTree_create_array_value(num_elements, array_elements, info);
    }
    else if(hash_keys[0] != 0) {
        *node = sNodeTree_create_hash_value(num_elements, hash_keys, hash_items, info);
    }

    return TRUE;
}

static BOOL parse_carray_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(array_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
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
        }
    }

    *node = sNodeTree_create_carray_value(num_elements, array_elements, info);

    return TRUE;
}

static BOOL parse_equalable_carray_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(array_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
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
        }
    }

    *node = sNodeTree_create_equalable_carray_value(num_elements, array_elements, info);

    return TRUE;
}

static BOOL parse_sortable_carray_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int array_elements[ARRAY_VALUE_ELEMENT_MAX];
    memset(array_elements, 0, sizeof(unsigned int)*ARRAY_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(array_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= ARRAY_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
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
        }
    }

    *node = sNodeTree_create_sortable_carray_value(num_elements, array_elements, info);

    return TRUE;
}

static BOOL parse_hash_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int hash_keys[HASH_VALUE_ELEMENT_MAX+1];
    unsigned int hash_items[HASH_VALUE_ELEMENT_MAX+1];

    memset(hash_keys, 0, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);
    memset(hash_items, 0, sizeof(unsigned int)*HASH_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(hash_keys + num_elements, info)) {
                return FALSE;
            }

            expect_next_character_with_one_forward(":", info);

            if(!expression(hash_items + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= HASH_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow hash value elements");
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
        }
    }

    *node = sNodeTree_create_hash_value(num_elements, hash_keys, hash_items, info);

    return TRUE;
}

static BOOL parse_list_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int list_elements[LIST_VALUE_ELEMENT_MAX];
    memset(list_elements, 0, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(list_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= LIST_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
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
        }
    }

    *node = sNodeTree_create_list_value(num_elements, list_elements, info);

    return TRUE;
}

static BOOL parse_equalable_list_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int list_elements[LIST_VALUE_ELEMENT_MAX];
    memset(list_elements, 0, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(list_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= LIST_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
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
        }
    }

    *node = sNodeTree_create_equalable_list_value(num_elements, list_elements, info);

    return TRUE;
}

static BOOL parse_sortable_list_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int list_elements[LIST_VALUE_ELEMENT_MAX];
    memset(list_elements, 0, sizeof(unsigned int)*LIST_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(list_elements + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= LIST_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
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
        }
    }

    *node = sNodeTree_create_sortable_list_value(num_elements, list_elements, info);

    return TRUE;
}

static BOOL parse_tuple_value(unsigned int* node, sParserInfo* info) 
{
    int num_elements = 0;

    unsigned int tuple_element[TUPLE_VALUE_ELEMENT_MAX];
    memset(tuple_element, 0, sizeof(unsigned int)*TUPLE_VALUE_ELEMENT_MAX);

    if(*info->p == '}') {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        while(1) {
            if(!expression(tuple_element + num_elements, info)) {
                return FALSE;
            }

            num_elements++;

            if(num_elements >= TUPLE_VALUE_ELEMENT_MAX) {
                parser_err_msg(info, "overflow array value elements");
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
        }
    }

    *node = sNodeTree_create_tuple_value(num_elements, tuple_element, info);

    return TRUE;
}

BOOL parse_iniherit(unsigned int* node, sParserInfo* info)
{
    unsigned int params[PARAMS_MAX];
    int num_params = 0;

    if(!parse_method_params(&num_params, params, info)) {
        return FALSE;
    }

    *node = sNodeTree_create_inherit_call(num_params, params, info->klass->mMethodIndexOnCompileTime-1, info);

    return TRUE;
}

BOOL parse_unset(unsigned int* node, sParserInfo* info)
{
    char var_name[VAR_NAME_MAX];

    /// name ///
    if(!parse_word(var_name, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    sVar* var = get_variable_from_table(info->lv_table, var_name);

    if(var == NULL) {
        parser_err_msg(info, "%s is not defined", var_name);
        info->err_num++;
        return TRUE;
    }

    xstrncpy(var->mName, "", VAR_NAME_MAX);

    return TRUE;
}

static BOOL parse_string_expression(sNodeBlock** string_expressions, int* string_expression_offsets, int* num_string_expression, sBuf* value, sParserInfo* info)
{
    sNodeBlock* block = NULL;
    if(!parse_block(ALLOC &block, info, NULL, FALSE, TRUE)) {
        return FALSE;
    }

    string_expressions[*num_string_expression] = block;
    string_expression_offsets[*num_string_expression] = value->mLen;

    (*num_string_expression)++;

    if(*num_string_expression >= STRING_EXPRESSION_MAX) {
        parser_err_msg(info, "overflow string expression number");
        return FALSE;
    }

    return TRUE;
}

static BOOL remove_indent_for_multi_line_string(sBuf* value, int indent, sParserInfo* info)
{
    int i;
    for(i=0; i<indent; i++) {
        if(*info->p == ' ') {
            info->p++;
        }
        else if(*info->p == '\n') {
            info->sline++;
            sBuf_append_char(value, *info->p);
            info->p++;

            remove_indent_for_multi_line_string(value, indent, info);
            break;
        }
        else {
            parser_err_msg(info, "require white space for indent of multi line string");
            info->err_num++;
        }
    }

    return TRUE;
}

static BOOL expression_node(unsigned int* node, sParserInfo* info)
{
    int num_method_chains = 0;
    unsigned int max_method_chains_node[METHOD_CHAIN_MAX];

    /// number ///
    if((*info->p == '-' && *(info->p+1) != '=' && *(info->p+1) != '-' && *(info->p+1) != '>') || (*info->p == '+' && *(info->p+1) != '=' && *(info->p+1) != '+')) 
    {
        if(*info->p == '-') {
            info->p++;
            skip_spaces_and_lf(info);

            if(isdigit(*info->p)) {
                if(!get_number(TRUE, node, info)) {
                    return FALSE;
                }
            }
            else {
                if(!expression_node(node, info)) {
                    return FALSE;
                }

                if(*node == 0) {
                    parser_err_msg(info, "require right value for -");
                    info->err_num++;
                }

                *node = sNodeTree_create_operand(kOpMinus, *node, 0, 0, info);
            }
        }
        else if(*info->p =='+') {
            info->p++;
            skip_spaces_and_lf(info);

            if(isdigit(*info->p)) {
                if(!get_number(FALSE, node, info)) {
                    return FALSE;
                }
            }
            else {
                if(!expression_node(node, info)) {
                    return FALSE;
                }

                if(*node == 0) {
                    parser_err_msg(info, "require right value for -");
                    info->err_num++;
                }
            }
        }
    }
    /// hex number ///
    else if(*info->p == '0' && *(info->p+1) == 'x') {
        info->p += 2;

        if(!get_hex_number(node, info)) {
            return FALSE;
        }
    }
    /// oct number ///
    else if(*info->p == '0' && isdigit(*(info->p+1))) {
        info->p++;

        if(!get_oct_number(node, info)) {
            return FALSE;
        }
    }
    /// number ///
    else if(isdigit(*info->p)) {
        if(!get_number(FALSE, node, info)) {
            return FALSE;
        }
    }
    /// multi line string ///
    else if(*info->p == '"' && *(info->p+1) == '"' && *(info->p + 2) == '"' && *(info->p+3) == '\n') 
    {
        int indent = 0;

        char* p = info->p;
        while(1) {
            if(p == info->source) {
                break;
            }
            else if(*p == '\n') {
                indent--;
                break;
            }
            else {
                p--;
                indent++;
            }
        }

        info->p+=4;

        int i;
        for(i=0; i<indent; i++) {
            if(*info->p == ' ') {
                info->p++;
            }
            else if(*info->p == '\n') {
                info->sline++;
                info->p++;
                break;
            }
            else {
                parser_err_msg(info, "require white space for indent of multi line string");
                info->err_num++;
            }
        }

        sBuf value;
        sBuf_init(&value);

        sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
        memset(string_expressions, 0, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

        int string_expression_offsets[STRING_EXPRESSION_MAX];
        memset(string_expression_offsets, 0, sizeof(int)*STRING_EXPRESSION_MAX);

        int num_string_expression = 0;

        while(1) {
            if(*info->p == '"' && *(info->p+1) == '"' && *(info->p + 2) == '"') 
            {
                info->p+=3;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;

                switch(*info->p) {
                    case '0':
                        sBuf_append_char(&value, '\0');
                        info->p++;
                        break;

                    case '{':
                        info->p++;

                        /// string expression ///
                        if(!parse_string_expression(string_expressions, string_expression_offsets, &num_string_expression, &value, info)) 
                        {
                            MFREE(value.mBuf);
                            return FALSE;
                        }
                        break;

                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \"\"\" to make string value");
                MFREE(value.mBuf);
                return FALSE;
            }
            else if(*info->p == '\n') {
                info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;

                remove_indent_for_multi_line_string(&value, indent, info);
            }
            else {
                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_string_value(MANAGED value.mBuf, string_expressions, string_expression_offsets, num_string_expression, info);
    }
    /// String object ///
    else if(*info->p == '"') {
        info->p++;

        sBuf value;
        sBuf_init(&value);

        sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
        memset(string_expressions, 0, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

        int string_expression_offsets[STRING_EXPRESSION_MAX];
        memset(string_expression_offsets, 0, sizeof(int)*STRING_EXPRESSION_MAX);

        int num_string_expression = 0;

        while(1) {
            if(*info->p == '"') {
                info->p++;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;

                switch(*info->p) {
                    case '0':
                        sBuf_append_char(&value, '\0');
                        info->p++;
                        break;

                    case '{':
                        info->p++;

                        /// string expression ///
                        if(!parse_string_expression(string_expressions, string_expression_offsets, &num_string_expression, &value, info)) 
                        {
                            MFREE(value.mBuf);
                            return FALSE;
                        }
                        break;

                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make string value");
                MFREE(value.mBuf);
                return FALSE;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_string_value(MANAGED value.mBuf, string_expressions, string_expression_offsets, num_string_expression, info);
    }
    /// buffer object ///
    else if((*info->p == 'B' || *info->p == 'b') && *(info->p+1) == '"') {
        info->p+=2;

        sBuf value;
        sBuf_init(&value);

        sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
        memset(string_expressions, 0, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

        int string_expression_offsets[STRING_EXPRESSION_MAX];
        memset(string_expression_offsets, 0, sizeof(int)*STRING_EXPRESSION_MAX);

        int num_string_expression = 0;

        while(1) {
            if(*info->p == '"') {
                info->p++;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;
                switch(*info->p) {
                    case '0':
                        sBuf_append_char(&value, '\0');
                        info->p++;
                        break;

                    case '{':
                        info->p++;

                        /// string expression ///
                        if(!parse_string_expression(string_expressions, string_expression_offsets, &num_string_expression, &value, info)) 
                        {
                            MFREE(value.mBuf);
                            return FALSE;
                        }
                        break;

                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make string buffer value");
                return FALSE;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_buffer_value(MANAGED value.mBuf, value.mLen, string_expressions, string_expression_offsets, num_string_expression, info);
    }
    /// path ///
    else if((*info->p == 'P' || *info->p == 'p') && *(info->p+1) == '"') {
        info->p+=2;

        sBuf value;
        sBuf_init(&value);

        sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
        memset(string_expressions, 0, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

        int string_expression_offsets[STRING_EXPRESSION_MAX];
        memset(string_expression_offsets, 0, sizeof(int)*STRING_EXPRESSION_MAX);

        int num_string_expression = 0;

        while(1) {
            if(*info->p == '"') {
                info->p++;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;
                switch(*info->p) {
                    case '0':
                        sBuf_append_char(&value, '\0');
                        info->p++;
                        break;

                    case '{':
                        info->p++;

                        /// string expression ///
                        if(!parse_string_expression(string_expressions, string_expression_offsets, &num_string_expression, &value, info)) 
                        {
                            MFREE(value.mBuf);
                            return FALSE;
                        }
                        break;

                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make string buffer value");
                return FALSE;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_path_value(MANAGED value.mBuf, value.mLen, string_expressions, string_expression_offsets, num_string_expression, info);
    }
    /// Character ///
    else if(*info->p == '\'') {
        info->p++;

        wchar_t c;

        if(*info->p == '\\') {
            info->p++;

            switch(*info->p) {
                case 'n':
                    c = '\n';
                    info->p++;
                    break;

                case 't':
                    c = '\t';
                    info->p++;
                    break;

                case 'r':
                    c = '\r';
                    info->p++;
                    break;

                case 'a':
                    c = '\a';
                    info->p++;
                    break;

                case '\\':
                    c = '\\';
                    info->p++;
                    break;

                case '0':
                    c = '\0';
                    info->p++;
                    break;

                default:
                    c = *info->p;
                    info->p++;
                    break;
            }
        }
        else {
            unsigned char p2 = *(unsigned char*)info->p;

            /// utf-8 character ///
            if(p2 > 127) {
                int size;
                char str[MB_LEN_MAX+1];

                size = ((p2 & 0x80) >> 7) + ((p2 & 0x40) >> 6) + ((p2 & 0x20) >> 5) + ((p2 & 0x10) >> 4);

                if(size > MB_LEN_MAX) {
                    parser_err_msg(info, "invalid utf-8 character. MB_LEN_MAX");
                    info->err_num++;
                }
                else {
                    memcpy(str, info->p, size);
                    str[size] = 0;

                    if(mbtowc(&c, str, size) < 0) {
                        parser_err_msg(info, "invalid utf-8 character. mbtowc");
                        info->err_num++;
                        c = 0;
                    }

                    info->p += size;
                }
            }
            /// ASCII character ///
            else {
                c = *info->p;
                info->p++;
            }
        }

        if(*info->p != '\'') {
            parser_err_msg(info, "close \' to make character value");
            info->err_num++;
        }
        else {
            info->p++;

            skip_spaces_and_lf(info);

            *node = sNodeTree_create_character_value(c, info);
        }
    }
    /// array or hash ///
    else if(*info->p == '[') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!parse_array_value_or_hash_value(node, info)) {
            return FALSE;
        }
    }
    /// block ///
    else if(*info->p == '{') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!parse_normal_block(node, info)) {
            return FALSE;
        }
    }
    /// Head of alphabets or _ ./configure is inside for shell mode
    else if(isalpha(*info->p) || (*info->p == '.' && *(info->p+1) == '/') || (*info->p == '_'))
    {
        char buf[VAR_NAME_MAX];

        char* p_before = info->p;
        int sline_before = info->sline;

        if(*info->p == '.' || *(info->p+1) == '/') {
            info->p += 2;
            buf[0] = '.';
            buf[1] = '/';

            /// name ///
            if(!parse_word(buf + 2, VAR_NAME_MAX -2, info, TRUE, TRUE)) {
                return FALSE;
            }
            skip_spaces_and_lf(info);
        }
        else {
            /// name ///
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, TRUE)) {
                return FALSE;
            }
            skip_spaces_and_lf(info);
        }

        BOOL including_slash = strstr(buf, "/") != NULL;
        if(strcmp(buf, "if") == 0) {
            skip_spaces_and_lf(info);

            if(!if_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "when") == 0) {
            skip_spaces_and_lf(info);

            if(!when_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "while") == 0) {
            skip_spaces_and_lf(info);

            if(!while_expression(node, info)) {
                return FALSE;
            }

        }
        else if(strcmp(buf, "for") == 0) {
            skip_spaces_and_lf(info);

            if(!for_expression(node, info)) {
                return FALSE;
            }

        }
        else if(strcmp(buf, "break") == 0) {
            skip_spaces_and_lf(info);

            *node = sNodeTree_break_expression(info);
        }
        else if(strcmp(buf, "true") == 0) {
            skip_spaces_and_lf(info);

            *node = sNodeTree_true_expression(info);
        }
        else if(strcmp(buf, "false") == 0) {
            skip_spaces_and_lf(info);

            *node = sNodeTree_false_expression(info);
        }
        else if(strcmp(buf, "null") == 0) {
            skip_spaces_and_lf(info);

            *node = sNodeTree_null_expression(info);
        }
        else if(strcmp(buf, "wildcard") == 0) {
            skip_spaces_and_lf(info);

            *node = sNodeTree_wildcard_expression(info);
        }
        else if(strcmp(buf, "throw") == 0) {
            skip_spaces_and_lf(info);

            if(!throw_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "try") == 0) {
            skip_spaces_and_lf(info);

            if(!try_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "return") == 0) {
            skip_spaces_and_lf(info);

            if(!return_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "new") == 0) {
            skip_spaces_and_lf(info);

            if(!new_expression(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "closure") == 0 && *info->p == '(') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("(", info);

            if(!parse_block_object(node, info, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "lambda") == 0 && *info->p == '(') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("(", info);

            if(!parse_block_object(node, info, TRUE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "var") == 0) {
            skip_spaces_and_lf(info);

            if(!parse_var(node, info, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "val") == 0) {
            skip_spaces_and_lf(info);

            if(!parse_var(node, info, TRUE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "def") == 0) {
            skip_spaces_and_lf(info);

            if(!parse_function(node, info, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "inherit") == 0) {
            skip_spaces_and_lf(info);

            if(!parse_iniherit(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "unset") == 0) {
            skip_spaces_and_lf(info);

            if(!parse_unset(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "list") == 0 && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_list_value(node, info)) {
                return FALSE;
            }
        }
        else if((strcmp(buf, "equalable_list") == 0 || strcmp(buf, "elist") == 0) && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_equalable_list_value(node, info)) {
                return FALSE;
            }
        }
        else if((strcmp(buf, "sortable_list") == 0 || strcmp(buf, "slist") == 0) && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_sortable_list_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "tuple") == 0 && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_tuple_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "hash") == 0 && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_hash_value(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "array") == 0 && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_carray_value(node, info)) {
                return FALSE;
            }
        }
        else if((strcmp(buf, "equalable_array") == 0 || strcmp(buf, "earray") == 0) && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_equalable_carray_value(node, info)) {
                return FALSE;
            }
        }
        else if((strcmp(buf, "sortable_array") == 0 || strcmp(buf, "sarray") == 0) && *info->p == '{') {
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward("{", info);

            if(!parse_sortable_carray_value(node, info)) {
                return FALSE;
            }
        }

        /// local variable ////
        else if(*info->p == ':') {
            skip_spaces_and_lf(info);

            info->p++;
            skip_spaces_and_lf(info);

            sNodeType* node_type;
            if(*info->p != '=') {
                if(!parse_type(&node_type, info)) {
                    return FALSE;
                }

                if(node_type->mClass == NULL) {
                    *node = 0;
                    return TRUE;
                }
                if(node_type) {
                    check_already_added_variable(info->lv_table, buf, info);
                    add_variable_to_table(info->lv_table, buf, node_type, FALSE);
                }
            }
            else {
                node_type = NULL;
                check_already_added_variable(info->lv_table, buf, info);
                add_variable_to_table(info->lv_table, buf, node_type, FALSE);

            }

            /// assign the value to a variable ///
            if(*info->p == '=' && *(info->p+1) != '=') {
                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    *node = sNodeTree_create_store_variable(buf, node_type, right_node, info->klass, info);
                }
            }
            else {
                parser_err_msg(info, "A variable should be initialized");
                info->err_num++;
            }
        }
        /// assignment for variable ///
        else if(*info->p == '=' && *(info->p+1) != '=') {
            /// local variable ///
            if(get_variable_from_table(info->lv_table, buf) || is_method_param_name(buf)) {
                skip_spaces_and_lf(info);

                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    sVar* var = get_variable_from_table(info->lv_table, buf);

                    if(var && var->mReadOnly) {
                        parser_err_msg(info, "This is readonly variable.");
                        info->err_num++;

                        *node = 0;
                    }
                    else {
                        *node = sNodeTree_create_store_variable(buf, NULL, right_node, info->klass, info);
                    }
                }
            }
            /// the field in the same class
            else if(info->klass && field_name_existance(info->klass, buf))
            {
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_load_variable("self", info);

                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    *node = sNodeTree_create_assign_field(buf, *node, right_node, info);
                }
            }
            /// the class field name in the same class ///
            else if(info->klass && class_field_name_existance(info->klass, buf)) 
            {
                skip_spaces_and_lf(info);

                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    *node = sNodeTree_create_assign_class_field(info->klass, buf, right_node, info);
                }
            }
            else {
                info->sline = sline_before;
                parser_err_msg(info, "%s is undeclared.(1)", buf);
                info->err_num++;
            }
        }
        /// -=, +=, etc ///
        else if(is_assign_operator(info)) {
            /// local variable ///
            if(get_variable_from_table(info->lv_table, buf) || is_method_param_name(buf)) {
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_load_variable(buf, info);

                /// go ///
                if(!assign_operator(node, info)) {
                    return FALSE;
                }

                *node = sNodeTree_create_store_variable(buf, NULL, *node, info->klass, info);
            }
            /// the class field name in the same class ///
            else if(info->klass && class_field_name_existance(info->klass, buf)) 
            {
                skip_spaces_and_lf(info);

                /// load field ///
                *node = sNodeTree_create_class_fields(info->klass, buf, info);

                /// go 
                if(!assign_operator(node, info)) {
                    return FALSE;
                }

                *node = sNodeTree_create_assign_class_field(info->klass, buf, *node, info);

                unsigned int right = sNodeTree_create_int_value(1, 0, 0, 0, info);

                *node = sNodeTree_create_operand(kOpSub, *node, right, 0, info);
            }
            /// the field in the same class
            else if(info->klass && field_name_existance(info->klass, buf))
            {
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_load_variable("self", info);

                unsigned int node2 = clone_node(*node);
                unsigned int node3 = clone_node(*node);

                /// load field ///
                *node = sNodeTree_create_fields(buf, node2, info);

                /// go 
                if(!assign_operator(node, info)) {
                    return FALSE;
                }

                *node = sNodeTree_create_assign_field(buf, node3, *node, info);

                unsigned int right = sNodeTree_create_int_value(1, 0, 0, 0, info);

                *node = sNodeTree_create_operand(kOpSub, *node, right, 0, info);
            }
            else {
                info->sline = sline_before;
                parser_err_msg(info, "%s is undeclared.(2)", buf);
                info->err_num++;
            }
        }
        else {
            sCLClass* klass;

            int sline_before = info->sline;

            if(strcmp(buf, "SELF") == 0) {
                klass = info->klass;
            }
            else {
                klass = get_class(buf);

                if(klass == NULL) {
#ifdef __DARWIN__
                    if(buf[0] >= 'A' && buf[0] <= 'Z') {  // for OSX. OSX ignores the case of file name
                        klass = get_class_with_load_and_initialize(buf);
                    }
                    else {
                        klass = NULL;
                    }
#else
                    klass = get_class_with_load_and_initialize(buf);
#endif
                }
            }

            sCLClass* global_klass = get_class("Global");
            sCLClass* system_klass = get_class("System");

            /// It is class name ///
            if(klass) {
                skip_spaces_and_lf(info);

                info->p = p_before;
                info->sline = sline_before;

                sNodeType* klass2;

                if(!parse_type(&klass2, info)) {
                    return FALSE;
                }

                /// class field or class method ///
                if(*info->p == '.') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    char buf[METHOD_NAME_MAX];

                    /// name ///
                    if(!parse_word(buf, METHOD_NAME_MAX, info, TRUE, FALSE)) {
                        return FALSE;
                    }

                    /// class method ///
                    if(*info->p == '(') {
                        unsigned int params[PARAMS_MAX];
                        int num_params = 0;

                        if(!parse_method_params(&num_params, params, info)) {
                            return FALSE;
                        }

                        *node = sNodeTree_create_class_method_call(klass2, buf, params, num_params, info);
                        max_method_chains_node[num_method_chains] = *node;
                        num_method_chains++;

                        if(num_method_chains >= METHOD_CHAIN_MAX) {
                            info->sline = sline_before;
                            parser_err_msg(info, "overflow method chain");
                            return FALSE;
                        }
                    }
                    /// class field ///
                    else {
                        if(is_assign_operator(info)) {
                            /// load field ///
                            *node = sNodeTree_create_class_fields(klass, buf, info);

                            /// go 
                            if(!assign_operator(node, info)) {
                                return FALSE;
                            }

                            *node = sNodeTree_create_assign_class_field(klass, buf, *node, info);
                        }
                        else if(*info->p == '=' && *(info->p +1) != '=') {
                            info->p++;
                            skip_spaces_and_lf(info);

                            unsigned int right_node = 0;

                            if(!expression(&right_node, info)) {
                                return FALSE;
                            }

                            if(right_node == 0) {
                                info->sline = sline_before;
                                parser_err_msg(info, "Require right value");
                                info->err_num++;

                                *node = 0;
                            }
                            else {
                                *node = sNodeTree_create_assign_class_field(klass, buf, right_node, info);
                            }
                        }
                        else {
                            *node = sNodeTree_create_class_fields(klass, buf, info);
                        }
                    }
                }
                else if(*info->p == '(' || *info->p == '[') {
                    info->p = p_before;
                    info->sline = sline_before;

                    if(!new_expression(node, info)) {
                        return FALSE;
                    }
                }
                else {
                    info->sline = sline_before;
                    parser_err_msg(info, "require . or ( or [ after class name");
                    info->err_num++;
                }
            }
            /// the local variable ///
            else if(strcmp(buf, "self") == 0 
                || is_method_param_name(buf) 
                || get_variable_from_table(info->lv_table, buf))
            {
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_load_variable(buf, info);

                /// calling lambda or closure ///
                if(*info->p == '(') {
                    unsigned int params[PARAMS_MAX];
                    int num_params = 0;

                    if(!parse_method_params(&num_params, params, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_block_call(*node, num_params, params, info);
                }
            }
            /// the field name in the same class ///
            else if(info->klass && field_name_existance(info->klass, buf) && *info->p != '(')
            {
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_load_variable("self", info);

                *node = sNodeTree_create_fields(buf, *node, info);
            }
            /// the class field name in the same class ///
            else if(info->klass && class_field_name_existance(info->klass, buf) && *info->p != '(')
            {
                skip_spaces_and_lf(info);

                if(is_assign_operator(info)) {
                    /// load field ///
                    *node = sNodeTree_create_class_fields(info->klass, buf, info);

                    /// go 
                    if(!assign_operator(node, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_assign_class_field(info->klass, buf, *node, info);
                }
                else if(*info->p == '=' && *(info->p +1) != '=') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    unsigned int right_node = 0;

                    if(!expression(&right_node, info)) {
                        return FALSE;
                    }

                    if(right_node == 0) {
                        info->sline = sline_before;
                        parser_err_msg(info, "Require right value");
                        info->err_num++;

                        *node = 0;
                    }
                    else {
                        *node = sNodeTree_create_assign_class_field(info->klass, buf, right_node, info);
                    }
                }
                else {
                    *node = sNodeTree_create_class_fields(info->klass, buf, info);
                }
            }
            /// the method name in the same class ///
            else if(info->klass && none_class_method_name_existance(info->klass, buf) && *info->p == '(')
            {
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_load_variable("self", info);

                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_method_params(&num_params, params, info)) {
                    return FALSE;
                }

                *node = sNodeTree_create_method_call(*node, buf, params, num_params, num_method_chains, info);
                max_method_chains_node[num_method_chains] = *node;

                num_method_chains++;

                if(num_method_chains >= METHOD_CHAIN_MAX) {
                    info->sline = sline_before;
                    parser_err_msg(info, "overflow method chain");
                    return FALSE;
                }
            }
            /// the class method name in the same class ///
            else if(info->klass && class_method_name_existance(info->klass, buf) && *info->p == '(')
            {
                skip_spaces_and_lf(info);

                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_method_params(&num_params, params, info)) {
                    return FALSE;
                }

                sNodeType* node_type = alloc_node_type();

                node_type->mClass = info->klass;
                node_type->mNumGenericsTypes = 0;

                *node = sNodeTree_create_class_method_call(node_type, buf, params, num_params, info);
                max_method_chains_node[num_method_chains] = *node;
                num_method_chains++;
                if(num_method_chains >= METHOD_CHAIN_MAX) {
                    info->sline = sline_before;
                    parser_err_msg(info, "overflow method chain");
                    return FALSE;
                }
            }
            /// is Sytem Class field ? ///
            else if(system_klass && class_field_name_existance(system_klass, buf) && *info->p != '(')
            {
                skip_spaces_and_lf(info);

                if(is_assign_operator(info)) {
                    /// load field ///
                    *node = sNodeTree_create_class_fields(system_klass, buf, info);

                    /// go 
                    if(!assign_operator(node, info)) {
                        return FALSE;
                    }

                    *node = sNodeTree_create_assign_class_field(system_klass, buf, *node, info);
                }
                else if(*info->p == '=' && *(info->p +1) != '=') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    unsigned int right_node = 0;

                    if(!expression(&right_node, info)) {
                        return FALSE;
                    }

                    if(right_node == 0) {
                        info->sline = sline_before;
                        parser_err_msg(info, "Require right value");
                        info->err_num++;

                        *node = 0;
                    }
                    else {
                        *node = sNodeTree_create_assign_class_field(system_klass, buf, right_node, info);
                    }
                }
                else {
                    *node = sNodeTree_create_class_fields(system_klass, buf, info);
                }
            }
            /// is Sytem Class method ? ///
            else if(system_klass && class_method_name_existance(system_klass, buf) && *info->p == '(')
            {
                skip_spaces_and_lf(info);

                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_method_params(&num_params, params, info)) {
                    return FALSE;
                }

                sNodeType* system_klass_type = alloc_node_type();

                system_klass_type->mClass = system_klass;
                system_klass_type->mNumGenericsTypes = 0;

                *node = sNodeTree_create_class_method_call(system_klass_type, buf, params, num_params, info);
                max_method_chains_node[num_method_chains] = *node;
                num_method_chains++;
                if(num_method_chains >= METHOD_CHAIN_MAX) {
                    info->sline = sline_before;
                    parser_err_msg(info, "overflow method chain");
                    return FALSE;
                }
            }
            /// Global class method ///
            else if(global_klass && class_method_name_existance(global_klass, buf) && *info->p == '(')
            {
                skip_spaces_and_lf(info);

                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_method_params(&num_params, params, info)) {
                    return FALSE;
                }

                sNodeType* global_klass_type = alloc_node_type();

                global_klass_type->mClass = global_klass;
                global_klass_type->mNumGenericsTypes = 0;

                *node = sNodeTree_create_class_method_call(global_klass_type, buf, params, num_params, info);
                max_method_chains_node[num_method_chains] = *node;
                num_method_chains++;
                if(num_method_chains >= METHOD_CHAIN_MAX) {
                    info->sline = sline_before;
                    parser_err_msg(info, "overflow method chain");
                    return FALSE;
                }
            }
            /// Command ///
            else if(get_variable_index(info->lv_table, buf) == -1 && is_command_name(buf) && *info->p == '(')
            {
                skip_spaces_and_lf(info);

                /// Command class method call ///
                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_method_params(&num_params, params, info)) {
                    return FALSE;
                }

                sCLClass* command_klass = get_class("Command");

                MASSERT(command_klass != NULL);

                sNodeType* command_klass_type = alloc_node_type();

                command_klass_type->mClass = command_klass;
                command_klass_type->mNumGenericsTypes = 0;

                *node = sNodeTree_create_class_method_call(command_klass_type, buf, params, num_params, info);
                max_method_chains_node[num_method_chains] = *node;
                num_method_chains++;

                if(num_method_chains >= METHOD_CHAIN_MAX) {
                    info->sline = sline_before;
                    parser_err_msg(info, "overflow method chain");
                    return FALSE;
                }
            }
            /// the local variable declaration for the multiple_assignments ///
            else if(info->multiple_assignment) 
            {
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_load_variable(buf, info);
            }
            /// shell mode ///
            else if(including_slash || (get_variable_index(info->lv_table, buf) == -1 && is_command_name(buf) && *info->p != '('))
            {
                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                char* method_name = buf;

                if(!parse_command_method_params(&num_params, params, info, TRUE, method_name)) {
                    return FALSE;
                }

                sCLClass* command_klass = get_class("Command");

                MASSERT(command_klass != NULL);

                sNodeType* command_klass_type = alloc_node_type();

                command_klass_type->mClass = command_klass;
                command_klass_type->mNumGenericsTypes = 0;

                *node = sNodeTree_create_class_method_call(command_klass_type, buf, params, num_params, info);
                max_method_chains_node[num_method_chains] = *node;
                num_method_chains++;

                if(num_method_chains >= METHOD_CHAIN_MAX) {
                    info->sline = sline_before;
                    parser_err_msg(info, "overflow method chain");
                    return FALSE;
                }

                while(1) {
                    if(*info->p == '|' && *(info->p+1) != '|') {
                        info->p++;
                        skip_spaces_and_lf(info);

                        char buf[VAR_NAME_MAX];

                        /// name ///
                        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, TRUE)) {
                            return FALSE;
                        }

                        unsigned int params[PARAMS_MAX];
                        int num_params = 0;

                        if(!parse_command_method_params(&num_params, params, info, FALSE, method_name)) {
                            return FALSE;
                        }

                        *node = sNodeTree_create_method_call(*node, buf, params, num_params, num_method_chains, info);
                        max_method_chains_node[num_method_chains] = *node;

                        num_method_chains++;

                        if(num_method_chains >= METHOD_CHAIN_MAX) {
                            info->sline = sline_before;
                            parser_err_msg(info, "overflow method chain");
                            return FALSE;
                        }
                    }
                    else if(info->next_command_is_to_bool || (*info->p == '&' && *(info->p+1) == '&') || (*info->p == '|' && *(info->p+1) == '|')) 
                    {
                        unsigned int params[PARAMS_MAX];
                        int num_params = 0;

                        if(gNodes[*node].mNodeType == kNodeTypeClassMethodCall) {
                            int string_node = sNodeTree_create_string_value(MANAGED MSTRDUP("--controlling-terminal"), NULL, NULL, 0, info);

                            int num_params = gNodes[*node].uValue.sClassMethodCall.mNumParams;
                            gNodes[*node].uValue.sClassMethodCall.mParams[num_params] = string_node;
                            gNodes[*node].uValue.sClassMethodCall.mNumParams++;
                        }
                        else if(gNodes[*node].mNodeType == kNodeTypeMethodCall) {
                            int string_node = sNodeTree_create_string_value(MANAGED MSTRDUP("--controlling-terminal"), NULL, NULL, 0, info);

                            int num_params = gNodes[*node].uValue.sMethodCall.mNumParams;
                            gNodes[*node].uValue.sMethodCall.mParams[num_params] = string_node;
                            gNodes[*node].uValue.sMethodCall.mNumParams++;
                        }

                        *node = sNodeTree_create_method_call(*node, "toBool", NULL, 0, num_method_chains, info);
                        /*
                        max_method_chains_node[num_method_chains] = *node;

                        num_method_chains++;

                        if(num_method_chains >= METHOD_CHAIN_MAX) {
                            info->sline = sline_before;
                            parser_err_msg(info, "overflow method chain");
                            return FALSE;
                        }
                        */
                        
                        info->next_command_is_to_bool = TRUE;
                        break;
                    }
                    else if(*info->p == ';' || *info->p == '\n') {
                        info->p++;
                        skip_spaces_and_lf(info);
                        break;
                    }
                    else if(*info->p == '\0') {
                        break;
                    }
                    else {
                        info->sline = sline_before;
                        parser_err_msg(info, "unexpected character (%c) 1", *info->p);
                        info->p++;
                        break;
                    }
                }
            }
            else {
                info->sline = sline_before;
                parser_err_msg(info, "%s is undeclared(3)", buf);
                info->err_num++;
            }
        }
    }
    /// regex ///
    else if(*info->p == '/' && *(info->p+1) != '*') {
        info->p++;
        skip_spaces_and_lf(info);

        sNodeBlock* string_expressions[STRING_EXPRESSION_MAX];
        memset(string_expressions, 0, sizeof(sNodeBlock*)*STRING_EXPRESSION_MAX);

        int string_expression_offsets[STRING_EXPRESSION_MAX];
        memset(string_expression_offsets, 0, sizeof(int)*STRING_EXPRESSION_MAX);

        int num_string_expression = 0;

        sBuf regex;
        sBuf_init(&regex);

        while(1) {
            if(*info->p == '\\' && *(info->p+1) == '/') {
                info->p++;
                sBuf_append_char(&regex, *info->p);
                info->p++;
            }
            else if(*info->p == '/') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else if(*info->p == '\\' && *(info->p+1) == '\\' && *(info->p+2) == '{') {
                sBuf_append_char(&regex, *info->p);
                info->p++;
                sBuf_append_char(&regex, *info->p);
                info->p++;
                sBuf_append_char(&regex, *info->p);
                info->p++;
            }
            else if(*info->p == '\\' && *(info->p+1) == '{') {
                info->p+=2;

                /// string expression ///
                if(!parse_string_expression(string_expressions, string_expression_offsets, &num_string_expression, &regex, info)) 
                {
                    MFREE(regex.mBuf);
                    return FALSE;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make string value");
                info->err_num++;
                break;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&regex, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        BOOL global = FALSE;
        BOOL ignore_case = FALSE;
        BOOL multiline = FALSE;
        BOOL extended = FALSE;
        BOOL dotall = FALSE;
        BOOL anchored = FALSE;
        BOOL dollar_endonly = FALSE;
        BOOL ungreedy = FALSE;
        while(1) {
            if(*info->p == 'g') {
                info->p++;
                global = TRUE;
            }
            else if(*info->p == 'i') {
                info->p++;
                ignore_case = TRUE;
            }
            else if(*info->p == 's') {
                info->p++;
                dotall = TRUE;
            }
            else if(*info->p == 'm') {
                info->p++;
                multiline = TRUE;
            }
            else if(*info->p == 'A') {
                info->p++;
                anchored = TRUE;
            }
            else if(*info->p == 'D') {
                info->p++;
                dollar_endonly = TRUE;
            }
            else if(*info->p == 'U') {
                info->p++;
                ungreedy = TRUE;
            }
            else if(*info->p == 'x') {
                info->p++;
                extended = TRUE;
            }
            else {
                break;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_regex(MANAGED regex.mBuf, global, ignore_case, multiline, extended, dotall, anchored, dollar_endonly, ungreedy, string_expressions, string_expression_offsets, num_string_expression, info);
    }
    /// Tuple or paren expression or multiple assginment ///
    else if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        info->multiple_assignment = TRUE;

        /// Is multiple assignment? ///
        if(!expression(node, info)) {
            info->multiple_assignment = FALSE;
            return FALSE;
        }
        skip_spaces_and_lf(info);

        if(*node == 0) {
            parser_err_msg(info, "require expression as ( operand");
            info->err_num++;
        }

        /// tuple ///
        if(*info->p == ',') {
            info->p++;
            skip_spaces_and_lf(info);

            int num_elements = 0;

            unsigned int tuple_element[TUPLE_VALUE_ELEMENT_MAX];
            memset(tuple_element, 0, sizeof(unsigned int)*TUPLE_VALUE_ELEMENT_MAX);

            tuple_element[0] = *node;
            num_elements++;

            while(1) {
                if(!expression(tuple_element + num_elements, info)) {
                    info->multiple_assignment = FALSE;
                    return FALSE;
                }

                num_elements++;

                if(num_elements >= TUPLE_VALUE_ELEMENT_MAX) {
                    parser_err_msg(info, "overflow array value elements");
                    info->multiple_assignment = FALSE;
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
            }

            /// multiple assignment1 ///
            if(*info->p == ':' && *(info->p+1) == '=') {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int node2 = 0;
                if(!expression(&node2, info)) {
                    info->multiple_assignment = FALSE;
                    return FALSE;
                }

                /// the varialbe declaration ///
                int i;
                for(i=0; i<num_elements; i++) {
                    int node = tuple_element[i];

                    if(gNodes[node].mNodeType != kNodeTypeLoadVariable) {
                        parser_err_msg(info, "require variable name for left value of :=");
                        info->err_num++;
                    }

                    char* var_name = gNodes[node].uValue.mVarName;

                    check_already_added_variable(info->lv_table, var_name, info);
                    add_variable_to_table(info->lv_table, var_name, NULL, FALSE);
                }

                *node = sNodeTree_create_multiple_asignment(num_elements, tuple_element, node2, info);
            }
            /// multiple assginment2 ///
            else if(*info->p == '=' && *(info->p+1) != '=') {
                info->p++;
                skip_spaces_and_lf(info);

                unsigned int node2 = 0;
                if(!expression(&node2, info)) {
                    info->multiple_assignment = FALSE;
                    return FALSE;
                }

                /// Is the local variable ? ///
                int i;
                for(i=0; i<num_elements; i++) {
                    int node = tuple_element[i];

                    if(gNodes[node].mNodeType == kNodeTypeLoadVariable) {
                        char* var_name = gNodes[node].uValue.mVarName;

                        int var_index = get_variable_index(info->lv_table, var_name);
                        if(var_index == -1) {
                            parser_err_msg(info, "undeclared variable(%s)(4)", var_name);
                            info->err_num++;
                        }
                    }
/*
                    else if(gNodes[node].mNodeType == kNodeTypeLoadField) {
                    }
                    else if(gNodes[node].mNodeType == kNodeTypeLoadClassField) {
                    }
*/
                    else {
                        parser_err_msg(info, "require variable name for left value of =");
                        info->err_num++;
                    }
                }

                *node = sNodeTree_create_multiple_asignment(num_elements, tuple_element, node2, info);
            }
            else {
                *node = sNodeTree_create_tuple_value(num_elements, tuple_element, info);
            }
        }
        else {
            if(!expect_next_character(")", info)) {
                info->multiple_assignment = FALSE;
                return FALSE;
            }
            info->p++;
            skip_spaces_and_lf(info);
        }

        info->multiple_assignment = FALSE;
    }
    /// operator getting address ///
    else if(*info->p == '&') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression(node, info)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_get_address(*node, info);
    }
    /// the source end ///
    else if(*info->p == 0) {
        *node = 0;
        return TRUE;
    }
    else if(*info->p == '#') {
        while(*info->p) {
            if(*info->p == '\n') {
                break;
            }

            info->p++;
        }

        *node = 0;
    }
    else if(*info->p == '#') {
        while(*info->p) {
            if(*info->p == '\n') {
                info->p++;
                info->sline++;
                break;
            }

            info->p++;
        }

        *node = 0;
    }
    else if(*info->p == '/' && *(info->p+1) == '*') {
        info->p+=2;

        BOOL in_string = FALSE;
        int nest = 0;
        while(1) {
            if(*info->p == '"') {
                info->p++;
                in_string = !in_string;
            }
            else if(*info->p == 0) {
                fprintf(stderr, "there is not a comment end until source end\n");
                return FALSE;
            }
            else if(!in_string && *info->p == '/' && *(info->p+1) == '*') {
                info->p+=2;
                nest++;
            }
            else if(!in_string && *info->p == '*' && *(info->p+1) == '/') {
                info->p+=2;
                if(nest == 0) {
                    break;
                }

                nest--;
            }
            else if(*info->p == '\n') {
                info->p++;
                info->sline++;
            }
            else {
                info->p++;
            }
        }

        *node = 0;
    }
    else {
        parser_err_msg(info, "invalid character (character code %d) (%c)", *info->p, *info->p);

        if(*info->p == '\n') info->sline++;
        info->p++;
        skip_spaces_and_lf(info);

        info->err_num++;

        *node = 0;
    }

    /// post position expression ///
    if(!postposition_operator(node, info, &num_method_chains, max_method_chains_node))
    {
        return FALSE;
    }

    gNodes[*node].mMaxMethodChains = num_method_chains;

    int i;
    for(i=0; i<num_method_chains; i++) {
        gNodes[max_method_chains_node[i]].mMaxMethodChains = num_method_chains;
    }

    return TRUE;
}

// from right to left order 
static BOOL expression_monadic_operator(unsigned int* node, sParserInfo* info)
{
    while(*info->p) {
        if(*info->p == '+' && *(info->p+1) == '+') {
            info->p +=2;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for operator ++");
                info->err_num++;
            }

            if(!check_node_is_variable(*node)) {
                parser_err_msg(info, "require the variable name for operator ++");
                info->err_num++;
            }

            *node = sNodeTree_create_monadic_increment_operand(*node, info);
            break;
        }
        else if(*info->p == '-' && *(info->p+1) == '-') {
            info->p +=2;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for operator --");
                info->err_num++;
            }

            if(!check_node_is_variable(*node)) {
                parser_err_msg(info, "require the variable name for operator ++");
                info->err_num++;
            }

            *node = sNodeTree_create_monadic_decrement_operand(*node, info);
            break;
        }
        else if(*info->p == '~') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for operator ~");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComplement, *node, 0, 0, info);
            break;
        }
        else if(*info->p == '!') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!expression_monadic_operator(node, info)) {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for !");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpLogicalDenial, *node, 0, 0, info);
            break;
        }
        else {
            if(!expression_node(node, info)) {
                return FALSE;
            }
            break;
        }
    }


    return TRUE;
}

static BOOL expression_implements(unsigned int* node, sParserInfo* info)
{
    if(!expression_monadic_operator(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(memcmp(info->p, "implements", 10) == 0) {
            info->p+=10;
            skip_spaces_and_lf(info);

            char buf[VAR_NAME_MAX+1];

            /// name ///
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }

            *node = sNodeTree_create_implements(*node, buf, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_mult_div(unsigned int* node, sParserInfo* info)
{
    if(!expression_implements(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '*' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_implements(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator *");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpMult, *node, right, 0, info);
        }
        else if(*info->p == '/' && *(info->p+1) != '=' && *(info->p+1) != '*') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_implements(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator /");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpDiv, *node, right, 0, info);
        }
        else if(*info->p == '%' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_implements(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator ^");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpMod, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_add_sub(unsigned int* node, sParserInfo* info)
{
    if(!expression_mult_div(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '+' && *(info->p+1) != '=' && *(info->p+1) != '+') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_mult_div(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator +");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpAdd, *node, right, 0, info);
        }
        else if(*info->p == '-' && *(info->p+1) != '=' && *(info->p+1) != '-' && *(info->p+1) != '>') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_mult_div(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator -");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpSub, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_shift(unsigned int* node, sParserInfo* info)
{
    if(!expression_add_sub(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) != '=') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_add_sub(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator <<");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpLeftShift, *node, right, 0, info);
        }
        else if(*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) != '=') {
            info->p+=2;
            skip_spaces_and_lf(info);
            
            unsigned int right = 0;
            if(!expression_add_sub(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator >>");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpRightShift, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_comparison_operator(unsigned int* node, sParserInfo* info)
{
    if(!expression_shift(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '>' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for >= operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonGreaterEqual, *node, right, 0, info);
        }
        else if(*info->p == '<' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for <= operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonLesserEqual, *node, right, 0, info);
        }
        else if(*info->p == '>' && *(info->p+1) != '>') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for > operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonGreater, *node, right, 0, info);
        }
        else if(*info->p == '<' && *(info->p+1) != '<') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for < operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonLesser, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_comparison_equal_operator(unsigned int* node, sParserInfo* info)
{
    if(!expression_comparison_operator(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '=' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_comparison_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for == operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonEqual, *node, right, 0, info);
        }
        else if(*info->p == '!' && *(info->p+1) == '=') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_comparison_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for != operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpComparisonNotEqual, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_and(unsigned int* node, sParserInfo* info)
{
    if(!expression_comparison_equal_operator(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '&' && *(info->p+1) != '&' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_comparison_equal_operator(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for & operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpAnd, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_xor(unsigned int* node, sParserInfo* info)
{
    if(!expression_and(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '^' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_and(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for ^ operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpXor, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_or(unsigned int* node, sParserInfo* info)
{
    if(!expression_xor(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '|' && *(info->p+1) != '=' && *(info->p+1) != '|') {
            (info->p)++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_xor(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for | operator");
                info->err_num++;
            }

            *node = sNodeTree_create_operand(kOpOr, *node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL expression_and_and_or_or(unsigned int* node, sParserInfo* info)
{
    if(!expression_or(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '&' && *(info->p+1) == '&') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_and_and_or_or(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for && operator");
                info->err_num++;
            }

            *node = sNodeTree_create_and_and(*node, right, info);
        }
        else if(*info->p == '|' && *(info->p+1) == '|') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_and_and_or_or(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator ||");
                info->err_num++;
            }

            *node = sNodeTree_create_or_or(*node, right, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

BOOL expression(unsigned int* node, sParserInfo* info) 
{
    skip_spaces_and_lf(info);

    if(!expression_and_and_or_or(node, info)) {
        return FALSE;
    }

    return TRUE;
}

