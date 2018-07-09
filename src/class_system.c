#include "common.h"

#include <wchar.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <libgen.h>
#include <dirent.h>
#include <utime.h>
#include <fnmatch.h>
#include <signal.h>
#include <getopt.h>
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif
#include <sys/syscall.h>
#ifdef HAVE_BSD_H
#include <bsd/stdlib.h>
#endif
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>

#ifdef HAVE_NCURSESW_H
#include <ncurses.h>
#endif

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

    /// Clover2 to C ///
    CLObject str_value = str->mObjectValue;

    /// go ///
    sCLObject* str_data = CLOBJECT(str_value);

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

    vm_mutex_off();
    unsigned int result = sleep(time->mIntValue);
    vm_mutex_on();

    (*stack_ptr)->mUIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_pthread_mutex_init(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* mutex = lvar;
    CLVALUE* attr = lvar + 1;

    if(mutex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_mutex_t* mutex_value = (pthread_mutex_t*)&CLOBJECT(mutex->mObjectValue)->mHeadOfMemory;
    pthread_mutexattr_t* attr_value = (pthread_mutexattr_t*)&attr->mUIntValue;

    /// go ///
    int result = pthread_mutex_init(mutex_value, attr_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutex_lock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* mutex = lvar;

    if(mutex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_mutex_t* mutex_value = (pthread_mutex_t*)&CLOBJECT(mutex->mObjectValue)->mHeadOfMemory;

    /// go ///
    int result = pthread_mutex_lock(mutex_value);

    if(result != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_mutex_lock is failed");
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutex_unlock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* mutex = lvar;

    if(mutex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_mutex_t* mutex_value = (pthread_mutex_t*)&CLOBJECT(mutex->mObjectValue)->mHeadOfMemory;

    /// go ///
    int result = pthread_mutex_unlock(mutex_value);

    if(result != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_mutex_unlock is failed");
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutex_destroy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* mutex = lvar;

    if(mutex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_mutex_t* mutex_value = (pthread_mutex_t*)&CLOBJECT(mutex->mObjectValue)->mHeadOfMemory;

    /// go ///
    int result = pthread_mutex_destroy(mutex_value);

    if(result != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_mutex_destroy is failed");
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutex_trylock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* mutex = lvar;

    if(mutex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_mutex_t* mutex_value = (pthread_mutex_t*)&CLOBJECT(mutex->mObjectValue)->mHeadOfMemory;

    /// go ///
    int result = pthread_mutex_trylock(mutex_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutexattr_init(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* attr = lvar;

    /// Clover to C Value ///
    pthread_mutexattr_t* attr_value = (pthread_mutexattr_t*)&attr->mUIntValue;

    /// go ///
    (void)pthread_mutexattr_init(attr_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutexattr_settype(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* attr = lvar;
    CLVALUE* kind = lvar + 1;

    /// Clover to C Value ///
    pthread_mutexattr_t* attr_value = (pthread_mutexattr_t*)&attr->mUIntValue;
    int kind_value = kind->mIntValue;

    /// go ///
    int result = pthread_mutexattr_settype(attr_value, kind_value);

    if(result != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_mutexattr_settype is failed. Error num is %d", result);
        return FALSE;
    }

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutexattr_destroy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* attr = lvar;

    /// Clover to C Value ///
    pthread_mutexattr_t* attr_value = (pthread_mutexattr_t*)&attr->mUIntValue;

    /// go ///
    (void)pthread_mutexattr_destroy(attr_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_mutexattr_gettype(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* attr = lvar;
    CLVALUE* kind = lvar + 1;

    /// Clover to C Value ///
    pthread_mutexattr_t* attr_value = (pthread_mutexattr_t*)&attr->mUIntValue;
    int* kind_value = (int*)kind->mPointerValue;

    /// go ///
    (void)pthread_mutexattr_gettype(attr_value, kind_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_cond_init(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* cond = lvar;
    CLVALUE* cond_attr = lvar + 1;

    if(cond->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_cond_t* cond_value = (pthread_cond_t*)&CLOBJECT(cond->mObjectValue)->mHeadOfMemory;
    pthread_condattr_t* cond_attr_value = (pthread_condattr_t*)&cond_attr->mULongValue;

    /// go ///
    (void)pthread_cond_init(cond_value, cond_attr_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_cond_signal(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* cond = lvar;

    if(cond->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_cond_t* cond_value = (pthread_cond_t*)&CLOBJECT(cond->mObjectValue)->mHeadOfMemory;

    /// go ///
    (void)pthread_cond_signal(cond_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_cond_broadcast(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* cond = lvar;

    if(cond->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_cond_t* cond_value = (pthread_cond_t*)&CLOBJECT(cond->mObjectValue)->mHeadOfMemory;

    /// go ///
    (void)pthread_cond_broadcast(cond_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_cond_wait(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* cond = lvar;
    CLVALUE* mutex = lvar + 1;

    if(cond->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(mutex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_cond_t* cond_value = (pthread_cond_t*)&CLOBJECT(cond->mObjectValue)->mHeadOfMemory;
    pthread_mutex_t* mutex_value = (pthread_mutex_t*)&CLOBJECT(mutex->mObjectValue)->mHeadOfMemory;

    /// go ///
    (void)pthread_cond_wait(cond_value, mutex_value);

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_cond_timedwait(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* cond = lvar;
    CLVALUE* mutex = lvar + 1;
    CLVALUE* abtime = lvar + 2;

    if(cond->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(mutex->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(abtime->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_cond_t* cond_value = (pthread_cond_t*)&CLOBJECT(cond->mObjectValue)->mHeadOfMemory;
    pthread_mutex_t* mutex_value = (pthread_mutex_t*)&CLOBJECT(mutex->mObjectValue)->mHeadOfMemory;

    sCLObject* object_data = CLOBJECT(abtime->mObjectValue);
    struct timespec abtime_value;

    abtime_value.tv_sec = object_data->mFields[0].mULongValue;
    abtime_value.tv_nsec = object_data->mFields[1].mLongValue;

    /// go ///
    int result = pthread_cond_timedwait(cond_value, mutex_value, &abtime_value);

    if(result != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_cond_timedwait is failed. Error num is %d", result);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_pthread_cond_destroy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* cond = lvar;

    if(cond->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C Value ///
    pthread_cond_t* cond_value = (pthread_cond_t*)&CLOBJECT(cond->mObjectValue)->mHeadOfMemory;

    /// go ///
    int result = pthread_cond_destroy(cond_value);

    if(result != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_cond_destroy is failed. Error num is %d", result);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL System_initialize_thread_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    sCLClass* system = get_class("System");

    system->mClassFields[0].mValue.mIntValue = EINVAL;
    system->mClassFields[1].mValue.mIntValue = EDEADLK;
    system->mClassFields[2].mValue.mIntValue = EBUSY;
    system->mClassFields[3].mValue.mIntValue = EPERM;
    system->mClassFields[4].mValue.mIntValue = EBUSY;
    system->mClassFields[5].mValue.mIntValue = ETIMEDOUT;
    system->mClassFields[6].mValue.mIntValue = EINTR;
    system->mClassFields[7].mValue.mUIntValue = PTHREAD_MUTEX_RECURSIVE;
    system->mClassFields[8].mValue.mUIntValue = PTHREAD_MUTEX_ERRORCHECK;

#endif
#define LAST_INITIALIZE_FIELD_NUM_ON_THREAD_SYSTEM 9

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

                if(param == 0) {
                    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer Exception");
                    MFREE(buf.mBuf);
                    MFREE(format_string);
                    return FALSE;
                }

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
    CLVALUE* src = lvar;
    CLVALUE* size = lvar+1;

    /// clover variable to c variable ///
    char* src_value = src->mPointerValue;
    size_t size_value = size->mULongValue;
    wchar_t* wcs = MCALLOC(1, sizeof(wchar_t)*(size_value+1));

    char* src_value2 = MCALLOC(1, size_value+1);

    memcpy(src_value2, src_value, size_value);
    src_value2[size_value] = '\0';

    /// go ///
    int size_wcs = mbstowcs(wcs, src_value2, size_value);

    MFREE(src_value2);

    if(size_wcs < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "mbstowcs(3). Invalid multi byte string");
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

    MFREE(wcs);

    (*stack_ptr)->mObjectValue = object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_wcstombs(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* src = lvar;

    if(src->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// clover variable to c variable ///
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

    /// go ///
    int result = wcstombs(mbs, wcs, size);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "wcstombs(3) returns -1");
        MFREE(wcs);
        MFREE(mbs);
        return FALSE;
    }

    /// make result ///
    sCLClass* klass = get_class("byte");

    MASSERT(klass != NULL);

    CLObject object;
    object = create_array_object(klass, result+1);
    sCLObject* object_data2 = CLOBJECT(object);

    for(i=0; i<result; i++) {
        object_data2->mFields[i].mByteValue = mbs[i];
    }
    object_data2->mFields[i].mByteValue = '\0';

    MFREE(wcs);
    MFREE(mbs);

    (*stack_ptr)->mObjectValue = object;
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

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_THREAD_SYSTEM+0].mValue.mIntValue = MB_LEN_MAX;

#define LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM (LAST_INITIALIZE_FIELD_NUM_ON_THREAD_SYSTEM+1)

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

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+72].mValue.mPointerValue = (char*)stdin;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+73].mValue.mPointerValue = (char*)stdout;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+74].mValue.mPointerValue = (char*)stderr;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+75].mValue.mIntValue = BUFSIZ;

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+76].mValue.mIntValue = PATH_MAX;

#define LAST_INITIALIZE_FIELD_NUM_ON_FILE_SYSTEM (LAST_INITIALIZE_FIELD_NUM_ON_STRING_SYSTEM+77)

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

    size_t buffer_size = get_size_from_buffer_object(buf->mObjectValue);

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

    size_t buffer_size = get_size_from_buffer_object(buf->mObjectValue);

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

    //vm_mutex_off();

    /// go ///
    pid_t result = fork();

    if(result < 0) {
        //vm_mutex_on();
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fork(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    /// child process
    if(result == 0) {
        //vm_mutex_on();

        int num_params = 0;

        if(!invoke_block(block_value, info->current_stack, info->current_var_num, num_params, stack_ptr, info, FALSE)) 
        {
            //vm_mutex_off();
            return FALSE;
        }

        //vm_mutex_off();

        exit(0);
    }

    //vm_mutex_on();

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

    (*stack_ptr)->mBoolValue = result != 0;
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

    (*stack_ptr)->mBoolValue = result != 0;
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

    (*stack_ptr)->mBoolValue = result != 0;
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

    (*stack_ptr)->mBoolValue = result != 0;
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

    /// Clover to C value ///
    int fd_value = fd->mIntValue;

    CLObject terminfo_object;
    if(!create_termios_object(&terminfo_object, stack_ptr, lvar, info)) {
        return FALSE;
    }

    CLVALUE cl_value;
    cl_value.mObjectValue = terminfo_object;

    push_value_to_global_stack(cl_value);

    /// go ///
    struct termios terminfo_value;
    int result = tcgetattr(fd_value, &terminfo_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "tcgetattr(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        pop_global_stack();
        return FALSE;
    }

    /// C to Clover object ///
    c_termios_to_clover_termios(&terminfo_value, terminfo_object);

    (*stack_ptr)->mObjectValue = terminfo_object;
    (*stack_ptr)++;

    pop_global_stack();

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
    CLObject terminfo_object;
    if(!create_termios_object(&terminfo_object, stack_ptr, lvar, info)) {
        return FALSE;
    }

    /// go ///
    struct termios terminfo_value;
    cfmakeraw(&terminfo_value);

    /// C to Clover object ///
    c_termios_to_clover_termios(&terminfo_value, terminfo_object);

    (*stack_ptr)->mObjectValue = terminfo_object;
    (*stack_ptr)++;

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

/*
BOOL System_secure_getenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* name = lvar;

    if(name->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* name_value = ALLOC string_object_to_char_array(name->mObjectValue);

    /// go ///
    char* result = secure_getenv(name_value);

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
*/

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

    size_t buffer_size = get_size_from_buffer_object(buf->mObjectValue);

    /// check size ///
    if(size_value > buffer_size) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Buffer size is smaller than the size value of argument");
        return FALSE;
    }

    /// go ///
    size_t result = fwrite(buf_value, 1, size_value, stream_value);

    if(result < size_value) {
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

    size_t buffer_size = get_size_from_buffer_object(buf->mObjectValue);
    
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
    errno = 0;
    int result = fgetc(stream_value);
    
    if(errno != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fgetc(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_fgets(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
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

    /// Clover to C lang ///
    char* buf_value = (char*)get_pointer_from_buffer_object(buf->mObjectValue);
    size_t buffer_size = get_size_from_buffer_object(buf->mObjectValue);

    int size_value = (int)size->mIntValue;
    FILE* stream_value = (FILE*)stream->mPointerValue;

    /// check size ///
    if(size_value == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Buffer size is smaller than the size value of argument");
        return FALSE;
    }
    if(size_value > buffer_size) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Buffer size is smaller than the size value of argument");
        return FALSE;
    }

    /// go ///
    errno = 0;
    char* result = fgets(buf_value, size_value, stream_value);

    if(errno != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "fgets(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    if(result == NULL) {
        buf_value[0] = '\0';
        sCLObject* obj_data = CLOBJECT(buf->mObjectValue);
        obj_data->mFields[1].mULongValue = 0;
    }
    else {
        sCLObject* obj_data = CLOBJECT(buf->mObjectValue);
        obj_data->mFields[1].mULongValue = strlen(result);                // len
    }

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getchar(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    errno = 0;
    int result = getchar();
    
    if(errno != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "getchar(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_ungetc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;
    CLVALUE* stream = lvar + 1;

    /// Clover to c value ///
    if(stream->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    int c_value = c->mIntValue;
    FILE* stream_value = (FILE*)stream->mPointerValue;

    /// go ///
    int result = ungetc(c_value, stream_value);
    
    if(result == EOF) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "ungetc(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getcwd(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    char buf[PATH_MAX];

    char* result = getcwd(buf, PATH_MAX);
    
    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "getcwd(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    CLObject obj = create_string_object(buf);

    (*stack_ptr)->mObjectValue = obj;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getopt(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* optstring = lvar;
    CLVALUE* opterr_arg = lvar + 1;

    /// Clover to c value ///
    if(optstring->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* optstring_value = ALLOC string_object_to_char_array(optstring->mObjectValue);
    BOOL opterr_value = opterr_arg->mBoolValue;


    /// go ///
    opterr = opterr_value;
    int result_value = getopt(gARGC, gARGV, optstring_value);

    sCLClass* tuple_class = get_class("Tuple3");

    CLVALUE cl_value;
    CLObject result = create_object(tuple_class, "Tuple3<Integer,String,Integer>");
    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    CLObject result_object = create_integer(result_value);
    cl_value.mObjectValue = result_object;
    push_value_to_global_stack(cl_value);

    CLObject optarg_object;
    if(optarg) {
        optarg_object = create_string_object(optarg);
        cl_value.mObjectValue = optarg_object;
        push_value_to_global_stack(cl_value);
    }
    else {
        optarg_object = 0; // null
    }

    CLObject optind_object = create_integer(optind);
    cl_value.mObjectValue = optind_object;
    push_value_to_global_stack(cl_value);

    sCLObject* obj_data = CLOBJECT(result);
    obj_data->mFields[0].mIntValue = result_object;             // result
    obj_data->mFields[1].mObjectValue = optarg_object;          // optarg
    obj_data->mFields[2].mIntValue = optind_object;             // optind

    (*stack_ptr)->mObjectValue = result;
    (*stack_ptr)++;

    pop_global_stack();
    pop_global_stack();
    if(optarg) { pop_global_stack(); }
    pop_global_stack();

    MFREE(optstring_value);

    return TRUE;
}

BOOL System_getopt_long(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* optstring = lvar;
    CLVALUE* longopts = lvar + 1;
    CLVALUE* opterr_arg = lvar + 2;

    /// Clover to c value ///
    if(optstring->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(longopts->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* optstring_value = ALLOC string_object_to_char_array(optstring->mObjectValue);

    sCLObject* object_data = CLOBJECT(longopts->mObjectValue);

    int num_option = object_data->mArrayNum;
    struct option* longopts_value = MCALLOC(1, sizeof(struct option)*(num_option+1));

    int i;
    for(i=0; i<num_option; i++) {
        sCLObject* object_data2 = CLOBJECT(object_data->mFields[i].mObjectValue);

        CLObject name_object = object_data2->mFields[0].mObjectValue;

        longopts_value[i].name = ALLOC string_object_to_char_array(name_object);
        longopts_value[i].has_arg = object_data2->mFields[1].mIntValue;
        longopts_value[i].flag = (void*)object_data2->mFields[2].mPointerValue;
        longopts_value[i].val = object_data2->mFields[3].mIntValue;
    }
    longopts_value[i].name = 0;
    longopts_value[i].has_arg = 0;
    longopts_value[i].flag = 0;
    longopts_value[i].val = 0;

    BOOL opterr_value = opterr_arg->mBoolValue;

    /// go ///
    opterr = opterr_value;
    optarg = NULL;
    int longindex = 0;
    int result_value = getopt_long(gARGC, gARGV, optstring_value, longopts_value, &longindex);

    sCLClass* tuple_class = get_class("Tuple4");

    CLVALUE cl_value;
    CLObject result = create_object(tuple_class, "Tuple4<Integer,String,Integer,Integer>");
    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    CLObject result_object = create_integer(result_value);
    cl_value.mObjectValue = result_object;
    push_value_to_global_stack(cl_value);

    CLObject optarg_object;
    if(optarg) {
        optarg_object = create_string_object(optarg);
        cl_value.mObjectValue = optarg_object;
        push_value_to_global_stack(cl_value);
    }
    else {
        optarg_object = 0; // null
    }

    CLObject optind_object = create_integer(optind);
    cl_value.mObjectValue = optind_object;
    push_value_to_global_stack(cl_value);

    CLObject longindex_object = create_integer(longindex);
    cl_value.mObjectValue = longindex_object;
    push_value_to_global_stack(cl_value);

    sCLObject* obj_data = CLOBJECT(result);
    obj_data->mFields[0].mObjectValue = result_object;              // result
    obj_data->mFields[1].mObjectValue = optarg_object;              // optarg
    obj_data->mFields[2].mObjectValue = optind_object;              // optind
    obj_data->mFields[3].mObjectValue = longindex_object;           // longindex

    (*stack_ptr)->mObjectValue = result;
    (*stack_ptr)++;

    pop_global_stack();
    pop_global_stack();
    if(optarg) { pop_global_stack(); }
    pop_global_stack();
    pop_global_stack();

    MFREE(optstring_value);

    for(i=0; i<num_option; i++) {
        MFREE((char*)longopts_value[i].name);
    }

    MFREE(longopts_value);

    return TRUE;
}

BOOL System_getopt_long_only(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* optstring = lvar;
    CLVALUE* longopts = lvar + 1;
    CLVALUE* opterr_arg = lvar + 2;

    /// Clover to c value ///
    if(optstring->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(longopts->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    char* optstring_value = ALLOC string_object_to_char_array(optstring->mObjectValue);

    sCLObject* object_data = CLOBJECT(longopts->mObjectValue);

    int num_option = object_data->mArrayNum;
    struct option* longopts_value = MCALLOC(1, sizeof(struct option)*(num_option+1));

    int i;
    for(i=0; i<num_option; i++) {
        sCLObject* object_data2 = CLOBJECT(object_data->mFields[i].mObjectValue);

        CLObject name_object = object_data2->mFields[0].mObjectValue;

        longopts_value[i].name = ALLOC string_object_to_char_array(name_object);
        longopts_value[i].has_arg = object_data2->mFields[1].mIntValue;
        longopts_value[i].flag = (void*)object_data2->mFields[2].mPointerValue;
        longopts_value[i].val = object_data2->mFields[3].mIntValue;
    }
    longopts_value[i].name = 0;
    longopts_value[i].has_arg = 0;
    longopts_value[i].flag = 0;
    longopts_value[i].val = 0;

    BOOL opterr_value = opterr_arg->mBoolValue;

    /// go ///
    opterr = opterr_value;
    optarg = NULL;
    int longindex = 0;
    int result_value = getopt_long_only(gARGC, gARGV, optstring_value, longopts_value, &longindex);

    sCLClass* tuple_class = get_class("Tuple4");

    CLVALUE cl_value;
    CLObject result = create_object(tuple_class, "Tuple4<Integer,String,Integer,Integer>");
    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    CLObject result_object = create_integer(result_value);
    cl_value.mObjectValue = result_object;
    push_value_to_global_stack(cl_value);

    CLObject optarg_object;
    if(optarg) {
        optarg_object = create_string_object(optarg);
        cl_value.mObjectValue = optarg_object;
        push_value_to_global_stack(cl_value);
    }
    else {
        optarg_object = 0; // null
    }

    CLObject optind_object = create_integer(optind);
    cl_value.mObjectValue = optind_object;
    push_value_to_global_stack(cl_value);

    CLObject longindex_object = create_integer(longindex);
    cl_value.mObjectValue = longindex_object;
    push_value_to_global_stack(cl_value);

    sCLObject* obj_data = CLOBJECT(result);
    obj_data->mFields[0].mObjectValue = result_object;              // result
    obj_data->mFields[1].mObjectValue = optarg_object;              // optarg
    obj_data->mFields[2].mObjectValue = optind_object;              // optind
    obj_data->mFields[3].mObjectValue = longindex_object;           // longindex

    (*stack_ptr)->mObjectValue = result;
    (*stack_ptr)++;

    pop_global_stack();
    pop_global_stack();
    if(optarg) { pop_global_stack(); }
    pop_global_stack();
    pop_global_stack();

    MFREE(optstring_value);

    for(i=0; i<num_option; i++) {
        MFREE((char*)longopts_value[i].name);
    }

    MFREE(longopts_value);

    return TRUE;
}

BOOL System_getppid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    pid_t result = getppid();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_setsid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    pid_t result = setsid();

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "setsid(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getsid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* pid = lvar;

    /// Clover to c value ///
    pid_t pid_value = pid->mIntValue;

    /// Clover to C value ///
    pid_t result = getsid(pid_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "getsid(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_setpgrp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    pid_t result = setpgrp();

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "setpgrp(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_gettid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    pid_t result = gettid();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_initialize_system_calls_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+0].mValue.mIntValue = O_CLOEXEC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+1].mValue.mIntValue = no_argument;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+2].mValue.mIntValue = required_argument;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+3].mValue.mIntValue = optional_argument;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+4].mValue.mIntValue = _IONBF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+5].mValue.mIntValue = _IOLBF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+6].mValue.mIntValue = _IOFBF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+7].mValue.mPointerValue = (char*)SIG_IGN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+8].mValue.mPointerValue = (char*)SIG_DFL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+9].mValue.mIntValue = SIGHUP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+10].mValue.mIntValue = SIGINT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+11].mValue.mIntValue = SIGQUIT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+12].mValue.mIntValue = SIGILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+13].mValue.mIntValue = SIGTRAP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+14].mValue.mIntValue = SIGABRT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+15].mValue.mIntValue = SIGBUS;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+16].mValue.mIntValue = SIGFPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+17].mValue.mIntValue = SIGKILL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+18].mValue.mIntValue = SIGUSR1;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+19].mValue.mIntValue = SIGSEGV;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+20].mValue.mIntValue = SIGUSR2;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+21].mValue.mIntValue = SIGPIPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+22].mValue.mIntValue = SIGALRM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+23].mValue.mIntValue = SIGTERM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+24].mValue.mIntValue = SIGSTKFLT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+25].mValue.mIntValue = SIGCHLD;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+26].mValue.mIntValue = SIGCONT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+27].mValue.mIntValue = SIGSTOP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+28].mValue.mIntValue = SIGTSTP;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+29].mValue.mIntValue = SIGTTIN;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+30].mValue.mIntValue = SIGTTOU;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+31].mValue.mIntValue = SIGURG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+32].mValue.mIntValue = SIGXCPU;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+33].mValue.mIntValue = SIGXFSZ;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+34].mValue.mIntValue = SIGVTALRM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+35].mValue.mIntValue = SIGPROF;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+36].mValue.mIntValue = SIGWINCH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+37].mValue.mIntValue = SIGIO;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+38].mValue.mIntValue = SIGPWR;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+39].mValue.mIntValue = SIGSYS;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+40].mValue.mIntValue = FD_SETSIZE;

#ifdef IOCADDRT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+41].mValue.mIntValue = IOCADDRT;
#endif
#ifdef SIOCDELRT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+42].mValue.mIntValue = SIOCDELRT;
#endif
#ifdef SIOCRTMSG
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+43].mValue.mIntValue = SIOCRTMSG;
#endif
#ifdef SIOCGIFNAME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+44].mValue.mIntValue = SIOCGIFNAME;
#endif
#ifdef SIOCSIFLINK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+45].mValue.mIntValue = SIOCSIFLINK;
#endif
#ifdef SIOCGIFCONF
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+46].mValue.mIntValue = SIOCGIFCONF;
#endif
#ifdef SIOCGIFFLAGS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+47].mValue.mIntValue = SIOCGIFFLAGS;
#endif
#ifdef SIOCSIFFLAGS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+48].mValue.mIntValue = SIOCSIFFLAGS;
#endif
#ifdef SIOCGIFADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+49].mValue.mIntValue = SIOCGIFADDR;
#endif
#ifdef SIOCSIFADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+50].mValue.mIntValue = SIOCSIFADDR;
#endif
#ifdef SIOCGIFDSTADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+51].mValue.mIntValue = SIOCGIFDSTADDR;
#endif
#ifdef SIOCSIFDSTADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+52].mValue.mIntValue = SIOCSIFDSTADDR;
#endif
#ifdef SIOCGIFBRDADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+53].mValue.mIntValue = SIOCGIFBRDADDR;
#endif
#ifdef SIOCSIFBRDADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+54].mValue.mIntValue = SIOCSIFBRDADDR;
#endif
#ifdef SIOCGIFNETMASK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+55].mValue.mIntValue = SIOCGIFNETMASK;
#endif
#ifdef SIOCSIFNETMASK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+56].mValue.mIntValue = SIOCSIFNETMASK;
#endif
#ifdef SIOCGIFMETRIC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+57].mValue.mIntValue = SIOCGIFMETRIC;
#endif
#ifdef SIOCSIFMETRIC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+58].mValue.mIntValue = SIOCSIFMETRIC;
#endif
#ifdef SIOCGIFMEM
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+59].mValue.mIntValue = SIOCGIFMEM;
#endif
#ifdef SIOCSIFMEM
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+60].mValue.mIntValue = SIOCSIFMEM;
#endif
#ifdef SIOCGIFMTU
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+61].mValue.mIntValue = SIOCGIFMTU;
#endif
#ifdef SIOCSIFMTU
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+62].mValue.mIntValue = SIOCSIFMTU;
#endif
#ifdef SIOCSIFNAME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+63].mValue.mIntValue = SIOCSIFNAME;
#endif
#ifdef SIOCSIFHWADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+64].mValue.mIntValue = SIOCSIFHWADDR;
#endif
#ifdef SIOCGIFENCAP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+65].mValue.mIntValue = SIOCGIFENCAP;
#endif
#ifdef SIOCSIFENCAP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+66].mValue.mIntValue = SIOCSIFENCAP;
#endif
#ifdef SIOCGIFHWADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+67].mValue.mIntValue = SIOCGIFHWADDR;
#endif
#ifdef SIOCGIFSLAVE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+68].mValue.mIntValue = SIOCGIFSLAVE;
#endif
#ifdef SIOCSIFSLAVE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+69].mValue.mIntValue = SIOCSIFSLAVE;
#endif
#ifdef SIOCADDMULTI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+70].mValue.mIntValue = SIOCADDMULTI;
#endif
#ifdef SIOCDELMULTI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+71].mValue.mIntValue = SIOCDELMULTI;
#endif
#ifdef SIOCGIFINDEX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+72].mValue.mIntValue = SIOCGIFINDEX;
#endif
#ifdef SIOGIFINDEX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+73].mValue.mIntValue = SIOGIFINDEX;
#endif
#ifdef SIOCSIFPFLAGS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+74].mValue.mIntValue = SIOCSIFPFLAGS;
#endif
#ifdef SIOCGIFPFLAGS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+75].mValue.mIntValue = SIOCGIFPFLAGS;
#endif
#ifdef SIOCDIFADDR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+76].mValue.mIntValue = SIOCDIFADDR;
#endif
#ifdef SIOCSIFHWBROADCAST
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+77].mValue.mIntValue = SIOCSIFHWBROADCAST;
#endif
#ifdef SIOCGIFCOUNT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+78].mValue.mIntValue = SIOCGIFCOUNT;
#endif
#ifdef SIOCGIFBR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+79].mValue.mIntValue = SIOCGIFBR;
#endif
#ifdef SIOCSIFBR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+80].mValue.mIntValue = SIOCSIFBR;
#endif
#ifdef SIOCGIFTXQLEN
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+81].mValue.mIntValue = SIOCGIFTXQLEN;
#endif
#ifdef SIOCSIFTXQLEN
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+82].mValue.mIntValue = SIOCSIFTXQLEN;
#endif
#ifdef SIOCDARP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+83].mValue.mIntValue = SIOCDARP;
#endif
#ifdef SIOCGARP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+84].mValue.mIntValue = SIOCGARP;
#endif
#ifdef SIOCSARP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+85].mValue.mIntValue = SIOCSARP;
#endif
#ifdef SIOCDRARP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+86].mValue.mIntValue = SIOCDRARP;
#endif
#ifdef SIOCGRARP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+87].mValue.mIntValue = SIOCGRARP;
#endif
#ifdef SIOCSRARP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+88].mValue.mIntValue = SIOCSRARP;
#endif
#ifdef SIOCGIFMAP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+89].mValue.mIntValue = SIOCGIFMAP;
#endif
#ifdef SIOCSIFMAP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+90].mValue.mIntValue = SIOCSIFMAP;
#endif
#ifdef SIOCADDDLCI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+91].mValue.mIntValue = SIOCADDDLCI;
#endif
#ifdef SIOCDELDLCI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+92].mValue.mIntValue = SIOCDELDLCI;
#endif
#ifdef SIOCDEVPRIVATE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+93].mValue.mIntValue = SIOCDEVPRIVATE;
#endif
#ifdef SIOCPROTOPRIVATE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+94].mValue.mIntValue = SIOCPROTOPRIVATE;
#endif
#ifdef TIOCM_LE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+95].mValue.mIntValue = TIOCM_LE;
#endif
#ifdef TIOCM_DTR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+96].mValue.mIntValue = TIOCM_DTR;
#endif
#ifdef TIOCM_RTS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+97].mValue.mIntValue = TIOCM_RTS;
#endif
#ifdef TIOCM_ST
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+98].mValue.mIntValue = TIOCM_ST;
#endif
#ifdef TIOCM_SR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+99].mValue.mIntValue = TIOCM_SR;
#endif
#ifdef TIOCM_CTS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+100].mValue.mIntValue = TIOCM_CTS;
#endif
#ifdef TIOCM_CAR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+101].mValue.mIntValue = TIOCM_CAR;
#endif
#ifdef TIOCM_RNG
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+102].mValue.mIntValue = TIOCM_RNG;
#endif
#ifdef TIOCM_DSR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+103].mValue.mIntValue = TIOCM_DSR;
#endif
#ifdef TIOCM_CD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+104].mValue.mIntValue = TIOCM_CD;
#endif
#ifdef TIOCM_RI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+105].mValue.mIntValue = TIOCM_RI;
#endif
#ifdef N_TTY
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+106].mValue.mIntValue = N_TTY;
#endif
#ifdef N_SLIP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+107].mValue.mIntValue = N_SLIP;
#endif
#ifdef N_MOUSE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+108].mValue.mIntValue = N_MOUSE;
#endif
#ifdef N_PPP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+109].mValue.mIntValue = N_PPP;
#endif
#ifdef N_STRIP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+110].mValue.mIntValue = N_STRIP;
#endif
#ifdef N_AX25
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+111].mValue.mIntValue = N_AX25;
#endif
#ifdef N_X25
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+112].mValue.mIntValue = N_X25;
#endif
#ifdef N_6PACK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+113].mValue.mIntValue = N_6PACK;
#endif
#ifdef N_MASC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+114].mValue.mIntValue = N_MASC;
#endif
#ifdef N_R3964
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+115].mValue.mIntValue = N_R3964;
#endif
#ifdef N_PROFIBUS_FDL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+116].mValue.mIntValue = N_PROFIBUS_FDL;
#endif
#ifdef N_IRDA
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+117].mValue.mIntValue = N_IRDA;
#endif
#ifdef N_SMSBLOCK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+118].mValue.mIntValue = N_SMSBLOCK;
#endif
#ifdef N_HDLC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+119].mValue.mIntValue = N_HDLC;
#endif
#ifdef N_SYNC_PPP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+120].mValue.mIntValue = N_SYNC_PPP;
#endif
#ifdef N_HCI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+121].mValue.mIntValue = N_HCI;
#endif
#ifdef TCGETS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+122].mValue.mIntValue = TCGETS;
#endif
#ifdef TCSETS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+123].mValue.mIntValue = TCSETS;
#endif
#ifdef TCSETSW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+124].mValue.mIntValue = TCSETSW;
#endif
#ifdef TCSETSF
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+125].mValue.mIntValue = TCSETSF;
#endif
#ifdef TCGETA
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+126].mValue.mIntValue = TCGETA;
#endif
#ifdef TCSETA
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+127].mValue.mIntValue = TCSETA;
#endif
#ifdef TCSETAW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+128].mValue.mIntValue = TCSETAW;
#endif
#ifdef TCSETAF
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+129].mValue.mIntValue = TCSETAF;
#endif
#ifdef TCSBRK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+130].mValue.mIntValue = TCSBRK;
#endif
#ifdef TCXONC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+131].mValue.mIntValue = TCXONC;
#endif
#ifdef TCFLSH
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+132].mValue.mIntValue = TCFLSH;
#endif
#ifdef TIOCEXCL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+133].mValue.mIntValue = TIOCEXCL;
#endif
#ifdef TIOCNXCL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+134].mValue.mIntValue = TIOCNXCL;
#endif
#ifdef TIOCSCTTY
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+135].mValue.mIntValue = TIOCSCTTY;
#endif
#ifdef TIOCGPGRP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+136].mValue.mIntValue = TIOCGPGRP;
#endif
#ifdef TIOCSPGRP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+137].mValue.mIntValue = TIOCSPGRP;
#endif
#ifdef TIOCOUTQ
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+138].mValue.mIntValue = TIOCOUTQ;
#endif
#ifdef TIOCSTI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+139].mValue.mIntValue = TIOCSTI;
#endif
#ifdef TIOCGWINSZ
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+140].mValue.mIntValue = TIOCGWINSZ;
#endif
#ifdef TIOCSWINSZ
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+141].mValue.mIntValue = TIOCSWINSZ;
#endif
#ifdef TIOCMGET
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+142].mValue.mIntValue = TIOCMGET;
#endif
#ifdef TIOCMBIS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+143].mValue.mIntValue = TIOCMBIS;
#endif
#ifdef TIOCMBIC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+144].mValue.mIntValue = TIOCMBIC;
#endif
#ifdef TIOCMSET
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+145].mValue.mIntValue = TIOCMSET;
#endif
#ifdef TIOCGSOFTCAR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+146].mValue.mIntValue = TIOCGSOFTCAR;
#endif
#ifdef TIOCSSOFTCAR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+147].mValue.mIntValue = TIOCSSOFTCAR;
#endif
#ifdef FIONREAD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+148].mValue.mIntValue = FIONREAD;
#endif
#ifdef TIOCINQ
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+149].mValue.mIntValue = TIOCINQ;
#endif
#ifdef TIOCLINUX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+150].mValue.mIntValue = TIOCLINUX;
#endif
#ifdef TIOCCONS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+151].mValue.mIntValue = TIOCCONS;
#endif
#ifdef TIOCGSERIAL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+152].mValue.mIntValue = TIOCGSERIAL;
#endif
#ifdef TIOCSSERIAL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+153].mValue.mIntValue = TIOCSSERIAL;
#endif
#ifdef TIOCPKT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+154].mValue.mIntValue = TIOCPKT;
#endif
#ifdef FIONBIO
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+155].mValue.mIntValue = FIONBIO;
#endif
#ifdef TIOCNOTT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+156].mValue.mIntValue = TIOCNOTT;
#endif
#ifdef TIOCSET
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+157].mValue.mIntValue = TIOCSET;
#endif
#ifdef TIOCGETD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+158].mValue.mIntValue = TIOCGETD;
#endif
#ifdef TCSBRKP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+159].mValue.mIntValue = TCSBRKP;
#endif
#ifdef TIOCSBRK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+160].mValue.mIntValue = TIOCSBRK;
#endif
#ifdef TIOCCBRK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+161].mValue.mIntValue = TIOCCBRK;
#endif
#ifdef TIOCGSID
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+162].mValue.mIntValue = TIOCGSID;
#endif
#ifdef TIOCGRS485
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+163].mValue.mIntValue = TIOCGRS485;
#endif
#ifdef TIOCSRS485
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+164].mValue.mIntValue = TIOCSRS485;
#endif
#ifdef TIOCGPTN
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+165].mValue.mIntValue = TIOCGPTN;
#endif
#ifdef TIOCSPTLCK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+166].mValue.mIntValue = TIOCSPTLCK;
#endif
#ifdef TIOCGDEV
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+167].mValue.mIntValue = TIOCGDEV;
#endif
#ifdef TCGETX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+168].mValue.mIntValue = TCGETX;
#endif
#ifdef TCSETX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+169].mValue.mIntValue = TCSETX;
#endif
#ifdef TCSETXF
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+170].mValue.mIntValue = TCSETXF;
#endif
#ifdef TCSETXW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+171].mValue.mIntValue = TCSETXW;
#endif
#ifdef TIOCSIG
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+172].mValue.mIntValue = TIOCSIG;
#endif
#ifdef TIOCVHANGUP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+173].mValue.mIntValue = TIOCVHANGUP;
#endif
#ifdef TIOCGPKT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+174].mValue.mIntValue = TIOCGPKT;
#endif
#ifdef TIOCGPTLCK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+175].mValue.mIntValue = TIOCGPTLCK;
#endif
#ifdef TIOCGEXCL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+176].mValue.mIntValue = TIOCGEXCL;
#endif
#ifdef FIONCLEX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+177].mValue.mIntValue = FIONCLEX;
#endif
#ifdef FIOCLEX
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+178].mValue.mIntValue = FIOCLEX;
#endif
#ifdef FIOASYNC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+179].mValue.mIntValue = FIOASYNC;
#endif
#ifdef TIOCSERCONFIG
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+180].mValue.mIntValue = TIOCSERCONFIG;
#endif
#ifdef TIOCSERGWILD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+181].mValue.mIntValue = TIOCSERGWILD;
#endif
#ifdef TIOCSERSWILD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+182].mValue.mIntValue = TIOCSERSWILD;
#endif
#ifdef TIOCGLCKTRMIOS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+183].mValue.mIntValue = TIOCGLCKTRMIOS;
#endif
#ifdef TIOCSLCKTRMIOS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+184].mValue.mIntValue = TIOCSLCKTRMIOS;
#endif
#ifdef TIOCSERGSTRUCT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+185].mValue.mIntValue = TIOCSERGSTRUCT;
#endif
#ifdef TIOCSERGETLSR 
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+186].mValue.mIntValue = TIOCSERGETLSR ;
#endif
#ifdef TIOCSERGETMULTI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+187].mValue.mIntValue = TIOCSERGETMULTI;
#endif
#ifdef TIOCSERSETMULTI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+188].mValue.mIntValue = TIOCSERSETMULTI;
#endif
#ifdef TIOCMIWAIT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+189].mValue.mIntValue = TIOCMIWAIT;
#endif
#ifdef TIOCGICOUNT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+190].mValue.mIntValue = TIOCGICOUNT;
#endif
#ifdef FIOQSIZE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+191].mValue.mIntValue = FIOQSIZE;
#endif
#ifdef TIOCPKT_DATA
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+192].mValue.mIntValue = TIOCPKT_DATA;
#endif
#ifdef TIOCPKT_FLUSHREAD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+193].mValue.mIntValue = TIOCPKT_FLUSHREAD;
#endif
#ifdef TIOCPKT_FLUSHWRITE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+194].mValue.mIntValue = TIOCPKT_FLUSHWRITE;
#endif
#ifdef TIOCPKT_STOP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+195].mValue.mIntValue = TIOCPKT_STOP;
#endif
#ifdef TIOCPKT_START
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+196].mValue.mIntValue = TIOCPKT_START;
#endif
#ifdef TIOCPKT_NOSTOP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+197].mValue.mIntValue = TIOCPKT_NOSTOP;
#endif
#ifdef TIOCPKT_DOSTOP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+198].mValue.mIntValue = TIOCPKT_DOSTOP;
#endif
#ifdef TIOCPKT_IOCTL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+199].mValue.mIntValue = TIOCPKT_IOCTL;
#endif

#ifdef TIOCSER_TEMT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+200].mValue.mIntValue = TIOCSER_TEMT;
#endif

#ifdef ACS_BLOCK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+201].mValue.mIntValue = ACS_BLOCK;
#endif
#ifdef ACS_BOARD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+202].mValue.mIntValue = ACS_BOARD;
#endif
#ifdef ACS_BTEE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+203].mValue.mIntValue = ACS_BTEE;
#endif
#ifdef ACS_BULLET
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+204].mValue.mIntValue = ACS_BULLET;
#endif
#ifdef ACS_CKBOARD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+205].mValue.mIntValue = ACS_CKBOARD;
#endif
#ifdef ACS_DARROW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+206].mValue.mIntValue = ACS_DARROW;
#endif
#ifdef ACS_DEGREE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+207].mValue.mIntValue = ACS_DEGREE;
#endif
#ifdef ACS_DIAMOND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+208].mValue.mIntValue = ACS_DIAMOND;
#endif
#ifdef ACS_GEQUAL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+209].mValue.mIntValue = ACS_GEQUAL;
#endif
#ifdef ACS_HLINE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+210].mValue.mIntValue = ACS_HLINE;
#endif
#ifdef ACS_LANTERN
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+211].mValue.mIntValue = ACS_LANTERN;
#endif
#ifdef ACS_LARROW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+212].mValue.mIntValue = ACS_LARROW;
#endif
#ifdef ACS_LEQUAL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+213].mValue.mIntValue = ACS_LEQUAL;
#endif
#ifdef ACS_LLCORNER
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+214].mValue.mIntValue = ACS_LLCORNER;
#endif
#ifdef ACS_LRCORNER
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+215].mValue.mIntValue = ACS_LRCORNER;
#endif
#ifdef ACS_LTEE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+216].mValue.mIntValue = ACS_LTEE;
#endif
#ifdef ACS_NEQUAL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+217].mValue.mIntValue = ACS_NEQUAL;
#endif
#ifdef ACS_PI
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+218].mValue.mIntValue = ACS_PI;
#endif
#ifdef ACS_PLMINUS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+219].mValue.mIntValue = ACS_PLMINUS;
#endif
#ifdef ACS_PLUS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+220].mValue.mIntValue = ACS_PLUS;
#endif
#ifdef ACS_RARROW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+221].mValue.mIntValue = ACS_RARROW;
#endif
#ifdef ACS_RTEE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+222].mValue.mIntValue = ACS_RTEE;
#endif
#ifdef ACS_S1
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+223].mValue.mIntValue = ACS_S1;
#endif
#ifdef ACS_S3
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+224].mValue.mIntValue = ACS_S3;
#endif
#ifdef ACS_S7
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+225].mValue.mIntValue = ACS_S7;
#endif
#ifdef ACS_S9
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+226].mValue.mIntValue = ACS_S9;
#endif
#ifdef ACS_STERLING
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+227].mValue.mIntValue = ACS_STERLING;
#endif
#ifdef ACS_TTEE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+228].mValue.mIntValue = ACS_TTEE;
#endif
#ifdef ACS_UARROW
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+229].mValue.mIntValue = ACS_UARROW;
#endif
#ifdef ACS_ULCORNER
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+230].mValue.mIntValue = ACS_ULCORNER;
#endif
#ifdef ACS_URCORNER
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+231].mValue.mIntValue = ACS_URCORNER;
#endif
#ifdef ACS_VLINE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+232].mValue.mIntValue = ACS_VLINE;
#endif
#ifdef A_BLINK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+233].mValue.mIntValue = A_BLINK;
#endif
#ifdef A_BOLD
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+234].mValue.mIntValue = A_BOLD;
#endif
#ifdef A_DIM
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+235].mValue.mIntValue = A_DIM;
#endif
#ifdef A_REVERSE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+236].mValue.mIntValue = A_REVERSE;
#endif
#ifdef A_STANDOUT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+237].mValue.mIntValue = A_STANDOUT;
#endif
#ifdef A_UNDERLINE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+238].mValue.mIntValue = A_UNDERLINE;
#endif
#ifdef KEY_DOWN
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+239].mValue.mIntValue = KEY_DOWN;
#endif
#ifdef KEY_UP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+240].mValue.mIntValue = KEY_UP;
#endif
#ifdef KEY_LEFT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+241].mValue.mIntValue = KEY_LEFT;
#endif
#ifdef KEY_RIGHT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+242].mValue.mIntValue = KEY_RIGHT;
#endif
#ifdef KEY_HOME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+243].mValue.mIntValue = KEY_HOME;
#endif
#ifdef KEY_BACKSPACE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+244].mValue.mIntValue = KEY_BACKSPACE;
#endif
#ifdef KEY_DL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+245].mValue.mIntValue = KEY_DL;
#endif
#ifdef KEY_IL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+246].mValue.mIntValue = KEY_IL;
#endif
#ifdef KEY_DC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+247].mValue.mIntValue = KEY_DC;
#endif
#ifdef KEY_IC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+248].mValue.mIntValue = KEY_IC;
#endif
#ifdef KEY_EIC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+249].mValue.mIntValue = KEY_EIC;
#endif
#ifdef KEY_CLEAR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+250].mValue.mIntValue = KEY_CLEAR;
#endif
#ifdef KEY_EOS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+251].mValue.mIntValue = KEY_EOS;
#endif
#ifdef KEY_EOL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+252].mValue.mIntValue = KEY_EOL;
#endif
#ifdef KEY_SF
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+253].mValue.mIntValue = KEY_SF;
#endif
#ifdef KEY_SR
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+254].mValue.mIntValue = KEY_SR;
#endif
#ifdef KEY_NPAGE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+255].mValue.mIntValue = KEY_NPAGE;
#endif
#ifdef KEY_PPAGE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+256].mValue.mIntValue = KEY_PPAGE;
#endif
#ifdef KEY_STAB
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+257].mValue.mIntValue = KEY_STAB;
#endif
#ifdef KEY_CTAB
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+258].mValue.mIntValue = KEY_CTAB;
#endif
#ifdef KEY_CATAB
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+259].mValue.mIntValue = KEY_CATAB;
#endif
#ifdef KEY_ENTER
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+260].mValue.mIntValue = KEY_ENTER;
#endif
#ifdef KEY_PRINT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+261].mValue.mIntValue = KEY_PRINT;
#endif
#ifdef KEY_LL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+262].mValue.mIntValue = KEY_LL;
#endif
#ifdef KEY_A1
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+263].mValue.mIntValue = KEY_A1;
#endif
#ifdef KEY_A3
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+264].mValue.mIntValue = KEY_A3;
#endif
#ifdef KEY_B2
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+265].mValue.mIntValue = KEY_B2;
#endif
#ifdef KEY_C1
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+266].mValue.mIntValue = KEY_C1;
#endif
#ifdef KEY_C3
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+267].mValue.mIntValue = KEY_C3;
#endif
#ifdef KEY_BTAB
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+268].mValue.mIntValue = KEY_BTAB;
#endif
#ifdef KEY_BEG
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+269].mValue.mIntValue = KEY_BEG;
#endif
#ifdef KEY_CANCEL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+270].mValue.mIntValue = KEY_CANCEL;
#endif
#ifdef KEY_CLOSE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+271].mValue.mIntValue = KEY_CLOSE;
#endif
#ifdef KEY_COMMAND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+272].mValue.mIntValue = KEY_COMMAND;
#endif
#ifdef KEY_COPY
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+273].mValue.mIntValue = KEY_COPY;
#endif
#ifdef KEY_CREATE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+274].mValue.mIntValue = KEY_CREATE;
#endif
#ifdef KEY_END
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+275].mValue.mIntValue = KEY_END;
#endif
#ifdef KEY_EXIT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+276].mValue.mIntValue = KEY_EXIT;
#endif
#ifdef KEY_FIND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+277].mValue.mIntValue = KEY_FIND;
#endif
#ifdef KEY_HELP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+278].mValue.mIntValue = KEY_HELP;
#endif
#ifdef KEY_MARK
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+279].mValue.mIntValue = KEY_MARK;
#endif
#ifdef KEY_MESSAGE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+280].mValue.mIntValue = KEY_MESSAGE;
#endif
#ifdef KEY_MOVE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+281].mValue.mIntValue = KEY_MOVE;
#endif
#ifdef KEY_NEXT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+282].mValue.mIntValue = KEY_NEXT;
#endif
#ifdef KEY_OPEN
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+283].mValue.mIntValue = KEY_OPEN;
#endif
#ifdef KEY_OPTIONS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+284].mValue.mIntValue = KEY_OPTIONS;
#endif
#ifdef KEY_PREVIOUS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+285].mValue.mIntValue = KEY_PREVIOUS;
#endif
#ifdef KEY_REDO
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+286].mValue.mIntValue = KEY_REDO;
#endif
#ifdef KEY_REFERENCE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+287].mValue.mIntValue = KEY_REFERENCE;
#endif
#ifdef KEY_REFRESH
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+288].mValue.mIntValue = KEY_REFRESH;
#endif
#ifdef KEY_REPLACE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+289].mValue.mIntValue = KEY_REPLACE;
#endif
#ifdef KEY_RESTART
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+290].mValue.mIntValue = KEY_RESTART;
#endif
#ifdef KEY_RESUME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+291].mValue.mIntValue = KEY_RESUME;
#endif
#ifdef KEY_SAVE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+292].mValue.mIntValue = KEY_SAVE;
#endif
#ifdef KEY_SBEG
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+293].mValue.mIntValue = KEY_SBEG;
#endif
#ifdef KEY_SCANCEL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+294].mValue.mIntValue = KEY_SCANCEL;
#endif
#ifdef KEY_SCOMMAND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+295].mValue.mIntValue = KEY_SCOMMAND;
#endif
#ifdef KEY_SCOPY
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+296].mValue.mIntValue = KEY_SCOPY;
#endif
#ifdef KEY_SCREATE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+297].mValue.mIntValue = KEY_SCREATE;
#endif
#ifdef KEY_SDC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+298].mValue.mIntValue = KEY_SDC;
#endif
#ifdef KEY_SDL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+299].mValue.mIntValue = KEY_SDL;
#endif
#ifdef KEY_SELECT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+300].mValue.mIntValue = KEY_SELECT;
#endif
#ifdef KEY_SEND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+301].mValue.mIntValue = KEY_SEND;
#endif
#ifdef KEY_SEOL
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+302].mValue.mIntValue = KEY_SEOL;
#endif
#ifdef KEY_SEXIT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+303].mValue.mIntValue = KEY_SEXIT;
#endif
#ifdef KEY_SFIND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+304].mValue.mIntValue = KEY_SFIND;
#endif
#ifdef KEY_SHELP
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+305].mValue.mIntValue = KEY_SHELP;
#endif
#ifdef KEY_SHOME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+306].mValue.mIntValue = KEY_SHOME;
#endif
#ifdef KEY_SIC
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+307].mValue.mIntValue = KEY_SIC;
#endif
#ifdef KEY_SLEFT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+308].mValue.mIntValue = KEY_SLEFT;
#endif
#ifdef KEY_SMESSAGE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+309].mValue.mIntValue = KEY_SMESSAGE;
#endif
#ifdef KEY_SMOVE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+310].mValue.mIntValue = KEY_SMOVE;
#endif
#ifdef KEY_SNEXT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+311].mValue.mIntValue = KEY_SNEXT;
#endif
#ifdef KEY_SOPTIONS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+312].mValue.mIntValue = KEY_SOPTIONS;
#endif
#ifdef KEY_SPREVIOUS
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+313].mValue.mIntValue = KEY_SPREVIOUS;
#endif
#ifdef KEY_SPRINT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+314].mValue.mIntValue = KEY_SPRINT;
#endif
#ifdef KEY_SREDO
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+315].mValue.mIntValue = KEY_SREDO;
#endif
#ifdef KEY_SREPLACE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+316].mValue.mIntValue = KEY_SREPLACE;
#endif
#ifdef KEY_SRIGHT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+317].mValue.mIntValue = KEY_SRIGHT;
#endif
#ifdef KEY_SRSUME
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+318].mValue.mIntValue = KEY_SRSUME;
#endif
#ifdef KEY_SSAVE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+319].mValue.mIntValue = KEY_SSAVE;
#endif
#ifdef KEY_SSUSPEND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+320].mValue.mIntValue = KEY_SSUSPEND;
#endif
#ifdef KEY_SUNDO
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+321].mValue.mIntValue = KEY_SUNDO;
#endif
#ifdef KEY_SUSPEND
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+322].mValue.mIntValue = KEY_SUSPEND;
#endif
#ifdef KEY_UNDO
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+323].mValue.mIntValue = KEY_UNDO;
#endif
#ifdef KEY_MOUSE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+324].mValue.mIntValue = KEY_MOUSE;
#endif
#ifdef KEY_RESIZE
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+325].mValue.mIntValue = KEY_RESIZE;
#endif
#ifdef KEY_EVENT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+326].mValue.mIntValue = KEY_EVENT;
#endif
#ifdef KEY_EVENT
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+327].mValue.mIntValue = KEY_MAX;
#endif
    //system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+328].mValue.mPointerValue = (char*)stdscr;

