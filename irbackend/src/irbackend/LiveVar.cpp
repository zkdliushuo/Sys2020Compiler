#include "LiveVar.h"
#include "Function.h"
#include "Instructions.h"
#include <cassert>

using namespace YAL;

int time1 = 0;

void DFS_VISIT(std::list<BasicBlock *> &BBList, BasicBlock *BB) {
  time1++;
  BB->visited = true;
  for (auto succ : BB->getSuccList()) {
    if (!succ->visited)
      DFS_VISIT(BBList, succ);
  }
  BB->finish_time = ++time1;
}

void DFS(Function &F) {
  auto BBList = F.getBasicBlockList();
  for (auto BB : BBList) {
    BB->visited = false;
    BB->finish_time = 0;
  }
  time1 = 0;
  for (auto b : BBList) {
    if (!b->visited)
      DFS_VISIT(BBList, b);
  }
}

struct classCompare {
  bool operator()(const BasicBlock *lhs, const BasicBlock *rhs) { return lhs->finish_time < rhs->finish_time; }
};

// int cmp(const void *a, const void *b) {
//   BasicBlock *V1 = (BasicBlock*)a;
//   BasicBlock *V2 = (BasicBlock*)b;
//   return V1->finish_time < V2->finish_time;
// }

bool LiveVars::runOnFunction(Function &F) {
  std::cout << "LiveVars::runOnFunction" << std::endl;
  // 深度优先排序，找到活跃变量分析的顺序
  F.setBlockOrder();
  std::cout << "setBlockOrder OK" << std::endl;
  DFS(F);
  std::cout << "DFS OK" << std::endl;
  std::set<BasicBlock *, classCompare> DFS_BB;
  for (BasicBlock *BB : F.getBasicBlockList()) {
    BB->init_usedef();
    DFS_BB.insert(BB);
  }
  // F.getBasicBlockList().sort(classCompare());
  // std::sort(F.getBasicBlockList().begin(), F.getBasicBlockList().end(), cmp);
  // for (auto BB : F.getBasicBlockList())
  //   std::cout << BB->getName() << ": " << BB->finish_time << std::endl;
  std::cout << "init_usedef OK" << std::endl;

  // 活跃变量分析
  bool hasChanged = true;
  while (hasChanged) {
    hasChanged = false;
    for (auto curBB : DFS_BB) {
      std::map<unsigned, Value *> temp, temp2;
      temp.clear();
      temp2.clear();
      // IN[B] = use[B] ∪ (OUT[B] - def[B])
      for (auto item : curBB->OUT_list) {
        if (curBB->def_list.find(item.first) == curBB->def_list.end())
          temp.insert(item);
      }
      // for (auto I : temp) {
      //   std::cout <<"(OUT[B] - def[B]) Instruction:" << I.second->getName() << std::endl;
      // }

      temp2 = curBB->use_list;
      for (auto item : temp)
        temp2.insert(item);
      // for (auto I : temp2) {
      //   std::cout <<"use[B] ∪ (OUT[B] - def[B]) Instruction:" << I.second->getName() << std::endl;
      // }

      // 计算temp2和IN的差集，如果没有变化temp为空
      bool IN_DIFF = false;
      for (auto item : temp2) {
        if (curBB->IN_list.find(item.first) == curBB->IN_list.end()) {
          IN_DIFF = true;
          break;
        }
      }
      if (IN_DIFF) {
        hasChanged = true;
        curBB->IN_list.clear();
        for (auto item : temp2) {
          curBB->IN_list.insert(item);
        }
      }

      // OUT[B] = ∪_{Succ}IN[S]
      curBB->OUT_list.clear();
      for (auto succBB : curBB->getSuccList()) {
        for (auto item : succBB->IN_list)
          curBB->OUT_list.insert(item);
      }
    }
  }
  for (auto BB : F.getBasicBlockList()) {
    std::cout << "BB: " << BB->getName() << std::endl;
    std::cout << "  use_list" << std::endl;
    for (auto item : BB->use_list) {
      std::cout << "  " << item.first << " " << isa<Instruction>(item.second) << std::endl;
    }
    std::cout << "  def_list" << std::endl;
    for (auto item : BB->def_list) {
      std::cout << "  " << item.first << " " << isa<Instruction>(item.second) << std::endl;
    }
    std::cout << "  IN_list" << std::endl;
    for (auto item : BB->IN_list) {
      std::cout << "  " << item.first << " " << isa<Instruction>(item.second) << std::endl;
    }
    std::cout << "  OUT_list" << std::endl;
    for (auto item : BB->OUT_list) {
      std::cout << "  " << item.first << " " << isa<Instruction>(item.second) << std::endl;
    }
  }

  for (BasicBlock *BB : F.getBasicBlockList()) {
    CalLiveInterval(BB);
  }
  return true;
}

