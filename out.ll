; ModuleID = 'EvaLLVM'
source_filename = "EvaLLVM"

@0 = private unnamed_addr constant [13 x i8] c"Hello papi!\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @0)
  ret i32 0
}
