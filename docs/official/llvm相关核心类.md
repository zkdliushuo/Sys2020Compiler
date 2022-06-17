## 说明

llvm核心类的相关材料可以在llvm.org上查得到（或者干脆直接使用google搜索需要了解的类，第一个就是官方文档）

推荐在https://github.com/llvm/llvm-project下载源代码，需要用到的代码在路径llvm/include和llvm/lib下

## llvm::LLVMContext

"This is an important class for using LLVM in a threaded context."

"It (opaquely) owns and manages the core "global" data of LLVM's core infrastructure, including the type and constant uniquing tables. LLVMContext itself provides no locking guarantees, so you should be careful to have one context per thread."

## llvm::Module

```cpp
  /// Print the module to an output stream with an optional
  /// AssemblyAnnotationWriter.  If \c ShouldPreserveUseListOrder, then include
  /// uselistorder directives so that use-lists can be recreated when reading
  /// the assembly.
  void print(raw_ostream &OS, AssemblyAnnotationWriter *AAW,
             bool ShouldPreserveUseListOrder = false,
             bool IsForDebug = false) const;
```



## llvm::Value

![Inheritance graph](https://llvm.org/doxygen/classllvm_1_1Value__inherit__graph.png)

#### 基本块类 llvm::BasicBlock

* llvm::BasicBlock：需要能够创建基本块

#### 常量类 llvm::Constant

* llvm::ConstantInt：

  ![Inheritance graph](https://llvm.org/doxygen/classllvm_1_1ConstantInt__inherit__graph.png)

  1. 定义整型和布尔型常量

  2. 使用Constant.get()方法得到相应的常量。

     ```c++
     cint = ConstantInt::get(context, APInt(32, num))
     ```

* llvm::ConstantArray:

  ![Inheritance graph](https://llvm.org/doxygen/classllvm_1_1ConstantArray__inherit__graph.png)

  1. 定义常量数组，可以用来初始化数组

  2. 使用ConstantArray.get()方法得到一个常量数组，也可以用它来初始化一个数组：

     ```cpp
     std::vector<llvm::Constant*> values;
     ...
     /* Make the value 42 appear in the array - ty is "i32" */
     llvm::Constant* c = llvm::Constant::getIntegerValue(ty, 42);
     values.push_back(c);
     ... // Add more values here ... 
     llvm::Constant* init = llvm::ConstantArray::get(arrayTy_0, values);
     GArray->setInitializer(init);
     ```

* llvm::GlobalVarible：![Inheritance graph](https://llvm.org/doxygen/classllvm_1_1GlobalVariable__inherit__graph.png)

  1. 定义全局变量

  2. 通过new GlobalVariable的方式来创建：

     ```cpp
     GlobalVariable(Module &M, Type *Ty, bool isConstant,
                      LinkageTypes Linkage, Constant *Initializer,
                      const Twine &Name = "", GlobalVariable *InsertBefore = nullptr,
                      ThreadLocalMode = NotThreadLocal, unsigned AddressSpace = 0,
                      bool isExternallyInitialized = false);
     ```

     可以通过setInitializer方法来赋初值

## llvm::Type

"The instances of the [Type](https://llvm.org/doxygen/classllvm_1_1Type.html) class are immutable: once they are created, they are never changed.

Also note that only one instance of a particular type is ever created. Thus seeing if two types are equal is a matter of doing a trivial pointer comparison. To enforce that no two equal instances are created, [Type](https://llvm.org/doxygen/classllvm_1_1Type.html) instances can only be created via static factory methods in class [Type](https://llvm.org/doxygen/classllvm_1_1Type.html) and in derived classes. Once allocated, Types are never free'd."

Ref: https://llvm.org/doxygen/classllvm_1_1Type.html

![Inheritance graph](https://llvm.org/doxygen/classllvm_1_1Type__inherit__graph.png)

* `getInt32Ty()`, `getInt32PtrTy()`

*  `isIntegerTy()` :

  ```cpp
  	/// True if this is an instance of IntegerType.
     bool isIntegerTy() const { return getTypeID() == IntegerTyID; }
   
     /// Return true if this is an IntegerType of the given width.
     bool isIntegerTy(unsigned Bitwidth) const;
  ```

* `isPointerTY()`, `isArrayTy()`

#### llvm::FunctionType

创建function的时候用来定义函数的返回值、参数等信息

* `get()`：

  ```cpp
    /// This static method is the primary way of constructing a FunctionType.
    static FunctionType *get(Type *Result,
                             ArrayRef<Type*> Params, bool isVarArg);
  
    /// Create a FunctionType taking no parameters.
    static FunctionType *get(Type *Result, bool isVarArg);
  ```

#### llvm::IntegerType

* `get()`:

  ```cpp
    /// This static method is the primary way of constructing an IntegerType.
    /// If an IntegerType with the same NumBits value was previously instantiated,
    /// that instance will be returned. Otherwise a new one will be created. Only
    /// one instance with a given NumBits value is ever created.
    /// Get or create an IntegerType instance.
    static IntegerType *get(LLVMContext &C, unsigned NumBits);
  ```

#### llvm::ArrayType



## llvm::IRBuilderBase

这是一个用来生成各种指令的类

* `SetInsertPoint()`：在基本块的最后设置插入点

  ```cpp
   void SetInsertPoint(BasicBlock *TheBB) {
      BB = TheBB;
      InsertPt = BB->end();
    }
  ```

* `CreateAlloca()`：创建一条alloca指令

  ```cpp
    AllocaInst *CreateAlloca(Type *Ty, unsigned AddrSpace,
                             Value *ArraySize = nullptr, const Twine &Name = "") {
      const DataLayout &DL = BB->getModule()->getDataLayout();
      Align AllocaAlign = DL.getPrefTypeAlign(Ty);
      return Insert(new AllocaInst(Ty, AddrSpace, ArraySize, AllocaAlign), Name);
    }
  
    AllocaInst *CreateAlloca(Type *Ty, Value *ArraySize = nullptr,
                             const Twine &Name = "") {
      const DataLayout &DL = BB->getModule()->getDataLayout();
      Align AllocaAlign = DL.getPrefTypeAlign(Ty);
      unsigned AddrSpace = DL.getAllocaAddrSpace();
      return Insert(new AllocaInst(Ty, AddrSpace, ArraySize, AllocaAlign), Name);
    }
  ```

* `CreateStore()`：创建一条store指令

  ```cpp
    StoreInst *CreateStore(Value *Val, Value *Ptr, bool isVolatile = false) {
      return CreateAlignedStore(Val, Ptr, MaybeAlign(), isVolatile);
    }
  ```

* `CreateLoad()`：创建一条load指令

  ```cpp
    LoadInst *CreateLoad(Type *Ty, Value *Ptr, const char *Name) {
      return CreateAlignedLoad(Ty, Ptr, MaybeAlign(), Name);
    }
  
    LoadInst *CreateLoad(Type *Ty, Value *Ptr, const Twine &Name = "") {
      return CreateAlignedLoad(Ty, Ptr, MaybeAlign(), Name);
    }
  
    LoadInst *CreateLoad(Type *Ty, Value *Ptr, bool isVolatile,
                         const Twine &Name = "") {
      return CreateAlignedLoad(Ty, Ptr, MaybeAlign(), isVolatile, Name);
    }
  
    // Deprecated [opaque pointer types]
    LoadInst *CreateLoad(Value *Ptr, const char *Name) {
      return CreateLoad(Ptr->getType()->getPointerElementType(), Ptr, Name);
    }
  
    // Deprecated [opaque pointer types]
    LoadInst *CreateLoad(Value *Ptr, const Twine &Name = "") {
      return CreateLoad(Ptr->getType()->getPointerElementType(), Ptr, Name);
    }
  
    // Deprecated [opaque pointer types]
    LoadInst *CreateLoad(Value *Ptr, bool isVolatile, const Twine &Name = "") {
      return CreateLoad(Ptr->getType()->getPointerElementType(), Ptr, isVolatile,
                        Name);
    }
  ```

* `CreateCondBr()`：创建一条条件跳转指令

  ```cpp
    BranchInst *CreateCondBr(Value *Cond, BasicBlock *True, BasicBlock *False,
                             MDNode *BranchWeights = nullptr,
                             MDNode *Unpredictable = nullptr) {
      return Insert(addBranchMetadata(BranchInst::Create(True, False, Cond),
                                      BranchWeights, Unpredictable));
    }
  
    /// Create a conditional 'br Cond, TrueDest, FalseDest'
    /// instruction. Copy branch meta data if available.
    BranchInst *CreateCondBr(Value *Cond, BasicBlock *True, BasicBlock *False,
                             Instruction *MDSrc) {
      BranchInst *Br = BranchInst::Create(True, False, Cond);
      if (MDSrc) {
        unsigned WL[4] = {LLVMContext::MD_prof, LLVMContext::MD_unpredictable,
                          LLVMContext::MD_make_implicit, LLVMContext::MD_dbg};
        Br->copyMetadata(*MDSrc, makeArrayRef(&WL[0], 4));
      }
      return Insert(Br);
    }
  ```

* `CreateBr()`：创建一条无条件跳转指令

  ```cpp
    BranchInst *CreateBr(BasicBlock *Dest) {
      return Insert(BranchInst::Create(Dest));
    }
  ```

* `CreateGEP()`：创建GEP指令，用来访问数组元素

  ```cpp
    Value *CreateGEP(Value *Ptr, ArrayRef<Value *> IdxList,
                     const Twine &Name = "") {
      return CreateGEP(nullptr, Ptr, IdxList, Name);
    }
  
    Value *CreateGEP(Type *Ty, Value *Ptr, ArrayRef<Value *> IdxList,
                     const Twine &Name = "") {
      if (auto *PC = dyn_cast<Constant>(Ptr)) {
        // Every index must be constant.
        size_t i, e;
        for (i = 0, e = IdxList.size(); i != e; ++i)
          if (!isa<Constant>(IdxList[i]))
            break;
        if (i == e)
          return Insert(Folder.CreateGetElementPtr(Ty, PC, IdxList), Name);
      }
      return Insert(GetElementPtrInst::Create(Ty, Ptr, IdxList), Name);
    }
  ```

* `CreateICmp**()`：一系列的整形常数比较指令

  ```cpp
  Value *CreateICmpEQ(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_EQ, LHS, RHS, Name);
    }
  
    Value *CreateICmpNE(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_NE, LHS, RHS, Name);
    }
  
    Value *CreateICmpUGT(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_UGT, LHS, RHS, Name);
    }
  
    Value *CreateICmpUGE(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_UGE, LHS, RHS, Name);
    }
  
    Value *CreateICmpULT(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_ULT, LHS, RHS, Name);
    }
  
    Value *CreateICmpULE(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_ULE, LHS, RHS, Name);
    }
  
    Value *CreateICmpSGT(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_SGT, LHS, RHS, Name);
    }
  
    Value *CreateICmpSGE(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_SGE, LHS, RHS, Name);
    }
  
    Value *CreateICmpSLT(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_SLT, LHS, RHS, Name);
    }
  
    Value *CreateICmpSLE(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateICmp(ICmpInst::ICMP_SLE, LHS, RHS, Name);
    }
  ```

* `CreateADD(), CreateNSWAdd()`：一系列的三地址计算指令

  ```cpp
    Value *CreateAdd(Value *LHS, Value *RHS, const Twine &Name = "",
                     bool HasNUW = false, bool HasNSW = false) {
      if (auto *LC = dyn_cast<Constant>(LHS))
        if (auto *RC = dyn_cast<Constant>(RHS))
          return Insert(Folder.CreateAdd(LC, RC, HasNUW, HasNSW), Name);
      return CreateInsertNUWNSWBinOp(Instruction::Add, LHS, RHS, Name,
                                     HasNUW, HasNSW);
    }
  
    Value *CreateNSWAdd(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateAdd(LHS, RHS, Name, false, true);
    }
  
    Value *CreateNUWAdd(Value *LHS, Value *RHS, const Twine &Name = "") {
      return CreateAdd(LHS, RHS, Name, true, false);
    }
  ```

* `CreateCall()`：创建函数调用指令

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
  
    CallInst *CreateCall(FunctionType *FTy, Value *Callee, ArrayRef<Value *> Args,
                         ArrayRef<OperandBundleDef> OpBundles,
                         const Twine &Name = "", MDNode *FPMathTag = nullptr) {
      CallInst *CI = CallInst::Create(FTy, Callee, Args, OpBundles);
      if (IsFPConstrained)
        setConstrainedFPCallAttr(CI);
      if (isa<FPMathOperator>(CI))
        setFPAttrs(CI, FPMathTag, FMF);
      return Insert(CI, Name);
    }
  
    CallInst *CreateCall(FunctionCallee Callee, ArrayRef<Value *> Args = None,
                         const Twine &Name = "", MDNode *FPMathTag = nullptr) {
      return CreateCall(Callee.getFunctionType(), Callee.getCallee(), Args, Name,
                        FPMathTag);
    }
  
    CallInst *CreateCall(FunctionCallee Callee, ArrayRef<Value *> Args,
                         ArrayRef<OperandBundleDef> OpBundles,
                         const Twine &Name = "", MDNode *FPMathTag = nullptr) {
      return CreateCall(Callee.getFunctionType(), Callee.getCallee(), Args,
                        OpBundles, Name, FPMathTag);
    }
  ```


