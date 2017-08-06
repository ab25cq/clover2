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

sVarTable* clone_var_table(sVarTable* lv_table)
{
    sVarTable* result = init_var_table();

    sVarTable* it = lv_table;

    sVar* p = it->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0) {
            (void)add_variable_to_table(result, p->mName, p->mType);
        }

        p++;

        if(p == lv_table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }

    if(it->mParent) {
        result->mParent = clone_var_table(it->mParent);
    }

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
            if(type_) {
                p->mType = clone_node_type(type_);
            }
            else {
                p->mType = NULL;
            }

            p->mBlockLevel = table->mBlockLevel;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                if(p->mBlockLevel < table->mBlockLevel) {
                    xstrncpy(p->mName, name, VAR_NAME_MAX);
                    p->mIndex = table->mVarNum++;
                    if(type_) {
                        p->mType = clone_node_type(type_);
                    }
                    else {
                        p->mType = NULL;
                    }
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

sVar* get_variable_from_index(sVarTable* table, int index)
{
    int hash_value;
    sVar* p;

    p = table->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0 && p->mIndex == index) {
            return p;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }

    return NULL;
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



void check_already_added_variable(sVarTable* table, char* name, struct sParserInfoStruct* info)
{
    sVar* var = get_variable_from_this_table_only(table, name);
    
    if(var != NULL) {
        parser_err_msg(info, "Variable (%s) has already_added in this variable table", name);
        info->err_num++;
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

int get_parent_var_num_of_sum(sVarTable* table)
{
    return get_sum_of_parent_var_num(table);
}

sVarTable* init_block_vtable(sVarTable* lv_table)
{
    sVarTable* new_table;

    new_table = init_var_table();
    if(lv_table) {
        new_table->mBlockLevel = lv_table->mBlockLevel + 1;
        new_table->mParent = lv_table;
    }
    else {
        new_table->mBlockLevel = 0;
        new_table->mParent = NULL;
    }

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

void show_vtable(sVarTable* table)
{
    sVarTable* it = table;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                printf("name %s\n", p->mName);
            }

            p++;

            if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        it = it->mParent;
    }
}
