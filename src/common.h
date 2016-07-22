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
#define CLASS_FLAGS_FINAL 0x02
#define CLASS_FLAGS_MODIFIED 0x04

struct sCLClassStruct;

struct sCLTypeStruct {
    int mClassNameOffset;

    int mNumGenericsTypes;
    struct sCLTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];

    BOOL mArray;
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

    int mGenericsParamClassNum;   // -1 is none generics param 

    int mVersion;
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
};

typedef struct sCLClassStruct sCLClass;

#define CLASS_NAME(klass) (CONS_str((&(klass)->mConst), (klass)->mClassNameOffset))
#define METHOD_NAME2(klass, method) (CONS_str((&(klass)->mConst), (method)->mNameOffset))

void class_init();
void class_final();

sCLClass* get_class(char* name);
unsigned int get_hash_key(char* name, unsigned int max);
sCLClass* alloc_class(char* class_name, BOOL primitive_, BOOL final_, int generics_param_class_num);
ALLOC sCLType* create_cl_type(sCLClass* klass, sCLClass* klass2);
void free_cl_type(sCLType* cl_type);
sCLClass* load_class_with_version(char* class_name, int class_version);
sCLClass* load_class(char* class_name);

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
struct sNodeTypeStruct {
    sCLClass* mClass;

    struct sNodeTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];
    int mNumGenericsTypes;

    BOOL mArray;
};

typedef struct sNodeTypeStruct sNodeType;

void init_node_types();
void free_node_types();
sNodeType* alloc_node_type();
sNodeType* clone_node_type(sNodeType* node_type);
sNodeType* create_node_type_with_class_name(char* class_name);
sNodeType* create_node_type_from_cl_type(sCLType* cl_type, sCLClass* klass);

BOOL substitution_posibility(sNodeType* left, sNodeType* right);
BOOL substitution_posibility_with_class_name(sNodeType* left, char* right_class_name);
BOOL operand_posibility(sNodeType* left, sNodeType* right);
BOOL operand_posibility_with_class_name(sNodeType* left, char* right_class_name);
BOOL solve_generics_types_for_node_type(sNodeType* node_type, ALLOC sNodeType** result, sNodeType* type_);
BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name);
BOOL type_identify(sNodeType* left, sNodeType* right);

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

// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_);

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name);

int get_var_num(sVarTable* table);

/// parser.c ///
struct sParserInfoStruct
{
    char* p;
    char* sname;
    int sline;
    int err_num;
    sVarTable* lv_table;
    int parse_phase;
    sCLClass* klass;
};

typedef struct sParserInfoStruct sParserInfo;

void parser_err_msg(sParserInfo* info, const char* msg, ...);
BOOL expression(unsigned int* node, sParserInfo* info);
void skip_spaces_and_lf(sParserInfo* info);
void expect_next_character_with_one_forward(char* characters, sParserInfo* info);
BOOL parse_word(char* buf, int buf_size, sParserInfo* info, BOOL print_out_err_msg);
BOOL parse_type(sNodeType** result_type, sParserInfo* info);

/// node_block ///
struct sNodeBlockStruct
{
    unsigned int* mNodes;
    unsigned int mSizeNodes;
    unsigned int mNumNodes;

    sVarTable* mLVTable;
};

typedef struct sNodeBlockStruct sNodeBlock;

void sNodeBlock_free(sNodeBlock* block);
BOOL parse_normal_block(ALLOC sNodeBlock** node_block, sParserInfo* info);
struct sCompileInfoStruct;
BOOL compile_normal_block(sNodeBlock* block, struct sCompileInfoStruct* info);

/// node.c ///
enum eNodeType { kNodeTypeOperand, kNodeTypeByteValue, kNodeTypeUByteValue, kNodeTypeShortValue, kNodeTypeUShortValue, kNodeTypeIntValue, kNodeTypeUIntValue, kNodeTypeLongValue, kNodeTypeULongValue, kNodeTypeAssignVariable, kNodeTypeLoadVariable, kNodeTypeIf, kNodeTypeWhile, kNodeTypeBreak, kNodeTypeTrue, kNodeTypeFalse, kNodeTypeNull, kNodeTypeFor, kNodeTypeClassMethodCall, kNodeTypeReturn, kNodeTypeNewOperator, kNodeTypeLoadField, kNodeTypeStoreField , kNodeTypeLoadClassField, kNodeTypeStoreClassField, kNodeTypeLoadValueFromPointer, kNodeTypeStoreValueToPointer, kNodeTypeIncrementOperand, kNodeTypeDecrementOperand, kNodeTypeIncrementWithValueOperand, kNodeTypeDecrementWithValueOperand, kNodeTypeMonadicIncrementOperand, kNodeTypeMonadicDecrementOperand, kNodeTypeLoadArrayElement, kNodeTypeStoreArrayElement };

