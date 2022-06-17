#include "Constants.h"
#include "LLVMContext.h"
#include "User.h"
#include "Use.h"
#include "Type.h"
#include "Types.h"

using namespace YAL;

ConstantInt::ConstantInt(IntegerType *type, int val, unsigned width)
    : Constant(type, Value::ConstantIntVal, nullptr, 0) {
  value = val;
  bitwidth = width;
}

ConstantInt *ConstantInt::get(LLVMContext &Context, int V,
                              unsigned width) {
  // get an existing value or the insertion position
  ConstantInt *result;
  if (width == 32) {
    auto temp = Context.Int32Constants.find(V);
    if (temp == Context.Int32Constants.end()) {
      IntegerType *Ty = Type::getInt32Ty(Context);
      result = new(0) ConstantInt(Ty, V, width);
      Context.Int32Constants.insert(std::pair<int, ConstantInt *>(V, result));
    } else {
      result = temp->second;
    }
  } else {
    if (V == 1)
      result = &Context.Cint1True;
    else
      result = &Context.Cint1False;
  }
  return result;
}

ConstantAggregateZero *ConstantAggregateZero::get(Type *Ty) {
  auto ATy = cast<ArrayType>(Ty);
  // auto Context = Ty->getContext();
  assert(ATy && "Ty should be ArrayType");
  auto temp = ATy->getContext().CAZs.find(ATy->getElementNum());
  ConstantAggregateZero *result;
  if (temp == ATy->getContext().CAZs.end()) {
    result = new(0) ConstantAggregateZero(Ty);
    ATy->getContext().CAZs.insert({ATy->getElementNum(), result});
  } else
    result = temp->second;
  return result;
}

ConstantArray::ConstantArray(ArrayType *T, ArrayRef<Constant *> Val)
    : Constant(T, Value::ConstantArrayVal, op_begin(), Val.size()) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create ConstantArray" << std::endl;
  // #endif
  for (int i = 0; i < Val.size(); i++) {
    getNumOperand(i) = Val[i];
  }
}

Constant *ConstantArray::get(ArrayType *T, ArrayRef<Constant *> V) {
  // std::cout << "-----ConstantArray::get size = " << V.size() << "---" << std::endl;
  assert(T && "Array Type is NUllptr");
  bool isAllZero = true;
  for (auto i = V.begin(); i != V.end(); i++) {
    auto temp = cast<ConstantInt>(*i);
    if (temp->getValue() != 0) {
      isAllZero = false;
      break;
    }
  }
  if (isAllZero)
    return ConstantAggregateZero::get(T);
  else
    return new (V.size()) ConstantArray(T, V);
}

UndefValue* UndefValue::get(Type *Ty){
  auto result = Ty->getContext().UndefValues[Ty];
  if (!result) {
    result = new UndefValue(Ty);
    Ty->getContext().UndefValues.insert(
        std::pair<Type*, UndefValue*>(Ty, result));
  }
  return result;
}

UndefValue *UndefValue::getSequentialElement() const {
  assert(cast<ArrayType>(getType()) && "Not an Array Type");
  return UndefValue::get(Type::getInt32Ty(getContext()));
}

unsigned UndefValue::getNumElements() const {
  Type *Ty = getType();
  assert(cast<ArrayType>(Ty) && "Not an Array Type");
  return cast<ArrayType>(Ty)->getElementNum();
}
