#include "LICM.h"


using namespace YAL;

void LICM::resolveLoopset(){
    auto livevars = new LiveVars();
    auto regassign = RegAssign(*Parent, &DT);
    Parent->setBlockOrder();
    auto RawLoopsets = regassign.calLoopDepth();

    for(auto rawiter = RawLoopsets.begin(); rawiter != RawLoopsets.end(); rawiter++){
        auto loopnode = new SimpleLoopNode;
        loopnode->start = (*rawiter)->start;
        loopnode->end = (*rawiter)->end;
        for(auto bbiter = (*rawiter)->LoopSet.begin(); bbiter != (*rawiter)->LoopSet.end(); bbiter++){
            loopnode->LoopSet.push_back(bbiter->second);
        }
        //check tail node
        for(auto bbiter = loopnode->LoopSet.begin(); bbiter != loopnode->LoopSet.end(); bbiter++){
            auto SuccList = (*bbiter)->getSuccList();
            for(auto succiter = SuccList.begin(); succiter != SuccList.end(); succiter++){
                if(std::find(loopnode->LoopSet.begin(), loopnode->LoopSet.end(), *succiter) == loopnode->LoopSet.end()){
                    loopnode->OutSet.push_back(*succiter);
                }
            }
        }
        Loopsets.push_back(loopnode);
    }

}

bool LICM::isIncluded(SimpleLoopNode *A, SimpleLoopNode*B){
    return A->LoopSet.size() < B->LoopSet.size() && 
            std::find(B->LoopSet.begin(), B->LoopSet.end(), A->start) != B->LoopSet.end() &&
            std::find(B->LoopSet.begin(), B->LoopSet.end(), A->end) != B->LoopSet.end();
}


void LICM::calLoopDepth(){
    auto size = Loopsets.size();
    for(int i = 0; i < size; i++){
        LoopDepth[Loopsets[i]] = 0;
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if(isIncluded(Loopsets[i], Loopsets[j])){
                if(LoopDepth[Loopsets[i]] == 0){
                    LoopParents[Loopsets[i]] = Loopsets[j];
                }
                else if(LoopParents.count(Loopsets[i]) > 0 && isIncluded(Loopsets[j], LoopParents[Loopsets[i]])){
                    LoopParents[Loopsets[i]] = Loopsets[j];
                }
            }
        }
    }

    bool changed = true;
    while(changed){
        changed = false;
        for(int i = 0; i < size; i++){
            if(LoopParents.count(Loopsets[i]) > 0 && LoopDepth[Loopsets[i]] != LoopDepth[LoopParents[Loopsets[i]]] + 1){
                changed = true;
                LoopDepth[Loopsets[i]] = LoopDepth[LoopParents[Loopsets[i]]] + 1;
                if(LoopDepth[Loopsets[i]] > maxLoopDepth){
                    maxLoopDepth = LoopDepth[Loopsets[i]];
                }
            }
        }
    }
}

bool LICM::dominatesTailNode(SimpleLoopNode *Node, BasicBlock *BB){
    bool dominated = true;
    for(auto iter = Node->OutSet.begin(); iter != Node->OutSet.end(); iter++){
        if(DT.dominates(BB, *iter) == false)
            dominated = false;
    }
    return dominated;
}


bool LICM::isAllowedMove(Instruction *I){
    return !isa<CallInst>(I)  && !isa<AllocaInst>(I) &&  !isa<ReturnInst>(I) &&
        !isa<PHINode>(I) && !I->isTerminator();
}



