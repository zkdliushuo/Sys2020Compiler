## IRBuilder创建指令过程中涉及到的相关类

#### `ReturnInst`：

使用到它的相关代码：

源代码：

```cpp
  ReturnInst *CreateRetVoid() {
    return Insert(ReturnInst::Create(Context));
  }

  ReturnInst *CreateRet(Value *V) {
    return Insert(ReturnInst::Create(Context, V));
  }
```

##### 属性

使用到的都是继承过来的属性

##### 方法

1. `ReturnInst::Create`，它相关的源码：

```cpp
  static ReturnInst* Create(LLVMContext &C, Value *retVal = nullptr,
                            Instruction *InsertBefore = nullptr) {
    return new(!!retVal) ReturnInst(C, retVal, InsertBefore);
  }
```

2. 其中的`ReturnInst()`函数定义如下：其中使用到了`Type`类`Type::getVoidTy()`、`Instruction`类的构造函数


```cpp
ReturnInst::ReturnInst(const ReturnInst &RI)
    : Instruction(Type::getVoidTy(RI.getContext()), Instruction::Ret,
                  OperandTraits<ReturnInst>::op_end(this) - RI.getNumOperands(),
                  RI.getNumOperands()) {
  if (RI.getNumOperands())
    Op<0>() = RI.Op<0>();
  SubclassOptionalData = RI.SubclassOptionalData;
}

ReturnInst::ReturnInst(LLVMContext &C, Value *retVal, Instruction *InsertBefore)
    : Instruction(Type::getVoidTy(C), Instruction::Ret,
                  OperandTraits<ReturnInst>::op_end(this) - !!retVal, !!retVal,
                  InsertBefore) {
  if (retVal)
    Op<0>() = retVal;
}

ReturnInst::ReturnInst(LLVMContext &C, Value *retVal, BasicBlock *InsertAtEnd)
    : Instruction(Type::getVoidTy(C), Instruction::Ret,
                  OperandTraits<ReturnInst>::op_end(this) - !!retVal, !!retVal,
                  InsertAtEnd) {
  if (retVal)
    Op<0>() = retVal;
}

ReturnInst::ReturnInst(LLVMContext &Context, BasicBlock *InsertAtEnd)
    : Instruction(Type::getVoidTy(Context), Instruction::Ret,
                  OperandTraits<ReturnInst>::op_end(this), 0, InsertAtEnd) {}
```



#### `BranchInst`

使用到它的代码：

```cpp
  /// Create an unconditional 'br label X' instruction.
  BranchInst *CreateBr(BasicBlock *Dest) {
    return Insert(BranchInst::Create(Dest));
  }

  /// Create a conditional 'br Cond, TrueDest, FalseDest'
  /// instruction.
  BranchInst *CreateCondBr(Value *Cond, BasicBlock *True, BasicBlock *False,
                           MDNode *BranchWeights = nullptr,
                           MDNode *Unpredictable = nullptr) {
    return Insert(addBranchMetadata(BranchInst::Create(True, False, Cond),
                                    BranchWeights, Unpredictable));
  }
```

##### 属性

使用继承属性

##### 方法

* `BranchInst::Create()`

  ```cpp
    static BranchInst *Create(BasicBlock *IfTrue,
                              Instruction *InsertBefore = nullptr) {
      return new(1) BranchInst(IfTrue, InsertBefore);
    }
  
    static BranchInst *Create(BasicBlock *IfTrue, BasicBlock *IfFalse,
                              Value *Cond, Instruction *InsertBefore = nullptr) {
      return new(3) BranchInst(IfTrue, IfFalse, Cond, InsertBefore);
    }
  ```

* `BranchInst()`：

  ```cpp
  BranchInst::BranchInst(BasicBlock *IfTrue, Instruction *InsertBefore)
      : Instruction(Type::getVoidTy(IfTrue->getContext()), Instruction::Br,
                    OperandTraits<BranchInst>::op_end(this) - 1, 1,
                    InsertBefore) {
    assert(IfTrue && "Branch destination may not be null!");
    Op<-1>() = IfTrue;
  }
  
  BranchInst::BranchInst(BasicBlock *IfTrue, BasicBlock *IfFalse, Value *Cond,
                         Instruction *InsertBefore)
      : Instruction(Type::getVoidTy(IfTrue->getContext()), Instruction::Br,
                    OperandTraits<BranchInst>::op_end(this) - 3, 3,
                    InsertBefore) {
    Op<-1>() = IfTrue;
    Op<-2>() = IfFalse;
    Op<-3>() = Cond;
  #ifndef NDEBUG
    AssertOK();
  #endif
  }
  ```



