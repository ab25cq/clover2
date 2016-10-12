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

BOOL is_this_class_with_class_name(sCLClass* klass, char* class_name)
{
    sCLClass* klass2 = get_class_with_load_and_initialize(class_name);
    MASSERT(klass2 != NULL);
    return klass == klass2;
}
