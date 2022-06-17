#ifndef YAL_IR_TYPES_H
#define YAL_IR_TYPES_H

#include "Type.h"
#include <vector>
#include <iostream>

namespace YAL {

// class Type;

//===--------------------------------------------------------------------===//
// FunctionType: 函数类型
//===--------------------------------------------------------------------===//
class FunctionType : public Type {

public:
  // 构造函数和析构函数
  FunctionType(Type *Result, ArrayRef<Type *> Params, bool IsVarArgs);
  // #ifdef DDD_DEBUG
  ~FunctionType() { }
  // #endif

  // 构建一个函数类型
  // 是否可以被构造函数替代？？
  static FunctionType *get(Type *Result, ArrayRef<Type *> Params,
                           bool isVarArg);

  // 构建没有参数的函数类型
  static FunctionType *get(Type *Result, bool isVarArg);

  // 获取返回值类型
  Type *getReturnType() const { return ContainedTypes[0]; }

  bool isReturnVoid() { return getReturnType()->isVoidTy(); }

  // 获取参数类型，第一个参数的下标从0开始
  Type *getParamType(unsigned i) const { return ContainedTypes[i + 1]; }

  // 获取参数个数
  unsigned getNumParams() const { return ContainedTypesNum - 1; }

  // TODO
  /// 得到这个函数类型是不是可变参的
  bool isVarArg() { return false; }
};

//===--------------------------------------------------------------------===//
// ArrayType: 数组类型
//===--------------------------------------------------------------------===//
class ArrayType : public Type {
private:
  Type *ElementType;
  unsigned ElementNum;

public:
  // 构造函数和析构函数
  ArrayType(Type *ElType, uint64_t NumEl);
  // #ifdef DDD_DEBUG
  ~ArrayType() { }
  // #endif

  // 构建数组类型
  // 是否可以被构造函数替代？？
  static ArrayType *get(Type *ElementType, uint64_t NumElements);

  // 获取元素的数据类型
  Type *getElementType() const { return ElementType; }

  // 获取数组元素个数
  unsigned getElementNum() const { return ElementNum; }
};

//===--------------------------------------------------------------------===//
// PointerType: 指针类型
//===--------------------------------------------------------------------===//
class PointerType : public YAL::Type {
private:
  Type *PointeeType;

public:
  // 构造函数和析构函数
  PointerType(Type *ElType);
  ~PointerType() { 
    // #ifdef DDD_DEBUG
    // std::cout << "delete PointerType" <<std::endl; 
    // #endif
  }

  static PointerType *get(Type *EleTy);

  // 获取元素的数据类型
  Type *getElementType() const { return PointeeType; }
};

//===--------------------------------------------------------------------===//
// IntegerType: 整数类型
//===--------------------------------------------------------------------===//
class IntegerType : public YAL::Type {
public:
  // 构造函数和析构函数
  IntegerType(LLVMContext &C, unsigned NumBits);
  ~IntegerType() { 
    // #ifdef DDD_DEBUG
    // std::cout << "delete IntegerType" <<std::endl; 
    // #endif
  }

  // 获取位宽
  unsigned getBitWidth() const { return getSubclassData(); }

  // virtual void print();
};
} // namespace YAL

#endif