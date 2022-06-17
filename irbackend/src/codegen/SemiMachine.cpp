#include "SemiMachine.h"

// #define SemiMachineListDebug

#include "Constant.h"
#include "Constants.h"
#include "Function.h"
#include "Instruction.h"
#include "Instructions.h"
#include "ModuleAnalyse.h"
#include "Use.h"
#include "Value.h"
#include "support.h"

#include <iostream>
#include <unordered_map>
using namespace YAL;

// #define ARM_V8

// #define ROUGH_VERSION
namespace semimachine {

// SemiMachineBlock::~SemiMachineBlock() { this->deleteBlock(); }

void SemiMachineBlock::deleteBlock() {
  // std::cout << "I am going to delete.";
  // this->print();
  SemiMachineInstruction *item;
  item = this->getHead();
  if (item == nullptr) {
    return;
  } else {
    while (item != nullptr) {
      auto temp = item;
      item = item->getNext();
      delete temp;
    }
  }
}

void SemiMachineBlock::addInstruction(SemiMachineInstruction *inst) {
  inst->setNext(nullptr);
  if (tail == nullptr) {
    head = inst;
    tail = inst;
  } else {
    tail->setNext(&*inst);
    tail = tail->getNext();
  }
}

SemiMachineBlock operator+(const SemiMachineBlock &block1, const SemiMachineBlock &block2) {
  SemiMachineBlock final_block;
  if (block1.getTail() == nullptr)
    return block2;
  if (block2.getTail() == nullptr)
    return block1;

  final_block = block1;
  final_block.getTail()->setNext(block2.getHead());
  final_block.setTail(block2.getTail());
  return final_block;
}

void SemiMachineBlock::operator+=(const SemiMachineBlock &other) {
  if (other.getTail() == nullptr) {
    return;
  }

  if (tail == nullptr) {
    head = other.getHead();
    tail = other.getTail();
    return;
  }

  tail->setNext(other.getHead());
  tail = other.getTail();
}

std::string ProcessSpillOut(int offset, int ri, SemiMachineBlock &semiblock){
  int max_num = 65535;
  if(offset > 127 || offset < -128){
    auto inst = "\tmovw\tr" + std::to_string(ri) + ", #" + std::to_string(offset & max_num);
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
    semiblock.addInstruction(I);
    int high_num = (unsigned int)offset >> 16;
    if(high_num != 0){
      auto inst1 = "\tmovt\tr" + std::to_string(ri) + ", #" + std::to_string(high_num);
      auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Mov_);
      semiblock.addInstruction(I1);
    }
    return "r" + std::to_string(ri);
  }
  else{
    return "#" + std::to_string(offset);
  }
}

