#include "CSE.h"
#include "Instructions.h"
#include "support.h"
#include "Deadcode.h"
#include "PropConstant.h"

int CSEElim=0;
int CSELdElim=0;
int CSELdStElim=0;
int CSERStElim=0;
int total_deleted_instr=0;

using namespace YAL;

void CSE_Basic_processing(BasicBlock* BB, Instruction* I, bool flag, DominatorTree& DT)
{
    // std::cout << " BB: " << BB->getName() << " I: " << I->FOrder << " " << I->getOpcodeName() << " flag: " << flag << std::endl;
    if(( isa<LoadInst>(I) || isa<StoreInst>(I) || I->isTerminator() || isa<AllocaInst>(I) || isa<BranchInst>(I))){
        return;
    }
    else{
        if (auto CI = cast<CallInst>(I)){
            auto called_func = cast<Function>(CI->getCalledValue());
            assert(called_func && "called function is nullptr");
            if(called_func->hasSideEffect() || called_func->isDeclaration()){
                // std::cout << "this called function " << called_func->getName() << " has side effect. " << std::endl;
                return;
            }  
        }
        if(flag==1){
            auto curBB = DT.getNode(BB);
            if(!curBB)
                return;
            assert(curBB && "Current BB is nullptr in Dominator Tree");
            auto child_of_curBB = curBB->getChildren();
            for (auto childBB = child_of_curBB.begin();childBB != child_of_curBB.end(); childBB++){
                std::set<Instruction*> worklist;
                // std::cout << "line 38 " << std::endl;
                for(auto i : (*childBB)->getBlock()->getInstList()){
                    if(I->isIdenticalto(i)){
                        CSEElim++;
                        total_deleted_instr++;
                        // std::cout << "line 43 " << std::endl;
                        (i)->replaceAllUsesWith(I);
                        // std::cout << "line 45 " << std::endl;
                        worklist.insert(i);
                    }
                }
                // std::cout << "line 47 " << std::endl;
                while(!worklist.empty()) {
                    Instruction *inst = *(worklist.begin());
                    worklist.erase(inst);
                    inst->eraseFromParent(); 
                }
                CSE_Basic_processing((*childBB)->getBlock(),I, 1, DT);
            }
        }
        else{
            Instruction* next_instr = I->getNextNonDebugInstruction();
            if(next_instr == nullptr){
                return;
            }
            std::set<Instruction*> worklist;
            while(next_instr != nullptr){
                if(I->isIdenticalto(next_instr)){
                    CSEElim++;
                    total_deleted_instr++;
                    next_instr->replaceAllUsesWith(I);
                    worklist.insert(next_instr);
                }
                next_instr = next_instr->getNextNonDebugInstruction();
            }
            while(worklist.size()>0) {
                // Get the first item 
                Instruction *inst = *(worklist.begin());
                // Erase it from worklist
                worklist.erase(inst);
                inst->eraseFromParent(); 
            }
            CSE_Basic_processing(&*BB,&*I,1,DT);
        }
    }
}

void CSE_Basic_Pass(Function* F, DominatorTree& DT){
    for(auto bb = F->getBasicBlockList().begin();bb!= F->getBasicBlockList().end(); bb++){
        for(auto i = (*bb)->begin(); i != (*bb)->end();i++){
            CSE_Basic_processing(*bb, *i, 0, DT);
        }
    }
}


bool Load_Elim_processing(Instruction* L, Instruction* R)
{
    LoadInst *li = cast<LoadInst>(R);
    if((li != NULL) && (L->getType() == R->getType()) && (((LoadInst*)L)->getPointerOperand() == ((LoadInst*)R)->getPointerOperand())){
        return true;
    }
    else{
      return false;
    }       
}

