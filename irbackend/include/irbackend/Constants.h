#ifndef YAL_IR_CONSTANTS_H
#define YAL_IR_CONSTANTS_H

#include "Constant.h"

namespace YAL {

class Value;
class User;
class IntegerType;
class Function;
class ArrayType;

class ConstantInt : public Constant {
private:
  int value;
  unsigned bitwidth;

public:
  // 构建和析构函数
  ConstantInt(IntegerType *type, int val, unsigned width = 32);
  ~ConstantInt() { 
    // #ifdef DDD_DEBUG
    // // std::cout << "Delete ConstantInt" << std::endl; 
    // #endif
  }

  // 获取某个int型常数
  static ConstantInt *get(LLVMContext &Context, int V, unsigned width = 32);

  // 获取值和位宽
  int getValue() const { return value; }
  unsigned getBitWidth() const { return bitwidth; }

  // 特殊值的判断
  bool isZero() const { return value == 0; }
  bool isOne() const { return value == 1; }
  bool isMinusOne() const { return value == -1; }

  // 获取全1的值
  static ConstantInt *getAllOne(LLVMContext &Context, unsigned width) {
    if (width == 1) 
      return get(Context, 1, 1);
    // else if (width == 32)
    return get(Context, 4294967295, 32);
  }

  static bool classof(Value *V) {
    return V->getValueID() == Value::ConstantIntVal;
  }
};

class ConstantAggregateZero : public Constant {
public:
  explicit ConstantAggregateZero(Type *Ty)
      : Constant(Ty, ConstantAggregateZeroVal, nullptr, 0) {
    // #ifdef DDD_DEBUG
    // // std::cout << "Create ConstantAggregateZero" << std::endl;
    // #endif
  }

  ConstantAggregateZero(const ConstantAggregateZero &) = delete;
  ~ConstantAggregateZero() { 
    // #ifdef DDD_DEBUG
    // // std::cout << "Delete ConstantAggregateZero" << std::endl; 
    // #endif
  }

  // 获取ConstantAggregateZero
  static ConstantAggregateZero *get(Type *Ty);

  static bool classof(Value *V) {
    return V->getValueID() == ConstantAggregateZeroVal;
  }
};

class ConstantArray final : public Constant {
  ConstantArray(ArrayType *T, ArrayRef<Constant *> Val);
  ~ConstantArray() {  }

public:
  // ConstantArray accessors
  static Constant *get(ArrayType *T, ArrayRef<Constant *> V);

public:
  ArrayType *getType() const { return cast<ArrayType>(Value::getType()); }

  static bool classof(const Value *V) {
    return V->getValueID() == Value::ConstantArrayVal;
  }
};

class UndefValue final : public Constant {

  explicit UndefValue(Type *T) : Constant(T, UndefValueVal, nullptr, 0) {}

public:
  UndefValue(const UndefValue &) = delete;

  static UndefValue *get(Type *T);

  UndefValue *getSequentialElement() const;

  unsigned getNumElements() const;

  static bool classof(const Value *V) {
    return V->getValueID() == UndefValueVal;
  }
};

} // namespace YAL
#endif
