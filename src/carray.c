#include "common.h"

CLObject create_carray_object()
{
    sCLClass* klass = get_class("Array");
    MASSERT(klass != NULL);
    CLObject obj = create_object(klass);

    return obj;
}

CLObject create_carray_object_with_elements(int num_elements, CLObject* elements)
{
    CLObject obj = create_carray_object();

    gGlobalStackPtr->mObjectValue = obj;
    gGlobalStackPtr++;

    sCLClass* object_class = get_class("Object");
    MASSERT(object_class != NULL);

    CLObject array = create_array_object(object_class, num_elements);
    sCLObject* obj_data = CLOBJECT(obj);
    obj_data->mFields[0].mObjectValue = array;

    sCLObject* obj_data2 = CLOBJECT(array);

    int i;
    for(i=0; i<num_elements; i++) {
        obj_data2->mFields[i].mObjectValue = elements[i];
    }

    gGlobalStackPtr--;

    return obj;
}

BOOL initialize_carray_object(CLObject array_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items)
{
    sCLClass* klass = get_class("Array");

    char* method_name_and_params = "initialize(GenericsParametorClass0[])";
    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    (*stack_ptr)->mObjectValue = array_object;  // self
    (*stack_ptr)++;

    CLObject items_array = create_array_object(class_items, num_elements);

    sCLObject* object_data2 = CLOBJECT(items_array);

    int i;
    for(i=0; i<num_elements; i++) {
        object_data2->mFields[i].mObjectValue = items[i];
    }

    (*stack_ptr)->mObjectValue = items_array;
    (*stack_ptr)++;

    if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
        return FALSE;
    }

    (*stack_ptr)--; // pop method result

    return TRUE;
}
