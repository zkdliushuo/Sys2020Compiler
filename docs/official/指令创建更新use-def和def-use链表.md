以BinaryOperator指令创建为例（lib/IR/Instructions.cpp）

```cpp
BinaryOperator *BinaryOperator::Create(BinaryOps Op, Value *S1, Value *S2,
                                       const Twine &Name,
                                       Instruction *InsertBefore) {
  assert(S1->getType() == S2->getType() &&
         "Cannot create binary operator with two operands of differing type!");
  return new BinaryOperator(Op, S1, S2, S1->getType(), Name, InsertBefore);
}
```

创建接口会调用构建函数来创建指令（lib/IR/Instructions.cpp）

```cpp
BinaryOperator::BinaryOperator(BinaryOps iType, Value *S1, Value *S2,
                               Type *Ty, const Twine &Name,
                               Instruction *InsertBefore)
  : Instruction(Ty, iType,
                OperandTraits<BinaryOperator>::op_begin(this),
                OperandTraits<BinaryOperator>::operands(this),
                InsertBefore) {
  Op<0>() = S1;
  Op<1>() = S2;
  setName(Name);
  AssertOK();
}
```

BinaryOperator继承自Instruction，会调用Instruction的构造函数（lib/IR/Instruction.cpp）

```cpp
Instruction::Instruction(Type *ty, unsigned it, Use *Ops, unsigned NumOps,
                         Instruction *InsertBefore)
  : User(ty, Value::InstructionVal + it, Ops, NumOps), Parent(nullptr) {

  // If requested, insert this instruction into a basic block...
  if (InsertBefore) {
    BasicBlock *BB = InsertBefore->getParent();
    assert(BB && "Instruction to insert before is not in a basic block!");
    BB->getInstList().insert(InsertBefore->getIterator(), this);
  }
}
```

Instruction继承自User，会调用User的构造函数（include/llvm/IR/User.h）

```cpp
  User(Type *ty, unsigned vty, Use *, unsigned NumOps)
      : Value(ty, vty) {
    assert(NumOps < (1u << NumUserOperandsBits) && "Too many operands");
    NumUserOperands = NumOps;
    // If we have hung off uses, then the operand list should initially be
    // null.
    assert((!HasHungOffUses || !getOperandList()) &&
           "Error in initializing hung off uses for User");
  }
```

User继承自Value，会调用Value的构造函数（lib/IR/Value.cpp）

```cpp
Value::Value(Type *ty, unsigned scid)
    : VTy(checkType(ty)), UseList(nullptr), SubclassID(scid),
      HasValueHandle(0), SubclassOptionalData(0), SubclassData(0),
      NumUserOperands(0), IsUsedByMD(false), HasName(false) {
  static_assert(ConstantFirstVal == 0, "!(SubclassID < ConstantFirstVal)");
  // FIXME: Why isn't this in the subclass gunk??
  // Note, we cannot call isa<CallInst> before the CallInst has been
  // constructed.
  if (SubclassID == Instruction::Call || SubclassID == Instruction::Invoke ||
      SubclassID == Instruction::CallBr)
    assert((VTy->isFirstClassType() || VTy->isVoidTy() || VTy->isStructTy()) &&
           "invalid CallInst type!");
  else if (SubclassID != BasicBlockVal &&
           (/*SubclassID < ConstantFirstVal ||*/ SubclassID > ConstantLastVal))
    assert((VTy->isFirstClassType() || VTy->isVoidTy()) &&
           "Cannot create non-first-class values except for constants!");
  static_assert(sizeof(Value) == 2 * sizeof(void *) + 2 * sizeof(unsigned),
                "Value too big");
}
```

从Value构造过程可以看出，初始Value中UseList为空。

UseList主要通过Value的addUse接口来添加：

include/llvm/IR/Value.h

```cpp
void addUse(Use &U) { U.addToList(&UseList); }
```

include/llvm/IR/Use.h

```cpp
  void addToList(Use **List) {
    Next = *List;
    if (Next)
      Next->setPrev(&Next);
    setPrev(List);
    *List = this;
  }
```

