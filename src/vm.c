#include "common.h"

#ifdef VM_DEBUG
static void show_stack(CLVALUE* stack, CLVALUE* stack_ptr)
{
    int i;
    for(i=0; i<5; i++) {
        if(stack_ptr-1 == stack + i) {
            printf("![%d] %d\n", i, stack[i].mIntValue);
        }
        else {
            printf("[%d] %d\n", i, stack[i].mIntValue);
        }
    }
}

static void show_inst(unsigned inst)
{
    switch(inst) {
        case OP_POP:
            puts("OP_POP");
            break;

        case OP_POP_N:
            puts("OP_POP_N");
            break;

        case OP_COND_JUMP:
            puts("OP_COND_JUMP");
            break;

        case OP_GOTO:
            puts("OP_GOTO");
            break;

        case OP_STORE:
            puts("OP_STORE");
            break;

        case OP_LOAD:
            puts("OP_LOAD");
            break;

        case OP_LDCINT:
            puts("OP_LDCINT");
            break;

        case OP_LDCNULL:
            puts("OP_LDCNULL");
            break;

        case OP_IADD:
            puts("OP_IADD");
            break;

        case OP_ISUB:
            puts("OP_ISUB");
            break;

        case OP_IEQ:
            puts("OP_IEQ");
            break;

        case OP_INOTEQ:
            puts("OP_INOTEQ");
            break;
    }
}

#endif

static void vm_mutex_on()
{
}

static void vm_mutex_off()
{
}

BOOL vm(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass)
{
    register char* pc = code->mCodes;

    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    while(pc - code->mCodes < code->mLen) {
        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);

#ifdef VM_DEBUG
show_inst(inst);
#endif

        switch(inst) {
            case OP_POP:
                vm_mutex_on();

                stack_ptr--;

                vm_mutex_off();
                break;

            case OP_POP_N:
                {
                    vm_mutex_on();
                    
                    int value = *(int*)pc;
                    pc += sizeof(int);
                    stack_ptr -= value;
                    
                    vm_mutex_off();
                }
                break;

            case OP_COND_JUMP:
                {
                    vm_mutex_on();

                    int jump_value = *(int*)pc;
                    pc += sizeof(int);

                    BOOL conditinal_value = (stack_ptr-1)->mBoolValue;
                    stack_ptr--;

                    if(conditinal_value) {
                        pc += jump_value;
                    }

                    vm_mutex_off();
                }
                break;

            case OP_GOTO:
                {
                    vm_mutex_on();

                    int jump_value = *(int*)pc;

                    pc = code->mCodes + jump_value;

                    vm_mutex_off();
                }
                break;

            case OP_STORE:
                {
                    vm_mutex_on();

                    int index = *(int*)pc;
                    pc += sizeof(int);

                    lvar[index] = *(stack_ptr-1);

                    vm_mutex_off();
                }
                break;

            case OP_LOAD:
                {
                    vm_mutex_on();

                    int index = *(int*)pc;
                    pc += sizeof(int);

                    *stack_ptr = lvar[index];
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCINT: 
                {
                    vm_mutex_on();

                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mIntValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCNULL:
                {
                    vm_mutex_on();

                    stack_ptr->mIntValue = 0;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IADD: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IEQ:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_INOTEQ:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;
        }
#ifdef VM_DEBUG
show_stack(stack, stack_ptr);
#endif
    }

    return TRUE;
}

