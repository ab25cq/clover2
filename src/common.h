#ifndef COMMON_H
#define COMMON_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "config.h"

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
#include <pcre.h>
#include <dlfcn.h>
#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif
#ifndef _USE_MISC
#define _USE_MISC
#endif
#ifndef __USE_BSD
#define __USE_BSD
#endif

#include <termios.h>

#define clint64 long long      // for 32 bit cpu

#include "clover2-macros.h"

/// debug.c ///
#include "clover2-debug.h"

/// buffer.c ///
#include "clover2-buffer.h"

/// xfunc.c ///
#include "clover2-xfunc.h"

/// limits ///
#define VERSION_MAX 128
#define HEAP_INIT_SIZE 128
#define HEAP_HANDLE_INIT_SIZE 128
#define CLASS_NAME_MAX 64
#define VAR_NAME_MAX 64
#define METHOD_NAME_MAX VAR_NAME_MAX
#define ELIF_NUM_MAX 32
#define BREAK_NUM_MAX 32
#define PARAMS_MAX 32
#define METHOD_VAR_NUM_MAX 64
#define GENERICS_TYPES_MAX 32
#define CLASS_VERSION_MAX 128
#define METHOD_PATH_MAX METHOD_NAME_MAX+32+CLASS_NAME_MAX+PARAMS_MAX*CLASS_NAME_MAX
#define METHOD_NUM_MAX 512
#define CL_MODULE_HASH_SIZE 256
#define CL_MODULE_NAME_MAX CLASS_NAME_MAX
#define ARRAY_VALUE_ELEMENT_MAX 32
#define LIST_VALUE_ELEMENT_MAX ARRAY_VALUE_ELEMENT_MAX
#define TUPLE_VALUE_ELEMENT_MAX ARRAY_VALUE_ELEMENT_MAX
#define HASH_VALUE_ELEMENT_MAX ARRAY_VALUE_ELEMENT_MAX
#define TYPEDEF_MAX 32
#define CLASS_NUM_MAX 512
#define CLOVER_STACK_SIZE 1024
//#define CLOVER_STACK_SIZE 512
#define METHOD_CHAIN_MAX 128
#define STRING_EXPRESSION_MAX 16
#define GLOBAL_STACK_MAX 128
#define METHOD_DEFAULT_PARAM_MAX 128
#define METHOD_BLOCK_PARAM_MAX 16
#define CLOVER2_NUM_THREAD_MAX 512
#define ANDAND_OROR_MAX 32
#define PARSER_ERR_MSG_MAX 8

#define WHEN_BLOCK_MAX 32

#define MAX_COND_JUMP 128

#define SIGMAX 256

/// CLVALUE ///
typedef unsigned int CLObject;

union CLVALUEUnion {
    unsigned int mUIntValue;
    unsigned char mUByteValue;
    unsigned short mUShortValue;
    unsigned clint64 mULongValue;
    int mIntValue;
    char mByteValue;
    short mShortValue;
    clint64 mLongValue;
    CLObject mObjectValue;
    wchar_t mCharValue;
    float mFloatValue;
    double mDoubleValue;
    BOOL mBoolValue;
    char* mPointerValue;
    void* LLVMValue;
    int mJSValue;
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
void sByteCode_clone(sByteCode* self, sByteCode* code);
void append_value_to_code(sByteCode* code, void* data, size_t size, BOOL no_output);
void append_opecode_to_code(sByteCode* code, unsigned int op, BOOL no_output);
void append_int_value_to_code(sByteCode* code, int value, BOOL no_output);
void append_long_value_to_code(sByteCode* code, clint64 value, BOOL no_output);
void append_double_value_to_code(sByteCode* code, double value, BOOL no_output);
void append_float_value_to_code(sByteCode* code, float value, BOOL no_output);

/// constant.c ///
struct sConstStruct
{
    char* mConst;
    unsigned int mSize;
    unsigned int mLen;
};

typedef struct sConstStruct sConst;

#define CONS_str(constant, offset) (char*)((constant)->mConst + offset)

void sConst_init(sConst* self);
void sConst_init_with_size(sConst* self, unsigned int size);
void sConst_free(sConst* self);
void sConst_clone(sConst* self, sConst* constant);

unsigned int sConst_append(sConst* self, void* data, int size, BOOL no_output);
unsigned int append_int_value_to_constant_pool(sConst* constant, int n, BOOL no_output);
unsigned int append_float_value_to_constant_pool(sConst* constant, float n, BOOL no_output);
unsigned int append_double_value_to_constant_pool(sConst* constant, double n, BOOL no_output);
unsigned int append_str_to_constant_pool(sConst* constant, char* str, BOOL no_output);
void append_buffer_to_constant_pool_and_code(sConst* constant, sByteCode* code, char* buf, int size, BOOL no_output);
unsigned int append_wstr_to_constant_pool(sConst* constant, char* str, BOOL no_output);
void append_str_to_constant_pool_and_code(sConst* constant, sByteCode* code, char* str, BOOL no_output);

/// stack.c ///
struct sCLStackStruct {
    CLVALUE* mStack;
    CLVALUE** mStackPtr;

    int mStackID;
    BOOL mGlobalStack;

    struct sCLStackStruct* mNextStack;
};

typedef struct sCLStackStruct sCLStack;

void stack_init();
void stack_final();

sCLStack* append_stack_to_stack_list(CLVALUE* stack_mem, CLVALUE** stack_ptr, BOOL global);
BOOL remove_stack_to_stack_list(sCLStack* stack);
BOOL check_variables_existance_on_stack(CLVALUE* stack, CLVALUE* stack_ptr);

struct sVMInfoStruct;

void create_global_stack_and_append_it_to_stack_list(struct sVMInfoStruct* info);
void push_value_to_global_stack(CLVALUE value, struct sVMInfoStruct* info);
void push_object_to_global_stack(CLObject obj, struct sVMInfoStruct* info);
void free_global_stack(struct sVMInfoStruct* info);
CLVALUE pop_global_stack(struct sVMInfoStruct* info);

extern sCLStack* gHeadStack;

/// klass.c ///
#define CLASS_FLAGS_PRIMITIVE 0x01
#define CLASS_FLAGS_INTERFACE 0x02
#define CLASS_FLAGS_MODIFIED 0x04
#define CLASS_FLAGS_ALLOCATED 0x08
#define CLASS_FLAGS_DYNAMIC_CLASS 0x10
#define CLASS_FLAGS_NO_FREE_OBJECT 0x20
#define CLASS_FLAGS_LAMBDA 0x40
#define CLASS_FLAGS_JS 0x80
#define CLASS_FLAGS_NATIVE 0x100

struct sCLTypeStruct;

struct sCLBlockTypeStruct {
    struct sCLTypeStruct* mParams[PARAMS_MAX];
    int mNumParams;

    struct sCLTypeStruct* mResultType;
};

typedef struct sCLBlockTypeStruct sCLBlockType;

struct sCLTypeStruct {
    unsigned int mClassNameOffset;

    int mNumGenericsTypes;
    struct sCLTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];

    BOOL mArray;
    BOOL mNullable;

    sCLBlockType* mBlockType;
};

typedef struct sCLTypeStruct sCLType;

struct sCLParamStruct {
    unsigned int mNameOffset;                // variable name

    sCLType* mType;

    unsigned int mDefaultValueOffset;
};

typedef struct sCLParamStruct sCLParam;

#define METHOD_FLAGS_NATIVE 0x01
#define METHOD_FLAGS_CLASS_METHOD 0x02
#define METHOD_FLAGS_MODIFIED 0x08
#define METHOD_FLAGS_C_FUNCTION 0x20
#define METHOD_FLAGS_DYNAMIC 0x40
#define METHOD_FLAGS_JS 0x80
#define METHOD_FLAGS_PURE_NATIVE 0x100

#define EXCEPTION_MESSAGE_MAX 1024
#define STACK_TRACE_MAX 64

struct sVMInfoStruct {
    char* try_catch_label_name;

    CLVALUE* current_stack;
    int current_var_num;
    int try_offset;
    char** try_pc;
    sByteCode* try_code;

    struct sCLClassStruct* running_class;
    struct sCLMethodStruct* running_method;

    sCLStack* stack_id;
    char exception_message[EXCEPTION_MESSAGE_MAX];

    char stack_trace_sname[STACK_TRACE_MAX][128];
    int stack_trace_sline[STACK_TRACE_MAX];

    int num_stack_trace;

    BOOL no_mutex_in_vm;

    BOOL andand_oror_left_value[ANDAND_OROR_MAX];
    BOOL andand_oror_right_value[ANDAND_OROR_MAX];
    int num_andand_oror;

    BOOL running_thread;

    BOOL prohibit_delete_global_stack;

    CLVALUE* mGlobalStack;
    CLVALUE* mGlobalStackPtr;
    int mSizeGlobalStack;
    sCLStack* mGlobalStackID;

    CLVALUE* mTmpGlobalStack;
    CLVALUE* mTmpGlobalStackPtr;
    int mTmpSizeGlobalStack;
    sCLStack* mTmpGlobalStackID;

    char* try_catch_label_name_before;
    int try_offset_before;
    sByteCode* try_code_before;

    char* running_class_name;
    char* running_method_name;

    char sname[128];
    int sline;
    char sname2[128];
    int sline2;

    sBuf* js_source;
    sConst* js_const;

    sBuf* js_class_source;
    BOOL js_compiling_class_source;

    sBuf* require_source;

    BOOL in_finalize_method;

    CLVALUE* stack;
};

typedef struct sVMInfoStruct sVMInfo;

