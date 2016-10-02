#include "common.h"

CLObject create_hash_object()
{
    sCLClass* klass = get_class("Hash");

    CLObject obj = create_object(klass);

    return obj;
}

BOOL initialize_hash_object(CLObject hash_object, int num_elements, CLObject* keys, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_keys, sCLClass* class_items)
{
    sCLClass* klass = get_class("Hash");

    char* method_name_and_params = "initialize(GenericsParametorClass0[],GenericsParametorClass1[],uint)";
    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    (*stack_ptr)->mObjectValue = hash_object;  // self
    (*stack_ptr)++;

    CLObject keys_array = create_array_object(class_keys, num_elements);

    sCLObject* object_data = CLOBJECT(keys_array);

    int i;
    for(i=0; i<num_elements; i++) {
        object_data->mFields[i].mObjectValue = keys[i];
    }

    (*stack_ptr)->mObjectValue = keys_array;
    (*stack_ptr)++;

    CLObject items_array = create_array_object(class_items, num_elements);

    sCLObject* object_data2 = CLOBJECT(items_array);

    for(i=0; i<num_elements; i++) {
        object_data2->mFields[i].mObjectValue = items[i];
    }

    (*stack_ptr)->mObjectValue = items_array;
    (*stack_ptr)++;

    (*stack_ptr)->mUIntValue = num_elements;
    (*stack_ptr)++;

    if(!invoke_method(klass, method, stack, var_num, stack_ptr, info)) {
        return FALSE;
    }

    (*stack_ptr)--; // pop method result

    return TRUE;
}

