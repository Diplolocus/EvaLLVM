
#include "./src/EvaLLVM.h"

int main(int argc, char const *argv[]) {
  /**
   * Program to execute.
   */
  std::string program = R"(
     42
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

