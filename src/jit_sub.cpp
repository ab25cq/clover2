#include "jit_common.hpp"

extern "C" 
{

GlobalVariable* gSigIntValue;
StructType* gCLValueAndBoolStruct;
StructType* gPointerAndBoolStruct;

void create_internal_functions()
{
    Type* result_type;
    std::vector<Type *> type_params;
    Type* param1_type;
    Type* param2_type;
    Type* param3_type;
    Type* param4_type;
    Type* param5_type;
    Type* param6_type;
    Type* param7_type;
    Type* param8_type;
    Type* param9_type;
    Type* param10_type;
    Type* param11_type;
    Type* param12_type;
    FunctionType* function_type;

    /// create_string_object ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_string_object", TheModule.get());

    /// create_byte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_byte", TheModule.get());

    /// create_ubyte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ubyte", TheModule.get());

    /// create_short ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_short", TheModule.get());

    /// create_ushort ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ushort", TheModule.get());

    /// create_integer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_integer", TheModule.get());

    /// create_uinteger ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_uinteger", TheModule.get());

    /// create_long ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_long", TheModule.get());

    /// create_ulong ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ulong", TheModule.get());

    /// create_float ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getFloatTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_float", TheModule.get());

    /// create_double ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getDoubleTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_double", TheModule.get());

    /// create_pointer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_pointer", TheModule.get());

    /// create_char ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_char", TheModule.get());

    /// create_bool ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_bool", TheModule.get());

    /// create_buffer_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_buffer_object", TheModule.get());

    /// create_path_object ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_path_object", TheModule.get());

    /// create_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_object", TheModule.get());

    /// create_regex_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_regex_object", TheModule.get());

    /// create_array_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_array_object", TheModule.get());

    /// run_head_of_expression ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_head_of_expression", TheModule.get());

    /// run_load_address ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_address", TheModule.get());

    /// run_ldclong ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ldclong", TheModule.get());

    /// run_ldcpointer ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ldcpointer", TheModule.get());

    /// run_lduclong ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ldculong", TheModule.get());

    /// show_inst ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_inst_in_jit", TheModule.get());

    /// show_number ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_number_in_jit", TheModule.get());

    /// show_str ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_str_in_jit", TheModule.get());

    /// show_stack_stat ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_stack_stat", TheModule.get());

    /// show_stack_in_jit ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_stack_in_jit", TheModule.get());

    /// invoke_method ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);
    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);
    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);
    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);
    param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param5_type);
    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);

    Function::Create(function_type, Function::ExternalLinkage, "invoke_method", TheModule.get());

    /// try_function ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "try_function", TheModule.get());

    /// get_try_catch_label_name ///
    type_params.clear();

    result_type = PointerType::get(IntegerType::get(TheContext,8), 0);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_try_catch_label_name", TheModule.get());

    /// entry_exception_object ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object", TheModule.get());

    /// get_field_from_object ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_field_from_object", TheModule.get());

    /// regex_equals ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "regex_equals", TheModule.get());

    /// entry_exception_object_with_class_name ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object_with_class_name2", TheModule.get());

    /// get_string_object_of_object_name ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_string_object_of_object_name", TheModule.get());

    /// object_implements_interface ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);
    
    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "object_implements_interface", TheModule.get());

    /// call_invoke_virtual_method ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param9_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "call_invoke_virtual_method", TheModule.get());

    /// invoke_dynamic_method ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param9_type);

    param10_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param10_type);

    param11_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param11_type);

    param12_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param12_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "invoke_dynamic_method", TheModule.get());

    /// invoke_block_in_jit ///
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "invoke_block_in_jit", TheModule.get());

    /// run_load_field_adrress ///
    type_params.clear();
    
    result_type = PointerType::get(IntegerType::get(TheContext, 8), 0);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_field_address", TheModule.get());

    /// store_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "store_field", TheModule.get());

    /// load_class_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "load_class_field", TheModule.get());

    /// run_load_class_field_address ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_class_field_address", TheModule.get());

    /// store_class_field ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "store_class_field", TheModule.get());

    /// load_element ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "load_element", TheModule.get());

    /// run_store_element ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_store_element", TheModule.get());

    /// get_array_length ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_array_length", TheModule.get());

    /// get_regex_global ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_global", TheModule.get());

    /// get_regex_ignorecase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_ignorecase", TheModule.get());

    /// get_regex_multiline ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_multiline", TheModule.get());

    /// get_regex_extended ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_extended", TheModule.get());

    /// get_regex_dotall ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_dotall", TheModule.get());

    /// get_regex_anchored ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_anchored", TheModule.get());

    /// get_regex_dollar_endonly ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_dollar_endonly", TheModule.get());

    /// get_regex_ungreedy ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_ungreedy", TheModule.get());

    /// get_regex_anchored ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_multiline", TheModule.get());

    /// char_uppercase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "char_uppercase", TheModule.get());

    /// char_lowercase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "char_lowercase", TheModule.get());

    /// run_create_array ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_array", TheModule.get());

    /// run_create_carray ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_carray", TheModule.get());

    /// run_create_equalable_carray ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_carray", TheModule.get());

    /// run_create_sortable_carray ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_carray", TheModule.get());

    /// run_create_list ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_list", TheModule.get());

    /// run_create_sortable_list ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_list", TheModule.get());

    /// run_create_equalable_list ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_list", TheModule.get());

    /// run_create_tuple ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_tuple", TheModule.get());

    /// run_create_hash ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param7_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_hash", TheModule.get());

    /// run_create_block_object ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    param9_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param9_type);

    param10_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param10_type);

    param11_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param11_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_block_object", TheModule.get());

    /// run_int_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_int_to_string_cast", TheModule.get());

    /// run_long_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_long_to_string_cast", TheModule.get());

    /// run_uint_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uint_to_string_cast", TheModule.get());

    /// run_ulong_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ulong_to_string_cast", TheModule.get());

    /// run_float_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getFloatTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_float_to_string_cast", TheModule.get());

    /// run_double_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getDoubleTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_double_to_string_cast", TheModule.get());

    /// run_bool_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_bool_to_string_cast", TheModule.get());

    /// run_regex_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_regex_to_string_cast", TheModule.get());

    /// run_pointer_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_pointer_to_string_cast", TheModule.get());
    /// run_char_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_char_to_string_cast", TheModule.get());

    /// run_cbyte_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_byte_cast", TheModule.get());

    /// run_cubyte_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_byte_cast", TheModule.get());

    /// run_cshort_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_byte_cast", TheModule.get());

    /// run_cushort_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_byte_cast", TheModule.get());

    /// run_integer_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_byte_cast", TheModule.get());

    /// run_uinteger_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_byte_cast", TheModule.get());

    /// run_clong_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_byte_cast", TheModule.get());

    /// run_culong_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_byte_cast", TheModule.get());

    /// run_cfloat_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_byte_cast", TheModule.get());

    /// run_cdouble_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_byte_cast", TheModule.get());

    /// run_cpointer_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_byte_cast", TheModule.get());

    /// run_cchar_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_byte_cast", TheModule.get());

    /// run_cbool_to_byte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_byte_cast", TheModule.get());

    /// run_cbyte_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_short_cast", TheModule.get());

    /// run_cubyte_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_short_cast", TheModule.get());

    /// run_cshort_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_short_cast", TheModule.get());

    /// run_cushort_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_short_cast", TheModule.get());

    /// run_integer_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_short_cast", TheModule.get());

    /// run_uinteger_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_short_cast", TheModule.get());

    /// run_clong_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_short_cast", TheModule.get());

    /// run_culong_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_short_cast", TheModule.get());

    /// run_cfloat_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_short_cast", TheModule.get());

    /// run_cdouble_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_short_cast", TheModule.get());
    /// run_cpointer_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_short_cast", TheModule.get());
    /// run_cchar_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_short_cast", TheModule.get());

    /// run_cbool_to_short_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_short_cast", TheModule.get());

    /// run_cbyte_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_int_cast", TheModule.get());

    /// run_cubyte_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_int_cast", TheModule.get());

    /// run_cshort_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_int_cast", TheModule.get());

    /// run_cushort_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_int_cast", TheModule.get());

    /// run_integer_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_int_cast", TheModule.get());

    /// run_uinteger_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_int_cast", TheModule.get());

    /// run_clong_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_int_cast", TheModule.get());

    /// run_culong_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_int_cast", TheModule.get());

    /// run_cfloat_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_int_cast", TheModule.get());

    /// run_cdouble_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_int_cast", TheModule.get());

    /// run_cpointer_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_int_cast", TheModule.get());

    /// run_cchar_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_int_cast", TheModule.get());

    /// run_cbool_to_int_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_int_cast", TheModule.get());


    /// run_cbyte_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_long_cast", TheModule.get());

    /// run_cubyte_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_long_cast", TheModule.get());

    /// run_cshort_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_long_cast", TheModule.get());

    /// run_cushort_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_long_cast", TheModule.get());

    /// run_integer_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_long_cast", TheModule.get());

    /// run_uinteger_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_long_cast", TheModule.get());

    /// run_clong_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_long_cast", TheModule.get());

    /// run_culong_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_long_cast", TheModule.get());

    /// run_cfloat_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_long_cast", TheModule.get());

    /// run_cdouble_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_long_cast", TheModule.get());

    /// run_cpointer_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_long_cast", TheModule.get());

    /// run_cchar_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_long_cast", TheModule.get());

    /// run_cbool_to_long_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_long_cast", TheModule.get());

    /// run_cbyte_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_ubyte_cast", TheModule.get());

    /// run_cubyte_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ubyte_cast", TheModule.get());

    /// run_cshort_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_ubyte_cast", TheModule.get());

    /// run_cushort_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ubyte_cast", TheModule.get());

    /// run_integer_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_ubyte_cast", TheModule.get());

    /// run_uinteger_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_ubyte_cast", TheModule.get());

    /// run_clong_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_ubyte_cast", TheModule.get());

    /// run_culong_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ubyte_cast", TheModule.get());

    /// run_cfloat_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_ubyte_cast", TheModule.get());

    /// run_cdouble_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_ubyte_cast", TheModule.get());

    /// run_cpointer_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_ubyte_cast", TheModule.get());

    /// run_cchar_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_ubyte_cast", TheModule.get());

    /// run_cbool_to_ubyte_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_ubyte_cast", TheModule.get());

    /// run_cbyte_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_ushort_cast", TheModule.get());

    /// run_cubyte_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ushort_cast", TheModule.get());

    /// run_cshort_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_ushort_cast", TheModule.get());

    /// run_cushort_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ushort_cast", TheModule.get());

    /// run_integer_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_ushort_cast", TheModule.get());

    /// run_uinteger_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_ushort_cast", TheModule.get());

    /// run_clong_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_ushort_cast", TheModule.get());

    /// run_culong_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ushort_cast", TheModule.get());

    /// run_cfloat_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_ushort_cast", TheModule.get());

    /// run_cdouble_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_ushort_cast", TheModule.get());
    /// run_cpointer_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_ushort_cast", TheModule.get());
    /// run_cchar_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_ushort_cast", TheModule.get());

    /// run_cbool_to_ushort_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_ushort_cast", TheModule.get());

    /// run_cbyte_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_uint_cast", TheModule.get());

    /// run_cubyte_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_uint_cast", TheModule.get());

    /// run_cshort_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_uint_cast", TheModule.get());

    /// run_cushort_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_uint_cast", TheModule.get());

    /// run_integer_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_uint_cast", TheModule.get());

    /// run_uinteger_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_uint_cast", TheModule.get());

    /// run_clong_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_uint_cast", TheModule.get());

    /// run_culong_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_uint_cast", TheModule.get());

    /// run_cfloat_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_uint_cast", TheModule.get());

    /// run_cdouble_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_uint_cast", TheModule.get());

    /// run_cpointer_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_uint_cast", TheModule.get());

    /// run_cchar_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_uint_cast", TheModule.get());

    /// run_cbool_to_uint_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_uint_cast", TheModule.get());

    /// run_cbyte_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_ulong_cast", TheModule.get());

    /// run_cubyte_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ulong_cast", TheModule.get());

    /// run_cshort_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_ulong_cast", TheModule.get());

    /// run_cushort_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ulong_cast", TheModule.get());

    /// run_integer_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_ulong_cast", TheModule.get());

    /// run_uinteger_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_ulong_cast", TheModule.get());

    /// run_clong_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_ulong_cast", TheModule.get());

    /// run_culong_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ulong_cast", TheModule.get());

    /// run_cfloat_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_ulong_cast", TheModule.get());

    /// run_cdouble_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_ulong_cast", TheModule.get());

    /// run_cpointer_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_ulong_cast", TheModule.get());

    /// run_cchar_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_ulong_cast", TheModule.get());

    /// run_cbool_to_ulong_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_ulong_cast", TheModule.get());

    /// run_cbyte_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_float_cast", TheModule.get());

    /// run_cubyte_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_float_cast", TheModule.get());

    /// run_cshort_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_float_cast", TheModule.get());

    /// run_cushort_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_float_cast", TheModule.get());

    /// run_integer_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_float_cast", TheModule.get());

    /// run_uinteger_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_float_cast", TheModule.get());

    /// run_clong_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_float_cast", TheModule.get());

    /// run_culong_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_float_cast", TheModule.get());

    /// run_cfloat_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_float_cast", TheModule.get());

    /// run_cdouble_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_float_cast", TheModule.get());


    /// run_cchar_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_float_cast", TheModule.get());

    /// run_cbool_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_float_cast", TheModule.get());

    /// run_cbyte_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_double_cast", TheModule.get());

    /// run_cubyte_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_double_cast", TheModule.get());

    /// run_cshort_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_double_cast", TheModule.get());

    /// run_cushort_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_double_cast", TheModule.get());

    /// run_integer_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_double_cast", TheModule.get());

    /// run_uinteger_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_double_cast", TheModule.get());

    /// run_clong_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_double_cast", TheModule.get());

    /// run_culong_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_double_cast", TheModule.get());

    /// run_cfloat_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_double_cast", TheModule.get());

    /// run_cdouble_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_double_cast", TheModule.get());


    /// run_cchar_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cchar_to_double_cast", TheModule.get());

    /// run_cbool_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbool_to_double_cast", TheModule.get());

    /// run_array_to_carray_cast ///
    type_params.clear();
    
    result_type = Type::getInt32Ty(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_array_to_carray_cast", TheModule.get());


    /// run_native_method_dec_stack_ptr ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);

    param4_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param4_type);

    param5_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_native_method_dec_stack_ptr", TheModule.get());

    /// gSigInt ///
    Type* variable_type = IntegerType::get(TheContext, 32);
    gSigIntValue = new GlobalVariable(*TheModule, variable_type, false, GlobalValue::ExternalLinkage, nullptr, "gSigInt");
}