#define LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS (LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+329)

    return TRUE;
}

BOOL System_popen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* command = lvar;
    CLVALUE* type = lvar+1;

    if(command->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    if(type->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    char* command_string = ALLOC string_object_to_char_array(command->mObjectValue);
    char* type_string = ALLOC string_object_to_char_array(type->mObjectValue);

    /// go ///
    FILE* result = popen(command_string, type_string);

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "popen(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        MFREE(command_string);
        MFREE(type_string);
        return FALSE;
    }

    MFREE(command_string);
    MFREE(type_string);

    (*stack_ptr)->mPointerValue = (void*)result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_pclose(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* stream = lvar;

    /// Clover to C ///
    FILE* stream_value = (FILE*)stream->mPointerValue;

    /// go ///
    int result = pclose(stream_value); // result code

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_initialize_cgi_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+0].mValue.mIntValue = LC_ALL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+1].mValue.mIntValue = LC_ADDRESS;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+2].mValue.mIntValue = LC_COLLATE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+3].mValue.mIntValue = LC_CTYPE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+4].mValue.mIntValue = LC_IDENTIFICATION;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+5].mValue.mIntValue = LC_MEASUREMENT;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+6].mValue.mIntValue = LC_MESSAGES;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+7].mValue.mIntValue = LC_MONETARY;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+8].mValue.mIntValue = LC_NAME;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+9].mValue.mIntValue = LC_NUMERIC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+10].mValue.mIntValue = LC_PAPER;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+11].mValue.mIntValue = LC_TELEPHONE;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+12].mValue.mIntValue = LC_TIME;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+13].mValue.mIntValue = LOCK_SH;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+14].mValue.mIntValue = LOCK_EX;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+15].mValue.mIntValue = LOCK_UN;

