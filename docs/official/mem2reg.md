#LLVM IR -> Strict SSA

LLVM IR不是严格的SSA指令的主要原因是局部变量通过alloca指令表现，同时会有多个load和store指令对其读写，这与SSA中要求每个变量只能store一次的要求相背，故LLVM IR需要进行处理。

### 调用mem2reg之前需要做的事：生成Dominator Tree

### 总览：mem2reg.cpp中的主要逻辑

```cpp
static bool promoteMemoryToRegister(Function &F, DominatorTree &DT,
                                    AssumptionCache &AC) {
  std::vector<AllocaInst *> Allocas;
  BasicBlock &BB = F.getEntryBlock(); // Get the entry node for the function
  bool Changed = false;

  while (true) {
    Allocas.clear();

    // Find allocas that are safe to promote, by looking at all instructions in
    // the entry node
    for (BasicBlock::iterator I = BB.begin(), E = --BB.end(); I != E; ++I)
      if (AllocaInst *AI = dyn_cast<AllocaInst>(I)) // Is it an alloca?
        if (isAllocaPromotable(AI))
          Allocas.push_back(AI);

    if (Allocas.empty())
      break;

    PromoteMemToReg(Allocas, DT, &AC);
    NumPromoted += Allocas.size();
    Changed = true;
  }
  return Changed;
}
```

遍历每个函数中所有的基本块，寻找alloca指令，对每个找到的alloca指令判断其是否能够提升为寄存器，将能够提升的全部提升。

###如何提升变量：PromoteMemToReg.cpp的主要逻辑

```cpp
void llvm::PromoteMemToReg(ArrayRef<AllocaInst *> Allocas, DominatorTree &DT,
                           AssumptionCache *AC) {
  // If there is nothing to do, bail out...
  if (Allocas.empty())
    return;

  PromoteMem2Reg(Allocas, DT, AC).run();
}
```

主要使用`PromoteMem2Reg`来完成操作，`PromoteMem2Reg`的构造函数：

```cpp
PromoteMem2Reg(ArrayRef<AllocaInst *> Allocas, DominatorTree &DT,
                 AssumptionCache *AC)
      : Allocas(Allocas.begin(), Allocas.end()), DT(DT),
        DIB(*DT.getRoot()->getParent()->getParent(), /*AllowUnresolved*/ false),
        AC(AC), SQ(DT.getRoot()->getParent()->getParent()->getDataLayout(),
                   nullptr, &DT, AC) {}
```

**主要逻辑在run这个成员函数中：**

**1、第一步：检查死代码**

```cpp
if (AI->use_empty()) {
      // If there are no uses of the alloca, just delete it now.
      AI->eraseFromParent();

      // Remove the alloca from the Allocas list, since it has been processed
      RemoveFromAllocasList(AllocaNum);
      ++NumDeadAlloca;
      continue;
    }
```

如果该alloca没有被使用过，直接删除

**2、第二步：计算每个alloca的属性**

包括它被store的基本块(DefiningBlocks)，被load的基本块(UsingBlocks)，是否只有一个基本块使用了这个alloca(OnlyUsedInOneBlock)

**3、第三步：根据alloca计算得到的信息来改写load**

- 如果alloca只在一个基本块中被store，则该alloca已经符合SSA的要求，找到所有被该store支配的load，用store的操作数替换load的use，注意可能存在load不被store支配的情况，但该情况存在与指针，不包含在本次比赛的语言子集中，不予考虑

```cpp
// If there is only a single store to this value, replace any loads of
    // it that are directly dominated by the definition with the value stored.
    if (Info.DefiningBlocks.size() == 1) {
      if (rewriteSingleStoreAlloca(AI, Info, LBI, SQ.DL, DT, AC)) {
        // The alloca has been processed, move on.
        RemoveFromAllocasList(AllocaNum);
        ++NumSingleStore;
        continue;
      }
```

执行替换操作的函数：

