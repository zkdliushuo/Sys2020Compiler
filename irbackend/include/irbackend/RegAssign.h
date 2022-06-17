#ifndef REGASSIGN_H
#define REGASSIGN_H
#include "LiveVar.h"
#include <list>
#include <vector>

namespace YAL {
class LiveVars;
class DominatorTree;

// typedef struct Vertex_ {
//   Instruction *I;
//   std::list<Vertex_> adjs;
// } Vertex;

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
    r11,
    r12,
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
    // for (int i = 0; i < VertexNum; i++) 
    //   delete[] Graph[i];
    // delete[] Graph;
    // delete[] Vertexes;
  }

  void addEdge(Value *I1, Value *I2) {
    int i = I1->idx, j = I2->idx;
    if (Graph[i][j] == 0) {
      Vertexes[i]->adjs.push_back(I2);
      Vertexes[i]->size += 1;
      Vertexes[j]->size += 1;
      Vertexes[j]->adjs.push_back(I1);
    }
    Graph[i][j] += 1;
    Graph[j][i] += 1;
  }

  int getColor(Value *I) {
    bool colors[13] = {0};
    if (I->Color != -1)
      return I->Color;
    // std::cout << "Analyze I: " << I->FOrder << std::endl;
    for (auto V : I->adjs) {
      // std::cout << "  V: " << V->FOrder << std::endl;
      if (V->Color != -1)
        colors[V->Color] = true;
    }

    for (int i = 0; i < 13; i++) {
      // std::cout << "  --Color[" << i << "] = " << colors[i] << std::endl;
      if (!colors[i]) {
        return i;
      }
    }
    return -1;
  }
};

class RegAssign {
private:
  HazardGraph HG;
  Function &F;
  LiveVars *LV;
  std::vector<Value *> Nodes;
  DominatorTree *DT;
  
public:
  RegAssign(Function &F, LiveVars *LV, DominatorTree *DT);
  ~RegAssign() = default;

  void runColoring();

  void calLoopDepth();

  bool eraseFromGraph(Value *I) {
    // unsigned x = I->idx;
    // for (int i = 0; i < VertexNum; i++) {
    //   Graph[x][i] = 0;
    //   Graph[i][x] = 0;
    // }
    for (auto V : I->adjs) {
      auto temp = std::find(V->adjs.begin(), V->adjs.end(), I);
      if (temp != V->adjs.end())
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