void InitializeModuleAndPassManager() 
{
    TheModule = llvm::make_unique<Module>("Clover2 jit", TheContext);
    TheModule->setDataLayout(TheJIT->getTargetMachine().createDataLayout());
    
    TheFPM = llvm::make_unique<legacy::FunctionPassManager>(TheModule.get());
    
    TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->doInitialization();

    create_internal_functions();
    TheLabels.clear();
}

void jit_init()
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    TheJIT = llvm::make_unique<CloverJIT>();

    InitializeModuleAndPassManager();

    /// CLVALUE and BOOL Struct type ///
    gCLValueAndBoolStruct = StructType::create(TheContext, "clvalue_and_bool_struct");

    std::vector<Type*> fields;
    Type* field_type1 = IntegerType::get(TheContext, 64);
    fields.push_back(field_type1);
    Type* field_type2 = IntegerType::get(TheContext, 32);
    fields.push_back(field_type2);

    if(gCLValueAndBoolStruct->isOpaque()) {
        gCLValueAndBoolStruct->setBody(fields, false);
    }

    /// CLVALUE and BOOL Struct type ///
    fields.clear();

    gPointerAndBoolStruct = StructType::create(TheContext, "pointer_and_bool_struct");

    field_type1 = PointerType::get(IntegerType::get(TheContext, 8), 0);
    fields.push_back(field_type1);
    field_type2 = IntegerType::get(TheContext, 32);
    fields.push_back(field_type2);

    if(gPointerAndBoolStruct->isOpaque()) {
        gPointerAndBoolStruct->setBody(fields, false);
    }
}