typedef BOOL (*fNativeMethod)(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

struct sCLMethodStruct {
    clint64 mFlags;
    unsigned int mNameOffset;
    unsigned int mPathOffset;
    unsigned int mMethodNameAndParamsOffset;
    unsigned int mJSMethodNameAndParamsOffset;
    unsigned int mJSMethodNameOffset;
    int mMethodIndex;

    sCLParam mParams[PARAMS_MAX]; // +1 --> self
    int mNumParams;

    sCLType* mResultType;

    sByteCode mByteCodes;
    fNativeMethod mNativeMethod;
    char* mNativeFunName;
    sBuf* mNativeCodes;
    
    int mVarNum;

    void* mJITDynamicSym;       // this requires runtime

    int mNumGenerics;
    unsigned int mGenericsParamTypeOffsets[GENERICS_TYPES_MAX];

    unsigned int mCLibraryOffset;
    void* mCFunctionPointer;    // this requires runtime
};

typedef struct sCLMethodStruct sCLMethod;

#define FIELD_FLAGS_PRIVATE 0x01
#define FIELD_FLAGS_PROTECTED 0x02
#define FIELD_FLAGS_MODIFIED 0x04
#define FIELD_FLAGS_DELEGATED 0x08
#define FIELD_FLAGS_READONLY 0x10

struct sCLFieldStruct {
    clint64 mFlags;
    unsigned int mNameOffset;

    sCLType* mResultType;
    CLVALUE mValue;

    int mInitializeValue; // -1 is none initialized value. This is for enum or C bridge.

    int mDelegatedMethodIndex[METHOD_NUM_MAX];  // compile time variable
    int mNumDelegatedMethod;
    int mNumGetterMethodIndex; 
};

struct sCLBlockObjectStruct {
    sByteCode mByteCodes;
    sConst mConst;
    int mVarNum;
    int mNumParams;
    BOOL mLambda;
};

typedef struct sCLBlockObjectStruct sCLBlockObject;

typedef struct sCLFieldStruct sCLField;
typedef void (*fFreeFun)(CLObject self);

struct sCLClassStruct {
    clint64 mFlags;

    int mGenericsParamClassNum;   // -1 is none generics param 
    int mMethodGenericsParamClassNum;  // -1 is none geenrics param
    int mNumGenerics;

    unsigned int mGenericsParamNameOffsets[GENERICS_TYPES_MAX];
    unsigned int mGenericsParamTypeOffsets[GENERICS_TYPES_MAX];

    sConst mConst;

    unsigned int mClassNameOffset;

    sCLMethod* mMethods;
    int mNumMethods;
    int mSizeMethods;

    sCLField* mFields;
    int mNumFields;
    int mSizeFields;

    sCLField* mClassFields;
    int mNumClassFields;
    int mSizeClassFields;

    sCLBlockObject* mBlockObjects;
    int mNumBlockObjects;
    int mSizeBlockObjects;

    int mClassInitializeMethodIndex;
    int mClassFinalizeMethodIndex;
    int mFinalizeMethodIndex;
    int mCallingMethodIndex;
    int mCallingClassMethodIndex;
    int mAllocSizeMethodIndex;

    int mMethodIndexOnCompileTime;                  // This requires on the compile time
    int mInitMethodIndexOnCompileTime;              // This requires on the compile time
    sCLMethod* mVirtualMethodTable[METHOD_NUM_MAX]; // This requires on the run time

    struct sCLClassStruct* mBoxingClass; // This requires on the run time 
    struct sCLClassStruct* mUnboxingClass; // This requires on the run time
    void* mDynamicLibrary;  // This requires on the run time

    fFreeFun mFreeFun;

    unsigned int mTypedefClassName1Offsets[TYPEDEF_MAX];
    unsigned int mTypedefClassName2Offsets[TYPEDEF_MAX];
    int mNumTypedef;

    unsigned int mUnboxingClassNameOffset;

    BOOL mInitialized;   // This requires on the run time

    int mLabelNum;      // This requires on the compile time

    int mVersion;

    BOOL mAlreadyLoadedJSClass;
};

typedef struct sCLClassStruct sCLClass;

#define CLASS_NAME(klass) (CONS_str((&(klass)->mConst), (klass)->mClassNameOffset))
#define METHOD_NAME2(klass, method) (CONS_str((&(klass)->mConst), (method)->mNameOffset))
#define METHOD_PATH(klass, method) (CONS_str((&(klass)->mConst), (method)->mPathOffset))
#define FIELD_NAME(klass, field) (CONS_str((&(klass)->mConst), (field)->mNameOffset))
#define METHOD_NAME_AND_PARAMS(klass, method) (CONS_str((&(klass)->mConst), (method)->mMethodNameAndParamsOffset))
#define METHOD_NAME_AND_PARAMS_JS(klass, method) (CONS_str((&(klass)->mConst), (method)->mJSMethodNameAndParamsOffset))

void class_init();
void class_final();

void reset_js_load_class();
sCLClass* get_class_with_load(char* class_name, BOOL js);
sCLClass* get_class(char* class_name, BOOL js);
unsigned int get_hash_key(char* name, unsigned int max);
sCLClass* alloc_class(char* class_name, BOOL primitive_, int generics_param_class_num, int method_generics_param_class_num, int generics_number, char name_of_generics_params[GENERICS_TYPES_MAX][VAR_NAME_MAX], sCLClass** type_of_generics_params, BOOL interface, BOOL dynamic_class, BOOL no_free_object, BOOL lambda, sCLClass* unboxing_class, int version, BOOL js, BOOL native_);
ALLOC sCLType* create_cl_type(sCLClass* klass, sCLClass* klass2);
void free_cl_type(sCLType* cl_type);
sCLClass* get_class(char* class_name, BOOL js);
sCLMethod* search_for_method_from_virtual_method_table(sCLClass* klass, char* method_name_and_params);
BOOL is_valid_class(sCLClass* klass);
BOOL put_class_to_table(char* class_name, sCLClass* klass);
BOOL jit_compile_all_classes();
sCLClass* load_class_from_class_file(char* class_name, char* class_file_name);
void set_boxing_and_unboxing_classes();
BOOL search_for_class_file(char* class_name, char* class_file_name, size_t class_file_name_size, int version, BOOL js);
BOOL is_class_file_existance(char* class_name, int version, BOOL js);
sCLClass* load_class(char* class_name, int version, BOOL js);

struct sClassTableStruct
{
    char* mName;
    sCLClass* mItem;
    BOOL mFreed;
    BOOL mInitialized;

    struct sClassTableStruct* mNextClass;
};

typedef struct sClassTableStruct sClassTable;

extern sClassTable* gHeadClassTable;
extern sClassTable* gJSHeadClassTable;

BOOL create_virtual_method_table(sCLClass* klass);

/// node_type.c ///
struct sNodeBlockTypeStruct;

struct sNodeTypeStruct {
    sCLClass* mClass;

    struct sNodeTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];
    int mNumGenericsTypes;

    BOOL mArray;
    BOOL mNullable;
    MANAGED struct sNodeBlockTypeStruct* mBlockType;
};

typedef struct sNodeTypeStruct sNodeType;

void init_node_types();
void free_node_types();
BOOL is_delegated_class(sNodeType* left_class, sNodeType* right_class);
sNodeType* alloc_node_type();
sNodeType* clone_node_type(sNodeType* node_type);
sNodeType* create_node_type_with_class_name(char* class_name, BOOL js);
sNodeType* create_node_type_with_class_name(char* class_name, BOOL js);
sNodeType* create_node_type_with_method_generics_number(int generics_num, BOOL js);
sNodeType* create_node_type_from_cl_type(sCLType* cl_type, sCLClass* klass);
sNodeType* create_node_type_with_class_pointer(sCLClass* klass);

struct sParserInfoStruct;
BOOL is_exception_type(sNodeType* exception_type);

BOOL substitution_posibility(sNodeType* left, sNodeType* right, sNodeType* left_generics_types, sNodeType* right_generics_types, sNodeType* left_method_generics, sNodeType* right_method_generics, BOOL output_message);
BOOL cast_posibility(sNodeType* left_type, sNodeType* right_type);
sNodeType* create_node_type_with_generics_number(int generics_num, BOOL js);
BOOL substitution_posibility_with_class_name(sNodeType* left, char* right_class_name, BOOL output_message);
BOOL operand_posibility_with_class_name(sNodeType* left, char* right_class_name, char* op_string);
BOOL operand_posibility(sNodeType* left, sNodeType* right, char* op_string);
BOOL solve_generics_types_for_node_type(sNodeType* node_type, ALLOC sNodeType** result, sNodeType* generics_type, BOOL solve_self, BOOL solve_method_generics);
void solve_generics_for_variable_to_class(sCLClass* klass, sCLClass** result, struct sParserInfoStruct* info);
void solve_method_generics_for_variable_to_class(sCLClass* klass, sCLClass** result, struct sParserInfoStruct* info);
void solve_generics_for_variable(sNodeType* generics_type, sNodeType** generics_type2, struct sParserInfoStruct* info);
BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name);
BOOL type_identify(sNodeType* left, sNodeType* right);
BOOL class_identify_with_class_name(sCLClass* klass, char* class_name);
void print_node_type(sNodeType* node_type);
BOOL boxing_posibility(sNodeType* left_type, sNodeType* right_type);
void boxing_to_lapper_type(sNodeType** type_);
BOOL unboxing_posibility(sNodeType* left_type, sNodeType* right_type);
BOOL unboxig_posibility(sCLClass* klass);
sNodeType* create_generics_types_from_generics_params(sCLClass* klass);
struct sCompileInfoStruct;
void boxing_to_lapper_class(sNodeType** type_, struct sCompileInfoStruct* info);
BOOL unboxing_to_primitive_type(sNodeType** left_type, struct sCompileInfoStruct* info);
void make_boxing_type(sNodeType* type, sNodeType** result);
BOOL no_cast_types_for_binary_operator(sNodeType* left_type, sNodeType* right_type);


/// node_block_object.c ///
struct sNodeBlockTypeStruct {
    sNodeType* mParams[PARAMS_MAX];
    int mNumParams;

    sNodeType* mResultType;

    BOOL mLambda;
};

typedef struct sNodeBlockTypeStruct sNodeBlockType;

void init_node_block_types();
void free_node_block_types();
sNodeBlockType* alloc_node_block_type();
sNodeBlockType* clone_node_block_type(sNodeBlockType* block);
BOOL substitution_posibility_for_node_block_type(sNodeBlockType* left_block, sNodeBlockType* right_block, sNodeType* left_generics_types, sNodeType* right_generics_types, BOOL output_message);
void free_block(CLObject self);

/// vtable.c ///
struct sVarStruct {
    char mName[VAR_NAME_MAX];
    int mIndex;
    sNodeType* mType;

    int mBlockLevel;

    BOOL mReadOnly;
};

typedef struct sVarStruct sVar;

#define LOCAL_VARIABLE_MAX 1024

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
sVarTable* clone_var_table(sVarTable* lv_table);
void restore_var_table(sVarTable* left, sVarTable* right);

void set_max_block_var_num(sVarTable* new_table, sVarTable* lv_table);

int get_variable_index(sVarTable* table, char* name);
void check_already_added_variable(sVarTable* table, char* name, struct sParserInfoStruct* info);

// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_, BOOL readonly);

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name);

// result: (null) not found (sVar*) found
sVar* get_variable_from_index(sVarTable* table, int index);

int get_var_num(sVarTable* table);
void show_vtable(sVarTable* table);

int get_parent_var_num_of_sum(sVarTable* table);

/// parser.c ///
extern BOOL gInterpreter;

extern char** gCommandNames;
extern int gNumCommandNames;

struct sGenericsParamInfoStruct
{
    char mParamNames[GENERICS_TYPES_MAX][VAR_NAME_MAX];
    int mNumParams;
    sCLClass* mInterface[GENERICS_TYPES_MAX];
};

typedef struct sGenericsParamInfoStruct sGenericsParamInfo;

struct sCompileInfoStruct;

struct sParserInfoStruct
{
    char* p;
    char* sname;
    char* source;
    int sline;
    int err_num;
    sVarTable* lv_table;
    int parse_phase;
    sCLClass* klass;
    sGenericsParamInfo generics_info;
    sGenericsParamInfo method_generics_info;
    struct sCompileInfoStruct* cinfo;
    BOOL included_source;
    BOOL get_type_for_interpreter;
    int get_in_the_shell_mode;
    BOOL inputing_shell_mode;
    BOOL next_command_is_to_bool;
    BOOL exist_block_object_err;
    BOOL exist_brace_unclosed;
    BOOL get_path_object;
    BOOL inputing_path_object;
    BOOL multiple_assignment;
    BOOL mJS;
};

typedef struct sParserInfoStruct sParserInfo;

