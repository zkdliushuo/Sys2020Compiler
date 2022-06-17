#ifndef YAL_IR_INSTRS_H
#define YAL_IR_INSTRS_H
#include "Instruction.h"
#include <string>
#include <iostream>

/// 此文件是用来定义各种的指令类型

namespace YAL {
class Value;
class Module;
class LLVMContext;
class Type;
class IntegerType;
class ArrayType;
class FunctionType;
class PointerType;

/* ****************************************************************** */
/*                             ReturnInst                             */
/* ****************************************************************** */
class ReturnInst : public Instruction {
protected:
  friend class Instruction;

public:
  // 构造函数和析构函数
  ReturnInst(LLVMContext &C, Value *retVal, Instruction *InsertBefore=nullptr);
  ~ReturnInst() = default;

  // 创建Return指令
  static ReturnInst *Create(LLVMContext &C, Value *retVal, Instruction *InsertBefore=nullptr) {
    return new (!!retVal) ReturnInst(C, retVal, InsertBefore);
  }
};

/* ****************************************************************** */
/*                             AllocaInst                             */
/* ****************************************************************** */
class AllocaInst : public Instruction {
  Type *AllocatedType;

protected:
  friend class Instruction;

public:
  AllocaInst(Type *Ty, Value *ArraySize, std::string Name = "", Instruction *InsertBefore=nullptr);
  ~AllocaInst() { 
    // #ifdef DDD_DEBUG
    // // std::cout << "delete AllocaInst" <<std::endl; 
    // #endif
  }

  static AllocaInst *Create(Type *Ty, Value *ArraySize, std::string Name, Instruction *InsertBefore=nullptr) {
    return new AllocaInst(Ty, ArraySize, Name, InsertBefore);
  }

  // 获取分配地址的类型
  Type *getAllocatedType() { return AllocatedType; }
  Type *getAllocatedType() const { return AllocatedType; }

  // 获取数组大小
  const Value *getArraySize() const { return Op<0>(); }
  Value *getArraySize() { return Op<0>(); }

  // 因为我们只用到int，所以alloca得到的类型一定是Int32Ptr
  PointerType *getPtrType(LLVMContext &C) const { return Type::getInt32PtrTy(C); }

  // 是否是数组类型
  bool isArrayAllocated() const {
    // Value* size = Op<0>();
    if (isa<ArrayType>(AllocatedType))
      return true;
    else
      return false;
  }

  void *operator new(size_t s) { return User::operator new(s, 1); }
};

/* ****************************************************************** */
/*                             LoadInst                               */
/* ****************************************************************** */
class LoadInst : public Instruction {
protected:
  friend class Instruction;

public:
  LoadInst(Type *Ty, Value *Ptr, std::string Name, Instruction *InsertBefore=nullptr);
  ~LoadInst() {
    // #ifdef DDD_DEBUG 
    // // std::cout << "delete LoadInst" <<std::endl; 
    // #endif
  }

  static LoadInst *Create(Type *Ty, Value *Ptr, std::string Name, Instruction *InsertBefore=nullptr) {
    return new LoadInst(Ty, Ptr, Name, InsertBefore);
  }

  void *operator new(size_t s) { return User::operator new(s, 1); }

  Value *getPointerOperand() { return getNumOperand(0); }
};

/* ****************************************************************** */
/*                             StoreInst                              */
/* ****************************************************************** */
class StoreInst : public Instruction {
protected:
  friend class Instruction;

public:
  StoreInst(Value *val, Value *addr, Instruction *InsertBefore=nullptr);
  ~StoreInst() { 
    // #ifdef DDD_DEBUG
    // // std::cout << "delete StoreInst" <<std::endl; 
    // #endif
  }

  static StoreInst *Create(Value *val, Value *addr, Instruction *InsertBefore=nullptr) {
    return new StoreInst(val, addr, InsertBefore);
  }

  void *operator new(size_t s) { return User::operator new(s, 2); }

