#include "common.h"
#ifdef HAVE_AVCALL_H
#include <avcall.h>
#endif

BOOL gSigInt = FALSE;

void show_stack(CLVALUE* stack, CLVALUE* stack_ptr)
{
    int i;
    for(i=0; i<30; i++) {
        if(stack + i < stack_ptr) {
            printf("[%d] %d on %p\n", i, stack[i].mIntValue, stack + i);
        }
    }
}

static void reset_andand_oror(sVMInfo* info)
{
    info->num_andand_oror = 0;
}

static int get_andand_oror_left_value(sVMInfo* info)
{
    return info->andand_oror_left_value[info->num_andand_oror-1];
}

static void set_andand_oror_left_value(BOOL flag, sVMInfo* info)
{
    info->andand_oror_left_value[info->num_andand_oror-1] = flag;
}

static int get_andand_oror_right_value(sVMInfo* info)
{
    return info->andand_oror_right_value[info->num_andand_oror-1];
}

static void set_andand_oror_right_value(BOOL flag, sVMInfo* info)
{
    info->andand_oror_right_value[info->num_andand_oror-1] = flag;
}

static void inc_andand_oror_array(sVMInfo* info)
{
    info->num_andand_oror++;

    if(info->num_andand_oror >= ANDAND_OROR_MAX) {
        fprintf(stderr, "overflow and and or or value\n");
        exit(1);
    }
}

static void dec_andand_oror_array(sVMInfo* info)
{
    info->num_andand_oror--;

    if(info->num_andand_oror < 0) {
        fprintf(stderr, "invalid and and or or value\n");
        exit(1);
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

        case OP_REVERSE:
            puts("OP_REVERSE");
            break;

        case OP_INT_TO_ULONG_CAST:
            puts("OP_INT_TO_ULONG_CAST");
            break;

        case OP_STORE_TO_BUFFER:
            puts("OP_STORE_TO_BUFFER");
            break;

        case OP_BUFFER_TO_POINTER_CAST:
            puts("OP_BUFFER_TO_POINTER_CAST");
            break;

        case OP_DUPE:
            puts("OP_DUPE");
            break;

        case OP_COND_JUMP :
            puts("OP_COND_JUMP");
            break;
        
        case OP_MARK_SOURCE_CODE_POSITION:
            puts("OP_MARK_SOURCE_CODE_POSITION");
            break;

        case OP_MARK_SOURCE_CODE_POSITION2:
            puts("OP_MARK_SOURCE_CODE_POSITION2");
            break;

        case OP_COND_NOT_JUMP :
            puts("OP_COND_NOT_JUMP");
            break;
        case OP_JIT_POP:
            puts("OP_JIT_POP");
            break;

        case OP_STORE_ANDAND_OROR_VALUE_LEFT:
            puts("OP_STORE_ANDAND_OROR_VALUE_LEFT");
            break;

        case OP_STORE_ANDAND_OROR_VALUE_RIGHT:
            puts("OP_STORE_ANDAND_OROR_VALUE_RIGHT");
            break;

        case OP_GET_ANDAND_OROR_RESULT_LEFT:
            puts("OP_GET_ANDAND_OROR_RESULT_LEFT");
            break;

        case OP_GET_ANDAND_OROR_RESULT_RIGHT:
            puts("OP_GET_ANDAND_OROR_RESULT_RIGHT");
            break;

        case OP_INC_ANDAND_OROR_ARRAY:
            puts("OP_INC_ANDAND_OROR_ARRAY");
            break;

        case OP_DEC_ANDAND_OROR_ARRAY:
            puts("OP_DEC_ANDAND_OROR_ARRAY");
            break;

        case OP_GOTO :
            puts("OP_GOTO");
            break;

        case OP_LABEL :
            puts("OP_LABEL");
            break;

        case OP_STORE_VALUE_TO_GLOBAL:
            puts("OP_STORE_VALUE_TO_GLOBAL");
            break;

        case OP_UINT_TO_UINTEGER_CAST:
            puts("OP_UINT_TO_UINTEGER_CAST");
            break;

        case OP_POP_VALUE_FROM_GLOBAL:
            puts("OP_POP_VALUE_FROM_GLOBAL");
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

        case OP_LDCBOOL :
            puts("OP_LDCBOOL");
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

BOOL invoke_method(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    sCLClass* running_class = info->running_class;
    sCLMethod* running_method = info->running_method;

    CLObject result_object = 0;

    int num_global_strck_ptr = info->mGlobalStackPtr - info->mGlobalStack;
    int num_tmp_global_stack_ptr = info->mTmpGlobalStackPtr - info->mTmpGlobalStack;

    info->running_class = klass;
    info->running_method = method;

    char* running_class_name = info->running_class_name;
    char* running_method_name = info->running_method_name;

    info->running_class_name = CLASS_NAME(klass);
    info->running_method_name = METHOD_NAME2(klass, method);

    char* sname2 = info->sname2;
    int sline2 = info->sline2;

    if(sname2) {
        if(info->num_stack_trace < STACK_TRACE_MAX-1) {
            xstrncpy(info->stack_trace_sname[info->num_stack_trace], sname2, 128);
            info->stack_trace_sline[info->num_stack_trace] = sline2;
            info->num_stack_trace++;
        }
        else {
            int i;
            for(i=0; i<info->num_stack_trace-1; i++) {
                xstrncpy(info->stack_trace_sname[i], info->stack_trace_sname[i+1], 128);
                info->stack_trace_sline[i] = info->stack_trace_sline[i+1];
            }
            info->num_stack_trace--;

            xstrncpy(info->stack_trace_sname[info->num_stack_trace], sname2, 128);
            info->stack_trace_sline[info->num_stack_trace] = sline2;
            info->num_stack_trace++;
        }
    }


    CLVALUE* lvar = NULL;
    int num_params = 0;

    if(method->mFlags & METHOD_FLAGS_C_FUNCTION) {
#ifdef HAVE_AVCALL_H
        lvar = *stack_ptr - method->mNumParams;
        num_params = method->mNumParams;

        int k;
        for(k=0; k<num_params; k++) {
            inc_refference_count(lvar[k].mObjectValue, 0, FALSE);
        }

        if(method->mCFunctionPointer == NULL) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "C Function method not found");
            info->running_class = running_class;
            info->running_method = running_method;
            info->running_class_name = running_class_name;
            info->running_method_name = running_method_name;

            info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
            info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
            return FALSE;
        }

        void* func = method->mCFunctionPointer;

        sCLClass* void_class = get_class("Null");
        sCLClass* int_class = get_class("int");
        sCLClass* uint_class = get_class("uint");
        sCLClass* byte_class = get_class("byte");
        sCLClass* ubyte_class = get_class("ubyte");
        sCLClass* short_class = get_class("short");
        sCLClass* ushort_class = get_class("ushort");
        sCLClass* long_class = get_class("long");
        sCLClass* ulong_class = get_class("ulong");
        sCLClass* float_class = get_class("float");
        sCLClass* double_class = get_class("double");
        sCLClass* pointer_class = get_class("pointer");
        sCLClass* bool_class = get_class("bool");
        sCLClass* char_class = get_class("char");
        sCLClass* lambda_class = get_class("lambda");

        int int_result_value = 0;
        unsigned int uint_result_value = 0;
        char byte_result_value = 0;
        unsigned char ubyte_result_value = 0;
        short short_result_value = 0;
        unsigned short ushort_result_value = 0;
        long long_result_value = 0;
        unsigned long ulong_result_value = 0;
        void* pointer_result_value = 0;
        float float_result_value = 0.0f;
        double double_result_value = 0.0;

        sCLClass* result_class = get_class_from_cl_type(method->mResultType, klass);

        av_alist alist;

        if(result_class == int_class || result_class == bool_class) {
            av_start_int(alist, func, &int_result_value);
        }
        else if(result_class == uint_class || result_class == char_class) {
            av_start_uint(alist, func, &uint_result_value);
        }
        else if(result_class == byte_class) {
            av_start_char(alist, func, &byte_result_value);
        }
        else if(result_class == ubyte_class) {
            av_start_uchar(alist, func, &ubyte_result_value);
        }
        else if(result_class == short_class) {
            av_start_short(alist, func, &short_result_value);
        }
        else if(result_class == ushort_class) {
            av_start_ushort(alist, func, &ushort_result_value);
        }
        else if(result_class == long_class) {
            av_start_long(alist, func, &long_result_value);
        }
        else if(result_class == ulong_class) {
            av_start_ulong(alist, func, &ulong_result_value);
        }
        else if(result_class == float_class) {
            av_start_float(alist, func, &float_result_value);
        }
        else if(result_class == double_class) {
            av_start_double(alist, func, &double_result_value);
        }
        else if(result_class == pointer_class) {
            av_start_ptr(alist, func, void*, &pointer_result_value);
        }
        else if(result_class == void_class) {
            av_start_void(alist, func);
        }
        else {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "C Function is not supported lambda or struct class");
            info->running_class = running_class;
            info->running_method = running_method;
            info->running_class_name = running_class_name;
            info->running_method_name = running_method_name;

            info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
            info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
            return FALSE;
        }

        int i;
        for(i=0; i<method->mNumParams; i++) {
            sCLParam* param_type = method->mParams + i;
            sCLClass* param_class = get_class_from_cl_type(param_type->mType, klass);

            CLVALUE* param = lvar + i;

            if(param_class == int_class || param_class == bool_class) {
                av_int(alist, param->mIntValue);
            }
            else if(param_class == uint_class || param_class == char_class) {
                av_uint(alist, param->mUIntValue);
            }
            else if(param_class == byte_class) {
                av_char(alist, param->mByteValue);
            }
            else if(param_class == ubyte_class) {
                av_uchar(alist, param->mUByteValue);
            }
            else if(param_class == short_class) {
                av_short(alist, param->mShortValue);
            }
            else if(param_class == ushort_class) {
                av_short(alist, param->mUShortValue);
            }
            else if(param_class == long_class) {
                av_long(alist, param->mLongValue);
            }
            else if(param_class == ulong_class) {
                av_ulong(alist, param->mULongValue);
            }
            else if(param_class == float_class) {
                av_float(alist, param->mFloatValue);
            }
            else if(param_class == double_class) {
                av_double(alist, param->mDoubleValue);
            }
            else if(param_class == pointer_class) {
                av_ptr(alist, void*, param->mPointerValue);
            }
            else {
                entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "C Function is not supported lambda or struct class");
                info->running_class = running_class;
                info->running_method = running_method;
                info->running_class_name = running_class_name;
                info->running_method_name = running_method_name;

                info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
                info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
                return FALSE;
            }
        }

/*
        for(k=0; k<num_params; k++) {
            dec_refference_count(lvar[k].mObjectValue, TRUE);
        }
*/

        if(result_class == int_class || result_class == bool_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mIntValue = int_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == uint_class || result_class == char_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mUIntValue = uint_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == byte_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mByteValue = byte_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == ubyte_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mUByteValue = ubyte_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == short_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mShortValue = short_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == ushort_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mUShortValue = ushort_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == long_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mLongValue = long_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == ulong_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mULongValue = ulong_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == pointer_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mPointerValue = pointer_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == float_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mFloatValue = float_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == double_class) {
            av_call(alist);
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            (*stack_ptr)->mDoubleValue = double_result_value;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else if(result_class == get_class("Null")) {
            av_call(alist);

            *stack_ptr = lvar;
            (*stack_ptr)->mLongValue = 0;    // zero clear for jit
            (*stack_ptr)->mIntValue = 0;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
        else {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "C Function is not supported lambda or struct class");

            info->running_class = running_class;
            info->running_method = running_method;
            info->running_class_name = running_class_name;
            info->running_method_name = running_method_name;

            info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
            info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
            return FALSE;
        }
#else
        entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "C Function is not supported. Please add --with-c-ffi to configure option.");
        info->running_class = running_class;
        info->running_method = running_method;
        info->running_class_name = running_class_name;
        info->running_method_name = running_method_name;

        info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
        info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
        return FALSE;
