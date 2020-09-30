#include "DominatorTree.h"

using namespace YAL;




//===----------------------------------------------------------------------===//
//                     Implementation of dominate functions                   //
//===----------------------------------------------------------------------===//

bool DominatorTree::dominates(   DominatorTreeNode *A,    DominatorTreeNode *B){


    //every node dominates itself
    if(A == B) return true;

    //an unreachable node is dominated by every node
    if(!isReachableFromEntry(B)) return true;

    //an unreachable node dominates nothing
    if(!isReachableFromEntry(A)) return false;

    if(B->getIdom() == A) return true;

    if(A->getIdom() == B) return false;

    if(A->getLevel() >= B->getLevel()) return false;


    //check if B is on the subtree of A
    if(DFSInfoValid){
        if(B->getDFSNumIn() >= A->getDFSNumIn() && B->getDFSNumOut() <= A->getDFSNumOut()) return true;
    }
    else{
        genDFSNums();
        if(B->getDFSNumIn() >= A->getDFSNumIn() && B->getDFSNumOut() <= A->getDFSNumOut()) return true;
    }


    //check if A dominates B's dominators
    auto tempB = B;
    while(tempB->getIdom() != nullptr && tempB->getIdom()->getLevel() >= A->getLevel()){
        tempB = tempB->getIdom();
    }

    return tempB == A;

}

bool DominatorTree::dominates(  BasicBlock *A,   BasicBlock *B) {
    if (A == B) return true;

    return dominates(getNode(A), getNode(B));
}

bool DominatorTree::dominates(  Instruction *Def,   Instruction *User){
      BasicBlock *UseBB = User->getParent();
      BasicBlock *DefBB = Def->getParent();

    if (!isReachableFromEntry(UseBB))
        return true;

    // Unreachable definitions don't dominate anything.
    if (!isReachableFromEntry(DefBB))
        return false;

    // An instruction doesn't dominate a use in itself.
    if (Def == User)
        return false;

    // A PHI is dominated only if the instruction dominates every possible use in
    // the UseBB.
    //if (isa<PHINode>(User))
    //    return dominates(Def, UseBB);

    if (DefBB != UseBB)
        return dominates(DefBB, UseBB);

    return Def->comesBefore(User);
}


bool DominatorTree::dominates(  Instruction *Def,   BasicBlock *UseBB){
      BasicBlock *DefBB = Def->getParent();

    // Any unreachable use is dominated, even if DefBB == UseBB.
    if (!isReachableFromEntry(UseBB))
        return true;

    // Unreachable definitions don't dominate anything.
    if (!isReachableFromEntry(DefBB))
        return false;

    // Def can not dominates use in itself
    if (DefBB == UseBB)
        return false;

    return dominates(DefBB, UseBB);
}

bool DominatorTree::dominates(  Instruction *Def,   Use &U){
  Instruction *UserInst = cast<Instruction>(U.getUser());
    BasicBlock *DefBB = Def->getParent();

  // Determine the block in which the use happens. PHI nodes use
  // their operands on edges; simulate this by thinking of the use
  // happening at the end of the predecessor block.
    BasicBlock *UseBB;
 // if (PHINode *PN = dyn_cast<PHINode>(UserInst))
  //  UseBB = PN->getIncomingBlock(U);
 // else
    UseBB = UserInst->getParent();

  // Any unreachable use is dominated, even if Def == User.
  if (!isReachableFromEntry(UseBB))
    return true;

  // Unreachable definitions don't dominate anything.
  if (!isReachableFromEntry(DefBB))
    return false;

  // If the def and use are in different blocks, do a simple CFG dominator
  // tree query.
  if (DefBB != UseBB)
    return dominates(DefBB, UseBB);

  // Ok, def and use are in the same block. If it's a PHI, it dominates
  // everything in the block.
  //if (isa<PHINode>(UserInst))
  //  return true;

  return Def->comesBefore(UserInst);
}



//===----------------------------------------------------------------------===//
//                     Implementation of DFS Number Function                  //
//===----------------------------------------------------------------------===//