#### `BinaryOperator`

使用到它的代码：

```cpp
  BinaryOperator *CreateInsertNUWNSWBinOp(BinaryOperator::BinaryOps Opc,
                                          Value *LHS, Value *RHS,
                                          const Twine &Name,
                                          bool HasNUW, bool HasNSW) {
    BinaryOperator *BO = Insert(BinaryOperator::Create(Opc, LHS, RHS), Name);
    if (HasNUW) BO->setHasNoUnsignedWrap();
    if (HasNSW) BO->setHasNoSignedWrap();
    return BO;
  }

// 包括所有的算术类的指令，如CreateAdd
  Value *CreateAdd(Value *LHS, Value *RHS, const Twine &Name = "",
                   bool HasNUW = false, bool HasNSW = false) {
    if (auto *LC = dyn_cast<Constant>(LHS))
      if (auto *RC = dyn_cast<Constant>(RHS))
        return Insert(Folder.CreateAdd(LC, RC, HasNUW, HasNSW), Name);
    return CreateInsertNUWNSWBinOp(Instruction::Add, LHS, RHS, Name,
                                   HasNUW, HasNSW);
  }
```

##### 方法

* `BinaryOperator::Create()`：

  ```cpp
  BinaryOperator *BinaryOperator::Create(BinaryOps Op, Value *S1, Value *S2,
                                         const Twine &Name,
                                         Instruction *InsertBefore) {
    assert(S1->getType() == S2->getType() &&
           "Cannot create binary operator with two operands of differing type!");
    return new BinaryOperator(Op, S1, S2, S1->getType(), Name, InsertBefore);
  }
  ```

* `BinaryOperator()`：

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
    setName(Name);//void llvm::Value::setName(const llvm::Twine &Name)
    AssertOK();
  }
  ```

* `setHasNoSignedWrap()`：是`Instruction`类中的方法，详细内容在`Instruction`下

#### `AllocaInst`

使用到的地方：

```cpp
  AllocaInst *CreateAlloca(Type *Ty, Value *ArraySize = nullptr,
                           const Twine &Name = "") {
    const DataLayout &DL = BB->getModule()->getDataLayout();
    Align AllocaAlign = DL.getPrefTypeAlign(Ty);
    unsigned AddrSpace = DL.getAllocaAddrSpace();
    return Insert(new AllocaInst(Ty, AddrSpace, ArraySize, AllocaAlign), Name);
  }
```

##### 方法

* `AllocaInst()`：

  ```cpp
  AllocaInst::AllocaInst(Type *Ty, unsigned AddrSpace, Value *ArraySize,
                         Align Align, const Twine &Name,
                         Instruction *InsertBefore)
      : UnaryInstruction(PointerType::get(Ty, AddrSpace), Alloca,
                         getAISize(Ty->getContext(), ArraySize), InsertBefore),
        AllocatedType(Ty) {
    setAlignment(Align);
    assert(!Ty->isVoidTy() && "Cannot allocate void!");
    setName(Name);
  }
  ```



#### `LoadInst`

使用到的地方：

```cpp
LoadInst *CreateAlignedLoad(Type *Ty, Value *Ptr, MaybeAlign Align,
                              bool isVolatile, const Twine &Name = "") {
    if (!Align) {
      const DataLayout &DL = BB->getModule()->getDataLayout();
      Align = DL.getABITypeAlign(Ty);
    }
    return Insert(new LoadInst(Ty, Ptr, Twine(), isVolatile, *Align), Name);
  }
