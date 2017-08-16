; ModuleID = 'Module JITTest'

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

declare void @try_function(i64*, i32, i64*)

declare void @catch_function(i64*, i64*)

declare i8* @get_try_catch_label_name(i64*)

declare void @entry_exception_object(i32, i64*)

declare i64 @get_field_from_object(i64**, i64*, i32, i64*, i32, i32)

declare i32 @regex_equals(i32, i32)

declare i32 @get_string_object_of_object_name(i32)

declare i32 @object_implements_interface(i32, i64*)

declare i32 @call_invoke_virtual_method(i32, i64*, i32, i64**, i64*, i64*, i32)

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

define i32 @"JITTest.run()$$1"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 4, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run2()$$2"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45306408 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run3()$$3"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45306412 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306424 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %lvar1 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar1, i64* %lvar_offset_value, align 8
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
  %catchcond = icmp ne i8* %4, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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

then_block_b:                                     ; preds = %then_block4
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block4
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run4()$$4"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306432 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %lvar1 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar1, i64* %lvar_offset_value, align 8
  %1 = call i32 @call_invoke_method(i64* %0, i32 4, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond2 = icmp ne i32 %1, 1
  br i1 %ifcond2, label %then_block3, label %entry_ifend4

then_block3:                                      ; preds = %entry_ifend
  %2 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %2, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  %4 = trunc i64 %stack_pointer_offset_value6 to i32
  %addtmp = add nuw i32 %4, 3
  %5 = zext i32 %addtmp to i64
  store i64 %5, i64* %stack, align 8
  ret i32 1

then_block_b:                                     ; preds = %then_block3
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block3
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run5()$$5"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306448 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %lvar1 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar1, i64* %lvar_offset_value, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  store i64 1, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value3 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value3, align 8
  store i64 2, i64* %loaded_stack_ptr_address_value3, align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value5 = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 1
  store i64* %inc_ptr_value5, i64** %stack_ptr_address
  %1 = call i32 @call_invoke_method(i64* %0, i32 5, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond6 = icmp ne i32 %1, 1
  br i1 %ifcond6, label %then_block7, label %entry_ifend8

then_block7:                                      ; preds = %entry_ifend
  %2 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %2, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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

then_block_b:                                     ; preds = %then_block7
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block7
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run6()$$6"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45306464 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306472 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %lvar1 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar1, i64* %lvar_offset_value, align 8
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
  %catchcond = icmp ne i8* %4, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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

then_block_b:                                     ; preds = %then_block4
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block4
  ret i32 0

entry_after_return:                               ; No predecessors!
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
  %lvar1 = load i64, i64* %"lvar$1$"
  %0 = trunc i64 %lvar1 to i32
  %addtmp = add nuw i32 %0, 1
  %1 = zext i32 %addtmp to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.method()$$8"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45306480 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run8()$$9"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %lvar1 = load i64, i64* %"lvar$0$"
  %0 = trunc i64 %lvar1 to i32
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306484 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %lvar2 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar2, i64* %lvar_offset_value, align 8
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
  %catchcond = icmp ne i8* %4, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  %6 = call i32 @create_string_object(i8* inttoptr (i64 45306492 to i8*))
  call void @push_jit_object(i32 %6)
  %7 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306496 to i8*))
  %ifcond13 = icmp eq i64* %7, null
  br i1 %ifcond13, label %then_block11, label %entry_ifend12

then_block_b:                                     ; preds = %then_block5
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block5
  ret i32 0

then_block11:                                     ; preds = %entry_ifend6
  ret i32 0

