#include "common.h"

static sNodeType** gNodeTypes = NULL;
static int gUsedPageNodeTypes = 0;
static int gSizePageNodeTypes = 0;
static int gUsedNodeTypes = 0;

#define NODE_TYPE_PAGE_SIZE 64

void init_node_types()
{
    const int size_page_node_types = 4;

    if(gSizePageNodeTypes == 0) {
        gNodeTypes = MCALLOC(1, sizeof(sNodeType*)*size_page_node_types);

        int i;
        for(i=0; i<size_page_node_types; i++) {
            gNodeTypes[i] = MCALLOC(1, sizeof(sNodeType)*NODE_TYPE_PAGE_SIZE);
        }

        gSizePageNodeTypes = size_page_node_types;
        gUsedPageNodeTypes = 0;
        gUsedNodeTypes = 0;
    }
}

void free_node_types()
{
    if(gSizePageNodeTypes > 0) {
        int i;
        for(i=0; i<gSizePageNodeTypes; i++) {
            if(gNodeTypes[i]->mBlockType) {
                free_node_block_type(gNodeTypes[i]->mBlockType);
            }
            MFREE(gNodeTypes[i]);
        }
        MFREE(gNodeTypes);

        gSizePageNodeTypes = 0;
        gUsedPageNodeTypes = 0;
        gUsedNodeTypes = 0;
    }
}

sNodeType* alloc_node_type()
{
    MASSERT(gNodeTypes != NULL && gSizePageNodeTypes > 0); // Is the node types initialized ?

    if(gUsedNodeTypes == NODE_TYPE_PAGE_SIZE) {
        gUsedNodeTypes = 0;
        gUsedPageNodeTypes++;

        if(gUsedPageNodeTypes == gSizePageNodeTypes) {
            int new_size = (gSizePageNodeTypes+1) * 2;
            gNodeTypes = MREALLOC(gNodeTypes, sizeof(sNodeType*)*new_size);
            memset(gNodeTypes + gSizePageNodeTypes, 0, sizeof(sNodeType*)*(new_size - gSizePageNodeTypes));

            int i;
            for(i=gSizePageNodeTypes; i<new_size; i++) {
                gNodeTypes[i] = MCALLOC(1, sizeof(sNodeType)*NODE_TYPE_PAGE_SIZE);
            }

            gSizePageNodeTypes = new_size;
        }
    }

    return &gNodeTypes[gUsedPageNodeTypes][gUsedNodeTypes++];
}

sNodeType* clone_node_type(sNodeType* node_type)
{
    sNodeType* node_type2 = alloc_node_type();

    node_type2->mClass = node_type->mClass;
    node_type2->mNumGenericsTypes = node_type->mNumGenericsTypes;

    int i;
    for(i=0; i<node_type->mNumGenericsTypes; i++) {
        node_type2->mGenericsTypes[i] = ALLOC clone_node_type(node_type->mGenericsTypes[i]);
    }

    node_type2->mArray = node_type->mArray;

    if(node_type->mBlockType) {
        node_type2->mBlockType = clone_node_block_type(node_type->mBlockType);
    }
    else {
        node_type2->mBlockType = NULL;
    }

    return node_type2;
}

sNodeType* create_node_type_with_class_pointer(sCLClass* klass)
{
    sNodeType* node_type = alloc_node_type();

    node_type->mClass = klass;
    node_type->mNumGenericsTypes = 0;
    node_type->mArray = FALSE;
    node_type->mBlockType = NULL;

    return node_type;
}

sNodeType* create_node_type_with_class_name(char* class_name)
{
    sNodeType* node_type = alloc_node_type();

    node_type->mClass = get_class(class_name);

    if(node_type->mClass == NULL) {
        node_type->mClass = load_class(class_name);
    }

    node_type->mNumGenericsTypes = 0;

    node_type->mArray = FALSE;
    node_type->mBlockType = NULL;

    return node_type;
}

sNodeType* create_node_type_with_generics_number(int generics_num)
{
    char class_name[CLASS_NAME_MAX+1];

    snprintf(class_name, CLASS_NAME_MAX, "GenericsParametorClass%d", generics_num);

    return create_node_type_with_class_name(class_name);
}

