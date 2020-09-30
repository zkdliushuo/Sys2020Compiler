#include "RegAssign.h"
#include "BasicBlock.h"
#include "Function.h"
#include "Instructions.h"
#include "DominatorTree.h"
#include "GlobalVariable.h"
#include <algorithm>
#include <stack>
#include <math.h>
#define RegNum 11
// #define DEBUG

using namespace YAL;

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
HazardGraph::HazardGraph(Function &F) : VertexNum(F.getMaxLabel()) {
  // 分配内存空间
  Vertexes.clear();
  Graph = new int *[VertexNum];
  for (int i = 0; i < VertexNum; i++)
    Graph[i] = new int[VertexNum];
  for (int i = 0; i < VertexNum; i++)
    for (int j = 0; j < VertexNum; j++)
      Graph[i][j] = 0;

  // 建立顶点
  int idx = 0;
  auto arg = F.Arg_begin();
  for (int i = 0; i < F.Arg_size() && i < 4; i++) {
    // std::cout << "  arg: " << (*arg)->FOrder << " weight: " << (*arg)->weight << std::endl;
    // if (idx <= 3)
    //   (*arg)->Color = r0 + idx;
    // else
    if ((*arg)->hasRegAllocated() && !(*arg)->isSpilled) {
      (*arg)->Color = -1;
      (*arg)->adjs.clear();
      (*arg)->idx = idx;
      (*arg)->size = 0;
      Vertexes.push_back(*arg);
      idx++;
    }
    else if ((*arg)->isSpilled) (*arg)->Color = (*arg)->getArgNo() + 7;
    else (*arg)->Color = -1;
    arg++;
  }
  for (BasicBlock *BB : F.getBasicBlockList()) {
    for (Instruction *I : BB->getInstList()) {
      if (I->hasRegAllocated() && !I->isSpilled) {
        I->adjs.clear();
        I->idx = idx;
        I->size = 0;
        I->Color = -1;
        Vertexes.push_back(I);
        idx++;
        // std::cout << "  instruction: " << I->FOrder << " weight: " << I->weight << std::endl;
      }
      else if (I->isSpilled) {
        if (auto LD = cast<LoadInst>(I)) {
          LD->Color = 11;
          if (LD->LoadUser){
            auto U = cast<Instruction>(LD->LoadUser);
            assert(U && "user should be an instruction");
            if (!isa<CallInst>(U)) {
              for (int k = 0; k < U->getNumOperands(); k++) {
                auto op = U->getNumOperand(k).get();
                if (op != LD && op->Color == 11) {
                  LD->Color = 12;
                }
              }
            }
          }
        }
        else I->Color = 11;
      }
      else I->Color = -1;
      if (I->SpilledAndUsedByCall) I->Color = 11;
    }
  }

  auto argi = F.Arg_begin();
  for (int i = 0; i < F.Arg_size() && i < 4; i++, argi++) {
    if ((*argi)->isSpilled) continue;
    auto argj = F.Arg_begin();
    for (int j = 0; j < F.Arg_size() && j < 4; j++, argj++) {
      if (i == j) continue;
      if ((*argj)->isSpilled) continue;
      addEdge(*argi, *argj);
      // std::cout << "Add edge: (" << (*argi)->FOrder << ", " << (*argj)->FOrder << ")\n";
    }
  }

  for (BasicBlock *BB : F.getBasicBlockList()) {
    int BBOrder = BB->Order;
    std::map<unsigned, Value *> L;
    for (auto item : BB->def_list)
      L.insert(item);
    for (auto item : BB->IN_list)
      L.insert(item);
    
    for (auto itemi : BB->def_list) {
      if (!itemi.second->hasRegAllocated() || itemi.second->isSpilled)
        continue;
      unsigned i = itemi.second->idx;
      auto infoI = itemi.second->getVarInfo();

      for (auto itemj : L) {
        if (!itemj.second->hasRegAllocated() || itemj.second->isSpilled || itemi == itemj)
          continue;
        unsigned j = itemj.second->idx;
        auto infoJ = itemj.second->getVarInfo();
        if (infoJ.start[BBOrder] <= infoI.start[BBOrder] && 
                 infoI.start[BBOrder]  < infoJ.killer[BBOrder]) {
          addEdge(itemi.second, itemj.second);
        }
      }
    }

  }

  #ifdef DEBUG
  std::cout << "VertexNum = " << VertexNum << std::endl;
  std::cout << "Vertexes.size() = " << Vertexes.size() << std::endl;
  std::cout << "\t\t|\t";
  for (int i = 0; i < Vertexes.size(); i++)
    std::cout << i << "\t";
  std::cout << std::endl;
  for (int i = 0; i < Vertexes.size(); i++) {
    std::cout << Vertexes[i]->idx << "\t" << Vertexes[i]->FOrder << "\t|\t";
    for (int j = 0; j < Vertexes.size(); j++)
      std::cout << Graph[i][j] << "\t";
    std::cout << std::endl;
  }
  std::cout << "Vertexes.size() = " << Vertexes.size() << std::endl;
  #endif
}