  Value *getPointerOperand() { return getNumOperand(1); }
};

/* ****************************************************************** */
/*                          GetElementPtrInst                         */
/* ****************************************************************** */
class GetElementPtrInst : public Instruction {
protected:
  friend class Instruction;

private:
  Type *SourceElementType;
  Type *ResultElementType;

public:
  GetElementPtrInst(Type *PointeeType, Value *Ptr, ArrayRef<Value *> IdxList,
                    unsigned Values, Instruction *InsertBefore=nullptr);
  GetElementPtrInst(Type *PointeeType, Value *Ptr, Value *Idx, unsigned Values, 
                    Instruction *InsertBefore=nullptr);
  ~GetElementPtrInst() {
    #ifdef DDD_DEBUG
    // std::cout << "delete GEPInst" <<std::endl; 
    #endif
  }

  /// getSourceElementType
  Type *getSourceElementType() const { return SourceElementType; }

  // 设置它是InBounds
  void setInBounds() {
    SubclassOptionalData = (SubclassOptionalData & ~1) | 1; // 最后一位置为1
  }

  bool hasAllZeroIndices() const;

  // 获取它是否是InBounds
  bool isInBounds() {
    if (SubclassOptionalData % 2 == 1)
      return true;
    else
      return false;
  }

  // 创建GetElementPtr指令
  static GetElementPtrInst *Create(Type *PointeeType, Value *Ptr,
                                   ArrayRef<Value *> IdxList, Instruction *InsertBefore=nullptr) {
    if (!PointeeType) {
      auto temp = cast<PointerType>(Ptr->getType());
      PointeeType = temp->getElementType();
    }
    // std::cout << "---GetElementPtrInst::Create !PointeeType---" << std::endl;
    unsigned Values = 1 + unsigned(IdxList.size());
    return new (Values) GetElementPtrInst(PointeeType, Ptr, IdxList, Values, InsertBefore);
  }

  static GetElementPtrInst *Create(Type *PointeeType, Value *Ptr,
                                   Value *IdxList, Instruction *InsertBefore=nullptr) {
    if (!PointeeType) {
      auto temp = cast<PointerType>(Ptr->getType());
      PointeeType = temp->getElementType();
    }
    unsigned Values = 2;
    return new (Values) GetElementPtrInst(PointeeType, Ptr, IdxList, Values, InsertBefore);
  }

  // 创建InBoundsGEP
  static GetElementPtrInst *CreateInBounds(Type *PointeeType, Value *Ptr,
                                           ArrayRef<Value *> IdxList, Instruction *InsertBefore=nullptr) {
    GetElementPtrInst *GEPInst = Create(PointeeType, Ptr, IdxList, InsertBefore);
    GEPInst->setInBounds();
    return GEPInst;
  }

  static GetElementPtrInst *CreateInBounds(Type *PointeeType, Value *Ptr,
                                           Value *Idx, Instruction *InsertBefore=nullptr) {
    GetElementPtrInst *GEPInst = Create(PointeeType, Ptr, Idx, InsertBefore);
    GEPInst->setInBounds();
    return GEPInst;
  }

  Value* getOffset(){ return Op<-1>().get();  }

  // 设置InBounds
};

/* ****************************************************************** */
/*                             BranchInst                             */
/* ****************************************************************** */
class BranchInst : public Instruction {
protected:
  friend class Instruction;

public:
  // 构造函数和析构函数
  BranchInst(BasicBlock *IfTrue, Instruction *InsertBefore=nullptr);
  BranchInst(BasicBlock *IfTrue, BasicBlock *IfFalse, Value *Cond, Instruction *InsertBefore=nullptr);
  ~BranchInst() { 
    // #ifdef DDD_DEBUG
    // // std::cout << "delete BranchInst" <<std::endl;
    // #endif
  }

  // 创建Branch指令
  static BranchInst *Create(BasicBlock *T, Instruction *InsertBefore=nullptr) {
     return new (1) BranchInst(T, InsertBefore); 
  }

  static BranchInst *Create(BasicBlock *T, BasicBlock *F, Value *Cond, Instruction *InsertBefore=nullptr) {
    return new (3) BranchInst(T, F, Cond, InsertBefore);
  }

  // 获取Condition
  Value *getCondition() { return Op<-3>(); }

  // 获取后继块
  BasicBlock *getSuccessor(unsigned i) {
    return dynamic_cast<BasicBlock *>(
        (&Op<-1>() - i)->get()); // cast_or_null, 暂时先用dynamic_cast代替
  }

