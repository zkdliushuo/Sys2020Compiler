#ifndef YAL_IR_GLOBALVARIABLE_H
#define YAL_IR_GLOBALVARIABLE_H

#include "Constant.h"
#include "Module.h"
#include <string>
/// 此文件用来定义全局变量

namespace YAL {

class Constant;
class User;

/// 实现GlobalVariable的继承关系，最好Function和GlobalVariable共同继承于
/// 一个Constant的子类，因为对于这俩个有一些共同的处理
/// (Mudole里面把这俩个存放在了一个list里面)
class GlobalVariable : public Constant {
private:
  // Is this a constant global
  bool isConstantGlobal : 1;
  // bool hasInitializer : 1; // TODO: to be done
  Type *ValueType;

public:
  GlobalVariable(Type *ty, bool isconstant, unsigned vty, Use *Ops,
                 unsigned NumOps, bool isExternallyInitialized = false)
      : Constant(ty, vty, Ops, NumOps) {
    isConstantGlobal = isconstant;
  }

  GlobalVariable(Module &M, Type *Ty, bool constant, Constant *InitVal,
                 std::string name = "");

  // Drop all the references
  ~GlobalVariable() { User::dropAllReferences(); }

  void operator=(const GlobalVariable &) = delete;
  GlobalVariable(const GlobalVariable &) = delete;

  // Space allocator
  void *operator new(size_t s) { return User::operator new(s, 1); }

  void operator delete(void *ptr) {
    assert(ptr != nullptr && "must not be nullptr");
    User *Obj = static_cast<User *>(ptr);
    // TODO :
    // Check if setGlobalVariableNumOperands(1) is necessary
    // Number of operands can be set to 0 after construction and initialization.
    // Make sure that number of operands is reset to 1, as this is needed in
    // User::operator delete Obj->setGlobalVariableNumOperands(1);
    User::operator delete(Obj);
  }

  Type *getValueType() const { return ValueType; }

  inline bool hasInitializer() const {
    // Original LLVM use isDeclaration() in Global.cpp:231
    // I made some override here.
    return this->getNumOperands() != 0;
  }

  // getInitializer - Return the initializer for this global variable.
  inline const Constant *getInitializer() const {
    assert(hasInitializer() && "GV doesn't have initializer!");
    return static_cast<Constant *>(Op<0>().get());
  }
  inline Constant *getInitializer() {
    assert(hasInitializer() && "GV doesn't have initializer!");
    return static_cast<Constant *>(Op<0>().get());
  }

  bool isConstant() const { return isConstantGlobal; }
  void setConstant(bool Val) { isConstantGlobal = Val; }
};

} // namespace YAL
#endif // !YAL_IR_GLOBALVARIABLE_H