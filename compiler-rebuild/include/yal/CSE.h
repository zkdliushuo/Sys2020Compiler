#ifndef CSE_H
#define CSE_H

#include "Function.h"
#include "DominatorTree.h"

namespace YAL{
    void CommonSubexpressionElimination(Function*, DominatorTree&);
}

#endif
