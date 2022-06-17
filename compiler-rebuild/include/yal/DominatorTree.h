#ifndef YAL_IR_DOMTREE_H
#define YAL_IR_DOMTREE_H

#include "BasicBlock.h"
#include "Type.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include "Instruction.h"
#include "Use.h"
#include <iterator>
#include "support.h"
#include "Function.h" 
#include <iostream>



namespace YAL{


    class DominatorTreeNode{
        //Basic Block this node points
        BasicBlock *BB;

        //The immediate dominator of this node
        DominatorTreeNode *Idom;

        //The children of this node
        std::vector< DominatorTreeNode *> Children;
    
        //The level of this node in the Dominator Tree
        unsigned Level;

        //The DFS number when walking in and out of this node
        mutable unsigned DFSNumIn = ~0;
        mutable unsigned DFSNumOut = ~0;



        public:


        DominatorTreeNode(BasicBlock *inputBB, DominatorTreeNode *idom){
            BB = inputBB;
            Idom = idom;
            Level = idom? idom->Level+1 : 0;
        }

        //===----------------------------------------------------------------------===//
        //                               Property Accessors                           //
        //===----------------------------------------------------------------------===//

        BasicBlock *getBlock() const {return BB;}
        DominatorTreeNode *getIdom() const {return Idom;}
        unsigned getLevel() const {return Level; }
        unsigned getDFSNumIn() const { return DFSNumIn; }
        unsigned getDFSNumOut() const { return DFSNumOut; }
        std::vector< DominatorTreeNode *> getChildren() {return Children; }

        bool isleaf() const { return Children.empty();}
        size_t getNumOfChildren() const {return Children.size(); }



        //===----------------------------------------------------------------------===//
        //                               Property Operators                           //
        //===----------------------------------------------------------------------===//

        void clearChildren(){ Children.clear(); }

         DominatorTreeNode *addChild( DominatorTreeNode *C){
            Children.push_back(C);
            return C;
        }
        
        void updateLevel(){
            assert(Idom);
            if (Level == Idom->Level + 1) return;
            std::vector< DominatorTreeNode *> workstack = {this};

            while(!workstack.empty()){
                DominatorTreeNode *Current = workstack.back();
                workstack.pop_back();
                Current->Level = Current->Idom->Level + 1;

                for( DominatorTreeNode *C: Current->Children){
                    assert(C->Idom);
                    if(C->Level != C->Idom->Level + 1) workstack.push_back(C);
                }
            }

        }

        //The return value indicates success or not
        bool setIdom( DominatorTreeNode *NewIdom){
            if (!NewIdom || NewIdom == Idom)
                return false;

            if(Idom){
                auto I = std::find(Idom->Children.begin(), Idom->Children.end(), this);
                if (I == Idom->Children.end()) return false;
                Idom->Children.erase(I);
            }
  
            Idom = NewIdom;
            NewIdom->Children.push_back(this);
            updateLevel();
            return true;
        }

        void setDFSNumIn(unsigned in){
            DFSNumIn = in;
        }

        void setDFSNumOut(unsigned out){
            DFSNumOut = out;
        }

        





    };

    class DominatorTree{
        std::map< BasicBlock *,  DominatorTreeNode *> DominatorTreeNodes;

         DominatorTreeNode * RootNode = nullptr;

        //Our dominator tree is not post-dominator, so it only have one root
         DominatorTreeNode * Root = nullptr;
        
        mutable bool DFSInfoValid = false;

        YAL::Function *ParentFunc;

        struct SemiNCAInfo{

            DominatorTree *Parent;

            struct InfoRec {
                unsigned DFSNum = 0;
                unsigned Parent = 0;
                unsigned Sdom = 0;
                std::vector< DominatorTreeNode *> ReverseChildren;
                 DominatorTreeNode *Idom = nullptr;
                 DominatorTreeNode *Label = nullptr;
            };

            std::vector< DominatorTreeNode *> NumToNode  = {nullptr};
            std::map< DominatorTreeNode*, InfoRec> NodeToInfo;

            SemiNCAInfo(DominatorTree *parent){
                Parent = parent;
            }

            unsigned runDFS(DominatorTreeNode* Node, unsigned LastNum);
            void runSemiNCA(unsigned MinLevel);
            DominatorTreeNode *eval(DominatorTreeNode *N, unsigned LastLinked, std::vector<InfoRec *> &stack);
            void updateNodeInfo();
        };






        public:
        
        DominatorTree() = default;
        explicit DominatorTree(Function *F) { buildTree(F); }


        //===----------------------------------------------------------------------===//
        //                               Property Accessors                           //
        //===----------------------------------------------------------------------===//

        //return the tree node of input basic block
        DominatorTreeNode *getNode(BasicBlock *basicblock) const{
            auto node = DominatorTreeNodes.find(basicblock);
            if (node != DominatorTreeNodes.end()){
                return node->second;
            }
            return nullptr;
        }

        DominatorTreeNode *getRootNode() {
            return RootNode;
        }

         DominatorTreeNode *getRoot() {
            return Root;
        }

        Function* getParent() {
            return ParentFunc;
        }

        //return if A dominates B
        bool dominates(DominatorTreeNode *A, DominatorTreeNode *B);
        bool dominates(BasicBlock *A, BasicBlock *B);

        bool dominates(Instruction *Def, Use &U);
        bool dominates(Instruction *Def, Instruction *User);
        bool dominates(Instruction *Def, BasicBlock *UseBB);


        bool isReachableFromEntry(BasicBlock *basicblock) const {
            return isReachableFromEntry(getNode(basicblock));
        }

        bool isReachableFromEntry(DominatorTreeNode *node) const {
            if (node) return true;
            return false;
        }

        bool isReachableFromEntry(Use &U) const;

        void genDFSNums();

        void printTree();
 

        //===----------------------------------------------------------------------===//
        //                               Tree Builder                                 //
        //===----------------------------------------------------------------------===//

        void buildTree(YAL::Function *F);
        void reset();

        








    };
}

#endif