#endif
    }
    else if(method->mFlags & METHOD_FLAGS_NATIVE) 
    {
        lvar = *stack_ptr - method->mNumParams;
        num_params = method->mNumParams;

        int k;
        for(k=0; k<num_params; k++) {
            inc_refference_count(lvar[k].mObjectValue, 0, FALSE);
        }

        if(method->mNativeMethod == NULL) {
            char* path = CONS_str(&klass->mConst, method->mPathOffset);

            char* fun_name;
            fNativeMethod native_method = get_native_method(path, &fun_name);

            if(native_method == NULL) {
                entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Native method not found");
                info->running_class = running_class;
                info->running_method = running_method;
                info->running_class_name = running_class_name;
                info->running_method_name = running_method_name;
                info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
                info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
                return FALSE;
            }

            method->mNativeMethod = native_method;
            method->mNativeFunName = fun_name;
        }

        info->current_stack = stack;        // for invoking_block in native method
        info->current_var_num = var_num;

        if(!method->mNativeMethod(stack_ptr, lvar, info)) {
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            **stack_ptr = result;
            (*stack_ptr)++;
            info->running_class = running_class;
            info->running_method = running_method;
            info->running_class_name = running_class_name;
            info->running_method_name = running_method_name;
            info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
            info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
            return FALSE;
        }

/*
        for(k=0; k<num_params; k++) {
            dec_refference_count(lvar[k].mObjectValue, TRUE);
        }
*/

        if(is_void_type(method->mResultType, klass)) {
            *stack_ptr = lvar;
            (*stack_ptr)->mLongValue = 0;    // zero clear for jit
            (*stack_ptr)->mIntValue = 0;
            (*stack_ptr)++;
        }
        else {
            CLVALUE result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            **stack_ptr = result;
            (*stack_ptr)++;

            result_object = result.mObjectValue;
        }
    }
    else {
        int real_param_num = method->mNumParams + (method->mFlags & METHOD_FLAGS_CLASS_METHOD ? 0:1);

        lvar = *stack_ptr - real_param_num;
        num_params = real_param_num;

        int k;
        for(k=0; k<num_params; k++) {
            inc_refference_count(lvar[k].mObjectValue, 0, FALSE);
        }

        sByteCode code;
        sByteCode_clone(&code, &method->mByteCodes);
        sConst constant;
        sConst_clone(&constant, &klass->mConst);

        CLVALUE* new_stack = lvar;
        int new_var_num = method->mVarNum;

        /// initialize local var except params ///
        memset(lvar + real_param_num, 0, sizeof(CLVALUE)* (new_var_num - real_param_num));

#ifdef ENABLE_JIT
        if(!jit(&code, &constant, new_stack, new_var_num, klass, method, 0, info, stack_ptr))
        {
            *stack_ptr = lvar;
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            sConst_free(&constant);
            sByteCode_free(&code);
            info->running_class_name = running_class_name;
            info->running_method_name = running_method_name;
            info->running_class = running_class;
            info->running_method = running_method;
            info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
            info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
            return FALSE;
        }
#else
        if(!vm(&code, &constant, new_stack, new_var_num, klass, info)) {
            *stack_ptr = lvar;
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            sConst_free(&constant);
            sByteCode_free(&code);
            info->running_class_name = running_class_name;
            info->running_method_name = running_method_name;
            info->running_class = running_class;
            info->running_method = running_method;
            info->mGlobalStackPtr = info->mGlobalStack + num_global_strck_ptr;
            info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;
            return FALSE;
        }
#endif

        *stack_ptr = lvar;      // see OP_RETURN
        **stack_ptr = *(new_stack+new_var_num);
        (*stack_ptr)++;

        result_object = (new_stack+new_var_num)->mObjectValue;

/*
        for(k=0; k<new_var_num; k++) {
            dec_refference_count(lvar[k].mObjectValue, TRUE);
        }
*/

        sConst_free(&constant);
        sByteCode_free(&code);
    }

    if(sname2) {
        info->num_stack_trace--;
    }

    info->running_class = running_class;
    info->running_method = running_method;

    info->running_class_name = running_class_name;
    info->running_method_name = running_method_name;

    free_global_stack_objects(info, result_object, num_global_strck_ptr, lvar, num_params);
    info->mTmpGlobalStackPtr = info->mTmpGlobalStack + num_tmp_global_stack_ptr;

    return TRUE;
}

BOOL invoke_block(CLObject block_object, CLVALUE* stack, int var_num, int num_params, CLVALUE** stack_ptr, sVMInfo* info, BOOL llvm_flag)
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

    info->running_class_name = "none";
    info->running_method_name = "block_object";

    if(lambda) {
        memcpy(new_stack, (*stack_ptr)-num_params, sizeof(CLVALUE)*num_params);

        if(!vm(&code, &constant, new_stack, new_var_num, klass, info)) {
            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            return FALSE;
        }
    }
    else {
/*
        /// check variable existance ///
        if(!check_variables_existance_on_stack(stack, *stack_ptr))
        {
            /// copy back variables to parent ///
            object_data = CLBLOCK(block_object);
            memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);

            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Parent variables doesn't exist. ID is %p", object_data->mStackID);
            return FALSE;
        }
*/
        /// copy variables ///
        memcpy(new_stack, object_data->mParentStack, sizeof(CLVALUE)*object_data->mParentVarNum);
        memcpy(new_stack + object_data->mParentVarNum, (*stack_ptr)-num_params, sizeof(CLVALUE)*num_params);

#ifdef ENABLE_JIT
        klass = object_data->mClass2;

        if(object_data->mBlockID == -1 || klass == NULL) {
            if(!vm(&code, &constant, new_stack, new_var_num, klass, info)) {
                /// copy back variables to parent ///
                object_data = CLBLOCK(block_object);
                memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);

                **stack_ptr = *(new_stack + new_var_num);
                (*stack_ptr)++;
                return FALSE;
            }
        }
        else {
            if(!jit(&code, &constant, new_stack, new_var_num, klass, NULL, block_object, info, stack_ptr))
            {
                /// copy back variables to parent ///
                object_data = CLBLOCK(block_object);
                memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);

                **stack_ptr = *(new_stack + new_var_num);
                (*stack_ptr)++;
                return FALSE;
            }
        }
#else
        if(!vm(&code, &constant, new_stack, new_var_num, klass, info)) {
            /// copy back variables to parent ///
            object_data = CLBLOCK(block_object);
            memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);

            **stack_ptr = *(new_stack + new_var_num);
            (*stack_ptr)++;
            return FALSE;
        }
#endif

        /// copy back variables to parent ///
        object_data = CLBLOCK(block_object);
        memcpy(object_data->mParentStack, new_stack, sizeof(CLVALUE)*object_data->mParentVarNum);
    }

    **stack_ptr = *(new_stack + new_var_num);
    (*stack_ptr)++;

    return TRUE;
}

static BOOL initialize_class(sCLClass* klass, BOOL compile_time)
{
    if(!klass->mInitialized) {
        if(klass->mClassInitializeMethodIndex != -1) {
            sCLMethod initialize_method = klass->mMethods[klass->mClassInitializeMethodIndex]; // struct copy for realloc

            const int stack_size = 512;
            CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
            CLVALUE* stack_ptr = stack;

            sVMInfo info;
            memset(&info, 0, sizeof(sVMInfo));

            info.prohibit_delete_global_stack = TRUE;

            create_global_stack_and_append_it_to_stack_list(&info);

            if(!invoke_method(klass, &initialize_method, stack, 0, &stack_ptr, &info)) {
                free_global_stack(&info);
                MFREE(stack);
                return FALSE;
            }

            free_global_stack(&info);

            MFREE(stack);
        }

        /// initialize enum ///
        int i;
        for(i=0; i<klass->mNumClassFields; i++) {
            sCLField* field = klass->mClassFields + i;

            if(field->mInitializeValue != -1) {
                field->mValue.mIntValue = field->mInitializeValue;
            }
        }

        klass->mInitialized = TRUE;
    }

    return TRUE;
}

