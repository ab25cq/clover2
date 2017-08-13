; ModuleID = 'ClassF.bc'
source_filename = "Module ClassF"

define i32 @"ClassF.method()___________0"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num) {
entry:
  %"lvar$0$" = alloca i64
  store i64 0, i64* %"lvar$0$"
  store i64 1, i64* %"lvar$0$"
  %lvar1 = load i64, i64* %"lvar$0$"
  ret i64 %lvar1
}
