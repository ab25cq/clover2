#include "common.h"

void entry_exception_object_with_class_name(CLVALUE* stack, sVMInfo* info, char* class_name, char* msg, ...)
{
    vm_mutex_on();

    sCLClass* klass = get_class(class_name);

    if(klass == NULL) {
        fprintf(stderr, "unexpected error. abort on entry_exception_object_with_class_name. The class name is %s.\n", class_name);
        exit(2);
    }

    CLObject object = create_object(klass);

    stack->mObjectValue = object;

    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    CLObject str = create_string_object(msg2);

    sCLObject* object_data = CLOBJECT(object);

    object_data->mFields[0].mObjectValue = str;

    xstrncpy(info->exception_message, msg2, EXCEPTION_MESSAGE_MAX); // for show_exception_message 

    vm_mutex_off();
}

void entry_exception_object(CLObject exception, sVMInfo* info)
{
    sCLObject* object_data = CLOBJECT(exception);

    CLObject message = object_data->mFields[0].mObjectValue;

    char* str = ALLOC string_object_to_char_array(message);

    xstrncpy(info->exception_message, str, EXCEPTION_MESSAGE_MAX); // for show_exception_message 

    MFREE(str);
}

void show_exception_message(char* message)
{
    fprintf(stderr, "%s\n", message);

/*
    vm_mutex_on();

    sCLObject* object_data = CLOBJECT(exception);
    CLObject string_object = object_data->mFields[0].mObjectValue;

    sCLObject* object_data2 = CLOBJECT(string_object);

    CLObject wchar_array = object_data2->mFields[0].mObjectValue;

    sCLObject* object_data3 = CLOBJECT(wchar_array);

    wchar_t* wstr = MCALLOC(1, sizeof(wchar_t)*(object_data3->mArrayNum+1));

    int i;
    for(i=0; i<object_data3->mArrayNum; i++) {
        wstr[i] = object_data3->mFields[i].mCharValue;
    }
    wstr[i] = '\0';

    fprintf(stderr, "%s: %ls\n", CLASS_NAME(object_data->mClass), wstr);

    MFREE(wstr);

    vm_mutex_off();
*/
}
