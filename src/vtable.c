#include "common.h"

sVarTable* gHeadVTable;

void init_vtable()
{
    gHeadVTable = NULL;
}

void final_vtable()
{
    sVarTable* it;

    it = gHeadVTable;
    while(it) {
        sVarTable* next;

        next = it->mNext;
        MFREE(it);

        it = next;
    }
}

sVarTable* init_var_table()
{
    sVarTable* result;

    result = MCALLOC(1, sizeof(sVarTable));

    result->mNext = gHeadVTable;
    gHeadVTable = result;

    return result;
}

//////////////////////////////////////////////////
// local variable table
//////////////////////////////////////////////////
// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_)
{
    int hash_value;
    sVar* p;

    hash_value = get_hash_key(name, LOCAL_VARIABLE_MAX);
    p = table->mLocalVariables + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            xstrncpy(p->mName, name, VAR_NAME_MAX);
            p->mIndex = table->mVarNum++;
            p->mType = type_;

            p->mBlockLevel = table->mBlockLevel;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                if(p->mBlockLevel < table->mBlockLevel) {
                    xstrncpy(p->mName, name, VAR_NAME_MAX);
                    p->mIndex = table->mVarNum++;
                    p->mType = type_;
                    p->mBlockLevel = table->mBlockLevel;

                    return TRUE;
                }
                else {
                    return FALSE;
                }
            }
            else {
                p++;

                if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
                    p = table->mLocalVariables;
                }
                else if(p == table->mLocalVariables + hash_value) {
                    return FALSE;
                }
            }
        }
    }
}

// result: (null) not found (sVar*) found
static sVar* get_variable_from_this_table_only(sVarTable* table, char* name)
{
    int hash_value;
    sVar* p;

    hash_value = get_hash_key(name, LOCAL_VARIABLE_MAX);

    p = table->mLocalVariables + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            p = table->mLocalVariables;
        }
        else if(p == table->mLocalVariables + hash_value) {
            return NULL;
        }
    }
}

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name)
{
    sVarTable* it;
    sVar* var;

    it = table;

    while(it) {
        var = get_variable_from_this_table_only(it, name);

        if(var) return var;

        it = it->mParent;
    }

    return NULL;
}

int get_var_num(sVarTable* table)
{
    return table->mVarNum + table->mMaxBlockVarNum;
}
