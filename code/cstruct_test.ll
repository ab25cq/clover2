; ModuleID = 'code/cstruct_test.bc'
source_filename = "Module code/cstruct_test.ocl"

@gSigInt = external global i32
@gVar = external global i32
@gVar2 = external global float
@gVar3 = external global double
@gVar4 = external global i64
@gVar5 = external global i8
@gVar6 = external global i8*
@gVar7 = external global [3 x i8]
@gVar8 = external global [3 x i32]
@gVar9 = external global [2 x i64]
@gCodeData = global [112 x i8] c"\0F\00\00\00\10\00\00\00\00\00\00\00\01\00\00\00+#\00\00\18\00\00\00\11\00\00\00$\00\00\00\01\00\00\00\B8\0B\00\00<\00\00\00\00\00\00\00 \00\00\00\12\00\00\00\01\00\00\00\0F\00\00\00\10\00\00\00@\00\00\00\03\00\00\00\11\00\00\00X\00\00\00\03\00\00\00\B8\0B\00\00p\00\00\00\05\00\00\00 \00\00\00\12\00\00\00\01\00\00\00", align 1
@gConstData = global [124 x i8] c"code/cstruct_test.cl\00\00\00\00HELLO WORLD\00code/cstruct_test.cl\00\00\00\00C\00\00\00code/cstruct_test.cl\00\00\00\00code/cstruct_test.cl\00\00\00\00CStructTest\00", align 1
@global_string = private constant [21 x i8] c"code/cstruct_test.cl\00", align 1
@global_string.2 = private constant [12 x i8] c"HELLO WORLD\00", align 1
@global_string.3 = private constant [21 x i8] c"code/cstruct_test.cl\00", align 1
@global_string.4 = private constant [10 x i8] c"Exception\00", align 1
@global_string.5 = private constant [17 x i8] c"Signal Interrupt\00", align 1
@global_string.6 = private constant [21 x i8] c"code/cstruct_test.cl\00", align 1
@global_string.7 = private constant [21 x i8] c"code/cstruct_test.cl\00", align 1
@global_string.8 = private constant [12 x i8] c"CStructTest\00", align 1
@global_string.9 = private constant [10 x i8] c"Exception\00", align 1
@global_string.10 = private constant [17 x i8] c"Signal Interrupt\00", align 1

declare void @entry_exception_object(i32, i64*)

declare i32 @entry_exception_object_with_class_name2(i64**, i64*, i32, i64*, i8*, i8*)

declare void @inc_andand_oror_array(i64*)

declare void @dec_andand_oror_array(i64*)

declare void @set_andand_oror_right_value(i32, i64*)

declare i32 @get_andand_oror_right_value(i64*)

declare void @set_andand_oror_left_value(i32, i64*)

declare i32 @get_andand_oror_left_value(i64*)

declare i64* @get_class_with_load_and_initialize(i8*, i32)

declare i8* @get_try_catch_label_name(i64*)

declare void @try_function(i64*, i32, i32, i64*, i64*)

declare i32 @call_invoke_method(i64*, i32, i64*, i32, i64**, i64*)

declare void @mark_source_position(i64*, i8*, i32)

declare void @mark_source_position2(i64*, i8*, i32)

declare i32 @get_field_from_object(i64**, i64*, i32, i64*, i32, i32, i64*)

declare i32 @create_array_object(i64*, i32, i64*)

declare i32 @create_object(i64*, i8*, i64*)

declare i32 @store_field(i64**, i64*, i32, i64*, i32, i64, i32, i32, i64*, i64*)

declare void @try_end_function(i64*, i32, i32, i64*, i64*)

declare i32 @run_store_to_buffer(i32, i8*, i64**, i64*, i32, i64*)

declare i32 @split_tuple(i64**, i64*, i32, i32, i64*, i32)

declare i32 @call_invoke_virtual_method(i32, i64*, i32, i64**, i64*, i64*, i32, i32, i32, i32)

declare i32 @call_invoke_dynamic_method(i32, i32, i32, i32, i32, i32, i64*, i32, i64**, i64*, i64*, i64*)

declare i32 @invoke_block(i32, i64*, i32, i32, i64**, i64*)

declare i32 @run_load_field_address(i64**, i64*, i32, i64*, i32, i32, i64*)

declare i32 @store_field_of_buffer(i64**, i64*, i32, i64*, i32, i64, i32, i64*)

declare i32 @load_class_field(i64**, i64*, i32, i64*, i32, i32, i64*, i64*)

declare i32 @run_load_class_field_address(i64**, i64*, i32, i64*, i32, i32, i64*, i64*)

declare i32 @store_class_field(i64**, i64*, i32, i64*, i32, i32, i64*, i64)

