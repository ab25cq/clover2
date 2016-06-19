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
        case OP_POP :
            puts("OP_POP");
            break;

        case OP_POP_N :
            puts("OP_POP_N");
            break;

        case OP_COND_JUMP :
            puts("OP_COND_JUMP");
            break;

        case OP_GOTO :
            puts("OP_GOTO");
            break;

        case OP_RETURN :
            puts("OP_RETURN");
            break;

        case OP_STORE :
            puts("OP_STORE");
            break;

        case OP_LOAD :
            puts("OP_LOAD");
            break;

        case OP_LDCBYTE :
            puts("OP_LDCBYTE");
            break;

        case OP_LDCUBYTE :
            puts("OP_LDCUBYTE");
            break;

        case OP_LDCSHORT :
            puts("OP_LDCSHORT");
            break;

        case OP_LDCUSHORT :
            puts("OP_LDCUSHORT");
            break;

        case OP_LDCINT :
            puts("OP_LDCINT");
            break;

        case OP_LDCUINT :
            puts("OP_LDCUINT");
            break;

        case OP_LDCLONG :
            puts("OP_LDCLONG");
            break;

        case OP_LDCULONG :
            puts("OP_LDCULONG");
            break;

        case OP_LDCNULL :
            puts("OP_LDCNULL");
            break;

        case OP_BADD :
            puts("OP_BADD");
            break;

        case OP_UBADD :
            puts("OP_UBADD");
            break;

        case OP_SADD :
            puts("OP_SADD");
            break;

        case OP_USADD :
            puts("OP_USADD");
            break;

        case OP_IADD :
            puts("OP_IADD");
            break;

        case OP_UIADD :
            puts("OP_UIADD");
            break;

        case OP_LADD :
            puts("OP_LADD");
            break;

        case OP_ULADD :
            puts("OP_ULADD");
            break;

        case OP_FADD :
            puts("OP_FADD");
            break;

        case OP_DADD :
            puts("OP_DADD");
            break;

        case OP_PADD :
            puts("OP_PADD");
            break;

        case OP_BSUB :
            puts("OP_BSUB");
            break;

        case OP_UBSUB :
            puts("OP_UBSUB");
            break;

        case OP_SSUB :
            puts("OP_SSUB");
            break;

        case OP_USSUB :
            puts("OP_USSUB");
            break;

        case OP_ISUB :
            puts("OP_ISUB");
            break;

        case OP_UISUB :
            puts("OP_UISUB");
            break;

        case OP_LSUB :
            puts("OP_LSUB");
            break;

        case OP_ULSUB :
            puts("OP_ULSUB");
            break;

        case OP_FSUB :
            puts("OP_FSUB");
            break;

        case OP_DSUB :
            puts("OP_DSUB");
            break;

        case OP_PSUB :
            puts("OP_PSUB");
            break;

        case OP_IEQ :
            puts("OP_IEQ");
            break;

        case OP_INOTEQ :
            puts("OP_INOTEQ");
            break;

        case OP_ANDAND:
            puts("OP_ANDAND");
            break;

        case OP_OROR:
            puts("OP_OROR");
            break;

        case OP_INVOKE_METHOD :
            puts("OP_INVOKE_METHOD");
            break;

        case OP_NEW :
            puts("OP_NEW");
            break;

        case OP_LOAD_FIELD:
            puts("OP_LOAD_FIELD");
            break;

        case OP_STORE_FIELD:
            puts("OP_STORE_FIELD");
            break;

        case OP_LOAD_CLASS_FIELD:
            puts("OP_LOAD_CLASS_FIELD");
            break;

        case OP_STORE_CLASS_FIELD:
            puts("OP_STORE_CLASS_FIELD");
            break;

        case OP_STORE_VALUE_TO_INT_ADDRESS:
            puts("OP_STORE_VALUE_TO_INT_ADDRESS");
            break;

        case OP_STORE_VALUE_TO_UINT_ADDRESS: 
            puts("OP_STORE_VALUE_TO_UINT_ADDRESS:");
            break;

        case OP_STORE_VALUE_TO_BYTE_ADDRESS: 
            puts("OP_STORE_VALUE_TO_BYTE_ADDRESS:");
            break;

        case OP_STORE_VALUE_TO_UBYTE_ADDRESS: 
            puts("OP_STORE_VALUE_TO_UBYTE_ADDRESS:");
            break;

        case OP_STORE_VALUE_TO_SHORT_ADDRESS: 
            puts("OP_STORE_VALUE_TO_SHORT_ADDRESS:");
            break;

        case OP_STORE_VALUE_TO_USHORT_ADDRESS: 
            puts("OP_STORE_VALUE_TO_USHORT_ADDRESS:");
            break;

        case OP_STORE_VALUE_TO_LONG_ADDRESS: 
            puts("OP_STORE_VALUE_TO_LONG_ADDRESS:");
            break;

        default:
            printf("inst %d\n", inst);
            break;
    }
}

