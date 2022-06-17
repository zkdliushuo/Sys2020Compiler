#include "PropConstant.h"
#include "Function.h"
#include "Instructions.h"
#include "IRBuilder.h"
#include "Instruction.h"
#include "Value.h"

using namespace YAL;

void PropConstant::runOnFunction(Module* M){
  for (auto f = M->getFunctionList().begin(); f != M->getFunctionList().end(); ++f) {
    runOnFunction(*(*f));
  }
}

bool PropConstant::runOnFunction(Function &F) {
  bool hasChanged = true;
  while (hasChanged) {
    hasChanged = false;
    for (auto BB : F.getBasicBlockList()) {
      for (auto I : BB->getInstList()) {

        Constant *result;
        bool twoConstant = false;
        if (auto cmp = cast<ICmpInst>(I)) {
          auto op1 = cmp->getNumOperand(0).get();
          auto op2 = cmp->getNumOperand(1).get();
          if (isa<ConstantInt>(op1) && isa<ConstantInt>(op2)) {
            auto cop1 = cast<ConstantInt>(op1);
            auto cop2 = cast<ConstantInt>(op2);
            result = getICmp(cmp->getCmp(), cop1, cop2);
            twoConstant = true;
          }
        }
        else if (auto BO = cast<BinaryOperator>(I)) {
          auto op1 = BO->getNumOperand(0).get();
          auto op2 = BO->getNumOperand(1).get();
          if (isa<ConstantInt>(op1) && isa<ConstantInt>(op2)) {
            auto cop1 = cast<ConstantInt>(op1);
            auto cop2 = cast<ConstantInt>(op2);
            twoConstant = true;
            switch (BO->getOpcode())
            {
            case Instruction::Add: result = getAdd(cop1, cop2); break;
            case Instruction::Sub: result = getSub(cop1, cop2); break;
            case Instruction::Mul: result = getMul(cop1, cop2); break;
            case Instruction::SDiv: result = getSDiv(cop1, cop2); break;
            case Instruction::SRem: result = getSRem(cop1, cop2); break;
            case Instruction::Or: result = getOr(cop1, cop2); break;
            case Instruction::And: result = getAdd(cop1, cop2); break;
            default: twoConstant = false; break;
            }
          }
        }

        if (twoConstant) {
          while (!I->user_empty()) {
            auto u = I->user_begin();
            if (u == I->user_end()) break;
            u.getUse() = result;
            hasChanged = true;
          }
          // I->eraseFromParent();
        }

      }
    }
  }
  return true;
}