// * Stack Frame Design
// Should Only Use the rith reg
SemiMachineBlock GetOperand(Value *Operand, int ri) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  if(auto GV = cast<GlobalVariable>(Operand)){
    // std::cout << "Operand is an " << GV->getType()->getTypeName() << std::endl;
    auto offset = current_used_global_variable.size();
    if(!current_used_global_variable.count(GV)){
      current_used_global_variable[GV] = offset * 4;
      used_gv_in_order.push_back(GV);
    }
    assert(current_used_global_variable.count(GV) && "This GV is not in current_used_global_variable");
    offset = current_used_global_variable[GV];
    // FIXME:
    // Here may have spill out situation
    auto inst = "\tadrl\tr" + std::to_string(ri) + ", " + TheFunction->getGVBBName() + "+" + std::to_string(offset);
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
    auto inst1 = "\tldr\tr" + std::to_string(ri) + ", [r" + std::to_string(ri) + "]";
    auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Ld_);
    semiblock.addInstruction(I);
    semiblock.addInstruction(I1);
    return semiblock;
  }
  if(auto AI = cast<AllocaInst>(Operand)){
    auto offset = temp_value[AI];
    offset = current_func_alloc_size - offset;

    auto inst = "\tadd\tr" + std::to_string(ri) + ", sp, " + ProcessSpillOut(offset, ri, semiblock);
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
    semiblock.addInstruction(I);
    return semiblock;
  }
  if (auto IO = cast<Instruction>(Operand)) {
    assert(!IO->getType()->isVoidTy() && "Operand is Void Type");
    assert(temp_value.count(IO) && "Operand is not defined");
    auto offset = temp_value[IO];
    offset = current_func_alloc_size - offset;
    auto inst = "\tldr\tr" + std::to_string(ri) + ", [sp, " + ProcessSpillOut(offset, ri, semiblock) + "]";
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
    semiblock.addInstruction(I);
    return semiblock;
  }
  if (auto CO = cast<ConstantInt>(Operand)) {
    auto imm = CO->getValue();
    std::string inst;
    // if(imm > 127 || imm < -128){
    //   inst = "\tldr\tr" + std::to_string(ri) + ", =" + std::to_string(CO->getValue());
    // }
    // else{
    //   inst = "\tmov\tr" + std::to_string(ri) + ", #" + std::to_string(CO->getValue());
    // }
    inst = "\tmov\tr" + std::to_string(ri) + ", " + ProcessSpillOut(imm, ri, semiblock);
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
    semiblock.addInstruction(I);
    return semiblock;
  }
  if (auto ArgumentO = cast<Argument>(Operand)) {
    assert(!ArgumentO->getType()->isVoidTy() && "Operand is Void Type");
    assert(temp_value.count(ArgumentO) && "Operand is not defined");
    auto offset = temp_value[ArgumentO];
    offset = current_func_alloc_size - offset;
    auto inst = "\tldr\tr" + std::to_string(ri) + ", [sp, " + ProcessSpillOut(offset, ri, semiblock) + "]";
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
    semiblock.addInstruction(I);
    return semiblock;
  }
  // Operand->getType()->print();
  // std::cout << "WRONG：No Such Operand As " << Operand->getType()->getTypeName() << std::endl;
  return semiblock;
}

SemiMachineBlock StoreTempValue(Value *instruction_item, int ri) {
  assert(!instruction_item->getType()->isVoidTy() && "Void-type instruction should not store its value in stack-frame");
  assert(temp_value.count(instruction_item) && "This instruction is not defined");
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto offset = temp_value[instruction_item];
  offset = current_func_alloc_size - offset;
  auto inst = "\tstr\tr" + std::to_string(ri) + ", [sp, " + ProcessSpillOut(offset, 4, semiblock) + "]";
  auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::St_);
  semiblock.addInstruction(I);
  return semiblock;
}