void LICM::handleOneLoop(SimpleLoopNode *Node){
    std::vector<Instruction *> CanPromote;
    std::map<GlobalVariable*, unsigned> AllocaStoredNum;
    std::map<GlobalVariable*, StoreInst*> OnlyStore;
    std::map<GlobalVariable*, std::vector<LoadInst *> > Loads;
    std::map<GlobalVariable*, bool> CanLoadPromote;
    std::map<GlobalVariable*, bool> CanStorePromote;

    //std::cout << "Start Handle Loop " << std::endl;

    //Step 1: Find all instructions which can be promoted
    for(auto bbiter = Node->LoopSet.begin(); bbiter != Node->LoopSet.end(); bbiter++){
        //std::cout << "Enter BB: " << (*bbiter)->getName() << std::endl;
        for(auto institer = (*bbiter)->begin(); institer !=(*bbiter)->end(); institer++){
            if(isa<LoadInst>(*institer)){
                //std::cout << "Find Load" << std::endl;
                auto alloca = cast<GlobalVariable>((*institer)->getNumOperand(0).get());
                if(!alloca){
                    //std::cout << "Null Load" << std::endl;
                }
                if(alloca != nullptr && AllocaStoredNum.count(alloca) == 0){
                    //std::cout << "Find Alloca" << std::endl;
                    AllocaStoredNum[alloca] = 0;
                    Loads[alloca].push_back(cast<LoadInst>(*institer));
                }

            }
            else if(isa<StoreInst>(*institer)){
                //std::cout << "Find Store" << std::endl;
                auto alloca = cast<GlobalVariable>((*institer)->getNumOperand(1).get());
                if(!alloca){
                    break;
                }
                else if(AllocaStoredNum.count(alloca) == 0){
                    AllocaStoredNum[alloca] = 1;
                    OnlyStore[alloca] = cast<StoreInst>(*institer);
                }
                else{
                    AllocaStoredNum[alloca]++;
                    OnlyStore[alloca] = cast<StoreInst>(*institer);
                }
            }
        }
    }

    //std::cout<< "Handle Loop Step 1-1: Alloca Scanned. " << std::endl;

    //std::cout << AllocaStoredNum.size() << "Global Variables Found" << std::endl;

    for(auto iter = AllocaStoredNum.begin(); iter !=AllocaStoredNum.end(); iter++){
        if(iter->second == 0){
            CanLoadPromote[iter->first] = true;
        }
        else if(iter->second == 1){
            auto store  = OnlyStore[iter->first];
            auto loads = Loads[iter->first];
            //std::cout << "Break 1" << std::endl;
            //std::cout << loads.size() << std::endl;
            for(auto loaditer = loads.begin(); loaditer != loads.end(); loaditer++){
                //std::cout << "Internal Break" << std::endl;
                if(!DT.dominates(store, *loaditer)){
                    //std::cout << "Store Can not promote" << std::endl;
                    CanStorePromote[iter->first] = false;
                }
            }
            //std::cout << "Break 2" << std::endl;
            if(CanStorePromote.count(iter->first) == 0 && isa<Constant>(store->getNumOperand(0).get())){
                CanStorePromote[iter->first] = true;
                CanLoadPromote[iter->first] = true;
            }
            else if(CanStorePromote[iter->first] == false){
                CanLoadPromote[iter->first] = false;
            }
        }
        else{
            CanLoadPromote[iter->first] = false;
            CanStorePromote[iter->first] = false;
        }
    }

    //std::cout << CanLoadPromote.size() << "Global Variables Loads Can Move" << std::endl;

    //std::cout<< "Handle Loop Step 1-2: Alloca Handled. " << std::endl;

    bool changed = true;
    while(changed){
        changed = false;
        for(auto bbiter = Node->LoopSet.begin(); bbiter != Node->LoopSet.end(); bbiter++){
            for(auto institer = (*bbiter)->begin(); institer != (*bbiter)->end(); institer++){
                //std::cout << "Handle Inst: " << (*institer)->getOpcodeName() << std::endl;
                //std::cout << "Is Allowed to Move " << isAllowedMove(*institer) << std::endl;
                //std::cout << "Dominates " << dominatesTailNode(Node, *bbiter) << std::endl;
                if(isAllowedMove(*institer)){
                    bool failed = false;
                    if(isa<LoadInst>(*institer)){
                        //std::cout << "Find Load" << std::endl;
                        auto alloca = cast<GlobalVariable>((*institer)->getNumOperand(0).get());
                        if(CanLoadPromote[alloca] == false || CanLoadPromote.count(alloca) == 0){
                            //std::cout << "Load Failed" << std::endl;
                            failed = true;
                            continue;
                        }
                    }
                    else if(isa<StoreInst>(*institer)){
                        auto operand = (*institer)->getNumOperand(0).get();
                        auto alloca = cast<GlobalVariable>((*institer)->getNumOperand(1).get());
                        if(CanStorePromote[alloca] == false){
                            failed = false;
                            continue;
                        }
                    }
                    else{
                        for(int i = 0; i < (*institer)->getNumOperands(); i++){
                            auto operand = (*institer)->getNumOperand(i).get();
                            if((!isa<Constant>(operand) && !isa<Argument>(operand))|| (isa<Instruction>(operand)  && std::find(CanPromote.begin(), CanPromote.end(), cast<Instruction>(operand)) == CanPromote.end() 
                            && std::find(Node->LoopSet.begin(), Node->LoopSet.end(), cast<Instruction>(operand)->getParent()) != Node->LoopSet.end())){
                                failed = true;
                                continue;
                            }
                        }
                    }
                    
                    if(!failed && std::find(CanPromote.begin(), CanPromote.end(), *institer) == CanPromote.end()){
                        CanPromote.push_back(*institer);
                        changed = true;
                    }

                }
            }
        }
    }

    //std::cout<< "Handle Loop Step 1-3: Other Insts Scanned. " << std::endl;


    //std::cout << CanPromote.size() << "Insts Can Move" << std::endl;

    if(CanPromote.size() == 0)
        return;

    //Step 2: Create New Basic Block

    //LLVMContext context;
    //std::cout<< "Creating BB" << std::endl;
    BasicBlock *NewBB = BasicBlock::Create(module->getContext(), Node->start->getName() + "LICMBlock", Parent, Node->start);

    for(auto BB: Node->start->getPredList()){
        if(std::find(Node->LoopSet.begin(), Node->LoopSet.end(), BB) == Node->LoopSet.end()){
            Node->start->deletePred(BB);
            NewBB->addPred(BB);
            BB->deleteSucc(Node->start);
            BB->addSucc(NewBB);
            auto branch = cast<BranchInst>(BB->getTerminator());
            if(branch){
                for(int i = 0; i < branch->getNumOperands(); i++){
                    //std::cout << i << std::endl;
                    if(branch->getNumOperand(i) == Node->start){
                        
                        branch->getNumOperand(i) = NewBB;
                        //std::cout << i << std::endl;
                        //std::cout << NewBB->getName() << std::endl;
                        //std::cout << NewBB->getType()->getTypeName() << std::endl;
                        //std::cout << branch->getNumOperand(i)->getType()->getTypeName() << std::endl;
                        //std::cout << "Modified Branch " << std::endl;
                        //break;
                    }
                }
            }
            
        }
    }

    NewBB->addSucc(Node->start);
    Node->start->addPred(NewBB);
    
    //std::cout<< "Handle Loop Step 2: New BB Created. " << std::endl;

    //Step 3: Insert Instructions
    for(auto institer = CanPromote.begin(); institer != CanPromote.end(); institer++){
        auto I = *institer;
        auto BB = I->getParent();
        auto &NewInstList = NewBB->getInstList();
        auto &OldInstList = BB->getInstList();
        OldInstList.erase(std::find(OldInstList.begin(), OldInstList.end(), I));
        NewInstList.push_back(I);
        I->setParent(NewBB);
    }

    //std::cout<< "Handle Loop Step 3: Insts Inserted. " << std::endl;



    //Step 4: Handle Phi Node

    for(auto institer = Node->start->begin(); institer != Node->start->end(); institer++){
        if(isa<PHINode>(*institer)){
            PHINode *PI = cast<PHINode>(*institer);

            //check Pred BBs which are moved into NewBB
            std::vector<int> MovedSet;
            for(int i = 0; i < PI->getNumOperands(); i++){
                auto PredBB = PI->getIncomingBlock(i);
                auto PredList = NewBB->getPredList();
                if(std::find(PredList.begin(), PredList.end(), PredBB) != PredList.end()){
                    MovedSet.push_back(i);
                }
            }

            //only one entry is from outside loop
            if(MovedSet.size() == 1){
                int index = MovedSet.back();
                MovedSet.pop_back();
                auto PredBB = PI->getIncomingBlock(index);
                PI->replaceIncomingBlockWith(PredBB, NewBB);
            }

            //more than onee entries are from outside loop
            else if(MovedSet.size() > 1){
                auto NewPN = PHINode::Create(PI->getType(), MovedSet.size(), 
                        PI->getName() + "LICMAdded",
                        *(NewBB->begin())); 

                for(auto iter = MovedSet.begin(); iter != MovedSet.end(); iter++){
                    int index = *iter;
                    auto PredBB = PI->getIncomingBlock(index);
                    auto Val = PI->getIncomingValue(index);
                    NewPN->addIncoming(Val, PredBB);
                    PI->removeIncomingValue(PredBB);
                }  

                PI->addIncoming(NewPN, NewBB);
                
            }

        }

        //std::cout<< "Handle Loop Step 4: Phi Node Handled. " << std::endl;
    }

    //Step 5: Insert Branch Inst
    auto BI = BranchInst::Create(Node->start);
    BI->setParent(NewBB);
    auto &NewInstList = NewBB->getInstList();
    NewInstList.push_back(BI);



    


    

    
}




