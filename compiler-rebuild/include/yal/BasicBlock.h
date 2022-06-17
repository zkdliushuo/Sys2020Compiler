#ifndef YAL_IR_BB_H
#define YAL_IR_BB_H

#include "Value.h"
#include "Instruction.h"
#include <list>
#include <string>
#include <iostream>
#include <set>
#include <map>
namespace YAL {

class Function;
class Instruction;
class PHINode;

class BasicBlock : public Value {
private:
  std::list<Instruction *>
      InstList; // 暂时用list替代源码中的SymbolTableList<Instruction>
  std::set<BasicBlock *> PredList;
  std::set<BasicBlock *> SuccList;
  Function *Parent;
  unsigned short BlockAddressRefCount : 15;
  unsigned short InstrOrderValid : 1;

public:
  bool visited = false;
  unsigned finish_time = 0;
  std::map<unsigned, Value*> use_list, def_list;
  std::map<unsigned, Value*> IN_list, OUT_list;
  std::map<PHINode *, Value *> Phi_use;

public:
  mutable unsigned Order = 0;

public:
  // 构造和析构函数
  BasicBlock(LLVMContext &C, std::string &Name, Function *NewParent);
  ~BasicBlock() {}

  using iterator = std::list<Instruction *>::iterator;
  iterator begin() { return InstList.begin(); }
  iterator end() { return InstList.end(); }

  auto begin() const { return InstList.begin(); }
  auto end() const { return InstList.end(); }

  // 获取所在的函数
  inline Function *getParent() { return Parent; }

  void setParent(Function *F) { Parent = F; }

  inline const Function *getParent() const { return Parent; }

  // 创建basicblock，去掉了BasicBlock *InsertBefore，默认插入到最后
  static BasicBlock *Create(LLVMContext &Context, std::string Name = "",
                            Function *Parent = nullptr) {
    return new BasicBlock(Context, Name, Parent);
  }

  static BasicBlock *Create(LLVMContext &Context, std::string Name,
                     Function *Parent, BasicBlock *InsertBefore);

  // 插入到function中
  void insertInto(Function *NewParent);

  // 获取终结语句
  Instruction *getTerminator();

  // 获取终结语句所连接的BasicBlock
  std::list<BasicBlock *> getNextBlocks();

  // 获取终结语句连接的BB的数量
  unsigned getTerminatorBBNum() {
    return getNextBlocks().size();
  }

  // 获取前驱的数量
  unsigned getPredNum() { return PredList.size(); }

  // 获取后继的数量
  unsigned getSuccNum() { return SuccList.size(); }

  // 获取指令列表
  std::list<Instruction *> &getInstList() { return InstList; }

  void dropAllReferences();

  // 添加前驱
  void addPred(BasicBlock *bb) { PredList.insert(bb); }

  // 添加后继
  void addSucc(BasicBlock *bb) { SuccList.insert(bb); }

  // 删除前驱
  void deletePred(BasicBlock *bb) { 
    auto temp = PredList.find(bb);
    if (temp != PredList.end())
      PredList.erase(temp);
  }

  // 删除后继
  void deleteSucc(BasicBlock *bb) { 
    auto temp = SuccList.find(bb);
    if (temp != SuccList.end())
      SuccList.erase(temp);
  }

  // 获取前驱列表
  std::set<BasicBlock *> getPredList() { return PredList; }

  // 获取后继列表
  std::set<BasicBlock *> getSuccList() { return SuccList; }

  // 从所在function中移除
  void removeFormParent();

  // 基本块是否为空
  bool empty() { return InstList.empty(); }

  // 是否已经给指令排序
  bool isOrderValid() { return InstrOrderValid; }

  void setOrderValid(bool i) { InstrOrderValid = i; }

  // 设置指令的顺序
  void setInstructionOrder();
  
  // 获取block序号
  unsigned getOrder() { return Order; }

  // 活跃变量分析初始化
  void init_usedef();

  void init_def();

  void init_use();

  bool operator<(const BasicBlock &other) {
    return this->finish_time < other.finish_time;
  }
};

} // namespace YAL
#endif
