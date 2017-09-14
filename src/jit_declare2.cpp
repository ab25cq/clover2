#include "jit_common.hpp"

extern "C"
{

void create_internal_functions2()
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

    /// get_regex_dotall ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_dotall", TheModule);

    /// get_regex_anchored ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_anchored", TheModule);

    /// get_regex_dollar_endonly ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_dollar_endonly", TheModule);

    /// get_regex_ungreedy ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_ungreedy", TheModule);

    /// get_regex_anchored ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_regex_multiline", TheModule);

    /// char_uppercase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "char_uppercase", TheModule);

    /// char_lowercase ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "char_lowercase", TheModule);

    /// run_create_array ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_array", TheModule);

    /// run_create_carray ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_carray", TheModule);

    /// run_create_equalable_carray ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_carray", TheModule);

    /// run_create_sortable_carray ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_carray", TheModule);

    /// run_create_list ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_list", TheModule);

    /// run_create_sortable_list ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_sortable_list", TheModule);

    /// run_create_equalable_list ///
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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_equalable_list", TheModule);

    /// run_create_tuple ///
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

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_tuple", TheModule);

    /// run_create_hash ///
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

    param7_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_create_hash", TheModule);

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
    Function::Create(function_type, Function::ExternalLinkage, "run_create_block_object", TheModule);

    /// run_int_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_int_to_string_cast", TheModule);

    /// run_long_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_long_to_string_cast", TheModule);

    /// run_uint_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uint_to_string_cast", TheModule);

    /// run_ulong_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 64);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_ulong_to_string_cast", TheModule);

    /// run_float_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getFloatTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_float_to_string_cast", TheModule);

    /// run_double_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = Type::getDoubleTy(TheContext);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_double_to_string_cast", TheModule);

    /// run_bool_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_bool_to_string_cast", TheModule);

    /// run_regex_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_regex_to_string_cast", TheModule);

    /// run_pointer_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_pointer_to_string_cast", TheModule);
    /// run_char_to_string_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_char_to_string_cast", TheModule);

    /// run_cbyte_to_byte_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 8);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cbyte_to_byte_cast", TheModule);

    /// run_cshort_to_short_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 16);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cshort_to_short_cast", TheModule);

    /// run_integer_to_int_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_integer_to_int_cast", TheModule);

    /// run_cfloat_to_int_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_int_cast", TheModule);

    /// run_cdouble_to_int_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_int_cast", TheModule);

    /// run_clong_to_long_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_clong_to_long_cast", TheModule);

    /// run_cubyte_to_ubyte_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 8);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cubyte_to_ubyte_cast", TheModule);

    /// run_cushort_to_ushort_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 16);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cushort_to_ushort_cast", TheModule);
    /// run_culong_to_ulong_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 64);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_culong_to_ulong_cast", TheModule);

    /// run_cpointer_to_pointer_cast ///
    type_params.clear();
    
    result_type = PointerType::get(IntegerType::get(TheContext, 8), 0);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cpointer_to_pointer_cast", TheModule);

    /// run_uinteger_to_uint_cast ///
    type_params.clear();
    
    result_type = IntegerType::get(TheContext, 32);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_uinteger_to_uint_cast", TheModule);

    /// run_cfloat_to_float_cast ///
    type_params.clear();
    
    result_type = Type::getFloatTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cfloat_to_float_cast", TheModule);

    /// run_cdouble_to_double_cast ///
    type_params.clear();
    
    result_type = Type::getDoubleTy(TheContext);

    param1_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param1_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_cdouble_to_double_cast", TheModule);

    /// entry_exception_object_with_class_name2 ///
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

    param5_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param5_type);

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "entry_exception_object_with_class_name2", TheModule);

    /// run_load_field_address ///
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

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_load_field_address", TheModule);

    /// run_array_to_carray_cast ///
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

    param6_type = PointerType::get(IntegerType::get(TheContext, 8), 0);
    type_params.push_back(param6_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "run_array_to_carray_cast", TheModule);

    /// show_method_parametor_address ///
    type_params.clear();
    
    result_type = Type::getVoidTy(TheContext);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param2_type);

    param3_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param3_type);

    param4_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param4_type);

    param5_type = PointerType::get(PointerType::get(IntegerType::get(TheContext, 64), 0), 0);
    type_params.push_back(param5_type);

    param6_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param6_type);

    param7_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param7_type);

    param8_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param8_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "show_method_parametor_address", TheModule);

    /// get_class_with_load_and_initialize_in_jit ///
    type_params.clear();
    
    result_type = PointerType::get(IntegerType::get(TheContext, 64), 0);

    param1_type = PointerType::get(IntegerType::get(TheContext, 64), 0);
    type_params.push_back(param1_type);

    param2_type = IntegerType::get(TheContext, 32);
    type_params.push_back(param2_type);

    function_type = FunctionType::get(result_type, type_params, false);
    Function::Create(function_type, Function::ExternalLinkage, "get_class_with_load_and_initialize_in_jit", TheModule);
}
}
