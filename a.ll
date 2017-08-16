; ModuleID = 'Module JITTest'

%clvalue_and_bool_struct = type { i64, i32 }

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

declare i64 @run_load_class_field_address(i64**, i64*, i32, i64*, i32, i32, i64*)

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

declare i32 @entry_exception_object_with_class_name2(i64**, i64*, i32, i64*, i8*, i8*)

declare i8** @run_load_field_address(i64**, i64*, i32, i64*, i32, i32)

declare %clvalue_and_bool_struct* @run_array_to_carray_cast(i64**, i64*, i32, i64*, i32, i8*)

declare i64* @get_class_with_load_and_initialize_in_jit(i8*)

define i32 @"JITTest.run()$$1"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 4, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run2()$$2"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27918512 to i8*))
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27918516 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918528 to i8*))
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
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918536 to i8*))
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
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918552 to i8*))
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27918568 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918576 to i8*))
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
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i64 124, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.method()$$8"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27918584 to i8*))
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
  %0 = trunc i64 %stack_offset_value to i32
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918588 to i8*))
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
  %6 = call i32 @create_string_object(i8* inttoptr (i64 27918596 to i8*))
  call void @push_jit_object(i32 %6)
  %7 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918600 to i8*))
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
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918608 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918624 to i8*))
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
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918640 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 27918652 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918664 to i8*))
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
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918676 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 27918688 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918700 to i8*))
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27918712 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918728 to i8*))
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
  call void @try_function(i64* %info, i32 2992, i32 92, i64* %code, i64* %constant)
  %6 = trunc i64 %stack_offset_value8 to i32
  %7 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27918752 to i8*))
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 1, i64* %"lvar$2$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  br label %entry_condend

entry_condend:                                    ; preds = %entry_condend, %entry
  %lvar913 = phi i64 [ 0, %entry ], [ %1, %entry_condend ]
  %0 = trunc i64 %lvar913 to i32
  %addtmp = add nuw i32 %0, 1
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %addtmp to i64
  store i64 %1, i64* %"lvar$1$", align 8
  %2 = trunc i64 %1 to i32
  %eqtmpx = icmp eq i32 %2, 1
  br i1 %eqtmpx, label %entry_condend4, label %entry_condend

entry_condend4:                                   ; preds = %entry_condend
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
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  br label %while_start_pointe

while_start_pointe:                               ; preds = %entry_condend, %entry
  %lvar2 = phi i64 [ %2, %entry_condend ], [ 0, %entry ]
  %lvar3 = phi i64 [ %3, %entry_condend ], [ 0, %entry ]
  %0 = trunc i64 %lvar3 to i32
  %letmp = icmp slt i32 %0, 3
  %1 = trunc i64 %lvar2 to i32
  br i1 %letmp, label %entry_condend, label %label_whilee

entry_condend:                                    ; preds = %while_start_pointe
  %addtmp = add nuw i32 %1, 1
  store i64 0, i64* %"lvar$1$"
  %2 = zext i32 %addtmp to i64
  store i64 %2, i64* %"lvar$1$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 0, i64* %"lvar$2$", align 8
  br label %for_start_pointf

