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
  InstrOrderValid = false;
  if (NewParent != nullptr)
    insertInto(NewParent);
  setValueName(Name);
}

BasicBlock *BasicBlock::Create(LLVMContext &Context, std::string Name ,
                            Function *Parent, BasicBlock *InsertBefore) {
  BasicBlock *new_BB = new BasicBlock(Context, Name, nullptr);
  new_BB->setParent(Parent);
  if (InsertBefore) {
    // assert(Parent && "this basicblock dosen't have a parent");
    assert(InsertBefore && "InsertBefore is null");
    assert(InsertBefore->getParent() && "InsertBefore's parent is null");
    auto temp = std::find(Parent->getBasicBlockList().begin(), Parent->getBasicBlockList().end(), InsertBefore);
    assert(temp != Parent->getBasicBlockList().end() && "Can't find InsertBefore");
    Parent->getBasicBlockList().insert(temp, new_BB);
  }
  return new_BB;
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
  auto temp = std::find(getParent()->BB_begin(), getParent()->BB_end(), this);
  assert(temp != getParent()->BB_end() && "can't find this BB");
  getParent()->getBasicBlockList().erase(temp);
}

void BasicBlock::setInstructionOrder() {
  // std::cout << ">> BB: " << getName() << std::endl;
  // if (!isOrderValid()) {
    unsigned i = 0;
    for (Instruction *I : getInstList()) {
      I->Order = i++;
      // std::cout << "*** I: " << I->FOrder << " Order: " << I->Order << " OpcodeName: " << I->getOpcodeName() << std::endl;
    }
    setOrderValid(true);
  // }
}

void BasicBlock::init_def() {
  IN_list.clear();
  OUT_list.clear();
  if (Order == 0) {
    auto F = getParent();
    auto arg = F->Arg_begin();
    for (int i = 0; i < F->Arg_size() && i < 4; i++) {
      IN_list.insert({i, (*arg)});
      arg++;
    }
  }

  for (Instruction *I : InstList) {
    if (I->hasRegAllocated()) {
      // if (auto phi = cast<PHINode>(I)) {
      //   for (int i = 0; i < phi->getNumOperands(); i++) {
      //     auto bb = phi->getIncomingBlock(i);
      //     bb->def_list.insert({phi->FOrder, phi});
      //   }
      // }
      // else 
        def_list.insert({I->FOrder, I});
    }
  }
}

void BasicBlock::init_use() {
  for (Instruction *I : InstList) {
    if (auto phi = cast<PHINode>(I)) {
      for (int i = 0; i < phi->getNumOperands(); i++) {
        auto op = phi->getIncomingValue(i);
        auto bb = phi->getIncomingBlock(i);
        bb->Phi_use.insert({phi, op});
        if (op->hasRegAllocated()) {
          if (!bb->def_list.count(op->FOrder))
            bb->use_list.insert({op->FOrder, op});
        
          auto beforeTerminator = bb->getTerminator();
          op->addAiveBlock(bb);
          op->setKiller(beforeTerminator);
        }
      }
    }

    else {
      for (int i = 0; i < I->getNumOperands(); i++) {
        Value *V = I->getNumOperand(i).get();
        if (V->hasRegAllocated()) {
          if (!def_list.count(V->FOrder))
            use_list.insert({V->FOrder, V});
          V->setKiller(I);
          V->addAiveBlock(this);
        }
      }
    }

  }
}

void BasicBlock::init_usedef() {
  IN_list.clear();
  OUT_list.clear();
  if (Order == 0) {
    auto F = getParent();
    auto arg = F->Arg_begin();
    // std::cout << " >> entry BB: " << getName() << std::endl;
    for (int i = 0; i < F->Arg_size() && i < 4; i++) {
      IN_list.insert({i, (*arg)});
      arg++;
    }
  }
  for (Instruction *I : InstList) {
    if (!isa<BranchInst>(I) && !isa<StoreInst>(I) && !isa<ReturnInst>(I) && !isa<AllocaInst>(I) && !isa<ICmpInst>(I)) {
      if (auto CI = cast<CallInst>(I)) {
        auto Fty = CI->getFunctionType();
        if (!Fty->getReturnType()->isVoidTy()) {
          def_list.insert({I->FOrder, I});
        }
      } else
        def_list.insert({I->FOrder, I});
    }
    if (auto phi = cast<PHINode>(I)) {
      for (int i = 0; i < phi->getNumOperands(); i++) {
        auto op = phi->getIncomingValue(i);
        auto bb = phi->getIncomingBlock(i);
        bb->Phi_use.insert({phi, op});
        if (op->isVar() && !isa<AllocaInst>(op)) {
          bb->use_list.insert({op->FOrder, op});
        }

        auto beforeTerminator = bb->getTerminator();
        op->addAiveBlock(bb);
        op->setKiller(beforeTerminator);
      }
    } 
    
    else {
      for (int i = 0; i < I->getNumOperands(); i++) {
        Value *V = I->getNumOperand(i).get();
        if (V->isVar() && !isa<AllocaInst>(V)) {
          if (!def_list.count(V->FOrder))
            use_list.insert({V->FOrder, V});
          V->setKiller(I);
          V->addAiveBlock(this);
        }
      }
    }
  }

}