```cpp
static bool rewriteSingleStoreAlloca(AllocaInst *AI, AllocaInfo &Info,
                                     LargeBlockInfo &LBI, const DataLayout &DL,
                                     DominatorTree &DT, AssumptionCache *AC) {
  StoreInst *OnlyStore = Info.OnlyStore;
  //检查store的是不是全局变量
  bool StoringGlobalVal = !isa<Instruction>(OnlyStore->getOperand(0));
  BasicBlock *StoreBB = OnlyStore->getParent();
  int StoreIndex = -1;

  // 清空，用于保存那些不能被修改的load
  Info.UsingBlocks.clear();

  for (auto UI = AI->user_begin(), E = AI->user_end(); UI != E;) {
    Instruction *UserInst = cast<Instruction>(*UI++);
    if (UserInst == OnlyStore)
      continue;
    LoadInst *LI = cast<LoadInst>(UserInst);
    
    //这一段程序都检查load不被store支配的情况，这种情况不能修改load
    if (!StoringGlobalVal) { // Non-instructions are always dominated.
      //检查load和store是否在一个基本块中，如果load在store的前面，则不能处理，但这种情况不存在于我们的程序
      if (LI->getParent() == StoreBB) {
        // If we have a use that is in the same block as the store, compare the
        // indices of the two instructions to see which one came first.  If the
        // load came before the store, we can't handle it.
        if (StoreIndex == -1)
          StoreIndex = LBI.getInstructionIndex(OnlyStore);

        if (unsigned(StoreIndex) > LBI.getInstructionIndex(LI)) {
          // Can't handle this load, bail out.
          Info.UsingBlocks.push_back(StoreBB);
          continue;
        }
      } 
      //这里同样处理store不支配load的情况
      else if (!DT.dominates(StoreBB, LI->getParent())) {
        // If the load and store are in different blocks, use BB dominance to
        // check their relationships.  If the store doesn't dom the use, bail
        // out.
        Info.UsingBlocks.push_back(LI->getParent());
        continue;
      }
    }
    
    
		//获取store的操作数
    Value *ReplVal = OnlyStore->getOperand(0);
    // store支配load但流程上load出现在store之前，说明存在一个不经过函数入口的路径先到达了load再到store，这时假设是undef，因为函数不可能不从入口进入
    if (ReplVal == LI)
      ReplVal = UndefValue::get(LI->getType());

    // If the load was marked as nonnull we don't want to lose
    // that information when we erase this Load. So we preserve
    // it with an assume.
    if (AC && LI->getMetadata(LLVMContext::MD_nonnull) &&
        !isKnownNonZero(ReplVal, DL, 0, AC, LI, &DT))
      addAssumeNonNull(AC, LI);
    
		//替换load的user
    LI->replaceAllUsesWith(ReplVal);
    LI->eraseFromParent();
    LBI.deleteValue(LI);
  }

  //存在不能修改的load，退出
  if (!Info.UsingBlocks.empty())
    return false; // If not, we'll have to fall back for the remainder.

  //debug信息
  for (DbgVariableIntrinsic *DII : Info.DbgDeclares) {
    DIBuilder DIB(*AI->getModule(), /*AllowUnresolved*/ false);
    ConvertDebugDeclareToDebugValue(DII, Info.OnlyStore, DIB);
    DII->eraseFromParent();
  }
  //如果所有load都能被修改，则本次修改成功
  //删除store，因为修改了load之后，store变成了死指令
  Info.OnlyStore->eraseFromParent();
  LBI.deleteValue(Info.OnlyStore);
	
  //删除alloca
  AI->eraseFromParent();
  return true;
}
```

- 如果alloca只在一个基本块中被使用(可能存在多个store)，同样也是将修改load

```cpp
if (Info.OnlyUsedInOneBlock &&
        promoteSingleBlockAlloca(AI, Info, LBI, SQ.DL, DT, AC)) {
      // The alloca has been processed, move on.
      RemoveFromAllocasList(AllocaNum);
      continue;
    }
```

修改主要使用`promoteSingleBlockAlloca`函数：

