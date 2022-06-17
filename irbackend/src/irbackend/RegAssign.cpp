#include "RegAssign.h"
#include "BasicBlock.h"
#include "Function.h"
#include "Instructions.h"
#include "DominatorTree.h"
#include <algorithm>
#include <stack>

using namespace YAL;

HazardGraph::HazardGraph(Function &F) : VertexNum(F.getMaxLabel()) {
  // 分配内存空间
  std::cout << "*** Allocate space ***" << std::endl;
  std::cout << "  MaxLabel: " << VertexNum << std::endl;
  Graph = new int *[VertexNum];
  for (int i = 0; i < VertexNum; i++)
    Graph[i] = new int[VertexNum];
  for (int i = 0; i < VertexNum; i++)
    for (int j = 0; j < VertexNum; j++)
      Graph[i][j] = 0;

  // 建立顶点
  std::cout << "*** Build Node ***" << std::endl;
  int idx = 0;
  auto arg = F.Arg_begin();
  for (idx = 0; idx < F.Arg_size(); idx++) {
    (*arg)->idx = idx;
    (*arg)->size = 0;
    if (idx <= 3)
      (*arg)->Color = r0 + idx;
    else
      (*arg)->Color = -1;
    Vertexes.push_back(*arg);
  }
  for (BasicBlock *BB : F.getBasicBlockList()) {
    for (Instruction *I : BB->getInstList()) {
      unsigned op = I->getOpcode();
      if (op != Instruction::Ret && op != Instruction::Br && op != Instruction::Store
          && op != Instruction::GetElementPtr, op != Instruction::Alloca) {
        I->idx = idx;
        I->size = 0;
        I->Color = -1;
        Vertexes.push_back(I);
        idx++;
        // 函数传参的寄存器为r0-r3
        if (op == Instruction::Call)
          for (int k = 0; k < I->getNumOperands(); k++) {
            if (k <= 3) {
              I->getNumOperand(k)->Color = r0 + k;
            }
          }

      }
    }
  }

  // 建立边的关系
  // 对于每个BB中定义的I0，对于另一个指令I1（不一定在BB中定义），它们之间在满足
  // 如下情况时才会有边：
  //   1. I1在入口处活跃且I1在出口处活跃
  //   2. I1在入口处活跃且I1在出口处不活跃，而且I1的引用在I0的定值之后
  //   3. I1在BB中定义且在出口处不活跃，它的生命周期和I0有重叠，如I0生命周期为
  //      [0, 5)，I1生命周期为[3, 7)，其中的数字为Order
  //   4. I1在BB中定义且在出口处活跃，而且I1的定值在I0的生命周期结束之前
  // 为了解决这个问题可以进行如下的完整的生命周期的定义：
  //   1. 对于每个BB，设IN_list∪def_list = L，指令数目为n
  //   2. 对于每个I∈L，若I∈IN_list，则有：
  //      (1). 若I∈OUT_list，则它的生命周期为[0, n+1]
  //      (2). 若!I∈OUT_list，则它的生命周期为[0, m)其中m为它在BB中的最后一次
  //           引用
  //   3. 对于每个I∈L，若I∈def_list，设它的定值在p, 则有：
  //      (1). 若I∈OUT_list，则它的生命周期为[p, n+1]
  //      (2). 若!I∈OUT_list，则它的生命周期为[p, m)其中m为它在BB中的最后一次
  //           引用
  //   4. 对于每个BB，只计算在BB中定值的指令和L中的指令的冲突关系，即：当且仅当
  //      指令I0在BB中定值的地方指令I1活跃，I0和I1之间连边
  //   5. PHI节点的操作数的生命周期至少要从它的定值到它所在基本块的末尾
  // 如此一来，对于生命周期有重叠的指令，在他们之间连边。
  std::cout << "*** Build Edge ***" << std::endl;
  for (BasicBlock *BB : F.getBasicBlockList()) {
    std::cout << ">> BB:" << BB->getName() << std::endl;
    int BBOrder = BB->Order;
    std::map<unsigned, Value *> L;
    for (auto item : BB->def_list)
      L.insert(item);
    for (auto item : BB->IN_list)
      L.insert(item);
    
    for (auto itemi : BB->def_list) {
      unsigned i = itemi.second->idx;
      auto infoI = itemi.second->getVarInfo();
      for (auto itemj : L) {
        if (itemi == itemj)
          continue;
        unsigned j = itemj.second->idx;
        auto infoJ = itemj.second->getVarInfo();
        if (infoJ.start[BBOrder] <= infoI.start[BBOrder] < infoJ.killer[BBOrder]) {
          std::cout << "  add edge (" << i << ", " << j << ")" << std::endl;
          addEdge(itemi.second, itemj.second);
        }
      }
    }
  }

  for (int i = 0; i < VertexNum; i++) {
    for (int j = 0; j < VertexNum; j++)
      std::cout << Graph[i][j] << " ";
    std::cout << std::endl;
  }
}

