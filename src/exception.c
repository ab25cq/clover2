#include "common.h"

void entry_exception_object_with_class_name(CLVALUE* stack, char* class_name, char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    fprintf(stderr, "%s\n", msg2);
/*

    vm_mutex_lock();

    klass = cl_get_class(class_name);

    if(klass == NULL) {
        fprintf(stderr, "unexpected error. abort on entry_exception_object_with_class_name. The class name is %s.\n", class_name);
        exit(2);
    }

    type1 = create_type_object(klass);

    (void)create_user_object(type1, &ovalue, 0, NULL, 0, info);

    info->stack_ptr->mObjectValue.mValue = ovalue;
    info->stack_ptr++;

    wcs = MMALLOC(sizeof(wchar_t)*(strlen(msg2)+1));
    (void)mbstowcs(wcs, msg2, strlen(msg2)+1);
    size = wcslen(wcs);

    ovalue2 = create_string_object(wcs, size, gStringTypeObject, info);

    CLUSEROBJECT(ovalue)->mFields[0].mObjectValue.mValue = ovalue2;

    MFREE(wcs);

    info->mRunningClassOnException = info->mRunningClass;
    info->mRunningMethodOnException = info->mRunningMethod;

    vm_mutex_unlock();
*/
}
