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

    strcpy(str1->mPointerValue, str2->mPointerValue);

    (*stack_ptr)->mPointerValue = str2->mPointerValue;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_memcpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;
    CLVALUE* len = lvar + 2;

    memcpy(str1->mPointerValue, str2->mPointerValue, len->mULongValue);

    (*stack_ptr)->mPointerValue = str2->mPointerValue;
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

    xstrncpy(str1->mPointerValue, str2->mPointerValue, size->mULongValue);

    (*stack_ptr)->mPointerValue = str2->mPointerValue;
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

    fprintf(stderr, "%ls", wstr);
    fflush(stderr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_printlnToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
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

    fprintf(stderr, "%ls\n", wstr);
    fflush(stderr);

    MFREE(wstr);

    return TRUE;
}

BOOL System_sleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* time = lvar;

    unsigned int result = sleep(lvar->mIntValue);

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

    /// convert Clover value to C value ///
    sRegexObject* regex_object_data = CLREGEX(regex->mObjectValue);

    pcre* regex_value = regex_object_data->mRegex;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* str_value = string_object_to_char_array(str->mObjectValue);

    int len = strlen(str_value);

    int ovec_max_value = ovec_max->mIntValue;
    int* ovec_value = MCALLOC(1, sizeof(int)*ovec_max_value * 3);

    int offset_value = utf32_index_to_utf8_index(str_value, offset->mIntValue);

    /// go ///
    int options = PCRE_NEWLINE_LF;
    int result = pcre_exec(regex_value, 0, str_value, len, offset_value, options, ovec_value, ovec_max_value*3);

    /// set result data on ovec object ///
    CLObject pcre_ovec_object = pcre_ovec->mObjectValue;
    sCLObject* pcre_ovec_object_data = CLOBJECT(pcre_ovec_object);

    CLObject pcre_ovec_start_array = pcre_ovec_object_data->mFields[0].mObjectValue;
    CLObject pcre_ovec_end_array = pcre_ovec_object_data->mFields[1].mObjectValue;

    sCLObject* pcre_ovec_start_array_data = CLOBJECT(pcre_ovec_start_array);
    sCLObject* pcre_ovec_end_array_data = CLOBJECT(pcre_ovec_end_array);

    int i;
    for(i=0; i<ovec_max_value; i++) {
        if(i < pcre_ovec_start_array_data->mArrayNum) {
            int utf32index = utf8_index_to_utf32_index(str_value, ovec_value[i*2]);
            pcre_ovec_start_array_data->mFields[i].mIntValue = utf32index;
        }
        if(i < pcre_ovec_end_array_data->mArrayNum) {
            int utf32index = utf8_index_to_utf32_index(str_value, ovec_value[i*2+1]);
            pcre_ovec_end_array_data->mFields[i].mIntValue = utf32index;
        }
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    MFREE(str_value);
    MFREE(ovec_value);

    return TRUE;
}

