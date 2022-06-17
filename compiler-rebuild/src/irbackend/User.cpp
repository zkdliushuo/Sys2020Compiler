#include "User.h"
#include <iostream>

using namespace YAL;

void User::allocHungoffUses(unsigned N, bool IsPhi) {
  assert(HasHungOffUses && "Should use parameterless operator new");
  uint8_t *Storage;
  if(IsPhi){
    Storage = static_cast<uint8_t *>(::operator new((sizeof(Use) + sizeof(BasicBlock *) )* N));
  }
  else{
    Storage = static_cast<uint8_t *>(::operator new(sizeof(Use)* N));
  }
  Use *Start = reinterpret_cast<Use *>(Storage);
  Use *End = Start + N;
  setOperandList(Start);
  for (; Start != End; Start++)
    new (Start) Use(this);
}

void *User::AllocUses(size_t Size, unsigned Us) {

  uint8_t *Storage =
      static_cast<uint8_t *>(::operator new(Size + sizeof(Use) * Us));
  Use *Start = reinterpret_cast<Use *>(Storage);
  Use *End = Start + Us;
  User *Obj = reinterpret_cast<User *>(End);
  Obj->NumUserOperands = Us;
  Obj->HasHungOffUses = false;
  for(unsigned i=0;i<Us;i++){
    auto temp = reinterpret_cast<Use *>(Start + i);
    new (temp) Use(Obj);
  }
  return Obj;
}

void *User::operator new(size_t Size, unsigned Us) {
  return AllocUses(Size, Us);
}

/// Just for PhiNode Construction
void *User::operator new(size_t Size) { 
  void *Storage = ::operator new(Size + sizeof(Use *));
  Use **HungOffOperandList = static_cast<Use **>(Storage);
  User *Obj = reinterpret_cast<User *>(HungOffOperandList + 1);
  Obj->NumUserOperands = 0;
  Obj->HasHungOffUses = true;
  *HungOffOperandList = nullptr;
  return Obj;
}

void User::operator delete(void *Usr) {
  User *Obj = static_cast<User *>(Usr);
  Use *Storage = Obj->op_begin();
  Use::zap(Storage, Storage + Obj->NumUserOperands, false);
  ::operator delete(Storage);
}

void User::growHungoffUses(unsigned NewNumUses, bool IsPhi) {
  assert(HasHungOffUses && "realloc must have hung off uses");

  unsigned OldNumUses = getNumOperands();

  assert(NewNumUses > OldNumUses && "realloc must grow num uses");

  Use *OldOps = getOperandBegin();
  allocHungoffUses(NewNumUses, IsPhi);
  Use *NewOps = getOperandBegin();

  std::copy(OldOps, OldOps + OldNumUses, NewOps);

  if (IsPhi) {
    auto *OldPtr = reinterpret_cast<char *>(OldOps + OldNumUses);
    auto *NewPtr = reinterpret_cast<char *>(NewOps + NewNumUses);
    std::copy(OldPtr, OldPtr + (OldNumUses * sizeof(BasicBlock *)), NewPtr);
  }
  Use::zap(OldOps, OldOps + OldNumUses, true);
}
