#include "common.h"

#include <wchar.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>
#include <dirent.h>
#include <utime.h>
#include <fnmatch.h>
#include <signal.h>

BOOL System_exit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* num = lvar;

    exit(num->mIntValue);

    return TRUE;
}

BOOL System_assert(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* exp = lvar;

    if(!exp->mBoolValue) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "System.assert failed");
        return FALSE;
    }

    return TRUE;
}

BOOL System_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* size = lvar;

    char* memory = MMALLOC(size->mULongValue);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_calloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* number = lvar;
    CLVALUE* size = lvar + 1;

    char* memory = MCALLOC(number->mIntValue, size->mULongValue);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_realloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* ptr = lvar;
    CLVALUE* size = lvar + 1;

    char* memory = MREALLOC(ptr->mPointerValue, size->mULongValue);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_free(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pointer = lvar;

    MFREE(pointer->mPointerValue);

    return TRUE;
}

BOOL System_strlen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    (*stack_ptr)->mIntValue = strlen(str->mPointerValue);
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strlen2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    /// clover params to c params ///
    CLObject array = str->mObjectValue;

    if(array == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* object_data = CLOBJECT(array);
    int len = object_data->mArrayNum;
    
    /// go ///
    int result = -1;

    int i;
    for(i=0; i<len; i++) {
        if(object_data->mFields[i].mByteValue == '\0') {
            result = i;
            break;
        }
    }

    if(result == -1) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid byte array");
        return FALSE;
    }

    (*stack_ptr)->mIntValue = i;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strcpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;

    char* result = strcpy(str1->mPointerValue, str2->mPointerValue);

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_memcpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;
    CLVALUE* len = lvar + 2;

    void* result = memcpy(str1->mPointerValue, str2->mPointerValue, len->mULongValue);

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_memcmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;
    CLVALUE* size = lvar + 2;

    int result = memcmp(str1->mPointerValue, str2->mPointerValue, size->mULongValue);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strncpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;
    CLVALUE* size = lvar + 2;

    char* result = xstrncpy(str1->mPointerValue, str2->mPointerValue, size->mULongValue);

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strdup(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    char* result = MSTRDUP(str->mPointerValue);

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_print(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = wstr_array_object_data->mArrayNum;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    printf("%ls", wstr);
    fflush(stdout);

    MFREE(wstr);

    return TRUE;
}

BOOL System_println(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;
    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = str_data->mFields[2].mIntValue;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    printf("%ls\n", wstr);
    fflush(stdout);

    MFREE(wstr);

    return TRUE;
}

BOOL System_printToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;

    if(wstr_array_object == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = wstr_array_object_data->mArrayNum;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    fprintf(stderr, "%ls", wstr);
    fflush(stderr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_printlnToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* str_data = CLOBJECT(str->mObjectValue);

    CLObject wstr_array_object = str_data->mFields[0].mObjectValue;

    if(wstr_array_object == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* wstr_array_object_data = CLOBJECT(wstr_array_object);

    int len = wstr_array_object_data->mArrayNum;
    CLVALUE* wchar_t_array = wstr_array_object_data->mFields;

    wchar_t* wstr = MMALLOC(sizeof(wchar_t)*(len+1));

    int i;
    for(i=0; i<len; i++) {
        wstr[i] = wchar_t_array[i].mCharValue;
    }
    wstr[i] = '\0';

    fprintf(stderr, "%ls\n", wstr);
    fflush(stderr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_sleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* time = lvar;

    unsigned int result = sleep(time->mIntValue);

    (*stack_ptr)->mUIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_pcre_exec(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* regex = lvar;
    CLVALUE* str = (lvar+1);
    CLVALUE* offset = (lvar+2);
    CLVALUE* ovec_max = (lvar+3);
    CLVALUE* pcre_ovec = (lvar+4);

    /// check null pointer exception ///
    if(regex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(pcre_ovec->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// convert Clover value to C value ///
    sRegexObject* regex_object_data = CLREGEX(regex->mObjectValue);

    pcre* regex_value = regex_object_data->mRegex;

    sCLObject* object_data = CLOBJECT(str->mObjectValue);

    char* str_value = object_data->mFields[0].mPointerValue;
    int len = object_data->mFields[1].mULongValue;

    int ovec_max_value = ovec_max->mIntValue;
    int* ovec_value = MCALLOC(1, sizeof(int)*ovec_max_value * 3);

    int offset_value = offset->mIntValue;

    /// go ///
    int options = PCRE_NEWLINE_LF;
    int result = pcre_exec(regex_value, 0, str_value, len, offset_value, options, ovec_value, ovec_max_value*3);

    /// set result data on ovec object ///
    CLObject pcre_ovec_object = pcre_ovec->mObjectValue;
    sCLObject* pcre_ovec_object_data = CLOBJECT(pcre_ovec_object);

    CLObject pcre_ovec_start_array = pcre_ovec_object_data->mFields[0].mObjectValue;
    CLObject pcre_ovec_end_array = pcre_ovec_object_data->mFields[1].mObjectValue;

    if(pcre_ovec_start_array == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(pcre_ovec_end_array == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    sCLObject* pcre_ovec_start_array_data = CLOBJECT(pcre_ovec_start_array);
    sCLObject* pcre_ovec_end_array_data = CLOBJECT(pcre_ovec_end_array);

    int i;
    for(i=0; i<ovec_max_value; i++) {
        if(i < pcre_ovec_start_array_data->mArrayNum) {
            pcre_ovec_start_array_data->mFields[i].mIntValue = ovec_value[i*2];
        }
        if(i < pcre_ovec_end_array_data->mArrayNum) {
            pcre_ovec_end_array_data->mFields[i].mIntValue = ovec_value[i*2+1];
        }
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(ovec_value);

    return TRUE;
}

BOOL System_sprintf(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* format = lvar;
    CLVALUE* params = lvar+1;

    if(format->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(params->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* format_string = ALLOC string_object_to_char_array(format->mObjectValue);

    char* p = format_string;

    sBuf buf;
    sBuf_init(&buf);

    int param_num = 0;
    int param_max = get_element_number_from_Array(params->mObjectValue);

    while(*p) {
        if(*p == '%') {
            p++;

            BOOL no_conversion = FALSE;

            char format2[128+1];
            char* p2 = format2;

            *p2++ = '%';

            /// flag characters ///
            while(1) {
                if(*p == '#' || *p == '0' || *p == '-' || *p == ' ' || *p == '+' || *p == '\'') {
                    *p2++ = *p++;

                    if(p2 - format2 >= 128) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                        MFREE(buf.mBuf);
                        MFREE(format_string);
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            /// field width ///
            while(1) {
                if(isdigit(*p)) {
                    *p2++ = *p++;

                    if(p2 - format2 >= 128) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                        MFREE(buf.mBuf);
                        MFREE(format_string);
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            /// precision ///
            if(*p == '.') {
                *p2++ = *p++;

                if(p2 - format2 >= 128) {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }

                while(1) {
                    if(isdigit(*p) || *p == '*' || *p == '$') {
                        *p2++ = *p++;

                        if(p2 - format2 >= 128) {
                            entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                            MFREE(buf.mBuf);
                            MFREE(format_string);
                            return FALSE;
                        }
                    }
                    else {
                        break;
                    }
                }
            }

            /// length modifiers ///
            while(1) {
                if((*p == 'h' && *(p+1) == 'h') || (*p == 'l' && *(p+1) == 'l')) {
                    *p2++ = *p++;
                    *p2++ = *p++;

                    if(p2 - format2 >= 128) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                        MFREE(buf.mBuf);
                        MFREE(format_string);
                        return FALSE;
                    }
                }
                else if(*p == 'h' || *p == 'l' || *p == 'L' || *p == 'j' || *p == 'z' || *p == 't') 
                {
                    *p2++ = *p++;

                    if(p2 - format2 >= 128) {
                        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                        MFREE(buf.mBuf);
                        MFREE(format_string);
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            /// convertion specifier ///
            if(*p == 'd' || *p == 'i' || *p == 'o' || *p == 'u' || *p == 'x' || *p == 'X' || *p == 'e' || *p == 'E'|| *p == 'f' || *p == 'F' || *p == 'g' || *p == 'G' || *p == 'a' || *p == 'A' || *p == 'c' || *p == 's' || *p == 'p' || *p == 'n' || *p == 'm') 
            {
                *p2++ = *p++;

                if(p2 - format2 >= 128) {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }
            }
            else if(*p == '%') {
                *p2++ = *p++;

                no_conversion = TRUE;

                if(p2 - format2 >= 128) {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }
            }
            else {
                entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                MFREE(buf.mBuf);
                MFREE(format_string);
                return FALSE;
            }

            *p2++ = 0;

            if(p2 - format2 >= 128) {
                entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                MFREE(buf.mBuf);
                MFREE(format_string);
                return FALSE;
            }

            if(no_conversion) {
                sBuf_append_char(&buf, '%');
            }
            else if(param_num < param_max) {
                char* str = NULL;

                CLObject param = get_element_from_Array(params->mObjectValue, param_num)->mObjectValue;
                sCLClass* klass = get_class_from_object(param);

                if(is_this_class_with_class_name(klass, "Byte")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Byte(param));
                }
                else if(is_this_class_with_class_name(klass, "UByte")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_UByte(param));
                }
                else if(is_this_class_with_class_name(klass, "Short")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Short(param));
                }
                else if(is_this_class_with_class_name(klass, "UShort")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_UShort(param));
                }
                else if(is_this_class_with_class_name(klass, "Integer")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Integer(param));
                }
                else if(is_this_class_with_class_name(klass, "UInteger")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_UInteger(param));
                }
                else if(is_this_class_with_class_name(klass, "Long")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Long(param));
                }
                else if(is_this_class_with_class_name(klass, "ULong")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_ULong(param));
                }
                else if(is_this_class_with_class_name(klass, "Char")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Char(param));
                }
                else if(is_this_class_with_class_name(klass, "Float")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Float(param));
                }
                else if(is_this_class_with_class_name(klass, "Double")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Double(param));
                }
                else if(is_this_class_with_class_name(klass, "Bool")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Bool(param));
                }
                else if(is_this_class_with_class_name(klass, "Pointer")) {
                    (void)asprintf(ALLOC &str, format2, get_value_from_Pointer(param));
                }
                else if(is_this_class_with_class_name(klass, "String")) {
                    char* str2 = ALLOC string_object_to_char_array(param);
                    (void)asprintf(ALLOC &str, format2, str2);
                    MFREE(str2);
                }
                else if(is_this_class_with_class_name(klass, "Buffer")) {
                    sCLObject* object_data = CLOBJECT(param);
                    char* str2 = object_data->mFields[0].mPointerValue;
                    (void)asprintf(ALLOC &str, format2, str2);
                }
                else {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }

                sBuf_append_str(&buf, str);

                free(str);

                param_num++;
            }
            else {
                entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid format string");
                MFREE(buf.mBuf);
                MFREE(format_string);
                return FALSE;
            }
        }
        else {
            sBuf_append_char(&buf, *p);
            p++;
        }
    }

    CLObject result = create_string_object(buf.mBuf);

    MFREE(format_string);
    MFREE(buf.mBuf);

    (*stack_ptr)->mObjectValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_mbstowcs(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* dest = lvar;
    CLVALUE* src = lvar+1;
    CLVALUE* size = lvar+2;

    /// clover variable to c variable ///
    char* src_value = src->mPointerValue;
    size_t size_value = size->mULongValue;
    wchar_t* wcs = MCALLOC(1, sizeof(wchar_t)*(size_value+1));
    CLVALUE* dest_value = (CLVALUE*)dest->mPointerValue;

    char* src_value2 = MCALLOC(1, size_value+1);

    memcpy(src_value2, src_value, size_value);
    src_value2[size_value] = '\0';

    /// go ///
    int size_wcs = mbstowcs(wcs, src_value2, size_value+16);

    MFREE(src_value2);

    if(size_wcs < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid multi byte string");
        MFREE(wcs);
        return FALSE;
    }

    /// make result ///
    sCLClass* klass = get_class("char");

    MASSERT(klass != NULL);

    CLObject object = create_array_object(klass, size_wcs+1);
    sCLObject* object_data = CLOBJECT(object);

    int i;
    for(i=0; i<size_wcs; i++) {
        object_data->mFields[i].mCharValue = wcs[i];
    }
    object_data->mFields[i].mCharValue = '\0';

    dest_value->mObjectValue = object;

    MFREE(wcs);

    (*stack_ptr)->mIntValue = size_wcs;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_wcstombs(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* dest = lvar;
    CLVALUE* src = lvar+1;

    if(src->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// clover variable to c variable ///
    CLVALUE* dest_value = (CLVALUE*)dest->mPointerValue;
    CLObject src_value = src->mObjectValue;

    sCLObject* object_data = CLOBJECT(src_value);
    int len = object_data->mArrayNum;

    wchar_t* wcs = MCALLOC(1, sizeof(wchar_t)*(len+1));
    size_t size = sizeof(char)*MB_LEN_MAX*len;
    char* mbs = MCALLOC(1, size+MB_LEN_MAX);

    int i;
    for(i=0; i<len; i++) {
        wcs[i] = object_data->mFields[i].mCharValue;
    }
    BOOL null_terminated = FALSE;
    if(len > 0 && wcs[len-1] == '\0') {
        null_terminated = TRUE;
    }

    /// go ///
    int num = wcstombs(mbs, wcs, size);

    if(num < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "wcstombs returns -1");
        MFREE(wcs);
        MFREE(mbs);
        return FALSE;
    }

    /// make result ///
    sCLClass* klass = get_class("byte");

    MASSERT(klass != NULL);

    CLObject object;
    if(null_terminated) {
        object = create_array_object(klass, num+1);
        sCLObject* object_data2 = CLOBJECT(object);

        for(i=0; i<num; i++) {
            object_data2->mFields[i].mByteValue = mbs[i];
        }
        object_data2->mFields[i].mByteValue = '\0';
    }
    else {
        object = create_array_object(klass, num);
        sCLObject* object_data2 = CLOBJECT(object);

        for(i=0; i<num; i++) {
            object_data2->mFields[i].mByteValue = mbs[i];
        }
    }

    dest_value->mObjectValue = object;

    MFREE(wcs);
    MFREE(mbs);

    (*stack_ptr)->mIntValue = num;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_atoi(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;

    char* str_value = ALLOC string_object_to_char_array(str_object);

    /// go ///
    int result = atoi(str_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_atof(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;

    char* str_value = ALLOC string_object_to_char_array(str_object);

    /// go ///
    float result = atof(str_value);

    (*stack_ptr)->mFloatValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_strtod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;

    char* str_value = ALLOC string_object_to_char_array(str_object);

    /// go ///
    char* endptr = NULL;
    double result = strtod(str_value, &endptr);

    if(endptr == str_value) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "strtod(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mDoubleValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_strcmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    CLVALUE* str2 = (lvar+1);

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(str2->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;
    char* str_value = ALLOC string_object_to_char_array(str_object);

    CLObject str_object2 = str2->mObjectValue;
    char* str_value2 = ALLOC string_object_to_char_array(str_object2);

    /// go ///
    int result = strcmp(str_value, str_value2);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(str_value);
    MFREE(str_value2);

    return TRUE;
}

BOOL System_strcasecmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    CLVALUE* str2 = (lvar+1);

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(str2->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;
    char* str_value = ALLOC string_object_to_char_array(str_object);

    CLObject str_object2 = str2->mObjectValue;
    char* str_value2 = ALLOC string_object_to_char_array(str_object2);

    /// go ///
    int result = strcasecmp(str_value, str_value2);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(str_value);
    MFREE(str_value2);

    return TRUE;
}

BOOL System_strtol(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    CLVALUE* base = (lvar+1);

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;

    char* str_value = ALLOC string_object_to_char_array(str_object);

    int base_value = base->mIntValue;

    /// go ///
    errno = 0;
    clint64 result = strtol(str_value, NULL, base_value);

    if(errno != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "strtol(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mLongValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_strtoul(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    CLVALUE* base = (lvar+1);

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;

    char* str_value = ALLOC string_object_to_char_array(str_object);

    int base_value = base->mIntValue;

    /// go ///
    errno = 0;
    unsigned clint64 result = strtoul(str_value, NULL, base_value);

    if(errno != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "strtoul(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mULongValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_srand(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* value = lvar;

    /// Clover to c value ///
    unsigned int value_value = value->mUIntValue;

    /// go ///
    srand(value_value);

    return TRUE;
}

BOOL System_rand(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = rand();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_time(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    unsigned clint64 result = time(NULL);

    if((time_t)result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "time(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mULongValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_open(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* file_name = lvar;
    CLVALUE* flags = (lvar+1);
    CLVALUE* mode = (lvar+2);

    /// Clover to c value ///
    if(file_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* file_name_value = ALLOC string_object_to_char_array(file_name->mObjectValue);

    int flags_value = flags->mIntValue;

    mode_t mode_value = mode->mIntValue;

    /// go ///
    int result = open(file_name_value, flags_value, mode_value);

    if(result < 0) {
        MFREE(file_name_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "open(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(file_name_value);

    return TRUE;
}

BOOL System_close(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;

    /// Clover to c value ///
    int fd_value = fd->mIntValue;

    /// go ///
    int result = close(fd_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "close(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_initialize_string_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[0].mValue.mIntValue = MB_LEN_MAX;

#define LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM 1

    return TRUE;
}

BOOL System_initialize_file_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+0].mValue.mIntValue = S_IFMT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+1].mValue.mIntValue = S_IFDIR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+2].mValue.mIntValue = S_IFCHR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+3].mValue.mIntValue = S_IFBLK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+4].mValue.mIntValue = S_IFREG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+5].mValue.mIntValue = S_IFIFO;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+6].mValue.mIntValue = S_IFLNK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+7].mValue.mIntValue = S_IFSOCK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+8].mValue.mIntValue = S_ISUID;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+9].mValue.mIntValue = S_ISGID;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+10].mValue.mIntValue = S_ISVTX;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+11].mValue.mIntValue = S_IRUSR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+12].mValue.mIntValue = S_IWUSR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+13].mValue.mIntValue = S_IXUSR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+14].mValue.mIntValue = S_IRWXU;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+15].mValue.mIntValue = S_IRGRP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+16].mValue.mIntValue = S_IWGRP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+17].mValue.mIntValue = S_IXGRP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+18].mValue.mIntValue = S_IRWXG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+19].mValue.mIntValue = S_IROTH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+20].mValue.mIntValue = S_IWOTH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+21].mValue.mIntValue = S_IXOTH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+22].mValue.mIntValue = S_IRWXO;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+23].mValue.mIntValue = R_OK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+24].mValue.mIntValue = W_OK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+25].mValue.mIntValue = X_OK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+26].mValue.mIntValue = F_OK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+27].mValue.mIntValue = O_APPEND;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+28].mValue.mIntValue = O_ASYNC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+29].mValue.mIntValue = O_RDONLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+30].mValue.mIntValue = O_WRONLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+31].mValue.mIntValue = O_RDWR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+32].mValue.mIntValue = O_CREAT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+33].mValue.mIntValue = O_DIRECTORY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+34].mValue.mIntValue = O_EXCL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+35].mValue.mIntValue = O_NOCTTY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+36].mValue.mIntValue = O_NOFOLLOW;
#ifdef O_TMPFILE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+37].mValue.mIntValue = O_TMPFILE;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+38].mValue.mIntValue = O_TRUNC;
#ifdef O_TTY_INIT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+39].mValue.mIntValue = O_TTY_INIT;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+40].mValue.mIntValue = O_CLOEXEC;
#ifdef O_DIRECT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+41].mValue.mIntValue = O_DIRECT;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+42].mValue.mIntValue = O_DSYNC;
#ifdef O_LARGEFILE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+43].mValue.mIntValue = O_LARGEFILE;
#endif
#ifdef O_NOATIME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+44].mValue.mIntValue = O_NOATIME;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+45].mValue.mIntValue = O_NONBLOCK;
#ifdef O_PATH
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+46].mValue.mIntValue = O_PATH;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+47].mValue.mIntValue = O_SYNC;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+48].mValue.mIntValue = FNM_NOESCAPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+49].mValue.mIntValue = FNM_PATHNAME;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+50].mValue.mIntValue = FNM_PERIOD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+51].mValue.mIntValue = FNM_FILE_NAME;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+52].mValue.mIntValue = FNM_LEADING_DIR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+53].mValue.mIntValue = FNM_CASEFOLD;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+54].mValue.mIntValue = CLOCK_REALTIME;
#ifdef CLOCK_REALTIME_COARSE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+55].mValue.mIntValue = CLOCK_REALTIME_COARSE;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+56].mValue.mIntValue = CLOCK_MONOTONIC;
#ifdef CLOCK_MONOTONIC_COARSE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+57].mValue.mIntValue = CLOCK_MONOTONIC_COARSE;
#endif
#ifdef CLOCK_MONOTONIC_RAW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+58].mValue.mIntValue = CLOCK_MONOTONIC_RAW;
#endif
#ifdef CLOCK_BOOTTIME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+59].mValue.mIntValue = CLOCK_BOOTTIME;
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+60].mValue.mIntValue = CLOCK_PROCESS_CPUTIME_ID;
#endif
#ifdef CLOCK_THREAD_CPUTIME_ID
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+61].mValue.mIntValue = CLOCK_THREAD_CPUTIME_ID;
#endif

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+62].mValue.mIntValue = RTLD_LAZY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+63].mValue.mIntValue = RTLD_NOW;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+64].mValue.mIntValue = RTLD_GLOBAL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+65].mValue.mIntValue = RTLD_LOCAL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+66].mValue.mIntValue = RTLD_NODELETE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+67].mValue.mIntValue = RTLD_NOLOAD;
#ifdef RTLD_DEEPBIND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+68].mValue.mIntValue = RTLD_DEEPBIND;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+69].mValue.mPointerValue = RTLD_DEFAULT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+70].mValue.mPointerValue = RTLD_NEXT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+71].mValue.mIntValue = EOF;

