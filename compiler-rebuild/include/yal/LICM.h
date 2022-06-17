#ifndef YAL_IR_LICM_H
#define YAL_IR_LICM_H
 
#include "RegAssign.h"
#include "BasicBlock.h"
#include "Instruction.h"
#include "Instructions.h"
#include "Module.h"
#include "Function.h"
#include "DominatorTree.h"
#include "support.h"
#include "LLVMContext.h"
#include "GlobalVariable.h"
#include <vector>
#include <map>
#include <iostream>



namespace YAL{
    struct SimpleLoopNode {
        BasicBlock *start;
        BasicBlock *end;
        std::vector<BasicBlock*> LoopSet;
        std::vector<BasicBlock *> OutSet;
    };

    class LICM{
        Function *Parent;
        DominatorTree DT;
        int maxLoopDepth = 0;
        std::vector<SimpleLoopNode *> Loopsets;
        std::map<SimpleLoopNode *, int > LoopDepth;
        std::map<SimpleLoopNode *, SimpleLoopNode* > LoopParents;
        Module *module;






        public:
            LICM(Function *F, DominatorTree domtree, Module *M){
                Parent = F;
                DT = domtree;
                module = M;
            }


        void run();
        void resolveLoopset();
        void calLoopDepth();
        bool isIncluded(SimpleLoopNode *A, SimpleLoopNode*B);
        bool dominatesTailNode(SimpleLoopNode *Node, BasicBlock *BB);
        bool isAllowedMove(Instruction *I);
        void handleOneLoop(SimpleLoopNode *Node);

    };
}


#endif