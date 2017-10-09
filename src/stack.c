#include "common.h"

sCLStack* gHeadStack;
CLVALUE* gGlobalStack;
CLVALUE* gGlobalStackPtr;

static void create_global_stack_and_append_it_to_stack_list()
{
    gGlobalStack = MCALLOC(1, sizeof(CLVALUE)*GLOBAL_STACK_MAX);
    gGlobalStackPtr = gGlobalStack;

    append_stack_to_stack_list(gGlobalStack, &gGlobalStackPtr);
}

void stack_init()
{
    gHeadStack = NULL;
    create_global_stack_and_append_it_to_stack_list();
}

void stack_final()
{
    sCLStack* it = gHeadStack;

    while(it) {
        sCLStack* next = it->mNextStack;
        MFREE(it);
        it = next;
    }
    MFREE(gGlobalStack);
}

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

