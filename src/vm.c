#include "common.h"

BOOL gSigInt = FALSE;

void show_stack(CLVALUE* stack, CLVALUE* stack_ptr, CLVALUE* lvar, int var_num)
{
    if(lvar == NULL) {
        lvar = stack + var_num;
    }

    if(stack_ptr == lvar+var_num) {
        puts("stack is empty");
    }

    if(stack_ptr < stack) {
        puts("stack is invalid. abort.");
        exit(3);
    }

    int i;
    for(i=0; i<30; i++) {
        if(stack + i < stack_ptr) {
            if(stack_ptr == stack + i) {
                printf("![%d] %d on %p\n", i, stack[i].mIntValue, stack + i);
            }
            else {
                printf("[%d] %d on %p\n", i, stack[i].mIntValue, stack + i);
            }
        }
    }
}

#ifdef VM_LOG
static void show_inst(unsigned inst)
{
    switch(inst) {
        case OP_POP :
            puts("OP_POP");
            break;

        case OP_POP_N :
            puts("OP_POP_N");
            break;

        case OP_REVERSE:
            puts("OP_REVERSE");
            break;

        case OP_DUPE:
            puts("OP_DUPE");
            break;

        case OP_COND_JUMP :
            puts("OP_COND_JUMP");
            break;

        case OP_COND_NOT_JUMP :
            puts("OP_COND_NOT_JUMP");
            break;

        case OP_GOTO :
            puts("OP_GOTO");
            break;

        case OP_LABEL :
            puts("OP_LABEL");
            break;

        case OP_RETURN :
            puts("OP_RETURN");
            break;

        case OP_HEAD_OF_EXPRESSION:
            puts("OP_HEAD_OF_EXPRESSION");
            break;

        case OP_SIGINT:
            puts("OP_SIGINT");
            break;

        case OP_THROW :
            puts("OP_THROW");
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

        case OP_LDCPOINTER :
            puts("OP_LDCPOINTER");
            break;

        case OP_LDCFLOAT:
            puts("OP_LDCFLOAT");
            break;

        case OP_LDCDOUBLE:
            puts("OP_LDCDOUBLE");
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

        case OP_CADD :
            puts("OP_CADD");
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

        case OP_CSUB :
            puts("OP_CSUB");
            break;

        case OP_IEQ :
            puts("OP_IEQ");
            break;

        case OP_INOTEQ :
            puts("OP_INOTEQ");
            break;

        case OP_REGEQ:
            puts("OP_REGEQ");
            break;

        case OP_REGNOTEQ:
            puts("OP_REGNOTEQ");
            break;

        case OP_ANDAND:
            puts("OP_ANDAND");
            break;

        case OP_OROR:
            puts("OP_OROR");
            break;

        case OP_LOGICAL_DENIAL:
            puts("OP_LOGICAL_DENIAL");
            break;

        case OP_INVOKE_METHOD :
            puts("OP_INVOKE_METHOD");
            break;

        case OP_INVOKE_VIRTUAL_METHOD:
            puts("OP_INVOKE_VIRTUAL_METHOD");
            break;

        case OP_INVOKE_DYNAMIC_METHOD:
            puts("OP_INVOKE_VIRTUAL_METHOD");
            break;

        case OP_INVOKE_BLOCK:
            puts("OP_INVOKE_BLOCK");
            break;

        case OP_NEW :
            puts("OP_NEW");
            break;

        case OP_LOAD_FIELD:
            puts("OP_LOAD_FIELD");
            break;

        case OP_LOAD_FIELD_ADDRESS:
            puts("OP_LOAD_FIELD_ADDRESS");
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

        case OP_LOAD_ELEMENT:
            puts("OP_LOAD_ELEMENT");
            break;

        case OP_STORE_ELEMENT:
            puts("OP_STORE_ELEMENT");
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

        case OP_CREATE_STRING:
            puts("OP_CREATE_STRING");
            break;

        case OP_CREATE_BUFFER:
            puts("OP_CREATE_BUFFER");
            break;

        case OP_CREATE_PATH:
            puts("OP_CREATE_PATH");
            break;

        case OP_CREATE_BLOCK_OBJECT:
            puts("OP_CREATE_BLOCK_OBJECT");
            break;

        case OP_BYTE_TO_STRING_CAST:
            puts("OP_BYTE_TO_STRING_CAST");
            break;

        case OP_SHORT_TO_STRING_CAST:
            puts("OP_SHORT_TO_STRING_CAST");
            break;

        case OP_INT_TO_STRING_CAST:
            puts("OP_INT_TO_STRING_CAST");
            break;

        case OP_LONG_TO_STRING_CAST:
            puts("OP_LONG_TO_STRING_CAST");
            break;

        case OP_UBYTE_TO_STRING_CAST:
            puts("OP_UBYTE_TO_STRING_CAST");
            break;

        case OP_USHORT_TO_STRING_CAST:
            puts("OP_USHORT_TO_STRING_CAST");
            break;

        case OP_UINT_TO_STRING_CAST:
            puts("OP_UINT_TO_STRING_CAST");
            break;

        case OP_ULONG_TO_STRING_CAST:
            puts("OP_ULONG_TO_STRING_CAST");
            break;

        case OP_FLOAT_TO_STRING_CAST:
            puts("OP_FLOAT_TO_STRING_CAST");
            break;

        case OP_DOUBLE_TO_STRING_CAST:
            puts("OP_DOUBLE_TO_STRING_CAST");
            break;

        case OP_BOOL_TO_STRING_CAST:
            puts("OP_BOOL_TO_STRING_CAST");
            break;

        case OP_POINTER_TO_STRING_CAST:
            puts("OP_POINTER_TO_STRING_CAST");
            break;

        case OP_CHAR_TO_STRING_CAST:
            puts("OP_CHAR_TO_STRING_CAST");
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

void new_vm_mutex()
{
}

BOOL invoke_method(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    if(method->mFlags & METHOD_FLAGS_NATIVE) {
        CLVALUE* lvar = *stack_ptr - method->mNumParams;

        if(method->uCode.mNativeMethod == NULL) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Native method not found");
            return FALSE;
        }

        info->current_stack = stack;        // for invoking_block in native method
        info->current_var_num = var_num;

        if(!method->uCode.mNativeMethod(stack_ptr, lvar, info)) {
            CLVALUE result = *(*stack_ptr - 1); // see OP_TRY
            *stack_ptr = lvar;
            **stack_ptr = result;
            (*stack_ptr)++;
            return FALSE;
        }

        if(is_void_type(method->mResultType, klass)) {
            *stack_ptr = lvar;
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
        CLVALUE* new_stack = lvar;
        int new_var_num = method->mVarNum;

if(strcmp(CLASS_NAME(klass), "JITTest") == 0 && strcmp(METHOD_NAME2(klass, method), "toBuffer") == 0) {
printf("real_param_num %d new_var_num %d\n", real_param_num, new_var_num);
}
        /// initialize local var except params ///
        memset(lvar + real_param_num, 0, sizeof(CLVALUE)* (new_var_num - real_param_num));

#ifdef ENABLE_JIT
        if(!jit(code, constant, new_stack, new_var_num, klass, method, info, stack_ptr))
        {
            *stack_ptr = lvar;
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            return FALSE;
        }
#else
        if(!vm(code, constant, new_stack, new_var_num, klass, info)) {
            *stack_ptr = lvar;
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            return FALSE;
        }
#endif

        *stack_ptr = lvar;      // see OP_RETURN
        **stack_ptr = *new_stack;
        (*stack_ptr)++;
    }

    return TRUE;
}

BOOL invoke_block(CLObject block_object, CLVALUE* stack, int var_num, int num_params, CLVALUE** stack_ptr, sVMInfo* info)
{
    sBlockObject* object_data = CLBLOCK(block_object);

    sByteCode code = object_data->mCodes;               // struct copy
    sConst constant = object_data->mConstant;           // struct copy
    CLVALUE* new_stack = *stack_ptr;
    int new_var_num = object_data->mBlockVarNum + object_data->mParentVarNum;
    BOOL lambda = object_data->mLambda;

    /// initialize local var except params ///
    memset(new_stack + num_params, 0, sizeof(CLVALUE)* (new_var_num - num_params));

    sCLClass* klass = NULL;

    if(lambda) {
        memcpy(new_stack, (*stack_ptr)-num_params, sizeof(CLVALUE)*num_params);

        if(!vm(&code, &constant, new_stack, new_var_num, klass, info)) {
            **stack_ptr = *new_stack;
            (*stack_ptr)++;
            return FALSE;
        }
    }
    else {
        /// check variable existance ///
        if(!check_variables_existance_on_stack(object_data->mStackID))
        {
            /// copy back variables to parent ///
            object_data = CLBLOCK(block_object);
            memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);

            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Parent variables doesn't exist");
            return FALSE;
        }

        /// copy variables ///
        memcpy(new_stack, object_data->mParentStack, sizeof(CLVALUE)*object_data->mParentVarNum);
        memcpy(new_stack + object_data->mParentVarNum, (*stack_ptr)-num_params, sizeof(CLVALUE)*num_params);

        if(!vm(&code, &constant, new_stack, new_var_num, klass, info)) {
            /// copy back variables to parent ///
            object_data = CLBLOCK(block_object);
            memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);

            **stack_ptr = *new_stack;
            (*stack_ptr)++;
            return FALSE;
        }

        /// copy back variables to parent ///
        object_data = CLBLOCK(block_object);
        memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);
    } 

    **stack_ptr = *new_stack;
    (*stack_ptr)++;

    return TRUE;
}

