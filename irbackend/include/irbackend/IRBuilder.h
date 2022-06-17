#ifndef YAL_IR_BUILDER_H
#define YAL_IR_BUILDER_H

#include "BasicBlock.h"
#include "Constants.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "Instructions.h"
#include "Value.h"

namespace YAL {

class LLVMContext;
class BasicBlock;
class Instruction;
class BinaryOperator;
class Constant;
class ConstantInt;

class IRBuilder {
  enum { EQ = 0, NE, GE, GT, LE, LT };

private:
  static ConstantInt *getAdd(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() + C2->getValue(), 32);
  }

  static ConstantInt *getSub(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() - C2->getValue(), 32);
  }

  static ConstantInt *getMul(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() * C2->getValue(), 32);
  }

  static ConstantInt *getSDiv(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() / C2->getValue(), 32);
  }

  static ConstantInt *getAnd(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() && C2->getValue(), 1);
  }

  static ConstantInt *getOr(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() || C2->getValue(), 1);
  }

  static ConstantInt *getSRem(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() % C2->getValue(), 32);
  }

  static ConstantInt *getNeg(ConstantInt *C1) { return ConstantInt::get(C1->getContext(), -(C1->getValue()), 32); }

  static ConstantInt *getNot(ConstantInt *C1) {
    return ConstantInt::get(C1->getContext(), ~(C1->getValue()), C1->getBitWidth());
  }

  static ConstantInt *getICmp(unsigned short pred, ConstantInt *LHS, ConstantInt *RHS) {
    int value;
    switch (pred) {
    case EQ: {
      value = LHS->getValue() == RHS->getValue();
      break;
    }
    case NE: {
      value = LHS->getValue() != RHS->getValue();
      break;
    }
    case GE: {
      value = LHS->getValue() >= RHS->getValue();
      break;
    }
    case GT: {
      value = LHS->getValue() > RHS->getValue();
      break;
    }
    case LE: {
      value = LHS->getValue() <= RHS->getValue();
      break;
    }
    case LT: {
      value = LHS->getValue() < RHS->getValue();
      break;
    }
    default:
      break;
    }
    return ConstantInt::get(LHS->getContext(), value, 1);
  }

protected:
  LLVMContext &Context;
  BasicBlock *curBB;
  // BasicBlock::iterator InsertPoint;

public:
  IRBuilder(LLVMContext &context) : Context(context) { ClearInsertionPoint(); }
  ~IRBuilder() = default;

  template <typename InstTy> InstTy *Insert(InstTy *I, std::string Name = "") const {
    curBB->getInstList().push_back(I);
    // I->setValueName(Name);
    I->setParent(curBB);
    return I;
  }

  Value *Insert(Value *V, std::string Name = "") const {
    if (Instruction *I = cast<Instruction>(V))
      return Insert(I, Name);
    return V;
  }

  void ClearInsertionPoint() { curBB = nullptr; }

  void SetInsertPoint(BasicBlock *bb) { curBB = bb; }

  BasicBlock *getInsertBlock() const { return curBB; }

  LLVMContext &getContext() const { return Context; }

  //===--------------------------------------------------------------------===//
  // Instruction creation methods: Terminators
  //===--------------------------------------------------------------------===//
public:
  /// Create Return void
  ReturnInst *CreateRetVoid() { return Insert(ReturnInst::Create(Context, nullptr)); }

  /// Create a 'ret <val>' instruction.
  ReturnInst *CreateRet(Value *V) { return Insert(ReturnInst::Create(Context, V)); }

  /// Create an unconditional 'br label X' instruction.
  BranchInst *CreateBr(BasicBlock *Dest) {
    auto I = Insert(BranchInst::Create(Dest));
    curBB->addSucc(Dest);
    Dest->addPred(curBB);
    return I;
  }

  /// Create a conditional 'br Cond, TrueDest, FalseDest'
  /// instruction.
  BranchInst *CreateCondBr(Value *Cond, BasicBlock *True, BasicBlock *False) {
    auto I = Insert(BranchInst::Create(True, False, Cond));
    curBB->addSucc(True);
    curBB->addSucc(False);
    True->addPred(curBB);
    False->addPred(curBB);
    return I;
    // return Insert(BranchInst::Create(True, False, Cond));
  }

  //===--------------------------------------------------------------------===//
  // Instruction creation methods: Binary Operators
  //===--------------------------------------------------------------------===//