```

##### 方法

* `LoadInst()`：

  ```cpp
  LoadInst::LoadInst(Type *Ty, Value *Ptr, const Twine &Name, bool isVolatile,
                     Align Align, AtomicOrdering Order, SyncScope::ID SSID,
                     Instruction *InsertBef)
      : UnaryInstruction(Ty, Load, Ptr, InsertBef) {
    assert(Ty == cast<PointerType>(Ptr->getType())->getElementType());
    setVolatile(isVolatile);
    setAlignment(Align);
    setAtomic(Order, SSID);
    AssertOK();
    setName(Name);
  }
  ```

* `setVolatile()`：设置value类的subClassData属性，在咱们的文法中用不到Volatile，可以直接默认为False，也可以不实现这个方法

  ```cpp
    void setVolatile(bool V) {
      setInstructionSubclassData((getSubclassDataFromInstruction() & ~1) |
                                 (V ? 1 : 0));
    }
  ```

* `setInstructionSubclassData()`：

  ```cpp
    void setInstructionSubclassData(unsigned short D) {
      Instruction::setInstructionSubclassData(D);
    }
  ```

* `setAlignment()`：设置对齐

  ```cpp
  void LoadInst::setAlignment(Align Align) {
    assert(Align <= MaximumAlignment &&
           "Alignment is greater than MaximumAlignment!");
    setInstructionSubclassData((getSubclassDataFromInstruction() & ~(31 << 1)) |
                               (encode(Align) << 1));
    assert(getAlign() == Align && "Alignment representation error!");
  }
  ```

* `setAtomic()`：我们的前端代码中都是默认Ordering=NotAtomic=0

  ```cpp
    /// Sets the ordering constraint and the synchronization scope ID of this load
    /// instruction.
    void setAtomic(AtomicOrdering Ordering,
                   SyncScope::ID SSID = SyncScope::System) {
      setOrdering(Ordering);
      setSyncScopeID(SSID);
    }
  ```

* `setOrdering`：Ordering默认为0

  ```cpp
    void setOrdering(AtomicOrdering Ordering) {
      setInstructionSubclassData((getSubclassDataFromInstruction() & ~(7 << 7)) |
                                 ((unsigned)Ordering << 7));
    }
  ```

* `setSyncScopeID`：在我们的代码中只会用到SSID=system=1，表示当前线程与所有并发执行的线程同步（具体定义在LLVMContext）

  ```cpp
  /// Sets the synchronization scope ID of this load instruction.
    void setSyncScopeID(SyncScope::ID SSID) {
      this->SSID = SSID;
    }
  ```

  

#### `StoreInst`

使用到的地方：

```cpp
  StoreInst *CreateAlignedStore(Value *Val, Value *Ptr, MaybeAlign Align,
                                bool isVolatile = false) {
    if (!Align) {
      const DataLayout &DL = BB->getModule()->getDataLayout();
      Align = DL.getABITypeAlign(Val->getType());
    }
    return Insert(new StoreInst(Val, Ptr, isVolatile, *Align));
  }
```

##### 属性

无

##### 方法

* `StoreInst()`：

  ```cpp
  StoreInst::StoreInst(Value *val, Value *addr, bool isVolatile, Align Align,
                       AtomicOrdering Order, SyncScope::ID SSID,
                       Instruction *InsertBefore)
      : Instruction(Type::getVoidTy(val->getContext()), Store,
                    OperandTraits<StoreInst>::op_begin(this),
                    OperandTraits<StoreInst>::operands(this), InsertBefore) {
    Op<0>() = val;
    Op<1>() = addr;
    setVolatile(isVolatile);
    setAlignment(Align);
    setAtomic(Order, SSID);
    AssertOK();
  }
  ```

* `setVolatile、setAlignment、setAtomic`和`LoadInst`一样

#### `GetElementPtrInst`

使用到的地方：

```cpp
  Value *CreateInBoundsGEP(Type *Ty, Value *Ptr, Value *Idx,
                           const Twine &Name = "") {
    if (auto *PC = dyn_cast<Constant>(Ptr))
      if (auto *IC = dyn_cast<Constant>(Idx))
        return Insert(Folder.CreateInBoundsGetElementPtr(Ty, PC, IC), Name);
    return Insert(GetElementPtrInst::CreateInBounds(Ty, Ptr, Idx), Name);
  }
