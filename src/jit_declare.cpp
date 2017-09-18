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
    Function::Create(function_type, Function::ExternalLinkage, "create_string_object", TheModule);

    /// create_byte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_byte", TheModule);

    /// create_ubyte ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 8);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ubyte", TheModule);

    /// create_short ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_short", TheModule);

    /// create_ushort ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 16);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ushort", TheModule);

    /// create_integer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_integer", TheModule);

    /// create_uinteger ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_uinteger", TheModule);

    /// create_long ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_long", TheModule);

    /// create_ulong ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext,64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_ulong", TheModule);

    /// create_float ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getFloatTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_float", TheModule);

    /// create_double ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getDoubleTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_double", TheModule);

    /// create_pointer ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_pointer", TheModule);

    /// create_char ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_char", TheModule);

    /// create_bool ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_bool", TheModule);

    /// create_buffer_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_buffer_object", TheModule);

    /// create_path_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_path_object", TheModule);

    /// create_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_object", TheModule);

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
    Function::Create(function_type, Function::ExternalLinkage, "create_regex_object", TheModule);

    /// create_array_object ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "create_array_object", TheModule);

    /// show_inst_in_jit ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_inst_in_jit", TheModule);

    /// show_number_in_jit ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_number_in_jit", TheModule);

    /// show_str_in_jit ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_str_in_jit", TheModule);

    /// show_stack_stat ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_stack_stat", TheModule);

    /// show_stack_in_jit ///
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

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_stack_in_jit", TheModule);

    /// call_invoke_method ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);
    param2_type = IntegerType::get(TheContext, 32);
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
    Function::Create(function_type, Function::ExternalLinkage, "call_invoke_method", TheModule);

    /// push_jit_object ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "push_jit_object", TheModule);

    /// try_function ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext,32);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext,32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param4_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "try_function", TheModule);

    /// catch_function ///
    type_params.clear();

    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "catch_function", TheModule);

    /// get_try_catch_label_name ///
    type_params.clear();

    result_type = PointerType::get(IntegerType::get(TheContext,8), 0);

    param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_try_catch_label_name", TheModule);

    /// entry_exception_object ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object", TheModule);

    /// get_field_from_object ///
    type_params.clear();
    
    result_type = PointerType::get(gCLValueAndBoolStruct, 0);

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
    Function::Create(function_type, Function::ExternalLinkage, "get_field_from_object", TheModule);

    /// regex_equals ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "regex_equals", TheModule);

    /// get_string_object_of_object_name ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_string_object_of_object_name", TheModule);

    /// object_implements_interface ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);
    
    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "object_implements_interface", TheModule);

    /// call_invoke_virtual_method ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param6_type);

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "call_invoke_virtual_method", TheModule);

    /// call_invoke_dynamic_method ///
    type_params.clear();

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

    param9_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param9_type);

    param10_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param10_type);

    param11_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param11_type);

    param12_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param12_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "call_invoke_dynamic_method", TheModule);

    /// invoke_block_in_jit ///
    type_params.clear();

    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param5_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "invoke_block_in_jit", TheModule);

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
    Function::Create(function_type, Function::ExternalLinkage, "store_field", TheModule);

    /// load_class_field ///
    type_params.clear();
    
    result_type = PointerType::get(gCLValueAndBoolStruct, 0);

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
    Function::Create(function_type, Function::ExternalLinkage, "load_class_field", TheModule);

    /// run_load_class_field_address ///
    type_params.clear();
    
    result_type = PointerType::get(gPointerAndBoolStruct, 0);

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
    Function::Create(function_type, Function::ExternalLinkage, "run_load_class_field_address", TheModule);

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
    Function::Create(function_type, Function::ExternalLinkage, "store_class_field", TheModule);

    /// load_element ///
    type_params.clear();
    
    result_type = PointerType::get(gCLValueAndBoolStruct, 0);

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
    Function::Create(function_type, Function::ExternalLinkage, "load_element", TheModule);

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
    Function::Create(function_type, Function::ExternalLinkage, "run_store_element", TheModule);

    /// get_array_length ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_array_length", TheModule);

    /// get_regex_global ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_global", TheModule);

    /// get_regex_ignorecase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_ignorecase", TheModule);

    /// get_regex_multiline ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_multiline", TheModule);

    /// get_regex_extended ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_extended", TheModule);

    /// gSigInt ///
    Type* variable_type = IntegerType::get(TheContext, 32);
    gSigIntValue = new GlobalVariable(*TheModule, variable_type, false, GlobalValue::ExternalLinkage, nullptr, "gSigInt");

    create_internal_functions2();
}

Function* create_llvm_function(const std::string& name)
{
    std::vector<Type *> params;

    Type* param1_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    params.push_back(param1_type);
    Type* param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    params.push_back(param2_type);
    Type* param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    params.push_back(param3_type);
    Type* param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    params.push_back(param4_type);
    Type* param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    params.push_back(param5_type);
    Type* param6_type = IntegerType::get(TheContext, 32);
    params.push_back(param6_type);
    Type* param7_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    params.push_back(param7_type);
    Type* param8_type = PointerType::get(IntegerType::get(TheContext,64), 0);
    params.push_back(param8_type);

    Type* result_type = IntegerType::get(TheContext, 32);
    FunctionType* function_type = FunctionType::get(result_type, params, false);

    Function* function = Function::Create(function_type, Function::ExternalLinkage, name, TheModule);
    std::vector<std::string> args;

    std::string stack_ptr_name("stack_ptr");
    args.push_back(stack_ptr_name);
    std::string lvar_name("lvar");
    args.push_back(lvar_name);
    std::string info_name("info");
    args.push_back(info_name);
    std::string stack_name("stack");
    args.push_back(stack_name);
    std::string stack_ptr_address_name("stack_ptr_address");
    args.push_back(stack_ptr_address_name);
    std::string var_num_name("var_num");
    args.push_back(var_num_name);
    std::string constant_name("constant");
    args.push_back(constant_name);
    std::string code_name("code");
    args.push_back(code_name);

    unsigned index = 0;
    for (auto &arg : function->args()) {
        arg.setName(args[index++]);
    }

    return function;
}


}
