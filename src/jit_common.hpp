extern "C" 
{
#include "common.h"
}

#include "llvm/ADT/APFloat.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

#include "llvm/ADT/iterator_range.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
//#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/RuntimeDyld.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/LambdaResolver.h"
#if LLVM_VERSION_MAJOR == 3
#include "llvm/ExecutionEngine/Orc/ObjectLinkingLayer.h"
#endif
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Mangler.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm-c/BitWriter.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/MemoryBuffer.h"
#if LLVM_VERSION_MAJOR == 3
#include "llvm/Bitcode/ReaderWriter.h"
#endif
//#include "llvm/Bitcode/BitcodeReader.h"
//#include "llvm/Bitcode/BitcodeWriter.h"
#include <fstream>
#include <iostream>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;
using namespace llvm::orc;

extern "C" 
{

#include <dlfcn.h>

inline void create_method_path_for_jit(sCLClass* klass, sCLMethod* method, char* result, int size_result)
{
    snprintf(result, size_result, "%s.%s$$%d", CLASS_NAME(klass), METHOD_NAME_AND_PARAMS(klass, method), method->mMethodIndex);
}

enum eLVALUEKind { kLVKindNone, kLVKindInt1, kLVKindInt8, kLVKindUInt8, kLVKindInt16, kLVKindUInt16, kLVKindInt32, kLVKindUInt32, kLVKindInt64, kLVKindUInt64, kLVKindMemory, kLVKindAddress, kLVKindConstantInt1, kLVKindConstantInt8, kLVKindConstantUInt8, kLVKindConstantInt16, kLVKindConstantUInt16, kLVKindConstantInt32, kLVKindConstantUInt32, kLVKindConstantInt64, kLVKindConstantUInt64, kLVKindConstantFloat, kLVKindConstantDouble, kLVKindFloat, kLVKindDouble, kLVKindPointer8, kLVKindPointer32, kLVKindPointer64, kLVKindPointerDouble, kLVKindObject };

struct LVALUEStruct {
    Value* value;
    int lvar_address_index;
    BOOL lvar_stored;
    enum eLVALUEKind kind;
    int parent_var_num;
    Value* parent_stack;
    struct LVALUEStruct* parent_llvm_stack;
};

void InitializeModuleAndPassManager(char* class_name);

typedef struct LVALUEStruct LVALUE;

typedef BOOL (*fJITMethodType)(CLVALUE* stack_ptr, CLVALUE* lvar, sVMInfo* info, CLVALUE* stack, CLVALUE** stack_ptr_address, int var_num, sConst* constant, sByteCode* code, CLVALUE** global_stack_ptr_address);

/// jit.cpp ///
struct sCLVALUEAndBoolResult {
    CLVALUE result1;
    BOOL result2;
};
struct sPointerAndBoolResult {
    char* result1;
    BOOL result2;
};
void init_jit_objects();
void free_jit_objects();
BOOL jit_compile_all_classes();

extern LLVMContext TheContext;
extern IRBuilder<> Builder;
extern Module* TheModule;
extern std::unique_ptr<legacy::FunctionPassManager> TheFPM;
extern std::map<std::string, BasicBlock*> TheLabels;

#define MAX_COND_JUMP 128

BOOL compile_to_native_code(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2);
BOOL compile_to_native_code2(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name);
BOOL compile_to_native_code3(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name);
BOOL compile_to_native_code4(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name);
BOOL compile_to_native_code5(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name);
BOOL compile_to_native_code6(sByteCode* code, sConst* constant, sCLClass* klass, sCLMethod* method, char* method_path2, int inst, char** pc, LVALUE** llvm_stack_ptr, LVALUE* llvm_stack, std::map<std::string, Value*>& params, BasicBlock** current_block, Function** function, int var_num, char** try_catch_label_name);


/// jit_debug.h ///
void show_stack_for_llvm_stack(LVALUE* llvm_stack, LVALUE* llvm_stack_ptr, int var_num);
void show_number_in_jit(clint64 number);
void call_show_number_in_jit(clint64 number);
void call_show_value_in_jit(LVALUE* llvm_value);
void call_show_value_in_jit2(LVALUE* llvm_value);
void show_str_in_jit(char* str);
void call_show_str_in_jit(Value* value);
void call_show_stack_stat(std::map<std::string, Value *> params);
void call_show_inst_in_jit(int opecode);
void show_stack_for_llvm_stack(LVALUE* llvm_stack, LVALUE* llvm_stack_ptr, int var_num);
void show_stack_stat(CLVALUE** stack_ptr, CLVALUE* stack);
void show_inst_in_jit(int opecode);
void show_llvm_stack(LVALUE* llvm_stack, LVALUE* llvm_stack_ptr, int var_num, std::map<std::string, Value*>& params, BasicBlock* current_block);
void show_llvm_stck_on_compile_time(LVALUE* llvm_stack, LVALUE* llvm_stack_ptr, int var_num);
void show_llvm_value(LVALUE* llvm_value);
void show_str(char* str);

/// jit_sub.cpp ///
LVALUE trunc_value(LVALUE* llvm_value, int size);
LVALUE trunc_value_to_float_or_double(LVALUE* llvm_value, int size);
LVALUE trunc_value_to_pointer(LVALUE* llvm_value);
void trunc_variable(LVALUE* llvm_value, int size);
void cast_llvm_value_from_inst(LVALUE* llvm_value, int inst);
Value* llvm_create_string(char* str);
Value* llvm_create_buffer(char* str, int len);
LVALUE* get_stack_ptr_value_from_index(LVALUE* llvm_stack_ptr, int index);
void dec_stack_ptr(LVALUE** llvm_stack_ptr, int value);
void push_value_to_stack_ptr(LVALUE** llvm_stack_ptr, LVALUE* value);
void insert_value_to_stack_ptr_with_offset(LVALUE** llvm_stack_ptr, LVALUE* value, int offset);
void store_llvm_value_to_lvar_with_offset(LVALUE* llvm_stack, int index, LVALUE* llvm_value, BOOL except_parent_stack);
void get_llvm_value_from_lvar_with_offset(LVALUE* result, LVALUE* llvm_stack, int index);
LVALUE get_vm_stack_ptr_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align);
void inc_vm_stack_ptr(std::map<std::string, Value*> params, BasicBlock* current_block, int value);
void push_value_to_vm_stack_ptr_with_aligned(std::map<std::string, Value*> params, BasicBlock* current_block, LVALUE* llvm_value);
LVALUE get_stack_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align);
void llvm_stack_to_vm_stack(LVALUE* llvm_stack_ptr, std::map<std::string, Value*> params, BasicBlock* current_block, int num);
void parent_llvm_stack_to_parent_vm_stack(Value* parent_stack, LVALUE* parent_llvm_stack, BasicBlock* current_block, int parent_var_num);
void parent_vm_stack_to_parent_llvm_stack(Value* parent_stack, LVALUE* parent_llvm_stack, BasicBlock* current_block, int parent_var_num);
void llvm_stack_to_vm_stack_of_parent(LVALUE* llvm_stack_ptr, Value* parent_stack, std::map<std::string, Value*> params, BasicBlock* current_block, int num);
void if_value_is_zero_ret_zero(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block);
void if_value_is_null_ret_zero(Value* value, int value_bit, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block);
void store_value_to_lvar_with_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, LVALUE* llvm_value);
StructType* get_vm_info_struct_type();
AllocaInst* create_entry_block_alloca(Function* function, int index);
void call_entry_exception_object_with_class_name2(std::map<std::string, Value *> params, char* class_name, char* message);
void if_value_is_zero_entry_exception_object(Value* value, int value_size, BOOL value_is_float, BOOL value_is_double, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block, char* class_name, char* message);
void vm_lvar_to_llvm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num);
void finish_method_call(Value* result, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char** try_catch_label_name, sByteCode* code, int real_param_num, int var_num, LVALUE* llvm_stack, LVALUE* llvm_stack_ptr);
void lvar_of_vm_to_lvar_of_llvm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num);
void lvar_of_llvm_to_lvar_of_vm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num);
void trunc_value_from_inst(LVALUE* value, int inst);
void store_value_to_vm_lvar(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset, LVALUE* llvm_value);
void llvm_lvar_to_vm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num);
LVALUE get_method_call_result(std::map<std::string, Value*>& params, BasicBlock* current_block);
void llvm_give_type_to_params(LVALUE* llvm_stack_ptr, std::map<std::string, Value*> params, BasicBlock* current_block, sCLMethod* method, sCLClass* klass);
void call_vm_mutex_on();
void call_vm_mutex_off();


/// jit declare.cpp ///
extern GlobalVariable* gSigIntValue;
extern GlobalVariable* gAndAndOrOrValue;
extern StructType* gCLValueAndBoolStruct;
extern StructType* gPointerAndBoolStruct;

void create_internal_functions();
void create_internal_functions2();
Function* create_llvm_function(const std::string& name);

/// jit_compile_method.cpp ///
BOOL jit_compile_all_classes();

/// jit_runtime.cpp ///
extern struct sCLVALUEAndBoolResult gCLValueAndBoolStructMemory;
extern struct sPointerAndBoolResult gCLPointerAndBoolStructMemory;
}