```

##### 方法

* `GetElementPtrInst::CreateInBounds()`：创建InBounds的GEP指令

  ```cpp
    static GetElementPtrInst *
    CreateInBounds(Type *PointeeType, Value *Ptr, ArrayRef<Value *> IdxList,
                   const Twine &NameStr = "",
                   Instruction *InsertBefore = nullptr) {
      GetElementPtrInst *GEP =
          Create(PointeeType, Ptr, IdxList, NameStr, InsertBefore);
      GEP->setIsInBounds(true);
      return GEP;
    }
  ```

* `GetElementPtrInst::Create()`：创建GEP指令

  ```cpp
  static GetElementPtrInst *Create(Type *PointeeType, Value *Ptr,
                                     ArrayRef<Value *> IdxList,
                                     const Twine &NameStr = "",
                                     Instruction *InsertBefore = nullptr) {
      unsigned Values = 1 + unsigned(IdxList.size());
      if (!PointeeType)
        PointeeType =
            cast<PointerType>(Ptr->getType()->getScalarType())->getElementType();
      else
        assert(
            PointeeType ==
            cast<PointerType>(Ptr->getType()->getScalarType())->getElementType());
      return new (Values) GetElementPtrInst(PointeeType, Ptr, IdxList, Values,
                                            NameStr, InsertBefore);
    }
  ```

* `GetElementPtrInst()`：构造函数

  ```cpp
  GetElementPtrInst::GetElementPtrInst(Type *PointeeType, Value *Ptr,
                                       ArrayRef<Value *> IdxList, unsigned Values,
                                       const Twine &NameStr,
                                       Instruction *InsertBefore)
      : Instruction(getGEPReturnType(PointeeType, Ptr, IdxList), GetElementPtr,
                    OperandTraits<GetElementPtrInst>::op_end(this) - Values,
                    Values, InsertBefore),
        SourceElementType(PointeeType),
        ResultElementType(getIndexedType(PointeeType, IdxList)) {
    assert(ResultElementType ==
           cast<PointerType>(getType()->getScalarType())->getElementType());
    init(Ptr, IdxList, NameStr);
  }
  ```

* `GetElementPtrInst::getGEPReturnType()`：获取指针类型（因为不涉及到vector，所以就是获取`PointerType`）

  ```cpp
    /// Returns the pointer type returned by the GEP
    /// instruction, which may be a vector of pointer.s  
    static Type *getGEPReturnType(Type *ElTy, Value *Ptr,
                                  ArrayRef<Value *> IdxList) {
      Type *PtrTy = PointerType::get(checkGEPType(getIndexedType(ElTy, IdxList)),
                                     Ptr->getType()->getPointerAddressSpace());
      // Vector GEP
      if (auto *PtrVTy = dyn_cast<VectorType>(Ptr->getType())) {
        ElementCount EltCount = PtrVTy->getElementCount();
        return VectorType::get(PtrTy, EltCount);
      }
      for (Value *Index : IdxList)
        if (auto *IndexVTy = dyn_cast<VectorType>(Index->getType())) {
          ElementCount EltCount = IndexVTy->getElementCount();
          return VectorType::get(PtrTy, EltCount);
        }
      // Scalar GEP
      return PtrTy;
    }
  ```

* `GetElementPtrInst::checkGEPType()`：该函数在我们实现的过程中完全可以直接删除

  ```cpp
  inline Type *checkGEPType(Type *Ty) {
    assert(Ty && "Invalid GetElementPtrInst indices for type!");
    return Ty;
  }
  ```

* `GetElementPtrInst::getIndexedType()`：

  ```cpp
  Type *GetElementPtrInst::getIndexedType(Type *Ty, ArrayRef<Value *> IdxList) {
    return getIndexedTypeInternal(Ty, IdxList);
  }
  
  // 这个模板函数并不属于任何类
  template <typename IndexTy>
  static Type *getIndexedTypeInternal(Type *Ty, ArrayRef<IndexTy> IdxList) {
    if (IdxList.empty())
      return Ty;
    for (IndexTy V : IdxList.slice(1)) {
      Ty = GetElementPtrInst::getTypeAtIndex(Ty, V);
      if (!Ty)
        return Ty;
    }
    return Ty;
  }
  ```

* `GetElementPtrInst::getTypeAtIndex()`：只用到Array

  ```cpp
  Type *GetElementPtrInst::getTypeAtIndex(Type *Ty, uint64_t Idx) {
    if (auto Struct = dyn_cast<StructType>(Ty)) {
      if (Idx >= Struct->getNumElements())
        return nullptr;
      return Struct->getElementType(Idx);
    }
    if (auto Array = dyn_cast<ArrayType>(Ty))
      return Array->getElementType();// 只会用到这一句
    if (auto Vector = dyn_cast<VectorType>(Ty))
      return Vector->getElementType();
    return nullptr;
  }
  ```

* `GetElementPtrInst::init()`：

  ```cpp
  void GetElementPtrInst::init(Value *Ptr, ArrayRef<Value *> IdxList,
                               const Twine &Name) {
    assert(getNumOperands() == 1 + IdxList.size() &&
           "NumOperands not initialized?");
    Op<0>() = Ptr;
    llvm::copy(IdxList, op_begin() + 1);
    setName(Name);
  }
  ```

* `GetElementPtrInst::setIsInBounds()`：通过GEPOperator类的setIsInBounds方法设置SubclassData

  ```cpp
  void GetElementPtrInst::setIsInBounds(bool B) {
    cast<GEPOperator>(this)->setIsInBounds(B);
  }
  ```

  `GEPOperator::setIsInBounds()`：

  ```cpp
    void setIsInBounds(bool B) {
      SubclassOptionalData =
        (SubclassOptionalData & ~IsInBounds) | (B * IsInBounds);
    }
  ```

#### `ICmpInst`

使用到的地方：

```cpp
  Value *CreateICmp(CmpInst::Predicate P, Value *LHS, Value *RHS,
                    const Twine &Name = "") {
    if (auto *LC = dyn_cast<Constant>(LHS))
      if (auto *RC = dyn_cast<Constant>(RHS))
        return Insert(Folder.CreateICmp(P, LC, RC), Name);
    return Insert(new ICmpInst(P, LHS, RHS), Name);
  }
