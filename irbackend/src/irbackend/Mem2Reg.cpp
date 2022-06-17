#include "Mem2Reg.h"


using namespace YAL;


bool MemoryPromoter::MemToReg(Function *F, DominatorTree &DT){
    std::vector<AllocaInst *> Allocas;
    BasicBlock *BB = F->getEntryBlock();
    bool changed = false;


    while(true){

        Allocas.clear();
        for(BasicBlock::iterator iter = BB->begin();  iter != BB->end(); ++iter){
            if(AllocaInst *AI = cast<AllocaInst>(*iter)){
                if(isPromotable(AI)){
                    Allocas.push_back(AI);
                }
            }
        }
        if(Allocas.empty())
            break;
        auto promoter = PromoteMemToReg(Allocas, DT);
        promoter.run();
        NumPromoted += Allocas.size();
        changed = true;
    }

    return changed;

}

bool MemoryPromoter::isPromotable(const AllocaInst *AI){
    for(const User *U: AI->users()){
        if(isa<LoadInst>(U)){
            continue;
        }
        else if(const StoreInst *SI = cast<StoreInst>(U)){
            if (SI->getNumOperand(0).get() == AI)
                return false; 
        }
        else if (const GetElementPtrInst *GEPI = cast<GetElementPtrInst>(U)){
            if (!GEPI->hasAllZeroIndices())
                return false;
        }
        else{
            return false;
        }
    }

    return true;
}


void IDFCalculator::calculate(std::vector<BasicBlock *> &PhiBlocks){
    using DomTreeNodePair =   std::pair<DominatorTreeNode*, std::pair<unsigned, unsigned> >;
    using IDFPriorityQueue =   std::priority_queue<DomTreeNodePair, std::vector<DomTreeNodePair>,less_second>;

    IDFPriorityQueue PQ;

    DT.genDFSNums();

    std::vector<DominatorTreeNode *> Worklist;
    std::vector<DominatorTreeNode *> VisitedPQ;
    std::vector<DominatorTreeNode *> VisitedWorklist;


    //push all def blocks in the queue since their successors may need phi nodes
    for (BasicBlock *BB : DefBlocks)
        if (DominatorTreeNode *Node = DT.getNode(BB)) {
            PQ.push({Node, std::make_pair(Node->getLevel(), Node->getDFSNumIn())});
            VisitedWorklist.push_back(Node);
        }

    while (!PQ.empty()) {
        DomTreeNodePair RootPair = PQ.top();
        PQ.pop();
        DominatorTreeNode *Root = RootPair.first;
        unsigned RootLevel = RootPair.second.first;

        Worklist.push_back(Root);

        while (!Worklist.empty()) {
            DominatorTreeNode *Node = Worklist.back();
            Worklist.pop_back();
            BasicBlock *BB = Node->getBlock();


            //check if a block needs phi node
            auto DoWork = [&](BasicBlock *Succ) {
                DominatorTreeNode *SuccNode = DT.getNode(Succ);

                unsigned SuccLevel = SuccNode->getLevel();
                //if (SuccLevel > RootLevel)  return;

                if(std::find(VisitedPQ.begin(), VisitedPQ.end(), SuccNode) == VisitedPQ.end())  
                    VisitedPQ.push_back(SuccNode);
                else
                    return;

                //this block must be live in before inserting a phi node
                BasicBlock *SuccBB = SuccNode->getBlock();
                if (std::find(LiveInBlocks.begin(), LiveInBlocks.end(), SuccBB) == LiveInBlocks.end())   return;

                PhiBlocks.emplace_back(SuccBB);

                //the successors of this block also needs check
                if (std::find(DefBlocks.begin(), DefBlocks.end(), SuccBB) == DefBlocks.end())
                    PQ.push(std::make_pair(SuccNode, std::make_pair(SuccLevel, SuccNode->getDFSNumIn())));
            };

            for (auto Succ : BB->getSuccList()){
                DoWork(Succ);
            }

            for (auto DomChild : Node->getChildren()) {
                if(std::find(VisitedWorklist.begin(), VisitedWorklist.end(), DomChild) == VisitedWorklist.end()){
                    VisitedWorklist.push_back(DomChild);
                    Worklist.push_back(DomChild);
                }
            }
        }
    }
}



