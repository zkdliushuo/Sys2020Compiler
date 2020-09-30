#include "Instructions.h"
#include "BasicBlock.h"
#include "Constants.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include "User.h"
#include <cassert>
#include <iostream>
#define DDD_DEBUG

using namespace YAL;

Instruction::Instruction(Type *ty, unsigned it, Use *Ops, unsigned NumOps, Instruction *InsertBefore)
    : User(ty, Value::InstructionVal + it, Ops, NumOps), Parent(nullptr) {
  if (InsertBefore) {
    // std::cout << "Insert: " << this->getOpcodeName() << " InsertBefore: " << InsertBefore->getOpcodeName() << std::endl;
    BasicBlock *BB = InsertBefore->getParent();
    // std::cout << "At BB: " << BB->getName() << std::endl;
    setParent(BB);
    assert(BB && "InsertBefore has no parent");
    auto I = std::find(BB->begin(), BB->end(), InsertBefore);
    assert(I != BB->end() && "InsertBefore is not in this BB");
    auto new_inst = BB->getInstList().insert(I, this);
    assert(new_inst != BB->end() && "Insert Failed");
  }
}

Instruction *Instruction::getNextNonDebugInstruction() {
  auto temp = std::find(getParent()->begin(), getParent()->end(), this);
  assert(temp != getParent()->end() && "can't find this instruction");
  temp++;
  if (temp == getParent()->end()) return nullptr;
  return *temp;
  // if (!isa<CallInst>(*temp))
  //   return *temp;
  // else {
  //   temp++;
  //   if (temp == getParent()->end()) return nullptr;
  //   else return *temp;
  // }
}

static bool haveSameSpecialState(Instruction *I1, Instruction *I2) {
  assert(I1->getOpcode() == I2->getOpcode() &&
         "Can not compare special state of different instructions");

  if (AllocaInst *AI = cast<AllocaInst>(I1))
    return AI->getAllocatedType() == cast<AllocaInst>(I2)->getAllocatedType();
  if (ICmpInst *CI = cast<ICmpInst>(I1))
    return CI->getCmp() == cast<ICmpInst>(I2)->getCmp();
  return true;
}

bool Instruction::isIdenticalto(Instruction *I) {
  assert(I != nullptr && "I is nullptr");
  auto op1 = getOpcode();
  auto op2 = I->getOpcode();
  if (op1 != op2) {
    return false;
  }
  if (getNumOperands() != I->getNumOperands()) {
    return false;
  }
  if (getType() != I->getType()) {
    return false;
  }
  if (getRawSubclassOptionalData() != I->getRawSubclassOptionalData()) {
    return false;
  }
  // std::cout << "222" << std::endl;
  // if (getOpcode() != I->getOpcode() ||
  //     getNumOperands() != I->getNumOperands() ||
  //     getType() != I->getType() || 
  //     getRawSubclassOptionalData() != I->getRawSubclassOptionalData()) {
  //   std::cout << "222" << std::endl;
  //   return false;
  // }

  if (I->getOpcode() == Add || I->getOpcode() == Mul) {
    if (I->getNumOperand(1) == getNumOperand(0) && 
        I->getNumOperand(0) == getNumOperand(1))
      return true;
  }

  // If both instructions have no operands, they are identical.
  if (getNumOperands() == 0 && I->getNumOperands() == 0)
    return haveSameSpecialState(this, I);


  if (!std::equal(op_begin(), op_end(), I->op_begin()))
    return false;

  if (PHINode *thisPHI = cast<PHINode>(this)) {
    PHINode *otherPHI = cast<PHINode>(I);
    return std::equal(thisPHI->block_begin(), thisPHI->block_end(),
                      otherPHI->block_begin());
  }

  return haveSameSpecialState(this, I);
}