void LICM::run(){

    //Step 1: Calculate all loops
    resolveLoopset();

    //std::cout<< "Step 1: Loop Calculated. " << std::endl;


    //Step 2: Find nested loops and their depth
    calLoopDepth();

    //std::cout<< "Step 1: Loop Depth Calculated. " << std::endl;

    //std::cout << "Find " << Loopsets.size() << "Loops" <<std::endl;
    //std::cout << "Max Depth" << maxLoopDepth << std::endl;


    //Step 3: Handle every loop iterally
    int CurrentDepth = maxLoopDepth;
    while(CurrentDepth >= 0){
        //std::cout << "Current Depth" << CurrentDepth << std::endl;
        for(auto iter = Loopsets.begin(); iter != Loopsets.end(); iter++){
            if(LoopDepth[*iter] == CurrentDepth){
                //std::cout<< "Loop Begin: " << (*iter)->start->getName() << std::endl;
                //std::cout<< "Loop End: " << (*iter)->start->getName() << std::endl;
                //std::cout << "Loop Size: " <<(*iter)->LoopSet.size() << std::endl;
                handleOneLoop(*iter);
                //std::cout<< "Step 3: One Loop Handled. " << std::endl;
            }
        }
        CurrentDepth--;
        //std::cout << "Depth Decreased: Current " << CurrentDepth << std::endl;
    }

    //std::cout << "Finished" << std::endl;


    //Step 4: Delete empty basic blocks
    

}