#include "Value.h"
#include "Instructions.h"
#include "Argument.h"
#include "GlobalVariable.h"
#include <cassert>

using namespace YAL;

bool Value::isVar() {
  if (isa<Instruction>(this))
    return true;
  if (auto arg = cast<Argument>(this))
    if (arg->getArgNo() < 4)
      return true;
  return false;
}

bool Value::hasRegAllocated(){
  if (isa<Instruction>(this)) {

    if (auto CI = cast<CallInst>(this)) {
      if (CI->getFunctionType()->isReturnVoid()) return false;
      else return true;
    }

    if (isa<ReturnInst>(this)) return false;

    if (isa<ICmpInst>(this)) return false;

    if (isa<BranchInst>(this)) return false;

    if (isa<AllocaInst>(this)) return false;

    if (isa<StoreInst>(this)) return false;

    if (isa<LoadInst>(this)) {
      if (this->SpilledAndUsedByCall) return false;
      else return true;
    }

    return true;
  }

  else if (auto arg = cast<Argument>(this)) {

    if (arg->getArgNo() < 4) return true;
    else return false;
  }

  return false;
}

void Value::setKiller(Instruction *I) {
  int bb_order = I->getParent()->Order;
  if ((info.killer.count(bb_order) && I->Order + 1 > info.killer[bb_order])
      || !info.killer.count(bb_order))
    info.killer[bb_order] = I->Order + 1;
}

void Value::setKiller(BasicBlock *BB) { info.killer[BB->Order] = BB->getInstList().size() + 1; }

void Value::setStart(BasicBlock *BB, unsigned i) {
  if (!info.start.count(BB->Order))
    info.start[BB->Order] = i;
  else if (i < info.start[BB->Order])
    info.start[BB->Order] = i;
}

Value::Value(Type *ty, unsigned scid)
    : VTy(ty), UseList(nullptr), SubclassID(scid), SubclassOptionalData(0),
      SubclassData(0), NumUserOperands(0), HasName(false) {
  if (SubclassID - InstructionVal == Instruction::Opcode::Call)
    assert((VTy->isVoidTy() || VTy->isFirstClassType()) && "invalid CallInst type!");
}

/// 对于就是Value*的指针使用~析构
Value::~Value() {
  /// 不可以在还有User的情况下删除
  // assert(use_empty() && "Uses remain when a value is destroyed!");
}

void Value::setValueName(std::string VN) {
  if (VN.empty()) {
    HasName = false;
    return;
  }
  HasName = true;
  ValueName = VN;
}

void Value::deleteValue() {
  /// 需要静态类型转化成对应类型再delete，才能不出现内存泄露
  /// 等完整的类型系统建立起来再做
  /// 对于泛型的Value*，这里不使用default ~Value
  delete this;
}

/// 还需要实现判断一个Value是不是在
bool Value::isUsedInBasicBlock(BasicBlock *BB) {
  /// value可以是bb中的instruction 也可以是bb中某条instruction的操作数
  /// 同时扫描这个bb的instruction链和value的user链，时间和最短的链相近
  BasicBlock::iterator BI = BB->begin(), BE = BB->end();
  user_iterator UI = user_begin(), UE = user_end();
  for (; BI != BE && UI != UE; ++BI, ++UI) {
    // TODO
    /// 如果this value包括在BI的操作数中
    /*if (is_contained(BI->operands(), this))
      return true;*/
    // Scan use list: Check if the use at UI is in BB.
    auto *User = dynamic_cast<Instruction *>(*UI);
    if (User && User->getParent() == BB)
      return true;
  }
  return false;
}

void Value::replaceAllUsesWith(Value *New) {
  assert(New && "Value::replaceAllUsesWith(<null>) is invalid!");

  while (!use_empty()) {
    Use &U = *UseList;
    U.set(New);
  }

  // if (BasicBlock *BB = cast<BasicBlock>(this))
  //   BB->replaceSuccessorsPhiUsesWith(cast<BasicBlock>(New));
}

void Value::addUse(Use &U) { U.addToList(&UseList); }

LLVMContext &Value::getContext() const { 
  assert(VTy && "VTy is NULLPTR");
  return VTy->getContext(); 
}
