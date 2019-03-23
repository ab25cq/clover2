#include "common.h"

sCLStack* gHeadStack;

void create_global_stack_and_append_it_to_stack_list(sVMInfo* info)
{
    info->mSizeGlobalStack = GLOBAL_STACK_MAX;
    info->mGlobalStack = MCALLOC(1, sizeof(CLVALUE)*info->mSizeGlobalStack);
    info->mGlobalStackPtr = info->mGlobalStack;

    info->mGlobalStackID = append_stack_to_stack_list(info->mGlobalStack, &info->mGlobalStackPtr, TRUE);

    info->mTmpSizeGlobalStack = GLOBAL_STACK_MAX;
    info->mTmpGlobalStack = MCALLOC(1, sizeof(CLVALUE)*info->mTmpSizeGlobalStack);
    info->mTmpGlobalStackPtr = info->mTmpGlobalStack;

    info->mTmpGlobalStackID = append_stack_to_stack_list(info->mTmpGlobalStack, &info->mTmpGlobalStackPtr, FALSE);
}

void free_global_stack(sVMInfo* info)
{
    MFREE(info->mGlobalStack);
    remove_stack_to_stack_list(info->mGlobalStackID);

    MFREE(info->mTmpGlobalStack);
    remove_stack_to_stack_list(info->mTmpGlobalStackID);
}

void push_value_to_global_stack(CLVALUE value, sVMInfo* info)
{
    int num_global_stack = info->mTmpGlobalStackPtr - info->mTmpGlobalStack;
    if(num_global_stack >= info->mTmpSizeGlobalStack-1) {
        int new_size = (info->mTmpSizeGlobalStack + num_global_stack) * 2;
        info->mTmpGlobalStack = MREALLOC(info->mTmpGlobalStack, sizeof(CLVALUE)*new_size);

        info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_global_stack;

        sCLStack* it = gHeadStack;
        while(it) {
            if(it == info->mTmpGlobalStackID) {
                it->mStack = info->mTmpGlobalStack;
                it->mStackPtr = &info->mTmpGlobalStackPtr;
                break;
            }

            it = it->mNextStack;
        }

        info->mTmpSizeGlobalStack = new_size;
    }

    *info->mTmpGlobalStackPtr = value;
    info->mTmpGlobalStackPtr++;
}

void push_object_to_global_stack(CLObject obj, struct sVMInfoStruct* info)
{
    int num_global_stack = info->mGlobalStackPtr - info->mGlobalStack;
    if(num_global_stack >= info->mSizeGlobalStack-1) {
        int new_size = (info->mSizeGlobalStack + num_global_stack) * 2;
        info->mGlobalStack = MREALLOC(info->mGlobalStack, sizeof(CLVALUE)*new_size);

        info->mGlobalStackPtr = info->mGlobalStack + num_global_stack;

        sCLStack* it = gHeadStack;
        while(it) {
            if(it == info->mGlobalStackID) {
                it->mStack = info->mGlobalStack;
                it->mStackPtr = &info->mGlobalStackPtr;
                break;
            }

            it = it->mNextStack;
        }

        info->mSizeGlobalStack = new_size;
    }

    info->mGlobalStackPtr->mObjectValue = obj;
    info->mGlobalStackPtr++;
}

CLVALUE pop_global_stack(sVMInfo* info)
{
    if(info->mTmpGlobalStackPtr <= info->mTmpGlobalStack) {
        fprintf(stderr, "Invalid global stack. abort\n");
        exit(2);
    }

    CLVALUE value = *(info->mTmpGlobalStackPtr-1);
    info->mTmpGlobalStackPtr--;

    return value;
}

#define NUM_STACK_MAX 256

static sCLStack gCLStacks[NUM_STACK_MAX];

void stack_init()
{
    gHeadStack = NULL;

    memset(gCLStacks, 0, sizeof(sCLStack)*NUM_STACK_MAX);
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

sCLStack* append_stack_to_stack_list(CLVALUE* stack_mem, CLVALUE** stack_ptr, BOOL global)
{
    sCLStack* stack = MCALLOC(1, sizeof(sCLStack));

    stack->mStack = stack_mem;
    stack->mStackPtr = stack_ptr;

    stack->mGlobalStack = global;

    stack->mNextStack = gHeadStack;
    gHeadStack = stack;

    sCLStack* it2 = gHeadStack;
    int max = 0;

    while(it2) {
        if(max < it2->mStackID) {
            max = it2->mStackID;
        }
        it2 = it2->mNextStack;
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

/*
sCLStack* append_stack_to_stack_list(CLVALUE* stack_mem, CLVALUE** stack_ptr)
{
    sCLStack* stack = MCALLOC(1, sizeof(sCLStack));

    stack->mStack = stack_mem;
    stack->mStackPtr = stack_ptr;

    stack->mNextStack = gHeadStack;
    gHeadStack = stack;

    return stack;
}

BOOL remove_stack_to_stack_list(sCLStack* stack)
{
    sCLStack* it = gHeadStack;
    sCLStack* it_before = gHeadStack;

    while(it) {
        if(it == stack) {
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
*/

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