#endif

void vm_mutex_on()
{
}

void vm_mutex_off()
{
}

static BOOL invoke_method(sCLClass* klass, sCLMethod* method, CLVALUE* stack, CLVALUE** stack_ptr, sVMInfo* info)
{
    if(method->mFlags & METHOD_FLAGS_NATIVE) {
        CLVALUE* lvar = *stack_ptr - method->mNumParams;

        if(method->uCode.mNativeMethod == NULL) {
            entry_exception_object_with_class_name(stack, "MethodNotFoundException", "method not found");
            return FALSE;
        }

        if(!method->uCode.mNativeMethod(stack_ptr, lvar, info)) {
            return FALSE;
        }

        if(is_void_type(method->mResultType, klass)) {
            (*stack_ptr)->mIntValue = 0;
            (*stack_ptr)++;
        }
        else {
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            **stack_ptr = result;
            (*stack_ptr)++;
        }
    }
    else {
        int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);
        CLVALUE* lvar = *stack_ptr - real_param_num;

        sByteCode* code = &method->uCode.mByteCodes;
        sConst* constant = &klass->mConst;
        CLVALUE* stack = lvar;
        int var_num = method->mVarNum;

        if(!vm(code, constant, stack, var_num, klass, info)) {
            return FALSE;
        }
        
        *stack_ptr = lvar;      // see OP_RETURN
        **stack_ptr = *stack;
        (*stack_ptr)++;
    }

    return TRUE;
}

static BOOL initialize_class(sCLClass* klass)
{
    if(klass->mInitializeMethodIndex != -1) {
        sCLMethod* initialize_method = klass->mMethods + klass->mInitializeMethodIndex;

        const int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
        CLVALUE* stack_ptr = stack;

        sVMInfo info;
        memset(&info, 0, sizeof(sVMInfo));

        if(!invoke_method(klass, initialize_method, stack, &stack_ptr, &info)) {
            MFREE(stack);
            return FALSE;
        }

        MFREE(stack);
    }

    return TRUE;
}

sCLClass* get_class_with_load_and_initialize(char* class_name)
{
    sCLClass* result = get_class(class_name);
    
    if(result == NULL) {
        result = load_class(class_name);

        if(!initialize_class(result)) {
            return NULL;
        }
    }

    return result;
}

