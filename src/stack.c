#include "common.h"

sCLStack* gHeadStack;

void create_global_stack_and_append_it_to_stack_list(sVMInfo* info)
{
    info->mSizeGlobalStack = GLOBAL_STACK_MAX;
    info->mGlobalStack = MCALLOC(1, sizeof(CLVALUE)*info->mSizeGlobalStack);
    info->mGlobalStackPtr = info->mGlobalStack;

    info->mGlobalStackID = append_stack_to_stack_list(info->mGlobalStack, &info->mGlobalStackPtr);
}

void free_global_stack(sVMInfo* info)
{
    remove_stack_to_stack_list(info->mGlobalStackID);
    MFREE(info->mGlobalStack);
}

void push_value_to_global_stack(CLVALUE value, sVMInfo* info)
{
    int num_global_stack = info->mGlobalStackPtr - info->mGlobalStack;
    if(num_global_stack >= info->mSizeGlobalStack-1) {
        int new_size = (info->mSizeGlobalStack + num_global_stack) * 2;
        info->mGlobalStack = MREALLOC(info->mGlobalStack, sizeof(CLVALUE)*new_size);

        info->mGlobalStackPtr = info->mGlobalStack + num_global_stack;

        sCLStack* it = gHeadStack;
        while(it) {
            if(it->mStackID == info->mGlobalStackID->mStackID) {
                it->mStack = info->mGlobalStack;
                it->mStackPtr = &info->mGlobalStackPtr;
                break;
            }

            it = it->mNextStack;
        }

        info->mSizeGlobalStack = new_size;
    }

    *info->mGlobalStackPtr = value;
    info->mGlobalStackPtr++;
}

void push_object_to_global_stack(CLObject obj, struct sVMInfoStruct* info)
{
    CLVALUE cl_value;
    cl_value.mObjectValue = obj;

    push_value_to_global_stack(cl_value, info);
}

CLVALUE pop_global_stack(sVMInfo* info)
{
    if(info->mGlobalStackPtr <= info->mGlobalStack) {
        fprintf(stderr, "Invalid global stack. abort\n");
        exit(2);
    }

    CLVALUE value = *(info->mGlobalStackPtr-1);
    info->mGlobalStackPtr--;

    return value;
}

void stack_init()
{
    gHeadStack = NULL;
}

void stack_final()
{
    sCLStack* it = gHeadStack;

    while(it) {
        sCLStack* next = it->mNextStack;
        MFREE(it);
        it = next;
    }
}


sCLStack* append_stack_to_stack_list(CLVALUE* stack_mem, CLVALUE** stack_ptr)
{
    sCLStack* stack = MCALLOC(1, sizeof(sCLStack));

    stack->mStack = stack_mem;
    stack->mStackPtr = stack_ptr;

    stack->mNextStack = gHeadStack;
    gHeadStack = stack;

    sCLStack* it = gHeadStack;
    int max = 0;

    while(it) {
        if(max < it->mStackID) {
            max = it->mStackID;
        }
        it = it->mNextStack;
    }

    stack->mStackID = max + 1;

    return stack;
}

BOOL remove_stack_to_stack_list(sCLStack* stack)
{
    sCLStack* it = gHeadStack;
    sCLStack* it_before = gHeadStack;

    while(it) {
        if(it->mStackID == stack->mStackID) {
            if(it == gHeadStack) {
                gHeadStack = it->mNextStack;
                MFREE(it);
            }
            else {
                it_before->mNextStack = it->mNextStack;
                MFREE(it);
            }

            return TRUE;
        }

        it_before = it;
        it = it->mNextStack;
    }

    return FALSE;
}

BOOL check_variables_existance_on_stack(CLVALUE* stack, CLVALUE* stack_ptr)
{
/*
    BOOL result = FALSE;
    sCLStack* it = gHeadStack;

    while(it) {
        if(it->mStack == stack && stack_ptr < (*it->mStackPtr)) {
            result = TRUE;
            break;
        }
        
        it = it->mNextStack;
    }

    return result;
*/
    return TRUE;
}