entry_ifend12:                                    ; preds = %entry_ifend6
  %lvar14 = load i64, i64* %"lvar$0$"
  %lvar_offset_value15 = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value15, align 8
  store i64 %lvar14, i64* %lvar_offset_value15, align 8
  %loaded_stack_ptr_address_value16 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value16, align 8
  store i64 %stack_pointer_offset_value9, i64* %loaded_stack_ptr_address_value16, align 8
  %loaded_stack_ptr_address_value17 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value18 = getelementptr i64, i64* %loaded_stack_ptr_address_value17, i64 1
  store i64* %inc_ptr_value18, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value19 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value19, align 8
  %8 = zext i32 %6 to i64
  store i64 %8, i64* %loaded_stack_ptr_address_value19, align 8
  %loaded_stack_ptr_address_value20 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value21 = getelementptr i64, i64* %loaded_stack_ptr_address_value20, i64 1
  store i64* %inc_ptr_value21, i64** %stack_ptr_address
  %9 = call i32 @call_invoke_method(i64* %7, i32 8, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond22 = icmp ne i32 %9, 1
  br i1 %ifcond22, label %then_block23, label %entry_ifend24

then_block23:                                     ; preds = %entry_ifend12
  %10 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond25 = icmp ne i8* %10, null
  br i1 %catchcond25, label %then_block_b26, label %entry_ifend_b27

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

then_block_b26:                                   ; preds = %then_block23
  ret i32 0

entry_ifend_b27:                                  ; preds = %then_block23
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run9()$$10"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306504 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306520 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block1, label %entry_ifend2

then_block1:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend2:                                     ; preds = %entry_ifend
  %lvar4 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar4, i64* %lvar_offset_value, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %1 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value6, align 8
  store i64 123, i64* %loaded_stack_ptr_address_value6, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value8 = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value8, i64** %stack_ptr_address
  %4 = call i32 @call_invoke_method(i64* %2, i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %4, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend2
  %5 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %5, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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

then_block_b:                                     ; preds = %then_block10
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block10
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run10()$$11"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306536 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 45306548 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306560 to i8*))
  %ifcond3 = icmp eq i64* %3, null
  br i1 %ifcond3, label %then_block1, label %entry_ifend2

then_block1:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend2:                                     ; preds = %entry_ifend
  %lvar4 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar4, i64* %lvar_offset_value, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value6, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %loaded_stack_ptr_address_value6, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value8 = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value8, i64** %stack_ptr_address
  %6 = call i32 @call_invoke_method(i64* %3, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %6, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend2
  %7 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %7, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  call void @entry_exception_object(i64 %stack_pointer_offset_value14, i64* %info)
  ret i32 0

then_block_b:                                     ; preds = %then_block10
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block10
  ret i32 0

entry_after_throw:                                ; No predecessors!
  store i64 1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.method2()$$12"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306572 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 45306584 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306596 to i8*))
  %ifcond3 = icmp eq i64* %3, null
  br i1 %ifcond3, label %then_block1, label %entry_ifend2

then_block1:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend2:                                     ; preds = %entry_ifend
  %lvar4 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar4, i64* %lvar_offset_value, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value6, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %loaded_stack_ptr_address_value6, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value8 = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value8, i64** %stack_ptr_address
  %6 = call i32 @call_invoke_method(i64* %3, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %6, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend2
  %7 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %7, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  call void @entry_exception_object(i64 %stack_pointer_offset_value14, i64* %info)
  ret i32 0

then_block_b:                                     ; preds = %then_block10
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block10
  ret i32 0

entry_after_throw:                                ; No predecessors!
  store i64 0, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
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
  %0 = call i32 @create_string_object(i8* inttoptr (i64 45306608 to i8*))
  call void @push_jit_object(i32 %0)
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306624 to i8*))
  %ifcond = icmp eq i64* %1, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %lvar1 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar1, i64* %lvar_offset_value, align 8
  %lvar2 = load i64, i64* %"lvar$1$"
  %lvar_offset_value3 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value3, align 8
  store i64 %lvar2, i64* %lvar_offset_value3, align 8
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
  %catchcond = icmp ne i8* %4, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  call void @try_function(i64* %info, i64 45306632, i32 92, i64 45334440)
  %lvar13 = load i64, i64* %"lvar$0$"
  %6 = trunc i64 %lvar13 to i32
  %7 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306648 to i8*))
  %ifcond16 = icmp eq i64* %7, null
  br i1 %ifcond16, label %then_block14, label %entry_ifend15

then_block_b:                                     ; preds = %then_block6
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block6
  ret i32 0

then_block14:                                     ; preds = %entry_ifend7
  ret i32 0

entry_ifend15:                                    ; preds = %entry_ifend7
  %lvar17 = load i64, i64* %"lvar$0$"
  %lvar_offset_value18 = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value18, align 8
  store i64 %lvar17, i64* %lvar_offset_value18, align 8
  %lvar19 = load i64, i64* %"lvar$1$"
  %lvar_offset_value20 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value20, align 8
  store i64 %lvar19, i64* %lvar_offset_value20, align 8
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
  %catchcond27 = icmp ne i8* %10, null
  br i1 %catchcond27, label %then_block_b28, label %entry_ifend_b29

entry_ifend26:                                    ; preds = %entry_ifend15
  %stack_offset_value30 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value30, i64* %"lvar$0$", align 8
  %stack_offset_address_value31 = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value32 = load i64, i64* %stack_offset_address_value31, align 8
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
  call void @try_function(i64* %info, i64 0, i32 0, i64 0)
  br label %try_enda

then_block_b28:                                   ; preds = %then_block25
  call void @try_function(i64* %info, i64 0, i32 0)
  br label %catch_labela