void LoadElim_Pass(Function* F){
    std::set<Instruction*> worklist;
    for(auto bb = F->getBasicBlockList().begin();bb!= F->getBasicBlockList().end(); bb++){
        for(auto i = (*bb)->begin(); i != (*bb)->end();i++){
            Instruction* next_instr = (*i)->getNextNonDebugInstruction();
            if(isa<LoadInst>(*i)){
                while(next_instr != NULL){
                    auto this_i = cast<LoadInst>(*i);
                    auto this_i_ptr = this_i->getNumOperand(0).get();
                    if(isa<AllocaInst>(this_i_ptr)){
                        if(auto SI = cast<StoreInst>(next_instr)){
                            auto SI_addr = SI->getNumOperand(1).get();
                            if(this_i_ptr == SI_addr)
                                break;
                        }   
                    }
                    else if(isa<GetElementPtrInst>(this_i_ptr)){
                        auto gep_addr = cast<GetElementPtrInst>(this_i_ptr)->getNumOperand(0).get();
                        auto CI = cast<CallInst>(next_instr);
                        auto SI = cast<StoreInst>(next_instr);
                        if(CI && CI->hasSideEffect(gep_addr)){
                            break;
                        }
                        else if(SI){
                            if(auto SI_addr = cast<GetElementPtrInst>(SI->getNumOperand(1).get())){
                                if(SI_addr->hasSamePtr(cast<GetElementPtrInst>(this_i_ptr))){
                                    break;
                                }
                            }
                        }  
                    }
                    else if(isa<GlobalVariable>(this_i_ptr)){
                        auto CI = cast<CallInst>(next_instr);
                        if(CI && CI->hasSideEffect(next_instr)){
                            break;
                        }
                        else if(auto SI = cast<StoreInst>(next_instr)){
                            auto SI_addr = SI->getNumOperand(1).get();
                            if(this_i_ptr == SI_addr)
                                break;
                        }
                    }
                    else{
                        if(auto SI = cast<StoreInst>(next_instr)){
                            auto SI_addr = SI->getNumOperand(1).get();
                            if(this_i_ptr == SI_addr)
                                break;
                        } 
                        std::cout << "Unexpected load inst's operand." << std::endl;
                    }
                    if(Load_Elim_processing(*i,next_instr)){
                        CSELdElim++;
                        total_deleted_instr++;
                        next_instr->replaceAllUsesWith(*i);
                        worklist.insert(next_instr);
                    }
                    next_instr = next_instr->getNextNonDebugInstruction();
                    while(worklist.size()>0) {
                        Instruction *inst = *(worklist.begin());
                        worklist.erase(inst);
                        inst->eraseFromParent(); 
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////LOAD-STORE ELIMINATION///////////////////////////////////////////////////////////////////////////////////////////////////////////
void LdSt_Elim(Function* F){
    for(auto bb = F->getBasicBlockList().begin();bb!= F->getBasicBlockList().end(); bb++){
        for(auto i = (*bb)->begin(); i != (*bb)->end();i++){
            if(isa<StoreInst>(*i)){
                auto next_instr=i;
                for(++next_instr;next_instr!=(*bb)->end();){            
                    if((isa<LoadInst>(*next_instr)) && (*i)->getNumOperand(0)->getType() == (*next_instr)->getType() && (*i)->getNumOperand(1) == (*next_instr)->getNumOperand(0)){
                        CSELdStElim++;
                        total_deleted_instr++;
                        (*next_instr)->replaceAllUsesWith((*i)->getNumOperand(0));
                        auto temp = next_instr++;
                        (*temp)->eraseFromParent();
                    }
                    else if((isa<StoreInst>(*next_instr)) && ((*i)->getNumOperand(0)->getType() == (*next_instr)->getNumOperand(0)->getType()) && (*i)->getNumOperand(1) == (*next_instr)->getNumOperand(1))
                    {
                        CSERStElim++;
                        total_deleted_instr++;
                        auto temp = i++;
                        (*temp)->eraseFromParent();
                    }
                    if(isa<StoreInst>(*next_instr) || isa<LoadInst>(*next_instr) || isa<CallInst>(*next_instr)){
                        break;
                    }
                    else{
                        next_instr++;              
                    }     
                }
            }
        }
    }
}

namespace YAL{

    void CommonSubexpressionElimination(Function* F, DominatorTree& DT){

        DeadcodeEliminator deadcode = DeadcodeEliminator();
        deadcode.run(F);
        PropConstant PC;
        PC.runOnFunction(*F);

        CSE_Basic_Pass(F, DT);
        LoadElim_Pass(F);
        LdSt_Elim(F);
        // 评估优化效果
        // std::cout << " ------------------- " << F->getName() << " ---------------------- " << std::endl;
        // std::cout << "CSE_Basic : "<< CSEElim << std::endl;
        // std::cout << "CSELdElim : "<< CSELdElim << std::endl;
        // std::cout << "CSERStElim : "<< CSERStElim << std::endl;
        // std::cout << "CSELdStElim : "<< CSELdStElim << std::endl;
        // std::cout << "total_deleted_instr first loop: "<< total_deleted_instr << std::endl;

        DeadcodeEliminator deadcode1 = DeadcodeEliminator();
        deadcode1.run(F);
        PropConstant PC1;
        PC1.runOnFunction(*F);

        CSE_Basic_Pass(F, DT);
        // std::cout << "CSE_Basic : "<< CSEElim << std::endl;
        // std::cout << "CSELdElim : "<< CSELdElim << std::endl;
        // std::cout << "CSERStElim : "<< CSERStElim << std::endl;
        // std::cout << "CSELdStElim : "<< CSELdStElim << std::endl;
        // std::cout << "total_deleted_instr second loop : "<< total_deleted_instr << std::endl;
    }
}