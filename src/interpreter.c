#include "common.h"
#include <locale.h>
#define _GNU_SOURCE
#include <stdio.h>

#ifdef HAVE_READLINE_H
#include <readline/readline.h>
#include <readline/history.h>
#endif

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

static int mgetmaxx()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    return ws.ws_col;
}

static int mgetmaxy()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    return ws.ws_row;
}

void display_candidates(char** candidates)
{
    char* candidate;
    char** p;
    int max_len;
    int maxx;
    int cols;
    int n;

    p = candidates;

    max_len = -1;

    while((candidate = *p) != NULL) {
        int len;

        len = strlen(candidate);

        if(len > max_len) {
            max_len = len;
        }
        p++;
    }

    maxx = mgetmaxx();

    cols = maxx / (max_len + 2);

    if(cols == 0) {
        cols = 1;
    }

    n = 0;

    puts("");

    p = candidates;
    while((candidate = *p) != NULL) {
        char format[128];
        format[0] = '%';
        format[1] = '-';
        snprintf(format + 2, 128-2, "%d", max_len + 2);
        xstrncat(format, "s", 128);

        printf(format, candidate);
        n++;
        if(n == cols) {
            puts("");
            n = 0;
        }
        p++;
    }

    puts("");
}

static ALLOC char* cl_type_to_buffer(sCLType* cl_type, sCLClass* klass);

static char* ALLOC cl_block_type_to_buffer(sCLBlockType* cl_block_type, sCLClass* klass)
{
    sBuf buf;

    sBuf_init(&buf);

    sBuf_append_str(&buf, "lambda(");

    int i;
    for(i=0; i<cl_block_type->mNumParams; i++) {
        sCLType* cl_type = cl_block_type->mParams[i];

        char* cl_type_name = ALLOC cl_type_to_buffer(cl_type, klass);

        sBuf_append_str(&buf, cl_type_name);

        MFREE(cl_type_name);

        if(i != cl_block_type->mNumParams-1) {
            sBuf_append_str(&buf, ",");
        }
    }

    sBuf_append_str(&buf, ")");

    if(cl_block_type->mResultType) {
        sBuf_append_str(&buf, ":");

        sCLType* cl_type = cl_block_type->mResultType;

        char* cl_type_name = ALLOC cl_type_to_buffer(cl_type, klass);

        sBuf_append_str(&buf, cl_type_name);

        MFREE(cl_type_name);
    }

    return buf.mBuf;
}

static ALLOC char* cl_type_to_buffer(sCLType* cl_type, sCLClass* klass)
{
    int i;
    sBuf buf;

    sBuf_init(&buf);

    if(cl_type == NULL) {
        sBuf_append_str(&buf, "NULL");
    }
    else if(cl_type->mNumGenericsTypes == 0) {
        if(cl_type->mBlockType) {
            char* block_type_str = ALLOC cl_block_type_to_buffer(cl_type->mBlockType, klass);

            sBuf_append_str(&buf, block_type_str);
            
            MFREE(block_type_str);
        }
        else {
            sBuf_append_str(&buf, CONS_str(&klass->mConst, cl_type->mClassNameOffset));
        }
    }
    else {
        if(cl_type->mClassNameOffset == 0) {
            sBuf_append_str(&buf, "NULL<");
        }
        else {
            sBuf_append_str(&buf, CONS_str(&klass->mConst, cl_type->mClassNameOffset));
            sBuf_append_str(&buf, "<");
        }
        for(i=0; i<cl_type->mNumGenericsTypes; i++) {
            char* result;

            result = cl_type_to_buffer(cl_type->mGenericsTypes[i], klass);

            sBuf_append_str(&buf, result);

            MFREE(result);
            if(i != cl_type->mNumGenericsTypes-1) { sBuf_append_str(&buf, ","); }
        }
        sBuf_append_str(&buf, ">");
    }

    return buf.mBuf;
}

ALLOC ALLOC char** get_method_names_with_arguments(sCLClass* klass, BOOL class_method, int* num_methods)
{
    int result_size = 128;
    char** result = MCALLOC(1, sizeof(char*)*result_size);
    int result_num = 0;

    *num_methods = 0;

    int i;
    for(i=0; i<klass->mNumMethods; i++) {
        sCLMethod* method = klass->mMethods + i;

        if((class_method && (method->mFlags & METHOD_FLAGS_CLASS_METHOD)) || (!class_method && !(method->mFlags & METHOD_FLAGS_CLASS_METHOD))) 
        {
            sBuf buf;
            sBuf_init(&buf);

            sBuf_append_str(&buf, METHOD_NAME2(klass, method));
            sBuf_append_str(&buf, "(");

            int j;
            for(j=0; j<method->mNumParams; j++) {
                sCLParam* param = method->mParams + j;
                sCLType* param_type = param->mType;

                char* argment_names = ALLOC cl_type_to_buffer(param_type, klass);

                sBuf_append_str(&buf, argment_names);

                if(j!=method->mNumParams-1) sBuf_append_str(&buf, ",");

                MFREE(argment_names);
            }

            sBuf_append_str(&buf, ")");

            *(result+result_num) = MANAGED buf.mBuf;
            result_num++;

            if(result_num >= result_size) {
                result_size *= 2;
                result = MREALLOC(result, sizeof(char*)*result_size);
            }
        }
    }

    /// special methods ///
    *(result+result_num) = MANAGED MSTRDUP("toAnonymous()");
    result_num++;

    if(result_num >= result_size) {
        result_size *= 2;
        result = MREALLOC(result, sizeof(char*)*result_size);
    }

    *(result+result_num) = MANAGED MSTRDUP("identifyWith(Object)");
    result_num++;

    if(result_num >= result_size) {
        result_size *= 2;
        result = MREALLOC(result, sizeof(char*)*result_size);
    }

    *(result+result_num) = MANAGED MSTRDUP("className()");
    result_num++;

    *(result+result_num) = MANAGED MSTRDUP("toNull()");
    result_num++;

    if(result_num >= result_size) {
        result_size *= 2;
        result = MREALLOC(result, sizeof(char*)*result_size);
    }
    
    /// field ///
    if(class_method) {
        for(i=0; i<klass->mNumClassFields; i++) {
            sCLField* field;

            field = klass->mClassFields + i;

            *(result+result_num) = MSTRDUP(FIELD_NAME(klass, field));
            result_num++;

            if(result_num >= result_size) {
                result_size *= 2;
                result = MREALLOC(result, sizeof(char*)*result_size);
            }
        }
    }
    else {
        for(i=0; i<klass->mNumFields; i++) {
            sCLField* field;

            field = klass->mFields + i;

            *(result+result_num) = MSTRDUP(FIELD_NAME(klass, field));
            result_num++;

            if(result_num >= result_size) {
                result_size *= 2;
                result = MREALLOC(result, sizeof(char*)*result_size);
            }
        }
    }

    *num_methods = result_num;

    *(result+result_num) = NULL;
    result_num++;

    if(result_num >= result_size) {
        result_size *= 2;
        result = MREALLOC(result, sizeof(char*)*result_size);
    }

    return result;
}