void jit_final()
{
}

void create_method_path_for_jit(sCLClass* klass, sCLMethod* method, char* result, int size_result)
{
    snprintf(result, size_result, "%s$$%d", METHOD_PATH(klass, method), method->mMethodIndex);
}

/////////////////////////////////////////////////////////////////////////////
/// JIT debug functions
/////////////////////////////////////////////////////////////////////////////
void show_stack_stat(CLVALUE** stack_ptr, CLVALUE* stack)
{
    printf("stack_ptr %p\n", stack_ptr);
    printf("*stack_ptr %p\n", *stack_ptr);
    printf("stack_ptr - stack %d\n", (int)(*stack_ptr - stack));
}

BOOL show_stack_in_jit(CLVALUE** stack_ptr, CLVALUE* stack, int var_num, sVMInfo* info)
{
    printf("var_num %d\n", var_num);
    show_stack_stat(stack_ptr, stack);

    int i;
    for(i=0; i<10; i++) {
        if(*stack_ptr == stack + i) {
            printf("! stack [%d] %d(%ld) on %p\n", i, stack[i].mIntValue, stack[i].mULongValue, stack + i);
        }
        else {
            printf("  stack [%d] %d(%ld) on %p\n", i, stack[i].mIntValue, stack[i].mULongValue, stack + i);
        }
    }

    return TRUE;
}

