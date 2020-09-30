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
  // auto temp = Val;
  // std::cout <<"After remove from list" <<std::endl;
  Val = V;
  if (V) {
    // std::cout << "Before" << std::endl;
    // for (auto u = Val->user_begin(); u != Val->user_end(); u++) {
    //   std::cout << " >> U: " << u->FOrder << std::endl;
    // }
    // std::cout <<"Before Value::addUse" <<std::endl;
    V->addUse(*this);
  }
  // if (temp) {
  //   std::cout << "\nAfter" << std::endl;
  //   for (auto u = temp->user_begin(); u != temp->user_end(); u++)
  //     std::cout << " >> U: " << u->FOrder << std::endl;
  //   // std::cout <<"Vaue::addUse successed" <<std::endl;
  // }
}
