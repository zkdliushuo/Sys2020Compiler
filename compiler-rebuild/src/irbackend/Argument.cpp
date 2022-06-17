#include "Argument.h"
#include "Value.h"

using namespace YAL;

Argument::Argument(Type *Ty, std::string Name, Function *Par, unsigned ArgNo)
    : Value(Ty, Value::ArgumentVal), Parent(Par), ArgNo(ArgNo) {
  setValueName(Name);
}