#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdarg.h>
#include <locale.h>

#include "macros.h"

/// debug.c ///
#include "debug.h"

/// buffer.c ///
#include "buffer.h"

/// xfunc.c ///
#include "xfunc.h"

/// limits ///
#define CLASS_NAME_MAX 32
#define VAR_NAME_MAX 32
#define METHOD_NAME_MAX VAR_NAME_MAX
#define ELIF_NUM_MAX 32
#define BREAK_NUM_MAX 32
#define PARAMS_MAX 32
#define GENERICS_TYPES_MAX 32
#define CLASS_VERSION_MAX 128
#define METHOD_PATH_MAX 1024
#define METHOD_NUM_MAX 128
#define CL_MODULE_HASH_SIZE 256
#define CL_MODULE_NAME_MAX CLASS_NAME_MAX

/// CLVALUE ///
typedef unsigned int CLObject;

union CLVALUEUnion {
    unsigned int mUIntValue;
    unsigned char mUByteValue;
    unsigned short mUShortValue;
    unsigned long mULongValue;
    int mIntValue;
    char mByteValue;
    short mShortValue;
    long mLongValue;
    CLObject mObjectValue;
    wchar_t mCharValue;
    float mFloatValue;
    double mDoubleValue;
    BOOL mBoolValue;
    char* mPointerValue;
};

typedef union CLVALUEUnion CLVALUE;

/// code.c ///
struct sByteCodeStruct {
    char* mCodes;
    unsigned int mLen;
    size_t mSize;
};

typedef struct sByteCodeStruct sByteCode;

void sByteCode_init(sByteCode* code);
void sByteCode_init_with_size(sByteCode* code, int size);
void sByteCode_free(sByteCode* code);
void append_value_to_code(sByteCode* code, void* data, size_t size, BOOL no_output);
void append_opecode_to_code(sByteCode* code, unsigned int op, BOOL no_output);
void append_int_value_to_code(sByteCode* code, int value, BOOL no_output);
void append_long_value_to_code(sByteCode* code, long value, BOOL no_output);

/// constant.c ///
struct sConstStruct
{
    char* mConst;
    int mSize;
    int mLen;
};

typedef struct sConstStruct sConst;

#define CONS_str(constant, offset) (char*)((constant)->mConst + offset)

void sConst_init(sConst* self);
void sConst_init_with_size(sConst* self, int size);
void sConst_free(sConst* self);

int sConst_append(sConst* self, void* data, size_t size, BOOL no_output);
int append_int_value_to_constant_pool(sConst* constant, int n, BOOL no_output);
int append_float_value_to_constant_pool(sConst* constant, float n, BOOL no_output);
int append_double_value_to_constant_pool(sConst* constant, double n, BOOL no_output);
int append_str_to_constant_pool(sConst* constant, char* str, BOOL no_output);
int append_wstr_to_constant_pool(sConst* constant, char* str, BOOL no_output);
void append_str_to_constant_pool_and_code(sConst* constant, sByteCode* code, char* str, BOOL no_output);

/// klass.c ///
#define CLASS_FLAGS_PRIMITIVE 0x01
#define CLASS_FLAGS_INTERFACE 0x02
#define CLASS_FLAGS_MODIFIED 0x04

struct sCLTypeStruct;

struct sCLBlockTypeStruct {
    struct sCLTypeStruct* mParams[PARAMS_MAX];
    int mNumParams;

    struct sCLTypeStruct* mResultType;
};

typedef struct sCLBlockTypeStruct sCLBlockType;

struct sCLTypeStruct {
    int mClassNameOffset;

    int mNumGenericsTypes;
    struct sCLTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];

    BOOL mArray;

    sCLBlockType* mBlockType;
};

typedef struct sCLTypeStruct sCLType;

struct sCLParamStruct {
    int mNameOffset;                // variable name

    sCLType* mType;
};

typedef struct sCLParamStruct sCLParam;

#define METHOD_FLAGS_NATIVE 0x01
#define METHOD_FLAGS_CLASS_METHOD 0x02

struct sVMInfoStruct {
};

typedef struct sVMInfoStruct sVMInfo;

typedef BOOL (*fNativeMethod)(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

struct sCLMethodStruct {
    long mFlags;
    int mNameOffset;
    int mPathOffset;
    int mMethodNameAndParamsOffset;

    sCLParam mParams[PARAMS_MAX]; // +1 --> self
    int mNumParams;

    sCLType* mResultType;

    union {
        sByteCode mByteCodes;
        fNativeMethod mNativeMethod;
    } uCode;
    
    int mVarNum;
};

typedef struct sCLMethodStruct sCLMethod;

#define FIELD_FLAGS_PRIVATE 0x01
#define FIELD_FLAGS_PROTECTED 0x02

struct sCLFieldStruct {
    long mFlags;
    int mNameOffset;

    sCLType* mResultType;
    CLVALUE mValue;
};

typedef struct sCLFieldStruct sCLField;

struct sCLClassStruct {
    long mFlags;

    int mVersion;

    int mGenericsParamClassNum;   // -1 is none generics param 
    int mNumGenerics;

    int mGenericsParamTypeOffsets[GENERICS_TYPES_MAX];

    sConst mConst;

    int mClassNameOffset;

    sCLMethod* mMethods;
    int mNumMethods;
    int mSizeMethods;

    sCLField* mFields;
    int mNumFields;
    int mSizeFields;

    sCLField* mClassFields;
    int mNumClassFields;
    int mSizeClassFields;

    int mClassInitializeMethodIndex;
    int mClassFinalizeMethodIndex;
    int mFinalizeMethodIndex;

    int mNumMethodsOnLoadTime; // This requires from the compile time
    int mMethodIndexOnCompileTime; // This require from the compile time

    sCLMethod* mVirtualMethodTable[METHOD_NUM_MAX]; // This requires from the run time
};

typedef struct sCLClassStruct sCLClass;

#define CLASS_NAME(klass) (CONS_str((&(klass)->mConst), (klass)->mClassNameOffset))
#define METHOD_NAME2(klass, method) (CONS_str((&(klass)->mConst), (method)->mNameOffset))
#define METHOD_NAME_AND_PARAMS(klass, method) (CONS_str((&(klass)->mConst), (method)->mMethodNameAndParamsOffset))

void class_init();
void class_final();

sCLClass* get_class(char* name);
unsigned int get_hash_key(char* name, unsigned int max);
sCLClass* alloc_class(char* class_name, BOOL primitive_, int generics_param_class_num, int generics_number, sCLClass** type_of_generics_params, BOOL interface);
ALLOC sCLType* create_cl_type(sCLClass* klass, sCLClass* klass2);
void free_cl_type(sCLType* cl_type);
sCLClass* load_class_with_version(char* class_name, int class_version);
sCLClass* load_class(char* class_name);
sCLMethod* search_for_method_from_virtual_method_table(sCLClass* klass, char* method_name_and_params);

struct sClassTableStruct
{
    char* mName;
    sCLClass* mItem;

    struct sClassTableStruct* mNextClass;
};

typedef struct sClassTableStruct sClassTable;

sClassTable* gHeadClassTable;

typedef fNativeMethod (*fGetNativeMethod)(char* path);
extern fGetNativeMethod gGetNativeMethod;

/// node_type.c ///
struct sNodeBlockTypeStruct;

struct sNodeTypeStruct {
    sCLClass* mClass;

    struct sNodeTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];
    int mNumGenericsTypes;

    BOOL mArray;
    MANAGED struct sNodeBlockTypeStruct* mBlockType;
};