static BOOL initialize_class(sCLClass* klass)
{
    if(klass->mClassInitializeMethodIndex != -1) {
        sCLMethod* initialize_method = klass->mMethods + klass->mClassInitializeMethodIndex;

        const int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
        CLVALUE* stack_ptr = stack;

        sVMInfo info;
        memset(&info, 0, sizeof(sVMInfo));

        if(!invoke_method(klass, initialize_method, stack, 0, &stack_ptr, &info)) {
            MFREE(stack);
            return FALSE;
        }

        MFREE(stack);
    }

    return TRUE;
}

static BOOL load_class_with_initialize(char* class_name)
{
    sCLClass* klass = load_class(class_name);

    if(klass) {
        if(!initialize_class(klass)) {
            return FALSE;
        }
    }

    return TRUE;
}

static BOOL load_fundamental_classes_on_runtime()
{
    if(!load_class_with_initialize("PcreOVec")) { return FALSE; }
    if(!load_class_with_initialize("System")) { return FALSE; }
    if(!load_class_with_initialize("Global")) { return FALSE; }

    if(!load_class_with_initialize("String")) { return FALSE; }
    if(!load_class_with_initialize("Buffer")) { return FALSE; }

    if(!load_class_with_initialize("Exception")) { return FALSE; }

    if(!load_class_with_initialize("Object")) { return FALSE; }

    if(!load_class_with_initialize("Byte")) { return FALSE; }
    if(!load_class_with_initialize("UByte")) { return FALSE; }
    if(!load_class_with_initialize("Short")) { return FALSE; }
    if(!load_class_with_initialize("UShort")) { return FALSE; }
    if(!load_class_with_initialize("Integer")) { return FALSE; }
    if(!load_class_with_initialize("UInteger")) { return FALSE; }
    if(!load_class_with_initialize("Long")) { return FALSE; }
    if(!load_class_with_initialize("ULong")) { return FALSE; }

    if(!load_class_with_initialize("Float")) { return FALSE; }
    if(!load_class_with_initialize("Double")) { return FALSE; }

    if(!load_class_with_initialize("Pointer")) { return FALSE; }
    if(!load_class_with_initialize("Char")) { return FALSE; }
    if(!load_class_with_initialize("Bool")) { return FALSE; }

    if(!load_class_with_initialize("Array")) { return FALSE; }
    if(!load_class_with_initialize("EqualableArray")) { return FALSE; }
    if(!load_class_with_initialize("SortableArray")) { return FALSE; }

    if(!load_class_with_initialize("IHashKey")) { return FALSE; }
    if(!load_class_with_initialize("IEqualable")) { return FALSE; }
    if(!load_class_with_initialize("ISortable")) { return FALSE; }

    if(!load_class_with_initialize("HashItem")) { return FALSE; }
    if(!load_class_with_initialize("Hash")) { return FALSE; }

    if(!load_class_with_initialize("ListItem")) { return FALSE; }
    if(!load_class_with_initialize("List")) { return FALSE; }
    if(!load_class_with_initialize("SortableList")) { return FALSE; }
    if(!load_class_with_initialize("EqualableList")) { return FALSE; }

    if(!load_class_with_initialize("Tuple1")) { return FALSE; }
    if(!load_class_with_initialize("Tuple2")) { return FALSE; }
    if(!load_class_with_initialize("Tuple3")) { return FALSE; }
    if(!load_class_with_initialize("Tuple4")) { return FALSE; }
    if(!load_class_with_initialize("Tuple5")) { return FALSE; }
    if(!load_class_with_initialize("Tuple6")) { return FALSE; }
    if(!load_class_with_initialize("Tuple7")) { return FALSE; }
    if(!load_class_with_initialize("Tuple8")) { return FALSE; }
    if(!load_class_with_initialize("Tuple9")) { return FALSE; }
    if(!load_class_with_initialize("Tuple10")) { return FALSE; }

    if(!load_class_with_initialize("File")) { return FALSE; }
    if(!load_class_with_initialize("Path")) { return FALSE; }
    if(!load_class_with_initialize("tm")) { return FALSE; }
    if(!load_class_with_initialize("stat")) { return FALSE; }
    if(!load_class_with_initialize("Directory")) { return FALSE; }
    if(!load_class_with_initialize("termios")) { return FALSE; }
    if(!load_class_with_initialize("Job")) { return FALSE; }
    if(!load_class_with_initialize("Command")) { return FALSE; }

    if(!load_class_with_initialize("Clover")) { return FALSE; }

    return TRUE;
}