```cpp
static bool promoteSingleBlockAlloca(AllocaInst *AI, const AllocaInfo &Info,
                                     LargeBlockInfo &LBI,
                                     const DataLayout &DL,
                                     DominatorTree &DT,
                                     AssumptionCache *AC) {
  
  using StoresByIndexTy = SmallVector<std::pair<unsigned, StoreInst *>, 64>;
  StoresByIndexTy StoresByIndex;

  
  //查找所有的store并记录store的位置
  for (User *U : AI->users())
    if (StoreInst *SI = dyn_cast<StoreInst>(U))
      StoresByIndex.push_back(std::make_pair(LBI.getInstructionIndex(SI), SI));
  llvm::sort(StoresByIndex, less_first());

	//查找所有的load
  for (auto UI = AI->user_begin(), E = AI->user_end(); UI != E;) {
    LoadInst *LI = dyn_cast<LoadInst>(*UI++);
    if (!LI)
      continue;

    unsigned LoadIdx = LBI.getInstructionIndex(LI);

    //查找离load最近的store
    StoresByIndexTy::iterator I = llvm::lower_bound(
        StoresByIndex,
        std::make_pair(LoadIdx, static_cast<StoreInst *>(nullptr)),
        less_first());
    //没有store在load前面，凉凉
    if (I == StoresByIndex.begin()) {
      //压根没store
      if (StoresByIndex.empty())
        LI->replaceAllUsesWith(UndefValue::get(LI->getType()));
      else
        return false;
    } 
    //找到store
    else {
      //获取store的操作数
      Value *ReplVal = std::prev(I)->second->getOperand(0);
      
      if (AC && LI->getMetadata(LLVMContext::MD_nonnull) &&
          !isKnownNonZero(ReplVal, DL, 0, AC, LI, &DT))
        addAssumeNonNull(AC, LI);

      // store支配load但流程上load出现在store之前，说明存在一个不经过函数入口的路径先到达了load再到store，这时假设是undef，因为函数不可能不从入口进入
      if (ReplVal == LI)
        ReplVal = UndefValue::get(LI->getType());
			
      //修改load
      LI->replaceAllUsesWith(ReplVal);
    }

    LI->eraseFromParent();
    LBI.deleteValue(LI);
  }

  // Remove the (now dead) stores and alloca.
  while (!AI->use_empty()) {
    StoreInst *SI = cast<StoreInst>(AI->user_back());
    // Record debuginfo for the store before removing it.
    for (DbgVariableIntrinsic *DII : Info.DbgDeclares) {
      DIBuilder DIB(*AI->getModule(), /*AllowUnresolved*/ false);
      ConvertDebugDeclareToDebugValue(DII, SI, DIB);
    }
    SI->eraseFromParent();
    LBI.deleteValue(SI);
  }

  AI->eraseFromParent();

  // The alloca's debuginfo can be removed as well.
  for (DbgVariableIntrinsic *DII : Info.DbgDeclares)
    DII->eraseFromParent();

  ++NumLocalPromoted;
  return true;
}
```

**4、第四步：计算每个alloca的live-in 基本块**

live-in的定义时在一个基本块中，对该alloca store的指令不能在所有load之前

```cpp
ComputeLiveInBlocks(AI, Info, DefBlocks, LiveInBlocks);
```

该函数的定义为：

```cpp
void PromoteMem2Reg::ComputeLiveInBlocks(
    AllocaInst *AI, AllocaInfo &Info,
    const SmallPtrSetImpl<BasicBlock *> &DefBlocks,
    SmallPtrSetImpl<BasicBlock *> &LiveInBlocks) {
  
  //先将所有用到alloca的基本块加入
  SmallVector<BasicBlock *, 64> LiveInBlockWorklist(Info.UsingBlocks.begin(),
                                                    Info.UsingBlocks.end());

  //对每个基本块进行扫描
  for (unsigned i = 0, e = LiveInBlockWorklist.size(); i != e; ++i) {
    BasicBlock *BB = LiveInBlockWorklist[i];
    //如果该基本块中并没有store，则不用管
    if (!DefBlocks.count(BB))
      continue;
		//对于有store的基本块，检查store是否在load前
    for (BasicBlock::iterator I = BB->begin();; ++I) {
      if (StoreInst *SI = dyn_cast<StoreInst>(I)) {
        if (SI->getOperand(1) != AI)
          continue;

        //store在load前，该基本块不是live-in的
        LiveInBlockWorklist[i] = LiveInBlockWorklist.back();
        LiveInBlockWorklist.pop_back();
        --i;
        --e;
        break;
      }
			//load在store前，说明是live-in的
      if (LoadInst *LI = dyn_cast<LoadInst>(I))
        if (LI->getOperand(0) == AI)
          break;
    }
  }

  // Now that we have a set of blocks where the phi is live-in, recursively add
  // their predecessors until we find the full region the value is live.
  while (!LiveInBlockWorklist.empty()) {
    BasicBlock *BB = LiveInBlockWorklist.pop_back_val();

    //将live-in的基本块收集起来
    if (!LiveInBlocks.insert(BB).second)
      continue;

    //live-in 的基本块的前继可能也是live-in的或者对这个alloca进行了store
    for (BasicBlock *P : predecessors(BB)) {
      //对alloca进行了store
      if (DefBlocks.count(P))
        continue;

      // live-in的
      LiveInBlockWorklist.push_back(P);
    }
  }
}
```

