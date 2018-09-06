#include "common.h"

CLObject create_list_object(char* type_name, sVMInfo* info)
{
    sCLClass* klass = get_class("List");
    MASSERT(klass != NULL);
    CLObject obj = create_object(klass, type_name, info);

    return obj;
}

BOOL initialize_list_object(CLObject list_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items)
{
    sCLClass* klass = get_class("List");

    char* method_name_and_params = "initialize(GenericsParametorClass0[],uint)";
    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    (*stack_ptr)->mObjectValue = list_object;  // self
    (*stack_ptr)++;

    CLObject items_array = create_array_object(class_items, num_elements, info);
    inc_refference_count(items_array);

    sCLObject* object_data2 = CLOBJECT(items_array);

    int i;
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

CLObject create_sortable_list_object(char* type_name, sVMInfo* info)
{
    sCLClass* klass = get_class("SortableList");
    MASSERT(klass != NULL);
    CLObject obj = create_object(klass, type_name, info);

    return obj;
}

BOOL initialize_sortable_list_object(CLObject list_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items)
{
    sCLClass* klass = get_class("SortableList");

    char* method_name_and_params = "initialize(GenericsParametorClass0[],uint)";
    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    (*stack_ptr)->mObjectValue = list_object;  // self
    (*stack_ptr)++;

    CLObject items_array = create_array_object(class_items, num_elements, info);
    inc_refference_count(items_array);

    sCLObject* object_data2 = CLOBJECT(items_array);

    int i;
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

CLObject create_equalable_list_object(char* type_name, sVMInfo* info)
{
    sCLClass* klass = get_class("EqualableList");
    MASSERT(klass != NULL);
    CLObject obj = create_object(klass, type_name, info);

    return obj;
}

BOOL initialize_equalable_list_object(CLObject list_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items)
{
    sCLClass* klass = get_class("EqualableList");

    char* method_name_and_params = "initialize(GenericsParametorClass0[],uint)";
    sCLMethod* method = search_for_method_from_virtual_method_table(klass, method_name_and_params);

    (*stack_ptr)->mObjectValue = list_object;  // self
    (*stack_ptr)++;

    CLObject items_array = create_array_object(class_items, num_elements, info);
    inc_refference_count(items_array);

    sCLObject* object_data2 = CLOBJECT(items_array);

    int i;
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
