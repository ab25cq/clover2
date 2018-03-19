#include "common.h"

sCLClass* get_class_from_cl_type(sCLType* cl_type, sCLClass* klass)
{
    char* class_name = CONS_str(&klass->mConst, cl_type->mClassNameOffset);

    return get_class_with_load_and_initialize(class_name);
}

BOOL is_void_type(sCLType* cl_type, sCLClass* klass)
{
    sCLClass* klass2 = get_class_from_cl_type(cl_type, klass);

    return klass2 == get_class("Null");
}

static void cl_type_to_string_core(sCLType* cl_type, sCLClass* klass, sBuf* buf)
{
    sBuf_append_str(buf, CONS_str(&klass->mConst, cl_type->mClassNameOffset));

    if(cl_type->mNumGenericsTypes > 0) {
        sBuf_append_str(buf, "<");

        int i;
        for(i=0; i<cl_type->mNumGenericsTypes; i++) {
            cl_type_to_string_core(cl_type->mGenericsTypes[i], klass, buf);

            if(i != cl_type->mNumGenericsTypes -1) {
                sBuf_append_str(buf, ",");
            }
        }

        sBuf_append_str(buf, ">");
    }

    if(cl_type->mArray) {
        sBuf_append_str(buf, "[]");
    }
    if(cl_type->mNullable) {
        sBuf_append_str(buf, "?");
    }

    if(cl_type->mBlockType) {
        sCLBlockType* block = cl_type->mBlockType;

        sBuf_append_str(buf, "(");

        int i;
        for(i=0; i<block->mNumParams; i++) {
            cl_type_to_string_core(block->mParams[i], klass, buf);

            if(i != block->mNumParams - 1) {
                sBuf_append_str(buf, ",");
            }
        }

        sBuf_append_str(buf, "):");

        cl_type_to_string_core(block->mResultType, klass, buf);
    }
}

ALLOC char* cl_type_to_string(sCLType* cl_type, sCLClass* klass)
{
    sBuf buf;
    sBuf_init(&buf);

    cl_type_to_string_core(cl_type, klass, &buf);

    return buf.mBuf;
}

BOOL is_this_class_with_class_name(sCLClass* klass, char* class_name)
{
    sCLClass* klass2 = get_class_with_load_and_initialize(class_name);
    MASSERT(klass2 != NULL);
    return klass == klass2;
}