// Design the entrance block
SemiMachineBlock IRToSemiEntryBB() {
  assert(temp_value.empty() && "At EntryBloack temp_value is not empty");
  assert(TheFunction && "Processed function is nullptr");
  SemiMachineBlock semiblock = SemiMachineBlock();
  int fNext = 0;
  int16_t num_of_most_trans_parameter = 0;
  int slot_num = TheFunction->Arg_size();
  fNext = (slot_num > 3)? 16 : 4 * slot_num;
  for (auto it = TheFunction->BB_begin(); it != TheFunction->BB_end(); it++) {
    for (auto I = (*it)->begin(); I != (*it)->end(); I++) {
      /// all Alloc Inst is Not VoidTy
      if (!(*I)->getType()->isVoidTy()) {
        if (auto AI = cast<AllocaInst>(*I)) {
          auto allocated_size = cast<ConstantInt>(AI->getArraySize());
          assert(allocated_size && "ArraySize of Alloc Inst is Not Constant Int");
          fNext += allocated_size->getValue() * 4;
          temp_value[*I] = fNext;
          slot_num++;
        }
        else{
          fNext += 4;
          temp_value[*I] = fNext;
          slot_num++;
        }
      }
      if (auto CI = cast<CallInst>(*I)) {
        auto args_num = CI->getNumOperands() - 1;
        if (args_num > num_of_most_trans_parameter) {
          num_of_most_trans_parameter = args_num;
        }
      }
    }
  }

  num_of_most_trans_parameter = (num_of_most_trans_parameter >3)? num_of_most_trans_parameter - 4: 0;

  current_func_alloc_size = 4 * num_of_most_trans_parameter + fNext;
  std::string inst1 =
      "\t@frame_size = " + std::to_string(fNext / 4) + "\n\t@alloc = " + std::to_string(current_func_alloc_size);
  auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Nop_);

  /// save lr unconditionally
  std::string inst2 = "\tpush\t{r4, lr}";
  auto I2 = new SemiMachineInstruction(inst2, 0, SemiMachineInstruction::St_);
  fNext = -4;

  slot_num = 0;
  for (auto it = TheFunction->Arg_begin(); it != TheFunction->Arg_end(); ++it) {
    if(slot_num < 4){
      temp_value[*it] = slot_num * 4 + 4;
    }
    else{
      temp_value[*it] = fNext;
      fNext -= 4;
    }
    slot_num++;
  }

  semiblock.addInstruction(I1);
  semiblock.addInstruction(I2);

  std::string inst3 = "\tsub\tsp, sp, " + ProcessSpillOut(current_func_alloc_size, 4, semiblock);
  auto I3 = new SemiMachineInstruction(inst3, 0, SemiMachineInstruction::Sub_);
  semiblock.addInstruction(I3);

  slot_num = 0;
  for (auto it = TheFunction->Arg_begin(); it != TheFunction->Arg_end(); ++it) {
    if(slot_num < 4){
      semiblock += StoreTempValue(*it, slot_num);
      slot_num++;
      continue;
    }
    break;
  }
  return semiblock;
}

// Design the return basic block
SemiMachineBlock IRToSemiRetBB() {
  assert(TheFunction && "Processed function is nullptr");

  // Ret BB
  SemiMachineBlock semiblock = SemiMachineBlock();
  std::string ret_bb_name = TheFunction->getRetBBName() + ":";
  SemiMachineInstruction *ret_bb_label =
      new SemiMachineInstruction(ret_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);
  semiblock.addInstruction(ret_bb_label);
  /// defualt design is that every return stmt mov its return value to r3
  std::string inst0 = "\tmov\tr0, r3";
  auto I0 = new SemiMachineInstruction(inst0, 0, SemiMachineInstruction::Mov_);
  std::string inst1 = "\tadd\tsp, sp, " + ProcessSpillOut(current_func_alloc_size, 4, semiblock);
  auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Add_);
  std::string inst2 = "\tpop\t{r4, lr}";
  auto I2 = new SemiMachineInstruction(inst2, 0, SemiMachineInstruction::Ld_);
  std::string inst3 = "\tbx\tlr";
  auto I3 = new SemiMachineInstruction(inst3, 0, SemiMachineInstruction::Br_);
  semiblock.addInstruction(I0);
  semiblock.addInstruction(I1);
  semiblock.addInstruction(I2);
  semiblock.addInstruction(I3);

  // Align BB
  SemiMachineBlock semiblock1 = SemiMachineBlock();
  std::string align_bb_name = TheFunction->getAlignBBName() + ":";
  SemiMachineInstruction *align_bb_label =
      new SemiMachineInstruction(align_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);
  semiblock1.addInstruction(align_bb_label);
  std::string inst4 = "\t.align\t2";
  auto I4 = new SemiMachineInstruction(inst4, 0, SemiMachineInstruction::Nop_);
  semiblock1.addInstruction(I4);
  semiblock += semiblock1;

  // GV Declaration BB
  if(current_used_global_variable.size()){
    SemiMachineBlock semiblock2 = SemiMachineBlock();
    std::string GV_bb_name = TheFunction->getGVBBName() + ":";
    SemiMachineInstruction *GV_bb_label =
        new SemiMachineInstruction(GV_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);
    semiblock2.addInstruction(GV_bb_label);
    for(auto it : used_gv_in_order){
      auto word = "\t.word\t" + it->getName();
      auto I5 = new SemiMachineInstruction(word, 0, SemiMachineInstruction::Nop_);
      semiblock2.addInstruction(I5);
    }
    semiblock += semiblock2;
  }
  return semiblock;
}

