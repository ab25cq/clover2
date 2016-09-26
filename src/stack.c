#include "common.h"

sCLStack* gHeadStack;
CLVALUE* gGlobalStack;
CLVALUE* gGlobalStackPtr;
int gNumStackID;

static void create_global_stack_and_append_it_to_stack_list()
{
    gGlobalStack = MCALLOC(1, sizeof(CLVALUE)*256);
    gGlobalStackPtr = gGlobalStack;

    append_stack_to_stack_list(gGlobalStack, &gGlobalStackPtr);
}

void stack_init()
{
    gHeadStack = NULL;
    create_global_stack_and_append_it_to_stack_list();
    gNumStackID = 0;
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

long append_stack_to_stack_list(CLVALUE* stack_mem, CLVALUE** stack_ptr)
{
    sCLStack* stack = MCALLOC(1, sizeof(sCLStack));

    stack->mStack = stack_mem;
    stack->mStackPtr = stack_ptr;

    stack->mNextStack = gHeadStack;
    gHeadStack = stack;

    stack->mStackID = gNumStackID++;

    return stack->mStackID;
}

BOOL remove_stack_to_stack_list(CLVALUE* stack)
{
    sCLStack* it = gHeadStack;
    sCLStack* it_before = gHeadStack;

    while(it) {
        if(it->mStack == stack) {
            if(it_before == gHeadStack) {
                MFREE(it);
                gHeadStack = it->mNextStack;
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

BOOL check_variables_existance_on_stack(long stack_id)
{
    BOOL result = FALSE;
    sCLStack* it = gHeadStack;

    while(it) {
        if(it->mStackID == stack_id) {
            result = TRUE;
            break;
        }
        
        it = it->mNextStack;
    }

    return result;
}
