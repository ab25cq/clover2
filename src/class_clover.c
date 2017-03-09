#include "common.h"

BOOL Clover_load(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    CLVALUE* file_name = lvar;

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