// #ifdef ROUGH_VERSION
// Design translation pattern for IR:ret
SemiMachineBlock IRToSemiRet(Instruction *instruction_item) {
  // Fetch the ret instruction
  auto val = instruction_item->getNumOperands();
  SemiMachineBlock inst_block = SemiMachineBlock();
  auto RetI = cast<ReturnInst>(instruction_item);

  if (val) {
    if(auto ret_const = cast<ConstantInt>(RetI->getNumOperand(0).get())){
      auto ret_result = ret_const->getValue();
      std::string inst;
      // if(ret_result > 127 || ret_result < -128){
      //   inst = "\tldr\tr3, =" + std::to_string(ret_result);
      // }
      // else{
      //   inst = "\tmov\tr3, #" + std::to_string(ret_result);
      // }
      inst = "\tmov\tr3, " + ProcessSpillOut(ret_result, 3, inst_block);
      auto I0 = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
      inst_block.addInstruction(I0);
    }
    else{
      assert(temp_value.count(RetI->getNumOperand(0).get()) && "Ret Value has not been calculated");
      auto offset = temp_value[RetI->getNumOperand(0).get()];
      offset = current_func_alloc_size - offset;
      // inst0: ldr r3, [sp + #offset]
      std::string inst0 = "\tldr\tr3, [sp, " + ProcessSpillOut(offset, 3, inst_block) + "]";
      auto I0 = new SemiMachineInstruction(inst0, 0, SemiMachineInstruction::Ld_);
      inst_block.addInstruction(I0);
    }
  }
  std::string inst = "\tb\t" + TheFunction->getRetBBName();
  auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Br_);
  inst_block.addInstruction(I);
  return inst_block;
}

SemiMachineBlock IRToSemiBr(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto BrI = cast<BranchInst>(instruction_item);
  assert(BrI && "this instruction should be an Br");
  if (BrI->isConditional()) {
    std::string true_branch_label = BrI->getNumOperand(2)->getName();
    std::string false_branch_label = BrI->getNumOperand(1)->getName();

    auto pred = BrI->getNumOperand(-3).get();
    if (auto CP = cast<ConstantInt>(pred)) {
      auto cmp_result = CP->getValue();
      if (cmp_result) {
        std::string inst1 = "\tb\t" + true_branch_label;
      } else {
        std::string inst1 = "\tb\t" + false_branch_label;
      }
    } else {
      auto pred_inst = cast<ICmpInst>(pred);
      assert(pred_inst && "Before CondBr there is some other insts but Icmp insts");
      auto icmp_opcode = pred_inst->getCmpType_codegen();

      std::string inst1 = "\tb" + icmp_opcode + "\t" + true_branch_label;
      auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Br_);

      std::string inst2 = "\tb\t" + false_branch_label;
      auto I2 = new SemiMachineInstruction(inst2, 0, SemiMachineInstruction::Br_);

      semiblock.addInstruction(I1);
      semiblock.addInstruction(I2);
    }
  } else {
    std::string inst = "\tb\t" + BrI->getNumOperand(0).get()->getName();
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Br_);

    semiblock.addInstruction(I);
  }

  return semiblock;
}