void show_inst_in_jit(int opecode)
{
    switch(opecode) {
        case OP_BYTE_TO_CULONG_CAST:
            puts("OP_BYTE_TO_CULONG_CAST");
            break;

        case OP_UBYTE_TO_CULONG_CAST:
            puts("OP_UBYTE_TO_CULONG_CAST");
            break;

        case OP_SHORT_TO_CULONG_CAST :
            puts("OP_SHORT_TO_CULONG_CAST ");
            break;

        case OP_USHORT_TO_CULONG_CAST :
            puts("OP_USHORT_TO_CULONG_CAST ");
            break;

        case OP_INT_TO_CULONG_CAST :
            puts("OP_INT_TO_CULONG_CAST ");
            break;

        case OP_UINT_TO_CULONG_CAST :
            puts("OP_UINT_TO_CULONG_CAST ");
            break;

        case OP_LONG_TO_CULONG_CAST :
            puts("OP_LONG_TO_CULONG_CAST ");
            break;

        case OP_ULONG_TO_CULONG_CAST :
            puts("OP_ULONG_TO_CULONG_CAST ");
            break;

        case OP_FLOAT_TO_CULONG_CAST :
            puts("OP_FLOAT_TO_CULONG_CAST ");
            break;

        case OP_DOUBLE_TO_CULONG_CAST :
            puts("OP_DOUBLE_TO_CULONG_CAST ");
            break;

        case OP_CHAR_TO_CULONG_CAST :
            puts("OP_CHAR_TO_CULONG_CAST ");
            break;

        case OP_POINTER_TO_CULONG_CAST :
            puts("OP_POINTER_TO_CULONG_CAST ");
            break;

        case OP_BOOL_TO_CULONG_CAST :
            puts("OP_BOOL_TO_CULONG_CAST ");
            break;

        case OP_INT_TO_ULONG_CAST:
            puts("OP_INT_TO_ULONG_CAST");
            break;

        case OP_CREATE_BUFFER :
            puts("OP_CREATE_BUFFER");
            break;

        case OP_CREATE_PATH :
            puts("OP_CREATE_PATH");
            break;

        case OP_CREATE_ARRAY :
            puts("OP_CREATE_ARRAY");
            break;

        case OP_CREATE_CARRAY :
            puts("OP_CREATE_CARRAY");
            break;

        case OP_CREATE_SORTABLE_CARRAY :
            puts("OP_CREATE_SORTABLE_CARRAY");
            break;

        case OP_CREATE_EQUALABLE_CARRAY :
            puts("OP_CREATE_EQUALABLE_CARRAY");
            break;

        case OP_CREATE_LIST :
            puts("OP_CREATE_LIST");
            break;

        case OP_CREATE_SORTALBE_LIST :
            puts("OP_CREATE_SORTALBE_LIST");
            break;

        case OP_CREATE_EQUALABLE_LIST :
            puts("OP_CREATE_EQUALABLE_LIST");
            break;

        case OP_CREATE_TUPLE :
            puts("OP_CREATE_TUPLE");
            break;

        case OP_CREATE_HASH :
            puts("OP_CREATE_HASH");
            break;

        case OP_CREATE_BLOCK_OBJECT :
            puts("OP_CREATE_BLOCK_OBJECT");
            break;

        case OP_BYTE_TO_STRING_CAST :
            puts("OP_BYTE_TO_STRING_CAST");
            break;

        case OP_SHORT_TO_STRING_CAST :
            puts("OP_SHORT_TO_STRING_CAST");
            break;

        case OP_INT_TO_STRING_CAST :
            puts("OP_INT_TO_STRING_CAST");
            break;

        case OP_LONG_TO_STRING_CAST :
            puts("OP_LONG_TO_STRING_CAST");
            break;

        case OP_UBYTE_TO_STRING_CAST :
            puts("OP_UBYTE_TO_STRING_CAST");
            break;

        case OP_USHORT_TO_STRING_CAST :
            puts("OP_USHORT_TO_STRING_CAST");
            break;

        case OP_UINT_TO_STRING_CAST :
            puts("OP_UINT_TO_STRING_CAST");
            break;

        case OP_ULONG_TO_STRING_CAST :
            puts("OP_ULONG_TO_STRING_CAST");
            break;

        case OP_FLOAT_TO_STRING_CAST :
            puts("OP_FLOAT_TO_STRING_CAST");
            break;

        case OP_DOUBLE_TO_STRING_CAST :
            puts("OP_DOUBLE_TO_STRING_CAST");
            break;

        case OP_BOOL_TO_STRING_CAST :
            puts("OP_BOOL_TO_STRING_CAST");
            break;

        case OP_REGEX_TO_STRING_CAST :
            puts("OP_REGEX_TO_STRING_CAST");
            break;

        case OP_POINTER_TO_STRING_CAST :
            puts("OP_POINTER_TO_STRING_CAST");
            break;

        case OP_BYTE_TO_INTEGER_CAST :
            puts("OP_BYTE_TO_INTEGER_CAST");
            break;

        case OP_UBYTE_TO_INTEGER_CAST :
            puts("OP_UBYTE_TO_INTEGER_CAST");
            break;

        case OP_SHORT_TO_INTEGER_CAST :
            puts("OP_SHORT_TO_INTEGER_CAST");
            break;

        case OP_USHORT_TO_INTEGER_CAST :
            puts("OP_USHORT_TO_INTEGER_CAST");
            break;

        case OP_INT_TO_INTEGER_CAST :
            puts("OP_INT_TO_INTEGER_CAST");
            break;

        case OP_UINT_TO_INTEGER_CAST :
            puts("OP_UINT_TO_INTEGER_CAST");
            break;

        case OP_LONG_TO_INTEGER_CAST :
            puts("OP_LONG_TO_INTEGER_CAST");
            break;

        case OP_ULONG_TO_INTEGER_CAST :
            puts("OP_ULONG_TO_INTEGER_CAST");
            break;

        case OP_FLOAT_TO_INTEGER_CAST :
            puts("OP_FLOAT_TO_INTEGER_CAST");
            break;

        case OP_DOUBLE_TO_INTEGER_CAST :
            puts("OP_DOUBLE_TO_INTEGER_CAST");
            break;

        case OP_CHAR_TO_INTEGER_CAST :
            puts("OP_CHAR_TO_INTEGER_CAST");
            break;

        case OP_POINTER_TO_INTEGER_CAST :
            puts("OP_POINTER_TO_INTEGER_CAST");
            break;

        case OP_BOOL_TO_INTEGER_CAST :
            puts("OP_BOOL_TO_INTEGER_CAST");
            break;

        case OP_CHAR_TO_STRING_CAST :
            puts("OP_CHAR_TO_STRING_CAST");
            break;

        case OP_STORE_FIELD:
            puts("OP_STORE_FIELD");
            break;

        case OP_POP:
            puts("OP_POP");
            break;

        case OP_DUPE:
            puts("OP_DUPE");
            break;

        case OP_COND_JUMP :
            puts("OP_COND_JUMP");
            break;

        case OP_COND_NOT_JUMP:
            puts("OP_COND_NOT_JUMP");
            break;

        case OP_GOTO:
            puts("OP_GOTO");
            break;

        case OP_LABEL:
            puts("OP_LABEL");
            break;

        case OP_LOAD:
            puts("OP_LOAD");
            break;

        case OP_STORE:
            puts("OP_STORE");
            break;

        case OP_LDCBYTE: 
            puts("OP_LDCBYTE");
            break;

        case OP_LDCINT: 
            puts("OP_LDCINT");
            break;

        case OP_LDCNULL:
            puts("OP_LDCNULL");
            break;

        case OP_BADD:
            puts("OP_BAND");
            break;

        case OP_BSUB:
            puts("OP_BSUB");
            break;

        case OP_BMULT:
            puts("OP_BMULT");
            break;

        case OP_BDIV:
            puts("OP_BDIV");
            break;

        case OP_BMOD:
            puts("OP_BMOD");
            break;

        case OP_BLSHIFT:
            puts("OP_BLSHIFT");
            break;

        case OP_BRSHIFT:
            puts("OP_BRSHIFT");
            break;

        case OP_BAND:
            puts("OP_BAND");
            break;

        case OP_BXOR:
            puts("OP_BXOR");
            break;

        case OP_BOR:
            puts("OP_BOR");
            break;

        case OP_UBADD:
            puts("OP_UBAND");
            break;

        case OP_UBSUB:
            puts("OP_UBSUB");
            break;

        case OP_UBMULT:
            puts("OP_UBMULT");
            break;

        case OP_UBDIV:
            puts("OP_UBDIV");
            break;

        case OP_UBMOD:
            puts("OP_UBMOD");
            break;

        case OP_UBLSHIFT:
            puts("OP_UBLSHIFT");
            break;

        case OP_UBRSHIFT:
            puts("OP_UBRSHIFT");
            break;

        case OP_UBAND:
            puts("OP_UBAND");
            break;

        case OP_UBXOR:
            puts("OP_UBXOR");
            break;

        case OP_UBOR:
            puts("OP_BOR");
            break;

        case OP_SADD:
            puts("OP_SADD");
            break;

        case OP_SSUB:
            puts("OP_SSUB");
            break;

        case OP_SMULT: 
            puts("OP_SMULT");
            break;

        case OP_SDIV: 
            puts("OP_SDIV");
            break;

        case OP_SMOD: 
            puts("OP_SMOD");
            break;

        case OP_SLSHIFT: 
            puts("OP_SLSHIFT");
            break;

        case OP_SRSHIFT: 
            puts("OP_SRSHIFT");
            break;

        case OP_SAND: 
            puts("OP_SAND");
            break;

        case OP_SXOR: 
            puts("OP_SXOR");
            break;

        case OP_SOR: 
            puts("OP_SOR");
            break;

        case OP_USADD: 
            puts("OP_USADD");
            break;

        case OP_USSUB: 
            puts("OP_USSUB");
            break;

        case OP_USMULT: 
            puts("OP_USMULT");
            break;

        case OP_USDIV: 
            puts("OP_USDIV");
            break;

        case OP_USMOD: 
            puts("OP_USMOD");
            break;

        case OP_USLSHIFT: 
            puts("OP_USLSHIFT");
            break;

        case OP_USRSHIFT: 
            puts("OP_USRSHIFT");
            break;

        case OP_USAND: 
            puts("OP_USAND");
            break;

        case OP_USXOR: 
            puts("OP_USXOR");
            break;

        case OP_USOR: 
            puts("OP_USOR");
            break;

        case OP_IADD: 
            puts("OP_IADD");
            break;

        case OP_ISUB: 
            puts("OP_ISUB");
            break;

        case OP_IMULT: 
            puts("OP_IMULT");
            break;

        case OP_IDIV: 
            puts("OP_IDIV");
            break;

        case OP_IMOD: 
            puts("OP_IMOD");
            break;

        case OP_ILSHIFT: 
            puts("OP_ILSHIFT");
            break;

        case OP_IRSHIFT: 
            puts("OP_IRSHIFT");
            break;

        case OP_IAND: 
            puts("OP_IAND");
            break;

        case OP_IXOR: 
            puts("OP_IXOR");
            break;

        case OP_IOR: 
            puts("OP_IOR");
            break;

        case OP_UIADD: 
            puts("OP_UIADD");
            break;

        case OP_UISUB: 
            puts("OP_UISUB");
            break;

        case OP_UIMULT: 
            puts("OP_UIMULT");
            break;

        case OP_UIDIV: 
            puts("OP_UIDIV");
            break;

        case OP_UIMOD: 
            puts("OP_UIMOD");
            break;

        case OP_UILSHIFT: 
            puts("OP_UILSHIFT");
            break;

        case OP_UIRSHIFT: 
            puts("OP_UIRSHIFT");
            break;

        case OP_UIAND: 
            puts("OP_UIAND");
            break;

        case OP_UIXOR: 
            puts("OP_UIXOR");
            break;

        case OP_UIOR: 
            puts("OP_UIOR");
            break;

        case OP_LADD: 
            puts("OP_LADD");
            break;

        case OP_LSUB: 
            puts("OP_LSUB");
            break;

        case OP_LMULT: 
            puts("OP_LMULT");
            break;

        case OP_LDIV: 
            puts("OP_LDIV");
            break;

        case OP_LMOD: 
            puts("OP_LMOD");
            break;

        case OP_LLSHIFT: 
            puts("OP_LLSHIFT");
            break;

        case OP_LRSHIFT: 
            puts("OP_LRSHIFT");
            break;

        case OP_LAND: 
            puts("OP_LAND");
            break;

        case OP_LXOR: 
            puts("OP_LXOR");
            break;

        case OP_LOR: 
            puts("OP_LOR");
            break;

        case OP_ULADD: 
            puts("OP_ULADD");
            break;

        case OP_ULSUB: 
            puts("OP_ULSUB");
            break;

        case OP_ULMULT: 
            puts("OP_ULMULT");
            break;

        case OP_ULDIV: 
            puts("OP_ULDIV");
            break;

        case OP_ULMOD: 
            puts("OP_ULMOD");
            break;

        case OP_ULLSHIFT: 
            puts("OP_ULLSHIFT");
            break;

        case OP_ULRSHIFT: 
            puts("OP_ULRSHIFT");
            break;

        case OP_ULAND: 
            puts("OP_ULAND");
            break;

        case OP_ULXOR: 
            puts("OP_ULXOR");
            break;

        case OP_UBCOMPLEMENT:
            puts("OP_UBCOMPLEMENT");
            break;

        case OP_SCOMPLEMENT:
            puts("OP_SCOMPLEMENT");
            break;

        case OP_USCOMPLEMENT:
            puts("OP_USCOMPLEMENT");
            break;

        case OP_ICOMPLEMENT:
            puts("OP_ICOMPLEMENT");
            break;

        case OP_UICOMPLEMENT:
            puts("OP_UICOMPLEMENT");
            break;

        case OP_LCOMPLEMENT:
            puts("OP_LCOMPLEMENT");
            break;

        case OP_ULCOMPLEMENT:
            puts("OP_ULCOMPLEMENT");
            break;


        case OP_FADD:
            puts("OP_FADD");
            break;

        case OP_FSUB:
            puts("OP_FSUB");
            break;

        case OP_FMULT:
            puts("OP_FMULT");
            break;

        case OP_FDIV:
            puts("OP_FDIV");
            break;


        case OP_DADD:
            puts("OP_DADD");
            break;

        case OP_DSUB:
            puts("OP_DSUB");
            break;

        case OP_DMULT:
            puts("OP_DMULT");
            break;

        case OP_DDIV:
            puts("OP_DDIV");
            break;


        case OP_PADD:
            puts("OP_PADD");
            break;

        case OP_PSUB:
            puts("OP_PSUB");
            break;

        case OP_PPSUB:
            puts("OP_PPSUB");
            break;


        case OP_CADD:
            puts("OP_CADD");
            break;

        case OP_CSUB:
            puts("OP_CSUB");
            break;


        case OP_BEQ :
            puts("OP_BEQ ");
            break;

        case OP_BNOTEQ :
            puts("OP_BNOTEQ ");
            break;

        case OP_BGT :
            puts("OP_BGT ");
            break;

        case OP_BLE :
            puts("OP_BLE ");
            break;

        case OP_BGTEQ :
            puts("OP_BGTEQ ");
            break;

        case OP_BLEEQ :
            puts("OP_BLEEQ ");
            break;


        case OP_UBEQ :
            puts("OP_UBEQ ");
            break;

        case OP_UBNOTEQ :
            puts("OP_UBNOTEQ ");
            break;

        case OP_UBGT :
            puts("OP_UBGT ");
            break;

        case OP_UBLE :
            puts("OP_UBLE ");
            break;

        case OP_UBGTEQ :
            puts("OP_UBGTEQ ");
            break;

        case OP_UBLEEQ :
            puts("OP_UBLEEQ ");
            break;


        case OP_SEQ :
            puts("OP_SEQ ");
            break;

        case OP_SNOTEQ :
            puts("OP_SNOTEQ ");
            break;

        case OP_SGT :
            puts("OP_SGT ");
            break;

        case OP_SLE :
            puts("OP_SLE ");
            break;

        case OP_SGTEQ :
            puts("OP_SGTEQ ");
            break;

        case OP_SLEEQ :
            puts("OP_SLEEQ ");
            break;


        case OP_USEQ :
            puts("OP_USEQ ");
            break;

        case OP_USNOTEQ :
            puts("OP_USNOTEQ ");
            break;

        case OP_USGT :
            puts("OP_USGT ");
            break;

        case OP_USLE :
            puts("OP_USLE ");
            break;

        case OP_USGTEQ :
            puts("OP_USGTEQ ");
            break;

        case OP_USLEEQ :
            puts("OP_USLEEQ ");
            break;

        case OP_INOTEQ :
            puts("OP_INOTEQ ");
            break;

        case OP_IGT :
            puts("OP_IGT ");
            break;

        case OP_UIEQ :
            puts("OP_UIEQ ");
            break;

        case OP_UINOTEQ :
            puts("OP_UINOTEQ ");
            break;

        case OP_UIGT :
            puts("OP_UIGT ");
            break;

        case OP_UILE :
            puts("OP_UILE ");
            break;

        case OP_UIGTEQ :
            puts("OP_UIGTEQ ");
            break;

        case OP_UILEEQ :
            puts("OP_UILEEQ ");
            break;



        case OP_LEQ :
            puts("OP_LEQ ");
            break;

        case OP_LNOTEQ :
            puts("OP_LNOTEQ ");
            break;

        case OP_LGT :
            puts("OP_LGT ");
            break;

        case OP_LLE :
            puts("OP_LLE ");
            break;

        case OP_LGTEQ :
            puts("OP_LGTEQ ");
            break;

        case OP_LLEEQ :
            puts("OP_LLEEQ ");
            break;


        case OP_ULEQ :
            puts("OP_ULEQ ");
            break;

        case OP_ULNOTEQ :
            puts("OP_ULNOTEQ ");
            break;

        case OP_ULGT :
            puts("OP_ULGT ");
            break;

        case OP_ULLE :
            puts("OP_ULLE ");
            break;

        case OP_ULGTEQ :
            puts("OP_ULGTEQ ");
            break;

        case OP_ULLEEQ :
            puts("OP_ULLEEQ ");
            break;



        case OP_FEQ :
            puts("OP_FEQ ");
            break;

        case OP_FNOTEQ :
            puts("OP_FNOTEQ ");
            break;

        case OP_FGT :
            puts("OP_FGT ");
            break;

        case OP_FLE :
            puts("OP_FLE ");
            break;

        case OP_FGTEQ :
            puts("OP_FGTEQ ");
            break;

        case OP_FLEEQ :
            puts("OP_FLEEQ ");
            break;



        case OP_DEQ :
            puts("OP_DEQ ");
            break;

        case OP_DNOTEQ :
            puts("OP_DNOTEQ ");
            break;

        case OP_DGT :
            puts("OP_DGT ");
            break;

        case OP_DLE :
            puts("OP_DLE ");
            break;

        case OP_DGTEQ :
            puts("OP_DGTEQ ");
            break;

        case OP_DLEEQ :
            puts("OP_DLEEQ ");
            break;



        case OP_PEQ :
            puts("OP_PEQ ");
            break;

        case OP_PNOTEQ :
            puts("OP_PNOTEQ ");
            break;

        case OP_PGT :
            puts("OP_PGT ");
            break;

        case OP_PLE :
            puts("OP_PLE ");
            break;

        case OP_PGTEQ :
            puts("OP_PGTEQ ");
            break;

        case OP_PLEEQ :
            puts("OP_PLEEQ ");
            break;


        case OP_CEQ :
            puts("OP_CEQ ");
            break;

        case OP_CNOTEQ :
            puts("OP_CNOTEQ ");
            break;

        case OP_CGT :
            puts("OP_CGT ");
            break;

        case OP_CLE :
            puts("OP_CLE ");
            break;

        case OP_CGTEQ :
            puts("OP_CGTEQ ");
            break;

        case OP_CLEEQ :
            puts("OP_CLEEQ ");
            break;

        case OP_REGEQ :
            puts("OP_REGEQ ");
            break;

        case OP_REGNOTEQ :
            puts("OP_REGNOTEQ ");
            break;

        case OP_ULOR: 
            puts("OP_ULOR");
            break;

        case OP_RETURN: 
            puts("OP_RETURN");
            break;

        case OP_TRY:
            puts("OP_TRY");
            break;

        case OP_INVOKE_METHOD:
            puts("OP_INVOKE_METHOD");
            break;

        case OP_THROW:
            puts("OP_THROW");
            break;

        case OP_CREATE_STRING:
            puts("OP_CREATE_STRING");
            break;

        case OP_CREATE_REGEX:
            puts("OP_CREATE_REGEX");
            break;

        case OP_HEAD_OF_EXPRESSION: 
            puts("OP_HEAD_OF_EXPRESSION");
            break;

        case OP_SIGINT:
            puts("OP_SIGINT");
            break;

        case OP_NEW:
            puts("OP_NEW");
            break;

        case OP_BCOMPLEMENT:
            puts("OP_BCOMPLEMENT");
            break;

        case OP_IEQ:
            puts("OP_IEQ");
            break;

        case OP_ILE:
            puts("OP_ILE");
            break;

        case OP_IGTEQ:
            puts("OP_IGTEQ");
            break;

        case OP_ANDAND:
            puts("OP_ANDAND");
            break;

        case OP_LOAD_FIELD:
            puts("OP_LOAD_FIELD");
            break;

        case OP_BYTE_TO_INT_CAST:
            puts("OP_BYTE_TO_INT_CAST");
            break;

        case OP_LOAD_ELEMENT :
            puts("OP_LOAD_ELEMENT");
            break;

        case OP_STORE_ELEMENT:
            puts("OP_STORE_ELEMENT");
            break;

/*
        case OP_INT_TO_BYTE_CAST:
            puts("OP_INT_TO_BYTE_CAST");
            break;
*/

        default:
            printf("opecode %d\n", opecode);
            break;
    }
}

