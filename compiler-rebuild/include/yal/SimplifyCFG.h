#include "BasicBlock.h"
#include "Function.h"
#include "Instruction.h"
#include "Instructions.h"
#include "support.h"



namespace YAL {

    class SimplifyCFG{

        Function *Parent;

        public:
            SimplifyCFG(Function *F){
                Parent = F;
            }
            void run();
            void removeBlock(BasicBlock *BB);
            void modifyPhiEntry(BasicBlock *Old, BasicBlock *New, BasicBlock *BB);
            bool modifyBranchEntry(BasicBlock *Old, BasicBlock *New, BasicBlock *BB);
            void removePhiEntry(BasicBlock *Old, BasicBlock *BB);

    };

}

