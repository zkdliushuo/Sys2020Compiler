#ifndef YAL_IR_VALUE_H
#define YAL_IR_VALUE_H

// #include "Type.h"
#include "support.h"
#include "Use.h"
#include <iterator>
#include <memory>
#include <string>
#include <map>
#include <list>
#include <set>

namespace YAL {
class User;
class Use;
class Module;
class BasicBlock;
class Instruction;
class LLVMContext;
class Type;

class Value {
  Type *VTy;
  Use *UseList;

  /// subclassID 只是用来判断是否可以cast
  const unsigned char SubclassID;

protected:
  /// 用来存放优化信息
  unsigned char SubclassOptionalData : 7;

private:
  /// 存放子类可能用到的信息
  unsigned short SubclassData;

public:
  int Color;
  int size;
  unsigned idx = 0;
  unsigned FOrder = 0;
  unsigned LoopDepth = 0;
  std::list<Value *> adjs;

  struct VarInfo {
    std::set<BasicBlock*> AliveBlocks;
    std::map<unsigned, unsigned> killer;
    std::map<unsigned, unsigned> start;
  };

  VarInfo info;

protected:
  /// 存放使用者User的个数
  unsigned NumUserOperands;

  /// 是否有名字
  bool HasName;
  std::string ValueName;

private:
  /// UseT == 'Use' or 'const Use'
  template <typename UseT>
  class use_iterator_impl
      : public std::iterator<std::forward_iterator_tag, UseT *> {
    friend class Value;

    UseT *U;

    explicit use_iterator_impl(UseT *u) : U(u) {}

  public:
    use_iterator_impl() : U() {}

    bool operator==(const use_iterator_impl &x) const { return U == x.U; }
    bool operator!=(const use_iterator_impl &x) const { return !operator==(x); }

    use_iterator_impl &operator++() { // Preincrement
      assert(U && "Cannot increment end iterator!");
      U = U->getNext();
      return *this;
    }

    use_iterator_impl operator++(int) { // Postincrement
      auto tmp = *this;
      ++*this;
      return tmp;
    }

    UseT &operator*() const {
      assert(U && "Cannot dereference end iterator!");
      return *U;
    }

    UseT *operator->() const { return &operator*(); }

    operator use_iterator_impl<const UseT>() const {
      return use_iterator_impl<const UseT>(U);
    }
  };

  /// UserTy == 'User' or 'const User'
  template <typename UserTy>
  class user_iterator_impl
      : public std::iterator<std::forward_iterator_tag, UserTy *> {
    use_iterator_impl<Use> UI;
    explicit user_iterator_impl(Use *U) : UI(U) {}
    friend class Value;

  public:
    user_iterator_impl() = default;

    bool operator==(const user_iterator_impl &x) const { return UI == x.UI; }
    bool operator!=(const user_iterator_impl &x) const {
      return !operator==(x);
    }

    /// Returns true if this iterator is equal to user_end() on the value.
    bool atEnd() const { return *this == user_iterator_impl(); }

    user_iterator_impl &operator++() { // Preincrement
      ++UI;
      return *this;
    }

    user_iterator_impl operator++(int) { // Postincrement
      auto tmp = *this;
      ++*this;
      return tmp;
    }

    // 从Use得到User
    UserTy *operator*() const { return UI->getUser(); }

    UserTy *operator->() const { return operator*(); }

    operator user_iterator_impl<const UserTy>() const {
      return user_iterator_impl<const UserTy>(*UI);
    }

    Use &getUse() const { return *UI; }
  };

protected:
  Value(Type *Ty, unsigned scid);

  /// 用deleteValue()
  ~Value();

public:
  bool isVar();

  std::string getReg() {
    switch (Color)
    {
    case 0: return "r4";
    case 1: return "r5";
    case 2: return "r6";
    case 3: return "r7";
    case 4: return "r8";
    case 5: return "r9";
    case 6: return "r10";
    case 7: return "r11";
    case 8: return "r12";
    case 9: return "r0";
    case 10: return "r1";
    case 11: return "r2";
    case 12: return "r3";
    default: return "error reg";
    }
  }