typedef struct sNodeTypeStruct sNodeType;

void init_node_types();
void free_node_types();
sNodeType* alloc_node_type();
sNodeType* clone_node_type(sNodeType* node_type);
sNodeType* create_node_type_with_class_name(char* class_name);
sNodeType* create_node_type_with_generics_number(int generics_num);
sNodeType* create_node_type_from_cl_type(sCLType* cl_type, sCLClass* klass);
sNodeType* create_node_type_with_class_pointer(sCLClass* klass);
BOOL is_exception_type(sNodeType* exception_type);

BOOL substitution_posibility(sNodeType* left, sNodeType* right);
BOOL substitution_posibility_with_class_name(sNodeType* left, char* right_class_name);
BOOL operand_posibility_with_class_name(sNodeType* left, char* right_class_name, char* op_string);
BOOL operand_posibility(sNodeType* left, sNodeType* right, char* op_string);
BOOL solve_generics_types_for_node_type(sNodeType* node_type, ALLOC sNodeType** result, sNodeType* type_);
BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name);
BOOL type_identify(sNodeType* left, sNodeType* right);

/// node_block_object.c ///
struct sNodeBlockTypeStruct {
    sNodeType* mParams[PARAMS_MAX];
    int mNumParams;

    struct sNodeTypeStruct* mResultType;
};

typedef struct sNodeBlockTypeStruct sNodeBlockType;

sNodeBlockType* alloc_node_block_type();
void free_node_block_type(sNodeBlockType* block);
sNodeBlockType* clone_node_block_type(sNodeBlockType* block);
BOOL substitution_posibility_for_node_block_type(sNodeBlockType* left, sNodeBlockType* right);

/// vtable.c ///
struct sVarStruct {
    char mName[VAR_NAME_MAX];
    int mIndex;
    sNodeType* mType;

    int mBlockLevel;
};

typedef struct sVarStruct sVar;

#define LOCAL_VARIABLE_MAX 128

struct sVarTableStruct {
    sVar mLocalVariables[LOCAL_VARIABLE_MAX];  // open address hash
    int mVarNum;
    int mMaxBlockVarNum;

    int mBlockLevel;

    struct sVarTableStruct* mParent;            // make linked list
    struct sVarTableStruct* mNext;              // for free var table
};

typedef struct sVarTableStruct sVarTable;

void init_vtable();
void final_vtable();

sVarTable* init_block_vtable(sVarTable* lv_table);

sVarTable* init_var_table();

void set_max_block_var_num(sVarTable* new_table, sVarTable* lv_table);

int get_variable_index(sVarTable* table, char* name);
struct sParserInfoStruct;
void check_already_added_variable(sVarTable* table, char* name, struct sParserInfoStruct* info);

// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_);

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name);

int get_var_num(sVarTable* table);
void show_vtable(sVarTable* table);

/// parser.c ///
struct sGenericsParamInfoStruct
{
    char mParamNames[GENERICS_TYPES_MAX][VAR_NAME_MAX];
    int mNumParams;
    sCLClass* mInterface[GENERICS_TYPES_MAX];
};

typedef struct sGenericsParamInfoStruct sGenericsParamInfo;

struct sParserInfoStruct
{
    char* p;
    char* sname;
    int sline;
    int err_num;
    sVarTable* lv_table;
    int parse_phase;
    sCLClass* klass;
    sGenericsParamInfo generics_info;
};

typedef struct sParserInfoStruct sParserInfo;

void parser_err_msg(sParserInfo* info, const char* msg, ...);
BOOL expression(unsigned int* node, sParserInfo* info);
void skip_spaces_and_lf(sParserInfo* info);
void expect_next_character_with_one_forward(char* characters, sParserInfo* info);
BOOL parse_word(char* buf, int buf_size, sParserInfo* info, BOOL print_out_err_msg);
BOOL parse_type(sNodeType** result_type, sParserInfo* info);
BOOL parse_class_type(sCLClass** klass, sParserInfo* info);

/// node_block.c ///
struct sNodeBlockStruct
{
    unsigned int* mNodes;
    unsigned int mSizeNodes;
    unsigned int mNumNodes;

    sVarTable* mLVTable;
};

typedef struct sNodeBlockStruct sNodeBlock;

void sNodeBlock_free(sNodeBlock* block);
BOOL parse_block(ALLOC sNodeBlock** node_block, sParserInfo* info, sVarTable* new_table, BOOL block_object);
struct sCompileInfoStruct;
BOOL compile_block(sNodeBlock* block, struct sCompileInfoStruct* info);

/// node.c ///
enum eNodeType { kNodeTypeOperand, kNodeTypeByteValue, kNodeTypeUByteValue, kNodeTypeShortValue, kNodeTypeUShortValue, kNodeTypeIntValue, kNodeTypeUIntValue, kNodeTypeLongValue, kNodeTypeULongValue, kNodeTypeAssignVariable, kNodeTypeLoadVariable, kNodeTypeIf, kNodeTypeWhile, kNodeTypeBreak, kNodeTypeTrue, kNodeTypeFalse, kNodeTypeNull, kNodeTypeFor, kNodeTypeClassMethodCall, kNodeTypeMethodCall, kNodeTypeReturn, kNodeTypeNewOperator, kNodeTypeLoadField, kNodeTypeStoreField , kNodeTypeLoadClassField, kNodeTypeStoreClassField, kNodeTypeLoadValueFromPointer, kNodeTypeStoreValueToPointer, kNodeTypeIncrementOperand, kNodeTypeDecrementOperand, kNodeTypeIncrementWithValueOperand, kNodeTypeDecrementWithValueOperand, kNodeTypeMonadicIncrementOperand, kNodeTypeMonadicDecrementOperand, kNodeTypeLoadArrayElement, kNodeTypeStoreArrayElement, kNodeTypeChar, kNodeTypeString, kNodeTypeThrow, kNodeTypeTry, kNodeTypeBlockObject, kNodeTypeBlockCall };