static ALLOC char* line_buffer_from_head_to_cursor_point()
{
    char* result;

    MASSERT(rl_point >= 0 && rl_point <= strlen(rl_line_buffer));

    result = MCALLOC(1, strlen(rl_line_buffer)+1);
    memcpy(result, rl_line_buffer, rl_point);
    result[rl_point] = 0;

    return result;
}

static BOOL get_type(char* source, char* fname, sVarTable* lv_table, CLVALUE* stack, sNodeType** type_, sVarTable** result_lv_table)
{
    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = lv_table;
    info.parse_phase = 0;
    info.get_type_for_interpreter = TRUE;

    sCompileInfo cinfo;
    
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sByteCode code;
    sByteCode_init(&code);
    cinfo.code = &code;

    sConst constant;
    sConst_init(&constant);
    cinfo.constant = &constant;

    cinfo.lv_table = lv_table;
    cinfo.no_output = TRUE;
    cinfo.pinfo = &info;

    info.cinfo = &cinfo;

    while(*info.p) {
        info.exist_block_object_err = FALSE;

        unsigned int node = 0;
        (void)expression(&node, &info);

        *result_lv_table = info.lv_table;

        if(node != 0) {
            (void)compile(node, &cinfo);

            *type_ = cinfo.type;

            if(*info.p == ';') {
                info.p++;
                skip_spaces_and_lf(&info);
            }
        }
    }

    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}

static void skip_curly(char** p, char** head, char** comma, char** semi_colon);

static void skip_paren(char** p, char** head, char** comma, char** semi_colon)
{
    char* head_before = *head;
    *head = *p;
    *comma = NULL;
    *semi_colon = NULL;
    BOOL squort = FALSE;
    BOOL dquort = FALSE;

    while(**p) {
        if(!squort && !dquort && **p == '{') {
            (*p)++;

            skip_curly(p, head, comma, semi_colon);

            if(*comma) {
                *head = *comma;
            }
            else if(*semi_colon) {
                *head = *semi_colon;
            }
        }
        else if(!squort && !dquort && **p == '(') {
            (*p)++;

            skip_paren(p, head, comma, semi_colon);

            if(*comma) {
                *head = *comma;
            }
            else if(*semi_colon) {
                *head = *semi_colon;
            }
        }
        else if(!squort && !dquort && **p == ')') {
            (*p)++;

            *head = head_before;
            *comma = NULL;
            *semi_colon = NULL;
            break;
        }
        else if(!squort && !dquort && **p == ',') {
            (*p)++;
            *comma = *p;
        }
        else if(!squort && !dquort && **p == '&' && *(*p+1) == '&') {
            (*p)+=2;

            *head = *p;
        }
        else if(!squort && !dquort && **p == '|' && *(*p+1) == '|') {
            (*p)+=2;

            *head = *p;
        }
        else if(!squort && !dquort && **p == '|') {
            (*p)++;

            *head = *p;
        }
        else if(!squort && !dquort && strstr(*p, "return") == *p) {
            (*p) += strlen("return");

            while(**p == ' ' || **p == '\t') {
                (*p)++;
            }

            *head = *p;
        }
        else if(**p == '\'') {
            (*p)++;
            squort = !squort;
        }
        else if(**p == '"') {
            (*p)++;
            dquort = !dquort;
        }
        else {
            (*p)++;
        }
    }
}

static void skip_curly(char** p, char** head, char** comma, char** semi_colon) 
{
    char* head_before = *head;
    *head = *p;
    *comma = NULL;
    *semi_colon = NULL;
    BOOL squort = FALSE;
    BOOL dquort = FALSE;

    while(**p) {
        if(!squort && !dquort && **p == '{') {
            (*p)++;

            skip_curly(p, head, comma, semi_colon);

            if(*comma) {
                *head = *comma;
            }
            else if(*semi_colon) {
                *head = *semi_colon;
            }
        }
        else if(!squort && !dquort && **p == '(') {
            (*p)++;

            skip_paren(p, head, comma, semi_colon);

            if(*comma) {
                *head = *comma;
            }
            else if(*semi_colon) {
                *head = *semi_colon;
            }
        }
        else if(!squort && !dquort && **p == '}') {
            (*p)++;

            *head = head_before;
            *comma = NULL;
            *semi_colon = NULL;
            break;
        }
        else if(!squort && !dquort && **p == ',') {
            (*p)++;

            *comma = *p;
        }
        else if(!squort && !dquort && **p == ';') {
            (*p)++;

            *semi_colon = *p;
        }
        else if(!squort && !dquort && **p == '&' && *(*p+1) == '&') {
            (*p)+=2;

            *head = *p;
        }
        else if(!squort && !dquort && **p == '|' && *(*p+1) == '|') {
            (*p)+=2;

            *head = *p;
        }
        else if(!squort && !dquort && **p == '|') {
            (*p)++;

            *head = *p;
        }
        else if(!squort && !dquort && strstr(*p, "return") == *p) {
            (*p) += strlen("return");

            while(**p == ' ' || **p == '\t') {
                (*p)++;
            }

            *head = *p;
        }
        else if(**p == '\'') {
            (*p)++;
            squort = !squort;
        }
        else if(**p == '"') {
            (*p)++;
            dquort = !dquort;
        }
        else {
            (*p)++;
        }
    }
}

static char* get_one_expression(char* source)
{
    char* head = source;
    char* comma = NULL;
    char* semi_colon = NULL;
    BOOL squort = FALSE;
    BOOL dquort = FALSE;

    char* p = source + strlen(source);

    while(p >= source) {
        if(*p == ';') {
            break;
        }
        
        p--;
    }

    p++;

    while(*p == ' ' || *p == '\t') {
        p++;
    }

    head = p;

    while(*p) {
        if(!squort && !dquort && *p == '(') {
            p++;

            skip_paren(&p, &head, &comma, &semi_colon);

            if(comma) {
                head = comma;
            }
            else if(semi_colon) {
                head = semi_colon;
            }
        }
        else if(!squort && !dquort && *p == '{') {
            p++;

            skip_curly(&p, &head, &comma, &semi_colon);

            if(comma) {
                head = comma;
            }
            else if(semi_colon) {
                head = semi_colon;
            }
        }
        else if(*p == '&' && *(p+1) == '&') {
            p+=2;

            head = p;
        }
        else if(*p == '|' && *(p+1) == '|') {
            p+=2;

            head = p;
        }
        else if(*p == '|') {
            p++;

            head = p;
        }
        else if(*p == '=' || *p == '<') {
            p++;

            head = p;
        }
        else if(strstr(p, "return") == p) {
            p += strlen("return");

            while(*p == ' ' || *p == '\t') {
                p++;
            }

            head = p;
        }
        else if(strstr(p, "new") == p) {
            p += strlen("new");

            while(*p == ' ' || *p == '\t') {
                p++;
            }

            head = p;
        }
        else if(*p == '\'') {
            p++;
            squort = !squort;
        }
        else if(*p == '"') {
            p++;
            dquort = !dquort;
        }
        else if(*p == ';') {
            *p = '\0';
            break;
        }
        else {
            p++;
        }
    }

    return head;
}