void PromoteMemToReg::AllocaInfo::analyze(AllocaInst *AI){
    clear();

    for (auto UI = AI->user_begin(), E = AI->user_end(); UI != E;) {
        Instruction *User = cast<Instruction>(*UI++);

        if (StoreInst *SI = cast<StoreInst>(User)) {
            DefBlocks.push_back(SI->getParent());
            OnlyStore = SI;
        } 
        else {
            LoadInst *LI = cast<LoadInst>(User);
            UseBlocks.push_back(LI->getParent());
        }

        if (OnlyUsedInOneBlock) {
            if (!OnlyBlock) OnlyBlock = User->getParent();
            else if (OnlyBlock != User->getParent())    OnlyUsedInOneBlock = false;
        }
    }

}


void PromoteMemToReg::removeAlloca(unsigned &AllocaNum){
    Allocas[AllocaNum] = Allocas.back();
    Allocas.pop_back();
    AllocaNum--;
}

bool PromoteMemToReg::processSingleStore(AllocaInst *AI, AllocaInfo &Info, DominatorTree &DT){
    StoreInst *OnlyStore = Info.OnlyStore;
    bool StoringGlobalVal = !isa<Instruction>(OnlyStore->getNumOperand(0).get());
    BasicBlock *StoreBB = OnlyStore->getParent();
    int StoreIndex = -1;

    Info.UseBlocks.clear();


    //replace all loadinst's use with storeinst
    for (auto UI = AI->user_begin(), E = AI->user_end(); UI != E;) {
        Instruction *UserInst = cast<Instruction>(*UI++);
        if (UserInst == OnlyStore)
            continue;
        LoadInst *LI = cast<LoadInst>(UserInst);

        //loads not dominated by store can not be processed
        if (!StoringGlobalVal && !DT.dominates(OnlyStore, LI)) { 
            Info.UseBlocks.push_back(LI->getParent());
            continue;
        }

        Value *ReplVal = OnlyStore->getNumOperand(0).get();
        if (ReplVal == LI)
            ReplVal = UndefValue::get(LI->getType());

        LI->replaceAllUsesWith(ReplVal);
        LI->eraseFromParent();
    }

    //not all loadinsts are processed
    if (!Info.UseBlocks.empty())  return false; 

    //remove dead store and alloca
    Info.OnlyStore->eraseFromParent();
    AI->eraseFromParent();
    return true;
}

bool PromoteMemToReg::processSingleBlock(AllocaInst *AI, AllocaInfo &Info, DominatorTree &DT, BlockInfo &BI){
    using StoresByIndexTy = std::map<unsigned, StoreInst *>;
    StoresByIndexTy StoresByIndex;


    for (User *U : AI->users())
        if (StoreInst *SI = cast<StoreInst>(U))
            StoresByIndex[BI.getIndex(SI)] = SI;


    //replace load's use with nearest store
    for (auto UI = AI->user_begin(), E = AI->user_end(); UI != E;) {
        LoadInst *LI = cast<LoadInst>(*UI++);
        if (!LI)    continue;

        unsigned LoadIdx = BI.getIndex(LI);

        //find the nearest store that has a lower index than this load.
        std::map<unsigned, StoreInst *>::iterator iter;
        for(unsigned index = LoadIdx; index >=0; index--){
            iter = StoresByIndex.find(index);
            if(iter != StoresByIndex.end()){
                break; 
            }
        }

        if (iter == StoresByIndex.end()) {
            if (StoresByIndex.empty())
                LI->replaceAllUsesWith(UndefValue::get(LI->getType()));
            else
                return false;
        } 
        else {
            Value *ReplVal = iter->second->getNumOperand(0).get();
            if (ReplVal == LI)
                ReplVal = UndefValue::get(LI->getType());

            LI->replaceAllUsesWith(ReplVal);
        }

        LI->eraseFromParent();
        BI.deleteValue(LI);
    }


    //remove dead stores and alloca.
    for (auto UI = AI->user_begin(), E = AI->user_end(); UI != E;) {
        StoreInst *SI = cast<StoreInst>(*UI++);
        if(SI)
            SI->eraseFromParent();
        BI.deleteValue(SI);
    }

    AI->eraseFromParent();

    ++NumLocalPromoted;
    return true;
}