void DominatorTree::genDFSNums() {
    if(DFSInfoValid)    return;
    std::vector<DominatorTreeNode * > workstack1;
    std::vector<int> workstack2;
    DominatorTreeNode *Root = getRootNode();
    if(!Root)   return;
    workstack1.push_back(Root);
    workstack2.push_back(0);

    //std::vector<std::vector< DominatorTreeNode *>::iterator>  temp;
    //temp.push_back(Root->getChildren().begin());
    //std::cout << (*(temp.back()))->getLevel() << std::endl;

    unsigned DFSNum = 0;
    Root->setDFSNumIn(DFSNum++);


    while(!workstack1.empty()){
        DominatorTreeNode *Node = workstack1.back();
        auto childIndex = workstack2.back();
        if(childIndex == Node->getChildren().size()){
            Node->setDFSNumOut(DFSNum++);
            workstack1.pop_back();
            workstack2.pop_back();
        }
        else{
            DominatorTreeNode *Child = Node->getChildren()[childIndex];
            childIndex++;
            workstack2.pop_back();
            workstack2.push_back(childIndex);
            workstack1.push_back(Child);
            workstack2.push_back(0);
            Child->setDFSNumIn(DFSNum++);

        }

    }
    DFSInfoValid = true;

}


//===----------------------------------------------------------------------===//
//                     Implementation of tree printer                         //
//===----------------------------------------------------------------------===//

void DominatorTree::printTree(){
    std::cout << "==========================Level: "  << RootNode->getLevel() << std::endl;
    std::cout << "Root Node: "  <<std::endl;
    auto bb = RootNode->getBlock();
    for(auto iter = RootNode->getBlock()->begin(); iter != RootNode->getBlock()->end(); iter++){
        std::cout << (*iter)->getOpcodeName() << std::endl;
    }
    std::vector<DominatorTreeNode *> workstack;
    workstack.push_back(RootNode);
    while(!workstack.empty()){
        auto node = workstack.back();
        workstack.pop_back();
        auto children = node->getChildren();
        if(!children.empty()){
            for(auto iter = children.begin(); iter != children.end(); iter++){
                workstack.insert(workstack.begin(), *iter);
                std::cout << "==========================Level: "  << (*iter)->getLevel() << std::endl;
                for(auto childiter = (*iter)->getBlock()->begin(); childiter != (*iter)->getBlock()->end(); childiter++){
                    std::cout << (*childiter)->getOpcodeName() << std::endl;
                }
            }
        }

    }

    
}

//===----------------------------------------------------------------------===//
//                  Implementation of dominator tree builder                  //
//===----------------------------------------------------------------------===//

void DominatorTree::reset(){
    DominatorTreeNodes.clear();
    RootNode = nullptr;
    Root = nullptr;
    DFSInfoValid = false;
    ParentFunc = nullptr;

}

unsigned DominatorTree::SemiNCAInfo::runDFS(DominatorTreeNode *Node, unsigned LastNum){
    if(! Node) return -1;

    std::vector<DominatorTreeNode *> worklist = {Node};

    if(NodeToInfo.count(Node) != 0) NodeToInfo[Node].Parent = 0;

    while(!worklist.empty()){
        DominatorTreeNode *BB = worklist.back();
        worklist.pop_back();

        if(NodeToInfo.find(BB) == NodeToInfo.end()){
            auto BBInfoPtr = new InfoRec;
            auto BBInfo = *BBInfoPtr;
            LastNum++;
            BBInfo.Sdom = LastNum;
            BBInfo.DFSNum = LastNum;
            BBInfo.Label = BB;
            NodeToInfo[BB] = BBInfo;
        }
        else if(NodeToInfo.find(BB) != NodeToInfo.end() && NodeToInfo.find(BB)->second.DFSNum == 0){
            auto &BBInfo = NodeToInfo[BB];
            LastNum++;
            BBInfo.Sdom = LastNum;
            BBInfo.DFSNum = LastNum;
            BBInfo.Label = BB;
        }
        else{
            continue;
        }


        NumToNode.push_back(BB);

        std::vector<DominatorTreeNode *> Succs;

        auto SuccList = BB->getBlock()->getSuccList();



        for(  BasicBlock *Succ: SuccList){
            if(Parent->DominatorTreeNodes.find(Succ) == Parent->DominatorTreeNodes.end()){
                auto Node = new DominatorTreeNode(Succ, nullptr);
                Parent->DominatorTreeNodes[Succ] = Node;
                Succs.push_back(Node);
            }
            else{
                Succs.push_back(Parent->DominatorTreeNodes[Succ]);
            }
            
        }

        for(  DominatorTreeNode *Succ: Succs){
              auto SIT = NodeToInfo.find(Succ);

            //if this node is visited
            if(SIT  != NodeToInfo.end() && SIT->second.DFSNum != 0){
                if (Succ != BB) SIT->second.ReverseChildren.push_back(BB);
                continue;
            }

            auto SuccInfoPtr = new InfoRec;
            auto SuccInfo = *SuccInfoPtr;
            worklist.push_back(Succ);
            SuccInfo.Parent = LastNum;
            SuccInfo.ReverseChildren.push_back(BB);
            NodeToInfo[Succ] = SuccInfo;
        }
    }
    
    return LastNum;

}