char** gCandidates = NULL;
int gNumCandidates = 0;

BOOL gInputingMethod = FALSE;
BOOL gInputingPath = FALSE;
BOOL gInputingCommandPath = FALSE;

CLVALUE* gStack = NULL;
sVarTable* gLVTable = NULL;

static void file_completion(char* line)
{
    DIR* result_opendir;
    char path[PATH_MAX];

    char* p = (char*)line + strlen(line);
    while(p >= line) {
        if(*p == '"') {
            break;
        }
        else {
            p--;
        }
    }

    if(*(p + 1) == 0) {
        result_opendir = opendir(".");
        path[0] = 0;
    }
    else {
        char* text2 = MSTRDUP(p + 1);

        if(text2[0] == '~') {
            char text3[PATH_MAX];
            char* home;

            home = getenv("HOME");

            if(home) {
                if(text2[1] == '/') {
                    snprintf(text3, PATH_MAX, "%s/%s", home, text2 + 2);
                }
                else {
                    snprintf(text3, PATH_MAX, "%s/%s", home, text2 + 1);
                }

                rl_delete_text(rl_point-strlen(text2), rl_point);
                rl_point -=strlen(text2);
                rl_insert_text(text3);

                result_opendir = opendir(text3);

                xstrncpy(path, text3, PATH_MAX);
            }
            else {
                result_opendir = opendir(text2);

                xstrncpy(path, text2, PATH_MAX);
            }
        }

        if(text2[0] == '.' && text2[1] == '/') {
            result_opendir = opendir(".");

            xstrncpy(path, "./", PATH_MAX);
        }
        else if(text2[strlen(text2)-1] == '/') {
            result_opendir = opendir(text2);

            xstrncpy(path, text2, PATH_MAX);
        }
        else {
            char* dirname_;

            dirname_ = dirname(text2);
            result_opendir = opendir(dirname_);

            if(strcmp(dirname_, ".") == 0) {
                path[0] = 0;
            }
            else {
                xstrncpy(path, dirname_, PATH_MAX);

                if(dirname_[strlen(dirname_)-1] != '/' ) {
                    xstrncat(path, "/", PATH_MAX);
                }
            }
        }

        MFREE(text2);
    }

    if(result_opendir) {
        int n;
        int size;

        n = 0;
        size = 128;

        gCandidates = MCALLOC(1, sizeof(char*)*size);

        while(1) {
            struct dirent* result_readdir;
            int len;
            char* candidate;

            result_readdir = readdir(result_opendir);

            if(result_readdir == NULL) {
                break;
            }

            if(strcmp(result_readdir->d_name, ".") != 0 && strcmp(result_readdir->d_name, "..") != 0)
            {
                struct stat stat_;
                len = strlen(path) + strlen(result_readdir->d_name) + 2 + 1 + 1;

                candidate = MMALLOC(len);

                xstrncpy(candidate, path, len);
                xstrncat(candidate, result_readdir->d_name, len);

                if(stat(candidate, &stat_) == 0) {
                    if(S_ISDIR(stat_.st_mode)) {
                        xstrncat(candidate, "/", len);
                    }

                    gCandidates[n++] = MANAGED candidate;

                    if(n >= size) {
                        size *= 2;
                        gCandidates = MREALLOC(gCandidates, sizeof(char*)*size);
                    }
                }
                else {
                    MFREE(candidate);
                }
            }
        }

        gCandidates[n] = NULL;

        gNumCandidates = n;

        closedir(result_opendir);
    }

    rl_completer_word_break_characters = "\t\n\"";
}

static void file_completion_command_line(char* text)
{
    DIR* result_opendir;
    char path[PATH_MAX];

    char* p = (char*)text + strlen(text);
    while(p >= text) {
        if(*p == ' ' || *p == '\t') {
            p++;
            break;
        }
        else {
            p--;
        }
    }

    if(*p == 0) {
        result_opendir = opendir(".");
        path[0] = 0;
    }
    else {
        char* text2 = MSTRDUP(p);

        if(text2[0] == '~') {
            char text3[PATH_MAX];
            char* home;

            home = getenv("HOME");

            if(home) {
                if(text2[1] == '/') {
                    snprintf(text3, PATH_MAX, "%s/%s", home, text2 + 2);
                }
                else {
                    snprintf(text3, PATH_MAX, "%s/%s", home, text2 + 1);
                }

                rl_delete_text(rl_point-strlen(text2), rl_point);
                rl_point -=strlen(text2);
                rl_insert_text(text3);

                result_opendir = opendir(text3);

                xstrncpy(path, text3, PATH_MAX);
            }
            else {
                result_opendir = opendir(text2);

                xstrncpy(path, text2, PATH_MAX);
            }
        }

        if(text2[0] == '.' && text2[1] == '/') {
            result_opendir = opendir(".");

            xstrncpy(path, "./", PATH_MAX);
        }
        else if(text2[strlen(text2)-1] == '/') {
            result_opendir = opendir(text2);

            xstrncpy(path, text2, PATH_MAX);
        }
        else {
            char* dirname_;

            dirname_ = dirname(text2);

            result_opendir = opendir(dirname_);

            if(strcmp(dirname_, ".") == 0) {
                path[0] = 0;
            }
            else {
                xstrncpy(path, dirname_, PATH_MAX);

                if(dirname_[strlen(dirname_)-1] != '/' ) {
                    xstrncat(path, "/", PATH_MAX);
                }
            }
        }

        MFREE(text2);
    }

    if(result_opendir) {
        int n;
        int size;

        n = 0;
        size = 128;

        gCandidates = MCALLOC(1, sizeof(char*)*size);

        while(1) {
            struct dirent* result_readdir;
            int len;
            char* candidate;

            result_readdir = readdir(result_opendir);

            if(result_readdir == NULL) {
                break;
            }

            if(strcmp(result_readdir->d_name, ".") != 0 && strcmp(result_readdir->d_name, "..") != 0)
            {
                struct stat stat_;
                len = strlen(path) + strlen(result_readdir->d_name) + 2 + 1 + 1;

                candidate = MMALLOC(len);

                xstrncpy(candidate, path, len);
                xstrncat(candidate, result_readdir->d_name, len);

                if(stat(candidate, &stat_) == 0) {
                    if(S_ISDIR(stat_.st_mode)) {
                        xstrncat(candidate, "/", len);
                    }

                    gCandidates[n++] = MANAGED candidate;

                    if(n >= size) {
                        size *= 2;
                        gCandidates = MREALLOC(gCandidates, sizeof(char*)*size);
                    }
                }
                else {
                    MFREE(candidate);
                }
            }
        }

        gCandidates[n] = NULL;

        gNumCandidates = n;

        closedir(result_opendir);
    }
}