#define LAST_INITIALIZE_FIELD_NUM_ON_CGI (LAST_INITIALIZE_FIELD_NUM_ON_SYSTEM_CALLS+16)

    return TRUE;
}

BOOL System_setlocale(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* category = lvar;
    CLVALUE* locale = lvar+1;

    if(locale->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    int category_value = category->mIntValue;
    char* locale_value = ALLOC string_object_to_char_array(locale->mObjectValue);

    /// go ///
    char* result = setlocale(category_value, locale_value);

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "setlocale(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        MFREE(locale_value);
        return FALSE;
    }

    MFREE(locale_value);

    CLObject result_object = create_string_object(result);

    (*stack_ptr)->mObjectValue = result_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_flock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* operation = lvar+1;

    /// Clover to C ///
    int fd_value = fd->mIntValue;
    int operation_value = operation->mIntValue;

    /// go ///
    int result = flock(fd_value, operation_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "flock(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_fileno(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* stream = lvar;

    /// Clover to c value ///
    if(stream->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    FILE* stream_value = (FILE*)stream->mPointerValue;

    /// go ///
    int result = fileno(stream_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

#ifdef HAVE_BSD_H
BOOL System_getbsize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* headerlenp = lvar;
    CLVALUE* blocksizep = lvar + 1;

    /// Clover to c value ///
    if(headerlenp->mPointerValue == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }
    if(blocksizep->mPointerValue == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    int* headerlenp_value = (int*)headerlenp->mPointerValue;
    long* blocksizep_value = (long*)blocksizep->mPointerValue;

    /// go ///
    char* result = getbsize(headerlenp_value, blocksizep_value);

    CLObject obj = create_string_object(result);

    (*stack_ptr)->mObjectValue = obj;
    (*stack_ptr)++;

    return TRUE;
}
#endif

BOOL System_getuid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    uid_t result = getuid();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_geteuid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    uid_t result = geteuid();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getgid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    gid_t result = getgid();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getegid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    gid_t result = getegid();

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isatty(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;

    /// Clover to c value ///
    int fd_value = fd->mIntValue;

    /// go ///
    int result = isatty(fd_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_umask(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* mask = lvar;

    /// Clover to c value ///
    mode_t mask_value = (mode_t)mask->mIntValue;

    /// go ///
    mode_t result = umask(mask_value);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_usleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* usec = lvar;

    /// Clover to c value ///
    useconds_t usec_value = (useconds_t)usec->mIntValue;

    /// go ///
    vm_mutex_off();
    int result = usleep(usec_value);
    vm_mutex_on();

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "usleep(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_nanosleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* req = lvar;
    CLVALUE* rem = lvar + 1;

    /// Clover to c value ///
    struct timespec req_value;

    sCLObject* object_data = CLOBJECT(req->mObjectValue);

    req_value.tv_sec = object_data->mFields[0].mIntValue;
    req_value.tv_nsec = object_data->mFields[1].mLongValue;

    struct timespec rem_value;
    memset(&rem_value, 0, sizeof(struct timespec));

    /// go ///
    vm_mutex_off();
    int result = nanosleep(&req_value, &rem_value);
    vm_mutex_on();

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "nanosleep(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);

        if(rem->mObjectValue != 0) {
            sCLObject* object_data2 = CLOBJECT(rem->mObjectValue);

            object_data2->mFields[0].mIntValue = rem_value.tv_sec;
            object_data2->mFields[1].mLongValue = rem_value.tv_nsec;
        }
        return FALSE;
    }

    if(rem->mObjectValue != 0) {
        sCLObject* object_data2 = CLOBJECT(rem->mObjectValue);

        object_data2->mFields[0].mIntValue = rem_value.tv_sec;
        object_data2->mFields[1].mLongValue = rem_value.tv_nsec;
    }

    return TRUE;
}

BOOL System_putenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
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
    int result = putenv(str_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "putenv(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);

        MFREE(str_value);
        return FALSE;
    }

    //MFREE(str_value); comment out for putenv

    return TRUE;
}

BOOL System_setvbuf(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* stream = lvar;
    CLVALUE* buf = lvar + 1;
    CLVALUE* mode = lvar + 2;
    CLVALUE* size = lvar + 3;

    if(stream->mPointerValue == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    FILE* stream_value = (FILE*)stream->mPointerValue;
    char* buf_value = (char*)buf->mPointerValue;
    int mode_value = mode->mIntValue;
    size_t size_value = size->mULongValue;

    /// go ///
    int result = setvbuf(stream_value, buf_value, mode_value, size_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "setvbuf(3) is faield. The error is %s. The errnor is %d", strerror(errno), errno);

        return FALSE;
    }

    return TRUE;
}

BOOL System_strncat(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* dest = lvar;
    CLVALUE* src = lvar + 1;
    CLVALUE* size = lvar + 2;

    /// Clover to c value ///
    char* dest_value = (char*)dest->mPointerValue;
    char* src_value = (char*)src->mPointerValue;
    size_t size_value = size->mULongValue;

    /// go ///
    char* result = xstrncat(dest_value, src_value, size_value);

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_strchr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;
    CLVALUE* c = lvar + 1;

    /// Clover to c value ///
    char* str_value = (char*)str->mPointerValue;
    char c_value = c->mByteValue;

    /// go ///
    char* result = strchr(str_value, c_value);

    (*stack_ptr)->mPointerValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_initialize_socket_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* system = get_class("System");

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+0].mValue.mIntValue = AF_UNIX;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+1].mValue.mIntValue = AF_LOCAL;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+2].mValue.mIntValue = AF_INET;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+3].mValue.mIntValue = AF_INET6;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+4].mValue.mIntValue = AF_IPX;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+5].mValue.mIntValue = AF_NETLINK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+6].mValue.mIntValue = AF_X25;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+7].mValue.mIntValue = AF_AX25;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+8].mValue.mIntValue = AF_ATMPVC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+9].mValue.mIntValue = AF_APPLETALK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+10].mValue.mIntValue = AF_PACKET;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+11].mValue.mIntValue = AF_ALG;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+12].mValue.mIntValue = SOCK_STREAM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+13].mValue.mIntValue = SOCK_DGRAM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+14].mValue.mIntValue = SOCK_SEQPACKET;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+15].mValue.mIntValue = SOCK_RAW;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+16].mValue.mIntValue = SOCK_RDM;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+17].mValue.mIntValue = SOCK_PACKET;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+18].mValue.mIntValue = SOCK_NONBLOCK;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+19].mValue.mIntValue = SOCK_CLOEXEC;
    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_CGI+20].mValue.mIntValue = SOCK_STREAM;