  // 判断是否是CondBr
  bool isConditional() {
    return getNumOperands() == 3;
  }
};

/* ****************************************************************** */
/*                             ICmpInst                               */
/* ****************************************************************** */
class ICmpInst : public Instruction {
protected:
  friend class Instruction;

public:
  enum CmpTypes {
    EQ = 0, /// equal
    NE,     /// not equal
    SGT,    /// signed greater than
    SGE,    /// signed greater than or equal
    SLT,    /// signed less than
    SLE     /// signed less than or equal
  };

public:
  ICmpInst(unsigned pred, Value *LHS, Value *RHS, Instruction *InsertBefore=nullptr);
  ~ICmpInst() { 
    // #ifdef DDD_DEBUG
    // // std::cout << "delete ICmpInst" <<std::endl; 
    // #endif
  }

  // 创建ICmp指令
  static ICmpInst *Create(unsigned pred, Value *LHS, Value *RHS, Instruction *InsertBefore=nullptr) {
    return new ICmpInst(pred, LHS, RHS, InsertBefore);
  }

  // 设置比较方式
  void setCmpType(unsigned type) { setSubclassData(type); }

  void *operator new(size_t s) { 
    // #ifdef DDD_DEBUG
    // std::cout << "IcmpInst new is calling User's new" <<std::endl;
    // #endif
    return User::operator new(s, 2); 
  }

  // 获取比较方式
  const char *getCmpType() const {
    switch (getSubclassDataFromValue()) {
    case EQ:
      return "eq";
    case NE:
      return "ne";
    case SGT:
      return "sgt";
    case SGE:
      return "sge";
    case SLT:
      return "slt";
    case SLE:
      return "sle";
    default:
      return "<Icmp type error>";
    }
  }

  std::string getCmpType_codegen() {
    switch (getSubclassDataFromValue()) {
    case EQ:
      return "eq";
    case NE:
      return "ne";
    case SGT:
      return "gt";
    case SGE:
      return "ge";
    case SLT:
      return "lt";
    case SLE:
      return "le";
    default:
      return "<Icmp type error>";
    }
  }
};

/* ****************************************************************** */
/*                         BinaryOperator                             */
/* ****************************************************************** */
class BinaryOperator : public Instruction {
protected:
  friend class Instruction;

public:
  BinaryOperator(unsigned iType, Value *S1, Value *S2, Type *Ty, Instruction *InsertBefore=nullptr);
  ~BinaryOperator() { 
    // #ifdef DDD_DEBUG
    // // std::cout << "delete BinaryOperator" <<std::endl; 
    // #endif
  }

  static BinaryOperator *Create(unsigned Op, Value *S1, Value *S2, Instruction *InsertBefore=nullptr) {
    return new BinaryOperator(Op, S1, S2, S1->getType(), InsertBefore);
  }

  static BinaryOperator *CreateNeg(Value *Op, std::string Name="", Instruction *InsertBefore=nullptr);
  static BinaryOperator *CreateNot(Value *Op, std::string Name="", Instruction *InsertBefore=nullptr);

  void setHasNoSignedWrap(bool B) {
    SubclassOptionalData = (SubclassOptionalData & ~2) | (B * 2);
  }

  void *operator new(size_t s) {
    return User::operator new(s, 2);
  }
};

/* ****************************************************************** */
/*                            CallInst                                */
/* ****************************************************************** */
class CallInst : public Instruction {
protected:
  friend class Instruction;

private:
  FunctionType *FTy;

public:
  CallInst(FunctionType *Ty, Value *Func, ArrayRef<Value *> args,
           std::string &Name, Instruction *InsertBefore=nullptr);
  ~CallInst() {
    // #ifdef DDD_DEBUG
    // // std::cout << "delete CallInst" <<std::endl;
    // #endif
  }

  void init(FunctionType *FTy, Value *Func, ArrayRef<Value *> args,
            std::string &NameStr);

  static CallInst *Create(FunctionType *Ty, Value *Func, ArrayRef<Value *> Args,
                          std::string NameStr = "", Instruction *InsertBefore=nullptr) {
    return new (Args.size() + 1) CallInst(Ty, Func, Args, NameStr, InsertBefore);
  }

  // 获取调用的函数
  Value *getCalledValue() const { return Op<-1>(); }

