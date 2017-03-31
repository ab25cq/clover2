; ModuleID = 'a.c'
source_filename = "a.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%union.CLVALUEUnion = type { i64 }

@stack = internal global [1024 x %union.CLVALUEUnion] zeroinitializer, align 16
@stack_ptr = internal global %union.CLVALUEUnion* null, align 8
@.str = private unnamed_addr constant [4 x i8] c"%p\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store %union.CLVALUEUnion* getelementptr inbounds ([1024 x %union.CLVALUEUnion], [1024 x %union.CLVALUEUnion]* @stack, i32 0, i32 0), %union.CLVALUEUnion** @stack_ptr, align 8
  %2 = load %union.CLVALUEUnion*, %union.CLVALUEUnion** @stack_ptr, align 8
  %3 = bitcast %union.CLVALUEUnion* %2 to i32*
  store i32 1, i32* %3, align 8
  %4 = load %union.CLVALUEUnion*, %union.CLVALUEUnion** @stack_ptr, align 8
  %5 = getelementptr inbounds %union.CLVALUEUnion, %union.CLVALUEUnion* %4, i64 1
  store %union.CLVALUEUnion* %5, %union.CLVALUEUnion** @stack_ptr, align 8
  %6 = load %union.CLVALUEUnion*, %union.CLVALUEUnion** @stack_ptr, align 8
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), %union.CLVALUEUnion* %6)
  %8 = load %union.CLVALUEUnion*, %union.CLVALUEUnion** @stack_ptr, align 8
  %9 = getelementptr inbounds %union.CLVALUEUnion, %union.CLVALUEUnion* %8, i64 -1
  %10 = bitcast %union.CLVALUEUnion* %9 to i32*
  %11 = load i32, i32* %10, align 8
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %11)
  call void @exit(i32 0) #3
  unreachable
                                                  ; No predecessors!
  %14 = load i32, i32* %1, align 4
  ret i32 %14
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: noreturn nounwind
declare void @exit(i32) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0-svn297204-1~exp1 (branches/release_40)"}
