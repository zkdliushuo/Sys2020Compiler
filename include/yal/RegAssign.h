#ifndef REGASSIGN_H
#define REGASSIGN_H
#include "LiveVar.h"
#include <list>
#include <vector>

namespace YAL {
class LiveVars;
class DominatorTree;
class LoadInst;

struct LoopNode {
  BasicBlock *start;
  BasicBlock *end;
  std::map<unsigned, BasicBlock*> LoopSet;
};

class HazardGraph {
public:
  enum Color {
    r4 = 0,
    r5,
    r6,
    r7,
    r8,
    r9,
    r10,
    r0,
    r1,
    r2,
    r3
  };
  unsigned VertexNum;
  int **Graph;
  std::vector<Value *> Vertexes;

public:
  explicit HazardGraph(Function &F);
  ~HazardGraph() {
    for (int i = 0; i < VertexNum; i++) 
      delete[] Graph[i];
    delete[] Graph;
  }

  void addEdge(Value *I1, Value *I2) {
    int i = I1->idx, j = I2->idx;
    if (Graph[i][j] == 0) {
      Vertexes[i]->adjs.insert(I2);
      Vertexes[i]->size += 1;
      Vertexes[j]->size += 1;
      Vertexes[j]->adjs.insert(I1);
    }
    Graph[i][j] = 1;
    if (Graph[j][i] == 0)
      Graph[j][i] = -1;
  }

  int getColor(Value *I);
};

class RegAssign {
private:
  Function &F;
  std::vector<Value *> Nodes;
  DominatorTree *DT;
  std::set<Value *> LD_set;
  
public:
  RegAssign(Function &F, DominatorTree *DT);
  ~RegAssign() = default;

  bool runColoring(HazardGraph &HG);

  void runOnFunction();

  void switchColor(HazardGraph &HG);

  void trySpill(Value *SpillVar);

  void calSpillWeight();

  // static bool isRegAvailable(Instruction *I, int Color);

  std::vector<LoopNode *> calLoopDepth();

  bool eraseFromGraph(Value *I) {
    for (auto V : I->adjs) {
      if (V->adjs.count(I))
        V->size -= 1;
    }
    auto temp = std::find(Nodes.begin(), Nodes.end(), I);
    if (temp != Nodes.end()) {
      Nodes.erase(temp);
      return true;
    }
    return false;
  }
};

} // namespace YAL

#endif