void LiveVars::CalLiveInterval(BasicBlock *BB) {
  unsigned n = BB->getInstList().size();
  unsigned BBOrder = BB->Order;
  std::cout << ">>>>>>>>>> Analyze BB: " << BB->getName() << " " << BB->getInstList().size() << " >>>>>>>>>>" << std::endl;

  for (auto item : BB->IN_list) {
    if (Instruction *I = cast<Instruction>(item.second)) {
      std::cout << "IN_list Instruction: " << I->FOrder << std::endl;
      I->addAiveBlock(BB);
      if (BB->OUT_list.find(item.first) != BB->OUT_list.end()) {
        I->setKiller(BB);
        I->setStart(BB, 0);
      } else {
        // 此时在BasicBlock::init_usedef中已经定义好了
        auto info = I->getVarInfo();
        assert(info.killer.find(BB->Order) != info.killer.end() && "init_usedef didn't find a killer");
      }
      auto infoI = I->getVarInfo();
      std::cout << "--Interval: [" << infoI.start[BBOrder] << ", " << infoI.killer[BBOrder] << ")" << std::endl;
    } else if (Argument *Arg = cast<Argument>(item.second)) {
      std::cout << "IN_list Argument: " << Arg->FOrder << std::endl;
      Arg->addAiveBlock(BB);
      if (BB->OUT_list.find(item.first) != BB->OUT_list.end()) {
        Arg->setKiller(BB);
        Arg->setStart(BB, 0);
      } else {
        // 此时在BasicBlock::init_usedef中已经定义好了
        auto info = Arg->getVarInfo();
        assert(info.killer.find(BB->Order) != info.killer.end() && "init_usedef didn't find a killer");
      }
      auto infoI = Arg->getVarInfo();
      std::cout << "--Interval: [" << infoI.start[BBOrder] << ", " << infoI.killer[BBOrder] << ")" << std::endl;
    }
  }

  for (auto item : BB->def_list) {
    Instruction *I = cast<Instruction>(item.second);
    std::cout << "def_list Instruction: " << I->FOrder << std::endl;
    I->addAiveBlock(BB);
    I->setStart(BB, I->Order + 1);
    if (BB->OUT_list.find(item.first) != BB->OUT_list.end()) {
      I->setKiller(BB);
    } else {
      // PHI节点需要至少活跃到基本块的末尾
      bool isPHIOperand = false;
      for (auto u = I->user_begin(); u != I->user_end(); u++)
        if (isa<PHINode>(*u)) {
          isPHIOperand = true;
          break;
        }
      
      if (isPHIOperand) {
        auto beforeTerminator = BB->end();
        beforeTerminator--;
        I->setKiller(*beforeTerminator);
      } else {
        bool isPHIOperand = false;
        for (auto u = I->user_begin(); u != I->user_end(); u++)
          if (isa<PHINode>(*u)) {
            isPHIOperand = true;
            break;
          }
        if (isPHIOperand) {
          auto beforeTerminator = BB->end();
          beforeTerminator--;
          I->setKiller(*beforeTerminator);
        } else {
          // 此时在BasicBlock::init_usedef中已经定义好了
          auto info = I->getVarInfo();
          if (info.killer.find(BB->Order) == info.killer.end()) {
            std::cout << "Can't find a killer" << std::endl;
            I->setKiller(I);
          }
        }
      }
      // assert(info.killer.find(BB->Order) != info.killer.end() && "init_usedef didn't find a killer");
    }
    auto infoI = I->getVarInfo();
    std::cout << "--Interval: [" << infoI.start[BBOrder] << ", " << infoI.killer[BBOrder] << ")" << std::endl;
  }
}