Function *Instruction::getFunction() { return Parent->getParent(); }
Module *Instruction::getModule() { return Parent->getParent()->getParent(); }
const char *Instruction::getOpcodeName() const {
  unsigned OpcodeID = getOpcode();
  switch (OpcodeID) {
  case PHI:
    return "phi";
  case Ret:
    return "ret";
  case Br:
    return "br";
  case Icmp:
    return "icmp";
  case Add:
    return "add";
  case Sub:
    return "sub";
  case Mul:
    return "mul";
  case SDiv:
    return "sdiv";
  case And:
    return "and";
  case Or:
    return "or";
  case Alloca:
    return "alloca";
  case Load:
    return "load";
  case Store:
    return "store";
  case GetElementPtr: {
    auto temp = cast<GetElementPtrInst>(this);
    if (temp->isInBounds()) {
      return "getelementptr inbounds";
    } else {
      return "getelementptr";
    }
  }
  case Call:
    return "call";
  case Xor:
    return "xor";
  case SRem:
    return "srem";
  case ZExt:
    return "zext";
  default:
    return "invalid opcode";
  }
}

bool Instruction::comesBefore(const Instruction *I) {
  assert(Parent && I->Parent && "instructions without BB parents have no order");
  assert(Parent == I->Parent && "cross-BB instruction order comparison");
  if (!Parent->isOrderValid())
    Parent->setInstructionOrder();
  return Order < I->Order;
}

unsigned Instruction::getOrder() {
  assert(Parent && "instructions without BB parents have no order");
  if (!Parent->isOrderValid())
    Parent->setInstructionOrder();
  return Order;
}

void Instruction::eraseFromParent() {
  auto BB = getParent();
  auto I = std::find(BB->begin(), BB->end(), this);
  if (I != BB->end()) {
    BB->getInstList().erase(I);
    for (int i = 0; i < getNumOperands(); i++) {
      auto &op = getNumOperand(i);
      op.remove();
    }

    if (auto br = cast<BranchInst>(this)) {
      auto pred = --I;
      auto succ_list = br->getParent()->getSuccList();
      int succ_num = br->isConditional() ? 2 : 1;
      for (int i = 0; i < succ_num; i++) {
        auto succ = br->getSuccessor(i);
        auto succ_iterator = std::find(succ_list.begin(), succ_list.end(), succ);
        assert(succ_iterator != succ_list.end() && "BB doesn't have this successor");
        bool different = true;

        if (auto pred_br = cast<BranchInst>(*pred)) {
          auto num = 1;
          if (pred_br->isConditional()) num = 2;
          for (int j = 0; j < num; j++) {
            auto p_succ = pred_br->getSuccessor(j);
            assert(succ_list.count(succ) != 0 && "BB doesn't have this successor");
            if (p_succ == succ) {
              different = false;
              break;
            }
          }
        }

        if (different) {
          BB->deleteSucc(succ);
          succ->deletePred(BB);
          // br->getParent()->getSuccList().erase(succ_iterator);
          // auto pred_list = succ->getPredList();
          // auto temp = std::find(pred_list.begin(), pred_list.end(), br->getParent());
          // assert(temp != succ->getPredList().end() && "succ doesn't have this pred");
          // succ->getPredList().erase(temp);
        }
      }
    }
    
  }
}

/* ****************************************************************** */
/*                             ReturnInst                             */
/* ****************************************************************** */
ReturnInst::ReturnInst(LLVMContext &C, Value *retVal, Instruction* InsertBefore)
    : Instruction(Type::getVoidTy(C), Instruction::Ret, op_begin(), !!retVal, InsertBefore) {
  // #ifdef DDD_DEBUG
  // #endif
  // std::cout << "Num of operand is "<<!!retVal <<std::endl;
  if (retVal)
    Op<0>() = retVal;
  // std::cout << "Create ReturnInst" <<std::endl;
}

/* ****************************************************************** */
/*                             BranchInst                             */
/* ****************************************************************** */
BranchInst::BranchInst(BasicBlock *IfTrue, Instruction *InsertBefore)
    : Instruction(Type::getVoidTy(IfTrue->getContext()), Instruction::Br, op_begin(), 1, InsertBefore) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create BranchInst" <<std::endl;
  // #endif
  Op<-1>() = IfTrue;
}

