#include "BasicBlock.h"
#include "Constants.h"
#include "Function.h"
#include "IRBuilder.h"
#include "LLVMContext.h"
#include "LiveVar.h"
#include "Module.h"
#include "ModuleAnalyse.h"
#include "RegAssign.h"
#include "Type.h"

#include <iostream>
#include <memory>

using namespace YAL;
using namespace semimachine;

int main() {
  LLVMContext context;
  IRBuilder builder(context);

  auto module = new Module("gen_fib", context);

  // std::cout << "----Create fib_args----" <<std::endl;
  std::vector<Type *> fib_args = {Type::getInt32Ty(context)};
  // std::cout << "----Finish fib_args----" <<std::endl;
  // std::cout << "----Create fib_functype----" <<std::endl;
  FunctionType *fib_func_type = FunctionType::get(Type::getInt32Ty(context), fib_args, false);
  // std::cout << "----Finish fib_functype----" <<std::endl;
  auto fib_func = Function::Create(fib_func_type, "fib", module);

  // set parameter n
  // fib_arg is Value *
  auto fib_arg = fib_func->Arg_begin();

  // basic blocks
  // std::cout << "basic blocks" <<std::endl;
  auto fib_entry_block = BasicBlock::Create(context, "fib_entry", fib_func);
  auto fib_return_block = BasicBlock::Create(context, "fib_return", fib_func);
  auto fib_zero_case_block = BasicBlock::Create(context, "zero_case", fib_func);
  auto fib_non_zero_case_block = BasicBlock::Create(context, "non_zero_case", fib_func);
  auto fib_one_case_block = BasicBlock::Create(context, "one_case", fib_func);
  auto fib_recursive_case_block = BasicBlock::Create(context, "recursive_case", fib_func);

  builder.SetInsertPoint(fib_entry_block);
  auto array_type = ArrayType::get(Type::getInt32Ty(context), 3);
  auto array = builder.CreateAlloca(array_type, ConstantInt::get(context, 3));
  auto fib_ret = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "ret_value");
  // std::cout << "Create Constant Int 0 " <<std::endl;
  auto fib_first_cond = builder.CreateICmpEQ(*fib_arg, ConstantInt::get(context, 0));
  // BranchInst is a subclass of Value
  builder.CreateCondBr(fib_first_cond, fib_zero_case_block, fib_non_zero_case_block);

  // n == 0
  builder.SetInsertPoint(fib_zero_case_block);
  builder.CreateStore(ConstantInt::get(context, 0), fib_ret);
  builder.CreateBr(fib_return_block);

  // n != 0
  // std::cout << "L55 " <<std::endl;
  builder.SetInsertPoint(fib_non_zero_case_block);
  // std::cout << "L57 " <<std::endl;
  auto fib_second_cond = builder.CreateICmpEQ(*fib_arg, ConstantInt::get(context, 1));
  // std::cout << "L59 " <<std::endl;
  builder.CreateCondBr(fib_second_cond, fib_one_case_block, fib_recursive_case_block);

  // n == 1
  // std::cout << "L63 " <<std::endl;
  builder.SetInsertPoint(fib_one_case_block);
  // std::cout << "L65 " <<std::endl;
  builder.CreateStore(ConstantInt::get(context, 1), fib_ret);
  // std::cout << "L67 " <<std::endl;
  builder.CreateBr(fib_return_block);

  // otherwise
  // std::cout << "L71 " <<std::endl;
  builder.SetInsertPoint(fib_recursive_case_block);
  // std::cout << "L73 " <<std::endl;
  auto fib_sub_by_1 = builder.CreateNSWSub(*fib_arg, ConstantInt::get(context, 1), "sub_1_temp");
  // std::cout << "L75 " <<std::endl;
  auto fib_call_fib_1 = builder.CreateCall(fib_func, {fib_sub_by_1}, "call_fib_1");
  // std::cout << "L77 " <<std::endl;
  auto fib_sub_by_2 = builder.CreateNSWSub(fib_sub_by_1, ConstantInt::get(context, 1), "sub_2_temp");
  // std::cout << "L79 " <<std::endl;
  auto fib_call_fib_2 = builder.CreateCall(fib_func, {fib_sub_by_2}, "call_fib_2");
  // std::cout << "L81 " <<std::endl;
  auto fib_result_add = builder.CreateNSWAdd(fib_call_fib_1, fib_call_fib_2, "add_temp");
  // std::cout << "L83 " <<std::endl;
  builder.CreateStore(fib_result_add, fib_ret);
  // std::cout << "L85 " <<std::endl;
  builder.CreateBr(fib_return_block);

  // return
  // std::cout << "L89 " <<std::endl;
  builder.SetInsertPoint(fib_return_block);
  // std::cout << "L91 " <<std::endl;
  auto fib_return_result = builder.CreateLoad(fib_ret);
  // std::cout << "L93 " <<std::endl;
  builder.CreateRet(fib_return_result);

  FunctionType *main_func_type = FunctionType::get(Type::getInt32Ty(context), std::vector<Type *>(), false);
  auto main_func = Function::Create(main_func_type, "main", module);

  // basic blocks
  auto main_entry_block = BasicBlock::Create(context, "main_entry", main_func);
  auto main_return_block = BasicBlock::Create(context, "main_return", main_func);
  auto main_cond_block = BasicBlock::Create(context, "cond", main_func);
  auto main_loop_block = BasicBlock::Create(context, "loop", main_func);

  // initialization
  builder.SetInsertPoint(main_entry_block);
  auto main_x = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "x");
  auto main_i = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "i");
  auto main_n = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "n");
  builder.CreateStore(ConstantInt::get(context, 0), main_x);
  builder.CreateStore(ConstantInt::get(context, 0), main_i);
  builder.CreateStore(ConstantInt::get(context, 8), main_n);
  builder.CreateBr(main_cond_block);

  // for-loop condition
  builder.SetInsertPoint(main_cond_block);
  auto main_i_tmp_1 = builder.CreateLoad(main_i);
  auto main_n_tmp_1 = builder.CreateLoad(main_n);
  auto main_loop_cond = builder.CreateICmpSLT(main_i_tmp_1, main_n_tmp_1);
  builder.CreateCondBr(main_loop_cond, main_loop_block, main_return_block);

  // for-loop body
  builder.SetInsertPoint(main_loop_block);
  auto main_i_tmp_2 = builder.CreateLoad(main_i);
  auto main_fib_call = builder.CreateCall(fib_func, {main_i_tmp_2});
  auto main_x_tmp = builder.CreateLoad(main_x);
  auto main_new_x = builder.CreateNSWAdd(main_x_tmp, main_fib_call, "add_x_tmp");
  builder.CreateStore(main_new_x, main_x);
  auto main_new_i = builder.CreateNSWAdd(main_i_tmp_2, ConstantInt::get(context, 1), "new_i_tmp");
  builder.CreateStore(main_new_i, main_i);
  builder.CreateBr(main_cond_block);

  // return
  builder.SetInsertPoint(main_return_block);
  auto main_return_result = builder.CreateLoad(main_x);
  builder.CreateRet(main_return_result);

  module->print();
  // auto result = moduleTransform(module);
  // result.print();
  // result.deleteBlock();
  // module->~Module();
  // LiveVars LV;
  // LV.runOnFunction(*fib_func);
  // RegAssign RA(*fib_func, &LV);
  // RA.runColoring();
  auto result = moduleTransform(module);
  result.print("fib.s");
  result.deleteBlock();
  module->~Module();
  return 0;
}