```

##### 方法

* `ICmpInst::ICmpInst()`：构造函数

  ```cpp
  ICmpInst(
      Predicate pred, ///< The predicate to use for the comparison
      Value *LHS,     ///< The left-hand-side of the expression
      Value *RHS,     ///< The right-hand-side of the expression
      const Twine &NameStr = "" ///< Name of the instruction
    ) : CmpInst(makeCmpResultType(LHS->getType()),
                Instruction::ICmp, pred, LHS, RHS, NameStr) {
  #ifndef NDEBUG
    AssertOK();
  #endif
    }
  ```

  使用到了`CmpInst`类

  * `CmpInst::CmpInst()`：构造函数

    ```cpp
    CmpInst::CmpInst(Type *ty, OtherOps op, Predicate predicate, Value *LHS,
                     Value *RHS, const Twine &Name, Instruction *InsertBefore,
                     Instruction *FlagsSource)
      : Instruction(ty, op,
                    OperandTraits<CmpInst>::op_begin(this),
                    OperandTraits<CmpInst>::operands(this),
                    InsertBefore) {
      Op<0>() = LHS;
      Op<1>() = RHS;
      setPredicate((Predicate)predicate);
      setName(Name);
      if (FlagsSource)
        copyIRFlags(FlagsSource);
    }
    ```

  * `CmpInst::setPredicate()`：Predict是enum用来标记比较的类型

    ```cpp
    void setPredicate(Predicate P) { setInstructionSubclassData(P); }
    ```

#### `CallInst`

使用到的地方：

```cpp
  CallInst *CreateCall(FunctionType *FTy, Value *Callee,
                       ArrayRef<Value *> Args = None, const Twine &Name = "",
                       MDNode *FPMathTag = nullptr) {
    CallInst *CI = CallInst::Create(FTy, Callee, Args, DefaultOperandBundles);
    if (IsFPConstrained)
      setConstrainedFPCallAttr(CI);
    if (isa<FPMathOperator>(CI))
      setFPAttrs(CI, FPMathTag, FMF);
    return Insert(CI, Name);
  }
```

##### 属性

```cpp
static constexpr int CalledOperandOpEndIdx = -1;

