#include "LiveVar.h"
#include "Function.h"
#include "Instructions.h"
#include <cassert>
// #define DEBUG

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
  bool operator()(const BasicBlock *lhs, const BasicBlock *rhs) const { return lhs->finish_time < rhs->finish_time; }
};

// int cmp(const void *a, const void *b) {
//   BasicBlock *V1 = (BasicBlock*)a;
//   BasicBlock *V2 = (BasicBlock*)b;
//   return V1->finish_time < V2->finish_time;
// }

bool LiveVars::runOnFunction(Function &F) {
  // std::cout << "LiveVars::runOnFunction" << std::endl;
  // 深度优先排序，找到活跃变量分析的顺序
  DFS(F);
  // std::cout << "DFS OK" << std::endl;
  std::set<BasicBlock *, classCompare> DFS_BB;
  for (BasicBlock *BB : F.getBasicBlockList()) {
    BB->init_def();
    DFS_BB.insert(BB);
  }

  for (auto *BB : F.getBasicBlockList())
    BB->init_use();

  // 活跃变量分析
  bool hasChanged = true;
  while (hasChanged) {
    hasChanged = false;
    for (auto curBB : DFS_BB) {
      // OUT[B] = ∪_{Succ}IN[S]
      curBB->OUT_list.clear();
      for (auto succBB : curBB->getSuccList()) {
        for (auto item : succBB->IN_list)
          curBB->OUT_list.insert(item);
      }

      std::map<unsigned, Value *> temp, temp2;
      temp.clear();
      temp2.clear();
      // IN[B] = use[B] ∪ (OUT[B] - def[B])
      // temp = (OUT[B] - def[B])
      for (auto item : curBB->OUT_list) {
        if (!curBB->def_list.count(item.first))
          temp.insert(item);
      }

      // temp2 = use[B] ∪ (OUT[B] - def[B])
      temp2 = curBB->use_list;
      for (auto item : temp)
        temp2.insert(item);

      // 计算temp2和IN的差集，如果没有变化temp为空
      bool IN_DIFF = false;
      for (auto item : temp2) {
        if (!curBB->IN_list.count(item.first)) {
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

    }
  }

  #ifdef DEBUG
  for (auto BB : F.getBasicBlockList()) {
    std::cout << "BB: " << BB->getName() << std::endl;
    std::cout << "  use_list" << std::endl;
    for (auto item : BB->use_list) {
      std::cout << "  " << item.first << " " << isa<Argument>(item.second) << std::endl;
    }
    std::cout << "  def_list" << std::endl;
    for (auto item : BB->def_list) {
      std::cout << "  " << item.first << " " << isa<Argument>(item.second) << std::endl;
    }
    std::cout << "  IN_list" << std::endl;
    for (auto item : BB->IN_list) {
      std::cout << "  " << item.first << " " << isa<Argument>(item.second) << std::endl;
    }
    std::cout << "  OUT_list" << std::endl;
    for (auto item : BB->OUT_list) {
      std::cout << "  " << item.first << " " << isa<Argument>(item.second) << std::endl;
    }
  }
  #endif

  for (BasicBlock *BB : F.getBasicBlockList())
    CalLiveInterval(BB);
  return true;
}

void LiveVars::CalLiveInterval(BasicBlock *BB) {
  #ifdef DEBUG
  std::cout << "*** LiveVars::CalLiveInterval BB: " << BB->getName() << " Order: " << BB->Order << "***" << std::endl;
  #endif
  unsigned n = BB->getInstList().size();
  unsigned BBOrder = BB->Order;

  for (auto item : BB->IN_list) {
    if (Instruction *I = cast<Instruction>(item.second)) {
      #ifdef DEBUG
      std::cout << "  IN_list Instruction: " << I->FOrder << " Order: " << I->Order << std::endl;
      #endif
      I->addAiveBlock(BB);
      I->setStart(BB, 0);
      if (BB->OUT_list.find(item.first) != BB->OUT_list.end()) {
        I->setKiller(BB);
      } else {
        // 此时在BasicBlock::init_usedef中已经定义好了
        auto info = I->getVarInfo();
        assert(info.killer.find(BB->Order) != info.killer.end() && "init_usedef didn't find a killer");
      }
      auto infoI = I->getVarInfo();
      #ifdef DEBUG
      std::cout << "   -Interval: [" << infoI.start[BBOrder] << ", " << infoI.killer[BBOrder] << ")" << std::endl;
      #endif
    } else if (Argument *Arg = cast<Argument>(item.second)) {
      #ifdef DEBUG
      std::cout << "  IN_list Argument: " << Arg->FOrder << std::endl;
      #endif
      Arg->addAiveBlock(BB);
      if (BB->OUT_list.find(item.first) != BB->OUT_list.end()) {
        Arg->setKiller(BB);
        Arg->setStart(BB, 0);
      }
      auto infoI = Arg->getVarInfo();
      #ifdef DEBUG
      std::cout << "   -Interval: [" << infoI.start[BBOrder] << ", " << infoI.killer[BBOrder] << ")" << std::endl;
      #endif
    }
  }

  for (auto item : BB->def_list) {
    Instruction *I = cast<Instruction>(item.second);
    #ifdef DEBUG
    std::cout << "  def_list Instruction: " << I->FOrder << " Order " << I->Order << std::endl;
    #endif
    I->addAiveBlock(BB);
    if (auto phi = cast<PHINode>(I)) {
      // phi->setStart(BB, BB->getTerminator()->Order);
      // phi->setKiller(BB->getTerminator());
      for (int k = 0; k < phi->getNumOperands(); k++) {
        auto bb = phi->getIncomingBlock(k);
        if (!bb->IN_list.count(phi->FOrder))
          bb->def_list.insert({phi->FOrder, phi});
        phi->addAiveBlock(bb);
        phi->setStart(bb, bb->getTerminator()->Order);
        phi->setKiller(bb->getTerminator());
        // std::cout << " >> set phi: " << phi->FOrder << " start at " << bb->getName() << " : " << bb->getTerminator()->Order << std::endl;
      }
    }
    else
      I->setStart(BB, I->Order + 1);
    if (BB->OUT_list.find(item.first) != BB->OUT_list.end()) {
      I->setKiller(BB);
    }
    auto infoI = I->getVarInfo();
    #ifdef DEBUG
    std::cout << "   -Interval: [" << infoI.start[BBOrder] << ", " << infoI.killer[BBOrder] << ")" << std::endl;
    #endif
  }
}