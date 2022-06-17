#ifndef YAL_IR_MEM2REG_H
#define YAL_IR_MEM2REG_H

#include "BasicBlock.h"
#include "DominatorTree.h"
#include "Function.h"
#include "Instruction.h"
#include "Instructions.h"
#include "Module.h"
#include "Use.h"
#include "User.h"
#include "LLVMContext.h"
#include "Constant.h"
#include "Constants.h"
#include <algorithm>
#include <cassert>
#include <queue>
#include <string>
#include <vector>

namespace YAL {

class MemoryPromoter {

  unsigned NumPromoted = 0;

public:
  MemoryPromoter() {}

  bool MemToReg(Function *F, DominatorTree &DT);
  bool isPromotable(const AllocaInst *AI);
};

class BlockInfo {
  std::map<Instruction *, unsigned> InstNumbers;

public:
  BlockInfo() {}

  bool isfocused(Instruction *I) {
    return (isa<LoadInst>(I) && isa<AllocaInst>(I->getNumOperand(0).get())) ||
           (isa<StoreInst>(I) && isa<AllocaInst>(I->getNumOperand(1).get()));
  }

  void clear() { InstNumbers.clear(); }

  unsigned getIndex(Instruction *I) {
    auto iter = InstNumbers.find(I);
    if (iter != InstNumbers.end())
      return iter->second;
    BasicBlock *BB = I->getParent();
    unsigned InstNo = 0;
    for (Instruction *BBI : *BB) {
      if (isfocused(BBI))
        InstNumbers[BBI] = InstNo++;
    }
    iter = InstNumbers.find(I);
    if (iter != InstNumbers.end())
      return iter->second;
  }

  void deleteValue(Instruction *I) { InstNumbers.erase(I); }
};

struct less_second {
  template <typename T> bool operator()(T &lhs, T &rhs) const { return lhs.second < rhs.second; }
};

struct RenamePassData {
  using ValVector = std::vector<Value *>;

  RenamePassData(BasicBlock *B, BasicBlock *P, ValVector V) : BB(B), Pred(P), Values(std::move(V)) {}
  BasicBlock *BB;
  BasicBlock *Pred;
  ValVector Values;
};

class IDFCalculator {
  DominatorTree &DT;
  std::vector<BasicBlock *> LiveInBlocks;
  std::vector<BasicBlock *> DefBlocks;

public:
  IDFCalculator(DominatorTree &DT, std::vector<BasicBlock *> liveinblocks, std::vector<BasicBlock *> defblocks)
      : DT(DT), LiveInBlocks(liveinblocks), DefBlocks(defblocks) {}
  void calculate(std::vector<BasicBlock *> &PhiBlocks);
};

class PromoteMemToReg {
  std::vector<AllocaInst *> Allocas;
  std::map<AllocaInst *, unsigned> AllocaLookup;
  DominatorTree &DT;

  std::map<BasicBlock *, unsigned> BBNumbers;
  std::map<std::pair<unsigned, unsigned>, PHINode *> NewPhiNodes;
  std::map<PHINode *, unsigned> PhiToAllocaMap;
  std::vector<BasicBlock *> VisitedInRename;

  unsigned NumDeadAlloca = 0;
  unsigned NumSingleStore = 0;
  unsigned NumLocalPromoted = 0;
  unsigned NumPHIInsert = 0;

  struct AllocaInfo {
    std::vector<BasicBlock *> DefBlocks;
    std::vector<BasicBlock *> UseBlocks;

    StoreInst *OnlyStore;
    BasicBlock *OnlyBlock;
    bool OnlyUsedInOneBlock;

    void clear() {
      DefBlocks.clear();
      UseBlocks.clear();
      OnlyStore = nullptr;
      OnlyBlock = nullptr;
      OnlyUsedInOneBlock = true;
    }

    void analyze(AllocaInst *AI);
  };

public:
  PromoteMemToReg(std::vector<AllocaInst *> Allocas, DominatorTree &DT)
      : Allocas(Allocas.begin(), Allocas.end()), DT(DT) {}

  void run();
  bool processSingleStore(AllocaInst *AI, AllocaInfo &Info, DominatorTree &DT);
  bool processSingleBlock(AllocaInst *AI, AllocaInfo &Info, DominatorTree &DT, BlockInfo &BI);
  void calculateLiveInBlocks(AllocaInst *AI, AllocaInfo &Info, std::vector<BasicBlock *> &defblocks,
                             std::vector<BasicBlock *> &liveinblocks);
  bool QueuePhiNode(BasicBlock *BB, unsigned AllocaNo, unsigned &Version);
  void RenamePass(BasicBlock *BB, BasicBlock *Pred, RenamePassData::ValVector &IncomingVals,
                  std::vector<RenamePassData> &Worklist);
  Value *simplifyPhiNode(PHINode *PN, DominatorTree DT);
  bool valueDominatesPhi(Value *V, PHINode *P, DominatorTree DT);
  void removeAlloca(unsigned &AllocaNum);
};

} // namespace YAL

#endif