private:
  BinaryOperator *CreateInsertNUWNSWBinOp(unsigned Opc, Value *LHS, Value *RHS, std::string Name, bool HasNUW,
                                          bool HasNSW) {
    // std::cout << "--CreateInsertNUWNSWBinOp--" << std::endl;
    BinaryOperator *BO = Insert(BinaryOperator::Create(Opc, LHS, RHS), Name);
    // if (HasNUW) BO->setHasNoUnsignedWrap();
    if (HasNSW)
      BO->setHasNoSignedWrap(true);
    return BO;
  }

public:
  /// Add instruction
  Value *CreateAdd(Value *LHS, Value *RHS, std::string Name = "", bool HasNUW = false, bool HasNSW = false) {
    if (auto *LC = cast<ConstantInt>(LHS))
      if (auto *RC = cast<ConstantInt>(RHS))
        return getAdd(LC, RC);
    // return Insert(Folder.CreateAdd(LC, RC, HasNUW, HasNSW), Name);
    return CreateInsertNUWNSWBinOp(Instruction::Add, LHS, RHS, Name, HasNUW, HasNSW);
  }

  Value *CreateNSWAdd(Value *LHS, Value *RHS, std::string Name = "") { return CreateAdd(LHS, RHS, Name, false, true); }

  /// Sub instruction
  Value *CreateSub(Value *LHS, Value *RHS, std::string Name = "", bool HasNUW = false, bool HasNSW = false) {
    if (auto *LC = cast<ConstantInt>(LHS))
      if (auto *RC = cast<ConstantInt>(RHS))
        return getSub(LC, RC);
    return CreateInsertNUWNSWBinOp(Instruction::Sub, LHS, RHS, Name, HasNUW, HasNSW);
  }

  Value *CreateNSWSub(Value *LHS, Value *RHS, std::string Name = "") { return CreateSub(LHS, RHS, Name, false, true); }

  /// Mul instruction
  Value *CreateMul(Value *LHS, Value *RHS, std::string Name = "", bool HasNUW = false, bool HasNSW = false) {
    if (auto *LC = cast<ConstantInt>(LHS))
      if (auto *RC = cast<ConstantInt>(RHS))
        return getMul(LC, RC);
    return CreateInsertNUWNSWBinOp(Instruction::Mul, LHS, RHS, Name, HasNUW, HasNSW);
  }

  Value *CreateNSWMul(Value *LHS, Value *RHS, std::string Name = "") { return CreateMul(LHS, RHS, Name, false, true); }

  /// Div instruction
  Value *CreateSDiv(Value *LHS, Value *RHS, std::string Name = "", bool isExact = false) {
    if (auto *LC = cast<ConstantInt>(LHS))
      if (auto *RC = cast<ConstantInt>(RHS))
        return getSDiv(LC, RC);
    return Insert(BinaryOperator::Create(Instruction::SDiv, LHS, RHS));
    // if (!isExact)
    // return Insert(BinaryOperator::CreateSDiv(LHS, RHS), Name);
    // return Insert(BinaryOperator::CreateExactSDiv(LHS, RHS), Name);
  }

  Value *CreateExactSDiv(Value *LHS, Value *RHS, std::string Name = "") { return CreateSDiv(LHS, RHS, Name, true); }

  /// And instruction
  Value *CreateAnd(Value *LHS, Value *RHS, std::string Name = "") {
    if (auto *RC = cast<ConstantInt>(RHS)) {
      if (isa<ConstantInt>(RC) && cast<ConstantInt>(RC)->isMinusOne())
        return LHS; // LHS & -1 -> LHS
      if (auto *LC = cast<ConstantInt>(LHS))
        return getAnd(LC, RC);
    }
    return Insert(BinaryOperator::Create(Instruction::And, LHS, RHS), Name);
  }

  /// Or instruction
  Value *CreateOr(Value *LHS, Value *RHS, std::string Name = "") {
    if (auto *RC = cast<ConstantInt>(RHS)) {
      if (RC->isZero())
        return LHS; // LHS | 0 -> LHS
      if (auto *LC = cast<ConstantInt>(LHS))
        return getOr(LC, RC);
    }
    return Insert(BinaryOperator::Create(Instruction::Or, LHS, RHS), Name);
  }

  // SRem instruction
  Value *CreateSRem(Value *LHS, Value *RHS, std::string Name = "") {
    if (auto *RC = cast<ConstantInt>(RHS))
      if (auto *LC = cast<ConstantInt>(LHS))
        return getSRem(LC, RC);
    return Insert(BinaryOperator::Create(Instruction::SRem, LHS, RHS), Name);
  }

  // Neg instruction
  Value *CreateNeg(Value *V, std::string Name = "") {
    if (auto RC = cast<ConstantInt>(V))
      return getNeg(RC);
    return Insert(BinaryOperator::CreateNeg(V), Name);
  }

  // Not instruction
  Value *CreateNot(Value *V, std::string Name = "") {
    if (auto RC = cast<ConstantInt>(V))
      return getNot(RC);
    return Insert(BinaryOperator::CreateNot(V), Name);
  }

  //===--------------------------------------------------------------------===//
  // Instruction creation methods: Memory Instructions
  //===--------------------------------------------------------------------===//
