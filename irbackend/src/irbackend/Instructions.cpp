#include "Instructions.h"
#include "BasicBlock.h"
#include "Constants.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include <cassert>
#include <iostream>
#define DDD_DEBUG

using namespace YAL;

Instruction::Instruction(Type *ty, unsigned it, Use *Ops, unsigned NumOps, Instruction *InsertBefore)
    : User(ty, Value::InstructionVal + it, Ops, NumOps), Parent(nullptr) {
  if (InsertBefore) {
    BasicBlock *BB = InsertBefore->getParent();
    setParent(BB);
    assert(BB && "InsertBefore has no parent");
    auto I = std::find(BB->begin(), BB->end(), InsertBefore);
    assert(I != BB->end() && "InsertBefore is not in this BB");
    BB->getInstList().insert(I, this);
  }
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
    // Op<i>() = args[i];
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