static void set_free_fun_to_classes()
{
    sCLClass* klass;

    klass = get_class("regex");
    klass->mFreeFun = regex_free_fun;
}

BOOL class_init_on_runtime()
{
    if(!load_fundamental_classes_on_runtime()) {
        return FALSE;
    }
    set_boxing_and_unboxing_classes();
    set_free_fun_to_classes();

    return TRUE;
}

static BOOL finalize_class(sCLClass* klass)
{
    if(klass->mClassFinalizeMethodIndex != -1) {
        sCLMethod* finalize_method = klass->mMethods + klass->mClassFinalizeMethodIndex;

        const int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
        CLVALUE* stack_ptr = stack;

        sVMInfo info;
        memset(&info, 0, sizeof(sVMInfo));

        if(!invoke_method(klass, finalize_method, stack, 0, &stack_ptr, &info)) {
            MFREE(stack);
            return FALSE;
        }

        MFREE(stack);
    }

    return TRUE;
}

BOOL call_finalize_method_on_free_object(sCLClass* klass, CLObject self)
{
    if(klass->mFinalizeMethodIndex != -1) {
        sCLMethod* finalize_method = klass->mMethods + klass->mFinalizeMethodIndex;

        const int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
        CLVALUE* stack_ptr = stack;

        sVMInfo info;
        memset(&info, 0, sizeof(sVMInfo));

        stack_ptr->mObjectValue = self;
        stack_ptr++;

        if(!invoke_method(klass, finalize_method, stack, 0, &stack_ptr, &info)) {
            MFREE(stack);
            return FALSE;
        }

        MFREE(stack);
    }

    return TRUE;
}

void class_final_on_runtime()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        (void)finalize_class(p->mItem);
        p = p->mNextClass;
    }
}

sCLClass* get_class_with_load_and_initialize(char* class_name)
{
    sCLClass* result = get_class(class_name);

    if(result == NULL) {
        result = load_class(class_name);

        if(result == NULL) {
            fprintf(stderr, "Clover2 can't load %s\n", class_name);
            return NULL;
        }
        if(!initialize_class(result)) {
            return NULL;
        }
    }

    return result;
}

#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

void boxing_primitive_value_to_object(CLVALUE object, CLVALUE* result, sCLClass* klass)
{
    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        if(is_this_class_with_class_name(klass, "byte")) {
            char value = object.mByteValue;
            CLObject obj = create_byte((char)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "ubyte")) {
            unsigned char value = object.mUByteValue;
            CLObject obj = create_ubyte((unsigned char)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "short")) {
            short value = object.mShortValue;
            CLObject obj = create_short((short)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "ushort")) {
            unsigned short value = object.mUShortValue;
            CLObject obj = create_ushort((unsigned short)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "int")) {
            int value = object.mIntValue;
            CLObject obj = create_integer((int)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "uint")) {
            unsigned int value = object.mUIntValue;
            CLObject obj = create_uinteger(value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "long")) {
            clint64 value = object.mLongValue;
            CLObject obj = create_long((clint64)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "ulong")) {
            unsigned clint64 value = object.mULongValue;
            CLObject obj = create_ulong((unsigned clint64)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "float")) {
            float value = object.mFloatValue;
            CLObject obj = create_float((float)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "double")) {
            double value = object.mDoubleValue;
            CLObject obj = create_double((double)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "pointer")) {
            char* value = object.mPointerValue;
            CLObject obj = create_pointer((char*)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "char")) {
            wchar_t value = object.mCharValue;
            CLObject obj = create_char((wchar_t)value);
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "bool")) {
            BOOL value = object.mBoolValue;
            CLObject obj = create_bool((BOOL)value);
            result->mObjectValue = obj;
        }
    }
    else {
        *result = object;
    }
}

