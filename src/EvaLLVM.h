#ifndef EvaLLVM_h
#define EvaLLVM_h

#include <string>
#include <memory>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

class EvaLLVM {
public:
  EvaLLVM() {
    moduleInit();
    setupExternFunctions();
  }

/**
 * Executes a program.
 */
void exec(const std::string &program) {
    // 1. Parse the program
    // auto ast = parser->parser(program);

    // 2. Compile to LLVM IR:
     compile();
    
    // Print generated code.
    module->print(llvm::outs(), nullptr);

    // 3. Save module IR to file:
    saveModuleToFile("./out.ll");
}

private:
  
  /**
   * Main compile loop.
   */
  llvm::Value *gen(/* exp */) {
  //  return builder->getInt32(42);
  
  //strings:
    auto str = builder->CreateGlobalStringPtr("Hello papi!\n");
  
  // call to printf:
  auto printfFn = module->getFunction("printf");

  // args
  std::vector<llvm::Value*> args{str};
  
  return builder->CreateCall(printfFn, args);
}

  /**
   * Define external functions.
   */
  void setupExternFunctions() {
    // i8 to substitute for char*, void*, etc.
    auto bytePtrTy = builder->getInt8Ty()->getPointerTo();

    // int printf(const char *format, ...)
    module->getOrInsertFunction("printf", llvm::FunctionType::get(builder->getInt32Ty(), bytePtrTy, true));
  }

  /**
   * Creates a function.
   */
  llvm::Function *createFunction(const std::string &fnName, llvm::FunctionType *fnType) {
    // Fuction prototype might alreadey be defined:
    auto fn = module->getFunction(fnName);

    // If not, allocate the function:
    if (fn == nullptr) {
      fn = createFunctionProto(fnName, fnType);
    }

    createFunctionBlock(fn);
    return fn;
  }

  /**
   * Creates function prototype (defines the function, but not the body)
   */
  llvm::Function *createFunctionProto(const std::string &fnName, llvm::FunctionType *fnType) {
    auto fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, fnName, *module);
    verifyFunction(*fn);
    return fn;
  }

  /**
   * Creates a function block.
   */
  void createFunctionBlock(llvm::Function *fn) {
    auto entry = createBB("entry", fn);
    builder->SetInsertPoint(entry);
  }

  /**
   * 
   */
  llvm::BasicBlock *createBB(std::string name, llvm::Function *fn = nullptr) {
    return llvm::BasicBlock::Create(*ctx, name, fn);
  }
  

  /**
   * Currently compiling function.
   */
  llvm::Function *fn;


  /**
   * Compiles an expression.
   */
  void compile(/*TODO: ast*/) {
    // 1. Create main function.
    fn = createFunction("main", llvm::FunctionType::get(/* return type */ builder->getInt32Ty()
                                                        /* varargs */, false));

    // 2. Compile main body.
    gen(/* ast */);
    
    builder->CreateRet(builder->getInt32(0));
  }


  /**
   * Saves IR to file.
   */
   void saveModuleToFile(const std::string &fileName) {
     std::error_code errorCode;
     llvm::raw_fd_ostream outLL(fileName, errorCode);
     module->print(outLL, nullptr);
   } 

  /**
   * Initialize the module.
   */
  void moduleInit() {
    ctx = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("EvaLLVM", *ctx);
    builder = std::make_unique<llvm::IRBuilder<>>(*ctx);
  }

  std::unique_ptr<llvm::LLVMContext> ctx;
  std::unique_ptr<llvm::Module> module;
  std::unique_ptr<llvm::IRBuilder<>> builder;
};

#endif