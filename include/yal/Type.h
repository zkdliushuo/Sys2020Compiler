#ifndef YAL_IR_TYPE_H
#define YAL_IR_TYPE_H

// #include "LLVMContext.h"
// #include "Types.h"
#include <iostream>

namespace YAL {

class IntegerType;
class LLVMContext;
class PointerType;

class Type {
public:
  enum TypeID {
    VoidTyID = 0, ///<  0: type with no size
    LabelTyID,    ///<  1: Labels
    IntegerTyID,  ///<  2: Arbitrary bit width integers
    FunctionTyID, ///<  3: Functions
    ArrayTyID,    ///<  4: Arrays
    PointerTyID,  ///<  5: Pointers
  };

private:
  LLVMContext &Context;
  TypeID ID;
  unsigned SubclassData : 24;

protected:
  unsigned ContainedTypesNum = 0;
  Type **ContainedTypes = nullptr;

  unsigned getSubclassData() const { return SubclassData; }
  void setSubclassData(unsigned value) { SubclassData = value; }

public:
  // 构造和析构函数
  Type(LLVMContext &C, TypeID tid) : Context(C), ID(tid), SubclassData(0) {
    // #ifdef DDD_DEBUG
    // std::cout << "Creating Type" << std::endl;
    // #endif
  }
  ~Type() { 
    // #ifdef DDD_DEBUG
    // std::cout << "delete Type" <<std::endl; 
    // #endif
  }

  // 获取类型ID
  TypeID getTypeID() const { return ID; }

  // 判断类型的函数
  bool isVoidTy() const { return getTypeID() == VoidTyID; }

  bool isLabelTy() const { return getTypeID() == LabelTyID; }

  bool isIntegerTy() const { return getTypeID() == IntegerTyID; }
  bool isIntegerTy(unsigned BitWidth) const;

  bool isFunctionTy() const { return getTypeID() == FunctionTyID; }

  bool isArrayTy() const { return getTypeID() == ArrayTyID; }

  bool isPointerTy() const { return getTypeID() == PointerTyID; }

  // 获取context
  LLVMContext &getContext() { 
    // #ifdef DDD_DEBUG
    // std::cout << "Type::getContext()" << std::endl;
    // #endif
    return Context; 
  }

  // 获取类型的函数
  static Type *getVoidTy(LLVMContext &C);
  static Type *getLabelTy(LLVMContext &C);
  static IntegerType *getIntNTy(LLVMContext &C, unsigned N);
  static IntegerType *getInt1Ty(LLVMContext &C);
  static IntegerType *getInt32Ty(LLVMContext &C);
  static PointerType *getInt32PtrTy(LLVMContext &C);

  Type *getPointerElementType() const {
    return ContainedTypes[0];
  }

  // 是否是firstClass
  bool isFirstClassType() const {
    return getTypeID() != FunctionTyID && getTypeID() != VoidTyID;
  }

  virtual void print() const;

  std::string getTypeName();
};
} // namespace YAL

#endif