public:
  /// Alloca instruction
  AllocaInst *CreateAlloca(Type *Ty, Value *ArraySize = nullptr, std::string Name = "") {
    // const DataLayout &DL = BB->getModule()->getDataLayout();
    // Align AllocaAlign = DL.getPrefTypeAlign(Ty);
    // unsigned AddrSpace = DL.getAllocaAddrSpace();
    return Insert(new AllocaInst(Ty, ArraySize), Name);
  }

  /// Load instruction
  LoadInst *CreateLoad(Type *Ty, Value *Ptr, std::string Name = "") { return CreateAlignedLoad(Ty, Ptr, Name); }

  LoadInst *CreateLoad(Value *Ptr, std::string Name = "") {
    return CreateLoad(Ptr->getType()->getPointerElementType(), Ptr, Name);
  }

  LoadInst *CreateAlignedLoad(Value *Ptr, std::string Name = "") {
    assert((Ptr && Ptr->getType() && Ptr->getType()->getPointerElementType()) && "Nullptr");
    return CreateAlignedLoad(Ptr->getType()->getPointerElementType(), Ptr, Name);
  }

  LoadInst *CreateAlignedLoad(Type *Ty, Value *Ptr, std::string Name = "") {
    // if (!Align) {
    //   const DataLayout &DL = BB->getModule()->getDataLayout();
    //   Align = DL.getABITypeAlign(Ty);
    // }
    return Insert(new LoadInst(Ty, Ptr, Name), Name);
  }

  /// Store instruction
  StoreInst *CreateStore(Value *Val, Value *Ptr, bool isVolatile = false) { return CreateAlignedStore(Val, Ptr); }

  StoreInst *CreateAlignedStore(Value *Val, Value *Ptr) {
    // if (!Align) {
    //   const DataLayout &DL = BB->getModule()->getDataLayout();
    //   Align = DL.getABITypeAlign(Val->getType());
    // }
    return Insert(new StoreInst(Val, Ptr));
  }

  /// GEP instruction
  Value *CreateGEP(Value *Ptr, ArrayRef<Value *> IdxList, std::string Name = "") {
    return CreateGEP(nullptr, Ptr, IdxList, Name);
  }

  Value *CreateGEP(Type *Ty, Value *Ptr, ArrayRef<Value *> IdxList, std::string Name = "") {
    // assert(IdxList.size() > 1 && "size of IdxList must be greater than 1");
    // if (auto *IndexC = cast<ConstantInt>(IdxList[1])) {
    //   if (auto *GV = cast<GlobalVariable>(Ptr)) {
    //     if (GV->isConstant()) {
    //       auto init = GV->getInitializer();
    //       if (auto *CAZ = cast<ConstantAggregateZero>(init)) {
    //         return Insert(ConstantInt::get(Ptr->getContext(), 0, 32));
    //       } else if (auto *CA = cast<ConstantArray>(init)) {
    //         auto V = CA->getNumOperand(IndexC->getValue());
    //         if (isa<ConstantInt>(V)) {
    //           return Insert(V, Name);
    //         }
    //       } else {
    //         assert(!isa<ConstantInt>(init) && "Ptr is not an Array");
    //       }
    //     }
    //   }
    // }
    // if (auto *PC = cast<Constant>(Ptr)) {
    //   // Every index must be constant.
    //   size_t i, e;
    //   for (i = 0, e = IdxList.size(); i != e; ++i)
    //     if (!isa<Constant>(IdxList[i]))
    //       break;
    //   if (i == e)
    //     return Insert(Folder.CreateGetElementPtr(Ty, PC, IdxList), Name);
    // }
    return Insert(GetElementPtrInst::Create(Ty, Ptr, IdxList), Name);
  }

  Value *CreateInBoundsGEP(Value *Ptr, ArrayRef<Value *> IdxList, std::string Name = "") {
    return CreateInBoundsGEP(nullptr, Ptr, IdxList, Name);
  }

  Value *CreateInBoundsGEP(Type *Ty, Value *Ptr, ArrayRef<Value *> IdxList, std::string Name = "") {
    // assert(IdxList.size() > 1 && "size of IdxList must be greater than 1");
    // if (auto *IndexC = cast<ConstantInt>(IdxList[1])) {
    //   if (auto *GV = cast<GlobalVariable>(Ptr)) {
    //     if (GV->isConstant()) {
    //       auto init = GV->getInitializer();
    //       if (auto *CAZ = cast<ConstantAggregateZero>(init)) {
    //         return Insert(ConstantInt::get(Ptr->getContext(), 0, 32));
    //       } else if (auto *CA = cast<ConstantArray>(init)) {
    //         return Insert(CA->getNumOperand(IndexC->getValue()));
    //       } else {
    //         assert(!isa<ConstantInt>(init) && "Ptr is not an Array");
    //       }
    //     }
    //   }
    // }
    // if (auto *PC = cast<Constant>(Ptr)) {
    //   // Every index must be constant.
    //   size_t i, e;
    //   for (i = 0, e = IdxList.size(); i != e; ++i)
    //     if (!isa<Constant>(IdxList[i]))
    //       break;
    //   if (i == e)
    //     return Insert(Folder.CreateInBoundsGetElementPtr(Ty, PC, IdxList),
    //                   Name);
    // }
    return Insert(GetElementPtrInst::CreateInBounds(Ty, Ptr, IdxList), Name);
  }

  Value *CreateInBoundsGEP(Value *Ptr, Value *Idx, std::string Name = "") {
    return CreateInBoundsGEP(nullptr, Ptr, Idx, Name);
  }

  Value *CreateInBoundsGEP(Type *Ty, Value *Ptr, Value *Idx, std::string Name = "") {
    // if (auto *PC = dyn_cast<Constant>(Ptr))
    //   if (auto *IC = dyn_cast<Constant>(Idx))
    //     return Insert(Folder.CreateInBoundsGetElementPtr(Ty, PC, IC), Name);
    return Insert(GetElementPtrInst::CreateInBounds(Ty, Ptr, Idx), Name);
  }

  //===--------------------------------------------------------------------===//
  // Instruction creation methods: Compare Instructions
  //===--------------------------------------------------------------------===//