int HazardGraph::getColor(Value *I) {
    bool colors[RegNum] = {0};
    int colors_weight[RegNum] = {0};
    if (I->Color != -1) {
      return I->Color;
    }

    for (auto V : I->adjs) {
      if (V->Color >= 0 && V->Color <= 10)
        colors[V->Color] = true;
    }

    if (auto inst = cast<Instruction>(I))
      for (auto U = I->user_begin(); U != I->user_end(); U++) {
        if (auto CI = cast<CallInst>(*U)) {
          int i = -1;
          for (i = 0; i < CI->getNumOperands();) {
            if (CI->getNumOperand(i).get() == I) {
              break;
            }
            i++;
          }
          assert(i != -1 && "can't find I in its user");
          Function *F = inst->getFunction();
          auto arg = F->Arg_begin();
          int c = -1;
          for (auto j = 0; j < F->Arg_size() && j < 4; j++, arg++) {
            if ((*arg)->getArgNo() == i && (*arg)->Color != -1) {
              c = (*arg)->Color;
              break;
            }
          }
          if (c != -1 && !colors[c]) return c;
          if (i >= 0 && i <= 3 && !colors[i + 7]) {
            if (i == 0) return r0;
            if (i == 1) return r1;
            if (i == 2) return r2;
            if (i == 3) return r3;
          }
        } 
        else if (auto phi = cast<PHINode>(*U)) {
          if (phi->Color != -1 && !colors[phi->Color])
            return phi->Color;
        }
      }

    int max = -1;
    int color = -1;
    for (int i = 0; i < RegNum; i++) {
      if (!colors[i]) {
        return i;
      }
    }
    return -1;
}

RegAssign::RegAssign(Function &F, DominatorTree *DT) 
    : F(F), DT(DT) {
  LD_set.clear();
}

std::vector<LoopNode *> RegAssign::calLoopDepth() {
  std::map<unsigned, BasicBlock*> Loop_set;
  std::stack<BasicBlock*> S;
  std::vector<LoopNode *> LNSet;
  for (auto BB : F.getBasicBlockList()) {
    for (auto succ : BB->getSuccList()) {
      if (DT->dominates(succ, BB)) {
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
        LoopNode *LN = new LoopNode();
        LN->start = succ;
        LN->end = BB;
        LN->LoopSet = Loop_set;
        for (auto item : Loop_set) {
          item.second->LoopDepth++;
          for (auto inst : item.second->getInstList()) {
            inst->LoopDepth++;
          }
        }
        LNSet.push_back(LN);
      }
    }
  }
  return LNSet;
}

void RegAssign::calSpillWeight() {
  for (auto arg = F.Arg_begin(); arg != F.Arg_end(); arg++) {
    int weight = (*arg)->getNumUses() + pow(100, (*arg)->LoopDepth);
    for (auto U = (*arg)->user_begin(); U != (*arg)->user_end(); U++)
      weight += pow(100, (*U)->LoopDepth);
    (*arg)->weight = weight;
  }
  for (auto BB : F.getBasicBlockList()) {
    for (auto I : BB->getInstList()) {
      int weight = 0;
      bool hasGV = false;
      weight = pow(100, I->LoopDepth) + I->getNumUses();
      for (int i = 0; i < I->getNumOperands(); i++) {
        if (isa<GlobalVariable>(I->getNumOperand(i).get())) {
          hasGV = true;
          break;
        }
      }
      // else
      //   weight = I->getNumUses();
      for (auto U = I->user_begin(); U != I->user_end(); U++)
        weight += pow(100, (*U)->LoopDepth);
      if (hasGV) weight *= 2;
      I->weight = weight;
    }
  }
}

typedef struct Dominate_note
{
  int idx;
  Value *V;
  LoadInst *LD;
};

int getSet(Dominate_note D[], int x) {
  if (D[x].idx == x) return x;
  else return getSet(D, D[x].idx);
}