declare i32 @store_class_field_of_buffer(i64**, i64*, i32, i64*, i32, i32, i64*, i64)

declare i32 @get_string_object_of_object_name(i32, i64*)

declare i32 @get_object_allocated_size(i32)

declare i32 @op_is_fun(i32, i32)

declare i32 @object_implements_interface(i32, i64*)

declare i32 @load_element(i64**, i64*, i32, i64*, i32, i32, i64*)

declare i32 @run_store_element(i64**, i64*, i32, i64*, i32, i32, i64)

declare i32 @run_store_element_of_buffer(i64**, i64*, i32, i64*, i32, i32, i64)

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

declare i32 @create_string_object(i8*, i64*)

declare i32 @run_op_string_with_string_expression(i8*, i32*, i32, i64**, i64*)

declare i32 @run_op_buffer_with_string_expression(i8*, i32*, i32, i64**, i64*)

declare i32 @run_op_path_with_string_expression(i8*, i32*, i32, i64**, i64*)

declare i32 @create_buffer_object(i8*, i32, i64*)

declare i32 @create_path_object(i8*, i64*)

declare i32 @run_create_array(i64**, i64*, i32, i64*, i32, i32, i64*, i64*)

declare i32 @run_create_carray(i64**, i64*, i32, i64*, i32, i32, i32, i64*, i64*)

declare i32 @run_create_equalable_carray(i64**, i64*, i32, i64*, i32, i32, i32, i64*, i64*)

declare i32 @run_create_list(i64**, i64*, i32, i64*, i32, i32, i32, i64*, i64*)

declare i32 @run_create_sortable_list(i64**, i64*, i32, i64*, i32, i32, i32, i64*, i64*)

declare i32 @run_create_equalable_list(i64**, i64*, i32, i64*, i32, i32, i32, i64*, i64*)

declare i32 @run_create_tuple(i64**, i64*, i32, i64*, i32, i8*, i64*)

declare i32 @run_create_hash(i64**, i64*, i32, i64*, i32, i32, i32, i32, i64*, i64*)

declare i32 @run_create_block_object(i64**, i64*, i64*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i64*, i32, i64*)

declare i32 @create_regex_object(i8*, i32, i32, i32, i32, i32, i32, i32, i32, i64*)

declare i32 @run_op_regex_with_string_expression(i8*, i32*, i32, i64**, i64*, i32, i32, i32, i32, i32, i32, i32, i32)

declare i32 @run_int_to_string_cast(i32, i64*)

declare i32 @run_long_to_string_cast(i64, i64*)

declare i32 @run_uint_to_string_cast(i32, i64*)

declare i32 @run_ulong_to_string_cast(i64, i64*)

declare i32 @run_float_to_string_cast(float, i64*)

declare i32 @run_double_to_string_cast(double, i64*)

declare i32 @run_bool_to_string_cast(i32, i64*)

declare i32 @run_regex_to_string_cast(i32, i64*)

declare i32 @run_pointer_to_string_cast(i8*, i64*)

declare i32 @run_char_to_string_cast(i32, i64*)

declare i32 @create_integer(i32, i64*)

declare i32 @create_uinteger(i32, i64*)

declare i32 @create_long(i64, i64*)

declare i32 @create_ulong(i64, i64*)

declare i32 @create_float(float, i64*)

declare i32 @create_double(double, i64*)

declare i32 @create_pointer(i8*, i64*)

declare i32 @create_char(i32, i64*)

declare i32 @create_bool(i32, i64*)

declare i32 @create_byte(i8, i64*)

declare i32 @create_ubyte(i8, i64*)

declare i32 @create_short(i16, i64*)

declare i32 @create_ushort(i16, i64*)

declare i32 @run_array_to_carray_cast(i64**, i64*, i32, i64*, i32, i8*, i64*)

declare i8* @run_array_to_clang_array_cast(i32, i64*)

declare i8* @run_buffer_to_pointer_cast(i32, i64*)

declare i8 @run_cbyte_to_byte_cast(i32)

declare i8 @run_cubyte_to_ubyte_cast(i32)

declare i16 @run_cshort_to_short_cast(i32)

declare i16 @run_cushort_to_ushort_cast(i32)

declare i32 @run_integer_to_int_cast(i32)

declare i32 @run_uinteger_to_uint_cast(i32)

declare i64 @run_clong_to_long_cast(i32)

declare i64 @run_culong_to_ulong_cast(i32)

declare float @run_cfloat_to_float_cast(i32)

declare double @run_cdouble_to_double_cast(i32)

declare void @print_value(i64)

declare void @print_str_value(i8*)

declare i32 @regex_equals(i32, i32)

declare i32 @run_create_sortable_carray(i64**, i64*, i32, i64*, i32, i32, i32, i64*, i64*)