**5、第五步：创建PHI节点**

```cpp
// At this point, we're committed to promoting the alloca using IDF's, and
    // the standard SSA construction algorithm.  Determine which blocks need phi
    // nodes and see if we can optimize out some work by avoiding insertion of
    // dead phi nodes.
    IDF.setLiveInBlocks(LiveInBlocks);
    IDF.setDefiningBlocks(DefBlocks);
    SmallVector<BasicBlock *, 32> PHIBlocks;
    IDF.calculate(PHIBlocks);
    llvm::sort(PHIBlocks, [this](BasicBlock *A, BasicBlock *B) {
      return BBNumbers.find(A)->second < BBNumbers.find(B)->second;
    });

    unsigned CurrentVersion = 0;
    for (BasicBlock *BB : PHIBlocks)
      QueuePhiNode(BB, AllocaNum, CurrentVersion);
  }
```

这里使用了IDF来计算那些基本块需要插入PHI节点，并使用`QueuePhiNode`来创建PHI节点

IDF指IteratedDominanceFrontier，存在于https://github.com/llvm/llvm-project/blob/master/llvm/include/llvm/Analysis/IteratedDominanceFrontier.h

```cpp
template <bool IsPostDom>
class IDFCalculator final : public IDFCalculatorBase<BasicBlock, IsPostDom> {
public:
  using IDFCalculatorBase =
      typename llvm::IDFCalculatorBase<BasicBlock, IsPostDom>;
  using ChildrenGetterTy = typename IDFCalculatorBase::ChildrenGetterTy;

  IDFCalculator(DominatorTreeBase<BasicBlock, IsPostDom> &DT)
      : IDFCalculatorBase(DT) {}

  IDFCalculator(DominatorTreeBase<BasicBlock, IsPostDom> &DT,
                const GraphDiff<BasicBlock *, IsPostDom> *GD)
      : IDFCalculatorBase(DT, ChildrenGetterTy(GD)) {
    assert(GD);
  }
};

using ForwardIDFCalculator = IDFCalculator<false>;
using ReverseIDFCalculator = IDFCalculator<true>;
```

该类由`IDFCalculatorBase`衍生，这个类的定义在https://github.com/llvm/llvm-project/blob/master/llvm/include/llvm/Support/GenericIteratedDominanceFrontier.h中：

```cpp
template <class NodeTy, bool IsPostDom> class IDFCalculatorBase {
public:
  using OrderedNodeTy =
      std::conditional_t<IsPostDom, Inverse<NodeTy *>, NodeTy *>;
  using ChildrenGetterTy =
      IDFCalculatorDetail::ChildrenGetterTy<NodeTy, IsPostDom>;

  IDFCalculatorBase(DominatorTreeBase<NodeTy, IsPostDom> &DT) : DT(DT) {}

  IDFCalculatorBase(DominatorTreeBase<NodeTy, IsPostDom> &DT,
                    const ChildrenGetterTy &C)
      : DT(DT), ChildrenGetter(C) {}

  /// Give the IDF calculator the set of blocks in which the value is
  /// defined.  This is equivalent to the set of starting blocks it should be
  /// calculating the IDF for (though later gets pruned based on liveness).
  ///
  /// Note: This set *must* live for the entire lifetime of the IDF calculator.
  void setDefiningBlocks(const SmallPtrSetImpl<NodeTy *> &Blocks) {
    DefBlocks = &Blocks;
  }

  /// Give the IDF calculator the set of blocks in which the value is
  /// live on entry to the block.   This is used to prune the IDF calculation to
  /// not include blocks where any phi insertion would be dead.
  ///
  /// Note: This set *must* live for the entire lifetime of the IDF calculator.
  void setLiveInBlocks(const SmallPtrSetImpl<NodeTy *> &Blocks) {
    LiveInBlocks = &Blocks;
    useLiveIn = true;
  }

  /// Reset the live-in block set to be empty, and tell the IDF
  /// calculator to not use liveness anymore.
  void resetLiveInBlocks() {
    LiveInBlocks = nullptr;
    useLiveIn = false;
  }

  /// Calculate iterated dominance frontiers
  ///
  /// This uses the linear-time phi algorithm based on DJ-graphs mentioned in
  /// the file-level comment.  It performs DF->IDF pruning using the live-in
  /// set, to avoid computing the IDF for blocks where an inserted PHI node
  /// would be dead.
  void calculate(SmallVectorImpl<NodeTy *> &IDFBlocks);

private:
  DominatorTreeBase<NodeTy, IsPostDom> &DT;
  ChildrenGetterTy ChildrenGetter;
  bool useLiveIn = false;
  const SmallPtrSetImpl<NodeTy *> *LiveInBlocks;
  const SmallPtrSetImpl<NodeTy *> *DefBlocks;
};
```