#define LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM (LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+72)

    return TRUE;
}

BOOL System_read(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* buf = lvar+1;
    CLVALUE* size = lvar + 2;

    if(buf->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    int fd_value = fd->mIntValue;

    void* buf_value = get_pointer_from_buffer_object(buf->mObjectValue);
    size_t size_value = (size_t)size->mULongValue;

    int buffer_size = get_size_from_buffer_object(buf->mObjectValue);

    /// check size ///
    if(size_value > buffer_size) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Buffer size is smaller than the size value of argument");
        return FALSE;
    }

    /// go ///
    ssize_t result = read(fd_value, buf_value, size_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "read(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    sCLObject* obj_data = CLOBJECT(buf->mObjectValue);
    obj_data->mFields[1].mULongValue = result;                // len

    (*stack_ptr)->mULongValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_write(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* buf = lvar+1;
    CLVALUE* size = lvar + 2;

    if(buf->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    int fd_value = fd->mIntValue;

    void* buf_value = get_pointer_from_buffer_object(buf->mObjectValue);
    size_t size_value = (size_t)size->mULongValue;

    int buffer_size = get_size_from_buffer_object(buf->mObjectValue);

    /// check size ///
    if(size_value > buffer_size) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Buffer size is smaller than the size value of argument");
        return FALSE;
    }

    /// go ///
    ssize_t result = write(fd_value, buf_value, size_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "write(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mULongValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_localtime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* time = lvar;
    CLVALUE* tm_sec = lvar + 1;
    CLVALUE* tm_min = lvar + 2;
    CLVALUE* tm_hour = lvar + 3;
    CLVALUE* tm_mday = lvar + 4;
    CLVALUE* tm_mon = lvar + 5;
    CLVALUE* tm_year = lvar + 6;
    CLVALUE* tm_wday = lvar + 7;
    CLVALUE* tm_yday = lvar + 8;
    CLVALUE* tm_isdst = lvar + 9;

    /// Clover to c value ///
    time_t time_value = (time_t)time->mULongValue;

    /// go ///
    struct tm* tm_struct = localtime(&time_value);

    if(tm_struct == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "localtime(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    *(int*)tm_sec->mPointerValue = tm_struct->tm_sec;
    *(int*)tm_min->mPointerValue = tm_struct->tm_min;
    *(int*)tm_hour->mPointerValue = tm_struct->tm_hour;
    *(int*)tm_mday->mPointerValue = tm_struct->tm_mday;
    *(int*)tm_mon->mPointerValue = tm_struct->tm_mon;
    *(int*)tm_year->mPointerValue = tm_struct->tm_year;
    *(int*)tm_wday->mPointerValue = tm_struct->tm_wday;
    *(int*)tm_yday->mPointerValue = tm_struct->tm_yday;
    *(BOOL*)tm_isdst->mPointerValue = tm_struct->tm_isdst;

    return TRUE;
}

BOOL System_mktime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* time = lvar;

    if(time->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    sCLObject* object_data = CLOBJECT(time->mObjectValue);

    struct tm tm;

    tm.tm_sec = object_data->mFields[0].mIntValue;
    tm.tm_min = object_data->mFields[1].mIntValue;
    tm.tm_hour = object_data->mFields[2].mIntValue;
    tm.tm_mday = object_data->mFields[3].mIntValue;
    tm.tm_mon = object_data->mFields[4].mIntValue;
    tm.tm_year = object_data->mFields[5].mIntValue;
    tm.tm_wday = object_data->mFields[6].mIntValue;
    tm.tm_yday = object_data->mFields[7].mIntValue;
    tm.tm_isdst = object_data->mFields[8].mBoolValue;

    /// go ///
    time_t result = mktime(&tm);

    if(result == -1) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "mktime(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mULongValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_stat(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* stat_ = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(stat_->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    struct stat stat_struct;
    int result = stat(path_value, &stat_struct);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "stat(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }
    sCLObject* object_data = CLOBJECT(stat_->mObjectValue);

    object_data->mFields[0].mULongValue = stat_struct.st_dev;
    object_data->mFields[1].mIntValue = stat_struct.st_mode;
    object_data->mFields[2].mIntValue = stat_struct.st_uid;
    object_data->mFields[3].mIntValue = stat_struct.st_gid;
    object_data->mFields[4].mULongValue = stat_struct.st_rdev;
    object_data->mFields[5].mULongValue = stat_struct.st_size;
    object_data->mFields[6].mULongValue = stat_struct.st_atime;
    object_data->mFields[7].mULongValue = stat_struct.st_mtime;
    object_data->mFields[8].mULongValue = stat_struct.st_ctime;

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_lstat(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* stat_ = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(stat_->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    struct stat stat_struct;
    int result = lstat(path_value, &stat_struct);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "lstat(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }
    sCLObject* object_data = CLOBJECT(stat_->mObjectValue);

    object_data->mFields[0].mULongValue = stat_struct.st_dev;
    object_data->mFields[1].mIntValue = stat_struct.st_mode;
    object_data->mFields[2].mIntValue = stat_struct.st_uid;
    object_data->mFields[3].mIntValue = stat_struct.st_gid;
    object_data->mFields[4].mULongValue = stat_struct.st_rdev;
    object_data->mFields[5].mULongValue = stat_struct.st_size;
    object_data->mFields[6].mULongValue = stat_struct.st_atime;
    object_data->mFields[7].mULongValue = stat_struct.st_mtime;
    object_data->mFields[8].mULongValue = stat_struct.st_ctime;

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_realpath(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    char result_path[PATH_MAX];

    char* result = realpath(path_value, result_path);

    if(result == NULL) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "realpath(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    /// result ///
    CLObject result_object = create_string_object(result_path);

    (*stack_ptr)->mObjectValue = result_object;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_dirname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    char* result_path = dirname(path_value);

    /// result ///
    CLObject result_object = create_string_object(result_path);

    (*stack_ptr)->mObjectValue = result_object;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_basename(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    char* result_path = basename(path_value);

    /// result ///
    CLObject result_object = create_string_object(result_path);

    (*stack_ptr)->mObjectValue = result_object;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_opendir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    DIR* result = opendir(path_value);

    if(result == NULL) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "opendir(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    /// result ///
    (*stack_ptr)->mPointerValue = (char*)result;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_readdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* dir = lvar;

    /// Clover to c value ///
    DIR* dir_value = (DIR*)dir->mPointerValue;

    /// go ///
    errno = 0;
    struct dirent* entry = readdir(dir_value);

    if(errno != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "readdir(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    /// result ///
    if(entry == NULL) {
        (*stack_ptr)->mObjectValue = 0;
        (*stack_ptr)++;
    }
    else {
        (*stack_ptr)->mObjectValue = create_string_object(entry->d_name);
        (*stack_ptr)++;
    }

    return TRUE;
}

BOOL System_closedir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* dir = lvar;

    /// Clover to c value ///
    DIR* dir_value = (DIR*)dir->mPointerValue;

    /// go ///
    int result = closedir(dir_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "closedir(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_initialize_command_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+0].mValue.mIntValue = WNOHANG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+1].mValue.mIntValue = WUNTRACED;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+2].mValue.mIntValue = WCONTINUED;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+3].mValue.mIntValue = SIGHUP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+4].mValue.mIntValue = SIGINT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+5].mValue.mIntValue = SIGQUIT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+6].mValue.mIntValue = SIGILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+7].mValue.mIntValue = SIGABRT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+8].mValue.mIntValue = SIGFPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+9].mValue.mIntValue = SIGKILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+10].mValue.mIntValue = SIGSEGV;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+11].mValue.mIntValue = SIGPIPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+12].mValue.mIntValue = SIGALRM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+13].mValue.mIntValue = SIGTERM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+14].mValue.mIntValue = SIGUSR1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+15].mValue.mIntValue = SIGUSR2;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+16].mValue.mIntValue = SIGCHLD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+17].mValue.mIntValue = SIGCONT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+18].mValue.mIntValue = SIGSTOP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+19].mValue.mIntValue = SIGTSTP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+20].mValue.mIntValue = SIGTTIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+21].mValue.mIntValue = SIGTTOU;

    // c_iflag bits
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+22].mValue.mIntValue = IGNBRK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+23].mValue.mIntValue = BRKINT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+24].mValue.mIntValue = IGNPAR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+25].mValue.mIntValue = PARMRK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+26].mValue.mIntValue = INPCK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+27].mValue.mIntValue = ISTRIP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+28].mValue.mIntValue = INLCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+29].mValue.mIntValue = IGNCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+30].mValue.mIntValue = ICRNL;
#ifdef IUCLC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+31].mValue.mIntValue = IUCLC;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+32].mValue.mIntValue = IXON;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+33].mValue.mIntValue = IXANY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+34].mValue.mIntValue = IXOFF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+35].mValue.mIntValue = IMAXBEL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+36].mValue.mIntValue = IUTF8;

    // c_oflag bits
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+37].mValue.mIntValue = OPOST;
#ifdef OLCUC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+38].mValue.mIntValue = OLCUC;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+39].mValue.mIntValue = ONLCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+40].mValue.mIntValue = OCRNL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+41].mValue.mIntValue = ONOCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+42].mValue.mIntValue = ONLRET;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+43].mValue.mIntValue = OFILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+44].mValue.mIntValue = OFDEL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+45].mValue.mIntValue = NLDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+46].mValue.mIntValue = NL0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+47].mValue.mIntValue = NL1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+48].mValue.mIntValue = CRDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+49].mValue.mIntValue = CR0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+50].mValue.mIntValue = CR1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+51].mValue.mIntValue = CR2;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+52].mValue.mIntValue = CR3;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+53].mValue.mIntValue = TABDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+54].mValue.mIntValue = TAB0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+55].mValue.mIntValue = TAB1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+56].mValue.mIntValue = TAB2;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+57].mValue.mIntValue = TAB3;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+58].mValue.mIntValue = BSDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+59].mValue.mIntValue = BS0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+60].mValue.mIntValue = BS1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+61].mValue.mIntValue = FFDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+62].mValue.mIntValue = FF0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+63].mValue.mIntValue = FF1;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+64].mValue.mIntValue = VTDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+65].mValue.mIntValue = VT0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+66].mValue.mIntValue = VT1;

