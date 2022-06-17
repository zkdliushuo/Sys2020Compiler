#include "Function.h"
#include "Argument.h"
#include "Constant.h"
#include "Module.h"
#include "SlotTracker.h"
#include "Types.h"
#include "Value.h"
#include "Instructions.h"
#include "GlobalVariable.h"
#include <iostream>

using namespace YAL;

Function::Function(FunctionType *Ty, std::string &name, Module *ParentModule)
    : Constant(Ty, Value::FunctionVal, nullptr, 0), NumArgs(Ty->getNumParams()) {

  // If the function has arguments, mark them as lazily built.
  if (Ty->getNumParams())
    setValueSubclassData(1); // Set the "has lazy arguments" bit.

  if (ParentModule)
    ParentModule->getFunctionList().push_back(this);

  BlockOrderValid = false;

  setValueName(name);

  auto *FT = getFunctionType();
  if (NumArgs > 0) {
    for (unsigned i = 0, e = NumArgs; i != e; ++i) {
      Type *ArgTy = FT->getParamType(i);
      assert(!ArgTy->isVoidTy() && "Cannot have void typed arguments!");
      Arguments.push_back(new Argument(ArgTy, "", const_cast<Function *>(this), i));
    }
  }
}

void Function::dropAllReferences() {
  for (BasicBlock *BB : BBList)
    BB->dropAllReferences();

  BBList.clear();
}

Function::~Function() {
  dropAllReferences(); // After this it is safe to delete instructions.
  // #ifdef DDD_DEBUG
  // // std::cout << "delete Function" << getName() <<std::endl;
  // #endif

  // Delete all of the method arguments and unlink from symbol table...
  if (!Arguments.empty())
    clearArguments();
}

void Function::clearArguments() {
  for (Argument *A : Arguments) {
    A->setValueName("");
    A->~Argument();
  }
  NumArgs = 0;
  Arguments.clear();
}

unsigned Function::getMaxLabel() const {
  SlotTracker SlotTable(this);
  SlotTable.setFunction(this);
  return SlotTable.getfNext();
}

void Function::setBlockOrder() {
  // if (!isOrderValid()) {
    unsigned i = 0;
    unsigned j = 0;
    auto arg = Arg_begin();
    for (j = 0; j < Arg_size(); j++) {
      (*arg)->FOrder = j;
      arg++;
    }
    for (BasicBlock *BB : getBasicBlockList()) {
      BB->Order = i++;
      BB->LoopDepth = 0;
      for (Instruction *I : BB->getInstList()) {
        I->clearAll();
        if (!isa<BranchInst>(I) && !isa<StoreInst>(I) && !isa<ReturnInst>(I))
          I->FOrder = j++;
      }
      BB->setInstructionOrder();
      BB->use_list.clear();
      BB->def_list.clear();
      BB->IN_list.clear();
      BB->OUT_list.clear();
    }
    setOrderValid(true);
  // }
}

void Function::searchGV() {
  GV.clear();
  CI.clear();
  for (auto BB : getBasicBlockList()) {
    for (auto I : BB->getInstList()) {
      if (auto st = cast<StoreInst>(I)) {
        auto op = st->getNumOperand(1).get();
        if (auto gv = cast<GlobalVariable>(op)) {
          if (!gv->isConstant())
            GV.insert(gv);
        } else if (auto gep = cast<GetElementPtrInst>(op)) {
          if (auto gv = cast<GlobalVariable>(gep->getNumOperand(0).get()))
            GV.insert(gv);
        }
      } else if (auto ci = cast<CallInst>(I)) {
        if (ci->getCalledValue() != this)
          CI.insert(ci);
      }
    }
  }
}

bool Function::hasSideEffect() {
  searchGV();
  if (!Arguments.empty())
    for (auto arg : Arguments) {
      if (arg->getType()->isPointerTy())
        return true;
    }
  if (!CI.empty())
    for (auto ci : CI) {
      if (auto f = cast<Function>(ci->getCalledValue()))
        if (f->hasSideEffect()) return true;
    }
  return !GV.empty();
}

bool Function::hasSideEffect(Value *V) {
  searchGV();
  if (!GV.empty())
    if (auto gv = cast<GlobalVariable>(V))
      return GV.count(gv);
  if (!CI.empty())
    for (auto ci : CI) {
      if (auto f = cast<Function>(ci->getCalledValue()))
        if (f->hasSideEffect(V)) return true;
    }
  return false;
}