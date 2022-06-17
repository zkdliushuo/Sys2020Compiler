#ifndef YAL_IR_USE_H
#define YAL_IR_USE_H

// #include "User.h"
// #include "Value.h"
#include <cassert>
#include <iostream>

namespace YAL {
class User;
class Value;
/*
            .------.  .------.  .------.
            | User*|  | User*|  | User*|
 Value      |------|  |------|  |------|
useList* -->| next*---> next*---> next*---> nullptr
            |------|  |------|  |------|
              use1      use2      use3

        .----------------------------------.
        |    .------.  .------.  .------.  |
 User   |    |      |  |      |  |      |  |
OpList  |    |Value*|  |Value*|  |Value*|  |
Vector  |    .------.  .------.  .------.  |
        .----------------------------------.
*/
class Use {
public:
  Use(const Use &U) = delete;

private:
  ~Use() {
    if (Val)
      removeFromList();
  }

public:
  friend class Value;

  Use(User *Parent) : UserRef(Parent) {}

  operator Value *() const { return Val; }
  Value *get() const { return Val; }

  User *getUser() const { return UserRef; }

  void set(Value *V);

  Value *operator=(Value *RHS) {
    set(RHS);
    return RHS;
  }

  const Use &operator=(const Use &RHS) {
    set(RHS.Val);
    return *this;
  }

  Value *operator->() { return Val; }
  const Value *operator->() const { return Val; }

  Use *getNext() const { return Next; }

  unsigned getOperandNo() const;

  void clear(){
    Val = nullptr;
    Next = nullptr;
    Prev = nullptr;
    UserRef = nullptr;
  }

private:
  Value *Val = nullptr;
  Use *Next = nullptr;
  Use **Prev = nullptr;
  User *UserRef = nullptr;

  void setPrev(Use **prev) { Prev = prev; }

  void addToList(Use **List) {
    // Next = PhiNode uselist   user链表首地址
    Next = *List;
    //  Phinode的user链表首地址的前驱是 &Next  == Loadinst的User链表的首地址的地址 
    if (Next)
      Next->setPrev(&Next);
    // LoadInst的User链表首地址的前驱设置为List  == Phinode的user链表的首地址的地址
    setPrev(List);
    // Phinode的user链表首地址设置为 Loadinst的user链表的首地址
    *List = this;
  }

  void removeFromList() {
    assert(Prev && "Prev is NULLPTR!");
    *Prev = Next;
    if (Next)
      Next->setPrev(Prev);
  }

public:
  static void zap(Use *Start, const Use *Stop, bool del) {
    while (Start != Stop)
      (--Stop)->~Use();
    if (del)
      ::operator delete(Start);
  }

  void remove(){
    removeFromList();
  }
};
} 
#endif