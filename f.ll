; ModuleID = 'Module ClassF'

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

define i32 @"ClassF.method()$$0"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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

define i32 @"ClassF.method2()$$1"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 1066192077, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method3()$$2"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 4607632778762754458, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method4(int)$$3"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  store i64 1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method5(int)$$4"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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

define i32 @"ClassF.method6()$$5"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 3, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method7(int,int)$$6"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %stack_offset_address_value2 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value3 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value3, i64* %"lvar$2$", align 8
  %lvar4 = load i64, i64* %"lvar$1$"
  %0 = trunc i64 %lvar4 to i32
  %lvar5 = load i64, i64* %"lvar$2$"
  %1 = trunc i64 %lvar5 to i32
  %addtmp = add nuw i32 %0, %1
  %2 = zext i32 %addtmp to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method8(double,double)$$7"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %stack_offset_address_value2 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value3 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value3, i64* %"lvar$2$", align 8
  %lvar4 = load i64, i64* %"lvar$1$"
  %0 = uitofp i64 %lvar4 to double
  %lvar5 = load i64, i64* %"lvar$2$"
  %1 = uitofp i64 %lvar5 to double
  %faddtmp = fadd double %0, %1
  %2 = bitcast double %faddtmp to i64
  store i64 %2, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method9(double)$$8"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %0 = uitofp i64 %lvar2 to double
  %faddtmp = fadd double %0, 3.100000e+00
  %1 = bitcast double %faddtmp to i64
  store i64 %1, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method10()$$9"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %lvar1 = load i64, i64* %"lvar$0$"
  %0 = trunc i64 %lvar1 to i32
  %1 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 47578664 to i8*))
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
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value4, align 8
  store i64 4607182418800017408, i64* %loaded_stack_ptr_address_value4, align 8
  %loaded_stack_ptr_address_value5 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value6 = getelementptr i64, i64* %loaded_stack_ptr_address_value5, i64 1
  store i64* %inc_ptr_value6, i64** %stack_ptr_address
  %3 = call i32 @call_invoke_method(i64* %1, i32 8, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond7 = icmp ne i32 %3, 1
  br i1 %ifcond7, label %then_block8, label %entry_ifend9

then_block8:                                      ; preds = %entry_ifend
  %4 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %4, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

entry_ifend9:                                     ; preds = %entry_ifend
  %stack_offset_value10 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value10, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value11 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value11, i64 -1
  %stack_pointer_offset_value12 = load i64, i64* %stack_pointer_offset_value, align 8
  %5 = trunc i64 %stack_pointer_offset_value12 to i32
  call void @push_jit_object(i32 %5)
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value12, i64* %stack, align 8
  ret i32 1

then_block_b:                                     ; preds = %then_block8
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block8
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method11(int)$$10"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %1 = sitofp i32 %0 to float
  %2 = fpext float %1 to double
  %faddtmp = fadd double 1.100000e+00, %2
  %3 = fptrunc double %faddtmp to float
  %4 = fpext float %3 to double
  %5 = bitcast double %4 to i64
  store i64 %5, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method12(int)$$11"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %1 = sitofp i32 %0 to float
  %faddtmp = fadd float 0x3FF19999A0000000, %1
  %2 = fpext float %faddtmp to double
  %3 = bitcast double %2 to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method13(int)$$12"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %1 = sitofp i32 %0 to double
  %faddtmp = fadd double 1.100000e+00, %1
  %2 = fptrunc double %faddtmp to float
  %3 = fpext float %2 to double
  %4 = bitcast double %3 to i64
  store i64 %4, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method14(int)$$13"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %1 = sitofp i32 %0 to float
  %2 = fpext float %1 to double
  %3 = bitcast double %2 to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method14(pointer)$$14"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %0 = inttoptr i64 %lvar2 to i64*
  %value2 = ptrtoint i64* %0 to i32
  %1 = sitofp i32 %value2 to float
  %2 = fpext float %1 to double
  %3 = bitcast double %2 to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method15(double,float)$$15"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %stack_offset_address_value2 = getelementptr i64, i64* %stack, i64 2
  %stack_offset_value3 = load i64, i64* %stack_offset_address_value2, align 8
  store i64 0, i64* %"lvar$2$"
  store i64 %stack_offset_value3, i64* %"lvar$2$", align 8
  %lvar4 = load i64, i64* %"lvar$1$"
  %0 = uitofp i64 %lvar4 to double
  %lvar5 = load i64, i64* %"lvar$2$"
  %1 = uitofp i64 %lvar5 to float
  %2 = fpext float %1 to double
  %faddtmp = fadd double %0, %2
  %value2 = fptosi double %faddtmp to i32
  %3 = zext i32 %value2 to i64
  store i64 %3, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method16()$$16"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 47578672 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 47578684 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block1, label %entry_ifend2

then_block1:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend2:                                     ; preds = %entry_ifend
  %lvar4 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar4, i64* %lvar_offset_value, align 8
  %lvar5 = load i64, i64* %"lvar$1$"
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 %lvar5, i64* %lvar_offset_value6, align 8
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
  %catchcond = icmp ne i8* %5, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  %lvar16 = load i64, i64* %"lvar$1$"
  %7 = trunc i64 %lvar16 to i32
  %8 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 47578696 to i8*))
  %ifcond19 = icmp eq i64* %8, null
  br i1 %ifcond19, label %then_block17, label %entry_ifend18