#ifdef XTABS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+67].mValue.mIntValue = XTABS;
#endif

    // c_cflag bit meaning
#ifdef CBAUD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+68].mValue.mIntValue = CBAUD;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+69].mValue.mIntValue = B0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+70].mValue.mIntValue = B50;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+71].mValue.mIntValue = B75;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+72].mValue.mIntValue = B110;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+73].mValue.mIntValue = B134;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+74].mValue.mIntValue = B150;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+75].mValue.mIntValue = B200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+76].mValue.mIntValue = B300;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+77].mValue.mIntValue = B600;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+78].mValue.mIntValue = B1200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+79].mValue.mIntValue = B1800;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+80].mValue.mIntValue = B2400;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+81].mValue.mIntValue = B4800;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+82].mValue.mIntValue = B9600;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+83].mValue.mIntValue = B19200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+84].mValue.mIntValue = B38400;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+85].mValue.mIntValue = EXTA;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+86].mValue.mIntValue = EXTB;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+87].mValue.mIntValue = CSIZE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+88].mValue.mIntValue = CS5;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+89].mValue.mIntValue = CS6;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+90].mValue.mIntValue = CS7;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+91].mValue.mIntValue = CS8;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+92].mValue.mIntValue = CSTOPB;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+93].mValue.mIntValue = CREAD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+94].mValue.mIntValue = PARENB;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+95].mValue.mIntValue = PARODD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+96].mValue.mIntValue = HUPCL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+97].mValue.mIntValue = CLOCAL;
#ifdef CBAUDEX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+98].mValue.mIntValue = CBAUDEX;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+99].mValue.mIntValue = B57600;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+100].mValue.mIntValue = B115200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+101].mValue.mIntValue = B230400;
#ifdef B460800
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+102].mValue.mIntValue = B460800;
#endif
#ifdef B500000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+103].mValue.mIntValue = B500000;
#endif
#ifdef B576000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+104].mValue.mIntValue = B576000;
#endif
#ifdef B921600
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+105].mValue.mIntValue = B921600;
#endif
#ifdef B1000000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+106].mValue.mIntValue = B1000000;
#endif
#ifdef B1152000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+107].mValue.mIntValue = B1152000;
#endif
#ifdef B1500000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+108].mValue.mIntValue = B1500000;
#endif
#ifdef B2000000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+109].mValue.mIntValue = B2000000;
#endif
#ifdef B2500000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+110].mValue.mIntValue = B2500000;
#endif
#ifdef B3000000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+111].mValue.mIntValue = B3000000;
#endif
#ifdef B3500000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+112].mValue.mIntValue = B3500000;
#endif
#ifdef B4000000
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+113].mValue.mIntValue = B4000000;
#endif
#ifdef CIBAUD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+114].mValue.mIntValue = CIBAUD;
#endif
#ifdef CMSPAR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+115].mValue.mIntValue = CMSPAR;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+116].mValue.mIntValue = CRTSCTS;

    // c_lflag bits
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+117].mValue.mIntValue = ISIG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+118].mValue.mIntValue = ICANON;
#ifdef XCASE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+119].mValue.mIntValue = XCASE;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+120].mValue.mIntValue = ECHO;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+121].mValue.mIntValue = ECHOE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+122].mValue.mIntValue = ECHOK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+123].mValue.mIntValue = ECHONL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+124].mValue.mIntValue = NOFLSH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+125].mValue.mIntValue = TOSTOP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+126].mValue.mIntValue = ECHOCTL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+127].mValue.mIntValue = ECHOPRT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+128].mValue.mIntValue = ECHOKE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+129].mValue.mIntValue = FLUSHO;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+130].mValue.mIntValue = PENDIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+131].mValue.mIntValue = IEXTEN;
#ifdef EXTPROC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+132].mValue.mIntValue = EXTPROC;
#endif

    // tcflow() and TCXONC use these 
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+133].mValue.mIntValue = TCOOFF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+134].mValue.mIntValue = TCOON;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+135].mValue.mIntValue = TCIOFF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+136].mValue.mIntValue = TCION;

    // tcflush() and TCFLSH use these
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+137].mValue.mIntValue = TCIFLUSH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+138].mValue.mIntValue = TCOFLUSH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+139].mValue.mIntValue = TCIOFLUSH;

    // tcsetattr uses these
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+140].mValue.mIntValue = TCSANOW;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+141].mValue.mIntValue = TCSADRAIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+142].mValue.mIntValue = TCSAFLUSH;

    // c_cc characters
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+143].mValue.mIntValue = VINTR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+144].mValue.mIntValue = VQUIT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+145].mValue.mIntValue = VERASE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+146].mValue.mIntValue = VKILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+147].mValue.mIntValue = VEOF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+148].mValue.mIntValue = VTIME;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+149].mValue.mIntValue = VMIN;
#ifdef VSWTC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+150].mValue.mIntValue = VSWTC;
#endif
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+151].mValue.mIntValue = VSTART;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+152].mValue.mIntValue = VSTOP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+153].mValue.mIntValue = VSUSP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+154].mValue.mIntValue = VEOL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+155].mValue.mIntValue = VREPRINT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+156].mValue.mIntValue = VDISCARD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+157].mValue.mIntValue = VWERASE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+158].mValue.mIntValue = VLNEXT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+159].mValue.mIntValue = VEOL2;

