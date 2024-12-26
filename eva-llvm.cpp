
#include "./src/EvaLLVM.h"

int main(int argc, char const *argv[]) {
  /**
   * Program to execute.
   */
  std::string program = R"(
    (printf "Value 1: %d\n" 69)
  )";

  /**
   * Compiler instance.
   */
  EvaLLVM vm;
  
  /**
   * Generate LLVM IR.
   */
   vm.exec(program);
  return 0;
}