  // 获取调用的函数类型
  FunctionType *getFunctionType() { return FTy; }
  FunctionType *getFunctionType() const { return FTy; }
};

/* ****************************************************************** */
/*                            ZExtInst                                */
/* ****************************************************************** */
class ZExtInst : public Instruction {
public:
  ZExtInst(Type *Ty, Value *V, Instruction *InsertBefore=nullptr);
  ~ZExtInst() {}

  void *operator new(size_t s) {
    return User::operator new(s, 1);
  }

  Type *getDestType() { return getType(); }

  Value *getValueTobeExtended() { return Op<0>(); }
};


/* ****************************************************************** */
/*                            PHINode                                 */
/* ****************************************************************** */
class PHINode : public Instruction {
  /// The number of operands actually allocated.  NumOperands is
  /// the number actually in use.
  unsigned ReservedSpace;

  PHINode(const PHINode &PN);

  explicit PHINode(Type *Ty, unsigned NumReservedValues,
                   std::string NameStr = "",
                   Instruction *InsertBefore = nullptr)
    : Instruction(Ty, Instruction::PHI, nullptr, 0, InsertBefore),
      ReservedSpace(NumReservedValues) {
    // setName(NameStr);
    allocHungoffUses(ReservedSpace);
  }

  // PHINode(Type *Ty, unsigned NumReservedValues, std::string NameStr,
  //         BasicBlock *InsertAtEnd)
  //   : Instruction(Ty, Instruction::PHI, nullptr, 0),
  //     ReservedSpace(NumReservedValues) {
  //   setName(NameStr);
  //   allocHungoffUses(ReservedSpace);
  // }

protected:
  // Note: Instruction needs to be a friend here to call cloneImpl.
  friend class Instruction;

  // PHINode *cloneImpl() const;

  // allocHungoffUses - this is more complicated than the generic
  // User::allocHungoffUses, because we have to allocate Uses for the incoming
  // values and pointers to the incoming blocks, all in one allocation.
  void allocHungoffUses(unsigned N) {
    User::allocHungoffUses(N, /* IsPhi */ true);
  }

public:
  /// Constructors - NumReservedValues is a hint for the number of incoming
  /// edges that this phi node will have (use 0 if you really have no idea).
  static PHINode *Create(Type *Ty, unsigned NumReservedValues,
                         std::string NameStr = "",
                         Instruction *InsertBefore = nullptr) {
    return new PHINode(Ty, NumReservedValues, NameStr, InsertBefore);
  }

  // static PHINode *Create(Type *Ty, unsigned NumReservedValues,
  //                        std::string NameStr, BasicBlock *InsertAtEnd) {
  //   return new PHINode(Ty, NumReservedValues, NameStr, InsertAtEnd);
  // }

  /// Provide fast operand accessors
  // DECLARE_TRANSPARENT_OPERAND_ACCESSORS(Value);

  // Block iterator interface. This provides access to the list of incoming
  // basic blocks, which parallels the list of incoming values.

  using block_iterator = BasicBlock **;
  using const_block_iterator = BasicBlock * const *;

  block_iterator block_begin() {
    return reinterpret_cast<block_iterator>(op_begin() + ReservedSpace);
  }

  const_block_iterator block_begin() const {
    return reinterpret_cast<const_block_iterator>(op_begin() + ReservedSpace);
  }

  block_iterator block_end() {
    return block_begin() + getNumOperands();
  }

  const_block_iterator block_end() const {
    return block_begin() + getNumOperands();
  }

  iterator_range<block_iterator> blocks() {
    return make_range(block_begin(), block_end());
  }

  iterator_range<const_block_iterator> blocks() const {
    return make_range(block_begin(), block_end());
  }

  op_range incoming_values() { return operands(); }

  const_op_range incoming_values() const { return operands(); }

  /// Return the number of incoming edges
  ///
  unsigned getNumIncomingValues() const { return getNumOperands(); }

  /// Return incoming value number x
  ///
  Value *getIncomingValue(unsigned i) const {
    return getNumOperand(i);
  }
  void setIncomingValue(unsigned i, Value *V) {
    assert(V && "PHI node got a null value!");
    assert(getType() == V->getType() &&
           "All operands to PHI node must be the same type as the PHI node!");
    getNumOperand(i) = V;
  }

  // static unsigned getOperandNumForIncomingValue(unsigned i) {
  //   return i;
  // }

  // static unsigned getIncomingValueNumForOperand(unsigned i) {
  //   return i;
  // }

