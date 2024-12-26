; ModuleID = 'EvaLLVM_module'
source_filename = "EvaLLVM_module"

@0 = private unnamed_addr constant [11 x i8] c"Value: %d\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %0 = call i32 (ptr, ...) @printf(ptr @0, i32 42)
  ret i32 0
}
