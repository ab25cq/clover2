#include "jit_common.hpp"

extern "C" 
{

//////////////////////////////////////////////////////////////////////
// VM functions
//////////////////////////////////////////////////////////////////////
BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, sVMInfo* info)
{
    if(!compile_jit_method(klass, method)) {
        return FALSE;
    }

    int object_stack_size = 1024;
    CLVALUE* object_stack = (CLVALUE*)MCALLOC(1, sizeof(CLVALUE)*object_stack_size);
    CLVALUE* object_stack_ptr = object_stack;

    long object_stack_id = append_stack_to_stack_list(object_stack, &object_stack_ptr);

    char method_path2[METHOD_NAME_MAX + 128];
    create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);
    
    auto ExprSymbol = TheJIT->findSymbol(method_path2);
    fJITMethodType function = nullptr;

    if(ExprSymbol) {
        function = (fJITMethodType)ExprSymbol.getAddress();
    }

    if(function != nullptr) {
        CLVALUE* stack_ptr = stack + var_num;
        CLVALUE* lvar = stack;

        long stack_id = append_stack_to_stack_list(stack, &stack_ptr);

        info->current_stack = stack;        // for invoking_block in native method
        info->current_var_num = var_num;
        info->stack_id = stack_id;

        BOOL result = function(stack_ptr, lvar, info, stack, &stack_ptr, var_num, object_stack, &object_stack_ptr);
        if(!result) {
            remove_stack_to_stack_list(stack, &stack_ptr);
            remove_stack_to_stack_list(object_stack, &object_stack_ptr);
            MFREE(object_stack);
            return FALSE;
        }

        remove_stack_to_stack_list(stack, &stack_ptr);
    }
    else {
        BOOL result = vm(code, constant, stack, var_num, klass, info);

        if(!result) {
            remove_stack_to_stack_list(object_stack, &object_stack_ptr);
            MFREE(object_stack);
            return FALSE;
        }
    }

    remove_stack_to_stack_list(object_stack, &object_stack_ptr);
    MFREE(object_stack);

    return TRUE;
}

} // extern "C"
