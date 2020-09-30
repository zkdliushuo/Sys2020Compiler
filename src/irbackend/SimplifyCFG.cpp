#include "SimplifyCFG.h"

using namespace YAL;



void SimplifyCFG::removeBlock(BasicBlock *BB){
    for(auto PredBB: BB->getPredList()){
        PredBB->deleteSucc(BB);
    }

    for(auto SuccBB: BB->getSuccList()){
        SuccBB->deletePred(BB);
    }

    Parent->getBasicBlockList().erase(std::find(Parent->getBasicBlockList().begin(), Parent->getBasicBlockList().end(), BB));
}

void SimplifyCFG::modifyPhiEntry(BasicBlock *Old, BasicBlock *New, BasicBlock *BB){
    for(auto institer = BB->begin(); institer != BB->end(); institer++){
        if(auto Phi = cast<PHINode>(*institer)){
            for(int i = 0; i < Phi->getNumOperands(); i++){
                if(Old == Phi->getIncomingBlock(i)){
                    Phi->replaceIncomingBlockWith(Old, New);
                    break;
                }
            }
        }
    }
}

bool SimplifyCFG::modifyBranchEntry(BasicBlock *Old, BasicBlock *New, BasicBlock *BB){
    auto branch = cast<BranchInst>(BB->getTerminator());
    if(branch){
        for(int i = 0; i < branch->getNumOperands(); i++){
            if(branch->getNumOperand(i) == New){
                return false;
            }
        }
        for(int i = 0; i < branch->getNumOperands(); i++){
            if(branch->getNumOperand(i) == Old){
                branch->getNumOperand(i) = New;
            }
        }
    }
    return true;
}

void SimplifyCFG::removePhiEntry(BasicBlock *Old, BasicBlock *BB){
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

void SimplifyCFG::run(){
    bool changed = true;

    while(changed){
        auto bbiter = Parent->BB_begin();
        for(; bbiter != Parent->BB_end(); bbiter++){
        auto BB = *bbiter;
        auto PredList = BB->getPredList();
        auto PredListSize = PredList.size();
        auto SuccList = BB->getSuccList();
        auto SuccListSize = SuccList.size();

        //Case 1: Delete BBs which do not have preds
        if(PredListSize == 0 && BB->getName() != "enter_block"){
            for(auto SuccBB: SuccList){
                removePhiEntry(BB, SuccBB);
            }
            removeBlock(BB);
            break;
        }

        //Case 3: Delete BBs which only has an unconditional branch instruction
        else if(SuccListSize == 1 && BB->getInstList().size() == 1 && PredListSize <= 1){
            bool failed = false;
            //std::cout << "Case 3: " << BB->getName() << std::endl;
            auto Branch = cast<BranchInst>(*BB->getInstList().begin());
            auto SuccBB = *SuccList.begin();
            if(BB->getName() == "enter_block" && cast<PHINode>(*SuccBB->begin())){
                continue;
            }

            if(Branch && !Branch->isConditional()){
                for(auto PredBB: PredList){
                    if(modifyBranchEntry(BB, SuccBB, PredBB)){
                        PredBB->addSucc(SuccBB);
                        modifyPhiEntry(BB, PredBB, SuccBB);
                        SuccBB->addPred(PredBB);
                    }
                    else{
                        failed = true;
                        break;
                    }
                }
                if(failed){
                    continue;
                }
                if(BB->getName() == "enter_block"){
                    SuccBB->setValueName("enter_block");
                }
                
                removeBlock(BB);
                break;
            }
        }

        //Case 2: Merge BBs which has only a predBB and this predBB only has a succBB
        else if(PredListSize == 1 && (*PredList.begin())->getSuccList().size() == 1){
            //std::cout << "Case 2: " << BB->getName() << std::endl;
            auto PredBB = *PredList.begin();
            auto PredBranch = cast<BranchInst>(PredBB->getTerminator());
            if(PredBranch && !PredBranch->isConditional()){
                auto &BBInstList = BB->getInstList();
                auto &PredInstList = PredBB->getInstList();
                PredInstList.erase(std::find(PredInstList.begin(), PredInstList.end(), PredBranch));
                for(auto inst: BBInstList){
                    PredInstList.push_back(inst);
                    inst->setParent(PredBB);
                }
                for(auto SuccBB: SuccList){
                    SuccBB->addPred(PredBB);
                    modifyPhiEntry(BB, PredBB, SuccBB);
                    PredBB->addSucc(SuccBB);
                }
                removeBlock(BB);
                break;
            }
        }

    }
        if(bbiter != Parent->BB_end()){
            changed = true;
        }
        else{
            changed = false;
        }
    }
    

}