RegAssign::RegAssign(Function &F, LiveVars *LV, DominatorTree *DT) 
    : F(F), HG(F), Nodes(HG.Vertexes), LV(LV), DT(DT) {
  // LV->runOnFunction(F);
}

void RegAssign::calLoopDepth() {
  std::cout << "*** runcalLoopDepth ***" << std::endl;
  std::map<unsigned, BasicBlock*> Loop_set;
  std::stack<BasicBlock*> S;
  for (auto BB : F.getBasicBlockList()) {
    for (auto succ : BB->getSuccList()) {
      if (DT->dominates(succ, BB)) {
        std::cout << ">>> find loop >>>" << std::endl;
        std::cout << "  succ:" << succ->getName() << " BB: " << BB->getName() << std::endl;
        // 初始化loop_set和stack
        Loop_set.clear();
        Loop_set.insert({BB->Order, BB});
        Loop_set.insert({succ->Order, succ});
        S.push(BB);

        while(!S.empty()) {
          BasicBlock *p = S.top();
          S.pop();
          for (auto q : p->getPredList()) {
            if (Loop_set.find(q->Order) == Loop_set.end()) {
              Loop_set.insert({q->Order, q});
              S.push(q);
            }
          }
        }
        std::cout << "-- loop_set: --" << std::endl;
        for (auto item : Loop_set) {
          std::cout << "  " << item.second->getName() << std::endl;
          item.second->LoopDepth ++;
        }
      }
    }
  }
  
}

int cmp(const void *a, const void *b) {
  Value *V1 = (Value*)a;
  Value *V2 = (Value*)b;
  return V1->size < V2->size;
}