  /// Return incoming basic block number @p i.
  ///
  BasicBlock *getIncomingBlock(unsigned i) const {
    return block_begin()[i];
  }

  /// Return incoming basic block corresponding
  /// to an operand of the PHI.
  ///
  BasicBlock *getIncomingBlock(const Use &U) const {
    assert(this == U.getUser() && "Iterator doesn't point to PHI's Uses?");
    return getIncomingBlock(unsigned(&U - op_begin()));
  }

  /// Return incoming basic block corresponding
  /// to value use iterator.
  ///
  BasicBlock *getIncomingBlock(Value::const_user_iterator I) const {
    return getIncomingBlock(I.getUse());
  }

  void setIncomingBlock(unsigned i, BasicBlock *BB) {
    assert(BB && "PHI node got a null basic block!");
    block_begin()[i] = BB;
  }

  /// Replace every incoming basic block \p Old to basic block \p New.
  void replaceIncomingBlockWith(const BasicBlock *Old, BasicBlock *New) {
    assert(New && Old && "PHI node got a null basic block!");
    for (unsigned Op = 0, NumOps = getNumOperands(); Op != NumOps; ++Op)
      if (getIncomingBlock(Op) == Old)
        setIncomingBlock(Op, New);
  }

  /// Add an incoming value to the end of the PHI list
  ///
  void addIncoming(Value *V, BasicBlock *BB) {
    if (getNumOperands() == ReservedSpace)
      growOperands();  // Get more space!
    // Initialize some new operands.
    setNumHungOffUseOperands(getNumOperands() + 1);
    setIncomingValue(getNumOperands() - 1, V);
    setIncomingBlock(getNumOperands() - 1, BB);
  }

  /// Remove an incoming value.  This is useful if a
  /// predecessor basic block is deleted.  The value removed is returned.
  ///
  /// If the last incoming value for a PHI node is removed (and DeletePHIIfEmpty
  /// is true), the PHI node is destroyed and any uses of it are replaced with
  /// dummy values.  The only time there should be zero incoming values to a PHI
  /// node is when the block is dead, so this strategy is sound.
  ///
  Value *removeIncomingValue(unsigned Idx, bool DeletePHIIfEmpty = true);

  Value *removeIncomingValue(const BasicBlock *BB, bool DeletePHIIfEmpty=true) {
    int Idx = getBasicBlockIndex(BB);
    assert(Idx >= 0 && "Invalid basic block argument to remove!");
    return removeIncomingValue(Idx, DeletePHIIfEmpty);
  }

  /// Return the first index of the specified basic
  /// block in the value list for this PHI.  Returns -1 if no instance.
  ///
  int getBasicBlockIndex(const BasicBlock *BB) const {
    for (unsigned i = 0, e = getNumOperands(); i != e; ++i)
      if (block_begin()[i] == BB)
        return i;
    return -1;
  }

  Value *getIncomingValueForBlock(const BasicBlock *BB) const {
    int Idx = getBasicBlockIndex(BB);
    assert(Idx >= 0 && "Invalid basic block argument!");
    return getIncomingValue(Idx);
  }

  /// Set every incoming value(s) for block \p BB to \p V.
  void setIncomingValueForBlock(const BasicBlock *BB, Value *V) {
    assert(BB && "PHI node got a null basic block!");
    bool Found = false;
    for (unsigned Op = 0, NumOps = getNumOperands(); Op != NumOps; ++Op)
      if (getIncomingBlock(Op) == BB) {
        Found = true;
        setIncomingValue(Op, V);
      }
    (void)Found;
    assert(Found && "Invalid basic block argument to set!");
  }

  /// If the specified PHI node always merges together the
  /// same value, return the value, otherwise return null.
  Value *hasConstantValue() const;

  /// Whether the specified PHI node always merges
  /// together the same value, assuming undefs are equal to a unique
  /// non-undef value.
  bool hasConstantOrUndefValue() const;

  /// Methods for support type inquiry through isa, cast, and dyn_cast:
  static bool classof(const Instruction *I) {
    return I->getOpcode() == Instruction::PHI;
  }
  static bool classof(const Value *V) {
    return isa<Instruction>(V) && classof(cast<Instruction>(V));
  }

private:
  void growOperands();
};
}
#endif