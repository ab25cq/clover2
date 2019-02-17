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
    node_type2->mNullable = node_type->mNullable;

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
    node_type->mNullable = FALSE;
    node_type->mBlockType = NULL;

    return node_type;
}

static void skip_spaces_for_parse_class_name(char** p) 
{
    while(**p == ' ' || **p == '\t') {
        (*p)++;
    }
}

static sNodeType* parse_class_name(char** p, char** p2, char* buf, BOOL js)
{
    sNodeType* node_type = alloc_node_type();

    node_type->mClass = NULL;
    node_type->mNumGenericsTypes = 0;
    node_type->mArray = FALSE;
    node_type->mNullable = FALSE;
    node_type->mBlockType = NULL;

    *p2 = buf;

    while(**p) {
        if(**p == '<') {
            (*p)++;
            skip_spaces_for_parse_class_name(p);

            **p2 = 0;

            node_type->mClass = get_class_with_load_and_initialize(buf, js);

            if(node_type->mClass == NULL) {
                return NULL;
            }

            while(1) {
                node_type->mGenericsTypes[node_type->mNumGenericsTypes] = parse_class_name(p, p2, buf, js);
                node_type->mNumGenericsTypes++;

                if(node_type->mNumGenericsTypes >= GENERICS_TYPES_MAX) {
                    return NULL;
                }

                if(**p == ',') {
                    (*p)++;
                    skip_spaces_for_parse_class_name(p);
                }
                else if(**p == '>') {
                    (*p)++;
                    skip_spaces_for_parse_class_name(p);
                    return node_type;
                }
                else {
                    return NULL;
                }
            }
        }
        else if(**p == '[') {
            (*p)++;
            skip_spaces_for_parse_class_name(p);

            if(**p == ']') {
                (*p)++;
                skip_spaces_for_parse_class_name(p);

                node_type->mArray = TRUE;
            }
        }
        else if(**p == '?') {
            (*p)++;
            skip_spaces_for_parse_class_name(p);

            node_type->mNullable = TRUE;
        }
        else if(**p == '>') {
            **p2 = 0;

            node_type->mClass = get_class_with_load_and_initialize(buf, js);

            if(node_type->mClass == NULL) {
                return NULL;
            }

            return node_type;
        }
        else {
            **p2 = **p;

            (*p)++;
            (*p2)++;
        }
    }

    if(*p2 - buf > 0) {
        **p2 = 0;

        node_type->mClass = get_class_with_load_and_initialize(buf, js);

        if(node_type->mClass == NULL) {
            return NULL;
        }
    }

    return node_type;
}

sNodeType* create_node_type_with_class_name(char* class_name, BOOL js)
{
    char buf[CLASS_NAME_MAX+1];

    char* p = class_name;
    char* p2 = buf;

    return parse_class_name(&p, &p2, buf, js);
}

sNodeType* create_node_type_with_generics_number(int generics_num, BOOL js)
{
    char class_name[CLASS_NAME_MAX+1];

    snprintf(class_name, CLASS_NAME_MAX, "GenericsParametorClass%d", generics_num);

    return create_node_type_with_class_name(class_name, js);
}

sNodeType* create_node_type_with_method_generics_number(int generics_num, BOOL js)
{
    char class_name[CLASS_NAME_MAX+1];

    snprintf(class_name, CLASS_NAME_MAX, "MethodGenericsParametorClass%d", generics_num);

    return create_node_type_with_class_name(class_name, js);
}

sNodeType* create_node_type_from_cl_type(sCLType* cl_type, sCLClass* klass)
{
    BOOL js = klass->mFlags & CLASS_FLAGS_JS;
    sNodeType* node_type = alloc_node_type();

    node_type->mClass = get_class_with_load_and_initialize(CONS_str(&klass->mConst, cl_type->mClassNameOffset), js);

    MASSERT(node_type->mClass != NULL);

    node_type->mNumGenericsTypes = cl_type->mNumGenericsTypes;

    int i;
    for(i=0; i<cl_type->mNumGenericsTypes; i++) {
        node_type->mGenericsTypes[i] = create_node_type_from_cl_type(cl_type->mGenericsTypes[i], klass);
    }

    node_type->mArray = cl_type->mArray;
    node_type->mNullable = cl_type->mNullable;

    if(cl_type->mBlockType) {
        node_type->mBlockType = alloc_node_block_type();
        node_type->mBlockType->mNumParams = cl_type->mBlockType->mNumParams;

        int i;
        for(i=0; i<cl_type->mBlockType->mNumParams; i++) {
            node_type->mBlockType->mParams[i] = create_node_type_from_cl_type(cl_type->mBlockType->mParams[i], klass);
        }

        node_type->mBlockType->mResultType = create_node_type_from_cl_type(cl_type->mBlockType->mResultType, klass);
    }
    else {
        node_type->mBlockType = NULL;
    }

    return node_type;
}