then_block_b:                                     ; preds = %then_block9
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block9
  ret i32 0

then_block17:                                     ; preds = %entry_ifend10
  ret i32 0

entry_ifend18:                                    ; preds = %entry_ifend10
  %lvar20 = load i64, i64* %"lvar$0$"
  %lvar_offset_value21 = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value21, align 8
  store i64 %lvar20, i64* %lvar_offset_value21, align 8
  %lvar22 = load i64, i64* %"lvar$1$"
  %lvar_offset_value23 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value23, align 8
  store i64 %lvar22, i64* %lvar_offset_value23, align 8
  %loaded_stack_ptr_address_value24 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value24, align 8
  %9 = zext i32 %7 to i64
  store i64 %9, i64* %loaded_stack_ptr_address_value24, align 8
  %loaded_stack_ptr_address_value25 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value26 = getelementptr i64, i64* %loaded_stack_ptr_address_value25, i64 1
  store i64* %inc_ptr_value26, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value27 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value27, align 8
  store i64 1, i64* %loaded_stack_ptr_address_value27, align 8
  %loaded_stack_ptr_address_value28 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value29 = getelementptr i64, i64* %loaded_stack_ptr_address_value28, i64 1
  store i64* %inc_ptr_value29, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value30 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value30, align 8
  store i64 2, i64* %loaded_stack_ptr_address_value30, align 8
  %loaded_stack_ptr_address_value31 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value32 = getelementptr i64, i64* %loaded_stack_ptr_address_value31, i64 1
  store i64* %inc_ptr_value32, i64** %stack_ptr_address
  %10 = call i32 @call_invoke_method(i64* %8, i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond33 = icmp ne i32 %10, 1
  br i1 %ifcond33, label %then_block34, label %entry_ifend35

then_block34:                                     ; preds = %entry_ifend18
  %11 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond36 = icmp ne i8* %11, null
  br i1 %catchcond36, label %then_block_b37, label %entry_ifend_b38

entry_ifend35:                                    ; preds = %entry_ifend18
  %stack_offset_value39 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value39, i64* %"lvar$0$", align 8
  %stack_offset_address_value40 = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value41 = load i64, i64* %stack_offset_address_value40, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value41, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value42 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value43 = getelementptr i64, i64* %loaded_stack_ptr_address_value42, i64 -1
  %stack_pointer_offset_value44 = load i64, i64* %stack_pointer_offset_value43, align 8
  %12 = trunc i64 %stack_pointer_offset_value44 to i32
  call void @push_jit_object(i32 %12)
  %loaded_stack_ptr_address_value45 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value46 = getelementptr i64, i64* %loaded_stack_ptr_address_value45, i64 1
  store i64* %dec_ptr_value46, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value44, i64* %stack, align 8
  ret i32 1

then_block_b37:                                   ; preds = %then_block34
  ret i32 0

entry_ifend_b38:                                  ; preds = %then_block34
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method17()$$17"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$1$" = alloca i64
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  store i64 0, i64* %"lvar$1$"
  store i64 0, i64* %"lvar$1$", align 8
  %0 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 47578708 to i8*))
  %ifcond = icmp eq i64* %0, null
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  ret i32 0

entry_ifend:                                      ; preds = %entry
  %1 = call i32 @create_object(i64* %0)
  call void @push_jit_object(i32 %1)
  %2 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 47578720 to i8*))
  %ifcond3 = icmp eq i64* %2, null
  br i1 %ifcond3, label %then_block1, label %entry_ifend2