BOOL System_sprintf(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* format = lvar;
    CLVALUE* params = lvar+1;

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
                    asprintf(ALLOC &str, format2, get_value_from_Byte(param));
                }
                else if(is_this_class_with_class_name(klass, "UByte")) {
                    asprintf(ALLOC &str, format2, get_value_from_UByte(param));
                }
                else if(is_this_class_with_class_name(klass, "Short")) {
                    asprintf(ALLOC &str, format2, get_value_from_Short(param));
                }
                else if(is_this_class_with_class_name(klass, "UShort")) {
                    asprintf(ALLOC &str, format2, get_value_from_UShort(param));
                }
                else if(is_this_class_with_class_name(klass, "Integer")) {
                    asprintf(ALLOC &str, format2, get_value_from_Integer(param));
                }
                else if(is_this_class_with_class_name(klass, "UInteger")) {
                    asprintf(ALLOC &str, format2, get_value_from_UInteger(param));
                }
                else if(is_this_class_with_class_name(klass, "Long")) {
                    asprintf(ALLOC &str, format2, get_value_from_Long(param));
                }
                else if(is_this_class_with_class_name(klass, "ULong")) {
                    asprintf(ALLOC &str, format2, get_value_from_ULong(param));
                }
                else if(is_this_class_with_class_name(klass, "Char")) {
                    asprintf(ALLOC &str, format2, get_value_from_Char(param));
                }
                else if(is_this_class_with_class_name(klass, "Float")) {
                    asprintf(ALLOC &str, format2, get_value_from_Float(param));
                }
                else if(is_this_class_with_class_name(klass, "Double")) {
                    asprintf(ALLOC &str, format2, get_value_from_Double(param));
                }
                else if(is_this_class_with_class_name(klass, "Bool")) {
                    asprintf(ALLOC &str, format2, get_value_from_Bool(param));
                }
                else if(is_this_class_with_class_name(klass, "Pointer")) {
                    asprintf(ALLOC &str, format2, get_value_from_Pointer(param));
                }
                else if(is_this_class_with_class_name(klass, "String")) {
                    char* str2 = ALLOC string_object_to_char_array(param);
                    asprintf(ALLOC &str, format2, str2);
                    MFREE(str2);
                }
                else if(is_this_class_with_class_name(klass, "Buffer")) {
                    sCLObject* object_data = CLOBJECT(param);
                    char* str2 = object_data->mFields[0].mPointerValue;
                    asprintf(ALLOC &str, format2, str2);
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
    wchar_t* wcs = MCALLOC(1, sizeof(wchar_t)*(size_value));
    CLVALUE* dest_value = (CLVALUE*)dest->mPointerValue;

    BOOL null_terminated = FALSE;
    if(src_value[size_value-1] == '\0') {
        null_terminated = TRUE;
    }

    /// go ///
    int size_wcs = mbstowcs(wcs, src_value, size_value);

    if(size_wcs < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "invalid multi byte string");
        MFREE(wcs);
        return FALSE;
    }

    /// make result ///
    sCLClass* klass = get_class("char");

    MASSERT(klass != NULL);

    if(null_terminated) {
        CLObject object = create_array_object(klass, size_wcs+1);
        sCLObject* object_data = CLOBJECT(object);

        int i;
        for(i=0; i<size_wcs; i++) {
            object_data->mFields[i].mCharValue = wcs[i];
        }
        object_data->mFields[i].mCharValue = '\0';

        dest_value->mObjectValue = object;
    }
    else {
        CLObject object = create_array_object(klass, size_wcs);
        sCLObject* object_data = CLOBJECT(object);

        int i;
        for(i=0; i<size_wcs; i++) {
            object_data->mFields[i].mCharValue = wcs[i];
        }

        dest_value->mObjectValue = object;
    }

    MFREE(wcs);

    (*stack_ptr)->mIntValue = size_wcs;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_wcstombs(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* dest = lvar;
    CLVALUE* src = lvar+1;

    /// clover variable to c variable ///
    CLVALUE* dest_value = (CLVALUE*)dest->mPointerValue;
    CLObject src_value = src->mObjectValue;
    sCLObject* object_data = CLOBJECT(src_value);
    int len = object_data->mArrayNum;

    wchar_t* wcs = MCALLOC(1, sizeof(wchar_t)*(len));
    size_t size = sizeof(char)*MB_LEN_MAX*(len);
    char* mbs = MCALLOC(1, size);

    int i;
    for(i=0; i<len; i++) {
        wcs[i] = object_data->mFields[i].mCharValue;
    }
    BOOL null_terminated = FALSE;
    if(wcs[len-1] == '\0') {
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

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;
    char* str_value = ALLOC string_object_to_char_array(str_object);

    /// go ///
    double result = strtod(str_value, NULL);

    (*stack_ptr)->mDoubleValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_strcmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    CLVALUE* str2 = (lvar+1);

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

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;
    char* str_value = ALLOC string_object_to_char_array(str_object);

    int base_value = base->mIntValue;

    /// go ///
    long result = strtol(str_value, NULL, base_value);

    (*stack_ptr)->mLongValue = result;
    (*stack_ptr)++;

    MFREE(str_value);

    return TRUE;
}

BOOL System_strtoul(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    CLVALUE* base = (lvar+1);

    /// Clover to c value ///
    CLObject str_object = str->mObjectValue;
    char* str_value = ALLOC string_object_to_char_array(str_object);

    int base_value = base->mIntValue;

    /// go ///
    unsigned long result = strtol(str_value, NULL, base_value);

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
    unsigned long result = time(NULL);

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
    char* file_name_value = ALLOC string_object_to_char_array(file_name->mObjectValue);

    int flags_value = flags->mIntValue;

    int mode_value = mode->mIntValue;

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

BOOL System_initialize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[0].mValue.mIntValue = S_IFMT;
    system->mClassFields[1].mValue.mIntValue = S_IFDIR;
    system->mClassFields[2].mValue.mIntValue = S_IFCHR;
    system->mClassFields[3].mValue.mIntValue = S_IFBLK;
    system->mClassFields[4].mValue.mIntValue = S_IFREG;
    system->mClassFields[5].mValue.mIntValue = S_IFIFO;
    system->mClassFields[6].mValue.mIntValue = S_IFLNK;
    system->mClassFields[7].mValue.mIntValue = S_IFSOCK;
    system->mClassFields[8].mValue.mIntValue = S_ISUID;
    system->mClassFields[9].mValue.mIntValue = S_ISGID;
    system->mClassFields[10].mValue.mIntValue = S_ISVTX;
    system->mClassFields[11].mValue.mIntValue = S_IRUSR;
    system->mClassFields[12].mValue.mIntValue = S_IWUSR;
    system->mClassFields[13].mValue.mIntValue = S_IXUSR;
    system->mClassFields[14].mValue.mIntValue = S_IRWXU;
    system->mClassFields[15].mValue.mIntValue = S_IRGRP;
    system->mClassFields[16].mValue.mIntValue = S_IWGRP;
    system->mClassFields[17].mValue.mIntValue = S_IXGRP;
    system->mClassFields[18].mValue.mIntValue = S_IRWXG;
    system->mClassFields[19].mValue.mIntValue = S_IROTH;
    system->mClassFields[20].mValue.mIntValue = S_IWOTH;
    system->mClassFields[21].mValue.mIntValue = S_IXOTH;
    system->mClassFields[22].mValue.mIntValue = S_IRWXO;
    system->mClassFields[23].mValue.mIntValue = R_OK;
    system->mClassFields[24].mValue.mIntValue = W_OK;
    system->mClassFields[25].mValue.mIntValue = X_OK;
    system->mClassFields[26].mValue.mIntValue = F_OK;
    system->mClassFields[27].mValue.mIntValue = O_APPEND;
    system->mClassFields[28].mValue.mIntValue = O_ASYNC;
    system->mClassFields[29].mValue.mIntValue = O_RDONLY;
    system->mClassFields[30].mValue.mIntValue = O_WRONLY;
    system->mClassFields[31].mValue.mIntValue = O_RDWR;
    system->mClassFields[32].mValue.mIntValue = O_CREAT;
    system->mClassFields[33].mValue.mIntValue = O_DIRECTORY;
    system->mClassFields[34].mValue.mIntValue = O_EXCL;
    system->mClassFields[35].mValue.mIntValue = O_NOCTTY;
    system->mClassFields[36].mValue.mIntValue = O_NOFOLLOW;
#ifdef O_TMPFILE
    system->mClassFields[37].mValue.mIntValue = O_TMPFILE;
#endif
    system->mClassFields[38].mValue.mIntValue = O_TRUNC;
#ifdef O_TTY_INIT
    system->mClassFields[39].mValue.mIntValue = O_TTY_INIT;
#endif
    system->mClassFields[40].mValue.mIntValue = O_CLOEXEC;
    system->mClassFields[41].mValue.mIntValue = O_DIRECT;
    system->mClassFields[42].mValue.mIntValue = O_DSYNC;
    system->mClassFields[43].mValue.mIntValue = O_LARGEFILE;
    system->mClassFields[44].mValue.mIntValue = O_NOATIME;
    system->mClassFields[45].mValue.mIntValue = O_NONBLOCK;
#ifdef O_PATH
    system->mClassFields[46].mValue.mIntValue = O_PATH;
#endif
    system->mClassFields[47].mValue.mIntValue = O_SYNC;

    system->mClassFields[48].mValue.mIntValue = FNM_NOESCAPE;
    system->mClassFields[49].mValue.mIntValue = FNM_PATHNAME;
    system->mClassFields[50].mValue.mIntValue = FNM_PERIOD;
    system->mClassFields[51].mValue.mIntValue = FNM_FILE_NAME;
    system->mClassFields[52].mValue.mIntValue = FNM_LEADING_DIR;
    system->mClassFields[53].mValue.mIntValue = FNM_CASEFOLD;

    system->mClassFields[54].mValue.mIntValue = CLOCK_REALTIME;
#ifdef CLOCK_REALTIME_COARSE
    system->mClassFields[55].mValue.mIntValue = CLOCK_REALTIME_COARSE;
#endif
    system->mClassFields[56].mValue.mIntValue = CLOCK_MONOTONIC;
#ifdef CLOCK_MONOTONIC_COARSE
    system->mClassFields[57].mValue.mIntValue = CLOCK_MONOTONIC_COARSE;
#endif
    system->mClassFields[58].mValue.mIntValue = CLOCK_MONOTONIC_RAW;
#ifdef CLOCK_BOOTTIME
    system->mClassFields[59].mValue.mIntValue = CLOCK_BOOTTIME;
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
    system->mClassFields[60].mValue.mIntValue = CLOCK_PROCESS_CPUTIME_ID;
#endif
#ifdef CLOCK_THREAD_CPUTIME_ID
    system->mClassFields[61].mValue.mIntValue = CLOCK_THREAD_CPUTIME_ID;
#endif

#define LAST_INITIALIZE_FIELD_NUM 61

    return TRUE;
}

BOOL System_read(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* buf = lvar+1;
    CLVALUE* size = lvar + 2;

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
    int result = read(fd_value, buf_value, size_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "read(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    sCLObject* obj_data = CLOBJECT(buf->mObjectValue);
    obj_data->mFields[1].mULongValue = result;                // len

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_write(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* buf = lvar+1;
    CLVALUE* size = lvar + 2;

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
    int result = write(fd_value, buf_value, size_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "write(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
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
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "localtime(3) is faield");
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
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "mktime(3) is faield");
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
    struct dirent* entry = readdir(dir_value);

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

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+1].mValue.mIntValue = WNOHANG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+2].mValue.mIntValue = WUNTRACED;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+3].mValue.mIntValue = WCONTINUED;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+4].mValue.mIntValue = SIGHUP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+5].mValue.mIntValue = SIGINT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+6].mValue.mIntValue = SIGQUIT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+7].mValue.mIntValue = SIGILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+8].mValue.mIntValue = SIGABRT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+9].mValue.mIntValue = SIGFPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+10].mValue.mIntValue = SIGKILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+11].mValue.mIntValue = SIGSEGV;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+12].mValue.mIntValue = SIGPIPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+13].mValue.mIntValue = SIGALRM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+14].mValue.mIntValue = SIGTERM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+15].mValue.mIntValue = SIGUSR1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+16].mValue.mIntValue = SIGUSR2;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+17].mValue.mIntValue = SIGCHLD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+18].mValue.mIntValue = SIGCONT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+19].mValue.mIntValue = SIGSTOP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+20].mValue.mIntValue = SIGTSTP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+21].mValue.mIntValue = SIGTTIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+22].mValue.mIntValue = SIGTTOU;

    // c_iflag bits
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+23].mValue.mIntValue = IGNBRK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+24].mValue.mIntValue = BRKINT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+25].mValue.mIntValue = IGNPAR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+26].mValue.mIntValue = PARMRK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+27].mValue.mIntValue = INPCK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+28].mValue.mIntValue = ISTRIP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+29].mValue.mIntValue = INLCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+30].mValue.mIntValue = IGNCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+31].mValue.mIntValue = ICRNL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+32].mValue.mIntValue = IUCLC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+33].mValue.mIntValue = IXON;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+34].mValue.mIntValue = IXANY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+35].mValue.mIntValue = IXOFF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+36].mValue.mIntValue = IMAXBEL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+37].mValue.mIntValue = IUTF8;

    // c_oflag bits
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+38].mValue.mIntValue = OPOST;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+39].mValue.mIntValue = OLCUC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+40].mValue.mIntValue = ONLCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+41].mValue.mIntValue = OCRNL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+42].mValue.mIntValue = ONOCR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+43].mValue.mIntValue = ONLRET;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+44].mValue.mIntValue = OFILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+45].mValue.mIntValue = OFDEL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+46].mValue.mIntValue = NLDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+47].mValue.mIntValue = NL0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+48].mValue.mIntValue = NL1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+49].mValue.mIntValue = CRDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+50].mValue.mIntValue = CR0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+51].mValue.mIntValue = CR1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+52].mValue.mIntValue = CR2;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+53].mValue.mIntValue = CR3;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+54].mValue.mIntValue = TABDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+55].mValue.mIntValue = TAB0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+56].mValue.mIntValue = TAB1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+57].mValue.mIntValue = TAB2;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+58].mValue.mIntValue = TAB3;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+59].mValue.mIntValue = BSDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+60].mValue.mIntValue = BS0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+61].mValue.mIntValue = BS1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+62].mValue.mIntValue = FFDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+63].mValue.mIntValue = FF0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+64].mValue.mIntValue = FF1;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+65].mValue.mIntValue = VTDLY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+66].mValue.mIntValue = VT0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+67].mValue.mIntValue = VT1;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+68].mValue.mIntValue = XTABS;

    // c_cflag bit meaning
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+69].mValue.mIntValue = CBAUD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+70].mValue.mIntValue = B0;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+71].mValue.mIntValue = B50;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+72].mValue.mIntValue = B75;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+73].mValue.mIntValue = B110;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+74].mValue.mIntValue = B134;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+75].mValue.mIntValue = B150;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+76].mValue.mIntValue = B200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+77].mValue.mIntValue = B300;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+78].mValue.mIntValue = B600;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+79].mValue.mIntValue = B1200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+80].mValue.mIntValue = B1800;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+81].mValue.mIntValue = B2400;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+82].mValue.mIntValue = B4800;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+83].mValue.mIntValue = B9600;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+84].mValue.mIntValue = B19200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+85].mValue.mIntValue = B38400;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+86].mValue.mIntValue = EXTA;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+87].mValue.mIntValue = EXTB;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+88].mValue.mIntValue = CSIZE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+89].mValue.mIntValue = CS5;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+90].mValue.mIntValue = CS6;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+91].mValue.mIntValue = CS7;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+92].mValue.mIntValue = CS8;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+93].mValue.mIntValue = CSTOPB;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+94].mValue.mIntValue = CREAD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+95].mValue.mIntValue = PARENB;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+96].mValue.mIntValue = PARODD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+97].mValue.mIntValue = HUPCL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+98].mValue.mIntValue = CLOCAL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+99].mValue.mIntValue = CBAUDEX;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+100].mValue.mIntValue = B57600;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+101].mValue.mIntValue = B115200;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+102].mValue.mIntValue = B230400;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+103].mValue.mIntValue = B460800;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+104].mValue.mIntValue = B500000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+105].mValue.mIntValue = B576000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+106].mValue.mIntValue = B921600;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+107].mValue.mIntValue = B1000000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+108].mValue.mIntValue = B1152000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+109].mValue.mIntValue = B1500000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+110].mValue.mIntValue = B2000000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+111].mValue.mIntValue = B2500000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+112].mValue.mIntValue = B3000000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+113].mValue.mIntValue = B3500000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+114].mValue.mIntValue = B4000000;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+115].mValue.mIntValue = CIBAUD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+116].mValue.mIntValue = CMSPAR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+117].mValue.mIntValue = CRTSCTS;

    // c_lflag bits
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+118].mValue.mIntValue = ISIG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+119].mValue.mIntValue = ICANON;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+120].mValue.mIntValue = XCASE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+121].mValue.mIntValue = ECHO;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+122].mValue.mIntValue = ECHOE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+123].mValue.mIntValue = ECHOK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+124].mValue.mIntValue = ECHONL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+125].mValue.mIntValue = NOFLSH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+126].mValue.mIntValue = TOSTOP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+127].mValue.mIntValue = ECHOCTL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+128].mValue.mIntValue = ECHOPRT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+129].mValue.mIntValue = ECHOKE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+130].mValue.mIntValue = FLUSHO;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+131].mValue.mIntValue = PENDIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+132].mValue.mIntValue = IEXTEN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+133].mValue.mIntValue = EXTPROC;

    // tcflow() and TCXONC use these 
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+134].mValue.mIntValue = TCOOFF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+135].mValue.mIntValue = TCOON;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+136].mValue.mIntValue = TCIOFF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+137].mValue.mIntValue = TCION;

    // tcflush() and TCFLSH use these
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+138].mValue.mIntValue = TCIFLUSH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+139].mValue.mIntValue = TCOFLUSH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+140].mValue.mIntValue = TCIOFLUSH;

    // tcsetattr uses these
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+141].mValue.mIntValue = TCSANOW;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+142].mValue.mIntValue = TCSADRAIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+143].mValue.mIntValue = TCSAFLUSH;

    // c_cc characters
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+144].mValue.mIntValue = VINTR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+145].mValue.mIntValue = VQUIT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+146].mValue.mIntValue = VERASE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+147].mValue.mIntValue = VKILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+148].mValue.mIntValue = VEOF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+149].mValue.mIntValue = VTIME;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+150].mValue.mIntValue = VMIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+151].mValue.mIntValue = VSWTC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+152].mValue.mIntValue = VSTART;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+153].mValue.mIntValue = VSTOP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+154].mValue.mIntValue = VSUSP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+155].mValue.mIntValue = VEOL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+156].mValue.mIntValue = VREPRINT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+157].mValue.mIntValue = VDISCARD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+158].mValue.mIntValue = VWERASE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+159].mValue.mIntValue = VLNEXT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM+160].mValue.mIntValue = VEOL2;