void parser_init();
void parser_final();
struct sParserParamStruct;
BOOL parse_params_and_entry_to_lvtable(struct sParserParamStruct* params, int* num_params, sParserInfo* info, sVarTable** new_table, sVarTable* parent_lv_table, int character_type);
void parser_err_msg(sParserInfo* info, const char* msg, ...);
BOOL expression(unsigned int* node, sParserInfo* info);
void skip_spaces_and_lf(sParserInfo* info);
void expect_next_character_with_one_forward(char* characters, sParserInfo* info);
BOOL parse_word(char* buf, int buf_size, sParserInfo* info, BOOL print_out_err_msg, BOOL no_skip_lf);
BOOL parse_type(sNodeType** result_type, sParserInfo* info);
BOOL parse_class_type(sCLClass** klass, sParserInfo* info);
BOOL parse_method_params(int* num_params, unsigned int* params, sParserInfo* info);
BOOL parse_block_object(unsigned int* node, sParserInfo* info, BOOL lambda);
BOOL parse_simple_lambda_params(unsigned int* node, sParserInfo* info, BOOL lambda);

/// node_block.c ///
struct sNodeBlockStruct
{
    unsigned int* mNodes;
    unsigned int mSizeNodes;
    unsigned int mNumNodes;

    sVarTable* mLVTable;
    BOOL mUnClosedBlock;

    sBuf mSource;
    char* mSName;
    int mSLine;
};

typedef struct sNodeBlockStruct sNodeBlock;

void sNodeBlock_free(sNodeBlock* block);
sNodeBlock* sNodeBlock_clone(sNodeBlock* block);
BOOL parse_block(ALLOC sNodeBlock** node_block, sParserInfo* info, sVarTable* new_table, BOOL block_object, BOOL string_expression);
BOOL create_null_block(ALLOC sNodeBlock** node_block, sParserInfo* info, sVarTable* new_table, BOOL block_object);
BOOL parse_question_operator_block(unsigned int object_node, int num_method_chains, ALLOC sNodeBlock** node_block, sParserInfo* info);

/// node.c ///
enum eNodeType { kNodeTypeOperand, kNodeTypeByteValue, kNodeTypeCByteValue, kNodeTypeUByteValue, kNodeTypeCUByteValue, kNodeTypeShortValue, kNodeTypeCShortValue, kNodeTypeUShortValue, kNodeTypeCUShortValue, kNodeTypeIntValue, kNodeTypeCIntValue, kNodeTypeUIntValue, kNodeTypeCUIntValue, kNodeTypeLongValue, kNodeTypeCLongValue, kNodeTypeULongValue, kNodeTypeCULongValue, kNodeTypeAssignVariable, kNodeTypeLoadVariable, kNodeTypeIf, kNodeTypeWhile, kNodeTypeBreak, kNodeTypeTrue, kNodeTypeFalse, kNodeTypeNull, kNodeTypeWildCard, kNodeTypeFor, kNodeTypeClassMethodCall, kNodeTypeMethodCall, kNodeTypeReturn, kNodeTypeNewOperator, kNodeTypeLoadField, kNodeTypeStoreField , kNodeTypeLoadClassField, kNodeTypeStoreClassField, kNodeTypeLoadValueFromPointer, kNodeTypeStoreValueToPointer, kNodeTypeMonadicIncrementOperand, kNodeTypeMonadicDecrementOperand, kNodeTypeLoadArrayElement, kNodeTypeStoreArrayElement, kNodeTypeChar, kNodeTypeString, kNodeTypeBuffer, kNodeTypeThrow, kNodeTypeTry, kNodeTypeBlockObject, kNodeTypeFunction, kNodeTypeBlockCall, kNodeTypeNormalBlock, kNodeTypeArrayValue, kNodeTypeAndAnd, kNodeTypeOrOr, kNodeTypeHashValue, kNodeTypeRegex, kNodeTypeListValue, kNodeTypeSortableListValue, kNodeTypeEqualableListValue, kNodeTypeTupleValue, kNodeTypeCArrayValue, kNodeTypeEqualableCArrayValue, kNodeTypeSortableCArrayValue, kNodeTypeImplements, kNodeTypeGetAddress, kNodeTypeInheritCall, kNodeTypeFloatValue, kNodeTypeCFloatValue, kNodeTypeDoubleValue, kNodeTypeCDoubleValue, kNodeTypePath, kNodeTypeWhen, kNodeTypeRange, kNodeTypeMultipleAsignment, kNodeTypeJSArray, kNodeTypeRequire };

enum eOperand { kOpAdd, kOpSub , kOpComplement, kOpLogicalDenial, kOpMult, kOpDiv, kOpMod, kOpLeftShift, kOpRightShift, kOpComparisonEqual, kOpComparisonNotEqual,kOpComparisonGreaterEqual, kOpComparisonLesserEqual, kOpComparisonGreater, kOpComparisonLesser, kOpAnd, kOpXor, kOpOr, kOpMinus };

struct sParserParamStruct 
{
    char mName[VAR_NAME_MAX];
    sNodeType* mType;

    char mDefaultValue[METHOD_DEFAULT_PARAM_MAX];
};

typedef struct sParserParamStruct sParserParam;

struct sNodeTreeStruct 
{
    enum eNodeType mNodeType;

    unsigned int mLeft;
    unsigned int mRight;
    unsigned int mMiddle;

    char* mSName;
    int mLine;

    union {
        enum eOperand mOperand;
        char mByteValue;
        unsigned char mUByteValue;
        short mShortValue;
        unsigned short mUShortValue;
        int mIntValue;
        unsigned int mUIntValue;
        clint64 mLongValue;
        unsigned clint64 mULongValue;
        char mVarName[VAR_NAME_MAX];

        struct {
            char mVarName[VAR_NAME_MAX];
            sCLClass* mClass;
        } sAssignVariable;

        struct {
            char mClassName[METHOD_NAME_MAX];
            char mFileName[METHOD_NAME_MAX];
        } sRequire;

        struct {
            unsigned int mExpressionNode;
            MANAGED sNodeBlock* mIfNodeBlock;
            unsigned int mElifExpressionNodes[ELIF_NUM_MAX];
            MANAGED sNodeBlock* mElifNodeBlocks[ELIF_NUM_MAX];
            int mElifNum;
            MANAGED sNodeBlock* mElseNodeBlock;
            BOOL mIfUnclosed;
            BOOL mElifUnclosed[ELIF_NUM_MAX];
        } sIf;
        struct {
            unsigned int mExpressionNode;
            int mNumWhenBlock;
            int mValueNodes[WHEN_BLOCK_MAX][WHEN_BLOCK_MAX];
            int mNumValues[WHEN_BLOCK_MAX];
            sNodeBlock* mWhenBlocks[WHEN_BLOCK_MAX];
            sNodeType* mWhenTypes[WHEN_BLOCK_MAX];
            sNodeType* mWhenTypes2[WHEN_BLOCK_MAX];
            BOOL mMatch[WHEN_BLOCK_MAX];
            sNodeBlock* mElseBlock;
        } sWhen;
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
            sNodeType* mClass;
            char mMethodName[METHOD_NAME_MAX];
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
        } sClassMethodCall;
        struct {
            char mMethodName[METHOD_NAME_MAX];
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
            int mNumMethodChains;
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
        struct {
            char* mString;
            sNodeBlock* mStringExpressions[STRING_EXPRESSION_MAX];
            int mStringExpressionOffsets[STRING_EXPRESSION_MAX];
            int mNumStringExpression;
        } sString;

        struct {
            char* mBuffer;
            int mLen;
            sNodeBlock* mStringExpressions[STRING_EXPRESSION_MAX];
            int mStringExpressionOffsets[STRING_EXPRESSION_MAX];
            int mNumStringExpression;
        } sBuffer;

        struct {
            sParserParam mParams[PARAMS_MAX];
            int mNumParams;
            sNodeType* mResultType;
            sNodeBlock* mBlockObjectCode;
            BOOL mLambda;
            BOOL mOmitResultType;
            BOOL mOmitParams;
            sVarTable* mOldTable;

            BOOL mQuestionOperator;
            sCLClass* mClass;
        } sBlockObject;

        struct {
            char mName[VAR_NAME_MAX];
            sParserParam mParams[PARAMS_MAX];
            int mNumParams;
            sNodeType* mResultType;
            sNodeBlock* mBlockObjectCode;
            BOOL mLambda;
            sCLClass* mClass;
        } sFunction;

        struct {
            char mBlockName[METHOD_NAME_MAX];
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
        } sBlockCall;

        struct {
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
            int mMethodIndex;
        } sInheritCall;

        sNodeBlock* mBlock;

        struct {
            unsigned int mArrayElements[ARRAY_VALUE_ELEMENT_MAX];
            int mNumArrayElements;
        } sArrayValue;
        struct {
            unsigned int mListElements[LIST_VALUE_ELEMENT_MAX];
            int mNumListElements;
        } sListValue;
        struct {
            unsigned int mTupleElements[TUPLE_VALUE_ELEMENT_MAX];
            int mNumTupleElements;
        } sTupleValue;
        struct {
            unsigned int mHashKeys[HASH_VALUE_ELEMENT_MAX];
            unsigned int mHashItems[HASH_VALUE_ELEMENT_MAX];
            int mNumHashElements;
        } sHashValue;
        struct {
            char* mRegexStr;
            BOOL mGlobal;
            BOOL mIgnoreCase;
            BOOL mMultiline;
            BOOL mExtended;
            BOOL mDotAll;
            BOOL mAnchored;
            BOOL mDollarEndOnly;
            BOOL mUngreedy;
            sNodeBlock* mStringExpressions[STRING_EXPRESSION_MAX];
            int mStringExpressionOffsets[STRING_EXPRESSION_MAX];
            int mNumStringExpression;
        } sRegex;

        float mFloatValue;
        double mDoubleValue;
    } uValue;

    sNodeType* mType;
    int mMaxMethodChains;
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
    struct sParserInfoStruct* pinfo;
    sNodeType* type;
    int* num_break_points;
    int* break_points;
    sCLMethod* method;
    sNodeType* block_result_type;
    BOOL in_block;
    BOOL omit_block_result_type;
    sNodeType* block_last_type;
    char* sname;
    int sline;

    char* break_point_label_name;
    BOOL no_pop_next;

    sNodeType* question_operator_result_type;

    int mNumBlockObject;
};

typedef struct sCompileInfoStruct sCompileInfo;

extern sNodeTree* gNodes;

void init_nodes();
void free_nodes();
void show_node(unsigned int node);
unsigned int clone_node(unsigned int node);

void compile_err_msg(sCompileInfo* info, const char* msg, ...);
BOOL compile(unsigned int node, sCompileInfo* info);
void append_class_name_to_constant_pool_and_code(sCompileInfo* info, sCLClass* klass);
void create_type_name_from_node_type(char* type_name, int type_name_max, sNodeType* node_type);
int get_var_size(sNodeType* var_type);
void boxing_before_method_call(char* method_name, sCompileInfo* info, BOOL* array_and_special_method);

