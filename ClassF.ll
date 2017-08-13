; ModuleID = 'ClassF.bc'

@gSigInt = external global i32

declare i32 @create_string_object(i8*)

declare i32 @create_byte(i8)

declare i32 @create_ubyte(i8)

declare i32 @create_short(i16)

declare i32 @create_ushort(i16)

declare i32 @create_integer(i32)

declare i32 @create_uinteger(i32)

declare i32 @create_long(i64)

declare i32 @create_ulong(i64)

declare i32 @create_float(float)

declare i32 @create_double(double)

declare i32 @create_pointer(i8*)

declare i32 @create_char(i32)

declare i32 @create_bool(i32)

declare i32 @create_buffer_object(i8*, i32)

declare i32 @create_path_object(i8*)

declare i32 @create_object(i64*)

declare i32 @create_regex_object(i8*, i32, i32, i32, i32, i32, i32, i32, i32)

declare i32 @create_array_object(i64*, i32)

declare void @show_inst_in_jit(i32)

declare void @show_number_in_jit(i32)

declare void @show_str_in_jit(i8*)

declare void @show_stack_stat(i64*)

declare i32 @show_stack_in_jit(i64*, i64*, i32, i64*)

declare i32 @call_invoke_method(i64*, i64*, i64*, i32, i64**, i64*, i64*)

declare void @push_jit_object(i32)

declare void @try_function(i64*, i32, i64*)

declare void @catch_function(i64*, i64*)

declare i8* @get_try_catch_label_name(i64*)

declare void @entry_exception_object(i32, i64*)

declare i64 @get_field_from_object(i64**, i64*, i32, i64*, i32, i32)

declare i32 @regex_equals(i32, i32)

declare i32 @get_string_object_of_object_name(i32)

declare i32 @object_implements_interface(i32, i64*)

declare i32 @call_invoke_virtual_method(i32, i32, i64*, i32, i64**, i64*, i64*, i64*, i32)

declare i32 @call_invoke_dynamic_method(i32, i32, i32, i32, i32, i32, i64*, i32, i64**, i64*, i64*, i64*)

declare i32 @invoke_block_in_jit(i32, i64*, i32, i64**, i64*)

declare i32 @store_field(i64**, i64*, i32, i64*, i32, i64, i32)

declare i64 @load_class_field(i64**, i64*, i32, i64*, i32, i32, i64*)

declare i64 @run_load_class_field_address(i64**, i64*, i32, i64*, i32, i32, i64*)

declare i32 @store_class_field(i64**, i64*, i32, i64*, i32, i32, i64*, i64)

declare i64 @load_element(i64**, i64*, i32, i64*, i32, i32)

declare i32 @run_store_element(i64**, i64*, i32, i64*, i32, i32, i64)

declare i32 @get_array_length(i32)

declare i32 @get_regex_global(i32)

declare i32 @get_regex_ignorecase(i32)

declare i32 @get_regex_multiline(i32)

declare i32 @get_regex_extended(i32)

declare i32 @get_regex_dotall(i32)

declare i32 @get_regex_anchored(i32)

declare i32 @get_regex_dollar_endonly(i32)

declare i32 @get_regex_ungreedy(i32)

declare i32 @get_regex_multiline.1(i32)

declare i32 @char_uppercase(i32)

declare i32 @char_lowercase(i32)

declare i64 @run_create_array(i64**, i64*, i32, i64*, i8*, i32)

declare i64 @run_create_carray(i64**, i64*, i32, i64*, i32, i8*)

declare i64 @run_create_equalable_carray(i64**, i64*, i32, i64*, i32, i8*)

declare i64 @run_create_sortable_carray(i64**, i64*, i32, i64*, i32, i8*)

declare i64 @run_create_list(i64**, i64*, i32, i64*, i32, i8*)

declare i64 @run_create_sortable_list(i64**, i64*, i32, i64*, i32, i8*)

declare i64 @run_create_equalable_list(i64**, i64*, i32, i64*, i32, i8*)

declare i64 @run_create_tuple(i64**, i64*, i32, i64*, i32)

declare i64 @run_create_hash(i64**, i64*, i32, i64*, i32, i8*, i8*)

declare i32 @run_create_block_object(i64**, i64*, i64*, i32, i32, i32, i32, i32, i32, i32, i64*)

declare i32 @run_int_to_string_cast(i32)

declare i32 @run_long_to_string_cast(i64)

declare i32 @run_uint_to_string_cast(i32)

declare i32 @run_ulong_to_string_cast(i64)

declare i32 @run_float_to_string_cast(float)

declare i32 @run_double_to_string_cast(double)

declare i32 @run_bool_to_string_cast(i32)

declare i32 @run_regex_to_string_cast(i32)

declare i32 @run_pointer_to_string_cast(i64*)

declare i32 @run_char_to_string_cast(i32)

declare i8 @run_cbyte_to_byte_cast(i32)

declare i16 @run_cshort_to_short_cast(i32)

declare i32 @run_integer_to_int_cast(i32)

declare i32 @run_cfloat_to_int_cast(i32)

declare i32 @run_cdouble_to_int_cast(i32)

declare i64 @run_clong_to_long_cast(i32)

declare i8 @run_cubyte_to_ubyte_cast(i32)

declare i16 @run_cushort_to_ushort_cast(i32)

declare i64 @run_culong_to_ulong_cast(i32)

declare i8* @run_cpointer_to_pointer_cast(i32)

declare i32 @run_uinteger_to_uint_cast(i32)

declare float @run_cfloat_to_float_cast(i32)

declare double @run_cdouble_to_double_cast(i32)

declare i32 @entry_exception_object_with_class_name2(i64*, i64*, i32, i64*, i8*, i8*)

declare i8** @run_load_field_address(i64**, i64*, i32, i64*, i32, i32)

declare i64 @run_array_to_carray_cast(i64**, i64*, i32, i64*, i32, i8*)

declare i64* @get_class_with_load_and_initialize_in_jit(i8*)

define i32 @"ClassF.method()$$0"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num) {
entry:
  %"lvar$0$" = alloca i64
  store i64 1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method2()$$1"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num) {
entry:
  %"lvar$0$" = alloca i64
  store i64 1066192077, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method3()$$2"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num) {
entry:
  %"lvar$0$" = alloca i64
  store i64 4607632778762754458, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}