BOOL vm(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sVMInfo* info)
{
    register char* pc = code->mCodes;

    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    append_stack_to_stack_list(stack, &stack_ptr);

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

            case OP_RETURN:
                *stack = *(stack_ptr-1);
                remove_stack_to_stack_list(stack);
                return TRUE;

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

            case OP_LDCBYTE: 
                {
                    vm_mutex_on();

                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mByteValue = (char)value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCUBYTE: 
                {
                    vm_mutex_on();

                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mUByteValue = (unsigned char)value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCSHORT: 
                {
                    vm_mutex_on();

                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mShortValue = (short)value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCUSHORT: 
                {
                    vm_mutex_on();

                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mUShortValue = (unsigned short)value;
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

            case OP_LDCUINT: 
                {
                    vm_mutex_on();

                    unsigned int value = *(unsigned int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mUIntValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCLONG: 
                {
                    vm_mutex_on();

                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    long lvalue;

                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                    stack_ptr->mLongValue = lvalue;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCULONG: 
                {
                    vm_mutex_on();

                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    unsigned long lvalue;

                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                    stack_ptr->mULongValue = lvalue;
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

            case OP_BADD:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBADD:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SADD:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USADD:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
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

            case OP_UIADD: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LADD: 
                {
                    vm_mutex_on();

                    long left = (stack_ptr-2)->mLongValue;
                    long right = (stack_ptr-1)->mLongValue;

                    long result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULADD: 
                {
                    vm_mutex_on();

                    unsigned long left = (stack_ptr-2)->mULongValue;
                    unsigned long right = (stack_ptr-1)->mULongValue;

                    unsigned long result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PADD: 
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    int right = (stack_ptr-1)->mIntValue;

                    char* result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mPointerValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PSUB: 
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    int right = (stack_ptr-1)->mIntValue;

                    char* result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mPointerValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BEQ:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBEQ:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SEQ:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USEQ:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
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

            case OP_UIEQ:
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LEQ:
                {
                    vm_mutex_on();

                    long left = (stack_ptr-2)->mLongValue;
                    long right = (stack_ptr-1)->mLongValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULEQ:
                {
                    vm_mutex_on();

                    unsigned long left = (stack_ptr-2)->mULongValue;
                    unsigned long right = (stack_ptr-1)->mULongValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_FEQ:
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DEQ:
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BNOTEQ:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_UBNOTEQ:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_SNOTEQ:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_USNOTEQ:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mShortValue;
                    unsigned short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
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

            case OP_UINOTEQ:
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_LNOTEQ:
                {
                    vm_mutex_on();

                    long left = (stack_ptr-2)->mLongValue;
                    long right = (stack_ptr-1)->mLongValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_ULNOTEQ:
                {
                    vm_mutex_on();

                    unsigned long left = (stack_ptr-2)->mULongValue;
                    unsigned long right = (stack_ptr-1)->mULongValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_FNOTEQ:
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_DNOTEQ:
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;


            case OP_ANDAND:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mBoolValue;
                    int right = (stack_ptr-1)->mBoolValue;

                    BOOL result = left && right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_OROR:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mBoolValue;
                    int right = (stack_ptr-1)->mBoolValue;

                    BOOL result = left || right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_INVOKE_METHOD:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int method_index = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "ClassNotFoundException", "class not found");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    if(method_index < 0 || method_index >= klass->mNumMethods) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "Exception", "Calling method index is invalid");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    sCLMethod* method = klass->mMethods + method_index;

                    if(!invoke_method(klass, method, stack, &stack_ptr, info)) {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    vm_mutex_off();
                }
                break;

            case OP_NEW:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "ClassNotFoundException", "class not found");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    CLObject obj = create_object(klass);
                    stack_ptr->mObjectValue = obj;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_FIELD:
                {
                    vm_mutex_on();

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -1)->mObjectValue;
                    stack_ptr--;

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "ClassNotFoundException", "class not found");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    CLVALUE value = object_pointer->mFields[field_index];
                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_FIELD:
                {
                    vm_mutex_on();

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -2)->mObjectValue;
                    CLVALUE value = *(stack_ptr-1);

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "ClassNotFoundException", "class not found");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    object_pointer->mFields[field_index] = value;
                    stack_ptr-=2;
                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_CLASS_FIELD:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "ClassNotFoundException", "class not found");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    sCLField* field = klass->mClassFields + field_index;

                    *stack_ptr = field->mValue;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_CLASS_FIELD:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "ClassNotFoundException", "class not found");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(stack, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack);
                        return FALSE;
                    }

                    CLVALUE value = *(stack_ptr-1);

                    sCLField* field = klass->mClassFields + field_index;
                    field->mValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_INT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(int*)address.mPointerValue = value.mIntValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_UINT_ADDRESS: 
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(unsigned int*)address.mPointerValue = value.mUIntValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_BYTE_ADDRESS: 
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(char*)address.mPointerValue = value.mByteValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_UBYTE_ADDRESS: 
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(unsigned char*)address.mPointerValue = value.mUByteValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_SHORT_ADDRESS: 
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(short*)address.mPointerValue = value.mShortValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_USHORT_ADDRESS: 
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(unsigned short*)address.mPointerValue = value.mUShortValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_LONG_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(long*)address.mPointerValue = value.mLongValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_ULONG_ADDRESS: 
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(unsigned long*)address.mPointerValue = value.mULongValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_INT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    int value = *(int*)address.mPointerValue;

                    stack_ptr->mIntValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_UINT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned int value = *(unsigned  int*)address.mPointerValue;

                    stack_ptr->mUIntValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_BYTE_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    char value = *(char*)address.mPointerValue;

                    stack_ptr->mByteValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_UBYTE_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned char value = *(unsigned char*)address.mPointerValue;

                    stack_ptr->mUByteValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_SHORT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    short value = *(short*)address.mPointerValue;

                    stack_ptr->mShortValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_USHORT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned short value = *(unsigned short*)address.mPointerValue;

                    stack_ptr->mUShortValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_LONG_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    long value = *(long*)address.mPointerValue;

                    stack_ptr->mLongValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_ULONG_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned long value = *(unsigned long*)address.mPointerValue;

                    stack_ptr->mULongValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;
        }
#ifdef VM_DEBUG
show_stack(stack, stack_ptr);
#endif
    }

    remove_stack_to_stack_list(stack);

    return TRUE;
}