unsigned int sNodeTree_create_operand(enum eOperand operand, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_js_array(int num_elements, unsigned int list_elements[], sParserInfo* info);
unsigned int sNodeTree_create_multiple_asignment(int num_elements, unsigned int tuple_elements[], int right_value, sParserInfo* info);
unsigned int sNodeTree_when_expression(unsigned int expression_node, unsigned int value_nodes[WHEN_BLOCK_MAX][WHEN_BLOCK_MAX], int num_values[WHEN_BLOCK_MAX], sNodeBlock* when_blocks[WHEN_BLOCK_MAX], int num_when_block, sNodeBlock* else_block, sNodeType* when_types[WHEN_BLOCK_MAX], sNodeType* when_types2[WHEN_BLOCK_MAX], BOOL when_match[WHEN_BLOCK_MAX], sParserInfo* info, char* sname, int sline);
unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED sNodeBlock* if_node_block, unsigned int* elif_expression_nodes, MANAGED sNodeBlock** elif_node_blocks, int elif_num, MANAGED sNodeBlock* else_node_block, BOOL if_unclosed, BOOL* elif_unclosed, sParserInfo* info, char* sname, int sline);
unsigned int sNodeTree_create_range(unsigned int head, unsigned int tail, sParserInfo* info);
unsigned int sNodeTree_create_byte_value(char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cbyte_value(char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_ubyte_value(unsigned char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cubyte_value(unsigned char value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_short_value(short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cshort_value(short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_ushort_value(unsigned short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cushort_value(unsigned short value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_int_value(int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cint_value(int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_uint_value(unsigned int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cuint_value(unsigned int value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_long_value(clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_clong_value(clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_ulong_value(unsigned clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_culong_value(unsigned clint64 value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_store_variable(char* var_name, sNodeType* node_type, int right, sCLClass* klass, sParserInfo* info);
unsigned int sNodeTree_create_assign_field(char* var_name, unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_load_variable(char* var_name, sParserInfo* info);
unsigned int sNodeTree_create_return_expression(unsigned int expression_node, sParserInfo* info);
unsigned int sNodeTree_create_throw_expression(unsigned int expression_node, sParserInfo* info);
unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED sNodeBlock* while_node_block, sParserInfo* info);
unsigned int sNodeTree_break_expression(sParserInfo* info);
unsigned int sNodeTree_false_expression(sParserInfo* info);
unsigned int sNodeTree_true_expression(sParserInfo* info);
unsigned int sNodeTree_null_expression(sParserInfo* info);
unsigned int sNodeTree_wildcard_expression(sParserInfo* info);
unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED sNodeBlock* for_node_block, sParserInfo* info);
BOOL check_node_is_variable(unsigned int node);
unsigned int sNodeTree_create_class_method_call(sNodeType* klass, char* method_name, unsigned int* params, int num_params, sParserInfo* info);
unsigned int sNodeTree_create_method_call(unsigned int object_node, char* method_name, unsigned int* params, int num_params, int num_method_chains, sParserInfo* info);
unsigned int sNodeTree_create_new_operator(sNodeType* node_type, unsigned int* params, int num_params, unsigned int array_num, sParserInfo* info);
unsigned int sNodeTree_create_fields(char* name, unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_class_fields(sCLClass* klass, char* name, sParserInfo* info);
unsigned int sNodeTree_create_assign_class_field(sCLClass* klass, char* name , unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_store_value_to_pointer(unsigned int left_node, sNodeType* node_type, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_load_value_from_pointer(unsigned int left_node, sNodeType* node_type, sParserInfo* info);
BOOL sNodeTree_create_monadic_decrement_operand(unsigned int right_node, sParserInfo* info);
BOOL sNodeTree_create_monadic_increment_operand(unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node, sParserInfo* info);
unsigned int sNodeTree_create_store_array_element(unsigned int array, unsigned int index_ndoe, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_character_value(wchar_t c, sParserInfo* info);

unsigned int sNodeTree_create_string_value(MANAGED char* value, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info);
unsigned int sNodeTree_create_buffer_value(MANAGED char* value, int len, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info);
unsigned int sNodeTree_try_expression(MANAGED sNodeBlock* try_node_block, MANAGED sNodeBlock* catch_node_block, char* exception_var_name, sParserInfo* info);

unsigned int sNodeTree_create_block_object(sParserParam* params, int num_params, sNodeType* result_type, MANAGED sNodeBlock* node_block, BOOL lambda, sParserInfo* info, BOOL omit_result_type, BOOL omit_params, sVarTable* old_table, BOOL question_operator);
unsigned int sNodeTree_create_block_call(unsigned int block, char* block_name, int num_params, unsigned int params[], sParserInfo* info);
unsigned int sNodeTree_conditional_expression(unsigned int expression_node, unsigned int true_expression_node, unsigned int false_expression_node, sParserInfo* info);
unsigned int sNodeTree_create_normal_block(MANAGED sNodeBlock* node_block, sParserInfo* info);
unsigned int sNodeTree_create_array_value(int num_elements, unsigned int array_elements[], sParserInfo* info);
unsigned int sNodeTree_create_list_value(int num_elements, unsigned int list_elements[], sParserInfo* info);
unsigned int sNodeTree_create_equalable_list_value(int num_elements, unsigned int list_elements[], sParserInfo* info);
unsigned int sNodeTree_create_sortable_list_value(int num_elements, unsigned int list_elements[], sParserInfo* info);
unsigned int sNodeTree_create_tuple_value(int num_elements, unsigned int tuple_elements[], sParserInfo* info);
unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_hash_value(int num_elements, unsigned int hash_keys[], unsigned int hash_items[], sParserInfo* info);
unsigned int sNodeTree_create_regex(MANAGED char* regex_str, BOOL global, BOOL ignore_case, BOOL multiline, BOOL extended, BOOL dotall, BOOL anchored, BOOL dollar_endonly, BOOL ungreedy, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info);
unsigned int sNodeTree_create_carray_value(int num_elements, unsigned int array_elements[], sParserInfo* info);
unsigned int sNodeTree_create_equalable_carray_value(int num_elements, unsigned int array_elements[], sParserInfo* info);
unsigned int sNodeTree_create_sortable_carray_value(int num_elements, unsigned int array_elements[], sParserInfo* info);
unsigned int sNodeTree_create_implements(unsigned int lnode, char* interface_name, sParserInfo* info);
unsigned int sNodeTree_create_get_address(unsigned int node, sParserInfo* info);
unsigned int sNodeTree_create_require(char* class_name, char* file_name, sParserInfo* info);
unsigned int sNodeTree_create_inherit_call(int num_params, unsigned int params[], int method_index, sParserInfo* info);
unsigned int sNodeTree_create_float_value(float value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cfloat_value(float value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_double_value(double value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_cdouble_value(double value, unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_path_value(MANAGED char* value, int len, sNodeBlock** string_expressions, int* string_expression_offsets, int num_string_expression, sParserInfo* info);
unsigned int sNodeTree_create_function(char* fun_name, sParserParam* params, int num_params, sNodeType* result_type, MANAGED sNodeBlock* node_block, BOOL lambda, sParserInfo* info);

void arrange_stack(sCompileInfo* cinfo);

/// node_block.c ///
BOOL compile_block(sNodeBlock* block, sCompileInfo* info, sNodeType* result_type, sNodeType** block_last_type);
BOOL compile_block_with_result(sNodeBlock* block, sCompileInfo* info);

/// script_ctime.c ///
BOOL compile_script(char* fname, char* source, BOOL js);
BOOL read_source(char* fname, sBuf* source);
BOOL delete_comment(sBuf* source, sBuf* source2);
void append_cwd_for_path(char* fname, char* fname2);

/// script.c ///
BOOL eval_file(char* fname, int stack_size);

/// cast.c ///
void cast_right_type_to_byte(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_short(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_int(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_long(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_ubyte(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_ushort(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_uint(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_ulong(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_float(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_double(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_char(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_bool(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_pointer(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_String(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Byte(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_UByte(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Short(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_UShort(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Integer(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_UInteger(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Long(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_ULong(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Float(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Double(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Pointer(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Char(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Bool(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_Array(sNodeType** right_type, sCompileInfo* info);
void cast_right_type_to_left_type(sNodeType* left_type, sNodeType** right_type, sCompileInfo* info);

/// vm.c ///
void show_stack(CLVALUE* stack, CLVALUE* stack_ptr);

extern BOOL gSigInt;
extern BOOL gRunningInitializer;
extern int gBufferToPointerCastCount;

#define OP_POP 1
#define OP_POP_N 2
#define OP_REVERSE 3
#define OP_DUPE 4
#define OP_COND_JUMP 5
#define OP_COND_NOT_JUMP 6
#define OP_GOTO 7
#define OP_RETURN 8
#define OP_THROW 9
#define OP_TRY 10
#define OP_TRY_END 11
#define OP_CATCH_POP 12
#define OP_CATCH_STORE 13
#define OP_CATCH_END 14
#define OP_HEAD_OF_EXPRESSION 15
#define OP_MARK_SOURCE_CODE_POSITION 16
#define OP_MARK_SOURCE_CODE_POSITION2 17
#define OP_SIGINT 18
#define OP_LABEL 19
#define OP_JS_IF 20
#define OP_JS_NOT_IF 21
#define OP_JS_ELSE 22
#define OP_JS_BLOCK_CLOSE 23

// for native code machine, it don't need to Virtual Machine
#define OP_STORE_ANDAND_OROR_VALUE_LEFT 24
#define OP_STORE_ANDAND_OROR_VALUE_RIGHT 25
#define OP_GET_ANDAND_OROR_RESULT_LEFT 26
#define OP_GET_ANDAND_OROR_RESULT_RIGHT 27
#define OP_INC_ANDAND_OROR_ARRAY 28
#define OP_DEC_ANDAND_OROR_ARRAY 29

#define OP_NOP 30

#define OP_STORE_VALUE_TO_GLOBAL 31
#define OP_POP_VALUE_FROM_GLOBAL 32

#define OP_STORE 33
#define OP_LOAD 34

#define OP_STORE_TO_BUFFER 35

#define OP_LDCBYTE 36
#define OP_LDCUBYTE 37
#define OP_LDCSHORT 38
#define OP_LDCUSHORT 39
#define OP_LDCINT 40
#define OP_LDCUINT 41
#define OP_LDCLONG 42
#define OP_LDCULONG 43
#define OP_LDCNULL 44
#define OP_LDCPOINTER 45
#define OP_LDCFLOAT 46
#define OP_LDCDOUBLE 47
#define OP_LDCBOOL 48

#define OP_BADD 50
#define OP_BSUB 51
#define OP_BMULT 52
#define OP_BDIV 53
#define OP_BMOD 54
#define OP_BLSHIFT 55
#define OP_BRSHIFT 56
#define OP_BAND 57
#define OP_BXOR 58
#define OP_BOR 59

#define OP_UBADD 80
#define OP_UBSUB 81
#define OP_UBMULT 82
#define OP_UBDIV 83
#define OP_UBMOD 84
#define OP_UBLSHIFT 85
#define OP_UBRSHIFT 86
#define OP_UBAND 87
#define OP_UBXOR 88
#define OP_UBOR 89

#define OP_SADD 100
#define OP_SSUB 101
#define OP_SMULT 102
#define OP_SDIV 103
#define OP_SMOD 104
#define OP_SLSHIFT 105
#define OP_SRSHIFT 106
#define OP_SAND 107
#define OP_SXOR 108
#define OP_SOR 109

#define OP_JS_LOOP 120
#define OP_JS_BREAK 121
#define OP_JS_ELSE_IF 122

#define OP_USADD 150
#define OP_USSUB 151
#define OP_USMULT 152
#define OP_USDIV 153
#define OP_USMOD 154
#define OP_USLSHIFT 155
#define OP_USRSHIFT 156
#define OP_USAND 157
#define OP_USXOR 158
#define OP_USOR 159

#define OP_IADD 200
#define OP_ISUB 201
#define OP_IMULT 202
#define OP_IDIV 203
#define OP_IMOD 204
#define OP_ILSHIFT 205
#define OP_IRSHIFT 206
#define OP_IAND 207
#define OP_IXOR 208
#define OP_IOR 209

#define OP_UISUB 250
#define OP_UIADD 251
#define OP_UIMULT 252
#define OP_UIDIV 253
#define OP_UIMOD 254
#define OP_UILSHIFT 255
#define OP_UIRSHIFT 256
#define OP_UIAND 257
#define OP_UIXOR 258
#define OP_UIOR 259

#define OP_LADD 300
#define OP_LSUB 301
#define OP_LMULT 302
#define OP_LDIV 303
#define OP_LMOD 304
#define OP_LLSHIFT 305
#define OP_LRSHIFT 306
#define OP_LAND 307
#define OP_LXOR 308
#define OP_LOR 309

#define OP_ULADD 400
#define OP_ULSUB 401
#define OP_ULMULT 402
#define OP_ULDIV 403
#define OP_ULMOD 404
#define OP_ULLSHIFT 405
#define OP_ULRSHIFT 406
#define OP_ULAND 407
#define OP_ULXOR 408
#define OP_ULOR 409

#define OP_BCOMPLEMENT 420
#define OP_UBCOMPLEMENT 421
#define OP_SCOMPLEMENT 422
#define OP_USCOMPLEMENT 423
#define OP_ICOMPLEMENT 424
#define OP_UICOMPLEMENT 425
#define OP_LCOMPLEMENT 426
#define OP_ULCOMPLEMENT 427

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
#define OP_PPSUB 602

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

#define OP_REGEQ 1220
#define OP_REGNOTEQ 1221

#define OP_OBJ_IDENTIFY 1300
#define OP_OBJ_IDENTIFY_NOT 1301
#define OP_CLASSNAME 1302
#define OP_IS 1303
#define OP_IMPLEMENTS 1304
#define OP_OBJ_ALLOCATED_SIZE 1305
#define OP_OBJ_HEAD_OF_MEMORY 1306

#define OP_LOAD_ADDRESS 1307
#define OP_SPLIT_TUPLE 1308

#define OP_ANDAND 2000
#define OP_OROR 2001
#define OP_LOGICAL_DENIAL 2002

#define OP_INVOKE_METHOD 3000
#define OP_INVOKE_VIRTUAL_METHOD 3001
#define OP_INVOKE_DYNAMIC_METHOD 3002
#define OP_INVOKE_BLOCK 3003

#define OP_NEW 4000
#define OP_LOAD_FIELD 4001
#define OP_LOAD_FIELD_ADDRESS 4002
#define OP_STORE_FIELD 4003
#define OP_STORE_FIELD_OF_BUFFER 4004
#define OP_LOAD_CLASS_FIELD 4005
#define OP_LOAD_CLASS_FIELD_ADDRESS 4006
#define OP_STORE_CLASS_FIELD 4007
#define OP_STORE_CLASS_FIELD_OF_BUFFER 4008
#define OP_LOAD_ELEMENT 4009
#define OP_STORE_ELEMENT 4010
#define OP_STORE_ELEMENT_OF_BUFFER 4011

#define OP_STORE_VALUE_TO_INT_ADDRESS 5000
#define OP_STORE_VALUE_TO_UINT_ADDRESS 5001
#define OP_STORE_VALUE_TO_BYTE_ADDRESS 5002
#define OP_STORE_VALUE_TO_UBYTE_ADDRESS 5003
#define OP_STORE_VALUE_TO_SHORT_ADDRESS 5004
#define OP_STORE_VALUE_TO_USHORT_ADDRESS 5005
#define OP_STORE_VALUE_TO_LONG_ADDRESS 5006
#define OP_STORE_VALUE_TO_ULONG_ADDRESS 5007
#define OP_STORE_VALUE_TO_FLOAT_ADDRESS 5008
#define OP_STORE_VALUE_TO_DOUBLE_ADDRESS 5009
#define OP_STORE_VALUE_TO_POINTER_ADDRESS 5010
#define OP_STORE_VALUE_TO_CHAR_ADDRESS 5011
#define OP_STORE_VALUE_TO_BOOL_ADDRESS 5012
#define OP_STORE_VALUE_TO_OBJECT_ADDRESS 5013

#define OP_LOAD_VALUE_FROM_INT_ADDRESS 6000
#define OP_LOAD_VALUE_FROM_UINT_ADDRESS 6001
#define OP_LOAD_VALUE_FROM_BYTE_ADDRESS 6002
#define OP_LOAD_VALUE_FROM_UBYTE_ADDRESS 6003
#define OP_LOAD_VALUE_FROM_SHORT_ADDRESS 6004
#define OP_LOAD_VALUE_FROM_USHORT_ADDRESS 6005
#define OP_LOAD_VALUE_FROM_LONG_ADDRESS 6006
#define OP_LOAD_VALUE_FROM_ULONG_ADDRESS 6007
#define OP_LOAD_VALUE_FROM_FLOAT_ADDRESS 6008
#define OP_LOAD_VALUE_FROM_DOUBLE_ADDRESS 6009
#define OP_LOAD_VALUE_FROM_POINTER_ADDRESS 6010
#define OP_LOAD_VALUE_FROM_CHAR_ADDRESS 6011
#define OP_LOAD_VALUE_FROM_BOOL_ADDRESS 6012
#define OP_LOAD_VALUE_FROM_OBJECT_ADDRESS 6013

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

#define OP_CBYTE_TO_BYTE_CAST 7011
#define OP_CUBYTE_TO_BYTE_CAST 7012
#define OP_CSHORT_TO_BYTE_CAST 7013
#define OP_CUSHORT_TO_BYTE_CAST 7014
#define OP_INTEGER_TO_BYTE_CAST 7015
#define OP_UINTEGER_TO_BYTE_CAST 7016
#define OP_CLONG_TO_BYTE_CAST 7017
#define OP_CULONG_TO_BYTE_CAST 7018
#define OP_CFLOAT_TO_BYTE_CAST 7019
#define OP_CDOUBLE_TO_BYTE_CAST 7020
#define OP_CPOINTER_TO_BYTE_CAST 7021
#define OP_CCHAR_TO_BYTE_CAST 7022
#define OP_CBOOL_TO_BYTE_CAST 7023

#define OP_BYTE_TO_SHORT_CAST 7030
#define OP_UBYTE_TO_SHORT_CAST 7031
#define OP_INT_TO_SHORT_CAST 7032
#define OP_UINT_TO_SHORT_CAST 7033
#define OP_LONG_TO_SHORT_CAST 7034
#define OP_ULONG_TO_SHORT_CAST 7035
#define OP_USHORT_TO_SHORT_CAST 7036
#define OP_FLOAT_TO_SHORT_CAST 7037
#define OP_DOUBLE_TO_SHORT_CAST 7038
#define OP_POINTER_TO_SHORT_CAST 7039
#define OP_CHAR_TO_SHORT_CAST 7040

#define OP_CBYTE_TO_SHORT_CAST 7041
#define OP_CUBYTE_TO_SHORT_CAST 7042
#define OP_CSHORT_TO_SHORT_CAST 7043
#define OP_CUSHORT_TO_SHORT_CAST 7044
#define OP_INTEGER_TO_SHORT_CAST 7045
#define OP_UINTEGER_TO_SHORT_CAST 7046
#define OP_CLONG_TO_SHORT_CAST 7047
#define OP_CULONG_TO_SHORT_CAST 7048
#define OP_CFLOAT_TO_SHORT_CAST 7049
#define OP_CDOUBLE_TO_SHORT_CAST 7050
#define OP_CPOINTER_TO_SHORT_CAST 7051
#define OP_CCHAR_TO_SHORT_CAST 7052
#define OP_CBOOL_TO_SHORT_CAST 7053

#define OP_BYTE_TO_INT_CAST 7060
#define OP_UBYTE_TO_INT_CAST 7061
#define OP_SHORT_TO_INT_CAST 7062
#define OP_USHORT_TO_INT_CAST 7063
#define OP_LONG_TO_INT_CAST 7064
#define OP_ULONG_TO_INT_CAST 7065
#define OP_UINT_TO_INT_CAST 7066
#define OP_FLOAT_TO_INT_CAST 7067
#define OP_DOUBLE_TO_INT_CAST 7068
#define OP_POINTER_TO_INT_CAST 7069
#define OP_CHAR_TO_INT_CAST 7070

#define OP_CBYTE_TO_INT_CAST 7071
#define OP_CUBYTE_TO_INT_CAST 7072
#define OP_CSHORT_TO_INT_CAST 7073
#define OP_CUSHORT_TO_INT_CAST 7074
#define OP_INTEGER_TO_INT_CAST 7075
#define OP_UINTEGER_TO_INT_CAST 7076
#define OP_CLONG_TO_INT_CAST 7077
#define OP_CULONG_TO_INT_CAST 7078
#define OP_CFLOAT_TO_INT_CAST 7079
#define OP_CDOUBLE_TO_INT_CAST 7080
#define OP_CPOINTER_TO_INT_CAST 7081
#define OP_CCHAR_TO_INT_CAST 7082
#define OP_CBOOL_TO_INT_CAST 7083

#define OP_BYTE_TO_LONG_CAST 7090
#define OP_UBYTE_TO_LONG_CAST 7091
#define OP_SHORT_TO_LONG_CAST 7092
#define OP_USHORT_TO_LONG_CAST 7093
#define OP_INT_TO_LONG_CAST 7094
#define OP_UINT_TO_LONG_CAST 7095
#define OP_ULONG_TO_LONG_CAST 7096
#define OP_FLOAT_TO_LONG_CAST 7097
#define OP_DOUBLE_TO_LONG_CAST 7098
#define OP_POINTER_TO_LONG_CAST 7099
#define OP_CHAR_TO_LONG_CAST 7100

#define OP_CBYTE_TO_LONG_CAST 7101
#define OP_CUBYTE_TO_LONG_CAST 7102
#define OP_CSHORT_TO_LONG_CAST 7103
#define OP_CUSHORT_TO_LONG_CAST 7104
#define OP_INTEGER_TO_LONG_CAST 7105
#define OP_UINTEGER_TO_LONG_CAST 7106
#define OP_CLONG_TO_LONG_CAST 7107
#define OP_CULONG_TO_LONG_CAST 7108
#define OP_CFLOAT_TO_LONG_CAST 7109
#define OP_CDOUBLE_TO_LONG_CAST 7110
#define OP_CPOINTER_TO_LONG_CAST 7111
#define OP_CCHAR_TO_LONG_CAST 7112
#define OP_CBOOL_TO_LONG_CAST 7113

#define OP_BYTE_TO_UBYTE_CAST 7120
#define OP_SHORT_TO_UBYTE_CAST 7121
#define OP_USHORT_TO_UBYTE_CAST 7122
#define OP_INT_TO_UBYTE_CAST 7123
#define OP_UINT_TO_UBYTE_CAST 7124
#define OP_LONG_TO_UBYTE_CAST 7125
#define OP_ULONG_TO_UBYTE_CAST 7126
#define OP_FLOAT_TO_UBYTE_CAST 7127
#define OP_DOUBLE_TO_UBYTE_CAST 7128
#define OP_POINTER_TO_UBYTE_CAST 7129
#define OP_CHAR_TO_UBYTE_CAST 7130

#define OP_CBYTE_TO_UBYTE_CAST 7131
#define OP_CUBYTE_TO_UBYTE_CAST 7132
#define OP_CSHORT_TO_UBYTE_CAST 7133
#define OP_CUSHORT_TO_UBYTE_CAST 7134
#define OP_INTEGER_TO_UBYTE_CAST 7135
#define OP_UINTEGER_TO_UBYTE_CAST 7136
#define OP_CLONG_TO_UBYTE_CAST 7137
#define OP_CULONG_TO_UBYTE_CAST 7138
#define OP_CFLOAT_TO_UBYTE_CAST 7139
#define OP_CDOUBLE_TO_UBYTE_CAST 7140
#define OP_CPOINTER_TO_UBYTE_CAST 7141
#define OP_CCHAR_TO_UBYTE_CAST 7142
#define OP_CBOOL_TO_UBYTE_CAST 7143

#define OP_BYTE_TO_USHORT_CAST 7150
#define OP_UBYTE_TO_USHORT_CAST 7151
#define OP_SHORT_TO_USHORT_CAST 7152
#define OP_INT_TO_USHORT_CAST 7153
#define OP_UINT_TO_USHORT_CAST 7154
#define OP_LONG_TO_USHORT_CAST 7155
#define OP_ULONG_TO_USHORT_CAST 7156
#define OP_FLOAT_TO_USHORT_CAST 7157
#define OP_DOUBLE_TO_USHORT_CAST 7158
#define OP_POINTER_TO_USHORT_CAST 7159
#define OP_CHAR_TO_USHORT_CAST 7160

#define OP_CBYTE_TO_USHORT_CAST 7161
#define OP_CUBYTE_TO_USHORT_CAST 7162
#define OP_CSHORT_TO_USHORT_CAST 7163
#define OP_CUSHORT_TO_USHORT_CAST 7164
#define OP_INTEGER_TO_USHORT_CAST 7165
#define OP_UINTEGER_TO_USHORT_CAST 7166
#define OP_CLONG_TO_USHORT_CAST 7167
#define OP_CULONG_TO_USHORT_CAST 7168
#define OP_CFLOAT_TO_USHORT_CAST 7169
#define OP_CDOUBLE_TO_USHORT_CAST 7170
#define OP_CPOINTER_TO_USHORT_CAST 7171
#define OP_CCHAR_TO_USHORT_CAST 7172
#define OP_CBOOL_TO_USHORT_CAST 7173

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

#define OP_CBYTE_TO_UINT_CAST 7211
#define OP_CUBYTE_TO_UINT_CAST 7212
#define OP_CSHORT_TO_UINT_CAST 7213
#define OP_CUSHORT_TO_UINT_CAST 7214
#define OP_INTEGER_TO_UINT_CAST 7215
#define OP_UINTEGER_TO_UINT_CAST 7216
#define OP_CLONG_TO_UINT_CAST 7217
#define OP_CULONG_TO_UINT_CAST 7218
#define OP_CFLOAT_TO_UINT_CAST 7219
#define OP_CDOUBLE_TO_UINT_CAST 7220
#define OP_CPOINTER_TO_UINT_CAST 7221
#define OP_CCHAR_TO_UINT_CAST 7222
#define OP_CBOOL_TO_UINT_CAST 7223

#define OP_BYTE_TO_ULONG_CAST 7230
#define OP_UBYTE_TO_ULONG_CAST 7231
#define OP_SHORT_TO_ULONG_CAST 7232
#define OP_USHORT_TO_ULONG_CAST 7233
#define OP_INT_TO_ULONG_CAST 7234
#define OP_UINT_TO_ULONG_CAST 7235
#define OP_LONG_TO_ULONG_CAST 7236
#define OP_FLOAT_TO_ULONG_CAST 7237
#define OP_DOUBLE_TO_ULONG_CAST 7238
#define OP_POINTER_TO_ULONG_CAST 7239
#define OP_CHAR_TO_ULONG_CAST 7240

#define OP_CBYTE_TO_ULONG_CAST 7241
#define OP_CUBYTE_TO_ULONG_CAST 7242
#define OP_CSHORT_TO_ULONG_CAST 7243
#define OP_CUSHORT_TO_ULONG_CAST 7244
#define OP_INTEGER_TO_ULONG_CAST 7245
#define OP_UINTEGER_TO_ULONG_CAST 7246
#define OP_CLONG_TO_ULONG_CAST 7247
#define OP_CULONG_TO_ULONG_CAST 7248
#define OP_CFLOAT_TO_ULONG_CAST 7249
#define OP_CDOUBLE_TO_ULONG_CAST 7250
#define OP_CPOINTER_TO_ULONG_CAST 7251
#define OP_CCHAR_TO_ULONG_CAST 7252
#define OP_CBOOL_TO_ULONG_CAST 7253

#define OP_BYTE_TO_FLOAT_CAST 7260
#define OP_UBYTE_TO_FLOAT_CAST 7261
#define OP_SHORT_TO_FLOAT_CAST 7262
#define OP_USHORT_TO_FLOAT_CAST 7263
#define OP_INT_TO_FLOAT_CAST 7264
#define OP_UINT_TO_FLOAT_CAST 7265
#define OP_LONG_TO_FLOAT_CAST 7266
#define OP_ULONG_TO_FLOAT_CAST 7267
#define OP_DOUBLE_TO_FLOAT_CAST 7268
#define OP_CHAR_TO_FLOAT_CAST 7269

#define OP_CBYTE_TO_FLOAT_CAST 7270
#define OP_CUBYTE_TO_FLOAT_CAST 7271
#define OP_CSHORT_TO_FLOAT_CAST 7272
#define OP_CUSHORT_TO_FLOAT_CAST 7273
#define OP_INTEGER_TO_FLOAT_CAST 7274
#define OP_UINTEGER_TO_FLOAT_CAST 7275
#define OP_CLONG_TO_FLOAT_CAST 7276
#define OP_CULONG_TO_FLOAT_CAST 7277
#define OP_CFLOAT_TO_FLOAT_CAST 7278
#define OP_CDOUBLE_TO_FLOAT_CAST 7279
#define OP_CCHAR_TO_FLOAT_CAST 7281
#define OP_CBOOL_TO_FLOAT_CAST 7282

#define OP_BYTE_TO_DOUBLE_CAST 7290
#define OP_UBYTE_TO_DOUBLE_CAST 7291
#define OP_SHORT_TO_DOUBLE_CAST 7292
#define OP_USHORT_TO_DOUBLE_CAST 7293
#define OP_INT_TO_DOUBLE_CAST 7294
#define OP_UINT_TO_DOUBLE_CAST 7295
#define OP_LONG_TO_DOUBLE_CAST 7296
#define OP_ULONG_TO_DOUBLE_CAST 7297
#define OP_FLOAT_TO_DOUBLE_CAST 7298
#define OP_CHAR_TO_DOUBLE_CAST 7299

#define OP_CBYTE_TO_DOUBLE_CAST 7300
#define OP_CUBYTE_TO_DOUBLE_CAST 7301
#define OP_CSHORT_TO_DOUBLE_CAST 7302
#define OP_CUSHORT_TO_DOUBLE_CAST 7303
#define OP_INTEGER_TO_DOUBLE_CAST 7304
#define OP_UINTEGER_TO_DOUBLE_CAST 7305
#define OP_CLONG_TO_DOUBLE_CAST 7306
#define OP_CULONG_TO_DOUBLE_CAST 7307
#define OP_CFLOAT_TO_DOUBLE_CAST 7308
#define OP_CDOUBLE_TO_DOUBLE_CAST 7309
#define OP_CCHAR_TO_DOUBLE_CAST 7311
#define OP_CBOOL_TO_DOUBLE_CAST 7312

#define OP_BYTE_TO_POINTER_CAST 7320
#define OP_UBYTE_TO_POINTER_CAST 7321
#define OP_SHORT_TO_POINTER_CAST 7322
#define OP_USHORT_TO_POINTER_CAST 7323
#define OP_INT_TO_POINTER_CAST 7324
#define OP_UINT_TO_POINTER_CAST 7325
#define OP_LONG_TO_POINTER_CAST 7326
#define OP_ULONG_TO_POINTER_CAST 7327
#define OP_CHAR_TO_POINTER_CAST 7328
#define OP_BUFFER_TO_POINTER_CAST 7329

#define OP_BYTE_TO_CHAR_CAST 7330
#define OP_UBYTE_TO_CHAR_CAST 7331
#define OP_SHORT_TO_CHAR_CAST 7332
#define OP_USHORT_TO_CHAR_CAST 7333
#define OP_INT_TO_CHAR_CAST 7334
#define OP_UINT_TO_CHAR_CAST 7335
#define OP_LONG_TO_CHAR_CAST 7336
#define OP_ULONG_TO_CHAR_CAST 7337
#define OP_FLOAT_TO_CHAR_CAST 7338
#define OP_DOUBLE_TO_CHAR_CAST 7339
#define OP_POINTER_TO_CHAR_CAST 7340

#define OP_CBYTE_TO_CHAR_CAST 7341
#define OP_CUBYTE_TO_CHAR_CAST 7342
#define OP_CSHORT_TO_CHAR_CAST 7343
#define OP_CUSHORT_TO_CHAR_CAST 7344
#define OP_INTEGER_TO_CHAR_CAST 7345
#define OP_UINTEGER_TO_CHAR_CAST 7346
#define OP_CLONG_TO_CHAR_CAST 7347
#define OP_CULONG_TO_CHAR_CAST 7348
#define OP_CFLOAT_TO_CHAR_CAST 7349
#define OP_CDOUBLE_TO_CHAR_CAST 7350
#define OP_CPOINTER_TO_CHAR_CAST 7351
#define OP_CCHAR_TO_CHAR_CAST 7352
#define OP_CBOOL_TO_CHAR_CAST 7353

#define OP_BYTE_TO_STRING_CAST 7360
#define OP_SHORT_TO_STRING_CAST 7361
#define OP_INT_TO_STRING_CAST 7362
#define OP_LONG_TO_STRING_CAST 7363
#define OP_UBYTE_TO_STRING_CAST 7364
#define OP_USHORT_TO_STRING_CAST 7365
#define OP_UINT_TO_STRING_CAST 7366
#define OP_ULONG_TO_STRING_CAST 7367
#define OP_FLOAT_TO_STRING_CAST 7368
#define OP_DOUBLE_TO_STRING_CAST 7369
#define OP_BOOL_TO_STRING_CAST 7370
#define OP_REGEX_TO_STRING_CAST 7371
#define OP_POINTER_TO_STRING_CAST 7372
#define OP_CHAR_TO_STRING_CAST 7373

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

#define OP_ARRAY_TO_CARRAY_CAST 7700

#define OP_GET_ARRAY_LENGTH 8000

#define OP_GET_REGEX_GLOBAL 8100
#define OP_GET_REGEX_IGNORE_CASE 8101
#define OP_GET_REGEX_MULTILINE 8102
#define OP_GET_REGEX_EXTENDED 8103
#define OP_GET_REGEX_DOTALL 8104
#define OP_GET_REGEX_ANCHORED 8105
#define OP_GET_REGEX_DOLLAR_ENDONLY 8106
#define OP_GET_REGEX_UNGREEDY 8107

#define OP_CHAR_UPPERCASE 8150
#define OP_CHAR_LOWERCASE 8151

#define OP_CREATE_STRING 9000
#define OP_CREATE_BUFFER 9001
#define OP_CREATE_PATH 9002
#define OP_CREATE_ARRAY 9003
#define OP_CREATE_CARRAY 9004
#define OP_CREATE_SORTABLE_CARRAY 9005
#define OP_CREATE_EQUALABLE_CARRAY 9006
#define OP_CREATE_LIST 9007
#define OP_CREATE_SORTABLE_LIST 9008
#define OP_CREATE_EQUALABLE_LIST 9009
#define OP_CREATE_TUPLE 9010
#define OP_CREATE_HASH 9011
#define OP_CREATE_BLOCK_OBJECT 9012
#define OP_CREATE_REGEX 9013
#define OP_JS_ARRAY 9014
#define OP_JS_FUNCTION 9015
#define OP_INVOKE_JS_FUNCTION 9016
#define OP_REQUIRE 9017

BOOL vm(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sVMInfo* info);
sCLClass* get_class_with_load_and_initialize(char* class_name, BOOL js);
void class_final_on_runtime();
BOOL call_finalize_method_on_free_object(sCLClass* klass, CLObject self);
BOOL call_alloc_size_method(sCLClass* klass, unsigned long long* result);
void callOnException(CLObject message, BOOL in_try, sVMInfo* info);
BOOL invoke_method(sCLClass* klass, sCLMethod* method, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info);
BOOL invoke_block(CLObject block_object, CLVALUE* stack, int var_num, int num_params, CLVALUE** stack_ptr, sVMInfo* info);
BOOL class_init_on_runtime();
BOOL class_init_on_runtime_for_js();
void boxing_primitive_value_to_object(CLVALUE object, CLVALUE* result, sCLClass* klass, sVMInfo* info);
void Self_convertion_of_method_name_and_params(char* method_name_and_params, char* method_name_and_params2, char* class_name);
void set_free_fun_to_classes();
BOOL call_all_class_initializer();
void show_inst(unsigned inst);

/// class_compiler.c ///
#define PARSE_PHASE_ALLOC_CLASSES 1
#define PARSE_PHASE_ADD_SUPER_CLASSES 2
#define PARSE_PHASE_CALCULATE_SUPER_CLASSES 3
#define PARSE_PHASE_ADD_GENERICS_TYPES 4
//#define PARSE_PHASE_RUN_SCRIPT 5
#define PARSE_PHASE_ADD_METHODS_AND_FIELDS 5
#define PARSE_PHASE_COMPILE_PARAM_INITIALIZER 6
#define PARSE_PHASE_DO_COMPILE_CODE 7
#define PARSE_PHASE_MAX 8

BOOL compile_class_source(char* fname, char* source);
BOOL parse_method_name_and_params(char* method_name, int method_name_max, sParserParam* params, int* num_params, sNodeType** result_type, BOOL* native_, BOOL* static_, BOOL* dynamic_, BOOL* pure_native_, sParserInfo* info, char* clibrary_path, size_t clibrary_path_size);

/// cycle.c ///
void set_dependency_compile();
BOOL dependency_check(char* fname);
BOOL dependency_compile(char* cwd, char* class_name, char* class_file_name, size_t class_file_name_size);
void dependency_final();

/// klass_compile_time.c ///
void add_native_code_to_method(sCLMethod* method, sBuf* native_code);
BOOL add_method_to_class(sCLClass* klass, char* method_name, sParserParam* params, int num_params, sNodeType* result_type, BOOL native_, BOOL static_, BOOL dynamic_, BOOL pure_native_, sGenericsParamInfo* ginfo, sCLMethod** appended_method, char* clibrary_path, sParserInfo* info);
int add_block_object_to_class(sCLClass* klass, sByteCode codes, sConst constant, int var_num, int num_params, BOOL lambda);
BOOL add_typedef_to_class(sCLClass* klass, char* class_name1, char* class_name2);
BOOL add_class_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, BOOL readonly, sNodeType* result_type, int initialize_value, char* header_path);
void add_code_to_method(sCLMethod* method, sByteCode* code, int var_num);
BOOL write_all_modified_classes();
int search_for_method(sCLClass* klass, char* method_name, sNodeType** param_types, int num_params, BOOL search_for_class_method, int start_point, sNodeType* left_generics_type, sNodeType* right_generics_type, sNodeType* right_method_generics, sNodeType** result_type, BOOL lazy_lambda_compile, sNodeType** method_generics_types, struct sParserInfoStruct* info);
BOOL search_for_methods_from_method_name(int method_indexes[], int size_method_indexes, int* num_methods, sCLClass* klass, char* method_name, int start_point, BOOL class_method);
int search_for_field(sCLClass* klass, char* field_name);
int search_for_class_field(sCLClass* klass, char* field_name);
void add_dependences_with_node_type(sCLClass* klass, sNodeType* node_type);
BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info, int chracter_type);
BOOL check_implemented_methods_for_interface(sCLClass* left_class, sCLClass* right_class, BOOL output_message);
BOOL class_method_name_existance(sCLClass* klass, char* method_name);
BOOL none_class_method_name_existance(sCLClass* klass, char* method_name);
BOOL class_field_name_existance(sCLClass* klass, char* field_name);
BOOL field_name_existance(sCLClass* klass, char* field_name);
void create_method_name_and_params(char* result, int size_result, sCLClass* klass, char* method_name, sNodeType* param_types[PARAMS_MAX], int num_params);
void create_method_name_and_params_for_js(char* result, int size_result, sCLClass* klass, char* method_name, sNodeType* param_types[PARAMS_MAX], int num_params);
BOOL determine_method_generics_types(sNodeType* left_param, sNodeType* right_param, sNodeType* method_generics_types);
BOOL is_method_param_name(char* name);
BOOL add_field_to_class(sCLClass* klass, char* name, BOOL private_, BOOL protected_, BOOL delegated, BOOL readonly, sNodeType* result_type);
BOOL add_field_to_class_with_class_name(sCLClass* klass, char* name, BOOL private_, BOOL protected_, BOOL delegated, char* field_type_name);
BOOL add_class_field_to_class_with_class_name(sCLClass* klass, char* name, BOOL private_, BOOL protected_, char* field_type_name, int initialize_value);

/// native_method.c ///
void native_method_init();
void native_method_final();

fNativeMethod get_native_method(char* path, char** fun_name);
void put_fun_to_hash_for_native_method(char* path, char* fun_name, fNativeMethod fun);

/// exception.c ///
void entry_exception_object_with_class_name(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, char* class_name, char* msg, ...);
void entry_exception_object(CLObject exception, sVMInfo* info);
void show_exception_message(char* message);
void entry_exception_object_with_class_name2(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info, char* class_name, char* msg);

/// method_compiler.c ///
BOOL compile_method(sCLMethod* method, sParserParam* params, int num_params, sParserInfo* info, sCompileInfo* cinfo);

/// type.c ///
BOOL is_void_type(sCLType* cl_type, sCLClass* klass);
sCLClass* get_class_from_cl_type(sCLType* cl_type, sCLClass* klass);
BOOL is_this_class_with_class_name(sCLClass* klass, char* class_name);
ALLOC char* cl_type_to_string(sCLType* cl_type, sCLClass* klass);;

/// heap.c ///
struct sCLHeapMemStruct {
    sCLClass* mClass;       // NULL --> no class only memory
    char* mType;
    int mSize;
    int mArrayNum;
    void* mMem;
};

typedef struct sCLHeapMemStruct sCLHeapMem;

#define CLHEAPMEM(obj) (get_object_pointer((obj)))

void heap_init(int heap_size, int size_handles);
void heap_final();

CLObject alloc_heap_mem(unsigned int size, sCLClass* klass, int array_num, sVMInfo* info);
sCLHeapMem* get_object_pointer(CLObject obj);
void show_heap(sVMInfo* info);
void mark_object(CLObject obj, unsigned char* mark_flg);
BOOL is_valid_object(CLObject obj);
void gc(sVMInfo* info);
void compaction();
void free_global_stack_objects(sVMInfo* info, CLObject result_object, int num_global_stack_ptr, CLVALUE* lvar, int num_params);

ALLOC unsigned char* get_mark_flg(CLObject obj);

void mark_and_store_class_field(sCLClass* klass, int field_index, CLVALUE cl_value);
void mark_singal_handler_object(CLObject obj);
void inc_refference_count(CLObject obj, CLObject prev_obj, BOOL value_is_object);
void dec_refference_count(CLObject obj, BOOL value_is_object);

/// module.c ///
struct sCLModuleStruct {
    BOOL mModified;
    char mName[CL_MODULE_NAME_MAX+1];
    sBuf mBody;
    char mSName[PATH_MAX];
    int mSLine;
};

typedef struct sCLModuleStruct sCLModule;

void module_init();
void module_final();
sCLModule* create_module(char* module_name, char* sname, int sline);
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

#define OBJECT_TYPE_NAME_MAX 128

struct sCLObjectStruct {
    sCLClass* mClass;
    char* mType;
    int mSize;
    union {
        int mArrayNum;
        int mNumFields;
    };
    union {
        int mHeadOfMemory;
        CLVALUE mFields[DUMMY_ARRAY_SIZE];
    };
};

typedef struct sCLObjectStruct sCLObject;

#define CLOBJECT(obj) ((sCLObject*)(get_object_pointer((obj))))

CLObject create_object(sCLClass* klass, char* type, sVMInfo* info);
BOOL free_object(CLObject self);
void object_mark_fun(CLObject self, unsigned char* mark_flg);
BOOL object_implements_interface(CLObject object, sCLClass* interface);

/// array.c ///
CLObject create_array_object(sCLClass* klass, int array_num, sVMInfo* info);
void array_mark_fun(CLObject self, unsigned char* mark_flg);
void free_array(CLObject self);

/// hash.c ///
CLObject create_hash_object(char* type_name, sVMInfo* info);
BOOL initialize_hash_object(CLObject hash_object, int num_elements, CLObject* keys, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_keys, sCLClass* class_items);

/// block.c ///
struct sBlockObjectStruct
{
    sCLClass* mClass;       // NULL --> no class only memory
    char* mType;
    int mSize;
    int mArrayNum;
    sByteCode mCodes;
    sConst mConstant;
    CLVALUE* mParentStack;
    int mParentVarNum;
    int mBlockVarNum;
    BOOL mLambda;
    void* mJITDynamicSym;       // this requires runtime
    int mBlockID;
    sCLClass* mClass2;
};

typedef struct sBlockObjectStruct sBlockObject;

#define CLBLOCK(obj) (sBlockObject*)(get_object_pointer((obj)))

CLObject create_block_object(sByteCode* codes, sConst* constant, CLVALUE* parent_stack, int parent_var_num, int block_var_num, BOOL lambda, int block_id, sCLClass* klass, sVMInfo* info);
void block_mark_fun(CLObject self, unsigned char* mark_flg);

/// regex.c ///
struct sRegexObjectStruct
{
    sCLClass* mClass;       // NULL --> no class only memory
    char* mType;
    int mSize;
    int mArrayNum;
    pcre* mRegex;
    char* mRegexString;
    BOOL mGlobal;
    BOOL mIgnoreCase;
    BOOL mMultiline;
    BOOL mExtended;
    BOOL mDotAll;
    BOOL mAnchored;
    BOOL mDollarEndOnly;
    BOOL mUngreedy;
};

typedef struct sRegexObjectStruct sRegexObject;

#define CLREGEX(obj) (sRegexObject*)(get_object_pointer((obj)))

CLObject create_regex_object(char* regex, BOOL global, BOOL ignore_case, BOOL multiline, BOOL extended, BOOL dotall, BOOL anchored, BOOL dollar_endonly, BOOL ungreedy, sVMInfo* info);
void regex_free_fun(CLObject obj);
BOOL regex_equals(CLObject left, CLObject right);

/// string.c ///
CLObject create_string_object(char* str, sVMInfo* info);
CLObject create_buffer_object(char* buffer, size_t size, sVMInfo* info);
CLObject create_path_object(char* path, sVMInfo* info);
CLObject create_string_from_two_strings(CLObject left, CLObject right);
int get_length_from_string_object(CLObject str);
CLVALUE* get_str_array_from_string_object(CLObject str);

/// integer.c ///
CLObject create_integer(int value, sVMInfo* info);
CLObject create_uinteger(unsigned int value, sVMInfo* info);

/// byte.c ///
CLObject create_byte(char value, sVMInfo* info);
CLObject create_ubyte(unsigned char value, sVMInfo* info);

/// short.c ///
CLObject create_short(short value, sVMInfo* info);
CLObject create_ushort(unsigned short value, sVMInfo* info);

/// long.c ///
CLObject create_long(clint64 value, sVMInfo* info);
CLObject create_ulong(unsigned clint64 value, sVMInfo* info);

/// float.c ///
CLObject create_float(float value, sVMInfo* info);
CLObject create_double(double value, sVMInfo* info);

/// pointer.c ///
CLObject create_pointer(char* value, sVMInfo* info);

/// char.c ///
CLObject create_char(wchar_t value, sVMInfo* info);

/// bool.c ///
CLObject create_bool(BOOL value, sVMInfo* info);

/// class_system.c ///
BOOL System_exit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_assert(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_realloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_calloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_free(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strlen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strlen2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strcpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strncpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strdup(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_print(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_println(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_printlnToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_printToError(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_sleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pcre_exec(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_sprintf(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_memcpy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_memset(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_memcmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_mbstowcs(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_wcstombs(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_atof(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_atoi(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strtod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strcmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strcasecmp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strtol(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strtoul(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_srand(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_rand(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_open(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_close(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_initialize_string_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_initialize_file_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_read(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_write(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_time(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_localtime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_mktime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_stat(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_lstat(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_basename(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_dirname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_realpath(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_opendir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_readdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_closedir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_initialize_command_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pipe(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fork(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_dup2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_execvp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_execv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_waitpid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WIFEXITED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WEXITSTATUS(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WIFSIGNALED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WTERMSIG(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WCOREDUMP(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WIFSTOPPED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WSTOPSIG(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_WIFCONTINUED(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getpid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_setpgid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_kill(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_tcsetpgrp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_tcgetattr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_tcsetattr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_tcsendbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_tcdrain(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_tcflush(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_tcflow(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_cfmakeraw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_cfgetispeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_cfgetospeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_cfsetispeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_cfsetospeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_cfsetspeed(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_chmod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_lchmod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fchmod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_chown(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_lchown(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fchown(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_unlink(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_access(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_utime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fnmatch(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_link(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_symlink(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_readlink(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_rename(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_truncate(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_ftruncate(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_chdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fchdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_rmdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_mkdir(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_clock_getres(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_clock_gettime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_clock_settime(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_setenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_unsetenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_dlopen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_dlclose(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_dlsym(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_put_fun_to_hash_for_native_method(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_initialize_system_calls_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_alarm(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_dup(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_dup3(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_execvpe(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fopen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fclose(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fwrite(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fread(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_feof(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fgetc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fgets(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getchar(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_ungetc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getcwd(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getopt(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getopt_long(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getopt_long_only(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getppid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_setsid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getsid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_setpgrp(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_gettid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_popen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pclose(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_initialize_thread_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutex_init(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutex_destroy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutex_lock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutex_unlock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutex_trylock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutexattr_gettype(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutexattr_destroy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutexattr_settype(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_mutexattr_init(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_cond_init(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_cond_signal(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_cond_broadcast(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_cond_wait(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_cond_timedwait(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_pthread_cond_destroy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_initialize_cgi_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_setlocale(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_flock(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_fileno(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getbsize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getegid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getgid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_geteuid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getuid(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isatty(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_umask(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_usleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_nanosleep(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_putenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
//BOOL System_secure_getenv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_setvbuf(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strncat(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_strchr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_initialize_socket_system(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_socket(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_connect(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_accept(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_accept2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_listen(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_bind(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_inet_addr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_connect2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_bind2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_gethostbyaddr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_gethostbyname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getservbyport(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getservbyname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_inet_ntoa(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_gethostname(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_signal(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
void class_system_init();
BOOL System_signal2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL fd_set_allocSize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

BOOL System_FD_ISSET(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_FD_SET(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_FD_CLR(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_FD_ZERO(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

BOOL System_select(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_ioctl(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

BOOL System_initscr(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_endwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_move(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_GC_malloc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_printw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_refresh(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_box(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isendwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_clear(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_erase(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_idcok(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_idlok(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_attron(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_attroff(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_attrset(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

BOOL System_echo(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_noecho(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_cbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_nocbreak(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_raw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_noraw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_nodelay(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getch(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_mvwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_wrefresh(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_wclear(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getEscapeDelay(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_setEscapeDelay(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_touchwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_keypad(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_newwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_delwin(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_wmove(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_wprintw(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getmaxx(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_getmaxy(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isblank(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isascii(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isxdigit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isupper(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isspace(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_ispunct(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isprint(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_islower(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isgraph(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isdigit(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_iscntrl(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isalnum(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_isalpha(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

BOOL System_send(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_sendto(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_sendto2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

BOOL System_recv(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_recvfrom(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL System_recvfrom2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

extern CLObject signal_handler_object[SIGMAX];

/// alignment.c ///
void alignment(unsigned int* size);

/// clover_to_clang ///
ALLOC wchar_t* string_object_to_wchar_array(CLObject string_object);
ALLOC char* string_object_to_char_array(CLObject string_object);
NULLABLE CLVALUE* get_element_from_array(CLObject array, int index);
NULLABLE CLVALUE* get_element_from_Array(CLObject array, int index);
int get_element_number_from_Array(CLObject array);
char get_value_from_Byte(CLObject object);
unsigned char get_value_from_UByte(CLObject object);
short get_value_from_Short(CLObject object);
unsigned short get_value_from_UShort(CLObject object);
int get_value_from_Integer(CLObject object);
unsigned int get_value_from_UInteger(CLObject object);
clint64 get_value_from_Long(CLObject object);
unsigned clint64 get_value_from_ULong(CLObject object);
wchar_t get_value_from_Char(CLObject object);
float get_value_from_Float(CLObject object);
double get_value_from_Double(CLObject object);
BOOL get_value_from_Bool(CLObject object);
char* get_value_from_Pointer(CLObject object);
sCLClass* get_class_from_object(CLObject object);
void* get_pointer_from_buffer_object(CLObject buffer);
size_t get_size_from_buffer_object(CLObject buffer);
ALLOC CLObject* list_to_array(CLObject list, int* num_elements);
void clover_termios_to_c_termios(CLObject terminfo_object, struct termios* terminfo_value);
void c_termios_to_clover_termios(struct termios* terminfo_value, CLObject terminfo_object);
BOOL create_termios_object(CLObject* result, CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

/// list.c ///
CLObject create_list_object(char* type_name, sVMInfo* info);
BOOL initialize_list_object(CLObject list_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items);
CLObject create_sortable_list_object(char* type_name, sVMInfo* info);
BOOL initialize_sortable_list_object(CLObject list_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items);
CLObject create_equalable_list_object(char* type_name, sVMInfo* info);
BOOL initialize_equalable_list_object(CLObject list_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items);

/// tuple.c ///
CLObject create_tuple_object(int num_elements, char* type_name, sVMInfo* info);
BOOL initialize_tuple_object(CLObject tuple_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info);

/// carray.c ///
CLObject create_carray_object(char* type_name, sVMInfo* info);
CLObject create_equalable_carray_object(char* type_name, sVMInfo* info);
CLObject create_sortable_carray_object(char* type_name, sVMInfo* info);
CLObject create_carray_object_with_elements(int num_elements, CLObject* elements, sVMInfo* info);
BOOL initialize_carray_object(CLObject array_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items);
CLObject create_equalable_carray_object_with_elements(int num_elements, CLObject* elements, sVMInfo* info);
BOOL initialize_equalable_carray_object(CLObject array_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items);
CLObject create_sortable_carray_object_with_elements(int num_elements, CLObject* elements, sVMInfo* info);
BOOL initialize_sortable_carray_object(CLObject array_object, int num_elements, CLObject* items, CLVALUE* stack, int var_num, CLVALUE** stack_ptr, sVMInfo* info, sCLClass* class_items);

/// utf.c ///
int utf8_index_to_utf32_index(char* str, int utf8index);
int utf32_index_to_utf8_index(char* str, int utf32index);

/// class_clover.c ///
BOOL Clover_load(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_initialize_lang(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_initialize_reflection(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_appendField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_appendMethod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_appendMethod2(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_declareMethod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_appendClassField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getMethod(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getClassField(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getClassGenericsParamNames(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getClassGenericsParamTypes(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getClassFlags(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getNumFields(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getNumClassFields(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getNumMethods(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_isLoadedClass(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_isDefinedClass(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_appendClass(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getAllClassName(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_createObject(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_createArray(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_isTypedefedClass(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_gc(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_compaction(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Clover_getType(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

/// jit.cpp ///
BOOL jit(sByteCode* code, sConst* constant, CLVALUE* stack, int var_num, sCLClass* klass, sCLMethod* method, CLObject block_object, sVMInfo* info, CLVALUE** stack_ptr);
void jit_init();
void jit_final();
BOOL compile_jit_method(sCLClass* klass, sCLMethod* method);

#ifdef ENABLE_JIT
/// jit_runtime.cpp ///
void jit_init_on_runtime();
void jit_final_on_runtime();
BOOL load_bc_file(sCLClass* klass);
BOOL jit_compile_class(sCLClass* klass);
#endif

/// class_parser.c ///
BOOL CLParser_initialize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

/// main.c ///
extern int gARGC;
extern char** gARGV;
extern char* gVersion;
extern BOOL gRunningCompiler;
extern BOOL gCompilingCore;

extern char gScriptDirPath[PATH_MAX];

/// class_thread.c ///
void thread_init();
void thread_final();
void vm_mutex_on();
void vm_mutex_off();
BOOL Thread_initialize_thread(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL Thread_pthread_join(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
void new_vm_mutex();
pid_t gettid();
BOOL pthread_mutex_t_allocSize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);
BOOL pthread_cond_t_allocSize(CLVALUE** stack_ptr, CLVALUE* lvar, sVMInfo* info);

extern BOOL gVMMutexFlg;

/// js.c ///
BOOL js_compiler(char* sname);
BOOL js_class_compiler(char* class_name);

#endif