public:
  Value *CreateICmpEQ(Value *LHS, Value *RHS, std::string Name = "") {
    return CreateICmp(ICmpInst::EQ, LHS, RHS, Name);
  }

  Value *CreateICmpNE(Value *LHS, Value *RHS, std::string Name = "") {
    return CreateICmp(ICmpInst::NE, LHS, RHS, Name);
  }

  Value *CreateICmpSGT(Value *LHS, Value *RHS, std::string Name = "") {
    return CreateICmp(ICmpInst::SGT, LHS, RHS, Name);
  }

  Value *CreateICmpSGE(Value *LHS, Value *RHS, std::string Name = "") {
    return CreateICmp(ICmpInst::SGE, LHS, RHS, Name);
  }

  Value *CreateICmpSLT(Value *LHS, Value *RHS, std::string Name = "") {
    return CreateICmp(ICmpInst::SLT, LHS, RHS, Name);
  }

  Value *CreateICmpSLE(Value *LHS, Value *RHS, std::string Name = "") {
    return CreateICmp(ICmpInst::SLE, LHS, RHS, Name);
  }

  Value *CreateICmp(unsigned P, Value *LHS, Value *RHS, std::string Name = "") {
    if (auto *LC = cast<ConstantInt>(LHS))
      if (auto *RC = cast<ConstantInt>(RHS)) {
        // std::cout << "--Create Icmp with two Constant--" << std::endl;
        return getICmp(P, LC, RC);
      }
    // std::cout << "--IRBuilder CreateICmp --" <<std::endl;
    auto New = ICmpInst::Create(P, LHS, RHS);
    // std::cout << "--Insert Icmp --" <<std::endl;
    return Insert(New, Name);
  }

  //===--------------------------------------------------------------------===//
  // Instruction creation methods: Other Instructions
  //===--------------------------------------------------------------------===//