这个接口主要由Use中的set接口调用，set接口主要由重载赋值运算来调用

```cpp
void Use::set(Value *V) {
  if (Val) removeFromList();
  Val = V;
  if (V) V->addUse(*this);
}

Value *Use::operator=(Value *RHS) {
  set(RHS);
  return RHS;
}

const Use &Use::operator=(const Use &RHS) {
  set(RHS.Val);
  return *this;
}
```



指令创建过程中，通过BinaryOperator构建函数中的如下代码块：

```cpp
  Op<0>() = S1;
  Op<1>() = S2;
```

这里的功能如下：

1）该赋值过程会调用赋值重载运算，BinaryOperator指令就添加到了两个Source的Uselist中了（set调用中，V表示两个source，所以addUse中用到的UseList是两个source自身的UseList，而This对应的是当前的Use，也就是BinaryOperator指令） ——更新了操作数的def-use，针对该链表的操作方法由Value类提供（use_begin/use_end）：

```cpp
use_iterator materialized_use_begin() { return use_iterator(UseList); }
  const_use_iterator materialized_use_begin() const {
    return const_use_iterator(UseList);
  }
  use_iterator use_begin() {
    assertModuleIsMaterialized();
    return materialized_use_begin();
  }
  const_use_iterator use_begin() const {
    assertModuleIsMaterialized();
    return materialized_use_begin();
  }
  use_iterator use_end() { return use_iterator(); }
  const_use_iterator use_end() const { return const_use_iterator(); }
  iterator_range<use_iterator> materialized_uses() {
    return make_range(materialized_use_begin(), use_end());
  }
  iterator_range<const_use_iterator> materialized_uses() const {
    return make_range(materialized_use_begin(), use_end());
  }
  iterator_range<use_iterator> uses() {
    assertModuleIsMaterialized();
    return materialized_uses();
  }
  iterator_range<const_use_iterator> uses() const {
    assertModuleIsMaterialized();
    return materialized_uses();
  }
```

2）添加到了指令的参数列表——更新了指令的use-def，操作接口由User提供，指令自身会对接口进行重载：

```cpp
DEFINE_TRANSPARENT_OPERAND_ACCESSORS(BinaryOperator, Value)
```

对应的宏为：提供了操作操作数的op_begin/op_end接口

```cpp
/// Macro for generating out-of-class operand accessor definitions
#define DEFINE_TRANSPARENT_OPERAND_ACCESSORS(CLASS, VALUECLASS) \
CLASS::op_iterator CLASS::op_begin() { \
  return OperandTraits<CLASS>::op_begin(this); \
} \
CLASS::const_op_iterator CLASS::op_begin() const { \
  return OperandTraits<CLASS>::op_begin(const_cast<CLASS*>(this)); \
} \
CLASS::op_iterator CLASS::op_end() { \
  return OperandTraits<CLASS>::op_end(this); \
} \
CLASS::const_op_iterator CLASS::op_end() const { \
  return OperandTraits<CLASS>::op_end(const_cast<CLASS*>(this)); \
} \
VALUECLASS *CLASS::getOperand(unsigned i_nocapture) const { \
  assert(i_nocapture < OperandTraits<CLASS>::operands(this) \
         && "getOperand() out of range!"); \
  return cast_or_null<VALUECLASS>( \
    OperandTraits<CLASS>::op_begin(const_cast<CLASS*>(this))[i_nocapture].get()); \
} \
void CLASS::setOperand(unsigned i_nocapture, VALUECLASS *Val_nocapture) { \
  assert(i_nocapture < OperandTraits<CLASS>::operands(this) \
         && "setOperand() out of range!"); \
  OperandTraits<CLASS>::op_begin(this)[i_nocapture] = Val_nocapture; \
} \
unsigned CLASS::getNumOperands() const { \
  return OperandTraits<CLASS>::operands(this); \
} \
template <int Idx_nocapture> Use &CLASS::Op() { \
  return this->OpFrom<Idx_nocapture>(this); \
} \
template <int Idx_nocapture> const Use &CLASS::Op() const { \
  return this->OpFrom<Idx_nocapture>(this); \
}
```

