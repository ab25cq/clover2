#include "common.h"
#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifdef HAVE_PTHREAD_H
static pthread_mutex_t gVMMutex;
static pthread_cond_t gStartVMCond = PTHREAD_COND_INITIALIZER;

int gNumThread = 0;

#endif

pid_t gettid()
{
    return syscall(SYS_gettid);
}

void thread_init()
{
#ifdef HAVE_PTHREAD_H
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
//    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&gVMMutex, &attr);
#endif
}

void thread_final()
{
#ifdef HAVE_PTHREAD_H
    pthread_mutex_destroy(&gVMMutex);
#endif
}

BOOL gVMMutexFlg = FALSE;


void vm_mutex_on()
{
#ifdef HAVE_PTHREAD_H
    pthread_mutex_lock(&gVMMutex);
    gVMMutexFlg = TRUE;
#endif
}

void vm_mutex_off()
{
#ifdef HAVE_PTHREAD_H
    gVMMutexFlg = FALSE;
    pthread_mutex_unlock(&gVMMutex);
#endif
}

void new_vm_mutex()
{
}

struct sThreadFuncArg {
    sByteCode* code;
    sConst* constant;
    int block_var_num;
    int block_var_num2;
    CLVALUE* parent_stack;
    int parent_var_num;
    BOOL lambda;
    sVMInfo mVMInfo;
};

void* thread_func(void* param)
{
#ifdef HAVE_PTHREAD_H
    vm_mutex_on();

    struct sThreadFuncArg* arg = param;

    sByteCode* code = arg->code;
    sConst* constant = arg->constant;
    int block_var_num = arg->block_var_num;
    int block_var_num2 = arg->block_var_num2;
    CLVALUE* parent_stack = arg->parent_stack;
    int parent_var_num = arg->parent_var_num;
    BOOL lambda = arg->lambda;
    sVMInfo* info = &arg->mVMInfo;

    /// run block ///
    int num_params = 0;

    sCLClass* klass = get_class("Thread");

    int stack_size = CLOVER_STACK_SIZE;
    CLVALUE* new_stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);

    memset(new_stack, 0, sizeof(CLVALUE)*stack_size);

    sVMInfo new_info;
    memset(&new_info, 0, sizeof(sVMInfo));

    new_info = *info; // struct copy

    create_global_stack_and_append_it_to_stack_list(&new_info);

    new_info.running_thread = TRUE;
    new_info.running_class_name = MSTRDUP("Thread");
    new_info.running_method_name = MSTRDUP("thread_func");

    if(lambda) {
        int new_var_num = block_var_num;

        new_info.current_stack = new_stack;
        new_info.current_var_num = new_var_num;

        sCLClass klass2 = *klass;

        if(!vm(code, constant, new_stack, new_var_num, &klass2, &new_info)) {
            MFREE(arg);
            MFREE(new_stack);
            MFREE(new_info.running_class_name);
            MFREE(new_info.running_method_name);

            sConst_free(constant);
            sByteCode_free(code);

            MFREE(constant);
            MFREE(code);
            
            free_global_stack(&new_info);

            vm_mutex_off();

            pthread_exit((void*)1);
        }
    }
    else {
        int new_var_num = block_var_num2;

        new_info.current_stack = new_stack;
        new_info.current_var_num = new_var_num;

        /// copy variables ///
        memcpy(new_stack, parent_stack, sizeof(CLVALUE)*parent_var_num);

        sCLClass klass2 = *klass;

        if(!vm(code, constant, new_stack, new_var_num, &klass2, &new_info)) {
            MFREE(arg);
            MFREE(new_stack);
            MFREE(new_info.running_class_name);
            MFREE(new_info.running_method_name);

            sConst_free(constant);
            sByteCode_free(code);

            MFREE(constant);
            MFREE(code);
            
            free_global_stack(&new_info);

            vm_mutex_off();

            pthread_exit((void*)1);
        }
    }

    MFREE(new_info.running_class_name);
    MFREE(new_info.running_method_name);

    MFREE(arg);
    MFREE(new_stack);

    sConst_free(constant);
    sByteCode_free(code);

    MFREE(constant);
    MFREE(code);
    
    free_global_stack(&new_info);

    vm_mutex_off();
#endif

    return NULL;
}

BOOL Thread_initialize_thread(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* thread = lvar;
    CLVALUE* block = lvar + 1;

    //gNumThread++;

    /// Clover to C ///
    CLObject thread_object = thread->mObjectValue;
    CLObject block_object = block->mObjectValue;

    /// go ///
    struct sThreadFuncArg* arg = MCALLOC(1, sizeof(struct sThreadFuncArg));

    sBlockObject* object_data = CLBLOCK(block_object);

    sByteCode* code = MCALLOC(1, sizeof(sByteCode));
    sByteCode_clone(code, &object_data->mCodes);
    sConst* constant = MCALLOC(1, sizeof(sConst));
    sConst_clone(constant, &object_data->mConstant);

    arg->code = code;
    arg->constant = constant;
    arg->lambda = object_data->mLambda;
    arg->block_var_num = object_data->mBlockVarNum;
    arg->block_var_num2 = object_data->mBlockVarNum + object_data->mParentVarNum;
    arg->parent_stack = object_data->mParentStack;
    arg->parent_var_num = object_data->mParentVarNum;

    arg->mVMInfo = *info;

    sCLObject* object_data2 = CLOBJECT(thread_object);
    object_data2->mFields[1].mObjectValue = block_object;

    vm_mutex_off();

    pthread_t thread_id;
    if(pthread_create(&thread_id, NULL, thread_func, MANAGED arg) != 0) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_create failed");
        pthread_detach(thread_id);
        return FALSE;
    }

    vm_mutex_on();
    object_data2 = CLOBJECT(thread_object);
    object_data2->mFields[0].mULongValue = thread_id;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL Thread_pthread_join(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    CLVALUE* thread_id = lvar;

    /// Clover to C ///
    pthread_t thread_id_value = thread_id->mULongValue;

    vm_mutex_off();

    /// go ///
    void* retval_value = 0;
    int result = pthread_join(thread_id_value, &retval_value);

    if(result != 0 || retval_value == (void*)1) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "pthread_join failed");
        return FALSE;
    }

    vm_mutex_on();
    //gNumThread--;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL pthread_mutex_t_allocSize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    (*stack_ptr)->mULongValue = sizeof(pthread_mutex_t);
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}

BOOL pthread_cond_t_allocSize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
#ifdef HAVE_PTHREAD_H
    (*stack_ptr)->mULongValue = sizeof(pthread_cond_t);
    (*stack_ptr)++;

    return TRUE;
#else
    entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Thread is not supported. Please add --with-thread to configure option");

    return FALSE;
#endif
}