其中最重要的`calculate`函数的定义：

```cpp
template <class NodeTy, bool IsPostDom>
void IDFCalculatorBase<NodeTy, IsPostDom>::calculate(
    SmallVectorImpl<NodeTy *> &IDFBlocks) {
  // Use a priority queue keyed on dominator tree level so that inserted nodes
  // are handled from the bottom of the dominator tree upwards. We also augment
  // the level with a DFS number to ensure that the blocks are ordered in a
  // deterministic way.
  using DomTreeNodePair =
      std::pair<DomTreeNodeBase<NodeTy> *, std::pair<unsigned, unsigned>>;
  using IDFPriorityQueue =
      std::priority_queue<DomTreeNodePair, SmallVector<DomTreeNodePair, 32>,
                          less_second>;

  IDFPriorityQueue PQ;

  DT.updateDFSNumbers();

  SmallVector<DomTreeNodeBase<NodeTy> *, 32> Worklist;
  SmallPtrSet<DomTreeNodeBase<NodeTy> *, 32> VisitedPQ;
  SmallPtrSet<DomTreeNodeBase<NodeTy> *, 32> VisitedWorklist;
  
  
	//所有含有store的基本块均被插入队列，因为它们的后继块可能需要插入PHI节点
  for (NodeTy *BB : *DefBlocks)
    if (DomTreeNodeBase<NodeTy> *Node = DT.getNode(BB)) {
      PQ.push({Node, std::make_pair(Node->getLevel(), Node->getDFSNumIn())});	//DFSNumIn指DFS访问的顺序
      VisitedWorklist.insert(Node);
    }

  while (!PQ.empty()) {
    DomTreeNodePair RootPair = PQ.top();
    PQ.pop();
    DomTreeNodeBase<NodeTy> *Root = RootPair.first;
    unsigned RootLevel = RootPair.second.first;

    // Walk all dominator tree children of Root, inspecting their CFG edges with
    // targets elsewhere on the dominator tree. Only targets whose level is at
    // most Root's level are added to the iterated dominance frontier of the
    // definition set.

    assert(Worklist.empty());
    Worklist.push_back(Root);

    while (!Worklist.empty()) {
      DomTreeNodeBase<NodeTy> *Node = Worklist.pop_back_val();
      NodeTy *BB = Node->getBlock();
      // Succ is the successor in the direction we are calculating IDF, so it is
      // successor for IDF, and predecessor for Reverse IDF.
      //检查需要插入PHI节点的基本块
      auto DoWork = [&](NodeTy *Succ) {
        DomTreeNodeBase<NodeTy> *SuccNode = DT.getNode(Succ);

        const unsigned SuccLevel = SuccNode->getLevel();
        if (SuccLevel > RootLevel)
          return;

        if (!VisitedPQ.insert(SuccNode).second)
          return;

        NodeTy *SuccBB = SuccNode->getBlock();
        //这个后继块必须要是live-in的，否则无论传入alloca的什么值，都会被后面的store覆盖，没有必要插入PHI节点
        if (useLiveIn && !LiveInBlocks->count(SuccBB))
          return;

        IDFBlocks.emplace_back(SuccBB);
        //这个后继基本块中没有store，它的后继也需要被检查，因为这个后继基本块的后继可能也需要插入PHI节点，其中一个来源是Node
        if (!DefBlocks->count(SuccBB))
          PQ.push(std::make_pair(
              SuccNode, std::make_pair(SuccLevel, SuccNode->getDFSNumIn())));
      };
			
      //检查这个基本块的每一个后继
      for (auto Succ : ChildrenGetter.get(BB))
        DoWork(Succ);

      for (auto DomChild : *Node) {
        if (VisitedWorklist.insert(DomChild).second)
          Worklist.push_back(DomChild);
      }
    }
  }
}
```

`QueuePhiNode`函数：