void RegAssign::trySpill(Value *SpillVar) {
  assert(!SpillVar->isSpilled && "SpillVar is spilt");

  #ifdef DEBUG
  std::cout << " >> spill var: " << SpillVar->FOrder; 
  std::cout << " weight = " << SpillVar->weight << std::endl;
  #endif

  Value *ignore_user = nullptr;
  if (auto LD = cast<LoadInst>(SpillVar))
    if (LD->LoadUser != nullptr) {
      ignore_user = LD->LoadUser;
      // std::cout << "has load user: " << LD->LoadUser->FOrder << std::endl;
    }

  int user_size = SpillVar->getNumUses();
  if (ignore_user != nullptr) user_size -= 1;

  Dominate_note *DNs = new Dominate_note[user_size];
  int i = 0;
  #ifdef DEBUG
  std::cout << "  user_size: " << user_size << std::endl;
  #endif
  for (auto U = SpillVar->user_begin(); i < user_size; i++, U++) {
    if (*U == ignore_user) continue;
    if (isa<PHINode>(*U)) {
      DNs[i].V = nullptr;
      DNs[i].idx = -1;
      continue;
    }
    DNs[i].LD = nullptr;
    DNs[i].idx = i;
    DNs[i].V = *U;
    #ifdef DEBUG
    std::cout << "  user: " << (*U)->FOrder << std::endl;
    #endif
  }

  for (i = 0; i < user_size; i++) {
    if (DNs[i].idx == -1) continue;
    for (int j = 0; j < user_size; j++) {
      if (j == i) continue;
      if (DNs[j].idx == -1) continue;
      Instruction *I1 = cast<Instruction>(DNs[i].V), *I2 = cast<Instruction>(DNs[j].V);
      if (DT->dominates(I1, I2))
        DNs[j].idx = i;
    }
  }

  Value *AI;
  StoreInst *ST;

  // 如果SpillVar是一条指令，那么在它的后边创建alloca和store
  if (auto Inst = cast<Instruction>(SpillVar)) {
    bool hasOPload = false;
    if (auto LD = cast<LoadInst>(Inst)) {
      for (int k = 0; k < LD->getNumOperands(); k++) {
        auto op = LD->getNumOperand(k).get();
        if (isa<LoadInst>(op) || isa<GetElementPtrInst>(op) || isa<GlobalVariable>(op))
          hasOPload = true;
      }
    }
    if (!isa<LoadInst>(Inst) || hasOPload) {
      auto t = std::find(Inst->getParent()->getInstList().begin(), 
                        Inst->getParent()->getInstList().end(), Inst);
      assert(t != Inst->getParent()->getInstList().end() && 
            "can't find this spill instruction in its parent");
      t++;
      
      if (auto AT = cast<ArrayType>(Inst->getType()))
        AI = AllocaInst::Create(AT, ConstantInt::get(AT->getContext(), AT->getElementNum()), "", (*t));
      else
        AI = AllocaInst::Create(Inst->getType(), nullptr, "", (*t));
      Inst->SpilledAI = cast<AllocaInst>(AI);

      if (auto phi = cast<PHINode>(Inst)) phi->isPHISpilled = true;
      else ST = StoreInst::Create(Inst, AI, (*t));

      Inst->isSpilled = true;
    } else {
      AI = Inst->getNumOperand(0);
      if (!ignore_user) {
        Inst->eraseFromParent();
      }
      else
        Inst->isSpilled = true;
    }
  }

  // 如果SpillVar是一个参数，那么在入口快的入口出创建alloca和store
  else if (auto Arg = cast<Argument>(SpillVar)) {
    Instruction *First = (*(*F.BB_begin())->begin());
    AI = AllocaInst::Create(Arg->getType(), nullptr, "", First);
    Arg->SpilledAI = cast<AllocaInst>(AI);
    Arg->isSpilled = true;

    ST = StoreInst::Create(Arg, AI, First);
  }

  else std::cerr << "Error Var Type " << std::endl;

  for (i = 0; i < user_size; i++) {
    if (DNs[i].idx == -1) continue;
    int s = getSet(DNs, i);
    if (s == i) {
      LoadInst *LD = LoadInst::Create(SpillVar->getType(), AI, "", cast<Instruction>(DNs[i].V));
      LD->LoadUser = DNs[i].V;
      LD_set.insert(LD);
      DNs[i].LD = LD;
      Instruction *I = cast<Instruction>(DNs[i].V);
      assert(I && "I is not an instruction");
      for (int k = 0; k < I->getNumOperands(); k++) {
        if (I->getNumOperand(k).get() == SpillVar) {
          #ifdef DEBUG
          std::cout << "  add load before " << I->FOrder << " load is from " << DNs[s].V->FOrder << std::endl;
          #endif
          I->getNumOperand(k) = LD;
        }
      }
      if (isa<CallInst>(DNs[i].V)) LD->SpilledAndUsedByCall = true;
    }
  }

  for (i = 0; i < user_size; i++) {
    if (DNs[i].idx == -1) continue;
    int s = getSet(DNs, i);
    if (s != i) {
      Instruction *I = cast<Instruction>(DNs[i].V);
      assert(I && "I is not an instruction");
      for (int k = 0; k < I->getNumOperands(); k++) {
        if (I->getNumOperand(k).get() == SpillVar) {
          #ifdef DEBUG
          std::cout << "  add load before " << I->FOrder << " load is from " << DNs[s].V->FOrder << std::endl;
          #endif
          I->getNumOperand(k) = DNs[s].LD;
        }
      }
      if (isa<CallInst>(DNs[i].V)) DNs[s].LD->SpilledAndUsedByCall = true;
    }
  }

  delete[] DNs;
}