static BOOL load_class_with_initialize(char* class_name)
{
    sCLClass* klass = load_class(class_name);

    if(klass) {
        if(!initialize_class(klass, FALSE)) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL gRunningInitializer = FALSE;

BOOL load_fundamental_classes_on_runtime()
{
    gRunningInitializer = TRUE;
    if(!load_class_with_initialize("PcreOVec")) { return FALSE; }
    if(!load_class_with_initialize("System")) { return FALSE; }
    if(!load_class_with_initialize("Global")) { return FALSE; }

    if(!load_class_with_initialize("String")) { return FALSE; }
    if(!load_class_with_initialize("Buffer")) { return FALSE; }

    if(!load_class_with_initialize("Exception")) { return FALSE; }

    if(!load_class_with_initialize("Object")) { return FALSE; }
    if(!load_class_with_initialize("Range")) { return FALSE; }

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
    if(!load_class_with_initialize("Class")) { return FALSE; }
    if(!load_class_with_initialize("Method")) { return FALSE; }
    if(!load_class_with_initialize("MethodParam")) { return FALSE; }
    if(!load_class_with_initialize("Field")) { return FALSE; }
    if(!load_class_with_initialize("Thread")) { return FALSE; }

    if(!load_class_with_initialize("Clover")) { return FALSE; }
    gRunningInitializer = FALSE;

    return TRUE;
}

void set_free_fun_to_classes()
{
    sCLClass* klass;

    klass = get_class("regex");
    klass->mFreeFun = regex_free_fun;

    klass = get_class("lambda");

    klass->mFreeFun = free_block;
}

BOOL call_all_class_initializer()
{
    vm_mutex_off();
    vm_mutex_on();

    sClassTable* p = gHeadClassTable;

    while(p) {
        if(p->mItem->mInitialized == FALSE) {
            if(!initialize_class(p->mItem, TRUE)) {
                vm_mutex_off();
                return TRUE;
            }
        }
        p = p->mNextClass;
    }

    vm_mutex_off();

    return TRUE;
}

BOOL class_init_on_runtime()
{
    vm_mutex_on();
    if(!load_fundamental_classes_on_runtime()) {
        vm_mutex_off();
        return FALSE;
    }
    set_boxing_and_unboxing_classes();
    set_free_fun_to_classes();

    vm_mutex_off();

    return TRUE;
}

static BOOL finalize_class(sCLClass* klass)
{
    if(klass->mClassFinalizeMethodIndex != -1) {
        sCLMethod finalize_method = klass->mMethods[klass->mClassFinalizeMethodIndex]; // struct copy for realloc

        const int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
        CLVALUE* stack_ptr = stack;

        sVMInfo info;
        memset(&info, 0, sizeof(sVMInfo));

        create_global_stack_and_append_it_to_stack_list(&info);
        
        if(!invoke_method(klass, &finalize_method, stack, 0, &stack_ptr, &info)) {
            MFREE(stack);
            free_global_stack(&info);
            return FALSE;
        }

        free_global_stack(&info);

        MFREE(stack);
    }

    return TRUE;
}

void callOnException(CLObject message, BOOL in_try, sVMInfo* info)
{
    static BOOL in_calling_on_exception = FALSE;
    if(!in_calling_on_exception) {
        in_calling_on_exception = TRUE;

        sCLClass* clover_class = get_class("Clover");

        if(clover_class) {
            int method_index = -1;

            int i;
            for(i=clover_class->mNumMethods-1; i>=0; i--) {
                sCLMethod* method = clover_class->mMethods + i;

                if(method->mNumParams == 2) {
                    sCLParam* param1 = method->mParams + 0;
                    sCLParam* param2 = method->mParams + 1;

                    sCLType* param1_type = param1->mType;
                    sCLType* param2_type = param2->mType;

                    if(strcmp(METHOD_NAME2(clover_class, method), "onException") == 0 && (method->mFlags & METHOD_FLAGS_CLASS_METHOD) && strcmp(CONS_str(&clover_class->mConst, param1_type->mClassNameOffset), "String") == 0 && strcmp(CONS_str(&clover_class->mConst, param2_type->mClassNameOffset), "bool") == 0)
                    {
                        method_index = i;
                        break;
                    }
                }
            }

            if(method_index >= 0) {
                sCLMethod* method = clover_class->mMethods + method_index;

                const int stack_size = 512;
                CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
                CLVALUE* stack_ptr = stack;

                stack_ptr->mObjectValue = message;
                stack_ptr++;

                stack_ptr->mBoolValue = in_try;
                stack_ptr++;

                sVMInfo info;
                memset(&info, 0, sizeof(sVMInfo));

                create_global_stack_and_append_it_to_stack_list(&info);
                
                (void)invoke_method(clover_class, method, stack, 0, &stack_ptr, &info);

                MFREE(stack);
                free_global_stack(&info);
            }
        }
        in_calling_on_exception = FALSE;
    }
}

BOOL call_finalize_method_on_free_object(sCLClass* klass, CLObject self)
{
    if(klass->mFinalizeMethodIndex != -1) {
        sCLMethod finalize_method = klass->mMethods[klass->mFinalizeMethodIndex]; // struct copy for realloc

        const int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
        CLVALUE* stack_ptr = stack;

        sVMInfo info;

        memset(&info, 0, sizeof(sVMInfo));

        create_global_stack_and_append_it_to_stack_list(&info);

        info.no_mutex_in_vm = TRUE;

        stack_ptr->mLongValue = 0;    // zero clear for jit
        stack_ptr->mObjectValue = self;
        stack_ptr++;

        if(!invoke_method(klass, &finalize_method, stack, 0, &stack_ptr, &info)) {
            free_global_stack(&info);
            MFREE(stack);
            return FALSE;
        }

        free_global_stack(&info);
        MFREE(stack);
    }

    return TRUE;
}

BOOL call_alloc_size_method(sCLClass* klass, unsigned long long* result)
{
    if(klass->mAllocSizeMethodIndex != -1) {
        sCLMethod alloc_size_method = klass->mMethods[klass->mAllocSizeMethodIndex]; // struct copy for realloc

        const int stack_size = 512;
        CLVALUE* stack = MCALLOC(1, sizeof(CLVALUE)*stack_size);
        CLVALUE* stack_ptr = stack;

        sVMInfo info;

        memset(&info, 0, sizeof(sVMInfo));

        create_global_stack_and_append_it_to_stack_list(&info);

        info.no_mutex_in_vm = TRUE;

        if(!invoke_method(klass, &alloc_size_method, stack, 0, &stack_ptr, &info)) {
            MFREE(stack);
            free_global_stack(&info);
            return FALSE;
        }

        *result = (stack_ptr-1)->mULongValue;

        MFREE(stack);

        free_global_stack(&info);
    }

    return TRUE;
}

void class_final_on_runtime()
{
    vm_mutex_off();
    vm_mutex_on();
    sClassTable* p = gHeadClassTable;

    while(p) {
        (void)finalize_class(p->mItem);
        p = p->mNextClass;
    }
    vm_mutex_off();
}

sCLClass* get_class_with_load_and_initialize(char* class_name)
{
    sCLClass* result = get_class(class_name);

    if(result == NULL) {
        result = load_class(class_name);

        if(result == NULL) {
            //fprintf(stderr, "Clover2 can't load %s\n", class_name);
            return NULL;
        }
        if(!initialize_class(result, FALSE)) {
            return NULL;
        }
    }

    return result;
}

#pragma clang diagnostic ignored "-Wint-to-pointer-cast"

void boxing_primitive_value_to_object(CLVALUE object, CLVALUE* result, sCLClass* klass, sVMInfo* info)
{
    if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        if(is_this_class_with_class_name(klass, "byte")) {
            char value = object.mByteValue;
            CLObject obj = create_byte((char)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "ubyte")) {
            unsigned char value = object.mUByteValue;
            CLObject obj = create_ubyte((unsigned char)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "short")) {
            short value = object.mShortValue;
            CLObject obj = create_short((short)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "ushort")) {
            unsigned short value = object.mUShortValue;
            CLObject obj = create_ushort((unsigned short)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "int")) {
            int value = object.mIntValue;
            CLObject obj = create_integer((int)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "uint")) {
            unsigned int value = object.mUIntValue;
            CLObject obj = create_uinteger(value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "long")) {
            clint64 value = object.mLongValue;
            CLObject obj = create_long((clint64)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "ulong")) {
            unsigned clint64 value = object.mULongValue;
            CLObject obj = create_ulong((unsigned clint64)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "float")) {
            float value = object.mFloatValue;
            CLObject obj = create_float((float)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "double")) {
            double value = object.mDoubleValue;
            CLObject obj = create_double((double)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "pointer")) {
            char* value = object.mPointerValue;
            CLObject obj = create_pointer((char*)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "char")) {
            wchar_t value = object.mCharValue;
            CLObject obj = create_char((wchar_t)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
        else if(is_this_class_with_class_name(klass, "bool")) {
            BOOL value = object.mBoolValue;
            CLObject obj = create_bool((BOOL)value, info);
            result->mLongValue = 0;                 // zero clear for jit
            result->mObjectValue = obj;
        }
    }
    else {
        *result = object;
    }
}

void Self_convertion_of_method_name_and_params(char* method_name_and_params, char* method_name_and_params2, char* class_name)
{
//    strcpy(method_name_and_params2, method_name_and_params);

    char* p = method_name_and_params;
    char* p2 = method_name_and_params2;

    char* result = strstr(p, "(");

    memcpy(p2, p, result -p);
    p2 += result -p;
    p = result;

    while(1) {
        char* result = strstr(p, class_name);

        if(result == NULL) {
            memcpy(p2, p, strlen(p));
            p2[strlen(p)] = '\0';
            break;
        }

        memcpy(p2, p, result - p);
        p2 += result - p;
        memcpy(p2, "Self", 4);
        p2 += 4;

        p = result + strlen(class_name);
    }
}

static BOOL string_expression(char* str, int str_len, sBuf* buf, int* string_expression_offsets, CLObject* string_expression_object, int num_string_expression, CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    int offset_before = 0;

    int i;
    for(i=0; i<num_string_expression; i++) {
        int offset = string_expression_offsets[i];

        sBuf_append(buf, str + offset_before, offset - offset_before);

        CLObject object = string_expression_object[i];

        if(object == 0) {
            entry_exception_object_with_class_name(stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(10)");
            return FALSE;
        }

        char* str2 = ALLOC string_object_to_char_array(object);
        sBuf_append_str(buf, str2);
        MFREE(str2);

        offset_before = offset;
    }

    sBuf_append(buf, str + offset_before, str_len - offset_before);

    return TRUE;
}

BOOL vm(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sVMInfo* info)
{
#ifdef ENABLE_JIT
    char* pc = code->mCodes;
#else
    register char* pc = code->mCodes;
#endif
    //reset_andand_oror(info);
    
    int l = 0;

    CLVALUE* stack_ptr = stack + var_num;
    CLVALUE* lvar = stack;

    sCLStack* stack_id = append_stack_to_stack_list(stack, &stack_ptr);

    int try_offset_before = 0;
    char** try_pc_before = NULL;
    sByteCode* try_code_before = NULL;

    if(!info->no_mutex_in_vm) {
        vm_mutex_off();
    }

    while(1) {
        if(!info->no_mutex_in_vm) {
            vm_mutex_on();
        }

        BOOL bvalue = pc - code->mCodes < code->mLen;

        if(!info->no_mutex_in_vm) {
            vm_mutex_off();
        }

        if(!bvalue) {
            break;
        }

        if(!info->no_mutex_in_vm) {
            vm_mutex_on();
        }

        unsigned int inst = *(unsigned int*)pc;
        pc+=sizeof(int);
/*
if(!gRunningCompiler && !gRunningInitializer) {
show_inst(inst);
}
*/
        switch(inst) {
            case OP_NOP:
                break;

            case OP_POP:
                stack_ptr--;

                break;

            case OP_POP_N:
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);
                    stack_ptr -= value;
                }
                break;

            case OP_REVERSE: {
                CLVALUE value = *(stack_ptr-2);

                *(stack_ptr -2) = *(stack_ptr -1);
                *(stack_ptr -1) = value;
                }
                break;

            case OP_DUPE: {
                CLVALUE value = *(stack_ptr-1);

                *stack_ptr = value;
                stack_ptr++;
                }
                break;

            case OP_COND_JUMP:
                {
                    int jump_value = *(int*)pc;
                    pc += sizeof(int);

                    BOOL conditional_value = (stack_ptr-1)->mBoolValue;
                    stack_ptr--;

                    if(conditional_value) {
                        pc += jump_value;
                    }
                }
                break;

            case OP_COND_NOT_JUMP:
                {
                    int jump_value = *(int*)pc;
                    pc += sizeof(int);

                    BOOL conditional_value = (stack_ptr-1)->mBoolValue;
                    stack_ptr--;

                    if(!conditional_value) {
                        pc += jump_value;
                    }
                }
                break;

            case OP_GOTO:
                {
                    int jump_value = *(int*)pc;
                    pc += sizeof(int);
                    int label_offset = *(int*)pc;
                    pc += sizeof(int);


                    pc = code->mCodes + jump_value;
                }
                break;

            case OP_RETURN:
                *(stack+var_num) = *(stack_ptr-1);

                remove_stack_to_stack_list(stack_id);
                return TRUE;

            case OP_THROW: {
                *(stack + var_num) = *(stack_ptr-1);

                CLObject exception = (stack_ptr-1)->mObjectValue;

                entry_exception_object(exception, info);

                remove_stack_to_stack_list(stack_id);
                }
                return FALSE;

            case OP_TRY: {
                try_offset_before = info->try_offset;
                try_code_before = info->try_code;

                info->try_offset = *(int*)pc;
                pc += sizeof(int);

#ifdef ENABLE_JIT
                try_pc_before = info->try_pc;
                info->try_pc = &pc;
#endif

                info->try_code = code;

                int catch_label_name_offset = *(int*)pc;
                pc += sizeof(int);

                int try_exception_var_index = *(int*)pc;
                pc += sizeof(int);
                }
                break;

            case OP_TRY_END:
#ifdef ENABLE_JIT
                info->try_pc = try_pc_before;
#endif
                info->try_code = try_code_before;
                info->try_offset = try_offset_before;
                break;

            case OP_CATCH_POP:
                stack_ptr--;
                break;

            case OP_CATCH_STORE: {
                int index = *(int*)pc;
                pc += sizeof(int);

                lvar[index] = *(stack_ptr-1);
                }
                break;

            case OP_STORE_ANDAND_OROR_VALUE_LEFT:
                set_andand_oror_left_value((stack_ptr-1)->mBoolValue, info);
                stack_ptr--;
                break;

            case OP_STORE_ANDAND_OROR_VALUE_RIGHT:
                set_andand_oror_right_value((stack_ptr-1)->mBoolValue, info);
                stack_ptr--;
                break;

            case OP_INC_ANDAND_OROR_ARRAY: {
                inc_andand_oror_array(info);
                }
                break;

            case OP_DEC_ANDAND_OROR_ARRAY: {
                dec_andand_oror_array(info);
                }
                break;

            case OP_GET_ANDAND_OROR_RESULT_LEFT: {
                stack_ptr->mIntValue = get_andand_oror_left_value(info);
                stack_ptr++;
                }
                break;

            case OP_GET_ANDAND_OROR_RESULT_RIGHT: {
                stack_ptr->mIntValue = get_andand_oror_right_value(info);
                stack_ptr++;
                }
                break;

            case OP_HEAD_OF_EXPRESSION:
                gSigInt = FALSE;
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

            case OP_MARK_SOURCE_CODE_POSITION2: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                char* sname = CONS_str(constant, offset);

                int sline = *(int*)pc;
                pc += sizeof(int);

                info->sname2 = sname;
                info->sline2 = sline;
                }
                break;

            case OP_SIGINT:
                if(gSigInt) {
                    gSigInt = FALSE;

                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Signal Interrupt");
                    remove_stack_to_stack_list(stack_id);
                    return FALSE;
                }
                break;

            case OP_LABEL: {
                int offset = *(int*)pc;
                pc += sizeof(int);

                /// nothing to do, this opecode is for Just In Time Compile
                }
                break;

            case OP_STORE_VALUE_TO_GLOBAL: {
                CLVALUE value = *(stack_ptr-1);
                stack_ptr--;

                push_value_to_global_stack(value, info);
                }
                break;

            case OP_POP_VALUE_FROM_GLOBAL: {
                int size = *(int*)pc;
                pc += sizeof(int);

                CLVALUE value = pop_global_stack(info);

                *stack_ptr = value;
                stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_FOR_MACHINE_STACK:
                break;

            case OP_POP_FOR_MACHINE_STACK:
                break;

            case OP_RESTORE_VALUE_FROM_MACHINE_STACK: {
                int size = *(int*)pc;
                pc += sizeof(int);
                }
                break;

            case OP_STORE:
                {
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    BOOL value_is_object = *(int*)pc;
                    pc += sizeof(int);

                    CLObject prev_obj = lvar[index].mObjectValue;

                    lvar[index] = *(stack_ptr-1);

                    inc_refference_count(lvar[index].mObjectValue, prev_obj, value_is_object);
                }
                break;

            case OP_STORE_TO_BUFFER:
                {
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = lvar[index].mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-1)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(obj);

                    char* p = (stack_ptr-1)->mPointerValue;

                    if(p < object_data->mFields[0].mPointerValue || p >= object_data->mFields[0].mPointerValue + object_data->mFields[2].mULongValue) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Out of range on memory safe pointer");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    object_data->mFields[3].mPointerValue = (stack_ptr-1)->mPointerValue;
                }
                break;

            case OP_LOAD:
                {
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    *stack_ptr = lvar[index];
                    stack_ptr++;
                }
                break;

            case OP_LOAD_ADDRESS:
                {
                    int index = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mPointerValue = (char*)&lvar[index];
                    stack_ptr++;
                }
                break;

            case OP_SPLIT_TUPLE: {
                int num_elements = *(int*)pc;
                pc += sizeof(int);

                int size[GENERICS_TYPES_MAX];

                int i;
                for(i = 0; i<num_elements; i++) {
                    size[i] = *(int*)pc;
                    pc += sizeof(int);
                }

                CLObject tuple = (stack_ptr-1)->mObjectValue;
                stack_ptr--;

                sCLObject* object_data = CLOBJECT(tuple);

                for(i=0; i<num_elements; i++) {
                    *stack_ptr = object_data->mFields[i];
                    stack_ptr++;
                }
                }
                break;

            case OP_LDCBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = (char)value;
                    stack_ptr++;
                }
                break;

            case OP_LDCUBYTE: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = (unsigned char)value;
                    stack_ptr++;
                }
                break;

            case OP_LDCSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = (short)value;
                    stack_ptr++;
                }
                break;

            case OP_LDCUSHORT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = (unsigned short)value;
                    stack_ptr++;
                }
                break;

            case OP_LDCINT: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = value;
                    stack_ptr++;
                }
                break;

            case OP_LDCBOOL: 
                {
                    int value = *(int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = value;
                    stack_ptr++;
                }
                break;

            case OP_LDCUINT: 
                {
                    unsigned int value = *(unsigned int*)pc;
                    pc += sizeof(int);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = value;
                    stack_ptr++;
                }
                break;

            case OP_LDCLONG: 
                {
                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    clint64 lvalue;

#ifdef __BIG_ENDIAN__
                    memcpy(&lvalue, &value1, sizeof(char));
                    memcpy((char*)&lvalue + 1, (char*)&value1 + 1, sizeof(char));
                    memcpy((char*)&lvalue + 2, (char*)&value1 + 2, sizeof(char));
                    memcpy((char*)&lvalue + 3, (char*)&value1 + 3, sizeof(char));
                    memcpy((char*)&lvalue + 4, (char*)&value2, sizeof(char));
                    memcpy((char*)&lvalue + 5, (char*)&value2 + 1, sizeof(char));
                    memcpy((char*)&lvalue + 6, (char*)&value2 + 2, sizeof(char));
                    memcpy((char*)&lvalue + 7, (char*)&value2 + 3, sizeof(char));
#else
                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));