```cpp
bool PromoteMem2Reg::QueuePhiNode(BasicBlock *BB, unsigned AllocaNo,
                                  unsigned &Version) {
  // Look up the basic-block in question.
  PHINode *&PN = NewPhiNodes[std::make_pair(BBNumbers[BB], AllocaNo)];

  // If the BB already has a phi node added for the i'th alloca then we're done!
  if (PN)
    return false;

  // Create a PhiNode using the dereferenced type... and add the phi-node to the
  // BasicBlock.
  PN = PHINode::Create(Allocas[AllocaNo]->getAllocatedType(), getNumPreds(BB),
                       Allocas[AllocaNo]->getName() + "." + Twine(Version++),
                       &BB->front());
  ++NumPHIInsert;
  PhiToAllocaMap[PN] = AllocaNo;
  return true;
}
```

**6、第六步：为每个PHI节点设置incoming value - 重命名**

```cpp
//把每一个alloca的incoming value设为null，incoming value意为流出block的该alloca的值
  RenamePassData::ValVector Values(Allocas.size());
  for (unsigned i = 0, e = Allocas.size(); i != e; ++i)
    Values[i] = UndefValue::get(Allocas[i]->getAllocatedType());

  // When handling debug info, treat all incoming values as if they have unknown
  // locations until proven otherwise.
  RenamePassData::LocationVector Locations(Allocas.size());

  // 这里只push了一个元素，所以现在RenamePassWorkList的长度为1，emplace_back与push_back类似但更优化
  std::vector<RenamePassData> RenamePassWorkList;
  RenamePassWorkList.emplace_back(&F.front(), nullptr, std::move(Values),
                                  std::move(Locations));
  do {
    RenamePassData RPD = std::move(RenamePassWorkList.back());
    RenamePassWorkList.pop_back();
    // 然而RenamePass可能会往RenamePassWorkList加入新的元素，故有循环
    RenamePass(RPD.BB, RPD.Pred, RPD.Values, RPD.Locations, RenamePassWorkList);
  } while (!RenamePassWorkList.empty());
```

需要注意的是，这个RenamePass只能rename从第一个基本块能够到达的其他基本块，有些不能到达的基本块则不会做任何处理

`RenamePass`执行主要的重命名过程：

