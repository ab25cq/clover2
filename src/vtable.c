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

static int get_sum_of_parent_var_num(sVarTable* table)
{
    int n = 0;
    sVarTable* p = table->mParent;

    while(p) {
        n += p->mVarNum;
        p = p->mParent;
    }

    return n;
}

int get_variable_index(sVarTable* table, char* name)
{
    sVarTable* it = table;

    while(it) {
        sVar* var = get_variable_from_this_table_only(it, name);

        if(var) {
            return var->mIndex + get_sum_of_parent_var_num(it);
        }

        it = it->mParent;
    }

    return -1;
}

int get_var_num(sVarTable* table)
{
    return table->mVarNum + table->mMaxBlockVarNum;
}

sVarTable* init_block_vtable(sVarTable* lv_table)
{
    sVarTable* new_table;

    MASSERT(lv_table != NULL);

    new_table = init_var_table();
    new_table->mBlockLevel = lv_table->mBlockLevel + 1;
    new_table->mParent = lv_table;

    return new_table;
}

void set_max_block_var_num(sVarTable* lv_table, sVarTable* old_table)
{
    /// get local var number of this block ///
    int lv_num_of_this_block = lv_table->mVarNum + lv_table->mMaxBlockVarNum;
    if(lv_num_of_this_block > old_table->mMaxBlockVarNum) {
       old_table->mMaxBlockVarNum = lv_num_of_this_block;
    }
}