/// get program name from PATH environment variable ///
void command_completion(char* line, char** candidates, int num_candidates)
{
    int size = 128 + num_candidates;
    gCandidates = MCALLOC(1, sizeof(char*)*size);
    int i;
    for(i=0; i<num_candidates; i++) {
        gCandidates[i] = candidates[i];
    }
    int n = num_candidates;

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
                                        gCandidates[n++] = MANAGED MSTRDUP(candidate);

                                        if(n >= size) {
                                            size *= 2;
                                            gCandidates = MREALLOC(gCandidates, sizeof(char*)*size);
                                        }

                                        snprintf(candidate, PATH_MAX, "%s", entry->d_name);
                                        gCandidates[n++] = MANAGED MSTRDUP(candidate);

                                        if(n >= size) {
                                            size *= 2;
                                            gCandidates = MREALLOC(gCandidates, sizeof(char*)*size);
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

    gCandidates[n] = NULL;
    gNumCandidates = n;
}

void get_class_names(char** candidates, int *num_candidates, int max_candidates)
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        if(*num_candidates < max_candidates) {
            candidates[*num_candidates] = MSTRDUP(p->mName);
            (*num_candidates)++;
        }

        p = p->mNextClass;
    }
}

void get_global_method_names(char** candidates, int *num_candidates, int max_candidates)
{
    sCLClass* global_class = get_class("Global");

    MASSERT(global_class != NULL);

    int i;
    for(i=0; i<global_class->mNumMethods; i++) {
        sCLMethod* method = global_class->mMethods + i;

        if(method->mFlags & METHOD_FLAGS_CLASS_METHOD) {
            sBuf buf;
            sBuf_init(&buf);

            sBuf_append_str(&buf, METHOD_NAME2(global_class, method));
            sBuf_append_str(&buf, "(");

            int j;
            for(j=0; j<method->mNumParams; j++) {
                sCLParam* param = method->mParams + j;
                sCLType* param_type = param->mType;

                char* argment_names = ALLOC cl_type_to_buffer(param_type, global_class);

                sBuf_append_str(&buf, argment_names);

                if(j!=method->mNumParams-1) sBuf_append_str(&buf, ",");

                MFREE(argment_names);
            }

            sBuf_append_str(&buf, ")");

            if(*num_candidates < max_candidates) {
                candidates[*num_candidates] = MANAGED buf.mBuf;
                (*num_candidates)++;
            }
            else {
                MFREE(buf.mBuf);
            }
        }
    }

}

void get_system_method_names(char** candidates, int *num_candidates, int max_candidates)
{
    sCLClass* system_class = get_class("System");

    MASSERT(system_class != NULL);

    int i;
    for(i=0; i<system_class->mNumMethods; i++) {
        sCLMethod* method = system_class->mMethods + i;

        if(method->mFlags & METHOD_FLAGS_CLASS_METHOD) {
            sBuf buf;
            sBuf_init(&buf);

            sBuf_append_str(&buf, METHOD_NAME2(system_class, method));
            sBuf_append_str(&buf, "(");

            int j;
            for(j=0; j<method->mNumParams; j++) {
                sCLParam* param = method->mParams + j;
                sCLType* param_type = param->mType;

                char* argment_names = ALLOC cl_type_to_buffer(param_type, system_class);

                sBuf_append_str(&buf, argment_names);

                if(j!=method->mNumParams-1) sBuf_append_str(&buf, ",");

                MFREE(argment_names);
            }

            sBuf_append_str(&buf, ")");

            if(*num_candidates < max_candidates) {
                candidates[*num_candidates] = MANAGED buf.mBuf;
                (*num_candidates)++;
            }
            else {
                MFREE(buf.mBuf);
            }
        }
    }
}

void local_variable_completion(char** candidates, int *num_candidates, int max_candidates)
{
    BOOL expression_is_void = TRUE;

    char* p = rl_line_buffer;
    while(*p) {
        if(*p == ' ' || *p == '\t' || *p == '\n' || isalpha(*p) || *p == '(' || *p == '_') {
            p++;
        }
        else {
            expression_is_void = FALSE;
            p++;
        }
    }

    if(expression_is_void) {
        sVarTable* table = gLVTable;

        while(table) {
            int j;
            for(j=0; j<LOCAL_VARIABLE_MAX; j++) {
                sVar* var = table->mLocalVariables + j;
                if(var->mName[0] != '\0') {
                    if(*num_candidates < max_candidates) {
                        candidates[*num_candidates] = MANAGED MSTRDUP(var->mName);
                        (*num_candidates)++;
                    }
                }
            }

            table = table->mParent;
        }
    }
    else {
        char* line2 = MCALLOC(1, sizeof(char)*(rl_point+1));
        memcpy(line2, rl_line_buffer, rl_point);
        line2[rl_point] = '\0';

        /// get type ///
        sVarTable* lv_table;
        sNodeType* type_ = NULL;
        sVarTable* tmp_lv_table = clone_var_table(gLVTable);
        (void)get_type(line2, "iclover2", tmp_lv_table, gStack, &type_, &lv_table);

        sVarTable* table = lv_table;

        while(table) {
            int j;
            for(j=0; j<LOCAL_VARIABLE_MAX; j++) {
                sVar* var = table->mLocalVariables + j;
                if(var->mName[0] != '\0') {
                    if(*num_candidates < max_candidates) {
                        candidates[*num_candidates] = MANAGED MSTRDUP(var->mName);
                        (*num_candidates)++;
                    }
                }
            }

            table = table->mParent;
        }

        MFREE(line2);
    }
}

char* on_complete(const char* text, int a);