enum eOperand { kOpAdd, kOpSub , kOpComplement, kOpLogicalDenial, kOpMult, kOpDiv, kOpMod, kOpLeftShift, kOpRightShift, kOpComparisonEqual, kOpComparisonNotEqual,kOpComparisonGreaterEqual, kOpComparisonLesserEqual, kOpComparisonGreater, kOpComparisonLesser, kOpAnd, kOpXor, kOpOr, kOpAndAnd, kOpOrOr, kOpConditional };

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
            sCLClass* mClass;
            char mMethodName[METHOD_NAME_MAX];
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
        } sClassMethodCall;
        struct {
            sNodeType* mType;
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
            int mArrayNum;
        } sNewOperator;
        struct {
            char mVarName[VAR_NAME_MAX];
            sCLClass* mClass;
        } sClassField;
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
unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED sNodeBlock* if_node_block, unsigned int* elif_expression_node, MANAGED sNodeBlock** elif_node_block, int elif_num, MANAGED sNodeBlock* else_node_block);
unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED sNodeBlock* while_node_block);
unsigned int sNodeTree_break_expression();
unsigned int sNodeTree_false_expression();
unsigned int sNodeTree_true_expression();
unsigned int sNodeTree_null_expression();
unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED sNodeBlock* for_node_block);
BOOL check_node_is_variable(unsigned int node);
unsigned int sNodeTree_create_class_method_call(sCLClass* klass, char* method_name, unsigned int* params, int num_params);
unsigned int sNodeTree_create_new_operator(sNodeType* node_type, unsigned int* params, int num_params, int array_num);
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

/// script.c ///
BOOL compile_script(char* fname, char* source);

/// vm.c ///

#define OP_POP 1
#define OP_POP_N 2
#define OP_REVERSE 3
#define OP_COND_JUMP 4
#define OP_GOTO 5
#define OP_RETURN 6

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

#define OP_UBADD 80
#define OP_UBSUB 81
#define OP_UBMULT 82
#define OP_UBDIV 83

#define OP_SADD 100
#define OP_SSUB 101
#define OP_SMULT 102
#define OP_SDIV 103

#define OP_USADD 150
#define OP_USSUB 151
#define OP_USMULT 152
#define OP_USDIV 153

#define OP_IADD 200
#define OP_ISUB 201
#define OP_IMULT 202
#define OP_IDIV 203

#define OP_UISUB 250
#define OP_UIADD 251
#define OP_UIMULT 252
#define OP_UIDIV 253

#define OP_LADD 300
#define OP_LSUB 301
#define OP_LMULT 302
#define OP_LDIV 303

#define OP_ULADD 400
#define OP_ULSUB 401
#define OP_ULMULT 402
#define OP_ULDIV 403

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

#define OP_ANDAND 2000
#define OP_OROR 2001

#define OP_INVOKE_METHOD 3000

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

#define OP_SHORT_TO_BYTE_CAST 7000
#define OP_INT_TO_BYTE_CAST 7001
#define OP_LONG_TO_BYTE_CAST 7002
#define OP_BYTE_TO_SHORT_CAST 7003
#define OP_INT_TO_SHORT_CAST 7004
#define OP_LONG_TO_SHORT_CAST 7005
#define OP_BYTE_TO_INT_CAST 7006
#define OP_SHORT_TO_INT_CAST 7007
#define OP_LONG_TO_INT_CAST 7008
#define OP_BYTE_TO_LONG_CAST 7009
#define OP_SHORT_TO_LONG_CAST 7010
#define OP_INT_TO_LONG_CAST 7011

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

struct sParserParamStruct 
{
    char mName[VAR_NAME_MAX];
    sNodeType* mType;
};

typedef struct sParserParamStruct sParserParam;

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

/// native_method.c ///
void native_method_init();
void native_method_final();

fNativeMethod get_native_method(char* path);

/// exception.c ///
void entry_exception_object_with_class_name(CLVALUE* stack, char* class_name, char* msg, ...);

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

sCLStack* gHeadStack;

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

#endif

