#include "common.h"
#include <wchar.h>

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
        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "System.assert failed");
        return FALSE;
    }

    return TRUE;
}

BOOL System_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* size = lvar;

    char* memory = MMALLOC(size->mIntValue);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_calloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* number = lvar;
    CLVALUE* size = lvar + 1;

    char* memory = MCALLOC(number->mIntValue, size->mIntValue);

    (*stack_ptr)->mPointerValue = memory;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_realloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* ptr = lvar;
    CLVALUE* size = lvar + 1;

    char* memory = MREALLOC(ptr->mPointerValue, size->mIntValue);

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
        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid byte array");
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

    memcpy(str1->mPointerValue, str2->mPointerValue, len->mIntValue);

    (*stack_ptr)->mPointerValue = str2->mPointerValue;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_memcmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;
    CLVALUE* size = lvar + 2;

    int result = memcmp(str1->mPointerValue, str2->mPointerValue, size->mIntValue);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strncpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str1 = lvar;
    CLVALUE* str2 = lvar + 1;
    CLVALUE* size = lvar + 2;

    xstrncpy(str1->mPointerValue, str2->mPointerValue, size->mIntValue);

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
    CLVALUE* ovec_max = (lvar+2);
    CLVALUE* pcre_ovec = (lvar+3);

    /// convert Clover value to C value ///
    sRegexObject* regex_object_data = CLREGEX(regex->mObjectValue);

    pcre* regex_value = regex_object_data->mRegex;

    wchar_t* wstr = ALLOC string_object_to_wchar_array(str->mObjectValue);

    int len = wcslen(wstr);
    
    char* str_value = ALLOC xwcstombs(wstr, len);

    MFREE(wstr);

    int ovec_max_value = ovec_max->mIntValue;
    int* ovec_value = MCALLOC(1, sizeof(int)*ovec_max_value * 3);

    /// go ///
    int options = PCRE_NEWLINE_LF;
    int offset = 0;
    int result = pcre_exec(regex_value, 0, str_value, len, offset, options, ovec_value, ovec_max_value*3);

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
            pcre_ovec_start_array_data->mFields[i].mIntValue = ovec_value[i*2];
        }
        if(i < pcre_ovec_end_array_data->mArrayNum) {
            pcre_ovec_end_array_data->mFields[i].mIntValue = ovec_value[i*2+1];
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
                        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
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
                        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
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
                    entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }

                while(1) {
                    if(isdigit(*p) || *p == '*' || *p == '$') {
                        *p2++ = *p++;

                        if(p2 - format2 >= 128) {
                            entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
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
                        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
                        MFREE(buf.mBuf);
                        MFREE(format_string);
                        return FALSE;
                    }
                }
                else if(*p == 'h' || *p == 'l' || *p == 'L' || *p == 'j' || *p == 'z' || *p == 't') 
                {
                    *p2++ = *p++;

                    if(p2 - format2 >= 128) {
                        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
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
                    entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }
            }
            else if(*p == '%') {
                *p2++ = *p++;

                no_conversion = TRUE;

                if(p2 - format2 >= 128) {
                    entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }
            }
            else {
                entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
                MFREE(buf.mBuf);
                MFREE(format_string);
                return FALSE;
            }

            *p2++ = 0;

            if(p2 - format2 >= 128) {
                entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
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
                else {
                    entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }

                sBuf_append_str(&buf, str);

                free(str);

                param_num++;
            }
            else {
                entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid format string");
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

    /// clover variable to c variable ///
    char* src_value = src->mPointerValue;
    int len = strlen(src_value);
    wchar_t* wcs = MCALLOC(1, sizeof(wchar_t)*(len+1));
    CLVALUE* dest_value = (CLVALUE*)dest->mPointerValue;

    /// go ///
    int memory = mbstowcs(wcs, src_value, len+1);

    if(memory < 0) {
        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "invalid multi byte string");
        MFREE(wcs);
        return FALSE;
    }

    /// make result ///
    sCLClass* klass = get_class("char");

    MASSERT(klass != NULL);

    CLObject object = create_array_object(klass, len+1);
    sCLObject* object_data = CLOBJECT(object);

    int i;
    for(i=0; i<len; i++) {
        object_data->mFields[i].mCharValue = wcs[i];
    }
    object_data->mFields[i].mCharValue = '\0';

    dest_value->mObjectValue = object;

    MFREE(wcs);

    (*stack_ptr)->mIntValue = memory;
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

    wchar_t* wcs = MCALLOC(1, sizeof(wchar_t)*(len+1));
    int size = sizeof(char)*MB_LEN_MAX*(len+1);
    char* mbs = MCALLOC(1, size);

    int i;
    for(i=0; i<len; i++) {
        wcs[i] = object_data->mFields[i].mCharValue;
    }
    wcs[i] = '\0';

    /// go ///
    int num = wcstombs(mbs, wcs, size);

    if(num < 0) {
        entry_exception_object_with_class_name(*stack_ptr, info, "Exception", "wcstombs returns -1");
        MFREE(wcs);
        MFREE(mbs);
        return FALSE;
    }

    /// make result ///
    sCLClass* klass = get_class("byte");

    MASSERT(klass != NULL);

    CLObject object = create_array_object(klass, size);
    sCLObject* object_data2 = CLOBJECT(object);

    for(i=0; i<size; i++) {
        object_data2->mFields[i].mByteValue = mbs[i];
    }

    dest_value->mObjectValue = object;

    MFREE(wcs);
    MFREE(mbs);

    (*stack_ptr)->mIntValue = num;
    (*stack_ptr)++;

    return TRUE;
}