```cpp
void PromoteMem2Reg::RenamePass(BasicBlock *BB, BasicBlock *Pred,
                                RenamePassData::ValVector &IncomingVals,
                                RenamePassData::LocationVector &IncomingLocs,
                                std::vector<RenamePassData> &Worklist) {
NextIteration:
  //基本块中有PHI节点
  if (PHINode *APN = dyn_cast<PHINode>(BB->begin())) {
    //该PHI节点与某个alloca相关
    if (PhiToAllocaMap.count(APN)) {
      // 注意PHI节点可能之前就存在，并不是被该算法插入，对于之前就存在的PHI节点要分开对待
      //	All other PHI nodes being
			// inserted by this pass of mem2reg will have the same number of incoming
			// operands so far.  Remember this count.
      unsigned NewPHINumOperands = APN->getNumOperands();
			//计算基本块与它的前继有多少路径连接
      unsigned NumEdges = std::count(succ_begin(Pred), succ_end(Pred), BB);
      assert(NumEdges && "Must be at least one edge from Pred to BB!");

      // Add entries for all the phis.
      BasicBlock::iterator PNI = BB->begin();
      do {
        unsigned AllocaNo = PhiToAllocaMap[APN];

        // Update the location of the phi node.
        updateForIncomingValueLocation(APN, IncomingLocs[AllocaNo],
                                       APN->getNumIncomingValues() > 0);

        // 把所有的incoming value存入PHI节点
        for (unsigned i = 0; i != NumEdges; ++i)
          APN->addIncoming(IncomingVals[AllocaNo], Pred);

        // 原来所有的incoming values是null，但现在该alloca的incoming value变成了这个PHI节点，注意后面这个值还可能会更新，因为基本块中可能存在store
        IncomingVals[AllocaNo] = APN;
        for (DbgVariableIntrinsic *DII : AllocaDbgDeclares[AllocaNo])
          ConvertDebugDeclareToDebugValue(DII, APN, DIB);

        // 下一个PHI节点
        ++PNI;
        APN = dyn_cast<PHINode>(PNI);
        if (!APN)
          break;

        // 操作数数量不一致，不是这个程序插入的PHI节点，不管
      } while (APN->getNumOperands() == NewPHINumOperands);
    }
  }

  // 不重复处理基本块
  if (!Visited.insert(BB).second)
    return;
  
  //开始更新基本块中的所有load和store

  for (BasicBlock::iterator II = BB->begin(); !II->isTerminator();) {
    Instruction *I = &*II++; // get the instruction, increment iterator

    if (LoadInst *LI = dyn_cast<LoadInst>(I)) {
      AllocaInst *Src = dyn_cast<AllocaInst>(LI->getPointerOperand());
      if (!Src)
        continue;

      DenseMap<AllocaInst *, unsigned>::iterator AI = AllocaLookup.find(Src);
      if (AI == AllocaLookup.end())
        continue;

      Value *V = IncomingVals[AI->second];

      // If the load was marked as nonnull we don't want to lose
      // that information when we erase this Load. So we preserve
      // it with an assume.
      if (AC && LI->getMetadata(LLVMContext::MD_nonnull) &&
          !isKnownNonZero(V, SQ.DL, 0, AC, LI, &DT))
        addAssumeNonNull(AC, LI);

      // 把load的use替换成PHI节点
      LI->replaceAllUsesWith(V);
      BB->getInstList().erase(LI);
    } else if (StoreInst *SI = dyn_cast<StoreInst>(I)) {
      // Delete this instruction and mark the name as the current holder of the
      // value
      AllocaInst *Dest = dyn_cast<AllocaInst>(SI->getPointerOperand());
      if (!Dest)
        continue;

      DenseMap<AllocaInst *, unsigned>::iterator ai = AllocaLookup.find(Dest);
      if (ai == AllocaLookup.end())
        continue;

      // 碰到store指令后，说明alloca的值还会改变，不再是之前PHI节点的输出值，故incoming values改写
      unsigned AllocaNo = ai->second;
      IncomingVals[AllocaNo] = SI->getOperand(0);

      // Record debuginfo for the store before removing it.
      IncomingLocs[AllocaNo] = SI->getDebugLoc();
      for (DbgVariableIntrinsic *DII : AllocaDbgDeclares[ai->second])
        ConvertDebugDeclareToDebugValue(DII, SI, DIB);
      //store指令直接被删掉
      BB->getInstList().erase(SI);
    }
  }

  // 处理基本块的后继
  succ_iterator I = succ_begin(BB), E = succ_end(BB);
  if (I == E)
    return;

  // Keep track of the successors so we don't visit the same successor twice
  SmallPtrSet<BasicBlock *, 8> VisitedSuccs;

  //第一个后继等下直接处理
  VisitedSuccs.insert(*I);
  Pred = BB;
  BB = *I;
  ++I;
	
  //其余的后继既计入RenamePassWorkList中跳回上面原有的do-while循环处理
  for (; I != E; ++I)
    if (VisitedSuccs.insert(*I).second)
      Worklist.emplace_back(*I, Pred, IncomingVals, IncomingLocs);

  goto NextIteration;
}
```

**7、第七步：删除所有的alloca指令**

因为现在所有的load的use均已被替换，alloca变成了死代码

```cpp
// Remove the allocas themselves from the function.
  for (Instruction *A : Allocas) {
    // If there are any uses of the alloca instructions left, they must be in
    // unreachable basic blocks that were not processed by walking the dominator
    // tree. Just delete the users now.
    if (!A->use_empty())
      A->replaceAllUsesWith(UndefValue::get(A->getType()));
    A->eraseFromParent();
  }

  // Remove alloca's dbg.declare instrinsics from the function.
  for (auto &Declares : AllocaDbgDeclares)
    for (auto *DII : Declares)
      DII->eraseFromParent();
```

**8、第八步：优化PHI节点**

这个时候所有多余的store被删掉了，理论上来说满足了SSA的要求，但是PHI节点仍有优化空间：

比如所有分支传过来的incoming value都一样，这个时候PHI节点就没有必要

```cpp
  bool EliminatedAPHI = true;
  while (EliminatedAPHI) {
    EliminatedAPHI = false;

    // Iterating over NewPhiNodes is deterministic, so it is safe to try to
    // simplify and RAUW them as we go.  If it was not, we could add uses to
    // the values we replace with in a non-deterministic order, thus creating
    // non-deterministic def->use chains.
    for (DenseMap<std::pair<unsigned, unsigned>, PHINode *>::iterator
             I = NewPhiNodes.begin(),
             E = NewPhiNodes.end();
         I != E;) {
      PHINode *PN = I->second;

      // If this PHI node merges one value and/or undefs, get the value.
      if (Value *V = SimplifyInstruction(PN, SQ)) {
        PN->replaceAllUsesWith(V);
        PN->eraseFromParent();
        NewPhiNodes.erase(I++);
        EliminatedAPHI = true;
        continue;
      }
      ++I;
    }
  }
```