enum eOperand { kOpAdd, kOpSub , kOpComplement, kOpLogicalDenial, kOpMult, kOpDiv, kOpMod, kOpLeftShift, kOpRightShift, kOpComparisonEqual, kOpComparisonNotEqual,kOpComparisonGreaterEqual, kOpComparisonLesserEqual, kOpComparisonGreater, kOpComparisonLesser, kOpAnd, kOpXor, kOpOr, kOpAndAnd, kOpOrOr, kOpConditional };

struct sParserParamStruct 
{
    char mName[VAR_NAME_MAX];
    sNodeType* mType;
};

typedef struct sParserParamStruct sParserParam;

struct sNodeTreeStruct 
{
    enum eNodeType mNodeType;

    unsigned int mLeft;
    unsigned int mRight;
    unsigned int mMiddle;

    union {
        enum eOperand mOperand;
        char mByteValue;
        unsigned char mUByteValue;
        short mShortValue;
        unsigned short mUShortValue;
        int mIntValue;
        unsigned int mUIntValue;
        long mLongValue;
        unsigned long mULongValue;
        char mVarName[VAR_NAME_MAX];

        struct {
            char mVarName[VAR_NAME_MAX];
            sCLClass* mClass;
        } sAssignVariable;

        struct {
            unsigned int mExpressionNode;
            MANAGED sNodeBlock* mIfNodeBlock;
            unsigned int mElifExpressionNodes[ELIF_NUM_MAX];
            MANAGED sNodeBlock* mElifNodeBlocks[ELIF_NUM_MAX];
            int mElifNum;
            MANAGED sNodeBlock* mElseNodeBlock;
        } sIf;
        struct {
            unsigned int mExpressionNode;
            MANAGED sNodeBlock* mWhileNodeBlock;
        } sWhile;
        struct {
            unsigned int mExpressionNode;
            unsigned int mExpressionNode2;
            unsigned int mExpressionNode3;
            MANAGED sNodeBlock* mForNodeBlock;
        } sFor;
        struct {
            MANAGED sNodeBlock* mTryNodeBlock;
            MANAGED sNodeBlock* mCatchNodeBlock;
            char mExceptionVarName[VAR_NAME_MAX];
        } sTry;
        struct {
            sCLClass* mClass;
            char mMethodName[METHOD_NAME_MAX];
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
        } sClassMethodCall;
        struct {
            char mMethodName[METHOD_NAME_MAX];
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
        } sMethodCall;
        struct {
            sNodeType* mType;
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
            unsigned int mArrayNum;
        } sNewOperator;
        struct {
            char mVarName[VAR_NAME_MAX];
            sCLClass* mClass;
        } sClassField;

        wchar_t mCharacter;
        char* mString;

        struct {
            sParserParam mParams[PARAMS_MAX];
            int mNumParams;
            sNodeType* mResultType;
            sNodeBlock* mBlockObjectCode;
        } sBlockObject;

        struct {
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
        } sBlockCall;
    } uValue;

    sNodeType* mType;
};

typedef struct sNodeTreeStruct sNodeTree;

struct sCompileInfoStruct
{
    sByteCode* code;
    sConst* constant;
    int stack_num;
    sVarTable* lv_table;
    BOOL no_output;
    int err_num;
    sParserInfo* pinfo;
    sNodeType* type;
    int* num_break_points;
    int* break_points;
    sCLMethod* method;
    sNodeType* block_result_type;
};

typedef struct sCompileInfoStruct sCompileInfo;

extern sNodeTree* gNodes;

void init_nodes();
void free_nodes();
void show_node(unsigned int node);

BOOL compile(unsigned int node, sCompileInfo* info);
void arrange_stack(sCompileInfo* cinfo);