#define LAST_INITIALIZE_FIELD_NUM_ON_SOCKET (LAST_INITIALIZE_FIELD_NUM_ON_CGI+21)

    return TRUE;
}

BOOL System_socket(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* domain = lvar;
    CLVALUE* type = (lvar+1);
    CLVALUE* protocol = (lvar+2);

    /// Clover to c value ///
    int domain_value = domain->mIntValue;
    int type_value = type->mIntValue;
    int protocol_value = protocol->mIntValue;

    /// go ///
    int result = socket(domain_value, type_value, protocol_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "socket(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_connect(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* sockfd = lvar;
    CLVALUE* addr = lvar+1;

    /// Clover to c value ///
    if(addr->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;

    }

    int sockfd_value = sockfd->mIntValue;
    CLObject addr_object = addr->mObjectValue;
    sCLObject* object_data = CLOBJECT(addr_object);

    struct sockaddr_un addr_value;

    memset(&addr_value, 0, sizeof(struct sockaddr_un));

    addr_value.sun_family = object_data->mFields[0].mIntValue;

    CLObject path_object = object_data->mFields[1].mObjectValue;

    char* path_value = ALLOC string_object_to_char_array(path_object);

    xstrncpy(addr_value.sun_path, path_value, sizeof(addr_value.sun_path));

    MFREE(path_value);

    socklen_t len_value = sizeof(addr_value);

    /// go ///
    int result = connect(sockfd_value, (struct sockaddr*)&addr_value, len_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "connect(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_bind(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* sockfd = lvar;
    CLVALUE* addr = lvar+1;

    /// Clover to c value ///
    if(addr->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;

    }

    int sockfd_value = sockfd->mIntValue;
    CLObject addr_object = addr->mObjectValue;
    sCLObject* object_data = CLOBJECT(addr_object);

    struct sockaddr_un addr_value;

    memset(&addr_value, 0, sizeof(struct sockaddr_un));

    addr_value.sun_family = object_data->mFields[0].mIntValue;

    CLObject path_object = object_data->mFields[1].mObjectValue;

    char* path_value = ALLOC string_object_to_char_array(path_object);

    xstrncpy(addr_value.sun_path, path_value, sizeof(addr_value.sun_path));

    MFREE(path_value);

    socklen_t len_value = sizeof(addr_value);

    /// go ///
    int result = bind(sockfd_value, (struct sockaddr*)&addr_value, len_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "bind(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_listen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* sockfd = lvar;
    CLVALUE* backlog = lvar+1;

    /// Clover to c value ///
    int sockfd_value = sockfd->mIntValue;
    int backlog_value = backlog->mIntValue;

    /// go ///
    int result = listen(sockfd_value, backlog_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "bind(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_accept(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* sockfd = lvar;
    CLVALUE* addr = lvar+1;

    /// Clover to c value ///
    int sockfd_value = sockfd->mIntValue;
    CLObject addr_object = addr->mObjectValue;

    struct sockaddr_un addr_value;
    socklen_t len_value;

    memset(&addr_value, 0, sizeof(struct sockaddr_un));

    /// go ///
    int result = accept(sockfd_value, (struct sockaddr*)&addr_value, &len_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "accept(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    sCLObject* object_data = CLOBJECT(addr_object);
    object_data->mFields[0].mIntValue = addr_value.sun_family;

    CLObject path_object = create_string_object(addr_value.sun_path);
    object_data = CLOBJECT(addr_object);
    object_data->mFields[1].mObjectValue = path_object;

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_inet_addr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* cp = lvar;

    /// Clover to c value ///
    if(cp->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    CLObject cp_object = cp->mObjectValue;
    char* cp_value = ALLOC string_object_to_char_array(cp_object);

    /// go ///
    in_addr_t result = inet_addr(cp_value);

    (*stack_ptr)->mUIntValue = result;
    (*stack_ptr)++;

    MFREE(cp_value);

    return TRUE;
}

BOOL System_connect2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* sockfd = lvar;
    CLVALUE* addr = lvar+1;

    /// Clover to c value ///
    if(addr->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;

    }

    int sockfd_value = sockfd->mIntValue;
    CLObject addr_object = addr->mObjectValue;
    sCLObject* object_data = CLOBJECT(addr_object);

    struct sockaddr_in addr_value;

    memset(&addr_value, 0, sizeof(struct sockaddr_in));

    addr_value.sin_family = object_data->mFields[0].mIntValue;

    CLObject sin_addr = object_data->mFields[1].mObjectValue;

    sCLObject* object_data2 = CLOBJECT(sin_addr);

    addr_value.sin_addr.s_addr = object_data2->mFields[0].mUIntValue;

    addr_value.sin_port = object_data->mFields[2].mIntValue;

    socklen_t len_value = sizeof(addr_value);

    /// go ///
    int result = connect(sockfd_value, (struct sockaddr*)&addr_value, len_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "connect(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

BOOL System_bind2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* sockfd = lvar;
    CLVALUE* addr = lvar+1;

    /// Clover to c value ///
    if(addr->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;

    }

    int sockfd_value = sockfd->mIntValue;
    CLObject addr_object = addr->mObjectValue;
    sCLObject* object_data = CLOBJECT(addr_object);

    struct sockaddr_in addr_value;

    memset(&addr_value, 0, sizeof(struct sockaddr_in));

    addr_value.sin_family = object_data->mFields[0].mIntValue;

    CLObject sin_addr = object_data->mFields[1].mObjectValue;

    sCLObject* object_data2 = CLOBJECT(sin_addr);

    addr_value.sin_addr.s_addr = object_data2->mFields[0].mUIntValue;

    addr_value.sin_port = object_data->mFields[2].mIntValue;

    socklen_t len_value = sizeof(addr_value);

    /// go ///
    int result = bind(sockfd_value, (struct sockaddr*)&addr_value, len_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "bind(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    return TRUE;
}

static CLObject create_string_array_from_ppchar_nullterminated(char** array) 
{
    CLObject result;

    int num_array = 0;
    char** p = array;
    while(*p) {
        num_array++;
        p++;
    }
    sCLClass* string_klass = get_class("String");

    result = create_array_object(string_klass, num_array);

    CLVALUE cl_value;
    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    int i;
    for(i=0; i < num_array; i++) {
        CLObject string_object = create_string_object(array[i]);

        cl_value.mObjectValue = result;
        push_value_to_global_stack(cl_value);

        sCLObject* object_data = CLOBJECT(result);
        object_data->mFields[i].mObjectValue = string_object;

        pop_global_stack();
    }

    pop_global_stack();

    return result;
}

static CLObject create_h_addr_list_array_from_ppchar_nullterminated(char** array) 
{
    CLObject result;

    int num_array = 0;
    char** p = array;
    while(*p) {
        num_array++;
        p++;
    }
    sCLClass* string_klass = get_class("String");

    result = create_array_object(string_klass, num_array);

    CLVALUE cl_value;
    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    int i;
    for(i=0; i < num_array; i++) {
        CLObject string_object = create_string_object(inet_ntoa(*(struct in_addr *)*(array + i)));

        cl_value.mObjectValue = result;
        push_value_to_global_stack(cl_value);

        sCLObject* object_data = CLOBJECT(result);
        object_data->mFields[i].mObjectValue = string_object;

        pop_global_stack();
    }

    pop_global_stack();

    return result;
}

static CLObject create_hostent_object(struct hostent* entry)
{
    sCLClass* klass = get_class_with_load_and_initialize("hostent");

    if(klass == NULL) {
        return 0;
    }

    CLObject result = create_object(klass, "hostent");

    CLVALUE cl_value;
    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    CLObject h_name_object = create_string_object(entry->h_name);

    cl_value.mObjectValue = h_name_object;
    push_value_to_global_stack(cl_value);

    sCLObject* object_data = CLOBJECT(result);

    object_data->mFields[0].mObjectValue = h_name_object;

    pop_global_stack();

    CLObject h_aliases = create_string_array_from_ppchar_nullterminated(entry->h_aliases);

    object_data = CLOBJECT(result);
    object_data->mFields[1].mObjectValue = h_aliases;
    object_data->mFields[2].mIntValue = entry->h_addrtype;
    object_data->mFields[3].mIntValue = entry->h_length;

    CLObject h_addr_list = create_h_addr_list_array_from_ppchar_nullterminated(entry->h_addr_list);
    object_data->mFields[4].mObjectValue = h_addr_list;

    pop_global_stack();

    return result;
}

BOOL System_gethostbyaddr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* addr = lvar;
    CLVALUE* len = lvar+1;
    CLVALUE* type = lvar+2;

    /// Clover to c value ///
    void* addr_value = addr->mPointerValue;
    size_t len_value = len->mULongValue;
    int type_value = type->mIntValue;

    /// go ///
    struct hostent* result = gethostbyaddr(addr_value, len_value, type_value);

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "gethostbyaddr(2) is faield. The errorno is %d", h_errno);
        return FALSE;
    }

    CLObject obj = create_hostent_object(result);

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "hostent class is not loaded");
        return FALSE;
    }

    (*stack_ptr)->mObjectValue = obj;
    (*stack_ptr)++;

    return TRUE;
}

static CLObject create_servent_object(struct servent* entry)
{
    sCLClass* klass = get_class_with_load_and_initialize("servent");

    if(klass == NULL) {
        return 0;
    }

    CLObject result = create_object(klass, "servent");

    CLVALUE cl_value;
    cl_value.mObjectValue = result;
    push_value_to_global_stack(cl_value);

    CLObject s_name_object = create_string_object(entry->s_name);

    cl_value.mObjectValue = s_name_object;
    push_value_to_global_stack(cl_value);

    sCLObject* object_data = CLOBJECT(result);

    object_data->mFields[0].mObjectValue = s_name_object;

    pop_global_stack();

    CLObject s_aliases = create_string_array_from_ppchar_nullterminated(entry->s_aliases);

    object_data = CLOBJECT(result);
    object_data->mFields[1].mObjectValue = s_aliases;
    object_data->mFields[2].mIntValue = entry->s_port;

    CLObject s_proto = create_string_object(entry->s_proto);

    cl_value.mObjectValue = s_proto;
    push_value_to_global_stack(cl_value);

    object_data = CLOBJECT(result);
    object_data->mFields[3].mObjectValue = s_proto;

    pop_global_stack();

    pop_global_stack();

    return result;
}

BOOL System_gethostbyname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* name = lvar;

    /// Clover to c value ///
    char* name_value = string_object_to_char_array(name->mObjectValue);

    /// go ///
    struct hostent* result = gethostbyname(name_value);

    MFREE(name_value);

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "gethostbyname(2) is faield. The errorno is %d", h_errno);
        return FALSE;
    }

    CLObject obj = create_hostent_object(result);

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "hostent class is not loaded");
        return FALSE;
    }

    (*stack_ptr)->mObjectValue = obj;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getservbyname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* name = lvar;
    CLVALUE* proto = lvar + 1;

    /// Clover to c value ///
    char* name_value = string_object_to_char_array(name->mObjectValue);
    char* proto_value = string_object_to_char_array(proto->mObjectValue);

    /// go ///
    struct servent* result = getservbyname(name_value, proto_value);

    MFREE(name_value);
    MFREE(proto_value);

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "getservbyname(2) is faield. The errorno is %d", h_errno);
        return FALSE;
    }

    CLObject obj = create_servent_object(result);

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "servent class is not loaded");
        return FALSE;
    }

    (*stack_ptr)->mObjectValue = obj;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getservbyport(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* port = lvar;
    CLVALUE* proto = lvar + 1;

    /// Clover to c value ///
    int port_value = port->mIntValue;
    char* proto_value = string_object_to_char_array(proto->mObjectValue);

    /// go ///
    struct servent* result = getservbyport(port_value, proto_value);

    MFREE(proto_value);

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "getservbyport(2) is faield. The errorno is %d", h_errno);
        return FALSE;
    }

    CLObject obj = create_servent_object(result);

    if(obj == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "servent class is not loaded");
        return FALSE;
    }

    (*stack_ptr)->mObjectValue = obj;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_inet_ntoa(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* in = lvar;

    /// Clover to c value ///
    CLObject in_object = in->mObjectValue;

    sCLObject* object_data = CLOBJECT(in_object);

    struct in_addr in_value;

    memset(&in_value, 0, sizeof(struct in_addr));

    in_value.s_addr = object_data->mFields[0].mUIntValue;

    /// go ///
    char* result = inet_ntoa(in_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "inet_ntoa(3) is faield.");
        return FALSE;
    }

    CLObject string_object = create_string_object(result);

    (*stack_ptr)->mObjectValue = string_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_gethostname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    char name[BUFSIZ];

    /// go ///
    int result = gethostname(name, BUFSIZ);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "gethostame(2) is faield");
        return FALSE;
    }

    CLObject string_object = create_string_object(name);

    (*stack_ptr)->mObjectValue = string_object;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_signal(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* signum = lvar;
    CLVALUE* handler = lvar+1;

    /// Clover to C ///
    int signum_value = signum->mIntValue;
    sighandler_t handler_value = (sighandler_t)handler->mPointerValue;

    /// go ///
    sighandler_t result = signal(signum_value, handler_value);

    if(result == SIG_ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "signal(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mPointerValue = (char*)result;
    (*stack_ptr)++;

    return TRUE;
}

CLObject signal_handler_object[SIGMAX];

void class_system_init()
{
    memset(signal_handler_object, 0, sizeof(CLObject)*SIGMAX);
}

void signal_user_handler(int signum)
{
    CLObject block = signal_handler_object[signum];

    if(block != 0) {
        sVMInfo info;

        memset(&info, 0, sizeof(sVMInfo));

        info.running_class_name = "signal";
        info.running_method_name = "signal_user_handler";

        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*CLOVER_STACK_SIZE);

        int var_num = 0;
        int num_params = 1;
        CLVALUE* p = stack + 1 + var_num;
        CLVALUE** stack_ptr = &p;

        stack->mIntValue = signum;

        (void)invoke_block(block, stack, var_num, num_params, stack_ptr, &info, FALSE);
    }
}