then_block1:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend2:                                     ; preds = %entry_ifend
  %lvar4 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar4, i64* %lvar_offset_value, align 8
  %lvar5 = load i64, i64* %"lvar$1$"
  %lvar_offset_value6 = getelementptr i64, i64* %lvar, i64 1
  store i64 0, i64* %lvar_offset_value6, align 8
  store i64 %lvar5, i64* %lvar_offset_value6, align 8
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
  %catchcond = icmp ne i8* %5, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

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
  %lvar16 = load i64, i64* %"lvar$1$"
  %7 = trunc i64 %lvar16 to i32
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
  %8 = zext i32 %7 to i64
  store i64 %8, i64* %loaded_stack_ptr_address_value21, align 8
  %loaded_stack_ptr_address_value22 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value23 = getelementptr i64, i64* %loaded_stack_ptr_address_value22, i64 1
  store i64* %inc_ptr_value23, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value24 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value24, align 8
  store i64 1, i64* %loaded_stack_ptr_address_value24, align 8
  %loaded_stack_ptr_address_value25 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value26 = getelementptr i64, i64* %loaded_stack_ptr_address_value25, i64 1
  store i64* %inc_ptr_value26, i64** %stack_ptr_address
  %loaded_stack_ptr_address_value27 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value27, align 8
  store i64 2, i64* %loaded_stack_ptr_address_value27, align 8
  %loaded_stack_ptr_address_value28 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value29 = getelementptr i64, i64* %loaded_stack_ptr_address_value28, i64 1
  store i64* %inc_ptr_value29, i64** %stack_ptr_address
  %9 = call i32 @call_invoke_virtual_method(i32 1356, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %constant, i32 %7)
  %ifcond30 = icmp ne i32 %9, 1
  br i1 %ifcond30, label %then_block31, label %entry_ifend32

then_block_b:                                     ; preds = %then_block9
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block9
  ret i32 0

then_block31:                                     ; preds = %entry_ifend10
  %10 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond33 = icmp ne i8* %10, null
  br i1 %catchcond33, label %then_block_b34, label %entry_ifend_b35

entry_ifend32:                                    ; preds = %entry_ifend10
  %stack_offset_value36 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value36, i64* %"lvar$0$", align 8
  %stack_offset_address_value37 = getelementptr i64, i64* %stack, i64 1
  %stack_offset_value38 = load i64, i64* %stack_offset_address_value37, align 8
  store i64 0, i64* %"lvar$1$"
  store i64 %stack_offset_value38, i64* %"lvar$1$", align 8
  %loaded_stack_ptr_address_value39 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value40 = getelementptr i64, i64* %loaded_stack_ptr_address_value39, i64 -1
  %stack_pointer_offset_value41 = load i64, i64* %stack_pointer_offset_value40, align 8
  %11 = trunc i64 %stack_pointer_offset_value41 to i32
  call void @push_jit_object(i32 %11)
  %loaded_stack_ptr_address_value42 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value43 = getelementptr i64, i64* %loaded_stack_ptr_address_value42, i64 1
  store i64* %dec_ptr_value43, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value41, i64* %stack, align 8
  ret i32 1

then_block_b34:                                   ; preds = %then_block31
  ret i32 0

entry_ifend_b35:                                  ; preds = %then_block31
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method18()$$18"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 47578748 to i8*))
  call void @push_jit_object(i32 %0)
  %lvar1 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar1, i64* %lvar_offset_value, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %2 = call i32 @call_invoke_dynamic_method(i32 1376, i32 1384, i32 1, i32 1, i32 0, i32 1, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %code, i64* %constant)
  %ifcond = icmp ne i32 %2, 1
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  %3 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %3, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

entry_ifend:                                      ; preds = %entry
  %stack_offset_value3 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value3, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 -1
  %stack_pointer_offset_value5 = load i64, i64* %stack_pointer_offset_value, align 8
  %4 = trunc i64 %stack_pointer_offset_value5 to i32
  call void @push_jit_object(i32 %4)
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  store i64 0, i64* %stack, align 8
  ret i32 1

then_block_b:                                     ; preds = %then_block
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method19()$$19"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
entry:
  %"lvar$0$" = alloca i64
  %stack_offset_value = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value, i64* %"lvar$0$", align 8
  %0 = call i32 @create_string_object(i8* inttoptr (i64 47578764 to i8*))
  call void @push_jit_object(i32 %0)
  %lvar1 = load i64, i64* %"lvar$0$"
  %lvar_offset_value = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value, align 8
  store i64 %lvar1, i64* %lvar_offset_value, align 8
  %loaded_stack_ptr_address_value = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value, align 8
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %loaded_stack_ptr_address_value, align 8
  %loaded_stack_ptr_address_value2 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value2, i64 1
  store i64* %inc_ptr_value, i64** %stack_ptr_address
  %2 = call i32 @call_invoke_dynamic_method(i32 1392, i32 1400, i32 1, i32 1, i32 0, i32 2, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info, i64* %code, i64* %constant)
  %ifcond = icmp ne i32 %2, 1
  br i1 %ifcond, label %then_block, label %entry_ifend

