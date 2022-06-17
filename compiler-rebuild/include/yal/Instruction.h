#ifndef YAL_IR_INSTR_H
#define YAL_IR_INSTR_H

#include "BasicBlock.h"
#include "LLVMContext.h"
#include "Type.h"
#include "Types.h"
#include "User.h"
#include "Value.h"
#include <list>
#include <set>

namespace YAL {

class BasicBlock;
class Module;
class Function;

class Instruction : public User {
public:
  enum Opcode {
    Ret = 0,
    Br,
    Icmp,
    Add,
    Sub,
    Mul,
    SDiv,
    SRem,
    And,
    Or,
    Xor,
    Alloca,
    Load,
    Store,
    GetElementPtr,
    Call,
    ZExt,
    PHI
  };
  BasicBlock *Parent;
  unsigned Order = 0;
  // mutable unsigned FOrder = 0;

public:
  // 构造函数和析构函数
  Instruction(Type *ty, unsigned it, Use *Ops, unsigned NumOps, Instruction* InsertBefore);
   ~Instruction() {}// std::cout << "delete Instruction" <<std::endl; }

  // 获取所在基本块/函数/模块
  inline BasicBlock *getParent() { return Parent; }
  Function *getFunction();
  Module *getModule();

  // 设置所在基本块
  void setParent(BasicBlock *bb) { Parent = bb; }

  // // 获取和设置SubclassData
  unsigned getSubclassData() { return getSubclassDataFromValue(); }
  void setSubclassData(unsigned data) { setValueSubclassData(data); }

  // 获取指令名称
  unsigned getOpcode() { return getValueID() - InstructionVal; }
  unsigned getOpcode() const { return getValueID() - InstructionVal; }
  const char *getOpcodeName() const;

  // 判断是否是终结语句
  bool isTerminator() {
    unsigned OpcodeID = getOpcode();
    if (OpcodeID == Ret || OpcodeID == Br)
      return true;
    else
      return false;
  }

  // 判断该指令是否在某个指令的前边
  bool comesBefore(const Instruction *I);
  
  // 获取指令顺序
  unsigned getOrder();

  void eraseFromParent();

  bool isIdenticalto(Instruction *I);

  Instruction *getNextNonDebugInstruction();
};
} // namespace YAL
#endif