AttributeList Attrs; ///< parameter attributes for callable
FunctionType *FTy;
```

* `CalledOperandOpEndIdx`：调用的函数（Function类）
* `Attrs`：参数列表
* `FunctionType`：函数类型

##### 方法

* `CallInst::Create()`：

  ```cpp
    static CallInst *Create(FunctionType *Ty, Value *Func, ArrayRef<Value *> Args,
                            const Twine &NameStr,
                            Instruction *InsertBefore = nullptr) {
      return new (ComputeNumOperands(Args.size()))
          CallInst(Ty, Func, Args, None, NameStr, InsertBefore);
    }
  ```

* `CallInst::ComputeNumOperands()`：计算操作数个数（这里我们不需要NumBundleInputs）

  ```cpp
    /// Compute the number of operands to allocate.
    static int ComputeNumOperands(int NumArgs, int NumBundleInputs = 0) {
      // We need one operand for the called function, plus the input operand
      // counts provided.
      return 1 + NumArgs + NumBundleInputs;
    }
  ```

* `CallInst::CallInst()`：构造函数

  ```cpp
  CallInst::CallInst(FunctionType *Ty, Value *Func, ArrayRef<Value *> Args,
                     ArrayRef<OperandBundleDef> Bundles, const Twine &NameStr,
                     Instruction *InsertBefore)
      : CallBase(Ty->getReturnType(), Instruction::Call,
                 OperandTraits<CallBase>::op_end(this) -
                     (Args.size() + CountBundleInputs(Bundles) + 1),
                 unsigned(Args.size() + CountBundleInputs(Bundles) + 1),
                 InsertBefore) {
    init(Ty, Func, Args, Bundles, NameStr);
  }
  ```

  使用到了`CallBase`类：

  * `CallBase::CallBase()`：构造函数

    ```cpp
    CallBase(AttributeList const &A, FunctionType *FT, ArgsTy &&... Args)
          : Instruction(std::forward<ArgsTy>(Args)...), Attrs(A), FTy(FT) {}
    ```

    这里还涉及到了`AttributeList`类，具体可以看参考Attributes.h和Attributes.cpp

* `CallInst::init`：

  ```cpp
  void CallInst::init(FunctionType *FTy, Value *Func, ArrayRef<Value *> Args,
                      ArrayRef<OperandBundleDef> Bundles, const Twine &NameStr) {
    this->FTy = FTy;
    assert(getNumOperands() == Args.size() + CountBundleInputs(Bundles) + 1 &&
           "NumOperands not set up?");
    setCalledOperand(Func);
  
  #ifndef NDEBUG
    assert((Args.size() == FTy->getNumParams() ||
            (FTy->isVarArg() && Args.size() > FTy->getNumParams())) &&
           "Calling a function with bad signature!");
  
    for (unsigned i = 0; i != Args.size(); ++i)
      assert((i >= FTy->getNumParams() ||
              FTy->getParamType(i) == Args[i]->getType()) &&
             "Calling a function with a bad signature!");
  #endif
  
    llvm::copy(Args, op_begin());
  
    auto It = populateBundleOperandInfos(Bundles, Args.size());//可以忽略它
    (void)It;
    assert(It + 1 == op_end() && "Should add up!");
  
    setName(NameStr);
  }
  ```

* `CallInst::setCalledOperand()`：设置操作数

  ```cpp
    void setCalledOperand(Value *V) { Op<CalledOperandOpEndIdx>() = V; }
  ```

## 其他涉及到的类

#### `ArrayRef`



#### `Module`

##### 属性

* `DL`

##### 方法

* `getDataLayout()`：

  ```cpp
  const DataLayout &Module::getDataLayout() const { return DL; }
  ```

  

#### `DataLayout`

##### 属性

* `AllocaAddrSpace`

##### 方法

* `getPrefTypeAlign`：这里还涉及到了结构体`Align`，它的相关定义在Align.h

  ```cpp
  Align DataLayout::getPrefTypeAlign(Type *Ty) const {
    return getAlignment(Ty, false);
  }
  
  ```

* `getAlignment()`：这里因为只需要整数类型、数组类型、标签类型和指针类型，可以省去一部分的工作。

  ```cpp
  Align DataLayout::getAlignment(Type *Ty, bool abi_or_pref) const {
    AlignTypeEnum AlignType;
  
    assert(Ty->isSized() && "Cannot getTypeInfo() on a type that is unsized!");
    switch (Ty->getTypeID()) {
    // Early escape for the non-numeric types.
    case Type::LabelTyID:
      return abi_or_pref ? getPointerABIAlignment(0) : getPointerPrefAlignment(0);
    case Type::PointerTyID: {
      unsigned AS = cast<PointerType>(Ty)->getAddressSpace();
      return abi_or_pref ? getPointerABIAlignment(AS)
                         : getPointerPrefAlignment(AS);
      }
    case Type::ArrayTyID:
      return getAlignment(cast<ArrayType>(Ty)->getElementType(), abi_or_pref);
  
    case Type::StructTyID: {
      // Packed structure types always have an ABI alignment of one.
      if (cast<StructType>(Ty)->isPacked() && abi_or_pref)
        return Align(1);
  
      // Get the layout annotation... which is lazily created on demand.
      const StructLayout *Layout = getStructLayout(cast<StructType>(Ty));
      const Align Align = getAlignmentInfo(AGGREGATE_ALIGN, 0, abi_or_pref, Ty);
      return std::max(Align, Layout->getAlignment());
    }
    case Type::IntegerTyID:
      AlignType = INTEGER_ALIGN;
      break;
    case Type::HalfTyID:
    case Type::BFloatTyID:
    case Type::FloatTyID:
    case Type::DoubleTyID:
    // PPC_FP128TyID and FP128TyID have different data contents, but the
    // same size and alignment, so they look the same here.
    case Type::PPC_FP128TyID:
    case Type::FP128TyID:
    case Type::X86_FP80TyID:
      AlignType = FLOAT_ALIGN;
      break;
    case Type::X86_MMXTyID:
    case Type::FixedVectorTyID:
    case Type::ScalableVectorTyID:
      AlignType = VECTOR_ALIGN;
      break;
    default:
      llvm_unreachable("Bad type for getAlignment!!!");
    }
  
    // If we're dealing with a scalable vector, we just need the known minimum
    // size for determining alignment. If not, we'll get the exact size.
    return getAlignmentInfo(AlignType, getTypeSizeInBits(Ty).getKnownMinSize(),
                            abi_or_pref, Ty);
  }
  
  ```

  

* `getAlignmentInfo()`：

  ```cpp
  /// getAlignmentInfo - Return the alignment (either ABI if ABIInfo = true or
  /// preferred if ABIInfo = false) the layout wants for the specified datatype.
  Align DataLayout::getAlignmentInfo(AlignTypeEnum AlignType, uint32_t BitWidth,
                                     bool ABIInfo, Type *Ty) const {
    AlignmentsTy::const_iterator I = findAlignmentLowerBound(AlignType, BitWidth);
    // See if we found an exact match. Of if we are looking for an integer type,
    // but don't have an exact match take the next largest integer. This is where
    // the lower_bound will point to when it fails an exact match.
    if (I != Alignments.end() && I->AlignType == (unsigned)AlignType &&
        (I->TypeBitWidth == BitWidth || AlignType == INTEGER_ALIGN))
      return ABIInfo ? I->ABIAlign : I->PrefAlign;
  
    if (AlignType == INTEGER_ALIGN) {
      // If we didn't have a larger value try the largest value we have.
      if (I != Alignments.begin()) {
        --I; // Go to the previous entry and see if its an integer.
        if (I->AlignType == INTEGER_ALIGN)
          return ABIInfo ? I->ABIAlign : I->PrefAlign;
      }
    } else if (AlignType == VECTOR_ALIGN) {
      // By default, use natural alignment for vector types. This is consistent
      // with what clang and llvm-gcc do.
      unsigned Alignment =
          getTypeAllocSize(cast<VectorType>(Ty)->getElementType());
      // We're only calculating a natural alignment, so it doesn't have to be
      // based on the full size for scalable vectors. Using the minimum element
      // count should be enough here.
      Alignment *= cast<VectorType>(Ty)->getElementCount().Min;
      Alignment = PowerOf2Ceil(Alignment);
      return Align(Alignment);
     }
  
    // If we still couldn't find a reasonable default alignment, fall back
    // to a simple heuristic that the alignment is the first power of two
    // greater-or-equal to the store size of the type.  This is a reasonable
    // approximation of reality, and if the user wanted something less
    // less conservative, they should have specified it explicitly in the data
    // layout.
     unsigned Alignment = getTypeStoreSize(Ty);
     Alignment = PowerOf2Ceil(Alignment);
     return Align(Alignment);
  }
  ```

* `getAllocaAddrSpace()`：

  ```cpp
  unsigned getAllocaAddrSpace() const { return AllocaAddrSpace; }
  ```

#### `Type`

* `Type::getVoidTy()`



#### `Instruction`

##### 属性

* `HasMetadataBit`：

```cpp
  enum {
      /// This is a bit stored in the SubClassData field which indicates whether
      /// this instruction has metadata attached to it or not.
      HasMetadataBit = 1 << 15
    };