entry_ifend_b29:                                  ; preds = %then_block25
  ret i32 0

catch_labela:                                     ; preds = %entry_after_goto, %then_block_b28
  store i64 0, i64* %"lvar$1$"
  %12 = zext i64* %"lvar$1$" to i64
  store i64 %12, i64* %"lvar$1$", align 8
  %13 = call i32 @create_string_object(i8* inttoptr (i64 45306684 to i8*))
  call void @push_jit_object(i32 %13)
  %14 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45306688 to i8*))
  %ifcond40 = icmp eq i64* %14, null
  br i1 %ifcond40, label %then_block38, label %entry_ifend39

try_enda:                                         ; preds = %entry_ifend50, %entry_ifend26
  store i64 0, i64* %stack, align 8
  ret i32 1

entry_after_goto:                                 ; No predecessors!
  br label %catch_labela

then_block38:                                     ; preds = %catch_labela
  ret i32 0

entry_ifend39:                                    ; preds = %catch_labela
  %lvar41 = load i64, i64* %"lvar$0$"
  %lvar_offset_value42 = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value42, align 8
  store i64 %lvar41, i64* %lvar_offset_value42, align 8
  %lvar43 = load i64, i64* %"lvar$1$"
  %lvar_offset_value44 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value44, align 8
  store i64 %lvar43, i64* %lvar_offset_value44, align 8
  %loaded_stack_ptr_address_value45 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value45, align 8
  %15 = zext i32 %13 to i64
  store i64 %15, i64* %loaded_stack_ptr_address_value45, align 8
  %loaded_stack_ptr_address_value46 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value47 = getelementptr i64, i64* %loaded_stack_ptr_address_value46, i64 1
  store i64* %inc_ptr_value47, i64** %stack_ptr_address
  %16 = call i32 @call_invoke_method(i64* %14, i32 3, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond48 = icmp ne i32 %16, 1
  br i1 %ifcond48, label %then_block49, label %entry_ifend50

then_block49:                                     ; preds = %entry_ifend39
  %17 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond51 = icmp ne i8* %17, null
  br i1 %catchcond51, label %then_block_b52, label %entry_ifend_b53

entry_ifend50:                                    ; preds = %entry_ifend39
  %stack_offset_value54 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value54, i64* %"lvar$0$", align 8
  %stack_offset_address_value55 = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value56 = load i64, i64* %stack_offset_address_value55, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value56, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value57 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value58 = getelementptr i64, i64* %loaded_stack_ptr_address_value57, i64 -1
  %stack_pointer_offset_value59 = load i64, i64* %stack_pointer_offset_value58, align 8
  %18 = trunc i64 %stack_pointer_offset_value59 to i32
  call void @push_jit_object(i32 %18)
  %loaded_stack_ptr_address_value60 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value61 = getelementptr i64, i64* %loaded_stack_ptr_address_value60, i64 1
  store i64* %dec_ptr_value61, i64** %stack_ptr_address
  br label %try_enda

then_block_b52:                                   ; preds = %then_block49
  ret i32 0

entry_ifend_b53:                                  ; preds = %then_block49
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTest.run12()$$14"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %lvar1 = load i64, i64* %"lvar$1$"
  %0 = trunc i64 %lvar1 to i32
  %eqtmpx = icmp eq i32 %0, 1
  store i64 0, i64* %"lvar$2$"
  %1 = zext i1 %eqtmpx to i64
  store i64 %1, i64* %"lvar$2$", align 8
  %lvar2 = load i64, i64* %"lvar$2$"
  %2 = trunc i64 %lvar2 to i32
  %3 = zext i32 %2 to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}
; ModuleID = 'Module JITTestClassA'

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

declare void @try_function(i64*, i32, i64*)

declare void @catch_function(i64*, i64*)

declare i8* @get_try_catch_label_name(i64*)

declare void @entry_exception_object(i32, i64*)

declare i64 @get_field_from_object(i64**, i64*, i32, i64*, i32, i32)

declare i32 @regex_equals(i32, i32)

declare i32 @get_string_object_of_object_name(i32)

declare i32 @object_implements_interface(i32, i64*)

declare i32 @call_invoke_virtual_method(i32, i64*, i32, i64**, i64*, i64*, i32)

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

define i32 @"JITTestClassA.method(int)$$2"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %lvar2 = load i64, i64* %"lvar$1$"
  %0 = trunc i64 %lvar2 to i32
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.method2()$$3"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45299996 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 45300008 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45300020 to i8*))
  %ifcond3 = icmp eq i64* %3, null
  br i1 %ifcond3, label %then_block1, label %entry_ifend2

