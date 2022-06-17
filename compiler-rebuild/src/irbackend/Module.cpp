#include "Module.h"

using namespace YAL;

Module::Module(std::string MID, LLVMContext &C):Context(C), ModuleID(MID){
  Context.addModule(this);
}


Module::~Module(){
  Context.removeModule(this);
  GlobalList.clear();
  FunctionList.clear();  
}