```

  

##### 方法

* `Instruction()`：构建函数

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
  
  Instruction::Instruction(Type *ty, unsigned it, Use *Ops, unsigned NumOps,
                           BasicBlock *InsertAtEnd)
    : User(ty, Value::InstructionVal + it, Ops, NumOps), Parent(nullptr) {
  
    // append this instruction into the basic block
    assert(InsertAtEnd && "Basic block to append to may not be NULL!");
    InsertAtEnd->getInstList().push_back(this);
  }
  ```

* 它是先将`Instruction`类转换成`OverflowingBinaryOperator`类，然后调用该类的方法

  ```cpp
  void Instruction::setHasNoSignedWrap(bool b) {
    cast<OverflowingBinaryOperator>(this)->setHasNoSignedWrap(b);
  }
  ```

  ```cpp
    // 这个方法是OverflowingBinaryOperator中的
    // OverflowingBinaryOperator::setHasNoSignedWrap
    void setHasNoSignedWrap(bool B) {
      SubclassOptionalData =
        (SubclassOptionalData & ~NoSignedWrap) | (B * NoSignedWrap);
    }
  
    enum {
      AnyWrap        = 0,
      NoUnsignedWrap = (1 << 0),
      NoSignedWrap   = (1 << 1)
    };
  ```


