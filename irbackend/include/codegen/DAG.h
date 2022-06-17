#ifndef CODEGEN_DAG_H
#define CODEGEN_DAG_H

#include <string>

namespace DAG {

// TODO: Convert a single BasicBlock to a DAG
class DAGNode {
private:
  bool type;
};

class DAGOprandNode {
private:
  int oprand_id;
  int oprand_value;
  int oprand_type;

public:
  DAGOprandNode(int id, int val = 0, int type = 0) {
    oprand_id = id;
    oprand_value = val;
    oprand_type = type;
  }
};

class DAGOpcodeNode {
private:
  unsigned opcode;
  DAGOprandNode *oprand_a;
  DAGOprandNode *oprand_b;
  DAGOprandNode *result;

public:
};
} // namespace DAG

#endif