static int my_complete_internal(int count, int key)
{
    gInputingMethod = FALSE;
    gInputingPath = FALSE;
    gInputingCommandPath = FALSE;
    gCandidates = NULL;
    gNumCandidates = 0;

    /// parse the line ///
    char* line = ALLOC line_buffer_from_head_to_cursor_point();
    char* exp = get_one_expression(line);

    /// in double quote or single quote ? ///
    BOOL in_double_quote = FALSE;
    BOOL in_single_quote = FALSE;
    char* p = exp;

    while(*p) {
        if(*p == '"') {
            p++;
            in_double_quote = !in_double_quote;
        }
        else if(*p == '\'') {
            p++;
            in_single_quote = !in_single_quote;
        }
        else if(*p == '\\') {
            p++;
            if(*p != '\0') {
                p++;
            }
        }
        else {
            p++;
        }
    }

    /// Is Command line ? ///
    BOOL inputing_command_line = FALSE;
    p = exp;
    while(*p) {
        if(*p == ' ' || *p == '\t') {
            p++;
        }
        else if(isalnum(*p) || *p == '-') {
            /// Command name ///
            while(isalnum(*p) || *p == '-') {
                p++;
            }

            if(*p == ' ' || *p == '\t') {
                while(*p == ' ' || *p == '\t') {
                    p++;
                }

                if(*p != '(' && *p != '{') {
                    inputing_command_line = TRUE;

                    /// params ////
                    while(*p) {
                        while(!(*p == ' ' || *p == '\t' || *p == '\0')) {
                            p++;
                        }
                        while(*p == ' ' || *p == '\t') {
                            p++;
                        }
                    }
                    break;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }

    /// Is expression void ? ///
    BOOL expression_is_void = TRUE;

    p = exp;
    while(*p) {
        if(*p == ' ' || *p == '\t' || *p == '\n' || isalpha(*p) || *p == '(' || *p == '_') {
            p++;
        }
        else {
            expression_is_void = FALSE;
            p++;
        }
    }

    p = exp + strlen(exp) -1;
    while(p >= exp) {
        if(isalnum(*p) || *p == '_') {
            p--;
        }
        else {
            break;
        }
    }

    /// Is in the method block ? ///
    BOOL in_the_method_block = FALSE;

    p = line;
    while(*p) {
        if(*p == '"') {
            p++;
            while(*p) {
                if(*p == '\\' && *p == '"') {
                    p+=2;
                }
                else if(*p == '"') {
                    p++;
                    break;
                }
                else {
                    p++;
                }
            }
        }
        else if(*p == '\'') {
            p++;

            if(*p == '\0') {
            }
            else if(*p == '\\') {
                p++;

                if(*p == '\0') {
                }
                else {
                    p++;
                }
            }
            else {
                p++;
            }

            if(*p == '\'') {
                p++;
            }
        }
        else if(*p == '.' && (isalnum(*(p+1)) || *(p+1) == '_')) {
            p++;

            while(isalnum(*p) || *p == '_') {
                p++;
            }

            while(*p == ' ' || *p == '\t' || *p == '\n') {
                p++;
            }

            if(*p == '{') {
                p++;
                in_the_method_block = TRUE;

                while(*p) {
                    if(*p == '"') {
                        p++;
                        while(*p) {
                            if(*p == '\\' && *p == '"') {
                                p+=2;
                            }
                            else if(*p == '"') {
                                p++;
                                break;
                            }
                            else {
                                p++;
                            }
                        }
                    }
                    else if(*p == '\'') {
                        p++;

                        if(*p == '\0') {
                        }
                        else if(*p == '\\') {
                            p++;

                            if(*p == '\0') {
                            }
                            else {
                                p++;
                            }
                        }
                        else {
                            p++;
                        }

                        if(*p == '\'') {
                            p++;
                        }
                    }
                    else if(*p == '}') {
                        p++;
                        in_the_method_block = FALSE;
                        break;
                    }
                    else {
                        p++;
                    }
                }
            }
        }
        else {
            p++;
        }
    }

    /// is class name completion ? ///
    BOOL class_name_completion = FALSE;

    p = line + strlen(line) -1;
    while(p >= line) {
        if(isalnum(*p) || *p == '_' || *p == ' ' || *p == '\t' || *p == ',') {
            p--;
        }
        else if(*p == ':' || *p == '<') {
            class_name_completion = TRUE;
            break;
        }
        else if(strstr(p, "new") == p) {
            class_name_completion = TRUE;
            break;
        }
        else {
            break;
        }
    }

    /// class name completion ///
    if(!in_double_quote && !in_single_quote && class_name_completion) {
        int num_candidates = 0;
        int max_candidates = CLASS_NUM_MAX + 128;
        char** candidates = MCALLOC(1, sizeof(char*)*max_candidates);

        get_class_names(candidates, &num_candidates, max_candidates);

        int size = 128 + num_candidates;
        gCandidates = MCALLOC(1, sizeof(char*)*size);
        int i;
        for(i=0; i<num_candidates; i++) {
            gCandidates[i] = candidates[i];
        }
        gCandidates[i] = NULL;
        gNumCandidates = i;

        MFREE(candidates);

        gInputingMethod = TRUE;
        rl_completer_word_break_characters = "\t :<,";
    }
    /// command line ///
    else if(!in_double_quote && !in_single_quote && inputing_command_line) {
        rl_completion_entry_function = on_complete;

        file_completion_command_line(exp);

        gInputingCommandPath = TRUE;
        rl_completer_word_break_characters = "\t ";
    }
    /// first word ///
    else if(expression_is_void) {
        rl_completion_entry_function = on_complete;

        char* words[] = {
            "if(",
            "while(",
            "for(",
            "break",
            "true",
            "false",
            "null",
            "throw",
            "try(",
            "return",
            "new",
            "closure(",
            "lambda(",
            "block{",
            "inherit(",
            "list{",
            "equalable_list{",
            "sortable_list{",
            "elist{",
            "slist{",
            "tuple{",
            "hash{",
            "array{",
            "equalable_array{",
            "sortable_array{",
            "earray{",
            "sarray{",
            NULL
        };
        int num_words = 0;
        while(words[num_words]) {
            num_words++;
        }

        int num_candidates = 0;
        int max_candidates = CLASS_NUM_MAX + METHOD_NUM_MAX * 3 + 128 + LOCAL_VARIABLE_MAX * 3 + 1024;
        char** candidates = MCALLOC(1, sizeof(char*)*max_candidates);

        int i;
        for(i=0; i<num_words; i++) {
            candidates[i] = MANAGED MSTRDUP(words[i]);
        }

        num_candidates += num_words;
        
        get_class_names(candidates, &num_candidates, max_candidates);
        get_global_method_names(candidates, &num_candidates, max_candidates);
        get_system_method_names(candidates, &num_candidates, max_candidates);
        local_variable_completion(candidates, &num_candidates, max_candidates);
        command_completion(exp, candidates, num_candidates);
        MFREE(candidates);

        gInputingMethod = TRUE;
        rl_completer_word_break_characters = "\t\n.({ =";
    }
    /// inputing method name ///
    else if(!in_double_quote && !in_single_quote && *p == '.') {
        rl_completion_entry_function = on_complete;

        /// class method ? ///
        char* p2 = p;
        p2--;

        while(p2 >= exp) {
            if(isalnum(*p2) || *p2 == '_') {
                p2--;
            }
            else {
                break;
            }
        }

        p2++;

        char* class_name = MCALLOC(1, sizeof(char)*(p-p2+1));

        memcpy(class_name, p2, p-p2);
        class_name[p-p2] = 0;

        sCLClass* klass = get_class(class_name);

        MFREE(class_name);

        gCandidates = NULL;
        gNumCandidates = 0;

        /// normal method ///
        if(klass == NULL) {
            /// get type ///
            sNodeType* type_ = NULL;
            sVarTable* result_lv_table;
            sVarTable* tmp_lv_table = clone_var_table(gLVTable);

            if(in_the_method_block) {
                (void)get_type(line, "iclover2", tmp_lv_table, gStack, &type_, &result_lv_table);
            }
            else {
                (void)get_type(exp, "iclover2", tmp_lv_table, gStack, &type_, &result_lv_table);
            }

            if(type_) {
                klass = type_->mClass;

                if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                    klass = klass->mBoxingClass;
                }
                else if(type_->mArray) {
                    klass = get_class("Array");
                }

                if(klass) {
                    if(strcmp(CLASS_NAME(klass), "Command") == 0) {
                        int num_methods = 0;
                        char** candidates = ALLOC ALLOC get_method_names_with_arguments(klass, FALSE, &num_methods);
                        command_completion(exp, candidates, num_methods);

                        MFREE(candidates);
                    }
                    else {
                        int num_methods = 0;
                        gCandidates = ALLOC ALLOC get_method_names_with_arguments(klass, FALSE, &num_methods);
                        gNumCandidates = num_methods;
                    }
                }
            }
        }
        /// class method ///
        else {
            int num_methods = 0;
            gCandidates = ALLOC ALLOC get_method_names_with_arguments(klass, TRUE, &num_methods);
            gNumCandidates = num_methods;
        }

        gInputingMethod = TRUE;
        rl_completer_word_break_characters = "\t\n.({";
    }
    /// file completion ///
    else {
        rl_completion_entry_function = on_complete;

        file_completion(exp);

        gInputingPath = TRUE;
        rl_completer_word_break_characters = "\t ";
    }

    MFREE(line);

    return rl_complete(0, key);
}

static BOOL name_sort(char* lfname, char* rfname)
{
    return strcmp(lfname, rfname) < 0;
}

static BOOL quick_sort(int left, int right)
{
    int i;
    int j;

    if(left < right) {
        char* center_item = gCandidates[(left+right) / 2];

        i = left;
        j = right;

        do { 
            while(1) {
                int ret = name_sort(gCandidates[i], center_item);
                if(ret < 0) return FALSE;
                if(gCandidates[i] == center_item || !ret)
                {
                    break;
                }
                i++;
            }
                     
            while(1) {
                int ret = name_sort(center_item, gCandidates[j]);
                if(ret < 0) return FALSE;
                if(center_item==gCandidates[j] || !ret)
                {
                    break;
                }
                j--;
            }

            if(i <= j) {
                char* tmp = gCandidates[i];
                gCandidates[i] = gCandidates[j];
                gCandidates[j] = tmp;

                i++;
                j--;
            }
        } while(i <= j);

        if(!quick_sort(left, j)) {
            return FALSE;
        }
        if(!quick_sort(i, right)) {
            return FALSE;
        }
    }

    return TRUE;
}

void sort_candidates()
{
    quick_sort(0, gNumCandidates-1);
}

char* on_complete(const char* text, int a)
{
    char* text2 = MSTRDUP((char*)text);

    if(gInputingMethod) {
        rl_completion_append_character = '(';

        if(strcmp(text2, "") != 0) {
            char* p = text2 + strlen(text2) -1;

            while(p >= text2) {
                if(*p == '(') {
                    char* tmp = MSTRDUP(p + 1);
                    MFREE(text2);
                    text2 = tmp;
                    break;
                }

                p--;
            }
        }
    }
    else if(gInputingPath) {
        rl_completion_append_character = '"';

        if(strcmp(text2, "") != 0) {
            char* p = text2 + strlen(text2) -1;

            while(p >= text2) {
                if(*p == ' ' || *p == '\t' || *p == '"') {
                    char* tmp = MSTRDUP(p + 1);
                    MFREE(text2);
                    text2 = tmp;
                    break;
                }

                p--;
            }
        }
    }
    else if(gInputingCommandPath) {
        rl_completion_append_character = ' ';

        if(strcmp(text2, "") != 0) {
            char* p = text2 + strlen(text2) - 1;

            while(p >= text2) {
                if(*p == ' ' || *p == '\t') {
                    char* tmp = MSTRDUP(p + 1);
                    MFREE(text2);
                    text2 = tmp;
                    break;
                }

                p--;
            }
        }
    }

    /// sort ///
    sort_candidates();

    /// go ///
    if(gCandidates) {
        if(strcmp(text2, "") == 0) {
            display_candidates(gCandidates);
            rl_forced_update_display();

            int j;
            for(j=0; j<gNumCandidates; j++) {
                MFREE(gCandidates[j]);
            }
            MFREE(gCandidates);
        }
        else {
            /// get candidates ///
            char* candidate;
            char** p2;
            char** candidates2;
            int num_candidates2;
            int j;

            p2 = gCandidates;

            candidates2 = MCALLOC(1, sizeof(char*)*(gNumCandidates+1));
            num_candidates2 = 0;

            while(p2 < gCandidates + gNumCandidates) {
                int len_candidate;
                int len_text;

                candidate = *p2;

                len_candidate = strlen(candidate);
                len_text = strlen(text2);

                if(len_candidate >= len_text && strncmp(candidate, text2, len_text) == 0) 
                {
                    candidates2[num_candidates2++] = candidate;
                }
                p2++;
            }

            candidates2[num_candidates2] = NULL;

            if(num_candidates2 == 0) {
            }
            else if(num_candidates2 == 1) {
                char* appended_chars;
                int len_candidate;
                int len_text;
                char* parenthesis;
                char appended_chars2[32];
                BOOL flg_field;

                candidate = *candidates2;

                flg_field = strstr(candidate, "(") == NULL && !gInputingCommandPath;

                if(gInputingMethod) {
                    parenthesis = strstr(candidate, "(");

                    if(parenthesis) {
                        len_candidate = parenthesis - candidate;
                    }
                    else {
                        len_candidate = strlen(candidate);
                    }
                }
                else {
                    len_candidate = strlen(candidate);
                }

                len_text = strlen(text2);

                appended_chars = MCALLOC(1, len_candidate-len_text+2);
                memcpy(appended_chars, candidate+len_text, len_candidate-len_text);
                appended_chars[len_candidate-len_text] = 0;

                rl_insert_text(appended_chars);

                MFREE(appended_chars);

                /// path completion ///
                if(gInputingPath) {
                    int len;

                    len = strlen(candidate);
                    if(candidate[len-1] != '/') {
                        appended_chars2[0] = rl_completion_append_character;
                        appended_chars2[1] = 0;

                        rl_insert_text(appended_chars2);
                    }
                }
                else if(gInputingCommandPath) {
                    int len = strlen(candidate);
                    if(candidate[len-1] != '/') {
                        appended_chars2[0] = rl_completion_append_character;
                        appended_chars2[1] = 0;

                        rl_insert_text(appended_chars2);
                    }
                }
                else if(gInputingMethod) {
                    int len = strlen(candidate);

                    if(candidate[len-1] == '(') {
                        appended_chars2[0] = rl_completion_append_character;
                        appended_chars2[1] = 0;

                        rl_insert_text(appended_chars2);
                    }
                }
                else if(flg_field) {
                    appended_chars2[0] = '.';
                    appended_chars2[1] = 0;

                    rl_insert_text(appended_chars2);
                }
                else {
                    rl_insert_text(appended_chars2);
                }

                display_candidates(candidates2);
                rl_forced_update_display();
            }
            else {
                /// get same text ///
                char* candidate_before;
                int same_len;

                candidate_before = NULL;
                same_len = -1;
                p2 = candidates2;

                while((candidate = *p2) != NULL) {
                    int i;
                    int len_candidate;
                    int len_candidate_before;

                    if(candidate_before) {
                        int len;
                        int same_len2;
                        char* parenthesis;

                        parenthesis = strstr(candidate, "(");
                        if(parenthesis) {
                            len_candidate = parenthesis - candidate;
                        }
                        else {
                            len_candidate = strlen(candidate);
                        }

                        parenthesis = strstr(candidate_before, "(");
                        if(parenthesis) {
                            len_candidate_before = parenthesis - candidate_before;
                        }
                        else {
                            len_candidate_before = strlen(candidate_before);
                        }


                        if(len_candidate < len_candidate_before) {
                            len = len_candidate;
                        }
                        else {
                            len = len_candidate_before;
                        }

                        same_len2 = len;

                        for(i=0; i<len; i++) {
                            if(candidate[i] != candidate_before[i]) {
                                same_len2 = i;
                                break;
                            }
                        }

                        if(same_len == -1 || same_len2 < same_len) {
                            same_len = same_len2;
                        }
                    }
                    
                    candidate_before = *p2;
                    p2++;
                }

                candidate = *candidates2;

                if(same_len > 0) {
                    char* appended_chars;
                    int len_candidate;
                    int len_text;

                    len_candidate = strlen(candidate);
                    len_text = strlen(text2);

                    if(same_len - len_text == 0) {
                        display_candidates(candidates2);
                        rl_forced_update_display();
                    }
                    else {
                        appended_chars = MCALLOC(1, same_len-len_text+2);
                        memcpy(appended_chars, candidate+len_text, same_len-len_text);
                        appended_chars[same_len-len_text] = 0;

                        rl_insert_text(appended_chars);

                        MFREE(appended_chars);
                    }
                }
                else if(same_len == 0) {
                    display_candidates(candidates2);
                    rl_forced_update_display();
                }
            }

            MFREE(candidates2);

            for(j=0; j<gNumCandidates; j++) {
                MFREE(gCandidates[j]);
            }
            MFREE(gCandidates);
        }
    }

    MFREE(text2);

    return 0;
}

static BOOL inputing_block_or_paren()
{
    char* source = rl_line_buffer;

    char* p = source;
    int block_nest = 0;
    int paren_nest = 0;

    while(*p) {
        if(*p == '{') {
            p++;

            block_nest++;
        }
        else if(*p == '}') {
            p++;

            block_nest--;
        }
        else if(*p == '(') {
            p++;

            paren_nest++;
        }
        else if(*p == ')') {
            p++;

            paren_nest--;
        }
        else {
            p++;
        }
    }

    return block_nest > 0 || paren_nest > 0;
}

static int my_bind_cr(int count, int key) 
{
    if(inputing_block_or_paren()) {
        rl_insert_text("\n");
    }
    else {
        puts("");
        rl_done = 1;
    }

    return 0;
}

static void sig_int()
{
    gSigInt = TRUE;

    rl_reset_line_state();
    rl_replace_line("", 0);
    rl_point = 0;
    puts("");
    rl_redisplay();
}

static void set_signal_for_interpreter() 
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = sig_int;
    if(sigaction(SIGINT, &sa, NULL) < 0) {
        perror("sigaction2");
        exit(1);
    }

    sigset_t signal_set;

    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGTTOU);
    sigaddset(&signal_set, SIGPIPE);

    sigprocmask(SIG_BLOCK, &signal_set, NULL);
}

