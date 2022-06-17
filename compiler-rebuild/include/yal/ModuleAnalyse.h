#ifndef CODEGEN_MODULEANALYSE_H
#define CODEGEN_MODULEANALYSE_H

#include <iostream>
#include <list>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include "Function.h"
#include "GlobalVariable.h"
#include "LLVMContext.h"
#include "Module.h"

#include "SemiMachine.h"
#include <set>
using namespace YAL;

namespace semimachine {
extern Function *TheFunction;
extern std::map<const GlobalVariable *, int> current_used_global_variable;
extern std::vector<const GlobalVariable *> used_gv_in_order;
extern std::unordered_map<const Value *, int> temp_value;
extern int current_func_alloc_size;
extern std::set<int> used_regs;

SemiMachineBlock globalVariableTransform(GlobalVariable *global_variable_item);
SemiMachineBlock functionTransform(Function *function_item);
SemiMachineBlock instructionTransform(Instruction *instruction_item);
SemiMachineBlock basicBlockTransform(BasicBlock *basic_block_item);
SemiMachineBlock moduleTransform(Module *module_item);
SemiMachineBlock globalVariableInitilize(Constant *CV, int);
} // end namespace semimachine

#endif