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

typedef void (*fMarkFun)(CLObject self, unsigned char* mark_flg);
typedef void (*fFreeFun)(CLObject self);

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

    fFreeFun mFreeFun;
    fMarkFun mMarkFun;

    int mInitializeMethodIndex;

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
void mark_all_class_fields(unsigned char* mark_flg);

struct sClassTableStruct
{
    char* mName;
    sCLClass* mItem;

    struct sClassTableStruct* mNextClass;
};

typedef struct sClassTableStruct sClassTable;

sClassTable* gHeadClassTable;

/// node_type.c ///
struct sNodeTypeStruct {
    sCLClass* mClass;

    struct sNodeTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];
    int mNumGenericsTypes;
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
enum eNodeType { kNodeTypeOperand, kNodeTypeByteValue, kNodeTypeUByteValue, kNodeTypeShortValue, kNodeTypeUShortValue, kNodeTypeIntValue, kNodeTypeUIntValue, kNodeTypeLongValue, kNodeTypeULongValue, kNodeTypeAssignVariable, kNodeTypeLoadVariable, kNodeTypeIf, kNodeTypeWhile, kNodeTypeBreak, kNodeTypeTrue, kNodeTypeFalse, kNodeTypeNull, kNodeTypeFor, kNodeTypeClassMethodCall, kNodeTypeReturn, kNodeTypeNewOperator, kNodeTypeLoadField, kNodeTypeStoreField , kNodeTypeLoadClassField, kNodeTypeStoreClassField, kNodeTypeLoadValueFromPointer, kNodeTypeStoreValueToPointer, kNodeTypeIncrementOperand, kNodeTypeDecrementOperand };

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
unsigned int sNodeTree_create_assign_variable(char* var_name, sNodeType* node_type, int right, sCLClass* klass);
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
unsigned int sNodeTree_create_new_operator(sNodeType* node_type, unsigned int* params, int num_params);
unsigned int sNodeTree_create_fields(char* name, unsigned int left_node);
unsigned int sNodeTree_create_class_fields(sCLClass* klass, char* name);
unsigned int sNodeTree_create_assign_class_field(sCLClass* klass, char* name , unsigned int right_node);
unsigned int sNodeTree_create_store_value_to_pointer(unsigned int left_node, sNodeType* node_type, unsigned int right_node);
unsigned int sNodeTree_create_load_value_from_pointer(unsigned int left_node, sNodeType* node_type);
BOOL sNodeTree_create_decment_operand(unsigned int left_node);
BOOL sNodeTree_create_increment_operand(unsigned int left_node);

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

#define OP_BADD 40
#define OP_BSUB 41
#define OP_UBADD 42
#define OP_UBSUB 43
#define OP_SADD 44
#define OP_SSUB 45
#define OP_USADD 46
#define OP_USSUB 47
#define OP_IADD 48
#define OP_ISUB 49
#define OP_UISUB 50
#define OP_UIADD 51
#define OP_LADD 52
#define OP_LSUB 53
#define OP_ULADD 54
#define OP_ULSUB 55
#define OP_FADD 56
#define OP_FSUB 57
#define OP_DADD 58
#define OP_DSUB 59
#define OP_PADD 60
#define OP_PSUB 61

#define OP_BEQ 100
#define OP_BNOTEQ 101
#define OP_UBEQ 102
#define OP_UBNOTEQ 103
#define OP_SEQ 104
#define OP_SNOTEQ 105
#define OP_USEQ 106
#define OP_USNOTEQ 107
#define OP_IEQ 108
#define OP_INOTEQ 109
#define OP_UIEQ 110
#define OP_UINOTEQ 111
#define OP_LEQ 112
#define OP_LNOTEQ 123
#define OP_ULEQ 124
#define OP_ULNOTEQ 125
#define OP_FEQ 126
#define OP_FNOTEQ 127
#define OP_DEQ 128
#define OP_DNOTEQ 129
#define OP_PEQ 130
#define OP_PNOTEQ 131

#define OP_ANDAND 150
#define OP_OROR 151

#define OP_INVOKE_METHOD 200

#define OP_NEW 300
#define OP_LOAD_FIELD 301
#define OP_STORE_FIELD 302
#define OP_LOAD_CLASS_FIELD 303
#define OP_STORE_CLASS_FIELD 304

#define OP_STORE_VALUE_TO_INT_ADDRESS 400
#define OP_STORE_VALUE_TO_UINT_ADDRESS 401
#define OP_STORE_VALUE_TO_BYTE_ADDRESS 402
#define OP_STORE_VALUE_TO_UBYTE_ADDRESS 403
#define OP_STORE_VALUE_TO_SHORT_ADDRESS 404
#define OP_STORE_VALUE_TO_USHORT_ADDRESS 405
#define OP_STORE_VALUE_TO_LONG_ADDRESS 406
#define OP_STORE_VALUE_TO_ULONG_ADDRESS 407

#define OP_LOAD_VALUE_FROM_INT_ADDRESS 450
#define OP_LOAD_VALUE_FROM_UINT_ADDRESS 451
#define OP_LOAD_VALUE_FROM_BYTE_ADDRESS 452
#define OP_LOAD_VALUE_FROM_UBYTE_ADDRESS 453
#define OP_LOAD_VALUE_FROM_SHORT_ADDRESS 454
#define OP_LOAD_VALUE_FROM_USHORT_ADDRESS 455
#define OP_LOAD_VALUE_FROM_LONG_ADDRESS 456
#define OP_LOAD_VALUE_FROM_ULONG_ADDRESS 457

BOOL vm(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sVMInfo* info);
void vm_mutex_on();
void vm_mutex_off();
sCLClass* get_class_with_load_and_initialize(char* class_name);

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
    void* mMem;
};

typedef struct sCLHeapMemStruct sCLHeapMem;

#define CLHEAPMEM(obj) (get_object_pointer((obj)))

void heap_init(int heap_size, int size_hadles);
void heap_final();

CLObject alloc_heap_mem(int size, sCLClass* klass);
sCLHeapMem* get_object_pointer(CLObject obj);
void show_heap(sVMInfo* info);
void mark_object(CLObject obj, unsigned char* mark_flg);

/// object.c ///
#define DUMMY_ARRAY_SIZE 32

struct sCLObjectStruct {
    int mSize;
    sCLClass* mClass;
    int mNumFields;
    CLVALUE mFields[DUMMY_ARRAY_SIZE];
};

typedef struct sCLObjectStruct sCLObject;

#define CLOBJECT(obj) (sCLObject*)(get_object_pointer((obj)))

void object_mark_fun(CLObject self, unsigned char* mark_flg);;
CLObject create_object(sCLClass* klass);

/// class_system.c ///
BOOL System_exit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_assert(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

/// class_clover.c ///
BOOL Clover_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_free(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

#endif