then_block1:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend2:                                     ; preds = %entry_ifend
  %lvar4 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar4, i64* %lvar_offset_value, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value6, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %loaded_stack_ptr_address_value6, align 8
  %loaded_stack_ptr_address_value7 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value8 = getelementptr i64, i64* %loaded_stack_ptr_address_value7, i64 1
  store i64* %inc_ptr_value8, i64** %stack_ptr_address
  %6 = call i32 @call_invoke_method(i64* %3, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond9 = icmp ne i32 %6, 1
  br i1 %ifcond9, label %then_block10, label %entry_ifend11

then_block10:                                     ; preds = %entry_ifend2
  %7 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %7, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  call void @entry_exception_object(i64 %stack_pointer_offset_value14, i64* %info)
  ret i32 0

then_block_b:                                     ; preds = %then_block10
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block10
  ret i32 0

entry_after_throw:                                ; No predecessors!
  store i64 0, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.classMethod()$$4"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  store i64 1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.classMethod(int,int)$$5"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %lvar2 = load i64, i64* %"lvar$0$"
  %0 = trunc i64 %lvar2 to i32
  %lvar3 = load i64, i64* %"lvar$1$"
  %1 = trunc i64 %lvar3 to i32
  %addtmp = add nuw i32 %0, %1
  %2 = zext i32 %addtmp to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.getValue()$$6"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %lvar1 = load i64, i64* %"lvar$0$"
  %0 = trunc i64 %lvar1 to i32
  %1 = call i64 @get_field_from_object(i64** %stack_ptr_address, i64* %stack, i32 %var_num, i64* %info, i32 %0, i32 0)
  %2 = getelementptr inbounds %clvalue_and_bool_struct, i64 %1, i32 0, i32 0
  %3 = getelementptr inbounds %clvalue_and_bool_struct, i64 %1, i32 0, i32 1
  %ifcond = icmp eq i32 addrspace(64)* %3, i32 0
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %4 = trunc i64 addrspace(64)* %2 to i32
  %5 = zext i32 %4 to i64
  store i64 %5, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.runException()$$7"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45300032 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i32 @create_string_object(i8* inttoptr (i64 45300044 to i8*))
  call void @push_jit_object(i32 %2)
  %3 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 45300048 to i8*))
  %ifcond3 = icmp eq i64* %3, null
  br i1 %ifcond3, label %then_block1, label %entry_ifend2

then_block1:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend2:                                     ; preds = %entry_ifend
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value5, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %loaded_stack_ptr_address_value5, align 8
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value7 = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %inc_ptr_value7, i64** %stack_ptr_address
  %6 = call i32 @call_invoke_method(i64* %3, i32 0, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond8 = icmp ne i32 %6, 1
  br i1 %ifcond8, label %then_block9, label %entry_ifend10

then_block9:                                      ; preds = %entry_ifend2
  %7 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %7, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

entry_ifend10:                                    ; preds = %entry_ifend2
  %loaded_stack_ptr_address_value11 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value11, i64 -1
  %stack_pointer_offset_value12 = load i64, i64* %stack_pointer_offset_value, align 8
  %8 = trunc i64 %stack_pointer_offset_value12 to i32
  call void @push_jit_object(i32 %8)
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value12, i64* %stack
  call void @entry_exception_object(i64 %stack_pointer_offset_value12, i64* %info)
  ret i32 0

then_block_b:                                     ; preds = %then_block9
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block9
  ret i32 0

entry_after_throw:                                ; No predecessors!
  store i64 0, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.method_byte(byte)$$8"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.aaaa()$$9"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  store i64 123, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"JITTestClassA.method10(int,int,lambda)$$10"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %lvar6 = load i64, i64* %"lvar$3$"
  %0 = trunc i64 %lvar6 to i32
  %lvar7 = load i64, i64* %"lvar$1$"
  %1 = trunc i64 %lvar7 to i32
  %lvar8 = load i64, i64* %"lvar$2$"
  %2 = trunc i64 %lvar8 to i32
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %3 = zext i32 %0 to i64
  store i64 %3, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value9 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value9, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value10 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value10, align 8
  %4 = zext i32 %1 to i64
  store i64 %4, i64* %loaded_stack_ptr_address_value10, align 8
  %loaded_stack_ptr_address_value11 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value12 = getelementptr i64, i64* %loaded_stack_ptr_address_value11, i64 1
  store i64* %inc_ptr_value12, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value13, align 8
  %5 = zext i32 %2 to i64
  store i64 %5, i64* %loaded_stack_ptr_address_value13, align 8
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

entry_after_return:                               ; No predecessors!
  ret i32 1
}
