#ifndef YAL_IR_ARGUMENT_H
#define YAL_IR_ARGUMENT_H

// #include "Function.h"
#include "Value.h"
#include <string>

namespace YAL {

class Function;
class Type;

class Argument final : public Value {
private:
  Function *Parent;
  unsigned ArgNo;
  friend class Function;
  bool isVar;

public:
  void setParent(Function *parent) { Parent = parent; }

  Argument(Type *Ty, std::string Name, Function *F = nullptr, unsigned ArgNo = 0);

  unsigned getArgNo() const {
    // assert(Parent && "can't get number of unparented arg");
    return ArgNo;
  }

  inline const Function *getParent() const { return Parent; }
  inline Function *getParent() { return Parent; }

  static bool classof(const Value *V) { return V->getValueID() == ArgumentVal; }
};
} // namespace YAL

#endif