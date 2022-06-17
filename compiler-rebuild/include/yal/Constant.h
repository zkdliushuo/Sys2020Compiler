#ifndef YAL_IR_CONSTANT_H
#define YAL_IR_CONSTANT_H
#include "Type.h"
#include "User.h"
#include "Value.h"

/// 此文件用来定义常量，它的继承关系图参见https://llvm.org/doxygen/classllvm_1_1Constant.html
// TODO: 完善该文件，需要考虑到Function类和GlobalVariable类是该类的子类

namespace YAL {

class User;

class Constant : public User {
private:
  /* data */
protected:
  Constant(Type *ty, unsigned vty, Use *Ops, unsigned NumOps)
      : User(ty, vty, Ops, NumOps) {
    // std::cout << "Create Constant" << std::endl;
  }
  ~Constant() { 
    // std::cout << "Delete Constant" << std::endl; 
  }

public:
  void operator=(const Constant &) = delete;
  Constant(const Constant &) = delete;
};

} // namespace YAL
#endif