void PromoteMemToReg::calculateLiveInBlocks(AllocaInst *AI, AllocaInfo &Info, std::vector<BasicBlock *> &defblocks, std::vector<BasicBlock *> &liveinblocks){
    std::vector<BasicBlock *> LiveInBlockWorklist(Info.UseBlocks.begin(), Info.UseBlocks.end());

    //if use block is the same with def block, check if store is before load
    for (unsigned i = 0, e = LiveInBlockWorklist.size(); i != e; ++i) {
        BasicBlock *BB = LiveInBlockWorklist[i];
        if (std::find(defblocks.begin(), defblocks.end(), BB) == defblocks.end())   continue;

        for (BasicBlock::iterator I = BB->begin();; ++I) {
            if (StoreInst *SI = cast<StoreInst>(*I)) {
                if (SI->getNumOperand(1).get() != AI)    continue;
                LiveInBlockWorklist[i] = LiveInBlockWorklist.back();
                LiveInBlockWorklist.pop_back();
                --i;
                --e;
                break;
            }

        if (LoadInst *LI = cast<LoadInst>(*I))
            if (LI->getNumOperand(0).get() == AI)    break;
        }
    }
    
    //add the useblocks' preds if they also not def alloca
    while (!LiveInBlockWorklist.empty()) {
        BasicBlock *BB = LiveInBlockWorklist.back();
        LiveInBlockWorklist.pop_back();

        if(std::find(liveinblocks.begin(), liveinblocks.end(), BB) == liveinblocks.end())     
            liveinblocks.push_back(BB);
        else 
            continue;

        for (BasicBlock *P : BB->getPredList()) {
            if (std::find(defblocks.begin(), defblocks.end(), P) != defblocks.end()) continue;
            LiveInBlockWorklist.push_back(P);
        }
    }
}

bool PromoteMemToReg::QueuePhiNode(BasicBlock *BB, unsigned AllocaNo, unsigned &Version){
    if(NewPhiNodes.find(std::make_pair(BBNumbers[BB], AllocaNo)) != NewPhiNodes.end())
        return false;

    auto PN = PHINode::Create(Allocas[AllocaNo]->getAllocatedType(), BB->getPredNum(), 
                        Allocas[AllocaNo]->getName() + "." + std::to_string(Version++),
                        *(BB->begin()));   

    ++NumPHIInsert;
    PhiToAllocaMap[PN] = AllocaNo;
    NewPhiNodes[std::make_pair(BBNumbers[BB], AllocaNo)] = PN;
    return true;
}