#define LAST_INITIALIZE_FIELD_NUM2 160

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

        if(!invoke_block(block_value, info->current_stack, info->current_var_num, num_params, stack_ptr, info)) {
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
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "execvp(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
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

    /// Clover to c value ///
    char* path_value = ALLOC string_object_to_char_array(path->mObjectValue);
    uid_t owner_value = owner->mIntValue;
    gid_t group_value = group->mIntValue;

    /// go ///
    int result = lchown(path_value, owner_value, group_value);

    if(result < 0) {
        MFREE(path_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "chown(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
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

    /// Clover to c value ///
    clockid_t clk_id_value = clk_id->mIntValue;
    CLObject tp_value = tp->mObjectValue;

    /// go ///
    struct timespec timespec_struct;
    int result = clock_gettime(clk_id_value, &timespec_struct);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "clock_getres(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
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

    /// Clover to c value ///
    clockid_t clk_id_value = clk_id->mIntValue;

    struct timespec timespec_struct;

    CLObject tp_value = tp->mObjectValue;
    sCLObject* object_data = CLOBJECT(tp_value);

    timespec_struct.tv_sec = object_data->mFields[0].mULongValue;
    timespec_struct.tv_nsec = object_data->mFields[1].mLongValue;

    /// go ///
    int result = clock_gettime(clk_id_value, &timespec_struct);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "clock_getres(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

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
