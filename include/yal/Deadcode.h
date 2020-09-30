#ifndef YAL_IR_DEADCODE_H
#define YAL_IR_DEADCODE_H

#include "Function.h"
#include "Module.h"
#include "Instruction.h"
#include "Instructions.h"
#include "support.h"
#include <vector>

namespace YAL{

    class DeadcodeEliminator{

        public:
            DeadcodeEliminator(){}
            bool run(Function *F);
            bool removeDeadInst(Instruction *I, std::vector<Instruction *> &worklist);
            bool isInstDead(Instruction *I);
            void removePhiEntry(BasicBlock *Old, BasicBlock *BB);

    };



}


#endif