; ModuleID = 'Module JITTest'

%clvalue_and_bool_struct = type { i64, i32 }
%pointer_and_bool_struct = type { i8*, i32 }

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

declare i32 @call_invoke_method(i64*, i32, i64*, i32, i64**, i64*)

declare void @push_jit_object(i32)

declare void @try_function(i64*, i32, i32, i64*, i64*)

declare void @catch_function(i64*, i64*)

declare i8* @get_try_catch_label_name(i64*)

declare void @entry_exception_object(i32, i64*)

declare %clvalue_and_bool_struct* @get_field_from_object(i64**, i64*, i32, i64*, i32, i32)

declare i32 @regex_equals(i32, i32)

declare i32 @get_string_object_of_object_name(i32)

declare i32 @object_implements_interface(i32, i64*)

declare i32 @call_invoke_virtual_method(i32, i64*, i32, i64**, i64*, i64*, i32)

declare i32 @call_invoke_dynamic_method(i32, i32, i32, i32, i32, i32, i64*, i32, i64**, i64*, i64*, i64*)

declare i32 @invoke_block_in_jit(i32, i64*, i32, i64**, i64*)

declare i32 @store_field(i64**, i64*, i32, i64*, i32, i64, i32)

declare %clvalue_and_bool_struct* @load_class_field(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %pointer_and_bool_struct* @run_load_class_field_address(i64**, i64*, i32, i64*, i32, i32, i64*)

declare i32 @store_class_field(i64**, i64*, i32, i64*, i32, i32, i64*, i64)

declare %clvalue_and_bool_struct* @load_element(i64**, i64*, i32, i64*, i32, i32)

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

declare %clvalue_and_bool_struct* @run_create_array(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %clvalue_and_bool_struct* @run_create_carray(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %clvalue_and_bool_struct* @run_create_equalable_carray(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %clvalue_and_bool_struct* @run_create_sortable_carray(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %clvalue_and_bool_struct* @run_create_list(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %clvalue_and_bool_struct* @run_create_sortable_list(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %clvalue_and_bool_struct* @run_create_equalable_list(i64**, i64*, i32, i64*, i32, i32, i64*)

declare %clvalue_and_bool_struct* @run_create_tuple(i64**, i64*, i32, i64*, i32)

declare %clvalue_and_bool_struct* @run_create_hash(i64**, i64*, i32, i64*, i32, i32, i32, i64*)

declare i32 @run_create_block_object(i64**, i64*, i64*, i32, i32, i32, i32, i32, i32, i32, i64*)

declare i32 @run_int_to_string_cast(i32)

declare i32 @run_long_to_string_cast(i64)

declare i32 @run_uint_to_string_cast(i32)

declare i32 @run_ulong_to_string_cast(i64)

declare i32 @run_float_to_string_cast(float)

declare i32 @run_double_to_string_cast(double)

declare i32 @run_bool_to_string_cast(i32)

declare i32 @run_regex_to_string_cast(i32)

declare i32 @run_pointer_to_string_cast(i8*)

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

declare i32 @entry_exception_object_with_class_name2(i64**, i64*, i32, i64*, i8*, i8*)

declare %pointer_and_bool_struct* @run_load_field_address(i64**, i64*, i32, i64*, i32, i32)

declare %clvalue_and_bool_struct* @run_array_to_carray_cast(i64**, i64*, i32, i64*, i32, i8*)

declare i64* @get_class_with_load_and_initialize_in_jit(i8*)

define i32 @"JITTest.run()$$1"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run2()$$2"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45642528 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run3()$$3"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45642532 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642544 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %2 = zext i32 %0 to i64
  store i64 %2, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %3 = call i32 @call_invoke_method(i64* %1, i32 21, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond3 = icmp ne i32 %3, 1
  br i1 %ifcond3, label %then_block4, label %entry_ifend5

then_block4:                                      ; preds = %entry_ifend
  %4 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend5:                                     ; preds = %entry_ifend
  %stack_offset_value6 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value6, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 -1
  %stack_pointer_offset_value8 = load i64, i64* %stack_pointer_offset_value, align 8
  %5 = trunc i64 %stack_pointer_offset_value8 to i32
  call void @push_jit_object(i32 %5)
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run4()$$4"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642552 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %1 = call i32 @call_invoke_method(i64* %0, i32 4, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond2 = icmp ne i32 %1, 1
  br i1 %ifcond2, label %then_block3, label %entry_ifend4

then_block3:                                      ; preds = %entry_ifend
  %2 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend4:                                     ; preds = %entry_ifend
  %stack_offset_value5 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value5, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value, i64 -1
  %stack_pointer_offset_value6 = load i64, i64* %stack_pointer_offset_value, align 8
  %3 = trunc i64 %stack_pointer_offset_value6 to i32
  call void @push_jit_object(i32 %3)
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  %addtmp = add nuw i32 %3, 3
  %4 = zext i32 %addtmp to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run5()$$5"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642568 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  store i64 1, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 2, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value5 = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 1
  store i64* %inc_ptr_value5, i64** %stack_ptr_address
  %1 = call i32 @call_invoke_method(i64* %0, i32 5, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond6 = icmp ne i32 %1, 1
  br i1 %ifcond6, label %then_block7, label %entry_ifend8

then_block7:                                      ; preds = %entry_ifend
  %2 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend8:                                     ; preds = %entry_ifend
  %stack_offset_value9 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value9, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value10 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value10, i64 -1
  %stack_pointer_offset_value11 = load i64, i64* %stack_pointer_offset_value, align 8
  %3 = trunc i64 %stack_pointer_offset_value11 to i32
  call void @push_jit_object(i32 %3)
  %loaded_stack_ptr_address_value12 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value12, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value11, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run6()$$6"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45642584 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642592 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %2 = zext i32 %0 to i64
  store i64 %2, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %3 = call i32 @call_invoke_method(i64* %1, i32 28, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond3 = icmp ne i32 %3, 1
  br i1 %ifcond3, label %then_block4, label %entry_ifend5

then_block4:                                      ; preds = %entry_ifend
  %4 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend5:                                     ; preds = %entry_ifend
  %stack_offset_value6 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value6, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 -1
  %stack_pointer_offset_value8 = load i64, i64* %stack_pointer_offset_value, align 8
  %5 = trunc i64 %stack_pointer_offset_value8 to i32
  call void @push_jit_object(i32 %5)
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run7()$$7"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 124, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.method()$$8"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45642600 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run8()$$9"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = trunc i64 %stack_offset_value to i32
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642604 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %then_block23, %entry_ifend6, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %2 = zext i32 %0 to i64
  store i64 %2, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %3 = call i32 @call_invoke_method(i64* %1, i32 8, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond4 = icmp ne i32 %3, 1
  br i1 %ifcond4, label %then_block5, label %entry_ifend6

then_block5:                                      ; preds = %entry_ifend
  %4 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend6:                                     ; preds = %entry_ifend
  %stack_offset_value7 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value7, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value8 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value8, i64 -1
  %stack_pointer_offset_value9 = load i64, i64* %stack_pointer_offset_value, align 8
  %5 = trunc i64 %stack_pointer_offset_value9 to i32
  call void @push_jit_object(i32 %5)
  %loaded_stack_ptr_address_value10 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value10, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  %6 = call i32 @create_string_object(i8* inttoptr (i64 45642612 to i8*))
  call void @push_jit_object(i32 %6)
  %7 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642616 to i8*))
  %ifcond13 = icmp eq i64* %7, null
  br i1 %ifcond13, label %then_block, label %entry_ifend12

entry_ifend12:                                    ; preds = %entry_ifend6
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value7, i64* %lvar, align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value16, align 8
  store i64 %stack_pointer_offset_value9, i64* %loaded_stack_ptr_address_value16, align 8
  %loaded_stack_ptr_address_value17 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value18 = getelementptr i64, i64* %loaded_stack_ptr_address_value17, i64 1
  store i64* %inc_ptr_value18, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value18, align 8
  %8 = zext i32 %6 to i64
  store i64 %8, i64* %inc_ptr_value18, align 8
  %loaded_stack_ptr_address_value20 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value21 = getelementptr i64, i64* %loaded_stack_ptr_address_value20, i64 1
  store i64* %inc_ptr_value21, i64** %stack_ptr_address
  %9 = call i32 @call_invoke_method(i64* %7, i32 8, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond22 = icmp ne i32 %9, 1
  br i1 %ifcond22, label %then_block23, label %entry_ifend24

then_block23:                                     ; preds = %entry_ifend12
  %10 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend24:                                    ; preds = %entry_ifend12
  %stack_offset_value28 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value28, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value29 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value30 = getelementptr i64, i64* %loaded_stack_ptr_address_value29, i64 -1
  %stack_pointer_offset_value31 = load i64, i64* %stack_pointer_offset_value30, align 8
  %11 = trunc i64 %stack_pointer_offset_value31 to i32
  call void @push_jit_object(i32 %11)
  %loaded_stack_ptr_address_value32 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value33 = getelementptr i64, i64* %loaded_stack_ptr_address_value32, i64 1
  store i64* %dec_ptr_value33, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value31, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run9()$$10"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642624 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642640 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value8 = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value8, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %4, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend11:                                    ; preds = %entry_ifend2
  %stack_offset_value12 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value12, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 -1
  %stack_pointer_offset_value14 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value14 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value15 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value15, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value14, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run10()$$11"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642656 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 45642668 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642680 to i8*))
  %ifcond3 = icmp eq i64* %3, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value8 = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value8, i64** %stack_ptr_address
  %6 = call i32 @call_invoke_method(i64* %3, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %6, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend2
  %7 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend11:                                    ; preds = %entry_ifend2
  %stack_offset_value12 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value12, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 -1
  %stack_pointer_offset_value14 = load i64, i64* %stack_pointer_offset_value, align 8
  %8 = trunc i64 %stack_pointer_offset_value14 to i32
  call void @push_jit_object(i32 %8)
  %loaded_stack_ptr_address_value15 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value15, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value14, i64* %stack
  call void @entry_exception_object(i32 %8, i64* %info)
  ret i32 0
}

define i32 @"JITTest.method2()$$12"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642692 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 45642704 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642716 to i8*))
  %ifcond3 = icmp eq i64* %3, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value8 = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value8, i64** %stack_ptr_address
  %6 = call i32 @call_invoke_method(i64* %3, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %6, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend2
  %7 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend11:                                    ; preds = %entry_ifend2
  %stack_offset_value12 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value12, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 -1
  %stack_pointer_offset_value14 = load i64, i64* %stack_pointer_offset_value, align 8
  %8 = trunc i64 %stack_pointer_offset_value14 to i32
  call void @push_jit_object(i32 %8)
  %loaded_stack_ptr_address_value15 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value15, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value14, i64* %stack
  call void @entry_exception_object(i32 %8, i64* %info)
  ret i32 0
}

define i32 @"JITTest.run11()$$13"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45642728 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642744 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %then_block25, %entry_ifend7, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value3 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value3, align 8
  store i64 0, i64* %lvar_offset_value3, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %2 = zext i32 %0 to i64
  store i64 %2, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %3 = call i32 @call_invoke_method(i64* %1, i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond5 = icmp ne i32 %3, 1
  br i1 %ifcond5, label %then_block6, label %entry_ifend7

then_block6:                                      ; preds = %entry_ifend
  %4 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend7:                                     ; preds = %entry_ifend
  %stack_offset_value8 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value8, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value9 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value9, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value10 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value10, i64 -1
  %stack_pointer_offset_value11 = load i64, i64* %stack_pointer_offset_value, align 8
  %5 = trunc i64 %stack_pointer_offset_value11 to i32
  call void @push_jit_object(i32 %5)
  %loaded_stack_ptr_address_value12 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value12, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i32 0, i32* @gSigInt
  call void @try_function(i64* %info, i32 9424, i32 92, i64* %code, i64* %constant)
  store i32 0, i32* @gSigInt
  %6 = trunc i64 %stack_offset_value8 to i32
  %7 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45642768 to i8*))
  %ifcond16 = icmp eq i64* %7, null
  br i1 %ifcond16, label %then_block, label %entry_ifend15

entry_ifend15:                                    ; preds = %entry_ifend7
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value8, i64* %lvar, align 8
  store i64 0, i64* %lvar_offset_value3, align 8
  store i64 %stack_offset_value9, i64* %lvar_offset_value3, align 8
  %loaded_stack_ptr_address_value21 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value21, align 8
  %8 = zext i32 %6 to i64
  store i64 %8, i64* %loaded_stack_ptr_address_value21, align 8
  %loaded_stack_ptr_address_value22 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value23 = getelementptr i64, i64* %loaded_stack_ptr_address_value22, i64 1
  store i64* %inc_ptr_value23, i64** %stack_ptr_address
  %9 = call i32 @call_invoke_method(i64* %7, i32 12, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond24 = icmp ne i32 %9, 1
  br i1 %ifcond24, label %then_block25, label %entry_ifend26

then_block25:                                     ; preds = %entry_ifend15
  %10 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend26:                                    ; preds = %entry_ifend15
  %stack_offset_value30 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value30, i64* %"lvar$0$", align 8
  %stack_offset_value32 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value32, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value33 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value34 = getelementptr i64, i64* %loaded_stack_ptr_address_value33, i64 -1
  %stack_pointer_offset_value35 = load i64, i64* %stack_pointer_offset_value34, align 8
  %11 = trunc i64 %stack_pointer_offset_value35 to i32
  call void @push_jit_object(i32 %11)
  %loaded_stack_ptr_address_value36 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value37 = getelementptr i64, i64* %loaded_stack_ptr_address_value36, i64 1
  store i64* %dec_ptr_value37, i64** %stack_ptr_address
  call void @try_function(i64* %info, i32 0, i32 0, i64* %code, i64* %constant)
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run11_5()$$14"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 1, i64* %"lvar$2$", align 8
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run12()$$15"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 1, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run13()$$16"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i32 0, i32* @gSigInt
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run14()$$17"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  br label %entry_condend

entry_condend:                                    ; preds = %entry_condend, %entry
  %lvar913 = phi i64 [ 0, %entry ], [ %1, %entry_condend ]
  store i32 0, i32* @gSigInt
  %0 = trunc i64 %lvar913 to i32
  %addtmp = add nuw i32 %0, 1
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %addtmp to i64
  store i64 %1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %2 = trunc i64 %1 to i32
  %eqtmpx = icmp eq i32 %2, 1
  br i1 %eqtmpx, label %entry_condend4, label %entry_condend

entry_condend4:                                   ; preds = %entry_condend
  store i32 0, i32* @gSigInt
  store i32 0, i32* @gSigInt
  %3 = trunc i64 %1 to i32
  %4 = zext i32 %3 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run15()$$18"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  br label %while_start_pointe

while_start_pointe:                               ; preds = %entry_condend, %entry
  %lvar2 = phi i64 [ %2, %entry_condend ], [ 0, %entry ]
  %lvar3 = phi i64 [ %3, %entry_condend ], [ 0, %entry ]
  %0 = trunc i64 %lvar3 to i32
  %letmp = icmp slt i32 %0, 3
  store i32 0, i32* @gSigInt
  %1 = trunc i64 %lvar2 to i32
  br i1 %letmp, label %entry_condend, label %label_whilee

entry_condend:                                    ; preds = %while_start_pointe
  %addtmp = add nuw i32 %1, 1
  store i64 0, i64* %"lvar$1$"
  %2 = zext i32 %addtmp to i64
  store i64 %2, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %addtmp4 = add nuw i32 %0, 1
  store i64 0, i64* %"lvar$2$"
  %3 = zext i32 %addtmp4 to i64
  store i64 %3, i64* %"lvar$2$", align 8
  br label %while_start_pointe

label_whilee:                                     ; preds = %while_start_pointe
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run16()$$19"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  br label %for_start_pointf

for_start_pointf:                                 ; preds = %entry_condend, %entry
  %lvar2 = phi i64 [ %2, %entry_condend ], [ 0, %entry ]
  %lvar3 = phi i64 [ %3, %entry_condend ], [ 0, %entry ]
  %0 = trunc i64 %lvar3 to i32
  %letmp = icmp slt i32 %0, 3
  store i32 0, i32* @gSigInt
  %1 = trunc i64 %lvar2 to i32
  br i1 %letmp, label %entry_condend, label %label_for_endf

entry_condend:                                    ; preds = %for_start_pointf
  %addtmp = add nuw i32 %1, 1
  store i64 0, i64* %"lvar$1$"
  %2 = zext i32 %addtmp to i64
  store i64 %2, i64* %"lvar$1$", align 8
  %addtmp4 = add nuw i32 %0, 1
  store i64 0, i64* %"lvar$2$"
  %3 = zext i32 %addtmp4 to i64
  store i64 %3, i64* %"lvar$2$", align 8
  br label %for_start_pointf

label_for_endf:                                   ; preds = %for_start_pointf
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run17()$$20"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %VALUE_FOR_ANDAND_OROR = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 1, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 2, i64* %"lvar$1$", align 8
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i32 0, i32* @gSigInt
  %0 = trunc i64 2 to i32
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run18()$$21"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %VALUE_FOR_ANDAND_OROR = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 1, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run19()$$22"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = trunc i64 %stack_offset_value to i32
  %1 = call %clvalue_and_bool_struct* @get_field_from_object(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %0, i32 0)
  %2 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %1, i32 0, i32 0
  %3 = load i64, i64* %2, align 4
  %4 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %1, i32 0, i32 1
  %5 = load i32, i32* %4, align 4
  %ifcond = icmp eq i32 %5, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %6 = trunc i64 %3 to i32
  %7 = zext i32 %6 to i64
  store i64 %7, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run20()$$23"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643260 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run21()$$24"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643264 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_regex_object(i8* inttoptr (i64 45643268 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @regex_equals(i32 %0, i32 %1)
  %3 = zext i32 %2 to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run22()$$25"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643272 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_regex_object(i8* inttoptr (i64 45643276 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @regex_equals(i32 %0, i32 %1)
  %bool_value_reverse = icmp eq i32 %2, 0
  %3 = zext i1 %bool_value_reverse to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run23()$$26"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 2, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run24()$$27"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run25()$$28"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 123, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 246, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run26()$$29"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 23, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 100, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run27()$$30"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 2, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run28()$$31"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 9, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 3, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run29()$$32"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 5, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 3, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run30()$$33"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run31()$$34"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run32()$$35"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run33()$$36"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run34()$$37"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 6, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run35()$$38"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run36()$$39"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 254, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run37()$$40"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4294967294, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run38()$$41"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4612136378497499136, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run39()$$42"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4612136378497499136, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run40()$$43"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4616189618054758400, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run41()$$44"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run42()$$45"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run43()$$46"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run44()$$47"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run45()$$48"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run46()$$49"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run47()$$50"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run48()$$51"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run49()$$52"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run49_5(pointer)$$53"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value1 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = inttoptr i64 %stack_offset_value1 to i8*
  %addtmp = getelementptr i8, i8* %0, i32 1
  store i64 0, i64* %"lvar$1$"
  %1 = ptrtoint i8* %addtmp to i64
  store i64 %1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %2 = inttoptr i64 %1 to i8*
  %addtmp4 = getelementptr i8, i8* %2, i64 2
  store i64 0, i64* %"lvar$1$"
  %3 = ptrtoint i8* %addtmp4 to i64
  store i64 %3, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run50()$$54"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45643280 to i8*))
  call void @push_jit_object(i32 %0)
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %2 = trunc i64 %1 to i32
  %ifcond = icmp eq i32 %2, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  %3 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* inttoptr (i64 18177632 to i8*), i8* inttoptr (i64 16039682 to i8*))
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %4 = call i32 @get_string_object_of_object_name(i32 %2)
  call void @push_jit_object(i32 %4)
  %5 = zext i32 %4 to i64
  store i64 %5, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run51()$$55"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45643284 to i8*))
  call void @push_jit_object(i32 %0)
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %2 = trunc i64 %1 to i32
  %ifcond = icmp eq i32 %2, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  %3 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* inttoptr (i64 18177632 to i8*), i8* inttoptr (i64 16039682 to i8*))
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %4 = call i32 @get_string_object_of_object_name(i32 %2)
  call void @push_jit_object(i32 %4)
  %5 = call i32 @create_string_object(i8* inttoptr (i64 45643288 to i8*))
  call void @push_jit_object(i32 %5)
  %6 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643296 to i8*))
  %ifcond4 = icmp eq i64* %6, null
  br i1 %ifcond4, label %then_block2, label %entry_ifend3

then_block2:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend3:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value7 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value7, align 8
  store i64 %1, i64* %lvar_offset_value7, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %7 = zext i32 %4 to i64
  store i64 %7, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value8 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value8, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %8 = zext i32 %5 to i64
  store i64 %8, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value10 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value11 = getelementptr i64, i64* %loaded_stack_ptr_address_value10, i64 1
  store i64* %inc_ptr_value11, i64** %stack_ptr_address
  %9 = call i32 @call_invoke_method(i64* %6, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond12 = icmp ne i32 %9, 1
  br i1 %ifcond12, label %then_block13, label %entry_ifend14

then_block13:                                     ; preds = %entry_ifend3
  %10 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend14:                                    ; preds = %entry_ifend3
  %stack_offset_value15 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value15, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value16 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value16, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value17 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value17, i64 -1
  %stack_pointer_offset_value18 = load i64, i64* %stack_pointer_offset_value, align 8
  %11 = trunc i64 %stack_pointer_offset_value18 to i32
  call void @push_jit_object(i32 %11)
  %loaded_stack_ptr_address_value19 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value19, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value18, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run52()$$56"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45643304 to i8*))
  call void @push_jit_object(i32 %0)
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %2 = trunc i64 %1 to i32
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643308 to i8*))
  %ifcond = icmp eq i64* %3, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %ifcond4 = icmp eq i32 %2, 0
  br i1 %ifcond4, label %then_block2, label %entry_ifend3

then_block2:                                      ; preds = %entry_ifend
  %4 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* inttoptr (i64 18177632 to i8*), i8* inttoptr (i64 16039708 to i8*))
  ret i32 0

entry_ifend3:                                     ; preds = %entry_ifend
  %5 = call i32 @object_implements_interface(i32 %2, i64* %3)
  %6 = zext i32 %5 to i64
  store i64 %6, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run53()$$57"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643316 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %then_block28, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643332 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond8 = icmp ne i32 %4, 1
  br i1 %ifcond8, label %then_block9, label %entry_ifend10

then_block9:                                      ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend10:                                    ; preds = %entry_ifend2
  %stack_offset_value11 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value11, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value12 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value12, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 -1
  %stack_pointer_offset_value14 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value14 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value15 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value15, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value14, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value11, i64* %lvar, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 %stack_pointer_offset_value14, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value21 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value21, align 8
  %7 = zext i32 %6 to i64
  store i64 %7, i64* %loaded_stack_ptr_address_value21, align 8
  %loaded_stack_ptr_address_value22 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value23 = getelementptr i64, i64* %loaded_stack_ptr_address_value22, i64 1
  store i64* %inc_ptr_value23, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value23, align 8
  store i64 123, i64* %inc_ptr_value23, align 8
  %loaded_stack_ptr_address_value25 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value26 = getelementptr i64, i64* %loaded_stack_ptr_address_value25, i64 1
  store i64* %inc_ptr_value26, i64** %stack_ptr_address
  %8 = call i32 @call_invoke_virtual_method(i32 10020, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %constant, i32 %6)
  %ifcond27 = icmp ne i32 %8, 1
  br i1 %ifcond27, label %then_block28, label %entry_ifend29

then_block28:                                     ; preds = %entry_ifend10
  %9 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend29:                                    ; preds = %entry_ifend10
  %stack_offset_value33 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value33, i64* %"lvar$0$", align 8
  %stack_offset_value35 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value35, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value36 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value37 = getelementptr i64, i64* %loaded_stack_ptr_address_value36, i64 -1
  %stack_pointer_offset_value38 = load i64, i64* %stack_pointer_offset_value37, align 8
  %10 = trunc i64 %stack_pointer_offset_value38 to i32
  call void @push_jit_object(i32 %10)
  %loaded_stack_ptr_address_value39 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value40 = getelementptr i64, i64* %loaded_stack_ptr_address_value39, i64 1
  store i64* %dec_ptr_value40, i64** %stack_ptr_address
  %addtmp = add nuw i32 %10, 123
  %11 = zext i32 %addtmp to i64
  store i64 %11, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run53_5()$$58"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643360 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %then_block25, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643376 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond8 = icmp ne i32 %4, 1
  br i1 %ifcond8, label %then_block9, label %entry_ifend10

then_block9:                                      ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend10:                                    ; preds = %entry_ifend2
  %stack_offset_value11 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value11, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value12 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value12, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 -1
  %stack_pointer_offset_value14 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value14 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value15 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value15, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value14, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value11, i64* %lvar, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 %stack_pointer_offset_value14, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value21 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value21, align 8
  %7 = zext i32 %6 to i64
  store i64 %7, i64* %loaded_stack_ptr_address_value21, align 8
  %loaded_stack_ptr_address_value22 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value23 = getelementptr i64, i64* %loaded_stack_ptr_address_value22, i64 1
  store i64* %inc_ptr_value23, i64** %stack_ptr_address
  %8 = call i32 @call_invoke_virtual_method(i32 10064, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %constant, i32 %6)
  %ifcond24 = icmp ne i32 %8, 1
  br i1 %ifcond24, label %then_block25, label %entry_ifend26

then_block25:                                     ; preds = %entry_ifend10
  %9 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend26:                                    ; preds = %entry_ifend10
  %stack_offset_value30 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value30, i64* %"lvar$0$", align 8
  %stack_offset_value32 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value32, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value33 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value34 = getelementptr i64, i64* %loaded_stack_ptr_address_value33, i64 -1
  %stack_pointer_offset_value35 = load i64, i64* %stack_pointer_offset_value34, align 8
  %10 = trunc i64 %stack_pointer_offset_value35 to i32
  call void @push_jit_object(i32 %10)
  %loaded_stack_ptr_address_value36 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value37 = getelementptr i64, i64* %loaded_stack_ptr_address_value36, i64 1
  store i64* %dec_ptr_value37, i64** %stack_ptr_address
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run54()$$59"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45643404 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_string_object(i8* inttoptr (i64 45643408 to i8*))
  call void @push_jit_object(i32 %1)
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %2 = zext i32 %0 to i64
  store i64 %2, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value5 = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 1
  store i64* %inc_ptr_value5, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_dynamic_method(i32 10092, i32 10100, i32 2, i32 1, i32 0, i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %code, i64* %constant)
  %ifcond = icmp ne i32 %4, 1
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %stack_offset_value6 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value6, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 -1
  %stack_pointer_offset_value8 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value8 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run55(int,int,lambda)$$60"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$3$" = alloca i64
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value1 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value1, i64* %"lvar$1$", align 8
  %stack_offset_address_value2 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value3 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value3, i64* %"lvar$2$", align 8
  %stack_offset_address_value4 = getelementptr i64, i64* %stack, i64 3
  %stack_offset_value5 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value5, i64* %"lvar$3$", align 8
  store i32 0, i32* @gSigInt
  %0 = trunc i64 %stack_offset_value5 to i32
  %1 = trunc i64 %stack_offset_value1 to i32
  %2 = trunc i64 %stack_offset_value3 to i32
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %0 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value11 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value12 = getelementptr i64, i64* %loaded_stack_ptr_address_value11, i64 1
  store i64* %inc_ptr_value12, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value12, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value12, align 8
  %loaded_stack_ptr_address_value14 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value15 = getelementptr i64, i64* %loaded_stack_ptr_address_value14, i64 1
  store i64* %inc_ptr_value15, i64** %stack_ptr_address
  %6 = call i32 @invoke_block_in_jit(i32 2, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond = icmp eq i32 %6, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %7 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %7)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value17, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run56()$$61"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = trunc i64 %stack_offset_value to i32
  %1 = call i32 @store_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %0, i64 777, i32 0)
  %ifcond = icmp eq i32 %1, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run57()$$62"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = trunc i64 %stack_offset_value to i32
  %1 = call %clvalue_and_bool_struct* @get_field_from_object(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %0, i32 0)
  %2 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %1, i32 0, i32 0
  %3 = load i64, i64* %2, align 4
  %4 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %1, i32 0, i32 1
  %5 = load i32, i32* %4, align 4
  %ifcond = icmp eq i32 %5, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %6 = trunc i64 %3 to i32
  %7 = zext i32 %6 to i64
  store i64 %7, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run58()$$63"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call %clvalue_and_bool_struct* @load_class_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 10104, i64* %constant)
  %1 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %0, i32 0, i32 0
  %2 = load i64, i64* %1, align 4
  %3 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %0, i32 0, i32 1
  %4 = load i32, i32* %3, align 4
  %ifcond = icmp eq i32 %4, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %5 = trunc i64 %2 to i32
  %6 = zext i32 %5 to i64
  store i64 %6, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run59()$$64"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @store_class_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 10112, i64* %constant, i64 777)
  %ifcond = icmp eq i32 %0, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  store i32 0, i32* @gSigInt
  %1 = call %clvalue_and_bool_struct* @load_class_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 10120, i64* %constant)
  %2 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %1, i32 0, i32 0
  %3 = load i64, i64* %2, align 4
  %4 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %1, i32 0, i32 1
  %5 = load i32, i32* %4, align 4
  %ifcond3 = icmp eq i32 %5, 0
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  %6 = trunc i64 %3 to i32
  %7 = zext i32 %6 to i64
  store i64 %7, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run60()$$65"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  store i64 %stack_offset_value, i64* %lvar, align 8
  store i64 123, i64* %gepaddtmp, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 2
  store i64 %0, i64* %lvar_offset_value6, align 8
  %2 = bitcast i8* %1 to i32*
  store i32 245, i32* %2, align 4
  %stack_offset_value7 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value7, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value8 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value8, i64* %"lvar$1$", align 8
  %stack_offset_address_value9 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value10 = load i64, i64* %stack_offset_address_value9, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value10, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %3 = trunc i64 %stack_offset_value8 to i32
  %4 = zext i32 %3 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run61()$$66"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  %2 = bitcast i8* %1 to i64*
  store i64 245, i64* %2, align 8
  %stack_offset_value2 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value2, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value3 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value3, i64* %"lvar$1$", align 8
  %stack_offset_address_value4 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value5 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value5, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 %stack_offset_value3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run62()$$67"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 4638362809345140326, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  %2 = bitcast i8* %1 to double*
  store double 2.451000e+02, double* %2, align 8
  %stack_offset_value2 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value2, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value3 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value3, i64* %"lvar$1$", align 8
  %stack_offset_address_value4 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value5 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value5, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %3 = uitofp i64 %stack_offset_value3 to double
  %4 = bitcast double %3 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run63()$$68"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643456 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend3, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_array_object(i64* %0, i32 5)
  call void @push_jit_object(i32 %1)
  store i64 0, i64* %"lvar$1$"
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %3 = trunc i64 %2 to i32
  %4 = call i32 @run_store_element(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %3, i32 1, i64 111)
  %ifcond4 = icmp eq i32 %4, 0
  br i1 %ifcond4, label %then_block, label %entry_ifend3

entry_ifend3:                                     ; preds = %entry_ifend
  store i32 0, i32* @gSigInt
  %5 = call i32 @run_store_element(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %3, i32 2, i64 222)
  %ifcond8 = icmp eq i32 %5, 0
  br i1 %ifcond8, label %then_block, label %entry_ifend7

entry_ifend7:                                     ; preds = %entry_ifend3
  store i32 0, i32* @gSigInt
  %6 = call i32 @get_array_length(i32 %3)
  %7 = zext i32 %6 to i64
  store i64 %7, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run64()$$69"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643460 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend7, %entry_ifend3, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_array_object(i64* %0, i32 5)
  call void @push_jit_object(i32 %1)
  store i64 0, i64* %"lvar$1$"
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %3 = trunc i64 %2 to i32
  %4 = call i32 @run_store_element(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %3, i32 1, i64 111)
  %ifcond4 = icmp eq i32 %4, 0
  br i1 %ifcond4, label %then_block, label %entry_ifend3

entry_ifend3:                                     ; preds = %entry_ifend
  store i32 0, i32* @gSigInt
  %5 = call i32 @run_store_element(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %3, i32 2, i64 222)
  %ifcond8 = icmp eq i32 %5, 0
  br i1 %ifcond8, label %then_block, label %entry_ifend7

entry_ifend7:                                     ; preds = %entry_ifend3
  store i32 0, i32* @gSigInt
  %6 = call %clvalue_and_bool_struct* @load_element(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %3, i32 1)
  %7 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 0
  %8 = load i64, i64* %7, align 4
  %9 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %ifcond12 = icmp eq i32 %10, 0
  br i1 %ifcond12, label %then_block, label %entry_ifend11

entry_ifend11:                                    ; preds = %entry_ifend7
  %11 = trunc i64 %8 to i32
  %12 = zext i32 %11 to i64
  store i64 %12, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run65()$$70"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @char_uppercase(i32 97)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run66()$$71"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @char_lowercase(i32 65)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run67()$$72"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643464 to i8*), i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @get_regex_global(i32 %0)
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run68()$$73"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643468 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @get_regex_global(i32 %0)
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run69()$$74"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643472 to i8*), i32 0, i32 1, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @get_regex_ignorecase(i32 %0)
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run70()$$75"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643476 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @get_regex_ignorecase(i32 %0)
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run70_5()$$76"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  store i64 1, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 2, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value4, align 8
  store i64 3, i64* %inc_ptr_value4, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %0 = call %clvalue_and_bool_struct* @run_create_array(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 3, i32 10152, i64* %constant)
  %1 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %0, i32 0, i32 0
  %2 = load i64, i64* %1, align 4
  %3 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %0, i32 0, i32 1
  %4 = load i32, i32* %3, align 4
  %ifcond = icmp eq i32 %4, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %5 = trunc i64 %2 to i32
  call void @push_jit_object(i32 %5)
  %loaded_stack_ptr_address_value8 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value8, i64 3
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run70_7()$$77"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_integer(i32 2)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_integer(i32 3)
  call void @push_jit_object(i32 %2)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %0 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value4, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value4, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %6 = call %clvalue_and_bool_struct* @run_create_carray(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 3, i32 10156, i64* %constant)
  %7 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 0
  %8 = load i64, i64* %7, align 4
  %9 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %ifcond = icmp eq i32 %10, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %11 = trunc i64 %8 to i32
  call void @push_jit_object(i32 %11)
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run71()$$78"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_integer(i32 2)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_integer(i32 3)
  call void @push_jit_object(i32 %2)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %0 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value4, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value4, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %6 = call %clvalue_and_bool_struct* @run_create_equalable_carray(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 3, i32 10164, i64* %constant)
  %7 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 0
  %8 = load i64, i64* %7, align 4
  %9 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %ifcond = icmp eq i32 %10, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %11 = trunc i64 %8 to i32
  call void @push_jit_object(i32 %11)
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run71_1()$$79"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_integer(i32 2)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_integer(i32 3)
  call void @push_jit_object(i32 %2)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %0 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value4, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value4, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %6 = call %clvalue_and_bool_struct* @run_create_list(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 3, i32 10172, i64* %constant)
  %7 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 0
  %8 = load i64, i64* %7, align 4
  %9 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %ifcond = icmp eq i32 %10, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %11 = trunc i64 %8 to i32
  call void @push_jit_object(i32 %11)
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run71_2()$$80"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_integer(i32 2)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_integer(i32 3)
  call void @push_jit_object(i32 %2)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %0 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value4, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value4, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %6 = call %clvalue_and_bool_struct* @run_create_equalable_list(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 3, i32 10180, i64* %constant)
  %7 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 0
  %8 = load i64, i64* %7, align 4
  %9 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %ifcond = icmp eq i32 %10, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %11 = trunc i64 %8 to i32
  call void @push_jit_object(i32 %11)
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run71_3()$$81"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_string_object(i8* inttoptr (i64 45643516 to i8*))
  call void @push_jit_object(i32 %1)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %2 = zext i32 %0 to i64
  store i64 %2, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  %4 = call %clvalue_and_bool_struct* @run_create_tuple(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 2)
  %5 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %4, i32 0, i32 0
  %6 = load i64, i64* %5, align 4
  %7 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %4, i32 0, i32 1
  %8 = load i32, i32* %7, align 4
  %ifcond = icmp eq i32 %8, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %9 = trunc i64 %6 to i32
  call void @push_jit_object(i32 %9)
  store i64 %6, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run71_4()$$82"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45643520 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 45643524 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i32 @create_integer(i32 2)
  call void @push_jit_object(i32 %3)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %4 = zext i32 %0 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %5 = zext i32 %1 to i64
  store i64 %5, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value4, align 8
  %6 = zext i32 %2 to i64
  store i64 %6, i64* %inc_ptr_value4, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value7, align 8
  %7 = zext i32 %3 to i64
  store i64 %7, i64* %inc_ptr_value7, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %8 = call %clvalue_and_bool_struct* @run_create_hash(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 2, i32 10200, i32 10208, i64* %constant)
  %9 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %8, i32 0, i32 0
  %10 = load i64, i64* %9, align 4
  %11 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %8, i32 0, i32 1
  %12 = load i32, i32* %11, align 4
  %ifcond = icmp eq i32 %12, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %13 = trunc i64 %10 to i32
  call void @push_jit_object(i32 %13)
  store i64 %10, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run72()$$83"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_create_block_object(i64** %stack_ptr_address, i64* %stack, i64* %constant, i32 10216, i32 36, i32 10252, i32 0, i32 2, i32 0, i32 1, i64* %info)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run72_5()$$84"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643580 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend26, %entry_ifend22, %entry_ifend12, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643596 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %lvar_offset_value8 = getelementptr i64, i64* %lvar, i64 2
  store i64 0, i64* %lvar_offset_value8, align 8
  store i64 0, i64* %lvar_offset_value8, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond10 = icmp ne i32 %4, 1
  br i1 %ifcond10, label %then_block11, label %entry_ifend12

then_block11:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend12:                                    ; preds = %entry_ifend2
  %stack_offset_value13 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value13, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value14 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value14, i64* %"lvar$1$", align 8
  %stack_offset_address_value15 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value16 = load i64, i64* %stack_offset_address_value15, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value16, i64* %"lvar$2$", align 8
  %loaded_stack_ptr_address_value17 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value17, i64 -1
  %stack_pointer_offset_value18 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value18 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value19 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value19, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value18, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @store_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %6, i64 123, i32 0)
  %ifcond23 = icmp eq i32 %7, 0
  br i1 %ifcond23, label %then_block, label %entry_ifend22

entry_ifend22:                                    ; preds = %entry_ifend12
  store i32 0, i32* @gSigInt
  %8 = call %pointer_and_bool_struct* @run_load_field_address(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 %6)
  %9 = getelementptr inbounds %pointer_and_bool_struct, %pointer_and_bool_struct* %8, i32 0, i32 0
  %10 = load i8*, i8** %9, align 8
  %11 = getelementptr inbounds %pointer_and_bool_struct, %pointer_and_bool_struct* %8, i32 0, i32 1
  %12 = load i32, i32* %11, align 4
  %ifcond27 = icmp eq i32 %12, 0
  br i1 %ifcond27, label %then_block, label %entry_ifend26

entry_ifend26:                                    ; preds = %entry_ifend22
  store i64 0, i64* %"lvar$2$"
  %13 = ptrtoint i8* %10 to i64
  store i64 %13, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %14 = inttoptr i64 %13 to i8*
  store i64 %stack_offset_value13, i64* %lvar, align 8
  store i64 %stack_pointer_offset_value18, i64* %lvar_offset_value6, align 8
  store i64 %13, i64* %lvar_offset_value8, align 8
  %15 = bitcast i8* %14 to i32*
  store i32 234, i32* %15, align 4
  %stack_offset_value35 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value35, i64* %"lvar$0$", align 8
  %stack_offset_value37 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value37, i64* %"lvar$1$", align 8
  %stack_offset_value39 = load i64, i64* %stack_offset_address_value15, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value39, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %16 = trunc i64 %stack_offset_value37 to i32
  %17 = call %clvalue_and_bool_struct* @get_field_from_object(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %16, i32 0)
  %18 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %17, i32 0, i32 0
  %19 = load i64, i64* %18, align 4
  %20 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %17, i32 0, i32 1
  %21 = load i32, i32* %20, align 4
  %ifcond43 = icmp eq i32 %21, 0
  br i1 %ifcond43, label %then_block, label %entry_ifend42

entry_ifend42:                                    ; preds = %entry_ifend26
  %22 = trunc i64 %19 to i32
  %23 = zext i32 %22 to i64
  store i64 %23, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run72_6()$$85"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  store i64 %stack_offset_value, i64* %lvar, align 8
  store i64 123, i64* %gepaddtmp, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 2
  store i64 %0, i64* %lvar_offset_value6, align 8
  %2 = bitcast i8* %1 to i32*
  %llvm_value = load i32, i32* %2, align 4
  %3 = zext i32 %llvm_value to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run72_7()$$86"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 4638362809345140326, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  store i64 %stack_offset_value, i64* %lvar, align 8
  store i64 4638362809345140326, i64* %gepaddtmp, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 2
  store i64 %0, i64* %lvar_offset_value6, align 8
  %2 = bitcast i8* %1 to double*
  %llvm_value = load double, double* %2, align 8
  %3 = bitcast double %llvm_value to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run72_8()$$87"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 1123431219, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  store i64 %stack_offset_value, i64* %lvar, align 8
  store i64 1123431219, i64* %gepaddtmp, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 2
  store i64 %0, i64* %lvar_offset_value6, align 8
  %2 = bitcast i8* %1 to float*
  %llvm_value = load float, float* %2, align 4
  %3 = fpext float %llvm_value to double
  %4 = bitcast double %3 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run72_9()$$88"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  store i64 %stack_offset_value, i64* %lvar, align 8
  store i64 123, i64* %gepaddtmp, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 2
  store i64 %0, i64* %lvar_offset_value6, align 8
  %2 = bitcast i8* %1 to i64*
  %llvm_value = load i64, i64* %2, align 8
  store i64 %llvm_value, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run72_a()$$89"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  %1 = inttoptr i64 %0 to i8*
  store i64 %stack_offset_value, i64* %lvar, align 8
  store i64 123, i64* %gepaddtmp, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 2
  store i64 %0, i64* %lvar_offset_value6, align 8
  %llvm_value = load i8, i8* %1, align 1
  %2 = zext i8 %llvm_value to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run73()$$90"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 12)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run74()$$91"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run75()$$92"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run76()$$93"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run77()$$94"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 65)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run78()$$95"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run78_1()$$96"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_uinteger(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run78_2()$$97"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_uinteger(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run78_3()$$98"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 -123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run79()$$99"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_byte(i8 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run80()$$100"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_byte(i8 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run80_1()$$101"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_byte(i8 -123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run81()$$102"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_ubyte(i8 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run82()$$103"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_ubyte(i8 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run82_1()$$104"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_short(i16 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run82_2()$$105"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_short(i16 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run82_3()$$106"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_ushort(i16 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run82_4()$$107"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_ushort(i16 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run82_5()$$108"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_short(i16 -123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run83()$$109"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_ulong(i64 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run84()$$110"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_long(i64 123456)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run85()$$111"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_float(float 1.230000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run86()$$112"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_float(float 0x405EC66660000000)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run87()$$113"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_float(float 0x405EC66660000000)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run87_1()$$114"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_float(float 1.230000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run87_2()$$115"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_float(float -1.230000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run88()$$116"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_double(double 1.230000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run89()$$117"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_double(double 0x405EC66660000000)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run90()$$118"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_double(double 1.231000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run90_1()$$119"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_double(double 1.230000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run90_2()$$120"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_double(double -1.230000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run91(pointer)$$121"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value1 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = inttoptr i64 %stack_offset_value1 to i8*
  %1 = call i32 @create_pointer(i8* %0)
  call void @push_jit_object(i32 %1)
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run92()$$122"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_bool(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run92_1()$$123"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_char(i32 65)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run92_2()$$124"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_char(i32 65)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_1()$$125"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_int_to_string_cast(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_2()$$126"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_long_to_string_cast(i64 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_3()$$127"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_int_to_string_cast(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_4()$$128"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_ulong_to_string_cast(i64 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_5()$$129"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_uint_to_string_cast(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_6()$$130"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_int_to_string_cast(i32 -123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_7()$$131"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_double_to_string_cast(double 1.231000e+02)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93_8()$$132"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_float_to_string_cast(float 0x405EC66660000000)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run93()$$133"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_double_to_string_cast(double 1.100000e+00)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run94()$$134"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_int_to_string_cast(i32 123)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95()$$135"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_char_to_string_cast(i32 97)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_1()$$136"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 45643612 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @run_regex_to_string_cast(i32 %0)
  call void @push_jit_object(i32 %1)
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_2()$$137"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_bool_to_string_cast(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_3()$$138"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @run_bool_to_string_cast(i32 0)
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_4(pointer)$$139"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value1 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value1, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = inttoptr i64 %stack_offset_value1 to i8*
  %1 = call i32 @run_pointer_to_string_cast(i8* %0)
  call void @push_jit_object(i32 %1)
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_5()$$140"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_6()$$141"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_7()$$142"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_8()$$143"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_9()$$144"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_10()$$145"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_11()$$146"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_12()$$147"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_13()$$148"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 123, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_14()$$149"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4638355772470722560, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_15()$$150"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4638355772470722560, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_16()$$151"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4638362809237766144, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_17()$$152"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4638355772470722560, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_18()$$153"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4638355772470722560, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_19()$$154"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4638362809237766144, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run95_20()$$155"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4638355772470722560, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96()$$156"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643616 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643624 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %8 = zext i32 %7 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96_1()$$157"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643632 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643640 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %value2 = trunc i32 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96_2()$$158"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643648 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643656 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %8 = sitofp i32 %7 to float
  %9 = fpext float %8 to double
  %10 = bitcast double %9 to i64
  store i64 %10, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96_3()$$159"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643664 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643672 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %8 = sitofp i32 %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96_4()$$160"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643680 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643688 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4294967173, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %value2 = trunc i32 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96_5()$$161"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643696 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643704 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4294967173, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %8 = sitofp i32 %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96_6()$$162"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643712 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643724 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_uinteger_to_uint_cast(i32 %6)
  %8 = uitofp i32 %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run96_7()$$163"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643736 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643748 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_uinteger_to_uint_cast(i32 %6)
  %value2 = trunc i32 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run97()$$164"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643760 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643768 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %value2 = sext i32 %7 to i64
  store i64 %value2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98()$$165"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643776 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643784 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_integer_to_int_cast(i32 %6)
  %8 = sitofp i32 %7 to float
  %9 = fpext float %8 to double
  %10 = bitcast double %9 to i64
  store i64 %10, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_1()$$166"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643792 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643800 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i8 @run_cbyte_to_byte_cast(i32 %6)
  %8 = zext i8 %7 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_2()$$167"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643808 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643816 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i8 @run_cbyte_to_byte_cast(i32 %6)
  %value2 = sext i8 %7 to i32
  %8 = zext i32 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_3()$$168"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643824 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643832 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i8 @run_cbyte_to_byte_cast(i32 %6)
  %8 = sitofp i8 %7 to float
  %9 = fpext float %8 to double
  %10 = bitcast double %9 to i64
  store i64 %10, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_4()$$169"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643840 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643848 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i8 @run_cbyte_to_byte_cast(i32 %6)
  %value2 = sext i8 %7 to i64
  store i64 %value2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_5()$$170"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643856 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643864 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i8 @run_cubyte_to_ubyte_cast(i32 %6)
  %value2 = zext i8 %7 to i64
  store i64 %value2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_6()$$171"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643872 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643880 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4294967295, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i8 @run_cbyte_to_byte_cast(i32 %6)
  %value2 = sext i8 %7 to i64
  store i64 %value2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_7()$$172"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643888 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643896 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i8 @run_cubyte_to_ubyte_cast(i32 %6)
  %8 = uitofp i8 %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_8()$$173"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643904 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643912 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i16 @run_cshort_to_short_cast(i32 %6)
  %8 = sitofp i16 %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_9()$$174"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643920 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643928 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i16 @run_cshort_to_short_cast(i32 %6)
  %value2 = trunc i16 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_10()$$175"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643936 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643944 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i16 @run_cshort_to_short_cast(i32 %6)
  %value2 = sext i16 %7 to i32
  %8 = zext i32 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_11()$$176"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643952 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643960 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4294967295, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i16 @run_cshort_to_short_cast(i32 %6)
  %8 = zext i16 %7 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_12()$$177"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643968 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643976 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4294967295, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 15, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i16 @run_cshort_to_short_cast(i32 %6)
  %value2 = trunc i16 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_13()$$178"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643984 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45643992 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i64 @run_clong_to_long_cast(i32 %6)
  store i64 %7, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_14()$$179"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644000 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644008 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i64 @run_clong_to_long_cast(i32 %6)
  %value2 = trunc i64 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_15()$$180"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644016 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644024 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i64 @run_clong_to_long_cast(i32 %6)
  %8 = sitofp i64 %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_16()$$181"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644032 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644040 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4294967173, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i64 @run_clong_to_long_cast(i32 %6)
  %8 = sitofp i64 %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_17()$$182"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644048 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644056 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4294967173, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i64 @run_clong_to_long_cast(i32 %6)
  %value2 = trunc i64 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_18()$$183"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644064 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644072 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 65, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_uinteger_to_uint_cast(i32 %6)
  %value2 = trunc i32 %7 to i8
  %8 = zext i8 %value2 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run98_19()$$184"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644080 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644088 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 65, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_uinteger_to_uint_cast(i32 %6)
  %8 = zext i32 %7 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run99()$$185"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run99_1()$$186"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644096 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644104 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 1074161254, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_cfloat_to_int_cast(i32 %6)
  %value2 = sext i32 %7 to i64
  store i64 %value2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run99_2()$$187"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644112 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644120 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 1074161254, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call float @run_cfloat_to_float_cast(i32 %6)
  %8 = fpext float %7 to double
  %9 = bitcast double %8 to i64
  store i64 %9, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run99_3()$$188"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644128 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644136 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 1074161254, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_cfloat_to_int_cast(i32 %6)
  %8 = zext i32 %7 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run99_4()$$189"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644144 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644152 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4611911198408756429, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call double @run_cdouble_to_double_cast(i32 %6)
  %8 = bitcast double %7 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run99_5()$$190"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644160 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644168 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block, label %entry_ifend2

entry_ifend2:                                     ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 0, i64* %lvar_offset_value6, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 4611911198408756429, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value10 = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value10, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 14, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond11 = icmp ne i32 %4, 1
  br i1 %ifcond11, label %then_block12, label %entry_ifend13

then_block12:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend13:                                    ; preds = %entry_ifend2
  %stack_offset_value14 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value14, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value15 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value15, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 -1
  %stack_pointer_offset_value17 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value17 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value18 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value18, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_pointer_offset_value17, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %7 = call i32 @run_cdouble_to_int_cast(i32 %6)
  %8 = zext i32 %7 to i64
  store i64 %8, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run100()$$191"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 4611686018427387904, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run101()$$192"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run102()$$193"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run103()$$194"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i32 0, i32* @gSigInt
  store i32 0, i32* @gSigInt
  store i32 0, i32* @gSigInt
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run104(lambda)$$195"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value1 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value1, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  br label %for_start_pointk

for_start_pointk:                                 ; preds = %entry_ifend, %entry
  %lvar11 = phi i64 [ %5, %entry_ifend ], [ 0, %entry ]
  %0 = trunc i64 %lvar11 to i32
  %letmp = icmp slt i32 %0, 3
  br i1 %letmp, label %entry_condend, label %label_for_endk

entry_condend:                                    ; preds = %for_start_pointk
  store i32 0, i32* @gSigInt
  %1 = trunc i64 %stack_offset_value1 to i32
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %2 = zext i32 %1 to i64
  store i64 %2, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  store i64 123, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %3 = call i32 @invoke_block_in_jit(i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond = icmp eq i32 %3, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

label_for_endk:                                   ; preds = %for_start_pointk
  store i64 0, i64* %stack, align 8
  ret i32 1

then_block:                                       ; preds = %entry_condend
  ret i32 0

entry_ifend:                                      ; preds = %entry_condend
  %loaded_stack_ptr_address_value8 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value8, i64 -1
  %stack_pointer_offset_value9 = load i64, i64* %stack_pointer_offset_value, align 8
  %4 = trunc i64 %stack_pointer_offset_value9 to i32
  call void @push_jit_object(i32 %4)
  %loaded_stack_ptr_address_value10 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value10, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  %addtmp = add nuw i32 %0, 1
  store i64 0, i64* %"lvar$2$"
  %5 = zext i32 %addtmp to i64
  store i64 %5, i64* %"lvar$2$", align 8
  br label %for_start_pointk
}

define i32 @"JITTest.run105()$$196"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i32 @create_integer(i32 1)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_integer(i32 2)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_integer(i32 3)
  call void @push_jit_object(i32 %2)
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %0 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value1 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value1, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %inc_ptr_value, align 8
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value4 = getelementptr i64, i64* %loaded_stack_ptr_address_value3, i64 1
  store i64* %inc_ptr_value4, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value4, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %inc_ptr_value4, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %6 = call %clvalue_and_bool_struct* @run_create_carray(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 3, i32 11328, i64* %constant)
  %7 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 0
  %8 = load i64, i64* %7, align 4
  %9 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %6, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %ifcond = icmp eq i32 %10, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %11 = trunc i64 %8 to i32
  call void @push_jit_object(i32 %11)
  store i64 0, i64* %"lvar$1$"
  store i64 %8, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  %12 = call i32 @run_create_block_object(i64** %stack_ptr_address, i64* %stack, i64* %constant, i32 11336, i32 44, i32 11380, i32 15, i32 1, i32 0, i32 1, i64* %info)
  call void @push_jit_object(i32 %12)
  %13 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644724 to i8*))
  %ifcond11 = icmp eq i64* %13, null
  br i1 %ifcond11, label %then_block, label %entry_ifend10

entry_ifend10:                                    ; preds = %entry_ifend
  store i64 0, i64* %lvar, align 8
  store i64 %stack_offset_value, i64* %lvar, align 8
  %lvar_offset_value14 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value14, align 8
  store i64 %8, i64* %lvar_offset_value14, align 8
  %loaded_stack_ptr_address_value15 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value15, align 8
  %14 = zext i32 %11 to i64
  store i64 %14, i64* %loaded_stack_ptr_address_value15, align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value17 = getelementptr i64, i64* %loaded_stack_ptr_address_value16, i64 1
  store i64* %inc_ptr_value17, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value17, align 8
  %15 = zext i32 %12 to i64
  store i64 %15, i64* %inc_ptr_value17, align 8
  %loaded_stack_ptr_address_value19 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value20 = getelementptr i64, i64* %loaded_stack_ptr_address_value19, i64 1
  store i64* %inc_ptr_value20, i64** %stack_ptr_address
  %16 = call i32 @call_invoke_method(i64* %13, i32 4, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond21 = icmp ne i32 %16, 1
  br i1 %ifcond21, label %then_block22, label %entry_ifend23

then_block22:                                     ; preds = %entry_ifend10
  %17 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend23:                                    ; preds = %entry_ifend10
  %stack_offset_value24 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value24, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value25 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value25, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value26 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value26, i64 -1
  %stack_pointer_offset_value27 = load i64, i64* %stack_pointer_offset_value, align 8
  %18 = trunc i64 %stack_pointer_offset_value27 to i32
  call void @push_jit_object(i32 %18)
  %loaded_stack_ptr_address_value28 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value28, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run106()$$197"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %VALUE_FOR_ANDAND_OROR = alloca i64
  %"lvar$3$" = alloca i64
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  store i64 0, i64* %"lvar$3$"
  store i64 0, i64* %"lvar$3$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$2$"
  store i64 123, i64* %"lvar$2$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$3$"
  store i64 123, i64* %"lvar$3$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 1, i64* %VALUE_FOR_ANDAND_OROR, align 8
  %0 = trunc i64 1 to i1
  store i32 0, i32* @gSigInt
  br i1 %0, label %entry_condend, label %label_elsel

entry_condend:                                    ; preds = %entry
  store i64 123, i64* %stack, align 8
  ret i32 1

label_elsel:                                      ; preds = %entry
  store i64 245, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.callingMethod(String,Array,int,int)$$198"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %VALUE_FOR_ANDAND_OROR104 = alloca i64
  %VALUE_FOR_ANDAND_OROR = alloca i64
  %"lvar$7$" = alloca i64
  %"lvar$6$" = alloca i64
  %"lvar$5$" = alloca i64
  %"lvar$4$" = alloca i64
  %"lvar$3$" = alloca i64
  %"lvar$2$" = alloca i64
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %stack_offset_address_value = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value1 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value1, i64* %"lvar$1$", align 8
  %stack_offset_address_value2 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value3 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value3, i64* %"lvar$2$", align 8
  %stack_offset_address_value4 = getelementptr i64, i64* %stack, i64 3
  %stack_offset_value5 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value5, i64* %"lvar$3$", align 8
  store i64 0, i64* %"lvar$4$"
  store i64 0, i64* %"lvar$4$", align 8
  store i64 0, i64* %"lvar$5$"
  store i64 0, i64* %"lvar$5$", align 8
  store i64 0, i64* %"lvar$6$"
  store i64 0, i64* %"lvar$6$", align 8
  store i64 0, i64* %"lvar$7$"
  store i64 0, i64* %"lvar$7$", align 8
  store i32 0, i32* @gSigInt
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644844 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %then_block299, %then_block241, %then_block191, %then_block138, %then_block73, %entry_ifend268, %label_if_endv, %label_if_elifv0a, %entry_condend165, %entry_ifend109, %entry_condend106, %entry_ifend27, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45644852 to i8*))
  %ifcond8 = icmp eq i64* %2, null
  br i1 %ifcond8, label %then_block, label %entry_ifend7

entry_ifend7:                                     ; preds = %entry_ifend
  %lvar9 = load i64, i64* %"lvar$0$"
  store i64 0, i64* %lvar, align 8
  store i64 %lvar9, i64* %lvar, align 8
  %lvar10 = load i64, i64* %"lvar$1$"
  %lvar_offset_value11 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value11, align 8
  store i64 %lvar10, i64* %lvar_offset_value11, align 8
  %lvar12 = load i64, i64* %"lvar$2$"
  %lvar_offset_value13 = getelementptr i64, i64* %lvar, i64 2
  store i64 0, i64* %lvar_offset_value13, align 8
  store i64 %lvar12, i64* %lvar_offset_value13, align 8
  %lvar14 = load i64, i64* %"lvar$3$"
  %lvar_offset_value15 = getelementptr i64, i64* %lvar, i64 3
  store i64 0, i64* %lvar_offset_value15, align 8
  store i64 %lvar14, i64* %lvar_offset_value15, align 8
  %lvar16 = load i64, i64* %"lvar$4$"
  %lvar_offset_value17 = getelementptr i64, i64* %lvar, i64 4
  store i64 0, i64* %lvar_offset_value17, align 8
  store i64 %lvar16, i64* %lvar_offset_value17, align 8
  %lvar18 = load i64, i64* %"lvar$5$"
  %lvar_offset_value19 = getelementptr i64, i64* %lvar, i64 5
  store i64 0, i64* %lvar_offset_value19, align 8
  store i64 %lvar18, i64* %lvar_offset_value19, align 8
  %lvar20 = load i64, i64* %"lvar$6$"
  %lvar_offset_value21 = getelementptr i64, i64* %lvar, i64 6
  store i64 0, i64* %lvar_offset_value21, align 8
  store i64 %lvar20, i64* %lvar_offset_value21, align 8
  %lvar22 = load i64, i64* %"lvar$7$"
  %lvar_offset_value23 = getelementptr i64, i64* %lvar, i64 7
  store i64 0, i64* %lvar_offset_value23, align 8
  store i64 %lvar22, i64* %lvar_offset_value23, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value24 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value24, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond25 = icmp ne i32 %4, 1
  br i1 %ifcond25, label %then_block26, label %entry_ifend27

then_block26:                                     ; preds = %entry_ifend7
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  ret i32 0

entry_ifend27:                                    ; preds = %entry_ifend7
  %stack_offset_value28 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value28, i64* %"lvar$0$", align 8
  %stack_offset_value30 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value30, i64* %"lvar$1$", align 8
  %stack_offset_value32 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value32, i64* %"lvar$2$", align 8
  %stack_offset_value34 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value34, i64* %"lvar$3$", align 8
  %stack_offset_address_value35 = getelementptr i64, i64* %stack, i64 4
  %stack_offset_value36 = load i64, i64* %stack_offset_address_value35, align 8
  store i64 0, i64* %"lvar$4$"
  store i64 %stack_offset_value36, i64* %"lvar$4$", align 8
  %stack_offset_address_value37 = getelementptr i64, i64* %stack, i64 5
  %stack_offset_value38 = load i64, i64* %stack_offset_address_value37, align 8
  store i64 0, i64* %"lvar$5$"
  store i64 %stack_offset_value38, i64* %"lvar$5$", align 8
  %stack_offset_address_value39 = getelementptr i64, i64* %stack, i64 6
  %stack_offset_value40 = load i64, i64* %stack_offset_address_value39, align 8
  store i64 0, i64* %"lvar$6$"
  store i64 %stack_offset_value40, i64* %"lvar$6$", align 8
  %stack_offset_address_value41 = getelementptr i64, i64* %stack, i64 7
  %stack_offset_value42 = load i64, i64* %stack_offset_address_value41, align 8
  store i64 0, i64* %"lvar$7$"
  store i64 %stack_offset_value42, i64* %"lvar$7$", align 8
  %loaded_stack_ptr_address_value43 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value43, i64 -1
  %stack_pointer_offset_value44 = load i64, i64* %stack_pointer_offset_value, align 8
  %6 = trunc i64 %stack_pointer_offset_value44 to i32
  call void @push_jit_object(i32 %6)
  %loaded_stack_ptr_address_value45 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value45, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %"lvar$4$"
  store i64 %stack_pointer_offset_value44, i64* %"lvar$4$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$5$"
  store i64 0, i64* %"lvar$5$", align 8
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$6$"
  store i64 0, i64* %"lvar$6$", align 8
  store i32 0, i32* @gSigInt
  %lvar46 = load i64, i64* %"lvar$1$"
  %7 = trunc i64 %lvar46 to i32
  %8 = call i32 @run_create_block_object(i64** %stack_ptr_address, i64* %stack, i64* %constant, i32 11532, i32 1408, i32 12940, i32 2062, i32 2, i32 7, i32 0, i64* %info)
  call void @push_jit_object(i32 %8)
  %9 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45648332 to i8*))
  %ifcond49 = icmp eq i64* %9, null
  br i1 %ifcond49, label %then_block, label %entry_ifend48

entry_ifend48:                                    ; preds = %entry_ifend27
  %lvar50 = load i64, i64* %"lvar$0$"
  store i64 0, i64* %lvar, align 8
  store i64 %lvar50, i64* %lvar, align 8
  %lvar52 = load i64, i64* %"lvar$1$"
  store i64 0, i64* %lvar_offset_value11, align 8
  store i64 %lvar52, i64* %lvar_offset_value11, align 8
  %lvar54 = load i64, i64* %"lvar$2$"
  store i64 0, i64* %lvar_offset_value13, align 8
  store i64 %lvar54, i64* %lvar_offset_value13, align 8
  %lvar56 = load i64, i64* %"lvar$3$"
  store i64 0, i64* %lvar_offset_value15, align 8
  store i64 %lvar56, i64* %lvar_offset_value15, align 8
  %lvar58 = load i64, i64* %"lvar$4$"
  store i64 0, i64* %lvar_offset_value17, align 8
  store i64 %lvar58, i64* %lvar_offset_value17, align 8
  %lvar60 = load i64, i64* %"lvar$5$"
  store i64 0, i64* %lvar_offset_value19, align 8
  store i64 %lvar60, i64* %lvar_offset_value19, align 8
  %lvar62 = load i64, i64* %"lvar$6$"
  store i64 0, i64* %lvar_offset_value21, align 8
  store i64 %lvar62, i64* %lvar_offset_value21, align 8
  %lvar64 = load i64, i64* %"lvar$7$"
  store i64 0, i64* %lvar_offset_value23, align 8
  store i64 %lvar64, i64* %lvar_offset_value23, align 8
  %loaded_stack_ptr_address_value66 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value66, align 8
  %10 = zext i32 %7 to i64
  store i64 %10, i64* %loaded_stack_ptr_address_value66, align 8
  %loaded_stack_ptr_address_value67 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value68 = getelementptr i64, i64* %loaded_stack_ptr_address_value67, i64 1
  store i64* %inc_ptr_value68, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value68, align 8
  %11 = zext i32 %8 to i64
  store i64 %11, i64* %inc_ptr_value68, align 8
  %loaded_stack_ptr_address_value70 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value71 = getelementptr i64, i64* %loaded_stack_ptr_address_value70, i64 1
  store i64* %inc_ptr_value71, i64** %stack_ptr_address
  %12 = call i32 @call_invoke_method(i64* %9, i32 4, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond72 = icmp ne i32 %12, 1
  br i1 %ifcond72, label %then_block73, label %entry_ifend74

then_block73:                                     ; preds = %entry_ifend48
  %13 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend74:                                    ; preds = %entry_ifend48
  %stack_offset_value78 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value78, i64* %"lvar$0$", align 8
  %stack_offset_value80 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value80, i64* %"lvar$1$", align 8
  %stack_offset_value82 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value82, i64* %"lvar$2$", align 8
  %stack_offset_value84 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value84, i64* %"lvar$3$", align 8
  %stack_offset_value86 = load i64, i64* %stack_offset_address_value35, align 8
  store i64 0, i64* %"lvar$4$"
  store i64 %stack_offset_value86, i64* %"lvar$4$", align 8
  %stack_offset_value88 = load i64, i64* %stack_offset_address_value37, align 8
  store i64 0, i64* %"lvar$5$"
  store i64 %stack_offset_value88, i64* %"lvar$5$", align 8
  %stack_offset_value90 = load i64, i64* %stack_offset_address_value39, align 8
  store i64 0, i64* %"lvar$6$"
  store i64 %stack_offset_value90, i64* %"lvar$6$", align 8
  %stack_offset_value92 = load i64, i64* %stack_offset_address_value41, align 8
  store i64 0, i64* %"lvar$7$"
  store i64 %stack_offset_value92, i64* %"lvar$7$", align 8
  %loaded_stack_ptr_address_value93 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value94 = getelementptr i64, i64* %loaded_stack_ptr_address_value93, i64 -1
  %stack_pointer_offset_value95 = load i64, i64* %stack_pointer_offset_value94, align 8
  %14 = trunc i64 %stack_pointer_offset_value95 to i32
  call void @push_jit_object(i32 %14)
  %loaded_stack_ptr_address_value96 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value97 = getelementptr i64, i64* %loaded_stack_ptr_address_value96, i64 1
  store i64* %dec_ptr_value97, i64** %stack_ptr_address
  store i32 0, i32* @gSigInt
  %lvar98 = load i64, i64* %"lvar$6$"
  %15 = trunc i64 %lvar98 to i32
  %16 = trunc i32 %15 to i1
  br i1 %16, label %entry_condend, label %label_elifv1a

entry_condend:                                    ; preds = %entry_ifend74
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$7$"
  store i64 0, i64* %"lvar$7$", align 8
  br label %label_if_endv

label_elifv1a:                                    ; preds = %entry_ifend74
  %lvar100 = load i64, i64* %"lvar$5$"
  %17 = trunc i64 %lvar100 to i32
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  %18 = zext i32 %17 to i64
  store i64 %18, i64* %VALUE_FOR_ANDAND_OROR, align 8
  %19 = trunc i32 %17 to i1
  br i1 %19, label %label_or_endpointw, label %entry_condnotend

label_if_endv:                                    ; preds = %entry_ifend242, %entry_ifend192, %entry_condend
  store i32 0, i32* @gSigInt
  %20 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45648608 to i8*))
  %ifcond269 = icmp eq i64* %20, null
  br i1 %ifcond269, label %then_block, label %entry_ifend268

entry_condnotend:                                 ; preds = %label_elifv1a
  %lvar102 = load i64, i64* %"lvar$2$"
  %21 = trunc i64 %lvar102 to i32
  %lvar103 = load i64, i64* %"lvar$3$"
  %22 = trunc i64 %lvar103 to i32
  %subtmp = sub nuw i32 %22, 1
  %eqtmpx = icmp eq i32 %21, %subtmp
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR104, align 8
  %23 = zext i1 %eqtmpx to i64
  store i64 %23, i64* %VALUE_FOR_ANDAND_OROR104, align 8
  %24 = zext i1 %eqtmpx to i32
  %25 = trunc i32 %24 to i1
  br i1 %25, label %entry_condend106, label %label_and_endpointx

label_or_endpointw:                               ; preds = %label_elifv1a, %label_and_endpointx
  %value_for_andand_oror163 = phi i64 [ %34, %label_and_endpointx ], [ %18, %label_elifv1a ]
  %26 = trunc i64 %value_for_andand_oror163 to i1
  store i32 0, i32* @gSigInt
  store i64 0, i64* %"lvar$7$"
  store i64 123, i64* %"lvar$7$", align 8
  store i32 0, i32* @gSigInt
  %27 = call i32 @run_int_to_string_cast(i32 123)
  call void @push_jit_object(i32 %27)
  br i1 %26, label %entry_condend165, label %label_if_elifv0a

entry_condend106:                                 ; preds = %entry_condnotend
  %28 = call %clvalue_and_bool_struct* @load_class_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 15100, i64* %constant)
  %29 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %28, i32 0, i32 0
  %30 = load i64, i64* %29, align 4
  %31 = getelementptr inbounds %clvalue_and_bool_struct, %clvalue_and_bool_struct* %28, i32 0, i32 1
  %32 = load i32, i32* %31, align 4
  %ifcond110 = icmp eq i32 %32, 0
  br i1 %ifcond110, label %then_block, label %entry_ifend109

label_and_endpointx:                              ; preds = %entry_condnotend, %entry_ifend139
  %value_for_andand_oror = phi i64 [ %43, %entry_ifend139 ], [ %23, %entry_condnotend ]
  %33 = trunc i64 %value_for_andand_oror to i1
  %34 = zext i1 %33 to i64
  store i64 %34, i64* %VALUE_FOR_ANDAND_OROR, align 8
  br label %label_or_endpointw

entry_ifend109:                                   ; preds = %entry_condend106
  %35 = trunc i64 %30 to i32
  %lvar111 = load i64, i64* %"lvar$0$"
  %36 = trunc i64 %lvar111 to i32
  %37 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45648436 to i8*))
  %ifcond114 = icmp eq i64* %37, null
  br i1 %ifcond114, label %then_block, label %entry_ifend113

entry_ifend113:                                   ; preds = %entry_ifend109
  %lvar115 = load i64, i64* %"lvar$0$"
  store i64 0, i64* %lvar, align 8
  store i64 %lvar115, i64* %lvar, align 8
  %lvar117 = load i64, i64* %"lvar$1$"
  store i64 0, i64* %lvar_offset_value11, align 8
  store i64 %lvar117, i64* %lvar_offset_value11, align 8
  %lvar119 = load i64, i64* %"lvar$2$"
  store i64 0, i64* %lvar_offset_value13, align 8
  store i64 %lvar119, i64* %lvar_offset_value13, align 8
  %lvar121 = load i64, i64* %"lvar$3$"
  store i64 0, i64* %lvar_offset_value15, align 8
  store i64 %lvar121, i64* %lvar_offset_value15, align 8
  %lvar123 = load i64, i64* %"lvar$4$"
  store i64 0, i64* %lvar_offset_value17, align 8
  store i64 %lvar123, i64* %lvar_offset_value17, align 8
  %lvar125 = load i64, i64* %"lvar$5$"
  store i64 0, i64* %lvar_offset_value19, align 8
  store i64 %lvar125, i64* %lvar_offset_value19, align 8
  %lvar127 = load i64, i64* %"lvar$6$"
  store i64 0, i64* %lvar_offset_value21, align 8
  store i64 %lvar127, i64* %lvar_offset_value21, align 8
  %lvar129 = load i64, i64* %"lvar$7$"
  store i64 0, i64* %lvar_offset_value23, align 8
  store i64 %lvar129, i64* %lvar_offset_value23, align 8
  %loaded_stack_ptr_address_value131 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value131, align 8
  %38 = zext i32 %35 to i64
  store i64 %38, i64* %loaded_stack_ptr_address_value131, align 8
  %loaded_stack_ptr_address_value132 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value133 = getelementptr i64, i64* %loaded_stack_ptr_address_value132, i64 1
  store i64* %inc_ptr_value133, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value133, align 8
  %39 = zext i32 %36 to i64
  store i64 %39, i64* %inc_ptr_value133, align 8
  %loaded_stack_ptr_address_value135 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value136 = getelementptr i64, i64* %loaded_stack_ptr_address_value135, i64 1
  store i64* %inc_ptr_value136, i64** %stack_ptr_address
  %40 = call i32 @call_invoke_method(i64* %37, i32 35, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond137 = icmp ne i32 %40, 1
  br i1 %ifcond137, label %then_block138, label %entry_ifend139

then_block138:                                    ; preds = %entry_ifend113
  %41 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend139:                                   ; preds = %entry_ifend113
  %stack_offset_value143 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value143, i64* %"lvar$0$", align 8
  %stack_offset_value145 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value145, i64* %"lvar$1$", align 8
  %stack_offset_value147 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value147, i64* %"lvar$2$", align 8
  %stack_offset_value149 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value149, i64* %"lvar$3$", align 8
  %stack_offset_value151 = load i64, i64* %stack_offset_address_value35, align 8
  store i64 0, i64* %"lvar$4$"
  store i64 %stack_offset_value151, i64* %"lvar$4$", align 8
  %stack_offset_value153 = load i64, i64* %stack_offset_address_value37, align 8
  store i64 0, i64* %"lvar$5$"
  store i64 %stack_offset_value153, i64* %"lvar$5$", align 8
  %stack_offset_value155 = load i64, i64* %stack_offset_address_value39, align 8
  store i64 0, i64* %"lvar$6$"
  store i64 %stack_offset_value155, i64* %"lvar$6$", align 8
  %stack_offset_value157 = load i64, i64* %stack_offset_address_value41, align 8
  store i64 0, i64* %"lvar$7$"
  store i64 %stack_offset_value157, i64* %"lvar$7$", align 8
  %loaded_stack_ptr_address_value158 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value159 = getelementptr i64, i64* %loaded_stack_ptr_address_value158, i64 -1
  %stack_pointer_offset_value160 = load i64, i64* %stack_pointer_offset_value159, align 8
  %42 = trunc i64 %stack_pointer_offset_value160 to i32
  call void @push_jit_object(i32 %42)
  %loaded_stack_ptr_address_value161 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value162 = getelementptr i64, i64* %loaded_stack_ptr_address_value161, i64 1
  store i64* %dec_ptr_value162, i64** %stack_ptr_address
  %noteqtmp = icmp ne i32 %42, -1
  %43 = zext i1 %noteqtmp to i64
  store i64 %43, i64* %VALUE_FOR_ANDAND_OROR104, align 8
  br label %label_and_endpointx

entry_condend165:                                 ; preds = %label_or_endpointw
  %44 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45648512 to i8*))
  %ifcond170 = icmp eq i64* %44, null
  br i1 %ifcond170, label %then_block, label %entry_ifend169

label_if_elifv0a:                                 ; preds = %label_or_endpointw
  %45 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45648568 to i8*))
  %ifcond220 = icmp eq i64* %45, null
  br i1 %ifcond220, label %then_block, label %entry_ifend219

entry_ifend169:                                   ; preds = %entry_condend165
  %lvar171 = load i64, i64* %"lvar$0$"
  store i64 0, i64* %lvar, align 8
  store i64 %lvar171, i64* %lvar, align 8
  %lvar173 = load i64, i64* %"lvar$1$"
  store i64 0, i64* %lvar_offset_value11, align 8
  store i64 %lvar173, i64* %lvar_offset_value11, align 8
  %lvar175 = load i64, i64* %"lvar$2$"
  store i64 0, i64* %lvar_offset_value13, align 8
  store i64 %lvar175, i64* %lvar_offset_value13, align 8
  %lvar177 = load i64, i64* %"lvar$3$"
  store i64 0, i64* %lvar_offset_value15, align 8
  store i64 %lvar177, i64* %lvar_offset_value15, align 8
  %lvar179 = load i64, i64* %"lvar$4$"
  store i64 0, i64* %lvar_offset_value17, align 8
  store i64 %lvar179, i64* %lvar_offset_value17, align 8
  %lvar181 = load i64, i64* %"lvar$5$"
  store i64 0, i64* %lvar_offset_value19, align 8
  store i64 %lvar181, i64* %lvar_offset_value19, align 8
  %lvar183 = load i64, i64* %"lvar$6$"
  store i64 0, i64* %lvar_offset_value21, align 8
  store i64 %lvar183, i64* %lvar_offset_value21, align 8
  %lvar185 = load i64, i64* %"lvar$7$"
  store i64 0, i64* %lvar_offset_value23, align 8
  store i64 %lvar185, i64* %lvar_offset_value23, align 8
  %loaded_stack_ptr_address_value187 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value187, align 8
  %46 = zext i32 %27 to i64
  store i64 %46, i64* %loaded_stack_ptr_address_value187, align 8
  %loaded_stack_ptr_address_value188 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value189 = getelementptr i64, i64* %loaded_stack_ptr_address_value188, i64 1
  store i64* %inc_ptr_value189, i64** %stack_ptr_address
  %47 = call i32 @call_invoke_method(i64* %44, i32 19, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond190 = icmp ne i32 %47, 1
  br i1 %ifcond190, label %then_block191, label %entry_ifend192

then_block191:                                    ; preds = %entry_ifend169
  %48 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend192:                                   ; preds = %entry_ifend169
  %stack_offset_value196 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value196, i64* %"lvar$0$", align 8
  %stack_offset_value198 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value198, i64* %"lvar$1$", align 8
  %stack_offset_value200 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value200, i64* %"lvar$2$", align 8
  %stack_offset_value202 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value202, i64* %"lvar$3$", align 8
  %stack_offset_value204 = load i64, i64* %stack_offset_address_value35, align 8
  store i64 0, i64* %"lvar$4$"
  store i64 %stack_offset_value204, i64* %"lvar$4$", align 8
  %stack_offset_value206 = load i64, i64* %stack_offset_address_value37, align 8
  store i64 0, i64* %"lvar$5$"
  store i64 %stack_offset_value206, i64* %"lvar$5$", align 8
  %stack_offset_value208 = load i64, i64* %stack_offset_address_value39, align 8
  store i64 0, i64* %"lvar$6$"
  store i64 %stack_offset_value208, i64* %"lvar$6$", align 8
  %stack_offset_value210 = load i64, i64* %stack_offset_address_value41, align 8
  store i64 0, i64* %"lvar$7$"
  store i64 %stack_offset_value210, i64* %"lvar$7$", align 8
  %loaded_stack_ptr_address_value211 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value212 = getelementptr i64, i64* %loaded_stack_ptr_address_value211, i64 -1
  %stack_pointer_offset_value213 = load i64, i64* %stack_pointer_offset_value212, align 8
  %49 = trunc i64 %stack_pointer_offset_value213 to i32
  call void @push_jit_object(i32 %49)
  %loaded_stack_ptr_address_value214 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value215 = getelementptr i64, i64* %loaded_stack_ptr_address_value214, i64 1
  store i64* %dec_ptr_value215, i64** %stack_ptr_address
  br label %label_if_endv

entry_ifend219:                                   ; preds = %label_if_elifv0a
  %lvar221 = load i64, i64* %"lvar$0$"
  store i64 0, i64* %lvar, align 8
  store i64 %lvar221, i64* %lvar, align 8
  %lvar223 = load i64, i64* %"lvar$1$"
  store i64 0, i64* %lvar_offset_value11, align 8
  store i64 %lvar223, i64* %lvar_offset_value11, align 8
  %lvar225 = load i64, i64* %"lvar$2$"
  store i64 0, i64* %lvar_offset_value13, align 8
  store i64 %lvar225, i64* %lvar_offset_value13, align 8
  %lvar227 = load i64, i64* %"lvar$3$"
  store i64 0, i64* %lvar_offset_value15, align 8
  store i64 %lvar227, i64* %lvar_offset_value15, align 8
  %lvar229 = load i64, i64* %"lvar$4$"
  store i64 0, i64* %lvar_offset_value17, align 8
  store i64 %lvar229, i64* %lvar_offset_value17, align 8
  %lvar231 = load i64, i64* %"lvar$5$"
  store i64 0, i64* %lvar_offset_value19, align 8
  store i64 %lvar231, i64* %lvar_offset_value19, align 8
  %lvar233 = load i64, i64* %"lvar$6$"
  store i64 0, i64* %lvar_offset_value21, align 8
  store i64 %lvar233, i64* %lvar_offset_value21, align 8
  %lvar235 = load i64, i64* %"lvar$7$"
  store i64 0, i64* %lvar_offset_value23, align 8
  store i64 %lvar235, i64* %lvar_offset_value23, align 8
  %loaded_stack_ptr_address_value237 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value237, align 8
  %50 = zext i32 %27 to i64
  store i64 %50, i64* %loaded_stack_ptr_address_value237, align 8
  %loaded_stack_ptr_address_value238 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value239 = getelementptr i64, i64* %loaded_stack_ptr_address_value238, i64 1
  store i64* %inc_ptr_value239, i64** %stack_ptr_address
  %51 = call i32 @call_invoke_method(i64* %45, i32 19, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond240 = icmp ne i32 %51, 1
  br i1 %ifcond240, label %then_block241, label %entry_ifend242

then_block241:                                    ; preds = %entry_ifend219
  %52 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend242:                                   ; preds = %entry_ifend219
  %stack_offset_value246 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value246, i64* %"lvar$0$", align 8
  %stack_offset_value248 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value248, i64* %"lvar$1$", align 8
  %stack_offset_value250 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value250, i64* %"lvar$2$", align 8
  %stack_offset_value252 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value252, i64* %"lvar$3$", align 8
  %stack_offset_value254 = load i64, i64* %stack_offset_address_value35, align 8
  store i64 0, i64* %"lvar$4$"
  store i64 %stack_offset_value254, i64* %"lvar$4$", align 8
  %stack_offset_value256 = load i64, i64* %stack_offset_address_value37, align 8
  store i64 0, i64* %"lvar$5$"
  store i64 %stack_offset_value256, i64* %"lvar$5$", align 8
  %stack_offset_value258 = load i64, i64* %stack_offset_address_value39, align 8
  store i64 0, i64* %"lvar$6$"
  store i64 %stack_offset_value258, i64* %"lvar$6$", align 8
  %stack_offset_value260 = load i64, i64* %stack_offset_address_value41, align 8
  store i64 0, i64* %"lvar$7$"
  store i64 %stack_offset_value260, i64* %"lvar$7$", align 8
  %loaded_stack_ptr_address_value261 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value262 = getelementptr i64, i64* %loaded_stack_ptr_address_value261, i64 -1
  %stack_pointer_offset_value263 = load i64, i64* %stack_pointer_offset_value262, align 8
  %53 = trunc i64 %stack_pointer_offset_value263 to i32
  call void @push_jit_object(i32 %53)
  %loaded_stack_ptr_address_value264 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value265 = getelementptr i64, i64* %loaded_stack_ptr_address_value264, i64 1
  store i64* %dec_ptr_value265, i64** %stack_ptr_address
  br label %label_if_endv

entry_ifend268:                                   ; preds = %label_if_endv
  %54 = call i32 @create_object(i64* %20)
  call void @push_jit_object(i32 %54)
  %55 = call i32 @create_string_object(i8* inttoptr (i64 45648616 to i8*))
  call void @push_jit_object(i32 %55)
  %56 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45648620 to i8*))
  %ifcond272 = icmp eq i64* %56, null
  br i1 %ifcond272, label %then_block, label %entry_ifend271

entry_ifend271:                                   ; preds = %entry_ifend268
  %lvar273 = load i64, i64* %"lvar$0$"
  store i64 0, i64* %lvar, align 8
  store i64 %lvar273, i64* %lvar, align 8
  %lvar275 = load i64, i64* %"lvar$1$"
  store i64 0, i64* %lvar_offset_value11, align 8
  store i64 %lvar275, i64* %lvar_offset_value11, align 8
  %lvar277 = load i64, i64* %"lvar$2$"
  store i64 0, i64* %lvar_offset_value13, align 8
  store i64 %lvar277, i64* %lvar_offset_value13, align 8
  %lvar279 = load i64, i64* %"lvar$3$"
  store i64 0, i64* %lvar_offset_value15, align 8
  store i64 %lvar279, i64* %lvar_offset_value15, align 8
  %lvar281 = load i64, i64* %"lvar$4$"
  store i64 0, i64* %lvar_offset_value17, align 8
  store i64 %lvar281, i64* %lvar_offset_value17, align 8
  %lvar283 = load i64, i64* %"lvar$5$"
  store i64 0, i64* %lvar_offset_value19, align 8
  store i64 %lvar283, i64* %lvar_offset_value19, align 8
  %lvar285 = load i64, i64* %"lvar$6$"
  store i64 0, i64* %lvar_offset_value21, align 8
  store i64 %lvar285, i64* %lvar_offset_value21, align 8
  %lvar287 = load i64, i64* %"lvar$7$"
  store i64 0, i64* %lvar_offset_value23, align 8
  store i64 %lvar287, i64* %lvar_offset_value23, align 8
  %loaded_stack_ptr_address_value289 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value289, align 8
  %57 = zext i32 %54 to i64
  store i64 %57, i64* %loaded_stack_ptr_address_value289, align 8
  %loaded_stack_ptr_address_value290 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value291 = getelementptr i64, i64* %loaded_stack_ptr_address_value290, i64 1
  store i64* %inc_ptr_value291, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value291, align 8
  %58 = zext i32 %55 to i64
  store i64 %58, i64* %inc_ptr_value291, align 8
  %loaded_stack_ptr_address_value293 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value294 = getelementptr i64, i64* %loaded_stack_ptr_address_value293, i64 1
  store i64* %inc_ptr_value294, i64** %stack_ptr_address
  store i64 0, i64* %inc_ptr_value294, align 8
  store i64 0, i64* %inc_ptr_value294, align 8
  %loaded_stack_ptr_address_value296 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value297 = getelementptr i64, i64* %loaded_stack_ptr_address_value296, i64 1
  store i64* %inc_ptr_value297, i64** %stack_ptr_address
  %59 = call i32 @call_invoke_method(i64* %56, i32 3, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond298 = icmp ne i32 %59, 1
  br i1 %ifcond298, label %then_block299, label %entry_ifend300

then_block299:                                    ; preds = %entry_ifend271
  %60 = call i8* @get_try_catch_label_name(i64* %info)
  br label %then_block

entry_ifend300:                                   ; preds = %entry_ifend271
  %stack_offset_value304 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value304, i64* %"lvar$0$", align 8
  %stack_offset_value306 = load i64, i64* %stack_offset_address_value, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value306, i64* %"lvar$1$", align 8
  %stack_offset_value308 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value308, i64* %"lvar$2$", align 8
  %stack_offset_value310 = load i64, i64* %stack_offset_address_value4, align 8
  store i64 0, i64* %"lvar$3$"
  store i64 %stack_offset_value310, i64* %"lvar$3$", align 8
  %stack_offset_value312 = load i64, i64* %stack_offset_address_value35, align 8
  store i64 0, i64* %"lvar$4$"
  store i64 %stack_offset_value312, i64* %"lvar$4$", align 8
  %stack_offset_value314 = load i64, i64* %stack_offset_address_value37, align 8
  store i64 0, i64* %"lvar$5$"
  store i64 %stack_offset_value314, i64* %"lvar$5$", align 8
  %stack_offset_value316 = load i64, i64* %stack_offset_address_value39, align 8
  store i64 0, i64* %"lvar$6$"
  store i64 %stack_offset_value316, i64* %"lvar$6$", align 8
  %stack_offset_value318 = load i64, i64* %stack_offset_address_value41, align 8
  store i64 0, i64* %"lvar$7$"
  store i64 %stack_offset_value318, i64* %"lvar$7$", align 8
  %loaded_stack_ptr_address_value319 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value320 = getelementptr i64, i64* %loaded_stack_ptr_address_value319, i64 -1
  %stack_pointer_offset_value321 = load i64, i64* %stack_pointer_offset_value320, align 8
  %61 = trunc i64 %stack_pointer_offset_value321 to i32
  call void @push_jit_object(i32 %61)
  %loaded_stack_ptr_address_value322 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value323 = getelementptr i64, i64* %loaded_stack_ptr_address_value322, i64 1
  store i64* %dec_ptr_value323, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value321, i64* %stack, align 8
  ret i32 1
}
