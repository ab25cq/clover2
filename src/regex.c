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
}

CLObject create_regex_object(char* regex, BOOL global, BOOL ignore_case)
{
    int size = object_size();

    sCLClass* klass = get_class("regex");

    MASSERT(klass != NULL);

    CLObject obj = alloc_heap_mem(size, klass, -1);

    sRegexObject* object_data = CLREGEX(obj);

    int option = ignore_case ? PCRE_CASELESS:0;

    const char* err;
    int erro_ofs;

    object_data->mRegex = pcre_compile(regex, 0 ,&err, &erro_ofs, NULL);
    object_data->mGlobal = global;
    object_data->mIgnoreCase = ignore_case;

    return obj;
}

