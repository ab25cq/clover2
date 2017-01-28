#include "common.h"
#include <locale.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
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

/*
static void get_class_name_or_namespace_name(char* result, char** p)
{
    if(isalpha(**p)) {
        while(isalpha(**p) || **p == '_' || isdigit(**p)) {
            *result = **p;
            result++;
            (*p)++;
        }
    }

    if(**p == '$') {
        *result = **p;
        result++;
        (*p)++;

       while(isdigit(**p)) {
           *result = **p;
           result++;
           (*p)++;
       }
    }

    while(**p == ' ' || **p == '\t' || **p == '\n') (*p)++;

    *result = 0;
}

static BOOL parse_class_name(char** p, sCLClass** klass)
{
    char real_class_name[CL_REAL_CLASS_NAME_MAX+1];

    get_class_name_or_namespace_name(real_class_name, p);

    if(**p == ':' && *(*p+1) == ':') {
        char real_class_name2[CL_REAL_CLASS_NAME_MAX];

        (*p)+=2;
        while(**p == ' ' || **p == '\t' || **p == '\n') (*p)++;

        get_class_name_or_namespace_name(real_class_name2, p);

        xstrncat(real_class_name, "::", CL_REAL_CLASS_NAME_MAX);
        xstrncat(real_class_name, real_class_name2, CL_REAL_CLASS_NAME_MAX);
    }

    *klass = cl_get_class(real_class_name);

    return TRUE;
}



static char** get_var_names(int* num_var_names)
{
    char* source;
    sBuf output;
    char** var_names;
    char* p;
    char* head_of_line;
    char** result;
    int result_size;
    
    source = ALLOC line_buffer_from_head_to_cursor_point();

    if(!run_parser("psclover --no-output get_variable_names", source, ALLOC &output)) {
        MFREE(source);
        *num_var_names = 0;
        return NULL;
    }

    MFREE(source);

    result_size = 128;
    result = MMALLOC(sizeof(char*)*result_size);

    p = output.mBuf;

    *num_var_names = 0;
    head_of_line = p;

    while(1) {
        if(*p == '\n') {
            char* line;
            int size;

            size = p - head_of_line;

            line = MMALLOC(size + 1);
            memcpy(line, head_of_line, size);
            line[size] = 0;

            result[*num_var_names] = MANAGED line;
            (*num_var_names)++;

            if(*num_var_names >= result_size) {
                result_size *= 2;
                result = MREALLOC(result, sizeof(char*)*result_size);
            }

            p++;
            head_of_line = p;
        }
        else if(*p == '\0') {
            char* line;
            int size;

            size = p - head_of_line;

            line = MMALLOC(size + 1);
            memcpy(line, head_of_line, size);
            line[size] = 0;

            result[*num_var_names] = MANAGED line;
            (*num_var_names)++;

            if(*num_var_names >= result_size) {
                result_size *= 2;
                result = MREALLOC(result, sizeof(char*)*result_size);
            }
            break;
        }
        else {
            p++;
        }
    }

    MFREE(output.mBuf);

    return result;
}
*/

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

static ALLOC char* cl_type_to_buffer(sCLType* cl_type, sCLClass* klass)
{
    int i;
    sBuf buf;

    sBuf_init(&buf);

    if(cl_type == NULL) {
        sBuf_append_str(&buf, "NULL");
    }
    else if(cl_type->mNumGenericsTypes == 0) {
        sBuf_append_str(&buf, CONS_str(&klass->mConst, cl_type->mClassNameOffset));
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
    
/*
    /// field ///
    if(class_method) {
        for(i=0; i<klass->mNumFields; i++) {
            sCLField* field;

            field = klass->mFields + i;

            if(field->mFlags & CL_STATIC_FIELD) {
                *(result+result_num) = MSTRDUP(FIELD_NAME(klass, i));
                result_num++;

                if(result_num >= result_size) {
                    result_size *= 2;
                    result = MREALLOC(result, sizeof(char*)*result_size);
                }
            }
        }
    }
    else {
    }
*/

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

static BOOL get_type(char* source, char* fname, sVarTable* lv_table, CLVALUE* stack, sNodeType** type_)
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
        unsigned int node = 0;
        (void)expression(&node, &info);

        (void)compile(node, &cinfo);

        *type_ = cinfo.type;

        if(*info.p == ';') {
            info.p++;
            skip_spaces_and_lf(&info);
        }
    }

    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}

static BOOL skip_paren(char** p) 
{
    while(1) {
        if(**p == '(') {
            (*p)++;
            
            if(!skip_paren(p)) {
                return FALSE;
            }
        }
        else if(**p == ')') {
            (*p)++;

            break;
        }
        else if(**p == '\0') {
            return FALSE;
        }
        else {
            (*p)++;
        }
    }

    return TRUE;
}