BOOL System_signal2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* signum = lvar;
    CLVALUE* handler = lvar+1;

    /// Clover to C ///
    int signum_value = signum->mIntValue;
    CLObject handler_object = handler->mObjectValue;
    
    sighandler_t handler_value = signal_user_handler;

    sBlockObject* object_data = CLBLOCK(handler_object);

    if(!object_data->mLambda) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "signal handler should be not closure but lambda");
        return FALSE;
    }

    /// go ///
    sighandler_t result = signal(signum_value, handler_value);

    if(result == SIG_ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "signal(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mObjectValue = signal_handler_object[signum_value];
    (*stack_ptr)++;

    signal_handler_object[signum_value] = handler_object;

    return TRUE;
}

BOOL fd_set_allocSize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    (*stack_ptr)->mULongValue = sizeof(fd_set);
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_FD_ZERO(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fdset = lvar;

    if(fdset->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// go ///
    fd_set fdset_value;
    FD_ZERO((fd_set*)&CLOBJECT(fdset->mObjectValue)->mHeadOfMemory);

    return TRUE;
}

BOOL System_FD_CLR(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* fdset = lvar + 1;

    if(fdset->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    int fd_value = fd->mIntValue;

    /// go ///
    FD_CLR(fd_value, (fd_set*)&CLOBJECT(fdset->mObjectValue)->mHeadOfMemory);

    return TRUE;
}

BOOL System_FD_SET(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* fdset = lvar + 1;

    if(fdset->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    int fd_value = fd->mIntValue;

    /// go ///
    FD_SET(fd_value, (fd_set*)&CLOBJECT(fdset->mObjectValue)->mHeadOfMemory);

    return TRUE;
}

BOOL System_FD_ISSET(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* fdset = lvar + 1;

    if(fdset->mPointerValue == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    int fd_value = fd->mIntValue;

    /// go ///
    int result = FD_ISSET(fd_value, (fd_set*)&CLOBJECT(fdset->mObjectValue)->mHeadOfMemory);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_select(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* nfds = lvar;
    CLVALUE* readfds = lvar+1;
    CLVALUE* writefds = lvar+2;
    CLVALUE* errorfds = lvar+3;
    CLVALUE* timeout = lvar+4;

    /// Clover to C ///
    int nfds_value = nfds->mIntValue;

    fd_set* readfds_value;
    if(readfds->mObjectValue == 0) {
        readfds_value = NULL;
    }
    else {
        readfds_value = (fd_set*)&CLOBJECT(readfds->mObjectValue)->mHeadOfMemory;
    }

    fd_set* writefds_value;
    if(writefds->mObjectValue == 0) {
        writefds_value = NULL;
    }
    else {
        writefds_value = (fd_set*)&CLOBJECT(writefds->mObjectValue)->mHeadOfMemory;
    }

    fd_set* errorfds_value;
    if(errorfds->mObjectValue == 0) {
        errorfds_value = NULL;
    }
    else {
        errorfds_value = (fd_set*)&CLOBJECT(errorfds->mObjectValue)->mHeadOfMemory;
    }

    struct timeval timeout_value;

    sCLObject* object_data = CLOBJECT(timeout->mObjectValue);

    timeout_value.tv_sec = object_data->mFields[0].mULongValue;
    timeout_value.tv_usec = object_data->mFields[1].mLongValue;

    /// go ///
    int result = select(nfds_value, readfds_value, writefds_value, errorfds_value, &timeout_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "select(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_ioctl(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* fd = lvar;
    CLVALUE* request = lvar+1;
    CLVALUE* arg = lvar+2;

    /// Clover to C ///
    int fd_value = fd->mIntValue;
    int request_value = request->mIntValue;
    void* arg_value = arg->mPointerValue;

    /// go ///
    int result = ioctl(fd_value, request_value, arg_value);

    if(result < 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "ioctl(2) is faield. The error is %s. The errnor is %d", strerror(errno), errno);
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

#ifdef HAVE_NCURSESW_H

BOOL System_initscr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    WINDOW* result = initscr();

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "initscr(3) is error.");
        return FALSE;
    }

    sCLClass* system = get_class("System");

    system->mClassFields[LAST_INITIALIZE_FIELD_NUM_ON_COMMAND_SYSTEM+328].mValue.mPointerValue = (char*)stdscr;

    (*stack_ptr)->mPointerValue = (char*)result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_endwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    int result = endwin();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "endwin(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_move(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* y = lvar;
    CLVALUE* x = lvar+1;

    /// Clover to C ///
    int y_value = y->mIntValue;
    int x_value = x->mIntValue;

    /// go ///
    int result = move(y_value, x_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "move(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_printw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* str = lvar;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    char* str_value = string_object_to_char_array(str->mObjectValue);

    int result = printw(str_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "printw(3) is error. str is (%s)", str_value);
        MFREE(str_value);
        return FALSE;
    }

    MFREE(str_value);

    return TRUE;
}

BOOL System_refresh(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    int result = refresh();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "refresh(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_box(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* win_ptr = lvar;
    CLVALUE* vetical_char = lvar + 1;
    CLVALUE* horizonal_char = lvar + 2;

    /// Clover to C ///
    WINDOW* win_ptr_value = (WINDOW*)win_ptr->mPointerValue;
    chtype vetical_char_value = (chtype)vetical_char->mCharValue;
    chtype horizonal_char_value = (chtype)horizonal_char->mCharValue;
    
    /// go ///
    int result = box(win_ptr_value, vetical_char_value, horizonal_char_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "box(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_isendwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    int result = isendwin();

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_clear(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = clear();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "clear(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_attron(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* attribute = lvar;

    /// Clover to C ///
    chtype attribute_value = attribute->mIntValue;
    
    /// go ///
    int result = attron(attribute_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "attron(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_attroff(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* attribute = lvar;

    /// Clover to C ///
    chtype attribute_value = attribute->mIntValue;
    
    /// go ///
    int result = attroff(attribute_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "attroff(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_attrset(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* attribute = lvar;

    /// Clover to C ///
    chtype attribute_value = attribute->mIntValue;
    
    /// go ///
    int result = attrset(attribute_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "attrset(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_echo(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = echo();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "echo(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_noecho(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = noecho();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "noecho(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_cbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = cbreak();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "cbreak(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_nocbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = nocbreak();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "nocbreak(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_raw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = raw();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "raw(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_noraw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = noraw();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "noraw(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_getch(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    /// go ///
    int result = getch();

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "getch(3) is error.");
        return FALSE;
    }

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_newwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* num_of_lines = lvar;
    CLVALUE* num_of_cols = lvar + 1;
    CLVALUE* start_y = lvar + 2;
    CLVALUE* start_x = lvar + 3;

    /// Clover to C ///
    int num_of_lines_value = num_of_lines->mIntValue;
    int num_of_cols_value = num_of_cols->mIntValue;
    int start_y_value = start_y->mIntValue;
    int start_x_value = start_x->mIntValue;

    /// go ///
    WINDOW* result = newwin(num_of_lines_value, num_of_cols_value, start_y_value, start_x_value);

    if(result == NULL) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "newwin(3) is error.");
        return FALSE;
    }

    (*stack_ptr)->mPointerValue = (char*)result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_delwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window_to_delete = lvar;

    /// Clover to C ///
    WINDOW* window_to_delete_value = (WINDOW*)window_to_delete->mPointerValue;

    /// go ///
    int result = delwin(window_to_delete_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "delwin(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_mvwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window_to_move = lvar;
    CLVALUE* new_y = lvar + 1;
    CLVALUE* new_x = lvar + 2;

    /// Clover to C ///
    WINDOW* window_to_move_value = (WINDOW*)window_to_move->mPointerValue;
    int new_y_value = new_y->mIntValue;
    int new_x_value = new_x->mIntValue;

    /// go ///
    int result = mvwin(window_to_move_value, new_y_value, new_x_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "mvwin(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_wrefresh(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window_to_ptr = lvar;

    /// Clover to C ///
    WINDOW* window_to_ptr_value = (WINDOW*)window_to_ptr->mPointerValue;

    /// go ///
    int result = wrefresh(window_to_ptr_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "wrefresh(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_wclear(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window_to_ptr = lvar;

    /// Clover to C ///
    WINDOW* window_to_ptr_value = (WINDOW*)window_to_ptr->mPointerValue;

    /// go ///
    int result = wclear(window_to_ptr_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "wclear(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_touchwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window_to_ptr = lvar;

    /// Clover to C ///
    WINDOW* window_to_ptr_value = (WINDOW*)window_to_ptr->mPointerValue;

    /// go ///
    int result = touchwin(window_to_ptr_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "touchwin(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_keypad(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window = lvar;
    CLVALUE* keypad_on = lvar + 1;

    /// Clover to C ///
    WINDOW* window_value = (WINDOW*)window->mPointerValue;
    BOOL keypad_on_value = keypad_on->mBoolValue;

    /// go ///
    int result = keypad(window_value, keypad_on_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "keypad(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_wmove(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window = lvar;
    CLVALUE* y = lvar + 1;
    CLVALUE* x = lvar + 1;

    /// Clover to C ///
    WINDOW* window_value = (WINDOW*)window->mPointerValue;
    int y_value = y->mIntValue;
    int x_value = x->mIntValue;

    /// go ///
    int result = wmove(window_value, y_value, x_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "wmove(3) is error.");
        return FALSE;
    }

    return TRUE;
}

BOOL System_wprintw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* window = lvar;
    CLVALUE* str = lvar + 1;

    if(str->mObjectValue == 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to C ///
    WINDOW* window_value = (WINDOW*)window->mPointerValue;
    char* str_value = string_object_to_char_array(str->mObjectValue);

    int result = wprintw(window_value, str_value);

    if(result == ERR) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "wprintw(3) is error.");
        MFREE(str_value);
        return FALSE;
    }

    MFREE(str_value);

    return TRUE;
}

BOOL System_getmaxx(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    int result = getmaxx(stdscr);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_getmaxy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    int result = getmaxy(stdscr);

    (*stack_ptr)->mIntValue = result;
    (*stack_ptr)++;

    return TRUE;
}

#else

BOOL System_initscr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_endwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_move(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_printw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_refresh(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_box(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_isendwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_clear(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_attron(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_attroff(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_attrset(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_echo(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_noecho(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_cbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_nocbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_raw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_noraw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_getch(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_newwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_delwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_mvwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_wrefresh(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_wclear(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_touchwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_keypad(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_wmove(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_wprintw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_getmaxx(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

BOOL System_getmaxy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "This method is not implemented. Requiring cursesw library ");
    return FALSE;
}

#endif

BOOL System_isalpha(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isalpha((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isalnum(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isalnum((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_iscntrl(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = iscntrl((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isdigit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isdigit((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isgraph(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isgraph((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_islower(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = islower((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isprint(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isprint((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_ispunct(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = ispunct((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isspace(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isspace((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isupper(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isupper((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isxdigit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isxdigit((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isascii(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isascii((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}

BOOL System_isblank(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* c = lvar;

    /// Clover to C ///
    wchar_t c_value = c->mCharValue;

    /// go ///
    int result = isblank((char)c_value);

    (*stack_ptr)->mBoolValue = result != 0;
    (*stack_ptr)++;

    return TRUE;
}