DominatorTreeNode* DominatorTree::SemiNCAInfo::eval(DominatorTreeNode *N, unsigned LastLinked, std::vector<InfoRec *> &stack){
    InfoRec *NInfo = &NodeToInfo[N];

    //for predecessors whose DFSNum is smaller than this node, just return them
    if(NInfo->Parent < LastLinked) return NInfo->Label;
    stack.clear();

    //Now handle predecessors whose DFSNum is larger than this node
    do{
        stack.push_back(NInfo);
        NInfo = &NodeToInfo[NumToNode[NInfo->Parent]];
    }while(NInfo->Parent >= LastLinked);


    //parents are invalid after run this
      InfoRec *PInfo  = NInfo;
      InfoRec *PLabelInfo = &NodeToInfo[PInfo->Label];
    do{
        NInfo = stack.back();
        stack.pop_back();
        NInfo->Parent = PInfo->Parent;
          InfoRec *NLabelInfo = &NodeToInfo[NInfo->Label];
        if(PLabelInfo->Sdom < NInfo->Sdom){
            NInfo->Label = PInfo->Label;
        }
        else{
            PLabelInfo = NLabelInfo;
        }
        PInfo = NInfo;
    }while(!stack.empty());
    return NInfo->Label;


}

void DominatorTree::SemiNCAInfo::runSemiNCA(unsigned MinLevel = 0){
    unsigned nextDFSNum = NumToNode.size();

    for(unsigned i = 1; i < nextDFSNum; ++i){
        DominatorTreeNode *Node = NumToNode[i];
        auto &NodeInfo = NodeToInfo[Node];
        NodeInfo.Idom = NumToNode[NodeInfo.Parent];
    }

    //calculate semidominators of every node
    std::vector<InfoRec *> evalstack;
    for(unsigned i = nextDFSNum - 1; i>=2; --i){
        DominatorTreeNode *W = NumToNode[i];
        auto &WInfo = NodeToInfo[W];
        WInfo.Sdom = WInfo.Parent;

        for(  auto &N: WInfo.ReverseChildren){
            if(NodeToInfo.count(N) == 0) continue;
            if(N && N->getLevel() < MinLevel) continue;
            unsigned SemiU = NodeToInfo[eval(N, i+1, evalstack)].Sdom;
            if(SemiU < WInfo.Sdom) WInfo.Sdom = SemiU;
        }

    }
    


    //calculate immediate dominators of every node
    for(unsigned i = 2; i < nextDFSNum; ++i){
          DominatorTreeNode *W = NumToNode[i];
        auto &WInfo = NodeToInfo[W];
          unsigned SdomNum = NodeToInfo[NumToNode[WInfo.Sdom]].DFSNum;
        DominatorTreeNode *P = WInfo.Idom;
        while(NodeToInfo[P].DFSNum > SdomNum){
            P = NodeToInfo[P].Idom;
        }
        WInfo.Idom = P;
    }


}

void DominatorTree::SemiNCAInfo::updateNodeInfo(){
    for(unsigned i = 1, e = NumToNode.size(); i < e; ++i){
        DominatorTreeNode *W = NumToNode[i];
        auto &WInfo = NodeToInfo[W];
        W->setIdom(WInfo.Idom);
    }
}


void DominatorTree::buildTree(YAL::Function *Parent) {

    //clear current dominator tre
    reset();
    ParentFunc = Parent;

    SemiNCAInfo SNCA(this);
    auto EntryBlock = Parent->getEntryBlock();

    if(!EntryBlock){
        // std::cerr << "Could not find the entry block of this function." << std::endl;
        return;
    }
    RootNode = new DominatorTreeNode(EntryBlock, nullptr);
    DominatorTreeNodes[EntryBlock] = RootNode;

    SNCA.runDFS(RootNode, 0);

    SNCA.runSemiNCA();


    SNCA.updateNodeInfo();



}