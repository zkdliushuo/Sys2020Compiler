#ifndef YAL_IR_FUNCTION_H
#define YAL_IR_FUNCTION_H

#include "Argument.h"
#include "BasicBlock.h"
// #include "Module.h"
// #include "Types.h"
#include "Value.h"
#include <list>
#include <iostream>

namespace YAL {

class Module;
class Argument;
class Type;
class User;
class GlobalVariable;
class CallInst;
class BasicBlock;

class Function : public Constant {
private:
  Module *Parent;
  std::list<BasicBlock*> BBList;
  // 设计可以再简化一点，因为不需要考虑变量类型和结构体，可以考虑删除Argument的private成员
  std::list<Argument*> Arguments; // The formal arguments
  std::set<GlobalVariable *> GV;
  std::set<CallInst *> CI;
  size_t NumArgs;
  unsigned short BlockOrderValid : 1;

public:
    // TODO
    /// function创建的时候，OP_begin从哪里来
  Function(FunctionType *Ty, std::string &name, Module *ParentModule);

  static Function *Create(FunctionType *Ty, std::string N,Module *M = nullptr) {
    return new Function(Ty, N, M);
  }

  Function(const Function &) = delete;
  void operator=(const Function &) = delete;
  ~Function();

  const Function &getFunction() const { return *this; }

  inline Module *getParent() { return Parent; }
  inline const Module *getParent() const { return Parent; }

  /// 得到函数的entry
  const BasicBlock* getEntryBlock() const { return BBList.front(); }
  BasicBlock* getEntryBlock() { return BBList.front(); }

  /// 得到迭代器方便遍历BB
  std::list<BasicBlock*>::iterator BB_begin() { return BBList.begin(); }
  std::list<BasicBlock*>::iterator BB_end() { return BBList.end(); }

  auto BB_begin() const { return BBList.begin(); }
  auto BB_end() const { return BBList.end(); }

  /// 得到迭代器方便遍历Arg
  auto Arg_begin() { return Arguments.begin(); }
  auto Arg_end() { return Arguments.end(); }
  auto Arg_size() const { return Arguments.size(); }

  auto Arg_begin() const { return Arguments.begin(); }
  auto Arg_end() const { return Arguments.end(); }

  bool isDeclaration() const { return BBList.empty(); }

  // Returns the FunctionType for function.
  FunctionType *getFunctionType() const {
    return cast<FunctionType>(getType());
  }

  // Returns the type of the return value.
  Type *getReturnType() const { return getFunctionType()->getReturnType(); }

  void clearArguments();
  void dropAllReferences();

  // 获取Blocklist
  std::list<BasicBlock*> &getBasicBlockList() { return BBList; }

  unsigned getMaxLabel() const;

  // 是否已经给block排序
  bool isOrderValid() { return BlockOrderValid; }

  void setOrderValid(bool i) { BlockOrderValid = i; }

  // 设置block的顺序
  void setBlockOrder();

  // 查看函数是否引用某个全局变量
  void searchGV();

  bool hasSideEffect();

  bool hasSideEffect(Value *V);

  BasicBlock* getReturnBlock();

  std::string getRetBBName() { return getName() + "_retbb";}
  std::string getAlignBBName() { return getName() + "_alignbb";}
  std::string getGVBBName() { return getName() + "_gvbb";}
};

} // namespace YAL
#endif // !YAL_IR_FUNCTION_H