sNodeType* create_node_type_from_cl_type(sCLType* cl_type, sCLClass* klass)
{
    sNodeType* node_type = alloc_node_type();

    node_type->mClass = get_class(CONS_str(&klass->mConst, cl_type->mClassNameOffset));

    MASSERT(node_type->mClass != NULL);

    node_type->mNumGenericsTypes = cl_type->mNumGenericsTypes;

    int i;
    for(i=0; i<cl_type->mNumGenericsTypes; i++) {
        node_type->mGenericsTypes[i] = create_node_type_from_cl_type(cl_type->mGenericsTypes[i], klass);
    }

    node_type->mArray = cl_type->mArray;

    return node_type;
}

BOOL substitution_posibility(sNodeType* left, sNodeType* right)
{
    sCLClass* left_class = left->mClass;
    sCLClass* right_class = right->mClass;

    if(left_class->mFlags & CLASS_FLAGS_INTERFACE) {
        return check_implemeted_methods_for_interface(left_class, right_class);
    }
    else if(type_identify_with_class_name(right, "Null") && !(left_class->mFlags & CLASS_FLAGS_PRIMITIVE)) {
        return TRUE;
    }
    else if(type_identify_with_class_name(left, "block")) {
        if(type_identify_with_class_name(right, "block")) {
            sNodeBlockType* left_block_type = left->mBlockType;
            sNodeBlockType* right_block_type = right->mBlockType;

            if(left_block_type && right_block_type) {
                return substitution_posibility_for_node_block_type(left_block_type, right_block_type);
            }
            else {
                return FALSE;
            }
        }
        else {
            return FALSE;
        }
    }
    else {
        if(left->mClass == right->mClass && left->mArray == right->mArray && left->mNumGenericsTypes == right->mNumGenericsTypes) {
            int i;
            for(i=0; i<left->mNumGenericsTypes; i++) {
                if(!type_identify(left->mGenericsTypes[i], right->mGenericsTypes[i])) {
                    return FALSE;
                }
            }

            return TRUE;
        }
        else {
            return FALSE;
        }
    }
}

BOOL substitution_posibility_with_class_name(sNodeType* left, char* right_class_name)
{
    return substitution_posibility(left, create_node_type_with_class_name(right_class_name));
}

BOOL operand_posibility(sNodeType* left, sNodeType* right, char* op_string)
{
    if(type_identify_with_class_name(left, "pointer") 
        && (strcmp(op_string, "+") == 0 || strcmp(op_string, "-") == 0))
    {
        return type_identify_with_class_name(right, "int");
    }
    else {
        return left->mClass == right->mClass;
    }
}

BOOL operand_posibility_with_class_name(sNodeType* left, char* right_class_name, char* op_string)
{
    return operand_posibility(left, create_node_type_with_class_name(right_class_name), op_string);
}

BOOL type_identify(sNodeType* left, sNodeType* right)
{
    return left->mClass == right->mClass && left->mArray == right->mArray;
}

BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name)
{
    return type_identify(left, create_node_type_with_class_name(right_class_name));
}

BOOL solve_generics_types_for_node_type(sNodeType* node_type, ALLOC sNodeType** result, sNodeType* generics_type)
{
    int i;
    int j;

    if(generics_type && generics_type->mNumGenericsTypes > 0) {
        for(i=0; i<GENERICS_TYPES_MAX; i++) {
            if(node_type->mClass->mGenericsParamClassNum == i) {
                if(i < generics_type->mNumGenericsTypes) {
                    *result = ALLOC clone_node_type(generics_type->mGenericsTypes[i]);
                    return TRUE;
                }
                else {
                    *result = ALLOC clone_node_type(node_type); // no solve
                    return FALSE; // error
                }
            }
        }

        *result = alloc_node_type();
        (*result)->mClass = node_type->mClass;

        (*result)->mNumGenericsTypes = node_type->mNumGenericsTypes;

        for(j=0; j<node_type->mNumGenericsTypes; j++) {
            (void)solve_generics_types_for_node_type(node_type->mGenericsTypes[j], &(*result)->mGenericsTypes[j], generics_type);

            // if it can not be solved generics, no solve the generics type
        }
    }
    else {
        *result = clone_node_type(node_type); // no solve
    }

    return TRUE;
}

BOOL is_exception_type(sNodeType* exception_type)
{
    return substitution_posibility_with_class_name(exception_type, "SystemException") || substitution_posibility_with_class_name(exception_type, "Exception");
}