void show_number_in_jit(int number)
{
    printf("%d(%p)\n", number, number);
}

void call_show_number_in_jit(int number)
{
    Function* show_number = TheModule->getFunction("show_number_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)number);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_number, params2);
}

void call_show_value_in_jit(Value* value)
{
    Function* show_number = TheModule->getFunction("show_number_in_jit");

    std::vector<Value*> params2;
    Value* param1 = value;
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_number, params2);
}

void show_str_in_jit(char* str)
{
    printf("%s\n", str);
}

void call_show_str_in_jit(Value* value)
{
    Function* show_str = TheModule->getFunction("show_str_in_jit");

    std::vector<Value*> params2;
    params2.push_back(value);

    Value* result = Builder.CreateCall(show_str, params2);
}

void call_show_stack_stat(std::map<std::string, Value *> params)
{
    Function* show_address_fun = TheModule->getFunction("show_stack_stat");

    std::vector<Value*> params2;

    std::string stack_ptr_address_arg_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_arg_name];
    Value* param1 = stack_ptr_address_value;
    params2.push_back(param1);

    std::string stack_arg_name("stack");
    Value* stack_value = params[stack_arg_name];
    Value* param2 = stack_value;
    params2.push_back(param2);

    Value* result = Builder.CreateCall(show_address_fun, params2);
}