BranchInst::BranchInst(BasicBlock *IfTrue, BasicBlock *IfFalse, Value *Cond, Instruction *InsertBefore)
    : Instruction(Type::getVoidTy(IfTrue->getContext()), Instruction::Br, op_begin(), 3, InsertBefore) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create Conditional BranchInst" <<std::endl;
  // #endif
  Op<-1>() = IfTrue;
  Op<-2>() = IfFalse;
  Op<-3>() = Cond;
}

/* ****************************************************************** */
/*                             AllocaInst                             */
/* ****************************************************************** */
AllocaInst::AllocaInst(Type *Ty, Value *ArraySize, std::string Name, Instruction *InsertBefor)
    : Instruction(PointerType::get(Ty), Instruction::Alloca, &Op<0>(), 1, InsertBefor), AllocatedType(Ty) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create AllocaInst" <<std::endl;
  if (!ArraySize) {
    Op<0>() = ConstantInt::get(Ty->getContext(), 1, 32);
    // std::cout << "--AllocaInst ConstantInt created--" << std::endl;
  } else
    Op<0>() = ArraySize;
}

/* ****************************************************************** */
/*                             LoadInst                               */
/* ****************************************************************** */
LoadInst::LoadInst(Type *Ty, Value *Ptr, std::string Name, Instruction *InsertBefore) 
             : Instruction(Ty, Instruction::Load, &Op<0>(), 1, InsertBefore) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create LoadInst" <<std::endl;
  // #endif
  LoadUser = nullptr;
  Op<0>() = Ptr;
}

/* ****************************************************************** */
/*                             StoreInst                              */
/* ****************************************************************** */
StoreInst::StoreInst(Value *val, Value *addr, Instruction *InsertBefore)
    : Instruction(Type::getVoidTy(val->getContext()), Instruction::Store, op_begin(), getNumOperands(), InsertBefore) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create StoreInst" <<std::endl;
  // #endif
  Op<0>() = val;
  Op<1>() = addr;
}

/* ****************************************************************** */
/*                          GetElementPtrInst                         */
/* ****************************************************************** */
GetElementPtrInst::GetElementPtrInst(Type *PointeeType, Value *Ptr, ArrayRef<Value *> IdxList, unsigned Values, Instruction *InsertBefore)
    // 只能是i32*
    : Instruction(Type::getInt32PtrTy(Ptr->getContext()), GetElementPtr, op_begin(), Values, InsertBefore),
      SourceElementType(PointeeType), ResultElementType(PointerType::get(PointeeType)) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create GEPInst with mutiple index" <<std::endl;
  // #endif
  Op<0>() = Ptr;
  for (int i = 0; i < IdxList.size(); i++) {
    getNumOperand(i + 1) = IdxList[i];
  }
}

GetElementPtrInst::GetElementPtrInst(Type *PointeeType, Value *Ptr, Value *Idx, unsigned Values, Instruction *InsertBefore)
    : Instruction(Type::getInt32PtrTy(Ptr->getContext()), GetElementPtr, op_begin(), Values, InsertBefore),
      SourceElementType(PointeeType), ResultElementType(PointerType::get(PointeeType)) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create GEPInst with one index" <<std::endl;
  // #endif
  Op<0>() = Ptr;
  Op<1>() = Idx;
}

bool GetElementPtrInst::hasAllZeroIndices() const {
  for (unsigned i = 1, e = getNumOperands(); i != e; ++i) {
    if (ConstantInt *CI = cast<ConstantInt>(getNumOperand(i).get())) {
      if (!CI->isZero())
        return false;
    } else {
      return false;
    }
  }
  return true;
}

/* ****************************************************************** */
/*                            ICmpInst                                */
/* ****************************************************************** */
ICmpInst::ICmpInst(unsigned pred, Value *LHS, Value *RHS, Instruction *InsertBefore)
    : Instruction(Type::getInt1Ty(LHS->getContext()), Icmp, op_begin(), getNumOperands(), InsertBefore) {
  Op<0>() = LHS;
  Op<1>() = RHS;
  setCmpType(pred);
  // #ifdef DDD_DEBUG
  // std::cout << "Create Icmp" <<getCmpType() << std::endl;
  // #endif
}

