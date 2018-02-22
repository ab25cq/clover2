#include "common.h"

BOOL Clover_load(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* file_name = lvar;

    if(file_name->mObjectValue) {
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Null pointer exception");
        return FALSE;
    }

    /// Clover to c value ///
    char* file_name_value = ALLOC string_object_to_char_array(file_name->mObjectValue);

    /// go ///
    BOOL result = eval_file(file_name_value, CLOVER_STACK_SIZE);

    if(!result) {
        MFREE(file_name_value);
        entry_exception_object_with_class_name(stack_ptr, info->current_stack, info->current_var_num, info, "Exception", "Clover.load is faield");
        return FALSE;
    }

    MFREE(file_name_value);

    return TRUE;
}

BOOL Clover_initialize_lang(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* clover = get_class("Clover");

    clover->mClassFields[0].mValue.mIntValue = gARGC;

    sCLClass* string_class = get_class("String");

    CLObject array = create_array_object(string_class, gARGC);

    CLVALUE value;
    value.mObjectValue = array;
    push_value_to_global_stack(value);

    int i;
    for(i=0; i<gARGC; i++) {
        CLObject obj = create_string_object(gARGV[i]);

        sCLObject* object_data = CLOBJECT(array);

        object_data->mFields[i].mObjectValue = obj;
    }

    clover->mClassFields[1].mValue.mObjectValue = array;
    clover->mClassFields[2].mValue.mObjectValue = create_string_object(gVersion);

    pop_global_stack();

    return TRUE;
}