declare i8* @get_object_head_of_memory(i32, i32)

declare void @show_vm_stack(i64*, i64**, i64*, i32)

declare void @push_value_to_global_stack(i64, i64*)

declare void @initialize_code_and_constant(i64*, i64*, i8*, i32, i8*, i32)

declare void @entry_jit_funcs(i8*, i32)

declare i32 @convert_i64array_to_struct(i8*, i64*, i64*)

declare i32 @puts(i8*)

declare i32 @strcmp(i8*, i8*)

declare void @fun([2 x i64])

declare void @fun2(i8*)

declare void @fun3(i32, i32)

declare void @fun4(i8*)

declare void @fun5([2 x i64])

declare i8* @fun6()

declare [2 x i64] @fun7()

declare void @fun8(i8*)

declare i32 @fun9(i32, i32)

declare i32 @fun10(i32)

declare void @fun11()

declare void @fun12(i8)

declare void @fun13(i32*)

declare void @fun14(i32*)

declare void @fun15(i8*)

declare void @fun16([2 x i64])

define i32 @clover2_main(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code, i64** %global_stack_ptr_address, i64* %stack_plus_var_num) {
entry:
  call void @initialize_code_and_constant(i64* %code, i64* %constant, i8* getelementptr inbounds ([112 x i8], [112 x i8]* @gCodeData, i32 0, i32 0), i32 112, i8* getelementptr inbounds ([124 x i8], [124 x i8]* @gConstData, i32 0, i32 0), i32 124)
  store i32 0, i32* @gSigInt
  call void @mark_source_position(i64* %info, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string, i32 0, i32 0), i32 1)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  store i64 ptrtoint ([12 x i8]* @global_string.2 to i64), i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %"inc_ptr_value(1)" = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %"inc_ptr_value(1)", i64** %stack_ptr_address
  call void @mark_source_position2(i64* %info, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string.3, i32 0, i32 0), i32 1)
  %0 = call i32 @puts(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.2, i32 0, i32 0))
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %"inc_ptr_value(1)3" = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 -1
  store i64* %"inc_ptr_value(1)3", i64** %stack_ptr_address
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value4, align 8
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %loaded_stack_ptr_address_value4, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %"inc_ptr_value(1)6" = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %"inc_ptr_value(1)6", i64** %stack_ptr_address
  %sig_int_value = load i32, i32* @gSigInt, align 4
  %2 = trunc i32 %sig_int_value to i1
  br i1 %2, label %sigint_then_block, label %entry_after_sigint

sigint_then_block:                                ; preds = %entry
  store i32 0, i32* @gSigInt
  %3 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.4, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @global_string.5, i32 0, i32 0))
  ret i32 0

entry_after_sigint:                               ; preds = %entry
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %"inc_ptr_value(1)8" = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 -1
  store i64* %"inc_ptr_value(1)8", i64** %stack_ptr_address
  store i32 0, i32* @gSigInt
  call void @mark_source_position(i64* %info, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string.6, i32 0, i32 0), i32 3)
  call void @mark_source_position2(i64* %info, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @global_string.7, i32 0, i32 0), i32 3)
  %4 = call i64* @get_class_with_load_and_initialize(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_string.8, i32 0, i32 0), i32 0)
  %ifcond = icmp eq i64* %4, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_after_sigint
  ret i32 0

entry_ifend:                                      ; preds = %entry_after_sigint
  %5 = call i32 @call_invoke_method(i64* %4, i32 5, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %5, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend
  %6 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %6, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

entry_ifend11:                                    ; preds = %entry_ifend
  %loaded_stack_ptr_address_value12 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value12, i64 -1
  %stack_pointer_offset_value13 = load i64, i64* %stack_pointer_offset_value, align 8
  %trunc_variable = trunc i64 %stack_pointer_offset_value13 to i32
  %sig_int_value14 = load i32, i32* @gSigInt, align 4
  %7 = trunc i32 %sig_int_value14 to i1
  br i1 %7, label %sigint_then_block15, label %entry_after_sigint16

then_block_b:                                     ; preds = %then_block10
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block10
  ret i32 0

sigint_then_block15:                              ; preds = %entry_ifend11
  store i32 0, i32* @gSigInt
  %8 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @global_string.9, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @global_string.10, i32 0, i32 0))
  ret i32 0

entry_after_sigint16:                             ; preds = %entry_ifend11
  %loaded_stack_ptr_address_value17 = load i64*, i64** %stack_ptr_address
  %"inc_ptr_value(1)18" = getelementptr i64, i64* %loaded_stack_ptr_address_value17, i64 -1
  store i64* %"inc_ptr_value(1)18", i64** %stack_ptr_address
  ret i32 1
}