BOOL vm(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sVMInfo* info)
{
#ifdef ENABLE_JIT
    char* pc = code->mCodes;
#else
    register char* pc = code->mCodes;
#endif

    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    sCLStack* stack_id = append_stack_to_stack_list(stack, &stack_ptr);

    while(pc - code->mCodes < code->mLen) {
        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);

#ifdef VM_LOG
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

            case OP_REVERSE: {
                vm_mutex_on();

                CLVALUE value = *(stack_ptr-2);

                *(stack_ptr -2) = *(stack_ptr -1);
                *(stack_ptr -1) = value;

                vm_mutex_off();
                }
                break;

            case OP_DUPE: {
                vm_mutex_on();

                CLVALUE value = *(stack_ptr-1);

                *stack_ptr = value;
                stack_ptr++;

                vm_mutex_off();
                }
                break;

            case OP_COND_JUMP:
                {
                    vm_mutex_on();

                    int jump_value = *(int*)pc;
                    pc += sizeof(int);

                    BOOL conditional_value = (stack_ptr-1)->mBoolValue;
                    stack_ptr--;

                    if(conditional_value) {
                        pc += jump_value;
                    }

                    vm_mutex_off();
                }
                break;

            case OP_COND_NOT_JUMP:
                {
                    vm_mutex_on();

                    int jump_value = *(int*)pc;
                    pc += sizeof(int);

                    BOOL conditional_value = (stack_ptr-1)->mBoolValue;
                    stack_ptr--;

                    if(!conditional_value) {
                        pc += jump_value;
                    }

                    vm_mutex_off();
                }
                break;

            case OP_GOTO:
                {
                    vm_mutex_on();

                    int jump_value = *(int*)pc;
                    pc += sizeof(int);
                    int label_offset = *(int*)pc;
                    pc += sizeof(int);


                    pc = code->mCodes + jump_value;

                    vm_mutex_off();
                }
                break;

            case OP_RETURN:
                *stack = *(stack_ptr-1);
                remove_stack_to_stack_list(stack_id);
#ifdef MDEBUG
if(stack_ptr != lvar + var_num + 1) {
    fprintf(stderr, "invalid stack1\n");
    exit(3);
}
#endif
                return TRUE;

            case OP_THROW: {
                *stack = *(stack_ptr-1);
                remove_stack_to_stack_list(stack_id);

                CLObject exception = stack->mObjectValue;

                entry_exception_object(exception, info);
#ifdef MDEBUG
if(stack_ptr != lvar + var_num + 1) {
    fprintf(stderr, "invalid stack2\n");
    exit(3);
}
#endif
                }
                return FALSE;

            case OP_TRY: {
                vm_mutex_on();

                info->try_offset = *(int*)pc;
                pc += sizeof(int);

#ifdef ENABLE_JIT
                info->try_pc = &pc;
#endif

                info->try_code = code;

                int catch_label_name_offset = *(int*)pc;
                pc += sizeof(int);
                
                vm_mutex_off();
                }
                break;

            case OP_TRY_END:
                vm_mutex_on();

#ifdef ENABLE_JIT
                info->try_pc = 0;
#endif
                info->try_code = NULL;
                info->try_offset = 0;
                
                vm_mutex_off();
                break;

            case OP_CATCH_POP:
                vm_mutex_on();

                stack_ptr--;

                vm_mutex_off();
                break;

            case OP_CATCH_STORE: {
                vm_mutex_on();

                int index = *(int*)pc;
                pc += sizeof(int);

                lvar[index] = *(stack_ptr-1);

                vm_mutex_off();
                }
                break;

            case OP_HEAD_OF_EXPRESSION:
                vm_mutex_on();

                gSigInt = FALSE;

                vm_mutex_off();
                break;

            case OP_MARK_SOURCE_CODE_POSITION: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                info->sname = sname;
                info->sline = sline;
                }
                break;

            case OP_SIGINT:
                vm_mutex_on();

                if(gSigInt) {
                    gSigInt = FALSE;
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Signal Interrupt");
                    remove_stack_to_stack_list(stack_id);
                    return FALSE;
                }

                vm_mutex_off();
                break;

            case OP_LABEL: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                /// nothing to do, this opecode is for Just In Time Compile
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

                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    *stack_ptr = lvar[index];
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_ADDRESS:
                {
                    vm_mutex_on();

                    int index = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mPointerValue = (char*)&lvar[index];
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

                    clint64 lvalue;

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

                    unsigned clint64 lvalue;

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

            case OP_LDCPOINTER: 
                {
                    vm_mutex_on();

                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    void* lvalue;

                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                    stack_ptr->mPointerValue = lvalue;
                    stack_ptr++;

                    vm_mutex_off();

                }
                break;

            case OP_LDCFLOAT: 
                {
                    vm_mutex_on();

                    float value1 = *(float*)pc;
                    pc += sizeof(float);

                    stack_ptr->mFloatValue = value1;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDCDOUBLE: 
                {
                    vm_mutex_on();

                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    double lvalue;

                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                    stack_ptr->mDoubleValue = lvalue;
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

            case OP_BSUB:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BMULT:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BDIV:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    char result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BMOD:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    char result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BLSHIFT:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BRSHIFT:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BAND:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BXOR:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BOR:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left | right;

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

            case OP_UBSUB:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBMULT:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBDIV:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned char result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBMOD:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned char result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBLSHIFT:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBRSHIFT:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBAND:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBXOR:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBOR:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left | right;

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

            case OP_SSUB:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SMULT:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SDIV:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    short result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SMOD:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    short result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SLSHIFT:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SRSHIFT:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SAND:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SXOR:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_SOR:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left | right;

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

            case OP_USSUB:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USMULT:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USDIV:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned short result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USMOD:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned short result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USLSHIFT:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USRSHIFT:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USAND:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USXOR:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USOR:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left | right;

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

            case OP_ISUB: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IMULT: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IDIV: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    int result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IMOD: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    int result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ILSHIFT: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IRSHIFT: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IAND: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IXOR: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IOR: 
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left | right;

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

            case OP_UISUB: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UIMULT: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UIDIV: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned int result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UIMOD: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned int result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UILSHIFT: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UIRSHIFT: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UIAND: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UIXOR: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UIOR: 
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LADD: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LSUB: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LMULT: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LDIV: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    clint64 result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LMOD: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    clint64 result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LLSHIFT: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LRSHIFT: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LAND: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LXOR: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOR: 
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULADD: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULSUB: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULMULT: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULDIV: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned clint64 result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULMOD: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    if(right == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    unsigned clint64 result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULLSHIFT: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULRSHIFT: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULAND: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULXOR: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULOR: 
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BCOMPLEMENT:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    value = ~value;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBCOMPLEMENT:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    value = ~value;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SCOMPLEMENT:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    value = ~value;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USCOMPLEMENT:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    value = ~value;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ICOMPLEMENT:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    value = ~value;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UICOMPLEMENT:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    value = ~value;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LCOMPLEMENT:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULCOMPLEMENT:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    value = ~value;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FADD: 
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    float result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_FSUB: 
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    float result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_FMULT: 
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    float result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_FDIV: 
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    if(right == 0.0f) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    float result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DADD: 
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    double result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DSUB: 
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    double result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DMULT: 
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    double result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DDIV: 
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    if(right == 0.0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    double result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PADD: 
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

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
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    char* result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mPointerValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PPSUB: 
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    unsigned clint64 result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CADD: 
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    wchar_t result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mCharValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CSUB: 
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    int right = (stack_ptr-1)->mIntValue;

                    wchar_t result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mCharValue = result;
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

            case OP_BGT:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BLE:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BGTEQ:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_BLEEQ:
                {
                    vm_mutex_on();

                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left <= right;

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

            case OP_UBGT:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_UBLE:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_UBGTEQ:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_UBLEEQ:
                {
                    vm_mutex_on();

                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
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

            case OP_SGT:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_SLE:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_SGTEQ:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_SLEEQ:
                {
                    vm_mutex_on();

                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
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

            case OP_USGT:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USLE:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USGTEQ:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_USLEEQ:
                {
                    vm_mutex_on();

                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left <= right;

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

                    BOOL result = (left == right);

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

            case OP_IGT:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_ILE:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_IGTEQ:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_ILEEQ:
                {
                    vm_mutex_on();

                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
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

            case OP_UIGT:
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_UILE:
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_UIGTEQ:
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_UILEEQ:
                {
                    vm_mutex_on();

                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_LEQ:
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LNOTEQ:
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_LGT:
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LLE:
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LGTEQ:
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LLEEQ:
                {
                    vm_mutex_on();

                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULEQ:
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_ULNOTEQ:
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_ULGT:
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_ULLE:
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_ULGTEQ:
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
                }
                break;

            case OP_ULLEEQ:
                {
                    vm_mutex_on();

                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_on();
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

            case OP_FGT:
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_FLE:
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_FGTEQ:
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_FLEEQ:
                {
                    vm_mutex_on();

                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left <= right;

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

            case OP_DGT:
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DLE:
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DGTEQ:
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_DLEEQ:
                {
                    vm_mutex_on();

                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PEQ:
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PNOTEQ:
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PGT:
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PLE:
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PGTEQ:
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_PLEEQ:
                {
                    vm_mutex_on();

                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CEQ:
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CNOTEQ:
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CGT:
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CLE:
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CGTEQ:
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CLEEQ:
                {
                    vm_mutex_on();

                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_REGEQ:
                {
                    vm_mutex_on();

                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    BOOL result = regex_equals(left, right);

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_REGNOTEQ:
                {
                    vm_mutex_on();

                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    BOOL result = !regex_equals(left, right);

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;


            case OP_OBJ_IDENTIFY:
                {
                    vm_mutex_on();

                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CLASSNAME:
                {
                    vm_mutex_on();

                    CLObject left = (stack_ptr-1)->mObjectValue;

                    if(left == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(1)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLObject* object_data = CLOBJECT(left);

                    CLObject result = create_string_object(CLASS_NAME(object_data->mClass));

                    stack_ptr--;
                    stack_ptr->mObjectValue = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_IMPLEMENTS:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(1)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject left = (stack_ptr-1)->mObjectValue;

                    if(left == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(2)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    BOOL result = object_implements_interface(left, klass);

                    stack_ptr--;
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;

                    vm_mutex_off();
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

            case OP_LOGICAL_DENIAL:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;
                    BOOL result = !value;

                    stack_ptr--;
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
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(2)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(method_index < 0 || method_index >= klass->mNumMethods) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_METHOD: Method not found");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLMethod* method = klass->mMethods + method_index;

                    if(!invoke_method(klass, method, stack, var_num, &stack_ptr, info)) {
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                        }
                        else {
                            vm_mutex_off();
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    vm_mutex_off();

#ifdef VM_LOG
show_stack(stack, stack_ptr, lvar, var_num);
#endif
                }
                break;

            case OP_INVOKE_VIRTUAL_METHOD:
                {
                    vm_mutex_on();

                    int num_real_params = *(int*)pc;
                    pc += sizeof(int);


                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    CLObject object = (stack_ptr-num_real_params)->mObjectValue;

                    sCLObject* object_data = CLOBJECT(object);

                    sCLClass* klass = object_data->mClass;

                    MASSERT(klass != NULL);

                    char* method_name_and_params = CONS_str(constant, offset);

                    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

                    if(method == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_VIRTUAL_METHOD: Method not found");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }
                    else {
                        if(!invoke_method(klass, method, stack, var_num, &stack_ptr, info)) {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                            }
                            else {
                                vm_mutex_off();
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }
                    }

                    vm_mutex_off();
                }
                break;

            case OP_INVOKE_DYNAMIC_METHOD: 
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    int num_params = *(int*)pc;
                    pc += sizeof(int);

                    BOOL static_ = *(int*)pc;
                    pc += sizeof(int);

                    int num_method_chains = *(int*)pc;
                    pc += sizeof(int);

                    int max_method_chains = *(int*)pc;
                    pc += sizeof(int);

                    /// none static method ////
                    if(static_ == 0) {
                        int num_real_params = num_params + 1;
                        char* method_name = CONS_str(constant, offset2);

                        CLObject object = (stack_ptr-num_real_params)->mObjectValue;

                        sCLObject* object_data = CLOBJECT(object);

                        sCLClass* klass = object_data->mClass;

                        MASSERT(klass != NULL);

                        if(klass->mCallingMethodIndex == -1) {
                            vm_mutex_off();
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_DYNAMIC_METHOD: Method not found(1)");
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }

                        sCLMethod* method = klass->mMethods + klass->mCallingMethodIndex;

                        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

                        int i;
                        for(i=0; i<num_params; i++) {
                            CLObject object = (stack_ptr-num_params + i)->mObjectValue;

                            elements[i] = object;
                        }

                        CLObject carray = create_carray_object_with_elements(num_params, elements);

                        gGlobalStackPtr->mObjectValue = carray;
                        gGlobalStackPtr++;

                        stack_ptr-=num_params;

                        stack_ptr->mObjectValue = create_string_object(method_name);
                        stack_ptr++;
                        stack_ptr->mObjectValue = carray;
                        stack_ptr++;
                        stack_ptr->mIntValue = num_method_chains;
                        stack_ptr++;
                        stack_ptr->mIntValue = max_method_chains;
                        stack_ptr++;

                        gGlobalStackPtr--;

                        if(!invoke_method(klass, method, stack, var_num, &stack_ptr, info)) {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                            }
                            else {
                                vm_mutex_off();
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }
                    }
                    /// static method ///
                    else {
                        char* class_name = CONS_str(constant, offset);
                        char* method_name = CONS_str(constant, offset2);

                        sCLClass* klass = get_class_with_load_and_initialize(class_name);

                        if(klass == NULL) {
                            vm_mutex_off();
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(3)");
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }

                        if(klass->mCallingClassMethodIndex == -1) {
                            vm_mutex_off();
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_DYNAMIC_METHOD: Method not found(2)");
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }

                        sCLMethod* method = klass->mMethods + klass->mCallingClassMethodIndex;

                        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

                        int i;
                        for(i=0; i<num_params; i++) {
                            CLObject object = (stack_ptr-num_params + i)->mObjectValue;

                            elements[i] = object;
                        }

                        CLObject carray = create_carray_object_with_elements(num_params, elements);

                        gGlobalStackPtr->mObjectValue = carray;
                        gGlobalStackPtr++;

                        stack_ptr-=num_params;

                        stack_ptr->mObjectValue = create_string_object(method_name);
                        stack_ptr++;
                        stack_ptr->mObjectValue = carray;
                        stack_ptr++;
                        stack_ptr->mIntValue = num_method_chains;
                        stack_ptr++;
                        stack_ptr->mIntValue = max_method_chains;
                        stack_ptr++;

                        gGlobalStackPtr--;

                        if(!invoke_method(klass, method, stack, var_num, &stack_ptr, info)) {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                            }
                            else {
                                vm_mutex_off();
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }
                    }

                    vm_mutex_off();
                }
                break;

            case OP_INVOKE_BLOCK:
                {
                    vm_mutex_on();

                    int num_params = *(int*)pc;
                    pc += sizeof(int);

                    CLObject block_object = (stack_ptr-num_params-1)->mObjectValue;

                    if(!invoke_block(block_object, stack, var_num, num_params, &stack_ptr, info)) 
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLVALUE result = *(stack_ptr-1);

                    stack_ptr -= num_params+1+1;

                    *stack_ptr = result;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_NEW:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    BOOL flg_array = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(3)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(flg_array) {
                        int array_num = (stack_ptr-1)->mIntValue;
                        stack_ptr--;

                        CLObject array = create_array_object(klass, array_num);
                        stack_ptr->mObjectValue = array;
                        stack_ptr++;
                    }
                    else {
                        CLObject obj = create_object(klass);
                        stack_ptr->mObjectValue = obj;
                        stack_ptr++;
                    }

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_FIELD:
                {
                    vm_mutex_on();

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -1)->mObjectValue;
                    stack_ptr--;

                    if(obj == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(4)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLVALUE value = object_pointer->mFields[field_index];
                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_FIELD_ADDRESS:
                {
                    vm_mutex_on();

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -1)->mObjectValue;
                    stack_ptr--;

                    if(obj == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(4)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(5)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    char* value = (char*)&object_pointer->mFields[field_index];
                    stack_ptr->mPointerValue = value;
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

                    if(obj == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(5)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(6)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack_id);
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

                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(7)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLField* field = klass->mClassFields + field_index;

                    *stack_ptr = field->mValue;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_CLASS_FIELD_ADDRESS:
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
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(8)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLField* field = klass->mClassFields + field_index;
                    char* value = (char*)&field->mValue;

                    stack_ptr->mPointerValue = value;
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
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(9)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLVALUE value = *(stack_ptr-1);

                    sCLField* field = klass->mClassFields + field_index;
                    field->mValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_ELEMENT:
                {
                    vm_mutex_on();

                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    CLObject array = (stack_ptr -2)->mObjectValue;
                    int element_num = (stack_ptr -1)->mIntValue;
                    stack_ptr-=2;

                    if(array == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(7)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLObject* object_pointer = CLOBJECT(array);

                    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "element index is invalid");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLVALUE value = object_pointer->mFields[element_num];
                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_ELEMENT:
                {
                    vm_mutex_on();

                    CLObject array = (stack_ptr -3)->mObjectValue;
                    int element_num = (stack_ptr -2)->mIntValue;
                    CLVALUE value = *(stack_ptr-1);

                    if(array == 0) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(8)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    sCLObject* object_pointer = CLOBJECT(array);

                    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "element index is invalid");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    object_pointer->mFields[element_num] = value;
                    stack_ptr-=3;
                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_INT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;

                    pointer->mIntValue = value.mIntValue;

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

                    *(clint64*)address.mPointerValue = value.mLongValue;

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

                    *(unsigned clint64*)address.mPointerValue = value.mULongValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_FLOAT_ADDRESS: 
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(float*)address.mPointerValue = value.mFloatValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_DOUBLE_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(double*)address.mPointerValue = value.mDoubleValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_POINTER_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(char**)address.mPointerValue = value.mPointerValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_CHAR_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(wchar_t*)address.mPointerValue = value.mCharValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_BOOL_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(BOOL*)address.mPointerValue = value.mBoolValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_STORE_VALUE_TO_OBJECT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    *(CLObject*)address.mPointerValue = value.mObjectValue;

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

                    clint64 value = *(clint64*)address.mPointerValue;

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

                    unsigned clint64 value = *(unsigned clint64*)address.mPointerValue;

                    stack_ptr->mULongValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_FLOAT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    float value = *(float*)address.mPointerValue;

                    stack_ptr->mFloatValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    double value = *(double*)address.mPointerValue;

                    stack_ptr->mDoubleValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_POINTER_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    char* value = *(char**)address.mPointerValue;

                    stack_ptr->mPointerValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_CHAR_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    wchar_t value = *(wchar_t*)address.mPointerValue;

                    stack_ptr->mCharValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_BOOL_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    BOOL value = *(BOOL*)address.mPointerValue;

                    stack_ptr->mBoolValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_LOAD_VALUE_FROM_OBJECT_ADDRESS:
                {
                    vm_mutex_on();

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    CLObject value = *(CLObject*)address.mPointerValue;

                    stack_ptr->mObjectValue = value;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (char)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBYTE_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_BYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mByteValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_BYTE_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (short)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_CBYTE_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_SHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_TO_INT_CAST:
                {
                    vm_mutex_on();

                    int value = (int)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_CBYTE_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_INT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (clint64)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBYTE_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_LONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mIntValue;
                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (unsigned char)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBYTE_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_UBYTE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mUByteValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (unsigned short)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBYTE_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_USHORT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mUShortValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_BYTE_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_LONG_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (unsigned int)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBYTE_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_UINT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mUIntValue = value;

                    vm_mutex_off();
                }
                break;



            case OP_BYTE_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_CBYTE_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_ULONG_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mULongValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_BYTE_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (float)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_CBYTE_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_CCHAR_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_FLOAT_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mFloatValue = value;

                    vm_mutex_off();
                }
                break;



            case OP_BYTE_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (double)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_CBYTE_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_DOUBLE_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_INT_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_POINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (char*)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mPointerValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_INT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;


            case OP_FLOAT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_DOUBLE_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (wchar_t)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBYTE_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUBYTE_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CSHORT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CUSHORT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_INTEGER_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_UINTEGER_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CLONG_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CULONG_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CFLOAT_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CDOUBLE_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CPOINTER_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CCHAR_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;

            case OP_CBOOL_TO_CHAR_CAST:
                {
                    vm_mutex_on();

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mCharValue = value;

                    vm_mutex_off();
                }
                break;
                
            case OP_BYTE_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mCharValue;

                    char buf[32];
                    snprintf(buf, 32, "%d", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_SHORT_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    char buf[32];
                    snprintf(buf, 32, "%d", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    char buf[32];
                    snprintf(buf, 32, "%d", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_LONG_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    char buf[32];
                    snprintf(buf, 32, "%lld", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_UBYTE_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    char buf[32];
                    snprintf(buf, 32, "%u", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    char buf[32];
                    snprintf(buf, 32, "%u", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_UINT_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    char buf[32];
                    snprintf(buf, 32, "%u", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_ULONG_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    char buf[32];
                    snprintf(buf, 32, "%llu", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    char buf[32];
                    snprintf(buf, 32, "%f", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    char buf[32];
                    snprintf(buf, 32, "%lf", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_BOOL_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    char buf[32];
                    if(value) {
                        snprintf(buf, 32, "true");
                    }
                    else {
                        snprintf(buf, 32, "false");
                    }

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_REGEX_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;

                    sRegexObject* object_data = CLREGEX(regex);

                    CLObject str = create_string_object(object_data->mRegexString);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_POINTER_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    char buf[32];
                    snprintf(buf, 32, "%p", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_TO_STRING_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    char buf[32];
                    snprintf(buf, 32, "%lc", value);

                    CLObject str = create_string_object(buf);

                    (stack_ptr-1)->mObjectValue = str;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_integer(value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_INTEGER_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_integer((int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_uinteger(value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_UINTEGER_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_uinteger((unsigned int)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CBYTE_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_byte((char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CUBYTE_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_ubyte((unsigned char)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CSHORT_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_short((short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CUSHORT_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_ushort((unsigned short)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CLONG_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_long((clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CULONG_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_ulong((unsigned clint64)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CFLOAT_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_float((float)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CDOUBLE_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_double((double)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

                
            case OP_CHAR_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CPOINTER_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_pointer((char*)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CCHAR_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_char((wchar_t)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_BYTE_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UBYTE_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_SHORT_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_USHORT_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_INT_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_UINT_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_LONG_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_ULONG_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_FLOAT_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_DOUBLE_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_CHAR_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_POINTER_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;
                
            case OP_BOOL_TO_CBOOL_CAST:
                {
                    vm_mutex_on();

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_bool((BOOL)value);

                    (stack_ptr-1)->mObjectValue = obj;

                    vm_mutex_off();
                }
                break;

            case OP_ARRAY_TO_CARRAY_CAST: {
                vm_mutex_on();

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(10)");
                    remove_stack_to_stack_list(stack_id);
                    return FALSE;
                }

                CLObject array = (stack_ptr-1)->mObjectValue;
                sCLObject* array_data = CLOBJECT(array);
                int array_num = array_data->mArrayNum;

                sCLClass* klass2 = get_class("Array");
                MASSERT(klass2 != NULL);

                CLObject new_array = create_object(klass2);

                stack_ptr->mObjectValue = new_array;   // push object
                stack_ptr++;

                CLObject new_primitive_array;
                if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                    new_primitive_array = create_array_object(klass->mBoxingClass, array_num);
                }
                else {
                    new_primitive_array = create_array_object(klass, array_num);
                }

                sCLObject* new_array_data = CLOBJECT(new_array);

                new_array_data->mFields[0].mObjectValue = new_primitive_array;

                /// boxing element ///
                int i;
                for(i=0; i<array_num; i++ ) {
                    array_data = CLOBJECT(array);           // reget for GC

                    CLVALUE element;
                    boxing_primitive_value_to_object(array_data->mFields[i], &element, klass);

                    sCLObject* new_primitive_array_data = CLOBJECT(new_primitive_array);
                    new_primitive_array_data->mFields[i] = element;
                }

                stack_ptr-=2;
                stack_ptr->mObjectValue = new_array;
                stack_ptr++;

                vm_mutex_off();
                }
                break;
                
            case OP_GET_ARRAY_LENGTH:
                {
                    vm_mutex_on();

                    CLObject array = (stack_ptr-1)->mObjectValue;
                    sCLObject* array_data = CLOBJECT(array);
                    stack_ptr--;

                    stack_ptr->mIntValue = array_data->mArrayNum;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_GLOBAL :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mGlobal;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_IGNORE_CASE :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mIgnoreCase;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_MULTILINE :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mMultiline;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_EXTENDED :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mExtended;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_DOTALL :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mDotAll;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_ANCHORED :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mAnchored;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_DOLLAR_ENDONLY :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mDollarEndOnly;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_GET_REGEX_UNGREEDY :
                {
                    vm_mutex_on();

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mBoolValue = regex_object->mUngreedy;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_UPPERCASE:
                {
                    vm_mutex_on();

                    wchar_t c = (stack_ptr-1)->mCharValue;

                    wchar_t result = c;
                    if(c >= 'a' && c <= 'z') {
                        result = c - 'a' + 'A';
                    }

                    (stack_ptr-1)->mCharValue = result;

                    vm_mutex_off();
                }
                break;

            case OP_CHAR_LOWERCASE:
                {
                    vm_mutex_on();

                    wchar_t c = (stack_ptr-1)->mCharValue;

                    wchar_t result = c;
                    if(c >= 'A' && c <= 'Z') {
                        result = c - 'A' + 'a';
                    }

                    (stack_ptr-1)->mCharValue = result;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_STRING:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    CLObject string_object = create_string_object(str);

                    stack_ptr->mObjectValue = string_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_BUFFER:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    char* buf = CONS_str(constant, offset);

                    CLObject buffer_object = create_buffer_object(buf, size);

                    stack_ptr->mObjectValue = buffer_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_PATH:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* buf = CONS_str(constant, offset);

                    CLObject path_object = create_path_object(buf);

                    stack_ptr->mObjectValue = path_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_ARRAY:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(11)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject array_object = create_array_object(klass, num_elements);
                    stack_ptr->mObjectValue = array_object; // push object
                    stack_ptr++;

                    sCLObject* object_data = CLOBJECT(array_object);

                    int i;
                    for(i=0; i<num_elements; i++) {
                        object_data->mFields[i] = *(stack_ptr-1-num_elements+i);
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_CARRAY:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject array_object = create_carray_object();
                    stack_ptr->mObjectValue = array_object; // push object
                    stack_ptr++;

                    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        CLVALUE element = *(stack_ptr-1-num_elements+i);
                        items[i] = (*(stack_ptr-1-num_elements+i)).mObjectValue;
                    }

                    if(!initialize_carray_object(array_object, num_elements, items, stack, var_num, &stack_ptr, info, klass))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_EQUALABLE_CARRAY:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject array_object = create_equalable_carray_object();
                    stack_ptr->mObjectValue = array_object; // push object
                    stack_ptr++;

                    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        CLVALUE element = *(stack_ptr-1-num_elements+i);
                        items[i] = (*(stack_ptr-1-num_elements+i)).mObjectValue;
                    }

                    if(!initialize_equalable_carray_object(array_object, num_elements, items, stack, var_num, &stack_ptr, info, klass))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_SORTABLE_CARRAY:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject array_object = create_sortable_carray_object();
                    stack_ptr->mObjectValue = array_object; // push object
                    stack_ptr++;

                    CLObject items[ARRAY_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        CLVALUE element = *(stack_ptr-1-num_elements+i);
                        items[i] = (*(stack_ptr-1-num_elements+i)).mObjectValue;
                    }

                    if(!initialize_sortable_carray_object(array_object, num_elements, items, stack, var_num, &stack_ptr, info, klass))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_LIST:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject list_object = create_list_object();
                    stack_ptr->mObjectValue = list_object; // push object
                    stack_ptr++;

                    CLObject items[LIST_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        CLVALUE element = *(stack_ptr-1-num_elements+i);
                        items[i] = (*(stack_ptr-1-num_elements+i)).mObjectValue;
                    }

                    if(!initialize_list_object(list_object, num_elements, items, stack, var_num, &stack_ptr, info, klass))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = list_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_SORTALBE_LIST:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject list_object = create_sortable_list_object();
                    stack_ptr->mObjectValue = list_object; // push object
                    stack_ptr++;

                    CLObject items[LIST_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        CLVALUE element = *(stack_ptr-1-num_elements+i);
                        items[i] = (*(stack_ptr-1-num_elements+i)).mObjectValue;
                    }

                    if(!initialize_sortable_list_object(list_object, num_elements, items, stack, var_num, &stack_ptr, info, klass))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = list_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_EQUALABLE_LIST:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject list_object = create_equalable_list_object();
                    stack_ptr->mObjectValue = list_object; // push object
                    stack_ptr++;

                    CLObject items[LIST_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        CLVALUE element = *(stack_ptr-1-num_elements+i);
                        items[i] = (*(stack_ptr-1-num_elements+i)).mObjectValue;
                    }

                    if(!initialize_equalable_list_object(list_object, num_elements, items, stack, var_num, &stack_ptr, info, klass))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = list_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_TUPLE:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    CLObject tuple_object = create_tuple_object(num_elements);
                    stack_ptr->mObjectValue = tuple_object; // push object
                    stack_ptr++;

                    CLObject items[TUPLE_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        CLVALUE element = *(stack_ptr-1-num_elements+i);
                        items[i] = (*(stack_ptr-1-num_elements+i)).mObjectValue;
                    }

                    if(!initialize_tuple_object(tuple_object, num_elements, items, stack, var_num, &stack_ptr, info))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mObjectValue = tuple_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_HASH:
                {
                    vm_mutex_on();

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(14)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name2 = CONS_str(constant, offset2);

                    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

                    if(klass2 == NULL) {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(15)");
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    CLObject keys[HASH_VALUE_ELEMENT_MAX];

                    int i;
                    for(i=0; i<num_elements; i++) {
                        keys[i] = (stack_ptr - num_elements * 2 + i * 2)->mObjectValue;
                    }

                    CLObject items[HASH_VALUE_ELEMENT_MAX];

                    for(i=0; i<num_elements; i++) {
                        items[i] = (stack_ptr - num_elements * 2 + i * 2 + 1)->mObjectValue;
                    }

                    CLObject hash_object = create_hash_object();
                    stack_ptr->mObjectValue = hash_object; // push object
                    stack_ptr++;

                    if(!initialize_hash_object(hash_object, num_elements, keys, items, stack, var_num, &stack_ptr, info, klass, klass2))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements*2;
                    stack_ptr->mObjectValue = hash_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_BLOCK_OBJECT:
                {
                    vm_mutex_on();

                    int code_offset = *(int*)pc;
                    pc += sizeof(int);

                    int code_len = *(int*)pc;
                    pc += sizeof(int);

                    sByteCode codes2;

//sByteCode_init_with_size(&codes2, code_len);
//append_value_to_code(&codes2, CONS_str(constant, code_offset), code_len, FALSE);

                    codes2.mCodes = CONS_str(constant, code_offset);
                    codes2.mLen = code_len;

                    int constant_offset = *(int*)pc;
                    pc += sizeof(int);

                    int constant_len = *(int*)pc;
                    pc += sizeof(int);

                    sConst constant2;

//sConst_init_with_size(&constant2, constant_len);
//sConst_append(&constant2, CONS_str(constant, constant_offset), constant_len, FALSE);

                    constant2.mConst = CONS_str(constant, constant_offset);
                    constant2.mLen = constant_len;

                    int block_var_num = *(int*)pc;
                    pc += sizeof(int);

                    int parent_var_num = *(int*)pc;
                    pc += sizeof(int);

                    int lambda = *(int*)pc;
                    pc += sizeof(int);

                    CLVALUE* parent_stack = stack;

                    CLObject block_object = create_block_object(&codes2, &constant2, parent_stack, parent_var_num, block_var_num, stack_id, lambda);

                    stack_ptr->mObjectValue = block_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;

            case OP_CREATE_REGEX:
                {
                    vm_mutex_on();

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    BOOL global = *(int*)pc;
                    pc += sizeof(int);

                    BOOL ignore_case = *(int*)pc;
                    pc += sizeof(int);

                    BOOL multiline = *(int*)pc;
                    pc += sizeof(int);

                    BOOL extended = *(int*)pc;
                    pc += sizeof(int);

                    BOOL dotall = *(int*)pc;
                    pc += sizeof(int);

                    BOOL anchored = *(int*)pc;
                    pc += sizeof(int);

                    BOOL dollar_endonly = *(int*)pc;
                    pc += sizeof(int);

                    BOOL ungreedy = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    CLObject regex_object = create_regex_object(str, global, ignore_case, multiline, extended, dotall, anchored, dollar_endonly, ungreedy);

                    stack_ptr->mObjectValue = regex_object;
                    stack_ptr++;

                    vm_mutex_off();
                }
                break;
        }
#ifdef VM_LOG
show_stack(stack, stack_ptr, lvar, var_num);
#endif
    }

    remove_stack_to_stack_list(stack_id);

#ifdef MDEBUG
if(stack_ptr != lvar + var_num) {
    fprintf(stderr, "invalid stack3\n");
    fprintf(stderr, "var_num %d\n", var_num);
    if(klass) { fprintf(stderr, "class name %s\n", CLASS_NAME(klass)); }
    fprintf(stderr, "stack_ptr - lvar - var_num %ld\n", stack_ptr - (lvar + var_num));
    exit(3);
}
#endif

    return TRUE;
}

