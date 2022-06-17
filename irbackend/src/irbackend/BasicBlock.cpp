#include "BasicBlock.h"
#include "Function.h"
#include "Instruction.h"
#include "Instructions.h"
#include "support.h"
#include <iostream>
#include <utility>

using namespace YAL;

BasicBlock::BasicBlock(LLVMContext &C, std::string &Name, Function *NewParent)
    : Value(Type::getLabelTy(C), Value::BasicBlockVal), Parent(NewParent) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create BasicBlock" <<std::endl;
  // #endif
  if (NewParent)
    insertInto(NewParent);
  setValueName(Name);
}

void BasicBlock::insertInto(Function *NewParent) { NewParent->getBasicBlockList().push_back(this); }

Instruction *BasicBlock::getTerminator() {
  if (InstList.empty() || !InstList.back()->isTerminator())
    return nullptr;
  else
    return InstList.back();
}

std::list<BasicBlock *> BasicBlock::getNextBlocks() {
  Instruction *I = getTerminator();
  std::list<BasicBlock *> BL;
  BL.clear();
  if (I) {
    if (auto *BI = cast<BranchInst>(I)) {
      if (BI->isConditional()) {
        BL.push_back(BI->getSuccessor(0));
        BL.push_back(BI->getSuccessor(1));
      } else {
        BL.push_back(BI->getSuccessor(0));
      }
    }
  }
  return BL;
}

void BasicBlock::dropAllReferences() {
  for (Instruction *I : InstList)
    I->dropAllReferences();
}

void BasicBlock::removeFormParent() {
  for (auto i = PredList.begin(); i != PredList.end(); i++)
    (*i)->deleteSucc(this);
  getParent()->getBasicBlockList().remove(this);
}

void BasicBlock::setInstructionOrder() {
  if (!isOrderValid()) {
    unsigned i = 0;
    for (Instruction *I : getInstList()) {
      I->Order = i++;
    }
    setOrderValid(true);
  }
}

void BasicBlock::init_usedef() {
  IN_list.clear();
  OUT_list.clear();
  if (Order == 0) {
    auto F = getParent();
    auto arg = F->Arg_begin();
    for (int i = 0; i < F->Arg_size(); i++) {
      IN_list.insert({i, (*arg)});
      arg++;
    }
  }
  // std::cout << "Analyze BB: " << getName() << std::endl;
  for (Instruction *I : InstList) {
    if (!isa<BranchInst>(I) && !isa<StoreInst>(I) && 
        !isa<ReturnInst>(I) && !isa<AllocaInst>(I) && !isa<GetElementPtrInst>(I)) {
      def_list.insert({I->FOrder, I});
      // std::cout << "Push " << I->FOrder << " to def_list" << std::endl;
    }
    if (!isa<PHINode>(I))
      for (int i = 0; i < I->getNumOperands(); i++) {
        Value *V = I->getNumOperand(i).get();
        if (V->isVar() && !isa<AllocaInst>(V) && !isa<GetElementPtrInst>(V)) {
          if (!def_list.count(V->FOrder)) {
            use_list.insert({V->FOrder, V});
            // std::cout << "Push " << I->FOrder << " to use_list" << std::endl;
          }
        // }
        // if (Instruction *UI = cast<Instruction>(V)) {
          V->setKiller(I);
          V->addAiveBlock(this);
        }
      }
  }
}