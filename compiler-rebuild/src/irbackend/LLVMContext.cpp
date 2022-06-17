#include "LLVMContext.h"
#include <iostream>

using namespace YAL;

LLVMContext::LLVMContext()
    : VoidTy(*this, Type::VoidTyID), LabelTy(*this, Type::LabelTyID),
      Int1Ty(*this, 1), Int8Ty(*this, 8), Int16Ty(*this, 16),
      Int32Ty(*this, 32), Int64Ty(*this, 64), Int32PTy(&Int32Ty),
      Cint1True(&Int1Ty, 1, 1), Cint1False(&Int1Ty, 0, 1), Ptr_Int32PtrTy(&Int32PTy) {
  // std::cout << "Create LLVMContext" <<std::endl;
}