// 每次循环从图中删除掉一个度数小于k的节点，并且将它插入到一个链表中去，直到所有
// 节点都被删除或者所有节点的度数都大于k为止。
//   1. 对于第一种情况，该冲突图可以着色，只需要按照删除节点的逆序进行着色就可以
//      找到一种着色方案
//   2. 对于第二种情况，可以从所有节点中删除一个溢出代价最小的节点插入到列表中，
//      随后重新返回去删除图中度数小于k的节点
//   3. 重复这种操作直到所有节点都被删除
//   4. 按照删除的逆序进行着色，找不到着色方案的节点需要溢出到存储器中。
bool RegAssign::runColoring(HazardGraph &HG) {
  
  std::stack<Value *> LI_list;

  while(true) {
    // 找到一个边数小于可用寄存器的数目的顶点
    while (true) {
      if (Nodes.size() == 0) break;
      auto temp = Nodes.front();
      bool found = false;
      for (auto item : Nodes) {
        // int arg_num = 0;
        // for (auto adj : item->adjs) {
        //   if (auto arg = cast<Argument>(adj))
        //     if (arg->getArgNo() < 4)
        //       arg_num++;
        // }
        if (item->size < RegNum) {
          temp = item;
          found = true;
          break;
        }
      }
      
      if (found) {
        LI_list.push(temp);
        eraseFromGraph(temp);
      } else break;
    }

    // 此时有解
    if (Nodes.empty()) {
      bool result = true;
      bool LD_set_empty = LD_set.empty();
      while (!LI_list.empty()) {
        Value *Var = LI_list.top();
        LI_list.pop();

        if (Var->SpilledAndUsedByCall || Var->isSpilled)
          continue;
        
        int color = HG.getColor(Var);
        if (color == -1) {
          #ifdef DEBUG
          std::cout << "Var: " << Var->FOrder << " can't get a color  ";
          std::cout << "| BB: " << cast<Instruction>(Var)->getParent()->getName() << " weight: " << Var->weight;
          std::cout << "  opcode name: " << cast<Instruction>(Var)->getOpcodeName() << std::endl;
          
          for (auto adj : Var->adjs) {
            std::cout << "  - adj: " << adj->FOrder << " color: " << adj->Color << std::endl;
          }
          #endif

          int min = Var->weight;
          Value *SpillVar = Var;

          for (int k = 0; k < HG.VertexNum; k++) {
            if (HG.Graph[Var->idx][k] == 1 && HG.Vertexes[k]->weight < min 
                && !HG.Vertexes[k]->isSpilled && !HG.Vertexes[k]->SpilledAndUsedByCall) {
              min = HG.Vertexes[k]->weight;
              SpillVar = HG.Vertexes[k];
            }
          }

          // std::set<Value *> c[11];
          // int c_weight[11];
          // for (int k = 0; k < 11; k++) { c[k].clear(); c_weight[k] = 0; }
          // for (auto neighbor = Var->adjs.begin(); neighbor != Var->adjs.end(); neighbor++) {
          //   int temp = (*neighbor)->Color;
          //   if (temp != -1) {
          //     c[temp].insert(*neighbor);
          //     // std::cout << "temp: " << temp << " insert: " << (*neighbor)->FOrder << std::endl;
          //     c_weight[temp] += (*neighbor)->weight;
          //   }
          // }
          
          // int min_set = -1;
          // for (int k = 0; k < 11; k++) {
          //   // std::cout << " c_weight[" << k << "] = " << c_weight[k] << std::endl;
          //   if (!c[k].empty() && c_weight[k] < min) {
          //     min = c_weight[k];
          //     min_set = k;
          //   }
          // }
          
          if (!LD_set_empty) {
            auto set_temp = LD_set;
            for (auto LD : set_temp) {
              if (!LD->isSpilled) {
                trySpill(LD);
              }
            }
            LD_set.clear();
            return false;
          }
          
          else {
            trySpill(SpillVar);
            // if (min_set == -1) trySpill(SpillVar);
            // else {
            //   for (auto V : c[min_set]) trySpill(V);
            // }
          }
          
          result = false;
        }

        Var->Color = color;
      }

      return result;
    }

    // 有变量溢出，找到溢出权重最小的变量，随后试探性的在它的一个user前增加LD指令，并且
    // 使用LD指令替换掉它的user
    else {

      int min = 10000000;
      int min_idx = 0;

      for (int k = 0; k < Nodes.size(); k++) {
        if (Nodes[k]->weight < min) {
          min_idx = k;
          min = Nodes[k]->weight;
        }
      }

      #ifdef DEBUG
      // std::cout << "May be spilt: " << Nodes[min_idx]->FOrder << " size: " << Nodes[min_idx]->size; 
      // std::cout << " weight: " << Nodes[min_idx]->weight << std::endl;
      #endif

      LI_list.push(Nodes[min_idx]);
      eraseFromGraph(Nodes[min_idx]);
    }
  }
}