void RegAssign::runColoring() {
  calLoopDepth();
  std::cout << "*** runColoring ***" << std::endl;
  std::stack<Value *> LI_list;
  int size = Nodes.size();
  
  // 每次循环从图中删除掉一个度数小于k的节点，并且将它插入到一个链表中去，直到所有
  // 节点都被删除或者所有节点的度数都大于k为止。
  //   1. 对于第一种情况，该冲突图可以着色，只需要按照删除节点的逆序进行着色就可以
  //      找到一种着色方案
  //   2. 对于第二种情况，可以从所有节点中删除一个溢出代价最小的节点插入到列表中，
  //      随后重新返回去删除图中度数小于k的节点
  //   3. 重复这种操作直到所有节点都被删除
  //   4. 按照删除的逆序进行着色，找不到着色方案的节点需要溢出到存储器中。
  while (true) {
    // 找到当前度数最小的点，若度数小于13则删除
    for (int i = 0; i < size; i++) {
      auto temp = Nodes.front();
      for (auto item : Nodes) {
        if (item->size < 13) {
          temp = item;
          break;
        }
      }
      // std::cout << "Analyze Node: " << Nodes[0]->FOrder << " ";
      // std::cout << "adjs.size: " << Nodes[0]->adjs.size() << std::endl;
      if (temp->adjs.size() < 13) {
        LI_list.push(temp);
        std::cout << "push " << temp->FOrder << " to LI_list" << std::endl;
        eraseFromGraph(temp);
      } else
        break;
    }

    if (Nodes.empty()) {
      std::list<LoadInst *> LD_list;
      // 此时着色问题可解，找到着色方案，退出循环
      while (!LI_list.empty()) {
        Value *I = LI_list.top();
        std::cout << "Instruction: " << I->FOrder << " size: " << I->adjs.size() << " ";
        int color = HG.getColor(I);
        if (color == -1) {
          // 此时需要溢出
          // 1. 溢出时需要考虑，将变量存到内容中，在它的每次use之进行load
          // 2. 对于产生的load指令，只需要将它和它的user赋值为同一个寄存器即可
          // 3. 更改user的use为新增加的load
          std::cout << "spill reg: " << I->FOrder << std::endl;
          if (auto *Inst = cast<Instruction>(I)) {
            // 如果是一条指令，在他的def之后创建alloca和store
            auto t = std::find(Inst->getParent()->getInstList().begin(), Inst->getParent()->getInstList().end(), Inst);
            assert(t != Inst->getParent()->getInstList().end() && "can't find this spill inst in its parent");
            t++;

            AllocaInst *AI;
            if (auto AT = cast<ArrayType>(Inst->getType()))
              AI = AllocaInst::Create(AT, ConstantInt::get(AT->getContext(), AT->getElementNum()), "", (*t));
            else
              AI = AllocaInst::Create(I->getType(), nullptr, "", (*t));
            
            for (auto item = Inst->user_begin(); item != Inst->user_end(); item++) {
              auto LD = LoadInst::Create(Inst->getType(), AI, "", cast<Instruction>(*item));
              LD_list.push_back(LD);
              for (int k = 0; k < item->getNumOperands(); k++) {
                Value *V = item->getNumOperand(k).get();
                if (V == Inst)
                  item->getNumOperand(k) == LD;
              }
            }

            auto ST = StoreInst::Create(Inst, AI, (*t));
          } else if (auto *Arg = cast<Argument>(I)) {
            // 如果是一个参数，在函数的开始将它store下来
            Instruction *First = (*(*F.BB_begin())->begin());
            AllocaInst *AI = AllocaInst::Create(I->getType(), nullptr, "", First);
            
            for (auto item = Arg->user_begin(); item != Arg->user_end(); item++) {
              auto LD = LoadInst::Create(Inst->getType(), AI, "", cast<Instruction>(*item));
              LD_list.push_back(LD);
              for (int k = 0; k < item->getNumOperands(); k++) {
                Value *V = item->getNumOperand(k).get();
                if (V == Inst)
                  item->getNumOperand(k) == LD;
              }
            }

            auto ST = StoreInst::Create(Arg, AI, First);
          } else 
            assert("Wrong Var Type!");
        }
        // assert(0 <= color < 13 && "getColor failed");
        I->Color = color;
        std::cout << " Color: " << color << std::endl;
        LI_list.pop();
      }

      // 给增加的Load指令分配寄存器
      for (auto item : LD_list) {
        auto U = item->user_begin();
        item->Color = U->Color;
      }
      LD_list.clear();
      break;
    }
    else {
      int min = 10;
      int min_idx = 0;
      for (int k = 0; k < Nodes.size(); k++) {
        if (Nodes[k]->LoopDepth < min) {
          min = Nodes[k]->LoopDepth;
          min_idx = k;
        }
      }
      std::cout << "delete Nodes[k]: " << Nodes[min_idx]->FOrder << std::endl;
      LI_list.push(Nodes[min_idx]);
      eraseFromGraph(Nodes[min_idx]);
    }
  }
}