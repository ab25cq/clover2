#include "common.h"

CLObject create_tuple_object(int num_elements)
{
    char class_name[CLASS_NAME_MAX+1];
    snprintf(class_name, CLASS_NAME_MAX, "Tuple%d", num_elements);
    sCLClass* klass = get_class(class_name);
    MASSERT(klass != NULL);
    CLObject obj = create_object(klass);

    return obj;
}

BOOL initialize_tuple_object(CLObject tuple_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info)
{
    char class_name[CLASS_NAME_MAX+1];
    snprintf(class_name, CLASS_NAME_MAX, "Tuple%d", num_elements);
    sCLClass* klass = get_class(class_name);

    char method_name_and_params[1024];

    method_name_and_params[0] = '\0';

    xstrncpy(method_name_and_params, "initialize(", 1024);

    int i;
    for(i=0; i<num_elements; i++) {
        char class_name[CLASS_NAME_MAX+1];
        snprintf(class_name, CLASS_NAME_MAX, "GenericsParametorClass%d", i);
        xstrncat(method_name_and_params, class_name, 1024);

        if(i == num_elements-1) {
            xstrncat(method_name_and_params, ")", 1024);
        }
        else {
            xstrncat(method_name_and_params, ",", 1024);
        }
    }

    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    (*stack_ptr)->mObjectValue = tuple_object;  // self
    (*stack_ptr)++;

    for(i=0; i<num_elements; i++) {
        (*stack_ptr)->mObjectValue = items[i];
        (*stack_ptr)++;
    }

    if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
        return FALSE;
    }

    (*stack_ptr)--; // pop method result

    return TRUE;
}