then_block:                                       ; preds = %entry
  %3 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond = icmp ne i8* %3, null
  br i1 %catchcond, label %then_block_b, label %entry_ifend_b

entry_ifend:                                      ; preds = %entry
  %stack_offset_value3 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value3, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value4 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value = getelementptr i64, i64* %loaded_stack_ptr_address_value4, i64 -1
  %stack_pointer_offset_value5 = load i64, i64* %stack_pointer_offset_value, align 8
  %4 = trunc i64 %stack_pointer_offset_value5 to i32
  call void @push_jit_object(i32 %4)
  %loaded_stack_ptr_address_value6 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value = getelementptr i64, i64* %loaded_stack_ptr_address_value6, i64 1
  store i64* %dec_ptr_value, i64** %stack_ptr_address
  %5 = call i64* @get_class_with_load_and_initialize_in_jit(i8* inttoptr (i64 47578780 to i8*))
  %ifcond9 = icmp eq i64* %5, null
  br i1 %ifcond9, label %then_block7, label %entry_ifend8

then_block_b:                                     ; preds = %then_block
  ret i32 0

entry_ifend_b:                                    ; preds = %then_block
  ret i32 0

then_block7:                                      ; preds = %entry_ifend
  ret i32 0

entry_ifend8:                                     ; preds = %entry_ifend
  %lvar10 = load i64, i64* %"lvar$0$"
  %lvar_offset_value11 = getelementptr i64, i64* %lvar, i64 0
  store i64 0, i64* %lvar_offset_value11, align 8
  store i64 %lvar10, i64* %lvar_offset_value11, align 8
  %loaded_stack_ptr_address_value12 = load i64*, i64** %stack_ptr_address, align 8
  store i64 0, i64* %loaded_stack_ptr_address_value12, align 8
  store i64 %stack_pointer_offset_value5, i64* %loaded_stack_ptr_address_value12, align 8
  %loaded_stack_ptr_address_value13 = load i64*, i64** %stack_ptr_address
  %inc_ptr_value14 = getelementptr i64, i64* %loaded_stack_ptr_address_value13, i64 1
  store i64* %inc_ptr_value14, i64** %stack_ptr_address
  %6 = call i32 @call_invoke_method(i64* %5, i32 11, i64* %stack, i32 %var_num, i64** %stack_ptr_address, i64* %info)
  %ifcond15 = icmp ne i32 %6, 1
  br i1 %ifcond15, label %then_block16, label %entry_ifend17

then_block16:                                     ; preds = %entry_ifend8
  %7 = call i8* @get_try_catch_label_name(i64* %info)
  %catchcond18 = icmp ne i8* %7, null
  br i1 %catchcond18, label %then_block_b19, label %entry_ifend_b20

entry_ifend17:                                    ; preds = %entry_ifend8
  %stack_offset_value21 = load i64, i64* %stack, align 8
  store i64 0, i64* %"lvar$0$"
  store i64 %stack_offset_value21, i64* %"lvar$0$", align 8
  %loaded_stack_ptr_address_value22 = load i64*, i64** %stack_ptr_address
  %stack_pointer_offset_value23 = getelementptr i64, i64* %loaded_stack_ptr_address_value22, i64 -1
  %stack_pointer_offset_value24 = load i64, i64* %stack_pointer_offset_value23, align 8
  %8 = trunc i64 %stack_pointer_offset_value24 to i32
  call void @push_jit_object(i32 %8)
  %loaded_stack_ptr_address_value25 = load i64*, i64** %stack_ptr_address
  %dec_ptr_value26 = getelementptr i64, i64* %loaded_stack_ptr_address_value25, i64 1
  store i64* %dec_ptr_value26, i64** %stack_ptr_address
  store i64 %stack_pointer_offset_value24, i64* %stack, align 8
  ret i32 1

then_block_b19:                                   ; preds = %then_block16
  ret i32 0

entry_ifend_b20:                                  ; preds = %then_block16
  ret i32 0

entry_after_return:                               ; No predecessors!
  ret i32 1
}

define i32 @"ClassF.method20()$$20"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num, i64* %constant, i64* %code) {
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
  %lvar1 = load i64, i64* %"lvar$1$"
  %0 = trunc i64 %lvar1 to i32
  store i64 0, i64* %"lvar$2$"
  %1 = zext i32 %0 to i64
  store i64 %1, i64* %"lvar$2$", align 8
  store i64 0, i64* %stack, align 8
  ret i32 1

entry_after_return:                               ; No predecessors!
  ret i32 1
}
