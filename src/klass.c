#include "common.h"

#define CLASS_NUM_MAX 512

struct sClassTableStruct
{
    char* mName;
    sCLClass* mItem;

    struct sClassTableStruct* mNextClass;
};

typedef struct sClassTableStruct sClassTable;

static sClassTable* gHeadClassTable = NULL;

static sClassTable gClassTable[CLASS_NUM_MAX];

unsigned int get_hash_key(char* name, unsigned int max)
{
    unsigned int result = 0;
    char* p = name;
    while(*p) {
        result += *p;
        p++;
    }

    return result % max;
}

static BOOL put_class_to_table(char* name, sCLClass* klass)
{
    unsigned int hash_key = get_hash_key(name, CLASS_NUM_MAX);
    sClassTable* p = gClassTable + hash_key;

    while(1) {
        if(p->mName == NULL) {
            p->mName = MSTRDUP(name);
            p->mItem = klass;

            p->mNextClass = gHeadClassTable;
            gHeadClassTable = p;
            break;
        }
        else {
            p++;

            if(p == gClassTable + CLASS_NUM_MAX) {
                p = gClassTable;
            }
            else if(p == gClassTable + hash_key) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

sCLClass* get_class(char* name)
{
    unsigned int hash_key = get_hash_key(name, CLASS_NUM_MAX);
    sClassTable* p = gClassTable + hash_key;

    while(1) {
        if(p->mName) {
            if(strcmp(p->mName, name) == 0) {
                return p->mItem;
            }
            else {
                p++;

                if(p == gClassTable + CLASS_NUM_MAX) {
                    p = gClassTable;
                }
                else if(p == gClassTable + hash_key) {
                    break;
                }
            }
        }
        else {
            break;
        }
    }

    return NULL;
}

sCLClass* alloc_class(char* name, BOOL primitive_)
{
    sCLClass* klass = MCALLOC(1, sizeof(sCLClass));

    klass->mFlags |= (primitive_ ? CLASS_FLAGS_PRIMITIVE:0);

    sConst_init(&klass->mConst);

    klass->mClassNameOffset = append_str_to_constant_pool(&klass->mConst, name, FALSE);

    put_class_to_table(name, klass);

    return klass;
}

static void free_class(sCLClass* klass)
{
    sConst_free(&klass->mConst);
    MFREE(klass);
}

void class_init()
{
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);

    alloc_class("int", TRUE);
    alloc_class("uint", TRUE);
    alloc_class("byte", TRUE);
    alloc_class("ubyte", TRUE);
    alloc_class("short", TRUE);
    alloc_class("ushort", TRUE);
    alloc_class("long", TRUE);
    alloc_class("ulong", TRUE);
    alloc_class("float", TRUE);
    alloc_class("double", TRUE);
    alloc_class("bool", TRUE);
    alloc_class("Null", FALSE);
}

void class_final()
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        free_class(p->mItem);
        MFREE(p->mName);
        p = p->mNextClass;
    }

    gHeadClassTable = NULL;
    memset(gClassTable, 0, sizeof(sClassTable)*CLASS_NUM_MAX);
}