`SimplifyInstruction`函数在https://github.com/llvm/llvm-project/blob/master/llvm/lib/Analysis/InstructionSimplify.cpp中，逻辑比较复杂，对所有的指令都设置了简化的函数，但是这里只对PHI指令进行优化，故只调用其中的`SimplifyPHINode`函数。函数优化成功则返回值，否则返回null

```cpp
static Value *SimplifyPHINode(PHINode *PN, const SimplifyQuery &Q) {
  // 如果PHI节点的所有incoming value都是同一个值，就删除PHI节点
  Value *CommonValue = nullptr;
  bool HasUndefInput = false;
  for (Value *Incoming : PN->incoming_values()) {
    // If the incoming value is the phi node itself, it can safely be skipped.
    if (Incoming == PN) continue;
    if (isa<UndefValue>(Incoming)) {
      // Remember that we saw an undef value, but otherwise ignore them.
      HasUndefInput = true;
      continue;
    }
    if (CommonValue && Incoming != CommonValue)
      return nullptr;  // Not the same, bail out.
    CommonValue = Incoming;
  }

  // If CommonValue is null then all of the incoming values were either undef or
  // equal to the phi node itself.
  if (!CommonValue)
    return UndefValue::get(PN->getType());

  // If we have a PHI node like phi(X, undef, X), where X is defined by some
  // instruction, we cannot return X as the result of the PHI node unless it
  // dominates the PHI block.
  if (HasUndefInput)
    return valueDominatesPHI(CommonValue, PN, Q.DT) ? CommonValue : nullptr;

  return CommonValue;
}

```

**9、第九步：处理前面并没有被访问到的孤立的基本块**

这些基本块没有前继，但可能有后继，这样会导致后继基本块的PHI节点的incoming values不全

```cpp
// At this point, the renamer has added entries to PHI nodes for all reachable
  // code.  Unfortunately, there may be unreachable blocks which the renamer
  // hasn't traversed.  If this is the case, the PHI nodes may not
  // have incoming values for all predecessors.  Loop over all PHI nodes we have
  // created, inserting undef values if they are missing any incoming values.
  for (DenseMap<std::pair<unsigned, unsigned>, PHINode *>::iterator
           I = NewPhiNodes.begin(),
           E = NewPhiNodes.end();
       I != E; ++I) {
    // 只处理每个基本块的第一个PHI节点
    PHINode *SomePHI = I->second;
    BasicBlock *BB = SomePHI->getParent();
    if (&BB->front() != SomePHI)
      continue;

    // PHI节点的incoming values数量与基本块前继数量相同,不管
    if (SomePHI->getNumIncomingValues() == getNumPreds(BB))
      continue;

    // 此时PHI节点的incoming values数量与基本块前继数量不符，需要添加undef补全所有incoming values
    SmallVector<BasicBlock *, 16> Preds(pred_begin(BB), pred_end(BB));

    // 给基本块的所有前继排个序
    auto CompareBBNumbers = [this](BasicBlock *A, BasicBlock *B) {
      return BBNumbers.find(A)->second < BBNumbers.find(B)->second;
    };
    llvm::sort(Preds, CompareBBNumbers);

    // 把在PHI节点中有incoming values的前继块除掉
    for (unsigned i = 0, e = SomePHI->getNumIncomingValues(); i != e; ++i) {
      // Do a log(n) search of the Preds list for the entry we want.
      SmallVectorImpl<BasicBlock *>::iterator EntIt = llvm::lower_bound(
          Preds, SomePHI->getIncomingBlock(i), CompareBBNumbers);
      assert(EntIt != Preds.end() && *EntIt == SomePHI->getIncomingBlock(i) &&
             "PHI node has entry for a block which is not a predecessor!");

      // Remove the entry
      Preds.erase(EntIt);
    }

    // 将剩下的前继基本块以undef的形式添加进基本块所有的PHI节点中
    unsigned NumBadPreds = SomePHI->getNumIncomingValues();
    BasicBlock::iterator BBI = BB->begin();
    while ((SomePHI = dyn_cast<PHINode>(BBI++)) &&
           SomePHI->getNumIncomingValues() == NumBadPreds) {
      Value *UndefVal = UndefValue::get(SomePHI->getType());
      for (BasicBlock *Pred : Preds)
        SomePHI->addIncoming(UndefVal, Pred);
    }
  }
```

到此整个mem2reg的流程结束

