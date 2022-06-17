#ifndef YAL_IR_USER_H
#define YAL_IR_USER_H

#include "Use.h"
#include "Value.h"
#include <cassert>
#include <vector>
#include <iostream>

// TODO
/// In order to avoid being assembly LLVM, may need to tranform from using pointers to using STL Vector
namespace YAL {

class Type;

class User : public Value {
private:
  bool HasHungOffUses;

  Use *getHungOffOperands() const {
    return *(reinterpret_cast<Use **>(const_cast<User *>(this)) - 1);
  }

  Use *&getHungOffOperands() { return *(reinterpret_cast<Use **>(this) - 1); }

  void setOperandList(Use *NewList) {
    assert(HasHungOffUses && "Set Operand List cannot be carried out in a non-User class");
    getHungOffOperands() = NewList;
  }

protected:
  /// 只有定长的操作数会被用到
  /// Size 是单个User 的大小
  void *operator new(size_t Size, unsigned Us);
  void *operator new(size_t Size);
  inline static void *AllocUses(size_t Size, unsigned Us);

  User(Type *ty, unsigned vty, Use *, unsigned NumOps) : Value(ty, vty) {
    NumUserOperands = NumOps;
  }

  void growHungoffUses(unsigned N, bool IsPhi = false);

protected:
  /// 使用deleteValue()删除
  /// 原因是需要动态转换以得到最小子类
  ~User() = default;

public:
  User(const User &) = delete;

  // TODO
  /// 对User和Use类回收分配的内存
  void operator delete(void *Usr);

protected:
  Use *getOperandBegin() {
    if(HasHungOffUses){
      return getHungOffOperands();
    }
    return reinterpret_cast<Use *>(const_cast<User *>(this)) - NumUserOperands;
  }

  Use *getOperandBegin() const {
    if(HasHungOffUses){
      return getHungOffOperands();
    }
    return reinterpret_cast<Use *>(const_cast<User *>(this)) - NumUserOperands;
  }

public:
  template <int Idx, typename U> Use &OpFrom(const U *that) const {
    // std::cout << "Idx is "<< Idx <<std::endl;
    return Idx < 0 ? getOperandBegin()[NumUserOperands + Idx] : getOperandBegin()[Idx];
  }

  template <int Idx> Use &Op() { return OpFrom<Idx>(this); }

  template <int Idx> const Use &Op() const { return OpFrom<Idx>(this); }

  Use &getNumOperand(int i) {
    assert(i < (int)NumUserOperands && "getNumOperand index is out of range");
    return i < 0 ? getOperandBegin()[NumUserOperands + i] : getOperandBegin()[i];
  }

  const Use &getNumOperand(int i) const {
    assert(i < (int)NumUserOperands && "getNumOperand index is out of range");
    return i < 0 ? getOperandBegin()[NumUserOperands + i] : getOperandBegin()[i];
  }

public:
  void setNumHungOffUseOperands(unsigned NumOps) {
    assert(HasHungOffUses && "Must have hung off uses to use this method");
    NumUserOperands = NumOps;
  }

  unsigned getNumOperands() const { return NumUserOperands; }

  void allocHungoffUses(unsigned N, bool IsPhi) ;

  /// 对Operand进行遍历的迭代器
  using op_iterator = Use *;
  using const_op_iterator = const Use *;
  using op_range = iterator_range<op_iterator>;
  using const_op_range = iterator_range<const_op_iterator>;

  op_iterator op_begin() { return getOperandBegin(); }
  const_op_iterator op_begin() const { return getOperandBegin(); }
  op_iterator op_end() { return getOperandBegin() + NumUserOperands; }
  const_op_iterator op_end() const { return getOperandBegin() + NumUserOperands; }
  op_range operands() { return op_range(op_begin(), op_end()); }
  const_op_range operands() const {
    return const_op_range(op_begin(), op_end());
  }

  /// 丢掉这个User的所有Use
  void dropAllReferences() {
    for (Use &U : operands())
      U.set(nullptr);
  }
};

} // namespace YAL
#endif
