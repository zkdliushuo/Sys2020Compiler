#ifndef YAL_IR_MODULE_H
#define YAL_IR_MODULE_H

#include "Function.h"
// #include "LLVMContext.h"
// #include "Types.h"
// #include "support.h"

#include <iterator>
#include <list>
#include <string>

namespace YAL {

class GlobalVariable;

class Module {
  using GlobalListType = std::list<GlobalVariable *>;
  using FunctionListType = std::list<Function *>;
private:
  LLVMContext &Context;
  GlobalListType GlobalList;
  FunctionListType FunctionList;
  std::string ModuleID;

public:
  explicit Module(std::string MID, LLVMContext &C);

  ~Module();

  /* ---      Module Property Accesssors       --- */

  // get the ID of this module
  const std::string &getID() const { return ModuleID; }

  // get the context of this module
  LLVMContext &getContext() const { return Context; }

  // get the global list of this module
  GlobalListType &getGlobalList() { return GlobalList; }

  // get the function list of this module
  auto &getFunctionList() { return FunctionList; }

  const auto &getFunctionList() const { return FunctionList; }

  /* ---      Module Property Setters         --- */

  // set the ID of this module
  void setID(std::string ID) { ModuleID = ID; }

  /* ---      Global Variable Accessors       --- */
  bool global_empty() const { return GlobalList.empty(); }

  const GlobalListType &globals() const { return GlobalList; }

  /// 需要重写或者使用llvm的raw_ostream来重载<<,产生输出
  /// 目前这里会有错
  void print(std::string target_name = "") const;
};

} // namespace YAL
#endif