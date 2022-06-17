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
    // #ifdef DDD_DEBUG
    // std::cout << "before set Value && Use's Val is "<< !!Val <<std::endl;
    // #endif
    set(RHS);
    // std::cout << "set Value successed" <<std::endl;
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
    Next = *List;
    if (Next)
      Next->setPrev(&Next);
    setPrev(List);
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
};
} 
#endif