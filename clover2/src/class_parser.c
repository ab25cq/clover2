#include "common.h"

BOOL CLParser_initialize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info)
{
    sCLClass* parser = get_class("CLParser");

    parser->mClassFields[0].mValue.mIntValue = GENERICS_TYPES_MAX;
    parser->mClassFields[1].mValue.mIntValue = PARAMS_MAX;

    return TRUE;
}
