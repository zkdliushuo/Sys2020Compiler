#include "ModuleAnalyse.h"
#include "Constants.h"
#include "Instructions.h"
#include "LabelTable.h"
#include "SemiMachine.h"
#include "support.h"

#include <vector>

// #define SemiMachineListDebug

using namespace labeltable;

using namespace YAL;
using namespace semimachine;

namespace semimachine {

Function *TheFunction = nullptr;
std::map<const GlobalVariable *, int> current_used_global_variable;
std::vector<const GlobalVariable *> used_gv_in_order;
std::unordered_map<const Value *, int> temp_value;
int current_func_alloc_size = 0;

SemiMachineBlock globalVariableInitilize(Constant *CV, int var_space) {
  SemiMachineBlock InitBlock;
  if (auto AllZero = cast<ConstantAggregateZero>(CV)){
    std::string word_value = "\t.space\t";
    word_value += std::to_string(4 * var_space);
    auto single_init = new SemiMachineInstruction(word_value, 0, SemiMachineInstruction::Nop_);
    InitBlock.addInstruction(single_init);
    return InitBlock;
  }
  if (auto CI = cast<ConstantInt>(CV)) {
    assert(CI->getBitWidth() == 32 && "Global variable is not i32");
    std::string word_value = "\t.word\t";
    word_value += std::to_string(CI->getValue());
    auto single_init = new SemiMachineInstruction(word_value, 0, SemiMachineInstruction::Nop_);
    InitBlock.addInstruction(single_init);
    return InitBlock;
  }
  if (auto CA = cast<ConstantArray>(CV)) {
    Type *ETy = CA->getType()->getElementType();
    for (unsigned i = 0, e = CA->getNumOperands(); i != e; ++i) {
      assert(cast<Constant>(CA->getNumOperand(i).get()) && "One element of constant Array is not Constant Int");
      InitBlock += globalVariableInitilize(cast<Constant>(CA->getNumOperand(i).get()), var_space - CA->getNumOperands());
    }
  }
  return InitBlock;
}

// * Build semi-machine block for global variable definition
// In most cases there is only one semi-machine instruction in a block.
// But when it comes to global array definition, it need more instructions.
// So the return value is SemiMachineBlock type instead of SemiMachineInstruction.
SemiMachineBlock globalVariableTransform(GlobalVariable *global_variable_item) {
  // TODO: To be done.
  // Build Symbol Table.
  SemiMachineBlock global_variable_slot;
  SemiMachineInstruction *inst = new SemiMachineInstruction();

  // Add a variable tag for the global variable
  inst->setType(SemiMachineInstruction::SemiMachineType::Variable);
  // Add the name of the variable
  std::string var_name = "";

  auto GV_type = cast<PointerType>(global_variable_item->getType());
  assert(GV_type && "Global Variable's Type should be pointer to Array Type");
  int word_num;
  if (auto init_constant_array = cast<ArrayType>(GV_type->getElementType())) {
    word_num = init_constant_array->getElementNum();
  } else {
    word_num = 1;
  }

  if (global_variable_item->isConstant()) {
    var_name += "	.global ";
    var_name += global_variable_item->getName();
    inst->setInstruction(var_name);
    inst->addAttribute("\n\t.section\t.rodata\n\t.align	2\n\t.type\t" + global_variable_item->getName() +
                       ", %object\n\t.size\t" + global_variable_item->getName() + ", " + std::to_string(word_num * 4));
    inst->addAttribute( "\n" + global_variable_item->getName() + ":\n");
  } else {
    var_name += "	.global ";
    var_name += global_variable_item->getName();
    inst->setInstruction(var_name);
    inst->addAttribute("\n\t.data\n\t.align	2\n\t.type\t" + global_variable_item->getName() +
                       ", %object\n\t.size	" + global_variable_item->getName() + ", " +
                       std::to_string(word_num * 4));
    inst->addAttribute( "\n" + global_variable_item->getName() + ":");
  }

  global_variable_slot.addInstruction(inst);
  auto GV_init_result = globalVariableInitilize(global_variable_item->getInitializer(), word_num);
  global_variable_slot += GV_init_result;

  return global_variable_slot;
}

// * Translate a single instruction into a Semi-machine Instruction
// 1st Stage (2020-07-18): direct translation
SemiMachineBlock instructionTransform(Instruction *instruction_item) {
  // ANCHOR: THIS IS A ROUGH VERSION OF CODEGEN!
  /// transform every inst individually
  auto val = instruction_item->getNumOperands();
  auto opcode = instruction_item->getOpcode();
  return InstructionToSemiMachine(instruction_item);
}

void AddBranchLabels(Instruction *inst, BasicBlock *true_bb, BasicBlock *fasle_bb, int in_scope = Instruction::Opcode::Or){
  // assert(inst && "Add Branch Labels to a nullptr");
  // assert(true_bb && fasle_bb && "Non-label Type can not be added to an instruction");
  // auto opcode = inst->getOpcode();
  // auto lhs = inst->getNumOperand(0).get();
  // auto rhs = inst->getNumOperand(1).get();
  // switch (opcode)
  // {
  //   case Instruction::Opcode::Or :{
  //     AddBranchLabels(cast<Instruction>(lhs), true_bb, fasle_bb, );
  //     AddBranchLabels(cast<Instruction>(rhs), true_bb, fasle_bb, true_bb);
  //     return ;
  //   }
  //   case Instruction::Opcode::And:{
  //     AddBranchLabels(cast<Instruction>(lhs), true_bb, fasle_bb);
  //     AddBranchLabels(cast<Instruction>(rhs), true_bb, fasle_bb);
  //   }
    
  //   default:
  //     break;
  // }

}

void ProcessBB(BasicBlock *basic_block_item){
  auto BrInst = cast<BranchInst>(basic_block_item->getTerminator());
  if(BrInst){
    if(BrInst->isConditional()){
      auto pred = cast<Instruction>(BrInst->getNumOperand(2).get());
      auto true_bb = cast<BasicBlock>(BrInst->getNumOperand(0).get());
      auto false_bb = cast<BasicBlock>(BrInst->getNumOperand(1).get());
      AddBranchLabels(pred, true_bb, false_bb);
    }
  }
}

SemiMachineBlock basicBlockTransform(BasicBlock *basic_block_item) {
#ifdef SemiMachineListDebug
  std::cout << "Enter BB Transform" << std::endl;
#endif
  // Prepare:
  SemiMachineBlock basic_block_semi_machine_block;

  // Add the basic block name in the beginning of the semi-machine-code block
  // To avoid conflicts here, all the basic block name are prefixed with function name
  std::string basic_block_name = basic_block_item->getName();
  basic_block_name = basic_block_name + ": ";
  SemiMachineInstruction *inst =
      new SemiMachineInstruction(basic_block_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);

  basic_block_semi_machine_block.addInstruction(inst);

#ifdef SemiMachineListDebug
  std::cout << "Before Enter EntryBB" << std::endl;
#endif

  if (basic_block_item->getParent()->getEntryBlock() == basic_block_item) {
    basic_block_semi_machine_block += IRToSemiEntryBB();
  }

#ifdef SemiMachineListDebug
  std::cout << "After EntryBB starter" << std::endl;
#endif

  // Translate all the instructions into semi-machine language
  for (auto item = basic_block_item->begin(); item != basic_block_item->end(); ++item) {
    auto instruction_semi_machine = instructionTransform(*item);
    basic_block_semi_machine_block += instruction_semi_machine;
  }

  return basic_block_semi_machine_block;
}

void processfunction(Function *function_item) {
  TheFunction = function_item;
  current_used_global_variable.clear();
  used_gv_in_order.clear();
  temp_value.clear();
  current_func_alloc_size = 0;
}

SemiMachineBlock functionTransform(Function *function_item) {
// ::current_func = function_item;
// Prepare:
#ifdef SemiMachineListDebug
  std::cout << "Enter Function Transform" << std::endl;
#endif
  SemiMachineBlock function_semi_machine_block;

  if(function_item->isDeclaration()){
    return function_semi_machine_block;
  }

  processfunction(function_item);
  auto func_name = function_item->getName();
  std::string func_label =
      "\t.text\n\t.align	2\n	.global	" + func_name + "\n\t.arch armv8-a\n\t.type	" + func_name + ", %function";
  SemiMachineInstruction *inst =
      new SemiMachineInstruction(func_label, SemiMachineInstruction::SemiMachineType::FuncLabel, 12);
  function_semi_machine_block.addInstruction(inst);

  function_item->getEntryBlock()->setValueName(function_item->getName());

#ifdef SemiMachineListDebug
  std::cout << "After add BasicBlockLabel" << std::endl;
#endif

  // Visit each single BasicBlock to transform
  for (auto item = function_item->getBasicBlockList().begin(); item != function_item->getBasicBlockList().end();
       ++item) {
    BasicBlock *item_tmp = *item;

    // Add BasicBlock Code
    auto basic_block_semi_machine_block = basicBlockTransform(item_tmp);
    function_semi_machine_block += basic_block_semi_machine_block;
  }

  auto ret_bb = IRToSemiRetBB();
  function_semi_machine_block += ret_bb;

  std::string func_size = "\t.size\t" + function_item->getName() + ", .-" + function_item->getName();
  function_semi_machine_block.addInstruction(new SemiMachineInstruction(func_size, 0, SemiMachineInstruction::Nop_));

#ifdef SemiMachineListDebug
  std::cout << "After all basicBlock Transform" << std::endl;
#endif

  return function_semi_machine_block;
}

SemiMachineBlock moduleTransform(Module *module_item) {
  // Prepare
  SemiMachineBlock module_semi_machine_block;
  LabelTable module_table;

  // Build module-level label table
  // for (auto item = module_item->getFunctionList().begin(); item != module_item->getFunctionList().end(); ++item) {
  //   Function *item_tmp = *item;
  //   module_table.addFunctionLabel(item_tmp->getName());
  // }

  // Handle Global Variables
  std::string label_for_div_mod_abi = "\t.text\n\t.global\t__aeabi_idivmod\n\t.global\t__aeabi_idiv\n\t.align\t2";
  auto mod_div_decl = new SemiMachineInstruction(label_for_div_mod_abi, 0, SemiMachineInstruction::Nop_);
  module_semi_machine_block.addInstruction(mod_div_decl);

  for (auto item = module_item->getGlobalList().begin(); item != module_item->getGlobalList().end(); ++item) {
    GlobalVariable *item_tmp = *item;
    auto global_block = globalVariableTransform(item_tmp);
    module_semi_machine_block += global_block;
  }

  // Handle Function
  for (auto item = module_item->getFunctionList().begin(); item != module_item->getFunctionList().end(); ++item) {
    Function *item_tmp = *item;
    auto function_block = functionTransform(item_tmp);
    module_semi_machine_block += function_block;
  }

  // After
  // ...
  return module_semi_machine_block;
}
} // namespace semimachine