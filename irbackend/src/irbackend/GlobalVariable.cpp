#include "GlobalVariable.h"
#include "Types.h"
#include "Type.h"
using namespace YAL;

GlobalVariable::GlobalVariable(Module &M, Type *Ty, bool constant, Constant *InitVal,
                    std::string name)
  : Constant(PointerType::get(Ty), Value::ConstantIntVal, nullptr, InitVal != nullptr),
    isConstantGlobal(constant), ValueType(Ty) {
    if (InitVal) {
      // assert(InitVal->getType() == Ty &&
      //       "Initializer should be the same type as the GlobalVariable!");
      Op<0>() = InitVal;
    }
    M.getGlobalList().push_back(this);
    setValueName(name);
}