* `getSubclassDataFromInstruction()`：

  ```cpp
    unsigned getSubclassDataFromInstruction() const {
      return getSubclassDataFromValue() & ~HasMetadataBit;
    }
  ```

* `setInstructionSubclassData()`：

  ```cpp
    void setInstructionSubclassData(unsigned short D) {
      assert((D & HasMetadataBit) == 0 && "Out of range value put into field");
      setValueSubclassData((getSubclassDataFromValue() & HasMetadataBit) | D);
    }
  ```

* `setValueSubclassData()`：

  ```cpp
    void setValueSubclassData(unsigned short D) {
      Value::setValueSubclassData(D);
    }
  ```

* `getSubclassDataFromValue`：

  ```cpp
    unsigned short getSubclassDataFromValue() const {
      return Value::getSubclassDataFromValue();
    }
  ```

  

#### `User`

##### 属性



##### 方法

* `user()`：构造函数

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

* `Op<num>()`：

  ```cpp
    template <int Idx, typename U> static Use &OpFrom(const U *that) {
      return Idx < 0
        ? OperandTraits<U>::op_end(const_cast<U*>(that))[Idx]
        : OperandTraits<U>::op_begin(const_cast<U*>(that))[Idx];
    }
  
    template <int Idx> Use &Op() {
      return OpFrom<Idx>(this);
    }
    template <int Idx> const Use &Op() const {
      return OpFrom<Idx>(this);
    }
  ```

  它的相关宏定义为：

  ```cpp
  #define DECLARE_TRANSPARENT_OPERAND_ACCESSORS(VALUECLASS) \
    public: \
    inline VALUECLASS *getOperand(unsigned) const; \
    inline void setOperand(unsigned, VALUECLASS*); \
    inline op_iterator op_begin(); \
    inline const_op_iterator op_begin() const; \
    inline op_iterator op_end(); \
    inline const_op_iterator op_end() const; \
    protected: \
    template <int> inline Use &Op(); \
    template <int> inline const Use &Op() const; \
    public: \
    inline unsigned getNumOperands() const
  ```

  关于它更详细的描述在OprendTraits.h

  

#### `Value`

##### 属性

* `subClassData`：用来标记算术指令的NSW、NUW；Load、Store指令的一些属性；Icmp指令的类型，如>、<、==等
* `SubclassOptionalData`：用来标记GEP指令是否是"InBounds"

##### 方法

* `Value()`：构造函数

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

* `getSubclassDataFromValue`：

  ```cpp
  unsigned short getSubclassDataFromValue() const { return SubclassData; }
  ```

* `setValueSubclassData`：

  ```cpp
  void setValueSubclassData(unsigned short D) { SubclassData = D; }
  ```

  