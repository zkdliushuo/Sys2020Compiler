#include "SimplifySpill.h"
#include "BasicBlock.h"
#include "Function.h"
#include "Instructions.h"

using namespace YAL;

void SimplifySpill::run() {
  for (auto BB : F.getBasicBlockList()) {
    for (auto I : BB->getInstList()) {
      if (I->isSpilled && !isa<LoadInst>(I)) {
        auto AI = I->SpilledAI;
        assert(AI && "SpilledAI is nullptr");
        auto ST = cast<StoreInst>(AI->getNextNonDebugInstruction());
        assert (ST && "ST is nullptr");
        auto LD = cast<LoadInst>(ST->getNextNonDebugInstruction());
        if (LD) {
          if (LD->Color == I->Color && LD->getNumOperand(0) == AI && LD->getNumUses() == 1) {
            auto U = LD->user_begin();
            LD->eraseFromParent();
            U.getUse() = I;
            if (AI->getNumUses() == 1) {
              AI->eraseFromParent();
              ST->eraseFromParent();
            }
          }
        }
      }
    }
  }
}