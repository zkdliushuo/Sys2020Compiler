#include "Use.h"
#include "Value.h"
#include "User.h"
#include <iostream>

using namespace YAL;

unsigned Use::getOperandNo() const { return this - getUser()->op_begin(); }

void Use::set(Value *V) {
  // std::cout <<"Enter set Value" <<std::endl;
  if (Val){
    // std::cout <<"Before remove from list" <<std::endl;
    removeFromList();
    // std::cout <<"remove from list successed" <<std::endl;
  }
  // std::cout <<"After remove from list" <<std::endl;
  Val = V;
  if (V) {
    // std::cout <<"Before Vaue::addUse" <<std::endl;
    V->addUse(*this);
    // std::cout <<"Vaue::addUse successed" <<std::endl;
  }
}