unsigned int sNodeTree_create_operand(enum eOperand operand, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_byte_value(char value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_ubyte_value(unsigned char value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_short_value(short value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_ushort_value(unsigned short value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_int_value(int value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_uint_value(unsigned int value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_long_value(long value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_ulong_value(unsigned long value, unsigned int left, unsigned int right, unsigned int middle);
unsigned int sNodeTree_create_store_variable(char* var_name, sNodeType* node_type, int right, sCLClass* klass);
unsigned int sNodeTree_create_assign_field(char* var_name, unsigned int left_node, unsigned int right_node);
unsigned int sNodeTree_create_load_variable(char* var_name);
unsigned int sNodeTree_create_return_expression(unsigned int expression_node);
unsigned int sNodeTree_create_throw_expression(unsigned int expression_node);
unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED sNodeBlock* if_node_block, unsigned int* elif_expression_node, MANAGED sNodeBlock** elif_node_block, int elif_num, MANAGED sNodeBlock* else_node_block);
unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED sNodeBlock* while_node_block);
unsigned int sNodeTree_break_expression();
unsigned int sNodeTree_false_expression();
unsigned int sNodeTree_true_expression();
unsigned int sNodeTree_null_expression();
unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED sNodeBlock* for_node_block);
BOOL check_node_is_variable(unsigned int node);
unsigned int sNodeTree_create_class_method_call(sCLClass* klass, char* method_name, unsigned int* params, int num_params);
unsigned int sNodeTree_create_method_call(unsigned int object_node, char* method_name, unsigned int* params, int num_params);
unsigned int sNodeTree_create_new_operator(sNodeType* node_type, unsigned int* params, int num_params, unsigned int array_num);
unsigned int sNodeTree_create_fields(char* name, unsigned int left_node);
unsigned int sNodeTree_create_class_fields(sCLClass* klass, char* name);
unsigned int sNodeTree_create_assign_class_field(sCLClass* klass, char* name , unsigned int right_node);
unsigned int sNodeTree_create_store_value_to_pointer(unsigned int left_node, sNodeType* node_type, unsigned int right_node);
unsigned int sNodeTree_create_load_value_from_pointer(unsigned int left_node, sNodeType* node_type);
BOOL sNodeTree_create_decrement_operand(unsigned int left_node);
BOOL sNodeTree_create_increment_operand(unsigned int left_node);
BOOL sNodeTree_create_increment_operand_with_value(unsigned int left_node, unsigned int value);
BOOL sNodeTree_create_decrement_operand_with_value(unsigned int left_node, unsigned int value);
BOOL sNodeTree_create_monadic_decrement_operand(unsigned int right_node);
BOOL sNodeTree_create_monadic_increment_operand(unsigned int right_node);
unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node);
unsigned int sNodeTree_create_store_array_element(unsigned int array, unsigned int index_ndoe, unsigned int right_node);
unsigned int sNodeTree_create_character_value(wchar_t c);
unsigned int sNodeTree_create_string_value(MANAGED char* value);
unsigned int sNodeTree_try_expression(MANAGED sNodeBlock* try_node_block, MANAGED sNodeBlock* catch_node_block, char* exception_var_name);

unsigned int sNodeTree_create_block_object(sParserParam* params, int num_params, sNodeType* result_type, MANAGED sNodeBlock* node_block);
unsigned int sNodeTree_create_block_call(unsigned int block, int num_params, unsigned int params[]);

/// script.c ///
BOOL compile_script(char* fname, char* source);

/// vm.c ///

#define OP_POP 1
#define OP_POP_N 2
#define OP_REVERSE 3
#define OP_COND_JUMP 4
#define OP_GOTO 5
#define OP_RETURN 6
#define OP_THROW 7
#define OP_TRY 8

#define OP_STORE 10
#define OP_LOAD 11

#define OP_LDCBYTE 20
#define OP_LDCUBYTE 21
#define OP_LDCSHORT 22
#define OP_LDCUSHORT 23
#define OP_LDCINT 24
#define OP_LDCUINT 25
#define OP_LDCLONG 26
#define OP_LDCULONG 27
#define OP_LDCNULL 28
#define OP_LDCPOINTER 29

#define OP_BADD 40
#define OP_BSUB 41
#define OP_BMULT 42
#define OP_BDIV 43
#define OP_BMOD 44

#define OP_UBADD 80
#define OP_UBSUB 81
#define OP_UBMULT 82
#define OP_UBDIV 83
#define OP_UBMOD 84

#define OP_SADD 100
#define OP_SSUB 101
#define OP_SMULT 102
#define OP_SDIV 103
#define OP_SMOD 104

#define OP_USADD 150
#define OP_USSUB 151
#define OP_USMULT 152
#define OP_USDIV 153
#define OP_USMOD 154

#define OP_IADD 200
#define OP_ISUB 201
#define OP_IMULT 202
#define OP_IDIV 203
#define OP_IMOD 204

#define OP_UISUB 250
#define OP_UIADD 251
#define OP_UIMULT 252
#define OP_UIDIV 253
#define OP_UIMOD 254

#define OP_LADD 300
#define OP_LSUB 301
#define OP_LMULT 302
#define OP_LDIV 303
#define OP_LMOD 304

#define OP_ULADD 400
#define OP_ULSUB 401
#define OP_ULMULT 402
#define OP_ULDIV 403
#define OP_ULMOD 404

#define OP_FADD 450
#define OP_FSUB 451
#define OP_FMULT 452
#define OP_FDIV 453

#define OP_DADD 500
#define OP_DSUB 501
#define OP_DMULT 502
#define OP_DDIV 503

#define OP_PADD 600
#define OP_PSUB 601

#define OP_CADD 700
#define OP_CSUB 701

#define OP_BEQ 1000
#define OP_BNOTEQ 1001
#define OP_BGT 1002
#define OP_BLE 1003
#define OP_BGTEQ 1004
#define OP_BLEEQ 1005

#define OP_UBEQ 1010
#define OP_UBNOTEQ 1011
#define OP_UBGT 1012
#define OP_UBLE 1013
#define OP_UBGTEQ 1014
#define OP_UBLEEQ 1015

#define OP_SEQ 1020
#define OP_SNOTEQ 1021
#define OP_SGT 1022
#define OP_SLE 1023
#define OP_SGTEQ 1024
#define OP_SLEEQ 1025

#define OP_USEQ 1030
#define OP_USNOTEQ 1031
#define OP_USGT 1032
#define OP_USLE 1033
#define OP_USGTEQ 1034
#define OP_USLEEQ 1035

#define OP_IEQ 1040
#define OP_INOTEQ 1041
#define OP_IGT 1042
#define OP_ILE 1043
#define OP_IGTEQ 1044
#define OP_ILEEQ 1045

#define OP_UIEQ 1050
#define OP_UINOTEQ 1051
#define OP_UIGT 1052
#define OP_UILE 1053
#define OP_UIGTEQ 1054
#define OP_UILEEQ 1055

#define OP_LEQ 1060
#define OP_LNOTEQ 1061
#define OP_LGT 1062
#define OP_LLE 1063
#define OP_LGTEQ 1064
#define OP_LLEEQ 1065

#define OP_ULEQ 1070
#define OP_ULNOTEQ 1071
#define OP_ULGT 1072
#define OP_ULLE 1073
#define OP_ULGTEQ 1074
#define OP_ULLEEQ 1075

#define OP_FEQ 1080
#define OP_FNOTEQ 1081
#define OP_FGT 1082
#define OP_FLE 1083
#define OP_FGTEQ 1084
#define OP_FLEEQ 1085

#define OP_DEQ 1090
#define OP_DNOTEQ 1091
#define OP_DGT 1092
#define OP_DLE 1093
#define OP_DGTEQ 1094
#define OP_DLEEQ 1095

#define OP_PEQ 1100
#define OP_PNOTEQ 1101
#define OP_PGT 1102
#define OP_PLE 1103
#define OP_PGTEQ 1104
#define OP_PLEEQ 1105

#define OP_CEQ 1200
#define OP_CNOTEQ 1201
#define OP_CGT 1202
#define OP_CLE 1203
#define OP_CGTEQ 1204
#define OP_CLEEQ 1205

#define OP_OBISNULL 1300
#define OP_CLASSNAME 1301

#define OP_ANDAND 2000
#define OP_OROR 2001
#define OP_LOGICAL_DENIAL 2002

#define OP_INVOKE_METHOD 3000
#define OP_INVOKE_VIRTUAL_METHOD 3001
#define OP_INVOKE_BLOCK 3002

#define OP_NEW 4000
#define OP_LOAD_FIELD 4001
#define OP_STORE_FIELD 4002
#define OP_LOAD_CLASS_FIELD 4003
#define OP_STORE_CLASS_FIELD 4004
#define OP_LOAD_ELEMENT 4005
#define OP_STORE_ELEMENT 4006

#define OP_STORE_VALUE_TO_INT_ADDRESS 5000
#define OP_STORE_VALUE_TO_UINT_ADDRESS 5001
#define OP_STORE_VALUE_TO_BYTE_ADDRESS 5002
#define OP_STORE_VALUE_TO_UBYTE_ADDRESS 5003
#define OP_STORE_VALUE_TO_SHORT_ADDRESS 5004
#define OP_STORE_VALUE_TO_USHORT_ADDRESS 5005
#define OP_STORE_VALUE_TO_LONG_ADDRESS 5006
#define OP_STORE_VALUE_TO_ULONG_ADDRESS 5007

#define OP_LOAD_VALUE_FROM_INT_ADDRESS 6000
#define OP_LOAD_VALUE_FROM_UINT_ADDRESS 6001
#define OP_LOAD_VALUE_FROM_BYTE_ADDRESS 6002
#define OP_LOAD_VALUE_FROM_UBYTE_ADDRESS 6003
#define OP_LOAD_VALUE_FROM_SHORT_ADDRESS 6004
#define OP_LOAD_VALUE_FROM_USHORT_ADDRESS 6005
#define OP_LOAD_VALUE_FROM_LONG_ADDRESS 6006
#define OP_LOAD_VALUE_FROM_ULONG_ADDRESS 6007

#define OP_UBYTE_TO_BYTE_CAST 7000
#define OP_SHORT_TO_BYTE_CAST 7001
#define OP_USHORT_TO_BYTE_CAST 7002
#define OP_INT_TO_BYTE_CAST 7003
#define OP_UINT_TO_BYTE_CAST 7004
#define OP_LONG_TO_BYTE_CAST 7005
#define OP_ULONG_TO_BYTE_CAST 7006
#define OP_FLOAT_TO_BYTE_CAST 7007
#define OP_DOUBLE_TO_BYTE_CAST 7008
#define OP_POINTER_TO_BYTE_CAST 7009
#define OP_CHAR_TO_BYTE_CAST 7010

#define OP_BYTE_TO_SHORT_CAST 7020
#define OP_UBYTE_TO_SHORT_CAST 7021
#define OP_USHORT_TO_SHORT_CAST 7022
#define OP_INT_TO_SHORT_CAST 7023
#define OP_UINT_TO_SHORT_CAST 7024
#define OP_LONG_TO_SHORT_CAST 7025
#define OP_ULONG_TO_SHORT_CAST 7026
#define OP_FLOAT_TO_SHORT_CAST 7027
#define OP_DOUBLE_TO_SHORT_CAST 7028
#define OP_POINTER_TO_SHORT_CAST 7029
#define OP_CHAR_TO_SHORT_CAST 7030

#define OP_BYTE_TO_INT_CAST 7040
#define OP_UBYTE_TO_INT_CAST 7041
#define OP_SHORT_TO_INT_CAST 7042
#define OP_USHORT_TO_INT_CAST 7043
#define OP_UINT_TO_INT_CAST 7044
#define OP_LONG_TO_INT_CAST 7045
#define OP_ULONG_TO_INT_CAST 7046
#define OP_FLOAT_TO_INT_CAST 7047
#define OP_DOUBLE_TO_INT_CAST 7048
#define OP_POINTER_TO_INT_CAST 7049
#define OP_CHAR_TO_INT_CAST 7050

#define OP_BYTE_TO_LONG_CAST 7060
#define OP_UBYTE_TO_LONG_CAST 7061
#define OP_SHORT_TO_LONG_CAST 7062
#define OP_USHORT_TO_LONG_CAST 7063
#define OP_INT_TO_LONG_CAST 7064
#define OP_UINT_TO_LONG_CAST 7065
#define OP_ULONG_TO_LONG_CAST 7066
#define OP_FLOAT_TO_LONG_CAST 7067
#define OP_DOUBLE_TO_LONG_CAST 7068
#define OP_POINTER_TO_LONG_CAST 7069
#define OP_CHAR_TO_LONG_CAST 7070

#define OP_BYTE_TO_UBYTE_CAST 7080
#define OP_SHORT_TO_UBYTE_CAST 7081
#define OP_USHORT_TO_UBYTE_CAST 7082
#define OP_INT_TO_UBYTE_CAST 7083
#define OP_UINT_TO_UBYTE_CAST 7084
#define OP_LONG_TO_UBYTE_CAST 7085
#define OP_ULONG_TO_UBYTE_CAST 7086
#define OP_FLOAT_TO_UBYTE_CAST 7087
#define OP_DOUBLE_TO_UBYTE_CAST 7088
#define OP_POINTER_TO_UBYTE_CAST 7089
#define OP_CHAR_TO_UBYTE_CAST 7090

#define OP_BYTE_TO_USHORT_CAST 7100
#define OP_UBYTE_TO_USHORT_CAST 7101
#define OP_SHORT_TO_USHORT_CAST 7102
#define OP_INT_TO_USHORT_CAST 7103
#define OP_UINT_TO_USHORT_CAST 7104
#define OP_LONG_TO_USHORT_CAST 7105
#define OP_ULONG_TO_USHORT_CAST 7106
#define OP_FLOAT_TO_USHORT_CAST 7107
#define OP_DOUBLE_TO_USHORT_CAST 7108
#define OP_POINTER_TO_USHORT_CAST 7109
#define OP_CHAR_TO_USHORT_CAST 7110

#define OP_BYTE_TO_UINT_CAST 7200
#define OP_UBYTE_TO_UINT_CAST 7201
#define OP_SHORT_TO_UINT_CAST 7202
#define OP_USHORT_TO_UINT_CAST 7203
#define OP_INT_TO_UINT_CAST 7204
#define OP_LONG_TO_UINT_CAST 7205
#define OP_ULONG_TO_UINT_CAST 7206
#define OP_FLOAT_TO_UINT_CAST 7207
#define OP_DOUBLE_TO_UINT_CAST 7208
#define OP_POINTER_TO_UINT_CAST 7209
#define OP_CHAR_TO_UINT_CAST 7210

#define OP_BYTE_TO_ULONG_CAST 7220
#define OP_UBYTE_TO_ULONG_CAST 7221
#define OP_SHORT_TO_ULONG_CAST 7222
#define OP_USHORT_TO_ULONG_CAST 7223
#define OP_INT_TO_ULONG_CAST 7224
#define OP_UINT_TO_ULONG_CAST 7225
#define OP_LONG_TO_ULONG_CAST 7226
#define OP_FLOAT_TO_ULONG_CAST 7227
#define OP_DOUBLE_TO_ULONG_CAST 7228
#define OP_POINTER_TO_ULONG_CAST 7229
#define OP_CHAR_TO_ULONG_CAST 7230

#define OP_BYTE_TO_FLOAT_CAST 7240
#define OP_UBYTE_TO_FLOAT_CAST 7241
#define OP_SHORT_TO_FLOAT_CAST 7242
#define OP_USHORT_TO_FLOAT_CAST 7243
#define OP_INT_TO_FLOAT_CAST 7244
#define OP_UINT_TO_FLOAT_CAST 7245
#define OP_LONG_TO_FLOAT_CAST 7246
#define OP_ULONG_TO_FLOAT_CAST 7247
#define OP_DOUBLE_TO_FLOAT_CAST 7248
#define OP_CHAR_TO_FLOAT_CAST 7250

#define OP_BYTE_TO_DOUBLE_CAST 7260
#define OP_UBYTE_TO_DOUBLE_CAST 7261
#define OP_SHORT_TO_DOUBLE_CAST 7262
#define OP_USHORT_TO_DOUBLE_CAST 7263
#define OP_INT_TO_DOUBLE_CAST 7264
#define OP_UINT_TO_DOUBLE_CAST 7265
#define OP_LONG_TO_DOUBLE_CAST 7266
#define OP_ULONG_TO_DOUBLE_CAST 7267
#define OP_FLOAT_TO_DOUBLE_CAST 7268
#define OP_CHAR_TO_DOUBLE_CAST 7270

#define OP_BYTE_TO_POINTER_CAST 7280
#define OP_UBYTE_TO_POINTER_CAST 7281
#define OP_SHORT_TO_POINTER_CAST 7282
#define OP_USHORT_TO_POINTER_CAST 7283
#define OP_INT_TO_POINTER_CAST 7284
#define OP_UINT_TO_POINTER_CAST 7285
#define OP_LONG_TO_POINTER_CAST 7286
#define OP_ULONG_TO_POINTER_CAST 7287
#define OP_CHAR_TO_POINTER_CAST 7290

#define OP_BYTE_TO_CHAR_CAST 7300
#define OP_UBYTE_TO_CHAR_CAST 7301
#define OP_SHORT_TO_CHAR_CAST 7302
#define OP_USHORT_TO_CHAR_CAST 7303
#define OP_INT_TO_CHAR_CAST 7304
#define OP_UINT_TO_CHAR_CAST 7305
#define OP_LONG_TO_CHAR_CAST 7306
#define OP_ULONG_TO_CHAR_CAST 7307
#define OP_FLOAT_TO_CHAR_CAST 7308
#define OP_DOUBLE_TO_CHAR_CAST 7309
#define OP_POINTER_TO_CHAR_CAST 7310

#define OP_BYTE_TO_STRING_CAST 7320
#define OP_SHORT_TO_STRING_CAST 7321
#define OP_INT_TO_STRING_CAST 7322
#define OP_LONG_TO_STRING_CAST 7323
#define OP_UBYTE_TO_STRING_CAST 7324
#define OP_USHORT_TO_STRING_CAST 7325
#define OP_UINT_TO_STRING_CAST 7326
#define OP_ULONG_TO_STRING_CAST 7327
#define OP_FLOAT_TO_STRING_CAST 7328
#define OP_DOUBLE_TO_STRING_CAST 7329
#define OP_BOOL_TO_STRING_CAST 7330
#define OP_POINTER_TO_STRING_CAST 7331
#define OP_CHAR_TO_STRING_CAST 7332

#define OP_BYTE_TO_INTEGER_CAST 7400
#define OP_UBYTE_TO_INTEGER_CAST 7401
#define OP_SHORT_TO_INTEGER_CAST 7402
#define OP_USHORT_TO_INTEGER_CAST 7403
#define OP_INT_TO_INTEGER_CAST 7404
#define OP_UINT_TO_INTEGER_CAST 7405
#define OP_LONG_TO_INTEGER_CAST 7406
#define OP_ULONG_TO_INTEGER_CAST 7407
#define OP_FLOAT_TO_INTEGER_CAST 7408
#define OP_DOUBLE_TO_INTEGER_CAST 7409
#define OP_CHAR_TO_INTEGER_CAST 7410
#define OP_POINTER_TO_INTEGER_CAST 7411
#define OP_BOOL_TO_INTEGER_CAST 7412

#define OP_BYTE_TO_UINTEGER_CAST 7420
#define OP_UBYTE_TO_UINTEGER_CAST 7421
#define OP_SHORT_TO_UINTEGER_CAST 7422
#define OP_USHORT_TO_UINTEGER_CAST 7423
#define OP_INT_TO_UINTEGER_CAST 7424
#define OP_UINT_TO_UINTEGER_CAST 7425
#define OP_LONG_TO_UINTEGER_CAST 7426
#define OP_ULONG_TO_UINTEGER_CAST 7427
#define OP_FLOAT_TO_UINTEGER_CAST 7428
#define OP_DOUBLE_TO_UINTEGER_CAST 7429
#define OP_CHAR_TO_UINTEGER_CAST 7430
#define OP_POINTER_TO_UINTEGER_CAST 7431
#define OP_BOOL_TO_UINTEGER_CAST 7432

#define OP_BYTE_TO_CBYTE_CAST 7440
#define OP_UBYTE_TO_CBYTE_CAST 7441
#define OP_SHORT_TO_CBYTE_CAST 7442
#define OP_USHORT_TO_CBYTE_CAST 7443
#define OP_INT_TO_CBYTE_CAST 7444
#define OP_UINT_TO_CBYTE_CAST 7445
#define OP_LONG_TO_CBYTE_CAST 7446
#define OP_ULONG_TO_CBYTE_CAST 7447
#define OP_FLOAT_TO_CBYTE_CAST 7448
#define OP_DOUBLE_TO_CBYTE_CAST 7449
#define OP_CHAR_TO_CBYTE_CAST 7450
#define OP_POINTER_TO_CBYTE_CAST 7451
#define OP_BOOL_TO_CBYTE_CAST 7452

#define OP_BYTE_TO_CUBYTE_CAST 7460
#define OP_UBYTE_TO_CUBYTE_CAST 7461
#define OP_SHORT_TO_CUBYTE_CAST 7462
#define OP_USHORT_TO_CUBYTE_CAST 7463
#define OP_INT_TO_CUBYTE_CAST 7464
#define OP_UINT_TO_CUBYTE_CAST 7465
#define OP_LONG_TO_CUBYTE_CAST 7466
#define OP_ULONG_TO_CUBYTE_CAST 7467
#define OP_FLOAT_TO_CUBYTE_CAST 7468
#define OP_DOUBLE_TO_CUBYTE_CAST 7469
#define OP_CHAR_TO_CUBYTE_CAST 7470
#define OP_POINTER_TO_CUBYTE_CAST 7471
#define OP_BOOL_TO_CUBYTE_CAST 7472

#define OP_BYTE_TO_CSHORT_CAST 7480
#define OP_UBYTE_TO_CSHORT_CAST 7481
#define OP_SHORT_TO_CSHORT_CAST 7482
#define OP_USHORT_TO_CSHORT_CAST 7483
#define OP_INT_TO_CSHORT_CAST 7484
#define OP_UINT_TO_CSHORT_CAST 7485
#define OP_LONG_TO_CSHORT_CAST 7486
#define OP_ULONG_TO_CSHORT_CAST 7487
#define OP_FLOAT_TO_CSHORT_CAST 7488
#define OP_DOUBLE_TO_CSHORT_CAST 7489
#define OP_CHAR_TO_CSHORT_CAST 7490
#define OP_POINTER_TO_CSHORT_CAST 7491
#define OP_BOOL_TO_CSHORT_CAST 7492

#define OP_BYTE_TO_CUSHORT_CAST 7500
#define OP_UBYTE_TO_CUSHORT_CAST 7501
#define OP_SHORT_TO_CUSHORT_CAST 7502
#define OP_USHORT_TO_CUSHORT_CAST 7503
#define OP_INT_TO_CUSHORT_CAST 7504
#define OP_UINT_TO_CUSHORT_CAST 7505
#define OP_LONG_TO_CUSHORT_CAST 7506
#define OP_ULONG_TO_CUSHORT_CAST 7507
#define OP_FLOAT_TO_CUSHORT_CAST 7508
#define OP_DOUBLE_TO_CUSHORT_CAST 7509
#define OP_CHAR_TO_CUSHORT_CAST 7510
#define OP_POINTER_TO_CUSHORT_CAST 7511
#define OP_BOOL_TO_CUSHORT_CAST 7512

#define OP_BYTE_TO_CLONG_CAST 7520
#define OP_UBYTE_TO_CLONG_CAST 7521
#define OP_SHORT_TO_CLONG_CAST 7522
#define OP_USHORT_TO_CLONG_CAST 7523
#define OP_INT_TO_CLONG_CAST 7524
#define OP_UINT_TO_CLONG_CAST 7525
#define OP_LONG_TO_CLONG_CAST 7526
#define OP_ULONG_TO_CLONG_CAST 7527
#define OP_FLOAT_TO_CLONG_CAST 7528
#define OP_DOUBLE_TO_CLONG_CAST 7529
#define OP_CHAR_TO_CLONG_CAST 7530
#define OP_POINTER_TO_CLONG_CAST 7531
#define OP_BOOL_TO_CLONG_CAST 7532

#define OP_BYTE_TO_CULONG_CAST 7540
#define OP_UBYTE_TO_CULONG_CAST 7541
#define OP_SHORT_TO_CULONG_CAST 7542
#define OP_USHORT_TO_CULONG_CAST 7543
#define OP_INT_TO_CULONG_CAST 7544
#define OP_UINT_TO_CULONG_CAST 7545
#define OP_LONG_TO_CULONG_CAST 7546
#define OP_ULONG_TO_CULONG_CAST 7547
#define OP_FLOAT_TO_CULONG_CAST 7548
#define OP_DOUBLE_TO_CULONG_CAST 7549
#define OP_CHAR_TO_CULONG_CAST 7550
#define OP_POINTER_TO_CULONG_CAST 7551
#define OP_BOOL_TO_CULONG_CAST 7552

#define OP_BYTE_TO_CFLOAT_CAST 7560
#define OP_UBYTE_TO_CFLOAT_CAST 7561
#define OP_SHORT_TO_CFLOAT_CAST 7562
#define OP_USHORT_TO_CFLOAT_CAST 7563
#define OP_INT_TO_CFLOAT_CAST 7564
#define OP_UINT_TO_CFLOAT_CAST 7565
#define OP_LONG_TO_CFLOAT_CAST 7566
#define OP_ULONG_TO_CFLOAT_CAST 7567
#define OP_FLOAT_TO_CFLOAT_CAST 7568
#define OP_DOUBLE_TO_CFLOAT_CAST 7569
#define OP_CHAR_TO_CFLOAT_CAST 7570
#define OP_BOOL_TO_CFLOAT_CAST 7572

#define OP_BYTE_TO_CDOUBLE_CAST 7580
#define OP_UBYTE_TO_CDOUBLE_CAST 7581
#define OP_SHORT_TO_CDOUBLE_CAST 7582
#define OP_USHORT_TO_CDOUBLE_CAST 7583
#define OP_INT_TO_CDOUBLE_CAST 7584
#define OP_UINT_TO_CDOUBLE_CAST 7585
#define OP_LONG_TO_CDOUBLE_CAST 7586
#define OP_ULONG_TO_CDOUBLE_CAST 7587
#define OP_FLOAT_TO_CDOUBLE_CAST 7588
#define OP_DOUBLE_TO_CDOUBLE_CAST 7589
#define OP_CHAR_TO_CDOUBLE_CAST 7590
#define OP_BOOL_TO_CDOUBLE_CAST 7592

#define OP_BYTE_TO_CPOINTER_CAST 7600
#define OP_UBYTE_TO_CPOINTER_CAST 7601
#define OP_SHORT_TO_CPOINTER_CAST 7602
#define OP_USHORT_TO_CPOINTER_CAST 7603
#define OP_INT_TO_CPOINTER_CAST 7604
#define OP_UINT_TO_CPOINTER_CAST 7605
#define OP_LONG_TO_CPOINTER_CAST 7606
#define OP_ULONG_TO_CPOINTER_CAST 7607
#define OP_CHAR_TO_CPOINTER_CAST 7610
#define OP_POINTER_TO_CPOINTER_CAST 7611
#define OP_BOOL_TO_CPOINTER_CAST 7612

#define OP_BYTE_TO_CCHAR_CAST 7620
#define OP_UBYTE_TO_CCHAR_CAST 7621
#define OP_SHORT_TO_CCHAR_CAST 7622
#define OP_USHORT_TO_CCHAR_CAST 7623
#define OP_INT_TO_CCHAR_CAST 7624
#define OP_UINT_TO_CCHAR_CAST 7625
#define OP_LONG_TO_CCHAR_CAST 7626
#define OP_ULONG_TO_CCHAR_CAST 7627
#define OP_FLOAT_TO_CCHAR_CAST 7628
#define OP_DOUBLE_TO_CCHAR_CAST 7629
#define OP_CHAR_TO_CCHAR_CAST 7630
#define OP_POINTER_TO_CCHAR_CAST 7631
#define OP_BOOL_TO_CCHAR_CAST 7632

#define OP_BYTE_TO_CBOOL_CAST 7640
#define OP_UBYTE_TO_CBOOL_CAST 7641
#define OP_SHORT_TO_CBOOL_CAST 7642
#define OP_USHORT_TO_CBOOL_CAST 7643
#define OP_INT_TO_CBOOL_CAST 7644
#define OP_UINT_TO_CBOOL_CAST 7645
#define OP_LONG_TO_CBOOL_CAST 7646
#define OP_ULONG_TO_CBOOL_CAST 7647
#define OP_FLOAT_TO_CBOOL_CAST 7648
#define OP_DOUBLE_TO_CBOOL_CAST 7649
#define OP_CHAR_TO_CBOOL_CAST 7650
#define OP_POINTER_TO_CBOOL_CAST 7651
#define OP_BOOL_TO_CBOOL_CAST 7652

#define OP_GET_ARRAY_LENGTH 8000

#define OP_CREATE_STRING 9000
#define OP_CREATE_BLOCK_OBJECT 9001

BOOL vm(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sVMInfo* info);
void vm_mutex_on();
void vm_mutex_off();
sCLClass* get_class_with_load_and_initialize(char* class_name);
void class_final_on_runtime();
BOOL call_finalize_method_on_free_object(sCLClass* klass, CLObject self);

/// class_compiler.c ///
#define PARSE_PHASE_ALLOC_CLASSES 1
#define PARSE_PHASE_ADD_SUPER_CLASSES 2
#define PARSE_PHASE_CALCULATE_SUPER_CLASSES 3
#define PARSE_PHASE_ADD_GENERICS_TYPES 4
#define PARSE_PHASE_ADD_METHODS_AND_FIELDS 5
#define PARSE_PHASE_COMPILE_PARAM_INITIALIZER 6
#define PARSE_PHASE_DO_COMPILE_CODE 7
#define PARSE_PHASE_MAX 8

BOOL compile_class_source(char* fname, char* source);

/// klass_compile_time.c ///
BOOL add_method_to_class(sCLClass* klass, char* method_name, sParserParam* params, int num_params, sNodeType* result_type, BOOL native_, BOOL static_);
BOOL add_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, sNodeType* result_type);
BOOL add_class_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, sNodeType* result_type);
void add_code_to_method(sCLMethod* method, sByteCode* code, int var_num);
BOOL write_all_modified_classes();
int search_for_method(sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, int start_point, sNodeType* generics_type, sNodeType** result_type);
int search_for_field(sCLClass* klass, char* field_name);
int search_for_class_field(sCLClass* klass, char* field_name);
void add_dependences_with_node_type(sCLClass* klass, sNodeType* node_type);
sCLClass* get_class_with_load(char* class_name);
BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info);
BOOL check_implemented_methods_for_interface(sCLClass* left_class, sCLClass* right_class);

/// native_method.c ///
void native_method_init();
void native_method_final();

fNativeMethod get_native_method(char* path);

/// exception.c ///
void entry_exception_object_with_class_name(CLVALUE* stack, char* class_name, char* msg, ...);
void show_exception_message(CLObject exception);

/// method_compiler.c ///
BOOL compile_method(sCLMethod* method, sParserParam* params, int num_params, sParserInfo* info, sCompileInfo* cinfo);

/// type.c ///
BOOL is_void_type(sCLType* cl_type, sCLClass* klass);
sCLClass* get_class_from_cl_type(sCLType* cl_type, sCLClass* klass);

/// stack.c ///
struct sCLStackStruct {
    CLVALUE* mStack;
    CLVALUE** mStackPtr;

    struct sCLStackStruct* mNextStack;
};

typedef struct sCLStackStruct sCLStack;

void stack_init();
void stack_final();

void append_stack_to_stack_list(CLVALUE* stack, CLVALUE** stack_ptr);
BOOL remove_stack_to_stack_list(CLVALUE* stack);
BOOL check_variables_existance_on_stack(CLVALUE* stack_top, int var_num);

sCLStack* gHeadStack;
CLVALUE* gGlobalStack;
CLVALUE* gGlobalStackPtr;

/// heap.c ///
struct sCLHeapMemStruct {
    int mSize;
    sCLClass* mClass;       // NULL --> no class only memory
    int mArrayNum;
    void* mMem;
};

typedef struct sCLHeapMemStruct sCLHeapMem;

#define CLHEAPMEM(obj) (get_object_pointer((obj)))

void heap_init(int heap_size, int size_hadles);
void heap_final();

CLObject alloc_heap_mem(int size, sCLClass* klass, int array_num);
sCLHeapMem* get_object_pointer(CLObject obj);
void show_heap(sVMInfo* info);
void mark_object(CLObject obj, unsigned char* mark_flg);

/// module.c ///
struct sCLModuleStruct {
    BOOL mModified;
    char mName[CL_MODULE_NAME_MAX+1];
    sBuf mBody;
};

typedef struct sCLModuleStruct sCLModule;

void module_init();
void module_final();
sCLModule* create_module(char* module_name);
void unload_module(char* module_name);
void append_character_to_module(sCLModule* self, char c);
void append_str_to_module(sCLModule* self, char* str);
sCLModule* get_module(char* module_name);
char* get_module_body(sCLModule* module);
void write_all_modified_modules();
void this_module_is_modified(sCLModule* self);
BOOL load_module_from_file(ALLOC sCLModule** self, char* module_name);

/// object.c ///
#define DUMMY_ARRAY_SIZE 32

struct sCLObjectStruct {
    int mSize;
    sCLClass* mClass;
    union {
        int mArrayNum;
        int mNumFields;
    };
    CLVALUE mFields[DUMMY_ARRAY_SIZE];
};

typedef struct sCLObjectStruct sCLObject;

#define CLOBJECT(obj) (sCLObject*)(get_object_pointer((obj)))

CLObject create_object(sCLClass* klass);
BOOL free_object(CLObject self);
void object_mark_fun(CLObject self, unsigned char* mark_flg);

/// array.c ///
CLObject create_array_object(sCLClass* klass, int array_num);
void array_mark_fun(CLObject self, unsigned char* mark_flg);

/// block.c ///
struct sBlockObjectStruct
{
    int mSize;
    sCLClass* mClass;       // NULL --> no class only memory
    int mArrayNum;
    sByteCode mCodes;
    sConst mConstant;
    CLVALUE* mParentStack;
    int mParentVarNum;
    int mBlockVarNum;
};

typedef struct sBlockObjectStruct sBlockObject;

#define CLBLOCK(obj) (sBlockObject*)(get_object_pointer((obj)))

CLObject create_block_object(sByteCode* codes, sConst* constant, CLVALUE* parent_stack, int parent_var_num, int block_var_num);

/// string.c ///
CLObject create_string_object(char* str);
CLObject create_string_from_two_strings(CLObject left, CLObject right);
int get_length_from_string_object(CLObject str);
CLVALUE* get_str_array_from_string_object(CLObject str);

/// integer.c ///
CLObject create_integer(int value);
CLObject create_uinteger(unsigned int value);

/// byte.c ///
CLObject create_byte(char value);
CLObject create_ubyte(unsigned char value);

/// short.c ///
CLObject create_short(short value);
CLObject create_ushort(unsigned short value);

/// long.c ///
CLObject create_long(long value);
CLObject create_ulong(unsigned long value);

/// float.c ///
CLObject create_float(float value);
CLObject create_double(double value);

/// pointer.c ///
CLObject create_pointer(char* value);

/// char.c ///
CLObject create_char(wchar_t value);

/// bool.c ///
CLObject create_bool(BOOL value);

/// class_system.c ///
BOOL System_exit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_assert(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_calloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_free(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strlen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strcpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strncpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strdup(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_print(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_println(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_printlnToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_printToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_sleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

#endif

