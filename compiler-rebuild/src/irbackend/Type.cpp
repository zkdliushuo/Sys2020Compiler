#include "Type.h"
#include "LLVMContext.h"
#include "Types.h"
#include "support.h"
#include <stdlib.h>
#include <iostream>
#define DDD_DEBUG
using namespace YAL;

Type *Type::getVoidTy(LLVMContext &C) { return &C.VoidTy; }
Type *Type::getLabelTy(LLVMContext &C) { return &C.LabelTy; }
IntegerType *Type::getInt1Ty(LLVMContext &C) { 
  return &C.Int1Ty; 
}
IntegerType *Type::getInt32Ty(LLVMContext &C) { return &C.Int32Ty; }
IntegerType *Type::getIntNTy(LLVMContext &C, unsigned N) {
  switch (N) {
  case 1:
    return &C.Int1Ty;
  case 8:
    return &C.Int8Ty;
  case 16:
    return &C.Int16Ty;
  case 32:
    return &C.Int32Ty;
  case 64:
    return &C.Int64Ty;
  default:
    return &C.Int32Ty;
  }
}

PointerType *Type::getInt32PtrTy(LLVMContext &C) { return &C.Int32PTy; }

bool Type::isIntegerTy(unsigned Bitwidth) const {
  auto temp = cast<IntegerType>(this);
  return isIntegerTy() && temp->getBitWidth() == Bitwidth;
}

std::string Type::getTypeName() {
  std::string TypeName = "";
  switch (getTypeID()) {
    case VoidTyID:  {   return "void";}
    case LabelTyID:  {   return "label"; }
    case IntegerTyID:{
        auto casted_Ty = cast<IntegerType>(this);
        assert(casted_Ty && "Ty is not IntegerType");
        return "i" + std::to_string(casted_Ty->getBitWidth());
    }
    case FunctionTyID: {
        FunctionType* FTy = cast<FunctionType>(this);
        TypeName += FTy->getReturnType()->getTypeName();
        TypeName += " (";
        int number = FTy->getNumParams();
        for (int i = 0; i < number; i++) {
            if (i)
                TypeName += ", ";
            TypeName += FTy->getParamType(i)->getTypeName();
        }
        if (FTy->isVarArg()) {
            if (FTy->getNumParams()) TypeName += ", ";
            TypeName += "...";
        }
        TypeName += " )";
        return TypeName;
    }
    case PointerTyID: {
        PointerType* PTy = cast<PointerType>(this);
        TypeName += PTy->getElementType()->getTypeName();
        TypeName += '*';
        return TypeName;
    }
    case ArrayTyID: {
        ArrayType *ATy = cast<ArrayType>(this);
        TypeName += ("[" + std::to_string(ATy->getElementNum()) + " x ");
        // std::cout << '[' << ATy->getElementNum() << " x " << std::endl;
        TypeName += ATy->getElementType()->getTypeName();
        TypeName += ']';
        // std::cout << ']' << std::endl;
        return TypeName;
    }
    default:
        return "Non-Type";
  }
}


FunctionType::FunctionType(Type *Result, ArrayRef<Type *> Params,
                           bool IsVarArgs)
    : Type(Result->getContext(), FunctionTyID) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create FunctionType" <<std::endl;
  // #endif
  ContainedTypes = (Type**)malloc(sizeof(Type*) * (Params.size() + 1));
  // Type **SubTys = reinterpret_cast<Type **>(this + 1);
  setSubclassData(IsVarArgs);
  ContainedTypes[0] = Result;
  for (int i = 0; i < Params.size(); i++) {
    assert(Params[i]->isFirstClassType() &&
           "Not a valid type for function argument!");
    ContainedTypes[i + 1] = Params[i];
  }
  // ContainedTypes = SubTys;
  ContainedTypesNum = Params.size() + 1;
}

FunctionType *FunctionType::get(Type *Result, ArrayRef<Type *> Params,
                           bool isVarArg) {
  return new FunctionType(Result, Params, isVarArg);
}

FunctionType *FunctionType::get(Type *Result, bool isVarArg) {
  ArrayRef<Type *> nullList;
  nullList.clear();
  return new FunctionType(Result, nullList, isVarArg);
}

ArrayType::ArrayType(Type *ElType, uint64_t NumEl)
    : Type(ElType->getContext(), ArrayTyID), ElementNum(NumEl),
      ElementType(ElType) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create ArrayType" <<std::endl;
  // #endif
  ContainedTypes = &ElementType;
  ContainedTypesNum = 1;
}

ArrayType *ArrayType::get(Type *ElementType, uint64_t NumElements) {
  ArrayType *result = ElementType->getContext().ArrayTypes[NumElements];
  if (!result) {
    result = new ArrayType(ElementType, NumElements);
    ElementType->getContext().ArrayTypes.insert(
        std::pair<uint64_t, ArrayType *>(NumElements, result));
  }
  return result;
}

PointerType::PointerType(Type *ElType)
    : Type(ElType->getContext(), PointerTyID), PointeeType(ElType) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create PointerType" <<std::endl;
  // #endif
  ContainedTypes = &PointeeType;
  ContainedTypesNum = 1;
}

PointerType *PointerType::get(Type *EleTy) {
  if (isa<IntegerType>(EleTy))
    return &EleTy->getContext().Int32PTy;
  else if (auto *AT = cast<ArrayType>(EleTy)) {
    PointerType *result;
    unsigned length = AT->getElementNum();
    auto temp = EleTy->getContext().ArrayPtrs.find(length);
    if (temp == EleTy->getContext().ArrayPtrs.end()) {
      result = new PointerType(AT);
      EleTy->getContext().ArrayPtrs.insert(std::pair<unsigned, PointerType *>(length, result));
    } else {
      result = temp->second;
    }
    return result;
  } else if (auto *PT = cast<PointerType>(EleTy)) {
    // std::cout << "\\\\\\\\\\\\\\\\PointerType::get PointerType\\\\\\\\\\\\\\\\\\\\" << std::endl;
    return &EleTy->getContext().Ptr_Int32PtrTy;
  }
  return &EleTy->getContext().Int32PTy;
}

IntegerType::IntegerType(LLVMContext &C, unsigned NumBits) : Type(C, IntegerTyID) {
  // #ifdef DDD_DEBUG
  // std::cout << "Create IntegerType" <<std::endl;
  // #endif
  setSubclassData(NumBits);
}