void RegAssign::switchColor(HazardGraph &HG) {
  int reg[11];
  int arg_reg[4];
  auto arg = F.Arg_begin();
  for (int i = 0; i < F.Arg_size() && i < 4; i++, arg++)
    arg_reg[i] = (*arg)->getColor();
  // for (int i = 0; i < 4; i++) {
  //   std::cout << "arg_reg[" << i << "] = " << arg_reg[i] << std::endl;
  // }
  for (int i = 0; i < 11; i++) reg[i] = i;

  for (int i = 0; i < F.Arg_size() && i < 4; i++) {
    if (arg_reg[i] != i) {
      int pos = -1;
      for (int j = 0; j < 11; j++) 
        if (reg[j] == arg_reg[i]) {
          pos = j;
          break;
        }
      assert(pos != -1 && "pos == -1");
      int temp = reg[pos];
      reg[pos] = reg[i];
      reg[i] = temp;
    }
  }

  for (auto V : HG.Vertexes) {
    int c = V->getColor();
    // std::cout << " V: " << V->FOrder << " color: " << c << std::endl;
    if (reg[c] != c) {
      int pos = -1;
      for (int j = 0; j < 11; j++) {
        if (reg[j] == c) {
          pos = j;
          break;
        }
      }
      assert(pos != -1 && "pos == -1");
      if (pos >= 4 && pos <= 10) V->Color = pos - 4;
      else if (pos >= 0 && pos <= 3) V->Color = pos + 7;
      else std::cerr << "Error Color!" << std::endl;
    }
  }

  // for (int i = 0; i < 11; i++)
  //   std::cout << "reg[" << i << "] = " << reg[i] << std::endl;
}

// 计算生命周期-->构建冲突图-->尝试着色
void RegAssign::runOnFunction() {
  #ifdef DEBUG
  std::cout << "---------- Function: " << F.getName() << " ----------" << std::endl;
  #endif
  
  int cnt = 0;

  while (true) {
    // if (cnt++ == 7) break;
    F.setBlockOrder();
    #ifdef DEBUG
    std::cout << "*** run Live Interval ***" << std::endl;
    #endif
    LiveVars LVar;
    LVar.runOnFunction(F);

    calLoopDepth();
    calSpillWeight();

    #ifdef DEBUG
    std::cout << "*** build Hazard Graph ***" << std::endl;
    #endif
    HazardGraph *HGraph = new HazardGraph(F);
    Nodes = HGraph->Vertexes;

    #ifdef DEBUG
    std::cout << "*** run Coloring ***" << std::endl;
    #endif
    if (runColoring(*HGraph)) {
      switchColor(*HGraph);
      break;
    }
    
    delete HGraph;
    // std::cout << std::endl;
  }
}