void call_show_inst_in_jit(int opecode)
{
    Function* show_inst = TheModule->getFunction("show_inst_in_jit");

    std::vector<Value*> params2;
    Value* param1 = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)opecode);
    params2.push_back(param1);

    Value* result = Builder.CreateCall(show_inst, params2);
}

void call_show_stack(std::map<std::string, Value *> params)
{
    Function* show_stack_fun = TheModule->getFunction("show_stack_in_jit");

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");
    std::string stack_name("stack");
    Value* stack_value = params[stack_name];

    std::vector<Value*> params2;
    Value* param1 = stack_ptr_address_value;
    params2.push_back(param1);

    Value* param2 = stack_value;
    params2.push_back(param2);

    std::string var_num_value_name("var_num");
    Value* param3 = params[var_num_value_name];
    params2.push_back(param3);

    std::string info_value_name("info");
    Value* param4 = params[info_value_name];
    params2.push_back(param4);

    Value* result = Builder.CreateCall(show_stack_fun, params2);
}

////////////////////////////////////////////////////////////
// LLVM invoking method
////////////////////////////////////////////////////////////
#define JIT_METHOD_CALL_COUNT 100

BOOL compile_jit_method(sCLClass* klass, sCLMethod* method)
{
    method->mMethodCallCount++;

if(strcmp(CLASS_NAME(klass), "JITTest") == 0) {
    method->mMethodCallCount = 1000;
}

    if(method->mMethodCallCount > JIT_METHOD_CALL_COUNT && !method->mJITCompiled) {
        if(strcmp(METHOD_NAME2(klass, method), "initialize") != 0 && strcmp(METHOD_NAME2(klass, method), "finalize") != 0) 
        {
            char method_path2[METHOD_NAME_MAX + 128];
            create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);

            sByteCode* code = &method->uCode.mByteCodes;
            sConst* constant = &klass->mConst;

            auto ExprSymbol = TheJIT->findSymbol(method_path2);
            if(!ExprSymbol) {
                if(!compile_to_native_code(code, constant, klass, method, method_path2)) {
                    return FALSE;
                }
TheModule->dump();


                auto H = TheJIT->addModule(std::move(TheModule));
                InitializeModuleAndPassManager();
            }
        }

        method->mJITCompiled = TRUE;
    }

    return TRUE;
}

} // extern "C"