#endif

                    stack_ptr->mLongValue = lvalue;
                    stack_ptr++;
                }
                break;

            case OP_LDCULONG: 
                {
                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    unsigned clint64 lvalue;

#ifdef __BIG_ENDIAN__
                    memcpy(&lvalue, &value1, sizeof(char));
                    memcpy((char*)&lvalue + 1, (char*)&value1 + 1, sizeof(char));
                    memcpy((char*)&lvalue + 2, (char*)&value1 + 2, sizeof(char));
                    memcpy((char*)&lvalue + 3, (char*)&value1 + 3, sizeof(char));
                    memcpy((char*)&lvalue + 4, (char*)&value2, sizeof(char));
                    memcpy((char*)&lvalue + 5, (char*)&value2 + 1, sizeof(char));
                    memcpy((char*)&lvalue + 6, (char*)&value2 + 2, sizeof(char));
                    memcpy((char*)&lvalue + 7, (char*)&value2 + 3, sizeof(char));
#else
                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));
#endif


                    stack_ptr->mULongValue = lvalue;
                    stack_ptr++;
                }
                break;

            case OP_LDCNULL:
                {
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = 0;
                    stack_ptr++;
                }
                break;

            case OP_LDCPOINTER: 
                {
                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    void* lvalue;

#if defined(__BIG_ENDIAN__) && defined(__32BIT_CPU__)
                    memcpy(&lvalue, &value1, sizeof(char));
                    memcpy((char*)&lvalue + 1, (char*)&value1 + 1, sizeof(char));
                    memcpy((char*)&lvalue + 2, (char*)&value1 + 2, sizeof(char));
                    memcpy((char*)&lvalue + 3, (char*)&value1 + 3, sizeof(char));
#elif defined(__BIG_ENDIAN__) && defined(__64BIT_CPU__)
                    memcpy(&lvalue, &value1, sizeof(char));
                    memcpy((char*)&lvalue + 1, (char*)&value1 + 1, sizeof(char));
                    memcpy((char*)&lvalue + 2, (char*)&value1 + 2, sizeof(char));
                    memcpy((char*)&lvalue + 3, (char*)&value1 + 3, sizeof(char));
                    memcpy((char*)&lvalue + 4, (char*)&value2, sizeof(char));
                    memcpy((char*)&lvalue + 5, (char*)&value2 + 1, sizeof(char));
                    memcpy((char*)&lvalue + 6, (char*)&value2 + 2, sizeof(char));
                    memcpy((char*)&lvalue + 7, (char*)&value2 + 3, sizeof(char));
#elif !defined(__BIG_ENDIAN__) && defined(__32BIT_CPU__)
                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));
//#elif !defined(__BIG_ENDIAN__) && defined(__64BIT_CPU__)
#else
                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));
