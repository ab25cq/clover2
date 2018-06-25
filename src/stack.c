#include "common.h"

sCLStack* gHeadStack;
CLVALUE* gGlobalStack;
CLVALUE* gGlobalStackPtr;
int gSizeGlobalStack;

static void create_global_stack_and_append_it_to_stack_list()
{
    gSizeGlobalStack = GLOBAL_STACK_MAX;
    gGlobalStack = MCALLOC(1, sizeof(CLVALUE)*gSizeGlobalStack);
    gGlobalStackPtr = gGlobalStack;

    append_stack_to_stack_list(gGlobalStack, &gGlobalStackPtr);
}

void push_value_to_global_stack(CLVALUE value)
{
    int num_global_stack = gGlobalStackPtr - gGlobalStack;
    if(num_global_stack >= gSizeGlobalStack) {
        CLVALUE* global_stack = gGlobalStack;
        int new_size = num_global_stack * 2;
        gGlobalStack = MREALLOC(gGlobalStack, sizeof(CLVALUE)*new_size);
        memset(gGlobalStack + num_global_stack, 0 , new_size - num_global_stack);

        gGlobalStackPtr = gGlobalStack + num_global_stack;

        sCLStack* it = gHeadStack;
        while(it) {
            if(it->mStack == global_stack) {
                it->mStack = gGlobalStack;
                it->mStackPtr = &gGlobalStackPtr;
                break;
            }

            it = it->mNextStack;
        }

    }

    *gGlobalStackPtr = value;
    gGlobalStackPtr++;
}

CLVALUE pop_global_stack()
{
    if(gGlobalStackPtr <= gGlobalStack) {
        fprintf(stderr, "Invalid global stack. abort\n");
        exit(2);
    }

    CLVALUE value = *(gGlobalStackPtr-1);
    gGlobalStackPtr--;

    return value;
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

void is_ok_stack_list()
{
    sCLStack* it = gHeadStack;

    while(it) {
        it = it->mNextStack;
    }
}

void is_ok_stack_list2()
{
    sCLStack* it = gHeadStack;

    while(it) {
        it = it->mNextStack;
    }
}

void is_ok_stack_list3()
{
    sCLStack* it = gHeadStack;

    while(it) {
        it = it->mNextStack;
    }
}

void is_ok_stack_list5()
{
    sCLStack* it = gHeadStack;

    while(it) {
        it = it->mNextStack;
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