public:
  /// Call instruction
  CallInst *CreateCall(Value *Callee, ArrayRef<Value *> Args, std::string Name = "") {
    auto *func = cast<Function>(Callee);
    return CreateCall(func->getFunctionType(), Callee, Args, Name);
  }

  // CallInst *CreateCall(FunctionCallee Callee, ArrayRef<Value *> Args,
  //                      ArrayRef<OperandBundleDef> OpBundles,
  //                      std::string Name = "", MDNode *FPMathTag = nullptr) {
  //   return CreateCall(Callee.getFunctionType(), Callee.getCallee(), Args,
  //                     OpBundles, Name, FPMathTag);
  // }

  CallInst *CreateCall(FunctionType *FTy, Value *Callee, ArrayRef<Value *> Args, std::string Name = "") {
    CallInst *CI = CallInst::Create(FTy, Callee, Args);
    return Insert(CI, Name);
  }

  // CallInst *CreateCall(FunctionType *FTy, Value *Callee, ArrayRef<Value *>
  // Args,
  //                      ArrayRef<OperandBundleDef> OpBundles,
  //                      std::string Name = "", MDNode *FPMathTag = nullptr) {
  //   CallInst *CI = CallInst::Create(FTy, Callee, Args, OpBundles);
  //   if (IsFPConstrained)
  //     setConstrainedFPCallAttr(CI);
  //   if (isa<FPMathOperator>(CI))
  //     setFPAttrs(CI, FPMathTag, FMF);
  //   return Insert(CI, Name);
  // }

  Value *CreateZExt(Value *V, Type *DestTy) {
    if (V->getType() == DestTy)
      return V;
    if (auto *VC = cast<ConstantInt>(V)) {
      return ConstantInt::get(DestTy->getContext(), VC->getValue(), 32);
    }
    return Insert(new ZExtInst(DestTy, V));
  }
};

} // namespace YAL
#endif