#define MAX_CODES 1024*4

static sByteCode gCodes[MAX_CODES];
static sConst gConst[MAX_CODES];
static int gNumCodes;

static void interpreter_init()
{
    gInterpreter = TRUE;
    memset(gCodes, 0, sizeof(sByteCode)*MAX_CODES);
    memset(gConst, 0, sizeof(sConst)*MAX_CODES);

    gNumCodes = 0;
}

static void interpreter_final()
{
    int i;
    for(i=0; i<gNumCodes; i++) {
        sByteCode_free(&gCodes[i]);
        sConst_free(&gConst[i]);
    }
}

static BOOL eval_str(char* source, char* fname, sVarTable* lv_table, CLVALUE* stack)
{
    sParserInfo info;

    memset(&info, 0, sizeof(sParserInfo));

    info.p = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = lv_table;
    info.parse_phase = 0;
    info.get_type_for_interpreter = FALSE;

    sCompileInfo cinfo;
    
    memset(&cinfo, 0, sizeof(sCompileInfo));

    sByteCode* code = &gCodes[gNumCodes];
    sByteCode_init(code);
    cinfo.code = code;

    sConst* constant = &gConst[gNumCodes];
    sConst_init(constant);
    cinfo.constant = constant;

    gNumCodes++;

    if(gNumCodes >= MAX_CODES) {
        fprintf(stderr, "overflow code and constant size. reset iclover2");
        exit(1);
    }

    cinfo.lv_table = lv_table;
    cinfo.no_output = FALSE;
    cinfo.pinfo = &info;

    info.cinfo = &cinfo;

    while(*info.p) {
        info.next_command_is_to_bool = FALSE;
        unsigned int node = 0;
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

            sCLClass* klass = cinfo.type->mClass;

            /// toString and println ///
            if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                cast_right_type_to_String(&cinfo.type, &cinfo);

                if(type_identify_with_class_name(cinfo.type, "String")) {
                    sCLClass* string_class = get_class("String");

                    MASSERT(string_class != NULL);

                    /// chomp ///
                    sNodeType* result_type = NULL;
                    sNodeType* result_method_generics_types = NULL;
                    int method_index = search_for_method(string_class, "chomp", NULL, 0, FALSE, string_class->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

                    if(method_index != -1) {
                        append_opecode_to_code(cinfo.code, OP_INVOKE_METHOD, cinfo.no_output);

                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code, method_index, cinfo.no_output);
                        int size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);

                        cinfo.stack_num--;
                        cinfo.stack_num++;

                        cinfo.type = result_type;
                    }

                    /// println ///
                    result_method_generics_types = NULL;
                    method_index = search_for_method(string_class, "printlnWithoutNullString", NULL, 0, FALSE, string_class->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

                    if(method_index != -1) {
                        append_opecode_to_code(cinfo.code, OP_INVOKE_METHOD, cinfo.no_output);

                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code, method_index, cinfo.no_output);
                        int size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);

                        cinfo.stack_num--;
                        cinfo.stack_num++;

                        cinfo.type = result_type;
                    }
                }
            }
            else {
                boxing_before_method_call("toString", &cinfo);

                klass = cinfo.type->mClass;

                sNodeType* result_type = NULL;
                sNodeType* result_method_generics_types = NULL;
                int method_index = search_for_method(klass, "toString", NULL, 0, FALSE, klass->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

                if(method_index != -1) {
                    append_opecode_to_code(cinfo.code, OP_INVOKE_METHOD, cinfo.no_output);

                    append_class_name_to_constant_pool_and_code(&cinfo, klass);
                    append_int_value_to_code(cinfo.code, method_index, cinfo.no_output);
                    int size = get_var_size(result_type);
                    append_int_value_to_code(cinfo.code, size, cinfo.no_output);

                    cinfo.stack_num--;
                    cinfo.stack_num++;

                    cinfo.type = result_type;

                    /// println ///
                    sCLClass* string_class = get_class("String");

                    MASSERT(string_class != NULL);

                    /// chomp ///
                    sNodeType* result_type = NULL;
                    sNodeType* result_method_generics_types = NULL;
                    int method_index = search_for_method(string_class, "chomp", NULL, 0, FALSE, string_class->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

                    if(method_index != -1) {
                        append_opecode_to_code(cinfo.code, OP_INVOKE_METHOD, cinfo.no_output);

                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code, method_index, cinfo.no_output);
                        int size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);

                        cinfo.stack_num--;
                        cinfo.stack_num++;

                        cinfo.type = result_type;
                    }

                    /// println ///
                    result_type = NULL;
                    result_method_generics_types = NULL;
                    method_index = search_for_method(string_class, "printlnWithoutNullString", NULL, 0, FALSE, string_class->mNumMethods-1, NULL, NULL, NULL, &result_type, FALSE, FALSE, &result_method_generics_types);

                    if(method_index != -1) {
                        append_opecode_to_code(cinfo.code, OP_INVOKE_METHOD, cinfo.no_output);

                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code, method_index, cinfo.no_output);
                        int size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);

                        cinfo.stack_num--;
                        cinfo.stack_num++;

                        cinfo.type = result_type;
                    }
                }
            }

            /// end of line ///
            arrange_stack(&cinfo);