BOOL is_delegated_class(sNodeType* left_type, sNodeType* right_type)
{
    sCLClass* right_class = right_type->mClass;

    int i;
    for(i=0; i<right_class->mNumFields; i++) {
        sCLField* field = right_class->mFields + i;

        sNodeType* right_type2 = create_node_type_from_cl_type(field->mResultType, right_class);

        if(type_identify(left_type, right_type2) && (field->mFlags & FIELD_FLAGS_DELEGATED)) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL substitution_posibility(sNodeType* left, sNodeType* right, sNodeType* left_generics_types, sNodeType* right_generics_types, sNodeType* left_method_generics, sNodeType* right_method_generics, BOOL output_message)
{
    BOOL js = left->mClass->mFlags & CLASS_FLAGS_JS;

    sNodeType* left2;

    if(left_method_generics) {
        if(!solve_generics_types_for_node_type(left, ALLOC &left2, left_method_generics, FALSE, TRUE)) 
        {
            return FALSE;
        }
    }
    else {
        left2 = left;
    }


    sNodeType* right2;

    if(right_method_generics) {
        if(!solve_generics_types_for_node_type(right, ALLOC &right2, right_method_generics, FALSE, TRUE)) 
        {
            return FALSE;
        }
    }
    else {
        right2 = right;
    }

    sNodeType* left3;
    if(left_generics_types) {
        if(!solve_generics_types_for_node_type(left2, ALLOC &left3, left_generics_types, TRUE, FALSE)) 
        {
            return FALSE;
        }
    }
    else {
        left3 = left2;
    }

    sNodeType* right3;
    if(right_generics_types) {
        if(!solve_generics_types_for_node_type(right2, ALLOC &right3, right_generics_types, TRUE, FALSE)) 
        {
            return FALSE;
        }
    }
    else {
        right3 = right2;
    }

    sCLClass* left_class = left3->mClass;
    sCLClass* right_class = right3->mClass;

    if(type_identify_with_class_name(right3, "Anonymous") && !(left_class->mFlags & CLASS_FLAGS_PRIMITIVE)) 
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(left3, "Anonymous") && !(right_class->mFlags & CLASS_FLAGS_PRIMITIVE)) 
    {
        return TRUE;
    }
    else if(left_class->mGenericsParamClassNum != -1 || right_class->mGenericsParamClassNum != -1) {
        return FALSE;
    }
    else if(type_identify_with_class_name(right3, "Null") && !(left_class->mFlags & CLASS_FLAGS_PRIMITIVE) && left->mNullable) 
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(right3, "Null") && type_identify_with_class_name(left3, "pointer"))
    {
        return TRUE;
    }
    else if(!js && type_identify_with_class_name(left3, "Buffer") && type_identify_with_class_name(right3, "pointer"))
    {
        return TRUE;
    }
    else if(type_identify_with_class_name(right3, "WildCard") 
        && !(left_class->mFlags & CLASS_FLAGS_PRIMITIVE)) 
    {
        return TRUE;
    }
    else if(left_class->mFlags & CLASS_FLAGS_INTERFACE) {
        if(right_class->mFlags & CLASS_FLAGS_INTERFACE) {
            return check_implemented_methods_for_interface(left_class, right_class, output_message);
            //return type_identify(left3, right3);
        }
        else if(right_class->mFlags & CLASS_FLAGS_PRIMITIVE) {
            return FALSE;
        }
        else {
            return check_implemented_methods_for_interface(left_class, right_class, output_message);
        }
    }
    else if(is_delegated_class(left3, right3)) {
        return TRUE;
    }
    else if(strcmp(CLASS_NAME(left3->mClass), "lambda") == 0) {
        if(strcmp(CLASS_NAME(right3->mClass), "lambda") == 0) 
        {
            if(left3->mArray != right3->mArray) {
                return FALSE;
            }

            sNodeBlockType* left_block_type = left3->mBlockType;
            sNodeBlockType* right_block_type = right3->mBlockType;

            if(left_block_type && right_block_type) {
                return substitution_posibility_for_node_block_type(left_block_type, right_block_type, left_generics_types, right_generics_types, output_message);
            }
            else {
                return FALSE;
            }
        }
        else if(left3->mNullable && type_identify_with_class_name(right3, "Null")) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        if(left3->mClass == right3->mClass && left3->mArray == right3->mArray && left3->mNumGenericsTypes == right3->mNumGenericsTypes) {
            int i;
            for(i=0; i<left3->mNumGenericsTypes; i++) {
/*
                if(type_identify_with_class_name(right3->mGenericsTypes[i], "Null") && !left3->mNullable) {  // prevent unintended
                    return FALSE;
                }
*/
                if(!substitution_posibility(left3->mGenericsTypes[i], right3->mGenericsTypes[i], left_generics_types, right_generics_types, left_method_generics, right_method_generics, output_message))
                {
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

BOOL substitution_posibility_with_class_name(sNodeType* left, char* right_class_name, BOOL output_message)
{
    return substitution_posibility(left, create_node_type_with_class_name(right_class_name, left->mClass->mFlags & CLASS_FLAGS_JS), NULL , NULL, NULL, NULL, output_message);
}

static BOOL is_numeric_type(sNodeType* type_)
{
    return type_identify_with_class_name(type_, "int") || type_identify_with_class_name(type_, "uint") || type_identify_with_class_name(type_, "byte") || type_identify_with_class_name(type_, "ubyte") || type_identify_with_class_name(type_, "short") || type_identify_with_class_name(type_, "ushort") || type_identify_with_class_name(type_, "long") || type_identify_with_class_name(type_, "ulong") || type_identify_with_class_name(type_, "float") || type_identify_with_class_name(type_, "double") || type_identify_with_class_name(type_, "Integer") || type_identify_with_class_name(type_, "UInteger") || type_identify_with_class_name(type_, "Byte") || type_identify_with_class_name(type_, "UByte") || type_identify_with_class_name(type_, "Short") || type_identify_with_class_name(type_, "UShort") || type_identify_with_class_name(type_, "Long") || type_identify_with_class_name(type_, "ULong") || type_identify_with_class_name(type_, "Float") || type_identify_with_class_name(type_, "Double");
}

BOOL no_cast_types_for_binary_operator(sNodeType* left_type, sNodeType* right_type)
{
    return (type_identify_with_class_name(left_type, "pointer") && is_numeric_type(right_type))
        || (type_identify_with_class_name(left_type, "Buffer") && is_numeric_type(right_type));
}

static BOOL is_numeric_type_without_float(sNodeType* type_)
{
    return type_identify_with_class_name(type_, "int") || type_identify_with_class_name(type_, "uint") || type_identify_with_class_name(type_, "byte") || type_identify_with_class_name(type_, "ubyte") || type_identify_with_class_name(type_, "short") || type_identify_with_class_name(type_, "ushort") || type_identify_with_class_name(type_, "long") || type_identify_with_class_name(type_, "ulong") || type_identify_with_class_name(type_, "Integer") || type_identify_with_class_name(type_, "UInteger") || type_identify_with_class_name(type_, "Byte") || type_identify_with_class_name(type_, "UByte") || type_identify_with_class_name(type_, "Short") || type_identify_with_class_name(type_, "UShort") || type_identify_with_class_name(type_, "Long") || type_identify_with_class_name(type_, "ULong");
}

BOOL operand_posibility(sNodeType* left, sNodeType* right, char* op_string)
{
    if(type_identify_with_class_name(left, "pointer") || type_identify_with_class_name(left, "Buffer"))
    {
        if(strcmp(op_string, "+") == 0) {
            return is_numeric_type(right);
        }
        else if(strcmp(op_string, "-") == 0) {
            return is_numeric_type(right) || type_identify_with_class_name(right, "pointer") || type_identify_with_class_name(right, "Buffer");
        }
        else if(strcmp(op_string, "==") == 0 || strcmp(op_string, "!=") == 0) {
            return type_identify_with_class_name(right, "Null") 
                || type_identify_with_class_name(right, "pointer") || type_identify_with_class_name(right, "Buffer");
        }
        else {
            return left->mClass == right->mClass;
        }
    }
    else if(left->mClass && !(left->mClass->mFlags & CLASS_FLAGS_PRIMITIVE) && type_identify_with_class_name(right, "Null") && (strcmp(op_string, "==") == 0 || strcmp(op_string, "!=") == 0))
    {
        return TRUE;
    }
    else {
        return left->mClass == right->mClass;
    }
}

BOOL operand_posibility_with_class_name(sNodeType* left, char* right_class_name, char* op_string)
{
    return operand_posibility(left, create_node_type_with_class_name(right_class_name, left->mClass->mFlags & CLASS_FLAGS_JS), op_string);
}

BOOL type_identify(sNodeType* left, sNodeType* right)
{
    return left->mClass == right->mClass && left->mArray == right->mArray;
}

BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name)
{
    sNodeType* right = create_node_type_with_class_name(right_class_name, left->mClass->mFlags & CLASS_FLAGS_JS);

    if(right == NULL) {
        return FALSE;
    }

    return type_identify(left, right);
}

BOOL class_identify_with_class_name(sCLClass* klass, char* class_name)
{
    BOOL js = klass->mFlags & CLASS_FLAGS_JS;
    sCLClass* klass2 = get_class_with_load_and_initialize(class_name, js);

    MASSERT(klass2 != NULL);

    return klass == klass2;
}

static void solve_self_for_node_type(sNodeType* node_type, ALLOC sNodeType** result, sNodeType* generics_type)
{
    if(type_identify_with_class_name(node_type, "Self")) {
        int j;
        *result = alloc_node_type();
        (*result)->mClass = generics_type->mClass;

        (*result)->mNumGenericsTypes = node_type->mNumGenericsTypes;

        for(j=0; j<node_type->mNumGenericsTypes; j++) {
            (void)solve_generics_types_for_node_type(node_type->mGenericsTypes[j], &(*result)->mGenericsTypes[j], generics_type, TRUE, FALSE);

            // if it can not be solved generics, no solve the generics type
        }

        (*result)->mBlockType = node_type->mBlockType;
        (*result)->mArray = node_type->mArray;
        (*result)->mNullable = node_type->mNullable;
    }
    else {
        (*result) = node_type;
    }
}

BOOL solve_generics_types_for_node_type(sNodeType* node_type, ALLOC sNodeType** result, sNodeType* generics_type, BOOL solve_self, BOOL solve_method_generics)
{
    int i;
    int j;

    sNodeType* node_type2; 
    if(solve_self) {
        solve_self_for_node_type(node_type, &node_type2, generics_type);
    }
    else {
        node_type2 = node_type;
    }

    if(generics_type == NULL) {
        *result = clone_node_type(node_type2); // no solve
    }
    else if(generics_type && generics_type->mNumGenericsTypes > 0) {
        int generics_param_class_num;

        if(solve_method_generics) {
            generics_param_class_num = node_type2->mClass->mMethodGenericsParamClassNum;
        }
        else {
            generics_param_class_num = node_type2->mClass->mGenericsParamClassNum;
        }

        for(i=0; i<GENERICS_TYPES_MAX; i++) {
            if(generics_param_class_num == i) {
                //if(i < generics_type->mNumGenericsTypes) {
                if(i < generics_type->mNumGenericsTypes && generics_type->mGenericsTypes[i]) {
                    *result = ALLOC clone_node_type(generics_type->mGenericsTypes[i]);
                    (*result)->mArray = node_type2->mArray;
                    (*result)->mNullable = node_type2->mNullable;
                    return TRUE;
                }
                else {
                    *result = ALLOC clone_node_type(node_type2); // no solve
                    return FALSE; // error
                }
            }
        }

        *result = alloc_node_type();
        (*result)->mClass = node_type2->mClass;

        (*result)->mNumGenericsTypes = node_type2->mNumGenericsTypes;

        for(j=0; j<node_type2->mNumGenericsTypes; j++) {
            (void)solve_generics_types_for_node_type(node_type2->mGenericsTypes[j], &(*result)->mGenericsTypes[j], generics_type, TRUE, solve_method_generics);

            // if it can not be solved generics, no solve the generics type
        }

//        (*result)->mBlockType = node_type2->mBlockType;

        if(node_type2->mBlockType) {
            sNodeBlockType* block_type = node_type2->mBlockType;

            sNodeBlockType* result_block_type = alloc_node_block_type();

            result_block_type->mNumParams = block_type->mNumParams;

            for(j=0; j<block_type->mNumParams; j++) {
                (void)solve_generics_types_for_node_type(block_type->mParams[j], &result_block_type->mParams[j], generics_type, TRUE, solve_method_generics);
            }

            (void)solve_generics_types_for_node_type(block_type->mResultType, &result_block_type->mResultType, generics_type, TRUE, solve_method_generics);

            (*result)->mBlockType = result_block_type;
        }
        else {
            (*result)->mBlockType = NULL;
        }

        (*result)->mArray = node_type2->mArray;
        (*result)->mNullable = node_type2->mNullable;
    }
    else {
        *result = clone_node_type(node_type2); // no solve
    }

    return TRUE;
}

sNodeType* create_generics_types_from_generics_params(sCLClass* klass)
{
    sNodeType* result = alloc_node_type();

    result->mClass = klass;
    result->mNumGenericsTypes = klass->mNumGenerics;

    int i;
    for(i=0; i<klass->mNumGenerics; i++) {
        int offset = klass->mGenericsParamTypeOffsets[i];
        BOOL js = klass->mFlags & CLASS_FLAGS_JS;
        sCLClass* interface = get_class_with_load_and_initialize(CONS_str(&klass->mConst, offset), js);

        MASSERT(interface != NULL);

        result->mGenericsTypes[i] = create_node_type_with_class_pointer(interface);
    }

    return result;
}

void solve_generics_for_variable_to_class(sCLClass* klass, sCLClass** result, struct sParserInfoStruct* info)
{
    sCLClass* generics_class = info->klass;
    int generics_param_number = klass->mGenericsParamClassNum;

    *result = klass;

    if(generics_param_number != -1) {
        if(generics_param_number < generics_class->mNumGenerics) {
            *result = info->generics_info.mInterface[generics_param_number];
        }
    }
}

void solve_method_generics_for_variable_to_class(sCLClass* klass, sCLClass** result, struct sParserInfoStruct* info)
{
    sCLClass* generics_class = info->klass;
    int generics_param_number = klass->mMethodGenericsParamClassNum;

    *result = klass;

    if(generics_param_number != -1) {
        *result = info->method_generics_info.mInterface[generics_param_number];
    }
}

void solve_generics_for_variable(sNodeType* generics_type, sNodeType** generics_type2, struct sParserInfoStruct* info)
{
    *generics_type2 = alloc_node_type();

    sCLClass* klass = generics_type->mClass;

    if(info->klass != NULL) {
        int generics_param_number = klass->mGenericsParamClassNum;

        if(generics_param_number != -1) {
            if(generics_param_number < info->klass->mNumGenerics) {
                klass = info->generics_info.mInterface[generics_param_number];
            }
        }

        int method_generics_param_number = klass->mMethodGenericsParamClassNum;

        if(method_generics_param_number != -1) {
            if(method_generics_param_number < info->method_generics_info.mNumParams) {
                klass = info->method_generics_info.mInterface[method_generics_param_number];
            }
        }
    }

    (*generics_type2)->mClass = klass;

    int i;
    for(i=0; i<generics_type->mNumGenericsTypes; i++) {
        solve_generics_for_variable(generics_type->mGenericsTypes[i], &(*generics_type2)->mGenericsTypes[i], info);
    }

    (*generics_type2)->mNumGenericsTypes = generics_type->mNumGenericsTypes;
    (*generics_type2)->mArray = generics_type->mArray;
    (*generics_type2)->mNullable = generics_type->mNullable;
    (*generics_type2)->mBlockType = generics_type->mBlockType;
}

BOOL is_exception_type(sNodeType* exception_type)
{
    return substitution_posibility_with_class_name(exception_type, "Exception", FALSE);
}

void print_node_type(sNodeType* node_type)
{
    if(node_type->mNumGenericsTypes == 0) {
        if(node_type == NULL) {
            printf("type is NULL\n");
        }
        else if(node_type->mClass == NULL) {
            printf("class of node type is NULL\n");
        }
        else {
            printf("%s", CLASS_NAME(node_type->mClass));
        }
    }
    else {
        if(node_type == NULL) {
            printf("type is NULL\n");
        }
        else if(node_type->mClass == NULL) {
            printf("class of node type is NULL\n");
        }
        else {
            printf("%s<", CLASS_NAME(node_type->mClass));
        }

        int i;
        for(i=0; i<node_type->mNumGenericsTypes; i++) {
            print_node_type(node_type->mGenericsTypes[i]);
            if(i != node_type->mNumGenericsTypes-1) printf(",");
        }

        printf(">");
    }

    if(node_type->mArray) {
        printf("[]");
    }
    if(node_type->mNullable) {
        printf("?");
    }
}

BOOL cast_posibility(sNodeType* left_type, sNodeType* right_type)
{
    sCLClass* left_class = left_type->mClass;
    sCLClass* right_class = right_type->mClass;

    BOOL js = left_class->mFlags & CLASS_FLAGS_JS;

    /// ulong --> int or int --> ulong etc
    if(is_numeric_type_without_float(left_type) && is_numeric_type_without_float(right_type)) {
        return TRUE;
    }
    else if(boxing_posibility(left_type, right_type)) {
        return TRUE;
    }
    else if(unboxing_posibility(left_type, right_type)) {
        return TRUE;
    }
    else if(type_identify_with_class_name(left_type, "pointer") && type_identify_with_class_name(right_type, "Buffer"))
    {
        return TRUE;
    }
    else if(is_numeric_type_without_float(left_type) && type_identify_with_class_name(right_type, "char")) 
    {
        return TRUE;
    }

    return FALSE;
}

BOOL boxing_posibility(sNodeType* left_type, sNodeType* right_type)
{
    if(left_type->mNumGenericsTypes == 0 && right_type->mNumGenericsTypes == 0) {
        sCLClass* left_class = left_type->mClass;
        sCLClass* right_class = right_type->mClass;

        if(right_class->mBoxingClass == left_class) {
            return TRUE;
        }

        if(class_identify_with_class_name(left_class, "Anonymous") || left_class->mGenericsParamClassNum != -1 || left_class->mMethodGenericsParamClassNum != -1) 
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL unboxing_posibility(sNodeType* left_type, sNodeType* right_type)
{
    if(left_type->mNumGenericsTypes == 0 && right_type->mNumGenericsTypes == 0) {
        sCLClass* left_class = left_type->mClass;
        sCLClass* right_class = right_type->mClass;

        if(left_class->mBoxingClass == right_class) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL unboxig_posibility(sCLClass* klass)
{
    return !(klass->mFlags & CLASS_FLAGS_PRIMITIVE) && klass->mUnboxingClass != NULL;
}

void boxing_to_lapper_type(sNodeType** type_)
{
    if((*type_)->mClass->mBoxingClass) {
        (*type_)->mClass = (*type_)->mClass->mBoxingClass;
    }
}

void boxing_to_lapper_class(sNodeType** type_, struct sCompileInfoStruct* info)
{
    sCLClass* klass = (*type_)->mClass;

    if((*type_)->mArray) {
        sNodeType* rapper_type;
        make_boxing_type((*type_), &rapper_type);

        cast_right_type_to_left_type(rapper_type, type_, info);
    }
    else if(klass->mFlags & CLASS_FLAGS_PRIMITIVE) {
        if(klass->mBoxingClass != NULL) {
            sNodeType* boxing_type = create_node_type_with_class_pointer(klass->mBoxingClass);

            cast_right_type_to_left_type(boxing_type, type_, info);
        }
        else {
            parser_err_msg(info->pinfo, "primitive class without boxing %s", CLASS_NAME(klass));
            info->err_num++;
        }
    }
}

BOOL unboxing_to_primitive_type(sNodeType** left_type, struct sCompileInfoStruct* info)
{
    sCLClass* primitive_class = (*left_type)->mClass->mUnboxingClass;
    sNodeType* primitive_type = create_node_type_with_class_pointer(primitive_class);
    cast_right_type_to_left_type(primitive_type, left_type, info);

    return TRUE;
}

void make_boxing_type(sNodeType* type, sNodeType** result)
{
    (*result) = alloc_node_type();

    sCLClass* klass = type->mClass;

    if(type->mArray) {
        (*result)->mClass = get_class("Array", klass->mFlags & CLASS_FLAGS_JS);

        (*result)->mNumGenericsTypes = 1;

        sNodeType* node_type = create_node_type_with_class_pointer(klass);

        make_boxing_type(node_type, &(*result)->mGenericsTypes[0]);
    }
    else if((klass->mFlags & CLASS_FLAGS_PRIMITIVE) && klass->mBoxingClass) {
        (*result)->mClass = klass->mBoxingClass;

        (*result)->mNumGenericsTypes = type->mNumGenericsTypes;

        int i;
        for(i=0; i<type->mNumGenericsTypes; i++) {
            make_boxing_type(type->mGenericsTypes[i], &(*result)->mGenericsTypes[i]);
        }
    }
    else {
        (*result)->mClass = klass;

        (*result)->mNumGenericsTypes = type->mNumGenericsTypes;

        int i;
        for(i=0; i<type->mNumGenericsTypes; i++) {
            make_boxing_type(type->mGenericsTypes[i], &(*result)->mGenericsTypes[i]);
        }
    }
}