static BOOL skip_curly(char** p) 
{
    while(1) {
        if(**p == '{') {
            (*p)++;
            
            if(!skip_curly(p)) {
                return FALSE;
            }
        }
        else if(**p == '}') {
            (*p)++;

            break;
        }
        else if(**p == '\0') {
            return FALSE;
        }
        else {
            (*p)++;
        }
    }

    return TRUE;
}

static char* get_one_line(char* source)
{
    char* head = source;

    char* p = source;

    while(*p) {
        if(*p == '(') {
            p++;

            char* p2 = p;
            
            if(!skip_paren(&p2)) {
                head = p;
            }
        }
        else if(*p == '{') {
            p++;

            char* p2 = p;
            
            if(!skip_curly(&p2)) {
                head = p;
            }
        }
        else if(*p == ',') {
            p++;
            head = p;
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
BOOL gInputingClass = FALSE;

CLVALUE* gStack = NULL;
sVarTable* gLVTable = NULL;

static int my_complete_internal(int count, int key)
{
    gInputingMethod = FALSE;
    gInputingPath = FALSE;
    gInputingClass = FALSE;
    gCandidates = NULL;
    gNumCandidates = 0;

    /// parse source ///
    char* source = ALLOC line_buffer_from_head_to_cursor_point();
    char* line = get_one_line(source);

    char* p = line + strlen(line) -1;
    while(p >= line) {
        if(isalnum(*p) || *p == '_') {
            p--;
        }
        else {
            break;
        }
    }

    /// inputing method name ///
    if(*p == '.') {
        /// class method ? ///
        char* p2 = p;
        p2--;

        while(p2 >= line) {
            if(isalnum(*p2) || *p2 == '_') {
                p2--;
            }
            else {
                break;
            }
        }

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
            (void)get_type(line, "iclover2", gLVTable, gStack, &type_);

            klass = type_->mClass;

            if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                klass = klass->mBoxingClass;
            }

            if(klass) {
                int num_methods = 0;
                gCandidates = ALLOC ALLOC get_method_names_with_arguments(klass, FALSE, &num_methods);
                gNumCandidates = num_methods;
            }
        }
        /// class method ///
        else {
            int num_methods = 0;
            gCandidates = ALLOC ALLOC get_method_names_with_arguments(klass, TRUE, &num_methods);
            gNumCandidates = num_methods;
        }

        rl_completer_word_break_characters = "\t\n.";

        gInputingMethod = TRUE;
    }
    else {
/*
        /// path completion ///
        if(inputing_path) {
            DIR* result_opendir;
            char path[PATH_MAX];

            gInputingPath = TRUE;

            p = (char*)line + strlen(line);
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
                text2 = MSTRDUP(p + 1);

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

                if(text2[strlen(text2)-1] == '/') {
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
                    }
                }

                gCandidates[n] = NULL;

                gNumCandidates = n;

                closedir(result_opendir);
            }

            rl_completer_word_break_characters = "\t\n\"";
        }
        /// method completion ///
        else if(inputing_method_name) {
        }
        /// class completion ///
        else {
            char** class_names;
            char** var_names;
            int num_class_names;
            int num_var_names;
            int i;

            gInputingClass = TRUE;
            
            class_names = ALLOC get_class_names(&num_class_names);

            var_names = ALLOC ALLOC get_var_names(&num_var_names);

            gCandidates = MCALLOC(1, sizeof(char*)*(num_class_names+num_var_names+1));

            for(i=0; i<num_class_names; i++) {
                gCandidates[i] = MSTRDUP(class_names[i]);
            }

            for(i=0; i<num_var_names; i++) {
                gCandidates[i+num_class_names] = MSTRDUP(var_names[i]);
            }

            gCandidates[i+num_class_names] = NULL;

            gNumCandidates = num_class_names + num_var_names;

            MFREE(class_names);
            if(var_names) {
                for(i=0; i<num_var_names; i++) {
                    MFREE(var_names[i]);
                }
                MFREE(var_names);
            }

            rl_completer_word_break_characters = " \t\n.(!\"#$%&')-=~^|\{`@[]}*+;:?/><,";
        }

        MFREE(source);
*/
    }

    MFREE(source);

    return rl_complete(0, key);
}

char* on_complete(const char* text, int a)
{
    if(gInputingMethod) {
        rl_completion_append_character = '(';
    }
    else if(gInputingPath) {
        rl_completion_append_character = '"';
    }
    else if(gInputingClass) {
        rl_completion_append_character = 0;
    }

    /// sort ///

    /// go ///
    if(gCandidates) {
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
            len_text = strlen(text);

            if(len_candidate >= len_text && strncmp(candidate, text, len_text) == 0) 
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

            flg_field = strstr(candidate, "(") == NULL;

            if(rl_completion_append_character == '(') {
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

            len_text = strlen(text);

            appended_chars = MCALLOC(1, len_candidate-len_text+2);
            memcpy(appended_chars, candidate+len_text, len_candidate-len_text);
            appended_chars[len_candidate-len_text] = 0;

            rl_insert_text(appended_chars);

            MFREE(appended_chars);

            /// path completion ///
            if(rl_completion_append_character == '"') {
                int len;

                len = strlen(candidate);
                if(candidate[len-1] != '/') {
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
            else if(rl_completion_append_character != 0) {
                appended_chars2[0] = rl_completion_append_character;
                appended_chars2[1] = 0;

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
                len_text = strlen(text);

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

    sigprocmask(SIG_BLOCK, &signal_set, NULL);
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
        if(!expression(&node, &info)) {
            sByteCode_free(&code);
            sConst_free(&constant);
            return FALSE;
        }

        if(info.err_num == 0 && node != 0) {
            if(!compile(node, &cinfo)) {
                sByteCode_free(&code);
                sConst_free(&constant);
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
        sByteCode_free(&code);
        sConst_free(&constant);
        return FALSE;
    }

    int var_num = get_var_num(info.lv_table);

    sVMInfo vinfo;
    memset(&vinfo, 0, sizeof(sVMInfo));

    if(!vm(&code, &constant, stack, var_num, NULL, &vinfo)) {
        show_exception_message(vinfo.exception_message);

        sByteCode_free(&code);
        sConst_free(&constant);
        return FALSE;
    }

    sByteCode_free(&code);
    sConst_free(&constant);

    return TRUE;
}

static void clover2_init()
{
    native_method_init();
    class_init();
    heap_init(128, 128);
    stack_init();
    (void)class_init_on_runtime();
}

static void compiler_init(BOOL no_load_fudamental_classes)
{
    init_nodes();
    init_node_types();
    set_boxing_and_unboxing_classes();
    init_vtable();
    module_init();
}

static void clover2_final()
{
    native_method_final();
    stack_final();
    heap_final();
    class_final_on_runtime();
}

static void compiler_final()
{
    module_final();
    free_nodes();
    free_node_types();
    final_vtable();
}

int main(int argc, char** argv)
{
    CHECKML_BEGIN;

    setlocale(LC_ALL, "");
    srandom((unsigned)time(NULL));

    set_signal_for_interpreter();

    compiler_init(FALSE);

    rl_basic_word_break_characters = "\t\n.";
    //rl_attempted_completion_function = on_complete;
    rl_completion_entry_function = on_complete;

    rl_bind_key('\t', my_complete_internal);
    rl_bind_key('\n', my_bind_cr);
    rl_bind_key('\r', my_bind_cr);

    printf("Welcome to Clover2\n");
    sVarTable* lv_table = init_var_table();
    int stack_size = 512;
    CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
    clover2_init();

    gStack = stack;
    gLVTable = lv_table;

    while(1) {
        char* line = readline("> ");

        if(line == NULL) {
            break;
        }

        /// clone lv_table ///
        sVarTable* lv_table2 = clone_var_table(lv_table);

        /// get type ///
        sNodeType* type_ = NULL;
        (void)get_type(line, "iclover2", lv_table2, stack, &type_);

        if(type_ != NULL) {
            sCLClass* klass = type_->mClass;

            sNodeType* result_type = NULL;
            int method_index = search_for_method(klass, "toString", NULL, 0, FALSE, klass->mNumMethods-1, NULL, NULL, &result_type);

            /// evel ///
            if((method_index == -1 || !type_identify_with_class_name(result_type, "String")) && !(klass->mFlags & CLASS_FLAGS_PRIMITIVE)) {
                if(!eval_str(line, "iclover2", lv_table, stack)) {
                    fprintf(stderr, "compile or runtime error\n");
                }
            }
            else {
                int len = strlen(line) + 128;
                char* line2 = MCALLOC(1, sizeof(char)*len);

                snprintf(line2, len, "(%s).toString().chomp().println()", line);

                if(!eval_str(line2, "iclover2", lv_table, stack)) {
                    fprintf(stderr, "compile or runtime error\n");
                }

                MFREE(line2);

            }

            add_history(line);
        }

        free(line);
    }
    clover2_final();

    MFREE(stack);

    compiler_final();

    CHECKML_END;

    exit(0);
}