#ifdef ENABLE_INTERPRETER
            append_opecode_to_code(cinfo.code, OP_SIGINT, cinfo.no_output);
#endif
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

    if(!vm(code, constant, stack, var_num, NULL, &vinfo)) {
        show_exception_message(vinfo.exception_message);

        return FALSE;
    }

    return TRUE;
}

static void clover2_init()
{
#ifdef ENABLE_JIT
    jit_init_on_runtime();
#endif
    native_method_init();
    class_init();
    heap_init(128, 128);
    stack_init();
    (void)class_init_on_runtime();
    //set_boxing_and_unboxing_classes();
}

static void clover2_final()
{
    class_final_on_runtime();
    heap_final();
    stack_final();
    class_final();
    native_method_final();
#ifdef ENABLE_JIT
    jit_final_on_runtime();
#endif
}

static void compiler_init(BOOL no_load_fudamental_classes)
{
    init_nodes();
    module_init();
}

static void compiler_final()
{
    module_final();
    free_nodes();
}

int gARGC;
char** gARGV;
char* gVersion = "3.6.5";

int main(int argc, char** argv)
{
    CHECKML_BEGIN;

    setlocale(LC_ALL, "");
    srandom((unsigned)time(NULL));

    setsid();

    gARGC = argc;
    gARGV = argv;

    set_signal_for_interpreter();

    rl_basic_word_break_characters = "\t\n";
    rl_completion_entry_function = on_complete;

    char history_path[PATH_MAX];
    snprintf(history_path, PATH_MAX, "%s/.clover2/history", getenv("HOME"));

    if(access(history_path, R_OK) == 0) {
        read_history(history_path);
    }

    init_vtable();
    init_node_types();
    init_node_block_types();
    clover2_init();
    interpreter_init();
    parser_init();

    rl_bind_key('\t', my_complete_internal);
    rl_bind_key('\n', my_bind_cr);
    rl_bind_key('\r', my_bind_cr);

    printf("Welcome to Clover2\n");
    sVarTable* lv_table = init_var_table();
    int stack_size = 512;
    CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);

    gStack = stack;
    gLVTable = lv_table;

    while(1) {
        compiler_init(FALSE);

        char* line = readline("> ");

        if(line == NULL) {
            compiler_final();
            break;
        }

        /// delete last spaces and semicolon ///
        char* p = line + strlen(line) -1;
        while(p >= line) {
            if(*p == ' ' || *p == '\t' || *p == '\n') {
                *p = '\0';
                p--;
            }
            else {
                break;
            }
        }

        if(line[strlen(line)-1] == ';') {
            line[strlen(line)-1] = '\0';
        }

        if(!eval_str(line, "iclover2", lv_table, stack)) {
            fprintf(stderr, "compile or runtime error\n");
        }

        compiler_final();

        add_history(line);

        free(line);
    }

    parser_final();
    interpreter_final();
    clover2_final();
    final_vtable();
    free_node_types();
    free_node_block_types();

    MFREE(stack);

    char history_dir[PATH_MAX];
    snprintf(history_dir, PATH_MAX, "%s/.clover2", getenv("HOME"));

    if(access(history_dir, X_OK) != 0) {
        (void)system("mkdir -p ~/.clover2");
    }

    write_history(history_path);

    CHECKML_END;

    exit(0);
}
