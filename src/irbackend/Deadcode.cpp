#include "Deadcode.h"    

using namespace YAL;


bool DeadcodeEliminator::isInstDead(Instruction *I){
    if(I->isTerminator())
        return false;
    if(auto SI = cast<StoreInst>(I))
        return false;
    if(auto CI = cast<CallInst>(I))
        return false;
    if(I->use_empty()){
        return true;
    }
        
    
    return false;
}

void DeadcodeEliminator::removePhiEntry(BasicBlock *Old, BasicBlock *BB){
    std::vector<PHINode *> RemovedPhis;
    for(auto institer = BB->begin(); institer != BB->end(); institer++){
        if(auto Phi = cast<PHINode>(*institer)){
            for(int i = 0; i < Phi->getNumOperands(); i++){
                if(Old == Phi->getIncomingBlock(i)){
                    Phi->removeIncomingValue(Old);
                    break;
                }
            }
            if(Phi->getNumOperands() == 1){
                Phi->replaceAllUsesWith(Phi->getIncomingValue(0));
                RemovedPhis.push_back(Phi);
            }
        }
    }
    for(int i = 0; i < RemovedPhis.size(); i++){
        RemovedPhis[i]->eraseFromParent();
    }
}



bool DeadcodeEliminator::removeDeadInst(Instruction *I, std::vector<Instruction *> &worklist){
    if(!I)
        return false;
    if(isInstDead(I)){
        for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i) {
            Value *OpV = I->getNumOperand(i);

            I->getNumOperand(i) = UndefValue::get(OpV->getType());


            if (OpV && (!OpV->use_empty() || I == OpV))  continue;

            if (Instruction *OpI = cast<Instruction>(OpV))
                if (isInstDead(OpI))
                    worklist.push_back(OpI);

        }

        I->eraseFromParent();
        return true;
    }

    return false;
}


bool DeadcodeEliminator::run(Function *F){
    bool changed = false;
    std::vector<Instruction *> worklist;


    //Step 1: Remove all inst without use
    auto bbiter = F->BB_begin();

    while(bbiter != F->BB_end()){
        auto &instlist = (*bbiter)->getInstList();
        bool removed = false;
        for(auto institer = instlist.begin(); institer != instlist.end(); institer++){
            Instruction *I = *institer;
            if(std::find(worklist.begin(), worklist.end(), I) == worklist.end()){
                if(removeDeadInst(I, worklist)){
                    changed = true;
                    removed = true;
                    break;
                    
                }
            }
        }
        if(!removed)
            bbiter++;
    }

    while(!worklist.empty()){
        Instruction *I = worklist.back();
        worklist.pop_back();
        changed |= removeDeadInst(I, worklist);
    }



    //Step 2: Remove all insts behind terminator
    bbiter = F->BB_begin();
    while(bbiter != F->BB_end()){
        bool afterTerminator = false;
        bool removed = false;
        for(auto institer = (*bbiter)->begin(); institer != (*bbiter)->end(); institer++){
            Instruction *I = *institer;
            if(afterTerminator){
                I->eraseFromParent();
                removed = true;
                break;
            }
            if(I->isTerminator())
                afterTerminator = true;
        }
        if(!removed)
            bbiter++;
    }

    //Step 3: Deprecade conditional branch to unconditional branch
    for(auto bbiter = F->BB_begin(); bbiter != F->BB_end(); bbiter++){
        auto branch = cast<BranchInst>((*bbiter)->getTerminator());
        auto &InstList = (*bbiter)->getInstList();
        if(branch && branch->isConditional()){
            for(int i = 0; i < 3; i++){
                auto condition = cast<ConstantInt>(branch->getNumOperand(i).get());
                if(condition){
                    auto TrueBlock = cast<BasicBlock>(branch->getNumOperand(2).get());
                    auto FalseBlock = cast<BasicBlock>(branch->getNumOperand(1).get());
                     if(condition->getValue() != 0){
                        auto newbranch = BranchInst::Create(TrueBlock);
                        newbranch->setParent(*bbiter);
                        (*bbiter)->deleteSucc(FalseBlock);
                        FalseBlock->deletePred(*bbiter);
                        removePhiEntry(*bbiter, FalseBlock);
                        InstList.push_back(newbranch);
                        InstList.erase(std::find(InstList.begin(), InstList.end(), branch));
                     }
                     else{
                        auto newbranch = BranchInst::Create(FalseBlock);
                        newbranch->setParent(*bbiter);
                        (*bbiter)->deleteSucc(TrueBlock);
                        TrueBlock->deletePred(*bbiter);
                        removePhiEntry(*bbiter, TrueBlock);
                        InstList.push_back(newbranch);
                        InstList.erase(std::find(InstList.begin(), InstList.end(), branch));
                     }
                     break;
                }
            }
        }
    }



    return changed;

}