#endif

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mPointerValue = lvalue;
                    stack_ptr++;

                }
                break;

            case OP_LDCFLOAT: 
                {
                    float value1 = *(float*)pc;
                    pc += sizeof(float);

                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mFloatValue = value1;
                    stack_ptr++;
                }
                break;

            case OP_LDCDOUBLE: 
                {
                    int value1 = *(int*)pc;
                    pc += sizeof(int);

                    int value2 = *(int*)pc;
                    pc += sizeof(int);

                    double lvalue;

                    memcpy(&lvalue, &value1, sizeof(int));
                    memcpy((char*)&lvalue + sizeof(int), &value2, sizeof(int));

                    stack_ptr->mDoubleValue = lvalue;
                    stack_ptr++;
                }
                break;

            case OP_BADD:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BSUB:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BMULT:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BDIV:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BMOD:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BLSHIFT:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BRSHIFT:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BAND:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BXOR:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BOR:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    char result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBADD:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBSUB:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBMULT:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBDIV:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned char result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBMOD:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned char result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBLSHIFT:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBRSHIFT:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBAND:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBXOR:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBOR:
                {
                    unsigned char left = (stack_ptr-2)->mByteValue;
                    unsigned char right = (stack_ptr-1)->mByteValue;

                    unsigned char result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUByteValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SADD:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SSUB:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SMULT:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SDIV:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    short result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SMOD:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    short result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SLSHIFT:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SRSHIFT:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SAND:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SXOR:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SOR:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    short result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USADD:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USSUB:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USMULT:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USDIV:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned short result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USMOD:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned short result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USLSHIFT:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USRSHIFT:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USAND:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USXOR:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USOR:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    unsigned short result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUShortValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IADD: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ISUB: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IMULT: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IDIV: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    int result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IMOD: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    int result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ILSHIFT: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IRSHIFT: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IAND: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IXOR: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IOR: 
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    int result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIADD: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UISUB: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIMULT: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIDIV: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned int result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIMOD: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned int result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UILSHIFT: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIRSHIFT: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIAND: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIXOR: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIOR: 
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    unsigned int result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mUIntValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LADD: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LSUB: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LMULT: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LDIV: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    clint64 result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LMOD: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    clint64 result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LLSHIFT: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LRSHIFT: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LAND: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left & right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LXOR: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LOR: 
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    clint64 result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULADD: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULSUB: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULMULT: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULDIV: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned clint64 result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULMOD: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    if(right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    unsigned clint64 result = left % right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULLSHIFT: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left << right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULRSHIFT: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left >> right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULAND: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULXOR: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left ^ right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULOR: 
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    unsigned clint64 result = left | right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BCOMPLEMENT:
                {
                    char value = (stack_ptr-1)->mByteValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = 0; // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;
                }
                break;

            case OP_UBCOMPLEMENT:
                {
                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = 0; // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;
                }
                break;

            case OP_SCOMPLEMENT:
                {
                    short value = (stack_ptr-1)->mShortValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = 0; // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;
                }
                break;

            case OP_USCOMPLEMENT:
                {
                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = 0; // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;
                }
                break;

            case OP_ICOMPLEMENT:
                {
                    int value = (stack_ptr-1)->mIntValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = 0; // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;
                }
                break;

            case OP_UICOMPLEMENT:
                {
                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = 0; // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;
                }
                break;

            case OP_LCOMPLEMENT:
                {
                    clint64 value = (stack_ptr-1)->mLongValue;

                    value = ~value;

                    (stack_ptr-1)->mLongValue = value;
                }
                break;

            case OP_ULCOMPLEMENT:
                {
                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    value = ~value;

                    (stack_ptr-1)->mULongValue = value;
                }
                break;

            case OP_FADD: 
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    float result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FSUB: 
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    float result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FMULT: 
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    float result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FDIV: 
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    if(right == 0.0f) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    float result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mFloatValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DADD: 
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    double result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DSUB: 
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    double result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DMULT: 
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    double result = left * right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DDIV: 
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    if(right == 0.0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "division by zero");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    double result = left / right;

                    stack_ptr-=2;
                    stack_ptr->mDoubleValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PADD: 
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    char* result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mPointerValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PSUB: 
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    char* result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mPointerValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PPSUB: 
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    unsigned clint64 result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mULongValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CADD: 
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    wchar_t result = left + right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mCharValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CSUB: 
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    int right = (stack_ptr-1)->mIntValue;

                    wchar_t result = left - right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mCharValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BEQ:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BNOTEQ:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BGT:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BLE:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BGTEQ:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_BLEEQ:
                {
                    char left = (stack_ptr-2)->mByteValue;
                    char right = (stack_ptr-1)->mByteValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBEQ:
                {
                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBNOTEQ:
                {
                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBGT:
                {
                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBLE:
                {
                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBGTEQ:
                {
                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UBLEEQ:
                {
                    unsigned char left = (stack_ptr-2)->mUByteValue;
                    unsigned char right = (stack_ptr-1)->mUByteValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SEQ:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SNOTEQ:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SGT:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SLE:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SGTEQ:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_SLEEQ:
                {
                    short left = (stack_ptr-2)->mShortValue;
                    short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USEQ:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USNOTEQ:
                {
                    unsigned short left = (stack_ptr-2)->mShortValue;
                    unsigned short right = (stack_ptr-1)->mShortValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USGT:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USLE:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USGTEQ:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_USLEEQ:
                {
                    unsigned short left = (stack_ptr-2)->mUShortValue;
                    unsigned short right = (stack_ptr-1)->mUShortValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IEQ:
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = (left == right);

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_INOTEQ:
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IGT:
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ILE:
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IGTEQ:
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ILEEQ:
                {
                    int left = (stack_ptr-2)->mIntValue;
                    int right = (stack_ptr-1)->mIntValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIEQ:
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UINOTEQ:
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIGT:
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UILE:
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UIGTEQ:
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_UILEEQ:
                {
                    unsigned int left = (stack_ptr-2)->mUIntValue;
                    unsigned int right = (stack_ptr-1)->mUIntValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LEQ:
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LNOTEQ:
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LGT:
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LLE:
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LGTEQ:
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LLEEQ:
                {
                    clint64 left = (stack_ptr-2)->mLongValue;
                    clint64 right = (stack_ptr-1)->mLongValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULEQ:
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULNOTEQ:
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULGT:
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULLE:
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULGTEQ:
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ULLEEQ:
                {
                    unsigned clint64 left = (stack_ptr-2)->mULongValue;
                    unsigned clint64 right = (stack_ptr-1)->mULongValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FEQ:
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FNOTEQ:
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FGT:
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FLE:
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FGTEQ:
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_FLEEQ:
                {
                    float left = (stack_ptr-2)->mFloatValue;
                    float right = (stack_ptr-1)->mFloatValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DEQ:
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DNOTEQ:
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DGT:
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DLE:
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DGTEQ:
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_DLEEQ:
                {
                    double left = (stack_ptr-2)->mDoubleValue;
                    double right = (stack_ptr-1)->mDoubleValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PEQ:
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PNOTEQ:
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PGT:
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PLE:
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PGTEQ:
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_PLEEQ:
                {
                    char* left = (stack_ptr-2)->mPointerValue;
                    char* right = (stack_ptr-1)->mPointerValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CEQ:
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CNOTEQ:
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CGT:
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left > right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CLE:
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left < right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CGTEQ:
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left >= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CLEEQ:
                {
                    wchar_t left = (stack_ptr-2)->mCharValue;
                    wchar_t right = (stack_ptr-1)->mCharValue;

                    BOOL result = left <= right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_REGEQ:
                {
                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    BOOL result = regex_equals(left, right);

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_REGNOTEQ:
                {
                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    BOOL result = !regex_equals(left, right);

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_OBJ_IDENTIFY:
                {
                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    BOOL result = left == right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_OBJ_IDENTIFY_NOT:
                {
                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    BOOL result = left != right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_CLASSNAME:
                {
                    CLObject left = (stack_ptr-1)->mObjectValue;

                    if(left == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(1-1)");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(left);

                    if(object_data->mType == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Object Type is Null");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLObject result = create_string_object(object_data->mType, info);

                    stack_ptr--;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mObjectValue = result;
                    stack_ptr++;
                }
                break;

            case OP_IS:
                {
                    CLObject left = (stack_ptr-2)->mObjectValue;
                    CLObject right = (stack_ptr-1)->mObjectValue;

                    if(left == 0 || right == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(1-2)");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(left);

                    char* left_class_name = object_data->mType;
                    char* right_class_name = ALLOC string_object_to_char_array(right);

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = strcmp(left_class_name, right_class_name) == 0;
                    stack_ptr++;

                    MFREE(right_class_name);
                }
                break;

            case OP_OBJ_ALLOCATED_SIZE:
                {
                    CLObject left = (stack_ptr-1)->mObjectValue;

                    if(left == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(1-3)");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(left);

                    stack_ptr--;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mIntValue = object_data->mSize;
                    stack_ptr++;
                }
                break;

            case OP_OBJ_HEAD_OF_MEMORY:
                {
                    CLObject left = (stack_ptr-1)->mObjectValue;

                    if(left == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(1-4)");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(left);

                    stack_ptr--;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mPointerValue = (void*)object_data->mFields;
                    stack_ptr++;
                }
                break;

            case OP_IMPLEMENTS:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(1)");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLObject left = (stack_ptr-1)->mObjectValue;

                    if(left == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(2)");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    BOOL result = object_implements_interface(left, klass);

                    stack_ptr--;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_ANDAND:
                {
                    int left = (stack_ptr-2)->mBoolValue;
                    int right = (stack_ptr-1)->mBoolValue;

                    BOOL result = left && right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_OROR:
                {
                    int left = (stack_ptr-2)->mBoolValue;
                    int right = (stack_ptr-1)->mBoolValue;

                    BOOL result = left || right;

                    stack_ptr-=2;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_LOGICAL_DENIAL:
                {
                    BOOL value = (stack_ptr-1)->mBoolValue;
                    BOOL result = !value;

                    stack_ptr--;
                    stack_ptr->mLongValue = 0; // zero clear for jit
                    stack_ptr->mBoolValue = result;
                    stack_ptr++;
                }
                break;

            case OP_INVOKE_METHOD:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int method_index = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(2)");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(method_index < 0 || method_index >= klass->mNumMethods) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_METHOD: Method not found");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLMethod method = klass->mMethods[method_index]; // struct copy for realloc

                    if(!invoke_method(klass, &method, stack, var_num, &stack_ptr, info)) {
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }
                }
                break;

            case OP_INVOKE_VIRTUAL_METHOD:
                {
                    int num_real_params = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    CLObject object = (stack_ptr-num_real_params)->mObjectValue;

                    if(object == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-2)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(object);

                    sCLClass* klass = object_data->mClass;

//printf("OP_VIRTUAL_METHOD %s\n", CLASS_NAME(klass));

                    MASSERT(klass != NULL);

                    char* method_name_and_params = CONS_str(constant, offset);

                    char method_name_and_params2[METHOD_NAME_MAX + num_real_params * CLASS_NAME_MAX + 128];
                    Self_convertion_of_method_name_and_params(method_name_and_params, method_name_and_params2, CLASS_NAME(klass));


                    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params2);
                    if(method == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_VIRTUAL_METHOD: Method not found(%s.%s)", CLASS_NAME(klass), method_name_and_params);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }
                    else {
                        if(!invoke_method(klass, method, stack, var_num, &stack_ptr, info)) {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }
                    }
                }
                break;

            case OP_INVOKE_DYNAMIC_METHOD: 
                {
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

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    /// none static method ////
                    if(static_ == 0) {
                        int num_real_params = num_params + 1;
                        char* method_name = CONS_str(constant, offset2);

                        CLObject object = (stack_ptr-num_real_params)->mObjectValue;

                        if(object == 0) {
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-3)");
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        sCLObject* object_data = CLOBJECT(object);

                        sCLClass* klass = object_data->mClass;

                        MASSERT(klass != NULL);

                        if(klass->mCallingMethodIndex == -1) {
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_DYNAMIC_METHOD: Method not found(1)");
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        sCLMethod method = klass->mMethods[klass->mCallingMethodIndex];

                        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

                        int i;
                        for(i=0; i<num_params; i++) {
                            CLObject object = (stack_ptr-num_params + i)->mObjectValue;

                            elements[i] = object;
                        }

                        CLObject carray = create_carray_object_with_elements(num_params, elements, info);

                        CLVALUE cl_value;
                        cl_value.mLongValue = 0;
                        cl_value.mObjectValue = carray;
                        push_value_to_global_stack(cl_value, info);

                        stack_ptr-=num_params;

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = create_string_object(method_name, info);
                        stack_ptr++;
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = carray;
                        stack_ptr++;
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mIntValue = num_method_chains;
                        stack_ptr++;
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mIntValue = max_method_chains;
                        stack_ptr++;

                        pop_global_stack(info);

                        if(!invoke_method(klass, &method, stack, var_num, &stack_ptr, info)) {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
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
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(3)");
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        if(klass->mCallingClassMethodIndex == -1) {
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "OP_INVOKE_DYNAMIC_METHOD: Method not found(2)");

                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        sCLMethod method = klass->mMethods[klass->mCallingClassMethodIndex]; // struct copy for realloc

                        CLObject elements[ARRAY_VALUE_ELEMENT_MAX];

                        int i;
                        for(i=0; i<num_params; i++) {
                            CLObject object = (stack_ptr-num_params + i)->mObjectValue;

                            elements[i] = object;
                        }

                        CLObject carray = create_carray_object_with_elements(num_params, elements, info);


                        CLVALUE cl_value;
                        cl_value.mLongValue = 0;
                        cl_value.mObjectValue = carray;
                        push_value_to_global_stack(cl_value, info);

                        stack_ptr-=num_params;

                        stack_ptr->mLongValue = 0;      // zero clera for jit
                        stack_ptr->mObjectValue = create_string_object(method_name, info);
                        stack_ptr++;
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = carray;
                        stack_ptr++;
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mIntValue = num_method_chains;
                        stack_ptr++;
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mIntValue = max_method_chains;
                        stack_ptr++;

                        pop_global_stack(info);

                        if(!invoke_method(klass, &method, stack, var_num, &stack_ptr, info)) {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }
                    }
                }
                break;

            case OP_INVOKE_BLOCK:
                {
                    int num_params = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    CLObject block_object = (stack_ptr-num_params-1)->mObjectValue;

                    if(!invoke_block(block_object, stack, var_num, num_params, &stack_ptr, info, FALSE)) 
                    {
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLVALUE result = *(stack_ptr-1);

                    stack_ptr -= num_params+1+1;

                    *stack_ptr = result;
                    stack_ptr++;
                }
                break;

            case OP_NEW:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    BOOL flg_array = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(3)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* type_name = CONS_str(constant, offset2);

                    if(flg_array) {
                        int array_num = (stack_ptr-1)->mIntValue;
                        stack_ptr--;

                        CLObject array = create_array_object(klass, array_num, info);
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = array;
                        stack_ptr++;
                    }
                    else {
                        CLObject obj = create_object(klass, type_name, info);
                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = obj;
                        stack_ptr++;
                    }
                }
                break;

            case OP_LOAD_FIELD:
                {
                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -1)->mObjectValue;
                    stack_ptr--;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-4)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(4)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(1). Field index is %d", field_index);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLVALUE value = object_pointer->mFields[field_index];
                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_LOAD_FIELD_ADDRESS:
                {
                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -1)->mObjectValue;
                    stack_ptr--;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(4)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(5)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(2). Field index is %d", field_index);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* value = (char*)&object_pointer->mFields[field_index];
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mPointerValue = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_FIELD:
                {
                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    int class_name_offset = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -2)->mObjectValue;
                    CLVALUE value = *(stack_ptr-1);

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(5)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(6-1)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(3). Object ID is %d. Field index is %d at %s.%s", obj, field_index, info->running_class_name, info->running_method_name);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLClass* obj_klass = object_pointer->mClass;

                    char* field_class_name = CONS_str(constant, class_name_offset);

                    sCLClass* field_class = get_class_with_load_and_initialize(field_class_name);

                    if(field_class == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(6-2) %s", field_class_name);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    BOOL value_is_object = !(field_class->mFlags & CLASS_FLAGS_NO_FREE_OBJECT);

                    CLObject prev_obj = object_pointer->mFields[field_index].mObjectValue;

                    object_pointer->mFields[field_index] = value;
                    stack_ptr-=2;
                    *stack_ptr = value;
                    stack_ptr++;

                    inc_refference_count(value.mObjectValue, prev_obj, value_is_object);
                }
                break;

            case OP_STORE_FIELD_OF_BUFFER:
                {
                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    CLObject obj = (stack_ptr -2)->mObjectValue;
                    CLVALUE value = *(stack_ptr-1);

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(5)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_pointer = CLOBJECT(obj);
                    sCLClass* klass = object_pointer->mClass;

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(6-3)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumFields) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(3). Field index is %d", field_index);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLObject obj2 = object_pointer->mFields[field_index].mObjectValue;

                    if(obj2 == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-5)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(obj2);

                    char* p = value.mPointerValue;

                    if(p < object_data->mFields[0].mPointerValue || p >= object_data->mFields[0].mPointerValue + object_data->mFields[2].mULongValue) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Out of range on memory safe pointer");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    object_data->mFields[3].mPointerValue = value.mPointerValue;

                    stack_ptr-=2;
                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_LOAD_CLASS_FIELD:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(7)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(4). Field index is %d", field_index);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLField* field = klass->mClassFields + field_index;

                    *stack_ptr = field->mValue;
                    stack_ptr++;
                }
                break;

            case OP_LOAD_CLASS_FIELD_ADDRESS:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(8)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(55555). Field index is %d", field_index);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLField* field = klass->mClassFields + field_index;
                    char* value = (char*)&field->mValue;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mPointerValue = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_CLASS_FIELD:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(9)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(6). Field index is %d", field_index);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLVALUE value = *(stack_ptr-1);

                    mark_and_store_class_field(klass, field_index, value);
                }
                break;

            case OP_STORE_CLASS_FIELD_OF_BUFFER:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int field_index = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(9)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    if(field_index < 0 || field_index >= klass->mNumClassFields) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "field index is invalid(6). Field index is %d", field_index);
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLVALUE value = *(stack_ptr-1);

                    sCLField* field = klass->mClassFields + field_index;

                    CLObject object = field->mValue.mObjectValue;

                    if(object == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-6)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(object);

                    char* p = value.mPointerValue;

                    if(p < object_data->mFields[0].mPointerValue || p >= object_data->mFields[0].mPointerValue + object_data->mFields[2].mULongValue) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Out of range on memory safe pointer");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    object_data->mFields[3].mPointerValue = value.mPointerValue;

                    //gc(info);
                }
                break;

            case OP_LOAD_ELEMENT:
                {
                    int tmp = *(int*)pc;
                    pc += sizeof(int);

                    CLObject array = (stack_ptr -2)->mObjectValue;
                    int element_num = (stack_ptr -1)->mIntValue;
                    stack_ptr-=2;

                    if(array == 0) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(7)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_pointer = CLOBJECT(array);

                    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "element index is invalid(1)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLVALUE value = object_pointer->mFields[element_num];
                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_ELEMENT:
                {
                    CLObject array = (stack_ptr -3)->mObjectValue;
                    int element_num = (stack_ptr -2)->mIntValue;
                    CLVALUE value = *(stack_ptr-1);

                    if(array == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(8)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_pointer = CLOBJECT(array);

                    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "element index is invalid(2)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLClass* klass = object_pointer->mClass;

                    BOOL value_is_object = !(klass->mFlags & CLASS_FLAGS_NO_FREE_OBJECT);

                    CLObject prev_obj = object_pointer->mFields[element_num].mObjectValue;

                    object_pointer->mFields[element_num] = value;

                    inc_refference_count(value.mObjectValue, prev_obj, value_is_object);

                    stack_ptr-=3;
                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_ELEMENT_OF_BUFFER:
                {
                    CLObject array = (stack_ptr -3)->mObjectValue;
                    int element_num = (stack_ptr -2)->mIntValue;
                    CLVALUE value = *(stack_ptr-1);

                    if(array == 0) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(8)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_pointer = CLOBJECT(array);

                    if(element_num < 0 || element_num >= object_pointer->mArrayNum) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "element index is invalid(3)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }


                    CLObject object = object_pointer->mFields[element_num].mObjectValue;

                    if(object == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-7)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }
                    sCLObject* object_data = CLOBJECT(object);

                    char* p = value.mPointerValue;

                    if(p < object_data->mFields[0].mPointerValue || p >= object_data->mFields[0].mPointerValue + object_data->mFields[2].mULongValue) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Out of range on memory safe pointer");

                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }
                    object_data->mFields[3].mPointerValue = value.mPointerValue;

                    stack_ptr-=3;
                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_INT_ADDRESS:
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mIntValue = value.mIntValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_UINT_ADDRESS: 
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mUIntValue = value.mUIntValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_BYTE_ADDRESS: 
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mByteValue = value.mByteValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_UBYTE_ADDRESS: 
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mUByteValue = value.mUByteValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_SHORT_ADDRESS: 
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mShortValue = value.mShortValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_USHORT_ADDRESS: 
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mUShortValue = value.mUShortValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_LONG_ADDRESS:
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mLongValue = value.mLongValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_ULONG_ADDRESS: 
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mULongValue = value.mULongValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_FLOAT_ADDRESS: 
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mFloatValue = value.mFloatValue;


                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_DOUBLE_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mDoubleValue = value.mDoubleValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_STORE_VALUE_TO_POINTER_ADDRESS:
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mPointerValue = value.mPointerValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;
                }
                break;

            case OP_STORE_VALUE_TO_CHAR_ADDRESS:
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mCharValue = value.mCharValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_STORE_VALUE_TO_BOOL_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/
                    pointer->mBoolValue = value.mBoolValue;

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_STORE_VALUE_TO_OBJECT_ADDRESS:
                {
                    CLVALUE address = *(stack_ptr-2);
                    CLVALUE value = *(stack_ptr-1);

                    CLVALUE* pointer = (CLVALUE*)address.mPointerValue;
/*
#ifndef __BIG_ENDIAN__

                    pointer->mLongValue = 0;              // zero clear for jit
#endif
*/

                    CLObject prev_obj = pointer->mObjectValue;

                    pointer->mObjectValue = value.mObjectValue;

                    inc_refference_count(value.mObjectValue, prev_obj, TRUE);

                    stack_ptr-=2;

                    *stack_ptr = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_INT_ADDRESS:
                {
                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    int value = *(int*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mIntValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_UINT_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned int value = *(unsigned  int*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mUIntValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_BYTE_ADDRESS:
                {
                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    char value = *(char*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mByteValue = value;
                    stack_ptr++;
                }
                break;

            case OP_LOAD_VALUE_FROM_UBYTE_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned char value = *(unsigned char*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mUByteValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_SHORT_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    short value = *(short*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mShortValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_USHORT_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned short value = *(unsigned short*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mUShortValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_LONG_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    clint64 value = *(clint64*)address.mPointerValue;

                    stack_ptr->mLongValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_ULONG_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    unsigned clint64 value = *(unsigned clint64*)address.mPointerValue;

                    stack_ptr->mULongValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_FLOAT_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    float value = *(float*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mFloatValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    double value = *(double*)address.mPointerValue;

                    stack_ptr->mDoubleValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_POINTER_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    char* value = *(char**)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mPointerValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_CHAR_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    wchar_t value = *(wchar_t*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mCharValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_BOOL_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    BOOL value = *(BOOL*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mBoolValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_LOAD_VALUE_FROM_OBJECT_ADDRESS:
                {
                    

                    CLVALUE address = *(stack_ptr-1);
                    stack_ptr--;

                    CLObject value = *(CLObject*)address.mPointerValue;

                    stack_ptr->mLongValue = 0;           // zero clear for jit
                    stack_ptr->mObjectValue = value;
                    stack_ptr++;

                    
                }
                break;

            case OP_UBYTE_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_SHORT_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_USHORT_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_INT_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_UINT_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_LONG_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_ULONG_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_POINTER_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CHAR_TO_BYTE_CAST:
                {
                    

                    char value = (char)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CBYTE_TO_BYTE_CAST:
                {
                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-8)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;
                }
                break;

            case OP_CUBYTE_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-9)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-10)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-11)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-12)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-13)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CLONG_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-14)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CULONG_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-15)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-16)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-17)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-18)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-19)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_BYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-20)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    char value = (char)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mByteValue = value;

                    
                }
                break;


            case OP_BYTE_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_USHORT_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_INT_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_UINT_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_LONG_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_ULONG_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_POINTER_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;
                
            case OP_CHAR_TO_SHORT_CAST:
                {
                    

                    short value = (short)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;


            case OP_CBYTE_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-21)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-22)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-23)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-24)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-25)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-26)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CLONG_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-27)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CULONG_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-28)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-29)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-30)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_SHORT_CAST:
                {
                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-31)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-32)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_SHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-33)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    short value = (short)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_BYTE_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_SHORT_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_USHORT_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_UINT_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_LONG_TO_INT_CAST:
                {
                    int value = (int)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_ULONG_TO_INT_CAST:
                {
                    int value = (int)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_POINTER_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CHAR_TO_INT_CAST:
                {
                    

                    int value = (int)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;


            case OP_CBYTE_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-34)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-35)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-36)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-37)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_INT_CAST:
                {
                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-38)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;
                }
                break;

            case OP_UINTEGER_TO_INT_CAST:
                {
                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-39)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CLONG_TO_INT_CAST:
                {
                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-40)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CULONG_TO_INT_CAST:
                {
                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-41)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;
                }
                break;

            case OP_CFLOAT_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-42)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-43)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-44)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-45)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_INT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-46)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    int value = (int)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mIntValue = value;

                    
                }
                break;

            case OP_BYTE_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_SHORT_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_USHORT_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_INT_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_UINT_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_ULONG_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_POINTER_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CHAR_TO_LONG_CAST:
                {
                    

                    clint64 value = (clint64)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CBYTE_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-47)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-48)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-49)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-50)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-51)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-52)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CLONG_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-53)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CULONG_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-54)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-55)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-56)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-57)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-58)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_LONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-59)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    clint64 value = (clint64)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = value;

                    
                }
                break;

            case OP_BYTE_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_SHORT_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_USHORT_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_INT_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mIntValue;
                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_UINT_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_LONG_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_ULONG_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_POINTER_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CHAR_TO_UBYTE_CAST:
                {
                    

                    unsigned char value = (unsigned char)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CBYTE_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-60)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-61)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-62)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-63)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-64)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-65)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CLONG_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-66)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CULONG_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-67)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-68)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-69)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-70)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-71)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_UBYTE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-72)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned char value = (unsigned char)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUByteValue = value;

                    
                }
                break;

            case OP_BYTE_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mShortValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_SHORT_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_INT_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_UINT_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_LONG_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_ULONG_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_POINTER_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;
                
            case OP_CHAR_TO_USHORT_CAST:
                {
                    

                    unsigned short value = (unsigned short)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CBYTE_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-73)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-74)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-75)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-76)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-77)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-78)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CLONG_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-78)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CULONG_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-79)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-80)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-81)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-82)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-83)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_USHORT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-84)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned short value = (unsigned short)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUShortValue = value;

                    
                }
                break;


            case OP_BYTE_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_SHORT_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_USHORT_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_INT_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;


            case OP_LONG_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_ULONG_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_POINTER_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CHAR_TO_UINT_CAST:
                {
                    

                    unsigned int value = (unsigned int)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CBYTE_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-85)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-86)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-87)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-88)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-89)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-90)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CLONG_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-91)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CULONG_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-92)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-93)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-94)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-95)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-96)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_UINT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-97)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned int value = (unsigned int)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mUIntValue = value;

                    
                }
                break;



            case OP_BYTE_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_SHORT_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_USHORT_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_INT_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_UINT_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_LONG_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_POINTER_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CHAR_TO_ULONG_CAST:
                {
                    

                    unsigned clint64 value = (unsigned clint64)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;


            case OP_CBYTE_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-98)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-99)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-100)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-101)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-102)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-103)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CLONG_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-104)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CULONG_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-105)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-106)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-107)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-108)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-109)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_ULONG_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-110)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    unsigned clint64 value = (unsigned clint64)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mULongValue = value;

                    
                }
                break;


            case OP_BYTE_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_SHORT_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_USHORT_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_INT_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_UINT_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_LONG_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_ULONG_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_DOUBLE_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;
                
            case OP_CHAR_TO_FLOAT_CAST:
                {
                    

                    float value = (float)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;


            case OP_CBYTE_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-111)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-112)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-113)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-114)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-115)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-116)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CLONG_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-117)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CULONG_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-118)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-119)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-120)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;


            case OP_CCHAR_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-121)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_FLOAT_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-122)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    float value = (float)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mFloatValue = value;

                    
                }
                break;



            case OP_BYTE_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_SHORT_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_USHORT_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_INT_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_UINT_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_LONG_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_ULONG_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_FLOAT_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;
                
            case OP_CHAR_TO_DOUBLE_CAST:
                {
                    

                    double value = (double)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;


            case OP_CBYTE_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-123)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-124)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-125)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-126)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-128)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-129)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CLONG_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-130)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CULONG_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-131)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-132)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-133)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-134)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_DOUBLE_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-135)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    double value = (double)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mDoubleValue = value;

                    
                }
                break;

            case OP_BYTE_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;

            case OP_SHORT_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;

            case OP_USHORT_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;
                
            case OP_INT_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;
                
            case OP_UINT_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;

            case OP_LONG_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;

            case OP_ULONG_TO_POINTER_CAST:
                {
                    

                    char* value = (char*)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;
                
            case OP_CHAR_TO_POINTER_CAST:
                {
                    char* value = (char*)(stack_ptr-1)->mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mPointerValue = value;

                    
                }
                break;

            case OP_BUFFER_TO_POINTER_CAST:
                {
                    CLObject object = (stack_ptr-1)->mObjectValue;

                    if(object == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-136)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* object_data = CLOBJECT(object);

                    char* pointer_value = object_data->mFields[3].mPointerValue;

                    CLVALUE cl_value;
                    cl_value.mObjectValue = object;
                    push_value_to_global_stack(cl_value, info);

                    (stack_ptr-1)->mLongValue = 0;
                    (stack_ptr-1)->mPointerValue = pointer_value;
                }
                break;

            case OP_BYTE_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_UBYTE_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_SHORT_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_USHORT_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;


            case OP_INT_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_UINT_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_LONG_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_ULONG_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;


            case OP_FLOAT_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;
                
            case OP_DOUBLE_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;
                
            case OP_POINTER_TO_CHAR_CAST:
                {
                    

                    wchar_t value = (wchar_t)(stack_ptr-1)->mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CBYTE_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-137)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CUBYTE_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-138)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mUByteValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CSHORT_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-139)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CUSHORT_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-140)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mUShortValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_INTEGER_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-141)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_UINTEGER_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-142)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mUIntValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CLONG_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-143)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mLongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CULONG_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-144)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mULongValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CFLOAT_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-145)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mFloatValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CDOUBLE_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-146)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mDoubleValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CPOINTER_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-147)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mPointerValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CCHAR_TO_CHAR_CAST:
                {
                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-148)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mCharValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;

            case OP_CBOOL_TO_CHAR_CAST:
                {
                    

                    CLObject obj = (stack_ptr-1)->mObjectValue;

                    if(obj == 0) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "Null pointer exception(3-149)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    sCLObject* obj_data = CLOBJECT(obj);

                    wchar_t value = (wchar_t)obj_data->mFields[0].mBoolValue;

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mCharValue = value;

                    
                }
                break;
                
            case OP_BYTE_TO_STRING_CAST:
                {
                    

                    char value = (stack_ptr-1)->mCharValue;

                    char buf[32];
                    snprintf(buf, 32, "%d", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_SHORT_TO_STRING_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    char buf[32];
                    snprintf(buf, 32, "%d", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_INT_TO_STRING_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    char buf[32];
                    snprintf(buf, 32, "%d", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_LONG_TO_STRING_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    char buf[32];
                    snprintf(buf, 32, "%lld", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_UBYTE_TO_STRING_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    char buf[32];
                    snprintf(buf, 32, "%u", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_USHORT_TO_STRING_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    char buf[32];
                    snprintf(buf, 32, "%u", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_UINT_TO_STRING_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    char buf[32];
                    snprintf(buf, 32, "%u", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_ULONG_TO_STRING_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    char buf[32];
                    snprintf(buf, 32, "%llu", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_FLOAT_TO_STRING_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    char buf[32];
                    snprintf(buf, 32, "%f", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_DOUBLE_TO_STRING_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    char buf[32];
                    snprintf(buf, 32, "%lf", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_BOOL_TO_STRING_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    char buf[32];
                    if(value) {
                        snprintf(buf, 32, "true");
                    }
                    else {
                        snprintf(buf, 32, "false");
                    }

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_REGEX_TO_STRING_CAST:
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;

                    sRegexObject* object_data = CLREGEX(regex);

                    CLObject str = create_string_object(object_data->mRegexString, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_POINTER_TO_STRING_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    char buf[32];
                    snprintf(buf, 32, "%p", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_CHAR_TO_STRING_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    char buf[32];
                    snprintf(buf, 32, "%lc", value);

                    CLObject str = create_string_object(buf, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = str;

                    
                }
                break;

            case OP_BYTE_TO_INTEGER_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_INTEGER_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_INTEGER_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_INTEGER_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_INTEGER_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_integer(value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_INTEGER_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_INTEGER_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_INTEGER_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_INTEGER_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_INTEGER_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_INTEGER_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_INTEGER_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_INTEGER_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_integer((int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_UINTEGER_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_UINTEGER_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_UINTEGER_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_UINTEGER_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_UINTEGER_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_UINTEGER_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_uinteger(value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_UINTEGER_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_UINTEGER_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_UINTEGER_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_UINTEGER_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_UINTEGER_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_UINTEGER_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_UINTEGER_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_uinteger((unsigned int)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CBYTE_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CBYTE_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CBYTE_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CBYTE_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CBYTE_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CBYTE_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CBYTE_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CBYTE_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CBYTE_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CBYTE_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CBYTE_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CBYTE_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CBYTE_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_byte((char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CUBYTE_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CUBYTE_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CUBYTE_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CUBYTE_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CUBYTE_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CUBYTE_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CUBYTE_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CUBYTE_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CUBYTE_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CUBYTE_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CUBYTE_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CUBYTE_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CUBYTE_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_ubyte((unsigned char)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CSHORT_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CSHORT_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CSHORT_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CSHORT_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CSHORT_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CSHORT_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CSHORT_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CSHORT_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CSHORT_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CSHORT_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CSHORT_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CSHORT_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CSHORT_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_short((short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CUSHORT_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CUSHORT_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CUSHORT_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CUSHORT_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CUSHORT_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CUSHORT_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CUSHORT_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CUSHORT_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CUSHORT_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CUSHORT_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CUSHORT_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CUSHORT_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CUSHORT_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_ushort((unsigned short)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CLONG_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CLONG_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CLONG_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CLONG_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CLONG_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CLONG_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CLONG_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CLONG_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CLONG_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CLONG_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CLONG_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CLONG_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CLONG_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_long((clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CULONG_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CULONG_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CULONG_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CULONG_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CULONG_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CULONG_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CULONG_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CULONG_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CULONG_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CULONG_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CULONG_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CULONG_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CULONG_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_ulong((unsigned clint64)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CFLOAT_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CFLOAT_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CFLOAT_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CFLOAT_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CFLOAT_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CFLOAT_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CFLOAT_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CFLOAT_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CFLOAT_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CFLOAT_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CFLOAT_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CFLOAT_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_float((float)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CDOUBLE_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CDOUBLE_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CDOUBLE_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CDOUBLE_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CDOUBLE_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CDOUBLE_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CDOUBLE_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CDOUBLE_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CDOUBLE_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CDOUBLE_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CDOUBLE_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CDOUBLE_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_double((double)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CPOINTER_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CPOINTER_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CPOINTER_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CPOINTER_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CPOINTER_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CPOINTER_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CPOINTER_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CPOINTER_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

                
            case OP_CHAR_TO_CPOINTER_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CPOINTER_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CPOINTER_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_pointer((char*)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CCHAR_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CCHAR_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CCHAR_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CCHAR_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CCHAR_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CCHAR_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CCHAR_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CCHAR_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CCHAR_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CCHAR_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CCHAR_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CCHAR_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CCHAR_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_char((wchar_t)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_BYTE_TO_CBOOL_CAST:
                {
                    

                    char value = (stack_ptr-1)->mByteValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UBYTE_TO_CBOOL_CAST:
                {
                    

                    unsigned char value = (stack_ptr-1)->mUByteValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_SHORT_TO_CBOOL_CAST:
                {
                    

                    short value = (stack_ptr-1)->mShortValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_USHORT_TO_CBOOL_CAST:
                {
                    

                    unsigned short value = (stack_ptr-1)->mUShortValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_INT_TO_CBOOL_CAST:
                {
                    

                    int value = (stack_ptr-1)->mIntValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_UINT_TO_CBOOL_CAST:
                {
                    

                    unsigned int value = (stack_ptr-1)->mUIntValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_LONG_TO_CBOOL_CAST:
                {
                    

                    clint64 value = (stack_ptr-1)->mLongValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_ULONG_TO_CBOOL_CAST:
                {
                    

                    unsigned clint64 value = (stack_ptr-1)->mULongValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_FLOAT_TO_CBOOL_CAST:
                {
                    

                    float value = (stack_ptr-1)->mFloatValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_DOUBLE_TO_CBOOL_CAST:
                {
                    

                    double value = (stack_ptr-1)->mDoubleValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_CHAR_TO_CBOOL_CAST:
                {
                    

                    wchar_t value = (stack_ptr-1)->mCharValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_POINTER_TO_CBOOL_CAST:
                {
                    

                    char* value = (stack_ptr-1)->mPointerValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;
                
            case OP_BOOL_TO_CBOOL_CAST:
                {
                    

                    BOOL value = (stack_ptr-1)->mBoolValue;

                    CLObject obj = create_bool((BOOL)value, info);

                    (stack_ptr-1)->mLongValue = 0;       // zero clear for jit
                    (stack_ptr-1)->mObjectValue = obj;

                    
                }
                break;

            case OP_ARRAY_TO_CARRAY_CAST: {
                

                int offset = *(int*)pc;
                pc += sizeof(int);

                char* class_name = CONS_str(constant, offset);

                sCLClass* klass = get_class_with_load_and_initialize(class_name);

                if(klass == NULL) {
                    entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(10)");
                    if(info->try_code == code && info->try_offset != 0) {
                        pc = code->mCodes + info->try_offset;
                        info->try_offset = 0;
                        info->try_code = NULL;
                        break;
                    }
                    else {
                        remove_stack_to_stack_list(stack_id);
                        return FALSE;
                    }
                }

                CLObject array = (stack_ptr-1)->mObjectValue;
                sCLObject* array_data = CLOBJECT(array);
                int array_num = array_data->mArrayNum;

                sCLClass* klass2 = get_class("Array");
                MASSERT(klass2 != NULL);

                char type_name[OBJECT_TYPE_NAME_MAX];
                snprintf(type_name, OBJECT_TYPE_NAME_MAX, "Array<%s>", CLASS_NAME(klass));

                CLObject new_array = create_object(klass2, type_name, info);

                stack_ptr->mLongValue = 0;       // zero clear for jit
                stack_ptr->mObjectValue = new_array;   // push object
                stack_ptr++;

                CLObject new_primitive_array;
                if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
                    new_primitive_array = create_array_object(klass->mBoxingClass, array_num, info);
                }
                else {
                    new_primitive_array = create_array_object(klass, array_num, info);
                }

                sCLObject* new_array_data = CLOBJECT(new_array);

                new_array_data->mFields[0].mLongValue = 0;
                new_array_data->mFields[0].mObjectValue = new_primitive_array;

                /// boxing element ///
                int i;
                for(i=0; i<array_num; i++ ) {
                    array_data = CLOBJECT(array);           // reget for GC

                    CLVALUE element;
                    boxing_primitive_value_to_object(array_data->mFields[i], &element, klass, info);

                    sCLObject* new_primitive_array_data = CLOBJECT(new_primitive_array);
                    new_primitive_array_data->mFields[i] = element;
                }

                stack_ptr-=2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = new_array;
                stack_ptr++;

                
                }
                break;
                
            case OP_GET_ARRAY_LENGTH:
                {
                    

                    CLObject array = (stack_ptr-1)->mObjectValue;
                    sCLObject* array_data = CLOBJECT(array);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mIntValue = array_data->mArrayNum;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_GLOBAL :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mGlobal;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_IGNORE_CASE :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mIgnoreCase;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_MULTILINE :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mMultiline;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_EXTENDED :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mExtended;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_DOTALL :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mDotAll;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_ANCHORED :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mAnchored;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_DOLLAR_ENDONLY :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mDollarEndOnly;
                    stack_ptr++;

                    
                }
                break;

            case OP_GET_REGEX_UNGREEDY :
                {
                    

                    CLObject regex = (stack_ptr-1)->mObjectValue;
                    sRegexObject* regex_object = CLREGEX(regex);
                    stack_ptr--;

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mBoolValue = regex_object->mUngreedy;
                    stack_ptr++;

                    
                }
                break;

            case OP_CHAR_UPPERCASE:
                {
                    

                    wchar_t c = (stack_ptr-1)->mCharValue;

                    wchar_t result = c;
                    if(c >= 'a' && c <= 'z') {
                        result = c - 'a' + 'A';
                    }

                    (stack_ptr-1)->mLongValue = 0;              // zero clear for jit
                    (stack_ptr-1)->mCharValue = result;

                    
                }
                break;

            case OP_CHAR_LOWERCASE:
                {
                    

                    wchar_t c = (stack_ptr-1)->mCharValue;

                    wchar_t result = c;
                    if(c >= 'A' && c <= 'Z') {
                        result = c - 'A' + 'a';
                    }

                    (stack_ptr-1)->mLongValue = 0;              // zero clear for jit
                    (stack_ptr-1)->mCharValue = result;

                    
                }
                break;

            case OP_CREATE_STRING:
                {
                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int num_string_expression = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    if(num_string_expression == 0) {
                        CLObject string_object = create_string_object(str, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = string_object;
                        stack_ptr++;
                    }
                    else {
                        int string_expression_offsets[STRING_EXPRESSION_MAX];
                        CLObject string_expression_object[STRING_EXPRESSION_MAX];

                        int i;
                        for(i=0; i<num_string_expression; i++) {
                            string_expression_offsets[i] = *(int*)pc;
                            pc += sizeof(int);

                            string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                        }

                        sBuf buf;
                        sBuf_init(&buf);

                        if(!string_expression(str, strlen(str), &buf, string_expression_offsets, string_expression_object, num_string_expression, &stack_ptr, stack, var_num, info))
                        {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                
                                MFREE(buf.mBuf);
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        stack_ptr -= num_string_expression;

                        CLObject string_object = create_string_object(buf.mBuf, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = string_object;
                        stack_ptr++;

                        MFREE(buf.mBuf);
                    }

                    
                }
                break;

            case OP_CREATE_BUFFER:
                {
                    

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int size = *(int*)pc;
                    pc += sizeof(int);

                    int num_string_expression = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    if(num_string_expression == 0) {
                        CLObject buffer_object = create_buffer_object(str, size, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = buffer_object;
                        stack_ptr++;
                    }
                    else {
                        int string_expression_offsets[STRING_EXPRESSION_MAX];
                        CLObject string_expression_object[STRING_EXPRESSION_MAX];

                        int i;
                        for(i=0; i<num_string_expression; i++) {
                            string_expression_offsets[i] = *(int*)pc;
                            pc += sizeof(int);

                            string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                        }

                        sBuf buf;
                        sBuf_init(&buf);

                        if(!string_expression(str, size, &buf, string_expression_offsets, string_expression_object, num_string_expression, &stack_ptr, stack, var_num, info))
                        {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                
                                MFREE(buf.mBuf);
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        stack_ptr -= num_string_expression;

                        CLObject buffer_object = create_buffer_object(buf.mBuf, buf.mLen, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = buffer_object;
                        stack_ptr++;

                        MFREE(buf.mBuf);
                    }

                    
                }
                break;

            case OP_CREATE_PATH:
                {
                    

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int num_string_expression = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    if(num_string_expression == 0) {
                        CLObject path_object = create_path_object(str, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = path_object;
                        stack_ptr++;
                    }
                    else {
                        int string_expression_offsets[STRING_EXPRESSION_MAX];
                        CLObject string_expression_object[STRING_EXPRESSION_MAX];

                        int i;
                        for(i=0; i<num_string_expression; i++) {
                            string_expression_offsets[i] = *(int*)pc;
                            pc += sizeof(int);

                            string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                        }

                        sBuf buf;
                        sBuf_init(&buf);

                        if(!string_expression(str, strlen(str), &buf, string_expression_offsets, string_expression_object, num_string_expression, &stack_ptr, stack, var_num, info))
                        {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                
                                MFREE(buf.mBuf);
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        stack_ptr -= num_string_expression;

                        CLObject path_object = create_path_object(buf.mBuf, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = path_object;
                        stack_ptr++;

                        MFREE(buf.mBuf);
                    }

                    
                }
                break;

            case OP_CREATE_ARRAY:
                {
                    

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(11)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    CLObject array_object = create_array_object(klass, num_elements, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = array_object; // push object
                    stack_ptr++;

                    sCLObject* object_data = CLOBJECT(array_object);

                    int i;
                    for(i=0; i<num_elements; i++) {
                        object_data->mFields[i] = *(stack_ptr-1-num_elements+i);
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;

                    
                }
                break;

            case OP_CREATE_CARRAY:
                {
                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* type_name = CONS_str(constant, offset2);

                    CLObject array_object = create_carray_object(type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
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
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;
                }
                break;

            case OP_CREATE_EQUALABLE_CARRAY:
                {
                    

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* type_name = CONS_str(constant, offset2);

                    CLObject array_object = create_equalable_carray_object(type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
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
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;

                    
                }
                break;

            case OP_CREATE_SORTABLE_CARRAY:
                {
                    

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(12)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* type_name = CONS_str(constant, offset2);

                    CLObject array_object = create_sortable_carray_object(type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
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
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = array_object;
                    stack_ptr++;

                    
                }
                break;

            case OP_CREATE_LIST:
                {
                    

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* type_name = CONS_str(constant, offset2);

                    CLObject list_object = create_list_object(type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
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
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = list_object;
                    stack_ptr++;

                    
                }
                break;

            case OP_CREATE_SORTALBE_LIST:
                {
                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* type_name = CONS_str(constant, offset2);

                    CLObject list_object = create_sortable_list_object(type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
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
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = list_object;
                    stack_ptr++;
                }
                break;

            case OP_CREATE_EQUALABLE_LIST:
                {
                    

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(13)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    char* type_name = CONS_str(constant, offset2);

                    CLObject list_object = create_equalable_list_object(type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
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
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = list_object;
                    stack_ptr++;

                    
                }
                break;

            case OP_CREATE_TUPLE:
                {
                    

                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* type_name = CONS_str(constant, offset);

                    CLObject tuple_object = create_tuple_object(num_elements, type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
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
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = tuple_object;
                    stack_ptr++;

                    
                }
                break;

            case OP_CREATE_HASH:
                {
                    int num_elements = *(int*)pc;
                    pc += sizeof(int);

                    int offset = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name = CONS_str(constant, offset);

                    sCLClass* klass = get_class_with_load_and_initialize(class_name);

                    if(klass == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(14)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    int offset2 = *(int*)pc;
                    pc += sizeof(int);

                    int offset3 = *(int*)pc;
                    pc += sizeof(int);

                    char* class_name2 = CONS_str(constant, offset2);

                    sCLClass* klass2 = get_class_with_load_and_initialize(class_name2);

                    if(klass2 == NULL) {
                        
                        entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(15)");
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
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

                    char* type_name = CONS_str(constant, offset3);

                    CLObject hash_object = create_hash_object(type_name, info);
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = hash_object; // push object
                    stack_ptr++;

                    if(!initialize_hash_object(hash_object, num_elements, keys, items, stack, var_num, &stack_ptr, info, klass, klass2))
                    {
                        if(info->try_code == code && info->try_offset != 0) {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = NULL;
                            break;
                        }
                        else {
                            remove_stack_to_stack_list(stack_id);
                            return FALSE;
                        }
                    }

                    stack_ptr--; // pop_object

                    stack_ptr-=num_elements*2;
                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = hash_object;
                    stack_ptr++;

                    
                }
                break;

            case OP_CREATE_BLOCK_OBJECT:
                {
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

                    int block_id = *(int*)pc;
                    pc += sizeof(int);

                    int class_name_offset = *(int*)pc;
                    pc += sizeof(int);

                    sCLClass* klass = NULL;
                    if(class_name_offset == -1) {
                        klass = NULL;
                    }
                    else {
                        char* class_name = CONS_str(constant, class_name_offset);

                        sCLClass* klass = get_class_with_load_and_initialize(class_name);

                        if(klass == NULL) {
                            entry_exception_object_with_class_name(&stack_ptr, stack, var_num, info, "Exception", "class not found(99) %s", class_name);
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }
                    }

                    CLVALUE* parent_stack = stack;

                    CLObject block_object = create_block_object(&codes2, &constant2, parent_stack, parent_var_num, block_var_num, lambda, block_id, klass, info);

                    stack_ptr->mLongValue = 0;              // zero clear for jit
                    stack_ptr->mObjectValue = block_object;
                    stack_ptr++;
                }
                break;

            case OP_CREATE_REGEX:
                {
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

                    int num_string_expression = *(int*)pc;
                    pc += sizeof(int);

                    char* str = CONS_str(constant, offset);

                    if(num_string_expression == 0) {
                        CLObject regex_object = create_regex_object(str, global, ignore_case, multiline, extended, dotall, anchored, dollar_endonly, ungreedy, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = regex_object;
                        stack_ptr++;
                    }
                    else {
                        int string_expression_offsets[STRING_EXPRESSION_MAX];
                        CLObject string_expression_object[STRING_EXPRESSION_MAX];

                        int i;
                        for(i=0; i<num_string_expression; i++) {
                            string_expression_offsets[i] = *(int*)pc;
                            pc += sizeof(int);

                            string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                        }

                        sBuf buf;
                        sBuf_init(&buf);

                        if(!string_expression(str, strlen(str), &buf, string_expression_offsets, string_expression_object, num_string_expression, &stack_ptr, stack, var_num, info))
                        {
                            if(info->try_code == code && info->try_offset != 0) {
                                pc = code->mCodes + info->try_offset;
                                info->try_offset = 0;
                                info->try_code = NULL;
                                break;
                            }
                            else {
                                
                                MFREE(buf.mBuf);
                                remove_stack_to_stack_list(stack_id);
                                return FALSE;
                            }
                        }

                        stack_ptr -= num_string_expression;

                        CLObject regex_object = create_regex_object(buf.mBuf, global, ignore_case, multiline, extended, dotall, anchored, dollar_endonly, ungreedy, info);

                        stack_ptr->mLongValue = 0;              // zero clear for jit
                        stack_ptr->mObjectValue = regex_object;
                        stack_ptr++;

                        MFREE(buf.mBuf);
                    }

                    
                }
                break;

        }

        if(!info->no_mutex_in_vm) {
            vm_mutex_off();
        }
//show_stack(stack, stack_ptr);
    }


    if(!info->no_mutex_in_vm) {
        vm_mutex_on();  // for invoke_method after running vm must be turn mutex on
    }
    
    remove_stack_to_stack_list(stack_id);

    return TRUE;
}
