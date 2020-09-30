#ifndef PROPCONSTANT_H
#define PROPCONSTANT_H

#include "Pass.h"
#include "Constant.h"
#include "Constants.h"

namespace YAL {

class Function;
class IRBuilder;

class PropConstant {
  enum { EQ = 0, NE, GT, GE, LT, LE };
public:

  bool runOnFunction(Function &F);
  void runOnFunction(Module* M);

  static ConstantInt *getAdd(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() + C2->getValue(), 32);
  }

  static ConstantInt *getSub(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() - C2->getValue(), 32);
  }

  static ConstantInt *getMul(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() * C2->getValue(), 32);
  }

  static ConstantInt *getSDiv(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() / C2->getValue(), 32);
  }

  static ConstantInt *getAnd(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() && C2->getValue(), 1);
  }

  static ConstantInt *getOr(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() || C2->getValue(), 1);
  }

  static ConstantInt *getSRem(ConstantInt *C1, ConstantInt *C2) {
    return ConstantInt::get(C1->getContext(), C1->getValue() % C2->getValue(), 32);
  }

  static ConstantInt *getNeg(ConstantInt *C1) { return ConstantInt::get(C1->getContext(), -(C1->getValue()), 32); }

  static ConstantInt *getNot(ConstantInt *C1) {
    return ConstantInt::get(C1->getContext(), ~(C1->getValue()), C1->getBitWidth());
  }

  static ConstantInt *getICmp(unsigned short pred, ConstantInt *LHS, ConstantInt *RHS) {
    int value;
    switch (pred) {
    case EQ: {
      value = LHS->getValue() == RHS->getValue();
      break;
    }
    case NE: {
      value = LHS->getValue() != RHS->getValue();
      break;
    }
    case GE: {
      value = LHS->getValue() >= RHS->getValue();
      break;
    }
    case GT: {
      value = LHS->getValue() > RHS->getValue();
      break;
    }
    case LE: {
      value = LHS->getValue() <= RHS->getValue();
      break;
    }
    case LT: {
      value = LHS->getValue() < RHS->getValue();
      break;
    }
    default:
      break;
    }
    return ConstantInt::get(LHS->getContext(), value, 1);
  }
};

}

#endif