  // 添加活跃块
  void addAiveBlock(BasicBlock *BB) {
    info.AliveBlocks.insert(BB);
  }

  // 设置killer
  void setKiller(Instruction *I);

  void setKiller(BasicBlock *BB);

  // 设置start
  void setStart(BasicBlock *BB, unsigned i);

  // 获取VarInfo
  VarInfo getVarInfo() { return info; }

  Value &operator=(const Value &) = delete;

  /// 使用这个删除泛型的Value
  void deleteValue();

  /// 执行打印功能 raw_ostream
  /// 实现在asmwriter里面
  virtual void print()const;

  /// 返回Type指针
  Type *getType() const { return VTy; }

  /// 从Type得到这个Context
  LLVMContext &getContext() const;

  /// 是否有名字，没有名字将使用插槽打印
  bool hasName() const { return HasName; }

  /// 得到名字
  std::string getName() const { return ValueName; }

  /// 设置名字
  void setValueName(std::string VN);

  ///
  bool use_empty() const { return UseList == nullptr; }

  /// 设置use迭代器
  using use_iterator = use_iterator_impl<Use>;
  using const_use_iterator = use_iterator_impl<const Use>;

  use_iterator use_begin() { return use_iterator(UseList); }
  const_use_iterator use_begin() const { return const_use_iterator(UseList); }

  use_iterator use_end() { return use_iterator(); }
  const_use_iterator use_end() const { return const_use_iterator(); }

  iterator_range<use_iterator> uses() {
    return make_range(use_begin(), use_end());
  }
  iterator_range<const_use_iterator> uses() const {
    return make_range(use_begin(), use_end());
  }

  bool user_empty() const { return UseList == nullptr; }

  /// 设置user迭代器
  using user_iterator = user_iterator_impl<User>;
  using const_user_iterator = user_iterator_impl<const User>;

  user_iterator user_begin() { return user_iterator(UseList); }
  const_user_iterator user_begin() const {
    return const_user_iterator(UseList);
  }

  user_iterator user_end() { return user_iterator(); }
  const_user_iterator user_end() const { return const_user_iterator(); }

  User *user_back() { return *user_begin(); }
  const User *user_back() const { return *user_begin(); }

  iterator_range<user_iterator> users() {
    return make_range(user_begin(), user_end());
  }
  iterator_range<const_user_iterator> users() const {
    return make_range(user_begin(), user_end());
  }

  /// 设置子类ID的宏定义
  enum ValueTy {
    /// Name -> NameVal 如：Instruction -> InstructionVal
    FunctionVal,
    GlobalVariableVal,
    ConstantArrayVal,
    UndefValueVal,
    ConstantAggregateZeroVal,
    ConstantDataArrayVal,
    ConstantIntVal,
    ArgumentVal,
    BasicBlockVal,
    InstructionVal
  };

  /// 是否在某个block里面
  bool isUsedInBasicBlock(BasicBlock *BB);

  /// 计算这个Value有多少个Users
  unsigned getNumUses() const {
    return (unsigned)std::distance(use_begin(), use_end());
  }

  /// This method should only be used by the Use class.
  void addUse(Use &U);

  /// 返回类的ID
  unsigned getValueID() const { return SubclassID; }

  /// 返回子类可能需要的优化信息
  unsigned getRawSubclassOptionalData() const { return SubclassOptionalData; }

  /// 清除已经保存的优化的信息
  void clearSubclassOptionalData() { SubclassOptionalData = 0; }

  void replaceAllUsesWith(Value *V);

protected:
  unsigned short getSubclassDataFromValue() const { return SubclassData; }
  void setValueSubclassData(unsigned short D) { SubclassData = D; }
};
} // namespace YAL

#endif