#include "common.h"

static unsigned int object_size()
{
    unsigned int size;

    size = sizeof(sRegexObject);

    /// align to 4 byte boundry
    alignment(&size);

    return size;
}

void regex_free_fun(CLObject obj)
{
    sRegexObject* object_data = CLREGEX(obj);

    pcre_free(object_data->mRegex);
    MFREE(object_data->mRegexString);
}

CLObject create_regex_object(char* regex, BOOL global, BOOL ignore_case, BOOL multiline, BOOL extended, BOOL dotall, BOOL anchored, BOOL dollar_endonly, BOOL ungreedy)
{
    int size = object_size();

    sCLClass* klass = get_class("regex");

    MASSERT(klass != NULL);

    CLObject obj = alloc_heap_mem(size, klass, -1);

    sRegexObject* object_data = CLREGEX(obj);

    int option = ignore_case ? PCRE_CASELESS:0;

    const char* err;
    int erro_ofs;

    int options = PCRE_UTF8 | (ignore_case ? PCRE_CASELESS:0) | (multiline ? PCRE_MULTILINE : 0) | (extended ? PCRE_EXTENDED :0) | (dotall ? PCRE_DOTALL :0) | (dollar_endonly ? PCRE_DOLLAR_ENDONLY:0) | (ungreedy ? PCRE_UNGREEDY:0);
    //int options = PCRE_UTF8 | (ignore_case ? PCRE_CASELESS:0) | (multiline ? PCRE_MULTILINE : 0) | (extended ? PCRE_EXTENDED :0) | (dotall ? PCRE_DOTALL :0) | (anchored ? PCRE_ANCHORED : 0) | (dollar_endonly ? PCRE_DOLLAR_ENDONLY) | (ungreedy ? PCRE_UNGREEDY);

    object_data->mRegexString = MSTRDUP(regex);

    object_data->mRegex = pcre_compile(regex, options,&err, &erro_ofs, NULL);
    object_data->mGlobal = global;
    object_data->mIgnoreCase = ignore_case;
    object_data->mMultiline = multiline;
    object_data->mExtended = extended;
    object_data->mDotAll = dotall;
    object_data->mAnchored = anchored;
    object_data->mDollarEndOnly = dollar_endonly;
    object_data->mUngreedy = ungreedy;

    return obj;
}

BOOL regex_equals(CLObject left, CLObject right)
{
    sRegexObject* left_object = CLREGEX(left);
    sRegexObject* right_object = CLREGEX(right);

    return strcmp(left_object->mRegexString, right_object->mRegexString) == 0
        && left_object->mGlobal == right_object->mGlobal 
        && left_object->mIgnoreCase == right_object->mIgnoreCase 
        && left_object->mMultiline == right_object->mMultiline 
        && left_object->mExtended == right_object->mExtended 
        && left_object->mDotAll == right_object->mDotAll 
        && left_object->mAnchored == right_object->mAnchored 
        && left_object->mDollarEndOnly == right_object->mDollarEndOnly 
        && left_object->mUngreedy == right_object->mUngreedy;
}

