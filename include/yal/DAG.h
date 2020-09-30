#ifndef CODEGEN_DAG_H
#define CODEGEN_DAG_H

#include <string>

namespace DAG {

class DagAtom {
private:
  int oprand_id;
  int oprand_value;
  int oprand_type;

public:
  DagAtom() {
    oprand_id = 0;
    oprand_value = 0;
    oprand_type = 0;
  }

  DagAtom(int id, int val = 0, int type = 0) {
    oprand_id = id;
    oprand_value = val;
    oprand_type = type;
  }
};

class DagNode {
private:
  unsigned opcode;
  DagAtom *oprand_a;
  DagAtom *oprand_b;
  DagAtom *result;

public:
};
} // namespace DAG

#endif