SemiMachineBlock IRToSemiIcmp(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto IcmpI = cast<ICmpInst>(instruction_item);
  assert(IcmpI && "this instruction should be an Icmp");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  auto I1 = new SemiMachineInstruction("\tcmp\tr1, r2", 0, SemiMachineInstruction::Cmp_);
  semiblock.addInstruction(I1);

  auto I2 = new SemiMachineInstruction("\tmov\tr3, #0", 0, SemiMachineInstruction::Mov_);
  semiblock.addInstruction(I2);

  auto I3 =
      new SemiMachineInstruction("\tmov" + IcmpI->getCmpType_codegen() + "\tr3, #1", 0, SemiMachineInstruction::Mov_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}


SemiMachineBlock IRToSemiAdd(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Add && "this instruction should be an ADD");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  auto I3 = new SemiMachineInstruction("\tadd\tr3, r1, r2", 0, SemiMachineInstruction::Add_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}

SemiMachineBlock IRToSemiSub(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Sub && "this instruction should be a SUB");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  auto I3 = new SemiMachineInstruction("\tsub\tr3, r1, r2", 0, SemiMachineInstruction::Add_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}

SemiMachineBlock IRToSemiMul(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Mul && "this instruction should be a MUL");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  auto I3 = new SemiMachineInstruction("\tmul\tr3, r1, r2", 0, SemiMachineInstruction::Mul_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}

#ifdef ARM_V8
SemiMachineBlock IRToSemiSDiv(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::SDiv && "this instruction should be a DIV");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  // TODO
  auto I3 = new SemiMachineInstruction("\tsdiv\tr3, r1, r2", 0, SemiMachineInstruction::Div_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}
#else
SemiMachineBlock IRToSemiSDiv(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::SDiv && "this instruction should be a DIV");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 0);
  semiblock += GetOperand(op2, 1);

  // TODO
  auto I3 = new SemiMachineInstruction("\tbl\t__aeabi_idiv", 0, SemiMachineInstruction::Br_);
  semiblock.addInstruction(I3);
  semiblock += StoreTempValue(instruction_item, 0);
  return semiblock;
}
#endif

SemiMachineBlock IRToSemiAnd(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::And && "this instruction should be an And");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  auto I3 = new SemiMachineInstruction("\tand\tr3, r1, r2", 0, SemiMachineInstruction::And_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}

SemiMachineBlock IRToSemiOr(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Or && "this instruction should be an OR");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  auto I3 = new SemiMachineInstruction("\tor\tr3, r1, r2", 0, SemiMachineInstruction::Or_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}

// FIXME:
// Need to implement it using Arm instruction
SemiMachineBlock IRToSemiXor(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Xor && "this instruction should be an XOR");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  auto I3 = new SemiMachineInstruction("\txor\tr3, r1, r2", 0, SemiMachineInstruction::Xor_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}

SemiMachineBlock IRToSemiAlloca(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Alloca && "this instruction should be an Alloca");
  return semiblock;
}

// 在IR中load指令的用法样例：
//       %4 = load i32, i32* %i
// 而在ARM中load相对应的指令是ldr：
//       ldr     r0, [sp]
// 所以可以暂时将[sp]替换为[i]
SemiMachineBlock IRToSemiLoad(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Load && "this instruction should be a Load");
  auto op1 = instruction_item->getNumOperand(0).get();
  std::string op1_name = instruction_item->getNumOperand(0)->getName();
  semiblock += GetOperand(op1, 1);
  std::string inst1 = "\tldr\tr3, [r1]";
  auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Ld_);
  semiblock.addInstruction(I1);
  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}

SemiMachineBlock IRToSemiStore(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Store && "this instruction should be a Store");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();
  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);
  std::string inst1 = "\tstr\tr1, [r2]";
  auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::St_);
  semiblock.addInstruction(I1);
  return semiblock;
}

SemiMachineBlock IRToSemiGetElementPtr(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto GepI = cast<GetElementPtrInst>(instruction_item);
  assert(GepI && "this instruction should be a GEP");
  auto ptr = GepI->getNumOperand(0).get();
  auto offset = GepI->getOffset();
  if (auto const_offset = cast<ConstantInt>(offset)) {
    semiblock += GetOperand(ptr, 1);
    std::string inst1 = "\tadd\tr1, r1, " + ProcessSpillOut(4*const_offset->getValue(), 4, semiblock);
    auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Add_);
    semiblock.addInstruction(I1);
    semiblock += StoreTempValue(instruction_item, 1);
  }
  else{
    assert(isa<Instruction>(offset) && "Offset of gep should be return result of another inst");
    semiblock += GetOperand(ptr, 1);
    semiblock += GetOperand(offset, 2);
    std::string inst = "\tlsl\tr2, r2, #2";
    semiblock.addInstruction(new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Lsl_));
    std::string inst1 = "\tadd\tr3, r1, r2";
    semiblock.addInstruction(new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Add_));
    semiblock += StoreTempValue(instruction_item, 3);
  }
  return semiblock;
}

