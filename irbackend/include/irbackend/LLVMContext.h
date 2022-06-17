#ifndef YAL_IR_CONTEXT_H
#define YAL_IR_CONTEXT_H
#include "Type.h"
#include "Constants.h"
#include "Types.h"

#include <list>
#include <map>
#include <utility>
#include <algorithm>
namespace YAL {

class Type;
class IntegerType;
class PointerType;
class ArrayType;
class ConstantInt;
class Module;
class ConstantAggregateZero;

class LLVMContext {
private:
  std::list<Module *> modules;

public:
  Type VoidTy, LabelTy;
  IntegerType Int1Ty, Int8Ty, Int16Ty, Int32Ty, Int64Ty;
  PointerType Int32PTy;
  PointerType Ptr_Int32PtrTy;
  std::map<unsigned, PointerType*> ArrayPtrs;
  std::map<int, ConstantInt *> Int32Constants;
  std::map<uint64_t, ArrayType *> ArrayTypes;
  std::map<Type*, UndefValue*> UndefValues;
  std::map<unsigned, ConstantAggregateZero*> CAZs;
  ConstantInt Cint1True, Cint1False;

public:
  LLVMContext();
  ~LLVMContext() = default;

  void addModule(Module *M) { modules.push_back(M); }
  void removeModule(Module *M) {
    modules.erase(std::find(modules.begin(), modules.end(), M));
  }
};
 // namespace YAL
}
#endif