/* ****************************************************************** */
/*                         BinaryOperator                             */
/* ****************************************************************** */
BinaryOperator::BinaryOperator(unsigned iType, Value *S1, Value *S2, Type *Ty, Instruction *InsertBefore)
    : Instruction(Ty, iType, op_begin(), getNumOperands(), InsertBefore) {
  // std::cout<<"S1 assign"<<std::endl;
  Op<0>() = S1;
  // std::cout<<"S2 assign"<<std::endl;
  Op<1>() = S2;
  // #ifdef DDD_DEBUG
  // std::cout << "Create BinaryOperator " << getOpcodeName() << std::endl;
  // #endif
}

BinaryOperator *BinaryOperator::CreateNeg(Value *Op, std::string Name, Instruction *InsertBefore) {
  auto zero = ConstantInt::get(Op->getContext(), 0, 32);
  return new BinaryOperator(Instruction::Sub, zero, Op, Op->getType(), InsertBefore);
}

BinaryOperator *BinaryOperator::CreateNot(Value *Op, std::string Name, Instruction *InsertBefore) {
  auto ty = cast<IntegerType>(Op->getType());
  auto One = ConstantInt::getAllOne(ty->getContext(), ty->getBitWidth());
  return new BinaryOperator(Instruction::Xor, One, Op, Op->getType(), InsertBefore);
}

/* ****************************************************************** */
/*                            CallInst                                */
/* ****************************************************************** */
void CallInst::init(FunctionType *FTy, Value *Func, ArrayRef<Value *> args, std::string &NameStr) {
  this->FTy = FTy;
  Op<-1>() = Func;
  setValueName(NameStr);
  for (int i = 0; i < args.size(); i++) {
    getNumOperand(i) = (args[i]);
  }
}

CallInst::CallInst(FunctionType *Ty, Value *Func, ArrayRef<Value *> args, std::string &Name, Instruction *InsertBefore)
    : Instruction(Ty->getReturnType(), Instruction::Call, op_begin(), args.size() + 1, InsertBefore) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create CallInst" <<std::endl;
  // #endif
  init(Ty, Func, args, Name);
}

/* ****************************************************************** */
/*                            ZExtInst                                */
/* ****************************************************************** */
ZExtInst::ZExtInst(Type *Ty, Value *V, Instruction *InsertBefore)
        : Instruction(Ty, Instruction::ZExt, &Op<0>(), 1, InsertBefore) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create ZExtInst" <<std::endl;
  // #endif
  Op<0>() = V;
}

void PHINode::growOperands() {
  unsigned e = getNumOperands();
  unsigned NumOps = e + e / 2;
  if (NumOps < 2)
    NumOps = 2; // 2 op PHI nodes are VERY common.

  ReservedSpace = NumOps;
  growHungoffUses(ReservedSpace, /* IsPhi */ true);
}

/* ****************************************************************** */
/*                            PHINode                                 */
/* ****************************************************************** */
Value *PHINode::removeIncomingValue(unsigned Idx, bool DeletePHIIfEmpty) {
  Value *Removed = getIncomingValue(Idx);

  // Move everything after this operand down.
  std::copy(op_begin() + Idx + 1, op_end(), op_begin() + Idx);
  std::copy(block_begin() + Idx + 1, block_end(), block_begin() + Idx);

  // Nuke the last value.
  Op<-1>().set(nullptr);
  setNumHungOffUseOperands(getNumOperands() - 1);

  // If the PHI node is dead, because it has zero entries, nuke it now.
  if (getNumOperands() == 0 && DeletePHIIfEmpty) {
    // If anyone is using this PHI, make them use a dummy value instead...
    replaceAllUsesWith(UndefValue::get(getType()));
    eraseFromParent();
  }
  return Removed;
}