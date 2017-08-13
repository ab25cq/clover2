define i32 @"ClassF.method()$$0"(i64* %stack_ptr, i64* %lvar, i64* %info, i64* %stack, i64** %stack_ptr_address, i32 %var_num) 
{
entry:
    %"lvar$0$" = alloca i64
    store i64 1, i64* %stack, align 4
    ret i32 1

  entry_after_return:                               ; No predecessors!
    ret i32 1
}