for_start_pointf:                                 ; preds = %entry_condend, %entry
  %lvar2 = phi i64 [ %2, %entry_condend ], [ 0, %entry ]
  %lvar3 = phi i64 [ %3, %entry_condend ], [ 0, %entry ]
  %0 = trunc i64 %lvar3 to i32
  %letmp = icmp slt i32 %0, 3
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 1, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 2, i64* %"lvar$1$", align 8
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i64 0, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 1, i64* %VALUE_FOR_ANDAND_OROR, align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run19()$$22"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
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
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 27919244 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
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
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 27919248 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_regex_object(i8* inttoptr (i64 27919252 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
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
  %0 = call i32 @create_regex_object(i8* inttoptr (i64 27919256 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_regex_object(i8* inttoptr (i64 27919260 to i8*), i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0)
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 2, i64* %"lvar$2$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 123, i64* %"lvar$2$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 23, i64* %"lvar$2$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 1, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 2, i64* %"lvar$2$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 9, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 3, i64* %"lvar$2$", align 8
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
  store i64 0, i64* %"lvar$1$"
  store i64 5, i64* %"lvar$1$", align 8
  store i64 0, i64* %"lvar$2$"
  store i64 3, i64* %"lvar$2$", align 8
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run30()$$33"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 2, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run31()$$34"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run32()$$35"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run33()$$36"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run34()$$37"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 6, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run35()$$38"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 3, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run36()$$39"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 254, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run37()$$40"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 4294967294, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run38()$$41"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 4612136378497499136, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run39()$$42"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 4612136378497499136, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run40()$$43"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 4616189618054758400, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run41()$$44"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run42()$$45"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run43()$$46"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run44()$$47"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run45()$$48"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run46()$$49"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run47()$$50"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run48()$$51"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1
}

define i32 @"JITTest.run49()$$52"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
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
  %0 = inttoptr i64 %stack_offset_value1 to i8*
  %addtmp = getelementptr i8, i8* %0, i32 1
  store i64 0, i64* %"lvar$1$"
  %1 = ptrtoint i8* %addtmp to i64
  store i64 %1, i64* %"lvar$1$", align 8
  %2 = inttoptr i64 %1 to i8*
  %addtmp4 = getelementptr i8, i8* %2, i64 2
  store i64 0, i64* %"lvar$1$"
  %3 = ptrtoint i8* %addtmp4 to i64
  store i64 %3, i64* %"lvar$1$", align 8
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27919264 to i8*))
  call void @push_jit_object(i32 %0)
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %"lvar$1$", align 8
  %2 = trunc i64 %1 to i32
  %ifcond = icmp eq i32 %2, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  %3 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* inttoptr (i64 18168736 to i8*), i8* inttoptr (i64 16030786 to i8*))
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27919268 to i8*))
  call void @push_jit_object(i32 %0)
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %"lvar$1$", align 8
  %2 = trunc i64 %1 to i32
  %ifcond = icmp eq i32 %2, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  %3 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* inttoptr (i64 18168736 to i8*), i8* inttoptr (i64 16030786 to i8*))
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %4 = call i32 @get_string_object_of_object_name(i32 %2)
  call void @push_jit_object(i32 %4)
  %5 = call i32 @create_string_object(i8* inttoptr (i64 27919272 to i8*))
  call void @push_jit_object(i32 %5)
  %6 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27919280 to i8*))
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27919288 to i8*))
  call void @push_jit_object(i32 %0)
  store i64 0, i64* %"lvar$1$"
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %"lvar$1$", align 8
  %2 = trunc i64 %1 to i32
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27919292 to i8*))
  %ifcond = icmp eq i64* %3, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %ifcond4 = icmp eq i32 %2, 0
  br i1 %ifcond4, label %then_block2, label %entry_ifend3

then_block2:                                      ; preds = %entry_ifend
  %4 = call i32 @entry_exception_object_with_class_name2(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i8* inttoptr (i64 18168736 to i8*), i8* inttoptr (i64 16030812 to i8*))
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
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27919300 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %then_block28, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27919316 to i8*))
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
  %8 = call i32 @call_invoke_virtual_method(i32 3588, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %constant, i32 %6)
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
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27919344 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %then_block25, %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 27919360 to i8*))
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
  %8 = call i32 @call_invoke_virtual_method(i32 3632, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %constant, i32 %6)
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 27919388 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i32 @create_string_object(i8* inttoptr (i64 27919392 to i8*))
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
  %4 = call i32 @call_invoke_dynamic_method(i32 3660, i32 3668, i32 2, i32 1, i32 0, i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %code, i64* %constant)
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
  %0 = call %clvalue_and_bool_struct* @load_class_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 3672, i64* %constant)
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
  %0 = call i32 @store_class_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 3680, i64* %constant, i64 777)
  %ifcond = icmp eq i32 %0, 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry_ifend, %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call %clvalue_and_bool_struct* @load_class_field(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 0, i32 3688, i64* %constant)
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
  store i64 0, i64* %"lvar$1$"
  store i64 123, i64* %"lvar$1$", align 8
  %gepaddtmp = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %"lvar$2$"
  %0 = ptrtoint i64* %gepaddtmp to i64
  store i64 %0, i64* %"lvar$2$", align 8
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
  %3 = trunc i64 %stack_offset_value8 to i32
  %4 = zext i32 %3 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1
}