SemiMachineBlock IRToSemiCall(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Call && "this instruction should be a Call");
  for (int i = 0; i < instruction_item->getNumOperands() - 1; i++) {
    std::string inst;
    if(i < 4){
      semiblock += GetOperand(instruction_item->getNumOperand(i).get(), i);
    }
    else{
      semiblock += GetOperand(instruction_item->getNumOperand(i).get(), 4);
      // inst = "\tstr\tr1, [sp, #" + std::to_string(i * 4) + "]";
      inst = "\tstr\tr4, [sp, " + ProcessSpillOut((i - 4) * 4, 5, semiblock) + "]";
      auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::St_);
      semiblock.addInstruction(I);
    }
  }
  std::string func_name, inst1;
  func_name = instruction_item->getNumOperand(-1)->getName();
  inst1 = "\tbl\t" + func_name;
  auto I = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Br_);
  semiblock.addInstruction(I);
  auto *CI = cast<CallInst>(instruction_item);
  if (!CI->getFunctionType()->isReturnVoid()) {
    semiblock += StoreTempValue(instruction_item, 0);
  }
  return semiblock;
}

// 不需要翻译
SemiMachineBlock IRToSemiZExt(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  return semiblock;
}
// #endif

#ifdef ARM_V8
SemiMachineBlock IRToSemiSRem(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::SRem && "this instruction should be a SRem");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 1);
  semiblock += GetOperand(op2, 2);

  // TODO
  auto I3 = new SemiMachineInstruction("\tsrem\tr3, r1, r2", 0, SemiMachineInstruction::Div_);
  semiblock.addInstruction(I3);

  semiblock += StoreTempValue(instruction_item, 3);
  return semiblock;
}
#else
SemiMachineBlock IRToSemiSRem(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::SRem && "this instruction should be a Rem");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();

  semiblock += GetOperand(op1, 0);
  semiblock += GetOperand(op2, 1);

  auto I3 = new SemiMachineInstruction("\tbl\t__aeabi_idivmod", 0, SemiMachineInstruction::Br_);
  semiblock.addInstruction(I3);
  // 注意：取模的时候，函数返回值在r1
  semiblock += StoreTempValue(instruction_item, 1);
  return semiblock;
}
#endif

SemiMachineBlock InstructionToSemiMachine(Instruction *instruction_item) {
  // std::cout << "Opcode is " << instruction_item->getOpcodeName() << std::endl;
  SemiMachineBlock instruction = SemiMachineBlock();
  if (instruction_item->getOpcode() == Instruction::Opcode::Ret) {
    return IRToSemiRet(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Br) {
    return IRToSemiBr(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Icmp) {
    return IRToSemiIcmp(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Add) {
    return IRToSemiAdd(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Sub) {
    return IRToSemiSub(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Mul) {
    return IRToSemiMul(instruction_item);
  }
  // FIXME:
  // Arm v7 Vs. Arm v8
  if (instruction_item->getOpcode() == Instruction::Opcode::SDiv) {
    return IRToSemiSDiv(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::And) {
    return IRToSemiAnd(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Or) {
    return IRToSemiOr(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Xor) {
    return IRToSemiXor(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Alloca) {
    return IRToSemiAlloca(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Load) {
    return IRToSemiLoad(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Store) {
    return IRToSemiStore(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::ZExt) {
    return IRToSemiZExt(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Call) {
    return IRToSemiCall(instruction_item);
  }
  // FIXME:
  if (instruction_item->getOpcode() == Instruction::Opcode::SRem) {
    return IRToSemiSRem(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::GetElementPtr) {
    return IRToSemiGetElementPtr(instruction_item);
  }
  if(instruction_item->getOpcode() == Instruction::Opcode::PHI){
    return instruction;
  }
  return instruction;
}
} // namespace semimachine
