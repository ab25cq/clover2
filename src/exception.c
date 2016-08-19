#include "common.h"

void entry_exception_object_with_class_name(CLVALUE* stack, char* class_name, char* msg, ...)
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

    vm_mutex_off();
}