#define LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM (LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM+160)

    return TRUE;
}

BOOL System_pipe(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* read_fd = lvar;
    CLVALUE* write_fd = lvar+1;

    /// Clover to c value ///
    int* read_fd_value = (int*)read_fd->mPointerValue;
    int* write_fd_value = (int*)write_fd->mPointerValue;

    /// go ///
    int pipefd[2];
    int result = pipe(pipefd);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pipe(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    *read_fd_value = pipefd[0];
    *write_fd_value = pipefd[1];

    return TRUE;
}

BOOL System_fork(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* block_ = lvar;

    if(block_->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    CLObject block_value = block_->mObjectValue;

    /// go ///
    pid_t result = fork();

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fork(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    /// child process
    if(result == 0) {
        vm_mutex_on();
        new_vm_mutex();         // avoid to dead lock
        vm_mutex_off();

        int num_params = 0;

        if(!invoke_block(block_value, info->current_stack, info->current_var_num, num_params, stack_ptr, info, FALSE)) {
            return FALSE;
        }

        exit(0);
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_dup2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd1 = lvar;
    CLVALUE* fd2 = lvar+1;

    /// Clover to c value ///
    int fd1_value = fd1->mIntValue;
    int fd2_value = fd2->mIntValue;

    /// go ///
    int result = dup2(fd1_value, fd2_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "dup2(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_execvp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* method_name = lvar;
    CLVALUE* params = lvar+1;

    if(method_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(params->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* method_name_value = ALLOC string_object_to_char_array(method_name->mObjectValue);
    int num_elements = 0;
    CLObject* params_objects = ALLOC list_to_array(params->mObjectValue, &num_elements);
    char** params_value = ALLOC MCALLOC(1, sizeof(char*)*(num_elements+2));
    int i;
    params_value[0] = method_name_value;
    for(i=0; i<num_elements; i++) {
        CLObject string_object = params_objects[i];
        params_value[i+1] = ALLOC string_object_to_char_array(string_object);
    }
    params_value[i+1] = NULL;
    MFREE(params_objects);

    /// go ///
    int result = execvp(method_name_value, params_value);

    if(result < 0) {
        int i;
        for(i=0; i<num_elements+1; i++) {
            MFREE(params_value[i]);
        }
        MFREE(params_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "execvp(2) is faield. The error is %s. The errnor is %d.", strerror(errno), errno);
        return FALSE;
    }

    for(i=0; i<num_elements+1; i++) {
        MFREE(params_value[i]);
    }
    MFREE(params_value);

    return TRUE;
}

BOOL System_execv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* method_name = lvar;
    CLVALUE* params = lvar+1;

    if(method_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(params->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* method_name_value = ALLOC string_object_to_char_array(method_name->mObjectValue);
    int num_elements = 0;
    CLObject* params_objects = ALLOC list_to_array(params->mObjectValue, &num_elements);
    char** params_value = ALLOC MCALLOC(1, sizeof(char*)*(num_elements+2));
    int i;
    params_value[0] = method_name_value;
    for(i=0; i<num_elements; i++) {
        CLObject string_object = params_objects[i];
        params_value[i+1] = ALLOC string_object_to_char_array(string_object);
    }
    params_value[i+1] = NULL;
    MFREE(params_objects);

    /// go ///
    int result = execv(method_name_value, params_value);

    if(result < 0) {
        int i;
        for(i=0; i<num_elements+1; i++) {
            MFREE(params_value[i]);
        }
        MFREE(params_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "execv(2) is faield. The error is %s. The errnor is %d.", strerror(errno), errno);
        return FALSE;
    }

    for(i=0; i<num_elements+1; i++) {
        MFREE(params_value[i]);
    }
    MFREE(params_value);

    return TRUE;
}

BOOL System_waitpid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pid = lvar;
    CLVALUE* status = lvar + 1;
    CLVALUE* option = lvar + 2;

    /// Clover to C value ///
    pid_t pid_value = pid->mIntValue;
    int* status_value = (int*)status->mPointerValue;
    int option_value = option->mIntValue;

    pid_t result = waitpid(pid_value, status_value, option_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "waitpid(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WIFEXITED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    BOOL result = WIFEXITED(status_value);

    (*stack_ptr)->mBoolValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WEXITSTATUS(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    int result = WEXITSTATUS(status_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WIFSIGNALED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    BOOL result = WIFSIGNALED(status_value);

    (*stack_ptr)->mBoolValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WTERMSIG(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    int result = WTERMSIG(status_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WCOREDUMP(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    int result = WCOREDUMP(status_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WIFSTOPPED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    BOOL result = WIFSTOPPED(status_value);

    (*stack_ptr)->mBoolValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WSTOPSIG(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    int result = WSTOPSIG(status_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_WIFCONTINUED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* status = lvar;

    /// Clover to C value ///
    int status_value = status->mIntValue;

    BOOL result = WIFCONTINUED(status_value);

    (*stack_ptr)->mBoolValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getpid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// Clover to C value ///
    pid_t result = getpid();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_setpgid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pid = lvar;
    CLVALUE* pgid = lvar + 1;

    /// Clover to C value ///
    pid_t pid_value = pid->mIntValue;
    pid_t pgid_value = pgid->mIntValue;

    int result = setpgid(pid_value, pgid_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "setpgid(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_kill(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pid = lvar;
    CLVALUE* sig = lvar + 1;

    /// Clover to C value ///
    int pid_value = pid->mIntValue;
    int sig_value = sig->mIntValue;

    /// go ///
    int result = kill(pid_value, sig_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "kill(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_tcsetpgrp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* pid = lvar + 1;

    /// Clover to C value ///
    int fd_value = fd->mIntValue;
    pid_t pid_value = pid->mIntValue;

    int result = tcsetpgrp(fd_value, pid_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcsetpgrp(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_tcgetattr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* terminfo = lvar + 1;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C value ///
    int fd_value = fd->mIntValue;
    CLObject terminfo_object = terminfo->mObjectValue;

    /// go ///
    struct termios terminfo_value;
    int result = tcgetattr(fd_value, &terminfo_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcgetattr(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    /// C to Clover object ///
    c_termios_to_clover_termios(&terminfo_value, terminfo_object);

    return TRUE;
}

BOOL System_tcsetattr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* optional_actions = lvar + 1;
    CLVALUE* terminfo = lvar + 2;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C value ///
    int fd_value = fd->mIntValue;
    int optional_actions_value = optional_actions->mIntValue;

    CLObject terminfo_object = terminfo->mObjectValue;
    struct termios terminfo_value;
    clover_termios_to_c_termios(terminfo_object, &terminfo_value);

    /// go ///
    int result = tcsetattr(fd_value, optional_actions_value, &terminfo_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcsetattr(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_tcsendbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* duration = lvar + 1;

    /// Clover to C value ///
    int fd_value = fd->mIntValue;
    int duration_value = duration->mIntValue;

    /// go ///
    int result = tcsendbreak(fd_value, duration_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcsendbreak(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_tcdrain(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;

    /// Clover to C value ///
    int fd_value = fd->mIntValue;

    /// go ///
    int result = tcdrain(fd_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcdrain(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_tcflush(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* queue_selector = lvar + 1;

    /// Clover to C value ///
    int fd_value = fd->mIntValue;
    int queue_selector_value = queue_selector->mIntValue;

    /// go ///
    int result = tcflush(fd_value, queue_selector_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcflush(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_tcflow(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* action = lvar + 1;

    /// Clover to C value ///
    int fd_value = fd->mIntValue;
    int action_value = action->mIntValue;

    /// go ///
    int result = tcflow(fd_value, action_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcflow(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_cfmakeraw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* terminfo = lvar;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C value ///
    CLObject terminfo_object = terminfo->mObjectValue;
    struct termios terminfo_value;
    clover_termios_to_c_termios(terminfo_object, &terminfo_value);

    /// go ///
    cfmakeraw(&terminfo_value);

    return TRUE;
}

BOOL System_cfgetispeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* terminfo = lvar;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }


    /// Clover to C value ///
    CLObject terminfo_object = terminfo->mObjectValue;
    struct termios terminfo_value;
    clover_termios_to_c_termios(terminfo_object, &terminfo_value);

    /// go ///
    int result = cfgetispeed(&terminfo_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_cfgetospeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* terminfo = lvar;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C value ///
    CLObject terminfo_object = terminfo->mObjectValue;
    struct termios terminfo_value;
    clover_termios_to_c_termios(terminfo_object, &terminfo_value);

    /// go ///
    int result = cfgetospeed(&terminfo_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_cfsetispeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* terminfo = lvar;
    CLVALUE* speed = lvar + 1;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C value ///
    CLObject terminfo_object = terminfo->mObjectValue;
    struct termios terminfo_value;
    clover_termios_to_c_termios(terminfo_object, &terminfo_value);

    speed_t speed_value = speed->mIntValue;

    /// go ///
    int result = cfsetispeed(&terminfo_value, speed_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "cfsetispeed(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_cfsetospeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* terminfo = lvar;
    CLVALUE* speed = lvar + 1;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C value ///
    CLObject terminfo_object = terminfo->mObjectValue;
    struct termios terminfo_value;
    clover_termios_to_c_termios(terminfo_object, &terminfo_value);

    speed_t speed_value = speed->mIntValue;

    /// go ///
    int result = cfsetospeed(&terminfo_value, speed_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "cfsetospeed(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_cfsetspeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* terminfo = lvar;
    CLVALUE* speed = lvar + 1;

    if(terminfo->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C value ///
    CLObject terminfo_object = terminfo->mObjectValue;
    struct termios terminfo_value;
    clover_termios_to_c_termios(terminfo_object, &terminfo_value);

    speed_t speed_value = speed->mIntValue;

    /// go ///
    int result = cfsetspeed(&terminfo_value, speed_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "cfsetspeed(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_chmod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* mode = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    mode_t mode_value = mode->mIntValue;

    /// go ///
    int result = chmod(path_value, mode_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "chmod(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_lchmod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* mode = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    mode_t mode_value = mode->mIntValue;

    /// go ///
    int result = lchmod(path_value, mode_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "lchmod(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_fchmod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* mode = lvar + 1;

    /// Clover to c value ///
    int fd_value = fd->mIntValue;
    mode_t mode_value = mode->mIntValue;

    /// go ///
    int result = fchmod(fd_value, mode_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fchmod(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_chown(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* owner = lvar + 1;
    CLVALUE* group = lvar + 2;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    uid_t owner_value = owner->mIntValue;
    gid_t group_value = group->mIntValue;

    /// go ///
    int result = chown(path_value, owner_value, group_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "chown(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_lchown(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* owner = lvar + 1;
    CLVALUE* group = lvar + 2;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    uid_t owner_value = owner->mIntValue;
    gid_t group_value = group->mIntValue;

    /// go ///
    int result = lchown(path_value, owner_value, group_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "lchown(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_fchown(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* owner = lvar + 1;
    CLVALUE* group = lvar + 2;

    /// Clover to c value ///
    int fd_value = fd->mIntValue;
    uid_t owner_value = owner->mIntValue;
    gid_t group_value = group->mIntValue;

    /// go ///
    int result = fchown(fd_value, owner_value, group_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fchown(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_unlink(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    int result = unlink(path_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "unlink(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_access(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* mode = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    int mode_value = mode->mIntValue;

    /// go ///
    int result = access(path_value, mode_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_utime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* actime = lvar + 1;
    CLVALUE* modtime = lvar + 2;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    time_t actime_value = actime->mULongValue;
    time_t modtime_value = modtime->mULongValue;

    struct utimbuf utimbuf_value;
    utimbuf_value.actime = actime_value;
    utimbuf_value.modtime = modtime_value;

    /// go ///
    int result = utime(path_value, &utimbuf_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "utime(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_fnmatch(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pattern = lvar;
    CLVALUE* path = lvar + 1;
    CLVALUE* flags = lvar + 2;

    if(pattern->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* pattern_value = ALLOC string_object_to_char_array(pattern->mObjectValue);
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    int flags_value = flags->mIntValue;

    /// go ///
    int result = fnmatch(pattern_value, path_value, flags_value);

    (*stack_ptr)->mBoolValue = result == 0;
    (*stack_ptr)++;

    MFREE(pattern_value);
    MFREE(path_value);

    return TRUE;
}

BOOL System_link(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* old_path = lvar;
    CLVALUE* new_path = lvar + 1;

    if(old_path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(new_path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* old_path_value = ALLOC string_object_to_char_array(old_path->mObjectValue);
    char* new_path_value = ALLOC string_object_to_char_array(new_path->mObjectValue);

    /// go ///
    int result = link(old_path_value, new_path_value);

    if(result < 0) {
        MFREE(old_path_value);
        MFREE(new_path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "link(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(old_path_value);
    MFREE(new_path_value);

    return TRUE;
}

BOOL System_symlink(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* old_path = lvar;
    CLVALUE* new_path = lvar + 1;

    if(old_path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(new_path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* old_path_value = ALLOC string_object_to_char_array(old_path->mObjectValue);
    char* new_path_value = ALLOC string_object_to_char_array(new_path->mObjectValue);

    /// go ///
    int result = symlink(old_path_value, new_path_value);

    if(result < 0) {
        MFREE(old_path_value);
        MFREE(new_path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "symlink(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(old_path_value);
    MFREE(new_path_value);

    return TRUE;
}

BOOL System_readlink(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    char result_path[PATH_MAX+1];
    int result = readlink(path_value, result_path, PATH_MAX);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "readlink(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    result_path[result] = '\0';

    (*stack_ptr)->mObjectValue = create_string_object(result_path);
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_rename(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* old_path = lvar;
    CLVALUE* new_path = lvar + 1;

    if(old_path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(new_path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* old_path_value = ALLOC string_object_to_char_array(old_path->mObjectValue);
    char* new_path_value = ALLOC string_object_to_char_array(new_path->mObjectValue);

    /// go ///
    int result = rename(old_path_value, new_path_value);

    if(result < 0) {
        MFREE(old_path_value);
        MFREE(new_path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "rename(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(old_path_value);
    MFREE(new_path_value);

    return TRUE;
}

BOOL System_truncate(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* length = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    off_t length_value = length->mULongValue;

    /// go ///
    int result = truncate(path_value, length_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "truncate(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_ftruncate(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* length = lvar + 1;

    /// Clover to c value ///
    int fd_value = fd->mIntValue;
    off_t length_value = length->mULongValue;

    /// go ///
    int result = ftruncate(fd_value, length_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "ftruncate(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_chdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    int result = chdir(path_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "chdir(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_fchdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;

    /// Clover to c value ///
    int fd_value = fd->mIntValue;

    /// go ///
    int result = fchdir(fd_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fchdir(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_rmdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);

    /// go ///
    int result = rmdir(path_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "rmdir(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_mkdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* mode = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    mode_t mode_value = mode->mIntValue;

    /// go ///
    int result = mkdir(path_value, mode_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "mkdir(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(path_value);

    return TRUE;
}

BOOL System_clock_getres(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* clk_id = lvar;
    CLVALUE* tp = lvar + 1;

    if(tp->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    clockid_t clk_id_value = clk_id->mIntValue;
    CLObject tp_value = tp->mObjectValue;

    /// go ///
    struct timespec timespec_struct;
    int result = clock_getres(clk_id_value, &timespec_struct);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "clock_getres(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }
    sCLObject* object_data = CLOBJECT(tp_value);

    object_data->mFields[0].mULongValue = timespec_struct.tv_sec;
    object_data->mFields[1].mLongValue = timespec_struct.tv_nsec;

    return TRUE;
}

BOOL System_clock_gettime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* clk_id = lvar;
    CLVALUE* tp = lvar + 1;

    if(tp->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    clockid_t clk_id_value = clk_id->mIntValue;
    CLObject tp_value = tp->mObjectValue;

    /// go ///
    struct timespec timespec_struct;
    int result = clock_gettime(clk_id_value, &timespec_struct);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "clock_getime(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }
    sCLObject* object_data = CLOBJECT(tp_value);

    object_data->mFields[0].mULongValue = timespec_struct.tv_sec;
    object_data->mFields[1].mLongValue = timespec_struct.tv_nsec;

    return TRUE;
}

BOOL System_clock_settime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* clk_id = lvar;
    CLVALUE* tp = lvar + 1;

    if(tp->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    clockid_t clk_id_value = clk_id->mIntValue;

    struct timespec timespec_struct;

    CLObject tp_value = tp->mObjectValue;
    sCLObject* object_data = CLOBJECT(tp_value);

    timespec_struct.tv_sec = object_data->mFields[0].mULongValue;
    timespec_struct.tv_nsec = object_data->mFields[1].mLongValue;

    /// go ///
    int result = clock_settime(clk_id_value, &timespec_struct);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "clock_settime(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* str_value = ALLOC string_object_to_char_array(str->mObjectValue);

    /// go ///
    int result = system(str_value);

    if(result < 0) {
        MFREE(str_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "system(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_getenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* name = lvar;

    if(name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* name_value = ALLOC string_object_to_char_array(name->mObjectValue);

    /// go ///
    char* result = getenv(name_value);

    if(result == NULL) {
        (*stack_ptr)->mIntValue = 0;
        (*stack_ptr)++;
    }
    else {
        (*stack_ptr)->mObjectValue = create_string_object(result);
        (*stack_ptr)++;
    }

    MFREE(name_value);

    return TRUE;
}

BOOL System_setenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* name = lvar;
    CLVALUE* value = lvar + 1;
    CLVALUE* overwrite = lvar + 2;

    if(name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(value->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* name_value = ALLOC string_object_to_char_array(name->mObjectValue);
    char* value_value = ALLOC string_object_to_char_array(value->mObjectValue);
    int overwrite_value = overwrite->mIntValue;

    /// go ///
    int result = setenv(name_value, value_value, overwrite_value);

    if(result < 0) {
        MFREE(name_value);
        MFREE(value_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "setenv(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(name_value);
    MFREE(value_value);

    return TRUE;
}

BOOL System_unsetenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* name = lvar;

    if(name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* name_value = ALLOC string_object_to_char_array(name->mObjectValue);

    /// go ///
    int result = unsetenv(name_value);

    if(result < 0) {
        MFREE(name_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "unsetenv(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    MFREE(name_value);

    return TRUE;
}

BOOL System_dlopen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* flags = lvar + 1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    int flags_value = flags->mIntValue;

    /// go ///
    void* result = dlopen(path_value, flags_value);

    if(result == NULL) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "dlopen(3) is faield. The error is %s", dlerror());
        return FALSE;
    }

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    MFREE(path_value);

    return TRUE;
}

BOOL System_dlclose(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* handle = lvar;

    /// Clover to c value ///
    void* handle_value = handle->mPointerValue;

    /// go ///
    int result = dlclose(handle_value);

    if(result != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "dlclose(3) is faield. The error is %s", dlerror());
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_dlsym(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* handle = lvar;
    CLVALUE* symbol = lvar + 1;

    if(symbol->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    void* handle_value = handle->mPointerValue;
    char* symbol_value = ALLOC string_object_to_char_array(symbol->mObjectValue);

    /// go ///
    void* result = dlsym(handle_value, symbol_value);

    if(result == NULL) {
        MFREE(symbol_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "dlsym(3) is faield. The error is %s", dlerror());
        return FALSE;
    }

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    MFREE(symbol_value);

    return TRUE;
}

BOOL System_put_fun_to_hash_for_native_method(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* fun_name = lvar + 1;
    CLVALUE* native_method = lvar + 2;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(fun_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    char* fun_name_value = ALLOC string_object_to_char_array(fun_name->mObjectValue);
    fNativeMethod native_method_value = (fNativeMethod)native_method->mPointerValue;

    /// go ///
    put_fun_to_hash_for_native_method(path_value, fun_name_value, native_method_value);

    MFREE(path_value);
    MFREE(fun_name_value);

    return TRUE;
}

BOOL System_alarm(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* seconds = lvar;

    /// Clover to c value ///
    unsigned int seconds_value = seconds->mUIntValue;

    /// go ///
    unsigned int result = alarm(seconds_value);

    (*stack_ptr)->mUIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_dup(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* old_fd = lvar;

    /// Clover to c value ///
    int old_fd_value = old_fd->mIntValue;

    /// go ///
    int result = dup(old_fd_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "dup(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_dup3(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* old_fd = lvar;
    CLVALUE* new_fd = lvar + 1;
    CLVALUE* flags = lvar + 2;

    /// Clover to c value ///
    int old_fd_value = old_fd->mIntValue;
    int new_fd_value = new_fd->mIntValue;
    int flags_value = flags->mIntValue;

    /// go ///
    int result = dup3(old_fd_value, new_fd_value, flags_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "dup3(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_execvpe(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* method_name = lvar;
    CLVALUE* params = lvar+1;
    CLVALUE* envp = lvar+2;

    if(method_name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(params->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(envp->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* method_name_value = ALLOC string_object_to_char_array(method_name->mObjectValue);
    int num_elements = 0;
    CLObject* params_objects = ALLOC list_to_array(params->mObjectValue, &num_elements);
    char** params_value = ALLOC MCALLOC(1, sizeof(char*)*(num_elements+2));
    int i;
    params_value[0] = method_name_value;
    for(i=0; i<num_elements; i++) {
        CLObject string_object = params_objects[i];
        params_value[i+1] = ALLOC string_object_to_char_array(string_object);
    }
    params_value[i+1] = NULL;
    MFREE(params_objects);

    int num_elements2 = 0;
    CLObject* envp_objects = ALLOC list_to_array(envp->mObjectValue, &num_elements2);
    char** envp_value = ALLOC MCALLOC(1, sizeof(char*)*(num_elements2+1));
    for(i=0; i<num_elements2; i++) {
        CLObject string_object = envp_objects[i];
        envp_value[i] = ALLOC string_object_to_char_array(string_object);
    }
    envp_value[i] = NULL;
    MFREE(envp_objects);

    /// go ///
    int result = execvpe(method_name_value, params_value, envp_value);

    if(result < 0) {
        int i;
        for(i=0; i<num_elements+1; i++) {
            MFREE(params_value[i]);
        }
        MFREE(params_value);
        for(i=0; i<num_elements2; i++) {
            MFREE(envp_value[i]);
        }
        MFREE(envp_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "execvpe(2) is faield. The error is %s. The errnor is %d.", strerror(errno), errno);
        return FALSE;
    }

    for(i=0; i<num_elements+1; i++) {
        MFREE(params_value[i]);
    }
    MFREE(params_value);
    for(i=0; i<num_elements2; i++) {
        MFREE(envp_value[i]);
    }
    MFREE(envp_value);

    return TRUE;
}

BOOL System_fopen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* path = lvar;
    CLVALUE* mode = lvar+1;

    if(path->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(mode->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    char* mode_value = ALLOC string_object_to_char_array(mode->mObjectValue);
    
    /// go ///
    FILE* result = fopen(path_value, mode_value);

    if(result == NULL) {
        MFREE(path_value);
        MFREE(mode_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fopen(3) is faield. The error is %s. The errnor is %d.", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mPointerValue = (char*)result;
    (*stack_ptr)++;

    MFREE(path_value);
    MFREE(mode_value);

    return TRUE;
}

BOOL System_fclose(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* stream = lvar;

    if(stream->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    FILE* stream_value = (FILE*)stream->mPointerValue;
    
    /// go ///
    int result = fclose(stream_value);

    if(result == EOF) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fclose(3) is faield. The error is %s. The errnor is %d.", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_fwrite(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* buf = lvar;
    CLVALUE* size = lvar + 1;
    CLVALUE* stream = lvar +2;

    /// Clover to c value ///
    if(buf->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    
    if(stream->mPointerValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    
    void* buf_value = get_pointer_from_buffer_object(buf->mObjectValue);
    size_t size_value = (size_t)size->mULongValue;
    FILE* stream_value = (FILE*)stream->mPointerValue;

    int buffer_size = get_size_from_buffer_object(buf->mObjectValue);

    /// check size ///
    if(size_value > buffer_size) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Buffer size is smaller than the size value of argument");
        return FALSE;
    }

    /// go ///
    ssize_t result = fwrite(buf_value, 1, size_value, stream_value);

    if(result <= 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fwrite(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mULongValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_fread(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* buf = lvar;
    CLVALUE* size = lvar + 1;
    CLVALUE* stream = lvar + 2;

    /// Clover to c value ///
    if(buf->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(stream->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    void* buf_value = get_pointer_from_buffer_object(buf->mObjectValue);
    size_t size_value = (size_t)size->mULongValue;

    int buffer_size = get_size_from_buffer_object(buf->mObjectValue);
    
    FILE* stream_value = (FILE*)stream->mPointerValue;

    /// check size ///
    if(size_value > buffer_size) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Buffer size is smaller than the size value of argument");
        return FALSE;
    }

    /// go ///
    size_t result = fread(buf_value, 1, size_value, stream_value);

    if(ferror(stream_value) != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fread(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    sCLObject* obj_data = CLOBJECT(buf->mObjectValue);
    obj_data->mFields[1].mULongValue = result;                // len

    (*stack_ptr)->mULongValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_feof(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* stream = lvar;

    /// Clover to c value ///
    if(stream->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    FILE* stream_value = (FILE*)stream->mPointerValue;

    /// go ///
    BOOL result = feof(stream_value) != 0;

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_fgetc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* stream = lvar;

    /// Clover to c value ///
    if(stream->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    FILE* stream_value = (FILE*)stream->mPointerValue;

    /// go ///
    int result = fgetc(stream_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_initialize_system_calls_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+0].mValue.mIntValue = O_CLOEXEC;

#define LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS (LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+1)

    return TRUE;
}