void PromoteMemToReg::RenamePass(BasicBlock *BB, BasicBlock *Pred, RenamePassData::ValVector &IncomingVals, std::vector<RenamePassData> &Worklist){
    
    NextIteration:

    //if Phi node exists, update it
    if (PHINode *APN = cast<PHINode>(*(BB->begin()))) {
        if (PhiToAllocaMap.count(APN)) {
            unsigned NewPHINumOperands = APN->getNumOperands();
            auto nextblocks = Pred->getNextBlocks();
            unsigned NumEdges = std::count(nextblocks.begin(), nextblocks.end(), BB);
            assert(NumEdges && "Must be at least one edge from Pred to BB!");


            // Add entries for all the phis.
            BasicBlock::iterator PNI = BB->begin();
            do {
                unsigned AllocaNo = PhiToAllocaMap[APN];
                for (unsigned i = 0; i != NumEdges; ++i)
                    APN->addIncoming(IncomingVals[AllocaNo], Pred);

                // The currently active variable for this block is now the PHI.
                IncomingVals[AllocaNo] = APN;

                // Get the next phi node.
                ++PNI;
                APN = cast<PHINode>(*PNI);
                if (!APN)   break;
            } while (APN->getNumOperands() == NewPHINumOperands);
        }
    }


    // Don't revisit blocks.
    if(std::find(VisitedInRename.begin(), VisitedInRename.end(), BB) == VisitedInRename.end())
        VisitedInRename.push_back(BB);
    else
        return;



    //handle load and store
    for (BasicBlock::iterator II = BB->begin(); !(*II)->isTerminator();) {
        Instruction *I = *II++;

        if (LoadInst *LI = cast<LoadInst>(I)) {
            AllocaInst *Src = cast<AllocaInst>(LI->getPointerOperand());
            if (!Src)   continue;

            auto AI = AllocaLookup.find(Src);
            if (AI == AllocaLookup.end())    continue;

            Value *V = IncomingVals[AI->second];
            LI->replaceAllUsesWith(V);
            LI->eraseFromParent();
        } 
        else if (StoreInst *SI = cast<StoreInst>(I)) {
            AllocaInst *Dest = cast<AllocaInst>(SI->getPointerOperand());
            if (!Dest)  continue;
            auto ai = AllocaLookup.find(Dest);
            if (ai == AllocaLookup.end())   continue;

            unsigned AllocaNo = ai->second;
            IncomingVals[AllocaNo] = SI->getNumOperand(0).get();
            SI->eraseFromParent();
        }
    }

    // handle successors
    auto succs = BB->getNextBlocks();
    int size = succs.size();
    if(size == 0)
        return;

    auto I = succs.begin();
    int index = 0;
    std::vector<BasicBlock *> VisitedSuccs;
    

    VisitedSuccs.push_back(*I);
    
    Pred = BB;
    BB = *I;
    ++I;
    index++;
    for (; index < size; I++, index++)
        if (std::find(VisitedSuccs.begin(), VisitedSuccs.end(), *I) == VisitedSuccs.end()){

            VisitedSuccs.push_back(*I);

            Worklist.emplace_back(*I, Pred, IncomingVals);
        }

    goto NextIteration;
}

bool PromoteMemToReg::valueDominatesPhi(Value *V, PHINode *P, DominatorTree DT){
    Instruction *I = cast<Instruction>(V);
    if (!I)
        return true;
    if (!I->getParent() || !P->getParent() || !I->getFunction())
        return false;

    
    if (DT.getRootNode())
        return DT.dominates(I, P);

    //if it is in the entry block, it dominates all blocks
    if (I->getParent() == I->getFunction()->getEntryBlock())
        return true;

    return false;
}

Value* PromoteMemToReg::simplifyPhiNode(PHINode *PN, DominatorTree DT) {
    // If all of the PHI's incoming values are the same then replace the PHI node
  // with the common value.
    Value *CommonValue = nullptr;
    bool HasUndefInput = false;
    int i = 0;
    for (Value *Incoming : PN->incoming_values()) {
        if (Incoming == PN) continue;
        if (isa<UndefValue>(Incoming)) {
            LLVMContext context;
            PN->setIncomingValue(i, ConstantInt::get(context, 0));
            HasUndefInput = true;
            i++;
        }
        if (CommonValue && Incoming != CommonValue) return nullptr;
        CommonValue = Incoming;
    }

    if (!CommonValue)
        return UndefValue::get(PN->getType());

    if (HasUndefInput)
        return valueDominatesPhi(CommonValue, PN, DT) ? CommonValue : nullptr;

    return CommonValue;
}

