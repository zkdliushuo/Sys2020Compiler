#ifndef LIVEVAR_h
#define LIVEVAR_h
#include "Instruction.h"
#include "Pass.h"

namespace YAL{

class Function;
class BasicBlock;

class LiveVars : public FunctionPass {
public:
  explicit LiveVars() : FunctionPass("LiveVariables") {};

  bool runOnFunction(Function &F);

  void CalLiveInterval(BasicBlock *BB);
};
}

#endif