void PromoteMemToReg::run(){
    Function *F = DT.getParent();

    AllocaInfo Info;
    auto BI = BlockInfo();


    for(unsigned AllocaNum = 0; AllocaNum < Allocas.size(); ++AllocaNum){
        AllocaInst *AI = Allocas[AllocaNum];


        //Step 1: Remove allocas never used
        if(AI->use_empty()){
            AI->eraseFromParent();
            removeAlloca(AllocaNum);
            ++NumDeadAlloca;
            continue;
        }


        //Step 2: Calculate properties of every AllocaInst
        Info.analyze(AI);


        //Step 3: Pruning

        //Step 3-1: If Alloca has only one def block
        if(Info.DefBlocks.size() == 1 && processSingleStore(AI, Info, DT)){
            removeAlloca(AllocaNum);
            ++NumSingleStore;
            continue;
        }


        //Step 3-2: If all load and store are in the same block
        if(Info.OnlyUsedInOneBlock && processSingleBlock(AI, Info, DT, BI)){
            removeAlloca(AllocaNum);
            continue;
        }

        AllocaLookup[Allocas[AllocaNum]] = AllocaNum;


        //Step 4: Calculate live-in blocks

        std::vector<BasicBlock *> defblocks(Info.DefBlocks.begin(), Info.DefBlocks.end());
        std::vector<BasicBlock *> liveinblocks;

        
        calculateLiveInBlocks(AI, Info, defblocks, liveinblocks);



        //Step 5: Create Phi Node
        IDFCalculator IDF(DT, liveinblocks, defblocks);
        std::vector<BasicBlock *> PhiBlocks;
        IDF.calculate(PhiBlocks);


        //calculate basicblock numbers
        if(BBNumbers.empty()){
            unsigned ID = 0;
            for(auto BB : F->getBasicBlockList())
                BBNumbers[BB] = ID++;
        }


        std::sort(PhiBlocks.begin(), PhiBlocks.end(), [this](BasicBlock *A, BasicBlock *B) {
            return BBNumbers.find(A)->second < BBNumbers.find(B)->second;
        });


        unsigned CurrentVersion = 0;
        for (BasicBlock *BB : PhiBlocks)
            QueuePhiNode(BB, AllocaNum, CurrentVersion);
    }

    if (Allocas.empty())    return; 
    BI.clear();


    //Step 6: Set incoming values for Phi nodes

    //LLVMContext context;
    std::vector<Value *> Values(Allocas.size());
    for (unsigned i = 0, e = Allocas.size(); i != e; ++i){
        Values[i] = UndefValue::get(Allocas[i]->getAllocatedType());   
    }

    std::vector<RenamePassData> RenamePassWorkList;
    RenamePassWorkList.emplace_back(F->getEntryBlock(), nullptr, std::move(Values));
    do {
        RenamePassData RPD = std::move(RenamePassWorkList.back());
        RenamePassWorkList.pop_back();
        RenamePass(RPD.BB, RPD.Pred, RPD.Values, RenamePassWorkList);
    } while (!RenamePassWorkList.empty());

    VisitedInRename.clear();


    //Step 7: Remove all dead allocas

    for (Instruction *A : Allocas) {
    //alloca should not have any uses now, if still have, just delete them
    if (!A->use_empty())
        A->replaceAllUsesWith(UndefValue::get(A->getType()));
    A->eraseFromParent();
    }


    //Step 8: Simplify Phi nodes
    bool EliminatedAPHI = true;
    while (EliminatedAPHI) {
        EliminatedAPHI = false;

        for (auto I = NewPhiNodes.begin(),  E = NewPhiNodes.end();  I != E;) {
            PHINode *PN = I->second;

            if (Value *V = simplifyPhiNode(PN, DT)) {
                PN->replaceAllUsesWith(V);
                PN->eraseFromParent();
                NewPhiNodes.erase(I++);
                EliminatedAPHI = true;
                continue;
            }
            ++I;
        }
    }

    NewPhiNodes.clear();



}